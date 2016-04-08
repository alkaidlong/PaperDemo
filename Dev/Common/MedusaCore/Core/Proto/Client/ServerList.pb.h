// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ServerList.proto

#ifndef PROTOBUF_ServerList_2eproto__INCLUDED
#define PROTOBUF_ServerList_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

namespace Medusa {
namespace CoreProto {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ServerList_2eproto();
void protobuf_AssignDesc_ServerList_2eproto();
void protobuf_ShutdownFile_ServerList_2eproto();

class ServerUsageItem;
class ServerListItem;
class ServerList;

enum ServerUsageType {
  LoginServer = 1,
  GameServer = 2
};
bool ServerUsageType_IsValid(int value);
const ServerUsageType ServerUsageType_MIN = LoginServer;
const ServerUsageType ServerUsageType_MAX = GameServer;
const int ServerUsageType_ARRAYSIZE = ServerUsageType_MAX + 1;

const ::google::protobuf::EnumDescriptor* ServerUsageType_descriptor();
inline const ::std::string& ServerUsageType_Name(ServerUsageType value) {
  return ::google::protobuf::internal::NameOfEnum(
    ServerUsageType_descriptor(), value);
}
inline bool ServerUsageType_Parse(
    const ::std::string& name, ServerUsageType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ServerUsageType>(
    ServerUsageType_descriptor(), name, value);
}
// ===================================================================

class ServerUsageItem : public ::google::protobuf::Message {
 public:
  ServerUsageItem();
  virtual ~ServerUsageItem();

  ServerUsageItem(const ServerUsageItem& from);

  inline ServerUsageItem& operator=(const ServerUsageItem& from) {
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
  static const ServerUsageItem& default_instance();

  void Swap(ServerUsageItem* other);

  // implements Message ----------------------------------------------

  ServerUsageItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ServerUsageItem& from);
  void MergeFrom(const ServerUsageItem& from);
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

  // required .Medusa.CoreProto.ServerUsageType Usage = 1;
  inline bool has_usage() const;
  inline void clear_usage();
  static const int kUsageFieldNumber = 1;
  inline ::Medusa::CoreProto::ServerUsageType usage() const;
  inline void set_usage(::Medusa::CoreProto::ServerUsageType value);

  // required uint32 ServerId = 2;
  inline bool has_serverid() const;
  inline void clear_serverid();
  static const int kServerIdFieldNumber = 2;
  inline ::google::protobuf::uint32 serverid() const;
  inline void set_serverid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:Medusa.CoreProto.ServerUsageItem)
 private:
  inline void set_has_usage();
  inline void clear_has_usage();
  inline void set_has_serverid();
  inline void clear_has_serverid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  int usage_;
  ::google::protobuf::uint32 serverid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_ServerList_2eproto();
  friend void protobuf_AssignDesc_ServerList_2eproto();
  friend void protobuf_ShutdownFile_ServerList_2eproto();

  void InitAsDefaultInstance();
  static ServerUsageItem* default_instance_;
};
// -------------------------------------------------------------------

class ServerListItem : public ::google::protobuf::Message {
 public:
  ServerListItem();
  virtual ~ServerListItem();

  ServerListItem(const ServerListItem& from);

  inline ServerListItem& operator=(const ServerListItem& from) {
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
  static const ServerListItem& default_instance();

  void Swap(ServerListItem* other);

  // implements Message ----------------------------------------------

  ServerListItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ServerListItem& from);
  void MergeFrom(const ServerListItem& from);
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

  // repeated .Medusa.CoreProto.ServerUsageItem ServerUsages = 2;
  inline int serverusages_size() const;
  inline void clear_serverusages();
  static const int kServerUsagesFieldNumber = 2;
  inline const ::Medusa::CoreProto::ServerUsageItem& serverusages(int index) const;
  inline ::Medusa::CoreProto::ServerUsageItem* mutable_serverusages(int index);
  inline ::Medusa::CoreProto::ServerUsageItem* add_serverusages();
  inline const ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::ServerUsageItem >&
      serverusages() const;
  inline ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::ServerUsageItem >*
      mutable_serverusages();

  // @@protoc_insertion_point(class_scope:Medusa.CoreProto.ServerListItem)
 private:
  inline void set_has_id();
  inline void clear_has_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::ServerUsageItem > serverusages_;
  ::google::protobuf::uint32 id_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_ServerList_2eproto();
  friend void protobuf_AssignDesc_ServerList_2eproto();
  friend void protobuf_ShutdownFile_ServerList_2eproto();

  void InitAsDefaultInstance();
  static ServerListItem* default_instance_;
};
// -------------------------------------------------------------------

class ServerList : public ::google::protobuf::Message {
 public:
  ServerList();
  virtual ~ServerList();

  ServerList(const ServerList& from);

  inline ServerList& operator=(const ServerList& from) {
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
  static const ServerList& default_instance();

  void Swap(ServerList* other);

  // implements Message ----------------------------------------------

  ServerList* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ServerList& from);
  void MergeFrom(const ServerList& from);
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

  // repeated .Medusa.CoreProto.ServerListItem Items = 1;
  inline int items_size() const;
  inline void clear_items();
  static const int kItemsFieldNumber = 1;
  inline const ::Medusa::CoreProto::ServerListItem& items(int index) const;
  inline ::Medusa::CoreProto::ServerListItem* mutable_items(int index);
  inline ::Medusa::CoreProto::ServerListItem* add_items();
  inline const ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::ServerListItem >&
      items() const;
  inline ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::ServerListItem >*
      mutable_items();

  // @@protoc_insertion_point(class_scope:Medusa.CoreProto.ServerList)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::ServerListItem > items_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_ServerList_2eproto();
  friend void protobuf_AssignDesc_ServerList_2eproto();
  friend void protobuf_ShutdownFile_ServerList_2eproto();

  void InitAsDefaultInstance();
  static ServerList* default_instance_;
};
// ===================================================================


// ===================================================================

// ServerUsageItem

// required .Medusa.CoreProto.ServerUsageType Usage = 1;
inline bool ServerUsageItem::has_usage() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ServerUsageItem::set_has_usage() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ServerUsageItem::clear_has_usage() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ServerUsageItem::clear_usage() {
  usage_ = 1;
  clear_has_usage();
}
inline ::Medusa::CoreProto::ServerUsageType ServerUsageItem::usage() const {
  return static_cast< ::Medusa::CoreProto::ServerUsageType >(usage_);
}
inline void ServerUsageItem::set_usage(::Medusa::CoreProto::ServerUsageType value) {
  assert(::Medusa::CoreProto::ServerUsageType_IsValid(value));
  set_has_usage();
  usage_ = value;
}

// required uint32 ServerId = 2;
inline bool ServerUsageItem::has_serverid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ServerUsageItem::set_has_serverid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ServerUsageItem::clear_has_serverid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ServerUsageItem::clear_serverid() {
  serverid_ = 0u;
  clear_has_serverid();
}
inline ::google::protobuf::uint32 ServerUsageItem::serverid() const {
  return serverid_;
}
inline void ServerUsageItem::set_serverid(::google::protobuf::uint32 value) {
  set_has_serverid();
  serverid_ = value;
}

// -------------------------------------------------------------------

// ServerListItem

// required uint32 Id = 1;
inline bool ServerListItem::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ServerListItem::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ServerListItem::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ServerListItem::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 ServerListItem::id() const {
  return id_;
}
inline void ServerListItem::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// repeated .Medusa.CoreProto.ServerUsageItem ServerUsages = 2;
inline int ServerListItem::serverusages_size() const {
  return serverusages_.size();
}
inline void ServerListItem::clear_serverusages() {
  serverusages_.Clear();
}
inline const ::Medusa::CoreProto::ServerUsageItem& ServerListItem::serverusages(int index) const {
  return serverusages_.Get(index);
}
inline ::Medusa::CoreProto::ServerUsageItem* ServerListItem::mutable_serverusages(int index) {
  return serverusages_.Mutable(index);
}
inline ::Medusa::CoreProto::ServerUsageItem* ServerListItem::add_serverusages() {
  return serverusages_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::ServerUsageItem >&
ServerListItem::serverusages() const {
  return serverusages_;
}
inline ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::ServerUsageItem >*
ServerListItem::mutable_serverusages() {
  return &serverusages_;
}

// -------------------------------------------------------------------

// ServerList

// repeated .Medusa.CoreProto.ServerListItem Items = 1;
inline int ServerList::items_size() const {
  return items_.size();
}
inline void ServerList::clear_items() {
  items_.Clear();
}
inline const ::Medusa::CoreProto::ServerListItem& ServerList::items(int index) const {
  return items_.Get(index);
}
inline ::Medusa::CoreProto::ServerListItem* ServerList::mutable_items(int index) {
  return items_.Mutable(index);
}
inline ::Medusa::CoreProto::ServerListItem* ServerList::add_items() {
  return items_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::ServerListItem >&
ServerList::items() const {
  return items_;
}
inline ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::ServerListItem >*
ServerList::mutable_items() {
  return &items_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace CoreProto
}  // namespace Medusa

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Medusa::CoreProto::ServerUsageType>() {
  return ::Medusa::CoreProto::ServerUsageType_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ServerList_2eproto__INCLUDED
