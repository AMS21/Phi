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

phi_trace("Build type: ${CMAKE_BUILD_TYPE}")

# Generate compile_commands.json to make it easier to work with clang based tools
set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE BOOL "" FORCE)

if(PHI_ENABLE_IPO)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT ipo_result OUTPUT ipo_output)

  if(ipo_result)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    if(PHI_COMPILER_CLANG)
      target_link_libraries(phi_project_options INTERFACE -fsplit-lto-unit)
    elseif(PHI_COMPILER_GCC)
      target_link_libraries(phi_project_options INTERFACE -Wl,--no-as-needed)
    endif()
  else()
    phi_warn("IPO is not supported: ${ipo_output}")
    set(PHI_ENABLE_IPO
        OFF
        CACHE BOOL "Enable Iterprocedural Optimization, aka Link Time Optimization (LTO)" FORCE)
  endif()
endif()

# Setting the runtime library on windows platforms
if(PHI_PLATFORM_WINDOWS)
  if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.15.0")
    if(${PHI_STANDARD_RUNTIME} STREQUAL "Static")
      set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    else()
      set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    endif()
  else()
    foreach(flag CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
                 CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
      if(${flag} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
      endif()
    endforeach()
  endif()
endif()

# Standard library
if(PHI_COMPILER_CLANG)
  if(${PHI_STANDARD_LIBRARY} STREQUAL "libc++")
    target_compile_options(phi_project_options INTERFACE -stdlib=libc++)
    target_link_libraries(phi_project_options INTERFACE -stdlib=libc++)
  endif()
endif()

# Color diagnostics
if(PHI_COMPILER_CLANG)
  target_compile_options(phi_project_options INTERFACE -fcolor-diagnostics)
elseif(PHI_COMPILER_GCC)
  target_compile_options(phi_project_options INTERFACE -fdiagnostics-color=always)
else()
  phi_warn("No colored compiler diagnostic set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
  set(PHI_COLOR_DIAGNOSTICS
      OFF
      CACHE BOOL "Enable colored diagnostics" FORCE)
endif()
