phi_include_guard()

# TODO: Support more than just clangs lib fuzzer

# https://llvm.org/docs/LibFuzzer.html

include(CMakeParseArguments)
include(CompilerFlags)
include(Functions)
include(Testing)

set(PHI_TEST_FUZZING_RUNTIME
    30
    CACHE STRING "Number of seconds to run fuzz tests during ctest run")

function(phi_add_fuzzer)
  # Simply do nothing for a compiler which doesn't support fuzzing
  if(NOT phi_fuzzing_support_flags AND ${PHI_FUZZING_LIBRARY} STREQUAL "default")
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

  # The compiler_rt for clang on windows is build with non debug static standard library
  if(PHI_COMPILER_CLANG AND PHI_PLATFORM_WINDOWS)
    if(NOT ${PHI_STANDARD_RUNTIME} STREQUAL "Static")
      phi_warn(
        "phi_add_fuzzer: Standard runtime '${PHI_STANDARD_RUNTIME}' is not supported for clang fuzzers. You should use 'Static'"
      )
    endif()

    # Ensure fuzzers are only build in release mode
    if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
      return()
    endif()
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
  if(NOT phi_sanitizer_support_flags)
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
  target_compile_options(${fuzz_TARGET} ${visibility_scope} ${phi_fuzzing_support_flags})
  target_link_options(${fuzz_TARGET} ${visibility_scope} ${phi_fuzzing_support_flags})

  target_compile_definitions(
    ${fuzz_TARGET} ${visibility_scope} "FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION"
                   "PHI_CONFIG_FUZZER_BUILD")
endfunction()
