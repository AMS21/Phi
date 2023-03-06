phi_include_guard()

include(CMakeParseArguments)
include(CompilerFlags)

# Extra disabled warnings for MSVC stl
set(phi_msvc_stl_extra_disable
    4365 # 'action' : conversion from 'type_1' to 'type_2', signed/unsigned mismatch -
    # https://learn.microsoft.com/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4365
    4530 # C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc
    # https://learn.microsoft.com/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4530
    4668 # 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives' -
    # https://learn.microsoft.com/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4668
    5262 # implicit fall-through occurs here; are you missing a break statement? Use
    # [[fallthrough]] when a break statement is intentionally omitted between cases -
    # https://learn.microsoft.com/cpp/error-messages/compiler-warnings/compiler-warnings-by-compiler-version
    CACHE INTERNAL "")

function(phi_target_set_common_flags)
  # Command line arguments
  cmake_parse_arguments(cf "ALL;COLOR_DIAGNOSTICS;TIME_TRACE" "TARGET" "" ${ARGN})

  # Check required arguments
  if(NOT cf_TARGET)
    phi_error("phi_target_set_common_flags: You must specify TARGET")
  endif()

  # Check if target is valid
  if(NOT TARGET ${cf_TARGET})
    phi_error(
      "phi_target_set_common_flags: The specified target \"${cf_TARGET}\" doesn't seem to be valid")
  endif()

  # Check ALL is mutially exclusive TODO:

  if(cf_ALL)
    set(cf_COLOR_DIAGNOSTICS 1)
    set(cf_TIME_TRACE 1)
  endif()

  # Get target type
  get_property(
    target_type
    TARGET ${cf_TARGET}
    PROPERTY TYPE)

  if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
    set(visibility_scope INTERFACE)
  else()
    set(visibility_scope PRIVATE)
  endif()

  # Set normal flags
  target_compile_options(${cf_TARGET} ${visibility_scope} ${phi_common_flags})

  # Get linker language
  get_property(
    target_linker_language
    TARGET ${cf_TARGET}
    PROPERTY LINKER_LANGUAGE)

  # Set cxx flags
  if("${target_linker_language}" STREQUAL "CXX" OR "${target_linker_language}" STREQUAL "")
    target_compile_options(${cf_TARGET} ${visibility_scope} ${phi_cxx_common_flags})
  endif()

  # Optionally enable color diagnostics
  if(cf_COLOR_DIAGNOSTICS)
    target_compile_options(${cf_TARGET} ${visibility_scope} ${phi_color_diagnostics_flag})
  endif()

  # Optionally set time trace
  if(cf_TIME_TRACE)
    target_compile_options(${cf_TARGET} ${visibility_scope} -ftime-trace)
  endif()

  # Disable warnings in the msvc stl
  if(PHI_COMPILER_MSVC)
    target_compile_definitions(
      "${cf_TARGET}"
      ${visibility_scope} "_STL_EXTRA_DISABLED_WARNINGS=${phi_msvc_stl_extra_disable}"
      "_ALLOW_RTCc_IN_STL")
  endif()
endfunction()
