phi_include_guard()

include(CMakeParseArguments)
include(internal/PhiCheckCCompilerFlag)
include(CheckLinkerFlag)

# https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Dialect-Options.html

set(phi_opt_compile_flags
    fallow-store-data-races
    fdeclone-ctor-dtor
    fdevirtualize-speculatively
    felide-constructors
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
    fno-enforce-eh-specs
    fsched-pressure
    fsemantic-interposition
    fnothrow-opt
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

# Clang and emcc claims to support 'GT' but then gives a warning (https://godbolt.org/z/P9r4czqxY)
if(PHI_COMPILER_CLANG OR PHI_PLATFORM_EMSCRIPTEN)
  list(REMOVE_ITEM phi_opt_compile_flags "GT")
endif()

# Clang on windows and emscripten seems to give errors when compiling with `fsemantic-interposition`
# (https://godbolt.org/z/cGd1WWrsW)
if((PHI_COMPILER_CLANG AND PHI_PLATFORM_WINDOWS) OR PHI_COMPILER_EMCC)
  list(REMOVE_ITEM phi_opt_compile_flags "fsemantic-interposition")
endif()

# Check optimize flags for C++
set(_phi_opt_compile_flags_cxx_supported CACHE INTERNAL "")
foreach(_test ${phi_opt_compile_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "_" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_CXX_FLAG_${_testName}")

  if(PHI_HAS_CXX_FLAG_${_testName})
    set(_phi_opt_compile_flags_cxx_supported
        ${_phi_opt_compile_flags_cxx_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

# Check C optimize flags
set(_phi_opt_compile_flags_c_supported CACHE INTERNAL "")
foreach(_test ${phi_opt_compile_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(REPLACE ":" "_" _testName ${_testName})
  string(REPLACE "_" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_c_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_C_FLAG_${_testName}")

  if(PHI_HAS_C_FLAG_${_testName})
    set(_phi_opt_compile_flags_c_supported
        ${_phi_opt_compile_flags_c_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

# https://clang.llvm.org/docs/ThinLTO.html https://llvm.org/docs/LinkTimeOptimization.html
# https://llvm.org/docs/LinkTimeOptimization.html
# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
# https://gcc.gnu.org/wiki/LinkTimeOptimization
# https://learn.microsoft.com/en-us/cpp/build/reference/ltcg-link-time-code-generation
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

  check_linker_flag(CXX ${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

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
set(phi_lto_opt fipa-pta fwhole-program fwhole-program-vtables fdevirtualize-at-ltrans
                fvirtual-function-elimination)

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
      foreach(flag ${_phi_opt_compile_flags_cxx_supported})
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
      if(${_phi_opt_lto_flag} STREQUAL "")
        phi_warn("Requested LTO but no supported flags where found")
      endif()
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
