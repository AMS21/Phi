phi_include_guard()

include(internal/Message)

# Log a trace message
function(phi_trace text)
  if(${PHI_MAIN_PROJECT})
    phi_message(STATUS "[Phi]: ${text}")
  endif()
endfunction()
