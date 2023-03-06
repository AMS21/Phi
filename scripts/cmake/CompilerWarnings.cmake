phi_include_guard()

include(CMakeParseArguments)
include(CompilerFlags)

# from here:
#
# https://github.com/lefticus/cppbestpractices/blob/master/02-Use_the_Tools_Available.md

# Enable warnings for project
function(phi_target_set_warnings)
  # Command line arguments
  cmake_parse_arguments(warn "WARNINGS_AS_ERRORS;PEDANTIC" "TARGET" "" ${ARGN})

  # Check required arguments
  if(NOT DEFINED warn_TARGET)
    phi_error("phi_target_set_warnings: You must specify a target with TARGET")
  endif()

  # Check target actually exists
  if(NOT TARGET ${warn_TARGET})
    phi_error(
      "phi_target_set_warnings: The specified target \"${warn_TARGET}\" doesn't seem to exist")
  endif()

  # Get target type
  get_property(
    target_type
    TARGET ${warn_TARGET}
    PROPERTY TYPE)

  if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
    set(visibility_scope INTERFACE)
  else()
    set(visibility_scope PRIVATE)
  endif()

  # Get linker language
  get_property(
    target_linker_language
    TARGET ${warn_TARGET}
    PROPERTY LINKER_LANGUAGE)

  # We're assuming CXX by default
  if("${target_linker_language}" STREQUAL "CXX" OR "${target_linker_language}" STREQUAL "")
    # Set C/C++ warning flags
    target_compile_options(${warn_TARGET} ${visibility_scope} ${phi_warning_flags}
                           ${phi_cxx_warning_flags})
  elseif("${target_linker_language}" STREQUAL "C")
    # Set only C warning flags
    target_compile_options(${warn_TARGET} ${visibility_scope} ${phi_warning_flags})
  endif()

  # Set disabled warnings
  target_compile_options(${warn_TARGET} ${visibility_scope} ${phi_disabled_warnings_flags})

  # Add optional warnings as errors
  if(warn_WARNINGS_AS_ERRORS)
    target_compile_options(${warn_TARGET} ${visibility_scope} ${phi_warnings_as_errors_flag})
    target_compile_definitions(${warn_TARGET} ${visibility_scope} "PHI_CONFIG_WARNINGS_AS_ERRORS")
  endif()

  # Add optional pedantic
  if(warn_PEDANTIC)
    target_compile_options(${warn_TARGET} ${visibility_scope} ${phi_pedantic_flags})
    target_compile_definitions(${warn_TARGET} ${visibility_scope} "PHI_CONFIG_PEDANTIC_WARNINGS")
  endif()
endfunction()
