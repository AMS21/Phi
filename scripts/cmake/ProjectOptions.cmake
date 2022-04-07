phi_include_guard()

include(CMakeParseArguments)
include(Common)
include(CompilerDebugFlags)
include(CompilerOptimizations)
include(CompilerWarnings)
include(Coverage)
include(Exceptions)
include(FloatingPointModel)
include(Formatting)
include(Linker)
include(Sanitizers)
include(Standard)
include(StaticAnalyzers)
include(Functions)

#
function(phi_configure_project)
  # Command line arguments
  cmake_parse_arguments(
    conf
    "NO_COMMON;TIME_TRACE;DEBUG_FLAGS;IPO;OPTIMIZATION_FLAGS;WARNINGS;WARNINGS_AS_ERRORS;PEDANTIC;COVERAGE;FPM_FAST;FPM_PRECISE;NO_EXCEPTIONS;UNITY_BUILD;CXX_EXTENSIONS"
    "NAME;PSO;STANDARD"
    "SANITIZER;STATIC_ANALYZERS"
    ${ARGN})

  # General parser error
  if(conf_UNPARSED_ARGUMENTS)
    phi_error("phi_configure_project: Unrecognized arguments \"${conf_UNPARSED_ARGUMENTS}\"")
  endif()

  if(conf_KEYWORDS_MISSING_VALUES)
    phi_error("phi_configure_project: Keywords missing values \"${conf_KEYWORDS_MISSING_VALUES}\"")
  endif()

  # Check required arguments
  if(NOT DEFINED conf_NAME)
    phi_error("phi_configure_project: You must specify NAME")
  endif()

  # Check target is valid
  if(TARGET conf_NAME)
    phi_error("phi_configure_project: A target named \"${conf_NAME}\" seems to already exist")
  endif()

  # Create our target
  add_library(${conf_NAME} INTERFACE)

  # Link common unless disabled
  if(NOT conf_NO_COMMON)
    if(conf_TIME_TRACE)
      phi_target_set_common_flags(TARGET ${conf_NAME} ALL)
    else()
      phi_target_set_common_flags(TARGET ${conf_NAME} COLOR_DIAGNOSTICS)
    endif()
  endif()

  # Link Debug flags
  if(conf_DEBUG_FLAGS)
    phi_target_enable_extra_debug_flags(TARGET ${conf_NAME})
  endif()

  # Compiler Optimizations
  if(conf_OPTIMIZATION_FLAGS
     OR conf_IPO
     OR DEFINED conf_PSO)
    # Build command
    set(opt_cmd)
    if(conf_IPO)
      set(opt_cmd IPO)
    endif()
    if(DEFINED conf_PSO)
      set(opt_cmd ${opt_cmd} PSO ${conf_PSO})
    endif()

    phi_target_enable_optimizations(TARGET ${conf_NAME} ${opt_cmd})
  endif()

  # Compiler warnings
  if(conf_WARNINGS
     OR conf_WARNIGNS_AS_ERROR
     OR conf_PEDANTIC)
    # Build command
    set(warn_cmd "")
    if(conf_WARNIGNS_AS_ERROR)
      set(warn_cmd WARNINGS_AS_ERRORS)
    endif()
    if(conf_PEDANTIC)
      set(warn_cmd ${warn_cmd} PEDANTIC)
    endif()

    phi_target_set_warnings(TARGET ${conf_NAME} warn_cmd)
  endif()

  # Coverage
  if(conf_COVERAGE)
    phi_target_enable_coverage(TARGET ${conf_NAME})
  endif()

  # FloatingPointModel
  set(fpm_cmd DEFAULT)
  if(conf_FPM_FAST)
    set(fpm_cmd FAST)
  elseif(conf_FPM_PRECISE)
    set(fpm_cmd PRECISE)
  endif()

  phi_target_set_floating_point_model(TARGET ${conf_NAME} ${fpm_cmd})

  # TODO: Formatting

  # User Linker
  phi_configure_linker(${conf_NAME})

  # Sanitizers TODO:

  # Standard
  set(use_std latest)
  if(DEFINED conf_STANDARD)
    set(use_std ${conf_STANDARD})
  endif()
  phi_target_set_standard(TARGET ${conf_NAME} STANDARD ${use_std} ${conf_CXX_EXTENSIONS})

  # Static analyzer
  if(DEFINED conf_STATIC_ANALYZERS)
    set(extra)
    if(conf_WARNINGS_AS_ERRORS)
      set(extra WARNINGS_AS_ERRORS)
    endif()

    phi_target_use_static_analyzers(TARGET ${conf_NAME} ${conf_STATIC_ANALYZERS} ${extra})
  endif()

  # No exceptions
  if(conf_NO_EXCEPTIONS)
    phi_target_disable_exceptions(TARGET ${conf_NAME})
  endif()

  # Unity build
  if(conf_UNITY_BUILD)
    set_target_properties(${conf_NAME} PROPERTIES UNITY_BUILD ON)
  endif()
endfunction()

function(phi_apply_project_configuration_from)
  # Command line arguments
  cmake_parse_arguments(apply "" "TARGET" "" ${ARGN})

  # Check TARGET was specified
  if(NOT apply_TARGET)
    phi_error("phi_apply_project_configuration_from: You must specify TARGET")
  endif()

  # Check that target is actually valid
  if(NOT TARGET ${apply_TARGET})
    phi_error(
      "phi_apply_project_configuration_from: The configuration target \"${apply_TARGET}\" seems to not exists"
    )
  endif()

  set(_properties_to_apply INTERPROCEDURAL_OPTIMIZATION CXX_INCLUDE_WHAT_YOU_USE CXX_CPPCHECK
                           CXX_CLANG_TIDY UNITY_BUILD)

  # Get our properties
  foreach(prop ${_properties_to_apply})
    get_target_property(${prop} ${apply_TARGET} ${prop})
  endforeach()

  phi_get_all_targets(_targets_list)

  foreach(target ${_targets_list})
    # Get target type
    get_property(
      target_type
      TARGET ${target}
      PROPERTY TYPE)

    if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
      set(visibility_scope INTERFACE)
    elseif("${target_type}" STREQUAL "UTILITY")
      # Skip utililty targets
      continue()
    else()
      set(visibility_scope PRIVATE)
    endif()

    # Link with our target to apply all the different flags etc.
    target_link_libraries(${target} ${visibility_scope} ${apply_TARGET})

    # Properties are per target to apply them there manually
    foreach(prop ${_properties_to_apply})
      if(${prop})
        set_target_properties(${target} PROPERTIES ${prop} "${${prop}}")
      endif()
    endforeach()
  endforeach()
endfunction()
