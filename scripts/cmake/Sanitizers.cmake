# Enable sanitizers for a specific project
function(enable_sanitizers project)
  if(PHI_COMPILER_GCC OR PHI_COMPILER_CLANG)
    option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

    if(ENABLE_COVERAGE)
      target_compile_options(project_options INTERFACE --coverage -O0 -g)
      target_link_libraries(project_options INTERFACE --coverage)

      if(PHI_COMPILER_CLANG)
        target_compile_options(project_options INTERFACE -fprofile-instr-generate -fcoverage-mapping)
        target_link_libraries(project_options INTERFACE -fprofile-instr-generate -fcoverage-mapping)
      endif()
    endif()

    set(sanitizers "")

    option(ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" FALSE)
    if(ENABLE_SANITIZER_ADDRESS)
      list(APPEND sanitizers "address")
    endif()

    option(ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" FALSE)
    if(ENABLE_SANITIZER_MEMORY)
      list(APPEND sanitizers "memory")
    endif()

    option(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR "Enable undefined behavior sanitizer" FALSE)
    if(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR)
      list(APPEND sanitizers "undefined")
    endif()

    option(ENABLE_SANITIZER_THREAD "Enable thread sanitizer" FALSE)
    if(ENABLE_SANITIZER_THREAD)
      list(APPEND sanitizers "thread")
    endif()

    option(ENABLE_SANITIZER_LEAK "Enable leak sanitizer" FALSE)
    if(ENABLE_SANITIZER_LEAK)
      list(APPEND sanitizers "leak")
    endif()

    option(ENABLE_FUZZING "Enable fuzzing flags" FALSE)
    if(ENABLE_FUZIING)
      list(APPEND sanitizers "fuzzer")
    endif()

    list(JOIN sanitizers "," list_of_sanitizers)

  endif()

  if(list_of_sanitizers)
    if(NOT "${list_of_sanitizers}" STREQUAL "")
      target_compile_options(${project} INTERFACE -fsanitize=${list_of_sanitizers})
      target_link_libraries(${project} INTERFACE -fsanitize=${list_of_sanitizers})
    endif()
  endif()

endfunction()
