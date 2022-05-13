#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/add_const.hpp>
#include <type_traits>
#include <vector>

template <typename T, typename U>
void test_add_const_impl()
{
    CHECK_SAME_TYPE(typename phi::add_const<T>::type, U);
    CHECK_SAME_TYPE(phi::add_const_t<T>, U);

    CHECK_SAME_TYPE(typename phi::add_const<T>::type, phi::add_const_t<T>);

    // Standard compatibility
    CHECK_SAME_TYPE(typename std::add_const<T>::type, U);
    CHECK_SAME_TYPE(typename phi::add_const<T>::type, typename std::add_const<T>::type);
    CHECK_SAME_TYPE(typename phi::add_const_t<T>, typename std::add_const<T>::type);
}

template <typename T>
void test_add_const()
{
    test_add_const_impl<T, const T>();
    test_add_const_impl<const T, const T>();
    test_add_const_impl<volatile T, const volatile T>();
    test_add_const_impl<const volatile T, const volatile T>();
}

TEST_CASE("type_traits.add_const")
{
    test_add_const<void>();
    test_add_const<phi::nullptr_t>();
    test_add_const<bool>();
    test_add_const<char>();
    test_add_const<signed char>();
    test_add_const<unsigned char>();
    test_add_const<short>();
    test_add_const<unsigned short>();
    test_add_const<int>();
    test_add_const<unsigned int>();
    test_add_const<long>();
    test_add_const<unsigned long>();
    test_add_const<long long>();
    test_add_const<unsigned long long>();
    test_add_const<float>();
    test_add_const<double>();
    test_add_const<long double>();
    test_add_const<char8_t>();
    test_add_const<char16_t>();
    test_add_const<char32_t>();
    test_add_const<wchar_t>();

    test_add_const<phi::boolean>();
    test_add_const<phi::integer<signed char>>();
    test_add_const<phi::integer<unsigned char>>();
    test_add_const<phi::integer<short>>();
    test_add_const<phi::integer<unsigned short>>();
    test_add_const<phi::integer<int>>();
    test_add_const<phi::integer<unsigned int>>();
    test_add_const<phi::integer<long>>();
    test_add_const<phi::integer<unsigned long>>();
    test_add_const<phi::integer<long long>>();
    test_add_const<phi::integer<unsigned long long>>();
    test_add_const<phi::floating_point<float>>();
    test_add_const<phi::floating_point<double>>();
    test_add_const<phi::floating_point<long double>>();

    test_add_const<std::vector<int>>();
    test_add_const<phi::scope_ptr<int>>();

    test_add_const<int&>();
    test_add_const<const int&>();
    test_add_const<volatile int&>();
    test_add_const<const volatile int&>();
    test_add_const<int&&>();
    test_add_const<const int&&>();
    test_add_const<volatile int&&>();
    test_add_const<const volatile int&&>();
    test_add_const<int*>();
    test_add_const<const int*>();
    test_add_const<volatile int*>();
    test_add_const<const volatile int*>();
    test_add_const<int**>();
    test_add_const<const int**>();
    test_add_const<volatile int**>();
    test_add_const<const volatile int**>();
    test_add_const<int*&>();
    test_add_const<const int*&>();
    test_add_const<volatile int*&>();
    test_add_const<const volatile int*&>();
    test_add_const<int*&&>();
    test_add_const<const int*&&>();
    test_add_const<volatile int*&&>();
    test_add_const<const volatile int*&&>();
    test_add_const<void*>();
    test_add_const<char[3]>();
    test_add_const<char[]>();
    test_add_const<char* [3]>();
    test_add_const<char*[]>();
    test_add_const<int(*)[3]>();
    test_add_const<int(*)[]>();
    test_add_const<int(&)[3]>();
    test_add_const<int(&)[]>();
    test_add_const<int(&&)[3]>();
    test_add_const<int(&&)[]>();
    test_add_const<char[3][2]>();
    test_add_const<char[][2]>();
    test_add_const<char* [3][2]>();
    test_add_const<char*[][2]>();
    test_add_const<int(*)[3][2]>();
    test_add_const<int(*)[][2]>();
    test_add_const<int(&)[3][2]>();
    test_add_const<int(&)[][2]>();
    test_add_const<int(&&)[3][2]>();
    test_add_const<int(&&)[][2]>();
    test_add_const<class_type>();
    test_add_const<class_type[]>();
    test_add_const<class_type[2]>();
    test_add_const<template_type<void>>();
    test_add_const<template_type<int>>();
    test_add_const<template_type<class_type>>();
    test_add_const<template_type<incomplete_type>>();
    test_add_const<variadic_template<>>();
    test_add_const<variadic_template<void>>();
    test_add_const<variadic_template<int>>();
    test_add_const<variadic_template<class_type>>();
    test_add_const<variadic_template<incomplete_type>>();
    test_add_const<variadic_template<int, void, class_type, volatile char[]>>();
    test_add_const<public_derived_from<base>>();
    test_add_const<public_derived_from<derived>>();
    test_add_const<public_derived_from<class_type>>();
    test_add_const<private_derived_from<base>>();
    test_add_const<private_derived_from<derived>>();
    test_add_const<private_derived_from<class_type>>();
    test_add_const<protected_derived_from<base>>();
    test_add_const<protected_derived_from<derived>>();
    test_add_const<protected_derived_from<class_type>>();
    test_add_const<virtual_derived_from<base>>();
    test_add_const<virtual_derived_from<derived>>();
    test_add_const<virtual_derived_from<class_type>>();
    test_add_const<union_type>();
    test_add_const<non_empty_union>();
    test_add_const<non_trivial_union>();
    test_add_const<empty>();
    test_add_const<not_empty>();
    test_add_const<non_trivial>();
    test_add_const<bit_zero>();
    test_add_const<bit_one>();
    test_add_const<base>();
    test_add_const<derived>();
    test_add_const<non_empty_base>();
    test_add_const<empty_base>();
    test_add_const<virtual_base>();
    test_add_const<polymorphic>();
    test_add_const<derived_polymorphic>();
    test_add_const<abstract>();
    test_add_const<public_abstract>();
    test_add_const<private_abstract>();
    test_add_const<protected_abstract>();
    test_add_const<abstract_template<int>>();
    test_add_const<abstract_template<double>>();
    test_add_const<abstract_template<class_type>>();
    test_add_const<abstract_template<incomplete_type>>();
    test_add_const<public_abstract_deleted_destructor>();
    test_add_const<protected_abstract_deleted_destructor>();
    test_add_const<private_abstract_deleted_destructor>();
    test_add_const<final_type>();
    test_add_const<final_derived>();
    test_add_const<public_destructor>();
    test_add_const<protected_destructor>();
    test_add_const<private_destructor>();
    test_add_const<virtual_public_destructor>();
    test_add_const<virtual_protected_destructor>();
    test_add_const<virtual_private_destructor>();
    test_add_const<pure_public_destructor>();
    test_add_const<pure_protected_destructor>();
    test_add_const<pure_private_destructor>();
    test_add_const<deleted_public_destructor>();
    test_add_const<deleted_protected_destructor>();
    test_add_const<deleted_private_destructor>();
    test_add_const<deleted_virtual_public_destructor>();
    test_add_const<deleted_virtual_protected_destructor>();
    test_add_const<deleted_virtual_private_destructor>();
    test_add_const<explicit_class>();
    test_add_const<nothrow_explicit_class>();
    test_add_const<throw_explicit_class>();
    test_add_const<throw_default_class>();
    test_add_const<throw_copy_constructible_class>();
    test_add_const<throw_move_constructible_class>();
    test_add_const<throw_destructor>();
    test_add_const<noexcept_explicit_class>();
    test_add_const<except_explicit_class>();
    test_add_const<noexcept_default_class>();
    test_add_const<except_default_class>();
    test_add_const<noexcept_copy_constructible_class>();
    test_add_const<except_copy_constructible_class>();
    test_add_const<noexcept_move_constructible_class>();
    test_add_const<except_move_constructible_class>();
    test_add_const<noexcept_copy_assign_class>();
    test_add_const<except_copy_assign_class>();
    test_add_const<noexcept_move_assign_class>();
    test_add_const<except_move_assign_class>();
    test_add_const<deleted_copy_assign_class>();
    test_add_const<deleted_move_assign_class>();
    test_add_const<noexcept_move_constructible_and_assignable_class>();
    test_add_const<except_move_constructible_noexcept_move_assign_class>();
    test_add_const<noexcept_move_constructible_except_move_assign_class>();
    test_add_const<except_move_constructible_and_assign_class>();
    test_add_const<implicit_to<int>>();
    test_add_const<implicit_to<float>>();
    test_add_const<implicit_to<class_type>>();
    test_add_const<deleted_implicit_to<int>>();
    test_add_const<deleted_implicit_to<float>>();
    test_add_const<deleted_implicit_to<class_type>>();
    test_add_const<explicit_to<int>>();
    test_add_const<explicit_to<float>>();
    test_add_const<explicit_to<class_type>>();
    test_add_const<deleted_explicit_to<int>>();
    test_add_const<deleted_explicit_to<float>>();
    test_add_const<deleted_explicit_to<class_type>>();
    test_add_const<ellipsis>();
    test_add_const<deleted_ellipsis>();
    test_add_const<copy_constructible_only_type>();
    test_add_const<move_constructible_only_type>();
    test_add_const<overloaded_operators>();
    test_add_const<public_int_member>();
    test_add_const<protected_int_member>();
    test_add_const<private_int_member>();
    test_add_const<public_static_int_member>();
    test_add_const<protected_static_int_member>();
    test_add_const<private_static_int_member>();
    test_add_const<public_template_member<int>>();
    test_add_const<public_template_member<float>>();
    test_add_const<public_template_member<class_type>>();
    test_add_const<protected_template_member<int>>();
    test_add_const<protected_template_member<float>>();
    test_add_const<protected_template_member<class_type>>();
    test_add_const<private_template_member<int>>();
    test_add_const<private_template_member<float>>();
    test_add_const<private_template_member<class_type>>();
    test_add_const<public_static_tempalte_member<int>>();
    test_add_const<public_static_tempalte_member<float>>();
    test_add_const<public_static_tempalte_member<class_type>>();
    test_add_const<protected_static_template_member<int>>();
    test_add_const<protected_static_template_member<float>>();
    test_add_const<protected_static_template_member<class_type>>();
    test_add_const<private_static_template_member<int>>();
    test_add_const<private_static_template_member<float>>();
    test_add_const<private_static_template_member<class_type>>();
    test_add_const<cannot_instantiate<int>>();
    test_add_const<cannot_instantiate<float>>();
    test_add_const<cannot_instantiate<class_type>>();
    test_add_const<natural_alignment>();
    test_add_const<Enum>();
    test_add_const<EnumSigned>();
    test_add_const<EnumUnsigned>();
    test_add_const<EnumClass>();
    test_add_const<EnumStruct>();
    test_add_const<function_type>();
    test_add_const<function_ptr>();
    test_add_const<member_object_ptr>();
    test_add_const<member_function_ptr>();
    test_add_const<lambda_type>();
    test_add_const<lambda_noexcept_type>();
    test_add_const<lambda_throws_type>();
    test_add_const<incomplete_type>();
    test_add_const<incomplete_template<void>>();
    test_add_const<incomplete_template<int>>();
    test_add_const<incomplete_template<class_type>>();
    test_add_const<incomplete_template<incomplete_type>>();
    test_add_const<incomplete_variadic_template<>>();
    test_add_const<incomplete_variadic_template<void>>();
    test_add_const<incomplete_variadic_template<int>>();
    test_add_const<incomplete_variadic_template<class_type>>();
    test_add_const<incomplete_variadic_template<incomplete_type>>();
    test_add_const<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_add_const<incomplete_union>();
    test_add_const<IncompleteEnumSigned>();
    test_add_const<IncompleteEnumUnsigned>();
    test_add_const<IncompleteEnumClass>();
    test_add_const<IncompleteEnumStruct>();
    test_add_const<int class_type::*>();
    test_add_const<float class_type::*>();
    test_add_const<void * class_type::*>();
    test_add_const<int * class_type::*>();
    test_add_const<Enum class_type::*>();
    test_add_const<not_empty class_type::*>();
    test_add_const<int class_type::*&>();
    test_add_const<float class_type::*&>();
    test_add_const<void * class_type::*&>();
    test_add_const<int * class_type::*&>();
    test_add_const<Enum class_type::*&>();
    test_add_const<not_empty class_type::*&>();
    test_add_const<int class_type::*&&>();
    test_add_const<float class_type::*&&>();
    test_add_const<void * class_type::*&&>();
    test_add_const<int * class_type::*&&>();
    test_add_const<Enum class_type::*&&>();
    test_add_const<not_empty class_type::*&&>();
    test_add_const<non_default_constructible>();
    test_add_const<non_copy_constructible>();
    test_add_const<non_move_constructible>();
    test_add_const<non_copy_assignable>();
    test_add_const<non_move_assignable>();
    test_add_const<non_assignable>();
    test_add_const<non_copyable>();
    test_add_const<non_moveable>();
    test_add_const<non_constructible>();
    test_add_const<non_destructible>();
    test_add_const<tracked>();
    test_add_const<trap_constructible>();
    test_add_const<trap_implicit_conversion>();
    test_add_const<trap_comma>();
    test_add_const<trap_call>();
    test_add_const<trap_self_assign>();
    test_add_const<trap_deref>();
    test_add_const<trap_array_subscript>();

    test_add_const<void()>();
    test_add_const<void()&>();
    test_add_const<void() &&>();
    test_add_const<void() const>();
    test_add_const<void() const&>();
    test_add_const<void() const&&>();
    test_add_const<void() volatile>();
    test_add_const<void() volatile&>();
    test_add_const<void() volatile&&>();
    test_add_const<void() const volatile>();
    test_add_const<void() const volatile&>();
    test_add_const<void() const volatile&&>();
    test_add_const<void() noexcept>();
    test_add_const<void()& noexcept>();
    test_add_const<void()&& noexcept>();
    test_add_const<void() const noexcept>();
    test_add_const<void() const& noexcept>();
    test_add_const<void() const&& noexcept>();
    test_add_const<void() volatile noexcept>();
    test_add_const<void() volatile& noexcept>();
    test_add_const<void() volatile&& noexcept>();
    test_add_const<void() const volatile noexcept>();
    test_add_const<void() const volatile& noexcept>();
    test_add_const<void() const volatile&& noexcept>();

    test_add_const<void(int)>();
    test_add_const<void(int)&>();
    test_add_const<void(int) &&>();
    test_add_const<void(int) const>();
    test_add_const<void(int) const&>();
    test_add_const<void(int) const&&>();
    test_add_const<void(int) volatile>();
    test_add_const<void(int) volatile&>();
    test_add_const<void(int) volatile&&>();
    test_add_const<void(int) const volatile>();
    test_add_const<void(int) const volatile&>();
    test_add_const<void(int) const volatile&&>();
    test_add_const<void(int) noexcept>();
    test_add_const<void(int)& noexcept>();
    test_add_const<void(int)&& noexcept>();
    test_add_const<void(int) const noexcept>();
    test_add_const<void(int) const& noexcept>();
    test_add_const<void(int) const&& noexcept>();
    test_add_const<void(int) volatile noexcept>();
    test_add_const<void(int) volatile& noexcept>();
    test_add_const<void(int) volatile&& noexcept>();
    test_add_const<void(int) const volatile noexcept>();
    test_add_const<void(int) const volatile& noexcept>();
    test_add_const<void(int) const volatile&& noexcept>();

    test_add_const<void(...)>();
    test_add_const<void(...)&>();
    test_add_const<void(...) &&>();
    test_add_const<void(...) const>();
    test_add_const<void(...) const&>();
    test_add_const<void(...) const&&>();
    test_add_const<void(...) volatile>();
    test_add_const<void(...) volatile&>();
    test_add_const<void(...) volatile&&>();
    test_add_const<void(...) const volatile>();
    test_add_const<void(...) const volatile&>();
    test_add_const<void(...) const volatile&&>();
    test_add_const<void(...) noexcept>();
    test_add_const<void(...)& noexcept>();
    test_add_const<void(...)&& noexcept>();
    test_add_const<void(...) const noexcept>();
    test_add_const<void(...) const& noexcept>();
    test_add_const<void(...) const&& noexcept>();
    test_add_const<void(...) volatile noexcept>();
    test_add_const<void(...) volatile& noexcept>();
    test_add_const<void(...) volatile&& noexcept>();
    test_add_const<void(...) const volatile noexcept>();
    test_add_const<void(...) const volatile& noexcept>();
    test_add_const<void(...) const volatile&& noexcept>();

    test_add_const<void(int, ...)>();
    test_add_const<void(int, ...)&>();
    test_add_const<void(int, ...) &&>();
    test_add_const<void(int, ...) const>();
    test_add_const<void(int, ...) const&>();
    test_add_const<void(int, ...) const&&>();
    test_add_const<void(int, ...) volatile>();
    test_add_const<void(int, ...) volatile&>();
    test_add_const<void(int, ...) volatile&&>();
    test_add_const<void(int, ...) const volatile>();
    test_add_const<void(int, ...) const volatile&>();
    test_add_const<void(int, ...) const volatile&&>();
    test_add_const<void(int, ...) noexcept>();
    test_add_const<void(int, ...)& noexcept>();
    test_add_const<void(int, ...)&& noexcept>();
    test_add_const<void(int, ...) const noexcept>();
    test_add_const<void(int, ...) const& noexcept>();
    test_add_const<void(int, ...) const&& noexcept>();
    test_add_const<void(int, ...) volatile noexcept>();
    test_add_const<void(int, ...) volatile& noexcept>();
    test_add_const<void(int, ...) volatile&& noexcept>();
    test_add_const<void(int, ...) const volatile noexcept>();
    test_add_const<void(int, ...) const volatile& noexcept>();
    test_add_const<void(int, ...) const volatile&& noexcept>();

    test_add_const<int()>();
    test_add_const<int()&>();
    test_add_const<int() &&>();
    test_add_const<int() const>();
    test_add_const<int() const&>();
    test_add_const<int() const&&>();
    test_add_const<int() volatile>();
    test_add_const<int() volatile&>();
    test_add_const<int() volatile&&>();
    test_add_const<int() const volatile>();
    test_add_const<int() const volatile&>();
    test_add_const<int() const volatile&&>();
    test_add_const<int() noexcept>();
    test_add_const<int()& noexcept>();
    test_add_const<int()&& noexcept>();
    test_add_const<int() const noexcept>();
    test_add_const<int() const& noexcept>();
    test_add_const<int() const&& noexcept>();
    test_add_const<int() volatile noexcept>();
    test_add_const<int() volatile& noexcept>();
    test_add_const<int() volatile&& noexcept>();
    test_add_const<int() const volatile noexcept>();
    test_add_const<int() const volatile& noexcept>();
    test_add_const<int() const volatile&& noexcept>();

    test_add_const<int(int)>();
    test_add_const<int(int)&>();
    test_add_const<int(int) &&>();
    test_add_const<int(int) const>();
    test_add_const<int(int) const&>();
    test_add_const<int(int) const&&>();
    test_add_const<int(int) volatile>();
    test_add_const<int(int) volatile&>();
    test_add_const<int(int) volatile&&>();
    test_add_const<int(int) const volatile>();
    test_add_const<int(int) const volatile&>();
    test_add_const<int(int) const volatile&&>();
    test_add_const<int(int) noexcept>();
    test_add_const<int(int)& noexcept>();
    test_add_const<int(int)&& noexcept>();
    test_add_const<int(int) const noexcept>();
    test_add_const<int(int) const& noexcept>();
    test_add_const<int(int) const&& noexcept>();
    test_add_const<int(int) volatile noexcept>();
    test_add_const<int(int) volatile& noexcept>();
    test_add_const<int(int) volatile&& noexcept>();
    test_add_const<int(int) const volatile noexcept>();
    test_add_const<int(int) const volatile& noexcept>();
    test_add_const<int(int) const volatile&& noexcept>();

    test_add_const<int(...)>();
    test_add_const<int(...)&>();
    test_add_const<int(...) &&>();
    test_add_const<int(...) const>();
    test_add_const<int(...) const&>();
    test_add_const<int(...) const&&>();
    test_add_const<int(...) volatile>();
    test_add_const<int(...) volatile&>();
    test_add_const<int(...) volatile&&>();
    test_add_const<int(...) const volatile>();
    test_add_const<int(...) const volatile&>();
    test_add_const<int(...) const volatile&&>();
    test_add_const<int(...) noexcept>();
    test_add_const<int(...)& noexcept>();
    test_add_const<int(...)&& noexcept>();
    test_add_const<int(...) const noexcept>();
    test_add_const<int(...) const& noexcept>();
    test_add_const<int(...) const&& noexcept>();
    test_add_const<int(...) volatile noexcept>();
    test_add_const<int(...) volatile& noexcept>();
    test_add_const<int(...) volatile&& noexcept>();
    test_add_const<int(...) const volatile noexcept>();
    test_add_const<int(...) const volatile& noexcept>();
    test_add_const<int(...) const volatile&& noexcept>();

    test_add_const<int(int, ...)>();
    test_add_const<int(int, ...)&>();
    test_add_const<int(int, ...) &&>();
    test_add_const<int(int, ...) const>();
    test_add_const<int(int, ...) const&>();
    test_add_const<int(int, ...) const&&>();
    test_add_const<int(int, ...) volatile>();
    test_add_const<int(int, ...) volatile&>();
    test_add_const<int(int, ...) volatile&&>();
    test_add_const<int(int, ...) const volatile>();
    test_add_const<int(int, ...) const volatile&>();
    test_add_const<int(int, ...) const volatile&&>();
    test_add_const<int(int, ...) noexcept>();
    test_add_const<int(int, ...)& noexcept>();
    test_add_const<int(int, ...)&& noexcept>();
    test_add_const<int(int, ...) const noexcept>();
    test_add_const<int(int, ...) const& noexcept>();
    test_add_const<int(int, ...) const&& noexcept>();
    test_add_const<int(int, ...) volatile noexcept>();
    test_add_const<int(int, ...) volatile& noexcept>();
    test_add_const<int(int, ...) volatile&& noexcept>();
    test_add_const<int(int, ...) const volatile noexcept>();
    test_add_const<int(int, ...) const volatile& noexcept>();
    test_add_const<int(int, ...) const volatile&& noexcept>();

    test_add_const<void (*)()>();
    test_add_const<void (*)() noexcept>();

    test_add_const<void (*)(int)>();
    test_add_const<void (*)(int) noexcept>();

    test_add_const<void (*)(...)>();
    test_add_const<void (*)(...) noexcept>();

    test_add_const<void (*)(int, ...)>();
    test_add_const<void (*)(int, ...) noexcept>();

    test_add_const<int (*)()>();
    test_add_const<int (*)() noexcept>();

    test_add_const<int (*)(int)>();
    test_add_const<int (*)(int) noexcept>();

    test_add_const<int (*)(...)>();
    test_add_const<int (*)(...) noexcept>();

    test_add_const<int (*)(int, ...)>();
    test_add_const<int (*)(int, ...) noexcept>();

    test_add_const<void (&)()>();
    test_add_const<void (&)() noexcept>();

    test_add_const<void (&)(int)>();
    test_add_const<void (&)(int) noexcept>();

    test_add_const<void (&)(...)>();
    test_add_const<void (&)(...) noexcept>();

    test_add_const<void (&)(int, ...)>();
    test_add_const<void (&)(int, ...) noexcept>();

    test_add_const<int (&)()>();
    test_add_const<int (&)() noexcept>();

    test_add_const<int (&)(int)>();
    test_add_const<int (&)(int) noexcept>();

    test_add_const<int (&)(...)>();
    test_add_const<int (&)(...) noexcept>();

    test_add_const<int (&)(int, ...)>();
    test_add_const<int (&)(int, ...) noexcept>();

    test_add_const<void(&&)()>();
    test_add_const<void(&&)() noexcept>();

    test_add_const<void(&&)(int)>();
    test_add_const<void(&&)(int) noexcept>();

    test_add_const<void(&&)(...)>();
    test_add_const<void(&&)(...) noexcept>();

    test_add_const<void(&&)(int, ...)>();
    test_add_const<void(&&)(int, ...) noexcept>();

    test_add_const<int(&&)()>();
    test_add_const<int(&&)() noexcept>();

    test_add_const<int(&&)(int)>();
    test_add_const<int(&&)(int) noexcept>();

    test_add_const<int(&&)(...)>();
    test_add_const<int(&&)(...) noexcept>();

    test_add_const<int(&&)(int, ...)>();
    test_add_const<int(&&)(int, ...) noexcept>();

    test_add_const<void (class_type::*)()>();
    test_add_const<void (class_type::*)()&>();
    test_add_const<void (class_type::*)() &&>();
    test_add_const<void (class_type::*)() const>();
    test_add_const<void (class_type::*)() const&>();
    test_add_const<void (class_type::*)() const&&>();
    test_add_const<void (class_type::*)() noexcept>();
    test_add_const<void (class_type::*)()& noexcept>();
    test_add_const<void (class_type::*)()&& noexcept>();
    test_add_const<void (class_type::*)() const noexcept>();
    test_add_const<void (class_type::*)() const& noexcept>();
    test_add_const<void (class_type::*)() const&& noexcept>();

    test_add_const<void (class_type::*)(int)>();
    test_add_const<void (class_type::*)(int)&>();
    test_add_const<void (class_type::*)(int) &&>();
    test_add_const<void (class_type::*)(int) const>();
    test_add_const<void (class_type::*)(int) const&>();
    test_add_const<void (class_type::*)(int) const&&>();
    test_add_const<void (class_type::*)(int) noexcept>();
    test_add_const<void (class_type::*)(int)& noexcept>();
    test_add_const<void (class_type::*)(int)&& noexcept>();
    test_add_const<void (class_type::*)(int) const noexcept>();
    test_add_const<void (class_type::*)(int) const& noexcept>();
    test_add_const<void (class_type::*)(int) const&& noexcept>();

    test_add_const<void (class_type::*)(...)>();
    test_add_const<void (class_type::*)(...)&>();
    test_add_const<void (class_type::*)(...) &&>();
    test_add_const<void (class_type::*)(...) const>();
    test_add_const<void (class_type::*)(...) const&>();
    test_add_const<void (class_type::*)(...) const&&>();
    test_add_const<void (class_type::*)(...) noexcept>();
    test_add_const<void (class_type::*)(...)& noexcept>();
    test_add_const<void (class_type::*)(...)&& noexcept>();
    test_add_const<void (class_type::*)(...) const noexcept>();
    test_add_const<void (class_type::*)(...) const& noexcept>();
    test_add_const<void (class_type::*)(...) const&& noexcept>();

    test_add_const<void (class_type::*)(int, ...)>();
    test_add_const<void (class_type::*)(int, ...)&>();
    test_add_const<void (class_type::*)(int, ...) &&>();
    test_add_const<void (class_type::*)(int, ...) const>();
    test_add_const<void (class_type::*)(int, ...) const&>();
    test_add_const<void (class_type::*)(int, ...) const&&>();
    test_add_const<void (class_type::*)(int, ...) noexcept>();
    test_add_const<void (class_type::*)(int, ...)& noexcept>();
    test_add_const<void (class_type::*)(int, ...)&& noexcept>();
    test_add_const<void (class_type::*)(int, ...) const noexcept>();
    test_add_const<void (class_type::*)(int, ...) const& noexcept>();
    test_add_const<void (class_type::*)(int, ...) const&& noexcept>();

    test_add_const<int (class_type::*)()>();
    test_add_const<int (class_type::*)()&>();
    test_add_const<int (class_type::*)() &&>();
    test_add_const<int (class_type::*)() const>();
    test_add_const<int (class_type::*)() const&>();
    test_add_const<int (class_type::*)() const&&>();
    test_add_const<int (class_type::*)() noexcept>();
    test_add_const<int (class_type::*)()& noexcept>();
    test_add_const<int (class_type::*)()&& noexcept>();
    test_add_const<int (class_type::*)() const noexcept>();
    test_add_const<int (class_type::*)() const& noexcept>();
    test_add_const<int (class_type::*)() const&& noexcept>();

    test_add_const<int (class_type::*)(int)>();
    test_add_const<int (class_type::*)(int)&>();
    test_add_const<int (class_type::*)(int) &&>();
    test_add_const<int (class_type::*)(int) const>();
    test_add_const<int (class_type::*)(int) const&>();
    test_add_const<int (class_type::*)(int) const&&>();
    test_add_const<int (class_type::*)(int) noexcept>();
    test_add_const<int (class_type::*)(int)& noexcept>();
    test_add_const<int (class_type::*)(int)&& noexcept>();
    test_add_const<int (class_type::*)(int) const noexcept>();
    test_add_const<int (class_type::*)(int) const& noexcept>();
    test_add_const<int (class_type::*)(int) const&& noexcept>();

    test_add_const<int (class_type::*)(...)>();
    test_add_const<int (class_type::*)(...)&>();
    test_add_const<int (class_type::*)(...) &&>();
    test_add_const<int (class_type::*)(...) const>();
    test_add_const<int (class_type::*)(...) const&>();
    test_add_const<int (class_type::*)(...) const&&>();
    test_add_const<int (class_type::*)(...) noexcept>();
    test_add_const<int (class_type::*)(...)& noexcept>();
    test_add_const<int (class_type::*)(...)&& noexcept>();
    test_add_const<int (class_type::*)(...) const noexcept>();
    test_add_const<int (class_type::*)(...) const& noexcept>();
    test_add_const<int (class_type::*)(...) const&& noexcept>();

    test_add_const<int (class_type::*)(int, ...)>();
    test_add_const<int (class_type::*)(int, ...)&>();
    test_add_const<int (class_type::*)(int, ...) &&>();
    test_add_const<int (class_type::*)(int, ...) const>();
    test_add_const<int (class_type::*)(int, ...) const&>();
    test_add_const<int (class_type::*)(int, ...) const&&>();
    test_add_const<int (class_type::*)(int, ...) noexcept>();
    test_add_const<int (class_type::*)(int, ...)& noexcept>();
    test_add_const<int (class_type::*)(int, ...)&& noexcept>();
    test_add_const<int (class_type::*)(int, ...) const noexcept>();
    test_add_const<int (class_type::*)(int, ...) const& noexcept>();
    test_add_const<int (class_type::*)(int, ...) const&& noexcept>();
}
