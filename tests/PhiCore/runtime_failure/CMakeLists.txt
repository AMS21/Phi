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

# algorithm string_length
runtime_failure_test(NAME "algorithm_string_length_nullptr" SOURCE
                     "src/algorithm/string_length/nullptr.fail.cpp")

# container string_view
runtime_failure_test(NAME "container_string_view_ConstructWithNullptr" SOURCE
                     "src/container/string_view/construct_nullptr.fail.cpp")
runtime_failure_test(NAME "container_string_view_ConstructWithNullptrAndSize" SOURCE
                     "src/container/string_view/construct_nullptr2.fail.cpp")
runtime_failure_test(NAME "container_string_view_ConstructWithZeroSize" SOURCE
                     "src/container/string_view/construct_zero_size.fail.cpp")
runtime_failure_test(NAME "container_string_view_TooShortString" SOURCE
                     "src/container/string_view/short_string.fail.cpp")
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
