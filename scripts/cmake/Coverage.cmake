include_guard(GLOBAL)

if(PHI_COVERAGE_BUILD)
  # Enable coverage flags
  if(PHI_COMPILER_GCC)
    target_compile_options(phi_project_options INTERFACE --coverage -O0 -g -fno-inline)
    target_link_libraries(phi_project_options INTERFACE --coverage)
  elseif(PHI_COMPILER_CLANG)
    target_compile_options(phi_project_options INTERFACE -fprofile-instr-generate
                                                         -fcoverage-mapping -O0 -g -fno-inline)
    target_link_libraries(phi_project_options INTERFACE -fprofile-instr-generate -fcoverage-mapping)
  else()
    phi_warn("No coverage flags set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
  endif()

  # Replace always inline with never inline
  target_compile_definitions(phi_project_options
                             INTERFACE PHI_CONFIG_ALWAYS_INLINE_OVERWRITE=PHI_NEVER_INLINE)

  # Disable optimization flags from Phi
  set(PHI_ENABLE_OPTIMIZATION_FLAGS OFF)

  phi_log("Enabled coverage flags")
endif()
