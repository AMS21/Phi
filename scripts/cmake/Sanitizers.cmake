phi_include_guard()

include(CMakeParseArguments)
include(CompilerFlags)

option(PHI_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" FALSE)
option(PHI_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" FALSE)
option(PHI_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" FALSE)
option(PHI_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" FALSE)
option(PHI_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" FALSE)

function(phi_target_enable_sanitizer)
  # Command line arguments
  cmake_parse_arguments(san "" "TARGET" "SANITIZERS" ${ARGN})

  # Check required arguments
  if(NOT san_TARGET)
    phi_error("phi_target_enable_sanitizer: You must specify a target using TARGET")
  endif()

  if(NOT TARGET ${san_TARGET})
    phi_error(
      "phi_target_enable_sanitizer: The specified target \"${san_TARGET}\" doesn't seem to exist")
  endif()

  if(NOT san_SANITIZERS)
    phi_error("phi_target_enable_sanitizer: No sanitizer specified.")
  endif()

  # Get target type
  get_property(
    target_type
    TARGET ${san_TARGET}
    PROPERTY TYPE)

  if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
    set(visibility_scope INTERFACE)
  else()
    set(visibility_scope PRIVATE)
  endif()

  # Enable required sanitizers
  foreach(sanitizer ${san_SANITIZERS})
    string(REPLACE "-" "_" var_sanitizer ${sanitizer})
    string(TOLOWER ${var_sanitizer} var_sanitizer)

    # Check if sanitizer is actually supported
    if(NOT phi_sanitizer_${var_sanitizer}_flags)
      phi_error(
        "phi_target_enable_sanitizer: Trying to enable '${sanitizer}' which is not supported!")
    endif()

    # Set sanitizer flags to target
    target_compile_options(${san_TARGET} ${visibility_scope}
                           ${phi_sanitizer_${var_sanitizer}_flags})
    target_link_options(${san_TARGET} ${visibility_scope} ${phi_sanitizer_${var_sanitizer}_flags})
  endforeach()

  # Set extra sanitizer flags to target
  target_compile_options(${san_TARGET} ${visibility_scope} ${phi_sanitizer_support_flags})
  target_link_options(${san_TARGET} ${visibility_scope} ${phi_sanitizer_support_flags})
endfunction()
