project("PhiCoreTestRuntimeFailure" CXX)

include(TestFail)

# selftest
runtime_failure_test(NAME "selftest_abort" SOURCE "src/selftest/abort.fail.cpp")
runtime_failure_test(NAME "selftest_configuration" SOURCE "src/selftest/configuration.fail.cpp")
runtime_failure_test(NAME "selftest_exit" SOURCE "src/selftest/exit.fail.cpp")
runtime_failure_test(NAME "selftest_regex" SOURCE "src/selftest/regex.fail.cpp" REGEX
                     "TEST_STRING_WHICH_INDICATES_TEST_FAILURE")
runtime_failure_test(NAME "selftest_return_one" SOURCE "src/selftest/return_one.fail.cpp")
runtime_failure_test(NAME "selftest_terminate" SOURCE "src/selftest/terminate.fail.cpp")
runtime_failure_test(NAME "selftest_unhandled_exception" SOURCE
                     "src/selftest/unhandled_exception.fail.cpp")

# algorithm

# at
runtime_failure_test(NAME "algorithm_at_array_out_of_bounds" SOURCE
                     "src/algorithm/at/array_out_of_bounds.fail.cpp")
runtime_failure_test(NAME "algorithm_at_carray_out_of_bounds" SOURCE
                     "src/algorithm/at/carray_out_of_bounds.fail.cpp")
runtime_failure_test(NAME "algorithm_at_initializer_list_out_of_bounds" SOURCE
                     "src/algorithm/at/initializer_list_out_of_bounds.fail.cpp")

# string_compare_unsafe
runtime_failure_test(NAME "algorithm_string_compare_unsafe_nullptr_lhs" SOURCE
                     "src/algorithm/string_compare_unsafe/nullptr_lhs.fail.cpp")
runtime_failure_test(NAME "algorithm_string_compare_unsafe_nullptr_rhs" SOURCE
                     "src/algorithm/string_compare_unsafe/nullptr_rhs.fail.cpp")
runtime_failure_test(NAME "algorithm_string_compare_unsafe_nullptr_both" SOURCE
                     "src/algorithm/string_compare_unsafe/nullptr_both.fail.cpp")
runtime_failure_test(NAME "algorithm_string_compare_unsafe_nullptr_lhs_with_size" SOURCE
                     "src/algorithm/string_compare_unsafe/nullptr_lhs_with_size.fail.cpp")
runtime_failure_test(NAME "algorithm_string_compare_unsafe_nullptr_rhs_with_size" SOURCE
                     "src/algorithm/string_compare_unsafe/nullptr_rhs_with_size.fail.cpp")
runtime_failure_test(NAME "algorithm_string_compare_unsafe_nullptr_both_with_size" SOURCE
                     "src/algorithm/string_compare_unsafe/nullptr_both_with_size.fail.cpp")

# string_length_unsafe
runtime_failure_test(NAME "algorithm_string_length_unsafe_nullptr" SOURCE
                     "src/algorithm/string_length_unsafe/nullptr.fail.cpp")
runtime_failure_test(NAME "algorithm_string_length_unsafe_nullptr_with_size" SOURCE
                     "src/algorithm/string_length_unsafe/nullptr_with_size.fail.cpp")

# container array
runtime_failure_test(NAME "container_array_AtOutOfBounds" SOURCE
                     "src/container/array/at_oob.fail.cpp")
runtime_failure_test(NAME "container_array_ConstAtOutOfBounds" SOURCE
                     "src/container/array/const_at_oob.fail.cpp")
runtime_failure_test(NAME "container_array_ZeroAtOutOfBounds" SOURCE
                     "src/container/array/zero_at_oob.fail.cpp")
runtime_failure_test(NAME "container_array_ZeroCountAtOutOfBounds" SOURCE
                     "src/container/array/zero_const_at_oob.fail.cpp")

runtime_failure_test(NAME "container_array_SubscriptOutOfBounds" SOURCE
                     "src/container/array/subscript_oob.fail.cpp")
runtime_failure_test(NAME "container_array_ConstSubscriptOutOfBounds" SOURCE
                     "src/container/array/const_subscript_oob.fail.cpp")
runtime_failure_test(NAME "container_array_ZeroSubscriptOutOfBounds" SOURCE
                     "src/container/array/zero_subscript_oob.fail.cpp")
runtime_failure_test(NAME "container_array_ZeroConstSubscriptOutOfBounds" SOURCE
                     "src/container/array/zero_const_subscript_oob.fail.cpp")

runtime_failure_test(NAME "container_array_FrontOutOfBounds" SOURCE
                     "src/container/array/front_oob.fail.cpp")
runtime_failure_test(NAME "container_array_ConstFrontOutOfBounds" SOURCE
                     "src/container/array/const_front_oob.fail.cpp")

runtime_failure_test(NAME "container_array_BackOutOfBounds" SOURCE
                     "src/container/array/back_oob.fail.cpp")
runtime_failure_test(NAME "container_array_ConstBackOutOfBounds" SOURCE
                     "src/container/array/const_back_oob.fail.cpp")

runtime_failure_test(NAME "container_array_ZeroMax" SOURCE "src/container/array/zero_max.fail.cpp")
runtime_failure_test(NAME "container_array_ZeroMin" SOURCE "src/container/array/zero_min.fail.cpp")
runtime_failure_test(NAME "container_array_ZeroMaxIndex" SOURCE
                     "src/container/array/zero_max_index.fail.cpp")
runtime_failure_test(NAME "container_array_ZeroMinIndex" SOURCE
                     "src/container/array/zero_min_index.fail.cpp")

# string_view
runtime_failure_test(NAME "container_string_view_AtOnEmpty" SOURCE
                     "src/container/string_view/empty_at.fail.cpp")
runtime_failure_test(NAME "container_string_view_BackOnEmpty" SOURCE
                     "src/container/string_view/empty_back.fail.cpp")
runtime_failure_test(NAME "container_string_view_FrontOnEmpty" SOURCE
                     "src/container/string_view/empty_front.fail.cpp")
runtime_failure_test(NAME "container_string_view_InvalidElementAccess" SOURCE
                     "src/container/string_view/invalid_element.fail.cpp")
runtime_failure_test(NAME "container_string_view_RemovePrefix" SOURCE
                     "src/container/string_view/remove_prefix.fail.cpp")
runtime_failure_test(NAME "container_string_view_RemoveSuffix" SOURCE
                     "src/container/string_view/remove_suffix.fail.cpp")
runtime_failure_test(NAME "container_string_view_Copy" SOURCE
                     "src/container/string_view/copy.fail.cpp")
runtime_failure_test(NAME "container_string_view_Substr" SOURCE
                     "src/container/string_view/substr.fail.cpp")

# core assert
runtime_failure_test(NAME "core_assert_with_args" SOURCE
                     "src/core/assert/assert_with_args.fail.cpp")
runtime_failure_test(NAME "core_assert_with_args_regex" SOURCE
                     "src/core/assert/assert_with_args.fail.cpp" REGEX "ASSERTION VIOLATION")
runtime_failure_test(NAME "core_assert_not_reached" SOURCE
                     "src/core/assert/assert_not_reached.fail.cpp")

runtime_failure_test(NAME "core_release_assert_with_args" SOURCE
                     "src/core/assert/release_assert_with_args.fail.cpp")
runtime_failure_test(
  NAME "core_release_assert_with_args_regex" SOURCE
  "src/core/assert/release_assert_with_args.fail.cpp" REGEX "ASSERTION VIOLATION")
runtime_failure_test(NAME "release_assert_not_reached" SOURCE
                     "src/core/assert/release_assert_not_reached.fail.cpp")

# flat_ptr
runtime_failure_test(NAME "core_flat_ptr_release_from_nullptr" SOURCE
                     "src/core/flat_ptr/release_from_nullptr.fail.cpp")
runtime_failure_test(NAME "core_flat_ptr_not_null_assign_nullptr" SOURCE
                     "src/core/flat_ptr/not_null_assign_nullptr.fail.cpp")

# narrow_cast
runtime_failure_test(NAME "core_narrow_cast_invalid" SOURCE "src/core/narrow_cast/invalid.fail.cpp")
runtime_failure_test(NAME "core_narrow_cast_invalid2" SOURCE
                     "src/core/narrow_cast/invalid2.fail.cpp")

# observer_ptr
runtime_failure_test(NAME "core_observer_ptr_not_null_assign_nullptr" SOURCE
                     "src/core/observer_ptr/not_null_assign_nullptr.fail.cpp")
runtime_failure_test(NAME "core_observer_ptr_release_from_nullptr" SOURCE
                     "src/core/observer_ptr/release_from_null.fail.cpp")
runtime_failure_test(NAME "core_observer_ptr_dereference_nullptr_operator_star" SOURCE
                     "src/core/observer_ptr/deref_null.fail.cpp")
runtime_failure_test(NAME "core_observer_ptr_dereference_nullptr_operator_arrow" SOURCE
                     "src/core/observer_ptr/deref_null2.fail.cpp")

# scope_ptr
runtime_failure_test(NAME "core_scope_ptr_dereference_nullptr_operator_star" SOURCE
                     "src/core/scope_ptr/deref_null.fail.cpp")
runtime_failure_test(NAME "core_scope_ptr_dereference_nullptr_operator_arrow" SOURCE
                     "src/core/scope_ptr/deref_null2.fail.cpp")
runtime_failure_test(NAME "core_scope_ptr_release_from_nullptr" SOURCE
                     "src/core/scope_ptr/release_from_nullptr.fail.cpp")
runtime_failure_test(NAME "core_scope_ptr_not_null_assign_nullptr" SOURCE
                     "src/core/scope_ptr/not_null_assign_nullptr.fail.cpp")
runtime_failure_test(NAME "core_scope_ptr_ConstructWithNullptr" SOURCE
                     "src/core/scope_ptr/not_null_construct_nullptr.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_AccessAfterLeakPtrCall" SOURCE
                     "src/core/scope_ptr/not_null_get_after_leak.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_AccessAfterMoved" SOURCE
                     "src/core/scope_ptr/not_null_get_after_move.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_ResetNullptr" SOURCE
                     "src/core/scope_ptr/not_null_reset_nullptr.fail.cpp")

# text binary_digit_value
runtime_failure_test(NAME "text_binary_digit_value_OutOfBounds" SOURCE
                     "src/text/binary_digit_value/out_of_bounds.fail.cpp")
runtime_failure_test(NAME "text_binary_digit_value_OutOfBounds2" SOURCE
                     "src/text/binary_digit_value/out_of_bounds2.fail.cpp")

# digit_value
runtime_failure_test(NAME "text_digit_value_OutOfBounds" SOURCE
                     "src/text/digit_value/out_of_bounds.fail.cpp")

# hex_digit_value
runtime_failure_test(NAME "text_hex_digit_value_OutOfBounds" SOURCE
                     "src/text/hex_digit_value/out_of_bounds.fail.cpp")

# octal_digit_value
runtime_failure_test(NAME "text_octal_digit_value_OutOfBounds" SOURCE
                     "src/text/octal_digit_value/out_of_bounds.fail.cpp")
runtime_failure_test(NAME "text_octal_digit_value_OutOfBounds2" SOURCE
                     "src/text/octal_digit_value/out_of_bounds2.fail.cpp")
