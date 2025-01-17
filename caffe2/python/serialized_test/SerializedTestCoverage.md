# Serialized Test Coverage Report
This is an automatically generated file. Please see `caffe2/python/serialized_test/README.md` for details. In the case of merge conflicts, please rebase and regenerate.
## Summary
Serialized tests have covered 220/852 (25.8%) operators

## Not covered operators
<details>
<summary>There are 632 not covered operators</summary>

* APMeter
* ATen
* Abs
* AbsGradient
* Accumulate
* AccumulateHistogram
* Accuracy
* Adam
* Add
* AddFakeFp16
* AddGradient
* Alias
* AliasWithName
* Allgather
* Allreduce
* And
* Append
* Assert
* AtomicAppend
* AtomicFetchAdd
* AtomicFetchAdd64
* AtomicIter
* AveragePool
* AveragePool1D
* AveragePool1DGradient
* AveragePool2D
* AveragePool2DGradient
* AveragePool3D
* AveragePool3DGradient
* AveragePoolGradient
* AveragePut
* BRGNCHWCToPackedInt8BGRAStylizerDeprocess
* Barrier
* BatchMatMulFP16Acc16Fake
* BatchMatMulFP16Acc32Fake
* BatchMatMulFP16Fake
* BatchPermutation
* BatchPermutationGradient
* BatchToSpace
* BisectPercentile
* BitwiseAnd
* BitwiseOr
* BitwiseXor
* BooleanMaskGradient
* BooleanMaskLengths
* Broadcast
* Bucketize
* ByteWeightDequant
* Cast
* Cbrt
* CbrtGradient
* CheckAtomicBool
* CheckCounterDone
* CheckDatasetConsistency
* Checkpoint
* CloneCommonWorld
* CloseBlobsQueue
* CloseRebatchingQueue
* Col2Im
* CollectRpnProposals
* CollectTensor
* ComputeOffset
* ConcatBatchMatMulBatchGatherOp
* ConcatTensorVector
* ConditionalSetAtomicBool
* Conv1D
* Conv1DGradient
* Conv2D
* Conv2DGradient
* Conv3D
* Conv3DGradient
* ConvRelu
* ConvTranspose
* ConvTransposeGradient
* Copy
* CopyCPUToGPU
* CopyFromCPUInput
* CopyGPUToCPU
* CopyOnDeviceLike
* CopyRowsToTensor
* CopyRowsToTensorGradient
* Cos
* CosGradient
* CosineSimilarity
* CosineSimilarityGradient
* CountDown
* CountUp
* Crash
* CreateAtomicBool
* CreateBlobsQueue
* CreateBlobsQueueDB
* CreateCommonWorld
* CreateCounter
* CreateDB
* CreateMap
* CreateMutex
* CreateRebatchingQueue
* CreateScope
* CreateTensorVector
* CreateTextFileReader
* CreateTreeCursor
* CrossEntropy
* CrossEntropyGradient
* Cube
* CubeGradient
* DBExists
* DataCouple
* DeformConv
* DeformConvGradient
* DenseVectorToIdList
* DepthConcat
* DepthSplit
* DequeueBlobs
* DequeueRebatchingQueue
* DestroyCommonWorld
* DistributeFpnProposals
* Div
* DivFakeFp16
* DivGradient
* Do
* DotProductWithPadding
* DotProductWithPaddingGradient
* EQ
* EnforceFinite
* EnqueueBlobs
* EnqueueRebatchingQueue
* EnsureCPUOutput
* EnsureClipped
* EnsureDense
* Equalizer
* Exp
* ExpandDims
* FCFp16X
* FCGradient_Decomp
* FCGradient_Prune
* FCTransposed
* FCTransposedGradient
* FC_Decomp
* FC_Prune
* FC_Sparse
* FP16MomentumSGDUpdate
* FP32MomentumSGDUpdate
* FP32ToFP16Fake
* FP32ToFP16FakeNoSubnormal
* Fail
* FbFCPacked
* FbGemmPack
* FbGemmPackTranspose
* FeedBlob
* FilterExampleIds
* FilterSparseLabels
* Flatten
* FlattenToVec
* Float16ConstantFill
* Float16UniformFill
* FloatToFused2BitFakeRowwiseQuantized
* FloatToFused2BitRowwiseQuantized
* FloatToFused4BitFakeRowwiseQuantized
* FloatToFused4BitRowwiseQuantized
* FloatToFused8BitRowwiseQuantized
* FloatToFused8BitRowwiseQuantizedHalfScaleBias
* FloatToFusedRandRowwiseQuantized
* FloatToHalf
* FloatToRowwiseQuantized8Bits
* Fp16FC
* Fp16FCAcc16
* Fp16FCAcc16NNPI
* Fp16FCAcc32
* Fp16FCAcc32NNPI
* Free
* Ftrl
* FunHash
* FunHashGradient
* Fused2BitRowwiseQuantizedToFloat
* Fused2BitRowwiseQuantizedToHalf
* Fused4BitRowwiseQuantizedToFloat
* Fused4BitRowwiseQuantizedToHalf
* Fused8BitRowwiseQuantizedHalfScaleBiasToFloat
* Fused8BitRowwiseQuantizedHalfScaleBiasToHalfFloat
* Fused8BitRowwiseQuantizedToFloat
* Fused8BitRowwiseQuantizedToHalfFloat
* FusedRandRowwiseQuantizedToFloat
* GE
* GFtrl
* GT
* GatherByKey
* GatherFused8BitRowwise
* GaussianFill
* Gelu
* GeluGradient
* GenerateProposals
* GenerateProposalsCPP
* GetAllBlobNames
* GetCursorOffset
* GetGPUMemoryUsage
* GivenTensorBoolFill
* GivenTensorByteStringToUInt8Fill
* GivenTensorDoubleFill
* GivenTensorFill
* GivenTensorInt16Fill
* GivenTensorInt64Fill
* GivenTensorIntFill
* GivenTensorStringFill
* HSoftmax
* HSoftmaxGradient
* HSoftmaxSearch
* HalfFloatToFused8BitRowwiseQuantized
* HalfFloatToFused8BitRowwiseQuantizedHalfScaleBias
* HalfToFloat
* HalfToFused2BitFakeRowwiseQuantized
* HalfToFused2BitRowwiseQuantized
* HalfToFused4BitFakeRowwiseQuantized
* HalfToFused4BitRowwiseQuantized
* HardSigmoid
* HardSigmoidGradient
* HasElements
* HasScope
* HeatmapMaxKeypoint
* Histogram
* HuffmanTreeHierarchy
* If
* Im2Col
* ImageInput
* IncrementPut
* IndexFreeze
* IndexGet
* IndexLoad
* IndexSize
* IndexStore
* InferenceLSTM
* Int8Add
* Int8AddRelu
* Int8AveragePool
* Int8AveragePoolRelu
* Int8ChannelShuffle
* Int8Concat
* Int8Conv
* Int8ConvRelu
* Int8ConvTranspose
* Int8Dequantize
* Int8DequantizeNNPI
* Int8FC
* Int8FCFakeAcc32NNPI
* Int8Flatten
* Int8GivenIntTensorFill
* Int8GivenTensorFill
* Int8LeakyRelu
* Int8MaxPool
* Int8MaxPoolRelu
* Int8Quantize
* Int8QuantizeNNPI
* Int8Relu
* Int8Reshape
* Int8ResizeNearest
* Int8RoIAlign
* Int8Sigmoid
* Int8Slice
* Int8Softmax
* Int8Sum
* Int8SumRelu
* Int8Transpose
* IntIndexCreate
* IsEmpty
* IsNaN
* Iter
* KeySplit
* KeyValueToMap
* L1Distance
* L1DistanceGradient
* LC1D
* LC1DGradient
* LC2D
* LC2DGradient
* LC3D
* LC3DGradient
* LE
* LRN
* LRNGradient
* LSTMUnit
* LSTMUnitGradient
* LT
* LabelCrossEntropy
* LabelCrossEntropyGradient
* LambdaRankNdcg
* LambdaRankNdcgGradient
* Lars
* LastNWindowCollector
* LayerNorm
* LayerNormFakeFP16
* LengthsIndicesInGradientMeanGradient
* LengthsIndicesInGradientSumGradient
* LengthsMax
* LengthsMaxWithMainInputAndForwardOutputGradient
* LengthsMean
* LengthsMeanGradient
* LengthsPartition
* LengthsSumGradient
* LengthsToSegmentIds
* LengthsToShape
* LengthsToWeights
* LengthsWeightedSum
* LengthsWeightedSumGradient
* LengthsWeightedSumWithMainInputGradient
* Load
* LogFatal
* Logit
* LogitGradient
* LongIndexCreate
* LpNorm
* LpNormGradient
* LpPool
* LpPoolGradient
* MSRAFill
* MakeTwoClass
* MakeTwoClassGradient
* MapToKeyValue
* MaxPool
* MaxPool1D
* MaxPool1DGradient
* MaxPool2D
* MaxPool2DGradient
* MaxPool3D
* MaxPool3DGradient
* MaxPoolGradient
* MaxPoolWithIndex
* MaxPoolWithIndexGradient
* MergeDim
* MergeExampleIds
* MergeMultiListFeatureTensors
* MergeMultiListFeatureTensorsGradient
* MergeMultiMapFeatureTensors
* MergeMultiMapFeatureTensorsGradient
* MergeMultiScalarFeatureTensors
* MergeMultiScalarFeatureTensorsGradient
* MergeSingleListFeatureTensors
* MergeSingleListFeatureTensorsGradient
* MergeSingleMapFeatureTensors
* MergeSingleMapFeatureTensorsGradient
* MergeSingleScalarFeatureTensors
* MergeSingleScalarFeatureTensorsGradient
* Mod
* MomentumSGDUpdate
* MulFakeFp16
* MulGradient
* MultiClassAccuracy
* NCHW2NHWC
* NE
* NGramFromCategorical
* NHWC2NCHW
* Normalize
* NormalizeGradient
* NormalizeL1
* NormalizePlanarYUV
* Not
* Onnxifi
* Or
* PRelu
* PReluGradient
* PackRecords
* PackedInt8BGRANHWCToNCHWCStylizerPreprocess
* PadEmptySamples
* Partition
* Percentile
* Perplexity
* PrependDim
* Print
* Python
* PythonDLPack
* PythonDLPackGradient
* PythonGradient
* QuantDecode
* QuantDecodeGradient
* QuantDecompZstd
* Quantile
* RMACRegions
* Range
* RangeFill
* ReadNextBatch
* ReadRandomBatch
* ReceiveTensor
* Reciprocal
* ReciprocalGradient
* RecurrentNetworkBlobFetcher
* Reduce
* ReduceBackSum
* ReduceBackSumGradient
* ReduceFrontWeightedSum
* ReduceFrontWeightedSumGradient
* ReduceL1
* ReduceL1Gradient
* ReduceScatter
* ReduceSum
* ReduceSumGradient
* ReduceTailSum
* ReluFakeFp16
* RemovePadding
* ReplaceNaN
* ReservoirSampling
* ResetCounter
* ResetCursor
* Reshape
* ResizeLike
* ResizeNearest
* ResizeNearest3D
* ResizeNearest3DGradient
* ResizeNearestGradient
* RetrieveCount
* RmsProp
* RoIAlign
* RoIAlignGradient
* RoIAlignRotated
* RoIAlignRotatedGradient
* RoIPool
* RoIPoolGradient
* RowMul
* RowWiseCounter
* RowWiseSparseAdagradFusedWithSparseLengthsSumGradient
* RowWiseSparseAdagradFusedWithSparseLengthsWeightedSumGradient
* RowWiseSparseAdagradFusedWithSparseLengthsWeightedSumGradientApprox
* RowWiseSparseAdam
* Rowwise8BitQuantizedToFloat
* Rsqrt
* RsqrtGradient
* SafeDequeueBlobs
* SafeEnqueueBlobs
* Save
* Scale
* ScaleBlobs
* Scatter
* ScriptModule
* ScriptModuleLoad
* SegmentIdsToLengths
* SegmentIdsToRanges
* SendTensor
* Shape
* Sigmoid
* SigmoidCrossEntropyWithLogits
* SigmoidCrossEntropyWithLogitsGradient
* SigmoidFakeFp16
* SigmoidFakeFp16NNPI
* SigmoidGradient
* Sin
* SinGradient
* Snapshot
* Softplus
* SoftplusGradient
* Softsign
* SoftsignGradient
* SortAndShuffle
* SortedSegmentMean
* SortedSegmentMeanGradient
* SortedSegmentRangeLogMeanExp
* SortedSegmentRangeLogMeanExpGradient
* SortedSegmentRangeLogSumExp
* SortedSegmentRangeLogSumExpGradient
* SortedSegmentRangeMax
* SortedSegmentRangeMaxGradient
* SortedSegmentRangeMean
* SortedSegmentRangeMeanGradient
* SortedSegmentRangeSum
* SortedSegmentRangeSumGradient
* SortedSegmentSum
* SortedSegmentSumGradient
* SortedSegmentWeightedSum
* SortedSegmentWeightedSumGradient
* SpaceToBatch
* SparseAdagradFusedWithSparseLengthsSumGradient
* SparseAdagradFusedWithSparseLengthsWeightedSumGradient
* SparseAdagradFusedWithSparseLengthsWeightedSumGradientApprox
* SparseAdam
* SparseDropoutWithReplacement
* SparseFtrl
* SparseFunHash
* SparseFunHashGradient
* SparseLabelSplit
* SparseLabelSplitGradient
* SparseLabelToBool
* SparseLabelToDense
* SparseLengthsIndicesInGradientMeanGradient
* SparseLengthsIndicesInGradientSumGradient
* SparseLengthsIndicesInGradientWeightedSumGradient
* SparseLengthsIndicesInGradientWeightedSumWithMainInputGradient
* SparseLengthsMean
* SparseLengthsMean2BitRowwiseSparse
* SparseLengthsMean4BitRowwiseSparse
* SparseLengthsMean8BitRowwiseSparse
* SparseLengthsMean8BitsRowwise
* SparseLengthsMeanFakeFP16
* SparseLengthsMeanFakeFP16AccFP16
* SparseLengthsMeanFakeFP16EmbeddingOnly
* SparseLengthsMeanFused2BitRowwise
* SparseLengthsMeanFused4BitRowwise
* SparseLengthsMeanFused8BitRowwise
* SparseLengthsMeanFused8BitRowwiseFakeFP16
* SparseLengthsMeanFused8BitRowwiseFakeFP16AccFP16
* SparseLengthsMeanGradient
* SparseLengthsPositionalWeightedSum
* SparseLengthsSum
* SparseLengthsSum2BitRowwiseSparse
* SparseLengthsSum4BitRowwiseSparse
* SparseLengthsSum8BitRowwiseSparse
* SparseLengthsSum8BitsRowwise
* SparseLengthsSumFakeFP16
* SparseLengthsSumFakeFP16AccFP16
* SparseLengthsSumFakeFP16EmbeddingOnly
* SparseLengthsSumFused2BitRowwise
* SparseLengthsSumFused4BitRowwise
* SparseLengthsSumFused4BitRowwiseFakeFP16EmbeddingOnly
* SparseLengthsSumFused4BitRowwiseFakeFP16NNPI
* SparseLengthsSumFused8BitRowwise
* SparseLengthsSumFused8BitRowwiseFakeFP16
* SparseLengthsSumFused8BitRowwiseFakeFP16AccFP16
* SparseLengthsSumFused8BitRowwiseFakeFP16AccInvScaleFP16
* SparseLengthsSumFused8BitRowwiseFakeFP16EmbeddingOnly
* SparseLengthsSumFused8BitRowwiseFakeFP16NNPI
* SparseLengthsSumFused8BitRowwiseFakeFP32NNPI
* SparseLengthsSumGradient
* SparseLengthsSumSparseLookup
* SparseLengthsWeightedMean8BitsRowwise
* SparseLengthsWeightedSum
* SparseLengthsWeightedSum2BitRowwiseSparse
* SparseLengthsWeightedSum4BitRowwiseSparse
* SparseLengthsWeightedSum8BitRowwiseSparse
* SparseLengthsWeightedSum8BitsRowwise
* SparseLengthsWeightedSumFakeFP16
* SparseLengthsWeightedSumFakeFP16AccFP16
* SparseLengthsWeightedSumFakeFP16EmbeddingOnly
* SparseLengthsWeightedSumFused2BitRowwise
* SparseLengthsWeightedSumFused4BitRowwise
* SparseLengthsWeightedSumFused4BitRowwiseFakeFP16EmbeddingOnly
* SparseLengthsWeightedSumFused4BitRowwiseFakeFP16NNPI
* SparseLengthsWeightedSumFused8BitRowwise
* SparseLengthsWeightedSumFused8BitRowwiseFakeFP16
* SparseLengthsWeightedSumFused8BitRowwiseFakeFP16AccFP16
* SparseLengthsWeightedSumFused8BitRowwiseFakeFP16AccInvScaleFP16
* SparseLengthsWeightedSumFused8BitRowwiseFakeFP16EmbeddingOnly
* SparseLengthsWeightedSumFused8BitRowwiseFakeFP16NNPI
* SparseLengthsWeightedSumFused8BitRowwiseFakeFP32NNPI
* SparseLengthsWeightedSumGradient
* SparseLengthsWeightedSumWithMainInputGradient
* SparseLpRegularizer
* SparseMatrixReshape
* SparseNormalize
* SparseSortedSegmentMean
* SparseSortedSegmentMeanGradient
* SparseSortedSegmentSum
* SparseSortedSegmentSumGradient
* SparseSortedSegmentWeightedSum
* SparseSortedSegmentWeightedSumGradient
* SparseStorm
* SparseToDense
* SparseToDenseMask
* SparseToDenseMaskGradient
* SparseUnsortedSegmentMean
* SparseUnsortedSegmentMeanGradient
* SparseUnsortedSegmentSum
* SparseUnsortedSegmentSumGradient
* SparseUnsortedSegmentWeightedSum
* SparseUnsortedSegmentWeightedSumGradient
* SpatialBNFakeFp16NNPI
* SpatialBNFakeLoweredFp16NNPI
* SpatialBNRelu
* Sqr
* SqrFakeFp16
* Sqrt
* SquaredL2Distance
* SquaredL2DistanceGradient
* Squeeze
* StatRegistryCreate
* StatRegistryExport
* StatRegistryUpdate
* StdDevPut
* StopGradient
* Storm
* StringIndexCreate
* StringJoin
* StringPrefix
* StringSuffix
* StumpFunc
* StumpFuncIndex
* SubFakeFp16
* SubGradient
* SumFakeFp16
* SumInt
* SumRelu
* Summarize
* SwapBestPath
* Swish
* SwishGradient
* TT
* TTContraction
* TTContractionGradient
* TTLinearGradient
* TTPad
* TTPadGradient
* TanhFakeFp16
* TanhFakeFp16NNPI
* TensorProtosDBInput
* TensorVectorSize
* TextFileReaderRead
* ThrowChildThreadException
* ThrowException
* TimerBegin
* TimerEnd
* TimerGet
* TimerGetAndEnd
* TrimDataset
* UnPackRecords
* UniformFill
* UniformIntFill
* UniqueUniformFill
* UnsortedSegmentMean
* UnsortedSegmentMeanGradient
* UnsortedSegmentSum
* UnsortedSegmentSumGradient
* UnsortedSegmentWeightedSum
* UnsortedSegmentWeightedSumGradient
* VariableLengthSequencePadding
* VideoInput
* ViterbiPath
* WallClockTime
* WeightScale
* WeightedMultiSampling
* WeightedSample
* WeightedSampleDequeueBlobs
* WeightedSigmoidCrossEntropyWithLogits
* WeightedSigmoidCrossEntropyWithLogitsGradient
* While
* XavierFill
* Xor
* YellowFin
* ZeroGradient
</details>

## Covered operators
<details>
<summary>There are 220 covered operators</summary>

* Acos
* AcosGradient
* Adadelta
* Adagrad
* AddPadding
* AffineChannel
* AffineChannelGradient
* ArgMax
* ArgMin
* Asin
* AsinGradient
* Atan
* AtanGradient
* AveragedLoss
* AveragedLossGradient
* BBoxTransform
* BatchBoxCox
* BatchBucketOneHot
* BatchBucketize
* BatchDenseToSparse
* BatchGather
* BatchGatherGradient
* BatchMatMul
* BatchMoments
* BatchMomentsGradient
* BatchOneHot
* BatchSparseToDense
* BernoulliJSD
* BernoulliJSDGradient
* BooleanMask
* BooleanUnmask
* BoxWithNMSLimit
* CTCBeamSearchDecoder
* CTCGreedyDecoder
* Ceil
* ChannelBackpropStats
* ChannelShuffle
* ChannelShuffleGradient
* ChannelStats
* Clip
* ClipGradient
* ClipTensorByScaling
* CollectAndDistributeFpnRpnProposals
* ColwiseMax
* ColwiseMaxGradient
* Concat
* Conditional
* ConstantFill
* Conv
* ConvGradient
* Cosh
* CoshGradient
* CosineEmbeddingCriterion
* CosineEmbeddingCriterionGradient
* DiagonalFill
* DotProduct
* DotProductGradient
* Dropout
* DropoutGrad
* ElementwiseLinear
* ElementwiseLinearGradient
* Elu
* EluGradient
* Erf
* ErfGradient
* Expand
* ExpandGradient
* FC
* FCGradient
* Find
* FindDuplicateElements
* FlexibleTopK
* FlexibleTopKGradient
* Floor
* GRUUnit
* GRUUnitGradient
* Gather
* GatherPadding
* GatherRanges
* GatherRangesToDense
* Glu
* GroupNorm
* GroupNormGradient
* IndexHash
* InstanceNorm
* InstanceNormGradient
* IntegralImage
* IntegralImageGradient
* IsMemberOf
* LC
* LCGradient
* LayerNormGradient
* LeakyRelu
* LeakyReluGradient
* LearningRate
* LearningRateAdaption
* LengthsGather
* LengthsPad
* LengthsRangeFill
* LengthsSplit
* LengthsSum
* LengthsTile
* LengthsToRanges
* LengthsTopK
* LengthsTopKGradient
* Log
* MarginRankingCriterion
* MarginRankingCriterionGradient
* MatMul
* Max
* MaxGradient
* Mean
* MeanGradient
* MergeIdLists
* Min
* MinGradient
* Moments
* MomentsGradient
* MomentumSGD
* Mul
* NanCheck
* NegateGradient
* Negative
* NumpyTile
* ONNXWhile
* OneHot
* PackRNNSequence
* PackSegments
* PadImage
* PadImageGradient
* PairWiseLoss
* PairWiseLossGradient
* PiecewiseLinearTransform
* Pow
* RecurrentNetwork
* RecurrentNetworkGradient
* ReduceBackMax
* ReduceBackMaxGradient
* ReduceBackMean
* ReduceBackMeanGradient
* ReduceFrontMax
* ReduceFrontMaxGradient
* ReduceFrontMean
* ReduceFrontMeanGradient
* ReduceFrontSum
* ReduceFrontSumGradient
* ReduceL2
* ReduceL2Gradient
* ReduceMax
* ReduceMaxGradient
* ReduceMean
* ReduceMeanGradient
* ReduceMin
* ReduceMinGradient
* Relu
* ReluGradient
* ReluN
* ReluNGradient
* RemoveDataBlocks
* ReversePackedSegs
* RowWiseSparseAdagrad
* RowwiseMax
* RowwiseMaxGradient
* ScatterAssign
* ScatterWeightedSum
* SegmentOneHot
* Selu
* SeluGradient
* SequenceMask
* Sign
* Sinh
* SinhGradient
* SinusoidPositionEncoding
* Size
* Slice
* SliceGradient
* Softmax
* SoftmaxGradient
* SoftmaxWithLoss
* SoftmaxWithLossGradient
* SparseAdadelta
* SparseAdagrad
* SparseMomentumSGDUpdate
* SparseWngrad
* SpatialBN
* SpatialBNGradient
* SpatialSoftmaxWithLoss
* SpatialSoftmaxWithLossGradient
* Split
* SplitByLengths
* SquareRootDivide
* StringEndsWith
* StringStartsWith
* Sub
* Sum
* SumElements
* SumElementsGradient
* SumElementsInt
* SumReduceLike
* SumSqrElements
* Tan
* TanGradient
* Tanh
* TanhGradient
* ThresholdedRelu
* ThresholdedReluGradient
* Tile
* TileGradient
* TopK
* TopKGradient
* Transpose
* Unique
* UnpackRNNSequence
* UnpackSegments
* UpsampleBilinear
* UpsampleBilinearGradient
* WeightedSum
* WeightedSumGradient
* Where
* Wngrad
</details>

## Excluded from coverage statistics
### Schemaless operators
<details>
<summary>There are 3 schemaless operators</summary>

* C10LayerNorm_DontUseThisOpYet
* LengthsSumFakeFp16
* SparseLengthsMax
</details>
