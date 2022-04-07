phi_include_guard()

include(CMakeParseArguments)

# TODO: MSVC support
set(phi_noexcept_flags fno-exceptions)

# Check noexcept flags
set(_noexcept_flags)
foreach(_test ${phi_noexcept_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "_" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    list(APPEND _noexcept_flags ${PHI_FLAG_PREFIX_CHAR}${_test})
  endif()
endforeach(_test)

function(phi_target_disable_exceptions)
  # Command line arguments
  cmake_parse_arguments(noexcept "" "TARGET" "" ${ARGN})

  # Check required arguments
  if(NOT noexcept_TARGET)
    phi_error("phi_target_disable_exceptions: You must specify TARGET")
  endif()

  # Check if target is valid
  if(NOT TARGET ${noexcept_TARGET})
    phi_error(
      "phi_target_disable_exceptions: The specified target \"${noexcept_TARGET}\" doesn't seem to be valid"
    )
  endif()

  # Get target type
  get_property(
    target_type
    TARGET ${noexcept_TARGET}
    PROPERTY TYPE)

  if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
    set(visibility_scope INTERFACE)
  else()
    set(visibility_scope PRIVATE)
  endif()

  foreach(flag ${_noexcept_flags})
    target_compile_options(${noexcept_TARGET} ${visibility_scope} ${flag})
    target_link_options(${noexcept_TARGET} ${visibility_scope} ${flag})
  endforeach()

  # Add a define
  target_compile_definitions(${noexcept_TARGET} ${visibility_scope} "PHI_CONFIG_NO_EXCEPTIONS")
endfunction()
