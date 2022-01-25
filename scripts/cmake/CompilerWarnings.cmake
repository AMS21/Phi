phi_include_guard()

include(internal/PhiCheckCXXCompilerFlag)

# Flags
set(phi_warning_flags
    -Wall
    -Walloc-zero
    -Walloca
    -Warith-conversion
    -Warray-bounds
    -Wattribute-alias=2
    -Wbidi-chars=any
    -Wcast-align # warn for potential performance problem casts
    -Wcast-qual
    -Wconversion # warn on type conversions that may lose data
    -Wdate-time
    -Wdouble-promotion # warn if float is implicit promoted to double
    -Wduplicated-branches # warn if if / else branches have duplicated code
    -Wduplicated-cond # warn if if / else chain has duplicated conditions
    -Wenum-conversion
    -Weverything
    -Wextra # reasonable and standard
    -Wfloat-equal
    -Wformat-overflow=2
    -Wformat-signedness
    -Wformat-truncation=2
    -Wformat=2 # warn on security issues around functions that format output (ie printf)
    -Winline
    -Winvalid-pch
    -Wlifetime
    -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
    -Wmisleading-indentation # warn if identation implies blocks where blocks do not exist
    -Wmissing-field-initializers
    -Wmissing-format-attribute
    -Wmissing-include-dirs
    -Wmissing-noreturn
    -Wnoexcept
    -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual
                       # destructor. This helps catch hard to track down memory errors
    -Wnormalized
    -Wnull-dereference # warn if a null dereference is detected
    -Wold-style-cast # warn for c-style casts
    -Woverloaded-virtual # warn if you overload (not override) a virtual function
    -Wpedantic # warn if non-standard C++ is used
    -Wpointer-arith
    -Wredundant-decls
    -Wrestrict
    -Wshadow # warn the user if a variable declaration shadows one from a parent context
    -Wshift-overflow=2
    -Wsign-conversion # warn on sign conversions
    -Wstack-protector
    -Wstrict-aliasing=2
    -Wstrict-overflow=5
    -Wsuggest-attribute=cold
    -Wsuggest-attribute=const
    -Wsuggest-attribute=format
    -Wsuggest-attribute=malloc
    -Wsuggest-attribute=noreturn
    -Wsuggest-attribute=pure
    -Wsync-nand
    -Wtrampolines
    -Wundef
    -Wuninitialized
    -Wunreachable-code
    -Wunsafe-loop-optimizations
    -Wunused # warn on anything being unused
    -Wunused-const-variable=2
    -Wunused-macros
    -Wunused-parameter
    -Wuseless-cast # warn if you perform a cast to the same type
    -Wvector-operation-performance
    -Wvla
    -Wzero-as-null-pointer-constant
    # MSVC
    /Wall # Baseline reasonable warnings
    /w14242 # 'identifier': conversion from 'type1' to 'type1', possible loss of data
    /w14254 # 'operator': conversion from 'type1:field_bits' to 'type2:field_bits', possible loss
    # of data
    /w14263 # 'function': member function does not override any base class virtual member function
    /w14265 # 'classname': class has virtual functions, but destructor is not virtual instances of
    # this class may not be destructed correctly
    /w14287 # 'operator': unsigned/negative constant mismatch
    /we4289 # nonstandard extension used: 'variable': loop control variable declared in the
    # for-loop is used outside the for-loop scope
    /w14296 # 'operator': expression is always 'boolean_value'
    /w14311 # 'variable': pointer truncation from 'type1' to 'type2'
    /w14545 # expression before comma evaluates to a function which is missing an argument list
    /w14546 # function call before comma missing argument list
    /w14547 # 'operator': operator before comma has no effect; expected operator with side-effect
    /w14549 # 'operator': operator before comma has no effect; did you intend 'operator'?
    /w14555 # expression has no effect; expected expression with side- effect
    /w14619 # pragma warning: there is no warning number 'number'
    /w14640 # Enable warning on thread un-safe static member initialization
    /w14826 # Conversion from 'type1' to 'type_2' is sign-extended. This may cause unexpected
    # runtime behavior.
    /w14905 # wide string literal cast to 'LPSTR'
    /w14906 # string literal cast to 'LPWSTR'
    /w14928 # illegal copy-initialization; more than one user-defined conversion has been
    # implicitly applied
)

set(phi_pendatic_flags "-pedantic" "-pedantic-errors" "-permissive-")

set(phi_warnings_as_errors_flags "-Werror" "-WX")

set(phi_disabled_warnings_flags
    # MSVC
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
    # specified Clang
    -Wno-constexpr-not-const
    -Wno-c++1y-extensions
    -Wno-c++1z-extensions
    -Wno-c++98-compat
    -Wno-c++98-compat-pedantic
    -Wno-c++98-c++11-compat-pedantic
    -Wno-documentation-unknown-command
    -Wno-gnu-zero-variadic-macro-arguments
    -Wno-language-extension-token
    -Wno-missing-prototypes
    -Wno-missing-variable-declarations
    -Wno-padded
    -Wno-unused-template
    -Wno-variadic-macros
    -Wno-weak-vtables
    # GCC
    -Wno-unused-function)

# Checks

# Check all normal warnings
set(_WarningsAvailible)
foreach(_test ${phi_warning_flags})
  string(REPLACE "-W" "" _testName ${_test})
  string(REPLACE "/" "" _testName ${_testName})
  string(REPLACE "-" "_" _testName ${_testName})
  string(REPLACE "=" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${_test} "PHI_HAS_WARNING_${_testName}")

  if(PHI_HAS_WARNING_${_testName})
    list(APPEND _WarningsAvailible ${_test})
  endif()
endforeach(_test)

# Check pedantic
set(_PedanticAvailible)
foreach(_test ${phi_pendatic_flags})
  string(REPLACE "-W" "W_" _testName ${_test})
  string(REPLACE "/" "" _testName ${_testName})
  string(REPLACE "-" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    list(APPEND _PedanticAvailible ${_test})
  endif()
endforeach(_test)

# Check warning as error
set(_WarningAsErrorAvailible)
foreach(_test ${phi_warnings_as_errors_flags})
  string(REPLACE "-W" "" _testName ${_test})
  string(REPLACE "/" "" _testName ${_testName})
  string(REPLACE "-" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    list(APPEND _WarningAsErrorAvailible ${_test})
  endif()
endforeach(_test)

# Disabled warnings
set(_DisableWarningAvailible)
foreach(_test ${phi_disabled_warnings_flags})
  string(REPLACE "-W" "W_" _testName ${_test})
  string(REPLACE "/" "" _testName ${_testName})
  string(REPLACE "-" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    list(APPEND _DisableWarningAvailible ${_test})
  endif()
endforeach(_test)

# GCC does except all -Wno-xxxx flags even if it can't handle them
if(PHI_COMPILER_GCC)
  set(_DisableWarningAvailible "-Wno-unused-function")

  if(GCC_COMPILER_VERSION VERSION_LESS "9.0.0")
    list(REMOVE_ITEM _WarningsAvailible "-Wuseless-cast")
  endif()
endif()

# Clang before 3.4 accepts all the -wdxxxx flags from MSVC but then gives compiler errors
if(PHI_COMPILER_CLANG AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.4")
  list(FILTER _DisableWarningAvailible EXCLUDE REGEX "-wd[0-9]+")
endif()

# Emscriptens warning suppression for some reason doesn't work correctly so we disable all
if(PHI_PLATFORM_EMSCRIPTEN)
  set(_WarningsAvailible "-Wundef")
  set(_DisableWarningAvailible "${_DisableWarningAvailible};-Wno-assume")
endif()

# from here:
#
# https://github.com/lefticus/cppbestpractices/blob/master/02-Use_the_Tools_Available.md

# Enable warnings for project
function(set_project_warnings project)
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

  # Set warnings
  target_compile_options(${project} ${visibility_scope} ${_WarningsAvailible})
  target_compile_options(${project} ${visibility_scope} ${_DisableWarningAvailible})

  # Warnings as errors
  if(PHI_WARNINGS_AS_ERRORS)
    set(project_warnings ${project_warnings} ${_WarningAsErrorAvailible})
  endif()

  # Pedantic flags
  if(PHI_PEDANTIC_WARNINGS)
    set(project_warnings ${project_warnings} ${_PedanticAvailible})
  endif()
endfunction()
