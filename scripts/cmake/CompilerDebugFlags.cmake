phi_include_guard()

include(CMakeParseArguments)
include(internal/PhiCheckCXXCompilerFlag)

set(phi_extra_debug_flags g3 ftrapv ftrivial-auto-var-init=pattern)

# Check extra debug flags
set(_ExtraDebugFlags)
foreach(_test ${phi_extra_debug_flags})
  string(REPLACE "/" "" _testName ${_test})
  string(REPLACE "-" "_" _testName ${_testName})
  string(REPLACE "=" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    list(APPEND _ExtraDebugFlags ${PHI_FLAG_PREFIX_CHAR}${_test})
  endif()
endforeach(_test)

function(phi_target_enable_extra_debug_flags)
  # Command line arguments
  cmake_parse_arguments(dbg "" "TARGET" "CONFIGS" ${ARGN})

  # Check required arguments
  if(NOT dbg_TARGET)
    phi_error("phi_target_enable_extra_debug_flags: You must specify TARGET")
  endif()

  # Check if target is valid
  if(NOT TARGET ${dbg_TARGET})
    phi_error(
      "phi_target_enable_extra_debug_flags: The specified target \"${dbg_TARGET}\" doesn't seem to be valid"
    )
  endif()

  # Optionally set configs
  if(NOT DEFINED ${dbg_CONFIGS})
    # set a default value
    set(dbg_CONFIGS "Debug;RelWithDebInfo")
  endif()

  # Get target type
  get_property(
    target_type
    TARGET ${dbg_TARGET}
    PROPERTY TYPE)

  if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
    set(visibility_scope INTERFACE)
  else()
    set(visibility_scope PRIVATE)
  endif()

  # Enable extra debug flags for each configuration
  foreach(config ${dbg_CONFIGS})
    # Set each flag
    foreach(flag ${_ExtraDebugFlags})
      target_compile_options(${dbg_TARGET} ${visibility_scope} $<$<CONFIG:${config}>:${flag}>)
      target_link_options(${dbg_TARGET} ${visibility_scope} $<$<CONFIG:${config}>:${flag}>)
    endforeach()
  endforeach()
endfunction()
