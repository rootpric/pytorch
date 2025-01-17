/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// This file is generated by nnapi/codegen.py
#ifndef _WIN32
#include <dlfcn.h>
#endif
#include <ATen/nnapi/nnapi_wrapper.h>
#include <c10/util/Logging.h>
static int loaded = 0;
static struct nnapi_wrapper nnapi_;
static struct nnapi_wrapper check_nnapi_;
int check__getDeviceCount(uint32_t* numDevices) {
  CAFFE_ENFORCE(nnapi_._getDeviceCount);
  int ret = nnapi_._getDeviceCount(numDevices);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "_getDeviceCount", "failed with error ", ret
  );
  return ret;
}
int check__getDevice(uint32_t devIndex, ANeuralNetworksDevice** device) {
  CAFFE_ENFORCE(nnapi_._getDevice);
  int ret = nnapi_._getDevice(devIndex,device);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "_getDevice", "failed with error ", ret
  );
  return ret;
}
int check_Device_getName(const ANeuralNetworksDevice* device, const char** name) {
  CAFFE_ENFORCE(nnapi_.Device_getName);
  int ret = nnapi_.Device_getName(device,name);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Device_getName", "failed with error ", ret
  );
  return ret;
}
int check_Device_getVersion(const ANeuralNetworksDevice* device, const char** version) {
  CAFFE_ENFORCE(nnapi_.Device_getVersion);
  int ret = nnapi_.Device_getVersion(device,version);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Device_getVersion", "failed with error ", ret
  );
  return ret;
}
int check_Device_getFeatureLevel(const ANeuralNetworksDevice* device, int64_t* featureLevel) {
  CAFFE_ENFORCE(nnapi_.Device_getFeatureLevel);
  int ret = nnapi_.Device_getFeatureLevel(device,featureLevel);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Device_getFeatureLevel", "failed with error ", ret
  );
  return ret;
}
int check_Model_getSupportedOperationsForDevices( const ANeuralNetworksModel* model, const ANeuralNetworksDevice* const* devices, uint32_t numDevices, bool* supportedOps) {
  CAFFE_ENFORCE(nnapi_.Model_getSupportedOperationsForDevices);
  int ret = nnapi_.Model_getSupportedOperationsForDevices(model,devices,numDevices,supportedOps);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Model_getSupportedOperationsForDevices", "failed with error ", ret
  );
  return ret;
}
int check_Compilation_createForDevices(ANeuralNetworksModel* model, const ANeuralNetworksDevice* const* devices, uint32_t numDevices, ANeuralNetworksCompilation** compilation) {
  CAFFE_ENFORCE(nnapi_.Compilation_createForDevices);
  int ret = nnapi_.Compilation_createForDevices(model,devices,numDevices,compilation);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Compilation_createForDevices", "failed with error ", ret
  );
  return ret;
}
int check_Execution_compute(ANeuralNetworksExecution* execution) {
  CAFFE_ENFORCE(nnapi_.Execution_compute);
  int ret = nnapi_.Execution_compute(execution);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Execution_compute", "failed with error ", ret
  );
  return ret;
}
int check_Memory_createFromFd(size_t size, int protect, int fd, size_t offset, ANeuralNetworksMemory** memory) {
  CAFFE_ENFORCE(nnapi_.Memory_createFromFd);
  int ret = nnapi_.Memory_createFromFd(size,protect,fd,offset,memory);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Memory_createFromFd", "failed with error ", ret
  );
  return ret;
}
void check_Memory_free(ANeuralNetworksMemory* memory) {
  CAFFE_ENFORCE(nnapi_.Memory_free);
  nnapi_.Memory_free(memory);
}
int check_Model_create(ANeuralNetworksModel** model) {
  CAFFE_ENFORCE(nnapi_.Model_create);
  int ret = nnapi_.Model_create(model);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Model_create", "failed with error ", ret
  );
  return ret;
}
void check_Model_free(ANeuralNetworksModel* model) {
  CAFFE_ENFORCE(nnapi_.Model_free);
  nnapi_.Model_free(model);
}
int check_Model_finish(ANeuralNetworksModel* model) {
  CAFFE_ENFORCE(nnapi_.Model_finish);
  int ret = nnapi_.Model_finish(model);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Model_finish", "failed with error ", ret
  );
  return ret;
}
int check_Model_addOperand(ANeuralNetworksModel* model, const ANeuralNetworksOperandType* type) {
  CAFFE_ENFORCE(nnapi_.Model_addOperand);
  int ret = nnapi_.Model_addOperand(model,type);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Model_addOperand", "failed with error ", ret
  );
  return ret;
}
int check_Model_setOperandValue(ANeuralNetworksModel* model, int32_t index, const void* buffer, size_t length) {
  CAFFE_ENFORCE(nnapi_.Model_setOperandValue);
  int ret = nnapi_.Model_setOperandValue(model,index,buffer,length);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Model_setOperandValue", "failed with error ", ret
  );
  return ret;
}
int check_Model_setOperandValueFromMemory(ANeuralNetworksModel* model, int32_t index, const ANeuralNetworksMemory* memory, size_t offset, size_t length) {
  CAFFE_ENFORCE(nnapi_.Model_setOperandValueFromMemory);
  int ret = nnapi_.Model_setOperandValueFromMemory(model,index,memory,offset,length);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Model_setOperandValueFromMemory", "failed with error ", ret
  );
  return ret;
}
int check_Model_addOperation(ANeuralNetworksModel* model, ANeuralNetworksOperationType type, uint32_t inputCount, const uint32_t* inputs, uint32_t outputCount, const uint32_t* outputs) {
  CAFFE_ENFORCE(nnapi_.Model_addOperation);
  int ret = nnapi_.Model_addOperation(model,type,inputCount,inputs,outputCount,outputs);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Model_addOperation", "failed with error ", ret
  );
  return ret;
}
int check_Model_identifyInputsAndOutputs(ANeuralNetworksModel* model, uint32_t inputCount, const uint32_t* inputs, uint32_t outputCount, const uint32_t* outputs) {
  CAFFE_ENFORCE(nnapi_.Model_identifyInputsAndOutputs);
  int ret = nnapi_.Model_identifyInputsAndOutputs(model,inputCount,inputs,outputCount,outputs);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Model_identifyInputsAndOutputs", "failed with error ", ret
  );
  return ret;
}
int check_Model_relaxComputationFloat32toFloat16(ANeuralNetworksModel* model, bool allow) {
  CAFFE_ENFORCE(nnapi_.Model_relaxComputationFloat32toFloat16);
  int ret = nnapi_.Model_relaxComputationFloat32toFloat16(model,allow);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Model_relaxComputationFloat32toFloat16", "failed with error ", ret
  );
  return ret;
}
int check_Compilation_create(ANeuralNetworksModel* model, ANeuralNetworksCompilation** compilation) {
  CAFFE_ENFORCE(nnapi_.Compilation_create);
  int ret = nnapi_.Compilation_create(model,compilation);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Compilation_create", "failed with error ", ret
  );
  return ret;
}
void check_Compilation_free(ANeuralNetworksCompilation* compilation) {
  CAFFE_ENFORCE(nnapi_.Compilation_free);
  nnapi_.Compilation_free(compilation);
}
int check_Compilation_setPreference(ANeuralNetworksCompilation* compilation, int32_t preference) {
  CAFFE_ENFORCE(nnapi_.Compilation_setPreference);
  int ret = nnapi_.Compilation_setPreference(compilation,preference);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Compilation_setPreference", "failed with error ", ret
  );
  return ret;
}
int check_Compilation_finish(ANeuralNetworksCompilation* compilation) {
  CAFFE_ENFORCE(nnapi_.Compilation_finish);
  int ret = nnapi_.Compilation_finish(compilation);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Compilation_finish", "failed with error ", ret
  );
  return ret;
}
int check_Execution_create(ANeuralNetworksCompilation* compilation, ANeuralNetworksExecution** execution) {
  CAFFE_ENFORCE(nnapi_.Execution_create);
  int ret = nnapi_.Execution_create(compilation,execution);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Execution_create", "failed with error ", ret
  );
  return ret;
}
void check_Execution_free(ANeuralNetworksExecution* execution) {
  CAFFE_ENFORCE(nnapi_.Execution_free);
  nnapi_.Execution_free(execution);
}
int check_Execution_setInput(ANeuralNetworksExecution* execution, int32_t index, const ANeuralNetworksOperandType* type, const void* buffer, size_t length) {
  CAFFE_ENFORCE(nnapi_.Execution_setInput);
  int ret = nnapi_.Execution_setInput(execution,index,type,buffer,length);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Execution_setInput", "failed with error ", ret
  );
  return ret;
}
int check_Execution_setInputFromMemory(ANeuralNetworksExecution* execution, int32_t index, const ANeuralNetworksOperandType* type, const ANeuralNetworksMemory* memory, size_t offset, size_t length) {
  CAFFE_ENFORCE(nnapi_.Execution_setInputFromMemory);
  int ret = nnapi_.Execution_setInputFromMemory(execution,index,type,memory,offset,length);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Execution_setInputFromMemory", "failed with error ", ret
  );
  return ret;
}
int check_Execution_setOutput(ANeuralNetworksExecution* execution, int32_t index, const ANeuralNetworksOperandType* type, void* buffer, size_t length) {
  CAFFE_ENFORCE(nnapi_.Execution_setOutput);
  int ret = nnapi_.Execution_setOutput(execution,index,type,buffer,length);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Execution_setOutput", "failed with error ", ret
  );
  return ret;
}
int check_Execution_setOutputFromMemory(ANeuralNetworksExecution* execution, int32_t index, const ANeuralNetworksOperandType* type, const ANeuralNetworksMemory* memory, size_t offset, size_t length) {
  CAFFE_ENFORCE(nnapi_.Execution_setOutputFromMemory);
  int ret = nnapi_.Execution_setOutputFromMemory(execution,index,type,memory,offset,length);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Execution_setOutputFromMemory", "failed with error ", ret
  );
  return ret;
}
int check_Execution_startCompute(ANeuralNetworksExecution* execution, ANeuralNetworksEvent** event) {
  CAFFE_ENFORCE(nnapi_.Execution_startCompute);
  int ret = nnapi_.Execution_startCompute(execution,event);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Execution_startCompute", "failed with error ", ret
  );
  return ret;
}
int check_Event_wait(ANeuralNetworksEvent* event) {
  CAFFE_ENFORCE(nnapi_.Event_wait);
  int ret = nnapi_.Event_wait(event);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Event_wait", "failed with error ", ret
  );
  return ret;
}
void check_Event_free(ANeuralNetworksEvent* event) {
  CAFFE_ENFORCE(nnapi_.Event_free);
  nnapi_.Event_free(event);
}
int check_Execution_getOutputOperandRank(ANeuralNetworksExecution* execution, int32_t index, uint32_t* rank) {
  CAFFE_ENFORCE(nnapi_.Execution_getOutputOperandRank);
  int ret = nnapi_.Execution_getOutputOperandRank(execution,index,rank);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Execution_getOutputOperandRank", "failed with error ", ret
  );
  return ret;
}
int check_Execution_getOutputOperandDimensions(ANeuralNetworksExecution* execution, int32_t index, uint32_t* dimensions) {
  CAFFE_ENFORCE(nnapi_.Execution_getOutputOperandDimensions);
  int ret = nnapi_.Execution_getOutputOperandDimensions(execution,index,dimensions);
  // TODO: Maybe add better logging here.
  CAFFE_ENFORCE(
    ret == ANEURALNETWORKS_NO_ERROR,
    "Execution_getOutputOperandDimensions", "failed with error ", ret
  );
  return ret;
}
void nnapi_wrapper_load(struct nnapi_wrapper** nnapi, struct nnapi_wrapper** check_nnapi) {
#ifdef _WIN32
  TORCH_CHECK(false, "Running NNAPI models is not supported on Windows.");
#else
  if (!loaded) {
    // Clear error flag.
    dlerror();
    void* handle = dlopen("libneuralnetworks.so", RTLD_LAZY | RTLD_LOCAL);
    CAFFE_ENFORCE(handle, "Failed to load libneuralnetworks.so ", dlerror());
    *(void**)&nnapi_._getDeviceCount = dlsym(handle, "ANeuralNetworks_getDeviceCount");
    check_nnapi_._getDeviceCount = check__getDeviceCount;
    *(void**)&nnapi_._getDevice = dlsym(handle, "ANeuralNetworks_getDevice");
    check_nnapi_._getDevice = check__getDevice;
    *(void**)&nnapi_.Device_getName = dlsym(handle, "ANeuralNetworksDevice_getName");
    check_nnapi_.Device_getName = check_Device_getName;
    *(void**)&nnapi_.Device_getVersion = dlsym(handle, "ANeuralNetworksDevice_getVersion");
    check_nnapi_.Device_getVersion = check_Device_getVersion;
    *(void**)&nnapi_.Device_getFeatureLevel = dlsym(handle, "ANeuralNetworksDevice_getFeatureLevel");
    check_nnapi_.Device_getFeatureLevel = check_Device_getFeatureLevel;
    *(void**)&nnapi_.Model_getSupportedOperationsForDevices = dlsym(handle, "ANeuralNetworksModel_getSupportedOperationsForDevices");
    check_nnapi_.Model_getSupportedOperationsForDevices = check_Model_getSupportedOperationsForDevices;
    *(void**)&nnapi_.Compilation_createForDevices = dlsym(handle, "ANeuralNetworksCompilation_createForDevices");
    check_nnapi_.Compilation_createForDevices = check_Compilation_createForDevices;
    *(void**)&nnapi_.Execution_compute = dlsym(handle, "ANeuralNetworksExecution_compute");
    check_nnapi_.Execution_compute = check_Execution_compute;
    *(void**)&nnapi_.Memory_createFromFd = dlsym(handle, "ANeuralNetworksMemory_createFromFd");
    check_nnapi_.Memory_createFromFd = check_Memory_createFromFd;
    *(void**)&nnapi_.Memory_free = dlsym(handle, "ANeuralNetworksMemory_free");
    check_nnapi_.Memory_free = check_Memory_free;
    *(void**)&nnapi_.Model_create = dlsym(handle, "ANeuralNetworksModel_create");
    check_nnapi_.Model_create = check_Model_create;
    *(void**)&nnapi_.Model_free = dlsym(handle, "ANeuralNetworksModel_free");
    check_nnapi_.Model_free = check_Model_free;
    *(void**)&nnapi_.Model_finish = dlsym(handle, "ANeuralNetworksModel_finish");
    check_nnapi_.Model_finish = check_Model_finish;
    *(void**)&nnapi_.Model_addOperand = dlsym(handle, "ANeuralNetworksModel_addOperand");
    check_nnapi_.Model_addOperand = check_Model_addOperand;
    *(void**)&nnapi_.Model_setOperandValue = dlsym(handle, "ANeuralNetworksModel_setOperandValue");
    check_nnapi_.Model_setOperandValue = check_Model_setOperandValue;
    *(void**)&nnapi_.Model_setOperandValueFromMemory = dlsym(handle, "ANeuralNetworksModel_setOperandValueFromMemory");
    check_nnapi_.Model_setOperandValueFromMemory = check_Model_setOperandValueFromMemory;
    *(void**)&nnapi_.Model_addOperation = dlsym(handle, "ANeuralNetworksModel_addOperation");
    check_nnapi_.Model_addOperation = check_Model_addOperation;
    *(void**)&nnapi_.Model_identifyInputsAndOutputs = dlsym(handle, "ANeuralNetworksModel_identifyInputsAndOutputs");
    check_nnapi_.Model_identifyInputsAndOutputs = check_Model_identifyInputsAndOutputs;
    *(void**)&nnapi_.Model_relaxComputationFloat32toFloat16 = dlsym(handle, "ANeuralNetworksModel_relaxComputationFloat32toFloat16");
    check_nnapi_.Model_relaxComputationFloat32toFloat16 = check_Model_relaxComputationFloat32toFloat16;
    *(void**)&nnapi_.Compilation_create = dlsym(handle, "ANeuralNetworksCompilation_create");
    check_nnapi_.Compilation_create = check_Compilation_create;
    *(void**)&nnapi_.Compilation_free = dlsym(handle, "ANeuralNetworksCompilation_free");
    check_nnapi_.Compilation_free = check_Compilation_free;
    *(void**)&nnapi_.Compilation_setPreference = dlsym(handle, "ANeuralNetworksCompilation_setPreference");
    check_nnapi_.Compilation_setPreference = check_Compilation_setPreference;
    *(void**)&nnapi_.Compilation_finish = dlsym(handle, "ANeuralNetworksCompilation_finish");
    check_nnapi_.Compilation_finish = check_Compilation_finish;
    *(void**)&nnapi_.Execution_create = dlsym(handle, "ANeuralNetworksExecution_create");
    check_nnapi_.Execution_create = check_Execution_create;
    *(void**)&nnapi_.Execution_free = dlsym(handle, "ANeuralNetworksExecution_free");
    check_nnapi_.Execution_free = check_Execution_free;
    *(void**)&nnapi_.Execution_setInput = dlsym(handle, "ANeuralNetworksExecution_setInput");
    check_nnapi_.Execution_setInput = check_Execution_setInput;
    *(void**)&nnapi_.Execution_setInputFromMemory = dlsym(handle, "ANeuralNetworksExecution_setInputFromMemory");
    check_nnapi_.Execution_setInputFromMemory = check_Execution_setInputFromMemory;
    *(void**)&nnapi_.Execution_setOutput = dlsym(handle, "ANeuralNetworksExecution_setOutput");
    check_nnapi_.Execution_setOutput = check_Execution_setOutput;
    *(void**)&nnapi_.Execution_setOutputFromMemory = dlsym(handle, "ANeuralNetworksExecution_setOutputFromMemory");
    check_nnapi_.Execution_setOutputFromMemory = check_Execution_setOutputFromMemory;
    *(void**)&nnapi_.Execution_startCompute = dlsym(handle, "ANeuralNetworksExecution_startCompute");
    check_nnapi_.Execution_startCompute = check_Execution_startCompute;
    *(void**)&nnapi_.Event_wait = dlsym(handle, "ANeuralNetworksEvent_wait");
    check_nnapi_.Event_wait = check_Event_wait;
    *(void**)&nnapi_.Event_free = dlsym(handle, "ANeuralNetworksEvent_free");
    check_nnapi_.Event_free = check_Event_free;
    *(void**)&nnapi_.Execution_getOutputOperandRank = dlsym(handle, "ANeuralNetworksExecution_getOutputOperandRank");
    check_nnapi_.Execution_getOutputOperandRank = check_Execution_getOutputOperandRank;
    *(void**)&nnapi_.Execution_getOutputOperandDimensions = dlsym(handle, "ANeuralNetworksExecution_getOutputOperandDimensions");
    check_nnapi_.Execution_getOutputOperandDimensions = check_Execution_getOutputOperandDimensions;
    loaded = 1;
  }
  *nnapi = &nnapi_;
  *check_nnapi = &check_nnapi_;
#endif
}
