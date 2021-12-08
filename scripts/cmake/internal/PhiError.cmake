phi_include_guard()

include(internal/PhiMessage)

# Give a configuration error
function(phi_error text)
  phi_message(FATAL_ERROR "[Phi]: Error: ${text}")
endfunction()
