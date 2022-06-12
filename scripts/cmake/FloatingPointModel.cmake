phi_include_guard()

include(CMakeParseArguments)

set(phi_fast_math_flags
    ffast-math
    fassociative-math
    fcx-limited-range
    fexcess-precision=fast
    ffinite-math-only
    ffp-contract=fast
    ffp-exception-behavior=ignore
    ffp-model=fast
    fno-honor-infinities
    fno-honor-nans
    fno-math-errno
    fno-rounding-math
    fno-signaling-nans
    fno-signed-zeros
    fno-trapping-math
    freciprocal-math
    funsafe-math-optimizations
    # MSVC
    fp:fast
    fp:except-)

# Check fast math flags
set(_phi_fpm_fast_math_flags_supported CACHE INTERNAL "")
foreach(_test ${phi_fast_math_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "_" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_fpm_fast_math_flags_supported
        ${_phi_fpm_fast_math_flags_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

set(phi_precise_math_flags
    fexcess-precision=standard ffp-contract=off ffp-exception-behavior=precise ffp-model=precise
    # MSVC
    fp:precise)

# Check precise math flags
set(_phi_fpm_precise_math_flags_supported CACHE INTERNAL "")
foreach(_test ${phi_precise_math_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "_" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_fpm_precise_math_flags_supported
        ${_phi_fpm_precise_math_flags_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

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
    foreach(flag ${_phi_fpm_fast_math_flags_supported})
      target_compile_options(${fpm_TARGET} ${visibility_scope} ${flag})
    endforeach()

    target_compile_definitions(${fpm_TARGET} ${visibility_scope} "PHI_CONFIG_FPM_FAST")

  elseif(fpm_PRECISE)
    foreach(flag ${_phi_fpm_precise_math_flags_supported})
      target_compile_options(${fpm_TARGET} ${visibility_scope} ${flag})
    endforeach()

    target_compile_definitions(${fpm_TARGET} ${visibility_scope} "PHI_CONFIG_FPM_PRECISE")
  endif()
endfunction()
