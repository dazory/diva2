# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: sensors.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='sensors.proto',
  package='sensors',
  syntax='proto3',
  serialized_options=None,
  create_key=_descriptor._internal_create_key,
  serialized_pb=b'\n\rsensors.proto\x12\x07sensors\x1a\x1fgoogle/protobuf/timestamp.proto\"d\n\x03Gps\x12\x10\n\x08latitude\x18\x01 \x01(\x01\x12\x11\n\tlongitude\x18\x02 \x01(\x01\x12%\n\x1dhorizontalDilutionOfPrecision\x18\x03 \x01(\x01\x12\x11\n\ttimestamp\x18\x04 \x01(\x01\"Z\n\x03Imu\x12\x14\n\x0cscaledAccelX\x18\x01 \x01(\x02\x12\x14\n\x0cscaledAccelY\x18\x02 \x01(\x02\x12\x14\n\x0cscaledAccelZ\x18\x03 \x01(\x02\x12\x11\n\ttimestamp\x18\x04 \x01(\x01\"H\n\x03\x43\x61m\x12\x0c\n\x04\x63ols\x18\x01 \x01(\x05\x12\x0c\n\x04rows\x18\x02 \x01(\x05\x12\x12\n\nimage_data\x18\x03 \x01(\x0c\x12\x11\n\ttimestamp\x18\x04 \x01(\x01\"r\n\x05Lidar\x12\x0c\n\x04size\x18\x01 \x01(\x02\x12 \n\x04\x64\x61ta\x18\x02 \x03(\x0b\x32\x12.sensors.Lidar.xyz\x12\x11\n\ttimestamp\x18\x03 \x01(\x01\x1a&\n\x03xyz\x12\t\n\x01x\x18\x01 \x01(\x02\x12\t\n\x01y\x18\x02 \x01(\x02\x12\t\n\x01z\x18\x03 \x01(\x02\"4\n\x03\x43\x61n\x12\x0c\n\x04type\x18\x01 \x01(\x02\x12\x0c\n\x04\x64\x61ta\x18\x02 \x01(\x02\x12\x11\n\ttimestamp\x18\x03 \x01(\x01\"c\n\x03Log\x12\x0e\n\x06\x63\x61n_id\x18\x02 \x01(\r\x12\x0f\n\x07\x63\x61n_dlc\x18\x03 \x01(\r\x12\r\n\x05__pad\x18\x04 \x01(\x0c\x12\x0e\n\x06__res0\x18\x05 \x01(\x0c\x12\x0e\n\x06__res1\x18\x06 \x01(\x0c\x12\x0c\n\x04\x64\x61ta\x18\x07 \x01(\x0c\"n\n\ralgorithm_img\x12\x0c\n\x04\x63ols\x18\x01 \x01(\x05\x12\x0c\n\x04rows\x18\x02 \x01(\x05\x12\x16\n\x0eimage_original\x18\x03 \x01(\x0c\x12\x14\n\x0cimage_result\x18\x04 \x01(\x0c\x12\x13\n\x0bmillis_term\x18\x05 \x01(\x02*U\n\x0c\x43hannelOrder\x12\r\n\tGRAYSCALE\x10\x00\x12\x07\n\x03\x42GR\x10\x01\x12\x07\n\x03RGB\x10\x02\x12\x08\n\x04\x42GRA\x10\x03\x12\x08\n\x04RGBA\x10\x04\x12\x10\n\x0cOPTICAL_FLOW\x10\x05\x62\x06proto3'
  ,
  dependencies=[google_dot_protobuf_dot_timestamp__pb2.DESCRIPTOR,])

_CHANNELORDER = _descriptor.EnumDescriptor(
  name='ChannelOrder',
  full_name='sensors.ChannelOrder',
  filename=None,
  file=DESCRIPTOR,
  create_key=_descriptor._internal_create_key,
  values=[
    _descriptor.EnumValueDescriptor(
      name='GRAYSCALE', index=0, number=0,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='BGR', index=1, number=1,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='RGB', index=2, number=2,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='BGRA', index=3, number=3,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='RGBA', index=4, number=4,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='OPTICAL_FLOW', index=5, number=5,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=710,
  serialized_end=795,
)
_sym_db.RegisterEnumDescriptor(_CHANNELORDER)

ChannelOrder = enum_type_wrapper.EnumTypeWrapper(_CHANNELORDER)
GRAYSCALE = 0
BGR = 1
RGB = 2
BGRA = 3
RGBA = 4
OPTICAL_FLOW = 5



_GPS = _descriptor.Descriptor(
  name='Gps',
  full_name='sensors.Gps',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='latitude', full_name='sensors.Gps.latitude', index=0,
      number=1, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='longitude', full_name='sensors.Gps.longitude', index=1,
      number=2, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='horizontalDilutionOfPrecision', full_name='sensors.Gps.horizontalDilutionOfPrecision', index=2,
      number=3, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='timestamp', full_name='sensors.Gps.timestamp', index=3,
      number=4, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=59,
  serialized_end=159,
)


_IMU = _descriptor.Descriptor(
  name='Imu',
  full_name='sensors.Imu',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='scaledAccelX', full_name='sensors.Imu.scaledAccelX', index=0,
      number=1, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='scaledAccelY', full_name='sensors.Imu.scaledAccelY', index=1,
      number=2, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='scaledAccelZ', full_name='sensors.Imu.scaledAccelZ', index=2,
      number=3, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='timestamp', full_name='sensors.Imu.timestamp', index=3,
      number=4, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=161,
  serialized_end=251,
)


_CAM = _descriptor.Descriptor(
  name='Cam',
  full_name='sensors.Cam',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='cols', full_name='sensors.Cam.cols', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='rows', full_name='sensors.Cam.rows', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='image_data', full_name='sensors.Cam.image_data', index=2,
      number=3, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=b"",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='timestamp', full_name='sensors.Cam.timestamp', index=3,
      number=4, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=253,
  serialized_end=325,
)


_LIDAR_XYZ = _descriptor.Descriptor(
  name='xyz',
  full_name='sensors.Lidar.xyz',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='x', full_name='sensors.Lidar.xyz.x', index=0,
      number=1, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='y', full_name='sensors.Lidar.xyz.y', index=1,
      number=2, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='z', full_name='sensors.Lidar.xyz.z', index=2,
      number=3, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=403,
  serialized_end=441,
)

_LIDAR = _descriptor.Descriptor(
  name='Lidar',
  full_name='sensors.Lidar',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='size', full_name='sensors.Lidar.size', index=0,
      number=1, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='data', full_name='sensors.Lidar.data', index=1,
      number=2, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='timestamp', full_name='sensors.Lidar.timestamp', index=2,
      number=3, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[_LIDAR_XYZ, ],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=327,
  serialized_end=441,
)


_CAN = _descriptor.Descriptor(
  name='Can',
  full_name='sensors.Can',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='type', full_name='sensors.Can.type', index=0,
      number=1, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='data', full_name='sensors.Can.data', index=1,
      number=2, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='timestamp', full_name='sensors.Can.timestamp', index=2,
      number=3, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=443,
  serialized_end=495,
)


_LOG = _descriptor.Descriptor(
  name='Log',
  full_name='sensors.Log',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='can_id', full_name='sensors.Log.can_id', index=0,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='can_dlc', full_name='sensors.Log.can_dlc', index=1,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='__pad', full_name='sensors.Log.__pad', index=2,
      number=4, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=b"",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='__res0', full_name='sensors.Log.__res0', index=3,
      number=5, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=b"",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='__res1', full_name='sensors.Log.__res1', index=4,
      number=6, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=b"",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='data', full_name='sensors.Log.data', index=5,
      number=7, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=b"",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=497,
  serialized_end=596,
)


_ALGORITHM_IMG = _descriptor.Descriptor(
  name='algorithm_img',
  full_name='sensors.algorithm_img',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='cols', full_name='sensors.algorithm_img.cols', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='rows', full_name='sensors.algorithm_img.rows', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='image_original', full_name='sensors.algorithm_img.image_original', index=2,
      number=3, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=b"",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='image_result', full_name='sensors.algorithm_img.image_result', index=3,
      number=4, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=b"",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='millis_term', full_name='sensors.algorithm_img.millis_term', index=4,
      number=5, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=598,
  serialized_end=708,
)

_LIDAR_XYZ.containing_type = _LIDAR
_LIDAR.fields_by_name['data'].message_type = _LIDAR_XYZ
DESCRIPTOR.message_types_by_name['Gps'] = _GPS
DESCRIPTOR.message_types_by_name['Imu'] = _IMU
DESCRIPTOR.message_types_by_name['Cam'] = _CAM
DESCRIPTOR.message_types_by_name['Lidar'] = _LIDAR
DESCRIPTOR.message_types_by_name['Can'] = _CAN
DESCRIPTOR.message_types_by_name['Log'] = _LOG
DESCRIPTOR.message_types_by_name['algorithm_img'] = _ALGORITHM_IMG
DESCRIPTOR.enum_types_by_name['ChannelOrder'] = _CHANNELORDER
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

Gps = _reflection.GeneratedProtocolMessageType('Gps', (_message.Message,), {
  'DESCRIPTOR' : _GPS,
  '__module__' : 'sensors_pb2'
  # @@protoc_insertion_point(class_scope:sensors.Gps)
  })
_sym_db.RegisterMessage(Gps)

Imu = _reflection.GeneratedProtocolMessageType('Imu', (_message.Message,), {
  'DESCRIPTOR' : _IMU,
  '__module__' : 'sensors_pb2'
  # @@protoc_insertion_point(class_scope:sensors.Imu)
  })
_sym_db.RegisterMessage(Imu)

Cam = _reflection.GeneratedProtocolMessageType('Cam', (_message.Message,), {
  'DESCRIPTOR' : _CAM,
  '__module__' : 'sensors_pb2'
  # @@protoc_insertion_point(class_scope:sensors.Cam)
  })
_sym_db.RegisterMessage(Cam)

Lidar = _reflection.GeneratedProtocolMessageType('Lidar', (_message.Message,), {

  'xyz' : _reflection.GeneratedProtocolMessageType('xyz', (_message.Message,), {
    'DESCRIPTOR' : _LIDAR_XYZ,
    '__module__' : 'sensors_pb2'
    # @@protoc_insertion_point(class_scope:sensors.Lidar.xyz)
    })
  ,
  'DESCRIPTOR' : _LIDAR,
  '__module__' : 'sensors_pb2'
  # @@protoc_insertion_point(class_scope:sensors.Lidar)
  })
_sym_db.RegisterMessage(Lidar)
_sym_db.RegisterMessage(Lidar.xyz)

Can = _reflection.GeneratedProtocolMessageType('Can', (_message.Message,), {
  'DESCRIPTOR' : _CAN,
  '__module__' : 'sensors_pb2'
  # @@protoc_insertion_point(class_scope:sensors.Can)
  })
_sym_db.RegisterMessage(Can)

Log = _reflection.GeneratedProtocolMessageType('Log', (_message.Message,), {
  'DESCRIPTOR' : _LOG,
  '__module__' : 'sensors_pb2'
  # @@protoc_insertion_point(class_scope:sensors.Log)
  })
_sym_db.RegisterMessage(Log)

algorithm_img = _reflection.GeneratedProtocolMessageType('algorithm_img', (_message.Message,), {
  'DESCRIPTOR' : _ALGORITHM_IMG,
  '__module__' : 'sensors_pb2'
  # @@protoc_insertion_point(class_scope:sensors.algorithm_img)
  })
_sym_db.RegisterMessage(algorithm_img)


# @@protoc_insertion_point(module_scope)
