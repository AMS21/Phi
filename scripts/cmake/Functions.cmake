phi_include_guard()

include(CMakeParseArguments)

# reference https://cmake.org/cmake/help/latest/command/message.html
function(phi_message _opt_mode)
  set(_msg_mode)
  set(_msg_text)

  if(${_opt_mode} STREQUAL "FATAL_ERROR")
    set(_msg_mode "FATAL_ERROR")
  elseif(${_opt_mode} STREQUAL "SEND_ERROR")
    set(_msg_mode "SEND_ERROR")
  elseif(${_opt_mode} STREQUAL "WARNING")
    set(_msg_mode "WARNING")
  elseif(${_opt_mode} STREQUAL "AUTHOR_WARNING")
    set(_msg_mode "AUTHOR_WARNING")
  elseif(${_opt_mode} STREQUAL "DEPRECATED")
    set(_msg_mode "DEPRECATED")
  elseif(${_opt_mode} STREQUAL "STATUS")
    set(_msg_mode "STATUS")

    # CMake >= 3.15
  elseif(${_opt_mode} STREQUAL "NOTICE")
    set(_msg_mode "NOTICE")
  elseif(${_opt_mode} STREQUAL "VERBOSE")
    set(_msg_mode "VERBOSE")
  elseif(${_opt_mode} STREQUAL "DEBUG")
    set(_msg_mode "DEBUG")
  elseif(${_opt_mode} STREQUAL "TRACE")
    set(_msg_mode "TRACE")

    # Reporting checks (CMake >= 3.17)
  elseif(${_opt_mode} STREQUAL "CHECK_START")
    set(_msg_mode "CHECK_START")
  elseif(${_opt_mode} STREQUAL "CHECK_PASS")
    set(_msg_mode "CHECK_PASS")
  elseif(${_opt_mode} STREQUAL "CHECK_FAIL")
    set(_msg_mode "CHECK_FAIL")

  else()
    set(_msg_text ${_opt_mode})
  endif()

  message(${_opt_mode} ${_msg_text} ${ARGN})
endfunction()

# Log a trace message
function(phi_trace text)
  phi_message(STATUS "[Phi]: ${text}")
endfunction()

# Log a specifc information
function(phi_log text)
  phi_message(STATUS "[Phi]: ${text}")
endfunction()

# Give a warning
function(phi_warn text)
  phi_message(WARNING "[Phi] Warning: ${text}")
endfunction()

# Give a configuration error
function(phi_error text)
  phi_message(FATAL_ERROR "[Phi]: Error: ${text}")
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

  # Set standard
  phi_set_standard_flag(${al_NAME})

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

# target_compile_feaetures (CMake 3.1) Reference:
# https://cmake.org/cmake/help/latest/command/target_compile_features.html
if(${CMAKE_VERSION} VERSION_LESS "3.1")
  macro(target_compile_features)
    # TODO: Implement something?
  endmacro()
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
  if(${CMAKE_VERSION} VERSION_GREATER "3.7")
    # TREE option was introduced with 3.8
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ae_SOURCES} ${ae_HEADERS})
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

# CheckCXXSourceCompiles Sources:
# https://github.com/Kitware/CMake/blob/master/Modules/CheckCXXSourceCompiles.cmake
# https://github.com/Kitware/CMake/blob/master/Modules/Internal/CheckSourceCompiles.cmake
function(phi_check_cxx_source_compiles _source _var)
  set(_FAIL_REGEX)
  set(_SRC_EXT)
  set(_key)
  foreach(arg ${ARGN})
    if("${arg}" MATCHES "^(FAIL_REGEX|SRC_EXT)$")
      set(_key "${arg}")
    elseif(_key STREQUAL "FAIL_REGEX")
      list(APPEND _FAIL_REGEX "${arg}")
    elseif(_key STREQUAL "SRC_EXT")
      set(_SRC_EXT "${arg}")
      set(_key "")
    else()
      message(FATAL_ERROR "Unknown argument:\n  ${arg}\n")
    endif()
  endforeach()

  if(NOT _SRC_EXT)
    set(_SRC_EXT "cpp")
  endif()

  if(CMAKE_REQUIRED_LINK_OPTIONS)
    set(CHECK_${LANG}_SOURCE_COMPILES_ADD_LINK_OPTIONS LINK_OPTIONS ${CMAKE_REQUIRED_LINK_OPTIONS})
  else()
    set(CHECK_${LANG}_SOURCE_COMPILES_ADD_LINK_OPTIONS)
  endif()
  if(CMAKE_REQUIRED_LIBRARIES)
    set(CHECK_${LANG}_SOURCE_COMPILES_ADD_LIBRARIES LINK_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES})
  else()
    set(CHECK_${LANG}_SOURCE_COMPILES_ADD_LIBRARIES)
  endif()
  if(CMAKE_REQUIRED_INCLUDES)
    set(CHECK_${LANG}_SOURCE_COMPILES_ADD_INCLUDES
        "-DINCLUDE_DIRECTORIES:STRING=${CMAKE_REQUIRED_INCLUDES}")
  else()
    set(CHECK_${LANG}_SOURCE_COMPILES_ADD_INCLUDES)
  endif()
  file(WRITE "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/src.${_SRC_EXT}" "${_source}\n")

  if(NOT CMAKE_REQUIRED_QUIET)
    message(CHECK_START "Performing Test ${_var}")
  endif()
  try_compile(
    ${_var} ${CMAKE_BINARY_DIR}
    ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/src.${_SRC_EXT}
    COMPILE_DEFINITIONS
      -D${_var} ${CMAKE_REQUIRED_DEFINITIONS} ${CHECK_${LANG}_SOURCE_COMPILES_ADD_LINK_OPTIONS}
      ${CHECK_${LANG}_SOURCE_COMPILES_ADD_LIBRARIES}
    CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${CMAKE_REQUIRED_FLAGS}
                "${CHECK_${LANG}_SOURCE_COMPILES_ADD_INCLUDES}"
    OUTPUT_VARIABLE OUTPUT)

  foreach(_regex ${_FAIL_REGEX})
    if("${OUTPUT}" MATCHES "${_regex}")
      set(${_var} 0)
    endif()
  endforeach()

  if(${_var})
    set(${_var}
        1
        CACHE INTERNAL "Test ${_var}")
    if(NOT CMAKE_REQUIRED_QUIET)
      message(CHECK_PASS "Success")
    endif()
    file(
      APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeOutput.log
      "Performing ${_lang_textual} SOURCE FILE Test ${_var} succeeded with the following output:\n"
      "${OUTPUT}\n" "Source file was:\n${_source}\n")
  else()
    if(NOT CMAKE_REQUIRED_QUIET)
      message(CHECK_FAIL "Failed")
    endif()
    set(${_var}
        ""
        CACHE INTERNAL "Test ${_var}")
    file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeError.log
         "Performing ${_lang_textual} SOURCE FILE Test ${_var} failed with the following output:\n"
         "${OUTPUT}\n" "Source file was:\n${_source}\n")
  endif()
endfunction()

# CheckCXXCompilerFlag Sources:
# https://github.com/Kitware/CMake/blob/master/Modules/CheckCXXCompilerFlag.cmake
# https://github.com/Kitware/CMake/blob/master/Modules/Internal/CheckCompilerFlag.cmake
# https://github.com/Kitware/CMake/blob/master/Modules/CMakeCheckCompilerFlagCommonPatterns.cmake
function(phi_check_cxx_compiler_flag _flag _var)
  set(_lang_src "int main() { return 0; }")
  set(_lang_fail_regex FAIL_REGEX "command[ -]line option .* is valid for .* but not for C\\+\\+"
                       FAIL_REGEX "-Werror=.* argument .* is not valid for C\\+\\+")

  set(CMAKE_REQUIRED_DEFINITIONS ${_flag})

  # Normalize locale during test compilation.
  set(_locale_vars LC_ALL LC_MESSAGES LANG)
  foreach(v IN LISTS _locale_vars)
    set(_locale_vars_saved_${v} "$ENV{${v}}")
    set(ENV{${v}} C)
  endforeach()

  # common patterns
  set(_common_patterns
      FAIL_REGEX
      "[Uu]nrecogni[sz]ed .*option" # GNU, NAG, Fujitsu
      FAIL_REGEX
      "switch .* is no longer supported" # GNU
      FAIL_REGEX
      "unknown .*option" # Clang
      FAIL_REGEX
      "optimization flag .* not supported" # Clang
      FAIL_REGEX
      "unknown argument ignored" # Clang (cl)
      FAIL_REGEX
      "ignoring unknown option" # MSVC, Intel
      FAIL_REGEX
      "warning D9002" # MSVC, any lang
      FAIL_REGEX
      "option.*not supported" # Intel
      FAIL_REGEX
      "invalid argument .*option" # Intel
      FAIL_REGEX
      "ignoring option .*argument required" # Intel
      FAIL_REGEX
      "ignoring option .*argument is of wrong type" # Intel
      FAIL_REGEX
      "[Uu]nknown option" # HP
      FAIL_REGEX
      "[Ww]arning: [Oo]ption" # SunPro
      FAIL_REGEX
      "command option .* is not recognized" # XL
      FAIL_REGEX
      "command option .* contains an incorrect subargument" # XL
      FAIL_REGEX
      "Option .* is not recognized.  Option will be ignored." # XL
      FAIL_REGEX
      "not supported in this configuration. ignored" # AIX
      FAIL_REGEX
      "File with unknown suffix passed to linker" # PGI
      FAIL_REGEX
      "[Uu]nknown switch" # PGI
      FAIL_REGEX
      "WARNING: unknown flag:" # Open64
      FAIL_REGEX
      "Incorrect command line option:" # Borland
      FAIL_REGEX
      "Warning: illegal option" # SunStudio 12
      FAIL_REGEX
      "[Ww]arning: Invalid suboption" # Fujitsu
      FAIL_REGEX
      "An invalid option .* appears on the command line" # Cray
  )

  phi_check_cxx_source_compiles("${_lang_src}" ${_var} ${_lang_fail_regex} ${_common_patterns})

  foreach(v IN LISTS _locale_vars)
    set(ENV{${v}} ${_locale_vars_saved_${v}})
  endforeach()
endfunction()
