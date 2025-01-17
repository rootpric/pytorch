# Copyright (c) Facebook, Inc. and its affiliates.
# All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(pthreadpool-download NONE)

include(ExternalProject)
ExternalProject_Add(pthreadpool
  GIT_REPOSITORY https://github.com/Maratyszcza/pthreadpool.git
  GIT_TAG master
  SOURCE_DIR "${CONFU_DEPENDENCIES_SOURCE_DIR}/pthreadpool"
  BINARY_DIR "${CONFU_DEPENDENCIES_BINARY_DIR}/pthreadpool"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)
