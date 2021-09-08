phi_include_guard()

include(CMakeParseArguments)

set(phi_supported_standards "23" "20" "17" "14" "11")

# Find the latest standard
if(${PHI_STANDARD} STREQUAL "latest")
  foreach(std IN ITEMS ${phi_supported_standards})
    if(DEFINED CMAKE_CXX${std}_STANDARD_COMPILE_OPTION OR CMAKE_CXX${std}_EXTENSION_COMPILE_OPTION)
      set(phi_standard_version "${std}")

      if(DEFINED CMAKE_CXX${std}_EXTENSION_COMPILE_OPTION)
        set(phi_standard_flag "${CMAKE_CXX${std}_EXTENSION_COMPILE_OPTION}")
      else()
        set(phi_standard_flag "${CMAKE_CXX${std}_STANDARD_COMPILE_OPTION}")
      endif()

      break()
    endif()
  endforeach()

  if(NOT DEFINED phi_standard_version OR NOT DEFINED phi_standard_flag)
    # No supported standard found
    phi_error("Failed to find latest supported standard")
  endif()

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

  phi_trace("Setting C++-${phi_standard_version} flag ${phi_standard_flag} for target ${target}")

  target_compile_options(${target} PUBLIC ${phi_standard_flag})
endfunction()
