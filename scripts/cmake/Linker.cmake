option(PHI_ENABLE_USER_LINKER "Enable a specific linker if available" OFF)

include(CheckCXXCompilerFlag)

set(PHI_USER_LINKER_OPTION
    "auto"
    CACHE STRING "Linker to be used")
set(PHI_USER_LINKER_OPTION_VALUES "auto" "lld" "gold" "bfd")
set_property(CACHE PHI_USER_LINKER_OPTION PROPERTY STRINGS ${PHI_USER_LINKER_OPTION_VALUES})
list(FIND PHI_USER_LINKER_OPTION_VALUES ${PHI_USER_LINKER_OPTION} PHI_USER_LINKER_OPTION_INDEX)

if(${PHI_USER_LINKER_OPTION_INDEX} EQUAL -1)
  message(
    STATUS
      "[Phi]: Using custom linker: '${PHI_USER_LINKER_OPTION}', explicitly supported entries are ${PHI_USER_LINKER_OPTION_VALUES}"
  )
endif()

function(phi_configure_linker project_name)
  if(NOT PHI_ENABLE_USER_LINKER)
    return()
  endif()

  set(LINKER_FLAG "-fuse-ld=${PHI_USER_LINKER_OPTION}")

  target_link_options(${project_name} INTERFACE ${LINKER_FLAG})
endfunction()

if(NOT PHI_ENABLE_USER_LINKER)
  return()
endif()

if(${PHI_USER_LINKER_OPTION} STREQUAL "auto")
  foreach(linker ${PHI_USER_LINKER_OPTION_VALUES})
    if(NOT ${linker} STREQUAL "auto")
      message(STATUS "[Phi]: Testing user linker ${linker}...")

      set(LINKER_FLAG "-fuse-ld=${PHI_USER_LINKER_OPTION}")

      check_cxx_compiler_flag(${LINKER_FLAG} CXX_SUPPORTS_USER_LINKER_${linker})
      if(CXX_SUPPORTS_USER_LINKER_${linker})
        message(STATUS "[Phi]: Testing user linker ${linker} - works")
        set(PHI_USER_LINKER_OPTION
            ${linker}
            CACHE STRING "Linker to be used" FORCE)
        break()
      else()
        message(STATUS "[Phi]: Testing user linker ${linker} - not working")
      endif()
    endif()
  endforeach()

  # User linker options is still auto means we coudn't find any user linker
  if(${PHI_USER_LINKER_OPTION} STREQUAL "auto")
    message(STATUS "[Phi]: No suitable user linker was found. Disabling")
    set(PHI_ENABLE_USER_LINKER
        OFF
        CACHE BOOL "Enable a specific linker if available" FORCE)
  endif()
else()
  set(LINKER_FLAG "-fuse-ld=${PHI_USER_LINKER_OPTION}")

  check_cxx_compiler_flag(${LINKER_FLAG} CXX_SUPPORTS_USER_LINKER_${PHI_USER_LINKER_OPTION})
  if(CXX_SUPPORTS_USER_LINKER_${PHI_USER_LINKER_OPTION})
    message(STATUS "[Phi]: User linker ${PHI_USER_LINKER_OPTION} found and enabled.")
  else()
    message(
      WARNING
        "[Phi]: User linker ${PHI_USER_LINKER_OPTION} is enabled but was not found. Disabling it.")
    set(PHI_ENABLE_USER_LINKER
        OFF
        CACHE BOOL "Enable a specific linker if available" FORCE)
  endif()
endif()
