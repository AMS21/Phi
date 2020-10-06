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

# Utilitay
runtime_failure_test(NAME "Utility_AssertNoArgs" SOURCE "src/Utility/Assert.NoArgs.fail.cpp")
runtime_failure_test(NAME "Utility_AssertNoArgsRegex" SOURCE "src/Utility/Assert.NoArgs.fail.cpp" REGEX "ASSERTION VIOLATION")
runtime_failure_test(NAME "Utility_AssertWithArgs" SOURCE "src/Utility/Assert.WithArgs.fail.cpp")
runtime_failure_test(NAME "Utility_AssertWithArgsRegex" SOURCE "src/Utility/Assert.WithArgs.fail.cpp" REGEX "[ASSERT FAILED]")
runtime_failure_test(NAME "Utility_DbgAssertNoArgs" SOURCE "src/Utility/DbgAssert.NoArgs.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Utility_DbgAssertNoArgsRegex" SOURCE "src/Utility/DbgAssert.NoArgs.fail.cpp" REGEX "ASSERTION VIOLATION" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Utility_DbgAssertWithArgsRegex" SOURCE "src/Utility/DbgAssert.WithArgs.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Utility_DbgAssertWithArgs" SOURCE "src/Utility/DbgAssert.WithArgs.fail.cpp" REGEX "[DBG ASSERT FAILED]" CONFIGURATIONS Debug)
