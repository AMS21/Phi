phi_include_guard()

include(CMakeParseArguments)
include(internal/PhiError)

function(phi_set_cache_value)
  # Commandline
  cmake_parse_arguments(scv "" "NAME;VALUE" "" ${ARGN})

  # Check required arguments
  if(NOT DEFINED scv_NAME)
    phi_error("phi_set_cache_value: NAME must be defined.")
  endif()

  if(NOT DEFINED scv_VALUE)
    phi_error("phi_set_cache_value: VALUE must be defined.")
  endif()

  set(${scv_NAME}
      ${scv_VALUE}
      CACHE INTERNAL "")
endfunction()
