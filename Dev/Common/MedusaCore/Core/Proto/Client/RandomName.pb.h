// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: RandomName.proto

#ifndef PROTOBUF_RandomName_2eproto__INCLUDED
#define PROTOBUF_RandomName_2eproto__INCLUDED

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

namespace Medusa {
namespace CoreProto {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_RandomName_2eproto();
void protobuf_AssignDesc_RandomName_2eproto();
void protobuf_ShutdownFile_RandomName_2eproto();

class RandomNameConfigItem;
class RandomNameConfig;

// ===================================================================

class RandomNameConfigItem : public ::google::protobuf::Message {
 public:
  RandomNameConfigItem();
  virtual ~RandomNameConfigItem();

  RandomNameConfigItem(const RandomNameConfigItem& from);

  inline RandomNameConfigItem& operator=(const RandomNameConfigItem& from) {
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
  static const RandomNameConfigItem& default_instance();

  void Swap(RandomNameConfigItem* other);

  // implements Message ----------------------------------------------

  RandomNameConfigItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RandomNameConfigItem& from);
  void MergeFrom(const RandomNameConfigItem& from);
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

  // required uint32 Position = 1;
  inline bool has_position() const;
  inline void clear_position();
  static const int kPositionFieldNumber = 1;
  inline ::google::protobuf::uint32 position() const;
  inline void set_position(::google::protobuf::uint32 value);

  // required string Value = 2;
  inline bool has_value() const;
  inline void clear_value();
  static const int kValueFieldNumber = 2;
  inline const ::std::string& value() const;
  inline void set_value(const ::std::string& value);
  inline void set_value(const char* value);
  inline void set_value(const char* value, size_t size);
  inline ::std::string* mutable_value();
  inline ::std::string* release_value();
  inline void set_allocated_value(::std::string* value);

  // @@protoc_insertion_point(class_scope:Medusa.CoreProto.RandomNameConfigItem)
 private:
  inline void set_has_position();
  inline void clear_has_position();
  inline void set_has_value();
  inline void clear_has_value();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* value_;
  ::google::protobuf::uint32 position_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_RandomName_2eproto();
  friend void protobuf_AssignDesc_RandomName_2eproto();
  friend void protobuf_ShutdownFile_RandomName_2eproto();

  void InitAsDefaultInstance();
  static RandomNameConfigItem* default_instance_;
};
// -------------------------------------------------------------------

class RandomNameConfig : public ::google::protobuf::Message {
 public:
  RandomNameConfig();
  virtual ~RandomNameConfig();

  RandomNameConfig(const RandomNameConfig& from);

  inline RandomNameConfig& operator=(const RandomNameConfig& from) {
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
  static const RandomNameConfig& default_instance();

  void Swap(RandomNameConfig* other);

  // implements Message ----------------------------------------------

  RandomNameConfig* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RandomNameConfig& from);
  void MergeFrom(const RandomNameConfig& from);
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

  // repeated .Medusa.CoreProto.RandomNameConfigItem Items = 1;
  inline int items_size() const;
  inline void clear_items();
  static const int kItemsFieldNumber = 1;
  inline const ::Medusa::CoreProto::RandomNameConfigItem& items(int index) const;
  inline ::Medusa::CoreProto::RandomNameConfigItem* mutable_items(int index);
  inline ::Medusa::CoreProto::RandomNameConfigItem* add_items();
  inline const ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::RandomNameConfigItem >&
      items() const;
  inline ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::RandomNameConfigItem >*
      mutable_items();

  // @@protoc_insertion_point(class_scope:Medusa.CoreProto.RandomNameConfig)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::RandomNameConfigItem > items_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_RandomName_2eproto();
  friend void protobuf_AssignDesc_RandomName_2eproto();
  friend void protobuf_ShutdownFile_RandomName_2eproto();

  void InitAsDefaultInstance();
  static RandomNameConfig* default_instance_;
};
// ===================================================================


// ===================================================================

// RandomNameConfigItem

// required uint32 Position = 1;
inline bool RandomNameConfigItem::has_position() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RandomNameConfigItem::set_has_position() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RandomNameConfigItem::clear_has_position() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RandomNameConfigItem::clear_position() {
  position_ = 0u;
  clear_has_position();
}
inline ::google::protobuf::uint32 RandomNameConfigItem::position() const {
  return position_;
}
inline void RandomNameConfigItem::set_position(::google::protobuf::uint32 value) {
  set_has_position();
  position_ = value;
}

// required string Value = 2;
inline bool RandomNameConfigItem::has_value() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RandomNameConfigItem::set_has_value() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RandomNameConfigItem::clear_has_value() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RandomNameConfigItem::clear_value() {
  if (value_ != &::google::protobuf::internal::kEmptyString) {
    value_->clear();
  }
  clear_has_value();
}
inline const ::std::string& RandomNameConfigItem::value() const {
  return *value_;
}
inline void RandomNameConfigItem::set_value(const ::std::string& value) {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  value_->assign(value);
}
inline void RandomNameConfigItem::set_value(const char* value) {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  value_->assign(value);
}
inline void RandomNameConfigItem::set_value(const char* value, size_t size) {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  value_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* RandomNameConfigItem::mutable_value() {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  return value_;
}
inline ::std::string* RandomNameConfigItem::release_value() {
  clear_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = value_;
    value_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void RandomNameConfigItem::set_allocated_value(::std::string* value) {
  if (value_ != &::google::protobuf::internal::kEmptyString) {
    delete value_;
  }
  if (value) {
    set_has_value();
    value_ = value;
  } else {
    clear_has_value();
    value_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// RandomNameConfig

// repeated .Medusa.CoreProto.RandomNameConfigItem Items = 1;
inline int RandomNameConfig::items_size() const {
  return items_.size();
}
inline void RandomNameConfig::clear_items() {
  items_.Clear();
}
inline const ::Medusa::CoreProto::RandomNameConfigItem& RandomNameConfig::items(int index) const {
  return items_.Get(index);
}
inline ::Medusa::CoreProto::RandomNameConfigItem* RandomNameConfig::mutable_items(int index) {
  return items_.Mutable(index);
}
inline ::Medusa::CoreProto::RandomNameConfigItem* RandomNameConfig::add_items() {
  return items_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::RandomNameConfigItem >&
RandomNameConfig::items() const {
  return items_;
}
inline ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::RandomNameConfigItem >*
RandomNameConfig::mutable_items() {
  return &items_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace CoreProto
}  // namespace Medusa

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_RandomName_2eproto__INCLUDED
