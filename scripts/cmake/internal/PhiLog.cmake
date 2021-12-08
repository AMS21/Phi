phi_include_guard()

include(internal/PhiMessage)

# Log a specifc information
function(phi_log text)
  phi_message(STATUS "[Phi]: ${text}")
endfunction()
