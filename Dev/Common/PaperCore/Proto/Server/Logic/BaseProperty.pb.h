// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: BaseProperty.proto

#ifndef PROTOBUF_BaseProperty_2eproto__INCLUDED
#define PROTOBUF_BaseProperty_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

namespace ServerProto {
namespace Logic {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_BaseProperty_2eproto();
void protobuf_AssignDesc_BaseProperty_2eproto();
void protobuf_ShutdownFile_BaseProperty_2eproto();

class CommonProperty;
class BaseProperty;

// ===================================================================

class CommonProperty : public ::google::protobuf::Message {
 public:
  CommonProperty();
  virtual ~CommonProperty();

  CommonProperty(const CommonProperty& from);

  inline CommonProperty& operator=(const CommonProperty& from) {
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
  static const CommonProperty& default_instance();

  void Swap(CommonProperty* other);

  // implements Message ----------------------------------------------

  CommonProperty* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CommonProperty& from);
  void MergeFrom(const CommonProperty& from);
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

  // required float MaxValue = 1;
  inline bool has_maxvalue() const;
  inline void clear_maxvalue();
  static const int kMaxValueFieldNumber = 1;
  inline float maxvalue() const;
  inline void set_maxvalue(float value);

  // required float ValueRegeneration = 2;
  inline bool has_valueregeneration() const;
  inline void clear_valueregeneration();
  static const int kValueRegenerationFieldNumber = 2;
  inline float valueregeneration() const;
  inline void set_valueregeneration(float value);

  // required float Attack = 3;
  inline bool has_attack() const;
  inline void clear_attack();
  static const int kAttackFieldNumber = 3;
  inline float attack() const;
  inline void set_attack(float value);

  // required float Defense = 4;
  inline bool has_defense() const;
  inline void clear_defense();
  static const int kDefenseFieldNumber = 4;
  inline float defense() const;
  inline void set_defense(float value);

  // required float DefensePenetration = 5;
  inline bool has_defensepenetration() const;
  inline void clear_defensepenetration();
  static const int kDefensePenetrationFieldNumber = 5;
  inline float defensepenetration() const;
  inline void set_defensepenetration(float value);

  // required float LifeSteal = 6;
  inline bool has_lifesteal() const;
  inline void clear_lifesteal();
  static const int kLifeStealFieldNumber = 6;
  inline float lifesteal() const;
  inline void set_lifesteal(float value);

  // required float Critical = 7;
  inline bool has_critical() const;
  inline void clear_critical();
  static const int kCriticalFieldNumber = 7;
  inline float critical() const;
  inline void set_critical(float value);

  // required float CriticalDamage = 8;
  inline bool has_criticaldamage() const;
  inline void clear_criticaldamage();
  static const int kCriticalDamageFieldNumber = 8;
  inline float criticaldamage() const;
  inline void set_criticaldamage(float value);

  // required float Toughness = 9;
  inline bool has_toughness() const;
  inline void clear_toughness();
  static const int kToughnessFieldNumber = 9;
  inline float toughness() const;
  inline void set_toughness(float value);

  // @@protoc_insertion_point(class_scope:ServerProto.Logic.CommonProperty)
 private:
  inline void set_has_maxvalue();
  inline void clear_has_maxvalue();
  inline void set_has_valueregeneration();
  inline void clear_has_valueregeneration();
  inline void set_has_attack();
  inline void clear_has_attack();
  inline void set_has_defense();
  inline void clear_has_defense();
  inline void set_has_defensepenetration();
  inline void clear_has_defensepenetration();
  inline void set_has_lifesteal();
  inline void clear_has_lifesteal();
  inline void set_has_critical();
  inline void clear_has_critical();
  inline void set_has_criticaldamage();
  inline void clear_has_criticaldamage();
  inline void set_has_toughness();
  inline void clear_has_toughness();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  float maxvalue_;
  float valueregeneration_;
  float attack_;
  float defense_;
  float defensepenetration_;
  float lifesteal_;
  float critical_;
  float criticaldamage_;
  float toughness_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(9 + 31) / 32];

  friend void  protobuf_AddDesc_BaseProperty_2eproto();
  friend void protobuf_AssignDesc_BaseProperty_2eproto();
  friend void protobuf_ShutdownFile_BaseProperty_2eproto();

  void InitAsDefaultInstance();
  static CommonProperty* default_instance_;
};
// -------------------------------------------------------------------

class BaseProperty : public ::google::protobuf::Message {
 public:
  BaseProperty();
  virtual ~BaseProperty();

  BaseProperty(const BaseProperty& from);

  inline BaseProperty& operator=(const BaseProperty& from) {
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
  static const BaseProperty& default_instance();

  void Swap(BaseProperty* other);

  // implements Message ----------------------------------------------

  BaseProperty* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BaseProperty& from);
  void MergeFrom(const BaseProperty& from);
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

  // optional .ServerProto.Logic.CommonProperty PhysicalProperty = 1;
  inline bool has_physicalproperty() const;
  inline void clear_physicalproperty();
  static const int kPhysicalPropertyFieldNumber = 1;
  inline const ::ServerProto::Logic::CommonProperty& physicalproperty() const;
  inline ::ServerProto::Logic::CommonProperty* mutable_physicalproperty();
  inline ::ServerProto::Logic::CommonProperty* release_physicalproperty();
  inline void set_allocated_physicalproperty(::ServerProto::Logic::CommonProperty* physicalproperty);

  // optional .ServerProto.Logic.CommonProperty MagicalProperty = 2;
  inline bool has_magicalproperty() const;
  inline void clear_magicalproperty();
  static const int kMagicalPropertyFieldNumber = 2;
  inline const ::ServerProto::Logic::CommonProperty& magicalproperty() const;
  inline ::ServerProto::Logic::CommonProperty* mutable_magicalproperty();
  inline ::ServerProto::Logic::CommonProperty* release_magicalproperty();
  inline void set_allocated_magicalproperty(::ServerProto::Logic::CommonProperty* magicalproperty);

  // required float CoolingReduction = 3;
  inline bool has_coolingreduction() const;
  inline void clear_coolingreduction();
  static const int kCoolingReductionFieldNumber = 3;
  inline float coolingreduction() const;
  inline void set_coolingreduction(float value);

  // required float AttackSpeed = 4;
  inline bool has_attackspeed() const;
  inline void clear_attackspeed();
  static const int kAttackSpeedFieldNumber = 4;
  inline float attackspeed() const;
  inline void set_attackspeed(float value);

  // required float MoveSpeed = 5;
  inline bool has_movespeed() const;
  inline void clear_movespeed();
  static const int kMoveSpeedFieldNumber = 5;
  inline float movespeed() const;
  inline void set_movespeed(float value);

  // @@protoc_insertion_point(class_scope:ServerProto.Logic.BaseProperty)
 private:
  inline void set_has_physicalproperty();
  inline void clear_has_physicalproperty();
  inline void set_has_magicalproperty();
  inline void clear_has_magicalproperty();
  inline void set_has_coolingreduction();
  inline void clear_has_coolingreduction();
  inline void set_has_attackspeed();
  inline void clear_has_attackspeed();
  inline void set_has_movespeed();
  inline void clear_has_movespeed();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::ServerProto::Logic::CommonProperty* physicalproperty_;
  ::ServerProto::Logic::CommonProperty* magicalproperty_;
  float coolingreduction_;
  float attackspeed_;
  float movespeed_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];

  friend void  protobuf_AddDesc_BaseProperty_2eproto();
  friend void protobuf_AssignDesc_BaseProperty_2eproto();
  friend void protobuf_ShutdownFile_BaseProperty_2eproto();

  void InitAsDefaultInstance();
  static BaseProperty* default_instance_;
};
// ===================================================================


// ===================================================================

// CommonProperty

// required float MaxValue = 1;
inline bool CommonProperty::has_maxvalue() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CommonProperty::set_has_maxvalue() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CommonProperty::clear_has_maxvalue() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CommonProperty::clear_maxvalue() {
  maxvalue_ = 0;
  clear_has_maxvalue();
}
inline float CommonProperty::maxvalue() const {
  return maxvalue_;
}
inline void CommonProperty::set_maxvalue(float value) {
  set_has_maxvalue();
  maxvalue_ = value;
}

// required float ValueRegeneration = 2;
inline bool CommonProperty::has_valueregeneration() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CommonProperty::set_has_valueregeneration() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CommonProperty::clear_has_valueregeneration() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CommonProperty::clear_valueregeneration() {
  valueregeneration_ = 0;
  clear_has_valueregeneration();
}
inline float CommonProperty::valueregeneration() const {
  return valueregeneration_;
}
inline void CommonProperty::set_valueregeneration(float value) {
  set_has_valueregeneration();
  valueregeneration_ = value;
}

// required float Attack = 3;
inline bool CommonProperty::has_attack() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void CommonProperty::set_has_attack() {
  _has_bits_[0] |= 0x00000004u;
}
inline void CommonProperty::clear_has_attack() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void CommonProperty::clear_attack() {
  attack_ = 0;
  clear_has_attack();
}
inline float CommonProperty::attack() const {
  return attack_;
}
inline void CommonProperty::set_attack(float value) {
  set_has_attack();
  attack_ = value;
}

// required float Defense = 4;
inline bool CommonProperty::has_defense() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void CommonProperty::set_has_defense() {
  _has_bits_[0] |= 0x00000008u;
}
inline void CommonProperty::clear_has_defense() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void CommonProperty::clear_defense() {
  defense_ = 0;
  clear_has_defense();
}
inline float CommonProperty::defense() const {
  return defense_;
}
inline void CommonProperty::set_defense(float value) {
  set_has_defense();
  defense_ = value;
}

// required float DefensePenetration = 5;
inline bool CommonProperty::has_defensepenetration() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void CommonProperty::set_has_defensepenetration() {
  _has_bits_[0] |= 0x00000010u;
}
inline void CommonProperty::clear_has_defensepenetration() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void CommonProperty::clear_defensepenetration() {
  defensepenetration_ = 0;
  clear_has_defensepenetration();
}
inline float CommonProperty::defensepenetration() const {
  return defensepenetration_;
}
inline void CommonProperty::set_defensepenetration(float value) {
  set_has_defensepenetration();
  defensepenetration_ = value;
}

// required float LifeSteal = 6;
inline bool CommonProperty::has_lifesteal() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void CommonProperty::set_has_lifesteal() {
  _has_bits_[0] |= 0x00000020u;
}
inline void CommonProperty::clear_has_lifesteal() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void CommonProperty::clear_lifesteal() {
  lifesteal_ = 0;
  clear_has_lifesteal();
}
inline float CommonProperty::lifesteal() const {
  return lifesteal_;
}
inline void CommonProperty::set_lifesteal(float value) {
  set_has_lifesteal();
  lifesteal_ = value;
}

// required float Critical = 7;
inline bool CommonProperty::has_critical() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void CommonProperty::set_has_critical() {
  _has_bits_[0] |= 0x00000040u;
}
inline void CommonProperty::clear_has_critical() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void CommonProperty::clear_critical() {
  critical_ = 0;
  clear_has_critical();
}
inline float CommonProperty::critical() const {
  return critical_;
}
inline void CommonProperty::set_critical(float value) {
  set_has_critical();
  critical_ = value;
}

// required float CriticalDamage = 8;
inline bool CommonProperty::has_criticaldamage() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void CommonProperty::set_has_criticaldamage() {
  _has_bits_[0] |= 0x00000080u;
}
inline void CommonProperty::clear_has_criticaldamage() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void CommonProperty::clear_criticaldamage() {
  criticaldamage_ = 0;
  clear_has_criticaldamage();
}
inline float CommonProperty::criticaldamage() const {
  return criticaldamage_;
}
inline void CommonProperty::set_criticaldamage(float value) {
  set_has_criticaldamage();
  criticaldamage_ = value;
}

// required float Toughness = 9;
inline bool CommonProperty::has_toughness() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void CommonProperty::set_has_toughness() {
  _has_bits_[0] |= 0x00000100u;
}
inline void CommonProperty::clear_has_toughness() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void CommonProperty::clear_toughness() {
  toughness_ = 0;
  clear_has_toughness();
}
inline float CommonProperty::toughness() const {
  return toughness_;
}
inline void CommonProperty::set_toughness(float value) {
  set_has_toughness();
  toughness_ = value;
}

// -------------------------------------------------------------------

// BaseProperty

// optional .ServerProto.Logic.CommonProperty PhysicalProperty = 1;
inline bool BaseProperty::has_physicalproperty() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BaseProperty::set_has_physicalproperty() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BaseProperty::clear_has_physicalproperty() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BaseProperty::clear_physicalproperty() {
  if (physicalproperty_ != NULL) physicalproperty_->::ServerProto::Logic::CommonProperty::Clear();
  clear_has_physicalproperty();
}
inline const ::ServerProto::Logic::CommonProperty& BaseProperty::physicalproperty() const {
  return physicalproperty_ != NULL ? *physicalproperty_ : *default_instance_->physicalproperty_;
}
inline ::ServerProto::Logic::CommonProperty* BaseProperty::mutable_physicalproperty() {
  set_has_physicalproperty();
  if (physicalproperty_ == NULL) physicalproperty_ = new ::ServerProto::Logic::CommonProperty;
  return physicalproperty_;
}
inline ::ServerProto::Logic::CommonProperty* BaseProperty::release_physicalproperty() {
  clear_has_physicalproperty();
  ::ServerProto::Logic::CommonProperty* temp = physicalproperty_;
  physicalproperty_ = NULL;
  return temp;
}
inline void BaseProperty::set_allocated_physicalproperty(::ServerProto::Logic::CommonProperty* physicalproperty) {
  delete physicalproperty_;
  physicalproperty_ = physicalproperty;
  if (physicalproperty) {
    set_has_physicalproperty();
  } else {
    clear_has_physicalproperty();
  }
}

// optional .ServerProto.Logic.CommonProperty MagicalProperty = 2;
inline bool BaseProperty::has_magicalproperty() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void BaseProperty::set_has_magicalproperty() {
  _has_bits_[0] |= 0x00000002u;
}
inline void BaseProperty::clear_has_magicalproperty() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void BaseProperty::clear_magicalproperty() {
  if (magicalproperty_ != NULL) magicalproperty_->::ServerProto::Logic::CommonProperty::Clear();
  clear_has_magicalproperty();
}
inline const ::ServerProto::Logic::CommonProperty& BaseProperty::magicalproperty() const {
  return magicalproperty_ != NULL ? *magicalproperty_ : *default_instance_->magicalproperty_;
}
inline ::ServerProto::Logic::CommonProperty* BaseProperty::mutable_magicalproperty() {
  set_has_magicalproperty();
  if (magicalproperty_ == NULL) magicalproperty_ = new ::ServerProto::Logic::CommonProperty;
  return magicalproperty_;
}
inline ::ServerProto::Logic::CommonProperty* BaseProperty::release_magicalproperty() {
  clear_has_magicalproperty();
  ::ServerProto::Logic::CommonProperty* temp = magicalproperty_;
  magicalproperty_ = NULL;
  return temp;
}
inline void BaseProperty::set_allocated_magicalproperty(::ServerProto::Logic::CommonProperty* magicalproperty) {
  delete magicalproperty_;
  magicalproperty_ = magicalproperty;
  if (magicalproperty) {
    set_has_magicalproperty();
  } else {
    clear_has_magicalproperty();
  }
}

// required float CoolingReduction = 3;
inline bool BaseProperty::has_coolingreduction() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void BaseProperty::set_has_coolingreduction() {
  _has_bits_[0] |= 0x00000004u;
}
inline void BaseProperty::clear_has_coolingreduction() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void BaseProperty::clear_coolingreduction() {
  coolingreduction_ = 0;
  clear_has_coolingreduction();
}
inline float BaseProperty::coolingreduction() const {
  return coolingreduction_;
}
inline void BaseProperty::set_coolingreduction(float value) {
  set_has_coolingreduction();
  coolingreduction_ = value;
}

// required float AttackSpeed = 4;
inline bool BaseProperty::has_attackspeed() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void BaseProperty::set_has_attackspeed() {
  _has_bits_[0] |= 0x00000008u;
}
inline void BaseProperty::clear_has_attackspeed() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void BaseProperty::clear_attackspeed() {
  attackspeed_ = 0;
  clear_has_attackspeed();
}
inline float BaseProperty::attackspeed() const {
  return attackspeed_;
}
inline void BaseProperty::set_attackspeed(float value) {
  set_has_attackspeed();
  attackspeed_ = value;
}

// required float MoveSpeed = 5;
inline bool BaseProperty::has_movespeed() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void BaseProperty::set_has_movespeed() {
  _has_bits_[0] |= 0x00000010u;
}
inline void BaseProperty::clear_has_movespeed() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void BaseProperty::clear_movespeed() {
  movespeed_ = 0;
  clear_has_movespeed();
}
inline float BaseProperty::movespeed() const {
  return movespeed_;
}
inline void BaseProperty::set_movespeed(float value) {
  set_has_movespeed();
  movespeed_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Logic
}  // namespace ServerProto

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_BaseProperty_2eproto__INCLUDED