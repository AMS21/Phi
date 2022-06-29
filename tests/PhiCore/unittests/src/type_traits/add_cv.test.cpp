#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/add_cv.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT, typename OtherT>
void test_add_cv_impl()
{
    CHECK_SAME_TYPE(typename phi::add_cv<TypeT>::type, OtherT);
    CHECK_SAME_TYPE(phi::add_cv_t<TypeT>, OtherT);
    CHECK_SAME_TYPE(typename phi::add_cv<TypeT>::type, phi::add_cv_t<TypeT>);

    // Standard compatibility
    CHECK_SAME_TYPE(typename std::add_cv<TypeT>::type, OtherT);
    CHECK_SAME_TYPE(typename phi::add_cv<TypeT>::type, typename std::add_cv<TypeT>::type);
    CHECK_SAME_TYPE(phi::add_cv_t<TypeT>, typename std::add_cv<TypeT>::type);
}

template <typename TypeT>
void test_add_cv()
{
    test_add_cv_impl<TypeT, const volatile TypeT>();
    test_add_cv_impl<const TypeT, const volatile TypeT>();
    test_add_cv_impl<volatile TypeT, const volatile TypeT>();
    test_add_cv_impl<const volatile TypeT, const volatile TypeT>();
}

TEST_CASE("type_traits.add_cv")
{
    test_add_cv<void>();
    test_add_cv<phi::nullptr_t>();
    test_add_cv<bool>();
    test_add_cv<char>();
    test_add_cv<signed char>();
    test_add_cv<unsigned char>();
    test_add_cv<short>();
    test_add_cv<unsigned short>();
    test_add_cv<int>();
    test_add_cv<unsigned int>();
    test_add_cv<long>();
    test_add_cv<unsigned long>();
    test_add_cv<long long>();
    test_add_cv<unsigned long long>();
    test_add_cv<float>();
    test_add_cv<double>();
    test_add_cv<long double>();
    test_add_cv<char8_t>();
    test_add_cv<char16_t>();
    test_add_cv<char32_t>();
    test_add_cv<wchar_t>();

    test_add_cv<phi::boolean>();
    test_add_cv<phi::integer<signed char>>();
    test_add_cv<phi::integer<unsigned char>>();
    test_add_cv<phi::integer<short>>();
    test_add_cv<phi::integer<unsigned short>>();
    test_add_cv<phi::integer<int>>();
    test_add_cv<phi::integer<unsigned int>>();
    test_add_cv<phi::integer<long>>();
    test_add_cv<phi::integer<unsigned long>>();
    test_add_cv<phi::integer<long long>>();
    test_add_cv<phi::integer<unsigned long long>>();
    test_add_cv<phi::floating_point<float>>();
    test_add_cv<phi::floating_point<double>>();
    test_add_cv<phi::floating_point<long double>>();

    test_add_cv<std::vector<int>>();
    test_add_cv<phi::scope_ptr<int>>();

    test_add_cv<int&>();
    test_add_cv<const int&>();
    test_add_cv<volatile int&>();
    test_add_cv<const volatile int&>();
    test_add_cv<int&&>();
    test_add_cv<const int&&>();
    test_add_cv<volatile int&&>();
    test_add_cv<const volatile int&&>();
    test_add_cv<int*>();
    test_add_cv<const int*>();
    test_add_cv<volatile int*>();
    test_add_cv<const volatile int*>();
    test_add_cv<int**>();
    test_add_cv<const int**>();
    test_add_cv<volatile int**>();
    test_add_cv<const volatile int**>();
    test_add_cv<int*&>();
    test_add_cv<const int*&>();
    test_add_cv<volatile int*&>();
    test_add_cv<const volatile int*&>();
    test_add_cv<int*&&>();
    test_add_cv<const int*&&>();
    test_add_cv<volatile int*&&>();
    test_add_cv<const volatile int*&&>();
    test_add_cv<void*>();
    test_add_cv<char[3]>();
    test_add_cv<char[]>();
    test_add_cv<char* [3]>();
    test_add_cv<char*[]>();
    test_add_cv<int(*)[3]>();
    test_add_cv<int(*)[]>();
    test_add_cv<int(&)[3]>();
    test_add_cv<int(&)[]>();
    test_add_cv<int(&&)[3]>();
    test_add_cv<int(&&)[]>();
    test_add_cv<char[3][2]>();
    test_add_cv<char[][2]>();
    test_add_cv<char* [3][2]>();
    test_add_cv<char*[][2]>();
    test_add_cv<int(*)[3][2]>();
    test_add_cv<int(*)[][2]>();
    test_add_cv<int(&)[3][2]>();
    test_add_cv<int(&)[][2]>();
    test_add_cv<int(&&)[3][2]>();
    test_add_cv<int(&&)[][2]>();
    test_add_cv<class_type>();
    test_add_cv<class_type[]>();
    test_add_cv<class_type[2]>();
    test_add_cv<template_type<void>>();
    test_add_cv<template_type<int>>();
    test_add_cv<template_type<class_type>>();
    test_add_cv<template_type<incomplete_type>>();
    test_add_cv<variadic_template<>>();
    test_add_cv<variadic_template<void>>();
    test_add_cv<variadic_template<int>>();
    test_add_cv<variadic_template<class_type>>();
    test_add_cv<variadic_template<incomplete_type>>();
    test_add_cv<variadic_template<int, void, class_type, volatile char[]>>();
    test_add_cv<public_derived_from<base>>();
    test_add_cv<public_derived_from<derived>>();
    test_add_cv<public_derived_from<class_type>>();
    test_add_cv<private_derived_from<base>>();
    test_add_cv<private_derived_from<derived>>();
    test_add_cv<private_derived_from<class_type>>();
    test_add_cv<protected_derived_from<base>>();
    test_add_cv<protected_derived_from<derived>>();
    test_add_cv<protected_derived_from<class_type>>();
    test_add_cv<virtual_derived_from<base>>();
    test_add_cv<virtual_derived_from<derived>>();
    test_add_cv<virtual_derived_from<class_type>>();
    test_add_cv<union_type>();
    test_add_cv<non_empty_union>();
    test_add_cv<non_trivial_union>();
    test_add_cv<empty>();
    test_add_cv<not_empty>();
    test_add_cv<non_trivial>();
    test_add_cv<bit_zero>();
    test_add_cv<bit_one>();
    test_add_cv<base>();
    test_add_cv<derived>();
    test_add_cv<non_empty_base>();
    test_add_cv<empty_base>();
    test_add_cv<virtual_base>();
    test_add_cv<polymorphic>();
    test_add_cv<derived_polymorphic>();
    test_add_cv<abstract>();
    test_add_cv<public_abstract>();
    test_add_cv<private_abstract>();
    test_add_cv<protected_abstract>();
    test_add_cv<abstract_template<int>>();
    test_add_cv<abstract_template<double>>();
    test_add_cv<abstract_template<class_type>>();
    test_add_cv<abstract_template<incomplete_type>>();
    test_add_cv<public_abstract_deleted_destructor>();
    test_add_cv<protected_abstract_deleted_destructor>();
    test_add_cv<private_abstract_deleted_destructor>();
    test_add_cv<final_type>();
    test_add_cv<final_derived>();
    test_add_cv<public_destructor>();
    test_add_cv<protected_destructor>();
    test_add_cv<private_destructor>();
    test_add_cv<virtual_public_destructor>();
    test_add_cv<virtual_protected_destructor>();
    test_add_cv<virtual_private_destructor>();
    test_add_cv<pure_public_destructor>();
    test_add_cv<pure_protected_destructor>();
    test_add_cv<pure_private_destructor>();
    test_add_cv<deleted_public_destructor>();
    test_add_cv<deleted_protected_destructor>();
    test_add_cv<deleted_private_destructor>();
    test_add_cv<deleted_virtual_public_destructor>();
    test_add_cv<deleted_virtual_protected_destructor>();
    test_add_cv<deleted_virtual_private_destructor>();
    test_add_cv<explicit_class>();
    test_add_cv<nothrow_explicit_class>();
    test_add_cv<throw_explicit_class>();
    test_add_cv<throw_default_class>();
    test_add_cv<throw_copy_constructible_class>();
    test_add_cv<throw_move_constructible_class>();
    test_add_cv<throw_destructor>();
    test_add_cv<noexcept_explicit_class>();
    test_add_cv<except_explicit_class>();
    test_add_cv<noexcept_default_class>();
    test_add_cv<except_default_class>();
    test_add_cv<noexcept_copy_constructible_class>();
    test_add_cv<except_copy_constructible_class>();
    test_add_cv<noexcept_move_constructible_class>();
    test_add_cv<except_move_constructible_class>();
    test_add_cv<noexcept_copy_assign_class>();
    test_add_cv<except_copy_assign_class>();
    test_add_cv<noexcept_move_assign_class>();
    test_add_cv<except_move_assign_class>();
    test_add_cv<deleted_copy_assign_class>();
    test_add_cv<deleted_move_assign_class>();
    test_add_cv<noexcept_move_constructible_and_assignable_class>();
    test_add_cv<except_move_constructible_noexcept_move_assign_class>();
    test_add_cv<noexcept_move_constructible_except_move_assign_class>();
    test_add_cv<except_move_constructible_and_assign_class>();
    test_add_cv<implicit_to<int>>();
    test_add_cv<implicit_to<float>>();
    test_add_cv<implicit_to<class_type>>();
    test_add_cv<deleted_implicit_to<int>>();
    test_add_cv<deleted_implicit_to<float>>();
    test_add_cv<deleted_implicit_to<class_type>>();
    test_add_cv<explicit_to<int>>();
    test_add_cv<explicit_to<float>>();
    test_add_cv<explicit_to<class_type>>();
    test_add_cv<deleted_explicit_to<int>>();
    test_add_cv<deleted_explicit_to<float>>();
    test_add_cv<deleted_explicit_to<class_type>>();
    test_add_cv<ellipsis>();
    test_add_cv<deleted_ellipsis>();
    test_add_cv<copy_constructible_only_type>();
    test_add_cv<move_constructible_only_type>();
    test_add_cv<overloaded_operators>();
    test_add_cv<public_int_member>();
    test_add_cv<protected_int_member>();
    test_add_cv<private_int_member>();
    test_add_cv<public_static_int_member>();
    test_add_cv<protected_static_int_member>();
    test_add_cv<private_static_int_member>();
    test_add_cv<public_template_member<int>>();
    test_add_cv<public_template_member<float>>();
    test_add_cv<public_template_member<class_type>>();
    test_add_cv<protected_template_member<int>>();
    test_add_cv<protected_template_member<float>>();
    test_add_cv<protected_template_member<class_type>>();
    test_add_cv<private_template_member<int>>();
    test_add_cv<private_template_member<float>>();
    test_add_cv<private_template_member<class_type>>();
    test_add_cv<public_static_template_member<int>>();
    test_add_cv<public_static_template_member<float>>();
    test_add_cv<public_static_template_member<class_type>>();
    test_add_cv<protected_static_template_member<int>>();
    test_add_cv<protected_static_template_member<float>>();
    test_add_cv<protected_static_template_member<class_type>>();
    test_add_cv<private_static_template_member<int>>();
    test_add_cv<private_static_template_member<float>>();
    test_add_cv<private_static_template_member<class_type>>();
    test_add_cv<cannot_instantiate<int>>();
    test_add_cv<cannot_instantiate<float>>();
    test_add_cv<cannot_instantiate<class_type>>();
    test_add_cv<natural_alignment>();
    test_add_cv<Enum>();
    test_add_cv<EnumSigned>();
    test_add_cv<EnumUnsigned>();
    test_add_cv<EnumClass>();
    test_add_cv<EnumStruct>();
    test_add_cv<function_type>();
    test_add_cv<function_ptr>();
    test_add_cv<member_object_ptr>();
    test_add_cv<member_function_ptr>();
    test_add_cv<lambda_type>();
    test_add_cv<lambda_noexcept_type>();
    test_add_cv<lambda_throws_type>();
    test_add_cv<incomplete_type>();
    test_add_cv<incomplete_template<void>>();
    test_add_cv<incomplete_template<int>>();
    test_add_cv<incomplete_template<class_type>>();
    test_add_cv<incomplete_template<incomplete_type>>();
    test_add_cv<incomplete_variadic_template<>>();
    test_add_cv<incomplete_variadic_template<void>>();
    test_add_cv<incomplete_variadic_template<int>>();
    test_add_cv<incomplete_variadic_template<class_type>>();
    test_add_cv<incomplete_variadic_template<incomplete_type>>();
    test_add_cv<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_add_cv<incomplete_union>();
    test_add_cv<IncompleteEnumSigned>();
    test_add_cv<IncompleteEnumUnsigned>();
    test_add_cv<IncompleteEnumClass>();
    test_add_cv<IncompleteEnumStruct>();
    test_add_cv<int class_type::*>();
    test_add_cv<float class_type::*>();
    test_add_cv<void * class_type::*>();
    test_add_cv<int * class_type::*>();
    test_add_cv<Enum class_type::*>();
    test_add_cv<not_empty class_type::*>();
    test_add_cv<int class_type::*&>();
    test_add_cv<float class_type::*&>();
    test_add_cv<void * class_type::*&>();
    test_add_cv<int * class_type::*&>();
    test_add_cv<Enum class_type::*&>();
    test_add_cv<not_empty class_type::*&>();
    test_add_cv<int class_type::*&&>();
    test_add_cv<float class_type::*&&>();
    test_add_cv<void * class_type::*&&>();
    test_add_cv<int * class_type::*&&>();
    test_add_cv<Enum class_type::*&&>();
    test_add_cv<not_empty class_type::*&&>();
    test_add_cv<non_default_constructible>();
    test_add_cv<non_copy_constructible>();
    test_add_cv<non_move_constructible>();
    test_add_cv<non_copy_assignable>();
    test_add_cv<non_move_assignable>();
    test_add_cv<non_assignable>();
    test_add_cv<non_copyable>();
    test_add_cv<non_moveable>();
    test_add_cv<non_constructible>();
    test_add_cv<non_destructible>();
    test_add_cv<tracked>();
    test_add_cv<trap_constructible>();
    test_add_cv<trap_implicit_conversion>();
    test_add_cv<trap_comma>();
    test_add_cv<trap_call>();
    test_add_cv<trap_self_assign>();
    test_add_cv<trap_deref>();
    test_add_cv<trap_array_subscript>();

    test_add_cv<void()>();
    test_add_cv<void()&>();
    test_add_cv<void() &&>();
    test_add_cv<void() const>();
    test_add_cv<void() const&>();
    test_add_cv<void() const&&>();
    test_add_cv<void() volatile>();
    test_add_cv<void() volatile&>();
    test_add_cv<void() volatile&&>();
    test_add_cv<void() const volatile>();
    test_add_cv<void() const volatile&>();
    test_add_cv<void() const volatile&&>();
    test_add_cv<void() noexcept>();
    test_add_cv<void()& noexcept>();
    test_add_cv<void()&& noexcept>();
    test_add_cv<void() const noexcept>();
    test_add_cv<void() const& noexcept>();
    test_add_cv<void() const&& noexcept>();
    test_add_cv<void() volatile noexcept>();
    test_add_cv<void() volatile& noexcept>();
    test_add_cv<void() volatile&& noexcept>();
    test_add_cv<void() const volatile noexcept>();
    test_add_cv<void() const volatile& noexcept>();
    test_add_cv<void() const volatile&& noexcept>();

    test_add_cv<void(int)>();
    test_add_cv<void(int)&>();
    test_add_cv<void(int) &&>();
    test_add_cv<void(int) const>();
    test_add_cv<void(int) const&>();
    test_add_cv<void(int) const&&>();
    test_add_cv<void(int) volatile>();
    test_add_cv<void(int) volatile&>();
    test_add_cv<void(int) volatile&&>();
    test_add_cv<void(int) const volatile>();
    test_add_cv<void(int) const volatile&>();
    test_add_cv<void(int) const volatile&&>();
    test_add_cv<void(int) noexcept>();
    test_add_cv<void(int)& noexcept>();
    test_add_cv<void(int)&& noexcept>();
    test_add_cv<void(int) const noexcept>();
    test_add_cv<void(int) const& noexcept>();
    test_add_cv<void(int) const&& noexcept>();
    test_add_cv<void(int) volatile noexcept>();
    test_add_cv<void(int) volatile& noexcept>();
    test_add_cv<void(int) volatile&& noexcept>();
    test_add_cv<void(int) const volatile noexcept>();
    test_add_cv<void(int) const volatile& noexcept>();
    test_add_cv<void(int) const volatile&& noexcept>();

    test_add_cv<void(...)>();
    test_add_cv<void(...)&>();
    test_add_cv<void(...) &&>();
    test_add_cv<void(...) const>();
    test_add_cv<void(...) const&>();
    test_add_cv<void(...) const&&>();
    test_add_cv<void(...) volatile>();
    test_add_cv<void(...) volatile&>();
    test_add_cv<void(...) volatile&&>();
    test_add_cv<void(...) const volatile>();
    test_add_cv<void(...) const volatile&>();
    test_add_cv<void(...) const volatile&&>();
    test_add_cv<void(...) noexcept>();
    test_add_cv<void(...)& noexcept>();
    test_add_cv<void(...)&& noexcept>();
    test_add_cv<void(...) const noexcept>();
    test_add_cv<void(...) const& noexcept>();
    test_add_cv<void(...) const&& noexcept>();
    test_add_cv<void(...) volatile noexcept>();
    test_add_cv<void(...) volatile& noexcept>();
    test_add_cv<void(...) volatile&& noexcept>();
    test_add_cv<void(...) const volatile noexcept>();
    test_add_cv<void(...) const volatile& noexcept>();
    test_add_cv<void(...) const volatile&& noexcept>();

    test_add_cv<void(int, ...)>();
    test_add_cv<void(int, ...)&>();
    test_add_cv<void(int, ...) &&>();
    test_add_cv<void(int, ...) const>();
    test_add_cv<void(int, ...) const&>();
    test_add_cv<void(int, ...) const&&>();
    test_add_cv<void(int, ...) volatile>();
    test_add_cv<void(int, ...) volatile&>();
    test_add_cv<void(int, ...) volatile&&>();
    test_add_cv<void(int, ...) const volatile>();
    test_add_cv<void(int, ...) const volatile&>();
    test_add_cv<void(int, ...) const volatile&&>();
    test_add_cv<void(int, ...) noexcept>();
    test_add_cv<void(int, ...)& noexcept>();
    test_add_cv<void(int, ...)&& noexcept>();
    test_add_cv<void(int, ...) const noexcept>();
    test_add_cv<void(int, ...) const& noexcept>();
    test_add_cv<void(int, ...) const&& noexcept>();
    test_add_cv<void(int, ...) volatile noexcept>();
    test_add_cv<void(int, ...) volatile& noexcept>();
    test_add_cv<void(int, ...) volatile&& noexcept>();
    test_add_cv<void(int, ...) const volatile noexcept>();
    test_add_cv<void(int, ...) const volatile& noexcept>();
    test_add_cv<void(int, ...) const volatile&& noexcept>();

    test_add_cv<int()>();
    test_add_cv<int()&>();
    test_add_cv<int() &&>();
    test_add_cv<int() const>();
    test_add_cv<int() const&>();
    test_add_cv<int() const&&>();
    test_add_cv<int() volatile>();
    test_add_cv<int() volatile&>();
    test_add_cv<int() volatile&&>();
    test_add_cv<int() const volatile>();
    test_add_cv<int() const volatile&>();
    test_add_cv<int() const volatile&&>();
    test_add_cv<int() noexcept>();
    test_add_cv<int()& noexcept>();
    test_add_cv<int()&& noexcept>();
    test_add_cv<int() const noexcept>();
    test_add_cv<int() const& noexcept>();
    test_add_cv<int() const&& noexcept>();
    test_add_cv<int() volatile noexcept>();
    test_add_cv<int() volatile& noexcept>();
    test_add_cv<int() volatile&& noexcept>();
    test_add_cv<int() const volatile noexcept>();
    test_add_cv<int() const volatile& noexcept>();
    test_add_cv<int() const volatile&& noexcept>();

    test_add_cv<int(int)>();
    test_add_cv<int(int)&>();
    test_add_cv<int(int) &&>();
    test_add_cv<int(int) const>();
    test_add_cv<int(int) const&>();
    test_add_cv<int(int) const&&>();
    test_add_cv<int(int) volatile>();
    test_add_cv<int(int) volatile&>();
    test_add_cv<int(int) volatile&&>();
    test_add_cv<int(int) const volatile>();
    test_add_cv<int(int) const volatile&>();
    test_add_cv<int(int) const volatile&&>();
    test_add_cv<int(int) noexcept>();
    test_add_cv<int(int)& noexcept>();
    test_add_cv<int(int)&& noexcept>();
    test_add_cv<int(int) const noexcept>();
    test_add_cv<int(int) const& noexcept>();
    test_add_cv<int(int) const&& noexcept>();
    test_add_cv<int(int) volatile noexcept>();
    test_add_cv<int(int) volatile& noexcept>();
    test_add_cv<int(int) volatile&& noexcept>();
    test_add_cv<int(int) const volatile noexcept>();
    test_add_cv<int(int) const volatile& noexcept>();
    test_add_cv<int(int) const volatile&& noexcept>();

    test_add_cv<int(...)>();
    test_add_cv<int(...)&>();
    test_add_cv<int(...) &&>();
    test_add_cv<int(...) const>();
    test_add_cv<int(...) const&>();
    test_add_cv<int(...) const&&>();
    test_add_cv<int(...) volatile>();
    test_add_cv<int(...) volatile&>();
    test_add_cv<int(...) volatile&&>();
    test_add_cv<int(...) const volatile>();
    test_add_cv<int(...) const volatile&>();
    test_add_cv<int(...) const volatile&&>();
    test_add_cv<int(...) noexcept>();
    test_add_cv<int(...)& noexcept>();
    test_add_cv<int(...)&& noexcept>();
    test_add_cv<int(...) const noexcept>();
    test_add_cv<int(...) const& noexcept>();
    test_add_cv<int(...) const&& noexcept>();
    test_add_cv<int(...) volatile noexcept>();
    test_add_cv<int(...) volatile& noexcept>();
    test_add_cv<int(...) volatile&& noexcept>();
    test_add_cv<int(...) const volatile noexcept>();
    test_add_cv<int(...) const volatile& noexcept>();
    test_add_cv<int(...) const volatile&& noexcept>();

    test_add_cv<int(int, ...)>();
    test_add_cv<int(int, ...)&>();
    test_add_cv<int(int, ...) &&>();
    test_add_cv<int(int, ...) const>();
    test_add_cv<int(int, ...) const&>();
    test_add_cv<int(int, ...) const&&>();
    test_add_cv<int(int, ...) volatile>();
    test_add_cv<int(int, ...) volatile&>();
    test_add_cv<int(int, ...) volatile&&>();
    test_add_cv<int(int, ...) const volatile>();
    test_add_cv<int(int, ...) const volatile&>();
    test_add_cv<int(int, ...) const volatile&&>();
    test_add_cv<int(int, ...) noexcept>();
    test_add_cv<int(int, ...)& noexcept>();
    test_add_cv<int(int, ...)&& noexcept>();
    test_add_cv<int(int, ...) const noexcept>();
    test_add_cv<int(int, ...) const& noexcept>();
    test_add_cv<int(int, ...) const&& noexcept>();
    test_add_cv<int(int, ...) volatile noexcept>();
    test_add_cv<int(int, ...) volatile& noexcept>();
    test_add_cv<int(int, ...) volatile&& noexcept>();
    test_add_cv<int(int, ...) const volatile noexcept>();
    test_add_cv<int(int, ...) const volatile& noexcept>();
    test_add_cv<int(int, ...) const volatile&& noexcept>();

    test_add_cv<void (*)()>();
    test_add_cv<void (*)() noexcept>();

    test_add_cv<void (*)(int)>();
    test_add_cv<void (*)(int) noexcept>();

    test_add_cv<void (*)(...)>();
    test_add_cv<void (*)(...) noexcept>();

    test_add_cv<void (*)(int, ...)>();
    test_add_cv<void (*)(int, ...) noexcept>();

    test_add_cv<int (*)()>();
    test_add_cv<int (*)() noexcept>();

    test_add_cv<int (*)(int)>();
    test_add_cv<int (*)(int) noexcept>();

    test_add_cv<int (*)(...)>();
    test_add_cv<int (*)(...) noexcept>();

    test_add_cv<int (*)(int, ...)>();
    test_add_cv<int (*)(int, ...) noexcept>();

    test_add_cv<void (&)()>();
    test_add_cv<void (&)() noexcept>();

    test_add_cv<void (&)(int)>();
    test_add_cv<void (&)(int) noexcept>();

    test_add_cv<void (&)(...)>();
    test_add_cv<void (&)(...) noexcept>();

    test_add_cv<void (&)(int, ...)>();
    test_add_cv<void (&)(int, ...) noexcept>();

    test_add_cv<int (&)()>();
    test_add_cv<int (&)() noexcept>();

    test_add_cv<int (&)(int)>();
    test_add_cv<int (&)(int) noexcept>();

    test_add_cv<int (&)(...)>();
    test_add_cv<int (&)(...) noexcept>();

    test_add_cv<int (&)(int, ...)>();
    test_add_cv<int (&)(int, ...) noexcept>();

    test_add_cv<void (&&)()>();
    test_add_cv<void (&&)() noexcept>();

    test_add_cv<void (&&)(int)>();
    test_add_cv<void (&&)(int) noexcept>();

    test_add_cv<void (&&)(...)>();
    test_add_cv<void (&&)(...) noexcept>();

    test_add_cv<void (&&)(int, ...)>();
    test_add_cv<void (&&)(int, ...) noexcept>();

    test_add_cv<int (&&)()>();
    test_add_cv<int (&&)() noexcept>();

    test_add_cv<int (&&)(int)>();
    test_add_cv<int (&&)(int) noexcept>();

    test_add_cv<int (&&)(...)>();
    test_add_cv<int (&&)(...) noexcept>();

    test_add_cv<int (&&)(int, ...)>();
    test_add_cv<int (&&)(int, ...) noexcept>();

    test_add_cv<void (class_type::*)()>();
    test_add_cv<void (class_type::*)()&>();
    test_add_cv<void (class_type::*)() &&>();
    test_add_cv<void (class_type::*)() const>();
    test_add_cv<void (class_type::*)() const&>();
    test_add_cv<void (class_type::*)() const&&>();
    test_add_cv<void (class_type::*)() noexcept>();
    test_add_cv<void (class_type::*)()& noexcept>();
    test_add_cv<void (class_type::*)()&& noexcept>();
    test_add_cv<void (class_type::*)() const noexcept>();
    test_add_cv<void (class_type::*)() const& noexcept>();
    test_add_cv<void (class_type::*)() const&& noexcept>();

    test_add_cv<void (class_type::*)(int)>();
    test_add_cv<void (class_type::*)(int)&>();
    test_add_cv<void (class_type::*)(int) &&>();
    test_add_cv<void (class_type::*)(int) const>();
    test_add_cv<void (class_type::*)(int) const&>();
    test_add_cv<void (class_type::*)(int) const&&>();
    test_add_cv<void (class_type::*)(int) noexcept>();
    test_add_cv<void (class_type::*)(int)& noexcept>();
    test_add_cv<void (class_type::*)(int)&& noexcept>();
    test_add_cv<void (class_type::*)(int) const noexcept>();
    test_add_cv<void (class_type::*)(int) const& noexcept>();
    test_add_cv<void (class_type::*)(int) const&& noexcept>();

    test_add_cv<void (class_type::*)(...)>();
    test_add_cv<void (class_type::*)(...)&>();
    test_add_cv<void (class_type::*)(...) &&>();
    test_add_cv<void (class_type::*)(...) const>();
    test_add_cv<void (class_type::*)(...) const&>();
    test_add_cv<void (class_type::*)(...) const&&>();
    test_add_cv<void (class_type::*)(...) noexcept>();
    test_add_cv<void (class_type::*)(...)& noexcept>();
    test_add_cv<void (class_type::*)(...)&& noexcept>();
    test_add_cv<void (class_type::*)(...) const noexcept>();
    test_add_cv<void (class_type::*)(...) const& noexcept>();
    test_add_cv<void (class_type::*)(...) const&& noexcept>();

    test_add_cv<void (class_type::*)(int, ...)>();
    test_add_cv<void (class_type::*)(int, ...)&>();
    test_add_cv<void (class_type::*)(int, ...) &&>();
    test_add_cv<void (class_type::*)(int, ...) const>();
    test_add_cv<void (class_type::*)(int, ...) const&>();
    test_add_cv<void (class_type::*)(int, ...) const&&>();
    test_add_cv<void (class_type::*)(int, ...) noexcept>();
    test_add_cv<void (class_type::*)(int, ...)& noexcept>();
    test_add_cv<void (class_type::*)(int, ...)&& noexcept>();
    test_add_cv<void (class_type::*)(int, ...) const noexcept>();
    test_add_cv<void (class_type::*)(int, ...) const& noexcept>();
    test_add_cv<void (class_type::*)(int, ...) const&& noexcept>();

    test_add_cv<int (class_type::*)()>();
    test_add_cv<int (class_type::*)()&>();
    test_add_cv<int (class_type::*)() &&>();
    test_add_cv<int (class_type::*)() const>();
    test_add_cv<int (class_type::*)() const&>();
    test_add_cv<int (class_type::*)() const&&>();
    test_add_cv<int (class_type::*)() noexcept>();
    test_add_cv<int (class_type::*)()& noexcept>();
    test_add_cv<int (class_type::*)()&& noexcept>();
    test_add_cv<int (class_type::*)() const noexcept>();
    test_add_cv<int (class_type::*)() const& noexcept>();
    test_add_cv<int (class_type::*)() const&& noexcept>();

    test_add_cv<int (class_type::*)(int)>();
    test_add_cv<int (class_type::*)(int)&>();
    test_add_cv<int (class_type::*)(int) &&>();
    test_add_cv<int (class_type::*)(int) const>();
    test_add_cv<int (class_type::*)(int) const&>();
    test_add_cv<int (class_type::*)(int) const&&>();
    test_add_cv<int (class_type::*)(int) noexcept>();
    test_add_cv<int (class_type::*)(int)& noexcept>();
    test_add_cv<int (class_type::*)(int)&& noexcept>();
    test_add_cv<int (class_type::*)(int) const noexcept>();
    test_add_cv<int (class_type::*)(int) const& noexcept>();
    test_add_cv<int (class_type::*)(int) const&& noexcept>();

    test_add_cv<int (class_type::*)(...)>();
    test_add_cv<int (class_type::*)(...)&>();
    test_add_cv<int (class_type::*)(...) &&>();
    test_add_cv<int (class_type::*)(...) const>();
    test_add_cv<int (class_type::*)(...) const&>();
    test_add_cv<int (class_type::*)(...) const&&>();
    test_add_cv<int (class_type::*)(...) noexcept>();
    test_add_cv<int (class_type::*)(...)& noexcept>();
    test_add_cv<int (class_type::*)(...)&& noexcept>();
    test_add_cv<int (class_type::*)(...) const noexcept>();
    test_add_cv<int (class_type::*)(...) const& noexcept>();
    test_add_cv<int (class_type::*)(...) const&& noexcept>();

    test_add_cv<int (class_type::*)(int, ...)>();
    test_add_cv<int (class_type::*)(int, ...)&>();
    test_add_cv<int (class_type::*)(int, ...) &&>();
    test_add_cv<int (class_type::*)(int, ...) const>();
    test_add_cv<int (class_type::*)(int, ...) const&>();
    test_add_cv<int (class_type::*)(int, ...) const&&>();
    test_add_cv<int (class_type::*)(int, ...) noexcept>();
    test_add_cv<int (class_type::*)(int, ...)& noexcept>();
    test_add_cv<int (class_type::*)(int, ...)&& noexcept>();
    test_add_cv<int (class_type::*)(int, ...) const noexcept>();
    test_add_cv<int (class_type::*)(int, ...) const& noexcept>();
    test_add_cv<int (class_type::*)(int, ...) const&& noexcept>();
}
