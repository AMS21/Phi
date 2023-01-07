phi_include_guard()

include(CMakeParseArguments)
include(internal/CheckCompilerFlagCommonPatterns)
include(internal/CheckSourceCompiles)
include(internal/SetCacheValue)
include(internal/CheckFlagCommonConfig)

# https://github.com/Kitware/CMake/blob/master/Modules/Internal/CheckCompilerFlag.cmake
function(phi_check_compiler_flag _lang _flag _var)
  # Parse extra arguments
  cmake_parse_arguments(PARSE_ARGV 3 CHECK_COMPILER_FLAG "" "OUTPUT_VARIABLE" "")

  phi_check_flag_common_init("check_compiler_flag" ${_lang} _lang_src _lang_fail_regex)

  set(CMAKE_REQUIRED_DEFINITIONS ${_flag})

  phi_check_compiler_flag_common_patterns(_common_patterns)
  phi_check_source_compiles(
    ${_lang}
    "${_lang_src}"
    ${_var}
    ${_lang_fail_regex}
    ${_common_patterns}
    OUTPUT_VARIABLE
    _output)

  if(CHECK_COMPILER_FLAG_OUTPUT_VARIABLE)
    set(${CHECK_COMPILER_FLAG_OUTPUT_VARIABLE}
        "${_output}"
        PARENT_SCOPE)
  endif()

  phi_check_flag_common_finish()
endfunction()
