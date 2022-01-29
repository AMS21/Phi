# PhiConfiguration.cmake

phi_include_guard()

# Load C++ Standard
include(CXXStandard)

if(PHI_COMPILER_CLANG AND PHI_BUILD_WITH_TIME_TRACE)
  target_compile_definitions(phi_project_options INTERFACE -ftime-trace)
endif()

# Compiler features
include(CompilerFeatures)

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
