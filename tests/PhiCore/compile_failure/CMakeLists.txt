project("PhiCoreTestCompileFailure" CXX)

include(TestFail)

# selftest
compile_failure_test(NAME "selftest_static_assert" SOURCE "src/selftest/static_assert.fail.cpp")

# algorithm string_length_unsafe
compile_failure_test(NAME "algorithm_string_length_unsafe_count_nullptr" SOURCE
                     "src/algorithm/string_length_unsafe/count_nullptr.fail.cpp")
compile_failure_test(NAME "algorithm_string_length_unsafe_nullptr" SOURCE
                     "src/algorithm/string_length_unsafe/nullptr.fail.cpp")

# container

# string_view
compile_failure_test(NAME "container_string_view_construct_with_nullptr" SOURCE
                     "src/container/string_view/construct_nullptr.fail.cpp")
compile_failure_test(NAME "container_string_view_assign_nullptr" SOURCE
                     "src/container/string_view/assign_nullptr.fail.cpp")

# core address_of
compile_failure_test(NAME "core_address_of_rvalue" SOURCE "src/core/address_of/rvalue.fail.cpp")

# iterator iter_reference
compile_failure_test(NAME "iterator_iter_reference_non_referenceable" SOURCE
                     "src/iterator/iter_reference/non_referenceable.fail.cpp")

# assert
compile_failure_test(NAME "core_assert_constexpr" SOURCE
                     "src/core/assert/assert_constexpr.fail.cpp")
compile_failure_test(NAME "core_assert_not_reached_constexpr" SOURCE
                     "src/core/assert/assert_not_reached_constexpr.fail.cpp")

# flat_ptr
compile_failure_test(NAME "core_flat_ptr_not_null_default_constructor" SOURCE
                     "src/core/flat_ptr/not_null_default.fail.cpp")
compile_failure_test(NAME "core_flat_ptr_not_null_construct_from_nullptr" SOURCE
                     "src/core/flat_ptr/not_null_construct_nullptr.fail.cpp")
compile_failure_test(NAME "core_flat_ptr_not_null_assign_nullptr" SOURCE
                     "src/core/flat_ptr/not_null_assign_nullptr.fail.cpp")

# floating_point
compile_failure_test(NAME "core_floating_point_construct_from_int" SOURCE
                     "src/core/floating_point/int.fail.cpp")

# integer
compile_failure_test(NAME "core_integer_construct_from_bool" SOURCE
                     "src/core/integer/bool.fail.cpp")
compile_failure_test(NAME "core_integer_construct_from_char" SOURCE
                     "src/core/integer/char.fail.cpp")
compile_failure_test(NAME "core_integer_construct_from_float" SOURCE
                     "src/core/integer/float.fail.cpp")
compile_failure_test(NAME "core_integer_unsigned_unary_minus" SOURCE
                     "src/core/integer/unsigned_unary_minus.fail.cpp")

# non_copyable
compile_failure_test(NAME "core_non_copyable_not_constructable" SOURCE
                     "src/core/non_copyable/construct.fail.cpp")
compile_failure_test(NAME "core_non_copyable_copy_assign" SOURCE
                     "src/core/non_copyable/copy_assign.fail.cpp")
compile_failure_test(NAME "core_non_copyable_copy_construct" SOURCE
                     "src/core/non_copyable/copy_construct.fail.cpp")

# not_null_ref_ptr
compile_failure_test(NAME "core_not_null_ref_ptr_assign_nullptr" SOURCE
                     "src/core/not_null_ref_ptr/assign_nullptr.fail.cpp")
compile_failure_test(NAME "core_not_null_ref_ptr_construct_nullptr" SOURCE
                     "src/core/not_null_ref_ptr/construct_nullptr.fail.cpp")
compile_failure_test(NAME "core_not_null_ref_ptr_default_constructor" SOURCE
                     "src/core/not_null_ref_ptr/default.fail.cpp")

# observer_ptr
compile_failure_test(NAME "core_observer_ptr_not_null_default_constructor" SOURCE
                     "src/core/observer_ptr/not_null_default.fail.cpp")
compile_failure_test(NAME "core_observer_ptr_not_null_construct_from_nullptr" SOURCE
                     "src/core/observer_ptr/not_null_construct_nullptr.fail.cpp")
compile_failure_test(NAME "core_observer_ptr_not_null_assign_nullptr" SOURCE
                     "src/core/observer_ptr/not_null_assign_nullptr.fail.cpp")

# scope_ptr
compile_failure_test(NAME "core_scope_ptr_assign_nullptr" SOURCE
                     "src/core/scope_ptr/not_null_assign_nullptr.fail.cpp")
compile_failure_test(NAME "core_not_null_scope_ptr_construct_from_nullptr" SOURCE
                     "src/core/scope_ptr/not_null_construct_nullptr.fail.cpp")
compile_failure_test(NAME "core_not_null_scope_ptr_default_constructor" SOURCE
                     "src/core/scope_ptr/not_null_default.fail.cpp")
compile_failure_test(NAME "core_not_null_scope_ptr_reset_with_nullptr" SOURCE
                     "src/core/scope_ptr/not_null_reset_nullptr.fail.cpp")

# math vector2
compile_failure_test(NAME "math_vector2_unary_minus" SOURCE "src/math/vector2/unary_minus.fail.cpp")

# vector3
compile_failure_test(NAME "math_vector3_unary_minus" SOURCE "src/math/vector3/unary_minus.fail.cpp")

# type_traits false_t
compile_failure_test(NAME "type_traits_false_t_two_phase_lookup" SOURCE
                     "src/type_traits/false_t/two_phase_lookup.fail.cpp")

# is_constant_evaluated
if(PHI_HAS_INTRINSIC_BUILTIN_IS_CONSTANT_EVALUATED)
  compile_failure_test(NAME "type_traits_is_constant_evaluated_static_assert" SOURCE
                       "src/type_traits/is_constant_evaluated/static_assert.fail.cpp")
  compile_failure_test(NAME "type_traits_is_constant_evaluated_constexpr" SOURCE
                       "src/type_traits/is_constant_evaluated/static_assert.fail.cpp")
endif()

# static_clamp
compile_failure_test(NAME "type_traits_static_clamp_min_less_than_max" SOURCE
                     "src/type_traits/static_clamp/min_less_max.fail.cpp")
