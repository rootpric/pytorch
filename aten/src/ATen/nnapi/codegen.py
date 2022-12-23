#!/usr/bin/env python3
"""
Code generator for NNAPI wrapper.  We can't link directly against
libneuralnetworks.so because we want PyTorch to work on Android
devices that don't have it available.  Instead, we generate a wrapper
that opens libneuralnetworks.so with dlopen and finds the functions
we need with dlsym.  We also generate a "check" wrapper that checks
return values and throws C++ exceptions on errors.
"""
import sys
import re
import pathlib
import textwrap


PREFIX = """\
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
"""


NNAPI_FUNCTIONS = [
    ("int", "ANeuralNetworks_getDeviceCount", "uint32_t* numDevices"),  # noqa: B950
    ("int", "ANeuralNetworks_getDevice", "uint32_t devIndex, ANeuralNetworksDevice** device"),  # noqa: B950
    ("int", "ANeuralNetworksDevice_getName", "const ANeuralNetworksDevice* device, const char** name"),  # noqa: B950
    ("int", "ANeuralNetworksDevice_getVersion", "const ANeuralNetworksDevice* device, const char** version"),  # noqa: B950
    ("int", "ANeuralNetworksDevice_getFeatureLevel", "const ANeuralNetworksDevice* device, int64_t* featureLevel"),  # noqa: B950
    ("int", "ANeuralNetworksModel_getSupportedOperationsForDevices", " const ANeuralNetworksModel* model, const ANeuralNetworksDevice* const* devices, uint32_t numDevices, bool* supportedOps"),  # noqa: B950
    ("int", "ANeuralNetworksCompilation_createForDevices", "ANeuralNetworksModel* model, const ANeuralNetworksDevice* const* devices, uint32_t numDevices, ANeuralNetworksCompilation** compilation"),  # noqa: B950
    ("int", "ANeuralNetworksExecution_compute", "ANeuralNetworksExecution* execution"),  # noqa: B950
    ("int", "ANeuralNetworksMemory_createFromFd", "size_t size, int protect, int fd, size_t offset, ANeuralNetworksMemory** memory"),  # noqa: B950
    ("void", "ANeuralNetworksMemory_free", "ANeuralNetworksMemory* memory"),  # noqa: B950
    ("int", "ANeuralNetworksModel_create", "ANeuralNetworksModel** model"),  # noqa: B950
    ("void", "ANeuralNetworksModel_free", "ANeuralNetworksModel* model"),  # noqa: B950
    ("int", "ANeuralNetworksModel_finish", "ANeuralNetworksModel* model"),  # noqa: B950
    ("int", "ANeuralNetworksModel_addOperand", "ANeuralNetworksModel* model, const ANeuralNetworksOperandType* type"),  # noqa: B950
    ("int", "ANeuralNetworksModel_setOperandValue", "ANeuralNetworksModel* model, int32_t index, const void* buffer, size_t length"),  # noqa: B950
    ("int", "ANeuralNetworksModel_setOperandValueFromMemory", "ANeuralNetworksModel* model, int32_t index, const ANeuralNetworksMemory* memory, size_t offset, size_t length"),  # noqa: B950
    ("int", "ANeuralNetworksModel_addOperation", "ANeuralNetworksModel* model, ANeuralNetworksOperationType type, uint32_t inputCount, const uint32_t* inputs, uint32_t outputCount, const uint32_t* outputs"),  # noqa: B950
    ("int", "ANeuralNetworksModel_identifyInputsAndOutputs", "ANeuralNetworksModel* model, uint32_t inputCount, const uint32_t* inputs, uint32_t outputCount, const uint32_t* outputs"),  # noqa: B950
    ("int", "ANeuralNetworksModel_relaxComputationFloat32toFloat16", "ANeuralNetworksModel* model, bool allow"),  # noqa: B950
    ("int", "ANeuralNetworksCompilation_create", "ANeuralNetworksModel* model, ANeuralNetworksCompilation** compilation"),  # noqa: B950
    ("void", "ANeuralNetworksCompilation_free", "ANeuralNetworksCompilation* compilation"),  # noqa: B950
    ("int", "ANeuralNetworksCompilation_setPreference", "ANeuralNetworksCompilation* compilation, int32_t preference"),  # noqa: B950
    ("int", "ANeuralNetworksCompilation_finish", "ANeuralNetworksCompilation* compilation"),  # noqa: B950
    ("int", "ANeuralNetworksExecution_create", "ANeuralNetworksCompilation* compilation, ANeuralNetworksExecution** execution"),  # noqa: B950
    ("void", "ANeuralNetworksExecution_free", "ANeuralNetworksExecution* execution"),  # noqa: B950
    ("int", "ANeuralNetworksExecution_setInput", "ANeuralNetworksExecution* execution, int32_t index, const ANeuralNetworksOperandType* type, const void* buffer, size_t length"),  # noqa: B950
    ("int", "ANeuralNetworksExecution_setInputFromMemory", "ANeuralNetworksExecution* execution, int32_t index, const ANeuralNetworksOperandType* type, const ANeuralNetworksMemory* memory, size_t offset, size_t length"),  # noqa: B950
    ("int", "ANeuralNetworksExecution_setOutput", "ANeuralNetworksExecution* execution, int32_t index, const ANeuralNetworksOperandType* type, void* buffer, size_t length"),  # noqa: B950
    ("int", "ANeuralNetworksExecution_setOutputFromMemory", "ANeuralNetworksExecution* execution, int32_t index, const ANeuralNetworksOperandType* type, const ANeuralNetworksMemory* memory, size_t offset, size_t length"),  # noqa: B950
    ("int", "ANeuralNetworksExecution_startCompute", "ANeuralNetworksExecution* execution, ANeuralNetworksEvent** event"),  # noqa: B950
    ("int", "ANeuralNetworksEvent_wait", "ANeuralNetworksEvent* event"),  # noqa: B950
    ("void", "ANeuralNetworksEvent_free", "ANeuralNetworksEvent* event"),  # noqa: B950
    ("int", "ANeuralNetworksExecution_getOutputOperandRank", "ANeuralNetworksExecution* execution, int32_t index, uint32_t* rank"),  # noqa: B950
    ("int", "ANeuralNetworksExecution_getOutputOperandDimensions", "ANeuralNetworksExecution* execution, int32_t index, uint32_t* dimensions"),  # noqa: B950
]


def main(argv):
    struct_members = []
    load_functions = []
    define_checks = []

    for ret, name, args in NNAPI_FUNCTIONS:
        short_name = name.replace("ANeuralNetworks", "", 1)

        struct_members.append(f"  {ret}(*{short_name})({args});")

        load_functions.append(f'    *(void**)&nnapi_.{short_name} = dlsym(handle, "{name}");')
        load_functions.append(f'    check_nnapi_.{short_name} = check_{short_name};')

        call_args = "".join(re.findall(r"\w+(?:,|$)", args))
        if ret == "void":
            define_checks.append(textwrap.dedent(f"""\
                {ret} check_{short_name}({args}) {{
                  CAFFE_ENFORCE(nnapi_.{short_name});
                  nnapi_.{short_name}({call_args});
                }}"""))
        if ret == "int":
            define_checks.append(textwrap.dedent(f"""\
                {ret} check_{short_name}({args}) {{
                  CAFFE_ENFORCE(nnapi_.{short_name});
                  int ret = nnapi_.{short_name}({call_args});
                  // TODO: Maybe add better logging here.
                  CAFFE_ENFORCE(
                    ret == ANEURALNETWORKS_NO_ERROR,
                    "{short_name}", "failed with error ", ret
                  );
                  return ret;
                }}"""))

    out_dir = pathlib.Path(__file__).parent

    (out_dir / "nnapi_wrapper.h").write_text(
        PREFIX +
        textwrap.dedent("""\
            #ifndef NNAPI_WRAPPER_H_
            #define NNAPI_WRAPPER_H_
            #include <stddef.h>
            #include <stdint.h>
            #include <ATen/nnapi/NeuralNetworks.h>
            struct nnapi_wrapper {
            __STRUCT_MEMBERS__
            };
            #ifdef __cplusplus
            void nnapi_wrapper_load(struct nnapi_wrapper** nnapi, struct nnapi_wrapper** check_nnapi);
            #endif
            #endif
            """)
        .replace("__STRUCT_MEMBERS__", "\n".join(struct_members))
    )

    (out_dir / "nnapi_wrapper.cpp").write_text(
        PREFIX +
        textwrap.dedent("""\
            #ifndef _WIN32
            #include <dlfcn.h>
            #endif
            #include <ATen/nnapi/nnapi_wrapper.h>
            #include <c10/util/Logging.h>
            // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
            static int loaded = 0;
            // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
            static struct nnapi_wrapper nnapi_;
            // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
            static struct nnapi_wrapper check_nnapi_;
            __DEFINE_CHECK_FUNCTIONS__
            void nnapi_wrapper_load(struct nnapi_wrapper** nnapi, struct nnapi_wrapper** check_nnapi) {
            #ifdef _WIN32
              TORCH_CHECK(false, "Running NNAPI models is not supported on Windows.");
            #else
              if (!loaded) {
                // Clear error flag.
                dlerror();
                void* handle = dlopen("libneuralnetworks.so", RTLD_LAZY | RTLD_LOCAL);
                CAFFE_ENFORCE(handle, "Failed to load libneuralnetworks.so ", dlerror());
            __LOAD_FUNCTIONS__
                loaded = 1;
              }
              *nnapi = &nnapi_;
              *check_nnapi = &check_nnapi_;
            #endif
            }
            """)
        .replace("__DEFINE_CHECK_FUNCTIONS__", "\n".join(define_checks))
        .replace("__LOAD_FUNCTIONS__", "\n".join(load_functions))
    )


if __name__ == "__main__":
    sys.exit(main(sys.argv))
