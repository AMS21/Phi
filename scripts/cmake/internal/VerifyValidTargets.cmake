phi_include_guard()

include(internal/PhiError)

function(phi_verify_valid_targets list_of_targets)
  foreach(target ${list_of_targets})
    if(NOT TARGET "${target}")
      phi_error("The target \"${target}\" doesn't seem to be valid")
    endif()
  endforeach(target)
endfunction()
