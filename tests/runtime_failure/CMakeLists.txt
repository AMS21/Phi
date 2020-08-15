include(TestFail)

# Selftest
runtime_failure_test(NAME "Selftest_Configuration" SOURCE "src/Selftest/Configuration.fail.cpp"
                     CONFIGURATIONS Debug)
runtime_failure_test(NAME "Selftest_Exit" SOURCE "src/Selftest/Exit.fail.cpp")
runtime_failure_test(NAME "Selftest_NonZeroReturn" SOURCE "src/Selftest/NonZeroReturn.fail.cpp")
runtime_failure_test(NAME "Selftest_Regex" SOURCE "src/Selftest/Regex.fail.cpp" REGEX
                     "TEST_STRING_WHICH_INDICATES_TEST_FAILURE")
