phi_include_guard()

function(phi_option name help_string type default_value)
  set(${name}
      ${default_value}
      CACHE ${type} "${help_string}")
endfunction()
