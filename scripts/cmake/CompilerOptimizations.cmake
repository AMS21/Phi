phi_include_guard()

include(CMakeParseArguments)
include(internal/CheckCCompilerFlag)
include(internal/CheckLinkerFlag)

# https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Dialect-Options.html

set(phi_opt_compile_flags
    fallow-store-data-races
    fdevirtualize-speculatively
    ffinite-loops
    fforce-emit-vtables
    fgcse-las
    fgcse-sm
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
    fsched-pressure
    fsemantic-interposition
    fstrict-aliasing
    fstrict-return
    fstrict-vtable-pointers
    ftree-loop-im
    ftree-loop-ivcanon
    # MSVC
    Og # Deprecated Global Optimizations -
       # https://learn.microsoft.com/cpp/build/reference/og-global-optimizations
    Ob3 # Inline Function Expansion -
        # https://learn.microsoft.com/cpp/build/reference/ob-inline-function-expansion
    Oi # Generate Intrinsic Functions -
       # https://learn.microsoft.com/cpp/build/reference/oi-generate-intrinsic-functions
    Ot # Favor Fast Code -
       # https://learn.microsoft.com/cpp/build/reference/os-ot-favor-small-code-favor-fast-code
    Oy # Frame-Pointer Omission -
       # https://learn.microsoft.com/cpp/build/reference/oy-frame-pointer-omission
    GT # Fiber-Safe Optimizations -
       # https://learn.microsoft.com/cpp/build/reference/gt-support-fiber-safe-thread-local-storage
    GF # Eliminate Duplicate Strings / String pooling -
       # https://learn.microsoft.com/cpp/build/reference/gf-eliminate-duplicate-strings
    Gw # Optimize Global Data -
       # https://learn.microsoft.com/cpp/build/reference/gw-optimize-global-data
    Gy # Function-Level Linking -
       # https://learn.microsoft.com/cpp/build/reference/gy-enable-function-level-linking
    Qpar # Auto-parallelizer -
         # https://learn.microsoft.com/cpp/build/reference/qpar-auto-parallelizer
    Qimprecise_fwaits # Remove fwaits Inside Try Blocks -
                      # https://learn.microsoft.com/cpp/build/reference/qimprecise-fwaits-remove-fwaits-inside-try-blocks
    QIntel-jcc-erratum # https://learn.microsoft.com/cpp/build/reference/qintel-jcc-erratum
)

set(phi_opt_cxx_compile_flags fdeclone-ctor-dtor felide-constructors fimplicit-constexpr
                              fno-enforce-eh-specs fnothrow-opt fstrict-enums)

# MSVC only options which cause problems with other compilers
if(NOT PHI_COMPILER_MSVC)
  list(
    REMOVE_ITEM
    phi_opt_compile_flags
    Og
    GT
    GF
    Gw
    Gy)
endif()

# Clang on windows and emscripten seems to give errors when compiling with `fsemantic-interposition`
# (https://godbolt.org/z/cGd1WWrsW)
if((PHI_COMPILER_CLANG AND PHI_PLATFORM_WINDOWS) OR PHI_COMPILER_EMCC)
  list(REMOVE_ITEM phi_opt_compile_flags "fsemantic-interposition")
endif()

# Check C optimize flags
set(_phi_opt_compile_flags_c_supported CACHE INTERNAL "")
foreach(_test ${phi_opt_compile_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "_" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_opt_compile_flags_c_supported
        ${_phi_opt_compile_flags_c_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

# Check optimize flags for C++
set(_phi_opt_compile_flags_cxx_supported CACHE INTERNAL "")
foreach(_test ${phi_opt_cxx_compile_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "_" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_opt_compile_flags_cxx_supported
        ${_phi_opt_compile_flags_cxx_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

# https://clang.llvm.org/docs/ThinLTO.html https://llvm.org/docs/LinkTimeOptimization.html
# https://llvm.org/docs/LinkTimeOptimization.html
# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
# https://gcc.gnu.org/wiki/LinkTimeOptimization
# https://learn.microsoft.com/cpp/build/reference/ltcg-link-time-code-generation
set(phi_lto_flags flto=full flto=thin flto=${PHI_PROCESSOR_COUNT} flto LTCG)

# Check LTO support
set(old_flags ${CMAKE_REQUIRED_FLAGS})

set(_phi_opt_lto_flag CACHE INTERNAL "")
foreach(_test ${phi_lto_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "_" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} ${PHI_FLAG_PREFIX_CHAR}${_test}")

  phi_check_linker_flag(CXX ${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  set(CMAKE_REQUIRED_FLAGS ${old_flags})

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_opt_lto_flag
        ${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")

    # Don't continue since theres ever only one valid LTO flag
    break()
  endif()
endforeach(_test)

# Extra LTO flags
set(phi_extra_lto_flags
    fsplit-lto-unit Wl,--no-as-needed
    CACHE INTERNAL "")

# LTO specific optimizations
set(phi_lto_opt
    fipa-pta
    fwhole-program
    fwhole-program-vtables
    fdevirtualize-at-ltrans
    fvirtual-function-elimination
    GL # Whole Program Optimizations -
       # https://learn.microsoft.com/cpp/build/reference/gl-whole-program-optimization
)

# MSVC only options which cause problems with other compilers
if(NOT PHI_COMPILER_MSVC)
  list(REMOVE_ITEM phi_lto_opt GL)
endif()

# Check LTO specific optimizations
set(old_flags ${CMAKE_REQUIRED_FLAGS})
set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} ${_phi_opt_lto_flag}")

set(_phi_opt_lto_extra_supported CACHE INTERNAL "")
foreach(_test ${phi_lto_opt})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "_" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_opt_lto_extra_supported
        ${_phi_opt_lto_extra_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

set(CMAKE_REQUIRED_FLAGS ${old_flags})

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
      foreach(flag ${_phi_opt_compile_flags_c_supported} ${_phi_opt_compile_flags_cxx_supported})
        target_compile_options(${opt_TARGET} ${visibility_scope} $<$<CONFIG:${config}>:${flag}>)
        target_link_options(${opt_TARGET} ${visibility_scope} $<$<CONFIG:${config}>:${flag}>)
      endforeach(flag)
    elseif("${target_linker_language}" STREQUAL "C")
      # Enable C optimizations flags
      foreach(flag ${_phi_opt_compile_flags_c_supported})
        target_compile_options(${opt_TARGET} ${visibility_scope} $<$<CONFIG:${config}>:${flag}>)
        target_link_options(${opt_TARGET} ${visibility_scope} $<$<CONFIG:${config}>:${flag}>)
      endforeach(flag)
    endif()

    if(opt_LTO)
      if("${_phi_opt_lto_flag}" STREQUAL "")
        phi_warn("Requested LTO but no supported flags where found")
      else()
        # Disable LTO from CMake
        set_target_properties(${opt_TARGET} PROPERTIES INTERPROCEDURAL_OPTIMIZATION OFF)

        # Set LTO flag
        target_compile_options(${opt_TARGET} ${visibility_scope}
                               $<$<CONFIG:${config}>:${_phi_opt_lto_flag}>)
        target_link_options(${opt_TARGET} ${visibility_scope}
                            $<$<CONFIG:${config}>:${_phi_opt_lto_flag}>)

        # Enable LTO specifc optimizations
        foreach(flag ${_phi_opt_lto_extra_supported})
          target_compile_options(${opt_TARGET} ${visibility_scope} $<$<CONFIG:${config}>:${flag}>)
          target_link_options(${opt_TARGET} ${visibility_scope} $<$<CONFIG:${config}>:${flag}>)
        endforeach()
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
