# PhiEngine
project(PhiEngine LANGUAGES CXX)

file(
  GLOB
  PHI_ENGINE_HEADERS
  # Phi
  "include/Phi/PhiConfig.hpp"
  # Math
  "include/Phi/Math/Constants.hpp"
  # Meta
  "include/Phi/Meta/AlwaysFalse.hpp"
  # Utility
  "include/Phi/Utility/Assert.hpp"
  "include/Phi/Utility/At.hpp"
  "include/Phi/Utility/Boolean.hpp"
  "include/Phi/Utility/Conversion.hpp"
  "include/Phi/Utility/FloatingPoint.hpp"
  "include/Phi/Utility/Integer.hpp"
  "include/Phi/Utility/Log.hpp"
  "include/Phi/Utility/Types.hpp")

file(GLOB PHI_ENGINE_SOURCES "src/Utility/Log.cpp")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PHI_ENGINE_HEADERS} ${PHI_ENGINE_SOURCES})

# Dependencies library
add_library(${PROJECT_NAME} STATIC ${PHI_ENGINE_HEADERS} ${PHI_ENGINE_SOURCES})
add_library(Phi::Engine ALIAS ${PROJECT_NAME})

enable_static_analyzers(${PROJECT_NAME})

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC "include"
  PRIVATE "src")

target_link_libraries(${PROJECT_NAME} PUBLIC Phi::InternalProjectOptions CppBase::CppBase spdlog::spdlog Threads::Threads)

if(WIN32)
  target_compile_definitions(${PROJECT_NAME} PRIVATE "NOMINMAX")
endif()
