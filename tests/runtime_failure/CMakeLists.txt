include(TestFail)

# Selftest
runtime_failure_test(NAME "Selftest_Abort" SOURCE "src/Selftest/Abort.fail.cpp")
runtime_failure_test(NAME "Selftest_Configuration" SOURCE "src/Selftest/Configuration.fail.cpp"
                     CONFIGURATIONS Debug)
runtime_failure_test(NAME "Selftest_Exit" SOURCE "src/Selftest/Exit.fail.cpp")
runtime_failure_test(NAME "Selftest_Regex" SOURCE "src/Selftest/Regex.fail.cpp" REGEX
                     "TEST_STRING_WHICH_INDICATES_TEST_FAILURE")
runtime_failure_test(NAME "Selftest_ReturnOne" SOURCE "src/Selftest/ReturnOne.fail.cpp")
runtime_failure_test(NAME "Selftest_Terminate" SOURCE "src/Selftest/Terminate.fail.cpp")
runtime_failure_test(NAME "Selftest_UnhandledException" SOURCE
                     "src/Selftest/UnhandledException.fail.cpp")

# Core
runtime_failure_test(NAME "Core_AssertNoArgs" SOURCE "src/Core/Assert.NoArgs.fail.cpp")
runtime_failure_test(NAME "Core_AssertNoArgsRegex" SOURCE "src/Core/Assert.NoArgs.fail.cpp" REGEX
                     "ASSERTION VIOLATION")
runtime_failure_test(NAME "Core_AssertWithArgs" SOURCE "src/Core/Assert.WithArgs.fail.cpp")
runtime_failure_test(NAME "Core_AssertWithArgsRegex" SOURCE "src/Core/Assert.WithArgs.fail.cpp"
                     REGEX "[ASSERT FAILED]")
runtime_failure_test(NAME "Core_DbgAssertNoArgs" SOURCE "src/Core/DbgAssert.NoArgs.fail.cpp"
                     CONFIGURATIONS Debug)
runtime_failure_test(
  NAME
  "Core_DbgAssertNoArgsRegex"
  SOURCE
  "src/Core/DbgAssert.NoArgs.fail.cpp"
  REGEX
  "ASSERTION VIOLATION"
  CONFIGURATIONS
  Debug)
runtime_failure_test(NAME "Core_DbgAssertWithArgsRegex" SOURCE
                     "src/Core/DbgAssert.WithArgs.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(
  NAME
  "Core_DbgAssertWithArgs"
  SOURCE
  "src/Core/DbgAssert.WithArgs.fail.cpp"
  REGEX
  "[DBG ASSERT FAILED]"
  CONFIGURATIONS
  Debug)
runtime_failure_test(NAME "Core_AssertNotReached" SOURCE "src/Core/AssertNotReached.fail.cpp")
runtime_failure_test(NAME "Core_DbgAssertNotReached" SOURCE "src/Core/DbgAssertNotReached.fail.cpp"
                     CONFIGURATIONS Debug)
runtime_failure_test(NAME "Core_FlatPtr_ReleaseFromNullptr" SOURCE "src/Core/FlatPtr.release_from_nullptr.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Core_NotNullFlatPtr_AssignNullptr" SOURCE "src/Core/NotNullFlatPtr.assign_nullptr.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Core_NotNullObserverPtr_AssignNullptr" SOURCE
                     "src/Core/NotNullObserverPtr.assign_nullptr.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Core_ObserverPtr_ReleaseFromNullptr" SOURCE
                     "src/Core/ObserverPtr.release_from_null.fail.cpp" CONFIGURATIONS DEBUG)
runtime_failure_test(NAME "Core_ObserverPtr_DereferenceNullptr_operator_star" SOURCE
                     "src/Core/ObserverPtr.deref_null.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Core_ObserverPtr_DereferenceNullptr_operator_arrow" SOURCE
                     "src/Core/ObserverPtr.deref_null2.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Core_ScopePtr_DereferenceNullptrOperatorStar" SOURCE
                     "src/Core/ScopePtr.deref_null.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Core_ScopePtr_DereferenceNullptrOperatorArrow" SOURCE
                     "src/Core/ScopePtr.deref_null2.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Core_ScopePtr_ReleaseFromNullptr" SOURCE
                     "src/Core/ScopePtr.release_from_nullptr.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Core_NotNullScopePtr_AssignNullptr" SOURCE
                     "src/Core/NotNullScopePtr.assign_nullptr.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Core_NotNullScopePtr_ConstructWithNullptr" SOURCE
                     "src/Core/NotNullScopePtr.construct_nullptr.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Core_NotNullScopePtr_AccessAfterLeakPtrCall" SOURCE
                     "src/Core/NotNullScopePtr.get_after_leak.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Core_NotNullScopePtr_AccessAfterMoved" SOURCE
                     "src/Core/NotNullScopePtr.get_after_move.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Core_NotNullScopePtr_ResetNullptr" SOURCE
                     "src/Core/NotNullScopePtr.reset_nullptr.fail.cpp" CONFIGURATIONS Debug)
