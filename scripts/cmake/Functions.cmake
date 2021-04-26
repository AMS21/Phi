include_guard(GLOBAL)

include(CMakeParseArguments)

# Log a trace message
function(phi_trace text)
  message(STATUS "[Phi]: ${text}")
endfunction()

# Log a specifc information
function(phi_log text)
  message(STATUS "[Phi]: ${text}")
endfunction()

# Give a warning
function(phi_warn text)
  message(WARNING "[Phi] Warning: ${text}")
endfunction()

# Give a configuration error
function(phi_error text)
  message(FATAL_ERROR "[Phi]: Error: ${text}")
endfunction()

function(phi_set_cache_value)
  # Commandline
  cmake_parse_arguments(scv "" "NAME;VALUE" "" ${ARGN})

  # Check required arguments
  if(NOT DEFINED scv_NAME)
    phi_error("phi_set_cache_value: NAME must be defined.")
  endif()

  if(NOT DEFINED scv_VALUE)
    phi_error("phi_set_cache_value: scv_VALUE must be defined.")
  endif()

  set(${scv_NAME}
      ${scv_VALUE}
      CACHE INTERNAL "")
endfunction()
