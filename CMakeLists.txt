# Phi top level cmake file
cmake_minimum_required(VERSION 3.12)

# Policy
if(${CMAKE_VERSION} VERSION_LESS 3.18)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.18)
endif()

# Cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake)

set(PHI_VERSION_MAJOR 0)
set(PHI_VERSION_MINOR 1)
set(PHI_VERSION_PATCH 0)

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
  else()
    set(PHI_MASTER_PROJECT OFF)
  endif()
endif()

# Options
option(PHI_BUILD_TESTS "Build tests" ${PHI_MASTER_PROJECT})
option(PHI_BUILD_EXAMPLES "Build examples" ${PHI_MASTER_PROJECT})
option(PHI_BUILD_SANDBOX "Build sandbox application" ${PHI_MASTER_PROJECT})
option(PHI_BUILD_DOCS "Generate the source code documentaion" OFF)
option(PHI_USE_PCH "Use a pre compiled header (pch)" OFF)
option(PHI_USE_UNITY_BUILD "Enable unity builds" OFF)
option(PHI_ENABLE_OPTIMIZATION_FLAGS "Enable all the optimization flags from Phi" ON)
option(PHI_ENABLE_CONSTEXPRTESTS "Build the constexpr tests" ON)
option(PHI_ENABLE_FAILURE_TESTS "Build the failure tests" ON)
option(PHI_COVERAGE_BUILD "Enable flags for creating coverage data" OFF)
option(PHI_AUTO_FORMATTING "Automatically format all source code when builds" ${PHI_MASTER_PROJECT})

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
  message(
    WARNING
      "[Phi] You shoudnt build in a source directory (or any directory with a CMakeLists.txt file)."
      "Please consider makeing a build subdirectory.")
endif()

# Check external directory
if(NOT IS_DIRECTORY "${CMAKE_SOURCE_DIR}/external/Catch2/src")
  message(
    FATAL_ERROR
      "The external dependencies repositories are missing! "
      "You probably did not clone the project with --recursive. It is possible to recover "
      "by calling \"git submodule update --init --recursive\"")
endif()

set(PHI_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Find required system libs
find_package(Threads REQUIRED)

# Load tools
add_subdirectory(tools)

# Load external dependencies
add_subdirectory(external)

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
