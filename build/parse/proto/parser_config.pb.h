// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: parse/proto/parser_config.proto

#ifndef PROTOBUF_parse_2fproto_2fparser_5fconfig_2eproto__INCLUDED
#define PROTOBUF_parse_2fproto_2fparser_5fconfig_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace hotbox {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_parse_2fproto_2fparser_5fconfig_2eproto();
void protobuf_AssignDesc_parse_2fproto_2fparser_5fconfig_2eproto();
void protobuf_ShutdownFile_parse_2fproto_2fparser_5fconfig_2eproto();

class LibSVMParserConfig;
class ParserConfig;

// ===================================================================

class ParserConfig : public ::google::protobuf::Message {
 public:
  ParserConfig();
  virtual ~ParserConfig();

  ParserConfig(const ParserConfig& from);

  inline ParserConfig& operator=(const ParserConfig& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ParserConfig& default_instance();

  enum ConfigCase {
    kLibsvmConfig = 1,
    CONFIG_NOT_SET = 0,
  };

  void Swap(ParserConfig* other);

  // implements Message ----------------------------------------------

  inline ParserConfig* New() const { return New(NULL); }

  ParserConfig* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ParserConfig& from);
  void MergeFrom(const ParserConfig& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(ParserConfig* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional .hotbox.LibSVMParserConfig libsvm_config = 1;
  bool has_libsvm_config() const;
  void clear_libsvm_config();
  static const int kLibsvmConfigFieldNumber = 1;
  const ::hotbox::LibSVMParserConfig& libsvm_config() const;
  ::hotbox::LibSVMParserConfig* mutable_libsvm_config();
  ::hotbox::LibSVMParserConfig* release_libsvm_config();
  void set_allocated_libsvm_config(::hotbox::LibSVMParserConfig* libsvm_config);

  ConfigCase config_case() const;
  // @@protoc_insertion_point(class_scope:hotbox.ParserConfig)
 private:
  inline void set_has_libsvm_config();

  inline bool has_config() const;
  void clear_config();
  inline void clear_has_config();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  union ConfigUnion {
    ConfigUnion() {}
    ::hotbox::LibSVMParserConfig* libsvm_config_;
  } config_;
  mutable int _cached_size_;
  ::google::protobuf::uint32 _oneof_case_[1];

  friend void  protobuf_AddDesc_parse_2fproto_2fparser_5fconfig_2eproto();
  friend void protobuf_AssignDesc_parse_2fproto_2fparser_5fconfig_2eproto();
  friend void protobuf_ShutdownFile_parse_2fproto_2fparser_5fconfig_2eproto();

  void InitAsDefaultInstance();
  static ParserConfig* default_instance_;
};
// -------------------------------------------------------------------

class LibSVMParserConfig : public ::google::protobuf::Message {
 public:
  LibSVMParserConfig();
  virtual ~LibSVMParserConfig();

  LibSVMParserConfig(const LibSVMParserConfig& from);

  inline LibSVMParserConfig& operator=(const LibSVMParserConfig& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const LibSVMParserConfig& default_instance();

  void Swap(LibSVMParserConfig* other);

  // implements Message ----------------------------------------------

  inline LibSVMParserConfig* New() const { return New(NULL); }

  LibSVMParserConfig* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const LibSVMParserConfig& from);
  void MergeFrom(const LibSVMParserConfig& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(LibSVMParserConfig* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional bool feature_one_based = 1;
  void clear_feature_one_based();
  static const int kFeatureOneBasedFieldNumber = 1;
  bool feature_one_based() const;
  void set_feature_one_based(bool value);

  // optional bool label_one_based = 2;
  void clear_label_one_based();
  static const int kLabelOneBasedFieldNumber = 2;
  bool label_one_based() const;
  void set_label_one_based(bool value);

  // @@protoc_insertion_point(class_scope:hotbox.LibSVMParserConfig)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  bool feature_one_based_;
  bool label_one_based_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_parse_2fproto_2fparser_5fconfig_2eproto();
  friend void protobuf_AssignDesc_parse_2fproto_2fparser_5fconfig_2eproto();
  friend void protobuf_ShutdownFile_parse_2fproto_2fparser_5fconfig_2eproto();

  void InitAsDefaultInstance();
  static LibSVMParserConfig* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// ParserConfig

// optional .hotbox.LibSVMParserConfig libsvm_config = 1;
inline bool ParserConfig::has_libsvm_config() const {
  return config_case() == kLibsvmConfig;
}
inline void ParserConfig::set_has_libsvm_config() {
  _oneof_case_[0] = kLibsvmConfig;
}
inline void ParserConfig::clear_libsvm_config() {
  if (has_libsvm_config()) {
    delete config_.libsvm_config_;
    clear_has_config();
  }
}
inline  const ::hotbox::LibSVMParserConfig& ParserConfig::libsvm_config() const {
  // @@protoc_insertion_point(field_get:hotbox.ParserConfig.libsvm_config)
  return has_libsvm_config()
      ? *config_.libsvm_config_
      : ::hotbox::LibSVMParserConfig::default_instance();
}
inline ::hotbox::LibSVMParserConfig* ParserConfig::mutable_libsvm_config() {
  if (!has_libsvm_config()) {
    clear_config();
    set_has_libsvm_config();
    config_.libsvm_config_ = new ::hotbox::LibSVMParserConfig;
  }
  // @@protoc_insertion_point(field_mutable:hotbox.ParserConfig.libsvm_config)
  return config_.libsvm_config_;
}
inline ::hotbox::LibSVMParserConfig* ParserConfig::release_libsvm_config() {
  if (has_libsvm_config()) {
    clear_has_config();
    ::hotbox::LibSVMParserConfig* temp = config_.libsvm_config_;
    config_.libsvm_config_ = NULL;
    return temp;
  } else {
    return NULL;
  }
}
inline void ParserConfig::set_allocated_libsvm_config(::hotbox::LibSVMParserConfig* libsvm_config) {
  clear_config();
  if (libsvm_config) {
    set_has_libsvm_config();
    config_.libsvm_config_ = libsvm_config;
  }
  // @@protoc_insertion_point(field_set_allocated:hotbox.ParserConfig.libsvm_config)
}

inline bool ParserConfig::has_config() const {
  return config_case() != CONFIG_NOT_SET;
}
inline void ParserConfig::clear_has_config() {
  _oneof_case_[0] = CONFIG_NOT_SET;
}
inline ParserConfig::ConfigCase ParserConfig::config_case() const {
  return ParserConfig::ConfigCase(_oneof_case_[0]);
}
// -------------------------------------------------------------------

// LibSVMParserConfig

// optional bool feature_one_based = 1;
inline void LibSVMParserConfig::clear_feature_one_based() {
  feature_one_based_ = false;
}
inline bool LibSVMParserConfig::feature_one_based() const {
  // @@protoc_insertion_point(field_get:hotbox.LibSVMParserConfig.feature_one_based)
  return feature_one_based_;
}
inline void LibSVMParserConfig::set_feature_one_based(bool value) {
  
  feature_one_based_ = value;
  // @@protoc_insertion_point(field_set:hotbox.LibSVMParserConfig.feature_one_based)
}

// optional bool label_one_based = 2;
inline void LibSVMParserConfig::clear_label_one_based() {
  label_one_based_ = false;
}
inline bool LibSVMParserConfig::label_one_based() const {
  // @@protoc_insertion_point(field_get:hotbox.LibSVMParserConfig.label_one_based)
  return label_one_based_;
}
inline void LibSVMParserConfig::set_label_one_based(bool value) {
  
  label_one_based_ = value;
  // @@protoc_insertion_point(field_set:hotbox.LibSVMParserConfig.label_one_based)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace hotbox

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_parse_2fproto_2fparser_5fconfig_2eproto__INCLUDED
