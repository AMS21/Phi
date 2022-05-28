phi_include_guard()

include(CMakeParseArguments)

set(phi_opt_compile_flags
    fallow-store-data-races
    fdeclone-ctor-dtor
    fdevirtualize-speculatively
    ffinite-loops
    fforce-emit-vtables
    fgcse-las
    fgcse-sm
    fimplicit-constexpr
    fira-hoist-pressure
    fira-loop-pressure
    fisolate-erroneous-paths-attribute
    fivopts
    floop-nest-optimize
    fmerge-all-constants
    fmerge-constants
    fmerge-functions
    fmodulo-sched
    fmodulo-sched-allow-regmoves
    fomit-frame-pointer
    fsched-pressure
    fsemantic-interposition
    fstrict-aliasing
    fstrict-enums
    fstrict-return
    fstrict-vtable-pointers
    ftree-loop-im
    ftree-loop-ivcanon
    # MSVC
    Oi
    Ot
    GT)

# Check optimize flags
set(_opt_compile_flags)
foreach(_test ${phi_opt_compile_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "_" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    list(APPEND _opt_compile_flags ${PHI_FLAG_PREFIX_CHAR}${_test})
  endif()
endforeach(_test)

# Check IPO support
if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.18.0")
  # Use the version supplied by cmake
  include(CheckIPOSupported)
  check_ipo_supported(RESULT result OUTPUT output)

  if(result)
    phi_log("Interprocedural optimization is supported")
    phi_set_cache_value(NAME PHI_SUPPORTS_IPO VALUE 1)
    phi_set_cache_value(NAME PHI_SUPPORTS_IPO_NATIVE VALUE 1)
  else()
    phi_log("Interprocedural optimization is NOT supported")
    phi_trace("Output: ${output}")

    phi_set_cache_value(NAME PHI_SUPPORTS_IPO_NATIVE VALUE 0)
    phi_set_cache_value(NAME PHI_SUPPORTS_IPO VALUE 0)
  endif()
else()
  # TODO: Implement
  phi_warn("Coudn't not determin support for IPO")
  phi_set_cache_value(NAME PHI_SUPPORTS_IPO_NATIVE VALUE 0)
  phi_set_cache_value(NAME PHI_SUPPORTS_IPO VALUE 0)
endif()

# Extra IPO flags
set(phi_extra_ipo_flags fsplit-lto-unit Wl,--no-as-needed)

# IPO specific optimizations
set(phi_ipo_opt fipa-pta fwhole-program fwhole-program-vtables fvirtual-function-elimination
                fdevirtualize-at-ltrans)

# Check ipo specific optimizations
set(old_flags ${CMAKE_REQUIRED_FLAGS})
set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} ${PHI_FLAG_PREFIX_CHAR}flto")

set(_opt_ipo_extra)
foreach(_test ${phi_ipo_opt})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "_" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    list(APPEND _opt_ipo_extra ${PHI_FLAG_PREFIX_CHAR}${_test})
  endif()
endforeach(_test)

set(CMAKE_REQUIRED_FLAGS ${old_flags})

# Clang and emcc claims to support 'GT' but then gives a warning (https://godbolt.org/z/P9r4czqxY)
if(PHI_COMPILER_CLANG OR PHI_PLATFORM_EMSCRIPTEN)
  list(REMOVE_ITEM _opt_compile_flags "${PHI_FLAG_PREFIX_CHAR}GT")
endif()

# Clang on windows seems to give errors when compiling with `fsemantic-interposition`
if(PHI_COMPILER_CLANG AND PHI_PLATFORM_WINDOWS)
  list(REMOVE_ITEM _opt_compile_flags "${PHI_FLAG_PREFIX_CHAR}fsemantic-interposition")
endif()

function(phi_target_enable_optimizations)
  # Command line arguments
  cmake_parse_arguments(opt "IPO" "TARGET;PSO" "CONFIGS" ${ARGN})

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

  # Enable options for each specified configuration
  foreach(config ${opt_CONFIGS})
    # Enable normal optimization flags
    foreach(flag ${_opt_compile_flags})
      target_compile_options(${opt_TARGET} ${visibility_scope} $<$<CONFIG:${config}>:${flag}>)
      target_link_options(${opt_TARGET} ${visibility_scope} $<$<CONFIG:${config}>:${flag}>)
    endforeach()

    if(opt_IPO)
      if(PHI_SUPPORTS_IPO_NATIVE)
        set_target_properties(${opt_TARGET} PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON)

      else()
        # TODO: Fix
        phi_warn("Can't enable IPO")
      endif()

      # Enable IPO specifc optimizations
      foreach(flag ${_opt_ipo_extra})
        target_compile_options(${opt_TARGET} ${visibility_scope} $<$<CONFIG:${config}>:${flag}>)
        target_link_options(${opt_TARGET} ${visibility_scope} $<$<CONFIG:${config}>:${flag}>)
      endforeach()
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
