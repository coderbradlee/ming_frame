// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: echo.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "echo.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace echo {

namespace {

const ::google::protobuf::Descriptor* EchoRequest_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  EchoRequest_reflection_ = NULL;
const ::google::protobuf::Descriptor* EchoResponse_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  EchoResponse_reflection_ = NULL;
const ::google::protobuf::ServiceDescriptor* EchoService_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_echo_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_echo_2eproto() {
  protobuf_AddDesc_echo_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "echo.proto");
  GOOGLE_CHECK(file != NULL);
  EchoRequest_descriptor_ = file->message_type(0);
  static const int EchoRequest_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(EchoRequest, payload_),
  };
  EchoRequest_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      EchoRequest_descriptor_,
      EchoRequest::default_instance_,
      EchoRequest_offsets_,
      -1,
      -1,
      -1,
      sizeof(EchoRequest),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(EchoRequest, _internal_metadata_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(EchoRequest, _is_default_instance_));
  EchoResponse_descriptor_ = file->message_type(1);
  static const int EchoResponse_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(EchoResponse, payload_),
  };
  EchoResponse_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      EchoResponse_descriptor_,
      EchoResponse::default_instance_,
      EchoResponse_offsets_,
      -1,
      -1,
      -1,
      sizeof(EchoResponse),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(EchoResponse, _internal_metadata_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(EchoResponse, _is_default_instance_));
  EchoService_descriptor_ = file->service(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_echo_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      EchoRequest_descriptor_, &EchoRequest::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      EchoResponse_descriptor_, &EchoResponse::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_echo_2eproto() {
  delete EchoRequest::default_instance_;
  delete EchoRequest_reflection_;
  delete EchoResponse::default_instance_;
  delete EchoResponse_reflection_;
}

void protobuf_AddDesc_echo_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AddDesc_echo_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\necho.proto\022\004echo\"\036\n\013EchoRequest\022\017\n\007pay"
    "load\030\001 \001(\t\"\037\n\014EchoResponse\022\017\n\007payload\030\002 "
    "\001(\t2<\n\013EchoService\022-\n\004Echo\022\021.echo.EchoRe"
    "quest\032\022.echo.EchoResponseB\027\n\004echoB\tEchoP"
    "roto\200\001\001\210\001\001b\006proto3", 178);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "echo.proto", &protobuf_RegisterTypes);
  EchoRequest::default_instance_ = new EchoRequest();
  EchoResponse::default_instance_ = new EchoResponse();
  EchoRequest::default_instance_->InitAsDefaultInstance();
  EchoResponse::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_echo_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_echo_2eproto {
  StaticDescriptorInitializer_echo_2eproto() {
    protobuf_AddDesc_echo_2eproto();
  }
} static_descriptor_initializer_echo_2eproto_;

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int EchoRequest::kPayloadFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

EchoRequest::EchoRequest()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:echo.EchoRequest)
}

void EchoRequest::InitAsDefaultInstance() {
  _is_default_instance_ = true;
}

EchoRequest::EchoRequest(const EchoRequest& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:echo.EchoRequest)
}

void EchoRequest::SharedCtor() {
    _is_default_instance_ = false;
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  payload_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

EchoRequest::~EchoRequest() {
  // @@protoc_insertion_point(destructor:echo.EchoRequest)
  SharedDtor();
}

void EchoRequest::SharedDtor() {
  payload_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void EchoRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* EchoRequest::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return EchoRequest_descriptor_;
}

const EchoRequest& EchoRequest::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_echo_2eproto();
  return *default_instance_;
}

EchoRequest* EchoRequest::default_instance_ = NULL;

EchoRequest* EchoRequest::New(::google::protobuf::Arena* arena) const {
  EchoRequest* n = new EchoRequest;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void EchoRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:echo.EchoRequest)
  payload_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

bool EchoRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:echo.EchoRequest)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string payload = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_payload()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->payload().data(), this->payload().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "echo.EchoRequest.payload"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:echo.EchoRequest)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:echo.EchoRequest)
  return false;
#undef DO_
}

void EchoRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:echo.EchoRequest)
  // optional string payload = 1;
  if (this->payload().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->payload().data(), this->payload().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "echo.EchoRequest.payload");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->payload(), output);
  }

  // @@protoc_insertion_point(serialize_end:echo.EchoRequest)
}

::google::protobuf::uint8* EchoRequest::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:echo.EchoRequest)
  // optional string payload = 1;
  if (this->payload().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->payload().data(), this->payload().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "echo.EchoRequest.payload");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->payload(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:echo.EchoRequest)
  return target;
}

int EchoRequest::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:echo.EchoRequest)
  int total_size = 0;

  // optional string payload = 1;
  if (this->payload().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->payload());
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void EchoRequest::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:echo.EchoRequest)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const EchoRequest* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const EchoRequest>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:echo.EchoRequest)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:echo.EchoRequest)
    MergeFrom(*source);
  }
}

void EchoRequest::MergeFrom(const EchoRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:echo.EchoRequest)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  if (from.payload().size() > 0) {

    payload_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.payload_);
  }
}

void EchoRequest::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:echo.EchoRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void EchoRequest::CopyFrom(const EchoRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:echo.EchoRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool EchoRequest::IsInitialized() const {

  return true;
}

void EchoRequest::Swap(EchoRequest* other) {
  if (other == this) return;
  InternalSwap(other);
}
void EchoRequest::InternalSwap(EchoRequest* other) {
  payload_.Swap(&other->payload_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata EchoRequest::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = EchoRequest_descriptor_;
  metadata.reflection = EchoRequest_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// EchoRequest

// optional string payload = 1;
void EchoRequest::clear_payload() {
  payload_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 const ::std::string& EchoRequest::payload() const {
  // @@protoc_insertion_point(field_get:echo.EchoRequest.payload)
  return payload_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void EchoRequest::set_payload(const ::std::string& value) {
  
  payload_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:echo.EchoRequest.payload)
}
 void EchoRequest::set_payload(const char* value) {
  
  payload_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:echo.EchoRequest.payload)
}
 void EchoRequest::set_payload(const char* value, size_t size) {
  
  payload_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:echo.EchoRequest.payload)
}
 ::std::string* EchoRequest::mutable_payload() {
  
  // @@protoc_insertion_point(field_mutable:echo.EchoRequest.payload)
  return payload_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* EchoRequest::release_payload() {
  // @@protoc_insertion_point(field_release:echo.EchoRequest.payload)
  
  return payload_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void EchoRequest::set_allocated_payload(::std::string* payload) {
  if (payload != NULL) {
    
  } else {
    
  }
  payload_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), payload);
  // @@protoc_insertion_point(field_set_allocated:echo.EchoRequest.payload)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int EchoResponse::kPayloadFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

EchoResponse::EchoResponse()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:echo.EchoResponse)
}

void EchoResponse::InitAsDefaultInstance() {
  _is_default_instance_ = true;
}

EchoResponse::EchoResponse(const EchoResponse& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:echo.EchoResponse)
}

void EchoResponse::SharedCtor() {
    _is_default_instance_ = false;
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  payload_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

EchoResponse::~EchoResponse() {
  // @@protoc_insertion_point(destructor:echo.EchoResponse)
  SharedDtor();
}

void EchoResponse::SharedDtor() {
  payload_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void EchoResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* EchoResponse::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return EchoResponse_descriptor_;
}

const EchoResponse& EchoResponse::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_echo_2eproto();
  return *default_instance_;
}

EchoResponse* EchoResponse::default_instance_ = NULL;

EchoResponse* EchoResponse::New(::google::protobuf::Arena* arena) const {
  EchoResponse* n = new EchoResponse;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void EchoResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:echo.EchoResponse)
  payload_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

bool EchoResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:echo.EchoResponse)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string payload = 2;
      case 2: {
        if (tag == 18) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_payload()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->payload().data(), this->payload().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "echo.EchoResponse.payload"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:echo.EchoResponse)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:echo.EchoResponse)
  return false;
#undef DO_
}

void EchoResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:echo.EchoResponse)
  // optional string payload = 2;
  if (this->payload().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->payload().data(), this->payload().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "echo.EchoResponse.payload");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->payload(), output);
  }

  // @@protoc_insertion_point(serialize_end:echo.EchoResponse)
}

::google::protobuf::uint8* EchoResponse::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:echo.EchoResponse)
  // optional string payload = 2;
  if (this->payload().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->payload().data(), this->payload().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "echo.EchoResponse.payload");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->payload(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:echo.EchoResponse)
  return target;
}

int EchoResponse::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:echo.EchoResponse)
  int total_size = 0;

  // optional string payload = 2;
  if (this->payload().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->payload());
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void EchoResponse::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:echo.EchoResponse)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const EchoResponse* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const EchoResponse>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:echo.EchoResponse)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:echo.EchoResponse)
    MergeFrom(*source);
  }
}

void EchoResponse::MergeFrom(const EchoResponse& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:echo.EchoResponse)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  if (from.payload().size() > 0) {

    payload_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.payload_);
  }
}

void EchoResponse::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:echo.EchoResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void EchoResponse::CopyFrom(const EchoResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:echo.EchoResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool EchoResponse::IsInitialized() const {

  return true;
}

void EchoResponse::Swap(EchoResponse* other) {
  if (other == this) return;
  InternalSwap(other);
}
void EchoResponse::InternalSwap(EchoResponse* other) {
  payload_.Swap(&other->payload_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata EchoResponse::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = EchoResponse_descriptor_;
  metadata.reflection = EchoResponse_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// EchoResponse

// optional string payload = 2;
void EchoResponse::clear_payload() {
  payload_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 const ::std::string& EchoResponse::payload() const {
  // @@protoc_insertion_point(field_get:echo.EchoResponse.payload)
  return payload_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void EchoResponse::set_payload(const ::std::string& value) {
  
  payload_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:echo.EchoResponse.payload)
}
 void EchoResponse::set_payload(const char* value) {
  
  payload_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:echo.EchoResponse.payload)
}
 void EchoResponse::set_payload(const char* value, size_t size) {
  
  payload_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:echo.EchoResponse.payload)
}
 ::std::string* EchoResponse::mutable_payload() {
  
  // @@protoc_insertion_point(field_mutable:echo.EchoResponse.payload)
  return payload_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* EchoResponse::release_payload() {
  // @@protoc_insertion_point(field_release:echo.EchoResponse.payload)
  
  return payload_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void EchoResponse::set_allocated_payload(::std::string* payload) {
  if (payload != NULL) {
    
  } else {
    
  }
  payload_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), payload);
  // @@protoc_insertion_point(field_set_allocated:echo.EchoResponse.payload)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

EchoService::~EchoService() {}

const ::google::protobuf::ServiceDescriptor* EchoService::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return EchoService_descriptor_;
}

const ::google::protobuf::ServiceDescriptor* EchoService::GetDescriptor() {
  protobuf_AssignDescriptorsOnce();
  return EchoService_descriptor_;
}

void EchoService::Echo(::google::protobuf::RpcController* controller,
                         const ::echo::EchoRequest*,
                         ::echo::EchoResponse*,
                         ::google::protobuf::Closure* done) {
  controller->SetFailed("Method Echo() not implemented.");
  done->Run();
}

void EchoService::CallMethod(const ::google::protobuf::MethodDescriptor* method,
                             ::google::protobuf::RpcController* controller,
                             const ::google::protobuf::Message* request,
                             ::google::protobuf::Message* response,
                             ::google::protobuf::Closure* done) {
  GOOGLE_DCHECK_EQ(method->service(), EchoService_descriptor_);
  switch(method->index()) {
    case 0:
      Echo(controller,
             ::google::protobuf::down_cast<const ::echo::EchoRequest*>(request),
             ::google::protobuf::down_cast< ::echo::EchoResponse*>(response),
             done);
      break;
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      break;
  }
}

const ::google::protobuf::Message& EchoService::GetRequestPrototype(
    const ::google::protobuf::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::echo::EchoRequest::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *::google::protobuf::MessageFactory::generated_factory()
          ->GetPrototype(method->input_type());
  }
}

const ::google::protobuf::Message& EchoService::GetResponsePrototype(
    const ::google::protobuf::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::echo::EchoResponse::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *::google::protobuf::MessageFactory::generated_factory()
          ->GetPrototype(method->output_type());
  }
}

EchoService_Stub::EchoService_Stub(::google::protobuf::RpcChannel* channel)
  : channel_(channel), owns_channel_(false) {}
EchoService_Stub::EchoService_Stub(
    ::google::protobuf::RpcChannel* channel,
    ::google::protobuf::Service::ChannelOwnership ownership)
  : channel_(channel),
    owns_channel_(ownership == ::google::protobuf::Service::STUB_OWNS_CHANNEL) {}
EchoService_Stub::~EchoService_Stub() {
  if (owns_channel_) delete channel_;
}

void EchoService_Stub::Echo(::google::protobuf::RpcController* controller,
                              const ::echo::EchoRequest* request,
                              ::echo::EchoResponse* response,
                              ::google::protobuf::Closure* done) {
  channel_->CallMethod(descriptor()->method(0),
                       controller, request, response, done);
}

// @@protoc_insertion_point(namespace_scope)

}  // namespace echo

// @@protoc_insertion_point(global_scope)
