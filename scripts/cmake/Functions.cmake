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
