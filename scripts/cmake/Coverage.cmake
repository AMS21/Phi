phi_include_guard()

include(CMakeParseArguments)
include(CheckLinkerFlag)
include(internal/PhiCheckCXXCompilerFlag)

set(phi_coverage_compile_flags -O0 -g3 -fno-inline -fno-inline-functions -fprofile-abs-path)

set(phi_coverage_link_flags -fprofile-instr-generate -fcoverage-mapping --coverage)

# Check for support of coverage compile flags
set(_coverage_compile_flags)
foreach(_test ${phi_coverage_compile_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${_test} "PHI_HAS_FLAG${_testName}")

  if(PHI_HAS_FLAG${_testName})
    list(APPEND _coverage_compile_flags ${_test})
  endif()
endforeach()

# Check for support of coverage linker flags
set(_coverage_linker_flags)
foreach(_test ${phi_coverage_link_flags})
  string(REPLACE "--" "_" _testName ${_test})
  string(REPLACE "-" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  check_linker_flag(CXX ${_test} "PHI_HAS_FLAG${_testName}")

  if(PHI_HAS_FLAG${_testName})
    list(APPEND _coverage_linker_flags ${_test})
  endif()
endforeach()

# Remove '--coverage' for clang since it produces a 'Wunused-command-line-argument' warning
if(PHI_COMPILER_CLANG)
  list(REMOVE_ITEM _coverage_linker_flags "--coverage")
endif()

function(phi_target_enable_coverage)
  # Command line arguments
  cmake_parse_arguments(cov "" "TARGET" "" ${ARGN})

  # Check required arguments
  if(NOT cov_TARGET)
    phi_error("phi_target_enable_coverage: You must specify TARGET")
  endif()

  # Check if target is actually valid
  if(NOT TARGET ${cov_TARGET})
    phi_error(
      "phi_target_enable_coverage: The specified target \"${cov_TARGET}\" doesn't seem to be valid")
  endif()

  # Check if we actually have coverage flags
  if(NOT _coverage_compile_flags AND _coverage_linker_flags)
    phi_warn(
      "phi_target_enable_coverage: There we no coverage flags found for your compiler \"${CMAKE_CXX_COMPILER_ID}\"!"
    )
  endif()

  # Get target type
  get_property(
    target_type
    TARGET ${cov_TARGET}
    PROPERTY TYPE)

  if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
    set(visibility_scope INTERFACE)
  else()
    set(visibility_scope PRIVATE)
  endif()

  # Set coverage compile flags
  foreach(flag ${_coverage_compile_flags})
    target_compile_options(${cov_TARGET} ${visibility_scope} ${flag})
  endforeach()

  # Set coverage linker flags
  foreach(flag ${_coverage_linker_flags})
    target_compile_options(${cov_TARGET} ${visibility_scope} ${flag})
    target_link_options(${cov_TARGET} ${visibility_scope} ${flag})
  endforeach()

  # Replace always inline with never inline
  target_compile_definitions(${cov_TARGET} ${visibility_scope}
                                           PHI_CONFIG_ALWAYS_INLINE_OVERWRITE=PHI_NEVER_INLINE)
endfunction()
