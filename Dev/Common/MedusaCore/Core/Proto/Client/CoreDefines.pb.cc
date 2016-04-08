// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CoreDefines.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "CoreDefines.pb.h"

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

namespace Medusa {
namespace CoreProto {

namespace {

const ::google::protobuf::Descriptor* Version_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Version_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_CoreDefines_2eproto() {
  protobuf_AddDesc_CoreDefines_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "CoreDefines.proto");
  GOOGLE_CHECK(file != NULL);
  Version_descriptor_ = file->message_type(0);
  static const int Version_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Version, major_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Version, minor_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Version, build_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Version, revision_),
  };
  Version_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Version_descriptor_,
      Version::default_instance_,
      Version_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Version, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Version, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Version));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_CoreDefines_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Version_descriptor_, &Version::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_CoreDefines_2eproto() {
  delete Version::default_instance_;
  delete Version_reflection_;
}

void protobuf_AddDesc_CoreDefines_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\021CoreDefines.proto\022\020Medusa.CoreProto\"H\n"
    "\007Version\022\r\n\005Major\030\001 \001(\r\022\r\n\005Minor\030\002 \001(\r\022\r"
    "\n\005Build\030\003 \001(\r\022\020\n\010Revision\030\004 \001(\r", 111);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "CoreDefines.proto", &protobuf_RegisterTypes);
  Version::default_instance_ = new Version();
  Version::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_CoreDefines_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_CoreDefines_2eproto {
  StaticDescriptorInitializer_CoreDefines_2eproto() {
    protobuf_AddDesc_CoreDefines_2eproto();
  }
} static_descriptor_initializer_CoreDefines_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Version::kMajorFieldNumber;
const int Version::kMinorFieldNumber;
const int Version::kBuildFieldNumber;
const int Version::kRevisionFieldNumber;
#endif  // !_MSC_VER

Version::Version()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Version::InitAsDefaultInstance() {
}

Version::Version(const Version& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Version::SharedCtor() {
  _cached_size_ = 0;
  major_ = 0u;
  minor_ = 0u;
  build_ = 0u;
  revision_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Version::~Version() {
  SharedDtor();
}

void Version::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Version::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Version::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Version_descriptor_;
}

const Version& Version::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_CoreDefines_2eproto();
  return *default_instance_;
}

Version* Version::default_instance_ = NULL;

Version* Version::New() const {
  return new Version;
}

void Version::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    major_ = 0u;
    minor_ = 0u;
    build_ = 0u;
    revision_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Version::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 Major = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &major_)));
          set_has_major();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_Minor;
        break;
      }

      // optional uint32 Minor = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_Minor:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &minor_)));
          set_has_minor();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_Build;
        break;
      }

      // optional uint32 Build = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_Build:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &build_)));
          set_has_build();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_Revision;
        break;
      }

      // optional uint32 Revision = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_Revision:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &revision_)));
          set_has_revision();
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

void Version::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional uint32 Major = 1;
  if (has_major()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->major(), output);
  }

  // optional uint32 Minor = 2;
  if (has_minor()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->minor(), output);
  }

  // optional uint32 Build = 3;
  if (has_build()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->build(), output);
  }

  // optional uint32 Revision = 4;
  if (has_revision()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->revision(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Version::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional uint32 Major = 1;
  if (has_major()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->major(), target);
  }

  // optional uint32 Minor = 2;
  if (has_minor()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->minor(), target);
  }

  // optional uint32 Build = 3;
  if (has_build()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->build(), target);
  }

  // optional uint32 Revision = 4;
  if (has_revision()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->revision(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Version::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 Major = 1;
    if (has_major()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->major());
    }

    // optional uint32 Minor = 2;
    if (has_minor()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->minor());
    }

    // optional uint32 Build = 3;
    if (has_build()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->build());
    }

    // optional uint32 Revision = 4;
    if (has_revision()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->revision());
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

void Version::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Version* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Version*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Version::MergeFrom(const Version& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_major()) {
      set_major(from.major());
    }
    if (from.has_minor()) {
      set_minor(from.minor());
    }
    if (from.has_build()) {
      set_build(from.build());
    }
    if (from.has_revision()) {
      set_revision(from.revision());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Version::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Version::CopyFrom(const Version& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Version::IsInitialized() const {

  return true;
}

void Version::Swap(Version* other) {
  if (other != this) {
    std::swap(major_, other->major_);
    std::swap(minor_, other->minor_);
    std::swap(build_, other->build_);
    std::swap(revision_, other->revision_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Version::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Version_descriptor_;
  metadata.reflection = Version_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace CoreProto
}  // namespace Medusa

// @@protoc_insertion_point(global_scope)