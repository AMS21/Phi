#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/integral_constant.hpp>
#include <phi/type_traits/is_same_rv.hpp>
#include <type_traits>
#include <vector>

template <typename T, typename U>
void test_is_same_rv_impl()
{
    STATIC_REQUIRE(phi::is_same_rv<T, U>::value);
    STATIC_REQUIRE(phi::is_same_rv<U, T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<U, T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_rv_v<T, U>);
    STATIC_REQUIRE(phi::is_same_rv_v<U, T>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<U, T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same_rv<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same_rv<T, U>);
}

template <typename T, typename U>
void test_is_not_same_rv()
{
    STATIC_REQUIRE_FALSE(phi::is_same_rv<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same_rv<U, T>::value);
    STATIC_REQUIRE(phi::is_not_same_rv<T, U>::value);
    STATIC_REQUIRE(phi::is_not_same_rv<U, T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_same_rv_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_same_rv_v<U, T>);
    STATIC_REQUIRE(phi::is_not_same_rv_v<T, U>);
    STATIC_REQUIRE(phi::is_not_same_rv_v<U, T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same_rv<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same_rv<T, U>);
}

template <typename T, typename U = T>
void test_is_same_rv()
{
    test_is_same_rv_impl<T, U>();
    test_is_not_same_rv<T, const U>();
    test_is_same_rv_impl<T, volatile U>();
    test_is_not_same_rv<T, const volatile U>();

    test_is_not_same_rv<const T, U>();
    test_is_same_rv_impl<const T, const U>();
    test_is_not_same_rv<const T, volatile U>();
    test_is_same_rv_impl<const T, const volatile U>();

    test_is_same_rv_impl<volatile T, U>();
    test_is_not_same_rv<volatile T, const U>();
    test_is_same_rv_impl<volatile T, volatile U>();
    test_is_not_same_rv<volatile T, const volatile U>();

    test_is_not_same_rv<const volatile T, U>();
    test_is_same_rv_impl<const volatile T, const U>();
    test_is_not_same_rv<const volatile T, volatile U>();
    test_is_same_rv_impl<const volatile T, const volatile U>();
}

template <typename T, typename U = T>
void test_is_same_rv_ref()
{
    test_is_same_rv_impl<T, U>();
    test_is_same_rv_impl<T, const U>();
    test_is_same_rv_impl<T, volatile U>();
    test_is_same_rv_impl<T, const volatile U>();

    test_is_same_rv_impl<const T, U>();
    test_is_same_rv_impl<const T, const U>();
    test_is_same_rv_impl<const T, volatile U>();
    test_is_same_rv_impl<const T, const volatile U>();

    test_is_same_rv_impl<volatile T, U>();
    test_is_same_rv_impl<volatile T, const U>();
    test_is_same_rv_impl<volatile T, volatile U>();
    test_is_same_rv_impl<volatile T, const volatile U>();

    test_is_same_rv_impl<const volatile T, U>();
    test_is_same_rv_impl<const volatile T, const U>();
    test_is_same_rv_impl<const volatile T, volatile U>();
    test_is_same_rv_impl<const volatile T, const volatile U>();
}

template <typename T>
struct OverloadTest
{
    void fn(phi::is_same_rv<T, int>)
    {}
    void fn(phi::false_type)
    {}
    void x()
    {
        fn(phi::false_type());
    }
};

struct A; // incomplete

TEST_CASE("is_same_rv")
{
    test_is_not_same_rv<int, void>();
    test_is_not_same_rv<void, class_type>();
    test_is_not_same_rv<class_type, int*>();
    test_is_not_same_rv<int*, int&>();
    test_is_not_same_rv<int&, int>();

    test_is_not_same_rv<int, const int>();
    test_is_not_same_rv<int, const volatile int>();
    test_is_not_same_rv<int, int&>();
    test_is_not_same_rv<int, const int&>();
    test_is_not_same_rv<int, volatile int&>();
    test_is_not_same_rv<int, const volatile int&>();
    test_is_not_same_rv<int, int&&>();
    test_is_not_same_rv<int, const int&&>();
    test_is_not_same_rv<int, volatile int&&>();
    test_is_not_same_rv<int, const volatile int&&>();

    OverloadTest<char> t;
    (void)t;

    test_is_same_rv<void>();
    test_is_same_rv<phi::nullptr_t>();
    test_is_same_rv<bool>();
    test_is_same_rv<char>();
    test_is_same_rv<signed char>();
    test_is_same_rv<unsigned char>();
    test_is_same_rv<short>();
    test_is_same_rv<unsigned short>();
    test_is_same_rv<int>();
    test_is_same_rv<unsigned int>();
    test_is_same_rv<long>();
    test_is_same_rv<unsigned long>();
    test_is_same_rv<long long>();
    test_is_same_rv<unsigned long long>();
    test_is_same_rv<float>();
    test_is_same_rv<double>();
    test_is_same_rv<long double>();
    test_is_same_rv<char8_t>();
    test_is_same_rv<char16_t>();
    test_is_same_rv<char32_t>();
    test_is_same_rv<wchar_t>();

    test_is_same_rv<phi::boolean>();
    test_is_same_rv<phi::integer<signed char>>();
    test_is_same_rv<phi::integer<unsigned char>>();
    test_is_same_rv<phi::integer<short>>();
    test_is_same_rv<phi::integer<unsigned short>>();
    test_is_same_rv<phi::integer<int>>();
    test_is_same_rv<phi::integer<unsigned int>>();
    test_is_same_rv<phi::integer<long>>();
    test_is_same_rv<phi::integer<unsigned long>>();
    test_is_same_rv<phi::integer<long long>>();
    test_is_same_rv<phi::integer<unsigned long long>>();
    test_is_same_rv<phi::floating_point<float>>();
    test_is_same_rv<phi::floating_point<double>>();
    test_is_same_rv<phi::floating_point<long double>>();

    test_is_same_rv<std::vector<int>>();
    test_is_same_rv<phi::scope_ptr<int>>();

    test_is_same_rv_ref<int&>();
    test_is_same_rv_ref<const int&>();
    test_is_same_rv_ref<volatile int&>();
    test_is_same_rv_ref<const volatile int&>();
    test_is_same_rv_ref<int&&>();
    test_is_same_rv_ref<const int&&>();
    test_is_same_rv_ref<volatile int&&>();
    test_is_same_rv_ref<const volatile int&&>();
    test_is_same_rv<int*>();
    test_is_same_rv<const int*>();
    test_is_same_rv<volatile int*>();
    test_is_same_rv<const volatile int*>();
    test_is_same_rv<int**>();
    test_is_same_rv<const int**>();
    test_is_same_rv<volatile int**>();
    test_is_same_rv<const volatile int**>();
    test_is_same_rv_ref<int*&>();
    test_is_same_rv_ref<const int*&>();
    test_is_same_rv_ref<volatile int*&>();
    test_is_same_rv_ref<const volatile int*&>();
    test_is_same_rv_ref<int*&&>();
    test_is_same_rv_ref<const int*&&>();
    test_is_same_rv_ref<volatile int*&&>();
    test_is_same_rv_ref<const volatile int*&&>();
    test_is_same_rv<void*>();
    test_is_same_rv<char[3]>();
    test_is_same_rv<char[]>();
    test_is_same_rv<char* [3]>();
    test_is_same_rv<char*[]>();
    test_is_same_rv<int(*)[3]>();
    test_is_same_rv<int(*)[]>();
    test_is_same_rv_ref<int(&)[3]>();
    test_is_same_rv_ref<int(&)[]>();
    test_is_same_rv_ref<int(&&)[3]>();
    test_is_same_rv_ref<int(&&)[]>();
    test_is_same_rv<char[3][2]>();
    test_is_same_rv<char[][2]>();
    test_is_same_rv<char* [3][2]>();
    test_is_same_rv<char*[][2]>();
    test_is_same_rv<int(*)[3][2]>();
    test_is_same_rv<int(*)[][2]>();
    test_is_same_rv_ref<int(&)[3][2]>();
    test_is_same_rv_ref<int(&)[][2]>();
    test_is_same_rv_ref<int(&&)[3][2]>();
    test_is_same_rv_ref<int(&&)[][2]>();
    test_is_same_rv<class_type>();
    test_is_same_rv<class_type[]>();
    test_is_same_rv<class_type[2]>();
    test_is_same_rv<template_type<void>>();
    test_is_same_rv<template_type<int>>();
    test_is_same_rv<template_type<class_type>>();
    test_is_same_rv<template_type<incomplete_type>>();
    test_is_same_rv<variadic_template<>>();
    test_is_same_rv<variadic_template<void>>();
    test_is_same_rv<variadic_template<int>>();
    test_is_same_rv<variadic_template<class_type>>();
    test_is_same_rv<variadic_template<incomplete_type>>();
    test_is_same_rv<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_same_rv<public_derived_from<base>>();
    test_is_same_rv<public_derived_from<derived>>();
    test_is_same_rv<public_derived_from<class_type>>();
    test_is_same_rv<private_derived_from<base>>();
    test_is_same_rv<private_derived_from<derived>>();
    test_is_same_rv<private_derived_from<class_type>>();
    test_is_same_rv<protected_derived_from<base>>();
    test_is_same_rv<protected_derived_from<derived>>();
    test_is_same_rv<protected_derived_from<class_type>>();
    test_is_same_rv<virtual_derived_from<base>>();
    test_is_same_rv<virtual_derived_from<derived>>();
    test_is_same_rv<virtual_derived_from<class_type>>();
    test_is_same_rv<union_type>();
    test_is_same_rv<non_empty_union>();
    test_is_same_rv<non_trivial_union>();
    test_is_same_rv<empty>();
    test_is_same_rv<not_empty>();
    test_is_same_rv<non_trivial>();
    test_is_same_rv<bit_zero>();
    test_is_same_rv<bit_one>();
    test_is_same_rv<base>();
    test_is_same_rv<derived>();
    test_is_same_rv<non_empty_base>();
    test_is_same_rv<empty_base>();
    test_is_same_rv<virtual_base>();
    test_is_same_rv<polymorphic>();
    test_is_same_rv<derived_polymorphic>();
    test_is_same_rv<abstract>();
    test_is_same_rv<public_abstract>();
    test_is_same_rv<private_abstract>();
    test_is_same_rv<protected_abstract>();
    test_is_same_rv<abstract_template<int>>();
    test_is_same_rv<abstract_template<double>>();
    test_is_same_rv<abstract_template<class_type>>();
    test_is_same_rv<abstract_template<incomplete_type>>();
    test_is_same_rv<public_abstract_deleted_destructor>();
    test_is_same_rv<protected_abstract_deleted_destructor>();
    test_is_same_rv<private_abstract_deleted_destructor>();
    test_is_same_rv<final_type>();
    test_is_same_rv<final_derived>();
    test_is_same_rv<public_destructor>();
    test_is_same_rv<protected_destructor>();
    test_is_same_rv<private_destructor>();
    test_is_same_rv<virtual_public_destructor>();
    test_is_same_rv<virtual_protected_destructor>();
    test_is_same_rv<virtual_private_destructor>();
    test_is_same_rv<pure_public_destructor>();
    test_is_same_rv<pure_protected_destructor>();
    test_is_same_rv<pure_private_destructor>();
    test_is_same_rv<deleted_public_destructor>();
    test_is_same_rv<deleted_protected_destructor>();
    test_is_same_rv<deleted_private_destructor>();
    test_is_same_rv<deleted_virtual_public_destructor>();
    test_is_same_rv<deleted_virtual_protected_destructor>();
    test_is_same_rv<deleted_virtual_private_destructor>();
    test_is_same_rv<explicit_class>();
    test_is_same_rv<nothrow_explicit_class>();
    test_is_same_rv<throw_explicit_class>();
    test_is_same_rv<throw_default_class>();
    test_is_same_rv<throw_copy_constructible_class>();
    test_is_same_rv<throw_move_constructible_class>();
    test_is_same_rv<throw_destructor>();
    test_is_same_rv<noexcept_explicit_class>();
    test_is_same_rv<except_explicit_class>();
    test_is_same_rv<noexcept_default_class>();
    test_is_same_rv<except_default_class>();
    test_is_same_rv<noexcept_copy_constructible_class>();
    test_is_same_rv<except_copy_constructible_class>();
    test_is_same_rv<noexcept_move_constructible_class>();
    test_is_same_rv<except_move_constructible_class>();
    test_is_same_rv<noexcept_copy_assign_class>();
    test_is_same_rv<except_copy_assign_class>();
    test_is_same_rv<noexcept_move_assign_class>();
    test_is_same_rv<except_move_assign_class>();
    test_is_same_rv<deleted_copy_assign_class>();
    test_is_same_rv<deleted_move_assign_class>();
    test_is_same_rv<noexcept_move_constructible_and_assignable_class>();
    test_is_same_rv<except_move_constructible_noexcept_move_assign_class>();
    test_is_same_rv<noexcept_move_constructible_except_move_assign_class>();
    test_is_same_rv<except_move_constructible_and_assign_class>();
    test_is_same_rv<implicit_to<int>>();
    test_is_same_rv<implicit_to<float>>();
    test_is_same_rv<implicit_to<class_type>>();
    test_is_same_rv<deleted_implicit_to<int>>();
    test_is_same_rv<deleted_implicit_to<float>>();
    test_is_same_rv<deleted_implicit_to<class_type>>();
    test_is_same_rv<explicit_to<int>>();
    test_is_same_rv<explicit_to<float>>();
    test_is_same_rv<explicit_to<class_type>>();
    test_is_same_rv<deleted_explicit_to<int>>();
    test_is_same_rv<deleted_explicit_to<float>>();
    test_is_same_rv<deleted_explicit_to<class_type>>();
    test_is_same_rv<ellipsis>();
    test_is_same_rv<deleted_ellipsis>();
    test_is_same_rv<copy_constructible_only_type>();
    test_is_same_rv<move_constructible_only_type>();
    test_is_same_rv<overloaded_operators>();
    test_is_same_rv<public_int_member>();
    test_is_same_rv<protected_int_member>();
    test_is_same_rv<private_int_member>();
    test_is_same_rv<public_static_int_member>();
    test_is_same_rv<protected_static_int_member>();
    test_is_same_rv<private_static_int_member>();
    test_is_same_rv<public_template_member<int>>();
    test_is_same_rv<public_template_member<float>>();
    test_is_same_rv<public_template_member<class_type>>();
    test_is_same_rv<protected_template_member<int>>();
    test_is_same_rv<protected_template_member<float>>();
    test_is_same_rv<protected_template_member<class_type>>();
    test_is_same_rv<private_template_member<int>>();
    test_is_same_rv<private_template_member<float>>();
    test_is_same_rv<private_template_member<class_type>>();
    test_is_same_rv<public_static_template_member<int>>();
    test_is_same_rv<public_static_template_member<float>>();
    test_is_same_rv<public_static_template_member<class_type>>();
    test_is_same_rv<protected_static_template_member<int>>();
    test_is_same_rv<protected_static_template_member<float>>();
    test_is_same_rv<protected_static_template_member<class_type>>();
    test_is_same_rv<private_static_template_member<int>>();
    test_is_same_rv<private_static_template_member<float>>();
    test_is_same_rv<private_static_template_member<class_type>>();
    test_is_same_rv<cannot_instantiate<int>>();
    test_is_same_rv<cannot_instantiate<float>>();
    test_is_same_rv<cannot_instantiate<class_type>>();
    test_is_same_rv<natural_alignment>();
    test_is_same_rv<Enum>();
    test_is_same_rv<EnumSigned>();
    test_is_same_rv<EnumUnsigned>();
    test_is_same_rv<EnumClass>();
    test_is_same_rv<EnumStruct>();
    test_is_same_rv_ref<function_type>();
    test_is_same_rv<function_ptr>();
    test_is_same_rv<member_object_ptr>();
    test_is_same_rv<member_function_ptr>();
    test_is_same_rv<lambda_type>();
    test_is_same_rv<lambda_noexcept_type>();
    test_is_same_rv<lambda_throws_type>();
    test_is_same_rv<incomplete_type>();
    test_is_same_rv<incomplete_template<void>>();
    test_is_same_rv<incomplete_template<int>>();
    test_is_same_rv<incomplete_template<class_type>>();
    test_is_same_rv<incomplete_template<incomplete_type>>();
    test_is_same_rv<incomplete_variadic_template<>>();
    test_is_same_rv<incomplete_variadic_template<void>>();
    test_is_same_rv<incomplete_variadic_template<int>>();
    test_is_same_rv<incomplete_variadic_template<class_type>>();
    test_is_same_rv<incomplete_variadic_template<incomplete_type>>();
    test_is_same_rv<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_same_rv<incomplete_union>();
    test_is_same_rv<IncompleteEnumSigned>();
    test_is_same_rv<IncompleteEnumUnsigned>();
    test_is_same_rv<IncompleteEnumClass>();
    test_is_same_rv<IncompleteEnumStruct>();
    test_is_same_rv<int class_type::*>();
    test_is_same_rv<float class_type::*>();
    test_is_same_rv<void * class_type::*>();
    test_is_same_rv<int * class_type::*>();
    test_is_same_rv<Enum class_type::*>();
    test_is_same_rv<not_empty class_type::*>();
    test_is_same_rv_ref<int class_type::*&>();
    test_is_same_rv_ref<float class_type::*&>();
    test_is_same_rv_ref<void * class_type::*&>();
    test_is_same_rv_ref<int * class_type::*&>();
    test_is_same_rv_ref<Enum class_type::*&>();
    test_is_same_rv_ref<not_empty class_type::*&>();
    test_is_same_rv_ref<int class_type::*&&>();
    test_is_same_rv_ref<float class_type::*&&>();
    test_is_same_rv_ref<void * class_type::*&&>();
    test_is_same_rv_ref<int * class_type::*&&>();
    test_is_same_rv_ref<Enum class_type::*&&>();
    test_is_same_rv_ref<not_empty class_type::*&&>();
    test_is_same_rv<non_default_constructible>();
    test_is_same_rv<non_copy_constructible>();
    test_is_same_rv<non_move_constructible>();
    test_is_same_rv<non_copy_assignable>();
    test_is_same_rv<non_move_assignable>();
    test_is_same_rv<non_assignable>();
    test_is_same_rv<non_copyable>();
    test_is_same_rv<non_moveable>();
    test_is_same_rv<non_constructible>();
    test_is_same_rv<non_destructible>();
    test_is_same_rv<tracked>();
    test_is_same_rv<trap_constructible>();
    test_is_same_rv<trap_implicit_conversion>();
    test_is_same_rv<trap_comma>();
    test_is_same_rv<trap_call>();
    test_is_same_rv<trap_self_assign>();
    test_is_same_rv<trap_deref>();
    test_is_same_rv<trap_array_subscript>();

#if PHI_HAS_EXTENSION_ZERO_SIZE_ARRAY()
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wzero-length-array")
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wpedantic")

    test_is_same_rv<int[0]>();

    PHI_GCC_SUPPRESS_WARNING_POP()
    PHI_CLANG_SUPPRESS_WARNING_POP()
#endif

    test_is_same_rv_ref<void()>();
    test_is_same_rv_ref<void()&>();
    test_is_same_rv_ref<void() &&>();
    test_is_same_rv_ref<void() const>();
    test_is_same_rv_ref<void() const&>();
    test_is_same_rv_ref<void() const&&>();
    test_is_same_rv_ref<void() volatile>();
    test_is_same_rv_ref<void() volatile&>();
    test_is_same_rv_ref<void() volatile&&>();
    test_is_same_rv_ref<void() const volatile>();
    test_is_same_rv_ref<void() const volatile&>();
    test_is_same_rv_ref<void() const volatile&&>();
    test_is_same_rv_ref<void() noexcept>();
    test_is_same_rv_ref<void()& noexcept>();
    test_is_same_rv_ref<void()&& noexcept>();
    test_is_same_rv_ref<void() const noexcept>();
    test_is_same_rv_ref<void() const& noexcept>();
    test_is_same_rv_ref<void() const&& noexcept>();
    test_is_same_rv_ref<void() volatile noexcept>();
    test_is_same_rv_ref<void() volatile& noexcept>();
    test_is_same_rv_ref<void() volatile&& noexcept>();
    test_is_same_rv_ref<void() const volatile noexcept>();
    test_is_same_rv_ref<void() const volatile& noexcept>();
    test_is_same_rv_ref<void() const volatile&& noexcept>();

    test_is_same_rv_ref<void(int)>();
    test_is_same_rv_ref<void(int)&>();
    test_is_same_rv_ref<void(int) &&>();
    test_is_same_rv_ref<void(int) const>();
    test_is_same_rv_ref<void(int) const&>();
    test_is_same_rv_ref<void(int) const&&>();
    test_is_same_rv_ref<void(int) volatile>();
    test_is_same_rv_ref<void(int) volatile&>();
    test_is_same_rv_ref<void(int) volatile&&>();
    test_is_same_rv_ref<void(int) const volatile>();
    test_is_same_rv_ref<void(int) const volatile&>();
    test_is_same_rv_ref<void(int) const volatile&&>();
    test_is_same_rv_ref<void(int) noexcept>();
    test_is_same_rv_ref<void(int)& noexcept>();
    test_is_same_rv_ref<void(int)&& noexcept>();
    test_is_same_rv_ref<void(int) const noexcept>();
    test_is_same_rv_ref<void(int) const& noexcept>();
    test_is_same_rv_ref<void(int) const&& noexcept>();
    test_is_same_rv_ref<void(int) volatile noexcept>();
    test_is_same_rv_ref<void(int) volatile& noexcept>();
    test_is_same_rv_ref<void(int) volatile&& noexcept>();
    test_is_same_rv_ref<void(int) const volatile noexcept>();
    test_is_same_rv_ref<void(int) const volatile& noexcept>();
    test_is_same_rv_ref<void(int) const volatile&& noexcept>();

    test_is_same_rv_ref<void(...)>();
    test_is_same_rv_ref<void(...)&>();
    test_is_same_rv_ref<void(...) &&>();
    test_is_same_rv_ref<void(...) const>();
    test_is_same_rv_ref<void(...) const&>();
    test_is_same_rv_ref<void(...) const&&>();
    test_is_same_rv_ref<void(...) volatile>();
    test_is_same_rv_ref<void(...) volatile&>();
    test_is_same_rv_ref<void(...) volatile&&>();
    test_is_same_rv_ref<void(...) const volatile>();
    test_is_same_rv_ref<void(...) const volatile&>();
    test_is_same_rv_ref<void(...) const volatile&&>();
    test_is_same_rv_ref<void(...) noexcept>();
    test_is_same_rv_ref<void(...)& noexcept>();
    test_is_same_rv_ref<void(...)&& noexcept>();
    test_is_same_rv_ref<void(...) const noexcept>();
    test_is_same_rv_ref<void(...) const& noexcept>();
    test_is_same_rv_ref<void(...) const&& noexcept>();
    test_is_same_rv_ref<void(...) volatile noexcept>();
    test_is_same_rv_ref<void(...) volatile& noexcept>();
    test_is_same_rv_ref<void(...) volatile&& noexcept>();
    test_is_same_rv_ref<void(...) const volatile noexcept>();
    test_is_same_rv_ref<void(...) const volatile& noexcept>();
    test_is_same_rv_ref<void(...) const volatile&& noexcept>();

    test_is_same_rv_ref<void(int, ...)>();
    test_is_same_rv_ref<void(int, ...)&>();
    test_is_same_rv_ref<void(int, ...) &&>();
    test_is_same_rv_ref<void(int, ...) const>();
    test_is_same_rv_ref<void(int, ...) const&>();
    test_is_same_rv_ref<void(int, ...) const&&>();
    test_is_same_rv_ref<void(int, ...) volatile>();
    test_is_same_rv_ref<void(int, ...) volatile&>();
    test_is_same_rv_ref<void(int, ...) volatile&&>();
    test_is_same_rv_ref<void(int, ...) const volatile>();
    test_is_same_rv_ref<void(int, ...) const volatile&>();
    test_is_same_rv_ref<void(int, ...) const volatile&&>();
    test_is_same_rv_ref<void(int, ...) noexcept>();
    test_is_same_rv_ref<void(int, ...)& noexcept>();
    test_is_same_rv_ref<void(int, ...)&& noexcept>();
    test_is_same_rv_ref<void(int, ...) const noexcept>();
    test_is_same_rv_ref<void(int, ...) const& noexcept>();
    test_is_same_rv_ref<void(int, ...) const&& noexcept>();
    test_is_same_rv_ref<void(int, ...) volatile noexcept>();
    test_is_same_rv_ref<void(int, ...) volatile& noexcept>();
    test_is_same_rv_ref<void(int, ...) volatile&& noexcept>();
    test_is_same_rv_ref<void(int, ...) const volatile noexcept>();
    test_is_same_rv_ref<void(int, ...) const volatile& noexcept>();
    test_is_same_rv_ref<void(int, ...) const volatile&& noexcept>();

    test_is_same_rv_ref<int()>();
    test_is_same_rv_ref<int()&>();
    test_is_same_rv_ref<int() &&>();
    test_is_same_rv_ref<int() const>();
    test_is_same_rv_ref<int() const&>();
    test_is_same_rv_ref<int() const&&>();
    test_is_same_rv_ref<int() volatile>();
    test_is_same_rv_ref<int() volatile&>();
    test_is_same_rv_ref<int() volatile&&>();
    test_is_same_rv_ref<int() const volatile>();
    test_is_same_rv_ref<int() const volatile&>();
    test_is_same_rv_ref<int() const volatile&&>();
    test_is_same_rv_ref<int() noexcept>();
    test_is_same_rv_ref<int()& noexcept>();
    test_is_same_rv_ref<int()&& noexcept>();
    test_is_same_rv_ref<int() const noexcept>();
    test_is_same_rv_ref<int() const& noexcept>();
    test_is_same_rv_ref<int() const&& noexcept>();
    test_is_same_rv_ref<int() volatile noexcept>();
    test_is_same_rv_ref<int() volatile& noexcept>();
    test_is_same_rv_ref<int() volatile&& noexcept>();
    test_is_same_rv_ref<int() const volatile noexcept>();
    test_is_same_rv_ref<int() const volatile& noexcept>();
    test_is_same_rv_ref<int() const volatile&& noexcept>();

    test_is_same_rv_ref<int(int)>();
    test_is_same_rv_ref<int(int)&>();
    test_is_same_rv_ref<int(int) &&>();
    test_is_same_rv_ref<int(int) const>();
    test_is_same_rv_ref<int(int) const&>();
    test_is_same_rv_ref<int(int) const&&>();
    test_is_same_rv_ref<int(int) volatile>();
    test_is_same_rv_ref<int(int) volatile&>();
    test_is_same_rv_ref<int(int) volatile&&>();
    test_is_same_rv_ref<int(int) const volatile>();
    test_is_same_rv_ref<int(int) const volatile&>();
    test_is_same_rv_ref<int(int) const volatile&&>();
    test_is_same_rv_ref<int(int) noexcept>();
    test_is_same_rv_ref<int(int)& noexcept>();
    test_is_same_rv_ref<int(int)&& noexcept>();
    test_is_same_rv_ref<int(int) const noexcept>();
    test_is_same_rv_ref<int(int) const& noexcept>();
    test_is_same_rv_ref<int(int) const&& noexcept>();
    test_is_same_rv_ref<int(int) volatile noexcept>();
    test_is_same_rv_ref<int(int) volatile& noexcept>();
    test_is_same_rv_ref<int(int) volatile&& noexcept>();
    test_is_same_rv_ref<int(int) const volatile noexcept>();
    test_is_same_rv_ref<int(int) const volatile& noexcept>();
    test_is_same_rv_ref<int(int) const volatile&& noexcept>();

    test_is_same_rv_ref<int(...)>();
    test_is_same_rv_ref<int(...)&>();
    test_is_same_rv_ref<int(...) &&>();
    test_is_same_rv_ref<int(...) const>();
    test_is_same_rv_ref<int(...) const&>();
    test_is_same_rv_ref<int(...) const&&>();
    test_is_same_rv_ref<int(...) volatile>();
    test_is_same_rv_ref<int(...) volatile&>();
    test_is_same_rv_ref<int(...) volatile&&>();
    test_is_same_rv_ref<int(...) const volatile>();
    test_is_same_rv_ref<int(...) const volatile&>();
    test_is_same_rv_ref<int(...) const volatile&&>();
    test_is_same_rv_ref<int(...) noexcept>();
    test_is_same_rv_ref<int(...)& noexcept>();
    test_is_same_rv_ref<int(...)&& noexcept>();
    test_is_same_rv_ref<int(...) const noexcept>();
    test_is_same_rv_ref<int(...) const& noexcept>();
    test_is_same_rv_ref<int(...) const&& noexcept>();
    test_is_same_rv_ref<int(...) volatile noexcept>();
    test_is_same_rv_ref<int(...) volatile& noexcept>();
    test_is_same_rv_ref<int(...) volatile&& noexcept>();
    test_is_same_rv_ref<int(...) const volatile noexcept>();
    test_is_same_rv_ref<int(...) const volatile& noexcept>();
    test_is_same_rv_ref<int(...) const volatile&& noexcept>();

    test_is_same_rv_ref<int(int, ...)>();
    test_is_same_rv_ref<int(int, ...)&>();
    test_is_same_rv_ref<int(int, ...) &&>();
    test_is_same_rv_ref<int(int, ...) const>();
    test_is_same_rv_ref<int(int, ...) const&>();
    test_is_same_rv_ref<int(int, ...) const&&>();
    test_is_same_rv_ref<int(int, ...) volatile>();
    test_is_same_rv_ref<int(int, ...) volatile&>();
    test_is_same_rv_ref<int(int, ...) volatile&&>();
    test_is_same_rv_ref<int(int, ...) const volatile>();
    test_is_same_rv_ref<int(int, ...) const volatile&>();
    test_is_same_rv_ref<int(int, ...) const volatile&&>();
    test_is_same_rv_ref<int(int, ...) noexcept>();
    test_is_same_rv_ref<int(int, ...)& noexcept>();
    test_is_same_rv_ref<int(int, ...)&& noexcept>();
    test_is_same_rv_ref<int(int, ...) const noexcept>();
    test_is_same_rv_ref<int(int, ...) const& noexcept>();
    test_is_same_rv_ref<int(int, ...) const&& noexcept>();
    test_is_same_rv_ref<int(int, ...) volatile noexcept>();
    test_is_same_rv_ref<int(int, ...) volatile& noexcept>();
    test_is_same_rv_ref<int(int, ...) volatile&& noexcept>();
    test_is_same_rv_ref<int(int, ...) const volatile noexcept>();
    test_is_same_rv_ref<int(int, ...) const volatile& noexcept>();
    test_is_same_rv_ref<int(int, ...) const volatile&& noexcept>();

    test_is_same_rv<void (*)()>();
    test_is_same_rv<void (*)() noexcept>();

    test_is_same_rv<void (*)(int)>();
    test_is_same_rv<void (*)(int) noexcept>();

    test_is_same_rv<void (*)(...)>();
    test_is_same_rv<void (*)(...) noexcept>();

    test_is_same_rv<void (*)(int, ...)>();
    test_is_same_rv<void (*)(int, ...) noexcept>();

    test_is_same_rv<int (*)()>();
    test_is_same_rv<int (*)() noexcept>();

    test_is_same_rv<int (*)(int)>();
    test_is_same_rv<int (*)(int) noexcept>();

    test_is_same_rv<int (*)(...)>();
    test_is_same_rv<int (*)(...) noexcept>();

    test_is_same_rv<int (*)(int, ...)>();
    test_is_same_rv<int (*)(int, ...) noexcept>();

    test_is_same_rv_ref<void (&)()>();
    test_is_same_rv_ref<void (&)() noexcept>();

    test_is_same_rv_ref<void (&)(int)>();
    test_is_same_rv_ref<void (&)(int) noexcept>();

    test_is_same_rv_ref<void (&)(...)>();
    test_is_same_rv_ref<void (&)(...) noexcept>();

    test_is_same_rv_ref<void (&)(int, ...)>();
    test_is_same_rv_ref<void (&)(int, ...) noexcept>();

    test_is_same_rv_ref<int (&)()>();
    test_is_same_rv_ref<int (&)() noexcept>();

    test_is_same_rv_ref<int (&)(int)>();
    test_is_same_rv_ref<int (&)(int) noexcept>();

    test_is_same_rv_ref<int (&)(...)>();
    test_is_same_rv_ref<int (&)(...) noexcept>();

    test_is_same_rv_ref<int (&)(int, ...)>();
    test_is_same_rv_ref<int (&)(int, ...) noexcept>();

    test_is_same_rv_ref<void(&&)()>();
    test_is_same_rv_ref<void(&&)() noexcept>();

    test_is_same_rv_ref<void(&&)(int)>();
    test_is_same_rv_ref<void(&&)(int) noexcept>();

    test_is_same_rv_ref<void(&&)(...)>();
    test_is_same_rv_ref<void(&&)(...) noexcept>();

    test_is_same_rv_ref<void(&&)(int, ...)>();
    test_is_same_rv_ref<void(&&)(int, ...) noexcept>();

    test_is_same_rv_ref<int(&&)()>();
    test_is_same_rv_ref<int(&&)() noexcept>();

    test_is_same_rv_ref<int(&&)(int)>();
    test_is_same_rv_ref<int(&&)(int) noexcept>();

    test_is_same_rv_ref<int(&&)(...)>();
    test_is_same_rv_ref<int(&&)(...) noexcept>();

    test_is_same_rv_ref<int(&&)(int, ...)>();
    test_is_same_rv_ref<int(&&)(int, ...) noexcept>();

    test_is_same_rv<void (class_type::*)()>();
    test_is_same_rv<void (class_type::*)()&>();
    test_is_same_rv<void (class_type::*)() &&>();
    test_is_same_rv<void (class_type::*)() const>();
    test_is_same_rv<void (class_type::*)() const&>();
    test_is_same_rv<void (class_type::*)() const&&>();
    test_is_same_rv<void (class_type::*)() noexcept>();
    test_is_same_rv<void (class_type::*)()& noexcept>();
    test_is_same_rv<void (class_type::*)()&& noexcept>();
    test_is_same_rv<void (class_type::*)() const noexcept>();
    test_is_same_rv<void (class_type::*)() const& noexcept>();
    test_is_same_rv<void (class_type::*)() const&& noexcept>();

    test_is_same_rv<void (class_type::*)(int)>();
    test_is_same_rv<void (class_type::*)(int)&>();
    test_is_same_rv<void (class_type::*)(int) &&>();
    test_is_same_rv<void (class_type::*)(int) const>();
    test_is_same_rv<void (class_type::*)(int) const&>();
    test_is_same_rv<void (class_type::*)(int) const&&>();
    test_is_same_rv<void (class_type::*)(int) noexcept>();
    test_is_same_rv<void (class_type::*)(int)& noexcept>();
    test_is_same_rv<void (class_type::*)(int)&& noexcept>();
    test_is_same_rv<void (class_type::*)(int) const noexcept>();
    test_is_same_rv<void (class_type::*)(int) const& noexcept>();
    test_is_same_rv<void (class_type::*)(int) const&& noexcept>();

    test_is_same_rv<void (class_type::*)(...)>();
    test_is_same_rv<void (class_type::*)(...)&>();
    test_is_same_rv<void (class_type::*)(...) &&>();
    test_is_same_rv<void (class_type::*)(...) const>();
    test_is_same_rv<void (class_type::*)(...) const&>();
    test_is_same_rv<void (class_type::*)(...) const&&>();
    test_is_same_rv<void (class_type::*)(...) noexcept>();
    test_is_same_rv<void (class_type::*)(...)& noexcept>();
    test_is_same_rv<void (class_type::*)(...)&& noexcept>();
    test_is_same_rv<void (class_type::*)(...) const noexcept>();
    test_is_same_rv<void (class_type::*)(...) const& noexcept>();
    test_is_same_rv<void (class_type::*)(...) const&& noexcept>();

    test_is_same_rv<void (class_type::*)(int, ...)>();
    test_is_same_rv<void (class_type::*)(int, ...)&>();
    test_is_same_rv<void (class_type::*)(int, ...) &&>();
    test_is_same_rv<void (class_type::*)(int, ...) const>();
    test_is_same_rv<void (class_type::*)(int, ...) const&>();
    test_is_same_rv<void (class_type::*)(int, ...) const&&>();
    test_is_same_rv<void (class_type::*)(int, ...) noexcept>();
    test_is_same_rv<void (class_type::*)(int, ...)& noexcept>();
    test_is_same_rv<void (class_type::*)(int, ...)&& noexcept>();
    test_is_same_rv<void (class_type::*)(int, ...) const noexcept>();
    test_is_same_rv<void (class_type::*)(int, ...) const& noexcept>();
    test_is_same_rv<void (class_type::*)(int, ...) const&& noexcept>();

    test_is_same_rv<int (class_type::*)()>();
    test_is_same_rv<int (class_type::*)()&>();
    test_is_same_rv<int (class_type::*)() &&>();
    test_is_same_rv<int (class_type::*)() const>();
    test_is_same_rv<int (class_type::*)() const&>();
    test_is_same_rv<int (class_type::*)() const&&>();
    test_is_same_rv<int (class_type::*)() noexcept>();
    test_is_same_rv<int (class_type::*)()& noexcept>();
    test_is_same_rv<int (class_type::*)()&& noexcept>();
    test_is_same_rv<int (class_type::*)() const noexcept>();
    test_is_same_rv<int (class_type::*)() const& noexcept>();
    test_is_same_rv<int (class_type::*)() const&& noexcept>();

    test_is_same_rv<int (class_type::*)(int)>();
    test_is_same_rv<int (class_type::*)(int)&>();
    test_is_same_rv<int (class_type::*)(int) &&>();
    test_is_same_rv<int (class_type::*)(int) const>();
    test_is_same_rv<int (class_type::*)(int) const&>();
    test_is_same_rv<int (class_type::*)(int) const&&>();
    test_is_same_rv<int (class_type::*)(int) noexcept>();
    test_is_same_rv<int (class_type::*)(int)& noexcept>();
    test_is_same_rv<int (class_type::*)(int)&& noexcept>();
    test_is_same_rv<int (class_type::*)(int) const noexcept>();
    test_is_same_rv<int (class_type::*)(int) const& noexcept>();
    test_is_same_rv<int (class_type::*)(int) const&& noexcept>();

    test_is_same_rv<int (class_type::*)(...)>();
    test_is_same_rv<int (class_type::*)(...)&>();
    test_is_same_rv<int (class_type::*)(...) &&>();
    test_is_same_rv<int (class_type::*)(...) const>();
    test_is_same_rv<int (class_type::*)(...) const&>();
    test_is_same_rv<int (class_type::*)(...) const&&>();
    test_is_same_rv<int (class_type::*)(...) noexcept>();
    test_is_same_rv<int (class_type::*)(...)& noexcept>();
    test_is_same_rv<int (class_type::*)(...)&& noexcept>();
    test_is_same_rv<int (class_type::*)(...) const noexcept>();
    test_is_same_rv<int (class_type::*)(...) const& noexcept>();
    test_is_same_rv<int (class_type::*)(...) const&& noexcept>();

    test_is_same_rv<int (class_type::*)(int, ...)>();
    test_is_same_rv<int (class_type::*)(int, ...)&>();
    test_is_same_rv<int (class_type::*)(int, ...) &&>();
    test_is_same_rv<int (class_type::*)(int, ...) const>();
    test_is_same_rv<int (class_type::*)(int, ...) const&>();
    test_is_same_rv<int (class_type::*)(int, ...) const&&>();
    test_is_same_rv<int (class_type::*)(int, ...) noexcept>();
    test_is_same_rv<int (class_type::*)(int, ...)& noexcept>();
    test_is_same_rv<int (class_type::*)(int, ...)&& noexcept>();
    test_is_same_rv<int (class_type::*)(int, ...) const noexcept>();
    test_is_same_rv<int (class_type::*)(int, ...) const& noexcept>();
    test_is_same_rv<int (class_type::*)(int, ...) const&& noexcept>();
}
