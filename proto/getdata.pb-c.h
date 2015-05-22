/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

#ifndef PROTOBUF_C_getdata_2eproto__INCLUDED
#define PROTOBUF_C_getdata_2eproto__INCLUDED

#include "protobuf-c.h"

PROTOBUF_C_BEGIN_DECLS


typedef struct _SensorInfo SensorInfo;
typedef struct _SensorT SensorT;


/* --- enums --- */


/* --- messages --- */

struct  _SensorInfo
{
  ProtobufCMessage base;
  int32_t roomid;
  float temperature;
  float humidity;
  float co2;
  protobuf_c_boolean has_light;
  float light;
};
#define SENSOR_INFO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&sensor_info__descriptor) \
    , 0, 0, 0, 0, 0,0 }


struct  _SensorT
{
  ProtobufCMessage base;
  int32_t roomid;
  float temperature;
};
#define SENSOR_T__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&sensor_t__descriptor) \
    , 0, 0 }


/* SensorInfo methods */
void   sensor_info__init
                     (SensorInfo         *message);
size_t sensor_info__get_packed_size
                     (const SensorInfo   *message);
size_t sensor_info__pack
                     (const SensorInfo   *message,
                      uint8_t             *out);
size_t sensor_info__pack_to_buffer
                     (const SensorInfo   *message,
                      ProtobufCBuffer     *buffer);
SensorInfo *
       sensor_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   sensor_info__free_unpacked
                     (SensorInfo *message,
                      ProtobufCAllocator *allocator);
/* SensorT methods */
void   sensor_t__init
                     (SensorT         *message);
size_t sensor_t__get_packed_size
                     (const SensorT   *message);
size_t sensor_t__pack
                     (const SensorT   *message,
                      uint8_t             *out);
size_t sensor_t__pack_to_buffer
                     (const SensorT   *message,
                      ProtobufCBuffer     *buffer);
SensorT *
       sensor_t__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   sensor_t__free_unpacked
                     (SensorT *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*SensorInfo_Closure)
                 (const SensorInfo *message,
                  void *closure_data);
typedef void (*SensorT_Closure)
                 (const SensorT *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor sensor_info__descriptor;
extern const ProtobufCMessageDescriptor sensor_t__descriptor;

PROTOBUF_C_END_DECLS


#endif  /* PROTOBUF_getdata_2eproto__INCLUDED */
