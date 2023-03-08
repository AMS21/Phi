# ExternalProject.cmake

phi_include_guard()

include(CMakeParseArguments)

function(phi_add_external_project)
  cmake_parse_arguments(ext "" "PROJECT" "TARGETS" ${ARGN})

  add_subdirectory(${ext_PROJECT} EXCLUDE_FROM_ALL)

  foreach(target ${ext_TARGETS})
    if(NOT TARGET ${target})
      phi_error(
        "Could not find target ${target} at phi_add_external_project when adding external project ${ext_PROJECT}"
      )
    endif()

    # Mark include directory as system include
    get_target_property(include_dir ${target} INTERFACE_INCLUDE_DIRECTORIES)
    set_target_properties(${target} PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES
                                               "${include_dir}")

    # Silence all warnings
    if(NOT ${target_type} STREQUAL "INTERFACE_LIBRARY")
      target_compile_options(${target} PRIVATE ${phi_disable_all_warnings_flag})
    endif()

    # Set folder to external
    if(NOT ${CMAKE_VERSION} VERSION_LESS "3.17" OR NOT ${target_type} STREQUAL "INTERFACE_LIBRARY")
      set_target_properties(${target} PROPERTIES FOLDER "External")
    endif()
  endforeach()

  phi_log("Added external project ${ext_PROJECT}")
endfunction()
