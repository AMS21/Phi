# from here:
#
# https://github.com/lefticus/cppbestpractices/blob/master/02-Use_the_Tools_Available.md

# Enable warnings for project
function(set_project_warnings project)
  option(PHI_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" FALSE)
  option(PHI_PEDANTIC_WARNINGS "Eanble pedantic mode" TRUE )

  set(phi_msvc_warnings
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

  set(phi_msvc_disabled_warnings
      /wd4514 # 'x': unreferenced inline function has been removed
      /wd4548 # expression before comma has no effect; expected expression with side-effect
      /wd4571 # SEH related
      /wd4623 # 'x': default constructor was implicitly defined as deleted
      /wd4625 # 'x': copy constructor was implicitly defined as deleted
      /wd4626 # 'x': assignment operator was implicitly defined as deleted
      /wd4643 # Forward declaring 'x' in namespace std is not permitted by the C++ Standard.
      /wd4710 # 'x': function not inlined
      /wd4711 # function 'x' selected for automatic inline expansion
      /wd4820 # 'bytes' bytes padding added after construct 'member_name' -
              # https://msdn.microsoft.com/en-us/library/t7khkyth.aspx
      /wd5026 # 'x': move constructor was implicitly defined as deleted
      /wd5027 # 'x': move assignment operator was implicitly defined as deleted
      /wd5045 # Compiler will insert Spectre mitigation for memory load if /Qspectre switch
              # specified
  )

  # standards conformance mode for MSVC compiler.
  set(phi_msvc_pedantic_flags
        /permissive-)

  # Clang
  set(phi_clang_warnings
      -Wall
      -Wextra # reasonable and standard
      -Wshadow # warn the user if a variable declaration shadows one from a parent context
      -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual
                         # destructor. This helps catch hard to track down memory errors
      -Wold-style-cast # warn for c-style casts
      -Wcast-align # warn for potential performance problem casts
      -Wunused # warn on anything being unused
      -Woverloaded-virtual # warn if you overload (not override) a virtual function
      -Wpedantic # warn if non-standard C++ is used
      -Wconversion # warn on type conversions that may lose data
      -Wsign-conversion # warn on sign conversions
      -Wnull-dereference # warn if a null dereference is detected
      -Wdouble-promotion # warn if float is implicit promoted to double
      -Wformat=2 # warn on security issues around functions that format output (ie printf)
      -Wcast-qual
      -Wfloat-equal
      -Wmissing-noreturn
      -Wundef
      -Wzero-as-null-pointer-constant)

  set(phi_clang_disabled_warnings)

  set(phi_clang_pedantic_flags
      -pedantic
      -pedantic-errors)

  set(phi_gcc_warnings
      ${phi_clang_warnings}
      -Wmisleading-indentation # warn if identation implies blocks where blocks do not exist
      -Wduplicated-cond # warn if if / else chain has duplicated conditions
      -Wduplicated-branches # warn if if / else branches have duplicated code
      -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
      -Wuseless-cast # warn if you perform a cast to the same type
      -Wpointer-arith
      -Wstack-protector
      -Wredundant-decls
      -Wstrict-aliasing=2
      -Wstrict-overflow=5
      -Wnoexcept
      -Wtrampolines
      -Wvector-operation-performance
      -Wshift-overflow=2
      -Walloc-zero
      -Wrestrict)

  # Warnings as errors
  if(PHI_WARNINGS_AS_ERRORS)
    set(phi_clang_warnings ${phi_clang_warnings} -Werror)
    set(phi_gcc_warnings ${phi_gcc_warnings} -Werror)
    set(phi_msvc_warnings ${phi_msvc_warnings} /WX)
  endif()

  # Pedantic flags
  if(PHI_PEDANTIC_WARNINGS)
     set(phi_clang_warnings ${phi_clang_warnings} ${phi_clang_pedantic_flags})
     set(phi_gcc_warnings ${phi_gcc_warnings} ${phi_clang_pedantic_flags})
     set(phi_msvc_warnings ${phi_msvc_warnings} ${phi_msvc_pedantic_flags})
  endif()

  # Check for correct compiler
  if(PHI_COMPILER_MSVC)
    set(project_warnings ${phi_msvc_warnings} ${phi_msvc_disabled_warnings})
  elseif(PHI_COMPILER_CLANG)
    set(project_warnings ${phi_clang_warnings})
  elseif(PHI_COMPILER_GCC)
    set(project_warnings ${phi_gcc_warnings})
  else()
    message(AUTHOR_WARNING "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
  endif()

  target_compile_options(${project} INTERFACE ${project_warnings})

endfunction()
