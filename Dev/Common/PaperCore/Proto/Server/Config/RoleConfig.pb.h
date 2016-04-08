// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: RoleConfig.proto

#ifndef PROTOBUF_RoleConfig_2eproto__INCLUDED
#define PROTOBUF_RoleConfig_2eproto__INCLUDED

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
#include <google/protobuf/unknown_field_set.h>
#include "BaseProperty.pb.h"
// @@protoc_insertion_point(includes)

namespace ServerProto {
namespace Config {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_RoleConfig_2eproto();
void protobuf_AssignDesc_RoleConfig_2eproto();
void protobuf_ShutdownFile_RoleConfig_2eproto();

class RoleConfigItem;
class RoleConfig;

// ===================================================================

class RoleConfigItem : public ::google::protobuf::Message {
 public:
  RoleConfigItem();
  virtual ~RoleConfigItem();

  RoleConfigItem(const RoleConfigItem& from);

  inline RoleConfigItem& operator=(const RoleConfigItem& from) {
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
  static const RoleConfigItem& default_instance();

  void Swap(RoleConfigItem* other);

  // implements Message ----------------------------------------------

  RoleConfigItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RoleConfigItem& from);
  void MergeFrom(const RoleConfigItem& from);
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

  // required uint32 Id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::uint32 id() const;
  inline void set_id(::google::protobuf::uint32 value);

  // required .ServerProto.Logic.BaseProperty Property = 2;
  inline bool has_property() const;
  inline void clear_property();
  static const int kPropertyFieldNumber = 2;
  inline const ::ServerProto::Logic::BaseProperty& property() const;
  inline ::ServerProto::Logic::BaseProperty* mutable_property();
  inline ::ServerProto::Logic::BaseProperty* release_property();
  inline void set_allocated_property(::ServerProto::Logic::BaseProperty* property);

  // required .ServerProto.Logic.BaseProperty DeltaProperty = 3;
  inline bool has_deltaproperty() const;
  inline void clear_deltaproperty();
  static const int kDeltaPropertyFieldNumber = 3;
  inline const ::ServerProto::Logic::BaseProperty& deltaproperty() const;
  inline ::ServerProto::Logic::BaseProperty* mutable_deltaproperty();
  inline ::ServerProto::Logic::BaseProperty* release_deltaproperty();
  inline void set_allocated_deltaproperty(::ServerProto::Logic::BaseProperty* deltaproperty);

  // @@protoc_insertion_point(class_scope:ServerProto.Config.RoleConfigItem)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_property();
  inline void clear_has_property();
  inline void set_has_deltaproperty();
  inline void clear_has_deltaproperty();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::ServerProto::Logic::BaseProperty* property_;
  ::ServerProto::Logic::BaseProperty* deltaproperty_;
  ::google::protobuf::uint32 id_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_RoleConfig_2eproto();
  friend void protobuf_AssignDesc_RoleConfig_2eproto();
  friend void protobuf_ShutdownFile_RoleConfig_2eproto();

  void InitAsDefaultInstance();
  static RoleConfigItem* default_instance_;
};
// -------------------------------------------------------------------

class RoleConfig : public ::google::protobuf::Message {
 public:
  RoleConfig();
  virtual ~RoleConfig();

  RoleConfig(const RoleConfig& from);

  inline RoleConfig& operator=(const RoleConfig& from) {
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
  static const RoleConfig& default_instance();

  void Swap(RoleConfig* other);

  // implements Message ----------------------------------------------

  RoleConfig* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RoleConfig& from);
  void MergeFrom(const RoleConfig& from);
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

  // repeated .ServerProto.Config.RoleConfigItem RoleConfigItems = 1;
  inline int roleconfigitems_size() const;
  inline void clear_roleconfigitems();
  static const int kRoleConfigItemsFieldNumber = 1;
  inline const ::ServerProto::Config::RoleConfigItem& roleconfigitems(int index) const;
  inline ::ServerProto::Config::RoleConfigItem* mutable_roleconfigitems(int index);
  inline ::ServerProto::Config::RoleConfigItem* add_roleconfigitems();
  inline const ::google::protobuf::RepeatedPtrField< ::ServerProto::Config::RoleConfigItem >&
      roleconfigitems() const;
  inline ::google::protobuf::RepeatedPtrField< ::ServerProto::Config::RoleConfigItem >*
      mutable_roleconfigitems();

  // @@protoc_insertion_point(class_scope:ServerProto.Config.RoleConfig)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::ServerProto::Config::RoleConfigItem > roleconfigitems_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_RoleConfig_2eproto();
  friend void protobuf_AssignDesc_RoleConfig_2eproto();
  friend void protobuf_ShutdownFile_RoleConfig_2eproto();

  void InitAsDefaultInstance();
  static RoleConfig* default_instance_;
};
// ===================================================================


// ===================================================================

// RoleConfigItem

// required uint32 Id = 1;
inline bool RoleConfigItem::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RoleConfigItem::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RoleConfigItem::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RoleConfigItem::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 RoleConfigItem::id() const {
  return id_;
}
inline void RoleConfigItem::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required .ServerProto.Logic.BaseProperty Property = 2;
inline bool RoleConfigItem::has_property() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RoleConfigItem::set_has_property() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RoleConfigItem::clear_has_property() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RoleConfigItem::clear_property() {
  if (property_ != NULL) property_->::ServerProto::Logic::BaseProperty::Clear();
  clear_has_property();
}
inline const ::ServerProto::Logic::BaseProperty& RoleConfigItem::property() const {
  return property_ != NULL ? *property_ : *default_instance_->property_;
}
inline ::ServerProto::Logic::BaseProperty* RoleConfigItem::mutable_property() {
  set_has_property();
  if (property_ == NULL) property_ = new ::ServerProto::Logic::BaseProperty;
  return property_;
}
inline ::ServerProto::Logic::BaseProperty* RoleConfigItem::release_property() {
  clear_has_property();
  ::ServerProto::Logic::BaseProperty* temp = property_;
  property_ = NULL;
  return temp;
}
inline void RoleConfigItem::set_allocated_property(::ServerProto::Logic::BaseProperty* property) {
  delete property_;
  property_ = property;
  if (property) {
    set_has_property();
  } else {
    clear_has_property();
  }
}

// required .ServerProto.Logic.BaseProperty DeltaProperty = 3;
inline bool RoleConfigItem::has_deltaproperty() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void RoleConfigItem::set_has_deltaproperty() {
  _has_bits_[0] |= 0x00000004u;
}
inline void RoleConfigItem::clear_has_deltaproperty() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void RoleConfigItem::clear_deltaproperty() {
  if (deltaproperty_ != NULL) deltaproperty_->::ServerProto::Logic::BaseProperty::Clear();
  clear_has_deltaproperty();
}
inline const ::ServerProto::Logic::BaseProperty& RoleConfigItem::deltaproperty() const {
  return deltaproperty_ != NULL ? *deltaproperty_ : *default_instance_->deltaproperty_;
}
inline ::ServerProto::Logic::BaseProperty* RoleConfigItem::mutable_deltaproperty() {
  set_has_deltaproperty();
  if (deltaproperty_ == NULL) deltaproperty_ = new ::ServerProto::Logic::BaseProperty;
  return deltaproperty_;
}
inline ::ServerProto::Logic::BaseProperty* RoleConfigItem::release_deltaproperty() {
  clear_has_deltaproperty();
  ::ServerProto::Logic::BaseProperty* temp = deltaproperty_;
  deltaproperty_ = NULL;
  return temp;
}
inline void RoleConfigItem::set_allocated_deltaproperty(::ServerProto::Logic::BaseProperty* deltaproperty) {
  delete deltaproperty_;
  deltaproperty_ = deltaproperty;
  if (deltaproperty) {
    set_has_deltaproperty();
  } else {
    clear_has_deltaproperty();
  }
}

// -------------------------------------------------------------------

// RoleConfig

// repeated .ServerProto.Config.RoleConfigItem RoleConfigItems = 1;
inline int RoleConfig::roleconfigitems_size() const {
  return roleconfigitems_.size();
}
inline void RoleConfig::clear_roleconfigitems() {
  roleconfigitems_.Clear();
}
inline const ::ServerProto::Config::RoleConfigItem& RoleConfig::roleconfigitems(int index) const {
  return roleconfigitems_.Get(index);
}
inline ::ServerProto::Config::RoleConfigItem* RoleConfig::mutable_roleconfigitems(int index) {
  return roleconfigitems_.Mutable(index);
}
inline ::ServerProto::Config::RoleConfigItem* RoleConfig::add_roleconfigitems() {
  return roleconfigitems_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ServerProto::Config::RoleConfigItem >&
RoleConfig::roleconfigitems() const {
  return roleconfigitems_;
}
inline ::google::protobuf::RepeatedPtrField< ::ServerProto::Config::RoleConfigItem >*
RoleConfig::mutable_roleconfigitems() {
  return &roleconfigitems_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Config
}  // namespace ServerProto

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_RoleConfig_2eproto__INCLUDED