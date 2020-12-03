# PhiCore
project(PhiCore LANGUAGES CXX)

file(
  GLOB
  PHI_ENGINE_HEADERS
  # Config
  "include/Phi/Config/Assume.hpp"
  "include/Phi/Config/Compiler.hpp"
  "include/Phi/Config/CurrentFunction.hpp"
  "include/Phi/Config/FunctionLikeMacro.hpp"
  "include/Phi/Config/Glue.hpp"
  "include/Phi/Config/Inline.hpp"
  "include/Phi/Config/Likely.hpp"
  "include/Phi/Config/Platform.hpp"
  "include/Phi/Config/Stringify.hpp"
  "include/Phi/Config/Versioning.hpp"
  "include/Phi/Config/Warning.hpp"
  # Core
  "include/Phi/Core/Assert.hpp"
  "include/Phi/Core/At.hpp"
  "include/Phi/Core/Boolean.hpp"
  "include/Phi/Core/Conversion.hpp"
  "include/Phi/Core/FinalAction.hpp"
  "include/Phi/Core/FloatingPoint.hpp"
  "include/Phi/Core/Integer.hpp"
  "include/Phi/Core/Log.hpp"
  "include/Phi/Core/NotNull.hpp"
  "include/Phi/Core/Types.hpp"
  # Math
  "include/Phi/Math/Constants.hpp"
  "include/Phi/Math/Vector2.hpp"
  # Meta
  "include/Phi/Meta/AlwaysFalse.hpp")

file(GLOB PHI_ENGINE_SOURCES "src/Core/Log.cpp")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PHI_ENGINE_HEADERS} ${PHI_ENGINE_SOURCES})

# Dependencies library
add_library(${PROJECT_NAME} STATIC ${PHI_ENGINE_HEADERS} ${PHI_ENGINE_SOURCES})
add_library(Phi::Core ALIAS ${PROJECT_NAME})

enable_static_analyzers(${PROJECT_NAME})

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC "include"
  PRIVATE "src")

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC spdlog::spdlog Threads::Threads
  PRIVATE Phi::InternalProjectOptions)

if(WIN32)
  target_compile_definitions(${PROJECT_NAME} PRIVATE "NOMINMAX")
endif()
