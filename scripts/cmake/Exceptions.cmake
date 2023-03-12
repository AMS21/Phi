phi_include_guard()

include(CMakeParseArguments)
include(CompilerFlags)

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

  target_compile_options(${noexcept_TARGET} ${visibility_scope} ${phi_noexcept_flag})
  target_link_options(${noexcept_TARGET} ${visibility_scope} ${phi_noexcept_flag})

  # Add a define
  target_compile_definitions(${noexcept_TARGET} ${visibility_scope} "PHI_CONFIG_NO_EXCEPTIONS")
endfunction()
