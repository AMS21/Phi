# ExternalProject.cmake

include("CMakeParseArguments")

function(phi_add_external_project)
  cmake_parse_arguments(ext "" "PROJECT" "TARGETS" ${ARGN})

  add_subdirectory(${ext_PROJECT} EXCLUDE_FROM_ALL)

  foreach(target ${ext_TARGETS})
    if(NOT TARGET ${target})
      message(
        FATAL_ERROR
          "[Phi]: Could not find target ${target} at phi_add_external_project when adding external project ${ext_PROJECT}"
      )
    endif()

    # Mark include directory as system include
    get_target_property(include_dir ${target} INTERFACE_INCLUDE_DIRECTORIES)
    set_target_properties(${target} PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES
                                               "${include_dir}")

    # Link with Phi::ProjectOptions
    get_target_property(target_type ${target} TYPE)
    if(NOT ${target_type} STREQUAL "INTERFACE_LIBRARY")
      target_link_libraries(${target} PRIVATE Phi::ProjectOptions)
    endif()

    # For MSVC we need to set the warnings flag to W0 to silence warnings since MSVC has no concept
    # of system includes
    if(MSVC AND NOT ${target_type} STREQUAL "INTERFACE_LIBRARY")
      target_compile_options(${target} PRIVATE "/W0")
    endif()

    # Set folder to external
    set_target_properties(${target} PROPERTIES FOLDER "External")
  endforeach()

  message(STATUS "[Phi]: Added external project ${ext_PROJECT}")
endfunction()
