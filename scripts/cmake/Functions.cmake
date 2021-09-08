phi_include_guard()

include(CMakeParseArguments)

# Log a trace message
function(phi_trace text)
  message(STATUS "[Phi]: ${text}")
endfunction()

# Log a specifc information
function(phi_log text)
  message(STATUS "[Phi]: ${text}")
endfunction()

# Give a warning
function(phi_warn text)
  message(WARNING "[Phi] Warning: ${text}")
endfunction()

# Give a configuration error
function(phi_error text)
  message(FATAL_ERROR "[Phi]: Error: ${text}")
endfunction()

function(phi_set_cache_value)
  # Commandline
  cmake_parse_arguments(scv "" "NAME;VALUE" "" ${ARGN})

  # Check required arguments
  if(NOT DEFINED scv_NAME)
    phi_error("phi_set_cache_value: NAME must be defined.")
  endif()

  if(NOT DEFINED scv_VALUE)
    phi_error("phi_set_cache_value: VALUE must be defined.")
  endif()

  set(${scv_NAME}
      ${scv_VALUE}
      CACHE INTERNAL "")
endfunction()

function(phi_option name help_string type default_value)
  set(${name}
      ${default_value}
      CACHE ${type} "${help_string}")
endfunction()

function(phi_add_library)
  # Command line arguments
  cmake_parse_arguments(
    al
    "STATIC;SHARED;MODULE;EXCLUDE_FROM_ALL"
    "NAME;FOLDER;ALIAS_TARGET"
    "SOURCES;HEADERS;PUBLIC_LINK_LIBRARIES;PRIVATE_LINK_LIBRARIES;INTERFACE_LINK_LIBRARIES;PUBLIC_INCLUDE_DIRS;PRIVATE_INCLUDE_DIRS;INTERFACE_INCLUDE_DIRS"
    ${ARGN})

  # Check required arguments
  if(NOT DEFINED al_NAME)
    phi_error("phi_add_library: You must specify a name using NAME")
  endif()

  if(NOT DEFINED al_STATIC
     AND NOT DEFINED al_SHARED
     AND NOT DEFINED al_MODULE)
    phi_error("phi_add_library: You must specify either STATIC, SHARED or MODULE")
  endif()

  if(NOT DEFINED al_SOURCES)
    phi_error("phi_add_library: No sources specified using SOURCES")
  endif()

  # Add required arguments
  set(command ${al_NAME})

  # Add type
  if(DEFINED al_STATIC)
    set(command ${command} STATIC)
  elseif(DEFINED al_SHARED)
    set(command ${command} SHARED)
  elseif(DEFINED al_MODULE)
    set(command ${command} MODULE)
  endif()

  # Add optional EXCLUDE_FROM_ALL
  if(DEFINED al_EXCLUDE_FROM_ALL)
    set(command ${command} EXCLUDE_FROM_ALL)
  endif()

  # Add sources and headers
  set(command ${command} ${al_SOURCES} ${al_HEADERS})

  # Add library
  add_library(${command})

  # Group source files
  if(${CMAKE_VERSION} VERSION_GREATER "3.7")
    # TREE option was introduced with 3.8
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${al_SOURCES} ${al_HEADERS})
  endif()

  # Add optional alias target
  if(DEFINED al_ALIAS_TARGET)
    add_library("${al_ALIAS_TARGET}" ALIAS ${al_NAME})
  endif()

  # Set optional folder
  if(DEFINED al_FOLDER)
    set_target_properties(${al_NAME} PROPERTIES FOLDER "${al_FOLDER}")
  endif()

  # Add optional private link libraries
  if(DEFINED al_PUBLIC_LINK_LIBRARIES)
    target_link_libraries(${al_NAME} PUBLIC "${al_PUBLIC_LINK_LIBRARIES}")
  endif()

  # Add optional private link libraries
  if(DEFINED al_PRIVATE_LINK_LIBRARIES)
    target_link_libraries(${al_NAME} PRIVATE "${al_PRIVATE_LINK_LIBRARIES}")
  endif()

  # Add optional interface link libraries
  if(DEFINED al_INTERFACE_LINK_LIBRARIES)
    target_link_libraries(${al_NAME} INTERFACE "${al_INTERFACE_LINK_LIBRARIES}")
  endif()

  # Add optional public include directories
  if(DEFINED al_PUBLIC_INCLUDE_DIRS)
    target_include_directories(${al_NAME} PUBLIC "${al_PUBLIC_INCLUDE_DIRS}")
  endif()

  # Add optional private include directories
  if(DEFINED al_PRIVATE_INCLUDE_DIRS)
    target_include_directories(${al_NAME} PRIVATE "${al_PRIVATE_INCLUDE_DIRS}")
  endif()

  # Add optional interface include directories
  if(DEFINED al_INTERFACE_INCLUDE_DIRS)
    target_include_directories(${al_NAME} INTERFACE "${al_INTERFACE_INCLUDE_DIRS}")
  endif()
endfunction(phi_add_library)

# Support for older CMake versions

# target_link_options (CMake 3.13) Reference:
# https://cmake.org/cmake/help/latest/command/target_link_options.html
if(${CMAKE_VERSION} VERSION_LESS "3.13")
  macro(target_link_options)
    target_link_libraries(${ARGN})
  endmacro(target_link_options)
endif()

function(phi_add_executable)
  # Command line arguments
  cmake_parse_arguments(
    ae
    "EXCLUDE_FROM_ALL"
    "NAME;FOLDER;ALIAS_TARGET"
    "SOURCES;HEADERS;PUBLIC_LINK_LIBRARIES;PRIVATE_LINK_LIBRARIES;INTERFACE_LINK_LIBRARIES;PUBLIC_INCLUDE_DIRS;PRIVATE_INCLUDE_DIRS;INTERFACE_INCLUDE_DIRS"
    ${ARGN})

  # Check required arguments
  if(NOT DEFINED ae_NAME)
    phi_error("phi_add_executable: You must specify a name using NAME")
  endif()

  # Add required arguments
  set(command ${ae_NAME})

  # Add optional EXCLUDE_FROM_ALL
  if(DEFINED ae_EXCLUDE_FROM_ALL)
    set(command ${command} EXCLUDE_FROM_ALL)
  endif()

  # Add sources and headers
  set(command ${command} ${ae_SOURCES} ${ae_HEADERS})

  # Add executable
  add_executable(${command})

  # Group source files
  if(${CMAKE_VERSION} VERSION_GREATER "3.7")
    # TREE option was introduced with 3.8
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ae_SOURCES} ${ae_HEADERS})
  endif()

  # Add optional alias target
  if(DEFINED ae_ALIAS_TARGET)
    add_executable("${ae_ALIAS_TARGET}" ALIAS ${ae_NAME})
  endif()

  # Set optional folder
  if(DEFINED ae_FOLDER)
    set_target_properties(${ae_NAME} PROPERTIES FOLDER "${ae_FOLDER}")
  endif()

  # Add optional private link libraries
  if(DEFINED ae_PUBLIC_LINK_LIBRARIES)
    target_link_libraries(${ae_NAME} PUBLIC "${ae_PUBLIC_LINK_LIBRARIES}")
  endif()

  # Add optional private link libraries
  if(DEFINED ae_PRIVATE_LINK_LIBRARIES)
    target_link_libraries(${ae_NAME} PRIVATE "${ae_PRIVATE_LINK_LIBRARIES}")
  endif()

  # Add optional interface link libraries
  if(DEFINED ae_INTERFACE_LINK_LIBRARIES)
    target_link_libraries(${ae_NAME} INTERFACE "${ae_INTERFACE_LINK_LIBRARIES}")
  endif()

  # Add optional public include directories
  if(DEFINED ae_PUBLIC_INCLUDE_DIRS)
    target_include_directories(${ae_NAME} PUBLIC "${ae_PUBLIC_INCLUDE_DIRS}")
  endif()

  # Add optional private include directories
  if(DEFINED ae_PRIVATE_INCLUDE_DIRS)
    target_include_directories(${ae_NAME} PRIVATE "${ae_PRIVATE_INCLUDE_DIRS}")
  endif()

  # Add optional interface include directories
  if(DEFINED ae_INTERFACE_INCLUDE_DIRS)
    target_include_directories(${ae_NAME} INTERFACE "${ae_INTERFACE_INCLUDE_DIRS}")
  endif()
endfunction()
