# PhiConfiguration.cmake

phi_include_guard()

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  phi_log("Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE
      RelWithDebInfo
      CACHE STRING "Choose the type of build." FORCE)

  # Set the possible values of build type for cmake-gui, ccmake
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel"
                                               "RelWithDebInfo")
endif()

if(CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  phi_trace("Build type: ${CMAKE_BUILD_TYPE}")
elseif(CMAKE_CONFIGURATION_TYPES)
  phi_trace("Configuration types: \"${CMAKE_CONFIGURATION_TYPES}\"")
endif()

# Generate compile_commands.json to make it easier to work with clang based tools
set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE BOOL "" FORCE)

include(ProjectOptions)

phi_configure_project(
  NAME
  phi_project_options
  DEBUG_FLAGS
  WARNINGS
  WARNINGS_AS_ERRORS
  OPTIMIZATION_FLAGS
  PEDANTIC)

# Enable automatic formatting
include(Formatting)
