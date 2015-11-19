#include "util/file_util.hpp"
#include "util/hotbox_exceptions.hpp"
#include "util/class_registry.hpp"
#include "util/compressor/all.hpp"
#include <glog/logging.h>
#include <sstream>
#include <memory>
#include <cmath>

#include <google/protobuf/io/zero_copy_stream_impl.h>

namespace hotbox {
  namespace io {

std::unique_ptr<dmlc::SeekStream> OpenFileStream(const std::string& file_path){
  std::unique_ptr<dmlc::SeekStream> sk
        (dmlc::SeekStream::CreateForRead(file_path.c_str())); 
  if (!sk) {
    throw FailedFileOperationException("Failed to open " + file_path
        + " for read.");
  }
  return sk;
}

// Implementation using zero_copy_stream_impl of protobuf.
std::string ReadCompressedFile(const std::string& file_path,
  Compressor compressor, 
  int32_t file_begin, int32_t len) {
  // sk is a smart pointer. We do own the SeekStream pointer.
  auto sk = io::OpenFileStream(file_path.c_str());  
  dmlc::istream in(sk.get()); // type conversion.
  // By default, read the whole file.
  if(len == 0) {
    len = GetFileSize(file_path);
  }
  auto fp = make_unique<google::protobuf::io::IstreamInputStream>
      (dynamic_cast<std::basic_istream<char>*>(&in),len);

  const void* buffer;
  int size;
  fp->Skip(file_begin); // offset to start reading.
  // Read a bulk of size len, into buffer, length returned in size
  bool b_succeed = fp->Next(&buffer, &size); 
  if (!b_succeed || (len != size)) {
    throw FailedFileOperationException("Failed to read file: " + file_path
        + "\n");
  }
  return ReadCompressedString(buffer, size, compressor);
}

size_t WriteSizeLimitedFiles(const std::string& file_dir, int32_t& file_idx,
    const std::string& data) {
  int32_t curr_atom_idx = file_idx;
  int32_t size_written = 0;

  std::string curr_file_path = file_dir + std::to_string(curr_atom_idx);
  size_t curr_atom_size = GetFileSize(curr_file_path);
  int32_t data_offset = kATOM_SIZE_MB - curr_atom_size;
  LOG(INFO) << "WriteSizeLimitedFiles: "
            << "Size Limit: " << kATOM_SIZE_MB << ". ";
  LOG(INFO) << "Space Left in Atom " << curr_atom_idx <<": " << data_offset;
  // Assume that an atom obj will never excceed kATOM_SIZE_MB, 
  // i.e. span 2 files.
  size_written += AppendFile(curr_file_path, data.substr(0, data_offset));
  if (data_offset < data.size()) {
    curr_file_path = file_dir + std::to_string(++curr_atom_idx);
    size_written += AppendFile(curr_file_path, data.substr(data_offset, 
                        kATOM_SIZE_MB));
    LOG(INFO) << "Bytes Written in Atom " << curr_atom_idx
              << ": " << data.size() - data_offset;
  } 
  file_idx = curr_atom_idx;
  LOG(INFO) << "After Writing Atom Idx: " << file_idx;
  return size_written;
/*
  int32_t curr_X = data.size() + curr_atom_size + kATOM_SIZE_MB;
  int32_t loop_size = curr_X / kATOM_SIZE_MB; // MACRO can't be put in demoninator?
  LOG(INFO) << "WriteSizeLimitedFiles: "
            << "Size Limit: " << kATOM_SIZE_MB << ". "
            << "Current Atom File: " << curr_atom_idx << ". "
            // << "Current X: " << curr_X << ". "
            // << "Data Size: " << data.size() << ". "
            << "curr_atom_size " << curr_atom_size << ". "
            << "Span # Atom Files: " << loop_size << ". ";
  
  //TODO(weiren): find a non-copy method for compressing data.
  for(int i=0; i < loop_size; i++, curr_atom_idx++) {
    // Write to the current atom file.
    if(i == 0) {
      data_offset = kATOM_SIZE_MB - curr_atom_size;
      LOG(INFO) << "Space Left in Atom " << curr_atom_idx <<": " << data_offset;
      size_written += AppendFile(curr_file_path, data.substr(0, data_offset));
    }
    // Write whole size_limit files.
    else if (i < loop_size - 1) {
      curr_file_path = file_dir + std::to_string(curr_atom_idx);
<<<<<<< Updated upstream
      size_written += AppendFile(curr_file_path, data.substr(data_offset, kATOM_SIZE_MB));
      data_offset += kATOM_SIZE_MB;
=======
      size_written += AppendFile(curr_file_path,
          data.substr(data_offset, atom_size_mb));
      data_offset += atom_size_mb;
>>>>>>> Stashed changes
      LOG(INFO) << "Data String Seeking Position: " << data_offset;
    }
    // Write the left data to a new file.
    else {
      curr_file_path = file_dir + std::to_string(curr_atom_idx);
      //int32_t len = data.size() - data_offset;
      //size_written += AppendFile(curr_file_path, data.substr(data_offset, len));
      size_written += AppendFile(curr_file_path, data.substr(data_offset, kATOM_SIZE_MB));
      LOG(INFO) << "Last, Data String Seeking Position. ";// << data_offset;
    }
  }
  file_idx = --curr_atom_idx;
*/
}

size_t WriteAtomFiles(const std::string& file_dir, int32_t& file_idx,
    const std::string& data, Compressor compressor) {
  // Fisrt Compress then write to separate files.
  if (compressor != Compressor::NO_COMPRESS) {
    LOG(INFO) << "Compressing Atom Data: " << data.size();
    auto& registry = ClassRegistry<CompressorIf>::GetRegistry();
    std::unique_ptr<CompressorIf> compressor_if = 
                          registry.CreateObject(compressor);
    std::string compressed = compressor_if->Compress(data);
    LOG(INFO) << "Compressed String Len: " << compressed.size(); 
    LOG(INFO) << "Writing to Atom Files. ";
    return WriteSizeLimitedFiles(file_dir, file_idx, compressed);
  } else {
    LOG(INFO) << "Writing UnCompressed Atom Data.";
    return WriteSizeLimitedFiles(file_dir, file_idx, data);
  }
}

size_t WriteCompressedFile(const std::string& file_path,
    const std::string& data, Compressor compressor) {
  // We do own this pointer.
  std::unique_ptr<dmlc::Stream> os(dmlc::Stream::Create(file_path.c_str(), "w"));
  if (!os) {
    throw FailedFileOperationException("Failed to open " + file_path
        + " for write.");
  }
  LOG(INFO) << "Writing to " << file_path << " using compressor "
    << compressor;
  if (compressor != Compressor::NO_COMPRESS) {
    // Compress always succeed.
    auto& registry = ClassRegistry<CompressorIf>::GetRegistry();
    std::unique_ptr<CompressorIf> compressor_if =
      registry.CreateObject(compressor);
    std::string compressed = compressor_if->Compress(data);
    os->Write(compressed.c_str(), compressed.size());
    return compressed.size();
  }
  os->Write(data.c_str(), data.size());
  return data.size();
}

size_t AppendFile(const std::string& file_path,
    const std::string& data) {
  // We do own this pointer.
  std::unique_ptr<dmlc::Stream> os(dmlc::Stream::Create(file_path.c_str(),
        "a"));
  if (!os) {
    throw FailedFileOperationException("Failed to open " + file_path
        + " for write.");
  }
  LOG(INFO) << "Writing to " << file_path;
  os->Write(data.c_str(), data.size());
  return data.size();
}

std::string ReadFile(const std::string& file_path) {
  return ReadCompressedFile(file_path, Compressor::NO_COMPRESS,0,0);
}

bool Exists(const std::string& path) {
  return dmlc::io::FileSystem::exist(path);
}

bool IsDirectory(const std::string& file_path) {
  return dmlc::io::FileSystem::is_directory(file_path);
}

int CreateDirectory(const std::string& file_path) {
  dmlc::io::URI path(file_path.c_str());
  // We don't own the FileSystem pointer.
  dmlc::io::FileSystem *fs = dmlc::io::FileSystem::GetInstance(path.protocol);
  return fs->CreateDirectory(path);
}

// Return the path of a file or directory
std::string Path(const std::string& file_path) {
  return dmlc::io::FileSystem::path(file_path);
}

// Return the parent path of a given file or directory.
std::string ParentPath(const std::string& file_path) {
  return dmlc::io::FileSystem::parent_path(file_path);
}

size_t GetFileSize(const std::string& file_path) {
  dmlc::io::URI path(file_path.c_str());
  // We don't own the FileSystem pointer.
  dmlc::io::FileSystem *fs = dmlc::io::FileSystem::GetInstance(path.protocol);
  dmlc::io::FileInfo info = fs->GetPathInfo(path);
  return info.size;
}

}  // namaspace hotbox::io
}  // namespace hotbox
