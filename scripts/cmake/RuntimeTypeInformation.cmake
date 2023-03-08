phi_include_guard()

include(CMakeParseArguments)
include(CompilerFlags)

function(phi_target_set_rtti)
  # Command line arguments
  cmake_parse_arguments(rtti "ENABLE;DISABLE" "TARGET" "" ${ARGN})

  # Check required arguments
  if(NOT rtti_TARGET)
    phi_error("phi_target_set_rtti: You must specify TARGET")
  endif()

  # Check if target is valid
  if(NOT TARGET ${rtti_TARGET})
    phi_error(
      "phi_target_set_rtti: The specified target \"${rtti_TARGET}\" doesn't seem to be valid")
  endif()

  # Check that user specified any model
  if(NOT rtti_ENABLE AND NOT rtti_DISABLE)
    phi_error("phi_target_set_rtti: You must specify either ENABLE or DISABLE!")
  endif()

  # Check that DEFAULT, FAST and PRECISE are mutually exclusive
  if(rtti_ENABLE AND rtti_DISABLE)
    phi_error("phi_target_set_rtti: You may only specify ENABLE or DISABLE not multiple!")
  endif()

  # Get target type
  get_property(
    target_type
    TARGET ${rtti_TARGET}
    PROPERTY TYPE)

  if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
    set(visibility_scope INTERFACE)
  else()
    set(visibility_scope PRIVATE)
  endif()

  get_property(
    target_linker_language
    TARGET ${rtti_TARGET}
    PROPERTY LINKER_LANGUAGE)

  # Ignore C targets
  if(NOT "${target_linker_language}" STREQUAL "CXX" AND NOT "${target_linker_language}" STREQUAL "")
    return()
  endif()

  # Enable specfied flags
  if(rtti_ENABLE)
    # Just a define to add
    target_compile_definitions(${rtti_TARGET} ${visibility_scope} "PHI_CONFIG_RTTI")
  elseif(rtti_DISABLE)
    target_compile_options(${rtti_TARGET} ${visibility_scope} ${phi_no_rtti_flags})

    target_compile_definitions(${rtti_TARGET} ${visibility_scope} "PHI_CONFIG_NO_RTTI")
  endif()
endfunction()
