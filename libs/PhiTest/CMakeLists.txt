# PhiTest
if(${CMAKE_VERSION} VERSION_LESS 3.0)
  project(PhiTest CXX C)
else()
  project(PhiTest LANGUAGES CXX)
endif()

file(GLOB PHI_TEST_HEADERS "src/phi/test/test_macros.hpp")

file(GLOB PHI_TEST_SOURCES "src/TestMacros.cpp")

phi_add_library(
  NAME
  ${PROJECT_NAME}
  STATIC
  SOURCES
  ${PHI_TEST_SOURCES}
  HEADERS
  ${PHI_TEST_HEADERS}
  ALIAS_TARGET
  Phi::Test
  PUBLIC_LINK_LIBRARIES
  Phi::Core
  PRIVATE_LINK_LIBRARIES
  Phi::InternalProjectOptions
  PUBLIC_INCLUDE_DIRS
  "include"
  PRIVATE_INCLUDE_DIRS
  "src")

phi_enable_static_analyzers(${PROJECT_NAME})
