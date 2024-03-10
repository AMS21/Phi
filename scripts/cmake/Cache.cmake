phi_include_guard()

if(NOT PHI_ENABLE_CACHE)
  return()
endif()

set(PHI_CACHE_OPTIONS
    "auto"
    CACHE STRING "Compiler cache to be used")
set(PHI_CACHE_OPTIONS_VALUES "auto" "sccache" "ccache" "clcache")
set_property(CACHE PHI_CACHE_OPTIONS PROPERTY STRINGS ${PHI_CACHE_OPTIONS_VALUES})
list(FIND PHI_CACHE_OPTIONS_VALUES ${PHI_CACHE_OPTIONS} PHI_CACHE_OPTIONS_INDEX)

if(${PHI_CACHE_OPTIONS_INDEX} EQUAL -1)
  phi_log(
    "Using custom compiler cache system: '${PHI_CACHE_OPTIONS}', explicitly supported entries are ${PHI_CACHE_OPTIONS_VALUES}"
  )
endif()

if(${PHI_CACHE_OPTIONS} STREQUAL "auto")
  foreach(option ${PHI_CACHE_OPTIONS_VALUES})
    if(NOT ${option} STREQUAL "auto")
      phi_trace("Testing cache compiler ${option}...")

      find_program(PHI_CACHE_BINARY ${option})
      if(PHI_CACHE_BINARY)
        phi_trace("Testing cache compiler ${option} - works")
        set(PHI_CACHE_OPTIONS
            ${option}
            CACHE STRING "Compiler cache to be used" FORCE)
        set(CMAKE_CXX_COMPILER_LAUNCHER ${PHI_CACHE_BINARY})
        break()
      else()
        phi_trace("Testing cache compiler ${option} - not working")
      endif()
    endif()
  endforeach()

  # Cache option is still auto means we coudn't find any suitable cache compiler
  if(${PHI_CACHE_OPTIONS} STREQUAL "auto")
    phi_log("No suitable compiler cache was found. Disabling caching")
    set(PHI_ENABLE_CACHE
        OFF
        CACHE BOOL "Enable cache if available" FORCE)
  endif()
else()
  find_program(PHI_CACHE_BINARY ${PHI_CACHE_OPTIONS})
  if(PHI_CACHE_BINARY)
    phi_log("${PHI_CACHE_OPTIONS} found and enabled")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${PHI_CACHE_BINARY})
  else()
    phi_warn("${PHI_CACHE_OPTIONS} is enabled but was not found. Disabling it.")
    set(PHI_ENABLE_CACHE
        OFF
        CACHE BOOL "Enable cache if available" FORCE)
  endif()
endif()
