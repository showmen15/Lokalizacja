// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: roboclaw.proto

#ifndef PROTOBUF_roboclaw_2eproto__INCLUDED
#define PROTOBUF_roboclaw_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
#include "drivermsg.pb.h"
// @@protoc_insertion_point(includes)

namespace amber {
namespace roboclaw_proto {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_roboclaw_2eproto();
void protobuf_AssignDesc_roboclaw_2eproto();
void protobuf_ShutdownFile_roboclaw_2eproto();

class MotorsSpeed;

// ===================================================================

class MotorsSpeed : public ::google::protobuf::Message {
 public:
  MotorsSpeed();
  virtual ~MotorsSpeed();

  MotorsSpeed(const MotorsSpeed& from);

  inline MotorsSpeed& operator=(const MotorsSpeed& from) {
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
  static const MotorsSpeed& default_instance();

  void Swap(MotorsSpeed* other);

  // implements Message ----------------------------------------------

  MotorsSpeed* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MotorsSpeed& from);
  void MergeFrom(const MotorsSpeed& from);
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

  // optional int32 frontLeftSpeed = 1;
  inline bool has_frontleftspeed() const;
  inline void clear_frontleftspeed();
  static const int kFrontLeftSpeedFieldNumber = 1;
  inline ::google::protobuf::int32 frontleftspeed() const;
  inline void set_frontleftspeed(::google::protobuf::int32 value);

  // optional int32 frontRightSpeed = 2;
  inline bool has_frontrightspeed() const;
  inline void clear_frontrightspeed();
  static const int kFrontRightSpeedFieldNumber = 2;
  inline ::google::protobuf::int32 frontrightspeed() const;
  inline void set_frontrightspeed(::google::protobuf::int32 value);

  // optional int32 rearLeftSpeed = 3;
  inline bool has_rearleftspeed() const;
  inline void clear_rearleftspeed();
  static const int kRearLeftSpeedFieldNumber = 3;
  inline ::google::protobuf::int32 rearleftspeed() const;
  inline void set_rearleftspeed(::google::protobuf::int32 value);

  // optional int32 rearRightSpeed = 4;
  inline bool has_rearrightspeed() const;
  inline void clear_rearrightspeed();
  static const int kRearRightSpeedFieldNumber = 4;
  inline ::google::protobuf::int32 rearrightspeed() const;
  inline void set_rearrightspeed(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:amber.roboclaw_proto.MotorsSpeed)
 private:
  inline void set_has_frontleftspeed();
  inline void clear_has_frontleftspeed();
  inline void set_has_frontrightspeed();
  inline void clear_has_frontrightspeed();
  inline void set_has_rearleftspeed();
  inline void clear_has_rearleftspeed();
  inline void set_has_rearrightspeed();
  inline void clear_has_rearrightspeed();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 frontleftspeed_;
  ::google::protobuf::int32 frontrightspeed_;
  ::google::protobuf::int32 rearleftspeed_;
  ::google::protobuf::int32 rearrightspeed_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];

  friend void  protobuf_AddDesc_roboclaw_2eproto();
  friend void protobuf_AssignDesc_roboclaw_2eproto();
  friend void protobuf_ShutdownFile_roboclaw_2eproto();

  void InitAsDefaultInstance();
  static MotorsSpeed* default_instance_;
};
// ===================================================================

static const int kMotorsCommandFieldNumber = 20;
extern ::google::protobuf::internal::ExtensionIdentifier< ::amber::DriverMsg,
    ::google::protobuf::internal::MessageTypeTraits< ::amber::roboclaw_proto::MotorsSpeed >, 11, false >
  motorsCommand;
static const int kCurrentSpeedRequestFieldNumber = 21;
extern ::google::protobuf::internal::ExtensionIdentifier< ::amber::DriverMsg,
    ::google::protobuf::internal::PrimitiveTypeTraits< bool >, 8, false >
  currentSpeedRequest;
static const int kCurrentSpeedFieldNumber = 22;
extern ::google::protobuf::internal::ExtensionIdentifier< ::amber::DriverMsg,
    ::google::protobuf::internal::MessageTypeTraits< ::amber::roboclaw_proto::MotorsSpeed >, 11, false >
  currentSpeed;

// ===================================================================

// MotorsSpeed

// optional int32 frontLeftSpeed = 1;
inline bool MotorsSpeed::has_frontleftspeed() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MotorsSpeed::set_has_frontleftspeed() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MotorsSpeed::clear_has_frontleftspeed() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MotorsSpeed::clear_frontleftspeed() {
  frontleftspeed_ = 0;
  clear_has_frontleftspeed();
}
inline ::google::protobuf::int32 MotorsSpeed::frontleftspeed() const {
  return frontleftspeed_;
}
inline void MotorsSpeed::set_frontleftspeed(::google::protobuf::int32 value) {
  set_has_frontleftspeed();
  frontleftspeed_ = value;
}

// optional int32 frontRightSpeed = 2;
inline bool MotorsSpeed::has_frontrightspeed() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MotorsSpeed::set_has_frontrightspeed() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MotorsSpeed::clear_has_frontrightspeed() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MotorsSpeed::clear_frontrightspeed() {
  frontrightspeed_ = 0;
  clear_has_frontrightspeed();
}
inline ::google::protobuf::int32 MotorsSpeed::frontrightspeed() const {
  return frontrightspeed_;
}
inline void MotorsSpeed::set_frontrightspeed(::google::protobuf::int32 value) {
  set_has_frontrightspeed();
  frontrightspeed_ = value;
}

// optional int32 rearLeftSpeed = 3;
inline bool MotorsSpeed::has_rearleftspeed() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MotorsSpeed::set_has_rearleftspeed() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MotorsSpeed::clear_has_rearleftspeed() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MotorsSpeed::clear_rearleftspeed() {
  rearleftspeed_ = 0;
  clear_has_rearleftspeed();
}
inline ::google::protobuf::int32 MotorsSpeed::rearleftspeed() const {
  return rearleftspeed_;
}
inline void MotorsSpeed::set_rearleftspeed(::google::protobuf::int32 value) {
  set_has_rearleftspeed();
  rearleftspeed_ = value;
}

// optional int32 rearRightSpeed = 4;
inline bool MotorsSpeed::has_rearrightspeed() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void MotorsSpeed::set_has_rearrightspeed() {
  _has_bits_[0] |= 0x00000008u;
}
inline void MotorsSpeed::clear_has_rearrightspeed() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void MotorsSpeed::clear_rearrightspeed() {
  rearrightspeed_ = 0;
  clear_has_rearrightspeed();
}
inline ::google::protobuf::int32 MotorsSpeed::rearrightspeed() const {
  return rearrightspeed_;
}
inline void MotorsSpeed::set_rearrightspeed(::google::protobuf::int32 value) {
  set_has_rearrightspeed();
  rearrightspeed_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace roboclaw_proto
}  // namespace amber

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_roboclaw_2eproto__INCLUDED
