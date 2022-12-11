phi_include_guard()

# TODO: Support more than just clangs lib fuzzer

# https://llvm.org/docs/LibFuzzer.html

include(CMakeParseArguments)
include(Functions)
include(Sanitizers)
include(Testing)
include(CompilerOptimizations)

set(PHI_TEST_FUZZING_RUNTIME
    30
    CACHE STRING "Number of seconds to run fuzz tests during ctest run")

# Check if fuzzing is supported
set(old_flags ${CMAKE_REQUIRED_FLAGS})
set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} ${PHI_FLAG_PREFIX_CHAR}fsanitize=fuzzer")

phi_check_cxx_source_compiles(
  "#include <cstddef>
#include <cstdint>
extern \"C\" int LLVMFuzzerTestOneInput(const std::uint8_t*, std::size_t) { return 0; }"
  PHI_SUPPORTS_SANITIZER_FUZZER)

set(CMAKE_REQUIRED_FLAGS ${old_flags})

check_linker_flag(CXX "${PHI_FLAG_PREFIX_CHAR}fsanitize=fuzzer-no-link"
                  PHI_SUPPORTS_SANITIZER_FUZZER_NO_LINK)

set(phi_fuzzing_target_default_flags fno-omit-frame-pointer fno-optimize-sibling-calls)

# Check optimize flags for C++
set(_phi_fuzzing_target_default_flags_suppported CACHE INTERNAL "")
foreach(_test ${phi_fuzzing_target_default_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "_" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_fuzzing_target_default_flags_suppported
        ${_phi_fuzzing_target_default_flags_suppported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

# Add fuzzer-no-link to default flags if supported and using default library
if(PHI_SUPPORTS_SANITIZER_FUZZER_NO_LINK AND ${PHI_FUZZING_LIBRARY} STREQUAL "default")
  set(_phi_fuzzing_target_default_flags_suppported
      ${_phi_fuzzing_target_default_flags_suppported};${PHI_FLAG_PREFIX_CHAR}fsanitize=fuzzer-no-link
      CACHE INTERNAL "")
endif()

function(phi_add_fuzzer)
  # Simply do nothing for a compiler which doesn't support fuzzing
  if(NOT ${PHI_SUPPORTS_SANITIZER_FUZZER} AND ${PHI_FUZZING_LIBRARY} STREQUAL "default")
    return()
  endif()

  # Command line arguments
  set(CMD_OPTIONS "ASCII_ONLY")
  set(CMD_ONE_VALUE "NAME")
  set(CMD_MULTI_VALUE "SOURCES;INCLUDE_DIRS;LINK_LIBRARIES;DEFINITIONS")

  cmake_parse_arguments(fuzz "${CMD_OPTIONS}" "${CMD_ONE_VALUE}" "${CMD_MULTI_VALUE}" ${ARGN})

  if(NOT fuzz_NAME)
    phi_error("phi_add_fuzzer: You must specify a name using NAME")
  endif()

  # Add our executable
  phi_add_executable(
    NAME
    ${fuzz_NAME}
    FOLDER
    "Fuzzer"
    SOURCES
    "${fuzz_SOURCES}"
    PRIVATE_INCLUDE_DIRS
    "${fuzz_INCLUDE_DIRS}"
    PRIVATE_LINK_LIBRARIES
    "${fuzz_LINK_LIBRARIES}"
    PRIVATE_DEFINITIONS
    "${fuzz_DEFINITIONS}")

  if(${PHI_FUZZING_LIBRARY} STREQUAL "default")
    target_compile_options(${fuzz_NAME} PRIVATE "${PHI_FLAG_PREFIX_CHAR}fsanitize=fuzzer")
    target_link_options(${fuzz_NAME} PRIVATE "${PHI_FLAG_PREFIX_CHAR}fsanitize=fuzzer")
  else()
    target_compile_options(${fuzz_NAME} PRIVATE "${PHI_FUZZING_LIBRARY}")
    target_link_options(${fuzz_NAME} PRIVATE "${PHI_FUZZING_LIBRARY}")
  endif()

  if(${ASCII_ONLY})
    add_test(NAME ${fuzz_NAME}_run COMMAND ${fuzz_NAME} -max_total_time=${PHI_TEST_FUZZING_RUNTIME}
                                           -close_fd_mask=1 -only_ascii=1)
  else()
    add_test(NAME ${fuzz_NAME}_run COMMAND ${fuzz_NAME} -max_total_time=${PHI_TEST_FUZZING_RUNTIME}
                                           -close_fd_mask=1)
    add_test(NAME ${fuzz_NAME}_ascii_only_run
             COMMAND ${fuzz_NAME} -max_total_time=${PHI_TEST_FUZZING_RUNTIME} -close_fd_mask=1
                     -only_ascii=1)
  endif()
endfunction()

# Set fuzzing flags on target
function(phi_target_enable_fuzzing_flags)
  # Simply do nothing for a compiler which doesn't support fuzzing
  if(NOT ${PHI_SUPPORTS_SANITIZER_FUZZER})
    return()
  endif()

  # Command line arguments
  set(CMD_OPTIONS "")
  set(CMD_ONE_VALUE "TARGET")
  set(CMD_MULTI_VALUE "")

  cmake_parse_arguments(fuzz "${CMD_OPTIONS}" "${CMD_ONE_VALUE}" "${CMD_MULTI_VALUE}" ${ARGN})

  if(NOT fuzz_TARGET)
    phi_error("phi_target_enable_fuzzing_flags: You must specify a target using TARGET")
  endif()

  if(NOT TARGET ${fuzz_TARGET})
    phi_error("phi_target_enable_fuzzing_flags: The target '${fuzz_TARGET}' doesn't seem to exist")
  endif()

  # Get target type
  get_property(
    target_type
    TARGET ${fuzz_TARGET}
    PROPERTY TYPE)

  if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
    set(visibility_scope INTERFACE)
  else()
    set(visibility_scope PRIVATE)
  endif()

  # Set compile and link flags
  foreach(flag ${_phi_fuzzing_target_default_flags_suppported})
    target_compile_options(${fuzz_TARGET} ${visibility_scope} ${flag})
    target_link_options(${fuzz_TARGET} ${visibility_scope} ${flag})
  endforeach()

  target_compile_definitions(
    ${fuzz_TARGET} ${visibility_scope} "FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION"
                   "PHI_CONFIG_FUZZER_BUILD")
endfunction()
