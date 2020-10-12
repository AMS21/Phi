include(TestFail)

# Phi/Core
compile_failure_test(NAME FloatingPoint_ConstructFromInt SOURCE
                     "src/Core/FloatingPoint.int.fail.cpp")
compile_failure_test(NAME Integer_ConstructFromBool SOURCE "src/Core/Integer.bool.fail.cpp")
compile_failure_test(NAME Integer_ConstructFromChar SOURCE "src/Core/Integer.char.fail.cpp")
compile_failure_test(NAME Integer_ConstructFromFloat SOURCE "src/Core/Integer.float.fail.cpp")
compile_failure_test(NAME Integer_UnsignedUnaryMinus SOURCE
                     "src/Core/Integer.unsigned_unary_minus.fail.cpp")

# Meta
compile_failure_test(NAME AlwaysFalse_TwoPhaseLookup SOURCE
                     "src/Meta/AlwaysFalse.two_phase_lookup.fail.cpp")

# Selftest
compile_failure_test(NAME Selftest_StaticAssert SOURCE "src/Selftest/StaticAssert.fail.cpp")
