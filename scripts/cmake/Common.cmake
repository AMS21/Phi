phi_include_guard()

include(CMakeParseArguments)

# https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Dialect-Options.html
# https://digitalkarabela.com/mingw-w64-how-to-fix-file-too-big-too-many-sections/

# common useful flags
set(phi_common_flags
    bigobj
    Wa,-mbig-obj
    fborland-extensions
    fdeclspec
    flarge-source-files
    fmacro-backtrace-limit=0
    fms-extensions
    fstrong-eval-order
    pipe
    MP # https://learn.microsoft.com/cpp/build/reference/mp-build-with-multiple-processes
    Zc:preprocessor # https://learn.microsoft.com/cpp/build/reference/zc-preprocessor
    Zc:__cplusplus # https://learn.microsoft.com/cpp/build/reference/zc-cplusplus
    Zc:char8_t # https://learn.microsoft.com/cpp/build/reference/zc-char8-t
    Zc:rvalueCast # https://learn.microsoft.com/cpp/build/reference/zc-rvaluecast-enforce-type-conversion-rules
    # https://learn.microsoft.com/cpp/build/reference/external-external-headers-diagnostics
    experimental:external
    external:W0
    external:anglebrackets
    analyze:external- # https://learn.microsoft.com/cpp/build/reference/analyze-code-analysis
    FC # https://learn.microsoft.com/cpp/build/reference/fc-full-path-of-source-code-file-in-diagnostics
)

# common useful cxx flags
set(phi_common_cxx_only_flags faligned-new fsized-deallocation fchar8_t fconcepts fcoroutines)

# clang and emcc say they accept "-bigobj" but then give a warning
if(PHI_COMPILER_CLANG OR PHI_PLATFORM_EMSCRIPTEN)
  list(REMOVE_ITEM phi_common_flags bigobj)
endif()

# Old emscripten versions don't seem to like the `-Wa,-mbig-obj` flag
if(PHI_COMPILER_EMCC AND "${PHI_EMCC_VERSION}" VERSION_LESS "1.39")
  list(REMOVE_ITEM phi_common_flags Wa,-mbig-obj)
endif()

# MSVC only options which cause problems for other compilers
if(NOT PHI_COMPILER_MSVC)
  list(
    REMOVE_ITEM
    phi_common_flags
    MP
    experimental:external
    external:W0
    external:anglebrackets
    analyze:external-
    FC)
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
set(phi_color_diagnostics fdiagnostics-color=always fcolor-diagnostics)

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

    # Don't continue
    break()
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

# Extra disabled warnings for MSVC stl
set(phi_msvc_stl_extra_disable
    4365 # 'action' : conversion from 'type_1' to 'type_2', signed/unsigned mismatch -
         # https://learn.microsoft.com/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4365
    4668 # 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives' -
         # https://learn.microsoft.com/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4668
    5262 # implicit fall-through occurs here; are you missing a break statement? Use [[fallthrough]]
         # when a break statement is intentionally omitted between cases -
         # https://learn.microsoft.com/cpp/error-messages/compiler-warnings/compiler-warnings-by-compiler-version
)

set(_phi_msvc_stl_extra_disable_supported CACHE INTERNAL "")
if(PHI_COMPILER_MSVC)
  foreach(_test ${phi_msvc_stl_extra_disable})
    phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}wd${_test} "PHI_HAS_FLAG_WD${_test}")

    if(PHI_HAS_FLAG_WD${_test})
      set(_phi_msvc_stl_extra_disable_supported
          "${_phi_msvc_stl_extra_disable_supported} ${_test}"
          CACHE INTERNAL "")
    endif()
  endforeach(_test)
endif()

string(STRIP "${_phi_msvc_stl_extra_disable_supported}" _phi_msvc_stl_extra_disable_supported)

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

  # Disable warnings in the msvc stl
  if(PHI_COMPILER_MSVC)
    target_compile_definitions(
      "${cf_TARGET}"
      ${visibility_scope} "_STL_EXTRA_DISABLED_WARNINGS=${_phi_msvc_stl_extra_disable_supported}"
      "_ALLOW_RTCc_IN_STL")
  endif()
endfunction()
