/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C_NO_DEPRECATED
#define PROTOBUF_C_NO_DEPRECATED
#endif

#include "getdata.pb-c.h"
void   sensor_info__init
                     (SensorInfo         *message)
{
  static SensorInfo init_value = SENSOR_INFO__INIT;
  *message = init_value;
}
size_t sensor_info__get_packed_size
                     (const SensorInfo *message)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &sensor_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t sensor_info__pack
                     (const SensorInfo *message,
                      uint8_t       *out)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &sensor_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t sensor_info__pack_to_buffer
                     (const SensorInfo *message,
                      ProtobufCBuffer *buffer)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &sensor_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
SensorInfo *
       sensor_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (SensorInfo *)
     protobuf_c_message_unpack (&sensor_info__descriptor,
                                allocator, len, data);
}
void   sensor_info__free_unpacked
                     (SensorInfo *message,
                      ProtobufCAllocator *allocator)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &sensor_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   sensor_t__init
                     (SensorT         *message)
{
  static SensorT init_value = SENSOR_T__INIT;
  *message = init_value;
}
size_t sensor_t__get_packed_size
                     (const SensorT *message)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &sensor_t__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t sensor_t__pack
                     (const SensorT *message,
                      uint8_t       *out)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &sensor_t__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t sensor_t__pack_to_buffer
                     (const SensorT *message,
                      ProtobufCBuffer *buffer)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &sensor_t__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
SensorT *
       sensor_t__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (SensorT *)
     protobuf_c_message_unpack (&sensor_t__descriptor,
                                allocator, len, data);
}
void   sensor_t__free_unpacked
                     (SensorT *message,
                      ProtobufCAllocator *allocator)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &sensor_t__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor sensor_info__field_descriptors[5] =
{
  {
    "Roomid",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(SensorInfo, roomid),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Temperature",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_FLOAT,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(SensorInfo, temperature),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Humidity",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_FLOAT,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(SensorInfo, humidity),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Co2",
    4,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_FLOAT,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(SensorInfo, co2),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Light",
    5,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_FLOAT,
    PROTOBUF_C_OFFSETOF(SensorInfo, has_light),
    PROTOBUF_C_OFFSETOF(SensorInfo, light),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned sensor_info__field_indices_by_name[] = {
  3,   /* field[3] = Co2 */
  2,   /* field[2] = Humidity */
  4,   /* field[4] = Light */
  0,   /* field[0] = Roomid */
  1,   /* field[1] = Temperature */
};
static const ProtobufCIntRange sensor_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 5 }
};
const ProtobufCMessageDescriptor sensor_info__descriptor =
{
  PROTOBUF_C_MESSAGE_DESCRIPTOR_MAGIC,
  "SensorInfo",
  "SensorInfo",
  "SensorInfo",
  "",
  sizeof(SensorInfo),
  5,
  sensor_info__field_descriptors,
  sensor_info__field_indices_by_name,
  1,  sensor_info__number_ranges,
  (ProtobufCMessageInit) sensor_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor sensor_t__field_descriptors[2] =
{
  {
    "Roomid",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(SensorT, roomid),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Temperature",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_FLOAT,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(SensorT, temperature),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned sensor_t__field_indices_by_name[] = {
  0,   /* field[0] = Roomid */
  1,   /* field[1] = Temperature */
};
static const ProtobufCIntRange sensor_t__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor sensor_t__descriptor =
{
  PROTOBUF_C_MESSAGE_DESCRIPTOR_MAGIC,
  "SensorT",
  "SensorT",
  "SensorT",
  "",
  sizeof(SensorT),
  2,
  sensor_t__field_descriptors,
  sensor_t__field_indices_by_name,
  1,  sensor_t__number_ranges,
  (ProtobufCMessageInit) sensor_t__init,
  NULL,NULL,NULL    /* reserved[123] */
};
