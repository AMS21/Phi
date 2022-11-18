phi_include_guard()

include(CMakeParseArguments)

# https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Dialect-Options.html
# https://clang.llvm.org/docs/ClangCommandLineReference.html#cmdoption-clang-frtti
# https://learn.microsoft.com/en-us/cpp/build/reference/gr-enable-run-time-type-information
set(phi_no_rtti_flags
    fno-rtti
    # MSVC
    GR-)

# Clang says it accepts GR- and then gives an error
if(PHI_COMPILER_CLANG OR PHI_PLATFORM_EMSCRIPTEN)
  list(REMOVE_ITEM phi_no_rtti_flags "GR-")
endif()

# Check no rtti flags
set(_phi_no_rtti_supported CACHE INTERNAL "")
foreach(_test ${phi_no_rtti_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "_" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_no_rtti_supported
        ${_phi_no_rtti_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

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
    foreach(flag ${_phi_no_rtti_supported})
      target_compile_options(${rtti_TARGET} ${visibility_scope} ${flag})
    endforeach()

    target_compile_definitions(${rtti_TARGET} ${visibility_scope} "PHI_CONFIG_NO_RTTI")
  endif()
endfunction()
