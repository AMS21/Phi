phi_include_guard()

include(CMakeParseArguments)

# common useful flags
set(phi_common_flags
    bigobj
    Wa,-mbig-obj # https://digitalkarabela.com/mingw-w64-how-to-fix-file-too-big-too-many-sections/
    fmacro-backtrace-limit=0
    fms-extensions
    fdeclspec
    fborland-extensions
    flarge-source-files)

# common useful cxx flags
set(phi_common_cxx_only_flags fcoroutines fconcepts fchar8_t)

# clang and emcc say they accept "-bigobj" but then give a warning
if(PHI_COMPILER_CLANG OR PHI_PLATFORM_EMSCRIPTEN)
  list(REMOVE_ITEM phi_common_flags bigobj)
endif()

# Old emscripten versions don't seem to like the `-Wa,-mbig-obj` flag
if(PHI_COMPILER_EMCC AND "${PHI_EMCC_VERSION}" VERSION_LESS "1.39")
  list(REMOVE_ITEM phi_common_flags Wa,-mbig-obj)
endif()

set(_phi_common_flags_supported CACHE INTERNAL "")
foreach(_test ${phi_common_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "," "" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_common_flags_supported
        ${_phi_common_flags_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

set(_phi_common_cxx_flags_supported CACHE INTERNAL "")
foreach(_test ${phi_common_cxx_only_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "," "" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_common_cxx_flags_supported
        ${_phi_common_cxx_flags_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

# Color diagnostics
set(phi_color_diagnostics fcolor-diagnostics fdiagnostics-color=always)

set(_phi_color_diagnostics_supported CACHE INTERNAL "")
foreach(_test ${phi_color_diagnostics})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "_" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_color_diagnostics_supported
        ${_phi_color_diagnostics_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

set(phi_time_trace_flags ftime-trace)

set(_phi_time_trace_flags_supported CACHE INTERNAL "")
foreach(_test ${phi_time_trace_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "_" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_time_trace_flags_supported
        ${_phi_time_trace_flags_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

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
  foreach(flag ${_phi_common_flags_supported})
    target_compile_options(${cf_TARGET} ${visibility_scope} ${flag})
  endforeach(flag)

  # Get linker language
  get_property(
    target_linker_language
    TARGET ${cf_TARGET}
    PROPERTY LINKER_LANGUAGE)

  # Set cxx flags
  if("${target_linker_language}" STREQUAL "CXX" OR "${target_linker_language}" STREQUAL "")
    foreach(flag ${_phi_common_cxx_flags_supported})
      target_compile_options(${cf_TARGET} ${visibility_scope} ${flag})
    endforeach(flag)
  endif()

  # Optionally enable color diagnostics
  if(cf_COLOR_DIAGNOSTICS)
    foreach(flag ${_phi_color_diagnostics_supported})
      target_compile_options(${cf_TARGET} ${visibility_scope} ${flag})
    endforeach(flag)
  endif()

  # Optionall set time trace
  if(cf_TIME_TRACE)
    foreach(flag ${_phi_time_trace_flags_supported})
      target_compile_options(${cf_TARGET} ${visibility_scope} ${flag})
    endforeach(flag)
  endif()
endfunction()
