#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/extensions/zero_size_array.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/has_element_type.hpp>
#include <vector>

template <typename TypeT>
void test_has_element_type_impl()
{
    STATIC_REQUIRE(phi::has_element_type<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::has_no_element_type<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::has_element_type_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::has_no_element_type_v<TypeT>);
#endif
}

template <typename TypeT>
void test_has_no_element_type_impl()
{
    STATIC_REQUIRE_FALSE(phi::has_element_type<TypeT>::value);
    STATIC_REQUIRE(phi::has_no_element_type<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::has_element_type_v<TypeT>);
    STATIC_REQUIRE(phi::has_no_element_type_v<TypeT>);
#endif
}

template <typename TypeT>
void test_has_element_type()
{
    test_has_element_type_impl<TypeT>();
    test_has_element_type_impl<const TypeT>();
    test_has_element_type_impl<volatile TypeT>();
    test_has_element_type_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_has_no_element_type()
{
    test_has_no_element_type_impl<TypeT>();
    test_has_no_element_type_impl<const TypeT>();
    test_has_no_element_type_impl<volatile TypeT>();
    test_has_no_element_type_impl<const volatile TypeT>();
}

struct type_with_element_type
{
    using element_type = int;
};

template <typename TypeT>
struct template_type_with_element_type
{
    using element_type = TypeT;
};

TEST_CASE("type_traits.has_element_type")
{
    test_has_element_type<type_with_element_type>();
    test_has_element_type<template_type_with_element_type<int>>();
    test_has_element_type<template_type_with_element_type<float>>();
    test_has_element_type<template_type_with_element_type<char>>();

    test_has_no_element_type<void>();
    test_has_no_element_type<phi::nullptr_t>();
    test_has_no_element_type<bool>();
    test_has_no_element_type<char>();
    test_has_no_element_type<signed char>();
    test_has_no_element_type<unsigned char>();
    test_has_no_element_type<short>();
    test_has_no_element_type<unsigned short>();
    test_has_no_element_type<int>();
    test_has_no_element_type<unsigned int>();
    test_has_no_element_type<long>();
    test_has_no_element_type<unsigned long>();
    test_has_no_element_type<long long>();
    test_has_no_element_type<unsigned long long>();
    test_has_no_element_type<float>();
    test_has_no_element_type<double>();
    test_has_no_element_type<long double>();
    test_has_no_element_type<char8_t>();
    test_has_no_element_type<char16_t>();
    test_has_no_element_type<char32_t>();
    test_has_no_element_type<wchar_t>();

    test_has_no_element_type<phi::boolean>();
    test_has_no_element_type<phi::integer<signed char>>();
    test_has_no_element_type<phi::integer<unsigned char>>();
    test_has_no_element_type<phi::integer<short>>();
    test_has_no_element_type<phi::integer<unsigned short>>();
    test_has_no_element_type<phi::integer<int>>();
    test_has_no_element_type<phi::integer<unsigned int>>();
    test_has_no_element_type<phi::integer<long>>();
    test_has_no_element_type<phi::integer<unsigned long>>();
    test_has_no_element_type<phi::integer<long long>>();
    test_has_no_element_type<phi::integer<unsigned long long>>();
    test_has_no_element_type<phi::floating_point<float>>();
    test_has_no_element_type<phi::floating_point<double>>();
    test_has_no_element_type<phi::floating_point<long double>>();

    test_has_no_element_type<std::vector<int>>();
    test_has_no_element_type<phi::scope_ptr<int>>();

    test_has_no_element_type<int&>();
    test_has_no_element_type<const int&>();
    test_has_no_element_type<volatile int&>();
    test_has_no_element_type<const volatile int&>();
    test_has_no_element_type<int&&>();
    test_has_no_element_type<const int&&>();
    test_has_no_element_type<volatile int&&>();
    test_has_no_element_type<const volatile int&&>();
    test_has_no_element_type<int*>();
    test_has_no_element_type<const int*>();
    test_has_no_element_type<volatile int*>();
    test_has_no_element_type<const volatile int*>();
    test_has_no_element_type<int**>();
    test_has_no_element_type<const int**>();
    test_has_no_element_type<volatile int**>();
    test_has_no_element_type<const volatile int**>();
    test_has_no_element_type<int*&>();
    test_has_no_element_type<const int*&>();
    test_has_no_element_type<volatile int*&>();
    test_has_no_element_type<const volatile int*&>();
    test_has_no_element_type<int*&&>();
    test_has_no_element_type<const int*&&>();
    test_has_no_element_type<volatile int*&&>();
    test_has_no_element_type<const volatile int*&&>();
    test_has_no_element_type<void*>();
    test_has_no_element_type<char[3]>();
    test_has_no_element_type<char[]>();
    test_has_no_element_type<char* [3]>();
    test_has_no_element_type<char*[]>();
    test_has_no_element_type<int(*)[3]>();
    test_has_no_element_type<int(*)[]>();
    test_has_no_element_type<int(&)[3]>();
    test_has_no_element_type<int(&)[]>();
    test_has_no_element_type<int(&&)[3]>();
    test_has_no_element_type<int(&&)[]>();
    test_has_no_element_type<char[3][2]>();
    test_has_no_element_type<char[][2]>();
    test_has_no_element_type<char* [3][2]>();
    test_has_no_element_type<char*[][2]>();
    test_has_no_element_type<int(*)[3][2]>();
    test_has_no_element_type<int(*)[][2]>();
    test_has_no_element_type<int(&)[3][2]>();
    test_has_no_element_type<int(&)[][2]>();
    test_has_no_element_type<int(&&)[3][2]>();
    test_has_no_element_type<int(&&)[][2]>();
    test_has_no_element_type<class_type>();
    test_has_no_element_type<class_type[]>();
    test_has_no_element_type<class_type[2]>();
    test_has_no_element_type<template_type<void>>();
    test_has_no_element_type<template_type<int>>();
    test_has_no_element_type<template_type<class_type>>();
    test_has_no_element_type<template_type<incomplete_type>>();
    test_has_no_element_type<variadic_template<>>();
    test_has_no_element_type<variadic_template<void>>();
    test_has_no_element_type<variadic_template<int>>();
    test_has_no_element_type<variadic_template<class_type>>();
    test_has_no_element_type<variadic_template<incomplete_type>>();
    test_has_no_element_type<variadic_template<int, void, class_type, volatile char[]>>();
    test_has_no_element_type<public_derived_from<base>>();
    test_has_no_element_type<public_derived_from<derived>>();
    test_has_no_element_type<public_derived_from<class_type>>();
    test_has_no_element_type<private_derived_from<base>>();
    test_has_no_element_type<private_derived_from<derived>>();
    test_has_no_element_type<private_derived_from<class_type>>();
    test_has_no_element_type<protected_derived_from<base>>();
    test_has_no_element_type<protected_derived_from<derived>>();
    test_has_no_element_type<protected_derived_from<class_type>>();
    test_has_no_element_type<virtual_derived_from<base>>();
    test_has_no_element_type<virtual_derived_from<derived>>();
    test_has_no_element_type<virtual_derived_from<class_type>>();
    test_has_no_element_type<union_type>();
    test_has_no_element_type<non_empty_union>();
    test_has_no_element_type<non_trivial_union>();
    test_has_no_element_type<empty>();
    test_has_no_element_type<not_empty>();
    test_has_no_element_type<non_trivial>();
    test_has_no_element_type<bit_zero>();
    test_has_no_element_type<bit_one>();
    test_has_no_element_type<base>();
    test_has_no_element_type<derived>();
    test_has_no_element_type<non_empty_base>();
    test_has_no_element_type<empty_base>();
    test_has_no_element_type<virtual_base>();
    test_has_no_element_type<polymorphic>();
    test_has_no_element_type<derived_polymorphic>();
    test_has_no_element_type<abstract>();
    test_has_no_element_type<public_abstract>();
    test_has_no_element_type<private_abstract>();
    test_has_no_element_type<protected_abstract>();
    test_has_no_element_type<abstract_template<int>>();
    test_has_no_element_type<abstract_template<double>>();
    test_has_no_element_type<abstract_template<class_type>>();
    test_has_no_element_type<abstract_template<incomplete_type>>();
    test_has_no_element_type<public_abstract_deleted_destructor>();
    test_has_no_element_type<protected_abstract_deleted_destructor>();
    test_has_no_element_type<private_abstract_deleted_destructor>();
    test_has_no_element_type<final_type>();
    test_has_no_element_type<final_derived>();
    test_has_no_element_type<public_destructor>();
    test_has_no_element_type<protected_destructor>();
    test_has_no_element_type<private_destructor>();
    test_has_no_element_type<virtual_public_destructor>();
    test_has_no_element_type<virtual_protected_destructor>();
    test_has_no_element_type<virtual_private_destructor>();
    test_has_no_element_type<pure_public_destructor>();
    test_has_no_element_type<pure_protected_destructor>();
    test_has_no_element_type<pure_private_destructor>();
    test_has_no_element_type<deleted_public_destructor>();
    test_has_no_element_type<deleted_protected_destructor>();
    test_has_no_element_type<deleted_private_destructor>();
    test_has_no_element_type<deleted_virtual_public_destructor>();
    test_has_no_element_type<deleted_virtual_protected_destructor>();
    test_has_no_element_type<deleted_virtual_private_destructor>();
    test_has_no_element_type<explicit_class>();
    test_has_no_element_type<nothrow_explicit_class>();
    test_has_no_element_type<throw_explicit_class>();
    test_has_no_element_type<throw_default_class>();
    test_has_no_element_type<throw_copy_constructible_class>();
    test_has_no_element_type<throw_move_constructible_class>();
    test_has_no_element_type<throw_destructor>();
    test_has_no_element_type<noexcept_explicit_class>();
    test_has_no_element_type<except_explicit_class>();
    test_has_no_element_type<noexcept_default_class>();
    test_has_no_element_type<except_default_class>();
    test_has_no_element_type<noexcept_copy_constructible_class>();
    test_has_no_element_type<except_copy_constructible_class>();
    test_has_no_element_type<noexcept_move_constructible_class>();
    test_has_no_element_type<except_move_constructible_class>();
    test_has_no_element_type<noexcept_copy_assign_class>();
    test_has_no_element_type<except_copy_assign_class>();
    test_has_no_element_type<noexcept_move_assign_class>();
    test_has_no_element_type<except_move_assign_class>();
    test_has_no_element_type<deleted_copy_assign_class>();
    test_has_no_element_type<deleted_move_assign_class>();
    test_has_no_element_type<noexcept_move_constructible_and_assignable_class>();
    test_has_no_element_type<except_move_constructible_noexcept_move_assign_class>();
    test_has_no_element_type<noexcept_move_constructible_except_move_assign_class>();
    test_has_no_element_type<except_move_constructible_and_assign_class>();
    test_has_no_element_type<implicit_to<int>>();
    test_has_no_element_type<implicit_to<float>>();
    test_has_no_element_type<implicit_to<class_type>>();
    test_has_no_element_type<deleted_implicit_to<int>>();
    test_has_no_element_type<deleted_implicit_to<float>>();
    test_has_no_element_type<deleted_implicit_to<class_type>>();
    test_has_no_element_type<explicit_to<int>>();
    test_has_no_element_type<explicit_to<float>>();
    test_has_no_element_type<explicit_to<class_type>>();
    test_has_no_element_type<deleted_explicit_to<int>>();
    test_has_no_element_type<deleted_explicit_to<float>>();
    test_has_no_element_type<deleted_explicit_to<class_type>>();
    test_has_no_element_type<ellipsis>();
    test_has_no_element_type<deleted_ellipsis>();
    test_has_no_element_type<copy_constructible_only_type>();
    test_has_no_element_type<move_constructible_only_type>();
    test_has_no_element_type<overloaded_operators>();
    test_has_no_element_type<public_int_member>();
    test_has_no_element_type<protected_int_member>();
    test_has_no_element_type<private_int_member>();
    test_has_no_element_type<public_static_int_member>();
    test_has_no_element_type<protected_static_int_member>();
    test_has_no_element_type<private_static_int_member>();
    test_has_no_element_type<public_template_member<int>>();
    test_has_no_element_type<public_template_member<float>>();
    test_has_no_element_type<public_template_member<class_type>>();
    test_has_no_element_type<protected_template_member<int>>();
    test_has_no_element_type<protected_template_member<float>>();
    test_has_no_element_type<protected_template_member<class_type>>();
    test_has_no_element_type<private_template_member<int>>();
    test_has_no_element_type<private_template_member<float>>();
    test_has_no_element_type<private_template_member<class_type>>();
    test_has_no_element_type<public_static_template_member<int>>();
    test_has_no_element_type<public_static_template_member<float>>();
    test_has_no_element_type<public_static_template_member<class_type>>();
    test_has_no_element_type<protected_static_template_member<int>>();
    test_has_no_element_type<protected_static_template_member<float>>();
    test_has_no_element_type<protected_static_template_member<class_type>>();
    test_has_no_element_type<private_static_template_member<int>>();
    test_has_no_element_type<private_static_template_member<float>>();
    test_has_no_element_type<private_static_template_member<class_type>>();
    test_has_no_element_type<natural_alignment>();
    test_has_no_element_type<Enum>();
    test_has_no_element_type<EnumSigned>();
    test_has_no_element_type<EnumUnsigned>();
    test_has_no_element_type<EnumClass>();
    test_has_no_element_type<EnumStruct>();
    test_has_no_element_type<function_type>();
    test_has_no_element_type<function_ptr>();
    test_has_no_element_type<member_object_ptr>();
    test_has_no_element_type<member_function_ptr>();
    test_has_no_element_type<lambda_type>();
    test_has_no_element_type<lambda_noexcept_type>();
    test_has_no_element_type<lambda_throws_type>();
    test_has_no_element_type<incomplete_type>();
    test_has_no_element_type<incomplete_template<void>>();
    test_has_no_element_type<incomplete_template<int>>();
    test_has_no_element_type<incomplete_template<class_type>>();
    test_has_no_element_type<incomplete_template<incomplete_type>>();
    test_has_no_element_type<incomplete_variadic_template<>>();
    test_has_no_element_type<incomplete_variadic_template<void>>();
    test_has_no_element_type<incomplete_variadic_template<int>>();
    test_has_no_element_type<incomplete_variadic_template<class_type>>();
    test_has_no_element_type<incomplete_variadic_template<incomplete_type>>();
    test_has_no_element_type<
            incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_has_no_element_type<incomplete_union>();
    test_has_no_element_type<IncompleteEnumSigned>();
    test_has_no_element_type<IncompleteEnumUnsigned>();
    test_has_no_element_type<IncompleteEnumClass>();
    test_has_no_element_type<IncompleteEnumStruct>();
    test_has_no_element_type<int class_type::*>();
    test_has_no_element_type<float class_type::*>();
    test_has_no_element_type<void * class_type::*>();
    test_has_no_element_type<int * class_type::*>();
    test_has_no_element_type<Enum class_type::*>();
    test_has_no_element_type<not_empty class_type::*>();
    test_has_no_element_type<int class_type::*&>();
    test_has_no_element_type<float class_type::*&>();
    test_has_no_element_type<void * class_type::*&>();
    test_has_no_element_type<int * class_type::*&>();
    test_has_no_element_type<Enum class_type::*&>();
    test_has_no_element_type<not_empty class_type::*&>();
    test_has_no_element_type<int class_type::*&&>();
    test_has_no_element_type<float class_type::*&&>();
    test_has_no_element_type<void * class_type::*&&>();
    test_has_no_element_type<int * class_type::*&&>();
    test_has_no_element_type<Enum class_type::*&&>();
    test_has_no_element_type<not_empty class_type::*&&>();
    test_has_no_element_type<non_default_constructible>();
    test_has_no_element_type<non_copy_constructible>();
    test_has_no_element_type<non_move_constructible>();
    test_has_no_element_type<non_copy_assignable>();
    test_has_no_element_type<non_move_assignable>();
    test_has_no_element_type<non_assignable>();
    test_has_no_element_type<non_copyable>();
    test_has_no_element_type<non_moveable>();
    test_has_no_element_type<non_constructible>();
    test_has_no_element_type<non_destructible>();
    test_has_no_element_type<tracked>();
    test_has_no_element_type<trap_constructible>();
    test_has_no_element_type<trap_implicit_conversion>();
    test_has_no_element_type<trap_comma>();
    test_has_no_element_type<trap_call>();
    test_has_no_element_type<trap_self_assign>();
    test_has_no_element_type<trap_deref>();
    test_has_no_element_type<trap_array_subscript>();
    test_has_no_element_type<operator_hijacker>();

#if PHI_HAS_EXTENSION_ZERO_SIZE_ARRAY()
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wzero-length-array")
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wpedantic")

    test_has_no_element_type<int[0]>();

    PHI_GCC_SUPPRESS_WARNING_POP()
    PHI_CLANG_SUPPRESS_WARNING_POP()
#endif

    test_has_no_element_type<void()>();
    test_has_no_element_type<void()&>();
    test_has_no_element_type<void() &&>();
    test_has_no_element_type<void() const>();
    test_has_no_element_type<void() const&>();
    test_has_no_element_type<void() const&&>();
    test_has_no_element_type<void() volatile>();
    test_has_no_element_type<void() volatile&>();
    test_has_no_element_type<void() volatile&&>();
    test_has_no_element_type<void() const volatile>();
    test_has_no_element_type<void() const volatile&>();
    test_has_no_element_type<void() const volatile&&>();
    test_has_no_element_type<void() noexcept>();
    test_has_no_element_type<void() & noexcept>();
    test_has_no_element_type<void() && noexcept>();
    test_has_no_element_type<void() const noexcept>();
    test_has_no_element_type<void() const & noexcept>();
    test_has_no_element_type<void() const && noexcept>();
    test_has_no_element_type<void() volatile noexcept>();
    test_has_no_element_type<void() volatile & noexcept>();
    test_has_no_element_type<void() volatile && noexcept>();
    test_has_no_element_type<void() const volatile noexcept>();
    test_has_no_element_type<void() const volatile & noexcept>();
    test_has_no_element_type<void() const volatile && noexcept>();

    test_has_no_element_type<void(int)>();
    test_has_no_element_type<void(int)&>();
    test_has_no_element_type<void(int) &&>();
    test_has_no_element_type<void(int) const>();
    test_has_no_element_type<void(int) const&>();
    test_has_no_element_type<void(int) const&&>();
    test_has_no_element_type<void(int) volatile>();
    test_has_no_element_type<void(int) volatile&>();
    test_has_no_element_type<void(int) volatile&&>();
    test_has_no_element_type<void(int) const volatile>();
    test_has_no_element_type<void(int) const volatile&>();
    test_has_no_element_type<void(int) const volatile&&>();
    test_has_no_element_type<void(int) noexcept>();
    test_has_no_element_type<void(int) & noexcept>();
    test_has_no_element_type<void(int) && noexcept>();
    test_has_no_element_type<void(int) const noexcept>();
    test_has_no_element_type<void(int) const & noexcept>();
    test_has_no_element_type<void(int) const && noexcept>();
    test_has_no_element_type<void(int) volatile noexcept>();
    test_has_no_element_type<void(int) volatile & noexcept>();
    test_has_no_element_type<void(int) volatile && noexcept>();
    test_has_no_element_type<void(int) const volatile noexcept>();
    test_has_no_element_type<void(int) const volatile & noexcept>();
    test_has_no_element_type<void(int) const volatile && noexcept>();

    test_has_no_element_type<void(...)>();
    test_has_no_element_type<void(...)&>();
    test_has_no_element_type<void(...) &&>();
    test_has_no_element_type<void(...) const>();
    test_has_no_element_type<void(...) const&>();
    test_has_no_element_type<void(...) const&&>();
    test_has_no_element_type<void(...) volatile>();
    test_has_no_element_type<void(...) volatile&>();
    test_has_no_element_type<void(...) volatile&&>();
    test_has_no_element_type<void(...) const volatile>();
    test_has_no_element_type<void(...) const volatile&>();
    test_has_no_element_type<void(...) const volatile&&>();
    test_has_no_element_type<void(...) noexcept>();
    test_has_no_element_type<void(...) & noexcept>();
    test_has_no_element_type<void(...) && noexcept>();
    test_has_no_element_type<void(...) const noexcept>();
    test_has_no_element_type<void(...) const & noexcept>();
    test_has_no_element_type<void(...) const && noexcept>();
    test_has_no_element_type<void(...) volatile noexcept>();
    test_has_no_element_type<void(...) volatile & noexcept>();
    test_has_no_element_type<void(...) volatile && noexcept>();
    test_has_no_element_type<void(...) const volatile noexcept>();
    test_has_no_element_type<void(...) const volatile & noexcept>();
    test_has_no_element_type<void(...) const volatile && noexcept>();

    test_has_no_element_type<void(int, ...)>();
    test_has_no_element_type<void(int, ...)&>();
    test_has_no_element_type<void(int, ...) &&>();
    test_has_no_element_type<void(int, ...) const>();
    test_has_no_element_type<void(int, ...) const&>();
    test_has_no_element_type<void(int, ...) const&&>();
    test_has_no_element_type<void(int, ...) volatile>();
    test_has_no_element_type<void(int, ...) volatile&>();
    test_has_no_element_type<void(int, ...) volatile&&>();
    test_has_no_element_type<void(int, ...) const volatile>();
    test_has_no_element_type<void(int, ...) const volatile&>();
    test_has_no_element_type<void(int, ...) const volatile&&>();
    test_has_no_element_type<void(int, ...) noexcept>();
    test_has_no_element_type<void(int, ...) & noexcept>();
    test_has_no_element_type<void(int, ...) && noexcept>();
    test_has_no_element_type<void(int, ...) const noexcept>();
    test_has_no_element_type<void(int, ...) const & noexcept>();
    test_has_no_element_type<void(int, ...) const && noexcept>();
    test_has_no_element_type<void(int, ...) volatile noexcept>();
    test_has_no_element_type<void(int, ...) volatile & noexcept>();
    test_has_no_element_type<void(int, ...) volatile && noexcept>();
    test_has_no_element_type<void(int, ...) const volatile noexcept>();
    test_has_no_element_type<void(int, ...) const volatile & noexcept>();
    test_has_no_element_type<void(int, ...) const volatile && noexcept>();

    test_has_no_element_type<int()>();
    test_has_no_element_type<int()&>();
    test_has_no_element_type<int() &&>();
    test_has_no_element_type<int() const>();
    test_has_no_element_type<int() const&>();
    test_has_no_element_type<int() const&&>();
    test_has_no_element_type<int() volatile>();
    test_has_no_element_type<int() volatile&>();
    test_has_no_element_type<int() volatile&&>();
    test_has_no_element_type<int() const volatile>();
    test_has_no_element_type<int() const volatile&>();
    test_has_no_element_type<int() const volatile&&>();
    test_has_no_element_type<int() noexcept>();
    test_has_no_element_type<int() & noexcept>();
    test_has_no_element_type<int() && noexcept>();
    test_has_no_element_type<int() const noexcept>();
    test_has_no_element_type<int() const & noexcept>();
    test_has_no_element_type<int() const && noexcept>();
    test_has_no_element_type<int() volatile noexcept>();
    test_has_no_element_type<int() volatile & noexcept>();
    test_has_no_element_type<int() volatile && noexcept>();
    test_has_no_element_type<int() const volatile noexcept>();
    test_has_no_element_type<int() const volatile & noexcept>();
    test_has_no_element_type<int() const volatile && noexcept>();

    test_has_no_element_type<int(int)>();
    test_has_no_element_type<int(int)&>();
    test_has_no_element_type<int(int) &&>();
    test_has_no_element_type<int(int) const>();
    test_has_no_element_type<int(int) const&>();
    test_has_no_element_type<int(int) const&&>();
    test_has_no_element_type<int(int) volatile>();
    test_has_no_element_type<int(int) volatile&>();
    test_has_no_element_type<int(int) volatile&&>();
    test_has_no_element_type<int(int) const volatile>();
    test_has_no_element_type<int(int) const volatile&>();
    test_has_no_element_type<int(int) const volatile&&>();
    test_has_no_element_type<int(int) noexcept>();
    test_has_no_element_type<int(int) & noexcept>();
    test_has_no_element_type<int(int) && noexcept>();
    test_has_no_element_type<int(int) const noexcept>();
    test_has_no_element_type<int(int) const & noexcept>();
    test_has_no_element_type<int(int) const && noexcept>();
    test_has_no_element_type<int(int) volatile noexcept>();
    test_has_no_element_type<int(int) volatile & noexcept>();
    test_has_no_element_type<int(int) volatile && noexcept>();
    test_has_no_element_type<int(int) const volatile noexcept>();
    test_has_no_element_type<int(int) const volatile & noexcept>();
    test_has_no_element_type<int(int) const volatile && noexcept>();

    test_has_no_element_type<int(...)>();
    test_has_no_element_type<int(...)&>();
    test_has_no_element_type<int(...) &&>();
    test_has_no_element_type<int(...) const>();
    test_has_no_element_type<int(...) const&>();
    test_has_no_element_type<int(...) const&&>();
    test_has_no_element_type<int(...) volatile>();
    test_has_no_element_type<int(...) volatile&>();
    test_has_no_element_type<int(...) volatile&&>();
    test_has_no_element_type<int(...) const volatile>();
    test_has_no_element_type<int(...) const volatile&>();
    test_has_no_element_type<int(...) const volatile&&>();
    test_has_no_element_type<int(...) noexcept>();
    test_has_no_element_type<int(...) & noexcept>();
    test_has_no_element_type<int(...) && noexcept>();
    test_has_no_element_type<int(...) const noexcept>();
    test_has_no_element_type<int(...) const & noexcept>();
    test_has_no_element_type<int(...) const && noexcept>();
    test_has_no_element_type<int(...) volatile noexcept>();
    test_has_no_element_type<int(...) volatile & noexcept>();
    test_has_no_element_type<int(...) volatile && noexcept>();
    test_has_no_element_type<int(...) const volatile noexcept>();
    test_has_no_element_type<int(...) const volatile & noexcept>();
    test_has_no_element_type<int(...) const volatile && noexcept>();

    test_has_no_element_type<int(int, ...)>();
    test_has_no_element_type<int(int, ...)&>();
    test_has_no_element_type<int(int, ...) &&>();
    test_has_no_element_type<int(int, ...) const>();
    test_has_no_element_type<int(int, ...) const&>();
    test_has_no_element_type<int(int, ...) const&&>();
    test_has_no_element_type<int(int, ...) volatile>();
    test_has_no_element_type<int(int, ...) volatile&>();
    test_has_no_element_type<int(int, ...) volatile&&>();
    test_has_no_element_type<int(int, ...) const volatile>();
    test_has_no_element_type<int(int, ...) const volatile&>();
    test_has_no_element_type<int(int, ...) const volatile&&>();
    test_has_no_element_type<int(int, ...) noexcept>();
    test_has_no_element_type<int(int, ...) & noexcept>();
    test_has_no_element_type<int(int, ...) && noexcept>();
    test_has_no_element_type<int(int, ...) const noexcept>();
    test_has_no_element_type<int(int, ...) const & noexcept>();
    test_has_no_element_type<int(int, ...) const && noexcept>();
    test_has_no_element_type<int(int, ...) volatile noexcept>();
    test_has_no_element_type<int(int, ...) volatile & noexcept>();
    test_has_no_element_type<int(int, ...) volatile && noexcept>();
    test_has_no_element_type<int(int, ...) const volatile noexcept>();
    test_has_no_element_type<int(int, ...) const volatile & noexcept>();
    test_has_no_element_type<int(int, ...) const volatile && noexcept>();

    test_has_no_element_type<void (*)()>();
    test_has_no_element_type<void (*)() noexcept>();

    test_has_no_element_type<void (*)(int)>();
    test_has_no_element_type<void (*)(int) noexcept>();

    test_has_no_element_type<void (*)(...)>();
    test_has_no_element_type<void (*)(...) noexcept>();

    test_has_no_element_type<void (*)(int, ...)>();
    test_has_no_element_type<void (*)(int, ...) noexcept>();

    test_has_no_element_type<int (*)()>();
    test_has_no_element_type<int (*)() noexcept>();

    test_has_no_element_type<int (*)(int)>();
    test_has_no_element_type<int (*)(int) noexcept>();

    test_has_no_element_type<int (*)(...)>();
    test_has_no_element_type<int (*)(...) noexcept>();

    test_has_no_element_type<int (*)(int, ...)>();
    test_has_no_element_type<int (*)(int, ...) noexcept>();

    test_has_no_element_type<void (&)()>();
    test_has_no_element_type<void (&)() noexcept>();

    test_has_no_element_type<void (&)(int)>();
    test_has_no_element_type<void (&)(int) noexcept>();

    test_has_no_element_type<void (&)(...)>();
    test_has_no_element_type<void (&)(...) noexcept>();

    test_has_no_element_type<void (&)(int, ...)>();
    test_has_no_element_type<void (&)(int, ...) noexcept>();

    test_has_no_element_type<int (&)()>();
    test_has_no_element_type<int (&)() noexcept>();

    test_has_no_element_type<int (&)(int)>();
    test_has_no_element_type<int (&)(int) noexcept>();

    test_has_no_element_type<int (&)(...)>();
    test_has_no_element_type<int (&)(...) noexcept>();

    test_has_no_element_type<int (&)(int, ...)>();
    test_has_no_element_type<int (&)(int, ...) noexcept>();

    test_has_no_element_type<void (&&)()>();
    test_has_no_element_type<void (&&)() noexcept>();

    test_has_no_element_type<void (&&)(int)>();
    test_has_no_element_type<void (&&)(int) noexcept>();

    test_has_no_element_type<void (&&)(...)>();
    test_has_no_element_type<void (&&)(...) noexcept>();

    test_has_no_element_type<void (&&)(int, ...)>();
    test_has_no_element_type<void (&&)(int, ...) noexcept>();

    test_has_no_element_type<int (&&)()>();
    test_has_no_element_type<int (&&)() noexcept>();

    test_has_no_element_type<int (&&)(int)>();
    test_has_no_element_type<int (&&)(int) noexcept>();

    test_has_no_element_type<int (&&)(...)>();
    test_has_no_element_type<int (&&)(...) noexcept>();

    test_has_no_element_type<int (&&)(int, ...)>();
    test_has_no_element_type<int (&&)(int, ...) noexcept>();

    test_has_no_element_type<void (class_type::*)()>();
    test_has_no_element_type<void (class_type::*)()&>();
    test_has_no_element_type<void (class_type::*)() &&>();
    test_has_no_element_type<void (class_type::*)() const>();
    test_has_no_element_type<void (class_type::*)() const&>();
    test_has_no_element_type<void (class_type::*)() const&&>();
    test_has_no_element_type<void (class_type::*)() noexcept>();
    test_has_no_element_type<void (class_type::*)() & noexcept>();
    test_has_no_element_type<void (class_type::*)() && noexcept>();
    test_has_no_element_type<void (class_type::*)() const noexcept>();
    test_has_no_element_type<void (class_type::*)() const & noexcept>();
    test_has_no_element_type<void (class_type::*)() const && noexcept>();

    test_has_no_element_type<void (class_type::*)(int)>();
    test_has_no_element_type<void (class_type::*)(int)&>();
    test_has_no_element_type<void (class_type::*)(int) &&>();
    test_has_no_element_type<void (class_type::*)(int) const>();
    test_has_no_element_type<void (class_type::*)(int) const&>();
    test_has_no_element_type<void (class_type::*)(int) const&&>();
    test_has_no_element_type<void (class_type::*)(int) noexcept>();
    test_has_no_element_type<void (class_type::*)(int) & noexcept>();
    test_has_no_element_type<void (class_type::*)(int) && noexcept>();
    test_has_no_element_type<void (class_type::*)(int) const noexcept>();
    test_has_no_element_type<void (class_type::*)(int) const & noexcept>();
    test_has_no_element_type<void (class_type::*)(int) const && noexcept>();

    test_has_no_element_type<void (class_type::*)(...)>();
    test_has_no_element_type<void (class_type::*)(...)&>();
    test_has_no_element_type<void (class_type::*)(...) &&>();
    test_has_no_element_type<void (class_type::*)(...) const>();
    test_has_no_element_type<void (class_type::*)(...) const&>();
    test_has_no_element_type<void (class_type::*)(...) const&&>();
    test_has_no_element_type<void (class_type::*)(...) noexcept>();
    test_has_no_element_type<void (class_type::*)(...) & noexcept>();
    test_has_no_element_type<void (class_type::*)(...) && noexcept>();
    test_has_no_element_type<void (class_type::*)(...) const noexcept>();
    test_has_no_element_type<void (class_type::*)(...) const & noexcept>();
    test_has_no_element_type<void (class_type::*)(...) const && noexcept>();

    test_has_no_element_type<void (class_type::*)(int, ...)>();
    test_has_no_element_type<void (class_type::*)(int, ...)&>();
    test_has_no_element_type<void (class_type::*)(int, ...) &&>();
    test_has_no_element_type<void (class_type::*)(int, ...) const>();
    test_has_no_element_type<void (class_type::*)(int, ...) const&>();
    test_has_no_element_type<void (class_type::*)(int, ...) const&&>();
    test_has_no_element_type<void (class_type::*)(int, ...) noexcept>();
    test_has_no_element_type<void (class_type::*)(int, ...) & noexcept>();
    test_has_no_element_type<void (class_type::*)(int, ...) && noexcept>();
    test_has_no_element_type<void (class_type::*)(int, ...) const noexcept>();
    test_has_no_element_type<void (class_type::*)(int, ...) const & noexcept>();
    test_has_no_element_type<void (class_type::*)(int, ...) const && noexcept>();

    test_has_no_element_type<int (class_type::*)()>();
    test_has_no_element_type<int (class_type::*)()&>();
    test_has_no_element_type<int (class_type::*)() &&>();
    test_has_no_element_type<int (class_type::*)() const>();
    test_has_no_element_type<int (class_type::*)() const&>();
    test_has_no_element_type<int (class_type::*)() const&&>();
    test_has_no_element_type<int (class_type::*)() noexcept>();
    test_has_no_element_type<int (class_type::*)() & noexcept>();
    test_has_no_element_type<int (class_type::*)() && noexcept>();
    test_has_no_element_type<int (class_type::*)() const noexcept>();
    test_has_no_element_type<int (class_type::*)() const & noexcept>();
    test_has_no_element_type<int (class_type::*)() const && noexcept>();

    test_has_no_element_type<int (class_type::*)(int)>();
    test_has_no_element_type<int (class_type::*)(int)&>();
    test_has_no_element_type<int (class_type::*)(int) &&>();
    test_has_no_element_type<int (class_type::*)(int) const>();
    test_has_no_element_type<int (class_type::*)(int) const&>();
    test_has_no_element_type<int (class_type::*)(int) const&&>();
    test_has_no_element_type<int (class_type::*)(int) noexcept>();
    test_has_no_element_type<int (class_type::*)(int) & noexcept>();
    test_has_no_element_type<int (class_type::*)(int) && noexcept>();
    test_has_no_element_type<int (class_type::*)(int) const noexcept>();
    test_has_no_element_type<int (class_type::*)(int) const & noexcept>();
    test_has_no_element_type<int (class_type::*)(int) const && noexcept>();

    test_has_no_element_type<int (class_type::*)(...)>();
    test_has_no_element_type<int (class_type::*)(...)&>();
    test_has_no_element_type<int (class_type::*)(...) &&>();
    test_has_no_element_type<int (class_type::*)(...) const>();
    test_has_no_element_type<int (class_type::*)(...) const&>();
    test_has_no_element_type<int (class_type::*)(...) const&&>();
    test_has_no_element_type<int (class_type::*)(...) noexcept>();
    test_has_no_element_type<int (class_type::*)(...) & noexcept>();
    test_has_no_element_type<int (class_type::*)(...) && noexcept>();
    test_has_no_element_type<int (class_type::*)(...) const noexcept>();
    test_has_no_element_type<int (class_type::*)(...) const & noexcept>();
    test_has_no_element_type<int (class_type::*)(...) const && noexcept>();

    test_has_no_element_type<int (class_type::*)(int, ...)>();
    test_has_no_element_type<int (class_type::*)(int, ...)&>();
    test_has_no_element_type<int (class_type::*)(int, ...) &&>();
    test_has_no_element_type<int (class_type::*)(int, ...) const>();
    test_has_no_element_type<int (class_type::*)(int, ...) const&>();
    test_has_no_element_type<int (class_type::*)(int, ...) const&&>();
    test_has_no_element_type<int (class_type::*)(int, ...) noexcept>();
    test_has_no_element_type<int (class_type::*)(int, ...) & noexcept>();
    test_has_no_element_type<int (class_type::*)(int, ...) && noexcept>();
    test_has_no_element_type<int (class_type::*)(int, ...) const noexcept>();
    test_has_no_element_type<int (class_type::*)(int, ...) const & noexcept>();
    test_has_no_element_type<int (class_type::*)(int, ...) const && noexcept>();
}
