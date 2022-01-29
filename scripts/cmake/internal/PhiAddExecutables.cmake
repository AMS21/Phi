phi_include_guard()

include(CMakeParseArguments)
include(internal/PhiError)

function(phi_add_executable)
  # Command line arguments
  cmake_parse_arguments(
    ae
    "EXCLUDE_FROM_ALL;NO_GROUP"
    "NAME;FOLDER;ALIAS_TARGET"
    "SOURCES;HEADERS;PUBLIC_LINK_LIBRARIES;PRIVATE_LINK_LIBRARIES;INTERFACE_LINK_LIBRARIES;PUBLIC_INCLUDE_DIRS;PRIVATE_INCLUDE_DIRS;INTERFACE_INCLUDE_DIRS"
    ${ARGN})

  # Check required arguments
  if(NOT ae_NAME)
    phi_error("phi_add_executable: You must specify a name using NAME")
  endif()

  # Add required arguments
  set(command ${ae_NAME})

  # Add optional EXCLUDE_FROM_ALL
  if(ae_EXCLUDE_FROM_ALL)
    set(command ${command} EXCLUDE_FROM_ALL)
  endif()

  # Add sources and headers
  set(command ${command} ${ae_SOURCES} ${ae_HEADERS})

  # Add executable
  add_executable(${command})

  # Set standard
  phi_set_standard_flag(${ae_NAME})

  # Group source files
  if(NOT ae_NO_GROUP)
    if(${CMAKE_VERSION} VERSION_GREATER "3.7")
      # TREE option was introduced with 3.8
      source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ae_SOURCES} ${ae_HEADERS})
    endif()
  endif()

  # Add optional alias target
  if(ae_ALIAS_TARGET)
    add_executable("${ae_ALIAS_TARGET}" ALIAS ${ae_NAME})
  endif()

  # Set optional folder
  if(ae_FOLDER)
    set_target_properties(${ae_NAME} PROPERTIES FOLDER "${ae_FOLDER}")
  endif()

  # Add optional private link libraries
  if(ae_PUBLIC_LINK_LIBRARIES)
    target_link_libraries(${ae_NAME} PUBLIC "${ae_PUBLIC_LINK_LIBRARIES}")
  endif()

  # Add optional private link libraries
  if(ae_PRIVATE_LINK_LIBRARIES)
    target_link_libraries(${ae_NAME} PRIVATE "${ae_PRIVATE_LINK_LIBRARIES}")
  endif()

  # Add optional interface link libraries
  if(ae_INTERFACE_LINK_LIBRARIES)
    target_link_libraries(${ae_NAME} INTERFACE "${ae_INTERFACE_LINK_LIBRARIES}")
  endif()

  # Add optional public include directories
  if(ae_PUBLIC_INCLUDE_DIRS)
    target_include_directories(${ae_NAME} PUBLIC "${ae_PUBLIC_INCLUDE_DIRS}")
  endif()

  # Add optional private include directories
  if(ae_PRIVATE_INCLUDE_DIRS)
    target_include_directories(${ae_NAME} PRIVATE "${ae_PRIVATE_INCLUDE_DIRS}")
  endif()

  # Add optional interface include directories
  if(ae_INTERFACE_INCLUDE_DIRS)
    target_include_directories(${ae_NAME} INTERFACE "${ae_INTERFACE_INCLUDE_DIRS}")
  endif()
endfunction()
