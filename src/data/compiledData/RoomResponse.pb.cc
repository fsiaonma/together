// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: RoomResponse.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "RoomResponse.pb.h"

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

namespace RoomResponse {

namespace {

const ::google::protobuf::Descriptor* ShowRoomListResponse_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ShowRoomListResponse_reflection_ = NULL;
const ::google::protobuf::Descriptor* RoomPeopleListResponse_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  RoomPeopleListResponse_reflection_ = NULL;
const ::google::protobuf::Descriptor* RoomInfoResponse_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  RoomInfoResponse_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_RoomResponse_2eproto() {
  protobuf_AddDesc_RoomResponse_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "RoomResponse.proto");
  GOOGLE_CHECK(file != NULL);
  ShowRoomListResponse_descriptor_ = file->message_type(0);
  static const int ShowRoomListResponse_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ShowRoomListResponse, room_list_),
  };
  ShowRoomListResponse_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ShowRoomListResponse_descriptor_,
      ShowRoomListResponse::default_instance_,
      ShowRoomListResponse_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ShowRoomListResponse, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ShowRoomListResponse, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ShowRoomListResponse));
  RoomPeopleListResponse_descriptor_ = file->message_type(1);
  static const int RoomPeopleListResponse_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomPeopleListResponse, people_list_),
  };
  RoomPeopleListResponse_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      RoomPeopleListResponse_descriptor_,
      RoomPeopleListResponse::default_instance_,
      RoomPeopleListResponse_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomPeopleListResponse, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomPeopleListResponse, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(RoomPeopleListResponse));
  RoomInfoResponse_descriptor_ = file->message_type(2);
  static const int RoomInfoResponse_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomInfoResponse, room_info_),
  };
  RoomInfoResponse_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      RoomInfoResponse_descriptor_,
      RoomInfoResponse::default_instance_,
      RoomInfoResponse_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomInfoResponse, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomInfoResponse, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(RoomInfoResponse));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_RoomResponse_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ShowRoomListResponse_descriptor_, &ShowRoomListResponse::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    RoomPeopleListResponse_descriptor_, &RoomPeopleListResponse::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    RoomInfoResponse_descriptor_, &RoomInfoResponse::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_RoomResponse_2eproto() {
  delete ShowRoomListResponse::default_instance_;
  delete ShowRoomListResponse_reflection_;
  delete RoomPeopleListResponse::default_instance_;
  delete RoomPeopleListResponse_reflection_;
  delete RoomInfoResponse::default_instance_;
  delete RoomInfoResponse_reflection_;
}

void protobuf_AddDesc_RoomResponse_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::Data::protobuf_AddDesc_data_2eproto();
  ::RoomData::protobuf_AddDesc_RoomData_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\022RoomResponse.proto\022\014RoomResponse\032\ndata"
    ".proto\032\016RoomData.proto\"5\n\024ShowRoomListRe"
    "sponse\022\035\n\troom_list\030\001 \001(\0132\n.Data.List\"9\n"
    "\026RoomPeopleListResponse\022\037\n\013people_list\030\001"
    " \001(\0132\n.Data.List\"9\n\020RoomInfoResponse\022%\n\t"
    "room_info\030\001 \001(\0132\022.RoomData.RoomInfo", 235);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "RoomResponse.proto", &protobuf_RegisterTypes);
  ShowRoomListResponse::default_instance_ = new ShowRoomListResponse();
  RoomPeopleListResponse::default_instance_ = new RoomPeopleListResponse();
  RoomInfoResponse::default_instance_ = new RoomInfoResponse();
  ShowRoomListResponse::default_instance_->InitAsDefaultInstance();
  RoomPeopleListResponse::default_instance_->InitAsDefaultInstance();
  RoomInfoResponse::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_RoomResponse_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_RoomResponse_2eproto {
  StaticDescriptorInitializer_RoomResponse_2eproto() {
    protobuf_AddDesc_RoomResponse_2eproto();
  }
} static_descriptor_initializer_RoomResponse_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int ShowRoomListResponse::kRoomListFieldNumber;
#endif  // !_MSC_VER

ShowRoomListResponse::ShowRoomListResponse()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ShowRoomListResponse::InitAsDefaultInstance() {
  room_list_ = const_cast< ::Data::List*>(&::Data::List::default_instance());
}

ShowRoomListResponse::ShowRoomListResponse(const ShowRoomListResponse& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ShowRoomListResponse::SharedCtor() {
  _cached_size_ = 0;
  room_list_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ShowRoomListResponse::~ShowRoomListResponse() {
  SharedDtor();
}

void ShowRoomListResponse::SharedDtor() {
  if (this != default_instance_) {
    delete room_list_;
  }
}

void ShowRoomListResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ShowRoomListResponse::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ShowRoomListResponse_descriptor_;
}

const ShowRoomListResponse& ShowRoomListResponse::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_RoomResponse_2eproto();
  return *default_instance_;
}

ShowRoomListResponse* ShowRoomListResponse::default_instance_ = NULL;

ShowRoomListResponse* ShowRoomListResponse::New() const {
  return new ShowRoomListResponse;
}

void ShowRoomListResponse::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_room_list()) {
      if (room_list_ != NULL) room_list_->::Data::List::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ShowRoomListResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .Data.List room_list = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_room_list()));
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

void ShowRoomListResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .Data.List room_list = 1;
  if (has_room_list()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->room_list(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ShowRoomListResponse::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .Data.List room_list = 1;
  if (has_room_list()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->room_list(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ShowRoomListResponse::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .Data.List room_list = 1;
    if (has_room_list()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->room_list());
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

void ShowRoomListResponse::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ShowRoomListResponse* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ShowRoomListResponse*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ShowRoomListResponse::MergeFrom(const ShowRoomListResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_room_list()) {
      mutable_room_list()->::Data::List::MergeFrom(from.room_list());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ShowRoomListResponse::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ShowRoomListResponse::CopyFrom(const ShowRoomListResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ShowRoomListResponse::IsInitialized() const {

  return true;
}

void ShowRoomListResponse::Swap(ShowRoomListResponse* other) {
  if (other != this) {
    std::swap(room_list_, other->room_list_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ShowRoomListResponse::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ShowRoomListResponse_descriptor_;
  metadata.reflection = ShowRoomListResponse_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int RoomPeopleListResponse::kPeopleListFieldNumber;
#endif  // !_MSC_VER

RoomPeopleListResponse::RoomPeopleListResponse()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void RoomPeopleListResponse::InitAsDefaultInstance() {
  people_list_ = const_cast< ::Data::List*>(&::Data::List::default_instance());
}

RoomPeopleListResponse::RoomPeopleListResponse(const RoomPeopleListResponse& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void RoomPeopleListResponse::SharedCtor() {
  _cached_size_ = 0;
  people_list_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

RoomPeopleListResponse::~RoomPeopleListResponse() {
  SharedDtor();
}

void RoomPeopleListResponse::SharedDtor() {
  if (this != default_instance_) {
    delete people_list_;
  }
}

void RoomPeopleListResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* RoomPeopleListResponse::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return RoomPeopleListResponse_descriptor_;
}

const RoomPeopleListResponse& RoomPeopleListResponse::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_RoomResponse_2eproto();
  return *default_instance_;
}

RoomPeopleListResponse* RoomPeopleListResponse::default_instance_ = NULL;

RoomPeopleListResponse* RoomPeopleListResponse::New() const {
  return new RoomPeopleListResponse;
}

void RoomPeopleListResponse::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_people_list()) {
      if (people_list_ != NULL) people_list_->::Data::List::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool RoomPeopleListResponse::MergePartialFromCodedStream(
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

void RoomPeopleListResponse::SerializeWithCachedSizes(
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

::google::protobuf::uint8* RoomPeopleListResponse::SerializeWithCachedSizesToArray(
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

int RoomPeopleListResponse::ByteSize() const {
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

void RoomPeopleListResponse::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const RoomPeopleListResponse* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const RoomPeopleListResponse*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void RoomPeopleListResponse::MergeFrom(const RoomPeopleListResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_people_list()) {
      mutable_people_list()->::Data::List::MergeFrom(from.people_list());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void RoomPeopleListResponse::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void RoomPeopleListResponse::CopyFrom(const RoomPeopleListResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RoomPeopleListResponse::IsInitialized() const {

  return true;
}

void RoomPeopleListResponse::Swap(RoomPeopleListResponse* other) {
  if (other != this) {
    std::swap(people_list_, other->people_list_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata RoomPeopleListResponse::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = RoomPeopleListResponse_descriptor_;
  metadata.reflection = RoomPeopleListResponse_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int RoomInfoResponse::kRoomInfoFieldNumber;
#endif  // !_MSC_VER

RoomInfoResponse::RoomInfoResponse()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void RoomInfoResponse::InitAsDefaultInstance() {
  room_info_ = const_cast< ::RoomData::RoomInfo*>(&::RoomData::RoomInfo::default_instance());
}

RoomInfoResponse::RoomInfoResponse(const RoomInfoResponse& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void RoomInfoResponse::SharedCtor() {
  _cached_size_ = 0;
  room_info_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

RoomInfoResponse::~RoomInfoResponse() {
  SharedDtor();
}

void RoomInfoResponse::SharedDtor() {
  if (this != default_instance_) {
    delete room_info_;
  }
}

void RoomInfoResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* RoomInfoResponse::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return RoomInfoResponse_descriptor_;
}

const RoomInfoResponse& RoomInfoResponse::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_RoomResponse_2eproto();
  return *default_instance_;
}

RoomInfoResponse* RoomInfoResponse::default_instance_ = NULL;

RoomInfoResponse* RoomInfoResponse::New() const {
  return new RoomInfoResponse;
}

void RoomInfoResponse::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_room_info()) {
      if (room_info_ != NULL) room_info_->::RoomData::RoomInfo::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool RoomInfoResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .RoomData.RoomInfo room_info = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_room_info()));
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

void RoomInfoResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .RoomData.RoomInfo room_info = 1;
  if (has_room_info()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->room_info(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* RoomInfoResponse::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .RoomData.RoomInfo room_info = 1;
  if (has_room_info()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->room_info(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int RoomInfoResponse::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .RoomData.RoomInfo room_info = 1;
    if (has_room_info()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->room_info());
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

void RoomInfoResponse::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const RoomInfoResponse* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const RoomInfoResponse*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void RoomInfoResponse::MergeFrom(const RoomInfoResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_room_info()) {
      mutable_room_info()->::RoomData::RoomInfo::MergeFrom(from.room_info());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void RoomInfoResponse::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void RoomInfoResponse::CopyFrom(const RoomInfoResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RoomInfoResponse::IsInitialized() const {

  return true;
}

void RoomInfoResponse::Swap(RoomInfoResponse* other) {
  if (other != this) {
    std::swap(room_info_, other->room_info_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata RoomInfoResponse::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = RoomInfoResponse_descriptor_;
  metadata.reflection = RoomInfoResponse_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace RoomResponse

// @@protoc_insertion_point(global_scope)
