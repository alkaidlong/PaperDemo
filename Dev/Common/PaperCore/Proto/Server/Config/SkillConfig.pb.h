// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SkillConfig.proto

#ifndef PROTOBUF_SkillConfig_2eproto__INCLUDED
#define PROTOBUF_SkillConfig_2eproto__INCLUDED

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
void  protobuf_AddDesc_SkillConfig_2eproto();
void protobuf_AssignDesc_SkillConfig_2eproto();
void protobuf_ShutdownFile_SkillConfig_2eproto();

class SkillConfigItem;
class SkillConfig;

// ===================================================================

class SkillConfigItem : public ::google::protobuf::Message {
 public:
  SkillConfigItem();
  virtual ~SkillConfigItem();

  SkillConfigItem(const SkillConfigItem& from);

  inline SkillConfigItem& operator=(const SkillConfigItem& from) {
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
  static const SkillConfigItem& default_instance();

  void Swap(SkillConfigItem* other);

  // implements Message ----------------------------------------------

  SkillConfigItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SkillConfigItem& from);
  void MergeFrom(const SkillConfigItem& from);
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

  // required .ServerProto.Logic.CommonProperty PhysicalProperty = 2;
  inline bool has_physicalproperty() const;
  inline void clear_physicalproperty();
  static const int kPhysicalPropertyFieldNumber = 2;
  inline const ::ServerProto::Logic::CommonProperty& physicalproperty() const;
  inline ::ServerProto::Logic::CommonProperty* mutable_physicalproperty();
  inline ::ServerProto::Logic::CommonProperty* release_physicalproperty();
  inline void set_allocated_physicalproperty(::ServerProto::Logic::CommonProperty* physicalproperty);

  // required .ServerProto.Logic.CommonProperty DeltaPhysicalProperty = 3;
  inline bool has_deltaphysicalproperty() const;
  inline void clear_deltaphysicalproperty();
  static const int kDeltaPhysicalPropertyFieldNumber = 3;
  inline const ::ServerProto::Logic::CommonProperty& deltaphysicalproperty() const;
  inline ::ServerProto::Logic::CommonProperty* mutable_deltaphysicalproperty();
  inline ::ServerProto::Logic::CommonProperty* release_deltaphysicalproperty();
  inline void set_allocated_deltaphysicalproperty(::ServerProto::Logic::CommonProperty* deltaphysicalproperty);

  // required .ServerProto.Logic.CommonProperty MagicalProperty = 4;
  inline bool has_magicalproperty() const;
  inline void clear_magicalproperty();
  static const int kMagicalPropertyFieldNumber = 4;
  inline const ::ServerProto::Logic::CommonProperty& magicalproperty() const;
  inline ::ServerProto::Logic::CommonProperty* mutable_magicalproperty();
  inline ::ServerProto::Logic::CommonProperty* release_magicalproperty();
  inline void set_allocated_magicalproperty(::ServerProto::Logic::CommonProperty* magicalproperty);

  // required .ServerProto.Logic.CommonProperty DeltaMagicalProperty = 5;
  inline bool has_deltamagicalproperty() const;
  inline void clear_deltamagicalproperty();
  static const int kDeltaMagicalPropertyFieldNumber = 5;
  inline const ::ServerProto::Logic::CommonProperty& deltamagicalproperty() const;
  inline ::ServerProto::Logic::CommonProperty* mutable_deltamagicalproperty();
  inline ::ServerProto::Logic::CommonProperty* release_deltamagicalproperty();
  inline void set_allocated_deltamagicalproperty(::ServerProto::Logic::CommonProperty* deltamagicalproperty);

  // required .ServerProto.Logic.CommonProperty HolyDamage = 6;
  inline bool has_holydamage() const;
  inline void clear_holydamage();
  static const int kHolyDamageFieldNumber = 6;
  inline const ::ServerProto::Logic::CommonProperty& holydamage() const;
  inline ::ServerProto::Logic::CommonProperty* mutable_holydamage();
  inline ::ServerProto::Logic::CommonProperty* release_holydamage();
  inline void set_allocated_holydamage(::ServerProto::Logic::CommonProperty* holydamage);

  // required .ServerProto.Logic.CommonProperty DeltaHolyPhysicalDamage = 7;
  inline bool has_deltaholyphysicaldamage() const;
  inline void clear_deltaholyphysicaldamage();
  static const int kDeltaHolyPhysicalDamageFieldNumber = 7;
  inline const ::ServerProto::Logic::CommonProperty& deltaholyphysicaldamage() const;
  inline ::ServerProto::Logic::CommonProperty* mutable_deltaholyphysicaldamage();
  inline ::ServerProto::Logic::CommonProperty* release_deltaholyphysicaldamage();
  inline void set_allocated_deltaholyphysicaldamage(::ServerProto::Logic::CommonProperty* deltaholyphysicaldamage);

  // required .ServerProto.Logic.CommonProperty DeltaHolyMagicalDamage = 8;
  inline bool has_deltaholymagicaldamage() const;
  inline void clear_deltaholymagicaldamage();
  static const int kDeltaHolyMagicalDamageFieldNumber = 8;
  inline const ::ServerProto::Logic::CommonProperty& deltaholymagicaldamage() const;
  inline ::ServerProto::Logic::CommonProperty* mutable_deltaholymagicaldamage();
  inline ::ServerProto::Logic::CommonProperty* release_deltaholymagicaldamage();
  inline void set_allocated_deltaholymagicaldamage(::ServerProto::Logic::CommonProperty* deltaholymagicaldamage);

  // @@protoc_insertion_point(class_scope:ServerProto.Config.SkillConfigItem)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_physicalproperty();
  inline void clear_has_physicalproperty();
  inline void set_has_deltaphysicalproperty();
  inline void clear_has_deltaphysicalproperty();
  inline void set_has_magicalproperty();
  inline void clear_has_magicalproperty();
  inline void set_has_deltamagicalproperty();
  inline void clear_has_deltamagicalproperty();
  inline void set_has_holydamage();
  inline void clear_has_holydamage();
  inline void set_has_deltaholyphysicaldamage();
  inline void clear_has_deltaholyphysicaldamage();
  inline void set_has_deltaholymagicaldamage();
  inline void clear_has_deltaholymagicaldamage();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::ServerProto::Logic::CommonProperty* physicalproperty_;
  ::ServerProto::Logic::CommonProperty* deltaphysicalproperty_;
  ::ServerProto::Logic::CommonProperty* magicalproperty_;
  ::ServerProto::Logic::CommonProperty* deltamagicalproperty_;
  ::ServerProto::Logic::CommonProperty* holydamage_;
  ::ServerProto::Logic::CommonProperty* deltaholyphysicaldamage_;
  ::ServerProto::Logic::CommonProperty* deltaholymagicaldamage_;
  ::google::protobuf::uint32 id_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(8 + 31) / 32];

  friend void  protobuf_AddDesc_SkillConfig_2eproto();
  friend void protobuf_AssignDesc_SkillConfig_2eproto();
  friend void protobuf_ShutdownFile_SkillConfig_2eproto();

  void InitAsDefaultInstance();
  static SkillConfigItem* default_instance_;
};
// -------------------------------------------------------------------

class SkillConfig : public ::google::protobuf::Message {
 public:
  SkillConfig();
  virtual ~SkillConfig();

  SkillConfig(const SkillConfig& from);

  inline SkillConfig& operator=(const SkillConfig& from) {
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
  static const SkillConfig& default_instance();

  void Swap(SkillConfig* other);

  // implements Message ----------------------------------------------

  SkillConfig* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SkillConfig& from);
  void MergeFrom(const SkillConfig& from);
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

  // repeated .ServerProto.Config.SkillConfigItem SkillConfigItems = 1;
  inline int skillconfigitems_size() const;
  inline void clear_skillconfigitems();
  static const int kSkillConfigItemsFieldNumber = 1;
  inline const ::ServerProto::Config::SkillConfigItem& skillconfigitems(int index) const;
  inline ::ServerProto::Config::SkillConfigItem* mutable_skillconfigitems(int index);
  inline ::ServerProto::Config::SkillConfigItem* add_skillconfigitems();
  inline const ::google::protobuf::RepeatedPtrField< ::ServerProto::Config::SkillConfigItem >&
      skillconfigitems() const;
  inline ::google::protobuf::RepeatedPtrField< ::ServerProto::Config::SkillConfigItem >*
      mutable_skillconfigitems();

  // @@protoc_insertion_point(class_scope:ServerProto.Config.SkillConfig)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::ServerProto::Config::SkillConfigItem > skillconfigitems_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_SkillConfig_2eproto();
  friend void protobuf_AssignDesc_SkillConfig_2eproto();
  friend void protobuf_ShutdownFile_SkillConfig_2eproto();

  void InitAsDefaultInstance();
  static SkillConfig* default_instance_;
};
// ===================================================================


// ===================================================================

// SkillConfigItem

// required uint32 Id = 1;
inline bool SkillConfigItem::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SkillConfigItem::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SkillConfigItem::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SkillConfigItem::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 SkillConfigItem::id() const {
  return id_;
}
inline void SkillConfigItem::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required .ServerProto.Logic.CommonProperty PhysicalProperty = 2;
inline bool SkillConfigItem::has_physicalproperty() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SkillConfigItem::set_has_physicalproperty() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SkillConfigItem::clear_has_physicalproperty() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SkillConfigItem::clear_physicalproperty() {
  if (physicalproperty_ != NULL) physicalproperty_->::ServerProto::Logic::CommonProperty::Clear();
  clear_has_physicalproperty();
}
inline const ::ServerProto::Logic::CommonProperty& SkillConfigItem::physicalproperty() const {
  return physicalproperty_ != NULL ? *physicalproperty_ : *default_instance_->physicalproperty_;
}
inline ::ServerProto::Logic::CommonProperty* SkillConfigItem::mutable_physicalproperty() {
  set_has_physicalproperty();
  if (physicalproperty_ == NULL) physicalproperty_ = new ::ServerProto::Logic::CommonProperty;
  return physicalproperty_;
}
inline ::ServerProto::Logic::CommonProperty* SkillConfigItem::release_physicalproperty() {
  clear_has_physicalproperty();
  ::ServerProto::Logic::CommonProperty* temp = physicalproperty_;
  physicalproperty_ = NULL;
  return temp;
}
inline void SkillConfigItem::set_allocated_physicalproperty(::ServerProto::Logic::CommonProperty* physicalproperty) {
  delete physicalproperty_;
  physicalproperty_ = physicalproperty;
  if (physicalproperty) {
    set_has_physicalproperty();
  } else {
    clear_has_physicalproperty();
  }
}

// required .ServerProto.Logic.CommonProperty DeltaPhysicalProperty = 3;
inline bool SkillConfigItem::has_deltaphysicalproperty() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void SkillConfigItem::set_has_deltaphysicalproperty() {
  _has_bits_[0] |= 0x00000004u;
}
inline void SkillConfigItem::clear_has_deltaphysicalproperty() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void SkillConfigItem::clear_deltaphysicalproperty() {
  if (deltaphysicalproperty_ != NULL) deltaphysicalproperty_->::ServerProto::Logic::CommonProperty::Clear();
  clear_has_deltaphysicalproperty();
}
inline const ::ServerProto::Logic::CommonProperty& SkillConfigItem::deltaphysicalproperty() const {
  return deltaphysicalproperty_ != NULL ? *deltaphysicalproperty_ : *default_instance_->deltaphysicalproperty_;
}
inline ::ServerProto::Logic::CommonProperty* SkillConfigItem::mutable_deltaphysicalproperty() {
  set_has_deltaphysicalproperty();
  if (deltaphysicalproperty_ == NULL) deltaphysicalproperty_ = new ::ServerProto::Logic::CommonProperty;
  return deltaphysicalproperty_;
}
inline ::ServerProto::Logic::CommonProperty* SkillConfigItem::release_deltaphysicalproperty() {
  clear_has_deltaphysicalproperty();
  ::ServerProto::Logic::CommonProperty* temp = deltaphysicalproperty_;
  deltaphysicalproperty_ = NULL;
  return temp;
}
inline void SkillConfigItem::set_allocated_deltaphysicalproperty(::ServerProto::Logic::CommonProperty* deltaphysicalproperty) {
  delete deltaphysicalproperty_;
  deltaphysicalproperty_ = deltaphysicalproperty;
  if (deltaphysicalproperty) {
    set_has_deltaphysicalproperty();
  } else {
    clear_has_deltaphysicalproperty();
  }
}

// required .ServerProto.Logic.CommonProperty MagicalProperty = 4;
inline bool SkillConfigItem::has_magicalproperty() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void SkillConfigItem::set_has_magicalproperty() {
  _has_bits_[0] |= 0x00000008u;
}
inline void SkillConfigItem::clear_has_magicalproperty() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void SkillConfigItem::clear_magicalproperty() {
  if (magicalproperty_ != NULL) magicalproperty_->::ServerProto::Logic::CommonProperty::Clear();
  clear_has_magicalproperty();
}
inline const ::ServerProto::Logic::CommonProperty& SkillConfigItem::magicalproperty() const {
  return magicalproperty_ != NULL ? *magicalproperty_ : *default_instance_->magicalproperty_;
}
inline ::ServerProto::Logic::CommonProperty* SkillConfigItem::mutable_magicalproperty() {
  set_has_magicalproperty();
  if (magicalproperty_ == NULL) magicalproperty_ = new ::ServerProto::Logic::CommonProperty;
  return magicalproperty_;
}
inline ::ServerProto::Logic::CommonProperty* SkillConfigItem::release_magicalproperty() {
  clear_has_magicalproperty();
  ::ServerProto::Logic::CommonProperty* temp = magicalproperty_;
  magicalproperty_ = NULL;
  return temp;
}
inline void SkillConfigItem::set_allocated_magicalproperty(::ServerProto::Logic::CommonProperty* magicalproperty) {
  delete magicalproperty_;
  magicalproperty_ = magicalproperty;
  if (magicalproperty) {
    set_has_magicalproperty();
  } else {
    clear_has_magicalproperty();
  }
}

// required .ServerProto.Logic.CommonProperty DeltaMagicalProperty = 5;
inline bool SkillConfigItem::has_deltamagicalproperty() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void SkillConfigItem::set_has_deltamagicalproperty() {
  _has_bits_[0] |= 0x00000010u;
}
inline void SkillConfigItem::clear_has_deltamagicalproperty() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void SkillConfigItem::clear_deltamagicalproperty() {
  if (deltamagicalproperty_ != NULL) deltamagicalproperty_->::ServerProto::Logic::CommonProperty::Clear();
  clear_has_deltamagicalproperty();
}
inline const ::ServerProto::Logic::CommonProperty& SkillConfigItem::deltamagicalproperty() const {
  return deltamagicalproperty_ != NULL ? *deltamagicalproperty_ : *default_instance_->deltamagicalproperty_;
}
inline ::ServerProto::Logic::CommonProperty* SkillConfigItem::mutable_deltamagicalproperty() {
  set_has_deltamagicalproperty();
  if (deltamagicalproperty_ == NULL) deltamagicalproperty_ = new ::ServerProto::Logic::CommonProperty;
  return deltamagicalproperty_;
}
inline ::ServerProto::Logic::CommonProperty* SkillConfigItem::release_deltamagicalproperty() {
  clear_has_deltamagicalproperty();
  ::ServerProto::Logic::CommonProperty* temp = deltamagicalproperty_;
  deltamagicalproperty_ = NULL;
  return temp;
}
inline void SkillConfigItem::set_allocated_deltamagicalproperty(::ServerProto::Logic::CommonProperty* deltamagicalproperty) {
  delete deltamagicalproperty_;
  deltamagicalproperty_ = deltamagicalproperty;
  if (deltamagicalproperty) {
    set_has_deltamagicalproperty();
  } else {
    clear_has_deltamagicalproperty();
  }
}

// required .ServerProto.Logic.CommonProperty HolyDamage = 6;
inline bool SkillConfigItem::has_holydamage() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void SkillConfigItem::set_has_holydamage() {
  _has_bits_[0] |= 0x00000020u;
}
inline void SkillConfigItem::clear_has_holydamage() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void SkillConfigItem::clear_holydamage() {
  if (holydamage_ != NULL) holydamage_->::ServerProto::Logic::CommonProperty::Clear();
  clear_has_holydamage();
}
inline const ::ServerProto::Logic::CommonProperty& SkillConfigItem::holydamage() const {
  return holydamage_ != NULL ? *holydamage_ : *default_instance_->holydamage_;
}
inline ::ServerProto::Logic::CommonProperty* SkillConfigItem::mutable_holydamage() {
  set_has_holydamage();
  if (holydamage_ == NULL) holydamage_ = new ::ServerProto::Logic::CommonProperty;
  return holydamage_;
}
inline ::ServerProto::Logic::CommonProperty* SkillConfigItem::release_holydamage() {
  clear_has_holydamage();
  ::ServerProto::Logic::CommonProperty* temp = holydamage_;
  holydamage_ = NULL;
  return temp;
}
inline void SkillConfigItem::set_allocated_holydamage(::ServerProto::Logic::CommonProperty* holydamage) {
  delete holydamage_;
  holydamage_ = holydamage;
  if (holydamage) {
    set_has_holydamage();
  } else {
    clear_has_holydamage();
  }
}

// required .ServerProto.Logic.CommonProperty DeltaHolyPhysicalDamage = 7;
inline bool SkillConfigItem::has_deltaholyphysicaldamage() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void SkillConfigItem::set_has_deltaholyphysicaldamage() {
  _has_bits_[0] |= 0x00000040u;
}
inline void SkillConfigItem::clear_has_deltaholyphysicaldamage() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void SkillConfigItem::clear_deltaholyphysicaldamage() {
  if (deltaholyphysicaldamage_ != NULL) deltaholyphysicaldamage_->::ServerProto::Logic::CommonProperty::Clear();
  clear_has_deltaholyphysicaldamage();
}
inline const ::ServerProto::Logic::CommonProperty& SkillConfigItem::deltaholyphysicaldamage() const {
  return deltaholyphysicaldamage_ != NULL ? *deltaholyphysicaldamage_ : *default_instance_->deltaholyphysicaldamage_;
}
inline ::ServerProto::Logic::CommonProperty* SkillConfigItem::mutable_deltaholyphysicaldamage() {
  set_has_deltaholyphysicaldamage();
  if (deltaholyphysicaldamage_ == NULL) deltaholyphysicaldamage_ = new ::ServerProto::Logic::CommonProperty;
  return deltaholyphysicaldamage_;
}
inline ::ServerProto::Logic::CommonProperty* SkillConfigItem::release_deltaholyphysicaldamage() {
  clear_has_deltaholyphysicaldamage();
  ::ServerProto::Logic::CommonProperty* temp = deltaholyphysicaldamage_;
  deltaholyphysicaldamage_ = NULL;
  return temp;
}
inline void SkillConfigItem::set_allocated_deltaholyphysicaldamage(::ServerProto::Logic::CommonProperty* deltaholyphysicaldamage) {
  delete deltaholyphysicaldamage_;
  deltaholyphysicaldamage_ = deltaholyphysicaldamage;
  if (deltaholyphysicaldamage) {
    set_has_deltaholyphysicaldamage();
  } else {
    clear_has_deltaholyphysicaldamage();
  }
}

// required .ServerProto.Logic.CommonProperty DeltaHolyMagicalDamage = 8;
inline bool SkillConfigItem::has_deltaholymagicaldamage() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void SkillConfigItem::set_has_deltaholymagicaldamage() {
  _has_bits_[0] |= 0x00000080u;
}
inline void SkillConfigItem::clear_has_deltaholymagicaldamage() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void SkillConfigItem::clear_deltaholymagicaldamage() {
  if (deltaholymagicaldamage_ != NULL) deltaholymagicaldamage_->::ServerProto::Logic::CommonProperty::Clear();
  clear_has_deltaholymagicaldamage();
}
inline const ::ServerProto::Logic::CommonProperty& SkillConfigItem::deltaholymagicaldamage() const {
  return deltaholymagicaldamage_ != NULL ? *deltaholymagicaldamage_ : *default_instance_->deltaholymagicaldamage_;
}
inline ::ServerProto::Logic::CommonProperty* SkillConfigItem::mutable_deltaholymagicaldamage() {
  set_has_deltaholymagicaldamage();
  if (deltaholymagicaldamage_ == NULL) deltaholymagicaldamage_ = new ::ServerProto::Logic::CommonProperty;
  return deltaholymagicaldamage_;
}
inline ::ServerProto::Logic::CommonProperty* SkillConfigItem::release_deltaholymagicaldamage() {
  clear_has_deltaholymagicaldamage();
  ::ServerProto::Logic::CommonProperty* temp = deltaholymagicaldamage_;
  deltaholymagicaldamage_ = NULL;
  return temp;
}
inline void SkillConfigItem::set_allocated_deltaholymagicaldamage(::ServerProto::Logic::CommonProperty* deltaholymagicaldamage) {
  delete deltaholymagicaldamage_;
  deltaholymagicaldamage_ = deltaholymagicaldamage;
  if (deltaholymagicaldamage) {
    set_has_deltaholymagicaldamage();
  } else {
    clear_has_deltaholymagicaldamage();
  }
}

// -------------------------------------------------------------------

// SkillConfig

// repeated .ServerProto.Config.SkillConfigItem SkillConfigItems = 1;
inline int SkillConfig::skillconfigitems_size() const {
  return skillconfigitems_.size();
}
inline void SkillConfig::clear_skillconfigitems() {
  skillconfigitems_.Clear();
}
inline const ::ServerProto::Config::SkillConfigItem& SkillConfig::skillconfigitems(int index) const {
  return skillconfigitems_.Get(index);
}
inline ::ServerProto::Config::SkillConfigItem* SkillConfig::mutable_skillconfigitems(int index) {
  return skillconfigitems_.Mutable(index);
}
inline ::ServerProto::Config::SkillConfigItem* SkillConfig::add_skillconfigitems() {
  return skillconfigitems_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ServerProto::Config::SkillConfigItem >&
SkillConfig::skillconfigitems() const {
  return skillconfigitems_;
}
inline ::google::protobuf::RepeatedPtrField< ::ServerProto::Config::SkillConfigItem >*
SkillConfig::mutable_skillconfigitems() {
  return &skillconfigitems_;
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

#endif  // PROTOBUF_SkillConfig_2eproto__INCLUDED
