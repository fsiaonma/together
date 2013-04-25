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

  // optional int32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int32 id() const;
  inline void set_id(::google::protobuf::int32 value);

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

  // optional string owner_nickname = 3;
  inline bool has_owner_nickname() const;
  inline void clear_owner_nickname();
  static const int kOwnerNicknameFieldNumber = 3;
  inline const ::std::string& owner_nickname() const;
  inline void set_owner_nickname(const ::std::string& value);
  inline void set_owner_nickname(const char* value);
  inline void set_owner_nickname(const char* value, size_t size);
  inline ::std::string* mutable_owner_nickname();
  inline ::std::string* release_owner_nickname();
  inline void set_allocated_owner_nickname(::std::string* owner_nickname);

  // optional int32 type = 4;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 4;
  inline ::google::protobuf::int32 type() const;
  inline void set_type(::google::protobuf::int32 value);

  // optional int32 status = 5;
  inline bool has_status() const;
  inline void clear_status();
  static const int kStatusFieldNumber = 5;
  inline ::google::protobuf::int32 status() const;
  inline void set_status(::google::protobuf::int32 value);

  // optional string pic_url = 6;
  inline bool has_pic_url() const;
  inline void clear_pic_url();
  static const int kPicUrlFieldNumber = 6;
  inline const ::std::string& pic_url() const;
  inline void set_pic_url(const ::std::string& value);
  inline void set_pic_url(const char* value);
  inline void set_pic_url(const char* value, size_t size);
  inline ::std::string* mutable_pic_url();
  inline ::std::string* release_pic_url();
  inline void set_allocated_pic_url(::std::string* pic_url);

  // optional int32 gender_type = 7;
  inline bool has_gender_type() const;
  inline void clear_gender_type();
  static const int kGenderTypeFieldNumber = 7;
  inline ::google::protobuf::int32 gender_type() const;
  inline void set_gender_type(::google::protobuf::int32 value);

  // optional double distance = 8;
  inline bool has_distance() const;
  inline void clear_distance();
  static const int kDistanceFieldNumber = 8;
  inline double distance() const;
  inline void set_distance(double value);

  // optional int32 join_person_count = 9;
  inline bool has_join_person_count() const;
  inline void clear_join_person_count();
  static const int kJoinPersonCountFieldNumber = 9;
  inline ::google::protobuf::int32 join_person_count() const;
  inline void set_join_person_count(::google::protobuf::int32 value);

  // optional int32 limit_person_count = 10;
  inline bool has_limit_person_count() const;
  inline void clear_limit_person_count();
  static const int kLimitPersonCountFieldNumber = 10;
  inline ::google::protobuf::int32 limit_person_count() const;
  inline void set_limit_person_count(::google::protobuf::int32 value);

  // optional string address = 11;
  inline bool has_address() const;
  inline void clear_address();
  static const int kAddressFieldNumber = 11;
  inline const ::std::string& address() const;
  inline void set_address(const ::std::string& value);
  inline void set_address(const char* value);
  inline void set_address(const char* value, size_t size);
  inline ::std::string* mutable_address();
  inline ::std::string* release_address();
  inline void set_allocated_address(::std::string* address);

  // optional string create_time = 12;
  inline bool has_create_time() const;
  inline void clear_create_time();
  static const int kCreateTimeFieldNumber = 12;
  inline const ::std::string& create_time() const;
  inline void set_create_time(const ::std::string& value);
  inline void set_create_time(const char* value);
  inline void set_create_time(const char* value, size_t size);
  inline ::std::string* mutable_create_time();
  inline ::std::string* release_create_time();
  inline void set_allocated_create_time(::std::string* create_time);

  // @@protoc_insertion_point(class_scope:RoomData.RoomInfo)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_title();
  inline void clear_has_title();
  inline void set_has_owner_nickname();
  inline void clear_has_owner_nickname();
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_status();
  inline void clear_has_status();
  inline void set_has_pic_url();
  inline void clear_has_pic_url();
  inline void set_has_gender_type();
  inline void clear_has_gender_type();
  inline void set_has_distance();
  inline void clear_has_distance();
  inline void set_has_join_person_count();
  inline void clear_has_join_person_count();
  inline void set_has_limit_person_count();
  inline void clear_has_limit_person_count();
  inline void set_has_address();
  inline void clear_has_address();
  inline void set_has_create_time();
  inline void clear_has_create_time();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* title_;
  ::google::protobuf::int32 id_;
  ::google::protobuf::int32 type_;
  ::std::string* owner_nickname_;
  ::std::string* pic_url_;
  ::google::protobuf::int32 status_;
  ::google::protobuf::int32 gender_type_;
  double distance_;
  ::google::protobuf::int32 join_person_count_;
  ::google::protobuf::int32 limit_person_count_;
  ::std::string* address_;
  ::std::string* create_time_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(12 + 31) / 32];

  friend void  protobuf_AddDesc_RoomData_2eproto();
  friend void protobuf_AssignDesc_RoomData_2eproto();
  friend void protobuf_ShutdownFile_RoomData_2eproto();

  void InitAsDefaultInstance();
  static RoomInfo* default_instance_;
};
// ===================================================================


// ===================================================================

// RoomInfo

// optional int32 id = 1;
inline bool RoomInfo::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RoomInfo::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RoomInfo::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RoomInfo::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 RoomInfo::id() const {
  return id_;
}
inline void RoomInfo::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
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

// optional string owner_nickname = 3;
inline bool RoomInfo::has_owner_nickname() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void RoomInfo::set_has_owner_nickname() {
  _has_bits_[0] |= 0x00000004u;
}
inline void RoomInfo::clear_has_owner_nickname() {
  _has_bits_[0] &= ~0x00000004u;
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

// optional int32 type = 4;
inline bool RoomInfo::has_type() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void RoomInfo::set_has_type() {
  _has_bits_[0] |= 0x00000008u;
}
inline void RoomInfo::clear_has_type() {
  _has_bits_[0] &= ~0x00000008u;
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

// optional int32 status = 5;
inline bool RoomInfo::has_status() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void RoomInfo::set_has_status() {
  _has_bits_[0] |= 0x00000010u;
}
inline void RoomInfo::clear_has_status() {
  _has_bits_[0] &= ~0x00000010u;
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

// optional string pic_url = 6;
inline bool RoomInfo::has_pic_url() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void RoomInfo::set_has_pic_url() {
  _has_bits_[0] |= 0x00000020u;
}
inline void RoomInfo::clear_has_pic_url() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void RoomInfo::clear_pic_url() {
  if (pic_url_ != &::google::protobuf::internal::kEmptyString) {
    pic_url_->clear();
  }
  clear_has_pic_url();
}
inline const ::std::string& RoomInfo::pic_url() const {
  return *pic_url_;
}
inline void RoomInfo::set_pic_url(const ::std::string& value) {
  set_has_pic_url();
  if (pic_url_ == &::google::protobuf::internal::kEmptyString) {
    pic_url_ = new ::std::string;
  }
  pic_url_->assign(value);
}
inline void RoomInfo::set_pic_url(const char* value) {
  set_has_pic_url();
  if (pic_url_ == &::google::protobuf::internal::kEmptyString) {
    pic_url_ = new ::std::string;
  }
  pic_url_->assign(value);
}
inline void RoomInfo::set_pic_url(const char* value, size_t size) {
  set_has_pic_url();
  if (pic_url_ == &::google::protobuf::internal::kEmptyString) {
    pic_url_ = new ::std::string;
  }
  pic_url_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* RoomInfo::mutable_pic_url() {
  set_has_pic_url();
  if (pic_url_ == &::google::protobuf::internal::kEmptyString) {
    pic_url_ = new ::std::string;
  }
  return pic_url_;
}
inline ::std::string* RoomInfo::release_pic_url() {
  clear_has_pic_url();
  if (pic_url_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = pic_url_;
    pic_url_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void RoomInfo::set_allocated_pic_url(::std::string* pic_url) {
  if (pic_url_ != &::google::protobuf::internal::kEmptyString) {
    delete pic_url_;
  }
  if (pic_url) {
    set_has_pic_url();
    pic_url_ = pic_url;
  } else {
    clear_has_pic_url();
    pic_url_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional int32 gender_type = 7;
inline bool RoomInfo::has_gender_type() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void RoomInfo::set_has_gender_type() {
  _has_bits_[0] |= 0x00000040u;
}
inline void RoomInfo::clear_has_gender_type() {
  _has_bits_[0] &= ~0x00000040u;
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

// optional double distance = 8;
inline bool RoomInfo::has_distance() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void RoomInfo::set_has_distance() {
  _has_bits_[0] |= 0x00000080u;
}
inline void RoomInfo::clear_has_distance() {
  _has_bits_[0] &= ~0x00000080u;
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

// optional int32 join_person_count = 9;
inline bool RoomInfo::has_join_person_count() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void RoomInfo::set_has_join_person_count() {
  _has_bits_[0] |= 0x00000100u;
}
inline void RoomInfo::clear_has_join_person_count() {
  _has_bits_[0] &= ~0x00000100u;
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

// optional int32 limit_person_count = 10;
inline bool RoomInfo::has_limit_person_count() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void RoomInfo::set_has_limit_person_count() {
  _has_bits_[0] |= 0x00000200u;
}
inline void RoomInfo::clear_has_limit_person_count() {
  _has_bits_[0] &= ~0x00000200u;
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

// optional string address = 11;
inline bool RoomInfo::has_address() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void RoomInfo::set_has_address() {
  _has_bits_[0] |= 0x00000400u;
}
inline void RoomInfo::clear_has_address() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void RoomInfo::clear_address() {
  if (address_ != &::google::protobuf::internal::kEmptyString) {
    address_->clear();
  }
  clear_has_address();
}
inline const ::std::string& RoomInfo::address() const {
  return *address_;
}
inline void RoomInfo::set_address(const ::std::string& value) {
  set_has_address();
  if (address_ == &::google::protobuf::internal::kEmptyString) {
    address_ = new ::std::string;
  }
  address_->assign(value);
}
inline void RoomInfo::set_address(const char* value) {
  set_has_address();
  if (address_ == &::google::protobuf::internal::kEmptyString) {
    address_ = new ::std::string;
  }
  address_->assign(value);
}
inline void RoomInfo::set_address(const char* value, size_t size) {
  set_has_address();
  if (address_ == &::google::protobuf::internal::kEmptyString) {
    address_ = new ::std::string;
  }
  address_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* RoomInfo::mutable_address() {
  set_has_address();
  if (address_ == &::google::protobuf::internal::kEmptyString) {
    address_ = new ::std::string;
  }
  return address_;
}
inline ::std::string* RoomInfo::release_address() {
  clear_has_address();
  if (address_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = address_;
    address_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void RoomInfo::set_allocated_address(::std::string* address) {
  if (address_ != &::google::protobuf::internal::kEmptyString) {
    delete address_;
  }
  if (address) {
    set_has_address();
    address_ = address;
  } else {
    clear_has_address();
    address_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional string create_time = 12;
inline bool RoomInfo::has_create_time() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void RoomInfo::set_has_create_time() {
  _has_bits_[0] |= 0x00000800u;
}
inline void RoomInfo::clear_has_create_time() {
  _has_bits_[0] &= ~0x00000800u;
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
