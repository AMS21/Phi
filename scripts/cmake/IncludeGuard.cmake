if(DEFINED "__PHI_INCLUDE_GUARD_INCLUDE_GUARD")
  return()
endif()
set("__PHI_INCLUDE_GUARD_INCLUDE_GUARD" TRUE)

macro(phi_include_guard)
  if(${CMAKE_VERSION} VERSION_GREATER "3.9")
    include_guard(GLOBAL)
  else()
    # Workaround for older CMake versions
    if(DEFINED "__PHI_INCLUDE_GUARD_${CMAKE_CURRENT_LIST_FILE}")
      return()
    endif()

    set("__PHI_INCLUDE_GUARD_${CMAKE_CURRENT_LIST_FILE}" TRUE)
  endif()
endmacro()
