// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Device.proto

#include "Device.pb.h"

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

namespace Device_msg {
class F710DefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<F710>
      _instance;
} _F710_default_instance_;
}  // namespace Device_msg
namespace protobuf_Device_2eproto {
static void InitDefaultsF710() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::Device_msg::_F710_default_instance_;
    new (ptr) ::Device_msg::F710();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::Device_msg::F710::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_F710 =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsF710}, {}};

void InitDefaults() {
  ::google::protobuf::internal::InitSCC(&scc_info_F710.base);
}

::google::protobuf::Metadata file_level_metadata[1];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, timestamp_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, lx_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, ly_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, rx_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, ry_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, lt_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, rt_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, lb_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, rb_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, left_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, right_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, up_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, down_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, a_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, b_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, x_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, y_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, start_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, back_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Device_msg::F710, logitech_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::Device_msg::F710)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::Device_msg::_F710_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  AssignDescriptors(
      "Device.proto", schemas, file_default_instances, TableStruct::offsets,
      file_level_metadata, NULL, NULL);
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
      "\n\014Device.proto\022\nDevice_msg\"\213\002\n\004F710\022\021\n\tT"
      "imestamp\030\025 \001(\004\022\n\n\002Lx\030\001 \001(\001\022\n\n\002Ly\030\002 \001(\001\022\n"
      "\n\002Rx\030\003 \001(\001\022\n\n\002Ry\030\004 \001(\001\022\n\n\002Lt\030\005 \001(\001\022\n\n\002Rt"
      "\030\006 \001(\001\022\n\n\002Lb\030\007 \001(\r\022\n\n\002Rb\030\010 \001(\r\022\014\n\004Left\030\n"
      " \001(\r\022\r\n\005Right\030\013 \001(\r\022\n\n\002Up\030\014 \001(\r\022\014\n\004Down\030"
      "\r \001(\r\022\t\n\001A\030\016 \001(\r\022\t\n\001B\030\017 \001(\r\022\t\n\001X\030\020 \001(\r\022\t"
      "\n\001Y\030\021 \001(\r\022\r\n\005Start\030\022 \001(\r\022\014\n\004Back\030\023 \001(\r\022\020"
      "\n\010Logitech\030\024 \001(\rb\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 304);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Device.proto", &protobuf_RegisterTypes);
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
}  // namespace protobuf_Device_2eproto
namespace Device_msg {

// ===================================================================

void F710::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int F710::kTimestampFieldNumber;
const int F710::kLxFieldNumber;
const int F710::kLyFieldNumber;
const int F710::kRxFieldNumber;
const int F710::kRyFieldNumber;
const int F710::kLtFieldNumber;
const int F710::kRtFieldNumber;
const int F710::kLbFieldNumber;
const int F710::kRbFieldNumber;
const int F710::kLeftFieldNumber;
const int F710::kRightFieldNumber;
const int F710::kUpFieldNumber;
const int F710::kDownFieldNumber;
const int F710::kAFieldNumber;
const int F710::kBFieldNumber;
const int F710::kXFieldNumber;
const int F710::kYFieldNumber;
const int F710::kStartFieldNumber;
const int F710::kBackFieldNumber;
const int F710::kLogitechFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

F710::F710()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_Device_2eproto::scc_info_F710.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:Device_msg.F710)
}
F710::F710(const F710& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&lx_, &from.lx_,
    static_cast<size_t>(reinterpret_cast<char*>(&logitech_) -
    reinterpret_cast<char*>(&lx_)) + sizeof(logitech_));
  // @@protoc_insertion_point(copy_constructor:Device_msg.F710)
}

void F710::SharedCtor() {
  ::memset(&lx_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&logitech_) -
      reinterpret_cast<char*>(&lx_)) + sizeof(logitech_));
}

F710::~F710() {
  // @@protoc_insertion_point(destructor:Device_msg.F710)
  SharedDtor();
}

void F710::SharedDtor() {
}

void F710::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* F710::descriptor() {
  ::protobuf_Device_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_Device_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const F710& F710::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_Device_2eproto::scc_info_F710.base);
  return *internal_default_instance();
}


void F710::Clear() {
// @@protoc_insertion_point(message_clear_start:Device_msg.F710)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&lx_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&logitech_) -
      reinterpret_cast<char*>(&lx_)) + sizeof(logitech_));
  _internal_metadata_.Clear();
}

bool F710::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Device_msg.F710)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(16383u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // double Lx = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(9u /* 9 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &lx_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // double Ly = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(17u /* 17 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &ly_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // double Rx = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(25u /* 25 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &rx_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // double Ry = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(33u /* 33 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &ry_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // double Lt = 5;
      case 5: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(41u /* 41 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &lt_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // double Rt = 6;
      case 6: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(49u /* 49 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &rt_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint32 Lb = 7;
      case 7: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(56u /* 56 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &lb_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint32 Rb = 8;
      case 8: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(64u /* 64 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &rb_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint32 Left = 10;
      case 10: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(80u /* 80 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &left_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint32 Right = 11;
      case 11: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(88u /* 88 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &right_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint32 Up = 12;
      case 12: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(96u /* 96 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &up_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint32 Down = 13;
      case 13: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(104u /* 104 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &down_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint32 A = 14;
      case 14: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(112u /* 112 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &a_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint32 B = 15;
      case 15: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(120u /* 120 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &b_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint32 X = 16;
      case 16: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(128u /* 128 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &x_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint32 Y = 17;
      case 17: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(136u /* 136 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &y_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint32 Start = 18;
      case 18: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(144u /* 144 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &start_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint32 Back = 19;
      case 19: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(152u /* 152 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &back_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint32 Logitech = 20;
      case 20: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(160u /* 160 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &logitech_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint64 Timestamp = 21;
      case 21: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(168u /* 168 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &timestamp_)));
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
  // @@protoc_insertion_point(parse_success:Device_msg.F710)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Device_msg.F710)
  return false;
#undef DO_
}

void F710::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Device_msg.F710)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // double Lx = 1;
  if (this->lx() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(1, this->lx(), output);
  }

  // double Ly = 2;
  if (this->ly() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(2, this->ly(), output);
  }

  // double Rx = 3;
  if (this->rx() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(3, this->rx(), output);
  }

  // double Ry = 4;
  if (this->ry() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(4, this->ry(), output);
  }

  // double Lt = 5;
  if (this->lt() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(5, this->lt(), output);
  }

  // double Rt = 6;
  if (this->rt() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(6, this->rt(), output);
  }

  // uint32 Lb = 7;
  if (this->lb() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(7, this->lb(), output);
  }

  // uint32 Rb = 8;
  if (this->rb() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(8, this->rb(), output);
  }

  // uint32 Left = 10;
  if (this->left() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(10, this->left(), output);
  }

  // uint32 Right = 11;
  if (this->right() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(11, this->right(), output);
  }

  // uint32 Up = 12;
  if (this->up() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(12, this->up(), output);
  }

  // uint32 Down = 13;
  if (this->down() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(13, this->down(), output);
  }

  // uint32 A = 14;
  if (this->a() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(14, this->a(), output);
  }

  // uint32 B = 15;
  if (this->b() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(15, this->b(), output);
  }

  // uint32 X = 16;
  if (this->x() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(16, this->x(), output);
  }

  // uint32 Y = 17;
  if (this->y() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(17, this->y(), output);
  }

  // uint32 Start = 18;
  if (this->start() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(18, this->start(), output);
  }

  // uint32 Back = 19;
  if (this->back() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(19, this->back(), output);
  }

  // uint32 Logitech = 20;
  if (this->logitech() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(20, this->logitech(), output);
  }

  // uint64 Timestamp = 21;
  if (this->timestamp() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(21, this->timestamp(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:Device_msg.F710)
}

::google::protobuf::uint8* F710::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:Device_msg.F710)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // double Lx = 1;
  if (this->lx() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(1, this->lx(), target);
  }

  // double Ly = 2;
  if (this->ly() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(2, this->ly(), target);
  }

  // double Rx = 3;
  if (this->rx() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(3, this->rx(), target);
  }

  // double Ry = 4;
  if (this->ry() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(4, this->ry(), target);
  }

  // double Lt = 5;
  if (this->lt() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(5, this->lt(), target);
  }

  // double Rt = 6;
  if (this->rt() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(6, this->rt(), target);
  }

  // uint32 Lb = 7;
  if (this->lb() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(7, this->lb(), target);
  }

  // uint32 Rb = 8;
  if (this->rb() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(8, this->rb(), target);
  }

  // uint32 Left = 10;
  if (this->left() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(10, this->left(), target);
  }

  // uint32 Right = 11;
  if (this->right() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(11, this->right(), target);
  }

  // uint32 Up = 12;
  if (this->up() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(12, this->up(), target);
  }

  // uint32 Down = 13;
  if (this->down() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(13, this->down(), target);
  }

  // uint32 A = 14;
  if (this->a() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(14, this->a(), target);
  }

  // uint32 B = 15;
  if (this->b() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(15, this->b(), target);
  }

  // uint32 X = 16;
  if (this->x() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(16, this->x(), target);
  }

  // uint32 Y = 17;
  if (this->y() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(17, this->y(), target);
  }

  // uint32 Start = 18;
  if (this->start() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(18, this->start(), target);
  }

  // uint32 Back = 19;
  if (this->back() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(19, this->back(), target);
  }

  // uint32 Logitech = 20;
  if (this->logitech() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(20, this->logitech(), target);
  }

  // uint64 Timestamp = 21;
  if (this->timestamp() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(21, this->timestamp(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Device_msg.F710)
  return target;
}

size_t F710::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Device_msg.F710)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // double Lx = 1;
  if (this->lx() != 0) {
    total_size += 1 + 8;
  }

  // double Ly = 2;
  if (this->ly() != 0) {
    total_size += 1 + 8;
  }

  // double Rx = 3;
  if (this->rx() != 0) {
    total_size += 1 + 8;
  }

  // double Ry = 4;
  if (this->ry() != 0) {
    total_size += 1 + 8;
  }

  // double Lt = 5;
  if (this->lt() != 0) {
    total_size += 1 + 8;
  }

  // double Rt = 6;
  if (this->rt() != 0) {
    total_size += 1 + 8;
  }

  // uint32 Lb = 7;
  if (this->lb() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->lb());
  }

  // uint32 Rb = 8;
  if (this->rb() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->rb());
  }

  // uint32 Left = 10;
  if (this->left() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->left());
  }

  // uint32 Right = 11;
  if (this->right() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->right());
  }

  // uint32 Up = 12;
  if (this->up() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->up());
  }

  // uint32 Down = 13;
  if (this->down() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->down());
  }

  // uint32 A = 14;
  if (this->a() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->a());
  }

  // uint32 B = 15;
  if (this->b() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->b());
  }

  // uint32 X = 16;
  if (this->x() != 0) {
    total_size += 2 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->x());
  }

  // uint32 Y = 17;
  if (this->y() != 0) {
    total_size += 2 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->y());
  }

  // uint32 Start = 18;
  if (this->start() != 0) {
    total_size += 2 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->start());
  }

  // uint32 Back = 19;
  if (this->back() != 0) {
    total_size += 2 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->back());
  }

  // uint64 Timestamp = 21;
  if (this->timestamp() != 0) {
    total_size += 2 +
      ::google::protobuf::internal::WireFormatLite::UInt64Size(
        this->timestamp());
  }

  // uint32 Logitech = 20;
  if (this->logitech() != 0) {
    total_size += 2 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->logitech());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void F710::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Device_msg.F710)
  GOOGLE_DCHECK_NE(&from, this);
  const F710* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const F710>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Device_msg.F710)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Device_msg.F710)
    MergeFrom(*source);
  }
}

void F710::MergeFrom(const F710& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Device_msg.F710)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.lx() != 0) {
    set_lx(from.lx());
  }
  if (from.ly() != 0) {
    set_ly(from.ly());
  }
  if (from.rx() != 0) {
    set_rx(from.rx());
  }
  if (from.ry() != 0) {
    set_ry(from.ry());
  }
  if (from.lt() != 0) {
    set_lt(from.lt());
  }
  if (from.rt() != 0) {
    set_rt(from.rt());
  }
  if (from.lb() != 0) {
    set_lb(from.lb());
  }
  if (from.rb() != 0) {
    set_rb(from.rb());
  }
  if (from.left() != 0) {
    set_left(from.left());
  }
  if (from.right() != 0) {
    set_right(from.right());
  }
  if (from.up() != 0) {
    set_up(from.up());
  }
  if (from.down() != 0) {
    set_down(from.down());
  }
  if (from.a() != 0) {
    set_a(from.a());
  }
  if (from.b() != 0) {
    set_b(from.b());
  }
  if (from.x() != 0) {
    set_x(from.x());
  }
  if (from.y() != 0) {
    set_y(from.y());
  }
  if (from.start() != 0) {
    set_start(from.start());
  }
  if (from.back() != 0) {
    set_back(from.back());
  }
  if (from.timestamp() != 0) {
    set_timestamp(from.timestamp());
  }
  if (from.logitech() != 0) {
    set_logitech(from.logitech());
  }
}

void F710::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Device_msg.F710)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void F710::CopyFrom(const F710& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Device_msg.F710)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool F710::IsInitialized() const {
  return true;
}

void F710::Swap(F710* other) {
  if (other == this) return;
  InternalSwap(other);
}
void F710::InternalSwap(F710* other) {
  using std::swap;
  swap(lx_, other->lx_);
  swap(ly_, other->ly_);
  swap(rx_, other->rx_);
  swap(ry_, other->ry_);
  swap(lt_, other->lt_);
  swap(rt_, other->rt_);
  swap(lb_, other->lb_);
  swap(rb_, other->rb_);
  swap(left_, other->left_);
  swap(right_, other->right_);
  swap(up_, other->up_);
  swap(down_, other->down_);
  swap(a_, other->a_);
  swap(b_, other->b_);
  swap(x_, other->x_);
  swap(y_, other->y_);
  swap(start_, other->start_);
  swap(back_, other->back_);
  swap(timestamp_, other->timestamp_);
  swap(logitech_, other->logitech_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata F710::GetMetadata() const {
  protobuf_Device_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_Device_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace Device_msg
namespace google {
namespace protobuf {
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::Device_msg::F710* Arena::CreateMaybeMessage< ::Device_msg::F710 >(Arena* arena) {
  return Arena::CreateInternal< ::Device_msg::F710 >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)