#!/bin/bash

# Get number of processors available
echo "PROC_COUNT=$(nproc)" >>$GITHUB_ENV
echo "OS_CODENAME=$(lsb_release -c -s)" >>$GITHUB_ENV

# Setup CMake stuff
# https://cmake.org/cmake/help/latest/envvar/CMAKE_BUILD_PARALLEL_LEVEL.html
echo "CMAKE_BUILD_PARALLEL_LEVEL=${PROC_COUNT}" >>$GITHUB_ENV
# https://cmake.org/cmake/help/latest/envvar/CTEST_PARALLEL_LEVEL.html
echo "CTEST_PARALLEL_LEVEL=${PROC_COUNT}" >>$GITHUB_ENV
# https://cmake.org/cmake/help/latest/envvar/CTEST_OUTPUT_ON_FAILURE.html
echo "CTEST_OUTPUT_ON_FAILURE=ON" >>$GITHUB_ENV

# Set some default options
# https://cmake.org/cmake/help/latest/envvar/CMAKE_EXPORT_COMPILE_COMMANDS.html
echo "CMAKE_EXPORT_COMPILE_COMMANDS=ON"
# https://cmake.org/cmake/help/latest/envvar/VERBOSE.html
echo "VERBOSE=ON" >>$GITHUB_ENV

# Latest versions
echo "LATEST_LLVM_VERSION=14" >>$GITHUB_ENV
echo "LATEST_GCC_VERSION=11" >>$GITHUB_ENV
