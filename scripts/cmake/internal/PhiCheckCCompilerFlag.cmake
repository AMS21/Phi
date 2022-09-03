phi_include_guard()

include(internal/PhiCheckCompilerFlag)

# https://github.com/Kitware/CMake/blob/master/Modules/CheckCCompilerFlag.cmake
macro(phi_check_c_compiler_flag _FLAG _RESULT)
  phi_check_compiler_flag(C "${_FLAG}" ${_RESULT})
endmacro()
