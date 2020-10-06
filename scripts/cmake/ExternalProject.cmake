# ExternalProject.cmake

function(phi_external_project project)
    if (NOT TARGET ${project})
        MESSAGE(FATAL_ERROR "Could not find target ${project}")
    endif()

    # Mark include directory as system include
    get_target_property(include_dir ${project} INTERFACE_INCLUDE_DIRECTORIES)
    set_target_properties(${project} PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${include_dir}")

    # Link with Phi::ProjectOptions
    get_target_property(target_type ${project} TYPE)
    if (NOT ${target_type} STREQUAL "INTERFACE_LIBRARY")
        target_link_libraries(${project} PRIVATE Phi::ProjectOptions)
    endif()

    # For MSVC we need to set the warnings flag to W0 to silence warnings since MSVC has no concept of system includes
    target_compile_options(${project} INTERFACE "/W0")

    message(STATUS "Added external project ${project}")
endfunction()
