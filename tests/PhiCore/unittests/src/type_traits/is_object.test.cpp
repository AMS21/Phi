#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_function.hpp>
#include <phi/type_traits/is_lvalue_reference.hpp>
#include <phi/type_traits/is_object.hpp>
#include <phi/type_traits/is_reference.hpp>
#include <phi/type_traits/is_rvalue_reference.hpp>
#include <phi/type_traits/is_void.hpp>

PHI_EXTERNAL_HEADERS_BEGIN()
#include <type_traits>
#include <vector>
PHI_EXTERNAL_HEADERS_END()

template <typename TypeT>
void test_is_object_impl()
{
#if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE(phi::is_object<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_object<TypeT>::value);

    STATIC_REQUIRE_FALSE(phi::is_function<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_void<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_object_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_object_v<TypeT>);

    STATIC_REQUIRE_FALSE(phi::is_function_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_void_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_object<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_object<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_object<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_not_object_impl()
{
#if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE_FALSE(phi::is_object<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_object<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_object_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_object_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_object<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_object<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_object<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_object()
{
    test_is_object_impl<TypeT>();
    test_is_object_impl<const TypeT>();
    test_is_object_impl<volatile TypeT>();
    test_is_object_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_object()
{
    test_is_not_object_impl<TypeT>();
    test_is_not_object_impl<const TypeT>();
    test_is_not_object_impl<volatile TypeT>();
    test_is_not_object_impl<const volatile TypeT>();
}

TEST_CASE("is_object")
{
    test_is_not_object<void>();
    test_is_object<phi::nullptr_t>();
    test_is_object<bool>();
    test_is_object<char>();
    test_is_object<signed char>();
    test_is_object<unsigned char>();
    test_is_object<short>();
    test_is_object<unsigned short>();
    test_is_object<int>();
    test_is_object<unsigned int>();
    test_is_object<long>();
    test_is_object<unsigned long>();
    test_is_object<long long>();
    test_is_object<unsigned long long>();
    test_is_object<float>();
    test_is_object<double>();
    test_is_object<long double>();
    test_is_object<char8_t>();
    test_is_object<char16_t>();
    test_is_object<char32_t>();
    test_is_object<wchar_t>();

    test_is_object<phi::boolean>();
    test_is_object<phi::integer<signed char>>();
    test_is_object<phi::integer<unsigned char>>();
    test_is_object<phi::integer<short>>();
    test_is_object<phi::integer<unsigned short>>();
    test_is_object<phi::integer<int>>();
    test_is_object<phi::integer<unsigned int>>();
    test_is_object<phi::integer<long>>();
    test_is_object<phi::integer<unsigned long>>();
    test_is_object<phi::integer<long long>>();
    test_is_object<phi::integer<unsigned long long>>();
    test_is_object<phi::floating_point<float>>();
    test_is_object<phi::floating_point<double>>();
    test_is_object<phi::floating_point<long double>>();

    test_is_object<std::vector<int>>();
    test_is_object<phi::scope_ptr<int>>();

    test_is_not_object<int&>();
    test_is_not_object<const int&>();
    test_is_not_object<volatile int&>();
    test_is_not_object<const volatile int&>();
    test_is_not_object<int&&>();
    test_is_not_object<const int&&>();
    test_is_not_object<volatile int&&>();
    test_is_not_object<const volatile int&&>();
    test_is_object<int*>();
    test_is_object<const int*>();
    test_is_object<volatile int*>();
    test_is_object<const volatile int*>();
    test_is_object<int**>();
    test_is_object<const int**>();
    test_is_object<volatile int**>();
    test_is_object<const volatile int**>();
    test_is_not_object<int*&>();
    test_is_not_object<const int*&>();
    test_is_not_object<volatile int*&>();
    test_is_not_object<const volatile int*&>();
    test_is_not_object<int*&&>();
    test_is_not_object<const int*&&>();
    test_is_not_object<volatile int*&&>();
    test_is_not_object<const volatile int*&&>();
    test_is_object<void*>();
    test_is_object<char[3]>();
    test_is_object<char[]>();
    test_is_object<char* [3]>();
    test_is_object<char*[]>();
    test_is_object<int(*)[3]>();
    test_is_object<int(*)[]>();
    test_is_not_object<int(&)[3]>();
    test_is_not_object<int(&)[]>();
    test_is_not_object<int(&&)[3]>();
    test_is_not_object<int(&&)[]>();
    test_is_object<char[3][2]>();
    test_is_object<char[][2]>();
    test_is_object<char* [3][2]>();
    test_is_object<char*[][2]>();
    test_is_object<int(*)[3][2]>();
    test_is_object<int(*)[][2]>();
    test_is_not_object<int(&)[3][2]>();
    test_is_not_object<int(&)[][2]>();
    test_is_not_object<int(&&)[3][2]>();
    test_is_not_object<int(&&)[][2]>();
    test_is_object<class_type>();
    test_is_object<class_type[]>();
    test_is_object<class_type[2]>();
    test_is_object<template_type<void>>();
    test_is_object<template_type<int>>();
    test_is_object<template_type<class_type>>();
    test_is_object<template_type<incomplete_type>>();
    test_is_object<variadic_template<>>();
    test_is_object<variadic_template<void>>();
    test_is_object<variadic_template<int>>();
    test_is_object<variadic_template<class_type>>();
    test_is_object<variadic_template<incomplete_type>>();
    test_is_object<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_object<public_derived_from<base>>();
    test_is_object<public_derived_from<derived>>();
    test_is_object<public_derived_from<class_type>>();
    test_is_object<private_derived_from<base>>();
    test_is_object<private_derived_from<derived>>();
    test_is_object<private_derived_from<class_type>>();
    test_is_object<protected_derived_from<base>>();
    test_is_object<protected_derived_from<derived>>();
    test_is_object<protected_derived_from<class_type>>();
    test_is_object<virtual_derived_from<base>>();
    test_is_object<virtual_derived_from<derived>>();
    test_is_object<virtual_derived_from<class_type>>();
    test_is_object<union_type>();
    test_is_object<non_empty_union>();
    test_is_object<non_trivial_union>();
    test_is_object<empty>();
    test_is_object<not_empty>();
    test_is_object<non_trivial>();
    test_is_object<bit_zero>();
    test_is_object<bit_one>();
    test_is_object<base>();
    test_is_object<derived>();
    test_is_object<non_empty_base>();
    test_is_object<empty_base>();
    test_is_object<virtual_base>();
    test_is_object<polymorphic>();
    test_is_object<derived_polymorphic>();
    test_is_object<abstract>();
    test_is_object<public_abstract>();
    test_is_object<private_abstract>();
    test_is_object<protected_abstract>();
    test_is_object<abstract_template<int>>();
    test_is_object<abstract_template<double>>();
    test_is_object<abstract_template<class_type>>();
    test_is_object<abstract_template<incomplete_type>>();
    test_is_object<public_abstract_deleted_destructor>();
    test_is_object<protected_abstract_deleted_destructor>();
    test_is_object<private_abstract_deleted_destructor>();
    test_is_object<final_type>();
    test_is_object<final_derived>();
    test_is_object<public_destructor>();
    test_is_object<protected_destructor>();
    test_is_object<private_destructor>();
    test_is_object<virtual_public_destructor>();
    test_is_object<virtual_protected_destructor>();
    test_is_object<virtual_private_destructor>();
    test_is_object<pure_public_destructor>();
    test_is_object<pure_protected_destructor>();
    test_is_object<pure_private_destructor>();
    test_is_object<deleted_public_destructor>();
    test_is_object<deleted_protected_destructor>();
    test_is_object<deleted_private_destructor>();
    test_is_object<deleted_virtual_public_destructor>();
    test_is_object<deleted_virtual_protected_destructor>();
    test_is_object<deleted_virtual_private_destructor>();
    test_is_object<explicit_class>();
    test_is_object<nothrow_explicit_class>();
    test_is_object<throw_explicit_class>();
    test_is_object<throw_default_class>();
    test_is_object<throw_copy_constructible_class>();
    test_is_object<throw_move_constructible_class>();
    test_is_object<throw_destructor>();
    test_is_object<noexcept_explicit_class>();
    test_is_object<except_explicit_class>();
    test_is_object<noexcept_default_class>();
    test_is_object<except_default_class>();
    test_is_object<noexcept_copy_constructible_class>();
    test_is_object<except_copy_constructible_class>();
    test_is_object<noexcept_move_constructible_class>();
    test_is_object<except_move_constructible_class>();
    test_is_object<noexcept_copy_assign_class>();
    test_is_object<except_copy_assign_class>();
    test_is_object<noexcept_move_assign_class>();
    test_is_object<except_move_assign_class>();
    test_is_object<deleted_copy_assign_class>();
    test_is_object<deleted_move_assign_class>();
    test_is_object<noexcept_move_constructible_and_assignable_class>();
    test_is_object<except_move_constructible_noexcept_move_assign_class>();
    test_is_object<noexcept_move_constructible_except_move_assign_class>();
    test_is_object<except_move_constructible_and_assign_class>();
    test_is_object<implicit_to<int>>();
    test_is_object<implicit_to<float>>();
    test_is_object<implicit_to<class_type>>();
    test_is_object<deleted_implicit_to<int>>();
    test_is_object<deleted_implicit_to<float>>();
    test_is_object<deleted_implicit_to<class_type>>();
    test_is_object<explicit_to<int>>();
    test_is_object<explicit_to<float>>();
    test_is_object<explicit_to<class_type>>();
    test_is_object<deleted_explicit_to<int>>();
    test_is_object<deleted_explicit_to<float>>();
    test_is_object<deleted_explicit_to<class_type>>();
    test_is_object<ellipsis>();
    test_is_object<deleted_ellipsis>();
    test_is_object<copy_constructible_only_type>();
    test_is_object<move_constructible_only_type>();
    test_is_object<overloaded_operators>();
    test_is_object<public_int_member>();
    test_is_object<protected_int_member>();
    test_is_object<private_int_member>();
    test_is_object<public_static_int_member>();
    test_is_object<protected_static_int_member>();
    test_is_object<private_static_int_member>();
    test_is_object<public_template_member<int>>();
    test_is_object<public_template_member<float>>();
    test_is_object<public_template_member<class_type>>();
    test_is_object<protected_template_member<int>>();
    test_is_object<protected_template_member<float>>();
    test_is_object<protected_template_member<class_type>>();
    test_is_object<private_template_member<int>>();
    test_is_object<private_template_member<float>>();
    test_is_object<private_template_member<class_type>>();
    test_is_object<public_static_template_member<int>>();
    test_is_object<public_static_template_member<float>>();
    test_is_object<public_static_template_member<class_type>>();
    test_is_object<protected_static_template_member<int>>();
    test_is_object<protected_static_template_member<float>>();
    test_is_object<protected_static_template_member<class_type>>();
    test_is_object<private_static_template_member<int>>();
    test_is_object<private_static_template_member<float>>();
    test_is_object<private_static_template_member<class_type>>();
    test_is_object<cannot_instantiate<int>>();
    test_is_object<cannot_instantiate<float>>();
    test_is_object<cannot_instantiate<class_type>>();
    test_is_object<natural_alignment>();
    test_is_object<Enum>();
    test_is_object<EnumSigned>();
    test_is_object<EnumUnsigned>();
    test_is_object<EnumClass>();
    test_is_object<EnumStruct>();
    test_is_not_object<function_type>();
    test_is_object<function_ptr>();
    test_is_object<member_object_ptr>();
    test_is_object<member_function_ptr>();
    test_is_object<lambda_type>();
    test_is_object<lambda_noexcept_type>();
    test_is_object<lambda_throws_type>();
    test_is_object<incomplete_type>();
    test_is_object<incomplete_template<void>>();
    test_is_object<incomplete_template<int>>();
    test_is_object<incomplete_template<class_type>>();
    test_is_object<incomplete_template<incomplete_type>>();
    test_is_object<incomplete_variadic_template<>>();
    test_is_object<incomplete_variadic_template<void>>();
    test_is_object<incomplete_variadic_template<int>>();
    test_is_object<incomplete_variadic_template<class_type>>();
    test_is_object<incomplete_variadic_template<incomplete_type>>();
    test_is_object<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_object<incomplete_union>();
    test_is_object<IncompleteEnumSigned>();
    test_is_object<IncompleteEnumUnsigned>();
    test_is_object<IncompleteEnumClass>();
    test_is_object<IncompleteEnumStruct>();
    test_is_object<int class_type::*>();
    test_is_object<float class_type::*>();
    test_is_object<void * class_type::*>();
    test_is_object<int * class_type::*>();
    test_is_object<Enum class_type::*>();
    test_is_object<not_empty class_type::*>();
    test_is_not_object<int class_type::*&>();
    test_is_not_object<float class_type::*&>();
    test_is_not_object<void * class_type::*&>();
    test_is_not_object<int * class_type::*&>();
    test_is_not_object<Enum class_type::*&>();
    test_is_not_object<not_empty class_type::*&>();
    test_is_not_object<int class_type::*&&>();
    test_is_not_object<float class_type::*&&>();
    test_is_not_object<void * class_type::*&&>();
    test_is_not_object<int * class_type::*&&>();
    test_is_not_object<Enum class_type::*&&>();
    test_is_not_object<not_empty class_type::*&&>();
    test_is_object<non_default_constructible>();
    test_is_object<non_copy_constructible>();
    test_is_object<non_move_constructible>();
    test_is_object<non_copy_assignable>();
    test_is_object<non_move_assignable>();
    test_is_object<non_assignable>();
    test_is_object<non_copyable>();
    test_is_object<non_moveable>();
    test_is_object<non_constructible>();
    test_is_object<non_destructible>();
    test_is_object<tracked>();
    test_is_object<trap_constructible>();
    test_is_object<trap_implicit_conversion>();
    test_is_object<trap_comma>();
    test_is_object<trap_call>();
    test_is_object<trap_self_assign>();
    test_is_object<trap_deref>();
    test_is_object<trap_array_subscript>();

    test_is_not_object<void()>();
    test_is_not_object<void()&>();
    test_is_not_object<void() &&>();
    test_is_not_object<void() const>();
    test_is_not_object<void() const&>();
    test_is_not_object<void() const&&>();
    test_is_not_object<void() volatile>();
    test_is_not_object<void() volatile&>();
    test_is_not_object<void() volatile&&>();
    test_is_not_object<void() const volatile>();
    test_is_not_object<void() const volatile&>();
    test_is_not_object<void() const volatile&&>();
    test_is_not_object<void() noexcept>();
    test_is_not_object<void() & noexcept>();
    test_is_not_object<void() && noexcept>();
    test_is_not_object<void() const noexcept>();
    test_is_not_object<void() const & noexcept>();
    test_is_not_object<void() const && noexcept>();
    test_is_not_object<void() volatile noexcept>();
    test_is_not_object<void() volatile & noexcept>();
    test_is_not_object<void() volatile && noexcept>();
    test_is_not_object<void() const volatile noexcept>();
    test_is_not_object<void() const volatile & noexcept>();
    test_is_not_object<void() const volatile && noexcept>();

    test_is_not_object<void(int)>();
    test_is_not_object<void(int)&>();
    test_is_not_object<void(int) &&>();
    test_is_not_object<void(int) const>();
    test_is_not_object<void(int) const&>();
    test_is_not_object<void(int) const&&>();
    test_is_not_object<void(int) volatile>();
    test_is_not_object<void(int) volatile&>();
    test_is_not_object<void(int) volatile&&>();
    test_is_not_object<void(int) const volatile>();
    test_is_not_object<void(int) const volatile&>();
    test_is_not_object<void(int) const volatile&&>();
    test_is_not_object<void(int) noexcept>();
    test_is_not_object<void(int) & noexcept>();
    test_is_not_object<void(int) && noexcept>();
    test_is_not_object<void(int) const noexcept>();
    test_is_not_object<void(int) const & noexcept>();
    test_is_not_object<void(int) const && noexcept>();
    test_is_not_object<void(int) volatile noexcept>();
    test_is_not_object<void(int) volatile & noexcept>();
    test_is_not_object<void(int) volatile && noexcept>();
    test_is_not_object<void(int) const volatile noexcept>();
    test_is_not_object<void(int) const volatile & noexcept>();
    test_is_not_object<void(int) const volatile && noexcept>();

    test_is_not_object<void(...)>();
    test_is_not_object<void(...)&>();
    test_is_not_object<void(...) &&>();
    test_is_not_object<void(...) const>();
    test_is_not_object<void(...) const&>();
    test_is_not_object<void(...) const&&>();
    test_is_not_object<void(...) volatile>();
    test_is_not_object<void(...) volatile&>();
    test_is_not_object<void(...) volatile&&>();
    test_is_not_object<void(...) const volatile>();
    test_is_not_object<void(...) const volatile&>();
    test_is_not_object<void(...) const volatile&&>();
    test_is_not_object<void(...) noexcept>();
    test_is_not_object<void(...) & noexcept>();
    test_is_not_object<void(...) && noexcept>();
    test_is_not_object<void(...) const noexcept>();
    test_is_not_object<void(...) const & noexcept>();
    test_is_not_object<void(...) const && noexcept>();
    test_is_not_object<void(...) volatile noexcept>();
    test_is_not_object<void(...) volatile & noexcept>();
    test_is_not_object<void(...) volatile && noexcept>();
    test_is_not_object<void(...) const volatile noexcept>();
    test_is_not_object<void(...) const volatile & noexcept>();
    test_is_not_object<void(...) const volatile && noexcept>();

    test_is_not_object<void(int, ...)>();
    test_is_not_object<void(int, ...)&>();
    test_is_not_object<void(int, ...) &&>();
    test_is_not_object<void(int, ...) const>();
    test_is_not_object<void(int, ...) const&>();
    test_is_not_object<void(int, ...) const&&>();
    test_is_not_object<void(int, ...) volatile>();
    test_is_not_object<void(int, ...) volatile&>();
    test_is_not_object<void(int, ...) volatile&&>();
    test_is_not_object<void(int, ...) const volatile>();
    test_is_not_object<void(int, ...) const volatile&>();
    test_is_not_object<void(int, ...) const volatile&&>();
    test_is_not_object<void(int, ...) noexcept>();
    test_is_not_object<void(int, ...) & noexcept>();
    test_is_not_object<void(int, ...) && noexcept>();
    test_is_not_object<void(int, ...) const noexcept>();
    test_is_not_object<void(int, ...) const & noexcept>();
    test_is_not_object<void(int, ...) const && noexcept>();
    test_is_not_object<void(int, ...) volatile noexcept>();
    test_is_not_object<void(int, ...) volatile & noexcept>();
    test_is_not_object<void(int, ...) volatile && noexcept>();
    test_is_not_object<void(int, ...) const volatile noexcept>();
    test_is_not_object<void(int, ...) const volatile & noexcept>();
    test_is_not_object<void(int, ...) const volatile && noexcept>();

    test_is_not_object<int()>();
    test_is_not_object<int()&>();
    test_is_not_object<int() &&>();
    test_is_not_object<int() const>();
    test_is_not_object<int() const&>();
    test_is_not_object<int() const&&>();
    test_is_not_object<int() volatile>();
    test_is_not_object<int() volatile&>();
    test_is_not_object<int() volatile&&>();
    test_is_not_object<int() const volatile>();
    test_is_not_object<int() const volatile&>();
    test_is_not_object<int() const volatile&&>();
    test_is_not_object<int() noexcept>();
    test_is_not_object<int() & noexcept>();
    test_is_not_object<int() && noexcept>();
    test_is_not_object<int() const noexcept>();
    test_is_not_object<int() const & noexcept>();
    test_is_not_object<int() const && noexcept>();
    test_is_not_object<int() volatile noexcept>();
    test_is_not_object<int() volatile & noexcept>();
    test_is_not_object<int() volatile && noexcept>();
    test_is_not_object<int() const volatile noexcept>();
    test_is_not_object<int() const volatile & noexcept>();
    test_is_not_object<int() const volatile && noexcept>();

    test_is_not_object<int(int)>();
    test_is_not_object<int(int)&>();
    test_is_not_object<int(int) &&>();
    test_is_not_object<int(int) const>();
    test_is_not_object<int(int) const&>();
    test_is_not_object<int(int) const&&>();
    test_is_not_object<int(int) volatile>();
    test_is_not_object<int(int) volatile&>();
    test_is_not_object<int(int) volatile&&>();
    test_is_not_object<int(int) const volatile>();
    test_is_not_object<int(int) const volatile&>();
    test_is_not_object<int(int) const volatile&&>();
    test_is_not_object<int(int) noexcept>();
    test_is_not_object<int(int) & noexcept>();
    test_is_not_object<int(int) && noexcept>();
    test_is_not_object<int(int) const noexcept>();
    test_is_not_object<int(int) const & noexcept>();
    test_is_not_object<int(int) const && noexcept>();
    test_is_not_object<int(int) volatile noexcept>();
    test_is_not_object<int(int) volatile & noexcept>();
    test_is_not_object<int(int) volatile && noexcept>();
    test_is_not_object<int(int) const volatile noexcept>();
    test_is_not_object<int(int) const volatile & noexcept>();
    test_is_not_object<int(int) const volatile && noexcept>();

    test_is_not_object<int(...)>();
    test_is_not_object<int(...)&>();
    test_is_not_object<int(...) &&>();
    test_is_not_object<int(...) const>();
    test_is_not_object<int(...) const&>();
    test_is_not_object<int(...) const&&>();
    test_is_not_object<int(...) volatile>();
    test_is_not_object<int(...) volatile&>();
    test_is_not_object<int(...) volatile&&>();
    test_is_not_object<int(...) const volatile>();
    test_is_not_object<int(...) const volatile&>();
    test_is_not_object<int(...) const volatile&&>();
    test_is_not_object<int(...) noexcept>();
    test_is_not_object<int(...) & noexcept>();
    test_is_not_object<int(...) && noexcept>();
    test_is_not_object<int(...) const noexcept>();
    test_is_not_object<int(...) const & noexcept>();
    test_is_not_object<int(...) const && noexcept>();
    test_is_not_object<int(...) volatile noexcept>();
    test_is_not_object<int(...) volatile & noexcept>();
    test_is_not_object<int(...) volatile && noexcept>();
    test_is_not_object<int(...) const volatile noexcept>();
    test_is_not_object<int(...) const volatile & noexcept>();
    test_is_not_object<int(...) const volatile && noexcept>();

    test_is_not_object<int(int, ...)>();
    test_is_not_object<int(int, ...)&>();
    test_is_not_object<int(int, ...) &&>();
    test_is_not_object<int(int, ...) const>();
    test_is_not_object<int(int, ...) const&>();
    test_is_not_object<int(int, ...) const&&>();
    test_is_not_object<int(int, ...) volatile>();
    test_is_not_object<int(int, ...) volatile&>();
    test_is_not_object<int(int, ...) volatile&&>();
    test_is_not_object<int(int, ...) const volatile>();
    test_is_not_object<int(int, ...) const volatile&>();
    test_is_not_object<int(int, ...) const volatile&&>();
    test_is_not_object<int(int, ...) noexcept>();
    test_is_not_object<int(int, ...) & noexcept>();
    test_is_not_object<int(int, ...) && noexcept>();
    test_is_not_object<int(int, ...) const noexcept>();
    test_is_not_object<int(int, ...) const & noexcept>();
    test_is_not_object<int(int, ...) const && noexcept>();
    test_is_not_object<int(int, ...) volatile noexcept>();
    test_is_not_object<int(int, ...) volatile & noexcept>();
    test_is_not_object<int(int, ...) volatile && noexcept>();
    test_is_not_object<int(int, ...) const volatile noexcept>();
    test_is_not_object<int(int, ...) const volatile & noexcept>();
    test_is_not_object<int(int, ...) const volatile && noexcept>();

    test_is_object<void (*)()>();
    test_is_object<void (*)() noexcept>();

    test_is_object<void (*)(int)>();
    test_is_object<void (*)(int) noexcept>();

    test_is_object<void (*)(...)>();
    test_is_object<void (*)(...) noexcept>();

    test_is_object<void (*)(int, ...)>();
    test_is_object<void (*)(int, ...) noexcept>();

    test_is_object<int (*)()>();
    test_is_object<int (*)() noexcept>();

    test_is_object<int (*)(int)>();
    test_is_object<int (*)(int) noexcept>();

    test_is_object<int (*)(...)>();
    test_is_object<int (*)(...) noexcept>();

    test_is_object<int (*)(int, ...)>();
    test_is_object<int (*)(int, ...) noexcept>();

    test_is_not_object<void (&)()>();
    test_is_not_object<void (&)() noexcept>();

    test_is_not_object<void (&)(int)>();
    test_is_not_object<void (&)(int) noexcept>();

    test_is_not_object<void (&)(...)>();
    test_is_not_object<void (&)(...) noexcept>();

    test_is_not_object<void (&)(int, ...)>();
    test_is_not_object<void (&)(int, ...) noexcept>();

    test_is_not_object<int (&)()>();
    test_is_not_object<int (&)() noexcept>();

    test_is_not_object<int (&)(int)>();
    test_is_not_object<int (&)(int) noexcept>();

    test_is_not_object<int (&)(...)>();
    test_is_not_object<int (&)(...) noexcept>();

    test_is_not_object<int (&)(int, ...)>();
    test_is_not_object<int (&)(int, ...) noexcept>();

    test_is_not_object<void (&&)()>();
    test_is_not_object<void (&&)() noexcept>();

    test_is_not_object<void (&&)(int)>();
    test_is_not_object<void (&&)(int) noexcept>();

    test_is_not_object<void (&&)(...)>();
    test_is_not_object<void (&&)(...) noexcept>();

    test_is_not_object<void (&&)(int, ...)>();
    test_is_not_object<void (&&)(int, ...) noexcept>();

    test_is_not_object<int (&&)()>();
    test_is_not_object<int (&&)() noexcept>();

    test_is_not_object<int (&&)(int)>();
    test_is_not_object<int (&&)(int) noexcept>();

    test_is_not_object<int (&&)(...)>();
    test_is_not_object<int (&&)(...) noexcept>();

    test_is_not_object<int (&&)(int, ...)>();
    test_is_not_object<int (&&)(int, ...) noexcept>();

    test_is_object<void (class_type::*)()>();
    test_is_object<void (class_type::*)()&>();
    test_is_object<void (class_type::*)() &&>();
    test_is_object<void (class_type::*)() const>();
    test_is_object<void (class_type::*)() const&>();
    test_is_object<void (class_type::*)() const&&>();
    test_is_object<void (class_type::*)() noexcept>();
    test_is_object<void (class_type::*)() & noexcept>();
    test_is_object<void (class_type::*)() && noexcept>();
    test_is_object<void (class_type::*)() const noexcept>();
    test_is_object<void (class_type::*)() const & noexcept>();
    test_is_object<void (class_type::*)() const && noexcept>();

    test_is_object<void (class_type::*)(int)>();
    test_is_object<void (class_type::*)(int)&>();
    test_is_object<void (class_type::*)(int) &&>();
    test_is_object<void (class_type::*)(int) const>();
    test_is_object<void (class_type::*)(int) const&>();
    test_is_object<void (class_type::*)(int) const&&>();
    test_is_object<void (class_type::*)(int) noexcept>();
    test_is_object<void (class_type::*)(int) & noexcept>();
    test_is_object<void (class_type::*)(int) && noexcept>();
    test_is_object<void (class_type::*)(int) const noexcept>();
    test_is_object<void (class_type::*)(int) const & noexcept>();
    test_is_object<void (class_type::*)(int) const && noexcept>();

    test_is_object<void (class_type::*)(...)>();
    test_is_object<void (class_type::*)(...)&>();
    test_is_object<void (class_type::*)(...) &&>();
    test_is_object<void (class_type::*)(...) const>();
    test_is_object<void (class_type::*)(...) const&>();
    test_is_object<void (class_type::*)(...) const&&>();
    test_is_object<void (class_type::*)(...) noexcept>();
    test_is_object<void (class_type::*)(...) & noexcept>();
    test_is_object<void (class_type::*)(...) && noexcept>();
    test_is_object<void (class_type::*)(...) const noexcept>();
    test_is_object<void (class_type::*)(...) const & noexcept>();
    test_is_object<void (class_type::*)(...) const && noexcept>();

    test_is_object<void (class_type::*)(int, ...)>();
    test_is_object<void (class_type::*)(int, ...)&>();
    test_is_object<void (class_type::*)(int, ...) &&>();
    test_is_object<void (class_type::*)(int, ...) const>();
    test_is_object<void (class_type::*)(int, ...) const&>();
    test_is_object<void (class_type::*)(int, ...) const&&>();
    test_is_object<void (class_type::*)(int, ...) noexcept>();
    test_is_object<void (class_type::*)(int, ...) & noexcept>();
    test_is_object<void (class_type::*)(int, ...) && noexcept>();
    test_is_object<void (class_type::*)(int, ...) const noexcept>();
    test_is_object<void (class_type::*)(int, ...) const & noexcept>();
    test_is_object<void (class_type::*)(int, ...) const && noexcept>();

    test_is_object<int (class_type::*)()>();
    test_is_object<int (class_type::*)()&>();
    test_is_object<int (class_type::*)() &&>();
    test_is_object<int (class_type::*)() const>();
    test_is_object<int (class_type::*)() const&>();
    test_is_object<int (class_type::*)() const&&>();
    test_is_object<int (class_type::*)() noexcept>();
    test_is_object<int (class_type::*)() & noexcept>();
    test_is_object<int (class_type::*)() && noexcept>();
    test_is_object<int (class_type::*)() const noexcept>();
    test_is_object<int (class_type::*)() const & noexcept>();
    test_is_object<int (class_type::*)() const && noexcept>();

    test_is_object<int (class_type::*)(int)>();
    test_is_object<int (class_type::*)(int)&>();
    test_is_object<int (class_type::*)(int) &&>();
    test_is_object<int (class_type::*)(int) const>();
    test_is_object<int (class_type::*)(int) const&>();
    test_is_object<int (class_type::*)(int) const&&>();
    test_is_object<int (class_type::*)(int) noexcept>();
    test_is_object<int (class_type::*)(int) & noexcept>();
    test_is_object<int (class_type::*)(int) && noexcept>();
    test_is_object<int (class_type::*)(int) const noexcept>();
    test_is_object<int (class_type::*)(int) const & noexcept>();
    test_is_object<int (class_type::*)(int) const && noexcept>();

    test_is_object<int (class_type::*)(...)>();
    test_is_object<int (class_type::*)(...)&>();
    test_is_object<int (class_type::*)(...) &&>();
    test_is_object<int (class_type::*)(...) const>();
    test_is_object<int (class_type::*)(...) const&>();
    test_is_object<int (class_type::*)(...) const&&>();
    test_is_object<int (class_type::*)(...) noexcept>();
    test_is_object<int (class_type::*)(...) & noexcept>();
    test_is_object<int (class_type::*)(...) && noexcept>();
    test_is_object<int (class_type::*)(...) const noexcept>();
    test_is_object<int (class_type::*)(...) const & noexcept>();
    test_is_object<int (class_type::*)(...) const && noexcept>();

    test_is_object<int (class_type::*)(int, ...)>();
    test_is_object<int (class_type::*)(int, ...)&>();
    test_is_object<int (class_type::*)(int, ...) &&>();
    test_is_object<int (class_type::*)(int, ...) const>();
    test_is_object<int (class_type::*)(int, ...) const&>();
    test_is_object<int (class_type::*)(int, ...) const&&>();
    test_is_object<int (class_type::*)(int, ...) noexcept>();
    test_is_object<int (class_type::*)(int, ...) & noexcept>();
    test_is_object<int (class_type::*)(int, ...) && noexcept>();
    test_is_object<int (class_type::*)(int, ...) const noexcept>();
    test_is_object<int (class_type::*)(int, ...) const & noexcept>();
    test_is_object<int (class_type::*)(int, ...) const && noexcept>();
}
