# PhiEngineStandardOptions.cmake

include(StandardProjectSettings)

# Project options
add_library(project_options INTERFACE)
add_library(Phi::ProjectOptions ALIAS project_options)
target_compile_features(project_options INTERFACE cxx_std_20)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE
         "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    add_compile_definitions(project_options INTERFACE -ftime-trace)
  endif()
endif()

# enable cache system
include(Cache)

# Standard compiler warnings
include(CompilerWarnings)
set_project_warnings(project_options)

# Compiler optimizations
include(CompilerOptimizations)
set_project_optimizations(project_options)

# sanitizer options if supported by compiler
include(Sanitizers)
enable_sanitizers(project_options)

# allow for static analysis options
include(StaticAnalyzers)
