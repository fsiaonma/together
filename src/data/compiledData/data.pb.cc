// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: data.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "data.pb.h"

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

namespace Data {

namespace {

const ::google::protobuf::Descriptor* List_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  List_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_data_2eproto() {
  protobuf_AddDesc_data_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "data.proto");
  GOOGLE_CHECK(file != NULL);
  List_descriptor_ = file->message_type(0);
  static const int List_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(List, is_end_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(List, room_info_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(List, user_detail_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(List, user_message_info_),
  };
  List_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      List_descriptor_,
      List::default_instance_,
      List_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(List, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(List, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(List));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_data_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    List_descriptor_, &List::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_data_2eproto() {
  delete List::default_instance_;
  delete List_reflection_;
}

void protobuf_AddDesc_data_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::RoomData::protobuf_AddDesc_RoomData_2eproto();
  ::UserData::protobuf_AddDesc_UserData_2eproto();
  ::UserResponse::protobuf_AddDesc_UserResponse_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\ndata.proto\022\004Data\032\016RoomData.proto\032\016User"
    "Data.proto\032\022UserResponse.proto\"\256\001\n\004List\022"
    "\016\n\006is_end\030\001 \001(\010\022%\n\troom_info\030\002 \003(\0132\022.Roo"
    "mData.RoomInfo\0221\n\013user_detail\030\003 \003(\0132\034.Us"
    "erResponse.DetailResponse\022<\n\021user_messag"
    "e_info\030\004 \003(\0132!.UserResponse.UserMessageR"
    "esponse", 247);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "data.proto", &protobuf_RegisterTypes);
  List::default_instance_ = new List();
  List::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_data_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_data_2eproto {
  StaticDescriptorInitializer_data_2eproto() {
    protobuf_AddDesc_data_2eproto();
  }
} static_descriptor_initializer_data_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int List::kIsEndFieldNumber;
const int List::kRoomInfoFieldNumber;
const int List::kUserDetailFieldNumber;
const int List::kUserMessageInfoFieldNumber;
#endif  // !_MSC_VER

List::List()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void List::InitAsDefaultInstance() {
}

List::List(const List& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void List::SharedCtor() {
  _cached_size_ = 0;
  is_end_ = false;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

List::~List() {
  SharedDtor();
}

void List::SharedDtor() {
  if (this != default_instance_) {
  }
}

void List::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* List::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return List_descriptor_;
}

const List& List::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_data_2eproto();
  return *default_instance_;
}

List* List::default_instance_ = NULL;

List* List::New() const {
  return new List;
}

void List::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    is_end_ = false;
  }
  room_info_.Clear();
  user_detail_.Clear();
  user_message_info_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool List::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional bool is_end = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &is_end_)));
          set_has_is_end();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_room_info;
        break;
      }

      // repeated .RoomData.RoomInfo room_info = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_room_info:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_room_info()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_room_info;
        if (input->ExpectTag(26)) goto parse_user_detail;
        break;
      }

      // repeated .UserResponse.DetailResponse user_detail = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_user_detail:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_user_detail()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_user_detail;
        if (input->ExpectTag(34)) goto parse_user_message_info;
        break;
      }

      // repeated .UserResponse.UserMessageResponse user_message_info = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_user_message_info:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_user_message_info()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_user_message_info;
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

void List::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional bool is_end = 1;
  if (has_is_end()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(1, this->is_end(), output);
  }

  // repeated .RoomData.RoomInfo room_info = 2;
  for (int i = 0; i < this->room_info_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->room_info(i), output);
  }

  // repeated .UserResponse.DetailResponse user_detail = 3;
  for (int i = 0; i < this->user_detail_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->user_detail(i), output);
  }

  // repeated .UserResponse.UserMessageResponse user_message_info = 4;
  for (int i = 0; i < this->user_message_info_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, this->user_message_info(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* List::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional bool is_end = 1;
  if (has_is_end()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(1, this->is_end(), target);
  }

  // repeated .RoomData.RoomInfo room_info = 2;
  for (int i = 0; i < this->room_info_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->room_info(i), target);
  }

  // repeated .UserResponse.DetailResponse user_detail = 3;
  for (int i = 0; i < this->user_detail_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->user_detail(i), target);
  }

  // repeated .UserResponse.UserMessageResponse user_message_info = 4;
  for (int i = 0; i < this->user_message_info_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        4, this->user_message_info(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int List::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional bool is_end = 1;
    if (has_is_end()) {
      total_size += 1 + 1;
    }

  }
  // repeated .RoomData.RoomInfo room_info = 2;
  total_size += 1 * this->room_info_size();
  for (int i = 0; i < this->room_info_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->room_info(i));
  }

  // repeated .UserResponse.DetailResponse user_detail = 3;
  total_size += 1 * this->user_detail_size();
  for (int i = 0; i < this->user_detail_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->user_detail(i));
  }

  // repeated .UserResponse.UserMessageResponse user_message_info = 4;
  total_size += 1 * this->user_message_info_size();
  for (int i = 0; i < this->user_message_info_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->user_message_info(i));
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

void List::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const List* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const List*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void List::MergeFrom(const List& from) {
  GOOGLE_CHECK_NE(&from, this);
  room_info_.MergeFrom(from.room_info_);
  user_detail_.MergeFrom(from.user_detail_);
  user_message_info_.MergeFrom(from.user_message_info_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_is_end()) {
      set_is_end(from.is_end());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void List::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void List::CopyFrom(const List& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool List::IsInitialized() const {

  return true;
}

void List::Swap(List* other) {
  if (other != this) {
    std::swap(is_end_, other->is_end_);
    room_info_.Swap(&other->room_info_);
    user_detail_.Swap(&other->user_detail_);
    user_message_info_.Swap(&other->user_message_info_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata List::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = List_descriptor_;
  metadata.reflection = List_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Data

// @@protoc_insertion_point(global_scope)
