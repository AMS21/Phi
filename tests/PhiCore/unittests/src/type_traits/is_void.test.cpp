#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_arithmetic.hpp>
#include <phi/type_traits/is_array.hpp>
#include <phi/type_traits/is_bool.hpp>
#include <phi/type_traits/is_class.hpp>
#include <phi/type_traits/is_compound.hpp>
#include <phi/type_traits/is_enum.hpp>
#include <phi/type_traits/is_floating_point.hpp>
#include <phi/type_traits/is_function.hpp>
#include <phi/type_traits/is_fundamental.hpp>
#include <phi/type_traits/is_integer.hpp>
#include <phi/type_traits/is_integral.hpp>
#include <phi/type_traits/is_lvalue_reference.hpp>
#include <phi/type_traits/is_member_function_pointer.hpp>
#include <phi/type_traits/is_member_object_pointer.hpp>
#include <phi/type_traits/is_member_pointer.hpp>
#include <phi/type_traits/is_null_pointer.hpp>
#include <phi/type_traits/is_object.hpp>
#include <phi/type_traits/is_pointer.hpp>
#include <phi/type_traits/is_reference.hpp>
#include <phi/type_traits/is_rvalue_reference.hpp>
#include <phi/type_traits/is_scalar.hpp>
#include <phi/type_traits/is_union.hpp>
#include <phi/type_traits/is_void.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_void_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_bool<TypeT>::value);
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class<TypeT>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_compound<TypeT>::value);
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum<TypeT>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_floating_point<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<TypeT>::value);
    STATIC_REQUIRE(phi::is_fundamental<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_integer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_integral<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer<TypeT>::value);
#if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE_FALSE(phi::is_object<TypeT>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<TypeT>::value);
#if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE_FALSE(phi::is_scalar<TypeT>::value);
#endif
#if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union<TypeT>::value);
#endif
    STATIC_REQUIRE(phi::is_void<TypeT>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_void<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_bool_v<TypeT>);
#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class_v<TypeT>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_compound_v<TypeT>);
#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum_v<TypeT>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_floating_point_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<TypeT>);
    STATIC_REQUIRE(phi::is_fundamental_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_integer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_integral_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<TypeT>);
#    if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE_FALSE(phi::is_object_v<TypeT>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<TypeT>);
#    if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE_FALSE(phi::is_scalar_v<TypeT>);
#    endif
#    if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union_v<TypeT>);
#    endif
    STATIC_REQUIRE(phi::is_void_v<TypeT>);

    STATIC_REQUIRE_FALSE(phi::is_not_void_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_void<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_void<TypeT>);

    // Standard compatbility
    STATIC_REQUIRE(std::is_void<TypeT>::value);
}

template <typename TypeT>
void test_is_void()
{
    test_is_void_impl<TypeT>();
    test_is_void_impl<const TypeT>();
    test_is_void_impl<volatile TypeT>();
    test_is_void_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_void_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_void<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_void<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_void_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_void_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_void<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_void<TypeT>);

    // Standard compatbility
    STATIC_REQUIRE_FALSE(std::is_void<TypeT>::value);
}

template <typename TypeT>
void test_is_not_void()
{
    test_is_not_void_impl<TypeT>();
    test_is_not_void_impl<const TypeT>();
    test_is_not_void_impl<volatile TypeT>();
    test_is_not_void_impl<const volatile TypeT>();
}

TEST_CASE("is_void")
{
    test_is_void<void>();
    test_is_not_void<phi::nullptr_t>();
    test_is_not_void<bool>();
    test_is_not_void<char>();
    test_is_not_void<signed char>();
    test_is_not_void<unsigned char>();
    test_is_not_void<short>();
    test_is_not_void<unsigned short>();
    test_is_not_void<int>();
    test_is_not_void<unsigned int>();
    test_is_not_void<long>();
    test_is_not_void<unsigned long>();
    test_is_not_void<long long>();
    test_is_not_void<unsigned long long>();
    test_is_not_void<float>();
    test_is_not_void<double>();
    test_is_not_void<long double>();
    test_is_not_void<char8_t>();
    test_is_not_void<char16_t>();
    test_is_not_void<char32_t>();
    test_is_not_void<wchar_t>();

    test_is_not_void<phi::boolean>();
    test_is_not_void<phi::integer<signed char>>();
    test_is_not_void<phi::integer<unsigned char>>();
    test_is_not_void<phi::integer<short>>();
    test_is_not_void<phi::integer<unsigned short>>();
    test_is_not_void<phi::integer<int>>();
    test_is_not_void<phi::integer<unsigned int>>();
    test_is_not_void<phi::integer<long>>();
    test_is_not_void<phi::integer<unsigned long>>();
    test_is_not_void<phi::integer<long long>>();
    test_is_not_void<phi::integer<unsigned long long>>();
    test_is_not_void<phi::floating_point<float>>();
    test_is_not_void<phi::floating_point<double>>();
    test_is_not_void<phi::floating_point<long double>>();

    test_is_not_void<std::vector<int>>();
    test_is_not_void<phi::scope_ptr<int>>();

    test_is_not_void<int&>();
    test_is_not_void<const int&>();
    test_is_not_void<volatile int&>();
    test_is_not_void<const volatile int&>();
    test_is_not_void<int&&>();
    test_is_not_void<const int&&>();
    test_is_not_void<volatile int&&>();
    test_is_not_void<const volatile int&&>();
    test_is_not_void<int*>();
    test_is_not_void<const int*>();
    test_is_not_void<volatile int*>();
    test_is_not_void<const volatile int*>();
    test_is_not_void<int**>();
    test_is_not_void<const int**>();
    test_is_not_void<volatile int**>();
    test_is_not_void<const volatile int**>();
    test_is_not_void<int*&>();
    test_is_not_void<const int*&>();
    test_is_not_void<volatile int*&>();
    test_is_not_void<const volatile int*&>();
    test_is_not_void<int*&&>();
    test_is_not_void<const int*&&>();
    test_is_not_void<volatile int*&&>();
    test_is_not_void<const volatile int*&&>();
    test_is_not_void<void*>();
    test_is_not_void<char[3]>();
    test_is_not_void<char[]>();
    test_is_not_void<char* [3]>();
    test_is_not_void<char*[]>();
    test_is_not_void<int(*)[3]>();
    test_is_not_void<int(*)[]>();
    test_is_not_void<int(&)[3]>();
    test_is_not_void<int(&)[]>();
    test_is_not_void<int(&&)[3]>();
    test_is_not_void<int(&&)[]>();
    test_is_not_void<char[3][2]>();
    test_is_not_void<char[][2]>();
    test_is_not_void<char* [3][2]>();
    test_is_not_void<char*[][2]>();
    test_is_not_void<int(*)[3][2]>();
    test_is_not_void<int(*)[][2]>();
    test_is_not_void<int(&)[3][2]>();
    test_is_not_void<int(&)[][2]>();
    test_is_not_void<int(&&)[3][2]>();
    test_is_not_void<int(&&)[][2]>();
    test_is_not_void<class_type>();
    test_is_not_void<class_type[]>();
    test_is_not_void<class_type[2]>();
    test_is_not_void<template_type<void>>();
    test_is_not_void<template_type<int>>();
    test_is_not_void<template_type<class_type>>();
    test_is_not_void<template_type<incomplete_type>>();
    test_is_not_void<variadic_template<>>();
    test_is_not_void<variadic_template<void>>();
    test_is_not_void<variadic_template<int>>();
    test_is_not_void<variadic_template<class_type>>();
    test_is_not_void<variadic_template<incomplete_type>>();
    test_is_not_void<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_void<public_derived_from<base>>();
    test_is_not_void<public_derived_from<derived>>();
    test_is_not_void<public_derived_from<class_type>>();
    test_is_not_void<private_derived_from<base>>();
    test_is_not_void<private_derived_from<derived>>();
    test_is_not_void<private_derived_from<class_type>>();
    test_is_not_void<protected_derived_from<base>>();
    test_is_not_void<protected_derived_from<derived>>();
    test_is_not_void<protected_derived_from<class_type>>();
    test_is_not_void<virtual_derived_from<base>>();
    test_is_not_void<virtual_derived_from<derived>>();
    test_is_not_void<virtual_derived_from<class_type>>();
    test_is_not_void<union_type>();
    test_is_not_void<non_empty_union>();
    test_is_not_void<non_trivial_union>();
    test_is_not_void<empty>();
    test_is_not_void<not_empty>();
    test_is_not_void<non_trivial>();
    test_is_not_void<bit_zero>();
    test_is_not_void<bit_one>();
    test_is_not_void<base>();
    test_is_not_void<derived>();
    test_is_not_void<non_empty_base>();
    test_is_not_void<empty_base>();
    test_is_not_void<virtual_base>();
    test_is_not_void<polymorphic>();
    test_is_not_void<derived_polymorphic>();
    test_is_not_void<abstract>();
    test_is_not_void<public_abstract>();
    test_is_not_void<private_abstract>();
    test_is_not_void<protected_abstract>();
    test_is_not_void<abstract_template<int>>();
    test_is_not_void<abstract_template<double>>();
    test_is_not_void<abstract_template<class_type>>();
    test_is_not_void<abstract_template<incomplete_type>>();
    test_is_not_void<public_abstract_deleted_destructor>();
    test_is_not_void<protected_abstract_deleted_destructor>();
    test_is_not_void<private_abstract_deleted_destructor>();
    test_is_not_void<final_type>();
    test_is_not_void<final_derived>();
    test_is_not_void<public_destructor>();
    test_is_not_void<protected_destructor>();
    test_is_not_void<private_destructor>();
    test_is_not_void<virtual_public_destructor>();
    test_is_not_void<virtual_protected_destructor>();
    test_is_not_void<virtual_private_destructor>();
    test_is_not_void<pure_public_destructor>();
    test_is_not_void<pure_protected_destructor>();
    test_is_not_void<pure_private_destructor>();
    test_is_not_void<deleted_public_destructor>();
    test_is_not_void<deleted_protected_destructor>();
    test_is_not_void<deleted_private_destructor>();
    test_is_not_void<deleted_virtual_public_destructor>();
    test_is_not_void<deleted_virtual_protected_destructor>();
    test_is_not_void<deleted_virtual_private_destructor>();
    test_is_not_void<explicit_class>();
    test_is_not_void<nothrow_explicit_class>();
    test_is_not_void<throw_explicit_class>();
    test_is_not_void<throw_default_class>();
    test_is_not_void<throw_copy_constructible_class>();
    test_is_not_void<throw_move_constructible_class>();
    test_is_not_void<throw_destructor>();
    test_is_not_void<noexcept_explicit_class>();
    test_is_not_void<except_explicit_class>();
    test_is_not_void<noexcept_default_class>();
    test_is_not_void<except_default_class>();
    test_is_not_void<noexcept_copy_constructible_class>();
    test_is_not_void<except_copy_constructible_class>();
    test_is_not_void<noexcept_move_constructible_class>();
    test_is_not_void<except_move_constructible_class>();
    test_is_not_void<noexcept_copy_assign_class>();
    test_is_not_void<except_copy_assign_class>();
    test_is_not_void<noexcept_move_assign_class>();
    test_is_not_void<except_move_assign_class>();
    test_is_not_void<deleted_copy_assign_class>();
    test_is_not_void<deleted_move_assign_class>();
    test_is_not_void<noexcept_move_constructible_and_assignable_class>();
    test_is_not_void<except_move_constructible_noexcept_move_assign_class>();
    test_is_not_void<noexcept_move_constructible_except_move_assign_class>();
    test_is_not_void<except_move_constructible_and_assign_class>();
    test_is_not_void<implicit_to<int>>();
    test_is_not_void<implicit_to<float>>();
    test_is_not_void<implicit_to<class_type>>();
    test_is_not_void<deleted_implicit_to<int>>();
    test_is_not_void<deleted_implicit_to<float>>();
    test_is_not_void<deleted_implicit_to<class_type>>();
    test_is_not_void<explicit_to<int>>();
    test_is_not_void<explicit_to<float>>();
    test_is_not_void<explicit_to<class_type>>();
    test_is_not_void<deleted_explicit_to<int>>();
    test_is_not_void<deleted_explicit_to<float>>();
    test_is_not_void<deleted_explicit_to<class_type>>();
    test_is_not_void<ellipsis>();
    test_is_not_void<deleted_ellipsis>();
    test_is_not_void<copy_constructible_only_type>();
    test_is_not_void<move_constructible_only_type>();
    test_is_not_void<overloaded_operators>();
    test_is_not_void<public_int_member>();
    test_is_not_void<protected_int_member>();
    test_is_not_void<private_int_member>();
    test_is_not_void<public_static_int_member>();
    test_is_not_void<protected_static_int_member>();
    test_is_not_void<private_static_int_member>();
    test_is_not_void<public_template_member<int>>();
    test_is_not_void<public_template_member<float>>();
    test_is_not_void<public_template_member<class_type>>();
    test_is_not_void<protected_template_member<int>>();
    test_is_not_void<protected_template_member<float>>();
    test_is_not_void<protected_template_member<class_type>>();
    test_is_not_void<private_template_member<int>>();
    test_is_not_void<private_template_member<float>>();
    test_is_not_void<private_template_member<class_type>>();
    test_is_not_void<public_static_template_member<int>>();
    test_is_not_void<public_static_template_member<float>>();
    test_is_not_void<public_static_template_member<class_type>>();
    test_is_not_void<protected_static_template_member<int>>();
    test_is_not_void<protected_static_template_member<float>>();
    test_is_not_void<protected_static_template_member<class_type>>();
    test_is_not_void<private_static_template_member<int>>();
    test_is_not_void<private_static_template_member<float>>();
    test_is_not_void<private_static_template_member<class_type>>();
    test_is_not_void<cannot_instantiate<int>>();
    test_is_not_void<cannot_instantiate<float>>();
    test_is_not_void<cannot_instantiate<class_type>>();
    test_is_not_void<natural_alignment>();
    test_is_not_void<Enum>();
    test_is_not_void<EnumSigned>();
    test_is_not_void<EnumUnsigned>();
    test_is_not_void<EnumClass>();
    test_is_not_void<EnumStruct>();
    test_is_not_void<function_type>();
    test_is_not_void<function_ptr>();
    test_is_not_void<member_object_ptr>();
    test_is_not_void<member_function_ptr>();
    test_is_not_void<lambda_type>();
    test_is_not_void<lambda_noexcept_type>();
    test_is_not_void<lambda_throws_type>();
    test_is_not_void<incomplete_type>();
    test_is_not_void<incomplete_template<void>>();
    test_is_not_void<incomplete_template<int>>();
    test_is_not_void<incomplete_template<class_type>>();
    test_is_not_void<incomplete_template<incomplete_type>>();
    test_is_not_void<incomplete_variadic_template<>>();
    test_is_not_void<incomplete_variadic_template<void>>();
    test_is_not_void<incomplete_variadic_template<int>>();
    test_is_not_void<incomplete_variadic_template<class_type>>();
    test_is_not_void<incomplete_variadic_template<incomplete_type>>();
    test_is_not_void<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_void<incomplete_union>();
    test_is_not_void<IncompleteEnumSigned>();
    test_is_not_void<IncompleteEnumUnsigned>();
    test_is_not_void<IncompleteEnumClass>();
    test_is_not_void<IncompleteEnumStruct>();
    test_is_not_void<int class_type::*>();
    test_is_not_void<float class_type::*>();
    test_is_not_void<void * class_type::*>();
    test_is_not_void<int * class_type::*>();
    test_is_not_void<Enum class_type::*>();
    test_is_not_void<not_empty class_type::*>();
    test_is_not_void<int class_type::*&>();
    test_is_not_void<float class_type::*&>();
    test_is_not_void<void * class_type::*&>();
    test_is_not_void<int * class_type::*&>();
    test_is_not_void<Enum class_type::*&>();
    test_is_not_void<not_empty class_type::*&>();
    test_is_not_void<int class_type::*&&>();
    test_is_not_void<float class_type::*&&>();
    test_is_not_void<void * class_type::*&&>();
    test_is_not_void<int * class_type::*&&>();
    test_is_not_void<Enum class_type::*&&>();
    test_is_not_void<not_empty class_type::*&&>();
    test_is_not_void<non_default_constructible>();
    test_is_not_void<non_copy_constructible>();
    test_is_not_void<non_move_constructible>();
    test_is_not_void<non_copy_assignable>();
    test_is_not_void<non_move_assignable>();
    test_is_not_void<non_assignable>();
    test_is_not_void<non_copyable>();
    test_is_not_void<non_moveable>();
    test_is_not_void<non_constructible>();
    test_is_not_void<non_destructible>();
    test_is_not_void<tracked>();
    test_is_not_void<trap_constructible>();
    test_is_not_void<trap_implicit_conversion>();
    test_is_not_void<trap_comma>();
    test_is_not_void<trap_call>();
    test_is_not_void<trap_self_assign>();
    test_is_not_void<trap_deref>();
    test_is_not_void<trap_array_subscript>();
    test_is_not_void<operator_hijacker>();

#if PHI_HAS_EXTENSION_ZERO_SIZE_ARRAY()
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wzero-length-array")
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wpedantic")

    test_is_not_void<int[0]>();

    PHI_GCC_SUPPRESS_WARNING_POP()
    PHI_CLANG_SUPPRESS_WARNING_POP()
#endif

    test_is_not_void<void()>();
    test_is_not_void<void()&>();
    test_is_not_void<void() &&>();
    test_is_not_void<void() const>();
    test_is_not_void<void() const&>();
    test_is_not_void<void() const&&>();
    test_is_not_void<void() volatile>();
    test_is_not_void<void() volatile&>();
    test_is_not_void<void() volatile&&>();
    test_is_not_void<void() const volatile>();
    test_is_not_void<void() const volatile&>();
    test_is_not_void<void() const volatile&&>();
    test_is_not_void<void() noexcept>();
    test_is_not_void<void() & noexcept>();
    test_is_not_void<void() && noexcept>();
    test_is_not_void<void() const noexcept>();
    test_is_not_void<void() const & noexcept>();
    test_is_not_void<void() const && noexcept>();
    test_is_not_void<void() volatile noexcept>();
    test_is_not_void<void() volatile & noexcept>();
    test_is_not_void<void() volatile && noexcept>();
    test_is_not_void<void() const volatile noexcept>();
    test_is_not_void<void() const volatile & noexcept>();
    test_is_not_void<void() const volatile && noexcept>();

    test_is_not_void<void(int)>();
    test_is_not_void<void(int)&>();
    test_is_not_void<void(int) &&>();
    test_is_not_void<void(int) const>();
    test_is_not_void<void(int) const&>();
    test_is_not_void<void(int) const&&>();
    test_is_not_void<void(int) volatile>();
    test_is_not_void<void(int) volatile&>();
    test_is_not_void<void(int) volatile&&>();
    test_is_not_void<void(int) const volatile>();
    test_is_not_void<void(int) const volatile&>();
    test_is_not_void<void(int) const volatile&&>();
    test_is_not_void<void(int) noexcept>();
    test_is_not_void<void(int) & noexcept>();
    test_is_not_void<void(int) && noexcept>();
    test_is_not_void<void(int) const noexcept>();
    test_is_not_void<void(int) const & noexcept>();
    test_is_not_void<void(int) const && noexcept>();
    test_is_not_void<void(int) volatile noexcept>();
    test_is_not_void<void(int) volatile & noexcept>();
    test_is_not_void<void(int) volatile && noexcept>();
    test_is_not_void<void(int) const volatile noexcept>();
    test_is_not_void<void(int) const volatile & noexcept>();
    test_is_not_void<void(int) const volatile && noexcept>();

    test_is_not_void<void(...)>();
    test_is_not_void<void(...)&>();
    test_is_not_void<void(...) &&>();
    test_is_not_void<void(...) const>();
    test_is_not_void<void(...) const&>();
    test_is_not_void<void(...) const&&>();
    test_is_not_void<void(...) volatile>();
    test_is_not_void<void(...) volatile&>();
    test_is_not_void<void(...) volatile&&>();
    test_is_not_void<void(...) const volatile>();
    test_is_not_void<void(...) const volatile&>();
    test_is_not_void<void(...) const volatile&&>();
    test_is_not_void<void(...) noexcept>();
    test_is_not_void<void(...) & noexcept>();
    test_is_not_void<void(...) && noexcept>();
    test_is_not_void<void(...) const noexcept>();
    test_is_not_void<void(...) const & noexcept>();
    test_is_not_void<void(...) const && noexcept>();
    test_is_not_void<void(...) volatile noexcept>();
    test_is_not_void<void(...) volatile & noexcept>();
    test_is_not_void<void(...) volatile && noexcept>();
    test_is_not_void<void(...) const volatile noexcept>();
    test_is_not_void<void(...) const volatile & noexcept>();
    test_is_not_void<void(...) const volatile && noexcept>();

    test_is_not_void<void(int, ...)>();
    test_is_not_void<void(int, ...)&>();
    test_is_not_void<void(int, ...) &&>();
    test_is_not_void<void(int, ...) const>();
    test_is_not_void<void(int, ...) const&>();
    test_is_not_void<void(int, ...) const&&>();
    test_is_not_void<void(int, ...) volatile>();
    test_is_not_void<void(int, ...) volatile&>();
    test_is_not_void<void(int, ...) volatile&&>();
    test_is_not_void<void(int, ...) const volatile>();
    test_is_not_void<void(int, ...) const volatile&>();
    test_is_not_void<void(int, ...) const volatile&&>();
    test_is_not_void<void(int, ...) noexcept>();
    test_is_not_void<void(int, ...) & noexcept>();
    test_is_not_void<void(int, ...) && noexcept>();
    test_is_not_void<void(int, ...) const noexcept>();
    test_is_not_void<void(int, ...) const & noexcept>();
    test_is_not_void<void(int, ...) const && noexcept>();
    test_is_not_void<void(int, ...) volatile noexcept>();
    test_is_not_void<void(int, ...) volatile & noexcept>();
    test_is_not_void<void(int, ...) volatile && noexcept>();
    test_is_not_void<void(int, ...) const volatile noexcept>();
    test_is_not_void<void(int, ...) const volatile & noexcept>();
    test_is_not_void<void(int, ...) const volatile && noexcept>();

    test_is_not_void<int()>();
    test_is_not_void<int()&>();
    test_is_not_void<int() &&>();
    test_is_not_void<int() const>();
    test_is_not_void<int() const&>();
    test_is_not_void<int() const&&>();
    test_is_not_void<int() volatile>();
    test_is_not_void<int() volatile&>();
    test_is_not_void<int() volatile&&>();
    test_is_not_void<int() const volatile>();
    test_is_not_void<int() const volatile&>();
    test_is_not_void<int() const volatile&&>();
    test_is_not_void<int() noexcept>();
    test_is_not_void<int() & noexcept>();
    test_is_not_void<int() && noexcept>();
    test_is_not_void<int() const noexcept>();
    test_is_not_void<int() const & noexcept>();
    test_is_not_void<int() const && noexcept>();
    test_is_not_void<int() volatile noexcept>();
    test_is_not_void<int() volatile & noexcept>();
    test_is_not_void<int() volatile && noexcept>();
    test_is_not_void<int() const volatile noexcept>();
    test_is_not_void<int() const volatile & noexcept>();
    test_is_not_void<int() const volatile && noexcept>();

    test_is_not_void<int(int)>();
    test_is_not_void<int(int)&>();
    test_is_not_void<int(int) &&>();
    test_is_not_void<int(int) const>();
    test_is_not_void<int(int) const&>();
    test_is_not_void<int(int) const&&>();
    test_is_not_void<int(int) volatile>();
    test_is_not_void<int(int) volatile&>();
    test_is_not_void<int(int) volatile&&>();
    test_is_not_void<int(int) const volatile>();
    test_is_not_void<int(int) const volatile&>();
    test_is_not_void<int(int) const volatile&&>();
    test_is_not_void<int(int) noexcept>();
    test_is_not_void<int(int) & noexcept>();
    test_is_not_void<int(int) && noexcept>();
    test_is_not_void<int(int) const noexcept>();
    test_is_not_void<int(int) const & noexcept>();
    test_is_not_void<int(int) const && noexcept>();
    test_is_not_void<int(int) volatile noexcept>();
    test_is_not_void<int(int) volatile & noexcept>();
    test_is_not_void<int(int) volatile && noexcept>();
    test_is_not_void<int(int) const volatile noexcept>();
    test_is_not_void<int(int) const volatile & noexcept>();
    test_is_not_void<int(int) const volatile && noexcept>();

    test_is_not_void<int(...)>();
    test_is_not_void<int(...)&>();
    test_is_not_void<int(...) &&>();
    test_is_not_void<int(...) const>();
    test_is_not_void<int(...) const&>();
    test_is_not_void<int(...) const&&>();
    test_is_not_void<int(...) volatile>();
    test_is_not_void<int(...) volatile&>();
    test_is_not_void<int(...) volatile&&>();
    test_is_not_void<int(...) const volatile>();
    test_is_not_void<int(...) const volatile&>();
    test_is_not_void<int(...) const volatile&&>();
    test_is_not_void<int(...) noexcept>();
    test_is_not_void<int(...) & noexcept>();
    test_is_not_void<int(...) && noexcept>();
    test_is_not_void<int(...) const noexcept>();
    test_is_not_void<int(...) const & noexcept>();
    test_is_not_void<int(...) const && noexcept>();
    test_is_not_void<int(...) volatile noexcept>();
    test_is_not_void<int(...) volatile & noexcept>();
    test_is_not_void<int(...) volatile && noexcept>();
    test_is_not_void<int(...) const volatile noexcept>();
    test_is_not_void<int(...) const volatile & noexcept>();
    test_is_not_void<int(...) const volatile && noexcept>();

    test_is_not_void<int(int, ...)>();
    test_is_not_void<int(int, ...)&>();
    test_is_not_void<int(int, ...) &&>();
    test_is_not_void<int(int, ...) const>();
    test_is_not_void<int(int, ...) const&>();
    test_is_not_void<int(int, ...) const&&>();
    test_is_not_void<int(int, ...) volatile>();
    test_is_not_void<int(int, ...) volatile&>();
    test_is_not_void<int(int, ...) volatile&&>();
    test_is_not_void<int(int, ...) const volatile>();
    test_is_not_void<int(int, ...) const volatile&>();
    test_is_not_void<int(int, ...) const volatile&&>();
    test_is_not_void<int(int, ...) noexcept>();
    test_is_not_void<int(int, ...) & noexcept>();
    test_is_not_void<int(int, ...) && noexcept>();
    test_is_not_void<int(int, ...) const noexcept>();
    test_is_not_void<int(int, ...) const & noexcept>();
    test_is_not_void<int(int, ...) const && noexcept>();
    test_is_not_void<int(int, ...) volatile noexcept>();
    test_is_not_void<int(int, ...) volatile & noexcept>();
    test_is_not_void<int(int, ...) volatile && noexcept>();
    test_is_not_void<int(int, ...) const volatile noexcept>();
    test_is_not_void<int(int, ...) const volatile & noexcept>();
    test_is_not_void<int(int, ...) const volatile && noexcept>();

    test_is_not_void<void (*)()>();
    test_is_not_void<void (*)() noexcept>();

    test_is_not_void<void (*)(int)>();
    test_is_not_void<void (*)(int) noexcept>();

    test_is_not_void<void (*)(...)>();
    test_is_not_void<void (*)(...) noexcept>();

    test_is_not_void<void (*)(int, ...)>();
    test_is_not_void<void (*)(int, ...) noexcept>();

    test_is_not_void<int (*)()>();
    test_is_not_void<int (*)() noexcept>();

    test_is_not_void<int (*)(int)>();
    test_is_not_void<int (*)(int) noexcept>();

    test_is_not_void<int (*)(...)>();
    test_is_not_void<int (*)(...) noexcept>();

    test_is_not_void<int (*)(int, ...)>();
    test_is_not_void<int (*)(int, ...) noexcept>();

    test_is_not_void<void (&)()>();
    test_is_not_void<void (&)() noexcept>();

    test_is_not_void<void (&)(int)>();
    test_is_not_void<void (&)(int) noexcept>();

    test_is_not_void<void (&)(...)>();
    test_is_not_void<void (&)(...) noexcept>();

    test_is_not_void<void (&)(int, ...)>();
    test_is_not_void<void (&)(int, ...) noexcept>();

    test_is_not_void<int (&)()>();
    test_is_not_void<int (&)() noexcept>();

    test_is_not_void<int (&)(int)>();
    test_is_not_void<int (&)(int) noexcept>();

    test_is_not_void<int (&)(...)>();
    test_is_not_void<int (&)(...) noexcept>();

    test_is_not_void<int (&)(int, ...)>();
    test_is_not_void<int (&)(int, ...) noexcept>();

    test_is_not_void<void (&&)()>();
    test_is_not_void<void (&&)() noexcept>();

    test_is_not_void<void (&&)(int)>();
    test_is_not_void<void (&&)(int) noexcept>();

    test_is_not_void<void (&&)(...)>();
    test_is_not_void<void (&&)(...) noexcept>();

    test_is_not_void<void (&&)(int, ...)>();
    test_is_not_void<void (&&)(int, ...) noexcept>();

    test_is_not_void<int (&&)()>();
    test_is_not_void<int (&&)() noexcept>();

    test_is_not_void<int (&&)(int)>();
    test_is_not_void<int (&&)(int) noexcept>();

    test_is_not_void<int (&&)(...)>();
    test_is_not_void<int (&&)(...) noexcept>();

    test_is_not_void<int (&&)(int, ...)>();
    test_is_not_void<int (&&)(int, ...) noexcept>();

    test_is_not_void<void (class_type::*)()>();
    test_is_not_void<void (class_type::*)()&>();
    test_is_not_void<void (class_type::*)() &&>();
    test_is_not_void<void (class_type::*)() const>();
    test_is_not_void<void (class_type::*)() const&>();
    test_is_not_void<void (class_type::*)() const&&>();
    test_is_not_void<void (class_type::*)() noexcept>();
    test_is_not_void<void (class_type::*)() & noexcept>();
    test_is_not_void<void (class_type::*)() && noexcept>();
    test_is_not_void<void (class_type::*)() const noexcept>();
    test_is_not_void<void (class_type::*)() const & noexcept>();
    test_is_not_void<void (class_type::*)() const && noexcept>();

    test_is_not_void<void (class_type::*)(int)>();
    test_is_not_void<void (class_type::*)(int)&>();
    test_is_not_void<void (class_type::*)(int) &&>();
    test_is_not_void<void (class_type::*)(int) const>();
    test_is_not_void<void (class_type::*)(int) const&>();
    test_is_not_void<void (class_type::*)(int) const&&>();
    test_is_not_void<void (class_type::*)(int) noexcept>();
    test_is_not_void<void (class_type::*)(int) & noexcept>();
    test_is_not_void<void (class_type::*)(int) && noexcept>();
    test_is_not_void<void (class_type::*)(int) const noexcept>();
    test_is_not_void<void (class_type::*)(int) const & noexcept>();
    test_is_not_void<void (class_type::*)(int) const && noexcept>();

    test_is_not_void<void (class_type::*)(...)>();
    test_is_not_void<void (class_type::*)(...)&>();
    test_is_not_void<void (class_type::*)(...) &&>();
    test_is_not_void<void (class_type::*)(...) const>();
    test_is_not_void<void (class_type::*)(...) const&>();
    test_is_not_void<void (class_type::*)(...) const&&>();
    test_is_not_void<void (class_type::*)(...) noexcept>();
    test_is_not_void<void (class_type::*)(...) & noexcept>();
    test_is_not_void<void (class_type::*)(...) && noexcept>();
    test_is_not_void<void (class_type::*)(...) const noexcept>();
    test_is_not_void<void (class_type::*)(...) const & noexcept>();
    test_is_not_void<void (class_type::*)(...) const && noexcept>();

    test_is_not_void<void (class_type::*)(int, ...)>();
    test_is_not_void<void (class_type::*)(int, ...)&>();
    test_is_not_void<void (class_type::*)(int, ...) &&>();
    test_is_not_void<void (class_type::*)(int, ...) const>();
    test_is_not_void<void (class_type::*)(int, ...) const&>();
    test_is_not_void<void (class_type::*)(int, ...) const&&>();
    test_is_not_void<void (class_type::*)(int, ...) noexcept>();
    test_is_not_void<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_void<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_void<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_void<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_void<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_void<int (class_type::*)()>();
    test_is_not_void<int (class_type::*)()&>();
    test_is_not_void<int (class_type::*)() &&>();
    test_is_not_void<int (class_type::*)() const>();
    test_is_not_void<int (class_type::*)() const&>();
    test_is_not_void<int (class_type::*)() const&&>();
    test_is_not_void<int (class_type::*)() noexcept>();
    test_is_not_void<int (class_type::*)() & noexcept>();
    test_is_not_void<int (class_type::*)() && noexcept>();
    test_is_not_void<int (class_type::*)() const noexcept>();
    test_is_not_void<int (class_type::*)() const & noexcept>();
    test_is_not_void<int (class_type::*)() const && noexcept>();

    test_is_not_void<int (class_type::*)(int)>();
    test_is_not_void<int (class_type::*)(int)&>();
    test_is_not_void<int (class_type::*)(int) &&>();
    test_is_not_void<int (class_type::*)(int) const>();
    test_is_not_void<int (class_type::*)(int) const&>();
    test_is_not_void<int (class_type::*)(int) const&&>();
    test_is_not_void<int (class_type::*)(int) noexcept>();
    test_is_not_void<int (class_type::*)(int) & noexcept>();
    test_is_not_void<int (class_type::*)(int) && noexcept>();
    test_is_not_void<int (class_type::*)(int) const noexcept>();
    test_is_not_void<int (class_type::*)(int) const & noexcept>();
    test_is_not_void<int (class_type::*)(int) const && noexcept>();

    test_is_not_void<int (class_type::*)(...)>();
    test_is_not_void<int (class_type::*)(...)&>();
    test_is_not_void<int (class_type::*)(...) &&>();
    test_is_not_void<int (class_type::*)(...) const>();
    test_is_not_void<int (class_type::*)(...) const&>();
    test_is_not_void<int (class_type::*)(...) const&&>();
    test_is_not_void<int (class_type::*)(...) noexcept>();
    test_is_not_void<int (class_type::*)(...) & noexcept>();
    test_is_not_void<int (class_type::*)(...) && noexcept>();
    test_is_not_void<int (class_type::*)(...) const noexcept>();
    test_is_not_void<int (class_type::*)(...) const & noexcept>();
    test_is_not_void<int (class_type::*)(...) const && noexcept>();

    test_is_not_void<int (class_type::*)(int, ...)>();
    test_is_not_void<int (class_type::*)(int, ...)&>();
    test_is_not_void<int (class_type::*)(int, ...) &&>();
    test_is_not_void<int (class_type::*)(int, ...) const>();
    test_is_not_void<int (class_type::*)(int, ...) const&>();
    test_is_not_void<int (class_type::*)(int, ...) const&&>();
    test_is_not_void<int (class_type::*)(int, ...) noexcept>();
    test_is_not_void<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_void<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_void<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_void<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_void<int (class_type::*)(int, ...) const && noexcept>();
}
