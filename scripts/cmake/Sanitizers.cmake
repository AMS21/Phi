# Enable sanitizers for a specific project
function(enable_sanitizers project)
  if(PHI_COMPILER_GCC OR PHI_COMPILER_CLANG)
    set(sanitizers "")

    option(ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" FALSE)
    if(ENABLE_SANITIZER_ADDRESS)
      list(APPEND sanitizers "address")
      phi_trace("Enabled address sanitizer")
    endif()

    option(ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" FALSE)
    if(ENABLE_SANITIZER_MEMORY)
      list(APPEND sanitizers "memory")
      phi_trace("Enabled memory sanitizer")
    endif()

    option(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR "Enable undefined behavior sanitizer" FALSE)
    if(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR)
      list(APPEND sanitizers "undefined")
      phi_trace("Enabled undefined behaviour sanitizer")
    endif()

    option(ENABLE_SANITIZER_THREAD "Enable thread sanitizer" FALSE)
    if(ENABLE_SANITIZER_THREAD)
      list(APPEND sanitizers "thread")
      phi_trace("Enabled thread sanitizer")
    endif()

    option(ENABLE_SANITIZER_LEAK "Enable leak sanitizer" FALSE)
    if(ENABLE_SANITIZER_LEAK)
      list(APPEND sanitizers "leak")
      phi_trace("Enabled leak sanitizer")
    endif()

    option(ENABLE_FUZZING "Enable fuzzing flags" FALSE)
    if(ENABLE_FUZIING)
      list(APPEND sanitizers "fuzzer")
      phi_trace("Enabled fuzzer flag")
    endif()

    list(JOIN sanitizers "," list_of_sanitizers)
  endif()

  # Get target type
  get_property(
    target_type
    TARGET ${project}
    PROPERTY TYPE)

  if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
    set(visibility_scope INTERFACE)
  else()
    set(visibility_scope PRIVATE)
  endif()

  if(list_of_sanitizers)
    if(NOT "${list_of_sanitizers}" STREQUAL "")
      target_compile_options(${project} ${visibility_scope} -fsanitize=${list_of_sanitizers})
      target_link_options(${project} ${visibility_scope} -fsanitize=${list_of_sanitizers})
    endif()
  endif()
endfunction()
