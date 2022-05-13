#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_same_rc.hpp>
#include <vector>

template <typename T, typename U>
void test_is_same_rc_impl()
{
    STATIC_REQUIRE(phi::is_same_rc<T, U>::value);
    STATIC_REQUIRE(phi::is_same_rc<U, T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<U, T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_rc_v<T, U>);
    STATIC_REQUIRE(phi::is_same_rc_v<U, T>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<U, T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same_rc<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same_rc<T, U>);
}

template <typename T, typename U>
void test_is_not_same_rc()
{
    STATIC_REQUIRE_FALSE(phi::is_same_rc<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same_rc<U, T>::value);
    STATIC_REQUIRE(phi::is_not_same_rc<T, U>::value);
    STATIC_REQUIRE(phi::is_not_same_rc<U, T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_same_rc_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_same_rc_v<U, T>);
    STATIC_REQUIRE(phi::is_not_same_rc_v<T, U>);
    STATIC_REQUIRE(phi::is_not_same_rc_v<U, T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same_rc<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same_rc<T, U>);
}

template <typename T, typename U = T>
void test_is_same_rc()
{
    // is_same_rc
    test_is_same_rc_impl<T, U>();
    test_is_same_rc_impl<T, const U>();
    test_is_not_same_rc<T, volatile U>();
    test_is_not_same_rc<T, const volatile U>();

    test_is_same_rc_impl<const T, U>();
    test_is_same_rc_impl<const T, const U>();
    test_is_not_same_rc<const T, volatile U>();
    test_is_not_same_rc<const T, const volatile U>();

    test_is_not_same_rc<volatile T, U>();
    test_is_not_same_rc<volatile T, const U>();
    test_is_same_rc_impl<volatile T, volatile U>();
    test_is_same_rc_impl<volatile T, const volatile U>();

    test_is_not_same_rc<const volatile T, U>();
    test_is_not_same_rc<const volatile T, const U>();
    test_is_same_rc_impl<const volatile T, volatile U>();
    test_is_same_rc_impl<const volatile T, const volatile U>();
}

template <typename T, typename U = T>
void test_is_same_rc_ref()
{
    test_is_same_rc_impl<T, U>();
    test_is_same_rc_impl<T, const U>();
    test_is_same_rc_impl<T, volatile U>();
    test_is_same_rc_impl<T, const volatile U>();

    test_is_same_rc_impl<const T, U>();
    test_is_same_rc_impl<const T, const U>();
    test_is_same_rc_impl<const T, volatile U>();
    test_is_same_rc_impl<const T, const volatile U>();

    test_is_same_rc_impl<volatile T, U>();
    test_is_same_rc_impl<volatile T, const U>();
    test_is_same_rc_impl<volatile T, volatile U>();
    test_is_same_rc_impl<volatile T, const volatile U>();

    test_is_same_rc_impl<const volatile T, U>();
    test_is_same_rc_impl<const volatile T, const U>();
    test_is_same_rc_impl<const volatile T, volatile U>();
    test_is_same_rc_impl<const volatile T, const volatile U>();
}

template <typename T>
struct OverloadTest
{
    void fn(phi::is_same_rc<T, int>)
    {}

    void fn(phi::false_type)
    {}

    void x()
    {
        fn(phi::false_type());
    }
};

struct A; // incomplete

TEST_CASE("is_same_rc")
{
    test_is_same_rc<A, A>();

    test_is_not_same_rc<int, void>();
    test_is_not_same_rc<void, class_type>();
    test_is_not_same_rc<class_type, int*>();
    test_is_not_same_rc<int*, int&>();
    test_is_not_same_rc<int&, int>();

    test_is_not_same_rc<int, volatile int>();
    test_is_not_same_rc<int, const volatile int>();
    test_is_not_same_rc<int, int&>();
    test_is_not_same_rc<int, const int&>();
    test_is_not_same_rc<int, volatile int&>();
    test_is_not_same_rc<int, const volatile int&>();
    test_is_not_same_rc<int, int&&>();
    test_is_not_same_rc<int, const int&&>();
    test_is_not_same_rc<int, volatile int&&>();
    test_is_not_same_rc<int, const volatile int&&>();

    OverloadTest<char> t;
    (void)t;

    test_is_same_rc<void>();
    test_is_same_rc<phi::nullptr_t>();
    test_is_same_rc<bool>();
    test_is_same_rc<char>();
    test_is_same_rc<signed char>();
    test_is_same_rc<unsigned char>();
    test_is_same_rc<short>();
    test_is_same_rc<unsigned short>();
    test_is_same_rc<int>();
    test_is_same_rc<unsigned int>();
    test_is_same_rc<long>();
    test_is_same_rc<unsigned long>();
    test_is_same_rc<long long>();
    test_is_same_rc<unsigned long long>();
    test_is_same_rc<float>();
    test_is_same_rc<double>();
    test_is_same_rc<long double>();
    test_is_same_rc<char8_t>();
    test_is_same_rc<char16_t>();
    test_is_same_rc<char32_t>();
    test_is_same_rc<wchar_t>();

    test_is_same_rc<phi::boolean>();
    test_is_same_rc<phi::integer<signed char>>();
    test_is_same_rc<phi::integer<unsigned char>>();
    test_is_same_rc<phi::integer<short>>();
    test_is_same_rc<phi::integer<unsigned short>>();
    test_is_same_rc<phi::integer<int>>();
    test_is_same_rc<phi::integer<unsigned int>>();
    test_is_same_rc<phi::integer<long>>();
    test_is_same_rc<phi::integer<unsigned long>>();
    test_is_same_rc<phi::integer<long long>>();
    test_is_same_rc<phi::integer<unsigned long long>>();
    test_is_same_rc<phi::floating_point<float>>();
    test_is_same_rc<phi::floating_point<double>>();
    test_is_same_rc<phi::floating_point<long double>>();

    test_is_same_rc<std::vector<int>>();
    test_is_same_rc<phi::scope_ptr<int>>();

    test_is_same_rc_ref<int&>();
    test_is_same_rc_ref<const int&>();
    test_is_same_rc_ref<volatile int&>();
    test_is_same_rc_ref<const volatile int&>();
    test_is_same_rc_ref<int&&>();
    test_is_same_rc_ref<const int&&>();
    test_is_same_rc_ref<volatile int&&>();
    test_is_same_rc_ref<const volatile int&&>();
    test_is_same_rc<int*>();
    test_is_same_rc<const int*>();
    test_is_same_rc<volatile int*>();
    test_is_same_rc<const volatile int*>();
    test_is_same_rc<int**>();
    test_is_same_rc<const int**>();
    test_is_same_rc<volatile int**>();
    test_is_same_rc<const volatile int**>();
    test_is_same_rc_ref<int*&>();
    test_is_same_rc_ref<const int*&>();
    test_is_same_rc_ref<volatile int*&>();
    test_is_same_rc_ref<const volatile int*&>();
    test_is_same_rc_ref<int*&&>();
    test_is_same_rc_ref<const int*&&>();
    test_is_same_rc_ref<volatile int*&&>();
    test_is_same_rc_ref<const volatile int*&&>();
    test_is_same_rc<void*>();
    test_is_same_rc<char[3]>();
    test_is_same_rc<char[]>();
    test_is_same_rc<char* [3]>();
    test_is_same_rc<char*[]>();
    test_is_same_rc<int(*)[3]>();
    test_is_same_rc<int(*)[]>();
    test_is_same_rc_ref<int(&)[3]>();
    test_is_same_rc_ref<int(&)[]>();
    test_is_same_rc_ref<int(&&)[3]>();
    test_is_same_rc_ref<int(&&)[]>();
    test_is_same_rc<char[3][2]>();
    test_is_same_rc<char[][2]>();
    test_is_same_rc<char* [3][2]>();
    test_is_same_rc<char*[][2]>();
    test_is_same_rc<int(*)[3][2]>();
    test_is_same_rc<int(*)[][2]>();
    test_is_same_rc_ref<int(&)[3][2]>();
    test_is_same_rc_ref<int(&)[][2]>();
    test_is_same_rc_ref<int(&&)[3][2]>();
    test_is_same_rc_ref<int(&&)[][2]>();
    test_is_same_rc<class_type>();
    test_is_same_rc<class_type[]>();
    test_is_same_rc<class_type[2]>();
    test_is_same_rc<template_type<void>>();
    test_is_same_rc<template_type<int>>();
    test_is_same_rc<template_type<class_type>>();
    test_is_same_rc<template_type<incomplete_type>>();
    test_is_same_rc<variadic_template<>>();
    test_is_same_rc<variadic_template<void>>();
    test_is_same_rc<variadic_template<int>>();
    test_is_same_rc<variadic_template<class_type>>();
    test_is_same_rc<variadic_template<incomplete_type>>();
    test_is_same_rc<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_same_rc<public_derived_from<base>>();
    test_is_same_rc<public_derived_from<derived>>();
    test_is_same_rc<public_derived_from<class_type>>();
    test_is_same_rc<private_derived_from<base>>();
    test_is_same_rc<private_derived_from<derived>>();
    test_is_same_rc<private_derived_from<class_type>>();
    test_is_same_rc<protected_derived_from<base>>();
    test_is_same_rc<protected_derived_from<derived>>();
    test_is_same_rc<protected_derived_from<class_type>>();
    test_is_same_rc<virtual_derived_from<base>>();
    test_is_same_rc<virtual_derived_from<derived>>();
    test_is_same_rc<virtual_derived_from<class_type>>();
    test_is_same_rc<union_type>();
    test_is_same_rc<non_empty_union>();
    test_is_same_rc<non_trivial_union>();
    test_is_same_rc<empty>();
    test_is_same_rc<not_empty>();
    test_is_same_rc<non_trivial>();
    test_is_same_rc<bit_zero>();
    test_is_same_rc<bit_one>();
    test_is_same_rc<base>();
    test_is_same_rc<derived>();
    test_is_same_rc<non_empty_base>();
    test_is_same_rc<empty_base>();
    test_is_same_rc<virtual_Base>();
    test_is_same_rc<polymorphic>();
    test_is_same_rc<derived_polymorphic>();
    test_is_same_rc<abstract>();
    test_is_same_rc<public_abstract>();
    test_is_same_rc<private_abstract>();
    test_is_same_rc<protected_abstract>();
    test_is_same_rc<abstract_template<int>>();
    test_is_same_rc<abstract_template<double>>();
    test_is_same_rc<abstract_template<class_type>>();
    test_is_same_rc<abstract_template<incomplete_type>>();
    test_is_same_rc<public_abstract_deleted_destructor>();
    test_is_same_rc<protected_abstract_deleted_destructor>();
    test_is_same_rc<private_abstract_deleted_destructor>();
    test_is_same_rc<final_type>();
    test_is_same_rc<final_derived>();
    test_is_same_rc<public_destructor>();
    test_is_same_rc<protected_destructor>();
    test_is_same_rc<private_destructor>();
    test_is_same_rc<virtual_public_destructor>();
    test_is_same_rc<virtual_protected_destructor>();
    test_is_same_rc<virtual_private_destructor>();
    test_is_same_rc<pure_public_destructor>();
    test_is_same_rc<pure_protected_destructor>();
    test_is_same_rc<pure_private_destructor>();
    test_is_same_rc<deleted_public_destructor>();
    test_is_same_rc<deleted_protected_destructor>();
    test_is_same_rc<deleted_private_destructor>();
    test_is_same_rc<deleted_virtual_public_destructor>();
    test_is_same_rc<deleted_virtual_protected_destructor>();
    test_is_same_rc<deleted_virtual_private_destructor>();
    test_is_same_rc<explicit_class>();
    test_is_same_rc<nothrow_explicit_class>();
    test_is_same_rc<throw_explicit_class>();
    test_is_same_rc<throw_default_class>();
    test_is_same_rc<throw_copy_constructible_class>();
    test_is_same_rc<throw_move_constructible_class>();
    test_is_same_rc<throw_destructor>();
    test_is_same_rc<noexcept_explicit_class>();
    test_is_same_rc<except_explicit_class>();
    test_is_same_rc<noexcept_default_class>();
    test_is_same_rc<except_default_class>();
    test_is_same_rc<noexcept_copy_constructible_class>();
    test_is_same_rc<except_copy_constructible_class>();
    test_is_same_rc<noexcept_move_constructible_class>();
    test_is_same_rc<except_move_constructible_class>();
    test_is_same_rc<noexcept_copy_assign_class>();
    test_is_same_rc<except_copy_assign_class>();
    test_is_same_rc<noexcept_move_assign_class>();
    test_is_same_rc<except_move_assign_class>();
    test_is_same_rc<deleted_copy_assign_class>();
    test_is_same_rc<deleted_move_assign_class>();
    test_is_same_rc<noexcept_move_constructible_and_assignable_class>();
    test_is_same_rc<except_move_constructible_noexcept_move_assign_class>();
    test_is_same_rc<noexcept_move_constructible_except_move_assign_class>();
    test_is_same_rc<except_move_constructible_and_assign_class>();
    test_is_same_rc<implicit_to<int>>();
    test_is_same_rc<implicit_to<float>>();
    test_is_same_rc<implicit_to<class_type>>();
    test_is_same_rc<deleted_implicit_to<int>>();
    test_is_same_rc<deleted_implicit_to<float>>();
    test_is_same_rc<deleted_implicit_to<class_type>>();
    test_is_same_rc<ExplicitTo<int>>();
    test_is_same_rc<ExplicitTo<float>>();
    test_is_same_rc<ExplicitTo<class_type>>();
    test_is_same_rc<deleted_explicit_to<int>>();
    test_is_same_rc<deleted_explicit_to<float>>();
    test_is_same_rc<deleted_explicit_to<class_type>>();
    test_is_same_rc<ellipsis>();
    test_is_same_rc<deleted_ellipsis>();
    test_is_same_rc<copy_constructible_only_type>();
    test_is_same_rc<move_constructible_only_type>();
    test_is_same_rc<overloaded_operators>();
    test_is_same_rc<public_int_member>();
    test_is_same_rc<protected_int_member>();
    test_is_same_rc<private_int_member>();
    test_is_same_rc<public_static_int_member>();
    test_is_same_rc<protected_static_int_member>();
    test_is_same_rc<private_static_int_member>();
    test_is_same_rc<public_template_member<int>>();
    test_is_same_rc<public_template_member<float>>();
    test_is_same_rc<public_template_member<class_type>>();
    test_is_same_rc<protected_template_member<int>>();
    test_is_same_rc<protected_template_member<float>>();
    test_is_same_rc<protected_template_member<class_type>>();
    test_is_same_rc<private_template_member<int>>();
    test_is_same_rc<private_template_member<float>>();
    test_is_same_rc<private_template_member<class_type>>();
    test_is_same_rc<public_static_tempalte_member<int>>();
    test_is_same_rc<public_static_tempalte_member<float>>();
    test_is_same_rc<public_static_tempalte_member<class_type>>();
    test_is_same_rc<protected_static_template_member<int>>();
    test_is_same_rc<protected_static_template_member<float>>();
    test_is_same_rc<protected_static_template_member<class_type>>();
    test_is_same_rc<private_static_template_member<int>>();
    test_is_same_rc<private_static_template_member<float>>();
    test_is_same_rc<private_static_template_member<class_type>>();
    test_is_same_rc<cannot_instantiate<int>>();
    test_is_same_rc<cannot_instantiate<float>>();
    test_is_same_rc<cannot_instantiate<class_type>>();
    test_is_same_rc<natural_alignment>();
    test_is_same_rc<enum_type>();
    test_is_same_rc<enum_signed>();
    test_is_same_rc<enum_unsigned>();
    test_is_same_rc<enum_class>();
    test_is_same_rc<enum_struct>();
    test_is_same_rc_ref<function_type>();
    test_is_same_rc<function_ptr>();
    test_is_same_rc<member_object_ptr>();
    test_is_same_rc<member_function_ptr>();
    test_is_same_rc<lambda_type>();
    test_is_same_rc<lambda_noexcept_type>();
    test_is_same_rc<lambda_throws_type>();
    test_is_same_rc<incomplete_type>();
    test_is_same_rc<incomplete_template<void>>();
    test_is_same_rc<incomplete_template<int>>();
    test_is_same_rc<incomplete_template<class_type>>();
    test_is_same_rc<incomplete_template<incomplete_type>>();
    test_is_same_rc<IncompleteVariadicTemplate<>>();
    test_is_same_rc<IncompleteVariadicTemplate<void>>();
    test_is_same_rc<IncompleteVariadicTemplate<int>>();
    test_is_same_rc<IncompleteVariadicTemplate<class_type>>();
    test_is_same_rc<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_same_rc<IncompleteVariadicTemplate<int, void, class_type, volatile char[]>>();
    test_is_same_rc<incomplete_union>();
    test_is_same_rc<incomplete_enum_signed>();
    test_is_same_rc<incomplete_enum_unsigned>();
    test_is_same_rc<incomplete_enum_class>();
    test_is_same_rc<incomplete_enum_struct>();
    test_is_same_rc<int class_type::*>();
    test_is_same_rc<float class_type::*>();
    test_is_same_rc<void * class_type::*>();
    test_is_same_rc<int * class_type::*>();
    test_is_same_rc<enum_type class_type::*>();
    test_is_same_rc<not_empty class_type::*>();
    test_is_same_rc_ref<int class_type::*&>();
    test_is_same_rc_ref<float class_type::*&>();
    test_is_same_rc_ref<void * class_type::*&>();
    test_is_same_rc_ref<int * class_type::*&>();
    test_is_same_rc_ref<enum_type class_type::*&>();
    test_is_same_rc_ref<not_empty class_type::*&>();
    test_is_same_rc_ref<int class_type::*&&>();
    test_is_same_rc_ref<float class_type::*&&>();
    test_is_same_rc_ref<void * class_type::*&&>();
    test_is_same_rc_ref<int * class_type::*&&>();
    test_is_same_rc_ref<enum_type class_type::*&&>();
    test_is_same_rc_ref<not_empty class_type::*&&>();
    test_is_same_rc<non_default_constructible>();
    test_is_same_rc<non_copy_constructible>();
    test_is_same_rc<non_move_constructible>();
    test_is_same_rc<non_copy_assignable>();
    test_is_same_rc<non_move_assignable>();
    test_is_same_rc<non_assignable>();
    test_is_same_rc<non_copyable>();
    test_is_same_rc<non_moveable>();
    test_is_same_rc<non_constructible>();
    test_is_same_rc<non_destructible>();
    test_is_same_rc<tracked>();
    test_is_same_rc<trap_constructible>();
    test_is_same_rc<trap_implicit_conversion>();
    test_is_same_rc<trap_comma>();
    test_is_same_rc<trap_call>();
    test_is_same_rc<trap_self_assign>();
    test_is_same_rc<trap_deref>();
    test_is_same_rc<trap_array_subscript>();

#if PHI_HAS_EXTENSION_ZERO_SIZE_ARRAY()
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wzero-length-array")
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wpedantic")

    test_is_same_rc<int[0]>();

    PHI_GCC_SUPPRESS_WARNING_POP()
    PHI_CLANG_SUPPRESS_WARNING_POP()
#endif

    test_is_same_rc_ref<void()>();
    test_is_same_rc_ref<void()&>();
    test_is_same_rc_ref<void() &&>();
    test_is_same_rc_ref<void() const>();
    test_is_same_rc_ref<void() const&>();
    test_is_same_rc_ref<void() const&&>();
    test_is_same_rc_ref<void() volatile>();
    test_is_same_rc_ref<void() volatile&>();
    test_is_same_rc_ref<void() volatile&&>();
    test_is_same_rc_ref<void() const volatile>();
    test_is_same_rc_ref<void() const volatile&>();
    test_is_same_rc_ref<void() const volatile&&>();
    test_is_same_rc_ref<void() noexcept>();
    test_is_same_rc_ref<void()& noexcept>();
    test_is_same_rc_ref<void()&& noexcept>();
    test_is_same_rc_ref<void() const noexcept>();
    test_is_same_rc_ref<void() const& noexcept>();
    test_is_same_rc_ref<void() const&& noexcept>();
    test_is_same_rc_ref<void() volatile noexcept>();
    test_is_same_rc_ref<void() volatile& noexcept>();
    test_is_same_rc_ref<void() volatile&& noexcept>();
    test_is_same_rc_ref<void() const volatile noexcept>();
    test_is_same_rc_ref<void() const volatile& noexcept>();
    test_is_same_rc_ref<void() const volatile&& noexcept>();

    test_is_same_rc_ref<void(int)>();
    test_is_same_rc_ref<void(int)&>();
    test_is_same_rc_ref<void(int) &&>();
    test_is_same_rc_ref<void(int) const>();
    test_is_same_rc_ref<void(int) const&>();
    test_is_same_rc_ref<void(int) const&&>();
    test_is_same_rc_ref<void(int) volatile>();
    test_is_same_rc_ref<void(int) volatile&>();
    test_is_same_rc_ref<void(int) volatile&&>();
    test_is_same_rc_ref<void(int) const volatile>();
    test_is_same_rc_ref<void(int) const volatile&>();
    test_is_same_rc_ref<void(int) const volatile&&>();
    test_is_same_rc_ref<void(int) noexcept>();
    test_is_same_rc_ref<void(int)& noexcept>();
    test_is_same_rc_ref<void(int)&& noexcept>();
    test_is_same_rc_ref<void(int) const noexcept>();
    test_is_same_rc_ref<void(int) const& noexcept>();
    test_is_same_rc_ref<void(int) const&& noexcept>();
    test_is_same_rc_ref<void(int) volatile noexcept>();
    test_is_same_rc_ref<void(int) volatile& noexcept>();
    test_is_same_rc_ref<void(int) volatile&& noexcept>();
    test_is_same_rc_ref<void(int) const volatile noexcept>();
    test_is_same_rc_ref<void(int) const volatile& noexcept>();
    test_is_same_rc_ref<void(int) const volatile&& noexcept>();

    test_is_same_rc_ref<void(...)>();
    test_is_same_rc_ref<void(...)&>();
    test_is_same_rc_ref<void(...) &&>();
    test_is_same_rc_ref<void(...) const>();
    test_is_same_rc_ref<void(...) const&>();
    test_is_same_rc_ref<void(...) const&&>();
    test_is_same_rc_ref<void(...) volatile>();
    test_is_same_rc_ref<void(...) volatile&>();
    test_is_same_rc_ref<void(...) volatile&&>();
    test_is_same_rc_ref<void(...) const volatile>();
    test_is_same_rc_ref<void(...) const volatile&>();
    test_is_same_rc_ref<void(...) const volatile&&>();
    test_is_same_rc_ref<void(...) noexcept>();
    test_is_same_rc_ref<void(...)& noexcept>();
    test_is_same_rc_ref<void(...)&& noexcept>();
    test_is_same_rc_ref<void(...) const noexcept>();
    test_is_same_rc_ref<void(...) const& noexcept>();
    test_is_same_rc_ref<void(...) const&& noexcept>();
    test_is_same_rc_ref<void(...) volatile noexcept>();
    test_is_same_rc_ref<void(...) volatile& noexcept>();
    test_is_same_rc_ref<void(...) volatile&& noexcept>();
    test_is_same_rc_ref<void(...) const volatile noexcept>();
    test_is_same_rc_ref<void(...) const volatile& noexcept>();
    test_is_same_rc_ref<void(...) const volatile&& noexcept>();

    test_is_same_rc_ref<void(int, ...)>();
    test_is_same_rc_ref<void(int, ...)&>();
    test_is_same_rc_ref<void(int, ...) &&>();
    test_is_same_rc_ref<void(int, ...) const>();
    test_is_same_rc_ref<void(int, ...) const&>();
    test_is_same_rc_ref<void(int, ...) const&&>();
    test_is_same_rc_ref<void(int, ...) volatile>();
    test_is_same_rc_ref<void(int, ...) volatile&>();
    test_is_same_rc_ref<void(int, ...) volatile&&>();
    test_is_same_rc_ref<void(int, ...) const volatile>();
    test_is_same_rc_ref<void(int, ...) const volatile&>();
    test_is_same_rc_ref<void(int, ...) const volatile&&>();
    test_is_same_rc_ref<void(int, ...) noexcept>();
    test_is_same_rc_ref<void(int, ...)& noexcept>();
    test_is_same_rc_ref<void(int, ...)&& noexcept>();
    test_is_same_rc_ref<void(int, ...) const noexcept>();
    test_is_same_rc_ref<void(int, ...) const& noexcept>();
    test_is_same_rc_ref<void(int, ...) const&& noexcept>();
    test_is_same_rc_ref<void(int, ...) volatile noexcept>();
    test_is_same_rc_ref<void(int, ...) volatile& noexcept>();
    test_is_same_rc_ref<void(int, ...) volatile&& noexcept>();
    test_is_same_rc_ref<void(int, ...) const volatile noexcept>();
    test_is_same_rc_ref<void(int, ...) const volatile& noexcept>();
    test_is_same_rc_ref<void(int, ...) const volatile&& noexcept>();

    test_is_same_rc_ref<int()>();
    test_is_same_rc_ref<int()&>();
    test_is_same_rc_ref<int() &&>();
    test_is_same_rc_ref<int() const>();
    test_is_same_rc_ref<int() const&>();
    test_is_same_rc_ref<int() const&&>();
    test_is_same_rc_ref<int() volatile>();
    test_is_same_rc_ref<int() volatile&>();
    test_is_same_rc_ref<int() volatile&&>();
    test_is_same_rc_ref<int() const volatile>();
    test_is_same_rc_ref<int() const volatile&>();
    test_is_same_rc_ref<int() const volatile&&>();
    test_is_same_rc_ref<int() noexcept>();
    test_is_same_rc_ref<int()& noexcept>();
    test_is_same_rc_ref<int()&& noexcept>();
    test_is_same_rc_ref<int() const noexcept>();
    test_is_same_rc_ref<int() const& noexcept>();
    test_is_same_rc_ref<int() const&& noexcept>();
    test_is_same_rc_ref<int() volatile noexcept>();
    test_is_same_rc_ref<int() volatile& noexcept>();
    test_is_same_rc_ref<int() volatile&& noexcept>();
    test_is_same_rc_ref<int() const volatile noexcept>();
    test_is_same_rc_ref<int() const volatile& noexcept>();
    test_is_same_rc_ref<int() const volatile&& noexcept>();

    test_is_same_rc_ref<int(int)>();
    test_is_same_rc_ref<int(int)&>();
    test_is_same_rc_ref<int(int) &&>();
    test_is_same_rc_ref<int(int) const>();
    test_is_same_rc_ref<int(int) const&>();
    test_is_same_rc_ref<int(int) const&&>();
    test_is_same_rc_ref<int(int) volatile>();
    test_is_same_rc_ref<int(int) volatile&>();
    test_is_same_rc_ref<int(int) volatile&&>();
    test_is_same_rc_ref<int(int) const volatile>();
    test_is_same_rc_ref<int(int) const volatile&>();
    test_is_same_rc_ref<int(int) const volatile&&>();
    test_is_same_rc_ref<int(int) noexcept>();
    test_is_same_rc_ref<int(int)& noexcept>();
    test_is_same_rc_ref<int(int)&& noexcept>();
    test_is_same_rc_ref<int(int) const noexcept>();
    test_is_same_rc_ref<int(int) const& noexcept>();
    test_is_same_rc_ref<int(int) const&& noexcept>();
    test_is_same_rc_ref<int(int) volatile noexcept>();
    test_is_same_rc_ref<int(int) volatile& noexcept>();
    test_is_same_rc_ref<int(int) volatile&& noexcept>();
    test_is_same_rc_ref<int(int) const volatile noexcept>();
    test_is_same_rc_ref<int(int) const volatile& noexcept>();
    test_is_same_rc_ref<int(int) const volatile&& noexcept>();

    test_is_same_rc_ref<int(...)>();
    test_is_same_rc_ref<int(...)&>();
    test_is_same_rc_ref<int(...) &&>();
    test_is_same_rc_ref<int(...) const>();
    test_is_same_rc_ref<int(...) const&>();
    test_is_same_rc_ref<int(...) const&&>();
    test_is_same_rc_ref<int(...) volatile>();
    test_is_same_rc_ref<int(...) volatile&>();
    test_is_same_rc_ref<int(...) volatile&&>();
    test_is_same_rc_ref<int(...) const volatile>();
    test_is_same_rc_ref<int(...) const volatile&>();
    test_is_same_rc_ref<int(...) const volatile&&>();
    test_is_same_rc_ref<int(...) noexcept>();
    test_is_same_rc_ref<int(...)& noexcept>();
    test_is_same_rc_ref<int(...)&& noexcept>();
    test_is_same_rc_ref<int(...) const noexcept>();
    test_is_same_rc_ref<int(...) const& noexcept>();
    test_is_same_rc_ref<int(...) const&& noexcept>();
    test_is_same_rc_ref<int(...) volatile noexcept>();
    test_is_same_rc_ref<int(...) volatile& noexcept>();
    test_is_same_rc_ref<int(...) volatile&& noexcept>();
    test_is_same_rc_ref<int(...) const volatile noexcept>();
    test_is_same_rc_ref<int(...) const volatile& noexcept>();
    test_is_same_rc_ref<int(...) const volatile&& noexcept>();

    test_is_same_rc_ref<int(int, ...)>();
    test_is_same_rc_ref<int(int, ...)&>();
    test_is_same_rc_ref<int(int, ...) &&>();
    test_is_same_rc_ref<int(int, ...) const>();
    test_is_same_rc_ref<int(int, ...) const&>();
    test_is_same_rc_ref<int(int, ...) const&&>();
    test_is_same_rc_ref<int(int, ...) volatile>();
    test_is_same_rc_ref<int(int, ...) volatile&>();
    test_is_same_rc_ref<int(int, ...) volatile&&>();
    test_is_same_rc_ref<int(int, ...) const volatile>();
    test_is_same_rc_ref<int(int, ...) const volatile&>();
    test_is_same_rc_ref<int(int, ...) const volatile&&>();
    test_is_same_rc_ref<int(int, ...) noexcept>();
    test_is_same_rc_ref<int(int, ...)& noexcept>();
    test_is_same_rc_ref<int(int, ...)&& noexcept>();
    test_is_same_rc_ref<int(int, ...) const noexcept>();
    test_is_same_rc_ref<int(int, ...) const& noexcept>();
    test_is_same_rc_ref<int(int, ...) const&& noexcept>();
    test_is_same_rc_ref<int(int, ...) volatile noexcept>();
    test_is_same_rc_ref<int(int, ...) volatile& noexcept>();
    test_is_same_rc_ref<int(int, ...) volatile&& noexcept>();
    test_is_same_rc_ref<int(int, ...) const volatile noexcept>();
    test_is_same_rc_ref<int(int, ...) const volatile& noexcept>();
    test_is_same_rc_ref<int(int, ...) const volatile&& noexcept>();

    test_is_same_rc<void (*)()>();
    test_is_same_rc<void (*)() noexcept>();

    test_is_same_rc<void (*)(int)>();
    test_is_same_rc<void (*)(int) noexcept>();

    test_is_same_rc<void (*)(...)>();
    test_is_same_rc<void (*)(...) noexcept>();

    test_is_same_rc<void (*)(int, ...)>();
    test_is_same_rc<void (*)(int, ...) noexcept>();

    test_is_same_rc<int (*)()>();
    test_is_same_rc<int (*)() noexcept>();

    test_is_same_rc<int (*)(int)>();
    test_is_same_rc<int (*)(int) noexcept>();

    test_is_same_rc<int (*)(...)>();
    test_is_same_rc<int (*)(...) noexcept>();

    test_is_same_rc<int (*)(int, ...)>();
    test_is_same_rc<int (*)(int, ...) noexcept>();

    test_is_same_rc_ref<void (&)()>();
    test_is_same_rc_ref<void (&)() noexcept>();

    test_is_same_rc_ref<void (&)(int)>();
    test_is_same_rc_ref<void (&)(int) noexcept>();

    test_is_same_rc_ref<void (&)(...)>();
    test_is_same_rc_ref<void (&)(...) noexcept>();

    test_is_same_rc_ref<void (&)(int, ...)>();
    test_is_same_rc_ref<void (&)(int, ...) noexcept>();

    test_is_same_rc_ref<int (&)()>();
    test_is_same_rc_ref<int (&)() noexcept>();

    test_is_same_rc_ref<int (&)(int)>();
    test_is_same_rc_ref<int (&)(int) noexcept>();

    test_is_same_rc_ref<int (&)(...)>();
    test_is_same_rc_ref<int (&)(...) noexcept>();

    test_is_same_rc_ref<int (&)(int, ...)>();
    test_is_same_rc_ref<int (&)(int, ...) noexcept>();

    test_is_same_rc_ref<void(&&)()>();
    test_is_same_rc_ref<void(&&)() noexcept>();

    test_is_same_rc_ref<void(&&)(int)>();
    test_is_same_rc_ref<void(&&)(int) noexcept>();

    test_is_same_rc_ref<void(&&)(...)>();
    test_is_same_rc_ref<void(&&)(...) noexcept>();

    test_is_same_rc_ref<void(&&)(int, ...)>();
    test_is_same_rc_ref<void(&&)(int, ...) noexcept>();

    test_is_same_rc_ref<int(&&)()>();
    test_is_same_rc_ref<int(&&)() noexcept>();

    test_is_same_rc_ref<int(&&)(int)>();
    test_is_same_rc_ref<int(&&)(int) noexcept>();

    test_is_same_rc_ref<int(&&)(...)>();
    test_is_same_rc_ref<int(&&)(...) noexcept>();

    test_is_same_rc_ref<int(&&)(int, ...)>();
    test_is_same_rc_ref<int(&&)(int, ...) noexcept>();

    test_is_same_rc<void (class_type::*)()>();
    test_is_same_rc<void (class_type::*)()&>();
    test_is_same_rc<void (class_type::*)() &&>();
    test_is_same_rc<void (class_type::*)() const>();
    test_is_same_rc<void (class_type::*)() const&>();
    test_is_same_rc<void (class_type::*)() const&&>();
    test_is_same_rc<void (class_type::*)() noexcept>();
    test_is_same_rc<void (class_type::*)()& noexcept>();
    test_is_same_rc<void (class_type::*)()&& noexcept>();
    test_is_same_rc<void (class_type::*)() const noexcept>();
    test_is_same_rc<void (class_type::*)() const& noexcept>();
    test_is_same_rc<void (class_type::*)() const&& noexcept>();

    test_is_same_rc<void (class_type::*)(int)>();
    test_is_same_rc<void (class_type::*)(int)&>();
    test_is_same_rc<void (class_type::*)(int) &&>();
    test_is_same_rc<void (class_type::*)(int) const>();
    test_is_same_rc<void (class_type::*)(int) const&>();
    test_is_same_rc<void (class_type::*)(int) const&&>();
    test_is_same_rc<void (class_type::*)(int) noexcept>();
    test_is_same_rc<void (class_type::*)(int)& noexcept>();
    test_is_same_rc<void (class_type::*)(int)&& noexcept>();
    test_is_same_rc<void (class_type::*)(int) const noexcept>();
    test_is_same_rc<void (class_type::*)(int) const& noexcept>();
    test_is_same_rc<void (class_type::*)(int) const&& noexcept>();

    test_is_same_rc<void (class_type::*)(...)>();
    test_is_same_rc<void (class_type::*)(...)&>();
    test_is_same_rc<void (class_type::*)(...) &&>();
    test_is_same_rc<void (class_type::*)(...) const>();
    test_is_same_rc<void (class_type::*)(...) const&>();
    test_is_same_rc<void (class_type::*)(...) const&&>();
    test_is_same_rc<void (class_type::*)(...) noexcept>();
    test_is_same_rc<void (class_type::*)(...)& noexcept>();
    test_is_same_rc<void (class_type::*)(...)&& noexcept>();
    test_is_same_rc<void (class_type::*)(...) const noexcept>();
    test_is_same_rc<void (class_type::*)(...) const& noexcept>();
    test_is_same_rc<void (class_type::*)(...) const&& noexcept>();

    test_is_same_rc<void (class_type::*)(int, ...)>();
    test_is_same_rc<void (class_type::*)(int, ...)&>();
    test_is_same_rc<void (class_type::*)(int, ...) &&>();
    test_is_same_rc<void (class_type::*)(int, ...) const>();
    test_is_same_rc<void (class_type::*)(int, ...) const&>();
    test_is_same_rc<void (class_type::*)(int, ...) const&&>();
    test_is_same_rc<void (class_type::*)(int, ...) noexcept>();
    test_is_same_rc<void (class_type::*)(int, ...)& noexcept>();
    test_is_same_rc<void (class_type::*)(int, ...)&& noexcept>();
    test_is_same_rc<void (class_type::*)(int, ...) const noexcept>();
    test_is_same_rc<void (class_type::*)(int, ...) const& noexcept>();
    test_is_same_rc<void (class_type::*)(int, ...) const&& noexcept>();

    test_is_same_rc<int (class_type::*)()>();
    test_is_same_rc<int (class_type::*)()&>();
    test_is_same_rc<int (class_type::*)() &&>();
    test_is_same_rc<int (class_type::*)() const>();
    test_is_same_rc<int (class_type::*)() const&>();
    test_is_same_rc<int (class_type::*)() const&&>();
    test_is_same_rc<int (class_type::*)() noexcept>();
    test_is_same_rc<int (class_type::*)()& noexcept>();
    test_is_same_rc<int (class_type::*)()&& noexcept>();
    test_is_same_rc<int (class_type::*)() const noexcept>();
    test_is_same_rc<int (class_type::*)() const& noexcept>();
    test_is_same_rc<int (class_type::*)() const&& noexcept>();

    test_is_same_rc<int (class_type::*)(int)>();
    test_is_same_rc<int (class_type::*)(int)&>();
    test_is_same_rc<int (class_type::*)(int) &&>();
    test_is_same_rc<int (class_type::*)(int) const>();
    test_is_same_rc<int (class_type::*)(int) const&>();
    test_is_same_rc<int (class_type::*)(int) const&&>();
    test_is_same_rc<int (class_type::*)(int) noexcept>();
    test_is_same_rc<int (class_type::*)(int)& noexcept>();
    test_is_same_rc<int (class_type::*)(int)&& noexcept>();
    test_is_same_rc<int (class_type::*)(int) const noexcept>();
    test_is_same_rc<int (class_type::*)(int) const& noexcept>();
    test_is_same_rc<int (class_type::*)(int) const&& noexcept>();

    test_is_same_rc<int (class_type::*)(...)>();
    test_is_same_rc<int (class_type::*)(...)&>();
    test_is_same_rc<int (class_type::*)(...) &&>();
    test_is_same_rc<int (class_type::*)(...) const>();
    test_is_same_rc<int (class_type::*)(...) const&>();
    test_is_same_rc<int (class_type::*)(...) const&&>();
    test_is_same_rc<int (class_type::*)(...) noexcept>();
    test_is_same_rc<int (class_type::*)(...)& noexcept>();
    test_is_same_rc<int (class_type::*)(...)&& noexcept>();
    test_is_same_rc<int (class_type::*)(...) const noexcept>();
    test_is_same_rc<int (class_type::*)(...) const& noexcept>();
    test_is_same_rc<int (class_type::*)(...) const&& noexcept>();

    test_is_same_rc<int (class_type::*)(int, ...)>();
    test_is_same_rc<int (class_type::*)(int, ...)&>();
    test_is_same_rc<int (class_type::*)(int, ...) &&>();
    test_is_same_rc<int (class_type::*)(int, ...) const>();
    test_is_same_rc<int (class_type::*)(int, ...) const&>();
    test_is_same_rc<int (class_type::*)(int, ...) const&&>();
    test_is_same_rc<int (class_type::*)(int, ...) noexcept>();
    test_is_same_rc<int (class_type::*)(int, ...)& noexcept>();
    test_is_same_rc<int (class_type::*)(int, ...)&& noexcept>();
    test_is_same_rc<int (class_type::*)(int, ...) const noexcept>();
    test_is_same_rc<int (class_type::*)(int, ...) const& noexcept>();
    test_is_same_rc<int (class_type::*)(int, ...) const&& noexcept>();
}
