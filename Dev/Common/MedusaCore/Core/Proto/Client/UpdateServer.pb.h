// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UpdateServer.proto

#ifndef PROTOBUF_UpdateServer_2eproto__INCLUDED
#define PROTOBUF_UpdateServer_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include "CoreDefines.pb.h"
// @@protoc_insertion_point(includes)

namespace Medusa {
namespace CoreProto {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_UpdateServer_2eproto();
void protobuf_AssignDesc_UpdateServer_2eproto();
void protobuf_ShutdownFile_UpdateServer_2eproto();

class UpdateServer;

enum UpdateServer_UpdateServerStatus {
  UpdateServer_UpdateServerStatus_OK = 0,
  UpdateServer_UpdateServerStatus_Maintain = 1,
  UpdateServer_UpdateServerStatus_Error = 2,
  UpdateServer_UpdateServerStatus_DontUpgrade = 3
};
bool UpdateServer_UpdateServerStatus_IsValid(int value);
const UpdateServer_UpdateServerStatus UpdateServer_UpdateServerStatus_UpdateServerStatus_MIN = UpdateServer_UpdateServerStatus_OK;
const UpdateServer_UpdateServerStatus UpdateServer_UpdateServerStatus_UpdateServerStatus_MAX = UpdateServer_UpdateServerStatus_DontUpgrade;
const int UpdateServer_UpdateServerStatus_UpdateServerStatus_ARRAYSIZE = UpdateServer_UpdateServerStatus_UpdateServerStatus_MAX + 1;

const ::google::protobuf::EnumDescriptor* UpdateServer_UpdateServerStatus_descriptor();
inline const ::std::string& UpdateServer_UpdateServerStatus_Name(UpdateServer_UpdateServerStatus value) {
  return ::google::protobuf::internal::NameOfEnum(
    UpdateServer_UpdateServerStatus_descriptor(), value);
}
inline bool UpdateServer_UpdateServerStatus_Parse(
    const ::std::string& name, UpdateServer_UpdateServerStatus* value) {
  return ::google::protobuf::internal::ParseNamedEnum<UpdateServer_UpdateServerStatus>(
    UpdateServer_UpdateServerStatus_descriptor(), name, value);
}
// ===================================================================

class UpdateServer : public ::google::protobuf::Message {
 public:
  UpdateServer();
  virtual ~UpdateServer();

  UpdateServer(const UpdateServer& from);

  inline UpdateServer& operator=(const UpdateServer& from) {
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
  static const UpdateServer& default_instance();

  void Swap(UpdateServer* other);

  // implements Message ----------------------------------------------

  UpdateServer* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UpdateServer& from);
  void MergeFrom(const UpdateServer& from);
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

  typedef UpdateServer_UpdateServerStatus UpdateServerStatus;
  static const UpdateServerStatus OK = UpdateServer_UpdateServerStatus_OK;
  static const UpdateServerStatus Maintain = UpdateServer_UpdateServerStatus_Maintain;
  static const UpdateServerStatus Error = UpdateServer_UpdateServerStatus_Error;
  static const UpdateServerStatus DontUpgrade = UpdateServer_UpdateServerStatus_DontUpgrade;
  static inline bool UpdateServerStatus_IsValid(int value) {
    return UpdateServer_UpdateServerStatus_IsValid(value);
  }
  static const UpdateServerStatus UpdateServerStatus_MIN =
    UpdateServer_UpdateServerStatus_UpdateServerStatus_MIN;
  static const UpdateServerStatus UpdateServerStatus_MAX =
    UpdateServer_UpdateServerStatus_UpdateServerStatus_MAX;
  static const int UpdateServerStatus_ARRAYSIZE =
    UpdateServer_UpdateServerStatus_UpdateServerStatus_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  UpdateServerStatus_descriptor() {
    return UpdateServer_UpdateServerStatus_descriptor();
  }
  static inline const ::std::string& UpdateServerStatus_Name(UpdateServerStatus value) {
    return UpdateServer_UpdateServerStatus_Name(value);
  }
  static inline bool UpdateServerStatus_Parse(const ::std::string& name,
      UpdateServerStatus* value) {
    return UpdateServer_UpdateServerStatus_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // required .Medusa.CoreProto.UpdateServer.UpdateServerStatus Status = 1;
  inline bool has_status() const;
  inline void clear_status();
  static const int kStatusFieldNumber = 1;
  inline ::Medusa::CoreProto::UpdateServer_UpdateServerStatus status() const;
  inline void set_status(::Medusa::CoreProto::UpdateServer_UpdateServerStatus value);

  // required .Medusa.CoreProto.Version MinVersion = 2;
  inline bool has_minversion() const;
  inline void clear_minversion();
  static const int kMinVersionFieldNumber = 2;
  inline const ::Medusa::CoreProto::Version& minversion() const;
  inline ::Medusa::CoreProto::Version* mutable_minversion();
  inline ::Medusa::CoreProto::Version* release_minversion();
  inline void set_allocated_minversion(::Medusa::CoreProto::Version* minversion);

  // required .Medusa.CoreProto.Version CurVersion = 3;
  inline bool has_curversion() const;
  inline void clear_curversion();
  static const int kCurVersionFieldNumber = 3;
  inline const ::Medusa::CoreProto::Version& curversion() const;
  inline ::Medusa::CoreProto::Version* mutable_curversion();
  inline ::Medusa::CoreProto::Version* release_curversion();
  inline void set_allocated_curversion(::Medusa::CoreProto::Version* curversion);

  // required string Description = 4;
  inline bool has_description() const;
  inline void clear_description();
  static const int kDescriptionFieldNumber = 4;
  inline const ::std::string& description() const;
  inline void set_description(const ::std::string& value);
  inline void set_description(const char* value);
  inline void set_description(const char* value, size_t size);
  inline ::std::string* mutable_description();
  inline ::std::string* release_description();
  inline void set_allocated_description(::std::string* description);

  // @@protoc_insertion_point(class_scope:Medusa.CoreProto.UpdateServer)
 private:
  inline void set_has_status();
  inline void clear_has_status();
  inline void set_has_minversion();
  inline void clear_has_minversion();
  inline void set_has_curversion();
  inline void clear_has_curversion();
  inline void set_has_description();
  inline void clear_has_description();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::Medusa::CoreProto::Version* minversion_;
  ::Medusa::CoreProto::Version* curversion_;
  ::std::string* description_;
  int status_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];

  friend void  protobuf_AddDesc_UpdateServer_2eproto();
  friend void protobuf_AssignDesc_UpdateServer_2eproto();
  friend void protobuf_ShutdownFile_UpdateServer_2eproto();

  void InitAsDefaultInstance();
  static UpdateServer* default_instance_;
};
// ===================================================================


// ===================================================================

// UpdateServer

// required .Medusa.CoreProto.UpdateServer.UpdateServerStatus Status = 1;
inline bool UpdateServer::has_status() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UpdateServer::set_has_status() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UpdateServer::clear_has_status() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UpdateServer::clear_status() {
  status_ = 0;
  clear_has_status();
}
inline ::Medusa::CoreProto::UpdateServer_UpdateServerStatus UpdateServer::status() const {
  return static_cast< ::Medusa::CoreProto::UpdateServer_UpdateServerStatus >(status_);
}
inline void UpdateServer::set_status(::Medusa::CoreProto::UpdateServer_UpdateServerStatus value) {
  assert(::Medusa::CoreProto::UpdateServer_UpdateServerStatus_IsValid(value));
  set_has_status();
  status_ = value;
}

// required .Medusa.CoreProto.Version MinVersion = 2;
inline bool UpdateServer::has_minversion() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UpdateServer::set_has_minversion() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UpdateServer::clear_has_minversion() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UpdateServer::clear_minversion() {
  if (minversion_ != NULL) minversion_->::Medusa::CoreProto::Version::Clear();
  clear_has_minversion();
}
inline const ::Medusa::CoreProto::Version& UpdateServer::minversion() const {
  return minversion_ != NULL ? *minversion_ : *default_instance_->minversion_;
}
inline ::Medusa::CoreProto::Version* UpdateServer::mutable_minversion() {
  set_has_minversion();
  if (minversion_ == NULL) minversion_ = new ::Medusa::CoreProto::Version;
  return minversion_;
}
inline ::Medusa::CoreProto::Version* UpdateServer::release_minversion() {
  clear_has_minversion();
  ::Medusa::CoreProto::Version* temp = minversion_;
  minversion_ = NULL;
  return temp;
}
inline void UpdateServer::set_allocated_minversion(::Medusa::CoreProto::Version* minversion) {
  delete minversion_;
  minversion_ = minversion;
  if (minversion) {
    set_has_minversion();
  } else {
    clear_has_minversion();
  }
}

// required .Medusa.CoreProto.Version CurVersion = 3;
inline bool UpdateServer::has_curversion() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void UpdateServer::set_has_curversion() {
  _has_bits_[0] |= 0x00000004u;
}
inline void UpdateServer::clear_has_curversion() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void UpdateServer::clear_curversion() {
  if (curversion_ != NULL) curversion_->::Medusa::CoreProto::Version::Clear();
  clear_has_curversion();
}
inline const ::Medusa::CoreProto::Version& UpdateServer::curversion() const {
  return curversion_ != NULL ? *curversion_ : *default_instance_->curversion_;
}
inline ::Medusa::CoreProto::Version* UpdateServer::mutable_curversion() {
  set_has_curversion();
  if (curversion_ == NULL) curversion_ = new ::Medusa::CoreProto::Version;
  return curversion_;
}
inline ::Medusa::CoreProto::Version* UpdateServer::release_curversion() {
  clear_has_curversion();
  ::Medusa::CoreProto::Version* temp = curversion_;
  curversion_ = NULL;
  return temp;
}
inline void UpdateServer::set_allocated_curversion(::Medusa::CoreProto::Version* curversion) {
  delete curversion_;
  curversion_ = curversion;
  if (curversion) {
    set_has_curversion();
  } else {
    clear_has_curversion();
  }
}

// required string Description = 4;
inline bool UpdateServer::has_description() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void UpdateServer::set_has_description() {
  _has_bits_[0] |= 0x00000008u;
}
inline void UpdateServer::clear_has_description() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void UpdateServer::clear_description() {
  if (description_ != &::google::protobuf::internal::kEmptyString) {
    description_->clear();
  }
  clear_has_description();
}
inline const ::std::string& UpdateServer::description() const {
  return *description_;
}
inline void UpdateServer::set_description(const ::std::string& value) {
  set_has_description();
  if (description_ == &::google::protobuf::internal::kEmptyString) {
    description_ = new ::std::string;
  }
  description_->assign(value);
}
inline void UpdateServer::set_description(const char* value) {
  set_has_description();
  if (description_ == &::google::protobuf::internal::kEmptyString) {
    description_ = new ::std::string;
  }
  description_->assign(value);
}
inline void UpdateServer::set_description(const char* value, size_t size) {
  set_has_description();
  if (description_ == &::google::protobuf::internal::kEmptyString) {
    description_ = new ::std::string;
  }
  description_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* UpdateServer::mutable_description() {
  set_has_description();
  if (description_ == &::google::protobuf::internal::kEmptyString) {
    description_ = new ::std::string;
  }
  return description_;
}
inline ::std::string* UpdateServer::release_description() {
  clear_has_description();
  if (description_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = description_;
    description_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void UpdateServer::set_allocated_description(::std::string* description) {
  if (description_ != &::google::protobuf::internal::kEmptyString) {
    delete description_;
  }
  if (description) {
    set_has_description();
    description_ = description;
  } else {
    clear_has_description();
    description_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace CoreProto
}  // namespace Medusa

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Medusa::CoreProto::UpdateServer_UpdateServerStatus>() {
  return ::Medusa::CoreProto::UpdateServer_UpdateServerStatus_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_UpdateServer_2eproto__INCLUDED