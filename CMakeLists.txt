# Phi top level cmake file
cmake_minimum_required(VERSION 2.8.12)

# Policy
if(${CMAKE_VERSION} VERSION_LESS 3.23)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.23)
endif()

# CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake)

include(internal/PhiIncludeGuard)
include(Functions)

set(PHI_VERSION_MAJOR 0)
set(PHI_VERSION_MINOR 1)
set(PHI_VERSION_PATCH 0)

phi_log("Configuring Phi version ${PHI_VERSION_MAJOR}.${PHI_VERSION_MINOR}.${PHI_VERSION_PATCH}")

# Project
if(${CMAKE_VERSION} VERSION_LESS 3.0)
  project(Phi CXX)
else()
  project(
    Phi
    VERSION "${PHI_VERSION_MAJOR}.${PHI_VERSION_MINOR}.${PHI_VERSION_PATCH}"
    LANGUAGES CXX)
endif()

# Check if Phi is being used directly or via add_subdirectory, but allow overriding
if(NOT DEFINED PHI_MAIN_PROJECT)
  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(PHI_MAIN_PROJECT ON)
    phi_trace("Building as main project")
  else()
    set(PHI_MAIN_PROJECT OFF)
    phi_trace("Building as submodule")
  endif()
endif()

# Load environemt information
include(Environment)

# Options
option(PHI_BUILD_TESTS "Build tests" ${PHI_MAIN_PROJECT})
option(PHI_BUILD_EXAMPLES "Build examples" ${PHI_MAIN_PROJECT})
option(PHI_BUILD_SANDBOX "Build sandbox application" ${PHI_MAIN_PROJECT})
option(PHI_BUILD_DOCS "Generate the source code documentaion" OFF)
option(PHI_USE_PCH "Use a pre compiled header (pch)" OFF)
option(PHI_USE_UNITY_BUILD "Enable unity builds" OFF)
option(PHI_ENABLE_CONSTEXPRTESTS "Build the constexpr tests" ON)
option(PHI_ENABLE_FAILURE_TESTS "Build the failure tests" ON)
option(PHI_COVERAGE_BUILD "Enable flags for creating coverage data" OFF)
option(PHI_AUTO_FORMATTING "Automatically format all source code during builds" ${PHI_MAIN_PROJECT})
option(PHI_TEST_WITH_VALGRIND "Automatically run tests with valgrind and print results" OFF)
option(PHI_ENABLE_CACHE "Enable cache if available" ON)
option(PHI_ENABLE_OPTIMIZATION_FLAGS "Enable all the optimization flags from Phi" ON)
option(PHI_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ${PHI_MAIN_PROJECT})
option(PHI_PEDANTIC_WARNINGS "Enable pedantic mode" ON)
option(PHI_ENABLE_USER_LINKER "Enable a specific linker if available" OFF)
option(PHI_BUILD_WITH_TIME_TRACE
       "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
option(PHI_ENABLE_IPO "Enable Interprocedural Optimization, aka Link Time Optimization (LTO)" OFF)
option(PHI_COLOR_DIAGNOSTICS "Enable colored diagnostics" ON)
option(PHI_ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
option(PHI_ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)
option(PHI_EANBLE_IWYU "Enable static analysis with include-what-you-use" OFF)
option(PHI_TEST_WITH_ALL_STANDARDS "Build test application for all standards" ON)
option(PHI_VERBOSE_CMAKE "Enable verbose priting during configuration" ${PHI_MAIN_PROJECT})

phi_option(PHI_STANDARD_RUNTIME "Which standard runtime to use. Only affects windows platforms"
           STRING "Dynamic")
set_property(CACHE PHI_STANDARD_RUNTIME PROPERTY STRINGS "Dynamic" "Static")

phi_option(PHI_STANDARD_LIBRARY "Which standard library to use. Only affects clang builds" STRING
           "Default")
set_property(CACHE PHI_STANDARD_LIBRARY PROPERTY STRINGS "Default" "libstdc++" "libc++")

phi_option(PHI_STANDARD "Which C++ Standard to use" STRING "latest")
set_property(
  CACHE PHI_STANDARD
  PROPERTY STRINGS
           "latest"
           "11"
           "14"
           "17"
           "20"
           "23")

option(PHI_ENABLE_PSO "Enable platform specific optimization" OFF)
phi_option(PHI_ARCH "Optimization target for platform specific optimization" STRING "native")

# CI Builds Settings
if(${PHI_CI_BUILD} AND ${PHI_MAIN_PROJECT})
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
include(ProjectOptions)

# Settings
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

phi_set_cache_value(NAME PHI_GENERATED_FILES_DIR VALUE "${CMAKE_BINARY_DIR}/generated-includes/")

# Warn about not out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
  phi_warn(
    "You shoudnt build in a source directory (or any directory with a CMakeLists.txt file). Please consider makeing a build subdirectory."
  )
endif()

set(PHI_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Find required system libs
find_package(Threads REQUIRED)

# Load libs
add_subdirectory(libs)

# Examples
if(${PHI_BUILD_EXAMPLES})
  add_subdirectory(examples)
endif()

# Tests
if(${PHI_BUILD_TESTS})
  include(Testing)

  add_subdirectory(tests)
endif()

# Documentation
if(${PHI_BUILD_DOCS})
  add_subdirectory(docs)
endif()

phi_configure_project(DEBUG_FLAGS WARNINGS WARNINGS_AS_ERRORS OPTIMIZATION_FLAGS PEDANTIC)
