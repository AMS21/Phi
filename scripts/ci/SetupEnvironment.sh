#!/bin/bash

PROC_COUNT=$(nproc)

# Get number of processors available
echo "PROC_COUNT=$PROC_COUNT" >>"$GITHUB_ENV"
echo "OS_CODENAME=$(lsb_release -c -s)" >>"$GITHUB_ENV"

# Setup CMake stuff
# https://cmake.org/cmake/help/latest/envvar/CMAKE_BUILD_PARALLEL_LEVEL.html
echo "CMAKE_BUILD_PARALLEL_LEVEL=${PROC_COUNT}" >>"$GITHUB_ENV"
# https://cmake.org/cmake/help/latest/envvar/CTEST_PARALLEL_LEVEL.html
echo "CTEST_PARALLEL_LEVEL=${PROC_COUNT}" >>"$GITHUB_ENV"
# https://cmake.org/cmake/help/latest/envvar/CTEST_OUTPUT_ON_FAILURE.html
echo "CTEST_OUTPUT_ON_FAILURE=ON" >>"$GITHUB_ENV"
# https://cmake.org/cmake/help/latest/variable/CMAKE_GENERATOR.html
echo "CMAKE_GENERATOR=Ninja" >>"$GITHUB_ENV"

# Set some default options
# https://cmake.org/cmake/help/latest/envvar/CMAKE_EXPORT_COMPILE_COMMANDS.html
echo "CMAKE_EXPORT_COMPILE_COMMANDS=ON" >>"$GITHUB_ENV"
# https://cmake.org/cmake/help/latest/envvar/VERBOSE.html
echo "VERBOSE=ON" >>"$GITHUB_ENV"

# Set sanitizer runtime flags
# https://github.com/google/sanitizers/wiki/SanitizerCommonFlags
# https://github.com/google/sanitizers/wiki/AddressSanitizerFlags#run-time-flags
echo "ASAN_OPTIONS=quarantine_size_mb=1024:redzone=256:strict_string_checks=1:detect_odr_violation=2:detect_stack_use_after_return=1:check_initialization_order=1:strict_init_order=1:detect_invalid_pointer_pairs=3:detect_leaks=1:print_stats=1:use_odr_indicator=1:strict_memcmp=1:print_scariness=1:handle_abort=1:symbolize=1:handle_segv=1:handle_sigill=1:allocator_release_to_os_interval_ms=500:handle_sigfpe=1:handle_sigbus=1:alloc_dealloc_mismatch=1:check_malloc_usable_size=1" >>"$GITHUB_ENV"
# https://github.com/google/sanitizers/wiki/AddressSanitizerLeakSanitizer#flags
echo "LSAN_OPTIONS=report_objects=1:use_unaligned=1" >>"$GITHUB_ENV"
echo "MSAN_OPTIONS=poison_in_dtor=1" >>"$GITHUB_ENV"
# https://github.com/google/sanitizers/wiki/ThreadSanitizerFlags#runtime-flags
echo "TSAN_OPTIONS=halt_on_error=1:history_size=3:force_seq_cst_atomics=1" >>"$GITHUB_ENV"
echo "UBSAN_OPTIONS=print_stacktrace=1:report_error_type=1" >>"$GITHUB_ENV"

# Latest versions
echo "LATEST_LLVM_VERSION=14" >>"$GITHUB_ENV"
echo "LATEST_GCC_VERSION=11" >>"$GITHUB_ENV"
