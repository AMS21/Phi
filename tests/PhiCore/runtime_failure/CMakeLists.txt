project("PhiCoreTestRuntimeFailure" CXX)

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

# Algorithm
runtime_failure_test(NAME "Algorithm_StringLengthNullptr" SOURCE "src/Algorithm/StringLength.nullptr.fail.cpp" CONFIGURATIONS Debug)

# Container
runtime_failure_test(NAME "Container_StringViewConstructWithNullptr" SOURCE "src/Container/StringView.construct_nullptr.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Container_StringViewConstructWithNullptrAndSize" SOURCE "src/Container/StringView.construct_nullptr2.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Container_StringViewConstructWithZeroSize" SOURCE "src/Container/StringView.construct_zero_size.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Container_StringViewTooShortString" SOURCE "src/Container/StringView.short_string.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Container_StringViewAtOnEmpty" SOURCE "src/Container/StringView.empty_at.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Container_StringViewBackOnEmpty" SOURCE "src/Container/StringView.empty_back.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Container_StringViewFrontOnEmpty" SOURCE "src/Container/StringView.empty_front.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Container_StringViewInvalidElementAccess" SOURCE "src/Container/StringView.invalid_element.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Container_StringViewRemovePrefix" SOURCE "src/Container/StringView.remove_prefix.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Container_StringViewRemoveSuffix" SOURCE "src/Container/StringView.remove_suffix.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Container_StringViewCopy" SOURCE "src/Container/StringView.copy.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Container_StringViewSubstr" SOURCE "src/Container/StringView.substr.fail.cpp" CONFIGURATIONS Debug)

# Core
runtime_failure_test(NAME "Core_AssertWithArgs" SOURCE "src/Core/Assert.WithArgs.fail.cpp")
runtime_failure_test(NAME "Core_AssertWithArgsRegex" SOURCE "src/Core/Assert.WithArgs.fail.cpp"
                     REGEX "[ASSERT FAILED]")
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
runtime_failure_test(NAME "Core_ObserverPtr_DereferenceNullptrOperatorStar" SOURCE
                     "src/Core/ObserverPtr.deref_null.fail.cpp" CONFIGURATIONS Debug)
runtime_failure_test(NAME "Core_ObserverPtr_DereferenceNullptrOperatorArrow" SOURCE
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
