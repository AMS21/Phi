include_guard(GLOBAL)

# Function to enable optimizations for a specific project
function(set_project_optimizations project)
  if(NOT PHI_ENABLE_OPTIMIZATION_FLAGS)
    return()
  endif()

  # MSVC
  set(phi_msvc_opt /Oi /Ot /GT /fp:fast /fp:except-)
  set(phi_msvc_linker_opt /OPT:REF)

  # Clang
  set(phi_clang_release_opt
      -fno-math-errno
      -ffinite-math-only
      -fno-signed-zeros
      -fno-trapping-math
      -fstrict-enums
      -fomit-frame-pointer
      -fforce-emit-vtables
      -fstrict-vtable-pointers
      -fstrict-return)

  # The -fwhole-program-vtables optimization for some reasons crashes the AppleClang compiler
  if(PHI_ENABLE_IPO AND NOT PHI_COMPILER_APPLECLANG)
    list(APPEND phi_clang_release_opt -fwhole-program-vtables)
  endif()

  set(phi_clang_opt $<$<CONFIG:RELEASE>:${phi_clang_release_opt}>)

  # GCC
  set(phi_gcc_release_opt -fno-math-errno -ffinite-math-only -fno-signed-zeros -fno-trapping-math
                          -fstrict-enums -fomit-frame-pointer)

  set(phi_gcc_opt $<$<CONFIG:RELEASE>:${phi_gcc_release_opt}>)

  if(PHI_COMPILER_MSVC)
    set(project_opt ${phi_msvc_opt})
    set(project_linker_opt ${phi_msvc_linker_opt})
  elseif(PHI_COMPILER_CLANG)
    set(project_opt ${phi_clang_opt})
  elseif(PHI_COMPILER_GCC)
    set(project_opt ${phi_gcc_opt})
  else()
    phi_warn("No compiler optimizations set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
  endif()

  # Get target type
  get_property(
    target_type
    TARGET ${project}
    PROPERTY TYPE)

  if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
    set(visibility_scope INTERFACE)
  else()
    set(visibility_scope PRIVATE)
  endif()

  target_compile_options(${project} ${visibility_scope} ${project_opt})
  target_link_options(${project} ${visibility_scope} ${project_linker_opt})

  if(PHI_ENABLE_PSO AND NOT PHI_COMPILER_MSVC)
    target_compile_options(${project} ${visibility_scope} "-march=${PHI_ARCH}")
  endif()

  phi_trace("Setting optimization flags for ${project}")
endfunction()
