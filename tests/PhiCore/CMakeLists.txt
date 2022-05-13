project("PhiCoreTests" CXX)

if(${PHI_TEST_COMPILE_FAILURES})
  add_subdirectory("compile_failure")
endif()

if(${PHI_TEST_RUNTIME_FAILURES})
  add_subdirectory("runtime_failure")
endif()

add_subdirectory("unittests")
