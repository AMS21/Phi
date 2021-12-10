phi_include_guard()

include(CMakeParseArguments)

# C++-11/14 Flags were introduces in CMake 3.1
if(${CMAKE_VERSION} VERSION_LESS "3.1")
  # C++-11
  set(phi_known_cxx11_flags "-std=c++11" "-std=c++0x" "-std:c++11" "-std:c++latest" "-Qstd=c++11")
  set(phi_known_cxx11_ext_flags "-std=gnu++11" "-std=gnu++0x")

  # Check normal flag
  foreach(flag IN ITEMS ${phi_known_cxx11_flags})
    set(var_name "PHI_STANDARD_FLAG${flag}")
    string(REPLACE "-" "_" var_name ${var_name})
    string(REPLACE "=" "_" var_name ${var_name})
    string(REPLACE ":" "_" var_name ${var_name})

    phi_check_cxx_compiler_flag(${flag} ${var_name})

    if(${var_name})
      phi_set_cache_value(NAME CMAKE_CXX11_STANDARD_COMPILE_OPTION VALUE ${flag})
      break()
    endif()
  endforeach()

  # Check extension flags
  foreach(flag IN ITEMS ${phi_known_cxx11_ext_flags})
    set(var_name "PHI_EXTENSION_FLAG${flag}")
    string(REPLACE "-" "_" var_name ${var_name})
    string(REPLACE "=" "_" var_name ${var_name})
    string(REPLACE ":" "_" var_name ${var_name})

    phi_check_cxx_compiler_flag(${flag} ${var_name})

    if(${var_name})
      phi_set_cache_value(NAME CMAKE_CXX11_EXTENSION_COMPILE_OPTION VALUE ${flag})
      break()
    endif()
  endforeach()

  # C++-14
  set(phi_known_cxx14_flags "-std=c++14" "-std=c++1y" "-std:c++14" "-std:c++latest" "-Qstd=c++14")
  set(phi_known_cxx14_ext_flags "-std=gnu++14" "-std=gnu++1y")

  # Check normal flag
  foreach(flag IN ITEMS ${phi_known_cxx14_flags})
    set(var_name "PHI_STANDARD_FLAG${flag}")
    string(REPLACE "-" "_" var_name ${var_name})
    string(REPLACE "=" "_" var_name ${var_name})
    string(REPLACE ":" "_" var_name ${var_name})

    phi_check_cxx_compiler_flag(${flag} ${var_name})

    if(${var_name})
      phi_set_cache_value(NAME CMAKE_CXX14_STANDARD_COMPILE_OPTION VALUE ${flag})
      break()
    endif()
  endforeach()

  # Check extension flags
  foreach(flag IN ITEMS ${phi_known_cxx14_ext_flags})
    set(var_name "PHI_EXTENSION_FLAG${flag}")
    string(REPLACE "-" "_" var_name ${var_name})
    string(REPLACE "=" "_" var_name ${var_name})
    string(REPLACE ":" "_" var_name ${var_name})

    phi_check_cxx_compiler_flag(${flag} ${var_name})

    if(${var_name})
      phi_set_cache_value(NAME CMAKE_CXX14_EXTENSION_COMPILE_OPTION VALUE ${flag})
      break()
    endif()
  endforeach()
endif()

# C++-17 Flags were introduced in CMake 3.8
if(${CMAKE_VERSION} VERSION_LESS "3.8")
  set(phi_known_cxx17_flags "-std=c++17" "-std=c++1z" "-std:c++17" "-std:c++latest" "-Qstd=c++17")
  set(phi_known_cxx17_ext_flags "-std=gnu++17" "-std=gnu++1z")

  # Check normal flag
  foreach(flag IN ITEMS ${phi_known_cxx17_flags})
    set(var_name "PHI_STANDARD_FLAG${flag}")
    string(REPLACE "-" "_" var_name ${var_name})
    string(REPLACE "=" "_" var_name ${var_name})
    string(REPLACE ":" "_" var_name ${var_name})

    phi_check_cxx_compiler_flag(${flag} ${var_name})

    if(${var_name})
      phi_set_cache_value(NAME CMAKE_CXX17_STANDARD_COMPILE_OPTION VALUE ${flag})
      break()
    endif()
  endforeach()

  # Check extension flags
  foreach(flag IN ITEMS ${phi_known_cxx17_ext_flags})
    set(var_name "PHI_EXTENSION_FLAG${flag}")
    string(REPLACE "-" "_" var_name ${var_name})
    string(REPLACE "=" "_" var_name ${var_name})
    string(REPLACE ":" "_" var_name ${var_name})

    phi_check_cxx_compiler_flag(${flag} ${var_name})

    if(${var_name})
      phi_set_cache_value(NAME CMAKE_CXX17_EXTENSION_COMPILE_OPTION VALUE ${flag})
      break()
    endif()
  endforeach()
endif()

# C++-20 Flags were introduced in CMake 3.12
if(${CMAKE_VERSION} VERSION_LESS "3.12")
  set(phi_known_cxx20_flags "-std=c++20" "-std=c++2a" "-std:c++20" "-std:c++latest" "-Qstd=c++20")
  set(phi_known_cxx20_ext_flags "-std=gnu++20" "-std=gnu++2a")

  # Check normal flag
  foreach(flag IN ITEMS ${phi_known_cxx20_flags})
    set(var_name "PHI_STANDARD_FLAG${flag}")
    string(REPLACE "-" "_" var_name ${var_name})
    string(REPLACE "=" "_" var_name ${var_name})
    string(REPLACE ":" "_" var_name ${var_name})

    phi_check_cxx_compiler_flag(${flag} ${var_name})

    if(${var_name})
      phi_set_cache_value(NAME CMAKE_CXX20_STANDARD_COMPILE_OPTION VALUE ${flag})
      break()
    endif()
  endforeach()

  # Check extension flags
  foreach(flag IN ITEMS ${phi_known_cxx20_ext_flags})
    set(var_name "PHI_EXTENSION_FLAG${flag}")
    string(REPLACE "-" "_" var_name ${var_name})
    string(REPLACE "=" "_" var_name ${var_name})
    string(REPLACE ":" "_" var_name ${var_name})

    phi_check_cxx_compiler_flag(${flag} ${var_name})

    if(${var_name})
      phi_set_cache_value(NAME CMAKE_CXX20_EXTENSION_COMPILE_OPTION VALUE ${flag})
      break()
    endif()
  endforeach()
endif()

# Don't trust what CMake says about emscriptens C++-23 support
if(DEFINED PHI_PLATFORM_EMSCRIPTEN)
  unset(CMAKE_CXX23_STANDARD_COMPILE_OPTION)
  unset(CMAKE_CXX23_EXTENSION_COMPILE_OPTION)
endif()

# C++-23 Flags were introduced in CMake 3.20
if(${CMAKE_VERSION} VERSION_LESS "3.20" OR DEFINED PHI_PLATFORM_EMSCRIPTEN)
  set(phi_known_cxx23_flags "-std=c++23" "-std=c++2b" "-std:c++23" "-std:c++latest" "-Qstd=c++23")
  set(phi_known_cxx23_ext_flags "-std=gnu++23" "-std=gnu++2b")

  # Check normal flag
  foreach(flag IN ITEMS ${phi_known_cxx23_flags})
    set(var_name "PHI_STANDARD_FLAG${flag}")
    string(REPLACE "-" "_" var_name ${var_name})
    string(REPLACE "=" "_" var_name ${var_name})
    string(REPLACE ":" "_" var_name ${var_name})

    phi_check_cxx_compiler_flag(${flag} ${var_name})

    if(${var_name})
      phi_set_cache_value(NAME CMAKE_CXX23_STANDARD_COMPILE_OPTION VALUE ${flag})
      break()
    endif()
  endforeach()

  # Check extension flags
  foreach(flag IN ITEMS ${phi_known_cxx23_ext_flags})
    set(var_name "PHI_EXTENSION_FLAG${flag}")
    string(REPLACE "-" "_" var_name ${var_name})
    string(REPLACE "=" "_" var_name ${var_name})
    string(REPLACE ":" "_" var_name ${var_name})

    phi_check_cxx_compiler_flag(${flag} ${var_name})

    if(${var_name})
      phi_set_cache_value(NAME CMAKE_CXX23_EXTENSION_COMPILE_OPTION VALUE ${flag})
      break()
    endif()
  endforeach()
endif()

set(phi_supported_standards "23" "20" "17" "14" "11")
# set(phi_supported_standards "17" "14" "11")

# Find the latest standard
foreach(std IN ITEMS ${phi_supported_standards})
  if(DEFINED CMAKE_CXX${std}_STANDARD_COMPILE_OPTION OR CMAKE_CXX${std}_EXTENSION_COMPILE_OPTION)
    set(phi_latest_standard_version "${std}")

    if(DEFINED CMAKE_CXX${std}_EXTENSION_COMPILE_OPTION)
      set(phi_latest_standard_flag "${CMAKE_CXX${std}_EXTENSION_COMPILE_OPTION}")
    else()
      set(phi_latest_standard_flag "${CMAKE_CXX${std}_STANDARD_COMPILE_OPTION}")
    endif()

    break()
  endif()
endforeach()

if(NOT DEFINED phi_latest_standard_version OR NOT DEFINED phi_latest_standard_flag)
  # No supported standard found
  phi_warn("Failed to find latest supported standard")
endif()

phi_log("Latest standard: C++-${phi_latest_standard_version}/\"${phi_latest_standard_flag}\"")

if(${PHI_STANDARD} STREQUAL "latest")
  if(NOT DEFINED phi_latest_standard_version OR NOT DEFINED phi_latest_standard_flag)
    # No supported standard found
    phi_error("Failed to find latest supported standard")
  endif()

  set(phi_standard_version "${phi_latest_standard_version}")
  set(phi_standard_flag "${phi_latest_standard_flag}")

  phi_log("Using latest standard: C++-${phi_standard_version}/\"${phi_standard_flag}\"")

else()
  # Explicit standard version
  foreach(std IN ITEMS ${phi_supported_standards})
    if(${PHI_STANDARD} STREQUAL ${std})
      if(DEFINED CMAKE_CXX${std}_STANDARD_COMPILE_OPTION
         OR DEFINED CMAKE_CXX${std}_EXTENSION_COMPILE_OPTION)
        set(phi_standard_version ${std})

        if(DEFINED CMAKE_CXX${std}_EXTENSION_COMPILE_OPTION)
          set(phi_standard_flag "${CMAKE_CXX${std}_EXTENSION_COMPILE_OPTION}")
        else()
          set(phi_standard_flag "${CMAKE_CXX${std}_STANDARD_COMPILE_OPTION}")
        endif()

        break()
      else()
        phi_error("Explicitly requested C++-${PHI_STANDARD} but no supported flags found")
      endif()
    endif()
  endforeach()

  if(NOT DEFINED phi_standard_version OR NOT DEFINED phi_standard_flag)
    phi_error("Unsupported value for PHI_STANADRD \"${PHI_STANDARD}\"")
  endif()

  phi_log("Using explicit standard: C++-${phi_standard_version}/\"${phi_standard_flag}\"")
endif()

function(phi_set_standard_flag target)
  if(NOT TARGET ${target})
    phi_error("phi_set_standard_flag: No target \"${target}\" found")
  endif()

  # phi_trace( "Setting C++-${phi_standard_version} flag \"${phi_standard_flag}\" for target
  # \"${target}\"")

  target_compile_options(${target} PUBLIC ${phi_standard_flag})
endfunction()
