# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: parse/proto/parser_config.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='parse/proto/parser_config.proto',
  package='hotbox',
  syntax='proto3',
  serialized_pb=b'\n\x1fparse/proto/parser_config.proto\x12\x06hotbox\"|\n\x0cParserConfig\x12\x33\n\rlibsvm_config\x18\x02 \x01(\x0b\x32\x1a.hotbox.LibSVMParserConfigH\x00\x12-\n\ncsv_config\x18\x01 \x01(\x0b\x32\x17.hotbox.CSVParserConfigH\x00\x42\x08\n\x06\x63onfig\"H\n\x12LibSVMParserConfig\x12\x19\n\x11\x66\x65\x61ture_one_based\x18\x01 \x01(\x08\x12\x17\n\x0flabel_one_based\x18\x02 \x01(\x08\":\n\x0f\x43SVParserConfig\x12\x12\n\nhas_header\x18\x03 \x01(\x08\x12\x13\n\x0blabel_front\x18\x04 \x01(\x08\x62\x06proto3'
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_PARSERCONFIG = _descriptor.Descriptor(
  name='ParserConfig',
  full_name='hotbox.ParserConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='libsvm_config', full_name='hotbox.ParserConfig.libsvm_config', index=0,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='csv_config', full_name='hotbox.ParserConfig.csv_config', index=1,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
    _descriptor.OneofDescriptor(
      name='config', full_name='hotbox.ParserConfig.config',
      index=0, containing_type=None, fields=[]),
  ],
  serialized_start=43,
  serialized_end=167,
)


_LIBSVMPARSERCONFIG = _descriptor.Descriptor(
  name='LibSVMParserConfig',
  full_name='hotbox.LibSVMParserConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='feature_one_based', full_name='hotbox.LibSVMParserConfig.feature_one_based', index=0,
      number=1, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='label_one_based', full_name='hotbox.LibSVMParserConfig.label_one_based', index=1,
      number=2, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=169,
  serialized_end=241,
)


_CSVPARSERCONFIG = _descriptor.Descriptor(
  name='CSVParserConfig',
  full_name='hotbox.CSVParserConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='has_header', full_name='hotbox.CSVParserConfig.has_header', index=0,
      number=3, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='label_front', full_name='hotbox.CSVParserConfig.label_front', index=1,
      number=4, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=243,
  serialized_end=301,
)

_PARSERCONFIG.fields_by_name['libsvm_config'].message_type = _LIBSVMPARSERCONFIG
_PARSERCONFIG.fields_by_name['csv_config'].message_type = _CSVPARSERCONFIG
_PARSERCONFIG.oneofs_by_name['config'].fields.append(
  _PARSERCONFIG.fields_by_name['libsvm_config'])
_PARSERCONFIG.fields_by_name['libsvm_config'].containing_oneof = _PARSERCONFIG.oneofs_by_name['config']
_PARSERCONFIG.oneofs_by_name['config'].fields.append(
  _PARSERCONFIG.fields_by_name['csv_config'])
_PARSERCONFIG.fields_by_name['csv_config'].containing_oneof = _PARSERCONFIG.oneofs_by_name['config']
DESCRIPTOR.message_types_by_name['ParserConfig'] = _PARSERCONFIG
DESCRIPTOR.message_types_by_name['LibSVMParserConfig'] = _LIBSVMPARSERCONFIG
DESCRIPTOR.message_types_by_name['CSVParserConfig'] = _CSVPARSERCONFIG

ParserConfig = _reflection.GeneratedProtocolMessageType('ParserConfig', (_message.Message,), dict(
  DESCRIPTOR = _PARSERCONFIG,
  __module__ = 'parse.proto.parser_config_pb2'
  # @@protoc_insertion_point(class_scope:hotbox.ParserConfig)
  ))
_sym_db.RegisterMessage(ParserConfig)

LibSVMParserConfig = _reflection.GeneratedProtocolMessageType('LibSVMParserConfig', (_message.Message,), dict(
  DESCRIPTOR = _LIBSVMPARSERCONFIG,
  __module__ = 'parse.proto.parser_config_pb2'
  # @@protoc_insertion_point(class_scope:hotbox.LibSVMParserConfig)
  ))
_sym_db.RegisterMessage(LibSVMParserConfig)

CSVParserConfig = _reflection.GeneratedProtocolMessageType('CSVParserConfig', (_message.Message,), dict(
  DESCRIPTOR = _CSVPARSERCONFIG,
  __module__ = 'parse.proto.parser_config_pb2'
  # @@protoc_insertion_point(class_scope:hotbox.CSVParserConfig)
  ))
_sym_db.RegisterMessage(CSVParserConfig)


# @@protoc_insertion_point(module_scope)
