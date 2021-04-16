# Phi top level cmake file
cmake_minimum_required(VERSION 3.12)

# Policy
if(${CMAKE_VERSION} VERSION_LESS 3.20)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.20)
endif()

# CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake)

include(Functions)

set(PHI_VERSION_MAJOR 0)
set(PHI_VERSION_MINOR 1)
set(PHI_VERSION_PATCH 0)

phi_log("Configuring Phi version ${PHI_VERSION_MAJOR}.${PHI_VERSION_MINOR}.${PHI_VERSION_PATCH}")

# Project
project(
  Phi
  LANGUAGES CXX
  VERSION "${PHI_VERSION_MAJOR}.${PHI_VERSION_MINOR}.${PHI_VERSION_PATCH}"
  DESCRIPTION "High performance, modular, modern, cross-platform Game Engine library")

# Check if Phi is being used directly or via add_subdirectory, but allow overriding
if(NOT DEFINED PHI_MASTER_PROJECT)
  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(PHI_MASTER_PROJECT ON)
    phi_trace("Building as master project")
  else()
    set(PHI_MASTER_PROJECT OFF)
    phi_trace("Building as submodule")
  endif()
endif()

# Load environemt information
include(Environment)

# Options
option(PHI_BUILD_TESTS "Build tests" ${PHI_MASTER_PROJECT})
option(PHI_BUILD_EXAMPLES "Build examples" ${PHI_MASTER_PROJECT})
option(PHI_BUILD_SANDBOX "Build sandbox application" ${PHI_MASTER_PROJECT})
option(PHI_BUILD_DOCS "Generate the source code documentaion" OFF)
option(PHI_USE_PCH "Use a pre compiled header (pch)" OFF)
option(PHI_USE_UNITY_BUILD "Enable unity builds" OFF)
option(PHI_ENABLE_CONSTEXPRTESTS "Build the constexpr tests" ON)
option(PHI_ENABLE_FAILURE_TESTS "Build the failure tests" ON)
option(PHI_COVERAGE_BUILD "Enable flags for creating coverage data" OFF)
option(PHI_AUTO_FORMATTING "Automatically format all source code during builds"
       ${PHI_MASTER_PROJECT})
option(PHI_TEST_WITH_VALGRIND "Automatically run tests with valgrind and print results" OFF)
option(PHI_ENABLE_CACHE "Enable cache if available" ON)
option(PHI_ENABLE_OPTIMIZATION_FLAGS "Enable all the optimization flags from Phi" ON)
option(PHI_ENABLE_PSO "Enable platform specific optimization" OFF)
option(PHI_ARCH "Optimization target for platform specific optimization" "native")
option(PHI_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)
option(PHI_PEDANTIC_WARNINGS "Enable pedantic mode" ON)
option(PHI_ENABLE_USER_LINKER "Enable a specific linker if available" OFF)
option(PHI_BUILD_WITH_TIME_TRACE
       "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
option(PHI_ENABLE_IPO "Enable Iterprocedural Optimization, aka Link Time Optimization (LTO)" OFF)
option(PHI_COLOR_DIAGNOSTICS ON "Enable colored diagnostics")
option(PHI_ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
option(PHI_ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)
option(PHI_EANBKE_IWYU "Enable static analysis with include-what-you-use" OFF)

option(PHI_STANDARD_RUNTIME "Which standard runtime to use. Only affects windows platforms"
       "Dynamic")
set_property(CACHE PHI_STANDARD_RUNTIME PROPERTY STRINGS "Dynamic" "Static")

option(PHI_STANDARD_LIBRARY "Which standard library to use. Only affects clang builds" "Default")
set_property(CACHE PHI_STANDARD_LIBRARY PROPERTY STRINGS "Default" "libstdc++" "libc++")

# CI Builds Settings
if(${PHI_CI_BUILD} AND ${PHI_MASTER_PROJECT})
  phi_trace("Is CI build")

  # Disable auto formatting
  set(PHI_AUTO_FORMATTING
      FALSE
      CACHE BOOL "" FORCE)

  # Enable verbose makefile
  set(CMAKE_VERBOSE_MAKEFILE
      TRUE
      CACHE BOOL "" FORCE)
endif()

# Load configuration
include(PhiConfiguration)

# Settings
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Warn about not out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
  phi_warn(
    "You shoudnt build in a source directory (or any directory with a CMakeLists.txt file). Please consider makeing a build subdirectory."
  )
endif()

# Check external directory
if(NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/external/Catch2/src")
  phi_error(
    "The external dependencies repositories are missing! "
    "You probably did not clone the project with --recursive flag. It is possible to recover "
    "by calling \"git submodule update --init --recursive\"")
endif()

set(PHI_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Find required system libs
find_package(Threads REQUIRED)

# Load external dependencies
add_subdirectory(external)

# Load tools
add_subdirectory(tools)

# Load libs
add_subdirectory(libs)

# Examples
if(${PHI_BUILD_EXAMPLES})
  add_subdirectory(examples)
endif()

# Tests
if(${PHI_BUILD_TESTS})
  include(CTest)

  add_subdirectory(tests)
endif()

# Documentation
if(${PHI_BUILD_DOCS})
  add_subdirectory(docs)
endif()

if(${PHI_USE_UNITY_BUILD})
  set_target_properties(Phi::Engine PROPERTIES UNITY_BUILD ON)
endif()
