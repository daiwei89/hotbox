#include "client/mt_transformer.hpp"
#include "util/global_config.hpp"
#include <glog/logging.h>
#include <algorithm>
#include <string>
#include <vector>
#include "util/all.hpp"
#include <chrono>
#include <ctime>

namespace hotbox {

MTTransformer::MTTransformer(const SessionProto &session_proto,
                             std::vector<std::function<
                               void(std::vector<TransDatum*>*)>> transforms,
                             size_t data_begin, size_t data_end,
                             int num_io_threads,
                             int num_transform_threads,
                             int transform_task_limit,
                             int batch_limit) : session_proto_(session_proto),
  transforms_(transforms),
  num_io_workers_(std::min(num_io_threads, transform_task_limit)),
  num_tf_workers_(std::min(num_transform_threads, batch_limit)),
  tf_limit_(transform_task_limit), bt_limit_(batch_limit),
  data_begin_(data_begin), data_end_(data_end),
  datum_ids_(session_proto_.file_map().datum_ids().cbegin(),
             session_proto_.file_map().datum_ids().cend()) {
  // Last atom file range ends with num_data.
  datum_ids_.push_back(session_proto_.file_map().num_data());

  num_cache_workers_ = num_io_workers_/2+1;
  Start();
}


MTTransformer::~MTTransformer() {
  Destory();
}

void MTTransformer::IoTaskLoop() {
  // LOG(INFO) << "IoTaskLoop " << std::this_thread::get_id() << " Starts...";
  while (true) {
    TaskId taskid;
    // get atom_id from io_queue
    if (io_queue_->isEmpty() || stop_flag_) {
      break;
    }
    io_queue_->blockingRead(taskid);

    auto& task = tasks_[taskid];

    std::string path = session_proto_.file_map().atom_path()
                              + std::to_string(task.atom_id);
    //task.buffer = std::move(io::ReadCompressedFile(
    //                          path, session_proto_.compressor()));
    task.buffer = std::move(io::ReadCompressedFile(
                              path, Compressor::NO_COMPRESS));

    cache_read_queue_->blockingWrite(taskid);
  }
  // LOG(INFO) << "IoTaskLoop " << std::this_thread::get_id() << " ends...";
}

// read cache and pass to tf
void MTTransformer::CacheReadLoop() {
  while (true) {
    TaskId taskid;
    if (stop_flag_ || total_tf_tasks_ <= 0)
      break;
    cache_read_queue_->blockingRead(taskid);
    if (taskid == -1) break; // sentinel task for termination

    auto& task = tasks_[taskid];

    tf_queue_->blockingWrite(taskid);
  }
}

// tid: transformer id
void MTTransformer::TransformTaskLoop(int tid) {
  auto& global_config = GlobalConfig::GetInstance();
  int batch_size = global_config.Get<int>("transform_batch_size");

  while (true) {
    TaskId taskid;
    // get content buffer from bf_queue
    if (stop_flag_ || total_tf_tasks_ <= 0)
      break;
    tf_queue_->blockingRead(taskid);
    --total_tf_tasks_;

    if (taskid == -1) break; // sentinel task for termination
    auto& task = tasks_[taskid];

    DBAtom atom_proto = StreamDeserialize<DBAtom>(task.buffer);
    task.buffer = "";
    task.buffer.shrink_to_fit(); // free unused memory
    auto output_store_type = session_proto_.output_store_type();
    auto output_dim = session_proto_.output_dim();
    std::vector<FlexiDatum> *vec = new std::vector<FlexiDatum>(
      task.datum_end - task.datum_begin);

    // Collect transform ranges to std::vector
    std::vector<TransformOutputRange> ranges(transforms_.size());
    for (int i = 0; i < transforms_.size(); ++i) {
      ranges[i] = session_proto_.transform_output_ranges(i);
    }
    // Trim data for atom files at the boundaries.
    int num_release = atom_proto.datum_protos_size() - task.datum_end;
    for (int j = 0; j < num_release; ++j) {
      delete atom_proto.mutable_datum_protos()->ReleaseLast();
    }
    // do transform by mini-batch
    int atom_size = atom_proto.datum_protos_size() - task.datum_begin;
    int num_batches = atom_size / batch_size;
    if (atom_size % batch_size != 0) {
      num_batches++;
    }
    for (int b = 0; b < num_batches; ++b) {
      int offset = b * batch_size;
      int num_items = (b == num_batches - 1) ? (atom_size - offset)
        : batch_size;
      std::vector<TransDatum*> data_batch(num_items);
      for (int j = 0; j < num_items; ++j) {
        DatumBase* datum_base = new DatumBase(
          atom_proto.mutable_datum_protos()->ReleaseLast());
        auto& last_range = session_proto_.transform_output_ranges(
            transforms_.size() - 1);
        data_batch[j] = new TransDatum(datum_base, session_proto_.label(),
                        session_proto_.weight(), output_store_type, output_dim,
                        ranges);
      }

      BigInt output_counter_old = 0;
      for (int t = 0; t < transforms_.size(); ++t) {
        for (int j = 0; j < num_items; ++j) {
          data_batch[j]->ReadyTransform(
            session_proto_.transform_output_ranges(t));
        }
        std::clock_t c_start = std::clock();
        transforms_[t](&data_batch);
        std::clock_t c_end = std::clock();

        BigInt output_counter_new = 0;
        for (int j = 0; j < num_items; ++j) {
          output_counter_new += data_batch[j]->GetOutputCounter();
        }

        DLOG(INFO) << "TFTaskLoop " << tid << " finish transform #" << t << " \
          in " << c_end - c_start << " ticks, generating " <<
          output_counter_new - output_counter_old << " values.";

        metrics_[tid][t].set_time(metrics_[tid][t].time() + (c_end-c_start) /
            CLOCKS_PER_SEC);
        metrics_[tid][t].set_space(metrics_[tid][t].space() +
            output_counter_new - output_counter_old);
        output_counter_old = output_counter_new;
      }
      for (int j = 0; j < num_items; ++j) {
        int i = task.datum_end - (j + offset) - 1;
        (*vec)[i - task.datum_begin] = std::move(data_batch[j]->GetFlexiDatum());
        delete data_batch[j];
      }
    }

    cache_write_queue_->blockingWrite(taskid);
    bt_queue_->blockingWrite(vec);
  }
  // LOG(INFO) << "TFTaskLoop " << std::this_thread::get_id() << " ends...";
}

// write cache out and pass output to bt_queue_
void MTTransformer::CacheWriteLoop() {
  while (true) {
    TaskId taskid;
    if (stop_flag_)
      break;
    cache_write_queue_->blockingRead(taskid);
    if (taskid == -1) break; // sentinel task for termination

    auto& task = tasks_[taskid];
  }
}

void MTTransformer::Destory() {
  // set stop flag
  stop_flag_ = true;

  // notify all workers to check stop flag and exit
  for (int i = 0; i < num_cache_workers_; i++) {
    cache_read_queue_->blockingWrite(-1);
  }
  for (int i = 0; i < num_tf_workers_; i++) {
    tf_queue_->blockingWrite(-1);
  }
  for (int i = 0; i < num_cache_workers_; i++) {
    cache_write_queue_->blockingWrite(-1);
  }

  for (auto &worker : io_workers_) {
    if (worker.joinable())
      worker.join();
  }

  for (auto &worker : cache_read_workers_) {
    if (worker.joinable())
      worker.join();
  }
  
  for (auto &worker : tf_workers_) {
    if (worker.joinable())
      worker.join();
  }

  for (auto &worker : cache_write_workers_) {
    if (worker.joinable())
      worker.join();
  }

  // delete any held pointers
  while (!bt_queue_->isEmpty()) {
    std::vector<FlexiDatum> * batch;
    bt_queue_->blockingRead(batch);
    delete batch;
  }
  LOG(INFO) << "MTTransform finished. Bye!";
}

std::vector<FlexiDatum> *MTTransformer::NextBatch() {
  if (total_batches_ <= 0) {
    return nullptr;
  }
  std::vector<FlexiDatum> *vec = nullptr;
  bt_queue_->blockingRead(vec);
  ///
  // for (int i = 0; i < vec->size(); ++i) {
  //   LOG(INFO) << (*vec)[i].ToString();
  // }
  total_batches_--;
  return vec;
}

// split data range into subrange group by atom file
void
MTTransformer::Translate(size_t data_begin, size_t data_end) {
  CHECK_LT(data_begin, data_end);
  auto low = std::upper_bound(datum_ids_.cbegin(), datum_ids_.cend(),
                              data_begin) - datum_ids_.cbegin() - 1;
  auto high = std::upper_bound(datum_ids_.cbegin(), datum_ids_.cend(),
                               data_end) - datum_ids_.cbegin();
  if (high == datum_ids_.size())
    high--;
  tasks_.reserve(high-low);

  io_queue_ = make_unique<folly::MPMCQueue<TaskId> >(high-low);
  tf_queue_ = make_unique<folly::MPMCQueue<TaskId> >(tf_limit_);  // buffer queue
  bt_queue_ = make_unique<folly::MPMCQueue<std::vector<FlexiDatum> *> >(bt_limit_);  // batch queue
  cache_read_queue_ = make_unique<folly::MPMCQueue<TaskId> >(num_io_workers_);
  cache_write_queue_ = make_unique<folly::MPMCQueue<TaskId> >(tf_limit_);


  for (int atom_id = low; atom_id < high; atom_id++) {
    tasks_[atom_id].datum_begin = std::max(data_begin, (size_t)datum_ids_[atom_id])
                      - datum_ids_[atom_id];
    tasks_[atom_id].datum_end = std::min(data_end, (size_t)datum_ids_[atom_id + 1])
                      - datum_ids_[atom_id];
    io_queue_->blockingWrite(atom_id);
  }

  total_tf_tasks_ = io_queue_->size();
  total_batches_ = io_queue_->size();
}


void MTTransformer::Start() {
  // metrics
  metrics_.resize(num_tf_workers_, TransStats(transforms_.size()));
  // translate data range into io tasks
  Translate(data_begin_, data_end_);

  for (int i = 0; i < num_io_workers_; i++) {
    io_workers_.push_back(std::thread([this]() {
      this->IoTaskLoop();
    }));
  }

  for (int i = 0; i < num_cache_workers_; i++) {
    cache_read_workers_.push_back(std::thread([this]() {
      this->CacheReadLoop();
    }));
    cache_write_workers_.push_back(std::thread([this]() {
      this->CacheWriteLoop();
    }));
  }

  for (int i = 0; i < num_tf_workers_; i++) {
    tf_workers_.push_back(std::thread([this, i]() {
      this->TransformTaskLoop(i);
    }));
  }
}

bool MTTransformer::HasNextBatch() const {
  return total_batches_;
}

std::unique_ptr<TransStats> MTTransformer::GetMetrics() {
  auto ret = std::unique_ptr<TransStats>(new TransStats(transforms_.size()));
  for (auto it = metrics_.begin(); it != metrics_.end(); ++it) {
    for (int i = 0; i < transforms_.size(); i++) {
      auto transform_stat = (*ret)[i];
      transform_stat.set_time(transform_stat.time() + (*it)[i].time());
      transform_stat.set_space(transform_stat.space() + (*it)[i].space());
    }
  }
  return ret;
}

}  // namespace hotbox
