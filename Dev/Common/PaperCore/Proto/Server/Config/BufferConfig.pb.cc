// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: BufferConfig.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "BufferConfig.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace ServerProto {
namespace Config {

namespace {

const ::google::protobuf::Descriptor* BufferConfigItem_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  BufferConfigItem_reflection_ = NULL;
const ::google::protobuf::Descriptor* BufferConfig_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  BufferConfig_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_BufferConfig_2eproto() {
  protobuf_AddDesc_BufferConfig_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "BufferConfig.proto");
  GOOGLE_CHECK(file != NULL);
  BufferConfigItem_descriptor_ = file->message_type(0);
  static const int BufferConfigItem_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BufferConfigItem, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BufferConfigItem, property_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BufferConfigItem, deltaproperty_),
  };
  BufferConfigItem_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      BufferConfigItem_descriptor_,
      BufferConfigItem::default_instance_,
      BufferConfigItem_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BufferConfigItem, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BufferConfigItem, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(BufferConfigItem));
  BufferConfig_descriptor_ = file->message_type(1);
  static const int BufferConfig_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BufferConfig, bufferconfigitems_),
  };
  BufferConfig_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      BufferConfig_descriptor_,
      BufferConfig::default_instance_,
      BufferConfig_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BufferConfig, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BufferConfig, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(BufferConfig));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_BufferConfig_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    BufferConfigItem_descriptor_, &BufferConfigItem::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    BufferConfig_descriptor_, &BufferConfig::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_BufferConfig_2eproto() {
  delete BufferConfigItem::default_instance_;
  delete BufferConfigItem_reflection_;
  delete BufferConfig::default_instance_;
  delete BufferConfig_reflection_;
}

void protobuf_AddDesc_BufferConfig_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::ServerProto::Logic::protobuf_AddDesc_BaseProperty_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\022BufferConfig.proto\022\022ServerProto.Config"
    "\032\022BaseProperty.proto\"\211\001\n\020BufferConfigIte"
    "m\022\n\n\002Id\030\001 \002(\r\0221\n\010Property\030\002 \002(\0132\037.Server"
    "Proto.Logic.BaseProperty\0226\n\rDeltaPropert"
    "y\030\003 \002(\0132\037.ServerProto.Logic.BaseProperty"
    "\"O\n\014BufferConfig\022\?\n\021BufferConfigItems\030\001 "
    "\003(\0132$.ServerProto.Config.BufferConfigIte"
    "m", 281);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "BufferConfig.proto", &protobuf_RegisterTypes);
  BufferConfigItem::default_instance_ = new BufferConfigItem();
  BufferConfig::default_instance_ = new BufferConfig();
  BufferConfigItem::default_instance_->InitAsDefaultInstance();
  BufferConfig::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_BufferConfig_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_BufferConfig_2eproto {
  StaticDescriptorInitializer_BufferConfig_2eproto() {
    protobuf_AddDesc_BufferConfig_2eproto();
  }
} static_descriptor_initializer_BufferConfig_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int BufferConfigItem::kIdFieldNumber;
const int BufferConfigItem::kPropertyFieldNumber;
const int BufferConfigItem::kDeltaPropertyFieldNumber;
#endif  // !_MSC_VER

BufferConfigItem::BufferConfigItem()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void BufferConfigItem::InitAsDefaultInstance() {
  property_ = const_cast< ::ServerProto::Logic::BaseProperty*>(&::ServerProto::Logic::BaseProperty::default_instance());
  deltaproperty_ = const_cast< ::ServerProto::Logic::BaseProperty*>(&::ServerProto::Logic::BaseProperty::default_instance());
}

BufferConfigItem::BufferConfigItem(const BufferConfigItem& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void BufferConfigItem::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0u;
  property_ = NULL;
  deltaproperty_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

BufferConfigItem::~BufferConfigItem() {
  SharedDtor();
}

void BufferConfigItem::SharedDtor() {
  if (this != default_instance_) {
    delete property_;
    delete deltaproperty_;
  }
}

void BufferConfigItem::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* BufferConfigItem::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return BufferConfigItem_descriptor_;
}

const BufferConfigItem& BufferConfigItem::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_BufferConfig_2eproto();
  return *default_instance_;
}

BufferConfigItem* BufferConfigItem::default_instance_ = NULL;

BufferConfigItem* BufferConfigItem::New() const {
  return new BufferConfigItem;
}

void BufferConfigItem::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    id_ = 0u;
    if (has_property()) {
      if (property_ != NULL) property_->::ServerProto::Logic::BaseProperty::Clear();
    }
    if (has_deltaproperty()) {
      if (deltaproperty_ != NULL) deltaproperty_->::ServerProto::Logic::BaseProperty::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool BufferConfigItem::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 Id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_Property;
        break;
      }

      // required .ServerProto.Logic.BaseProperty Property = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_Property:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_property()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_DeltaProperty;
        break;
      }

      // required .ServerProto.Logic.BaseProperty DeltaProperty = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_DeltaProperty:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_deltaproperty()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void BufferConfigItem::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 Id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->id(), output);
  }

  // required .ServerProto.Logic.BaseProperty Property = 2;
  if (has_property()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->property(), output);
  }

  // required .ServerProto.Logic.BaseProperty DeltaProperty = 3;
  if (has_deltaproperty()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->deltaproperty(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* BufferConfigItem::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 Id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->id(), target);
  }

  // required .ServerProto.Logic.BaseProperty Property = 2;
  if (has_property()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->property(), target);
  }

  // required .ServerProto.Logic.BaseProperty DeltaProperty = 3;
  if (has_deltaproperty()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->deltaproperty(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int BufferConfigItem::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 Id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }

    // required .ServerProto.Logic.BaseProperty Property = 2;
    if (has_property()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->property());
    }

    // required .ServerProto.Logic.BaseProperty DeltaProperty = 3;
    if (has_deltaproperty()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->deltaproperty());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void BufferConfigItem::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const BufferConfigItem* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const BufferConfigItem*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void BufferConfigItem::MergeFrom(const BufferConfigItem& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_property()) {
      mutable_property()->::ServerProto::Logic::BaseProperty::MergeFrom(from.property());
    }
    if (from.has_deltaproperty()) {
      mutable_deltaproperty()->::ServerProto::Logic::BaseProperty::MergeFrom(from.deltaproperty());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void BufferConfigItem::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void BufferConfigItem::CopyFrom(const BufferConfigItem& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool BufferConfigItem::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  if (has_property()) {
    if (!this->property().IsInitialized()) return false;
  }
  if (has_deltaproperty()) {
    if (!this->deltaproperty().IsInitialized()) return false;
  }
  return true;
}

void BufferConfigItem::Swap(BufferConfigItem* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(property_, other->property_);
    std::swap(deltaproperty_, other->deltaproperty_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata BufferConfigItem::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = BufferConfigItem_descriptor_;
  metadata.reflection = BufferConfigItem_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int BufferConfig::kBufferConfigItemsFieldNumber;
#endif  // !_MSC_VER

BufferConfig::BufferConfig()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void BufferConfig::InitAsDefaultInstance() {
}

BufferConfig::BufferConfig(const BufferConfig& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void BufferConfig::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

BufferConfig::~BufferConfig() {
  SharedDtor();
}

void BufferConfig::SharedDtor() {
  if (this != default_instance_) {
  }
}

void BufferConfig::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* BufferConfig::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return BufferConfig_descriptor_;
}

const BufferConfig& BufferConfig::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_BufferConfig_2eproto();
  return *default_instance_;
}

BufferConfig* BufferConfig::default_instance_ = NULL;

BufferConfig* BufferConfig::New() const {
  return new BufferConfig;
}

void BufferConfig::Clear() {
  bufferconfigitems_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool BufferConfig::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .ServerProto.Config.BufferConfigItem BufferConfigItems = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_BufferConfigItems:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_bufferconfigitems()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_BufferConfigItems;
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void BufferConfig::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .ServerProto.Config.BufferConfigItem BufferConfigItems = 1;
  for (int i = 0; i < this->bufferconfigitems_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->bufferconfigitems(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* BufferConfig::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .ServerProto.Config.BufferConfigItem BufferConfigItems = 1;
  for (int i = 0; i < this->bufferconfigitems_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->bufferconfigitems(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int BufferConfig::ByteSize() const {
  int total_size = 0;

  // repeated .ServerProto.Config.BufferConfigItem BufferConfigItems = 1;
  total_size += 1 * this->bufferconfigitems_size();
  for (int i = 0; i < this->bufferconfigitems_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->bufferconfigitems(i));
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void BufferConfig::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const BufferConfig* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const BufferConfig*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void BufferConfig::MergeFrom(const BufferConfig& from) {
  GOOGLE_CHECK_NE(&from, this);
  bufferconfigitems_.MergeFrom(from.bufferconfigitems_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void BufferConfig::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void BufferConfig::CopyFrom(const BufferConfig& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool BufferConfig::IsInitialized() const {

  for (int i = 0; i < bufferconfigitems_size(); i++) {
    if (!this->bufferconfigitems(i).IsInitialized()) return false;
  }
  return true;
}

void BufferConfig::Swap(BufferConfig* other) {
  if (other != this) {
    bufferconfigitems_.Swap(&other->bufferconfigitems_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata BufferConfig::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = BufferConfig_descriptor_;
  metadata.reflection = BufferConfig_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Config
}  // namespace ServerProto

// @@protoc_insertion_point(global_scope)