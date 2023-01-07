phi_include_guard()

include(CMakeParseArguments)
include(internal/CheckCXXCompilerFlag)

set(phi_extra_debug_flags
    fasynchronous-unwind-tables
    fcf-protection=full
    fcheck-new
    fdebug-macro
    fharden-compares
    fharden-conditional-branches
    fstack-clash-protection
    fstack-protector-all
    ftrapv
    ftrivial-auto-var-init=pattern
    fvar-tracking
    fvar-tracking-assignments
    ginline-points
    grecord-command-line
    grecord-gcc-switches
    gstatement-frontiers
    mcet
    GZ # https://learn.microsoft.com/cpp/build/reference/gz-enable-stack-frame-run-time-error-checking
    guard:cf # https://learn.microsoft.com/cpp/build/reference/guard-enable-control-flow-guard
    guard:signret
    guard:ehcont
    GS # https://learn.microsoft.com/cpp/build/reference/gs-buffer-security-check
    Ge # https://learn.microsoft.com/cpp/build/reference/ge-enable-stack-probes
    sdl # Security Development Lifecycle -
    # https://learn.microsoft.com/cpp/build/reference/sdl-enable-additional-security-checks
)

# Clang on windows seems to give errors when compiling with `fstack-clash-protection`
if((PHI_COMPILER_CLANG AND PHI_PLATFORM_WINDOWS) OR PHI_COMPILER_EMCC)
  list(REMOVE_ITEM phi_extra_debug_flags "fstack-clash-protection")
endif()

# Remove "/Ge" and "/GZ" since they are deprecated since VS2005 and cause noisy compiler warnings
if("${PHI_MSVC_YEAR}" GREATER_EQUAL 2005)
  list(REMOVE_ITEM phi_extra_debug_flags "Ge" "GZ")
endif()

# MSVC only options which cause problems with other compilers
if(NOT PHI_COMPILER_MSVC)
  list(REMOVE_ITEM phi_extra_debug_flags GZ GS Ge)
endif()

# Check extra debug flags
set(_phi_extra_debug_flags_supported CACHE INTERNAL "")
foreach(_test ${phi_extra_debug_flags})
  string(REPLACE "/" "" _testName ${_test})
  string(REPLACE "-" "_" _testName ${_testName})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_extra_debug_flags_supported
        ${_phi_extra_debug_flags_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

# Extra debug flags which can ONLY be enabled with debug builds
set(phi_extra_debug_only_flags
    # https://learn.microsoft.com/cpp/build/reference/rtc-run-time-error-checks
    RTCc RTCsu)

# These flags only work with MSVC
if(NOT PHI_COMPILER_MSVC)
  set(phi_extra_debug_only_flags "")
endif()

# Check extra debug flags
set(_phi_extra_debug_only_flags_supported CACHE INTERNAL "")
foreach(_test ${phi_extra_debug_only_flags})
  string(REPLACE "/" "" _testName ${_test})
  string(REPLACE "-" "_" _testName ${_testName})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_extra_debug_only_flags_supported
        ${_phi_extra_debug_only_flags_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

set(phi_extra_debug_defines
    _GLIBCXX_ASSERTIONS _GLIBCXX_SANITIZE_VECTOR _LIBCPP_ENABLE_ASSERTIONS=1
    _LIBCPP_ENABLE_THREAD_SAFETY_ANNOTATIONS
    CACHE INTERNAL "")

function(phi_target_enable_extra_debug_flags)
  # Command line arguments
  cmake_parse_arguments(dbg "" "TARGET" "CONFIGS" ${ARGN})

  # Check required arguments
  if(NOT dbg_TARGET)
    phi_error("phi_target_enable_extra_debug_flags: You must specify TARGET")
  endif()

  # Check if target is valid
  if(NOT TARGET ${dbg_TARGET})
    phi_error(
      "phi_target_enable_extra_debug_flags: The specified target \"${dbg_TARGET}\" doesn't seem to be valid"
    )
  endif()

  # Optionally set configs
  if(NOT DEFINED ${dbg_CONFIGS})
    # set a default value
    set(dbg_CONFIGS "Debug;RelWithDebInfo")
  endif()

  # Get target type
  get_property(
    target_type
    TARGET ${dbg_TARGET}
    PROPERTY TYPE)

  if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
    set(visibility_scope INTERFACE)
  else()
    set(visibility_scope PRIVATE)
  endif()

  # Enable extra debug flags for each configuration
  foreach(config ${dbg_CONFIGS})
    if("${config}" STREQUAL "Debug")
      foreach(flag ${_phi_extra_debug_only_flags_supported})
        target_compile_options(${dbg_TARGET} ${visibility_scope} $<$<CONFIG:${config}>:${flag}>)
        target_link_options(${dbg_TARGET} ${visibility_scope} $<$<CONFIG:${config}>:${flag}>)
      endforeach()
    endif()

    # Set each flag
    foreach(flag ${_phi_extra_debug_flags_supported})
      target_compile_options(${dbg_TARGET} ${visibility_scope} $<$<CONFIG:${config}>:${flag}>)
      target_link_options(${dbg_TARGET} ${visibility_scope} $<$<CONFIG:${config}>:${flag}>)
    endforeach()

    target_compile_definitions(${dbg_TARGET} ${visibility_scope}
                                             $<$<CONFIG:${config}>:${phi_extra_debug_defines}>)
  endforeach()
endfunction()
