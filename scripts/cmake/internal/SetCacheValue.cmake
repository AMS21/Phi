phi_include_guard()

function(phi_set_cache_value name value)
  set(${name}
      "${value}"
      CACHE INTERNAL " ")
endfunction()
