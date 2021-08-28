# PhiConfiguration.cmake

phi_include_guard()

# Set C++ Standard
include(CXXStandard)
if(${CMAKE_VERSION} VERSION_GREATER "3.7")
  set_target_properties(
    phi_project_options PROPERTIES INTERFACE_COMPILE_FEATURES cxx_std_${phi_standard_version}
                                   INTERFACE_CXX_EXTENSIONS OFF)
else()
  target_compile_options(phi_project_options INTERFACE "${phi_standard_flag}")
endif()

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
