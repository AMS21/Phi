project("Phi_CoreUnittestsTests" CXX)

file(GLOB TEST_HEADERS "include/ConstexprHelper.hpp" "include/Noexcept.hpp" "include/SameType.hpp" "include/TestTypes.hpp")

file(
  GLOB
  TEST_SOURCES
  # Algorithm
  "src/Algorithm/Exchange.test.cpp"
  "src/Algorithm/StringLength.test.cpp"
  "src/Algorithm/Swap.test.cpp"
  # CompilerSupport
  "src/CompilerSupport/Char8_t.test.cpp"
  "src/CompilerSupport/Likely.test.cpp"
  # Config
  "src/Config/Assume.test.cpp"
  "src/Config/Compiler.test.cpp"
  "src/Config/CurrentFunction.test.cpp"
  "src/Config/FunctionLikemacro.test.cpp"
  "src/Config/Glue.test.cpp"
  "src/Config/Inline.test.cpp"
  "src/Config/Platform.test.cpp"
  "src/Config/SourceLine.test.cpp"
  "src/Config/Stringify.test.cpp"
  "src/Config/Unreachable.test.cpp"
  "src/Config/Versioning.test.cpp"
  "src/Config/Warnings.test.cpp"
  # Container
  "src/Container/Array.test.cpp"
  "src/Container/StringView.test.cpp"
  # Core
  "src/Core/AsConst.test.cpp"
  "src/Core/Assert.test.cpp"
  "src/Core/At.test.cpp"
  "src/Core/Boolean.test.cpp"
  "src/Core/Conversion.test.cpp"
  "src/Core/Declval.test.cpp"
  "src/Core/FlatPtr.test.cpp"
  "src/Core/FloatingPoint.test.cpp"
  "src/Core/Forward.test.cpp"
  "src/Core/Integer.test.cpp"
  "src/Core/Invoke.test.cpp"
  "src/Core/Monitor.test.cpp"
  "src/Core/Move.test.cpp"
  "src/Core/NamedType.test.cpp"
  "src/Core/NonCopyable.test.cpp"
  "src/Core/NotNull.test.cpp"
  "src/Core/ObserverPtr.test.cpp"
  "src/Core/Optional.test.cpp"
  "src/Core/ScopedValueGuard.test.cpp"
  "src/Core/ScopeGuard.test.cpp"
  "src/Core/ScopePtr.test.cpp"
  "src/Core/SizeT.test.cpp"
  "src/Core/StopWatch.test.cpp"
  "src/Core/Types.test.cpp"
  # Math
  "src/Math/Abs.test.cpp"
  "src/Math/Constants.test.cpp"
  "src/Math/IsNaN.test.cpp"
  "src/Math/Signum.test.cpp"
  "src/Math/Vector2.test.cpp"
  # Selftest
  "src/Selftest/ConstexprHelper.test.cpp"
  # TypeTraits
  "src/TypeTraits/detail/yes_no_type.test.cpp"
  "src/TypeTraits/add_const.test.cpp"
  "src/TypeTraits/add_cv.test.cpp"
  "src/TypeTraits/add_lvalue_reference.test.cpp"
  "src/TypeTraits/add_pointer.test.cpp"
  "src/TypeTraits/add_rvalue_reference.test.cpp"
  "src/TypeTraits/add_volatile.test.cpp"
  "src/TypeTraits/alignment_of.test.cpp"
  "src/TypeTraits/always_false.test.cpp"
  "src/TypeTraits/conditional.test.cpp"
  "src/TypeTraits/conjunction.test.cpp"
  "src/TypeTraits/copy_const.test.cpp"
  "src/TypeTraits/copy_volatile.test.cpp"
  "src/TypeTraits/decay.test.cpp"
  "src/TypeTraits/disable_if.test.cpp"
  "src/TypeTraits/disjunction.test.cpp"
  "src/TypeTraits/enable_if.test.cpp"
  "src/TypeTraits/extent.test.cpp"
  "src/TypeTraits/has_unique_object_representation.test.cpp"
  "src/TypeTraits/has_virtual_destructor.test.cpp"
  "src/TypeTraits/integral_constant.test.cpp"
  "src/TypeTraits/invoke_result.test.cpp"
  "src/TypeTraits/is_abstract.test.cpp"
  "src/TypeTraits/is_aggregate.test.cpp"
  "src/TypeTraits/is_arithmetic.test.cpp"
  "src/TypeTraits/is_array.test.cpp"
  "src/TypeTraits/is_assignable.test.cpp"
  "src/TypeTraits/is_base_of.test.cpp"
  "src/TypeTraits/is_bool.test.cpp"
  "src/TypeTraits/is_bounded_array.test.cpp"
  "src/TypeTraits/is_class.test.cpp"
  "src/TypeTraits/is_complete.test.cpp"
  "src/TypeTraits/is_compound.test.cpp"
  "src/TypeTraits/is_const.test.cpp"
  "src/TypeTraits/is_constant_evaluated.test.cpp"
  "src/TypeTraits/is_constructible.test.cpp"
  "src/TypeTraits/is_convertible.test.cpp"
  "src/TypeTraits/is_copy_assignable.test.cpp"
  "src/TypeTraits/is_copy_constructible.test.cpp"
  "src/TypeTraits/is_default_constructible.test.cpp"
  "src/TypeTraits/is_destructible.test.cpp"
  "src/TypeTraits/is_empty.test.cpp"
  "src/TypeTraits/is_enum.test.cpp"
  "src/TypeTraits/is_final.test.cpp"
  "src/TypeTraits/is_floating_point.test.cpp"
  "src/TypeTraits/is_function_pointer.test.cpp"
  "src/TypeTraits/is_function.test.cpp"
  "src/TypeTraits/is_fundamental.test.cpp"
  "src/TypeTraits/is_integer.test.cpp"
  "src/TypeTraits/is_integral.test.cpp"
  "src/TypeTraits/is_invocable.test.cpp"
  "src/TypeTraits/is_lvalue_reference.test.cpp"
  "src/TypeTraits/is_member_function_pointer.test.cpp"
  "src/TypeTraits/is_member_object_pointer.test.cpp"
  "src/TypeTraits/is_member_pointer.test.cpp"
  "src/TypeTraits/is_move_assignable.test.cpp"
  "src/TypeTraits/is_move_constructible.test.cpp"
  "src/TypeTraits/is_nothrow_assignable.test.cpp"
  "src/TypeTraits/is_nothrow_constructible.test.cpp"
  "src/TypeTraits/is_nothrow_convertible.test.cpp"
  "src/TypeTraits/is_nothrow_copy_assignable.test.cpp"
  "src/TypeTraits/is_nothrow_copy_constructible.test.cpp"
  "src/TypeTraits/is_nothrow_default_constructible.test.cpp"
  "src/TypeTraits/is_nothrow_destructible.test.cpp"
  "src/TypeTraits/is_nothrow_invocable.test.cpp"
  "src/TypeTraits/is_nothrow_move_assignable.test.cpp"
  "src/TypeTraits/is_nothrow_move_constructible.test.cpp"
  "src/TypeTraits/is_nothrow_swappable_with.test.cpp"
  "src/TypeTraits/is_nothrow_swappable.test.cpp"
  "src/TypeTraits/is_null_pointer_or_pointer.test.cpp"
  "src/TypeTraits/is_null_pointer.test.cpp"
  "src/TypeTraits/is_object.test.cpp"
  "src/TypeTraits/is_pointer.test.cpp"
  "src/TypeTraits/is_polymorphic.test.cpp"
  "src/TypeTraits/is_reference.test.cpp"
  "src/TypeTraits/is_reference_wrapper.test.cpp"
  "src/TypeTraits/is_rvalue_reference.test.cpp"
  "src/TypeTraits/is_safe_arithmetic.test.cpp"
  "src/TypeTraits/is_safe_bool.test.cpp"
  "src/TypeTraits/is_safe_floating_point.test.cpp"
  "src/TypeTraits/is_safe_integer.test.cpp"
  "src/TypeTraits/is_safe_integral.test.cpp"
  "src/TypeTraits/is_safe_type.test.cpp"
  "src/TypeTraits/is_same_rc.test.cpp"
  "src/TypeTraits/is_same_rcv.test.cpp"
  "src/TypeTraits/is_same_rcvref.test.cpp"
  "src/TypeTraits/is_same_rv.test.cpp"
  "src/TypeTraits/is_same.test.cpp"
  "src/TypeTraits/is_scalar.test.cpp"
  "src/TypeTraits/is_standard_layout.test.cpp"
  "src/TypeTraits/is_scoped_enum.test.cpp"
  "src/TypeTraits/is_swappable_with.test.cpp"
  "src/TypeTraits/is_swappable.test.cpp"
  "src/TypeTraits/is_trivial.test.cpp"
  "src/TypeTraits/is_trivially_assignable.test.cpp"
  "src/TypeTraits/is_trivially_constructible.test.cpp"
  "src/TypeTraits/is_trivially_copy_assignable.test.cpp"
  "src/TypeTraits/is_trivially_copy_constructible.test.cpp"
  "src/TypeTraits/is_trivially_copyable.test.cpp"
  "src/TypeTraits/is_trivially_default_constructible.test.cpp"
  "src/TypeTraits/is_trivially_destructible.test.cpp"
  "src/TypeTraits/is_trivially_move_assignable.test.cpp"
  "src/TypeTraits/is_trivially_move_constructible.test.cpp"
  "src/TypeTraits/is_unbounded_array.test.cpp"
  "src/TypeTraits/is_union.test.cpp"
  "src/TypeTraits/is_unsafe_arithmetic.test.cpp"
  "src/TypeTraits/is_unsafe_bool.test.cpp"
  "src/TypeTraits/is_unsafe_floating_point.test.cpp"
  "src/TypeTraits/is_unsafe_integer.test.cpp"
  "src/TypeTraits/is_unsafe_integral.test.cpp"
  "src/TypeTraits/is_unsafe_type.test.cpp"
  "src/TypeTraits/is_unscoped_enum.test.cpp"
  "src/TypeTraits/is_unsigned.test.cpp"
  "src/TypeTraits/is_signed.test.cpp"
  "src/TypeTraits/is_void.test.cpp"
  "src/TypeTraits/is_volatile.test.cpp"
  "src/TypeTraits/make_safe.test.cpp"
  "src/TypeTraits/make_unsafe.test.cpp"
  "src/TypeTraits/make_unsigned.test.cpp"
  "src/TypeTraits/negation.test.cpp"
  "src/TypeTraits/rank.test.cpp"
  "src/TypeTraits/remove_all_extents.test.cpp"
  "src/TypeTraits/remove_const.test.cpp"
  "src/TypeTraits/remove_cv.test.cpp"
  "src/TypeTraits/remove_cvref.test.cpp"
  "src/TypeTraits/remove_extent.test.cpp"
  "src/TypeTraits/remove_pointer.test.cpp"
  "src/TypeTraits/remove_reference.test.cpp"
  "src/TypeTraits/remove_volatile.test.cpp"
  "src/TypeTraits/to_safe.test.cpp"
  "src/TypeTraits/to_unsafe.test.cpp"
  "src/TypeTraits/type_identity.test.cpp"
  "src/TypeTraits/underlying_type.test.cpp"
  "src/TypeTraits/void_t.test.cpp"
  # Base
  "src/PhiConfig.test.cpp")

if (${CMAKE_VERSION} VERSION_GREATER "3.7")
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TEST_HEADERS} ${TEST_SOURCES})
endif()

foreach(file IN ITEMS ${TEST_SOURCES})
  get_filename_component(file_name "${file}" NAME_WE)
  set(dynamic_name "Phi_Unittest_${file_name}")
  set(static_name "Phi_Unittest_${file_name}_Constexpr")
  set(no_intrinsic_name "Phi_Unittest_${file_name}_NoIntrinsic")

  # Normal test
  phi_add_executable(NAME ${dynamic_name} SOURCES ${file} FOLDER "Tests/Unittests/Dynamic" PRIVATE_LINK_LIBRARIES Phi::InternalProjectOptions Phi::Core Catch2::Catch2 PRIVATE_INCLUDE_DIRS "include")
  target_compile_definitions(${dynamic_name} PRIVATE CATCH_CONFIG_MAIN CATCH_CONFIG_RUNTIME_STATIC_REQUIRE)
  phi_enable_static_analyzers(${dynamic_name})
  phi_add_test(TARGET ${dynamic_name})

  # Constexpr test
  phi_add_executable(NAME ${static_name} SOURCES ${file} FOLDER "Tests/Unittests/Constexpr" PRIVATE_LINK_LIBRARIES Phi::InternalProjectOptions Phi::Core Catch2::Catch2 PRIVATE_INCLUDE_DIRS "include")
  target_compile_definitions(${static_name} PRIVATE CATCH_CONFIG_MAIN)
  phi_enable_static_analyzers(${static_name})
  phi_add_test(TARGET ${static_name})

  # No intrinsic test
  #phi_add_executable(NAME ${no_intrinsic_name} SOURCES ${file} FOLDER "Tests/Unittests/NoIntrinsics" PRIVATE_LINK_LIBRARIES Phi::InternalProjectOptions Phi::Core Catch2::Catch2 PRIVATE_INCLUDE_DIRS "include")
  #target_compile_definitions(${no_intrinsic_name} PRIVATE CATCH_CONFIG_MAIN PHI_CONFIG_NO_INTRINSICS)
  #phi_enable_static_analyzers(${no_intrinsic_name})
  #phi_add_test(TARGET ${no_intrinsic_name})
endforeach()
