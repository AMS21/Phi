phi_include_guard()

include(internal/Message)

# Log a trace message
function(phi_trace text)
  if(PHI_VERBOSE_CMAKE)
    phi_message(STATUS "[Phi]: ${text}")
  endif()
endfunction()
