include(TestFail)

# Selftest
runtime_failure_test(NAME "Selftest_Abort" SOURCE "src/Selftest/Abort.fail.cpp")
runtime_failure_test(NAME "Selftest_Configuration" SOURCE "src/Selftest/Configuration.fail.cpp"
                     CONFIGURATIONS Debug)
runtime_failure_test(NAME "Selftest_Exit" SOURCE "src/Selftest/Exit.fail.cpp")
runtime_failure_test(NAME "Selftest_NonZeroReturn" SOURCE "src/Selftest/NonZeroReturn.fail.cpp")
runtime_failure_test(NAME "Selftest_Regex" SOURCE "src/Selftest/Regex.fail.cpp" REGEX
                     "TEST_STRING_WHICH_INDICATES_TEST_FAILURE")
runtime_failure_test(NAME "Selftest_ReturnOne" SOURCE "src/Selftest/ReturnOne.fail.cpp")
runtime_failure_test(NAME "Selftest_Terminate" SOURCE "src/Selftest/Terminate.fail.cpp")
runtime_failure_test(NAME "Selftest_UnhandledException" SOURCE "src/Selftest/UnhandledException.fail.cpp")
