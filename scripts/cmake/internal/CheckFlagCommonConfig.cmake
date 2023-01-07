phi_include_guard()

# Reference:
# https://github.com/Kitware/CMake/blob/master/Modules/Internal/CheckFlagCommonConfig.cmake
macro(PHI_CHECK_FLAG_COMMON_INIT _FUNC _LANG _SRC _PATTERNS)
  if("${_LANG}" STREQUAL "C")
    set(${_SRC} "int main(void) { return 0; }")
    set(${_PATTERNS} FAIL_REGEX "command[ -]line option .* is valid for .* but not for C"
                     FAIL_REGEX "-Werror=.* argument .* is not valid for C")
  elseif("${_LANG}" STREQUAL "CXX")
    set(${_SRC} "int main() { return 0; }")
    set(${_PATTERNS} FAIL_REGEX "command[ -]line option .* is valid for .* but not for C\\+\\+"
                     FAIL_REGEX "-Werror=.* argument .* is not valid for C\\+\\+")
  elseif("${_LANG}" STREQUAL "CUDA")
    set(${_SRC} "__host__ int main() { return 0; }")
    set(${_PATTERNS}
        FAIL_REGEX "command[ -]line option .* is valid for .* but not for C\\+\\+" # Host GNU
        FAIL_REGEX "argument unused during compilation: .*") # Clang
  elseif("${_LANG}" STREQUAL "Fortran")
    set(${_SRC} "       program test\n       stop\n       end program")
    set(${_PATTERNS} FAIL_REGEX "command[ -]line option .* is valid for .* but not for Fortran")
  elseif("${_LANG}" STREQUAL "HIP")
    set(${_SRC} "__host__ int main() { return 0; }")
    set(${_PATTERNS} FAIL_REGEX "argument unused during compilation: .*") # Clang
  elseif("${_LANG}" STREQUAL "OBJC")
    set(${_SRC}
        [=[
      #ifndef __OBJC__
      #  error "Not an Objective-C compiler"
      #endif
      int main(void) { return 0; }]=])
    set(${_PATTERNS}
        FAIL_REGEX "command[ -]line option .* is valid for .* but not for Objective-C" # GNU
        FAIL_REGEX "argument unused during compilation: .*") # Clang
  elseif("${_LANG}" STREQUAL "OBJCXX")
    set(${_SRC}
        [=[
      #ifndef __OBJC__
      #  error "Not an Objective-C++ compiler"
      #endif
      int main(void) { return 0; }]=])
    set(${_PATTERNS}
        FAIL_REGEX "command[ -]line option .* is valid for .* but not for Objective-C\\+\\+" # GNU
        FAIL_REGEX "argument unused during compilation: .*") # Clang
  elseif("${_LANG}" STREQUAL "ISPC")
    set(${_SRC} "float func(uniform int32, float a) { return a / 2.25; }")
  elseif("${_LANG}" STREQUAL "Swift")
    set(${_SRC} "func blarpy() { }")
  else()
    message(SEND_ERROR "${_FUNC}: ${_LANG}: unknown language.")
    return()
  endif()

  get_property(_supported_languages GLOBAL PROPERTY ENABLED_LANGUAGES)
  if(NOT "${_LANG}" IN_LIST _supported_languages)
    message(SEND_ERROR "${_FUNC}: ${_LANG}: needs to be enabled before use.")
    return()
  endif()
  # Normalize locale during test compilation.
  set(_CFCC_locale_vars LC_ALL LC_MESSAGES LANG)
  foreach(v IN LISTS _CFCC_locale_vars)
    set(_PHI_CHECK_FLAG_COMMON_CONFIG_locale_vars_saved_${v} "$ENV{${v}}")
    set(ENV{${v}} C)
  endforeach()
endmacro()

macro(PHI_CHECK_FLAG_COMMON_FINISH)
  foreach(v IN LISTS _CFCC_locale_vars)
    set(ENV{${v}} ${_PHI_CHECK_FLAG_COMMON_CONFIG_locale_vars_saved_${v}})
  endforeach()
endmacro()
