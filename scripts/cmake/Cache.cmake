option(ENABLE_CACHE "Enable cache if available" ON)
if(NOT ENABLE_CACHE)
  return()
endif()

set(CACHE_OPTION
    "auto"
    CACHE STRING "Compiler cache to be used")
set(CACHE_OPTION_VALUES "auto" "ccache" "sccache")
set_property(CACHE CACHE_OPTION PROPERTY STRINGS ${CACHE_OPTION_VALUES})
list(FIND CACHE_OPTION_VALUES ${CACHE_OPTION} CACHE_OPTION_INDEX)

if(${CACHE_OPTION_INDEX} EQUAL -1)
  message(STATUS "Using custom compiler cache system: '${CACHE_OPTION}', "
                 "explicitly supported entries are ${CACHE_OPTION_VALUES}")
endif()

if(${CACHE_OPTION} STREQUAL "auto")
  foreach(option ${CACHE_OPTION_VALUES})
    if(NOT ${option} STREQUAL "auto")
      message(STATUS "Testing cache compiler ${option}...")

      find_program(CACHE_BINARY ${option})
      if(CACHE_BINARY)
        message(STATUS "Testing cache compiler ${option} - works")
        set(CACHE_OPTION
            ${option}
            CACHE STRING "Compiler cache to be used" FORCE)
        set(CMAKE_CXX_COMPILER_LAUNCHER ${CACHE_BINARY})
        break()
      else()
        message(STATUS "Testing cache compiler ${option} - not working")
      endif()
    endif()
  endforeach()

  # Cache option is still auto means we coudn't find any suitable cache compiler
  if(${CACHE_OPTION} STREQUAL "auto")
    message(STATUS "No suitable compiler cache was found. Disabling caching")
    set(ENABLE_CACHE
        OFF
        CACHE BOOL "Enable cache if available" FORCE)
  endif()
else()
  find_program(CACHE_BINARY ${CACHE_OPTION})
  if(CACHE_BINARY)
    message(STATUS "${CACHE_OPTION} found and enabled")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CACHE_BINARY})
  else()
    message(WARNING "${CACHE_OPTION} is enabled but was not found. Disabling it.")
    set(ENABLE_CACHE
        OFF
        CACHE BOOL "Enable cache if available" FORCE)
  endif()
endif()
