"""
@generated by mypy-protobuf.  Do not edit manually!
isort:skip_file
"""
import builtins
import caffe2.proto.caffe2_pb2
import google.protobuf.descriptor
import google.protobuf.internal.containers
import google.protobuf.message
import typing
import typing_extensions

DESCRIPTOR: google.protobuf.descriptor.FileDescriptor = ...

class ModelInfo(google.protobuf.message.Message):
    DESCRIPTOR: google.protobuf.descriptor.Descriptor = ...
    PROJECT_FIELD_NUMBER: int
    MODELCLASS_FIELD_NUMBER: int
    VERSION_FIELD_NUMBER: int
    PREDICTORTYPE_FIELD_NUMBER: int
    MODELID_FIELD_NUMBER: int
    project: typing.Text = ...
    modelClass: typing.Text = ...
    version: typing.Text = ...
    predictorType: typing.Text = ...
    modelId: typing.Text = ...

    def __init__(self,
        *,
        project : typing.Optional[typing.Text] = ...,
        modelClass : typing.Optional[typing.Text] = ...,
        version : typing.Optional[typing.Text] = ...,
        predictorType : typing.Optional[typing.Text] = ...,
        modelId : typing.Optional[typing.Text] = ...,
        ) -> None: ...
    def HasField(self, field_name: typing_extensions.Literal[u"modelClass",b"modelClass",u"modelId",b"modelId",u"predictorType",b"predictorType",u"project",b"project",u"version",b"version"]) -> bool: ...
    def ClearField(self, field_name: typing_extensions.Literal[u"modelClass",b"modelClass",u"modelId",b"modelId",u"predictorType",b"predictorType",u"project",b"project",u"version",b"version"]) -> None: ...
global___ModelInfo = ModelInfo

class BlobsMap(google.protobuf.message.Message):
    DESCRIPTOR: google.protobuf.descriptor.Descriptor = ...
    KEY_FIELD_NUMBER: int
    VALUE_FIELD_NUMBER: int
    key: typing.Text = ...
    value: google.protobuf.internal.containers.RepeatedScalarFieldContainer[typing.Text] = ...

    def __init__(self,
        *,
        key : typing.Optional[typing.Text] = ...,
        value : typing.Optional[typing.Iterable[typing.Text]] = ...,
        ) -> None: ...
    def HasField(self, field_name: typing_extensions.Literal[u"key",b"key"]) -> bool: ...
    def ClearField(self, field_name: typing_extensions.Literal[u"key",b"key",u"value",b"value"]) -> None: ...
global___BlobsMap = BlobsMap

class NetsMap(google.protobuf.message.Message):
    DESCRIPTOR: google.protobuf.descriptor.Descriptor = ...
    KEY_FIELD_NUMBER: int
    VALUE_FIELD_NUMBER: int
    key: typing.Text = ...

    @property
    def value(self) -> caffe2.proto.caffe2_pb2.NetDef: ...

    def __init__(self,
        *,
        key : typing.Optional[typing.Text] = ...,
        value : typing.Optional[caffe2.proto.caffe2_pb2.NetDef] = ...,
        ) -> None: ...
    def HasField(self, field_name: typing_extensions.Literal[u"key",b"key",u"value",b"value"]) -> bool: ...
    def ClearField(self, field_name: typing_extensions.Literal[u"key",b"key",u"value",b"value"]) -> None: ...
global___NetsMap = NetsMap

class PlansMap(google.protobuf.message.Message):
    DESCRIPTOR: google.protobuf.descriptor.Descriptor = ...
    KEY_FIELD_NUMBER: int
    VALUE_FIELD_NUMBER: int
    key: typing.Text = ...

    @property
    def value(self) -> caffe2.proto.caffe2_pb2.PlanDef: ...

    def __init__(self,
        *,
        key : typing.Optional[typing.Text] = ...,
        value : typing.Optional[caffe2.proto.caffe2_pb2.PlanDef] = ...,
        ) -> None: ...
    def HasField(self, field_name: typing_extensions.Literal[u"key",b"key",u"value",b"value"]) -> bool: ...
    def ClearField(self, field_name: typing_extensions.Literal[u"key",b"key",u"value",b"value"]) -> None: ...
global___PlansMap = PlansMap

class StringMap(google.protobuf.message.Message):
    DESCRIPTOR: google.protobuf.descriptor.Descriptor = ...
    KEY_FIELD_NUMBER: int
    VALUE_FIELD_NUMBER: int
    key: typing.Text = ...
    value: typing.Text = ...

    def __init__(self,
        *,
        key : typing.Optional[typing.Text] = ...,
        value : typing.Optional[typing.Text] = ...,
        ) -> None: ...
    def HasField(self, field_name: typing_extensions.Literal[u"key",b"key",u"value",b"value"]) -> bool: ...
    def ClearField(self, field_name: typing_extensions.Literal[u"key",b"key",u"value",b"value"]) -> None: ...
global___StringMap = StringMap

class MetaNetDef(google.protobuf.message.Message):
    DESCRIPTOR: google.protobuf.descriptor.Descriptor = ...
    BLOBS_FIELD_NUMBER: int
    NETS_FIELD_NUMBER: int
    MODELINFO_FIELD_NUMBER: int
    PLANS_FIELD_NUMBER: int
    APPLICATIONSPECIFICINFO_FIELD_NUMBER: int
    BLOBSORDER_FIELD_NUMBER: int
    PRELOADBLOBS_FIELD_NUMBER: int
    TENSORBOUNDSHAPES_FIELD_NUMBER: int
    REQUESTONLYEMBEDDINGS_FIELD_NUMBER: int
    AOTCONFIG_FIELD_NUMBER: int
    blobsOrder: google.protobuf.internal.containers.RepeatedScalarFieldContainer[typing.Text] = ...
    preLoadBlobs: google.protobuf.internal.containers.RepeatedScalarFieldContainer[typing.Text] = ...
    requestOnlyEmbeddings: google.protobuf.internal.containers.RepeatedScalarFieldContainer[typing.Text] = ...

    @property
    def blobs(self) -> google.protobuf.internal.containers.RepeatedCompositeFieldContainer[global___BlobsMap]: ...

    @property
    def nets(self) -> google.protobuf.internal.containers.RepeatedCompositeFieldContainer[global___NetsMap]: ...

    @property
    def modelInfo(self) -> global___ModelInfo: ...

    @property
    def plans(self) -> google.protobuf.internal.containers.RepeatedCompositeFieldContainer[global___PlansMap]: ...

    @property
    def applicationSpecificInfo(self) -> google.protobuf.internal.containers.RepeatedCompositeFieldContainer[global___StringMap]: ...

    @property
    def tensorBoundShapes(self) -> caffe2.proto.caffe2_pb2.TensorBoundShapes: ...

    @property
    def aotConfig(self) -> caffe2.proto.caffe2_pb2.AOTConfig: ...

    def __init__(self,
        *,
        blobs : typing.Optional[typing.Iterable[global___BlobsMap]] = ...,
        nets : typing.Optional[typing.Iterable[global___NetsMap]] = ...,
        modelInfo : typing.Optional[global___ModelInfo] = ...,
        plans : typing.Optional[typing.Iterable[global___PlansMap]] = ...,
        applicationSpecificInfo : typing.Optional[typing.Iterable[global___StringMap]] = ...,
        blobsOrder : typing.Optional[typing.Iterable[typing.Text]] = ...,
        preLoadBlobs : typing.Optional[typing.Iterable[typing.Text]] = ...,
        tensorBoundShapes : typing.Optional[caffe2.proto.caffe2_pb2.TensorBoundShapes] = ...,
        requestOnlyEmbeddings : typing.Optional[typing.Iterable[typing.Text]] = ...,
        aotConfig : typing.Optional[caffe2.proto.caffe2_pb2.AOTConfig] = ...,
        ) -> None: ...
    def HasField(self, field_name: typing_extensions.Literal[u"aotConfig",b"aotConfig",u"modelInfo",b"modelInfo",u"tensorBoundShapes",b"tensorBoundShapes"]) -> bool: ...
    def ClearField(self, field_name: typing_extensions.Literal[u"aotConfig",b"aotConfig",u"applicationSpecificInfo",b"applicationSpecificInfo",u"blobs",b"blobs",u"blobsOrder",b"blobsOrder",u"modelInfo",b"modelInfo",u"nets",b"nets",u"plans",b"plans",u"preLoadBlobs",b"preLoadBlobs",u"requestOnlyEmbeddings",b"requestOnlyEmbeddings",u"tensorBoundShapes",b"tensorBoundShapes"]) -> None: ...
global___MetaNetDef = MetaNetDef
