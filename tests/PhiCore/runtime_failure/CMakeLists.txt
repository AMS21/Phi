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
runtime_failure_test(NAME "algorithm_at_vector_out_of_bounds" SOURCE
                     "src/algorithm/at/vector_out_of_bounds.fail.cpp")

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

# string_equals
runtime_failure_test(NAME "algorithm_string_equals_zero_count" SOURCE
                     "src/algorithm/string_equals/zero_count.fail.cpp")

# string_length_unsafe
runtime_failure_test(NAME "algorithm_string_length_unsafe_nullptr" SOURCE
                     "src/algorithm/string_length_unsafe/nullptr.fail.cpp")
runtime_failure_test(NAME "algorithm_string_length_unsafe_nullptr_with_size" SOURCE
                     "src/algorithm/string_length_unsafe/nullptr_with_size.fail.cpp")

# container

# array
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
runtime_failure_test(NAME "container_string_view_substring_view_iterator" SOURCE
                     "src/container/string_view/substring_view_iterator.fail.cpp")
runtime_failure_test(NAME "container_string_view_substring_view_iterator2" SOURCE
                     "src/container/string_view/substring_view_iterator2.fail.cpp")
runtime_failure_test(NAME "container_string_view_substring_view_iterator3" SOURCE
                     "src/container/string_view/substring_view_iterator3.fail.cpp")
runtime_failure_test(NAME "container_string_view_substring_view" SOURCE
                     "src/container/string_view/substring_view.fail.cpp")
runtime_failure_test(NAME "container_string_view_substring_view2" SOURCE
                     "src/container/string_view/substring_view2.fail.cpp")

# core

# assert
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

# integer
runtime_failure_test(NAME "core_integer_divide_equals" SOURCE
                     "src/core/integer/divide_equals.fail.cpp")
runtime_failure_test(NAME "core_integer_divide" SOURCE "src/core/integer/divide.fail.cpp")
runtime_failure_test(NAME "core_integer_minus_equals" SOURCE
                     "src/core/integer/minus_equals.fail.cpp")
runtime_failure_test(NAME "core_integer_minus" SOURCE "src/core/integer/minus.fail.cpp")
runtime_failure_test(NAME "core_integer_modulo_equals" SOURCE
                     "src/core/integer/modulo_equals.fail.cpp")
runtime_failure_test(NAME "core_integer_modulo" SOURCE "src/core/integer/modulo.fail.cpp")
runtime_failure_test(NAME "core_integer_plus_equals" SOURCE "src/core/integer/plus_equals.fail.cpp")
runtime_failure_test(NAME "core_integer_plus" SOURCE "src/core/integer/plus.fail.cpp")
runtime_failure_test(NAME "core_integer_post_decrement" SOURCE
                     "src/core/integer/post_decrement.fail.cpp")
runtime_failure_test(NAME "core_integer_post_increment" SOURCE
                     "src/core/integer/post_increment.fail.cpp")
runtime_failure_test(NAME "core_integer_pre_decrement" SOURCE
                     "src/core/integer/pre_decrement.fail.cpp")
runtime_failure_test(NAME "core_integer_pre_increment" SOURCE
                     "src/core/integer/pre_increment.fail.cpp")
runtime_failure_test(NAME "core_integer_time_equals" SOURCE
                     "src/core/integer/times_equals.fail.cpp")
runtime_failure_test(NAME "core_integer_time" SOURCE "src/core/integer/times.fail.cpp")
runtime_failure_test(NAME "core_integer_unary_minus_overflow" SOURCE
                     "src/core/integer/unary_minus_overflow.fail.cpp")

# narrow_cast
runtime_failure_test(NAME "core_narrow_cast_invalid" SOURCE "src/core/narrow_cast/invalid.fail.cpp")
runtime_failure_test(NAME "core_narrow_cast_invalid2" SOURCE
                     "src/core/narrow_cast/invalid2.fail.cpp")
runtime_failure_test(NAME "core_narrow_cast_invalid3" SOURCE
                     "src/core/narrow_cast/invalid3.fail.cpp")

# not_null_flat_ptr
runtime_failure_test(NAME "core_not_null_flat_ptr_assign_nullptr" SOURCE
                     "src/core/not_null_flat_ptr/assign_nullptr.fail.cpp")
runtime_failure_test(NAME "core_not_null_flat_ptr_construct_nullptr" SOURCE
                     "src/core/not_null_flat_ptr/construct_nullptr.fail.cpp")
runtime_failure_test(NAME "core_not_null_flat_ptr_get_const" SOURCE
                     "src/core/not_null_flat_ptr/get_const.fail.cpp")
runtime_failure_test(NAME "core_not_null_flat_ptr_get" SOURCE
                     "src/core/not_null_flat_ptr/get.fail.cpp")
runtime_failure_test(NAME "core_not_null_flat_ptr_reset_nullptr" SOURCE
                     "src/core/not_null_flat_ptr/reset_nullptr.fail.cpp")
runtime_failure_test(NAME "core_not_null_flat_ptr_swap_other" SOURCE
                     "src/core/not_null_flat_ptr/swap_other.fail.cpp")
runtime_failure_test(NAME "core_not_null_flat_ptr_swap_this" SOURCE
                     "src/core/not_null_flat_ptr/swap_this.fail.cpp")

# not_null_observer_ptr
runtime_failure_test(NAME "core_not_null_observer_ptr_assign_nullptr" SOURCE
                     "src/core/not_null_observer_ptr/assign_nullptr.fail.cpp")
runtime_failure_test(NAME "core_not_null_observer_ptr_construct_nullptr" SOURCE
                     "src/core/not_null_observer_ptr/construct_nullptr.fail.cpp")
runtime_failure_test(NAME "core_not_null_observer_ptr_copy_construct_null" SOURCE
                     "src/core/not_null_observer_ptr/copy_construct_null.fail.cpp")
runtime_failure_test(NAME "core_not_null_observer_ptr_copy_construct_null2" SOURCE
                     "src/core/not_null_observer_ptr/copy_construct_null2.fail.cpp")
runtime_failure_test(NAME "core_not_null_observer_ptr_deref_null_const" SOURCE
                     "src/core/not_null_observer_ptr/deref_null_const.fail.cpp")
runtime_failure_test(NAME "core_not_null_observer_ptr_deref_null_const2" SOURCE
                     "src/core/not_null_observer_ptr/deref_null_const2.fail.cpp")
runtime_failure_test(NAME "core_not_null_observer_ptr_deref_null" SOURCE
                     "src/core/not_null_observer_ptr/deref_null.fail.cpp")
runtime_failure_test(NAME "core_not_null_observer_ptr_deref_null2" SOURCE
                     "src/core/not_null_observer_ptr/deref_null2.fail.cpp")
runtime_failure_test(NAME "core_not_null_observer_ptr_get" SOURCE
                     "src/core/not_null_observer_ptr/get.fail.cpp")
runtime_failure_test(NAME "core_not_null_observer_ptr_move_construct_null" SOURCE
                     "src/core/not_null_observer_ptr/move_construct_null.fail.cpp")
runtime_failure_test(NAME "core_not_null_observer_ptr_move_construct_null2" SOURCE
                     "src/core/not_null_observer_ptr/move_construct_null2.fail.cpp")
runtime_failure_test(NAME "core_not_null_observer_ptr_not_null_flat" SOURCE
                     "src/core/not_null_observer_ptr/not_null_flat.fail.cpp")
runtime_failure_test(NAME "core_not_null_observer_ptr_reset_nullptr" SOURCE
                     "src/core/not_null_observer_ptr/reset_nullptr.fail.cpp")
runtime_failure_test(NAME "core_not_null_observer_ptr_swap" SOURCE
                     "src/core/not_null_observer_ptr/swap.fail.cpp")
runtime_failure_test(NAME "core_not_null_observer_ptr_swap2" SOURCE
                     "src/core/not_null_observer_ptr/swap2.fail.cpp")

# not_null_ref_ptr
runtime_failure_test(NAME "core_not_null_ref_ptr_assign_nullptr" SOURCE
                     "src/core/not_null_ref_ptr/assign_nullptr.fail.cpp")
runtime_failure_test(NAME "core_not_null_ref_ptr_construct_nullptr" SOURCE
                     "src/core/not_null_ref_ptr/construct_nullptr.fail.cpp")
runtime_failure_test(NAME "core_not_null_ref_ptr_copy_construct_with_null" SOURCE
                     "src/core/not_null_ref_ptr/copy_construct_with_null.fail.cpp")
runtime_failure_test(NAME "core_not_null_ref_ptr_copy_construct_with_null2" SOURCE
                     "src/core/not_null_ref_ptr/copy_construct_with_null2.fail.cpp")
runtime_failure_test(NAME "core_not_null_ref_ptr_get_after_moved" SOURCE
                     "src/core/not_null_ref_ptr/get_after_moved.fail.cpp")
runtime_failure_test(NAME "core_not_null_ref_ptr_move_construct_with_null" SOURCE
                     "src/core/not_null_ref_ptr/move_construct_with_null.fail.cpp")
runtime_failure_test(NAME "core_not_null_ref_ptr_move_construct_with_null2" SOURCE
                     "src/core/not_null_ref_ptr/move_construct_with_null2.fail.cpp")
runtime_failure_test(NAME "core_not_null_ref_ptr_reset_nullptr" SOURCE
                     "src/core/not_null_ref_ptr/reset_nullptr.fail.cpp")

# not_null_scope_ptr
runtime_failure_test(NAME "core_not_null_scope_ptr_assign_moved_not_null_scope_ptr" SOURCE
                     "src/core/not_null_scope_ptr/assign_moved_not_null_scope_ptr.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_assign_nullptr" SOURCE
                     "src/core/not_null_scope_ptr/assign_nullptr.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_construct_moved_not_null_scope_ptr" SOURCE
                     "src/core/not_null_scope_ptr/construct_moved_not_null_scope_ptr.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_construct_nullptr" SOURCE
                     "src/core/not_null_scope_ptr/construct_nullptr.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_get_after_leak" SOURCE
                     "src/core/not_null_scope_ptr/get_after_leak.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_get_after_leak_const" SOURCE
                     "src/core/not_null_scope_ptr/get_after_leak_const.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_get_after_move" SOURCE
                     "src/core/not_null_scope_ptr/get_after_move.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_leak_ptr_after_leak" SOURCE
                     "src/core/not_null_scope_ptr/leak_ptr_after_leak.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_leak_ptr_after_move" SOURCE
                     "src/core/not_null_scope_ptr/leak_ptr_after_move.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_not_null_flat" SOURCE
                     "src/core/not_null_scope_ptr/not_null_flat.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_not_null_flat_const" SOURCE
                     "src/core/not_null_scope_ptr/not_null_flat_const.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_not_null_observer" SOURCE
                     "src/core/not_null_scope_ptr/not_null_observer.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_not_null_observer_const" SOURCE
                     "src/core/not_null_scope_ptr/not_null_observer_const.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_operator_arrow_after_leak" SOURCE
                     "src/core/not_null_scope_ptr/operator_arrow_after_leak.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_operator_arrow_after_leak_const" SOURCE
                     "src/core/not_null_scope_ptr/operator_arrow_after_leak_const.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_operator_arrow_after_move" SOURCE
                     "src/core/not_null_scope_ptr/operator_star_after_move.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_operator_star_after_leak" SOURCE
                     "src/core/not_null_scope_ptr/operator_star_after_leak.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_operator_star_after_leak_const" SOURCE
                     "src/core/not_null_scope_ptr/operator_star_after_leak_const.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_operator_star_after_move" SOURCE
                     "src/core/not_null_scope_ptr/operator_star_after_move.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_release_from_nullptr" SOURCE
                     "src/core/not_null_scope_ptr/release_from_nullptr.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_reset_nullptr" SOURCE
                     "src/core/not_null_scope_ptr/reset_nullptr.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_swap_after_move" SOURCE
                     "src/core/not_null_scope_ptr/swap_after_move.fail.cpp")
runtime_failure_test(NAME "core_not_null_scope_ptr_swap_after_move2" SOURCE
                     "src/core/not_null_scope_ptr/swap_after_move2.fail.cpp")

# observer_ptr
runtime_failure_test(NAME "core_observer_ptr_copy_construct_null" SOURCE
                     "src/core/observer_ptr/copy_construct_null.fail.cpp")
runtime_failure_test(NAME "core_observer_ptr_copy_construct_null2" SOURCE
                     "src/core/observer_ptr/copy_construct_null2.fail.cpp")
runtime_failure_test(NAME "core_observer_ptr_not_null" SOURCE
                     "src/core/observer_ptr/not_null.fail.cpp")
runtime_failure_test(NAME "core_observer_ptr_not_null_flat" SOURCE
                     "src/core/observer_ptr/not_null_flat.fail.cpp")
runtime_failure_test(NAME "core_observer_ptr_dereference_nullptr_operator_star" SOURCE
                     "src/core/observer_ptr/deref_null.fail.cpp")
runtime_failure_test(NAME "core_observer_ptr_dereference_nullptr_operator_star_const" SOURCE
                     "src/core/observer_ptr/deref_null_const.fail.cpp")
runtime_failure_test(NAME "core_observer_ptr_move_construct_null" SOURCE
                     "src/core/observer_ptr/move_construct_null.fail.cpp")
runtime_failure_test(NAME "core_observer_ptr_move_construct_null2" SOURCE
                     "src/core/observer_ptr/move_construct_null2.fail.cpp")
runtime_failure_test(NAME "core_observer_ptr_dereference_nullptr_operator_arrow" SOURCE
                     "src/core/observer_ptr/deref_null2.fail.cpp")
runtime_failure_test(NAME "core_observer_ptr_dereference_nullptr_operator_arrow_const" SOURCE
                     "src/core/observer_ptr/deref_null2_const.fail.cpp")

# ref_ptr
runtime_failure_test(NAME "core_ref_ptr_control_block_double_free" SOURCE
                     "src/core/ref_ptr/control_block_double_free.fail.cpp")
runtime_failure_test(NAME "core_ref_ptr_copy_construct_with_null" SOURCE
                     "src/core/ref_ptr/copy_construct_with_null.fail.cpp")
runtime_failure_test(NAME "core_ref_ptr_copy_construct_with_null2" SOURCE
                     "src/core/ref_ptr/copy_construct_with_null2.fail.cpp")
runtime_failure_test(NAME "core_ref_ptr_move_construct_with_null" SOURCE
                     "src/core/ref_ptr/move_construct_with_null.fail.cpp")
runtime_failure_test(NAME "core_ref_ptr_move_construct_with_null2" SOURCE
                     "src/core/ref_ptr/move_construct_with_null2.fail.cpp")
runtime_failure_test(NAME "core_ref_ptr_not_null_flat" SOURCE
                     "src/core/ref_ptr/not_null_flat.fail.cpp")
runtime_failure_test(NAME "core_ref_ptr_not_null_observer" SOURCE
                     "src/core/ref_ptr/not_null_observer.fail.cpp")
runtime_failure_test(NAME "core_ref_ptr_operator_arrow" SOURCE
                     "src/core/ref_ptr/operator_arrow.fail.cpp")
runtime_failure_test(NAME "core_ref_ptr_operator_arrow_const" SOURCE
                     "src/core/ref_ptr/operator_arrow_const.fail.cpp")
runtime_failure_test(NAME "core_ref_ptr_operator_star" SOURCE
                     "src/core/ref_ptr/operator_star.fail.cpp")
runtime_failure_test(NAME "core_ref_ptr_operator_star_const" SOURCE
                     "src/core/ref_ptr/operator_star_const.fail.cpp")

# scope_ptr
runtime_failure_test(NAME "core_scope_ptr_assign_moved_not_null_scope_ptr" SOURCE
                     "src/core/scope_ptr/assign_moved_not_null_scope_ptr.fail.cpp")
runtime_failure_test(NAME "core_scope_ptr_construct_moved_not_null_scope_ptr" SOURCE
                     "src/core/scope_ptr/construct_moved_not_null_scope_ptr.fail.cpp")
runtime_failure_test(NAME "core_scope_ptr_not_null_flat" SOURCE
                     "src/core/scope_ptr/not_null_flat.fail.cpp")
runtime_failure_test(NAME "core_scope_ptr_not_null_flat_const" SOURCE
                     "src/core/scope_ptr/not_null_flat_const.fail.cpp")
runtime_failure_test(NAME "core_scope_ptr_not_null_observer" SOURCE
                     "src/core/scope_ptr/not_null_observer.fail.cpp")
runtime_failure_test(NAME "core_scope_ptr_not_null_observer_const" SOURCE
                     "src/core/scope_ptr/not_null_observer_const.fail.cpp")
runtime_failure_test(NAME "core_scope_ptr_dereference_nullptr_operator_star" SOURCE
                     "src/core/scope_ptr/deref_null.fail.cpp")
runtime_failure_test(NAME "core_scope_ptr_dereference_nullptr_operator_star_const" SOURCE
                     "src/core/scope_ptr/deref_null_const.fail.cpp")
runtime_failure_test(NAME "core_scope_ptr_dereference_nullptr_operator_arrow" SOURCE
                     "src/core/scope_ptr/deref_null2.fail.cpp")
runtime_failure_test(NAME "core_scope_ptr_dereference_nullptr_operator_arrow_const" SOURCE
                     "src/core/scope_ptr/deref_null_const2.fail.cpp")

# source_location
runtime_failure_test(NAME "core_source_location_construct_file_nullptr" SOURCE
                     "src/core/source_location/construct_file_nullptr.fail.cpp")
runtime_failure_test(NAME "core_source_location_construct_function_nullptr" SOURCE
                     "src/core/source_location/construct_function_nullptr.fail.cpp")
runtime_failure_test(NAME "core_source_location_construct_line_zero" SOURCE
                     "src/core/source_location/construct_line_zero.fail.cpp")

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
runtime_failure_test(NAME "text_hex_digit_value_OutOfBounds2" SOURCE
                     "src/text/hex_digit_value/out_of_bounds2.fail.cpp")
runtime_failure_test(NAME "text_hex_digit_value_OutOfBounds3" SOURCE
                     "src/text/hex_digit_value/out_of_bounds3.fail.cpp")
runtime_failure_test(NAME "text_hex_digit_value_OutOfBounds4" SOURCE
                     "src/text/hex_digit_value/out_of_bounds4.fail.cpp")
runtime_failure_test(NAME "text_hex_digit_value_OutOfBounds5" SOURCE
                     "src/text/hex_digit_value/out_of_bounds5.fail.cpp")

# octal_digit_value
runtime_failure_test(NAME "text_octal_digit_value_OutOfBounds" SOURCE
                     "src/text/octal_digit_value/out_of_bounds.fail.cpp")
runtime_failure_test(NAME "text_octal_digit_value_OutOfBounds2" SOURCE
                     "src/text/octal_digit_value/out_of_bounds2.fail.cpp")
