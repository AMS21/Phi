include(TestFail)

# Meta
compile_failure_test(NAME AlwaysFalse_TwoPhaseLookup SOURCE
                     "src/Meta/AlwaysFalse.two_phase_lookup.fail.cpp")

# Selftest
compile_failure_test(NAME Selftest_StaticAssert SOURCE "src/Selftest/StaticAssert.fail.cpp")

# Phi/Utility
compile_failure_test(NAME FloatingPoint_ConstructFromInt SOURCE
                     "src/Utility/FloatingPoint.int.fail.cpp")
compile_failure_test(NAME Integer_ConstructFromBool SOURCE "src/Utility/Integer.bool.fail.cpp")
compile_failure_test(NAME Integer_ConstructFromChar SOURCE "src/Utility/Integer.char.fail.cpp")
compile_failure_test(NAME Integer_ConstructFromFloat SOURCE "src/Utility/Integer.float.fail.cpp")
compile_failure_test(NAME Integer_UnsignedUnaryMinus SOURCE
                     "src/Utility/Integer.unsigned_unary_minus.fail.cpp")
