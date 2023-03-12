phi_include_guard()

include(CMakeParseArguments)
include(CompilerFlags)

function(phi_target_set_floating_point_model)
  # Command line arguments
  cmake_parse_arguments(fpm "DEFAULT;FAST;PRECISE" "TARGET" "" ${ARGN})

  # Check required arguments
  if(NOT fpm_TARGET)
    phi_error("phi_target_set_floating_point_model: You must specify TARGET")
  endif()

  # Check if target is valid
  if(NOT TARGET ${fpm_TARGET})
    phi_error(
      "phi_target_set_floating_point_model: The specified target \"${fpm_TARGET}\" doesn't seem to be valid"
    )
  endif()

  # Check that user specified any model
  if(NOT fpm_DEFAULT
     AND NOT fpm_FAST
     AND NOT fpm_PRECISE)
    phi_error(
      "phi_target_set_floating_point_model: You must specify either DEFAULT, FAST or PRECISE!")
  endif()

  # Check that DEFAULT, FAST and PRECISE are mutually exclusive
  if((fpm_DEFAULT AND (fpm_FAST OR fpm_PRECISE)) OR (fpm_FAST AND fpm_PRECISE))
    phi_error(
      "phi_target_set_floating_point_model: You may only specify DEFAULT, FAST or PRECISE not multiple!"
    )
  endif()

  # Get target type
  get_property(
    target_type
    TARGET ${fpm_TARGET}
    PROPERTY TYPE)

  if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
    set(visibility_scope INTERFACE)
  else()
    set(visibility_scope PRIVATE)
  endif()

  # Enable specfied flags
  if(fpm_DEFAULT)
    # No special flags to enable just add a define
    target_compile_definitions(${fpm_TARGET} ${visibility_scope} "PHI_CONFIG_FPM_DEFAULT")
  elseif(fpm_FAST)
    target_compile_options(${fpm_TARGET} ${visibility_scope} "${phi_fast_math_flags}")
    target_compile_definitions(${fpm_TARGET} ${visibility_scope} "PHI_CONFIG_FPM_FAST")
  elseif(fpm_PRECISE)
    target_compile_options(${fpm_TARGET} ${visibility_scope} ${phi_precise_math_flags})
    target_compile_definitions(${fpm_TARGET} ${visibility_scope} "PHI_CONFIG_FPM_PRECISE")
  endif()
endfunction()
