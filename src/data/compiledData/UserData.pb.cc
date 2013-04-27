// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UserData.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "UserData.pb.h"

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

namespace UserData {

namespace {

const ::google::protobuf::Descriptor* User_Info_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  User_Info_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_UserData_2eproto() {
  protobuf_AddDesc_UserData_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "UserData.proto");
  GOOGLE_CHECK(file != NULL);
  User_Info_descriptor_ = file->message_type(0);
  static const int User_Info_offsets_[10] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(User_Info, uid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(User_Info, username_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(User_Info, nick_name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(User_Info, birthday_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(User_Info, signature_text_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(User_Info, signature_record_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(User_Info, praise_num_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(User_Info, visit_num_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(User_Info, followed_num_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(User_Info, follow_num_),
  };
  User_Info_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      User_Info_descriptor_,
      User_Info::default_instance_,
      User_Info_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(User_Info, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(User_Info, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(User_Info));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_UserData_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    User_Info_descriptor_, &User_Info::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_UserData_2eproto() {
  delete User_Info::default_instance_;
  delete User_Info_reflection_;
}

void protobuf_AddDesc_UserData_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\016UserData.proto\022\010UserData\"\325\001\n\tUser_Info"
    "\022\013\n\003uid\030\001 \001(\005\022\020\n\010username\030\002 \001(\t\022\021\n\tnick_"
    "name\030\003 \001(\t\022\020\n\010birthday\030\004 \001(\005\022\026\n\016signatur"
    "e_text\030\005 \001(\t\022\033\n\023signature_record_id\030\006 \001("
    "\005\022\022\n\npraise_num\030\007 \001(\005\022\021\n\tvisit_num\030\010 \001(\005"
    "\022\024\n\014followed_num\030\t \001(\005\022\022\n\nfollow_num\030\n \001"
    "(\005", 242);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "UserData.proto", &protobuf_RegisterTypes);
  User_Info::default_instance_ = new User_Info();
  User_Info::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_UserData_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_UserData_2eproto {
  StaticDescriptorInitializer_UserData_2eproto() {
    protobuf_AddDesc_UserData_2eproto();
  }
} static_descriptor_initializer_UserData_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int User_Info::kUidFieldNumber;
const int User_Info::kUsernameFieldNumber;
const int User_Info::kNickNameFieldNumber;
const int User_Info::kBirthdayFieldNumber;
const int User_Info::kSignatureTextFieldNumber;
const int User_Info::kSignatureRecordIdFieldNumber;
const int User_Info::kPraiseNumFieldNumber;
const int User_Info::kVisitNumFieldNumber;
const int User_Info::kFollowedNumFieldNumber;
const int User_Info::kFollowNumFieldNumber;
#endif  // !_MSC_VER

User_Info::User_Info()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void User_Info::InitAsDefaultInstance() {
}

User_Info::User_Info(const User_Info& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void User_Info::SharedCtor() {
  _cached_size_ = 0;
  uid_ = 0;
  username_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  nick_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  birthday_ = 0;
  signature_text_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  signature_record_id_ = 0;
  praise_num_ = 0;
  visit_num_ = 0;
  followed_num_ = 0;
  follow_num_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

User_Info::~User_Info() {
  SharedDtor();
}

void User_Info::SharedDtor() {
  if (username_ != &::google::protobuf::internal::kEmptyString) {
    delete username_;
  }
  if (nick_name_ != &::google::protobuf::internal::kEmptyString) {
    delete nick_name_;
  }
  if (signature_text_ != &::google::protobuf::internal::kEmptyString) {
    delete signature_text_;
  }
  if (this != default_instance_) {
  }
}

void User_Info::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* User_Info::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return User_Info_descriptor_;
}

const User_Info& User_Info::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_UserData_2eproto();
  return *default_instance_;
}

User_Info* User_Info::default_instance_ = NULL;

User_Info* User_Info::New() const {
  return new User_Info;
}

void User_Info::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    uid_ = 0;
    if (has_username()) {
      if (username_ != &::google::protobuf::internal::kEmptyString) {
        username_->clear();
      }
    }
    if (has_nick_name()) {
      if (nick_name_ != &::google::protobuf::internal::kEmptyString) {
        nick_name_->clear();
      }
    }
    birthday_ = 0;
    if (has_signature_text()) {
      if (signature_text_ != &::google::protobuf::internal::kEmptyString) {
        signature_text_->clear();
      }
    }
    signature_record_id_ = 0;
    praise_num_ = 0;
    visit_num_ = 0;
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    followed_num_ = 0;
    follow_num_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool User_Info::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 uid = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &uid_)));
          set_has_uid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_username;
        break;
      }

      // optional string username = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_username:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_username()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->username().data(), this->username().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_nick_name;
        break;
      }

      // optional string nick_name = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_nick_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_nick_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->nick_name().data(), this->nick_name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_birthday;
        break;
      }

      // optional int32 birthday = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_birthday:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &birthday_)));
          set_has_birthday();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_signature_text;
        break;
      }

      // optional string signature_text = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_signature_text:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_signature_text()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->signature_text().data(), this->signature_text().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_signature_record_id;
        break;
      }

      // optional int32 signature_record_id = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_signature_record_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &signature_record_id_)));
          set_has_signature_record_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_praise_num;
        break;
      }

      // optional int32 praise_num = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_praise_num:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &praise_num_)));
          set_has_praise_num();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(64)) goto parse_visit_num;
        break;
      }

      // optional int32 visit_num = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_visit_num:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &visit_num_)));
          set_has_visit_num();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(72)) goto parse_followed_num;
        break;
      }

      // optional int32 followed_num = 9;
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_followed_num:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &followed_num_)));
          set_has_followed_num();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(80)) goto parse_follow_num;
        break;
      }

      // optional int32 follow_num = 10;
      case 10: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_follow_num:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &follow_num_)));
          set_has_follow_num();
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

void User_Info::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional int32 uid = 1;
  if (has_uid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->uid(), output);
  }

  // optional string username = 2;
  if (has_username()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->username().data(), this->username().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->username(), output);
  }

  // optional string nick_name = 3;
  if (has_nick_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->nick_name().data(), this->nick_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->nick_name(), output);
  }

  // optional int32 birthday = 4;
  if (has_birthday()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->birthday(), output);
  }

  // optional string signature_text = 5;
  if (has_signature_text()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->signature_text().data(), this->signature_text().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      5, this->signature_text(), output);
  }

  // optional int32 signature_record_id = 6;
  if (has_signature_record_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(6, this->signature_record_id(), output);
  }

  // optional int32 praise_num = 7;
  if (has_praise_num()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(7, this->praise_num(), output);
  }

  // optional int32 visit_num = 8;
  if (has_visit_num()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(8, this->visit_num(), output);
  }

  // optional int32 followed_num = 9;
  if (has_followed_num()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(9, this->followed_num(), output);
  }

  // optional int32 follow_num = 10;
  if (has_follow_num()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(10, this->follow_num(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* User_Info::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional int32 uid = 1;
  if (has_uid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->uid(), target);
  }

  // optional string username = 2;
  if (has_username()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->username().data(), this->username().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->username(), target);
  }

  // optional string nick_name = 3;
  if (has_nick_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->nick_name().data(), this->nick_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->nick_name(), target);
  }

  // optional int32 birthday = 4;
  if (has_birthday()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(4, this->birthday(), target);
  }

  // optional string signature_text = 5;
  if (has_signature_text()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->signature_text().data(), this->signature_text().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        5, this->signature_text(), target);
  }

  // optional int32 signature_record_id = 6;
  if (has_signature_record_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(6, this->signature_record_id(), target);
  }

  // optional int32 praise_num = 7;
  if (has_praise_num()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(7, this->praise_num(), target);
  }

  // optional int32 visit_num = 8;
  if (has_visit_num()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(8, this->visit_num(), target);
  }

  // optional int32 followed_num = 9;
  if (has_followed_num()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(9, this->followed_num(), target);
  }

  // optional int32 follow_num = 10;
  if (has_follow_num()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(10, this->follow_num(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int User_Info::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional int32 uid = 1;
    if (has_uid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->uid());
    }

    // optional string username = 2;
    if (has_username()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->username());
    }

    // optional string nick_name = 3;
    if (has_nick_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->nick_name());
    }

    // optional int32 birthday = 4;
    if (has_birthday()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->birthday());
    }

    // optional string signature_text = 5;
    if (has_signature_text()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->signature_text());
    }

    // optional int32 signature_record_id = 6;
    if (has_signature_record_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->signature_record_id());
    }

    // optional int32 praise_num = 7;
    if (has_praise_num()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->praise_num());
    }

    // optional int32 visit_num = 8;
    if (has_visit_num()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->visit_num());
    }

  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional int32 followed_num = 9;
    if (has_followed_num()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->followed_num());
    }

    // optional int32 follow_num = 10;
    if (has_follow_num()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->follow_num());
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

void User_Info::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const User_Info* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const User_Info*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void User_Info::MergeFrom(const User_Info& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_uid()) {
      set_uid(from.uid());
    }
    if (from.has_username()) {
      set_username(from.username());
    }
    if (from.has_nick_name()) {
      set_nick_name(from.nick_name());
    }
    if (from.has_birthday()) {
      set_birthday(from.birthday());
    }
    if (from.has_signature_text()) {
      set_signature_text(from.signature_text());
    }
    if (from.has_signature_record_id()) {
      set_signature_record_id(from.signature_record_id());
    }
    if (from.has_praise_num()) {
      set_praise_num(from.praise_num());
    }
    if (from.has_visit_num()) {
      set_visit_num(from.visit_num());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_followed_num()) {
      set_followed_num(from.followed_num());
    }
    if (from.has_follow_num()) {
      set_follow_num(from.follow_num());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void User_Info::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void User_Info::CopyFrom(const User_Info& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool User_Info::IsInitialized() const {

  return true;
}

void User_Info::Swap(User_Info* other) {
  if (other != this) {
    std::swap(uid_, other->uid_);
    std::swap(username_, other->username_);
    std::swap(nick_name_, other->nick_name_);
    std::swap(birthday_, other->birthday_);
    std::swap(signature_text_, other->signature_text_);
    std::swap(signature_record_id_, other->signature_record_id_);
    std::swap(praise_num_, other->praise_num_);
    std::swap(visit_num_, other->visit_num_);
    std::swap(followed_num_, other->followed_num_);
    std::swap(follow_num_, other->follow_num_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata User_Info::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = User_Info_descriptor_;
  metadata.reflection = User_Info_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace UserData

// @@protoc_insertion_point(global_scope)
