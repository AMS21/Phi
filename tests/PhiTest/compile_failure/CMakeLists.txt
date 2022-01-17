project("PhiTestCompileFailureTests" CXX)

include(TestFail)

compile_failure_test(NAME "PhiTest_CHECK_NOEXCEPT" SOURCE "src/CheckNoexcept.fail.cpp" LIB
                     Phi::Test)
compile_failure_test(NAME "PhiTest_CHECK_NOT_NOEXCEPT" SOURCE "src/CheckNotNoexcept.fail.cpp" LIB
                     Phi::Test)
compile_failure_test(NAME "PhiTest_CHECK_NOT_SAME_TYPE" SOURCE "src/CheckNotSameType.fail.cpp" LIB
                     Phi::Test)
compile_failure_test(NAME "PhiTest_CHECK_SAME_TYPE" SOURCE "src/CheckSameType.fail.cpp" LIB
                     Phi::Test)
compile_failure_test(NAME "PhiTest_STATIC_REQUIRE" SOURCE "src/StaticRequire.fail.cpp" LIB
                     Phi::Test)
compile_failure_test(NAME "PhiTest_STATIC_REQUIRE_FALSE" SOURCE "src/StaticRequireFalse.fail.cpp"
                     LIB Phi::Test)
