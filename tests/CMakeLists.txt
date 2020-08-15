if(${PHI_ENABLE_FAILURE_TESTS})
  add_subdirectory(compile_failure)
  add_subdirectory(runtime_failure)
endif()

add_subdirectory(integration)
add_subdirectory(unittests)
