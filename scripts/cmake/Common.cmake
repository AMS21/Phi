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
    fchar8_t
    fcoroutines
    fconcepts)

set(_common_flags)
foreach(_test ${phi_common_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "," "" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    list(APPEND _common_flags ${PHI_FLAG_PREFIX_CHAR}${_test})
  endif()
endforeach(_test)

# clang and emcc say they accept "-bigobj" but then give a warning
if(PHI_COMPILER_CLANG OR PHI_PLATFORM_EMSCRIPTEN)
  list(REMOVE_ITEM _common_flags ${PHI_FLAG_PREFIX_CHAR}bigobj)
endif()

# Color diagnostics
set(phi_color_diagnostics fcolor-diagnostics fdiagnostics-color=always)

set(_color_diagnostics)
foreach(_test ${phi_color_diagnostics})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "_" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    list(APPEND _color_diagnostics ${PHI_FLAG_PREFIX_CHAR}${_test})
  endif()
endforeach(_test)

set(phi_time_trace_flags ftime-trace)

set(_time_trace_flags)
foreach(_test ${phi_time_trace_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "_" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    list(APPEND _time_trace_flags ${PHI_FLAG_PREFIX_CHAR}${_test})
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
  foreach(flag ${_common_flags})
    target_compile_options(${cf_TARGET} ${visibility_scope} ${flag})
  endforeach(flag)

  # Optionally enable color diagnostics
  if(cf_COLOR_DIAGNOSTICS)
    foreach(flag ${_color_diagnostics})
      target_compile_options(${cf_TARGET} ${visibility_scope} ${flag})
    endforeach(flag)
  endif()

  # Optionall set time trace
  if(cf_TIME_TRACE)
    foreach(flag ${_time_trace_flags})
      target_compile_options(${cf_TARGET} ${visibility_scope} ${flag})
    endforeach(flag)
  endif()
endfunction()
