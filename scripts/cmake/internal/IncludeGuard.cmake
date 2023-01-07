if(DEFINED "__PHI_INCLUDE_GUARD_INCLUDE_GUARD__")
  return()
endif()
set("__PHI_INCLUDE_GUARD_INCLUDE_GUARD__" TRUE)

macro(phi_include_guard)
  if(${CMAKE_VERSION} VERSION_GREATER "3.9")
    include_guard(GLOBAL)
  else()
    # Workaround for older CMake versions
    if(DEFINED "__PHI_INCLUDE_GUARD_${CMAKE_CURRENT_LIST_FILE}__")
      return()
    endif()

    set("__PHI_INCLUDE_GUARD_${CMAKE_CURRENT_LIST_FILE}__" TRUE)
  endif()
endmacro()
