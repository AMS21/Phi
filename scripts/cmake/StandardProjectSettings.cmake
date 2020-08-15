# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE
      RelWithDebInfo
      CACHE STRING "Choose the type of build." FORCE)

  # Set the possible values of build type for cmake-gui, ccmake
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel"
                                               "RelWithDebInfo")
endif()

# Generate compile_commands.json to make it easier to work with clang based tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_IPO "Enable Iterprocedural Optimization, aka Link Time Optimization (LTO)" ON)

if(ENABLE_IPO)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT ipo_result OUTPUT ipo_output)
  if(ipo_result)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
  else()
    message(WARNING "IPO is not supported: ${ipo_output}")
    set(ENABLE_IPO
        OFF
        CACHE BOOL "Enable Iterprocedural Optimization, aka Link Time Optimization (LTO)" FORCE)
  endif()
endif()

# Setting the runtime library on windows platforms
option(PHI_STANDARD_RUNTIME "Which standard runtime to use. Only affects windows platforms"
       "Dynamic")
set_property(CACHE PHI_STANDARD_RUNTIME PROPERTY STRINGS "Dynamic" "Static")

if(WIN32)
  if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.15.0")
    if(${PHI_STANDARD_RUNTIME} STREQUAL "Static")
      set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    else()
      set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    endif()
  else()
    # TODO: Needs workaround
  endif()
endif()
