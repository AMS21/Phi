phi_include_guard()

# Get all the CMake targets in the given directory
macro(phi_get_all_targets_recursive targets dir)
  get_property(
    subdirectories
    DIRECTORY ${dir}
    PROPERTY SUBDIRECTORIES)
  foreach(subdir ${subdirectories})
    phi_get_all_targets_recursive(${targets} ${subdir})
  endforeach()

  get_property(
    current_targets
    DIRECTORY ${dir}
    PROPERTY BUILDSYSTEM_TARGETS)
  list(APPEND ${targets} ${current_targets})
endmacro()

# Get all the CMake targets
function(phi_get_all_targets var)
  set(targets)
  phi_get_all_targets_recursive(targets ${CMAKE_CURRENT_SOURCE_DIR})
  set(${var}
      ${targets}
      PARENT_SCOPE)
endfunction()
