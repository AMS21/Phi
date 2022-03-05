project("PhiTestRuntimeFailureTests" CXX)

include(TestFail)

runtime_failure_test(NAME "PhiTest_CHECK" SOURCE "src/Check.fail.cpp" LIB Phi::Test)
runtime_failure_test(NAME "PhiTest_CHECK_FALSE" SOURCE "src/CheckFalse.fail.cpp" LIB Phi::Test)
runtime_failure_test(NAME "PhiTest_REQUIRE" SOURCE "src/Require.fail.cpp" LIB Phi::Test)
runtime_failure_test(NAME "PhiTest_REQUIRE_FALSE" SOURCE "src/RequireFalse.fail.cpp" LIB Phi::Test)
