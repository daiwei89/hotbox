# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: schema/proto/schema.proto

from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='schema/proto/schema.proto',
  package='hotbox',
  syntax='proto3',
  serialized_pb=b'\n\x19schema/proto/schema.proto\x12\x06hotbox\"j\n\x07\x46\x65\x61ture\x12\x0c\n\x04name\x18\x01 \x01(\t\x12,\n\nstore_type\x18\x02 \x01(\x0e\x32\x18.hotbox.FeatureStoreType\x12\x0e\n\x06offset\x18\x03 \x01(\x03\x12\x13\n\x0binitialized\x18\x04 \x01(\x08\"\xca\x03\n\nDatumProto\x12\x17\n\x0f\x64\x65nse_cat_store\x18\x01 \x03(\x03\x12\x17\n\x0f\x64\x65nse_num_store\x18\x02 \x03(\x02\x12\x19\n\x11\x64\x65nse_bytes_store\x18\x03 \x03(\x0c\x12@\n\x10sparse_cat_store\x18\x04 \x03(\x0b\x32&.hotbox.DatumProto.SparseCatStoreEntry\x12@\n\x10sparse_num_store\x18\x05 \x03(\x0b\x32&.hotbox.DatumProto.SparseNumStoreEntry\x12\x44\n\x12sparse_bytes_store\x18\x06 \x03(\x0b\x32(.hotbox.DatumProto.SparseBytesStoreEntry\x1a\x35\n\x13SparseCatStoreEntry\x12\x0b\n\x03key\x18\x01 \x01(\r\x12\r\n\x05value\x18\x02 \x01(\x03:\x02\x38\x01\x1a\x35\n\x13SparseNumStoreEntry\x12\x0b\n\x03key\x18\x01 \x01(\r\x12\r\n\x05value\x18\x02 \x01(\x02:\x02\x38\x01\x1a\x37\n\x15SparseBytesStoreEntry\x12\x0b\n\x03key\x18\x01 \x01(\r\x12\r\n\x05value\x18\x02 \x01(\x0c:\x02\x38\x01\"#\n\x10\x44\x61tumProtoOffset\x12\x0f\n\x07offsets\x18\x01 \x03(\x03\"\xd1\x01\n\x12\x46\x65\x61tureFamilyProto\x12\x13\n\x0b\x66\x61mily_name\x18\x01 \x01(\t\x12K\n\x12name_to_family_idx\x18\x02 \x03(\x0b\x32/.hotbox.FeatureFamilyProto.NameToFamilyIdxEntry\x12!\n\x08\x66\x65\x61tures\x18\x03 \x03(\x0b\x32\x0f.hotbox.Feature\x1a\x36\n\x14NameToFamilyIdxEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\x03:\x02\x38\x01\";\n\x0cSchemaConfig\x12\x11\n\tint_label\x18\x01 \x01(\x08\x12\x18\n\x10use_dense_weight\x18\x02 \x01(\x08\"\xea\x01\n\x0bSchemaProto\x12\x0f\n\x07version\x18\x01 \x01(\r\x12\x33\n\x08\x66\x61milies\x18\x02 \x03(\x0b\x32!.hotbox.SchemaProto.FamiliesEntry\x12\x17\n\x0foutput_families\x18\x03 \x03(\t\x12/\n\rappend_offset\x18\x05 \x01(\x0b\x32\x18.hotbox.DatumProtoOffset\x1aK\n\rFamiliesEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12)\n\x05value\x18\x02 \x01(\x0b\x32\x1a.hotbox.FeatureFamilyProto:\x02\x38\x01\"S\n\x0cOSchemaProto\x12\x15\n\rfeature_names\x18\x01 \x03(\t\x12\x14\n\x0c\x66\x61mily_names\x18\x02 \x03(\t\x12\x16\n\x0e\x66\x61mily_offsets\x18\x03 \x03(\x03*R\n\x0b\x46\x65\x61tureType\x12\x18\n\x14UNKNOWN_FEATURE_TYPE\x10\x00\x12\x0f\n\x0b\x43\x41TEGORICAL\x10\x01\x12\r\n\tNUMERICAL\x10\x02\x12\t\n\x05\x42YTES\x10\x03*(\n\x0fOutputStoreType\x12\n\n\x06SPARSE\x10\x00\x12\t\n\x05\x44\x45NSE\x10\x01*(\n\x10\x46\x65\x61tureIndexType\x12\t\n\x05INT64\x10\x00\x12\t\n\x05INT32\x10\x01*\x94\x01\n\x10\x46\x65\x61tureStoreType\x12\n\n\x06OUTPUT\x10\x00\x12\r\n\tDENSE_CAT\x10\x01\x12\r\n\tDENSE_NUM\x10\x02\x12\x0f\n\x0b\x44\x45NSE_BYTES\x10\x03\x12\x0e\n\nSPARSE_CAT\x10\x04\x12\x0e\n\nSPARSE_NUM\x10\x05\x12\x10\n\x0cSPARSE_BYTES\x10\x06\x12\x13\n\x0fNUM_STORE_TYPES\x10\x07\x62\x06proto3'
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

_FEATURETYPE = _descriptor.EnumDescriptor(
  name='FeatureType',
  full_name='hotbox.FeatureType',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='UNKNOWN_FEATURE_TYPE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CATEGORICAL', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='NUMERICAL', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='BYTES', index=3, number=3,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=1238,
  serialized_end=1320,
)
_sym_db.RegisterEnumDescriptor(_FEATURETYPE)

FeatureType = enum_type_wrapper.EnumTypeWrapper(_FEATURETYPE)
_OUTPUTSTORETYPE = _descriptor.EnumDescriptor(
  name='OutputStoreType',
  full_name='hotbox.OutputStoreType',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='SPARSE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='DENSE', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=1322,
  serialized_end=1362,
)
_sym_db.RegisterEnumDescriptor(_OUTPUTSTORETYPE)

OutputStoreType = enum_type_wrapper.EnumTypeWrapper(_OUTPUTSTORETYPE)
_FEATUREINDEXTYPE = _descriptor.EnumDescriptor(
  name='FeatureIndexType',
  full_name='hotbox.FeatureIndexType',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='INT64', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='INT32', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=1364,
  serialized_end=1404,
)
_sym_db.RegisterEnumDescriptor(_FEATUREINDEXTYPE)

FeatureIndexType = enum_type_wrapper.EnumTypeWrapper(_FEATUREINDEXTYPE)
_FEATURESTORETYPE = _descriptor.EnumDescriptor(
  name='FeatureStoreType',
  full_name='hotbox.FeatureStoreType',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='OUTPUT', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='DENSE_CAT', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='DENSE_NUM', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='DENSE_BYTES', index=3, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SPARSE_CAT', index=4, number=4,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SPARSE_NUM', index=5, number=5,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SPARSE_BYTES', index=6, number=6,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='NUM_STORE_TYPES', index=7, number=7,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=1407,
  serialized_end=1555,
)
_sym_db.RegisterEnumDescriptor(_FEATURESTORETYPE)

FeatureStoreType = enum_type_wrapper.EnumTypeWrapper(_FEATURESTORETYPE)
UNKNOWN_FEATURE_TYPE = 0
CATEGORICAL = 1
NUMERICAL = 2
BYTES = 3
SPARSE = 0
DENSE = 1
INT64 = 0
INT32 = 1
OUTPUT = 0
DENSE_CAT = 1
DENSE_NUM = 2
DENSE_BYTES = 3
SPARSE_CAT = 4
SPARSE_NUM = 5
SPARSE_BYTES = 6
NUM_STORE_TYPES = 7



_FEATURE = _descriptor.Descriptor(
  name='Feature',
  full_name='hotbox.Feature',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='name', full_name='hotbox.Feature.name', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='store_type', full_name='hotbox.Feature.store_type', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='offset', full_name='hotbox.Feature.offset', index=2,
      number=3, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='initialized', full_name='hotbox.Feature.initialized', index=3,
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
  serialized_start=37,
  serialized_end=143,
)


_DATUMPROTO_SPARSECATSTOREENTRY = _descriptor.Descriptor(
  name='SparseCatStoreEntry',
  full_name='hotbox.DatumProto.SparseCatStoreEntry',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='key', full_name='hotbox.DatumProto.SparseCatStoreEntry.key', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='value', full_name='hotbox.DatumProto.SparseCatStoreEntry.value', index=1,
      number=2, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=_descriptor._ParseOptions(descriptor_pb2.MessageOptions(), b'8\001'),
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=439,
  serialized_end=492,
)

_DATUMPROTO_SPARSENUMSTOREENTRY = _descriptor.Descriptor(
  name='SparseNumStoreEntry',
  full_name='hotbox.DatumProto.SparseNumStoreEntry',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='key', full_name='hotbox.DatumProto.SparseNumStoreEntry.key', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='value', full_name='hotbox.DatumProto.SparseNumStoreEntry.value', index=1,
      number=2, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=_descriptor._ParseOptions(descriptor_pb2.MessageOptions(), b'8\001'),
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=494,
  serialized_end=547,
)

_DATUMPROTO_SPARSEBYTESSTOREENTRY = _descriptor.Descriptor(
  name='SparseBytesStoreEntry',
  full_name='hotbox.DatumProto.SparseBytesStoreEntry',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='key', full_name='hotbox.DatumProto.SparseBytesStoreEntry.key', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='value', full_name='hotbox.DatumProto.SparseBytesStoreEntry.value', index=1,
      number=2, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=b"",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=_descriptor._ParseOptions(descriptor_pb2.MessageOptions(), b'8\001'),
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=549,
  serialized_end=604,
)

_DATUMPROTO = _descriptor.Descriptor(
  name='DatumProto',
  full_name='hotbox.DatumProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='dense_cat_store', full_name='hotbox.DatumProto.dense_cat_store', index=0,
      number=1, type=3, cpp_type=2, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='dense_num_store', full_name='hotbox.DatumProto.dense_num_store', index=1,
      number=2, type=2, cpp_type=6, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='dense_bytes_store', full_name='hotbox.DatumProto.dense_bytes_store', index=2,
      number=3, type=12, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='sparse_cat_store', full_name='hotbox.DatumProto.sparse_cat_store', index=3,
      number=4, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='sparse_num_store', full_name='hotbox.DatumProto.sparse_num_store', index=4,
      number=5, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='sparse_bytes_store', full_name='hotbox.DatumProto.sparse_bytes_store', index=5,
      number=6, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[_DATUMPROTO_SPARSECATSTOREENTRY, _DATUMPROTO_SPARSENUMSTOREENTRY, _DATUMPROTO_SPARSEBYTESSTOREENTRY, ],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=146,
  serialized_end=604,
)


_DATUMPROTOOFFSET = _descriptor.Descriptor(
  name='DatumProtoOffset',
  full_name='hotbox.DatumProtoOffset',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='offsets', full_name='hotbox.DatumProtoOffset.offsets', index=0,
      number=1, type=3, cpp_type=2, label=3,
      has_default_value=False, default_value=[],
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
  serialized_start=606,
  serialized_end=641,
)


_FEATUREFAMILYPROTO_NAMETOFAMILYIDXENTRY = _descriptor.Descriptor(
  name='NameToFamilyIdxEntry',
  full_name='hotbox.FeatureFamilyProto.NameToFamilyIdxEntry',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='key', full_name='hotbox.FeatureFamilyProto.NameToFamilyIdxEntry.key', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='value', full_name='hotbox.FeatureFamilyProto.NameToFamilyIdxEntry.value', index=1,
      number=2, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=_descriptor._ParseOptions(descriptor_pb2.MessageOptions(), b'8\001'),
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=799,
  serialized_end=853,
)

_FEATUREFAMILYPROTO = _descriptor.Descriptor(
  name='FeatureFamilyProto',
  full_name='hotbox.FeatureFamilyProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='family_name', full_name='hotbox.FeatureFamilyProto.family_name', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='name_to_family_idx', full_name='hotbox.FeatureFamilyProto.name_to_family_idx', index=1,
      number=2, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='features', full_name='hotbox.FeatureFamilyProto.features', index=2,
      number=3, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[_FEATUREFAMILYPROTO_NAMETOFAMILYIDXENTRY, ],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=644,
  serialized_end=853,
)


_SCHEMACONFIG = _descriptor.Descriptor(
  name='SchemaConfig',
  full_name='hotbox.SchemaConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='int_label', full_name='hotbox.SchemaConfig.int_label', index=0,
      number=1, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='use_dense_weight', full_name='hotbox.SchemaConfig.use_dense_weight', index=1,
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
  serialized_start=855,
  serialized_end=914,
)


_SCHEMAPROTO_FAMILIESENTRY = _descriptor.Descriptor(
  name='FamiliesEntry',
  full_name='hotbox.SchemaProto.FamiliesEntry',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='key', full_name='hotbox.SchemaProto.FamiliesEntry.key', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='value', full_name='hotbox.SchemaProto.FamiliesEntry.value', index=1,
      number=2, type=11, cpp_type=10, label=1,
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
  options=_descriptor._ParseOptions(descriptor_pb2.MessageOptions(), b'8\001'),
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1076,
  serialized_end=1151,
)

_SCHEMAPROTO = _descriptor.Descriptor(
  name='SchemaProto',
  full_name='hotbox.SchemaProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='version', full_name='hotbox.SchemaProto.version', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='families', full_name='hotbox.SchemaProto.families', index=1,
      number=2, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='output_families', full_name='hotbox.SchemaProto.output_families', index=2,
      number=3, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='append_offset', full_name='hotbox.SchemaProto.append_offset', index=3,
      number=5, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[_SCHEMAPROTO_FAMILIESENTRY, ],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=917,
  serialized_end=1151,
)


_OSCHEMAPROTO = _descriptor.Descriptor(
  name='OSchemaProto',
  full_name='hotbox.OSchemaProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='feature_names', full_name='hotbox.OSchemaProto.feature_names', index=0,
      number=1, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='family_names', full_name='hotbox.OSchemaProto.family_names', index=1,
      number=2, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='family_offsets', full_name='hotbox.OSchemaProto.family_offsets', index=2,
      number=3, type=3, cpp_type=2, label=3,
      has_default_value=False, default_value=[],
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
  serialized_start=1153,
  serialized_end=1236,
)

_FEATURE.fields_by_name['store_type'].enum_type = _FEATURESTORETYPE
_DATUMPROTO_SPARSECATSTOREENTRY.containing_type = _DATUMPROTO
_DATUMPROTO_SPARSENUMSTOREENTRY.containing_type = _DATUMPROTO
_DATUMPROTO_SPARSEBYTESSTOREENTRY.containing_type = _DATUMPROTO
_DATUMPROTO.fields_by_name['sparse_cat_store'].message_type = _DATUMPROTO_SPARSECATSTOREENTRY
_DATUMPROTO.fields_by_name['sparse_num_store'].message_type = _DATUMPROTO_SPARSENUMSTOREENTRY
_DATUMPROTO.fields_by_name['sparse_bytes_store'].message_type = _DATUMPROTO_SPARSEBYTESSTOREENTRY
_FEATUREFAMILYPROTO_NAMETOFAMILYIDXENTRY.containing_type = _FEATUREFAMILYPROTO
_FEATUREFAMILYPROTO.fields_by_name['name_to_family_idx'].message_type = _FEATUREFAMILYPROTO_NAMETOFAMILYIDXENTRY
_FEATUREFAMILYPROTO.fields_by_name['features'].message_type = _FEATURE
_SCHEMAPROTO_FAMILIESENTRY.fields_by_name['value'].message_type = _FEATUREFAMILYPROTO
_SCHEMAPROTO_FAMILIESENTRY.containing_type = _SCHEMAPROTO
_SCHEMAPROTO.fields_by_name['families'].message_type = _SCHEMAPROTO_FAMILIESENTRY
_SCHEMAPROTO.fields_by_name['append_offset'].message_type = _DATUMPROTOOFFSET
DESCRIPTOR.message_types_by_name['Feature'] = _FEATURE
DESCRIPTOR.message_types_by_name['DatumProto'] = _DATUMPROTO
DESCRIPTOR.message_types_by_name['DatumProtoOffset'] = _DATUMPROTOOFFSET
DESCRIPTOR.message_types_by_name['FeatureFamilyProto'] = _FEATUREFAMILYPROTO
DESCRIPTOR.message_types_by_name['SchemaConfig'] = _SCHEMACONFIG
DESCRIPTOR.message_types_by_name['SchemaProto'] = _SCHEMAPROTO
DESCRIPTOR.message_types_by_name['OSchemaProto'] = _OSCHEMAPROTO
DESCRIPTOR.enum_types_by_name['FeatureType'] = _FEATURETYPE
DESCRIPTOR.enum_types_by_name['OutputStoreType'] = _OUTPUTSTORETYPE
DESCRIPTOR.enum_types_by_name['FeatureIndexType'] = _FEATUREINDEXTYPE
DESCRIPTOR.enum_types_by_name['FeatureStoreType'] = _FEATURESTORETYPE

Feature = _reflection.GeneratedProtocolMessageType('Feature', (_message.Message,), dict(
  DESCRIPTOR = _FEATURE,
  __module__ = 'schema.proto.schema_pb2'
  # @@protoc_insertion_point(class_scope:hotbox.Feature)
  ))
_sym_db.RegisterMessage(Feature)

DatumProto = _reflection.GeneratedProtocolMessageType('DatumProto', (_message.Message,), dict(

  SparseCatStoreEntry = _reflection.GeneratedProtocolMessageType('SparseCatStoreEntry', (_message.Message,), dict(
    DESCRIPTOR = _DATUMPROTO_SPARSECATSTOREENTRY,
    __module__ = 'schema.proto.schema_pb2'
    # @@protoc_insertion_point(class_scope:hotbox.DatumProto.SparseCatStoreEntry)
    ))
  ,

  SparseNumStoreEntry = _reflection.GeneratedProtocolMessageType('SparseNumStoreEntry', (_message.Message,), dict(
    DESCRIPTOR = _DATUMPROTO_SPARSENUMSTOREENTRY,
    __module__ = 'schema.proto.schema_pb2'
    # @@protoc_insertion_point(class_scope:hotbox.DatumProto.SparseNumStoreEntry)
    ))
  ,

  SparseBytesStoreEntry = _reflection.GeneratedProtocolMessageType('SparseBytesStoreEntry', (_message.Message,), dict(
    DESCRIPTOR = _DATUMPROTO_SPARSEBYTESSTOREENTRY,
    __module__ = 'schema.proto.schema_pb2'
    # @@protoc_insertion_point(class_scope:hotbox.DatumProto.SparseBytesStoreEntry)
    ))
  ,
  DESCRIPTOR = _DATUMPROTO,
  __module__ = 'schema.proto.schema_pb2'
  # @@protoc_insertion_point(class_scope:hotbox.DatumProto)
  ))
_sym_db.RegisterMessage(DatumProto)
_sym_db.RegisterMessage(DatumProto.SparseCatStoreEntry)
_sym_db.RegisterMessage(DatumProto.SparseNumStoreEntry)
_sym_db.RegisterMessage(DatumProto.SparseBytesStoreEntry)

DatumProtoOffset = _reflection.GeneratedProtocolMessageType('DatumProtoOffset', (_message.Message,), dict(
  DESCRIPTOR = _DATUMPROTOOFFSET,
  __module__ = 'schema.proto.schema_pb2'
  # @@protoc_insertion_point(class_scope:hotbox.DatumProtoOffset)
  ))
_sym_db.RegisterMessage(DatumProtoOffset)

FeatureFamilyProto = _reflection.GeneratedProtocolMessageType('FeatureFamilyProto', (_message.Message,), dict(

  NameToFamilyIdxEntry = _reflection.GeneratedProtocolMessageType('NameToFamilyIdxEntry', (_message.Message,), dict(
    DESCRIPTOR = _FEATUREFAMILYPROTO_NAMETOFAMILYIDXENTRY,
    __module__ = 'schema.proto.schema_pb2'
    # @@protoc_insertion_point(class_scope:hotbox.FeatureFamilyProto.NameToFamilyIdxEntry)
    ))
  ,
  DESCRIPTOR = _FEATUREFAMILYPROTO,
  __module__ = 'schema.proto.schema_pb2'
  # @@protoc_insertion_point(class_scope:hotbox.FeatureFamilyProto)
  ))
_sym_db.RegisterMessage(FeatureFamilyProto)
_sym_db.RegisterMessage(FeatureFamilyProto.NameToFamilyIdxEntry)

SchemaConfig = _reflection.GeneratedProtocolMessageType('SchemaConfig', (_message.Message,), dict(
  DESCRIPTOR = _SCHEMACONFIG,
  __module__ = 'schema.proto.schema_pb2'
  # @@protoc_insertion_point(class_scope:hotbox.SchemaConfig)
  ))
_sym_db.RegisterMessage(SchemaConfig)

SchemaProto = _reflection.GeneratedProtocolMessageType('SchemaProto', (_message.Message,), dict(

  FamiliesEntry = _reflection.GeneratedProtocolMessageType('FamiliesEntry', (_message.Message,), dict(
    DESCRIPTOR = _SCHEMAPROTO_FAMILIESENTRY,
    __module__ = 'schema.proto.schema_pb2'
    # @@protoc_insertion_point(class_scope:hotbox.SchemaProto.FamiliesEntry)
    ))
  ,
  DESCRIPTOR = _SCHEMAPROTO,
  __module__ = 'schema.proto.schema_pb2'
  # @@protoc_insertion_point(class_scope:hotbox.SchemaProto)
  ))
_sym_db.RegisterMessage(SchemaProto)
_sym_db.RegisterMessage(SchemaProto.FamiliesEntry)

OSchemaProto = _reflection.GeneratedProtocolMessageType('OSchemaProto', (_message.Message,), dict(
  DESCRIPTOR = _OSCHEMAPROTO,
  __module__ = 'schema.proto.schema_pb2'
  # @@protoc_insertion_point(class_scope:hotbox.OSchemaProto)
  ))
_sym_db.RegisterMessage(OSchemaProto)


_DATUMPROTO_SPARSECATSTOREENTRY.has_options = True
_DATUMPROTO_SPARSECATSTOREENTRY._options = _descriptor._ParseOptions(descriptor_pb2.MessageOptions(), b'8\001')
_DATUMPROTO_SPARSENUMSTOREENTRY.has_options = True
_DATUMPROTO_SPARSENUMSTOREENTRY._options = _descriptor._ParseOptions(descriptor_pb2.MessageOptions(), b'8\001')
_DATUMPROTO_SPARSEBYTESSTOREENTRY.has_options = True
_DATUMPROTO_SPARSEBYTESSTOREENTRY._options = _descriptor._ParseOptions(descriptor_pb2.MessageOptions(), b'8\001')
_FEATUREFAMILYPROTO_NAMETOFAMILYIDXENTRY.has_options = True
_FEATUREFAMILYPROTO_NAMETOFAMILYIDXENTRY._options = _descriptor._ParseOptions(descriptor_pb2.MessageOptions(), b'8\001')
_SCHEMAPROTO_FAMILIESENTRY.has_options = True
_SCHEMAPROTO_FAMILIESENTRY._options = _descriptor._ParseOptions(descriptor_pb2.MessageOptions(), b'8\001')
# @@protoc_insertion_point(module_scope)
