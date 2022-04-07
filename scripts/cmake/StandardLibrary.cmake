phi_include_guard()

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

if(PHI_COMPILER_CLANG)
  if(${PHI_STANDARD_LIBRARY} STREQUAL "libc++")
    target_compile_options(phi_project_options INTERFACE -stdlib=libc++)
    target_link_libraries(phi_project_options INTERFACE -stdlib=libc++)
  endif()
endif()

function(phi_target_configure_std_lib)
  # TODO: Implement me!
endfunction()
