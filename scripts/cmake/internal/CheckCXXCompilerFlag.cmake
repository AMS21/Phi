phi_include_guard()

include(internal/CheckCompilerFlag)

# https://github.com/Kitware/CMake/blob/master/Modules/CheckCXXCompilerFlag.cmake
macro(phi_check_cxx_compiler_flag _FLAG _RESULT)
  phi_check_compiler_flag(CXX "${_FLAG}" ${_RESULT})
endmacro()
