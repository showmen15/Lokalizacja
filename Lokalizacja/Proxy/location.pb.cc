// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: location.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "location.pb.h"

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

namespace amber {
namespace location_proto {

namespace {

const ::google::protobuf::Descriptor* Location_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Location_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_location_2eproto() {
  protobuf_AddDesc_location_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "location.proto");
  GOOGLE_CHECK(file != NULL);
  Location_descriptor_ = file->message_type(0);
  static const int Location_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Location, x_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Location, y_),
  };
  Location_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Location_descriptor_,
      Location::default_instance_,
      Location_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Location, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Location, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Location));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_location_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Location_descriptor_, &Location::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_location_2eproto() {
  delete Location::default_instance_;
  delete Location_reflection_;
}

void protobuf_AddDesc_location_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::amber::protobuf_AddDesc_drivermsg_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\016location.proto\022\024amber.location_proto\032\017"
    "drivermsg.proto\" \n\010Location\022\t\n\001x\030\001 \001(\001\022\t"
    "\n\001y\030\002 \001(\001:&\n\014get_location\022\020.amber.Driver"
    "Msg\030\036 \001(\010:I\n\017currentLocation\022\020.amber.Dri"
    "verMsg\030\037 \001(\0132\036.amber.location_proto.Loca"
    "tionB0\n\037pl.edu.agh.amber.location.protoB"
    "\rLocationProto", 254);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "location.proto", &protobuf_RegisterTypes);
  Location::default_instance_ = new Location();
  ::google::protobuf::internal::ExtensionSet::RegisterExtension(
    &::amber::DriverMsg::default_instance(),
    30, 8, false, false);
  ::google::protobuf::internal::ExtensionSet::RegisterMessageExtension(
    &::amber::DriverMsg::default_instance(),
    31, 11, false, false,
    &::amber::location_proto::Location::default_instance());
  Location::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_location_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_location_2eproto {
  StaticDescriptorInitializer_location_2eproto() {
    protobuf_AddDesc_location_2eproto();
  }
} static_descriptor_initializer_location_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Location::kXFieldNumber;
const int Location::kYFieldNumber;
#endif  // !_MSC_VER

Location::Location()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Location::InitAsDefaultInstance() {
}

Location::Location(const Location& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Location::SharedCtor() {
  _cached_size_ = 0;
  x_ = 0;
  y_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Location::~Location() {
  SharedDtor();
}

void Location::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Location::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Location::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Location_descriptor_;
}

const Location& Location::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_location_2eproto();
  return *default_instance_;
}

Location* Location::default_instance_ = NULL;

Location* Location::New() const {
  return new Location;
}

void Location::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    x_ = 0;
    y_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Location::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional double x = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &x_)));
          set_has_x();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(17)) goto parse_y;
        break;
      }

      // optional double y = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_y:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &y_)));
          set_has_y();
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

void Location::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional double x = 1;
  if (has_x()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(1, this->x(), output);
  }

  // optional double y = 2;
  if (has_y()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(2, this->y(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Location::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional double x = 1;
  if (has_x()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(1, this->x(), target);
  }

  // optional double y = 2;
  if (has_y()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(2, this->y(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Location::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional double x = 1;
    if (has_x()) {
      total_size += 1 + 8;
    }

    // optional double y = 2;
    if (has_y()) {
      total_size += 1 + 8;
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

void Location::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Location* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Location*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Location::MergeFrom(const Location& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_x()) {
      set_x(from.x());
    }
    if (from.has_y()) {
      set_y(from.y());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Location::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Location::CopyFrom(const Location& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Location::IsInitialized() const {

  return true;
}

void Location::Swap(Location* other) {
  if (other != this) {
    std::swap(x_, other->x_);
    std::swap(y_, other->y_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Location::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Location_descriptor_;
  metadata.reflection = Location_reflection_;
  return metadata;
}

::google::protobuf::internal::ExtensionIdentifier< ::amber::DriverMsg,
    ::google::protobuf::internal::PrimitiveTypeTraits< bool >, 8, false >
  get_location(kGetLocationFieldNumber, false);
::google::protobuf::internal::ExtensionIdentifier< ::amber::DriverMsg,
    ::google::protobuf::internal::MessageTypeTraits< ::amber::location_proto::Location >, 11, false >
  currentLocation(kCurrentLocationFieldNumber, ::amber::location_proto::Location::default_instance());

// @@protoc_insertion_point(namespace_scope)

}  // namespace location_proto
}  // namespace amber

// @@protoc_insertion_point(global_scope)
