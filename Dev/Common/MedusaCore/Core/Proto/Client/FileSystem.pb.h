// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: FileSystem.proto

#ifndef PROTOBUF_FileSystem_2eproto__INCLUDED
#define PROTOBUF_FileSystem_2eproto__INCLUDED

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
#include "Geometry.pb.h"
// @@protoc_insertion_point(includes)

namespace Medusa {
namespace CoreProto {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_FileSystem_2eproto();
void protobuf_AssignDesc_FileSystem_2eproto();
void protobuf_ShutdownFile_FileSystem_2eproto();

class FileId;
class FileSystemOrderItem;
class FileSystemNameItem;
class FileSystemTagItem;
class FileSystem;

// ===================================================================

class FileId : public ::google::protobuf::Message {
 public:
  FileId();
  virtual ~FileId();

  FileId(const FileId& from);

  inline FileId& operator=(const FileId& from) {
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
  static const FileId& default_instance();

  void Swap(FileId* other);

  // implements Message ----------------------------------------------

  FileId* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const FileId& from);
  void MergeFrom(const FileId& from);
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

  // required string Name = 1;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 1;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // optional uint32 Order = 2;
  inline bool has_order() const;
  inline void clear_order();
  static const int kOrderFieldNumber = 2;
  inline ::google::protobuf::uint32 order() const;
  inline void set_order(::google::protobuf::uint32 value);

  // optional int32 Tag = 3;
  inline bool has_tag() const;
  inline void clear_tag();
  static const int kTagFieldNumber = 3;
  inline ::google::protobuf::int32 tag() const;
  inline void set_tag(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:Medusa.CoreProto.FileId)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_order();
  inline void clear_has_order();
  inline void set_has_tag();
  inline void clear_has_tag();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* name_;
  ::google::protobuf::uint32 order_;
  ::google::protobuf::int32 tag_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_FileSystem_2eproto();
  friend void protobuf_AssignDesc_FileSystem_2eproto();
  friend void protobuf_ShutdownFile_FileSystem_2eproto();

  void InitAsDefaultInstance();
  static FileId* default_instance_;
};
// -------------------------------------------------------------------

class FileSystemOrderItem : public ::google::protobuf::Message {
 public:
  FileSystemOrderItem();
  virtual ~FileSystemOrderItem();

  FileSystemOrderItem(const FileSystemOrderItem& from);

  inline FileSystemOrderItem& operator=(const FileSystemOrderItem& from) {
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
  static const FileSystemOrderItem& default_instance();

  void Swap(FileSystemOrderItem* other);

  // implements Message ----------------------------------------------

  FileSystemOrderItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const FileSystemOrderItem& from);
  void MergeFrom(const FileSystemOrderItem& from);
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

  // required uint32 Order = 1;
  inline bool has_order() const;
  inline void clear_order();
  static const int kOrderFieldNumber = 1;
  inline ::google::protobuf::uint32 order() const;
  inline void set_order(::google::protobuf::uint32 value);

  // optional uint32 FileId = 2;
  inline bool has_fileid() const;
  inline void clear_fileid();
  static const int kFileIdFieldNumber = 2;
  inline ::google::protobuf::uint32 fileid() const;
  inline void set_fileid(::google::protobuf::uint32 value);

  // optional .Medusa.CoreProto.RectU TextureRect = 3;
  inline bool has_texturerect() const;
  inline void clear_texturerect();
  static const int kTextureRectFieldNumber = 3;
  inline const ::Medusa::CoreProto::RectU& texturerect() const;
  inline ::Medusa::CoreProto::RectU* mutable_texturerect();
  inline ::Medusa::CoreProto::RectU* release_texturerect();
  inline void set_allocated_texturerect(::Medusa::CoreProto::RectU* texturerect);

  // optional .Medusa.CoreProto.PointU Offset = 4;
  inline bool has_offset() const;
  inline void clear_offset();
  static const int kOffsetFieldNumber = 4;
  inline const ::Medusa::CoreProto::PointU& offset() const;
  inline ::Medusa::CoreProto::PointU* mutable_offset();
  inline ::Medusa::CoreProto::PointU* release_offset();
  inline void set_allocated_offset(::Medusa::CoreProto::PointU* offset);

  // optional .Medusa.CoreProto.SizeU OriginalSize = 5;
  inline bool has_originalsize() const;
  inline void clear_originalsize();
  static const int kOriginalSizeFieldNumber = 5;
  inline const ::Medusa::CoreProto::SizeU& originalsize() const;
  inline ::Medusa::CoreProto::SizeU* mutable_originalsize();
  inline ::Medusa::CoreProto::SizeU* release_originalsize();
  inline void set_allocated_originalsize(::Medusa::CoreProto::SizeU* originalsize);

  // optional bytes Data = 6;
  inline bool has_data() const;
  inline void clear_data();
  static const int kDataFieldNumber = 6;
  inline const ::std::string& data() const;
  inline void set_data(const ::std::string& value);
  inline void set_data(const char* value);
  inline void set_data(const void* value, size_t size);
  inline ::std::string* mutable_data();
  inline ::std::string* release_data();
  inline void set_allocated_data(::std::string* data);

  // @@protoc_insertion_point(class_scope:Medusa.CoreProto.FileSystemOrderItem)
 private:
  inline void set_has_order();
  inline void clear_has_order();
  inline void set_has_fileid();
  inline void clear_has_fileid();
  inline void set_has_texturerect();
  inline void clear_has_texturerect();
  inline void set_has_offset();
  inline void clear_has_offset();
  inline void set_has_originalsize();
  inline void clear_has_originalsize();
  inline void set_has_data();
  inline void clear_has_data();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 order_;
  ::google::protobuf::uint32 fileid_;
  ::Medusa::CoreProto::RectU* texturerect_;
  ::Medusa::CoreProto::PointU* offset_;
  ::Medusa::CoreProto::SizeU* originalsize_;
  ::std::string* data_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(6 + 31) / 32];

  friend void  protobuf_AddDesc_FileSystem_2eproto();
  friend void protobuf_AssignDesc_FileSystem_2eproto();
  friend void protobuf_ShutdownFile_FileSystem_2eproto();

  void InitAsDefaultInstance();
  static FileSystemOrderItem* default_instance_;
};
// -------------------------------------------------------------------

class FileSystemNameItem : public ::google::protobuf::Message {
 public:
  FileSystemNameItem();
  virtual ~FileSystemNameItem();

  FileSystemNameItem(const FileSystemNameItem& from);

  inline FileSystemNameItem& operator=(const FileSystemNameItem& from) {
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
  static const FileSystemNameItem& default_instance();

  void Swap(FileSystemNameItem* other);

  // implements Message ----------------------------------------------

  FileSystemNameItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const FileSystemNameItem& from);
  void MergeFrom(const FileSystemNameItem& from);
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

  // required string Name = 1;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 1;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // repeated .Medusa.CoreProto.FileSystemOrderItem OrderItems = 2;
  inline int orderitems_size() const;
  inline void clear_orderitems();
  static const int kOrderItemsFieldNumber = 2;
  inline const ::Medusa::CoreProto::FileSystemOrderItem& orderitems(int index) const;
  inline ::Medusa::CoreProto::FileSystemOrderItem* mutable_orderitems(int index);
  inline ::Medusa::CoreProto::FileSystemOrderItem* add_orderitems();
  inline const ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::FileSystemOrderItem >&
      orderitems() const;
  inline ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::FileSystemOrderItem >*
      mutable_orderitems();

  // @@protoc_insertion_point(class_scope:Medusa.CoreProto.FileSystemNameItem)
 private:
  inline void set_has_name();
  inline void clear_has_name();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* name_;
  ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::FileSystemOrderItem > orderitems_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_FileSystem_2eproto();
  friend void protobuf_AssignDesc_FileSystem_2eproto();
  friend void protobuf_ShutdownFile_FileSystem_2eproto();

  void InitAsDefaultInstance();
  static FileSystemNameItem* default_instance_;
};
// -------------------------------------------------------------------

class FileSystemTagItem : public ::google::protobuf::Message {
 public:
  FileSystemTagItem();
  virtual ~FileSystemTagItem();

  FileSystemTagItem(const FileSystemTagItem& from);

  inline FileSystemTagItem& operator=(const FileSystemTagItem& from) {
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
  static const FileSystemTagItem& default_instance();

  void Swap(FileSystemTagItem* other);

  // implements Message ----------------------------------------------

  FileSystemTagItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const FileSystemTagItem& from);
  void MergeFrom(const FileSystemTagItem& from);
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

  // required int32 Tag = 1;
  inline bool has_tag() const;
  inline void clear_tag();
  static const int kTagFieldNumber = 1;
  inline ::google::protobuf::int32 tag() const;
  inline void set_tag(::google::protobuf::int32 value);

  // repeated .Medusa.CoreProto.FileSystemNameItem NameItems = 2;
  inline int nameitems_size() const;
  inline void clear_nameitems();
  static const int kNameItemsFieldNumber = 2;
  inline const ::Medusa::CoreProto::FileSystemNameItem& nameitems(int index) const;
  inline ::Medusa::CoreProto::FileSystemNameItem* mutable_nameitems(int index);
  inline ::Medusa::CoreProto::FileSystemNameItem* add_nameitems();
  inline const ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::FileSystemNameItem >&
      nameitems() const;
  inline ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::FileSystemNameItem >*
      mutable_nameitems();

  // @@protoc_insertion_point(class_scope:Medusa.CoreProto.FileSystemTagItem)
 private:
  inline void set_has_tag();
  inline void clear_has_tag();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::FileSystemNameItem > nameitems_;
  ::google::protobuf::int32 tag_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_FileSystem_2eproto();
  friend void protobuf_AssignDesc_FileSystem_2eproto();
  friend void protobuf_ShutdownFile_FileSystem_2eproto();

  void InitAsDefaultInstance();
  static FileSystemTagItem* default_instance_;
};
// -------------------------------------------------------------------

class FileSystem : public ::google::protobuf::Message {
 public:
  FileSystem();
  virtual ~FileSystem();

  FileSystem(const FileSystem& from);

  inline FileSystem& operator=(const FileSystem& from) {
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
  static const FileSystem& default_instance();

  void Swap(FileSystem* other);

  // implements Message ----------------------------------------------

  FileSystem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const FileSystem& from);
  void MergeFrom(const FileSystem& from);
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

  // repeated .Medusa.CoreProto.FileSystemTagItem TagItems = 1;
  inline int tagitems_size() const;
  inline void clear_tagitems();
  static const int kTagItemsFieldNumber = 1;
  inline const ::Medusa::CoreProto::FileSystemTagItem& tagitems(int index) const;
  inline ::Medusa::CoreProto::FileSystemTagItem* mutable_tagitems(int index);
  inline ::Medusa::CoreProto::FileSystemTagItem* add_tagitems();
  inline const ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::FileSystemTagItem >&
      tagitems() const;
  inline ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::FileSystemTagItem >*
      mutable_tagitems();

  // @@protoc_insertion_point(class_scope:Medusa.CoreProto.FileSystem)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::FileSystemTagItem > tagitems_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_FileSystem_2eproto();
  friend void protobuf_AssignDesc_FileSystem_2eproto();
  friend void protobuf_ShutdownFile_FileSystem_2eproto();

  void InitAsDefaultInstance();
  static FileSystem* default_instance_;
};
// ===================================================================


// ===================================================================

// FileId

// required string Name = 1;
inline bool FileId::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void FileId::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void FileId::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void FileId::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& FileId::name() const {
  return *name_;
}
inline void FileId::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void FileId::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void FileId::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* FileId::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* FileId::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void FileId::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional uint32 Order = 2;
inline bool FileId::has_order() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void FileId::set_has_order() {
  _has_bits_[0] |= 0x00000002u;
}
inline void FileId::clear_has_order() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void FileId::clear_order() {
  order_ = 0u;
  clear_has_order();
}
inline ::google::protobuf::uint32 FileId::order() const {
  return order_;
}
inline void FileId::set_order(::google::protobuf::uint32 value) {
  set_has_order();
  order_ = value;
}

// optional int32 Tag = 3;
inline bool FileId::has_tag() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void FileId::set_has_tag() {
  _has_bits_[0] |= 0x00000004u;
}
inline void FileId::clear_has_tag() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void FileId::clear_tag() {
  tag_ = 0;
  clear_has_tag();
}
inline ::google::protobuf::int32 FileId::tag() const {
  return tag_;
}
inline void FileId::set_tag(::google::protobuf::int32 value) {
  set_has_tag();
  tag_ = value;
}

// -------------------------------------------------------------------

// FileSystemOrderItem

// required uint32 Order = 1;
inline bool FileSystemOrderItem::has_order() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void FileSystemOrderItem::set_has_order() {
  _has_bits_[0] |= 0x00000001u;
}
inline void FileSystemOrderItem::clear_has_order() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void FileSystemOrderItem::clear_order() {
  order_ = 0u;
  clear_has_order();
}
inline ::google::protobuf::uint32 FileSystemOrderItem::order() const {
  return order_;
}
inline void FileSystemOrderItem::set_order(::google::protobuf::uint32 value) {
  set_has_order();
  order_ = value;
}

// optional uint32 FileId = 2;
inline bool FileSystemOrderItem::has_fileid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void FileSystemOrderItem::set_has_fileid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void FileSystemOrderItem::clear_has_fileid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void FileSystemOrderItem::clear_fileid() {
  fileid_ = 0u;
  clear_has_fileid();
}
inline ::google::protobuf::uint32 FileSystemOrderItem::fileid() const {
  return fileid_;
}
inline void FileSystemOrderItem::set_fileid(::google::protobuf::uint32 value) {
  set_has_fileid();
  fileid_ = value;
}

// optional .Medusa.CoreProto.RectU TextureRect = 3;
inline bool FileSystemOrderItem::has_texturerect() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void FileSystemOrderItem::set_has_texturerect() {
  _has_bits_[0] |= 0x00000004u;
}
inline void FileSystemOrderItem::clear_has_texturerect() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void FileSystemOrderItem::clear_texturerect() {
  if (texturerect_ != NULL) texturerect_->::Medusa::CoreProto::RectU::Clear();
  clear_has_texturerect();
}
inline const ::Medusa::CoreProto::RectU& FileSystemOrderItem::texturerect() const {
  return texturerect_ != NULL ? *texturerect_ : *default_instance_->texturerect_;
}
inline ::Medusa::CoreProto::RectU* FileSystemOrderItem::mutable_texturerect() {
  set_has_texturerect();
  if (texturerect_ == NULL) texturerect_ = new ::Medusa::CoreProto::RectU;
  return texturerect_;
}
inline ::Medusa::CoreProto::RectU* FileSystemOrderItem::release_texturerect() {
  clear_has_texturerect();
  ::Medusa::CoreProto::RectU* temp = texturerect_;
  texturerect_ = NULL;
  return temp;
}
inline void FileSystemOrderItem::set_allocated_texturerect(::Medusa::CoreProto::RectU* texturerect) {
  delete texturerect_;
  texturerect_ = texturerect;
  if (texturerect) {
    set_has_texturerect();
  } else {
    clear_has_texturerect();
  }
}

// optional .Medusa.CoreProto.PointU Offset = 4;
inline bool FileSystemOrderItem::has_offset() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void FileSystemOrderItem::set_has_offset() {
  _has_bits_[0] |= 0x00000008u;
}
inline void FileSystemOrderItem::clear_has_offset() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void FileSystemOrderItem::clear_offset() {
  if (offset_ != NULL) offset_->::Medusa::CoreProto::PointU::Clear();
  clear_has_offset();
}
inline const ::Medusa::CoreProto::PointU& FileSystemOrderItem::offset() const {
  return offset_ != NULL ? *offset_ : *default_instance_->offset_;
}
inline ::Medusa::CoreProto::PointU* FileSystemOrderItem::mutable_offset() {
  set_has_offset();
  if (offset_ == NULL) offset_ = new ::Medusa::CoreProto::PointU;
  return offset_;
}
inline ::Medusa::CoreProto::PointU* FileSystemOrderItem::release_offset() {
  clear_has_offset();
  ::Medusa::CoreProto::PointU* temp = offset_;
  offset_ = NULL;
  return temp;
}
inline void FileSystemOrderItem::set_allocated_offset(::Medusa::CoreProto::PointU* offset) {
  delete offset_;
  offset_ = offset;
  if (offset) {
    set_has_offset();
  } else {
    clear_has_offset();
  }
}

// optional .Medusa.CoreProto.SizeU OriginalSize = 5;
inline bool FileSystemOrderItem::has_originalsize() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void FileSystemOrderItem::set_has_originalsize() {
  _has_bits_[0] |= 0x00000010u;
}
inline void FileSystemOrderItem::clear_has_originalsize() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void FileSystemOrderItem::clear_originalsize() {
  if (originalsize_ != NULL) originalsize_->::Medusa::CoreProto::SizeU::Clear();
  clear_has_originalsize();
}
inline const ::Medusa::CoreProto::SizeU& FileSystemOrderItem::originalsize() const {
  return originalsize_ != NULL ? *originalsize_ : *default_instance_->originalsize_;
}
inline ::Medusa::CoreProto::SizeU* FileSystemOrderItem::mutable_originalsize() {
  set_has_originalsize();
  if (originalsize_ == NULL) originalsize_ = new ::Medusa::CoreProto::SizeU;
  return originalsize_;
}
inline ::Medusa::CoreProto::SizeU* FileSystemOrderItem::release_originalsize() {
  clear_has_originalsize();
  ::Medusa::CoreProto::SizeU* temp = originalsize_;
  originalsize_ = NULL;
  return temp;
}
inline void FileSystemOrderItem::set_allocated_originalsize(::Medusa::CoreProto::SizeU* originalsize) {
  delete originalsize_;
  originalsize_ = originalsize;
  if (originalsize) {
    set_has_originalsize();
  } else {
    clear_has_originalsize();
  }
}

// optional bytes Data = 6;
inline bool FileSystemOrderItem::has_data() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void FileSystemOrderItem::set_has_data() {
  _has_bits_[0] |= 0x00000020u;
}
inline void FileSystemOrderItem::clear_has_data() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void FileSystemOrderItem::clear_data() {
  if (data_ != &::google::protobuf::internal::kEmptyString) {
    data_->clear();
  }
  clear_has_data();
}
inline const ::std::string& FileSystemOrderItem::data() const {
  return *data_;
}
inline void FileSystemOrderItem::set_data(const ::std::string& value) {
  set_has_data();
  if (data_ == &::google::protobuf::internal::kEmptyString) {
    data_ = new ::std::string;
  }
  data_->assign(value);
}
inline void FileSystemOrderItem::set_data(const char* value) {
  set_has_data();
  if (data_ == &::google::protobuf::internal::kEmptyString) {
    data_ = new ::std::string;
  }
  data_->assign(value);
}
inline void FileSystemOrderItem::set_data(const void* value, size_t size) {
  set_has_data();
  if (data_ == &::google::protobuf::internal::kEmptyString) {
    data_ = new ::std::string;
  }
  data_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* FileSystemOrderItem::mutable_data() {
  set_has_data();
  if (data_ == &::google::protobuf::internal::kEmptyString) {
    data_ = new ::std::string;
  }
  return data_;
}
inline ::std::string* FileSystemOrderItem::release_data() {
  clear_has_data();
  if (data_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = data_;
    data_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void FileSystemOrderItem::set_allocated_data(::std::string* data) {
  if (data_ != &::google::protobuf::internal::kEmptyString) {
    delete data_;
  }
  if (data) {
    set_has_data();
    data_ = data;
  } else {
    clear_has_data();
    data_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// FileSystemNameItem

// required string Name = 1;
inline bool FileSystemNameItem::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void FileSystemNameItem::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void FileSystemNameItem::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void FileSystemNameItem::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& FileSystemNameItem::name() const {
  return *name_;
}
inline void FileSystemNameItem::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void FileSystemNameItem::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void FileSystemNameItem::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* FileSystemNameItem::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* FileSystemNameItem::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void FileSystemNameItem::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// repeated .Medusa.CoreProto.FileSystemOrderItem OrderItems = 2;
inline int FileSystemNameItem::orderitems_size() const {
  return orderitems_.size();
}
inline void FileSystemNameItem::clear_orderitems() {
  orderitems_.Clear();
}
inline const ::Medusa::CoreProto::FileSystemOrderItem& FileSystemNameItem::orderitems(int index) const {
  return orderitems_.Get(index);
}
inline ::Medusa::CoreProto::FileSystemOrderItem* FileSystemNameItem::mutable_orderitems(int index) {
  return orderitems_.Mutable(index);
}
inline ::Medusa::CoreProto::FileSystemOrderItem* FileSystemNameItem::add_orderitems() {
  return orderitems_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::FileSystemOrderItem >&
FileSystemNameItem::orderitems() const {
  return orderitems_;
}
inline ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::FileSystemOrderItem >*
FileSystemNameItem::mutable_orderitems() {
  return &orderitems_;
}

// -------------------------------------------------------------------

// FileSystemTagItem

// required int32 Tag = 1;
inline bool FileSystemTagItem::has_tag() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void FileSystemTagItem::set_has_tag() {
  _has_bits_[0] |= 0x00000001u;
}
inline void FileSystemTagItem::clear_has_tag() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void FileSystemTagItem::clear_tag() {
  tag_ = 0;
  clear_has_tag();
}
inline ::google::protobuf::int32 FileSystemTagItem::tag() const {
  return tag_;
}
inline void FileSystemTagItem::set_tag(::google::protobuf::int32 value) {
  set_has_tag();
  tag_ = value;
}

// repeated .Medusa.CoreProto.FileSystemNameItem NameItems = 2;
inline int FileSystemTagItem::nameitems_size() const {
  return nameitems_.size();
}
inline void FileSystemTagItem::clear_nameitems() {
  nameitems_.Clear();
}
inline const ::Medusa::CoreProto::FileSystemNameItem& FileSystemTagItem::nameitems(int index) const {
  return nameitems_.Get(index);
}
inline ::Medusa::CoreProto::FileSystemNameItem* FileSystemTagItem::mutable_nameitems(int index) {
  return nameitems_.Mutable(index);
}
inline ::Medusa::CoreProto::FileSystemNameItem* FileSystemTagItem::add_nameitems() {
  return nameitems_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::FileSystemNameItem >&
FileSystemTagItem::nameitems() const {
  return nameitems_;
}
inline ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::FileSystemNameItem >*
FileSystemTagItem::mutable_nameitems() {
  return &nameitems_;
}

// -------------------------------------------------------------------

// FileSystem

// repeated .Medusa.CoreProto.FileSystemTagItem TagItems = 1;
inline int FileSystem::tagitems_size() const {
  return tagitems_.size();
}
inline void FileSystem::clear_tagitems() {
  tagitems_.Clear();
}
inline const ::Medusa::CoreProto::FileSystemTagItem& FileSystem::tagitems(int index) const {
  return tagitems_.Get(index);
}
inline ::Medusa::CoreProto::FileSystemTagItem* FileSystem::mutable_tagitems(int index) {
  return tagitems_.Mutable(index);
}
inline ::Medusa::CoreProto::FileSystemTagItem* FileSystem::add_tagitems() {
  return tagitems_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::FileSystemTagItem >&
FileSystem::tagitems() const {
  return tagitems_;
}
inline ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::FileSystemTagItem >*
FileSystem::mutable_tagitems() {
  return &tagitems_;
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

#endif  // PROTOBUF_FileSystem_2eproto__INCLUDED