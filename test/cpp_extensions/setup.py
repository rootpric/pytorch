import sys
import torch.cuda
import os
from setuptools import setup
from torch.utils.cpp_extension import BuildExtension, CppExtension, CUDAExtension
from torch.utils.cpp_extension import CUDA_HOME, ROCM_HOME
from torch.testing._internal.common_utils import IS_WINDOWS

if sys.platform == 'win32':
    vc_version = os.getenv('VCToolsVersion', '')
    if vc_version.startswith('14.16.'):
        CXX_FLAGS = ['/sdl']
    else:
        CXX_FLAGS = ['/sdl', '/permissive-']
else:
    CXX_FLAGS = ['-g']

USE_NINJA = os.getenv('USE_NINJA') == '1'

ext_modules = [
    CppExtension(
        'torch_test_cpp_extension.cpp', ['extension.cpp'],
        extra_compile_args=CXX_FLAGS),
    CppExtension(
        'torch_test_cpp_extension.ort', ['ort_extension.cpp'],
        extra_compile_args=CXX_FLAGS),
    CppExtension(
        'torch_test_cpp_extension.rng', ['rng_extension.cpp'],
        extra_compile_args=CXX_FLAGS),
]

if torch.cuda.is_available() and (CUDA_HOME is not None or ROCM_HOME is not None):
    extension = CUDAExtension(
        'torch_test_cpp_extension.cuda', [
            'cuda_extension.cpp',
            'cuda_extension_kernel.cu',
            'cuda_extension_kernel2.cu',
        ],
        extra_compile_args={'cxx': CXX_FLAGS,
                            'nvcc': ['-O2']})
    ext_modules.append(extension)

if torch.cuda.is_available() and (CUDA_HOME is not None or ROCM_HOME is not None):
    extension = CUDAExtension(
        'torch_test_cpp_extension.torch_library', [
            'torch_library.cu'
        ],
        extra_compile_args={'cxx': CXX_FLAGS,
                            'nvcc': ['-O2']})
    ext_modules.append(extension)

# todo(mkozuki): Figure out the root cause
if (not IS_WINDOWS) and torch.cuda.is_available() and CUDA_HOME is not None:
    # malfet: One shoudl not assume that PyTorch re-exports CUDA dependencies
    cublas_extension = CUDAExtension(
        name='torch_test_cpp_extension.cublas_extension',
        sources=['cublas_extension.cpp'],
        libraries=['cublas'] if torch.version.hip is None else [],
    )
    ext_modules.append(cublas_extension)

    cusolver_extension = CUDAExtension(
        name='torch_test_cpp_extension.cusolver_extension',
        sources=['cusolver_extension.cpp'],
        libraries=['cusolver'] if torch.version.hip is None else [],
    )
    ext_modules.append(cusolver_extension)

if USE_NINJA and (not IS_WINDOWS) and torch.cuda.is_available() and CUDA_HOME is not None:
    extension = CUDAExtension(
        name='torch_test_cpp_extension.cuda_dlink',
        sources=[
            'cuda_dlink_extension.cpp',
            'cuda_dlink_extension_kernel.cu',
            'cuda_dlink_extension_add.cu',
        ],
        dlink=True,
        extra_compile_args={'cxx': CXX_FLAGS,
                            'nvcc': ['-O2', '-dc']})
    ext_modules.append(extension)

setup(
    name='torch_test_cpp_extension',
    packages=['torch_test_cpp_extension'],
    ext_modules=ext_modules,
    include_dirs='self_compiler_include_dirs_test',
    cmdclass={'build_ext': BuildExtension.with_options(use_ninja=USE_NINJA)})
