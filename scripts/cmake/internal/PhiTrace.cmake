phi_include_guard()

include(internal/PhiMessage)

# Log a trace message
function(phi_trace text)
  phi_message(STATUS "[Phi]: ${text}")
endfunction()
