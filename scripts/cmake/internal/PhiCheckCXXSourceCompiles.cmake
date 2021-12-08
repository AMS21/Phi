phi_include_guard()

include(internal/PhiCheckSourceCompiles)

# https://github.com/Kitware/CMake/blob/master/Modules/CheckCXXSourceCompiles.cmake
macro(phi_check_cxx_source_compiles SOURCE VAR)
  phi_check_source_compiles(CXX "${SOURCE}" ${VAR} ${ARGN})
endmacro()
