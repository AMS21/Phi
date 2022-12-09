phi_include_guard()

include(CMakeParseArguments)
include(Functions)

# TODO: Improve these add flag testing and refactor into a function call

if(PHI_PLATFORM_WINDOWS)
  if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.15.0")
    if(${PHI_STANDARD_RUNTIME} STREQUAL "Static")
      set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    else()
      set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    endif()
  else()
    # TODO: Better way to get all flags since the user could have addede or removed more
    foreach(flag CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
                 CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
      if(${flag} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
      endif()
    endforeach()
  endif()
endif()

# Test support for standard library flags
# https://clang.llvm.org/docs/ClangCommandLineReference.html#cmdoption-clang-stdlib
# https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Dialect-Options.html#C_002b_002b-Dialect-Options
phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}stdlib=libc++ "PHI_HAS_FLAG_STDLIB_LIBCXX")
phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}stdlib=libstdc++ "PHI_HAS_FLAG_STDLIB_LIBSTDCXX")
phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}stdlib=platform "PHI_HAS_FLAG_STDLIB_PLATFORM")

function(phi_target_set_stdlib)
  set(CMD_OPTIONS "")
  set(CMD_ONE_VALUE "TARGET;LIBRARY")
  set(CMD_MULTI_VALUE "")

  cmake_parse_arguments(stdlib "${CMD_OPTIONS}" "${CMD_ONE_VALUE}" "${CMD_MULTI_VALUE}" ${ARGN})

  # Check required arguments are set
  if(NOT stdlib_TARGET)
    phi_error("phi_target_set_stdlib: Required argument TARGET is missing")
  endif()

  # Check that the target actually exists
  if(NOT TARGET ${stdlib_TARGET})
    phi_error(
      "phi_target_set_stdlib: The specified target \"${stdlib_TARGET}\" doesn't seem to exist")
  endif()

  if(NOT stdlib_LIBRARY)
    phi_error("phi_target_set_stdlib: Required argument LIBRARY is missing")
  endif()

  # Get target type
  get_property(
    target_type
    TARGET ${stdlib_TARGET}
    PROPERTY TYPE)

  if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
    set(visibility_scope INTERFACE)
  else()
    set(visibility_scope PRIVATE)
  endif()

  # Transform library name to lower case
  string(TOLOWER ${stdlib_LIBRARY} lib)

  # Set standard library flag
  if(${lib} STREQUAL "libc++")
    if(NOT ${PHI_HAS_FLAG_STDLIB_LIBCXX})
      phi_error(
        "phi_target_set_stdlib: The compiler doesn't seem to support 'libc++' the standard library")
    endif()

    target_compile_options(${stdlib_TARGET} ${visibility_scope}
                           ${PHI_FLAG_PREFIX_CHAR}stdlib=libc++)
    target_link_options(${stdlib_TARGET} ${visibility_scope} ${PHI_FLAG_PREFIX_CHAR}stdlib=libc++)
    target_compile_definitions(${stdlib_TARGET} ${visibility_scope} "PHI_CONFIG_STDLIB_LIBCXX")
  elseif(${lib} STREQUAL "libstdc++")
    if(NOT ${PHI_HAS_FLAG_STDLIB_LIBSTDCXX})
      phi_error(
        "phi_target_set_stdlib: The compiler doesn't seem to support 'libstdc++' the standard library"
      )
    endif()

    target_compile_options(${stdlib_TARGET} ${visibility_scope}
                           ${PHI_FLAG_PREFIX_CHAR}stdlib=libstdc++)
    target_link_options(${stdlib_TARGET} ${visibility_scope}
                        ${PHI_FLAG_PREFIX_CHAR}stdlib=libstdc++)
    target_compile_definitions(${stdlib_TARGET} ${visibility_scope} "PHI_CONFIG_STDLIB_LIBSTDCXX")
  elseif(${lib} STREQUAL "platform")
    if(NOT ${PHI_HAS_FLAG_STDLIB_PLATFORM})
      phi_error(
        "phi_target_set_stdlib: The compiler doesn't seem to support 'platform' the standard library"
      )
    endif()

    target_compile_options(${stdlib_TARGET} ${visibility_scope}
                           ${PHI_FLAG_PREFIX_CHAR}stdlib=platform)
    target_link_options(${stdlib_TARGET} ${visibility_scope} ${PHI_FLAG_PREFIX_CHAR}stdlib=platform)
    target_compile_definitions(${stdlib_TARGET} ${visibility_scope} "PHI_CONFIG_STDLIB_PLATFORM")
  elseif(${lib} STREQUAL "default")
    target_compile_definitions(${stdlib_TARGET} ${visibility_scope} "PHI_CONFIG_STDLIB_DEFAULT")
  else()
    phi_error(
      "phi_target_set_stdlib: Unsupported option ${stdlib_LIBRARY} for LIBRARY. Supported options are 'default', 'libc++', 'libstdc++' and 'platform'"
    )
  endif()
endfunction()
