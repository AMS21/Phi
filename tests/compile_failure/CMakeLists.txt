include(TestFail)

# Phi/Core
compile_failure_test(NAME "Core_FloatingPoint_ConstructFromInt" SOURCE
                     "src/Core/FloatingPoint.int.fail.cpp")
compile_failure_test(NAME "Core_Integer_ConstructFromBool" SOURCE "src/Core/Integer.bool.fail.cpp")
compile_failure_test(NAME "Core_Integer_ConstructFromChar" SOURCE "src/Core/Integer.char.fail.cpp")
compile_failure_test(NAME "Core_Integer_ConstructFromFloat" SOURCE
                     "src/Core/Integer.float.fail.cpp")
compile_failure_test(NAME "Core_Integer_UnsignedUnaryMinus" SOURCE
                     "src/Core/Integer.unsigned_unary_minus.fail.cpp")
compile_failure_test(NAME "Core_NotNull_DefaultConstructor" SOURCE
                     "src/Core/NotNull.defaulted.fail.cpp")
compile_failure_test(NAME "Core_NotNull_NonPointer" SOURCE "src/Core/NotNull.non_pointer.fail.cpp")
compile_failure_test(NAME "Core_NotNull_ConstructFromNullptr" SOURCE
                     "src/Core/NotNull.nullptr.fail.cpp")
compile_failure_test(NAME "Core_NotNull_ConstructFromZero" SOURCE "src/Core/NotNull.zero.fail.cpp")
# compile_failure_test(NAME "Core_NotNullObserverPtr_DefaultConstructor" SOURCE
# "src/Core/NotNullObserverPtr.default.fail.cpp") compile_failure_test(NAME
# "Core_NotNullObserverPtr_ConstructFromNullptr" SOURCE
# "src/Core/NotNullObserverPtr.construct_nullptr.fail.cpp"); compile_failure_test(NAME
# "Core_NotNUllObserverPtr_AssignNullptr" SOURCE
# "src/Core/NotNullObserverPtr.assign_nullptr.fail.cpp")

# Meta
compile_failure_test(NAME "Meta_AlwaysFalse_TwoPhaseLookup" SOURCE
                     "src/Meta/AlwaysFalse.two_phase_lookup.fail.cpp")

# Selftest
compile_failure_test(NAME "Selftest_StaticAssert" SOURCE "src/Selftest/StaticAssert.fail.cpp")
