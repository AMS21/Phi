# PhiEngine
project(PhiEngine LANGUAGES CXX)

file(GLOB PHI_ENGINE_HEADERS
     # Phi
     "include/Phi/PhiConfig.hpp"
     # Utility
     "include/Phi/Utility/Boolean.hpp"
     "include/Phi/Utility/FloatingPoint.hpp"
     )

file(GLOB PHI_ENGINE_SOURCES "src/main.cpp")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PHI_ENGINE_HEADERS} ${PHI_ENGINE_SOURCES})

# Dependencies library
add_library(${PROJECT_NAME} STATIC ${PHI_ENGINE_HEADERS} ${PHI_ENGINE_SOURCES})
add_library(Phi::Engine ALIAS ${PROJECT_NAME})

enable_static_analyzers(${PROJECT_NAME})

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC "include"
  PRIVATE "src")

target_link_libraries(${PROJECT_NAME} PUBLIC Phi::ProjectOptions CppBase::CppBase)

if(WIN32)
  target_compile_definitions(${PROJECT_NAME} PRIVATE "NOMINMAX")
endif()
