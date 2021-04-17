// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: FailControlMessage.proto

#include "FailControlMessage.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)

class FailControlMessageDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<FailControlMessage>
      _instance;
} _FailControlMessage_default_instance_;
namespace protobuf_FailControlMessage_2eproto {
static void InitDefaultsFailControlMessage() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_FailControlMessage_default_instance_;
    new (ptr) ::FailControlMessage();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::FailControlMessage::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_FailControlMessage =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsFailControlMessage}, {}};

void InitDefaults() {
  ::google::protobuf::internal::InitSCC(&scc_info_FailControlMessage.base);
}

::google::protobuf::Metadata file_level_metadata[1];
const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[1];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::FailControlMessage, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::FailControlMessage, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::FailControlMessage, command_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::FailControlMessage, workloadid_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::FailControlMessage, build_id_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::FailControlMessage, run_id_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::FailControlMessage, job_size_),
  1,
  ~0u,
  0,
  3,
  2,
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 10, sizeof(::FailControlMessage)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::_FailControlMessage_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  AssignDescriptors(
      "FailControlMessage.proto", schemas, file_default_instances, TableStruct::offsets,
      file_level_metadata, file_level_enum_descriptors, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\030FailControlMessage.proto\"\343\001\n\022FailContr"
      "olMessage\022,\n\007command\030\001 \002(\0162\033.FailControl"
      "Message.Command\022\022\n\nworkloadID\030\002 \003(\r\022\020\n\010b"
      "uild_id\030\003 \002(\004\022\016\n\006run_id\030\004 \001(\004\022\020\n\010job_siz"
      "e\030\005 \001(\r\"W\n\007Command\022\r\n\tNEED_WORK\020\000\022\022\n\016RES"
      "ULT_FOLLOWS\020\001\022\020\n\014WORK_FOLLOWS\020\006\022\016\n\nCOME_"
      "AGAIN\020\007\022\007\n\003DIE\020\010"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 256);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "FailControlMessage.proto", &protobuf_RegisterTypes);
}

void AddDescriptors() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_FailControlMessage_2eproto
const ::google::protobuf::EnumDescriptor* FailControlMessage_Command_descriptor() {
  protobuf_FailControlMessage_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_FailControlMessage_2eproto::file_level_enum_descriptors[0];
}
bool FailControlMessage_Command_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 6:
    case 7:
    case 8:
      return true;
    default:
      return false;
  }
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const FailControlMessage_Command FailControlMessage::NEED_WORK;
const FailControlMessage_Command FailControlMessage::RESULT_FOLLOWS;
const FailControlMessage_Command FailControlMessage::WORK_FOLLOWS;
const FailControlMessage_Command FailControlMessage::COME_AGAIN;
const FailControlMessage_Command FailControlMessage::DIE;
const FailControlMessage_Command FailControlMessage::Command_MIN;
const FailControlMessage_Command FailControlMessage::Command_MAX;
const int FailControlMessage::Command_ARRAYSIZE;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

// ===================================================================

void FailControlMessage::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int FailControlMessage::kCommandFieldNumber;
const int FailControlMessage::kWorkloadIDFieldNumber;
const int FailControlMessage::kBuildIdFieldNumber;
const int FailControlMessage::kRunIdFieldNumber;
const int FailControlMessage::kJobSizeFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

FailControlMessage::FailControlMessage()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_FailControlMessage_2eproto::scc_info_FailControlMessage.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:FailControlMessage)
}
FailControlMessage::FailControlMessage(const FailControlMessage& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      workloadid_(from.workloadid_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&build_id_, &from.build_id_,
    static_cast<size_t>(reinterpret_cast<char*>(&run_id_) -
    reinterpret_cast<char*>(&build_id_)) + sizeof(run_id_));
  // @@protoc_insertion_point(copy_constructor:FailControlMessage)
}

void FailControlMessage::SharedCtor() {
  ::memset(&build_id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&run_id_) -
      reinterpret_cast<char*>(&build_id_)) + sizeof(run_id_));
}

FailControlMessage::~FailControlMessage() {
  // @@protoc_insertion_point(destructor:FailControlMessage)
  SharedDtor();
}

void FailControlMessage::SharedDtor() {
}

void FailControlMessage::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* FailControlMessage::descriptor() {
  ::protobuf_FailControlMessage_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_FailControlMessage_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const FailControlMessage& FailControlMessage::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_FailControlMessage_2eproto::scc_info_FailControlMessage.base);
  return *internal_default_instance();
}


void FailControlMessage::Clear() {
// @@protoc_insertion_point(message_clear_start:FailControlMessage)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  workloadid_.Clear();
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 15u) {
    ::memset(&build_id_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&run_id_) -
        reinterpret_cast<char*>(&build_id_)) + sizeof(run_id_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool FailControlMessage::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:FailControlMessage)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .FailControlMessage.Command command = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::FailControlMessage_Command_IsValid(value)) {
            set_command(static_cast< ::FailControlMessage_Command >(value));
          } else {
            mutable_unknown_fields()->AddVarint(
                1, static_cast< ::google::protobuf::uint64>(value));
          }
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated uint32 workloadID = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 16u, input, this->mutable_workloadid())));
        } else if (
            static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_workloadid())));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required uint64 build_id = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(24u /* 24 & 0xFF */)) {
          set_has_build_id();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &build_id_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional uint64 run_id = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(32u /* 32 & 0xFF */)) {
          set_has_run_id();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &run_id_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional uint32 job_size = 5;
      case 5: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(40u /* 40 & 0xFF */)) {
          set_has_job_size();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &job_size_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:FailControlMessage)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:FailControlMessage)
  return false;
#undef DO_
}

void FailControlMessage::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:FailControlMessage)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required .FailControlMessage.Command command = 1;
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->command(), output);
  }

  // repeated uint32 workloadID = 2;
  for (int i = 0, n = this->workloadid_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      2, this->workloadid(i), output);
  }

  // required uint64 build_id = 3;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(3, this->build_id(), output);
  }

  // optional uint64 run_id = 4;
  if (cached_has_bits & 0x00000008u) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(4, this->run_id(), output);
  }

  // optional uint32 job_size = 5;
  if (cached_has_bits & 0x00000004u) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->job_size(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:FailControlMessage)
}

::google::protobuf::uint8* FailControlMessage::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:FailControlMessage)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required .FailControlMessage.Command command = 1;
  if (cached_has_bits & 0x00000002u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->command(), target);
  }

  // repeated uint32 workloadID = 2;
  target = ::google::protobuf::internal::WireFormatLite::
    WriteUInt32ToArray(2, this->workloadid_, target);

  // required uint64 build_id = 3;
  if (cached_has_bits & 0x00000001u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(3, this->build_id(), target);
  }

  // optional uint64 run_id = 4;
  if (cached_has_bits & 0x00000008u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(4, this->run_id(), target);
  }

  // optional uint32 job_size = 5;
  if (cached_has_bits & 0x00000004u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(5, this->job_size(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:FailControlMessage)
  return target;
}

size_t FailControlMessage::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:FailControlMessage)
  size_t total_size = 0;

  if (has_build_id()) {
    // required uint64 build_id = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt64Size(
        this->build_id());
  }

  if (has_command()) {
    // required .FailControlMessage.Command command = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->command());
  }

  return total_size;
}
size_t FailControlMessage::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:FailControlMessage)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required uint64 build_id = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt64Size(
        this->build_id());

    // required .FailControlMessage.Command command = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->command());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  // repeated uint32 workloadID = 2;
  {
    size_t data_size = ::google::protobuf::internal::WireFormatLite::
      UInt32Size(this->workloadid_);
    total_size += 1 *
                  ::google::protobuf::internal::FromIntSize(this->workloadid_size());
    total_size += data_size;
  }

  if (_has_bits_[0 / 32] & 12u) {
    // optional uint32 job_size = 5;
    if (has_job_size()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->job_size());
    }

    // optional uint64 run_id = 4;
    if (has_run_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->run_id());
    }

  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void FailControlMessage::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:FailControlMessage)
  GOOGLE_DCHECK_NE(&from, this);
  const FailControlMessage* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const FailControlMessage>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:FailControlMessage)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:FailControlMessage)
    MergeFrom(*source);
  }
}

void FailControlMessage::MergeFrom(const FailControlMessage& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:FailControlMessage)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  workloadid_.MergeFrom(from.workloadid_);
  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 15u) {
    if (cached_has_bits & 0x00000001u) {
      build_id_ = from.build_id_;
    }
    if (cached_has_bits & 0x00000002u) {
      command_ = from.command_;
    }
    if (cached_has_bits & 0x00000004u) {
      job_size_ = from.job_size_;
    }
    if (cached_has_bits & 0x00000008u) {
      run_id_ = from.run_id_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void FailControlMessage::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:FailControlMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void FailControlMessage::CopyFrom(const FailControlMessage& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:FailControlMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FailControlMessage::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  return true;
}

void FailControlMessage::Swap(FailControlMessage* other) {
  if (other == this) return;
  InternalSwap(other);
}
void FailControlMessage::InternalSwap(FailControlMessage* other) {
  using std::swap;
  workloadid_.InternalSwap(&other->workloadid_);
  swap(build_id_, other->build_id_);
  swap(command_, other->command_);
  swap(job_size_, other->job_size_);
  swap(run_id_, other->run_id_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata FailControlMessage::GetMetadata() const {
  protobuf_FailControlMessage_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_FailControlMessage_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
namespace google {
namespace protobuf {
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::FailControlMessage* Arena::CreateMaybeMessage< ::FailControlMessage >(Arena* arena) {
  return Arena::CreateInternal< ::FailControlMessage >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
