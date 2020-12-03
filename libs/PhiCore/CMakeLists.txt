# PhiCore
project(PhiCore LANGUAGES CXX)

file(
  GLOB
  PHI_CORE_HEADERS
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

file(GLOB PHI_CORE_SOURCES "src/Core/Log.cpp")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PHI_CORE_HEADERS} ${PHI_CORE_SOURCES})

# PhiCore library
set(DYNAMIC_LIB_NAME "${PROJECT_NAME}Dynamic")

add_library(${PROJECT_NAME} STATIC ${PHI_CORE_HEADERS} ${PHI_CORE_SOURCES})
add_library(${DYNAMIC_LIB_NAME} SHARED ${PHI_CORE_HEADERS} ${PHI_CORE_SOURCES})

# Alias targets
add_library(Phi::Core ALIAS ${PROJECT_NAME})
add_library(Phi::CoreDynamic ALIAS ${DYNAMIC_LIB_NAME})

foreach(lib ${PROJECT_NAME} ${DYNAMIC_LIB_NAME})
  enable_static_analyzers(${lib})

  target_include_directories(
    ${lib}
    PUBLIC "include"
    PRIVATE "src")

  target_link_libraries(
    ${lib}
    PUBLIC spdlog::spdlog Threads::Threads
    PRIVATE Phi::InternalProjectOptions)
endforeach()

target_compile_definitions(${PROJECT_NAME} PUBLIC "PHI_STATIC_BUILD")
target_compile_definitions(${DYNAMIC_LIB_NAME} INTERFACE "PHI_IMPORT")

# Fix dynamic target dependency libs
phi_fix_dynamic_dep(${DYNAMIC_LIB_NAME})
