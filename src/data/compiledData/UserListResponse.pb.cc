// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UserListResponse.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "UserListResponse.pb.h"

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

namespace UserListResponse {

namespace {

const ::google::protobuf::Descriptor* FollowListResponse_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  FollowListResponse_reflection_ = NULL;
const ::google::protobuf::Descriptor* FollowedListResponse_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  FollowedListResponse_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_UserListResponse_2eproto() {
  protobuf_AddDesc_UserListResponse_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "UserListResponse.proto");
  GOOGLE_CHECK(file != NULL);
  FollowListResponse_descriptor_ = file->message_type(0);
  static const int FollowListResponse_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FollowListResponse, people_list_),
  };
  FollowListResponse_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      FollowListResponse_descriptor_,
      FollowListResponse::default_instance_,
      FollowListResponse_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FollowListResponse, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FollowListResponse, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(FollowListResponse));
  FollowedListResponse_descriptor_ = file->message_type(1);
  static const int FollowedListResponse_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FollowedListResponse, people_list_),
  };
  FollowedListResponse_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      FollowedListResponse_descriptor_,
      FollowedListResponse::default_instance_,
      FollowedListResponse_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FollowedListResponse, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FollowedListResponse, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(FollowedListResponse));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_UserListResponse_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    FollowListResponse_descriptor_, &FollowListResponse::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    FollowedListResponse_descriptor_, &FollowedListResponse::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_UserListResponse_2eproto() {
  delete FollowListResponse::default_instance_;
  delete FollowListResponse_reflection_;
  delete FollowedListResponse::default_instance_;
  delete FollowedListResponse_reflection_;
}

void protobuf_AddDesc_UserListResponse_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::Data::protobuf_AddDesc_data_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\026UserListResponse.proto\022\020UserListRespon"
    "se\032\ndata.proto\"5\n\022FollowListResponse\022\037\n\013"
    "people_list\030\001 \001(\0132\n.Data.List\"7\n\024Followe"
    "dListResponse\022\037\n\013people_list\030\001 \001(\0132\n.Dat"
    "a.List", 166);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "UserListResponse.proto", &protobuf_RegisterTypes);
  FollowListResponse::default_instance_ = new FollowListResponse();
  FollowedListResponse::default_instance_ = new FollowedListResponse();
  FollowListResponse::default_instance_->InitAsDefaultInstance();
  FollowedListResponse::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_UserListResponse_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_UserListResponse_2eproto {
  StaticDescriptorInitializer_UserListResponse_2eproto() {
    protobuf_AddDesc_UserListResponse_2eproto();
  }
} static_descriptor_initializer_UserListResponse_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int FollowListResponse::kPeopleListFieldNumber;
#endif  // !_MSC_VER

FollowListResponse::FollowListResponse()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void FollowListResponse::InitAsDefaultInstance() {
  people_list_ = const_cast< ::Data::List*>(&::Data::List::default_instance());
}

FollowListResponse::FollowListResponse(const FollowListResponse& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void FollowListResponse::SharedCtor() {
  _cached_size_ = 0;
  people_list_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

FollowListResponse::~FollowListResponse() {
  SharedDtor();
}

void FollowListResponse::SharedDtor() {
  if (this != default_instance_) {
    delete people_list_;
  }
}

void FollowListResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* FollowListResponse::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return FollowListResponse_descriptor_;
}

const FollowListResponse& FollowListResponse::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_UserListResponse_2eproto();
  return *default_instance_;
}

FollowListResponse* FollowListResponse::default_instance_ = NULL;

FollowListResponse* FollowListResponse::New() const {
  return new FollowListResponse;
}

void FollowListResponse::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_people_list()) {
      if (people_list_ != NULL) people_list_->::Data::List::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool FollowListResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .Data.List people_list = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_people_list()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void FollowListResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .Data.List people_list = 1;
  if (has_people_list()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->people_list(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* FollowListResponse::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .Data.List people_list = 1;
  if (has_people_list()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->people_list(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int FollowListResponse::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .Data.List people_list = 1;
    if (has_people_list()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->people_list());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void FollowListResponse::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const FollowListResponse* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const FollowListResponse*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void FollowListResponse::MergeFrom(const FollowListResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_people_list()) {
      mutable_people_list()->::Data::List::MergeFrom(from.people_list());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void FollowListResponse::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void FollowListResponse::CopyFrom(const FollowListResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FollowListResponse::IsInitialized() const {

  return true;
}

void FollowListResponse::Swap(FollowListResponse* other) {
  if (other != this) {
    std::swap(people_list_, other->people_list_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata FollowListResponse::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = FollowListResponse_descriptor_;
  metadata.reflection = FollowListResponse_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int FollowedListResponse::kPeopleListFieldNumber;
#endif  // !_MSC_VER

FollowedListResponse::FollowedListResponse()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void FollowedListResponse::InitAsDefaultInstance() {
  people_list_ = const_cast< ::Data::List*>(&::Data::List::default_instance());
}

FollowedListResponse::FollowedListResponse(const FollowedListResponse& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void FollowedListResponse::SharedCtor() {
  _cached_size_ = 0;
  people_list_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

FollowedListResponse::~FollowedListResponse() {
  SharedDtor();
}

void FollowedListResponse::SharedDtor() {
  if (this != default_instance_) {
    delete people_list_;
  }
}

void FollowedListResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* FollowedListResponse::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return FollowedListResponse_descriptor_;
}

const FollowedListResponse& FollowedListResponse::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_UserListResponse_2eproto();
  return *default_instance_;
}

FollowedListResponse* FollowedListResponse::default_instance_ = NULL;

FollowedListResponse* FollowedListResponse::New() const {
  return new FollowedListResponse;
}

void FollowedListResponse::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_people_list()) {
      if (people_list_ != NULL) people_list_->::Data::List::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool FollowedListResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .Data.List people_list = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_people_list()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void FollowedListResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .Data.List people_list = 1;
  if (has_people_list()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->people_list(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* FollowedListResponse::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .Data.List people_list = 1;
  if (has_people_list()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->people_list(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int FollowedListResponse::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .Data.List people_list = 1;
    if (has_people_list()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->people_list());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void FollowedListResponse::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const FollowedListResponse* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const FollowedListResponse*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void FollowedListResponse::MergeFrom(const FollowedListResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_people_list()) {
      mutable_people_list()->::Data::List::MergeFrom(from.people_list());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void FollowedListResponse::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void FollowedListResponse::CopyFrom(const FollowedListResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FollowedListResponse::IsInitialized() const {

  return true;
}

void FollowedListResponse::Swap(FollowedListResponse* other) {
  if (other != this) {
    std::swap(people_list_, other->people_list_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata FollowedListResponse::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = FollowedListResponse_descriptor_;
  metadata.reflection = FollowedListResponse_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace UserListResponse

// @@protoc_insertion_point(global_scope)