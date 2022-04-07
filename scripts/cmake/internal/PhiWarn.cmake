phi_include_guard()

include(internal/PhiMessage)

# Give a warning
function(phi_warn text)
  phi_message(WARNING "[Phi] Warning: ${text}")
endfunction()
