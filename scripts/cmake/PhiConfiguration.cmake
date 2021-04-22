# PhiConfiguration.cmake

include_guard(GLOBAL)

# Project options
add_library(phi_project_options INTERFACE)
add_library(Phi::ProjectOptions ALIAS phi_project_options)
# Require C++17 and disable extensions
set_target_properties(phi_project_options PROPERTIES INTERFACE_COMPILE_FEATURES cxx_std_17
                                                     INTERFACE_CXX_EXTENSIONS OFF)

add_library(phi_internal_project_options INTERFACE)
add_library(Phi::InternalProjectOptions ALIAS phi_internal_project_options)

target_link_libraries(phi_internal_project_options INTERFACE Phi::ProjectOptions)

if(PHI_COMPILER_CLANG AND PHI_BUILD_WITH_TIME_TRACE)
  target_compile_definitions(phi_project_options INTERFACE -ftime-trace)
endif()

# Standard project settings
include(StandardProjectSettings)

# Include coverage settings
include(Coverage)

# enable cache system
include(Cache)

# Standard compiler warnings
include(CompilerWarnings)
set_project_warnings(phi_internal_project_options)

# Compiler optimizations
include(CompilerOptimizations)
set_project_optimizations(phi_project_options)

# sanitizer options if supported by compiler
include(Sanitizers)
enable_sanitizers(phi_project_options)

# allow for static analysis options
include(StaticAnalyzers)

# Enable automatic formatting
include(Formatting)

# Enable user linker
include(Linker)
phi_configure_linker(phi_project_options)
