// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: RoomData.proto

#ifndef PROTOBUF_RoomData_2eproto__INCLUDED
#define PROTOBUF_RoomData_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

namespace RoomData {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_RoomData_2eproto();
void protobuf_AssignDesc_RoomData_2eproto();
void protobuf_ShutdownFile_RoomData_2eproto();

class RoomInfo;
class Address;

// ===================================================================

class RoomInfo : public ::google::protobuf::Message {
 public:
  RoomInfo();
  virtual ~RoomInfo();

  RoomInfo(const RoomInfo& from);

  inline RoomInfo& operator=(const RoomInfo& from) {
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
  static const RoomInfo& default_instance();

  void Swap(RoomInfo* other);

  // implements Message ----------------------------------------------

  RoomInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RoomInfo& from);
  void MergeFrom(const RoomInfo& from);
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

  // optional int32 room_id = 1;
  inline bool has_room_id() const;
  inline void clear_room_id();
  static const int kRoomIdFieldNumber = 1;
  inline ::google::protobuf::int32 room_id() const;
  inline void set_room_id(::google::protobuf::int32 value);

  // optional string title = 2;
  inline bool has_title() const;
  inline void clear_title();
  static const int kTitleFieldNumber = 2;
  inline const ::std::string& title() const;
  inline void set_title(const ::std::string& value);
  inline void set_title(const char* value);
  inline void set_title(const char* value, size_t size);
  inline ::std::string* mutable_title();
  inline ::std::string* release_title();
  inline void set_allocated_title(::std::string* title);

  // optional int32 owner_id = 3;
  inline bool has_owner_id() const;
  inline void clear_owner_id();
  static const int kOwnerIdFieldNumber = 3;
  inline ::google::protobuf::int32 owner_id() const;
  inline void set_owner_id(::google::protobuf::int32 value);

  // optional string owner_nickname = 4;
  inline bool has_owner_nickname() const;
  inline void clear_owner_nickname();
  static const int kOwnerNicknameFieldNumber = 4;
  inline const ::std::string& owner_nickname() const;
  inline void set_owner_nickname(const ::std::string& value);
  inline void set_owner_nickname(const char* value);
  inline void set_owner_nickname(const char* value, size_t size);
  inline ::std::string* mutable_owner_nickname();
  inline ::std::string* release_owner_nickname();
  inline void set_allocated_owner_nickname(::std::string* owner_nickname);

  // optional int32 type = 5;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 5;
  inline ::google::protobuf::int32 type() const;
  inline void set_type(::google::protobuf::int32 value);

  // optional int32 status = 6;
  inline bool has_status() const;
  inline void clear_status();
  static const int kStatusFieldNumber = 6;
  inline ::google::protobuf::int32 status() const;
  inline void set_status(::google::protobuf::int32 value);

  // optional int32 pic_id = 7;
  inline bool has_pic_id() const;
  inline void clear_pic_id();
  static const int kPicIdFieldNumber = 7;
  inline ::google::protobuf::int32 pic_id() const;
  inline void set_pic_id(::google::protobuf::int32 value);

  // optional int32 gender_type = 8;
  inline bool has_gender_type() const;
  inline void clear_gender_type();
  static const int kGenderTypeFieldNumber = 8;
  inline ::google::protobuf::int32 gender_type() const;
  inline void set_gender_type(::google::protobuf::int32 value);

  // optional double distance = 9;
  inline bool has_distance() const;
  inline void clear_distance();
  static const int kDistanceFieldNumber = 9;
  inline double distance() const;
  inline void set_distance(double value);

  // optional int32 join_person_count = 10;
  inline bool has_join_person_count() const;
  inline void clear_join_person_count();
  static const int kJoinPersonCountFieldNumber = 10;
  inline ::google::protobuf::int32 join_person_count() const;
  inline void set_join_person_count(::google::protobuf::int32 value);

  // optional int32 limit_person_count = 11;
  inline bool has_limit_person_count() const;
  inline void clear_limit_person_count();
  static const int kLimitPersonCountFieldNumber = 11;
  inline ::google::protobuf::int32 limit_person_count() const;
  inline void set_limit_person_count(::google::protobuf::int32 value);

  // optional int32 record_id = 12;
  inline bool has_record_id() const;
  inline void clear_record_id();
  static const int kRecordIdFieldNumber = 12;
  inline ::google::protobuf::int32 record_id() const;
  inline void set_record_id(::google::protobuf::int32 value);

  // optional string create_time = 13;
  inline bool has_create_time() const;
  inline void clear_create_time();
  static const int kCreateTimeFieldNumber = 13;
  inline const ::std::string& create_time() const;
  inline void set_create_time(const ::std::string& value);
  inline void set_create_time(const char* value);
  inline void set_create_time(const char* value, size_t size);
  inline ::std::string* mutable_create_time();
  inline ::std::string* release_create_time();
  inline void set_allocated_create_time(::std::string* create_time);

  // optional string begin_time = 14;
  inline bool has_begin_time() const;
  inline void clear_begin_time();
  static const int kBeginTimeFieldNumber = 14;
  inline const ::std::string& begin_time() const;
  inline void set_begin_time(const ::std::string& value);
  inline void set_begin_time(const char* value);
  inline void set_begin_time(const char* value, size_t size);
  inline ::std::string* mutable_begin_time();
  inline ::std::string* release_begin_time();
  inline void set_allocated_begin_time(::std::string* begin_time);

  // optional .RoomData.Address address = 15;
  inline bool has_address() const;
  inline void clear_address();
  static const int kAddressFieldNumber = 15;
  inline const ::RoomData::Address& address() const;
  inline ::RoomData::Address* mutable_address();
  inline ::RoomData::Address* release_address();
  inline void set_allocated_address(::RoomData::Address* address);

  // optional int32 join_status = 16;
  inline bool has_join_status() const;
  inline void clear_join_status();
  static const int kJoinStatusFieldNumber = 16;
  inline ::google::protobuf::int32 join_status() const;
  inline void set_join_status(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:RoomData.RoomInfo)
 private:
  inline void set_has_room_id();
  inline void clear_has_room_id();
  inline void set_has_title();
  inline void clear_has_title();
  inline void set_has_owner_id();
  inline void clear_has_owner_id();
  inline void set_has_owner_nickname();
  inline void clear_has_owner_nickname();
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_status();
  inline void clear_has_status();
  inline void set_has_pic_id();
  inline void clear_has_pic_id();
  inline void set_has_gender_type();
  inline void clear_has_gender_type();
  inline void set_has_distance();
  inline void clear_has_distance();
  inline void set_has_join_person_count();
  inline void clear_has_join_person_count();
  inline void set_has_limit_person_count();
  inline void clear_has_limit_person_count();
  inline void set_has_record_id();
  inline void clear_has_record_id();
  inline void set_has_create_time();
  inline void clear_has_create_time();
  inline void set_has_begin_time();
  inline void clear_has_begin_time();
  inline void set_has_address();
  inline void clear_has_address();
  inline void set_has_join_status();
  inline void clear_has_join_status();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* title_;
  ::google::protobuf::int32 room_id_;
  ::google::protobuf::int32 owner_id_;
  ::std::string* owner_nickname_;
  ::google::protobuf::int32 type_;
  ::google::protobuf::int32 status_;
  ::google::protobuf::int32 pic_id_;
  ::google::protobuf::int32 gender_type_;
  double distance_;
  ::google::protobuf::int32 join_person_count_;
  ::google::protobuf::int32 limit_person_count_;
  ::std::string* create_time_;
  ::std::string* begin_time_;
  ::google::protobuf::int32 record_id_;
  ::google::protobuf::int32 join_status_;
  ::RoomData::Address* address_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(16 + 31) / 32];

  friend void  protobuf_AddDesc_RoomData_2eproto();
  friend void protobuf_AssignDesc_RoomData_2eproto();
  friend void protobuf_ShutdownFile_RoomData_2eproto();

  void InitAsDefaultInstance();
  static RoomInfo* default_instance_;
};
// -------------------------------------------------------------------

class Address : public ::google::protobuf::Message {
 public:
  Address();
  virtual ~Address();

  Address(const Address& from);

  inline Address& operator=(const Address& from) {
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
  static const Address& default_instance();

  void Swap(Address* other);

  // implements Message ----------------------------------------------

  Address* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Address& from);
  void MergeFrom(const Address& from);
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

  // optional int32 addr_type = 1;
  inline bool has_addr_type() const;
  inline void clear_addr_type();
  static const int kAddrTypeFieldNumber = 1;
  inline ::google::protobuf::int32 addr_type() const;
  inline void set_addr_type(::google::protobuf::int32 value);

  // optional double longitude = 2;
  inline bool has_longitude() const;
  inline void clear_longitude();
  static const int kLongitudeFieldNumber = 2;
  inline double longitude() const;
  inline void set_longitude(double value);

  // optional double latitude = 3;
  inline bool has_latitude() const;
  inline void clear_latitude();
  static const int kLatitudeFieldNumber = 3;
  inline double latitude() const;
  inline void set_latitude(double value);

  // optional string detail_addr = 4;
  inline bool has_detail_addr() const;
  inline void clear_detail_addr();
  static const int kDetailAddrFieldNumber = 4;
  inline const ::std::string& detail_addr() const;
  inline void set_detail_addr(const ::std::string& value);
  inline void set_detail_addr(const char* value);
  inline void set_detail_addr(const char* value, size_t size);
  inline ::std::string* mutable_detail_addr();
  inline ::std::string* release_detail_addr();
  inline void set_allocated_detail_addr(::std::string* detail_addr);

  // optional string addr_remark = 5;
  inline bool has_addr_remark() const;
  inline void clear_addr_remark();
  static const int kAddrRemarkFieldNumber = 5;
  inline const ::std::string& addr_remark() const;
  inline void set_addr_remark(const ::std::string& value);
  inline void set_addr_remark(const char* value);
  inline void set_addr_remark(const char* value, size_t size);
  inline ::std::string* mutable_addr_remark();
  inline ::std::string* release_addr_remark();
  inline void set_allocated_addr_remark(::std::string* addr_remark);

  // @@protoc_insertion_point(class_scope:RoomData.Address)
 private:
  inline void set_has_addr_type();
  inline void clear_has_addr_type();
  inline void set_has_longitude();
  inline void clear_has_longitude();
  inline void set_has_latitude();
  inline void clear_has_latitude();
  inline void set_has_detail_addr();
  inline void clear_has_detail_addr();
  inline void set_has_addr_remark();
  inline void clear_has_addr_remark();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  double longitude_;
  double latitude_;
  ::std::string* detail_addr_;
  ::std::string* addr_remark_;
  ::google::protobuf::int32 addr_type_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];

  friend void  protobuf_AddDesc_RoomData_2eproto();
  friend void protobuf_AssignDesc_RoomData_2eproto();
  friend void protobuf_ShutdownFile_RoomData_2eproto();

  void InitAsDefaultInstance();
  static Address* default_instance_;
};
// ===================================================================


// ===================================================================

// RoomInfo

// optional int32 room_id = 1;
inline bool RoomInfo::has_room_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RoomInfo::set_has_room_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RoomInfo::clear_has_room_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RoomInfo::clear_room_id() {
  room_id_ = 0;
  clear_has_room_id();
}
inline ::google::protobuf::int32 RoomInfo::room_id() const {
  return room_id_;
}
inline void RoomInfo::set_room_id(::google::protobuf::int32 value) {
  set_has_room_id();
  room_id_ = value;
}

// optional string title = 2;
inline bool RoomInfo::has_title() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RoomInfo::set_has_title() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RoomInfo::clear_has_title() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RoomInfo::clear_title() {
  if (title_ != &::google::protobuf::internal::kEmptyString) {
    title_->clear();
  }
  clear_has_title();
}
inline const ::std::string& RoomInfo::title() const {
  return *title_;
}
inline void RoomInfo::set_title(const ::std::string& value) {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  title_->assign(value);
}
inline void RoomInfo::set_title(const char* value) {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  title_->assign(value);
}
inline void RoomInfo::set_title(const char* value, size_t size) {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  title_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* RoomInfo::mutable_title() {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  return title_;
}
inline ::std::string* RoomInfo::release_title() {
  clear_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = title_;
    title_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void RoomInfo::set_allocated_title(::std::string* title) {
  if (title_ != &::google::protobuf::internal::kEmptyString) {
    delete title_;
  }
  if (title) {
    set_has_title();
    title_ = title;
  } else {
    clear_has_title();
    title_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional int32 owner_id = 3;
inline bool RoomInfo::has_owner_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void RoomInfo::set_has_owner_id() {
  _has_bits_[0] |= 0x00000004u;
}
inline void RoomInfo::clear_has_owner_id() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void RoomInfo::clear_owner_id() {
  owner_id_ = 0;
  clear_has_owner_id();
}
inline ::google::protobuf::int32 RoomInfo::owner_id() const {
  return owner_id_;
}
inline void RoomInfo::set_owner_id(::google::protobuf::int32 value) {
  set_has_owner_id();
  owner_id_ = value;
}

// optional string owner_nickname = 4;
inline bool RoomInfo::has_owner_nickname() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void RoomInfo::set_has_owner_nickname() {
  _has_bits_[0] |= 0x00000008u;
}
inline void RoomInfo::clear_has_owner_nickname() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void RoomInfo::clear_owner_nickname() {
  if (owner_nickname_ != &::google::protobuf::internal::kEmptyString) {
    owner_nickname_->clear();
  }
  clear_has_owner_nickname();
}
inline const ::std::string& RoomInfo::owner_nickname() const {
  return *owner_nickname_;
}
inline void RoomInfo::set_owner_nickname(const ::std::string& value) {
  set_has_owner_nickname();
  if (owner_nickname_ == &::google::protobuf::internal::kEmptyString) {
    owner_nickname_ = new ::std::string;
  }
  owner_nickname_->assign(value);
}
inline void RoomInfo::set_owner_nickname(const char* value) {
  set_has_owner_nickname();
  if (owner_nickname_ == &::google::protobuf::internal::kEmptyString) {
    owner_nickname_ = new ::std::string;
  }
  owner_nickname_->assign(value);
}
inline void RoomInfo::set_owner_nickname(const char* value, size_t size) {
  set_has_owner_nickname();
  if (owner_nickname_ == &::google::protobuf::internal::kEmptyString) {
    owner_nickname_ = new ::std::string;
  }
  owner_nickname_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* RoomInfo::mutable_owner_nickname() {
  set_has_owner_nickname();
  if (owner_nickname_ == &::google::protobuf::internal::kEmptyString) {
    owner_nickname_ = new ::std::string;
  }
  return owner_nickname_;
}
inline ::std::string* RoomInfo::release_owner_nickname() {
  clear_has_owner_nickname();
  if (owner_nickname_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = owner_nickname_;
    owner_nickname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void RoomInfo::set_allocated_owner_nickname(::std::string* owner_nickname) {
  if (owner_nickname_ != &::google::protobuf::internal::kEmptyString) {
    delete owner_nickname_;
  }
  if (owner_nickname) {
    set_has_owner_nickname();
    owner_nickname_ = owner_nickname;
  } else {
    clear_has_owner_nickname();
    owner_nickname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional int32 type = 5;
inline bool RoomInfo::has_type() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void RoomInfo::set_has_type() {
  _has_bits_[0] |= 0x00000010u;
}
inline void RoomInfo::clear_has_type() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void RoomInfo::clear_type() {
  type_ = 0;
  clear_has_type();
}
inline ::google::protobuf::int32 RoomInfo::type() const {
  return type_;
}
inline void RoomInfo::set_type(::google::protobuf::int32 value) {
  set_has_type();
  type_ = value;
}

// optional int32 status = 6;
inline bool RoomInfo::has_status() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void RoomInfo::set_has_status() {
  _has_bits_[0] |= 0x00000020u;
}
inline void RoomInfo::clear_has_status() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void RoomInfo::clear_status() {
  status_ = 0;
  clear_has_status();
}
inline ::google::protobuf::int32 RoomInfo::status() const {
  return status_;
}
inline void RoomInfo::set_status(::google::protobuf::int32 value) {
  set_has_status();
  status_ = value;
}

// optional int32 pic_id = 7;
inline bool RoomInfo::has_pic_id() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void RoomInfo::set_has_pic_id() {
  _has_bits_[0] |= 0x00000040u;
}
inline void RoomInfo::clear_has_pic_id() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void RoomInfo::clear_pic_id() {
  pic_id_ = 0;
  clear_has_pic_id();
}
inline ::google::protobuf::int32 RoomInfo::pic_id() const {
  return pic_id_;
}
inline void RoomInfo::set_pic_id(::google::protobuf::int32 value) {
  set_has_pic_id();
  pic_id_ = value;
}

// optional int32 gender_type = 8;
inline bool RoomInfo::has_gender_type() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void RoomInfo::set_has_gender_type() {
  _has_bits_[0] |= 0x00000080u;
}
inline void RoomInfo::clear_has_gender_type() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void RoomInfo::clear_gender_type() {
  gender_type_ = 0;
  clear_has_gender_type();
}
inline ::google::protobuf::int32 RoomInfo::gender_type() const {
  return gender_type_;
}
inline void RoomInfo::set_gender_type(::google::protobuf::int32 value) {
  set_has_gender_type();
  gender_type_ = value;
}

// optional double distance = 9;
inline bool RoomInfo::has_distance() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void RoomInfo::set_has_distance() {
  _has_bits_[0] |= 0x00000100u;
}
inline void RoomInfo::clear_has_distance() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void RoomInfo::clear_distance() {
  distance_ = 0;
  clear_has_distance();
}
inline double RoomInfo::distance() const {
  return distance_;
}
inline void RoomInfo::set_distance(double value) {
  set_has_distance();
  distance_ = value;
}

// optional int32 join_person_count = 10;
inline bool RoomInfo::has_join_person_count() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void RoomInfo::set_has_join_person_count() {
  _has_bits_[0] |= 0x00000200u;
}
inline void RoomInfo::clear_has_join_person_count() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void RoomInfo::clear_join_person_count() {
  join_person_count_ = 0;
  clear_has_join_person_count();
}
inline ::google::protobuf::int32 RoomInfo::join_person_count() const {
  return join_person_count_;
}
inline void RoomInfo::set_join_person_count(::google::protobuf::int32 value) {
  set_has_join_person_count();
  join_person_count_ = value;
}

// optional int32 limit_person_count = 11;
inline bool RoomInfo::has_limit_person_count() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void RoomInfo::set_has_limit_person_count() {
  _has_bits_[0] |= 0x00000400u;
}
inline void RoomInfo::clear_has_limit_person_count() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void RoomInfo::clear_limit_person_count() {
  limit_person_count_ = 0;
  clear_has_limit_person_count();
}
inline ::google::protobuf::int32 RoomInfo::limit_person_count() const {
  return limit_person_count_;
}
inline void RoomInfo::set_limit_person_count(::google::protobuf::int32 value) {
  set_has_limit_person_count();
  limit_person_count_ = value;
}

// optional int32 record_id = 12;
inline bool RoomInfo::has_record_id() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void RoomInfo::set_has_record_id() {
  _has_bits_[0] |= 0x00000800u;
}
inline void RoomInfo::clear_has_record_id() {
  _has_bits_[0] &= ~0x00000800u;
}
inline void RoomInfo::clear_record_id() {
  record_id_ = 0;
  clear_has_record_id();
}
inline ::google::protobuf::int32 RoomInfo::record_id() const {
  return record_id_;
}
inline void RoomInfo::set_record_id(::google::protobuf::int32 value) {
  set_has_record_id();
  record_id_ = value;
}

// optional string create_time = 13;
inline bool RoomInfo::has_create_time() const {
  return (_has_bits_[0] & 0x00001000u) != 0;
}
inline void RoomInfo::set_has_create_time() {
  _has_bits_[0] |= 0x00001000u;
}
inline void RoomInfo::clear_has_create_time() {
  _has_bits_[0] &= ~0x00001000u;
}
inline void RoomInfo::clear_create_time() {
  if (create_time_ != &::google::protobuf::internal::kEmptyString) {
    create_time_->clear();
  }
  clear_has_create_time();
}
inline const ::std::string& RoomInfo::create_time() const {
  return *create_time_;
}
inline void RoomInfo::set_create_time(const ::std::string& value) {
  set_has_create_time();
  if (create_time_ == &::google::protobuf::internal::kEmptyString) {
    create_time_ = new ::std::string;
  }
  create_time_->assign(value);
}
inline void RoomInfo::set_create_time(const char* value) {
  set_has_create_time();
  if (create_time_ == &::google::protobuf::internal::kEmptyString) {
    create_time_ = new ::std::string;
  }
  create_time_->assign(value);
}
inline void RoomInfo::set_create_time(const char* value, size_t size) {
  set_has_create_time();
  if (create_time_ == &::google::protobuf::internal::kEmptyString) {
    create_time_ = new ::std::string;
  }
  create_time_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* RoomInfo::mutable_create_time() {
  set_has_create_time();
  if (create_time_ == &::google::protobuf::internal::kEmptyString) {
    create_time_ = new ::std::string;
  }
  return create_time_;
}
inline ::std::string* RoomInfo::release_create_time() {
  clear_has_create_time();
  if (create_time_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = create_time_;
    create_time_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void RoomInfo::set_allocated_create_time(::std::string* create_time) {
  if (create_time_ != &::google::protobuf::internal::kEmptyString) {
    delete create_time_;
  }
  if (create_time) {
    set_has_create_time();
    create_time_ = create_time;
  } else {
    clear_has_create_time();
    create_time_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional string begin_time = 14;
inline bool RoomInfo::has_begin_time() const {
  return (_has_bits_[0] & 0x00002000u) != 0;
}
inline void RoomInfo::set_has_begin_time() {
  _has_bits_[0] |= 0x00002000u;
}
inline void RoomInfo::clear_has_begin_time() {
  _has_bits_[0] &= ~0x00002000u;
}
inline void RoomInfo::clear_begin_time() {
  if (begin_time_ != &::google::protobuf::internal::kEmptyString) {
    begin_time_->clear();
  }
  clear_has_begin_time();
}
inline const ::std::string& RoomInfo::begin_time() const {
  return *begin_time_;
}
inline void RoomInfo::set_begin_time(const ::std::string& value) {
  set_has_begin_time();
  if (begin_time_ == &::google::protobuf::internal::kEmptyString) {
    begin_time_ = new ::std::string;
  }
  begin_time_->assign(value);
}
inline void RoomInfo::set_begin_time(const char* value) {
  set_has_begin_time();
  if (begin_time_ == &::google::protobuf::internal::kEmptyString) {
    begin_time_ = new ::std::string;
  }
  begin_time_->assign(value);
}
inline void RoomInfo::set_begin_time(const char* value, size_t size) {
  set_has_begin_time();
  if (begin_time_ == &::google::protobuf::internal::kEmptyString) {
    begin_time_ = new ::std::string;
  }
  begin_time_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* RoomInfo::mutable_begin_time() {
  set_has_begin_time();
  if (begin_time_ == &::google::protobuf::internal::kEmptyString) {
    begin_time_ = new ::std::string;
  }
  return begin_time_;
}
inline ::std::string* RoomInfo::release_begin_time() {
  clear_has_begin_time();
  if (begin_time_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = begin_time_;
    begin_time_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void RoomInfo::set_allocated_begin_time(::std::string* begin_time) {
  if (begin_time_ != &::google::protobuf::internal::kEmptyString) {
    delete begin_time_;
  }
  if (begin_time) {
    set_has_begin_time();
    begin_time_ = begin_time;
  } else {
    clear_has_begin_time();
    begin_time_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional .RoomData.Address address = 15;
inline bool RoomInfo::has_address() const {
  return (_has_bits_[0] & 0x00004000u) != 0;
}
inline void RoomInfo::set_has_address() {
  _has_bits_[0] |= 0x00004000u;
}
inline void RoomInfo::clear_has_address() {
  _has_bits_[0] &= ~0x00004000u;
}
inline void RoomInfo::clear_address() {
  if (address_ != NULL) address_->::RoomData::Address::Clear();
  clear_has_address();
}
inline const ::RoomData::Address& RoomInfo::address() const {
  return address_ != NULL ? *address_ : *default_instance_->address_;
}
inline ::RoomData::Address* RoomInfo::mutable_address() {
  set_has_address();
  if (address_ == NULL) address_ = new ::RoomData::Address;
  return address_;
}
inline ::RoomData::Address* RoomInfo::release_address() {
  clear_has_address();
  ::RoomData::Address* temp = address_;
  address_ = NULL;
  return temp;
}
inline void RoomInfo::set_allocated_address(::RoomData::Address* address) {
  delete address_;
  address_ = address;
  if (address) {
    set_has_address();
  } else {
    clear_has_address();
  }
}

// optional int32 join_status = 16;
inline bool RoomInfo::has_join_status() const {
  return (_has_bits_[0] & 0x00008000u) != 0;
}
inline void RoomInfo::set_has_join_status() {
  _has_bits_[0] |= 0x00008000u;
}
inline void RoomInfo::clear_has_join_status() {
  _has_bits_[0] &= ~0x00008000u;
}
inline void RoomInfo::clear_join_status() {
  join_status_ = 0;
  clear_has_join_status();
}
inline ::google::protobuf::int32 RoomInfo::join_status() const {
  return join_status_;
}
inline void RoomInfo::set_join_status(::google::protobuf::int32 value) {
  set_has_join_status();
  join_status_ = value;
}

// -------------------------------------------------------------------

// Address

// optional int32 addr_type = 1;
inline bool Address::has_addr_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Address::set_has_addr_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Address::clear_has_addr_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Address::clear_addr_type() {
  addr_type_ = 0;
  clear_has_addr_type();
}
inline ::google::protobuf::int32 Address::addr_type() const {
  return addr_type_;
}
inline void Address::set_addr_type(::google::protobuf::int32 value) {
  set_has_addr_type();
  addr_type_ = value;
}

// optional double longitude = 2;
inline bool Address::has_longitude() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Address::set_has_longitude() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Address::clear_has_longitude() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Address::clear_longitude() {
  longitude_ = 0;
  clear_has_longitude();
}
inline double Address::longitude() const {
  return longitude_;
}
inline void Address::set_longitude(double value) {
  set_has_longitude();
  longitude_ = value;
}

// optional double latitude = 3;
inline bool Address::has_latitude() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Address::set_has_latitude() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Address::clear_has_latitude() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Address::clear_latitude() {
  latitude_ = 0;
  clear_has_latitude();
}
inline double Address::latitude() const {
  return latitude_;
}
inline void Address::set_latitude(double value) {
  set_has_latitude();
  latitude_ = value;
}

// optional string detail_addr = 4;
inline bool Address::has_detail_addr() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Address::set_has_detail_addr() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Address::clear_has_detail_addr() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Address::clear_detail_addr() {
  if (detail_addr_ != &::google::protobuf::internal::kEmptyString) {
    detail_addr_->clear();
  }
  clear_has_detail_addr();
}
inline const ::std::string& Address::detail_addr() const {
  return *detail_addr_;
}
inline void Address::set_detail_addr(const ::std::string& value) {
  set_has_detail_addr();
  if (detail_addr_ == &::google::protobuf::internal::kEmptyString) {
    detail_addr_ = new ::std::string;
  }
  detail_addr_->assign(value);
}
inline void Address::set_detail_addr(const char* value) {
  set_has_detail_addr();
  if (detail_addr_ == &::google::protobuf::internal::kEmptyString) {
    detail_addr_ = new ::std::string;
  }
  detail_addr_->assign(value);
}
inline void Address::set_detail_addr(const char* value, size_t size) {
  set_has_detail_addr();
  if (detail_addr_ == &::google::protobuf::internal::kEmptyString) {
    detail_addr_ = new ::std::string;
  }
  detail_addr_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Address::mutable_detail_addr() {
  set_has_detail_addr();
  if (detail_addr_ == &::google::protobuf::internal::kEmptyString) {
    detail_addr_ = new ::std::string;
  }
  return detail_addr_;
}
inline ::std::string* Address::release_detail_addr() {
  clear_has_detail_addr();
  if (detail_addr_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = detail_addr_;
    detail_addr_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Address::set_allocated_detail_addr(::std::string* detail_addr) {
  if (detail_addr_ != &::google::protobuf::internal::kEmptyString) {
    delete detail_addr_;
  }
  if (detail_addr) {
    set_has_detail_addr();
    detail_addr_ = detail_addr;
  } else {
    clear_has_detail_addr();
    detail_addr_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional string addr_remark = 5;
inline bool Address::has_addr_remark() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Address::set_has_addr_remark() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Address::clear_has_addr_remark() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Address::clear_addr_remark() {
  if (addr_remark_ != &::google::protobuf::internal::kEmptyString) {
    addr_remark_->clear();
  }
  clear_has_addr_remark();
}
inline const ::std::string& Address::addr_remark() const {
  return *addr_remark_;
}
inline void Address::set_addr_remark(const ::std::string& value) {
  set_has_addr_remark();
  if (addr_remark_ == &::google::protobuf::internal::kEmptyString) {
    addr_remark_ = new ::std::string;
  }
  addr_remark_->assign(value);
}
inline void Address::set_addr_remark(const char* value) {
  set_has_addr_remark();
  if (addr_remark_ == &::google::protobuf::internal::kEmptyString) {
    addr_remark_ = new ::std::string;
  }
  addr_remark_->assign(value);
}
inline void Address::set_addr_remark(const char* value, size_t size) {
  set_has_addr_remark();
  if (addr_remark_ == &::google::protobuf::internal::kEmptyString) {
    addr_remark_ = new ::std::string;
  }
  addr_remark_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Address::mutable_addr_remark() {
  set_has_addr_remark();
  if (addr_remark_ == &::google::protobuf::internal::kEmptyString) {
    addr_remark_ = new ::std::string;
  }
  return addr_remark_;
}
inline ::std::string* Address::release_addr_remark() {
  clear_has_addr_remark();
  if (addr_remark_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = addr_remark_;
    addr_remark_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Address::set_allocated_addr_remark(::std::string* addr_remark) {
  if (addr_remark_ != &::google::protobuf::internal::kEmptyString) {
    delete addr_remark_;
  }
  if (addr_remark) {
    set_has_addr_remark();
    addr_remark_ = addr_remark;
  } else {
    clear_has_addr_remark();
    addr_remark_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace RoomData

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_RoomData_2eproto__INCLUDED
