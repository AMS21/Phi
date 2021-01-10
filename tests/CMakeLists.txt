if(${PHI_ENABLE_FAILURE_TESTS})
  add_subdirectory(compile_failure)
  add_subdirectory(runtime_failure)
endif()

add_subdirectory(integration)
add_subdirectory(unittests)

# Configure valgrind mode
if(${PHI_TEST_WITH_VALGRIND})
  add_custom_target(
    test_valgrind ALL
    DEPENDS Phi_Unittests Phi_ConstexprUnittests Phi_UnittestsDynamic Phi_ConstexprUnittestsDynamic
    COMMAND ${CMAKE_CTEST_COMMAND} --force-new-ctest-process --test-action memcheck --parallel
            ${PHI_PROCESSOR_COUNT}
    COMMAND cat "${CMAKE_BINARY_DIR}/Testing/Temporary/MemoryChecker.*.log"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
endif()
