#pragma once

#include <vector>
#include <thread>
#include <string>
#include <mutex>
#include <queue>
#include <atomic>
#include <condition_variable>
#include "db/proto/db.pb.h"
#include "metrics/metrics.hpp"
#include "schema/all.hpp"
#include "folly/MPMCQueue.h"

namespace hotbox {
/*
MTTransformer works as described below:
                 num_io_threads                                 num_tf_threads
 io task queue --> 2.IoTaskLoop --> transform task queue --> 3.TransformTaskLoop
       |                                                           |
 1.Translate data range                  4.NextBatch     <--    batch queue
*/

/** Some explaination:
 *  tf. tf is short for transform
 *  bt. bt is short for batch
 *  Batch. In a atom file, there are many individual blocks that can be
 *    decompressed and transformed individually. I call the transformed data
 *    from a block "batch". If some datums in a block if out of the requested
 *    data range, such datums will be abandoned before transforming.
 *
 */

  // One task for one atom file.
  // Both IoTaskLoop and TransformTaskLoop use this structure.
  struct Task {
    int atom_id;
    BigInt datum_begin;  // datum range within atom file
    BigInt datum_end;
    std::string buffer;  // will be filled in IoTaskLoop
  };


class MTTransformer {
 public:
  MTTransformer(const SessionProto &session_proto,
                std::vector<std::function<
                  void(std::vector<TransDatum*>*)>> transforms,
                size_t data_begin, size_t data_end,
                int num_io_threads,
                int num_transform_threads,
                int transform_task_limit,
                int batch_limit);

  ~MTTransformer();

  // check if there is any transformed or untransformed data batch
  bool HasNextBatch() const;
  // NextBatch will take a batch from bt_queue_.
  // It will be blocked only if no batch is available
  // It will transfer the returned pointer's ownership to caller.
  // It The calller is responsible to release it
  // It will return nullptr if HasNextBatch returns false
  std::vector<FlexiDatum> *NextBatch();

  void Start();

  // Collect and gather the metrics ThreadTransStats and produce TransStats
  std::unique_ptr<TransStats> GetMetrics();
  
 private:
  // It will translate data range into io tasks and push them to io_queue_.
  void Translate(size_t data_begin, size_t data_end);

  // notify all workers to stop and delete unused batches
  void Destory();

  // 1. IoTaskLoop will take Task from io_queue_ and load file into Task.buffer,
  // 2. then push the Task into tf_queue_
  // 3. Loop 1 and 2 until io_queue_ is empty.
  // each io_worker will run this function.
  void IoTaskLoop();

  // TransformTaskLoop will take Task from tf_queue_, then decompress,
  // deserialize it into a batch. Then it will do transforms on the batch and
  // push the batch to bt_queue_.
  // each transform worker will run this function.
  void TransformTaskLoop(int);


  const SessionProto &session_proto_;

  std::vector<std::thread> io_workers_;
  std::vector<std::thread> tf_workers_;
  std::vector<std::function<void(std::vector<TransDatum*>*)>> transforms_;

  // imagine blocking queue
  std::unique_ptr<folly::MPMCQueue<Task,std::atomic,true> > io_queue_;  // io files queue
  std::unique_ptr<folly::MPMCQueue<Task> > tf_queue_;  // buffer queue
  std::unique_ptr<folly::MPMCQueue<std::vector<FlexiDatum> *> > bt_queue_;  // batch queue

  // mutex
  // IoTaskLoop and TransformTaskLoop will check stop_flag_
  // whether it should stop or not
  std::atomic_bool stop_flag_{false};

  // total_batches is in the view of HasNextBatch(). It's used to see if there
  // is any batch in the batch queue or to be generated by TransformTaskLoop()
  //
  // if I don't use it. when I wants to check if there is any batch, I have
  // to check the batch queue,  tf task queue, and io queue. if all the three
  // queues are empty, it doesn't mean there is no batch. for example, there
  // is only one transform task in buffer_queue and no batches in batch queue.
  // Then it's taken by TransformTaskLoop. Now both queues are empty while there
  // is one batch to be generated by TransformTaskLoop. see below, one way is to
  // add more variable to count how many tasks hold by TransformTaskLoop, but
  // it's too complex.
  // io_queue     --> empty
  //      |
  // io_task_loop --> holds nothing
  //      |
  // tf_queue     --> empty
  //      |
  // TransformTaskLoop --> hold one transform task
  //      |
  // bt_queue     --> empty
  //
  // set by Translate(), equals to # of total blocks within data range
  // decrease 1 by NextBatch()
  std::atomic_int total_batches_;  // protected by bt_mtx_

  // total_tf_tasks_ is similar with total_batches_. it's used by
  // TransformTaskLoop to see if there is any TfTasks in tf_queue or to be
  // generated.
  //
  // set by Translate(), equals to # of total blocks within data range // decrease 1 when TransformTaskLoop pick up a transform task from tf_queue_
  std::atomic_int total_tf_tasks_;  // protected by tf_mtx_

  const int num_io_workers_;
  const int num_tf_workers_;

  // transform task queue size limit, used for io speed control
  const int tf_limit_;
  // batch queue size limit, used for transform speed control
  const int bt_limit_;

  const BigInt data_begin_;
  const BigInt data_end_;
  std::vector<BigInt> datum_ids_;

  ThreadTransStats metrics_;
};

}  // namespace hotbox
