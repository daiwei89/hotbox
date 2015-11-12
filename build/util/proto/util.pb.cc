// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: util/proto/util.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "util/proto/util.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace hotbox {

namespace {

const ::google::protobuf::EnumDescriptor* Compressor_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* FileFormat_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* StatusCode_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_util_2fproto_2futil_2eproto() {
  protobuf_AddDesc_util_2fproto_2futil_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "util/proto/util.proto");
  GOOGLE_CHECK(file != NULL);
  Compressor_descriptor_ = file->enum_type(0);
  FileFormat_descriptor_ = file->enum_type(1);
  StatusCode_descriptor_ = file->enum_type(2);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_util_2fproto_2futil_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_util_2fproto_2futil_2eproto() {
}

void protobuf_AddDesc_util_2fproto_2futil_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\025util/proto/util.proto\022\006hotbox*)\n\nCompr"
    "essor\022\n\n\006SNAPPY\020\000\022\017\n\013NO_COMPRESS\020\001*F\n\nFi"
    "leFormat\022\027\n\023UNKNOWN_FILE_FORMAT\020\000\022\n\n\006LIB"
    "SVM\020\001\022\007\n\003CSV\020\002\022\n\n\006FAMILY\020\003*&\n\nStatusCode"
    "\022\006\n\002OK\020\000\022\020\n\014DB_NOT_FOUND\020\001b\006proto3", 194);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "util/proto/util.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_util_2fproto_2futil_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_util_2fproto_2futil_2eproto {
  StaticDescriptorInitializer_util_2fproto_2futil_2eproto() {
    protobuf_AddDesc_util_2fproto_2futil_2eproto();
  }
} static_descriptor_initializer_util_2fproto_2futil_2eproto_;
const ::google::protobuf::EnumDescriptor* Compressor_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Compressor_descriptor_;
}
bool Compressor_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* FileFormat_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return FileFormat_descriptor_;
}
bool FileFormat_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* StatusCode_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return StatusCode_descriptor_;
}
bool StatusCode_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace hotbox

// @@protoc_insertion_point(global_scope)
