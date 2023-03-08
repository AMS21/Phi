phi_include_guard()

include(Environment)
include(internal/SetCacheValue)

if(PHI_COMPILER_CLANG)
  # https://clang.llvm.org/docs/DiagnosticsReference.html
  # https://clang.llvm.org/docs/ThreadSafetyAnalysis.html https://clang.llvm.org/docs/ThinLTO.html
  # https://llvm.org/docs/LinkTimeOptimization.html https://llvm.org/docs/LinkTimeOptimization.html
  # https://clang.llvm.org/docs/SourceBasedCodeCoverage.html
  # https://clang.llvm.org/docs/ClangCommandLineReference.html

  set(phi_warning_flags -Weverything -Wformat=2 -Wstrict-aliasing=2)
  set(phi_cxx_warning_flags)
  set(phi_warnings_as_errors_flag -Werror)
  set(phi_pedantic_flags -pedantic -pedantic-errors)
  set(phi_disabled_warnings_flags
      -Wno-constexpr-not-const
      -Wno-c++-compat
      -Wno-c++0x-compat
      -Wno-c++0x-extensions
      -Wno-c++0x-narrowing
      -Wno-c++1y-extensions
      -Wno-c++1z-compat
      -Wno-c++1z-extensions
      -Wno-c++2a-compat
      -Wno-c++2a-extensions
      -Wno-c++11-compat
      -Wno-c++11-extensions
      -Wno-c++11-narrowing
      -Wno-c++14-compat
      -Wno-c++14-extensions
      -Wno-c++17-compat
      -Wno-c++17-extensions
      -Wno-c++98-compat
      -Wno-c++98-compat-pedantic
      -Wno-c++98-c++11-compat
      -Wno-c++98-c++11-compat-pedantic
      -Wno-c++98-c++11-c++14-compat
      -Wno-c++98-c++11-c++14-compat-pedantic
      -Wno-c++98-c++11-c++14-c++17-compat
      -Wno-c++98-c++11-c++14-c++17-compat-pedantic
      -Wno-documentation-unknown-command
      -Wno-gnu-zero-variadic-macro-arguments
      -Wno-language-extension-token
      -Wno-missing-prototypes
      -Wno-missing-variable-declarations
      -Wno-padded
      -Wno-switch-enum
      -Wno-unused-macros
      -Wno-unused-template
      -Wno-variadic-macros
      -Wno-weak-vtables)
  set(phi_check_required_flags -Werror=unknown-attributes -Werror=attributes)
  set(phi_optimize_flags
      -felide-constructors
      -fforce-emit-vtables
      -fmerge-all-constants
      -fstrict-aliasing
      -fstrict-enums
      -fstrict-return
      -fstrict-vtable-pointers)
  set(phi_cxx_optimize_flags)
  set(phi_lto_flags -flto=full -fsplit-lto-unit)
  set(phi_lto_optimization_flags -fwhole-program-vtables -fvirtual-function-elimination)
  set(phi_common_flags
      -fborland-extensions
      -fdeclspec
      -fmacro-backtrace-limit=0
      -fms-extensions
      -pipe
      -faligned-new
      -fsized-deallocation
      -fchar8_t)
  set(phi_cxx_common_flags)
  set(phi_color_diagnostics_flag -fdiagnostics-color=always)
  set(phi_disable_all_warnings_flag -w)
  set(phi_debug_flags -fasynchronous-unwind-tables -fcheck-new -fdebug-macro
                      -ftrivial-auto-var-init=pattern -grecord-command-line)
  set(phi_debug_only_flags)
  set(phi_coverage_compile_flags -fno-common -fno-inline -fno-inline-functions
                                 -fno-omit-frame-pointer)
  set(phi_coverage_link_flags -fprofile-arcs -ftest-coverage -fprofile-instr-generate
                              -fcoverage-mapping)
  set(phi_noexcept_flag -fno-exceptions)
  set(phi_fast_math_flags
      -ffast-math
      -fassociative-math
      -ffinite-math-only
      -ffp-contract=fast
      -ffp-exception-behavior=ignore
      -ffp-model=fast
      -fno-honor-infinities
      -fno-honor-nans
      -fno-math-errno
      -fno-rounding-math
      -fno-signed-zeros
      -fno-trapping-math
      -freciprocal-math
      -funsafe-math-optimizations)
  set(phi_precise_math_flags -ffp-contract=off -ffp-exception-behavior=strict -ffp-model=precise)
  set(phi_no_rtti_flags -fno-rtti)

  # Clang-10 flags
  if(PHI_CLANG_VERSION VERSION_GREATER_EQUAL 10)
    set(phi_disabled_warnings_flags ${phi_disabled_warnings_flags} -Wno-c++20-compat
                                    -Wno-c++20-extensions)
  endif()

  # Clang-11 flags
  if(PHI_CLANG_VERSION VERSION_GREATER_EQUAL 11)
    # stack-clash-protection basically only works with linux
    if(PHI_PLATFORM_LINUX)
      set(phi_debug_flags ${phi_debug_flags} -fstack-clash-protection)
    endif()
  endif()

  # Clang-12 flags
  if(PHI_CLANG_VERSION VERSION_GREATER_EQUAL 12)
    set(phi_optimize_flags ${phi_optimize_flags} -ffinite-loops)
  endif()

  # Clang-13 flags
  if(PHI_CLANG_VERSION VERSION_GREATER_EQUAL 13)
    set(phi_disabled_warnings_flags ${phi_disabled_warnings_flags} -Wno-c++2b-extensions)
  endif()

elseif(PHI_COMPILER_EMCC)

  set(phi_warning_flags -Wundef)
  set(phi_cxx_warning_flags)
  set(phi_warnings_as_errors_flag -Werror)
  set(phi_pedantic_flags -pedantic -pedantic-errors)
  set(phi_disabled_warnings_flags -w)
  set(phi_check_required_flags -Werror=unknown-attributes -Werror=attributes)
  set(phi_optimize_flags
      -felide-constructors
      -ffinite-loops
      -fforce-emit-vtables
      -fmerge-all-constants
      -fstrict-aliasing
      -fstrict-enums
      -fstrict-return
      -fstrict-vtable-pointers)
  set(phi_cxx_optimize_flags)
  set(phi_lto_flags -flto=full -fsplit-lto-unit -Wl,--no-as-needed)
  set(phi_lto_optimization_flags -fwhole-program-vtables -fvirtual-function-elimination)
  set(phi_common_flags
      -bigobj
      -fborland-extensions
      -fdeclspec
      -fmacro-backtrace-limit=0
      -fms-extensions
      -pipe
      -faligned-new
      -fsized-deallocation
      -fchar8_t)
  set(phi_cxx_common_flags)
  set(phi_color_diagnostics_flag -fdiagnostics-color=always)
  set(phi_disable_all_warnings_flag -w)
  set(phi_debug_flags -fasynchronous-unwind-tables -fcheck-new -fdebug-macro
                      -ftrivial-auto-var-init=pattern -grecord-command-line)
  set(phi_debug_only_flags)
  set(phi_coverage_compile_flags)
  set(phi_coverage_link_flags)
  set(phi_noexcept_flag -fno-exceptions)
  set(phi_fast_math_flags
      -ffast-math
      -fassociative-math
      -ffinite-math-only
      -ffp-contract=fast
      -ffp-exception-behavior=ignore
      -ffp-model=fast
      -fno-honor-infinities
      -fno-honor-nans
      -fno-math-errno
      -fno-rounding-math
      -fno-signed-zeros
      -fno-trapping-math
      -freciprocal-math
      -funsafe-math-optimizations)
  set(phi_precise_math_flags -ffp-contract=off -ffp-exception-behavior=strict -ffp-model=precise)
  set(phi_no_rtti_flags -fno-rtti)

elseif(PHI_COMPILER_GCC)

  # https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Dialect-Options.html
  # https://gcc.gnu.org/onlinedocs/gcc/Debugging-Options.html
  # https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html
  # https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
  # https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
  # https://gcc.gnu.org/wiki/LinkTimeOptimization

  set(phi_warning_flags
      -Wall
      -Walloc-zero
      -Walloca
      -Warray-bounds
      -Wcast-align # warn for potential performance problem casts
      -Wcast-qual
      -Wconversion # warn on type conversions that may lose data
      -Wdate-time
      -Wdouble-promotion # warn if float is implicit promoted to double
      -Wduplicated-branches # warn if if / else branches have duplicated code
      -Wduplicated-cond # warn if if / else chain has duplicated conditions
      -Wextra # reasonable and standard
      -Wfloat-equal
      -Wformat-overflow=2
      -Wformat-signedness
      -Wformat-truncation=2
      -Wformat=2 # warn on security issues around functions that format output (ie printf)
      -Winvalid-pch
      -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
      -Wmisleading-indentation # warn if identation implies blocks where blocks do not exist
      -Wmissing-field-initializers
      -Wmissing-format-attribute
      -Wmissing-noreturn
      -Wnormalized
      -Wnull-dereference # warn if a null dereference is detected
      -Wpedantic # warn if non-standard C++ is used
      -Wpointer-arith
      -Wredundant-decls
      -Wrestrict
      -Wshadow # warn the user if a variable declaration shadows one from a parent context
      -Wshift-overflow=2
      -Wsign-conversion # warn on sign conversions
      -Wstack-protector
      -Wstrict-aliasing=2
      -Wstringop-overflow=2
      -Wsuggest-attribute=cold
      -Wsuggest-attribute=const
      -Wsuggest-attribute=format
      -Wsuggest-attribute=malloc
      -Wsuggest-attribute=noreturn
      -Wsuggest-attribute=pure
      -Wsuggest-final-methods
      -Wsuggest-final-types
      -Wsync-nand
      -Wtrampolines
      -Wundef
      -Wuninitialized
      -Wunreachable-code
      -Wunsafe-loop-optimizations
      -Wunused # warn on anything being unused
      -Wunused-const-variable=2
      -Wunused-parameter
      -Wvector-operation-performance
      -Wvla)
  set(phi_cxx_warning_flags
      -Waligned-new=all
      -Wcatch-value=3
      -Wdelete-non-virtual-dtor
      -Wextra-semi
      -Wnoexcept
      -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual
      # destructor. This helps catch hard to track down memory errors
      -Wold-style-cast # warn for c-style casts
      -Woverloaded-virtual # warn if you overload (not override) a virtual function
      -Wplacement-new=2
      -Wregister
      -Wreorder
      -Wsign-promo
      -Wstrict-null-sentinel
      -Wsuggest-override
      -Wzero-as-null-pointer-constant)
  set(phi_warnings_as_errors_flag -Werror)
  set(phi_pedantic_flags -pedantic -pedantic-errors)
  set(phi_disabled_warnings_flags -Wno-padded -Wno-switch-enum -Wno-unused-macros
                                  -Wno-variadic-macros -Wno-unused-function)
  set(phi_check_required_flags -Werror=attributes)
  set(phi_optimize_flags
      -fdevirtualize-speculatively
      -fgcse-las
      -fgcse-sm
      -fira-hoist-pressure
      -fira-loop-pressure
      -fisolate-erroneous-paths-attribute
      -fivopts
      -floop-nest-optimize
      -fmerge-all-constants
      -fmerge-constants
      -fmodulo-sched
      -fmodulo-sched-allow-regmoves
      -fsched-pressure
      -fstrict-aliasing
      -ftree-loop-im
      -ftree-loop-ivcanon)
  set(phi_cxx_optimize_flags -fdeclone-ctor-dtor -felide-constructors -fno-enforce-eh-specs
                             -fnothrow-opt -fstrict-enums)
  set(phi_lto_flags -flto=${PHI_PROCESSOR_COUNT} -fsplit-lto-unit -Wl,--no-as-needed)
  set(phi_lto_optimization_flags -fipa-pta -fwhole-program -fwhole-program-vtables
                                 -fdevirtualize-at-ltrans -fvirtual-function-elimination)
  set(phi_common_flags -fms-extensions -fstrong-eval-order -pipe)
  set(phi_cxx_common_flags -faligned-new -fsized-deallocation -fconcepts)
  set(phi_color_diagnostics_flag -fdiagnostics-color)
  set(phi_disable_all_warnings_flag -w)
  set(phi_debug_flags
      -fasynchronous-unwind-tables
      -fcheck-new
      -fvar-tracking
      -fvar-tracking-assignments
      -ginline-points
      -grecord-gcc-switches
      -gstatement-frontiers)
  set(phi_debug_only_flags)
  set(phi_coverage_compile_flags -fno-common -fno-inline -fno-inline-functions
                                 -fno-omit-frame-pointer -fprofile-abs-path)
  set(phi_coverage_link_flags -fprofile-arcs -ftest-coverage --coverage)
  set(phi_noexcept_flag -fno-exceptions)
  set(phi_fast_math_flags
      -ffast-math
      -fassociative-math
      -fcx-limited-range
      -fexcess-precision=fast
      -ffinite-math-only
      -ffp-contract=fast
      -fno-math-errno
      -fno-rounding-math
      -fno-signaling-nans
      -fno-signed-zeros
      -fno-trapping-math
      -freciprocal-math
      -funsafe-math-optimizations)
  set(phi_precise_math_flags -ffp-contract=off)
  set(phi_no_rtti_flags -fno-rtti)

  # MacOS seems to have problems for missing include directories which come from MacOS SDK itself so
  # we only enable it on non MacOS platforms
  if(NOT PHI_PLATFORM_APPLE)
    set(phi_warning_flags ${phi_warning_flags} -Wmissing-include-dirs)
  endif()

  # GCC-9 flags
  if(PHI_GCC_VERSION VERSION_GREATER_EQUAL 9)
    set(phi_warning_flags ${phi_warning_flags} -Wattribute-alias=2 -Wuseless-cast)
    set(phi_cxx_warning_flags ${phi_cxx_warning_flags} -Wclass-conversion -Wdeprecated-copy)
    set(phi_cxx_common_flags ${phi_cxx_common_flags} -fchar8_t)
  else()
    set(phi_warning_flags ${phi_warning_flags} -Wattribute-alias)
  endif()

  # GCC-10 flags
  if(PHI_GCC_VERSION VERSION_GREATER_EQUAL 10)
    set(phi_warning_flags ${phi_warning_flags} -Warith-conversion)
    set(phi_cxx_warning_flags ${phi_cxx_warning_flags} -Wcomma-subscript -Wmismatched-tags
                              -Wredundant-tags -Wvolatile)
    set(phi_optimize_flags ${phi_optimize_flags} -ffinite-loops)
    set(phi_cxx_optimize_flags ${phi_cxx_optimize_flags} -fallow-store-data-races)
    set(phi_cxx_common_flags ${phi_cxx_common_flags} -fcoroutines)
  endif()

  # GCC-11 flags
  if(PHI_GCC_VERSION VERSION_GREATER_EQUAL 11)
    set(phi_warning_flags ${phi_warnings_flags} -Wenum-conversion -Wstringop-overread)
    set(phi_cxx_warning_flags ${phi_cxx_warning_flags} -Wdeprecated-enum-enum-conversion
                              -Wdeprecated-enum-float-conversion -Winvalid-imported-macros)
    set(phi_common_flags ${phi_common_flags} -flarge-source-files)
  endif()

  # GCC-12 flags
  if(PHI_GCC_VERSION VERSION_GREATER_EQUAL 12)
    set(phi_warning_flags ${phi_warning_flags} -Wbidi-chars=any -Wuse-after-free=3)
    set(phi_cxx_warning_flags ${phi_cxx_warning_flags} -Winterference-size)
    set(phi_cxx_optimize_flags ${phi_cxx_optimize_flags} -fimplicit-constexpr)
    set(phi_debug_flags ${phi_debug_flags} -fharden-compares -fharden-conditional-branches
                        -ftrivial-auto-var-init=pattern)
  endif()

elseif(PHI_COMPILER_MSVC)

  # https://learn.microsoft.com/cpp/build/reference/ltcg-link-time-code-generation

  set(phi_warning_flags /Wall)
  set(phi_cxx_warning_flags)
  set(phi_warnings_as_errors_flag /WX)
  set(phi_pedantic_flags /permissive-)
  set(phi_disabled_warnings_flags
      /wd4101 # 'x': unreferenced local variable
      /wd4464 # relative include path contains '..'
      /wd4481 # nonstandard extension used: override specifier 'override'
      /wd4514 # 'x': unreferenced inline function has been removed
      /wd4548 # expression before comma has no effect; expected expression with side-effect
      /wd4571 # SEH related
      /wd4577 # 'noexcept' used with no exception handling mode specified; termination on exception
      # is not guaranteed. Specify /EHsc
      /wd4616 # invalid compiler warnings - https://msdn.microsoft.com/en-us/library/t7ab6xtd.aspx
      /wd4619 # invalid compiler warnings - https://msdn.microsoft.com/en-us/library/tacee08d.aspx
      /wd4623 # 'x': default constructor was implicitly defined as deleted
      /wd4625 # 'x': copy constructor was implicitly defined as deleted
      /wd4626 # 'x': assignment operator was implicitly defined as deleted
      /wd4643 # Forward declaring 'x' in namespace std is not permitted by the C++ Standard.
      /wd4710 # 'x': function not inlined
      /wd4711 # function 'x' selected for automatic inline expansion
      /wd4814 # 'x in C++14 'constexpr' will not imply 'const'; consider explicitly specifying
      # 'const'
      /wd4820 # 'bytes' bytes padding added after construct 'member_name' -
      # https://msdn.microsoft.com/en-us/library/t7khkyth.aspx
      /wd5026 # 'x': move constructor was implicitly defined as deleted
      /wd5027 # 'x': move assignment operator was implicitly defined as deleted
      /wd5045 # Compiler will insert Spectre mitigation for memory load if /Qspectre switch
      # specified
      /wd4505 # 'x': unreferenced function with internal linkage has been removed
      /wd4180 # qualifier applied to function type has no meaning; ignored
      /wd5052 # Keyword 'char8_t' was introduced in C++20 and requires use of the '/std:c++latest'
      # command-line option
      /wd4866 # compilerr may not enforce left-to-right evaluation order for call to 'x'
      /wd4324 # 'struct_name' : structure was padded due to __declspec(align())
      /wd5220 # 'name': a non-static data member with a volatile qualified type no longer implies
      # that compiler generated copy/move constructors and copy/move assignment operators are not
      # trivial
      /wd4061 # enumerator 'identifier' in switch of enum 'enumeration' is not explicitly handled by
      # a case label -
      # https://learn.microsoft.com/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4061
      /wd4868 # 'file(line_number)' compiler may not enforce left-to-right evaluation order in
              # braced
      # initializer list -
      # https://learn.microsoft.com/cpp/error-messages/compiler-warnings/compiler-warning-c4868
      /wd5264 # 'variable-name': 'const' variable is not used -
      # https://learn.microsoft.com/cpp/error-messages/compiler-warnings/compiler-warnings-by-compiler-version
  )
  set(phi_check_required_flags
      # https://learn.microsoft.com/cpp/error-messages/compiler-warnings/compiler-warnings-c4800-through-c4999
      # "attribute 'attribute-name' is not recognized"
      /we5030)
  set(phi_optimize_flags
      # Deprecated Global Optimizations -
      # https://learn.microsoft.com/cpp/build/reference/og-global-optimizations
      /Og
      # Inline Function Expansion -
      # https://learn.microsoft.com/cpp/build/reference/ob-inline-function-expansion
      /Ob3
      # Generate Intrinsic Functions -
      # https://learn.microsoft.com/cpp/build/reference/oi-generate-intrinsic-functions
      /Oi
      # Favor Fast Code -
      # https://learn.microsoft.com/cpp/build/reference/os-ot-favor-small-code-favor-fast-code
      /Ot
      # Frame-Pointer Omission -
      # https://learn.microsoft.com/cpp/build/reference/oy-frame-pointer-omission
      /Oy
      # Fiber-Safe Optimizations -
      # https://learn.microsoft.com/cpp/build/reference/gt-support-fiber-safe-thread-local-storage
      /GT
      # Eliminate Duplicate Strings / String pooling -
      # https://learn.microsoft.com/cpp/build/reference/gf-eliminate-duplicate-strings
      /GF
      # Optimize Global Data -
      # https://learn.microsoft.com/cpp/build/reference/gw-optimize-global-data
      /Gw
      # Function-Level Linking -
      # https://learn.microsoft.com/cpp/build/reference/gy-enable-function-level-linking
      /Gy
      # Auto-parallelizer - https://learn.microsoft.com/cpp/build/reference/qpar-auto-parallelizer
      /Qpar
      # Remove fwaits Inside Try Blocks -
      # https://learn.microsoft.com/cpp/build/reference/qimprecise-fwaits-remove-fwaits-inside-try-blocks
      /Qimprecise_fwaits
      # https://learn.microsoft.com/cpp/build/reference/qintel-jcc-erratum
      /QIntel-jcc-erratum)
  set(phi_cxx_optimize_flags)
  set(phi_lto_flags /LTCG)
  set(phi_lto_optimization_flags /GL # Whole Program Optimizations -
      # https://learn.microsoft.com/cpp/build/reference/gl-whole-program-optimization
  )
  set(phi_common_flags
      /MP # https://learn.microsoft.com/cpp/build/reference/mp-build-with-multiple-processes
      /Zc:preprocessor # https://learn.microsoft.com/cpp/build/reference/zc-preprocessor
      /Zc:__cplusplus # https://learn.microsoft.com/cpp/build/reference/zc-cplusplus
      /Zc:char8_t # https://learn.microsoft.com/cpp/build/reference/zc-char8-t
      /Zc:rvalueCast # https://learn.microsoft.com/cpp/build/reference/zc-rvaluecast-enforce-type-conversion-rules
      # https://learn.microsoft.com/cpp/build/reference/external-external-headers-diagnostics
      /experimental:external
      /external:W0
      /external:anglebrackets
      /analyze:external- # https://learn.microsoft.com/cpp/build/reference/analyze-code-analysis
      /FC # https://learn.microsoft.com/cpp/build/reference/fc-full-path-of-source-code-file-in-diagnostics
  )
  set(phi_cxx_common_flags)
  set(phi_color_diagnostics_flag)
  set(phi_disable_all_warnings_flag /W0)
  set(phi_debug_flags
      /sdl # Security Development Lifecycle -
      # https://learn.microsoft.com/cpp/build/reference/sdl-enable-additional-security-checks
  )
  set(phi_debug_only_flags
      # https://learn.microsoft.com/cpp/build/reference/rtc-run-time-error-checks
      /RTCc /RTCsu)
  set(phi_coverage_compile_flags)
  set(phi_coverage_link_flags)
  set(phi_noexcept_flag) # TODO: Add support for MSVC
  set(phi_fast_math_flags /fp:fast /fp:except-)
  set(phi_precise_math_flags /fp:precise)
  set(phi_no_rtti_flags # https://learn.microsoft.com/cpp/build/reference/gr-enable-run-time-type-information
      /GR-)

  # "/Ge" and "/GZ" were deprecated with VS2005 and cause noisy compiler warnings
  if("${PHI_MSVC_YEAR}" VERSION_LESS 2005)
    set(phi_debug_flags
        ${phi_debug_flags}
        /Ge # https://learn.microsoft.com/cpp/build/reference/ge-enable-stack-probes
        /GZ # https://learn.microsoft.com/cpp/build/reference/gz-enable-stack-frame-run-time-error-checking
    )
  endif()
endif()

# Move all flags to the cache
phi_set_cache_value(phi_warning_flags "${phi_warning_flags}")
phi_set_cache_value(phi_cxx_warning_flags "${phi_cxx_warning_flags}")
phi_set_cache_value(phi_warnings_as_errors_flag "${phi_warnings_as_errors_flag}")
phi_set_cache_value(phi_pedantic_flags "${phi_pedantic_flags}")
phi_set_cache_value(phi_disabled_warnings_flags "${phi_disabled_warnings_flags}")
phi_set_cache_value(phi_check_required_flags "${phi_check_required_flags}")
phi_set_cache_value(phi_optimize_flags "${phi_optimize_flags}")
phi_set_cache_value(phi_cxx_optimize_flags "${phi_cxx_optimize_flags}")
phi_set_cache_value(phi_lto_flags "${phi_lto_flags}")
phi_set_cache_value(phi_lto_optimization_flags "${phi_lto_optimization_flags}")
phi_set_cache_value(phi_common_flags "${phi_common_flags}")
phi_set_cache_value(phi_cxx_common_flags "${phi_cxx_common_flags}")
phi_set_cache_value(phi_disable_all_warnings_flag "${phi_disable_all_warnings_flag}")
phi_set_cache_value(phi_debug_flags "${phi_debug_flags}")
phi_set_cache_value(phi_debug_only_flags "${phi_debug_only_flags}")
phi_set_cache_value(phi_coverage_compile_flags "${phi_coverage_compile_flags}")
phi_set_cache_value(phi_coverage_link_flags "${phi_coverage_link_flags}")
phi_set_cache_value(phi_noexcept_flag "${phi_noexcept_flag}")
phi_set_cache_value(phi_fast_math_flags "${phi_fast_math_flags}")
phi_set_cache_value(phi_precise_math_flags "${phi_precise_math_flags}")
