phi_include_guard()

# target_compile_features (CMake 3.1) Reference:
# https://cmake.org/cmake/help/latest/command/target_compile_features.html
if(${CMAKE_VERSION} VERSION_LESS "3.1")
  macro(target_compile_features)
    # TODO: Implement something?
  endmacro()
endif()
