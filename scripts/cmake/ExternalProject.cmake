# ExternalProject.cmake

include("CMakeParseArguments")

function(mock_target)
  cmake_parse_arguments(mock "" "NAME;TARGET;BASE_DIR" "" ${ARGN})

  get_target_property(sourceFilesRaw ${mock_TARGET} SOURCES)
      get_target_property(linkLibs ${mock_TARGET} LINK_LIBRARIES)
      get_target_property(includeDirs ${mock_TARGET} INCLUDE_DIRECTORIES)
      get_target_property(interfaceIncludeDirs ${mock_TARGET} INTERFACE_INCLUDE_DIRECTORIES)
      get_target_property(systemIncludeDirs ${mock_TARGET} INTERFACE_SYSTEM_INCLUDE_DIRECTORIES)
      get_target_property(compileDefinitions ${mock_TARGET} COMPILE_DEFINITIONS)
      get_target_property(compileOptions ${mock_TARGET} COMPILE_OPTIONS)
      
      # Convert relative paths to absolute paths
      set(sourceFiles)
      foreach(file ${sourceFilesRaw})
        get_filename_component(path ${file}
                       REALPATH BASE_DIR ${mock_BASE_DIR})
        list(APPEND sourceFiles ${path})
      endforeach()

      add_library(${mock_NAME} STATIC ${sourceFiles})

      if(linkLibs)
        target_link_libraries(${mock_NAME} PRIVATE ${linkLibs})
      endif()
      if(includeDirs)
        target_include_directories(${mock_NAME} PRIVATE ${includeDirs})
      endif()
      if(interfaceIncludeDirs)
        target_include_directories(${mock_NAME} INTERFACE ${interfaceIncludeDirs})
      endif()
      if(systemIncludeDirs)
        set_target_properties(${mock_NAME} PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${systemIncludeDirs}")
      endif()
      if(compileDefinitions)
        target_compile_definitions(${mock_NAME} PRIVATE ${compileDefinitions})
      endif()
      if(compileOptions)
        target_compile_options(${mock_NAME} PRIVATE ${compileOptions})
      endif()
endfunction()

function(phi_add_external_project)
  cmake_parse_arguments(ext "" "PROJECT" "TARGETS" ${ARGN})

  add_subdirectory(${ext_PROJECT} EXCLUDE_FROM_ALL)

  foreach(target ${ext_TARGETS})
    if(NOT TARGET ${target})
      message(FATAL_ERROR "Could not find target ${target} at phi_add_external_project when adding external project ${ext_PROJECT}")
    endif()

    # Mark include directory as system include
    get_target_property(include_dir ${target} INTERFACE_INCLUDE_DIRECTORIES)
    set_target_properties(${target} PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${include_dir}")

    # Link with Phi::ProjectOptions
    get_target_property(target_type ${target} TYPE)
    if(NOT ${target_type} STREQUAL "INTERFACE_LIBRARY")
      target_link_libraries(${target} PRIVATE Phi::ProjectOptions)
    endif()

    # For MSVC we need to set the warnings flag to W0 to silence warnings since MSVC has no concept of
    # system includes
    if(MSVC AND NOT ${target_type} STREQUAL "INTERFACE_LIBRARY")
      target_compile_options(${target} PRIVATE "/W0")
    endif()

    # If the target is a static library, we create a seperate static library with PIC enabled so it can be used
    # from shared libraries
    if(${target_type} STREQUAL "STATIC_LIBRARY")
      set(mock_name ${target}_dyn)

      mock_target(NAME ${mock_name} TARGET ${target} BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${ext_PROJECT}")

      set_target_properties(${mock_name} PROPERTIES POSITION_INDEPENDENT_CODE True)
      set_target_properties(${mock_name} PROPERTIES FOLDER "External/Generated")
    endif()

    # Set folder to external
    set_target_properties(${target} PROPERTIES FOLDER "External")
  endforeach()

  message(STATUS "Added external project ${ext_PROJECT}")
endfunction()
