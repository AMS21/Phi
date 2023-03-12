phi_include_guard()

include(CMakeParseArguments)
include(CompilerFlags)

function(phi_target_enable_optimizations)
  # Command line arguments
  cmake_parse_arguments(opt "LTO" "TARGET;PSO" "CONFIGS" ${ARGN})

  # Check required arguments
  if(NOT opt_TARGET)
    phi_error("phi_target_enable_optimizations: You must specify TARGET")
  endif()

  # Check if target is valid
  if(NOT TARGET ${opt_TARGET})
    phi_error(
      "phi_target_enable_optimizations: The specified target \"${opt_TARGET}\" doesn't seem to be valid"
    )
  endif()

  # Optional CONFIGS
  if(NOT DEFINED ${opt_CONFIGS})
    # Set default value
    set(opt_CONFIGS "Release")
  endif()

  # Get target type
  get_property(
    target_type
    TARGET ${opt_TARGET}
    PROPERTY TYPE)

  if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
    set(visibility_scope INTERFACE)
  else()
    set(visibility_scope PRIVATE)
  endif()

  # Get linker language
  get_property(
    target_linker_language
    TARGET ${opt_TARGET}
    PROPERTY LINKER_LANGUAGE)

  # Enable options for each specified configuration
  foreach(config ${opt_CONFIGS})
    if("${target_linker_language}" STREQUAL "CXX" OR "${target_linker_language}" STREQUAL "")
      # Enable C++ optimizations flags
      target_compile_options(
        ${opt_TARGET} ${visibility_scope} $<$<CONFIG:${config}>:${phi_optimize_flags}>
        $<$<CONFIG:${config}>:${phi_cxx_optimize_flags}>)
      target_link_options(
        ${opt_TARGET} ${visibility_scope} $<$<CONFIG:${config}>:${phi_optimize_flags}>
        $<$<CONFIG:${config}>:${phi_cxx_optimize_flags}>)
    elseif("${target_linker_language}" STREQUAL "C")
      # Enable C optimizations flags
      target_compile_options(${opt_TARGET} ${visibility_scope}
                             $<$<CONFIG:${config}>:${phi_optimize_flags}>)
      target_link_options(${opt_TARGET} ${visibility_scope}
                          $<$<CONFIG:${config}>:${phi_optimize_flags}>)
    endif()

    if(opt_LTO)
      if("${phi_lto_flags}" STREQUAL "")
        phi_warn("Requested LTO but no supported flags where found")
      else()
        # Disable LTO from CMake
        set_target_properties(${opt_TARGET} PROPERTIES INTERPROCEDURAL_OPTIMIZATION OFF)

        # Set LTO flag
        target_compile_options(${opt_TARGET} ${visibility_scope}
                               $<$<CONFIG:${config}>:${phi_lto_flags}>)
        target_link_options(${opt_TARGET} ${visibility_scope}
                            $<$<CONFIG:${config}>:${phi_lto_flags}>)

        # Enable LTO specifc optimizations
        target_compile_options(${opt_TARGET} ${visibility_scope}
                               $<$<CONFIG:${config}>:${phi_lto_optimization_flags}>)
        target_link_options(${opt_TARGET} ${visibility_scope}
                            $<$<CONFIG:${config}>:${phi_lto_optimization_flags}>)
      endif()
    endif()

    # Optionally enable Platform specifc optimizations
    if(DEFINED opt_PSO)
      # TODO: Support native on Windows

      # Default to native
      if(opt_PSO STREQUAL "")
        set(opt_PSO "native")
      endif()

      # Check if compiler support our PSO
      string(REPLACE "-" "_" _testName ${opt_PSO})
      string(REPLACE "=" "_" _testName ${_testName})
      string(REPLACE ":" "_" _testName ${_testName})
      string(REPLACE "_" "_" _testName ${_testName})
      string(TOUPPER ${_testName} _testName)

      phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}march=${opt_PSO}
                                  "PHI_HAS_FLAG_MARCH_${_testName}")
      if(PHI_HAS_FLAG_MARCH_${_testName})
        target_compile_options(${opt_TARGET} ${visibility_scope}
                               $<$<CONFIG:${config}>:${PHI_FLAG_PREFIX_CHAR}march=${opt_PSO}>)
        target_link_options(${opt_TARGET} ${visibility_scope}
                            $<$<CONFIG:${config}>:${PHI_FLAG_PREFIX_CHAR}march=${opt_PSO}>)
      else()

        phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}arch=${opt_PSO}
                                    "PHI_HAS_FLAG_ARCH_${_testName}")
        if(PHI_HAS_FLAG_ARCH_${_testName})
          target_compile_options(${opt_TARGET} ${visibility_scope}
                                 $<$<CONFIG:${config}>:${PHI_FLAG_PREFIX_CHAR}arch=${opt_PSO}>)
          target_link_options(${opt_TARGET} ${visibility_scope}
                              $<$<CONFIG:${config}>:${PHI_FLAG_PREFIX_CHAR}arch=${opt_PSO}>)
        else()
          phi_error("Compiler doesn't seem to support PSO for \"${opt_PSO}\"")
        endif()
      endif()
    endif()
  endforeach()
endfunction()
