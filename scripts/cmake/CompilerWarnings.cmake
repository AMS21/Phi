phi_include_guard()

include(CMakeParseArguments)
include(internal/PhiCheckCXXCompilerFlag)
include(internal/PhiCheckCCompilerFlag)

# References

# https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
# https://clang.llvm.org/docs/DiagnosticsReference.html
# https://clang.llvm.org/docs/ThreadSafetyAnalysis.html

# Flags
set(phi_warning_flags
    Wabi-tag
    Waligned-new=all
    Wall
    Walloc-zero
    Walloca
    Warith-conversion
    Warray-bounds
    Wattribute-alias=2
    Wbidi-chars=any
    Wcast-align # warn for potential performance problem casts
    Wcast-qual
    Wcatch-value=3
    Wclass-conversion
    Wcomma-subscript
    Wconversion # warn on type conversions that may lose data
    Wdangling-reference
    Wdate-time
    Wdelete-non-virtual-dtor
    Wdeprecated-copy
    Wdeprecated-enum-enum-conversion
    Wdeprecated-enum-float-conversion
    Wdouble-promotion # warn if float is implicit promoted to double
    Wduplicated-branches # warn if if / else branches have duplicated code
    Wduplicated-cond # warn if if / else chain has duplicated conditions
    Wenum-conversion
    Weverything
    Wextra # reasonable and standard
    Wextra-semi
    Wfloat-equal
    Wformat-overflow=2
    Wformat-signedness
    Wformat-truncation=2
    Wformat=2 # warn on security issues around functions that format output (ie printf)
    Winterference-size
    Winvalid-imported-macros
    Winvalid-pch
    Wlifetime
    Wlogical-op # warn about logical operations being used where bitwise were probably wanted
    Wmisexpect
    Wmisleading-indentation # warn if identation implies blocks where blocks do not exist
    Wmismatched-tags
    Wmissing-field-initializers
    Wmissing-format-attribute
    Wmissing-include-dirs
    Wmissing-noreturn
    Wnoexcept
    Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual
                      # destructor. This helps catch hard to track down memory errors
    Wnormalized
    Wnull-dereference # warn if a null dereference is detected
    Wold-style-cast # warn for c-style casts
    Woverloaded-virtual # warn if you overload (not override) a virtual function
    Wpedantic # warn if non-standard C++ is used
    Wplacement-new=2
    Wpointer-arith
    Wredundant-decls
    Wredundant-tags
    Wregister
    Wreorder
    Wrestrict
    Wshadow # warn the user if a variable declaration shadows one from a parent context
    Wshift-overflow=2
    Wshorten-64-to-32
    Wsign-conversion # warn on sign conversions
    Wsign-promo
    Wstack-protector
    Wstrict-aliasing=2
    Wstrict-null-sentinel
    Wstringop-overflow=2
    Wstringop-overread
    Wsuggest-attribute=cold
    Wsuggest-attribute=const
    Wsuggest-attribute=format
    Wsuggest-attribute=malloc
    Wsuggest-attribute=noreturn
    Wsuggest-attribute=pure
    Wsuggest-final-methods
    Wsuggest-final-types
    Wsuggest-override
    Wsync-nand
    Wthread-safety
    Wtrampolines
    Wundef
    Wuninitialized
    Wunreachable-code
    Wunsafe-loop-optimizations
    Wunused # warn on anything being unused
    Wunused-const-variable=2
    Wunused-parameter
    Wuse-after-free=3
    Wuseless-cast # warn if you perform a cast to the same type
    Wvector-operation-performance
    Wvla
    Wvolatile
    Wzero-as-null-pointer-constant)

set(phi_pedantic_flags "pedantic" "pedantic-errors" "permissive-")

set(phi_warnings_as_errors_flags "Werror" "WX")

set(phi_disabled_warnings_flags
    # MSVC
    wd4101 # 'x': unreferenced local variable
    wd4464 # relative include path contains '..'
    wd4481 # nonstandard extension used: override specifier 'override'
    wd4514 # 'x': unreferenced inline function has been removed
    wd4548 # expression before comma has no effect; expected expression with side-effect
    wd4571 # SEH related
    wd4577 # 'noexcept' used with no exception handling mode specified; termination on exception
    # is not guaranteed. Specify /EHsc
    wd4616 # invalid compiler warnings - https://msdn.microsoft.com/en-us/library/t7ab6xtd.aspx
    wd4619 # invalid compiler warnings - https://msdn.microsoft.com/en-us/library/tacee08d.aspx
    wd4623 # 'x': default constructor was implicitly defined as deleted
    wd4625 # 'x': copy constructor was implicitly defined as deleted
    wd4626 # 'x': assignment operator was implicitly defined as deleted
    wd4643 # Forward declaring 'x' in namespace std is not permitted by the C++ Standard.
    wd4710 # 'x': function not inlined
    wd4711 # function 'x' selected for automatic inline expansion
    wd4814 # 'x in C++14 'constexpr' will not imply 'const'; consider explicitly specifying
    # 'const'
    wd4820 # 'bytes' bytes padding added after construct 'member_name' -
    # https://msdn.microsoft.com/en-us/library/t7khkyth.aspx
    wd5026 # 'x': move constructor was implicitly defined as deleted
    wd5027 # 'x': move assignment operator was implicitly defined as deleted
    wd5045 # Compiler will insert Spectre mitigation for memory load if /Qspectre switch
    # specified
    wd4505 # 'x': unreferenced function with internal linkage has been removed
    wd4180 # qualifier applied to function type has no meaning; ignored
    wd5052 # Keyword 'char8_t' was introduced in C++20 and requires use of the '/std:c++latest'
    # command-line option
    wd4866 # compilerr may not enforce left-to-right evaluation order for call to 'x'
    wd4324 # 'struct_name' : structure was padded due to __declspec(align())
    wd5220 # 'name': a non-static data member with a volatile qualified type no longer implies that
    # compiler generated copy/move constructors and copy/move assignment operators are not trivial
    wd4061 # enumerator 'identifier' in switch of enum 'enumeration' is not explicitly handled by a
           # case label -
           # https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4061
    wd4868 # 'file(line_number)' compiler may not enforce left-to-right evaluation order in braced
           # initializer list -
           # https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-c4868
    wd5264 # 'variable-name': 'const' variable is not used -
           # https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-by-compiler-version
    Wno-constexpr-not-const
    Wno-c++1y-extensions
    Wno-c++1z-extensions
    Wno-c++2a-compat
    Wno-c++20-compat
    Wno-c++98-compat
    Wno-c++98-compat-pedantic
    Wno-c++98-c++11-compat-pedantic
    Wno-documentation-unknown-command
    Wno-gnu-zero-variadic-macro-arguments
    Wno-language-extension-token
    Wno-missing-prototypes
    Wno-missing-variable-declarations
    Wno-padded
    Wno-switch-enum # Warns about enum switches with a default label
    Wno-unused-macros
    Wno-unused-template
    Wno-variadic-macros
    Wno-weak-vtables
    # GCC
    Wno-unused-function)

set(phi_msvc_stl_extra_disable
    4668 # 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives' -
         # https://learn.microsoft.com/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4668
    5262 # implicit fall-through occurs here; are you missing a break statement? Use [[fallthrough]]
         # when a break statement is intentionally omitted between cases -
         # https://learn.microsoft.com/cpp/error-messages/compiler-warnings/compiler-warnings-by-compiler-version
)

set(phi_check_required_flags
    Werror=unknown-attributes
    Werror=attributes
    # https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4800-through-c4999
    # "attribute 'attribute-name' is not recognized"
    we5030)

# GCC does except all -Wno-xxxx flags even if it can't handle them
if(PHI_COMPILER_GCC)
  set(phi_disabled_warnings_flags "Wno-unused-function")

  if(PHI_GCC_VERSION VERSION_LESS "9.0.0")
    list(REMOVE_ITEM phi_warning_flags "Wuseless-cast")
  endif()

  if(PHI_GCC_VERSION VERSION_LESS "8.0.0")
    list(REMOVE_ITEM phi_warning_flags "Wduplicated-branches")
  endif()
endif()

# AppleClang seems to cause warnings for missing includirs which come from XCode itself so disable
# the warning here
if(PHI_COMPILER_APPLECLANG)
  list(REMOVE_ITEM phi_warning_flags "Wmissing-include-dirs")
endif()

# Disable warnings for known problematic compilers
if(PHI_IS_PROBLEMATIC_COMPILER)
  set(phi_warning_flags "Wundef")
  set(phi_disabled_warnings_flags "w")
endif()

# Checks

# Check all normal warnings for C++
set(_phi_warning_flags_cxx_supported CACHE INTERNAL "")
foreach(_test ${phi_warning_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_CXX_FLAG_${_testName}")

  if(PHI_HAS_CXX_FLAG_${_testName})
    set(_phi_warning_flags_cxx_supported
        ${_phi_warning_flags_cxx_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

# Check all C normal warnings
set(_phi_warning_flags_c_supported CACHE INTERNAL "")
foreach(_test ${phi_warning_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_c_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_C_FLAG_${_testName}")

  if(PHI_HAS_C_FLAG_${_testName})
    set(_phi_warning_flags_c_supported
        ${_phi_warning_flags_c_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

# Check pedantic
set(_phi_pedantic_flags_supported CACHE INTERNAL "")
foreach(_test ${phi_pedantic_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_pedantic_flags_supported
        ${_phi_pedantic_flags_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

# Check warning as error
set(_phi_warnings_as_errors_supported CACHE INTERNAL "")
foreach(_test ${phi_warnings_as_errors_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_warnings_as_errors_supported
        ${_phi_warnings_as_errors_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

# Disabled warnings
set(_phi_disabled_warnings_flags_supported CACHE INTERNAL "")
foreach(_test ${phi_disabled_warnings_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_disabled_warnings_flags_supported
        ${_phi_disabled_warnings_flags_supported};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

# Extra disabled warnings for MSVC stl
set(_phi_msvc_stl_extra_disable_supported CACHE INTERNAL "")
if(PHI_COMPILER_MSVC)
  foreach(_test ${phi_msvc_stl_extra_disable})
    phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}wd${_test} "PHI_HAS_FLAG_WD${_test}")

    if(PHI_HAS_FLAG_WD${_test})
      set(_phi_msvc_stl_extra_disable_supported
          "${_phi_msvc_stl_extra_disable_supported} ${_test}"
          CACHE INTERNAL "")
    endif()
  endforeach(_test)
endif()

# Check required flags
set(_phi_check_required_flags CACHE INTERNAL "")
foreach(_test ${phi_check_required_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_check_required_flags
        ${_phi_check_required_flags};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

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

  # message(STATUS "Target: ${warn_TARGET}") message(STATUS "Linker language:
  # ${target_linker_language}")

  # We're assuming CXX by default
  if("${target_linker_language}" STREQUAL "CXX" OR "${target_linker_language}" STREQUAL "")
    # Set C++ warning flags
    foreach(flag ${_phi_warning_flags_cxx_supported})
      target_compile_options(${warn_TARGET} ${visibility_scope} ${flag})
    endforeach()
  elseif("${target_linker_language}" STREQUAL "C")
    # Set C warning flags
    foreach(flag ${_phi_warning_flags_c_supported})
      target_compile_options(${warn_TARGET} ${visibility_scope} ${flag})
    endforeach()
  endif()

  # Set disabled warnings
  target_compile_options(${warn_TARGET} ${visibility_scope}
                         ${_phi_disabled_warnings_flags_supported})

  # Add optional warnings as errors
  if(warn_WARNINGS_AS_ERRORS)
    # Give a warnings if no warnigns as error flag is available
    if(NOT _phi_warnings_as_errors_supported)
      phi_warn(
        "phi_target_set_warnings: Trying to enable warnings as errors but no supported flags we're found while processing target ${warn_TARGET}"
      )
    endif()

    target_compile_options(${warn_TARGET} ${visibility_scope} ${_phi_warnings_as_errors_supported})
    target_compile_definitions(${warn_TARGET} ${visibility_scope} "PHI_CONFIG_WARNINGS_AS_ERRORS")
  endif()

  # Add optional pedantic
  if(warn_PEDANTIC)
    target_compile_options(${warn_TARGET} ${visibility_scope} ${_PedanticAvailible})
    target_compile_definitions(${warn_TARGET} ${visibility_scope} "PHI_CONFIG_PEDANTIC_WARNINGS")
  endif()

  # Disable warnings in the msvc stl
  if(PHI_COMPILER_MSVC)
    target_compile_definitions(
      ${warn_TARGET} ${visibility_scope}
                     "_STL_EXTRA_DISABLED_WARNINGS=${_phi_msvc_stl_extra_disable_supported}")
  endif()
endfunction()
