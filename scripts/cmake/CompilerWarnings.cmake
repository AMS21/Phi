phi_include_guard()

include(CMakeParseArguments)
include(Environment)

# Set flags
if(PHI_COMPILER_CLANG)
  # https://clang.llvm.org/docs/DiagnosticsReference.html
  # https://clang.llvm.org/docs/ThreadSafetyAnalysis.html
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

  # Clang-10 flags
  if(PHI_CLANG_VERSION VERSION_GREATER_EQUAL 10)
    set(phi_disabled_warnings_flags ${phi_disabled_warnings_flags} -Wno-c++20-compat
                                    -Wno-c++20-extensions)
  endif()

  # Clang-13 flags
  if(PHI_CLANG_VERSION VERSION_GREATER_EQUAL 13)
    set(phi_disabled_warnings_flags ${phi_disabled_warnings_flags} -Wno-c++2b-extensions)
  endif()

  set(phi_check_required_flags -Werror=unknown-attributes -Werror=attributes)
elseif(PHI_COMPILER_EMCC)
  set(phi_warning_flags -Wundef)
  set(phi_cxx_warning_flags)
  set(phi_warnings_as_errors_flag -Werror)
  set(phi_pedantic_flags -pedantic -pedantic-errors)
  set(phi_disabled_warnings_flags -w)
  set(phi_check_required_flags -Werror=unknown-attributes -Werror=attributes)
elseif(PHI_COMPILER_GCC)
  # https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
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
      -Wmissing-include-dirs
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
      -Wuseless-cast # warn if you perform a cast to the same type
      -Wzero-as-null-pointer-constant)

  # GCC-9 flags
  if(PHI_GCC_VERSION VERSION_GREATER_EQUAL 9)
    set(phi_warning_flags ${phi_warning_flags} -Wattribute-alias=2)
    set(phi_cxx_warning_flags ${phi_cxx_warning_flags} -Wclass-conversion -Wdeprecated-copy)
  else()
    set(phi_warning_flags ${phi_warning_flags} -Wattribute-alias)
  endif()

  # GCC-10 flags
  if(PHI_GCC_VERSION VERSION_GREATER_EQUAL 10)
    set(phi_warning_flags ${phi_warning_flags} -Warith-conversion)
    set(phi_cxx_warning_flags ${phi_cxx_warning_flags} -Wcomma-subscript -Wmismatched-tags
                              -Wredundant-tags -Wvolatile)
  endif()

  # GCC-11 flags
  if(PHI_GCC_VERSION VERSION_GREATER_EQUAL 11)
    set(phi_warning_flags ${phi_warnings_flags} -Wenum-conversion -Wstringop-overread)
    set(phi_cxx_warning_flags ${phi_cxx_warning_flags} -Wdeprecated-enum-enum-conversion
                              -Wdeprecated-enum-float-conversion -Winvalid-imported-macros)
  endif()

  # GCC-12 flags
  if(PHI_GCC_VERSION VERSION_GREATER_EQUAL 12)
    set(phi_warning_flags ${phi_warning_flags} -Wbidi-chars=any -Wuse-after-free=3)
    set(phi_cxx_warning_flags ${phi_cxx_warning_flags} -Winterference-size)
  endif()

  set(phi_warnings_as_errors_flag -Werror)
  set(phi_pedantic_flags -pedantic -pedantic-errors)
  set(phi_disabled_warnings_flags -Wno-padded -Wno-switch-enum -Wno-unused-macros
                                  -Wno-variadic-macros -Wno-unused-function)
  set(phi_check_required_flags -Werror=attributes)
elseif(PHI_COMPILER_MSVC)
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
endif()

# MacOS seems to have problems for missing include directories which come from MacOS SDK itself so
# disable the warning here
if(PHI_PLATFORM_APPLE)
  list(REMOVE_ITEM phi_warning_flags -Wmissing-include-dirs)
endif()

# from here:
#
# https://github.com/lefticus/cppbestpractices/blob/master/02-Use_the_Tools_Available.md

# Enable warnings for project
function(phi_target_set_warnings)
  # Command line arguments
  cmake_parse_arguments(warn "WARNINGS_AS_ERRORS;PEDANTIC" "TARGET" "" ${ARGN})

  # Check required arguments
  if(NOT DEFINED warn_TARGET)
    phi_error("phi_target_set_warnings: You must specify a target with TARGET")
  endif()

  # Check target actually exists
  if(NOT TARGET ${warn_TARGET})
    phi_error(
      "phi_target_set_warnings: The specified target \"${warn_TARGET}\" doesn't seem to exist")
  endif()

  # Get target type
  get_property(
    target_type
    TARGET ${warn_TARGET}
    PROPERTY TYPE)

  if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
    set(visibility_scope INTERFACE)
  else()
    set(visibility_scope PRIVATE)
  endif()

  # Get linker language
  get_property(
    target_linker_language
    TARGET ${warn_TARGET}
    PROPERTY LINKER_LANGUAGE)

  # We're assuming CXX by default
  if("${target_linker_language}" STREQUAL "CXX" OR "${target_linker_language}" STREQUAL "")
    # Set C/C++ warning flags
    target_compile_options(${warn_TARGET} ${visibility_scope} ${phi_warning_flags}
                           ${phi_cxx_warning_flags})
  elseif("${target_linker_language}" STREQUAL "C")
    # Set only C warning flags
    target_compile_options(${warn_TARGET} ${visibility_scope} ${phi_warning_flags})
  endif()

  # Set disabled warnings
  target_compile_options(${warn_TARGET} ${visibility_scope} ${phi_disabled_warnings_flags})

  # Add optional warnings as errors
  if(warn_WARNINGS_AS_ERRORS)
    target_compile_options(${warn_TARGET} ${visibility_scope} ${phi_warnings_as_errors_flag})
    target_compile_definitions(${warn_TARGET} ${visibility_scope} "PHI_CONFIG_WARNINGS_AS_ERRORS")
  endif()

  # Add optional pedantic
  if(warn_PEDANTIC)
    target_compile_options(${warn_TARGET} ${visibility_scope} ${phi_pedantic_flags})
    target_compile_definitions(${warn_TARGET} ${visibility_scope} "PHI_CONFIG_PEDANTIC_WARNINGS")
  endif()
endfunction()
