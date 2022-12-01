phi_include_guard()

include(CMakeParseArguments)
include(CheckLinkerFlag)
include(internal/PhiCheckCXXCompilerFlag)

# https://clang.llvm.org/docs/SourceBasedCodeCoverage.html
# https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html

set(phi_coverage_compile_flags fno-common fno-inline fno-inline-functions fno-omit-frame-pointer
                               fprofile-abs-path)

set(phi_coverage_link_flags -fprofile-arcs -ftest-coverage -fprofile-instr-generate
                            -fcoverage-mapping --coverage)

# Remove '--coverage' for clang since it produces a 'Wunused-command-line-argument' warning
if(PHI_COMPILER_CLANG)
  list(REMOVE_ITEM phi_coverage_link_flags "--coverage")
endif()

# Check for support of coverage compile flags
set(_phi_coverage_compile_flags_supported CACHE INTERNAL "")
foreach(_test ${phi_coverage_compile_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_coverage_compile_flags_supported
        ${_phi_coverage_compile_flags_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach()

# Check for support of coverage linker flags
set(_phi_coverage_linker_flags_supported CACHE INTERNAL "")
foreach(_test ${phi_coverage_link_flags})
  string(REPLACE "--" "_" _testName ${_test})
  string(REPLACE "-" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  check_linker_flag(CXX ${_test} "PHI_HAS_FLAG${_testName}")

  if(PHI_HAS_FLAG${_testName})
    set(_phi_coverage_linker_flags_supported
        ${_phi_coverage_linker_flags_supported};${_test}
        CACHE INTERNAL "")
  endif()
endforeach()

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
  if(NOT _phi_coverage_compile_flags_supported AND _phi_coverage_linker_flags_supported)
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
  foreach(flag ${_phi_coverage_compile_flags_supported})
    target_compile_options(${cov_TARGET} ${visibility_scope} ${flag})
  endforeach()

  # Set coverage linker flags
  foreach(flag ${_phi_coverage_linker_flags_supported})
    target_compile_options(${cov_TARGET} ${visibility_scope} ${flag})
    target_link_options(${cov_TARGET} ${visibility_scope} ${flag})
  endforeach()

  # Replace always inline with just inline
  target_compile_definitions(${cov_TARGET} ${visibility_scope}
                                           PHI_CONFIG_ALWAYS_INLINE_OVERWRITE=inline)
  # Add define to inform user that it's a coverage build
  target_compile_definitions(${cov_TARGET} ${visibility_scope} PHI_CONFIG_COVERAGE_BUILD)
endfunction()
