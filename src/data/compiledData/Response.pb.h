// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Response.proto

#ifndef PROTOBUF_Response_2eproto__INCLUDED
#define PROTOBUF_Response_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
#include "UserResponse.pb.h"
#include "RoomResponse.pb.h"
// @@protoc_insertion_point(includes)

namespace Response {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Response_2eproto();
void protobuf_AssignDesc_Response_2eproto();
void protobuf_ShutdownFile_Response_2eproto();

class HTTPResponse;

// ===================================================================

class HTTPResponse : public ::google::protobuf::Message {
 public:
  HTTPResponse();
  virtual ~HTTPResponse();

  HTTPResponse(const HTTPResponse& from);

  inline HTTPResponse& operator=(const HTTPResponse& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const HTTPResponse& default_instance();

  void Swap(HTTPResponse* other);

  // implements Message ----------------------------------------------

  HTTPResponse* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const HTTPResponse& from);
  void MergeFrom(const HTTPResponse& from);
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
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 code = 1;
  inline bool has_code() const;
  inline void clear_code();
  static const int kCodeFieldNumber = 1;
  inline ::google::protobuf::int32 code() const;
  inline void set_code(::google::protobuf::int32 value);

  // optional bool success = 2;
  inline bool has_success() const;
  inline void clear_success();
  static const int kSuccessFieldNumber = 2;
  inline bool success() const;
  inline void set_success(bool value);

  // optional string msg = 3;
  inline bool has_msg() const;
  inline void clear_msg();
  static const int kMsgFieldNumber = 3;
  inline const ::std::string& msg() const;
  inline void set_msg(const ::std::string& value);
  inline void set_msg(const char* value);
  inline void set_msg(const char* value, size_t size);
  inline ::std::string* mutable_msg();
  inline ::std::string* release_msg();
  inline void set_allocated_msg(::std::string* msg);

  // optional .UserResponse.LoginResponse login_response = 4;
  inline bool has_login_response() const;
  inline void clear_login_response();
  static const int kLoginResponseFieldNumber = 4;
  inline const ::UserResponse::LoginResponse& login_response() const;
  inline ::UserResponse::LoginResponse* mutable_login_response();
  inline ::UserResponse::LoginResponse* release_login_response();
  inline void set_allocated_login_response(::UserResponse::LoginResponse* login_response);

  // optional .UserResponse.DetailResponse detail_response = 5;
  inline bool has_detail_response() const;
  inline void clear_detail_response();
  static const int kDetailResponseFieldNumber = 5;
  inline const ::UserResponse::DetailResponse& detail_response() const;
  inline ::UserResponse::DetailResponse* mutable_detail_response();
  inline ::UserResponse::DetailResponse* release_detail_response();
  inline void set_allocated_detail_response(::UserResponse::DetailResponse* detail_response);

  // optional .UserResponse.UsernameExistResponse exist_response = 6;
  inline bool has_exist_response() const;
  inline void clear_exist_response();
  static const int kExistResponseFieldNumber = 6;
  inline const ::UserResponse::UsernameExistResponse& exist_response() const;
  inline ::UserResponse::UsernameExistResponse* mutable_exist_response();
  inline ::UserResponse::UsernameExistResponse* release_exist_response();
  inline void set_allocated_exist_response(::UserResponse::UsernameExistResponse* exist_response);

  // optional .RoomResponse.ShowRoomListResponse room_list_response = 7;
  inline bool has_room_list_response() const;
  inline void clear_room_list_response();
  static const int kRoomListResponseFieldNumber = 7;
  inline const ::RoomResponse::ShowRoomListResponse& room_list_response() const;
  inline ::RoomResponse::ShowRoomListResponse* mutable_room_list_response();
  inline ::RoomResponse::ShowRoomListResponse* release_room_list_response();
  inline void set_allocated_room_list_response(::RoomResponse::ShowRoomListResponse* room_list_response);

  // optional .RoomResponse.RoomPeopleListResponse room_people_list_response = 8;
  inline bool has_room_people_list_response() const;
  inline void clear_room_people_list_response();
  static const int kRoomPeopleListResponseFieldNumber = 8;
  inline const ::RoomResponse::RoomPeopleListResponse& room_people_list_response() const;
  inline ::RoomResponse::RoomPeopleListResponse* mutable_room_people_list_response();
  inline ::RoomResponse::RoomPeopleListResponse* release_room_people_list_response();
  inline void set_allocated_room_people_list_response(::RoomResponse::RoomPeopleListResponse* room_people_list_response);

  // @@protoc_insertion_point(class_scope:Response.HTTPResponse)
 private:
  inline void set_has_code();
  inline void clear_has_code();
  inline void set_has_success();
  inline void clear_has_success();
  inline void set_has_msg();
  inline void clear_has_msg();
  inline void set_has_login_response();
  inline void clear_has_login_response();
  inline void set_has_detail_response();
  inline void clear_has_detail_response();
  inline void set_has_exist_response();
  inline void clear_has_exist_response();
  inline void set_has_room_list_response();
  inline void clear_has_room_list_response();
  inline void set_has_room_people_list_response();
  inline void clear_has_room_people_list_response();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 code_;
  bool success_;
  ::std::string* msg_;
  ::UserResponse::LoginResponse* login_response_;
  ::UserResponse::DetailResponse* detail_response_;
  ::UserResponse::UsernameExistResponse* exist_response_;
  ::RoomResponse::ShowRoomListResponse* room_list_response_;
  ::RoomResponse::RoomPeopleListResponse* room_people_list_response_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(8 + 31) / 32];

  friend void  protobuf_AddDesc_Response_2eproto();
  friend void protobuf_AssignDesc_Response_2eproto();
  friend void protobuf_ShutdownFile_Response_2eproto();

  void InitAsDefaultInstance();
  static HTTPResponse* default_instance_;
};
// ===================================================================


// ===================================================================

// HTTPResponse

// optional int32 code = 1;
inline bool HTTPResponse::has_code() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void HTTPResponse::set_has_code() {
  _has_bits_[0] |= 0x00000001u;
}
inline void HTTPResponse::clear_has_code() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void HTTPResponse::clear_code() {
  code_ = 0;
  clear_has_code();
}
inline ::google::protobuf::int32 HTTPResponse::code() const {
  return code_;
}
inline void HTTPResponse::set_code(::google::protobuf::int32 value) {
  set_has_code();
  code_ = value;
}

// optional bool success = 2;
inline bool HTTPResponse::has_success() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void HTTPResponse::set_has_success() {
  _has_bits_[0] |= 0x00000002u;
}
inline void HTTPResponse::clear_has_success() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void HTTPResponse::clear_success() {
  success_ = false;
  clear_has_success();
}
inline bool HTTPResponse::success() const {
  return success_;
}
inline void HTTPResponse::set_success(bool value) {
  set_has_success();
  success_ = value;
}

// optional string msg = 3;
inline bool HTTPResponse::has_msg() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void HTTPResponse::set_has_msg() {
  _has_bits_[0] |= 0x00000004u;
}
inline void HTTPResponse::clear_has_msg() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void HTTPResponse::clear_msg() {
  if (msg_ != &::google::protobuf::internal::kEmptyString) {
    msg_->clear();
  }
  clear_has_msg();
}
inline const ::std::string& HTTPResponse::msg() const {
  return *msg_;
}
inline void HTTPResponse::set_msg(const ::std::string& value) {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::kEmptyString) {
    msg_ = new ::std::string;
  }
  msg_->assign(value);
}
inline void HTTPResponse::set_msg(const char* value) {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::kEmptyString) {
    msg_ = new ::std::string;
  }
  msg_->assign(value);
}
inline void HTTPResponse::set_msg(const char* value, size_t size) {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::kEmptyString) {
    msg_ = new ::std::string;
  }
  msg_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* HTTPResponse::mutable_msg() {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::kEmptyString) {
    msg_ = new ::std::string;
  }
  return msg_;
}
inline ::std::string* HTTPResponse::release_msg() {
  clear_has_msg();
  if (msg_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = msg_;
    msg_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void HTTPResponse::set_allocated_msg(::std::string* msg) {
  if (msg_ != &::google::protobuf::internal::kEmptyString) {
    delete msg_;
  }
  if (msg) {
    set_has_msg();
    msg_ = msg;
  } else {
    clear_has_msg();
    msg_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional .UserResponse.LoginResponse login_response = 4;
inline bool HTTPResponse::has_login_response() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void HTTPResponse::set_has_login_response() {
  _has_bits_[0] |= 0x00000008u;
}
inline void HTTPResponse::clear_has_login_response() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void HTTPResponse::clear_login_response() {
  if (login_response_ != NULL) login_response_->::UserResponse::LoginResponse::Clear();
  clear_has_login_response();
}
inline const ::UserResponse::LoginResponse& HTTPResponse::login_response() const {
  return login_response_ != NULL ? *login_response_ : *default_instance_->login_response_;
}
inline ::UserResponse::LoginResponse* HTTPResponse::mutable_login_response() {
  set_has_login_response();
  if (login_response_ == NULL) login_response_ = new ::UserResponse::LoginResponse;
  return login_response_;
}
inline ::UserResponse::LoginResponse* HTTPResponse::release_login_response() {
  clear_has_login_response();
  ::UserResponse::LoginResponse* temp = login_response_;
  login_response_ = NULL;
  return temp;
}
inline void HTTPResponse::set_allocated_login_response(::UserResponse::LoginResponse* login_response) {
  delete login_response_;
  login_response_ = login_response;
  if (login_response) {
    set_has_login_response();
  } else {
    clear_has_login_response();
  }
}

// optional .UserResponse.DetailResponse detail_response = 5;
inline bool HTTPResponse::has_detail_response() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void HTTPResponse::set_has_detail_response() {
  _has_bits_[0] |= 0x00000010u;
}
inline void HTTPResponse::clear_has_detail_response() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void HTTPResponse::clear_detail_response() {
  if (detail_response_ != NULL) detail_response_->::UserResponse::DetailResponse::Clear();
  clear_has_detail_response();
}
inline const ::UserResponse::DetailResponse& HTTPResponse::detail_response() const {
  return detail_response_ != NULL ? *detail_response_ : *default_instance_->detail_response_;
}
inline ::UserResponse::DetailResponse* HTTPResponse::mutable_detail_response() {
  set_has_detail_response();
  if (detail_response_ == NULL) detail_response_ = new ::UserResponse::DetailResponse;
  return detail_response_;
}
inline ::UserResponse::DetailResponse* HTTPResponse::release_detail_response() {
  clear_has_detail_response();
  ::UserResponse::DetailResponse* temp = detail_response_;
  detail_response_ = NULL;
  return temp;
}
inline void HTTPResponse::set_allocated_detail_response(::UserResponse::DetailResponse* detail_response) {
  delete detail_response_;
  detail_response_ = detail_response;
  if (detail_response) {
    set_has_detail_response();
  } else {
    clear_has_detail_response();
  }
}

// optional .UserResponse.UsernameExistResponse exist_response = 6;
inline bool HTTPResponse::has_exist_response() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void HTTPResponse::set_has_exist_response() {
  _has_bits_[0] |= 0x00000020u;
}
inline void HTTPResponse::clear_has_exist_response() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void HTTPResponse::clear_exist_response() {
  if (exist_response_ != NULL) exist_response_->::UserResponse::UsernameExistResponse::Clear();
  clear_has_exist_response();
}
inline const ::UserResponse::UsernameExistResponse& HTTPResponse::exist_response() const {
  return exist_response_ != NULL ? *exist_response_ : *default_instance_->exist_response_;
}
inline ::UserResponse::UsernameExistResponse* HTTPResponse::mutable_exist_response() {
  set_has_exist_response();
  if (exist_response_ == NULL) exist_response_ = new ::UserResponse::UsernameExistResponse;
  return exist_response_;
}
inline ::UserResponse::UsernameExistResponse* HTTPResponse::release_exist_response() {
  clear_has_exist_response();
  ::UserResponse::UsernameExistResponse* temp = exist_response_;
  exist_response_ = NULL;
  return temp;
}
inline void HTTPResponse::set_allocated_exist_response(::UserResponse::UsernameExistResponse* exist_response) {
  delete exist_response_;
  exist_response_ = exist_response;
  if (exist_response) {
    set_has_exist_response();
  } else {
    clear_has_exist_response();
  }
}

// optional .RoomResponse.ShowRoomListResponse room_list_response = 7;
inline bool HTTPResponse::has_room_list_response() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void HTTPResponse::set_has_room_list_response() {
  _has_bits_[0] |= 0x00000040u;
}
inline void HTTPResponse::clear_has_room_list_response() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void HTTPResponse::clear_room_list_response() {
  if (room_list_response_ != NULL) room_list_response_->::RoomResponse::ShowRoomListResponse::Clear();
  clear_has_room_list_response();
}
inline const ::RoomResponse::ShowRoomListResponse& HTTPResponse::room_list_response() const {
  return room_list_response_ != NULL ? *room_list_response_ : *default_instance_->room_list_response_;
}
inline ::RoomResponse::ShowRoomListResponse* HTTPResponse::mutable_room_list_response() {
  set_has_room_list_response();
  if (room_list_response_ == NULL) room_list_response_ = new ::RoomResponse::ShowRoomListResponse;
  return room_list_response_;
}
inline ::RoomResponse::ShowRoomListResponse* HTTPResponse::release_room_list_response() {
  clear_has_room_list_response();
  ::RoomResponse::ShowRoomListResponse* temp = room_list_response_;
  room_list_response_ = NULL;
  return temp;
}
inline void HTTPResponse::set_allocated_room_list_response(::RoomResponse::ShowRoomListResponse* room_list_response) {
  delete room_list_response_;
  room_list_response_ = room_list_response;
  if (room_list_response) {
    set_has_room_list_response();
  } else {
    clear_has_room_list_response();
  }
}

// optional .RoomResponse.RoomPeopleListResponse room_people_list_response = 8;
inline bool HTTPResponse::has_room_people_list_response() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void HTTPResponse::set_has_room_people_list_response() {
  _has_bits_[0] |= 0x00000080u;
}
inline void HTTPResponse::clear_has_room_people_list_response() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void HTTPResponse::clear_room_people_list_response() {
  if (room_people_list_response_ != NULL) room_people_list_response_->::RoomResponse::RoomPeopleListResponse::Clear();
  clear_has_room_people_list_response();
}
inline const ::RoomResponse::RoomPeopleListResponse& HTTPResponse::room_people_list_response() const {
  return room_people_list_response_ != NULL ? *room_people_list_response_ : *default_instance_->room_people_list_response_;
}
inline ::RoomResponse::RoomPeopleListResponse* HTTPResponse::mutable_room_people_list_response() {
  set_has_room_people_list_response();
  if (room_people_list_response_ == NULL) room_people_list_response_ = new ::RoomResponse::RoomPeopleListResponse;
  return room_people_list_response_;
}
inline ::RoomResponse::RoomPeopleListResponse* HTTPResponse::release_room_people_list_response() {
  clear_has_room_people_list_response();
  ::RoomResponse::RoomPeopleListResponse* temp = room_people_list_response_;
  room_people_list_response_ = NULL;
  return temp;
}
inline void HTTPResponse::set_allocated_room_people_list_response(::RoomResponse::RoomPeopleListResponse* room_people_list_response) {
  delete room_people_list_response_;
  room_people_list_response_ = room_people_list_response;
  if (room_people_list_response) {
    set_has_room_people_list_response();
  } else {
    clear_has_room_people_list_response();
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Response

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Response_2eproto__INCLUDED
