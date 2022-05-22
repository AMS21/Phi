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
#include <phi/type_traits/is_same.hpp>
#include <type_traits>
#include <vector>

template <typename T, typename U>
void test_is_same_impl()
{
    STATIC_REQUIRE(phi::is_same<T, U>::value);
    STATIC_REQUIRE(phi::is_same<U, T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same<U, T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_v<T, U>);
    STATIC_REQUIRE(phi::is_same_v<U, T>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<U, T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same<T, U>);
}

template <typename T, typename U>
void test_is_not_same()
{
    STATIC_REQUIRE_FALSE(phi::is_same<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same<U, T>::value);
    STATIC_REQUIRE(phi::is_not_same<T, U>::value);
    STATIC_REQUIRE(phi::is_not_same<U, T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_same_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_same_v<U, T>);
    STATIC_REQUIRE(phi::is_not_same_v<T, U>);
    STATIC_REQUIRE(phi::is_not_same_v<U, T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same<T, U>);
}

template <typename T, typename U = T>
void test_is_same()
{
    test_is_same_impl<T, U>();
    test_is_not_same<T, const U>();
    test_is_not_same<T, volatile U>();
    test_is_not_same<T, const volatile U>();

    test_is_not_same<const T, U>();
    test_is_same_impl<const T, const U>();
    test_is_not_same<const T, volatile U>();
    test_is_not_same<const T, const volatile U>();

    test_is_not_same<volatile T, U>();
    test_is_not_same<volatile T, const U>();
    test_is_same_impl<volatile T, volatile U>();
    test_is_not_same<volatile T, const volatile U>();

    test_is_not_same<const volatile T, U>();
    test_is_not_same<const volatile T, const U>();
    test_is_not_same<const volatile T, volatile U>();
    test_is_same_impl<const volatile T, const volatile U>();
}

template <typename T, typename U = T>
void test_is_same_ref()
{
    test_is_same_impl<T, U>();
    test_is_same_impl<T, const U>();
    test_is_same_impl<T, volatile U>();
    test_is_same_impl<T, const volatile U>();

    test_is_same_impl<const T, U>();
    test_is_same_impl<const T, const U>();
    test_is_same_impl<const T, volatile U>();
    test_is_same_impl<const T, const volatile U>();

    test_is_same_impl<volatile T, U>();
    test_is_same_impl<volatile T, const U>();
    test_is_same_impl<volatile T, volatile U>();
    test_is_same_impl<volatile T, const volatile U>();

    test_is_same_impl<const volatile T, U>();
    test_is_same_impl<const volatile T, const U>();
    test_is_same_impl<const volatile T, volatile U>();
    test_is_same_impl<const volatile T, const volatile U>();
}

template <typename T>
struct OverloadTest
{
    void fn(phi::is_same<T, int>)
    {}
    void fn(phi::false_type)
    {}
    void x()
    {
        fn(phi::false_type());
    }
};

struct A; // incomplete

TEST_CASE("is_same")
{
    test_is_not_same<int, void>();
    test_is_not_same<void, class_type>();
    test_is_not_same<class_type, int*>();
    test_is_not_same<int*, int&>();
    test_is_not_same<int&, int>();

    test_is_not_same<int, const int>();
    test_is_not_same<int, volatile int>();
    test_is_not_same<int, const volatile int>();
    test_is_not_same<int, int&>();
    test_is_not_same<int, const int&>();
    test_is_not_same<int, volatile int&>();
    test_is_not_same<int, const volatile int&>();
    test_is_not_same<int, int&&>();
    test_is_not_same<int, const int&&>();
    test_is_not_same<int, volatile int&&>();
    test_is_not_same<int, const volatile int&&>();

    OverloadTest<char> t;
    (void)t;

    test_is_same<void>();
    test_is_same<phi::nullptr_t>();
    test_is_same<bool>();
    test_is_same<char>();
    test_is_same<signed char>();
    test_is_same<unsigned char>();
    test_is_same<short>();
    test_is_same<unsigned short>();
    test_is_same<int>();
    test_is_same<unsigned int>();
    test_is_same<long>();
    test_is_same<unsigned long>();
    test_is_same<long long>();
    test_is_same<unsigned long long>();
    test_is_same<float>();
    test_is_same<double>();
    test_is_same<long double>();
    test_is_same<char8_t>();
    test_is_same<char16_t>();
    test_is_same<char32_t>();
    test_is_same<wchar_t>();

    test_is_same<phi::boolean>();
    test_is_same<phi::integer<signed char>>();
    test_is_same<phi::integer<unsigned char>>();
    test_is_same<phi::integer<short>>();
    test_is_same<phi::integer<unsigned short>>();
    test_is_same<phi::integer<int>>();
    test_is_same<phi::integer<unsigned int>>();
    test_is_same<phi::integer<long>>();
    test_is_same<phi::integer<unsigned long>>();
    test_is_same<phi::integer<long long>>();
    test_is_same<phi::integer<unsigned long long>>();
    test_is_same<phi::floating_point<float>>();
    test_is_same<phi::floating_point<double>>();
    test_is_same<phi::floating_point<long double>>();

    test_is_same<std::vector<int>>();
    test_is_same<phi::scope_ptr<int>>();

    test_is_same_ref<int&>();
    test_is_same_ref<const int&>();
    test_is_same_ref<volatile int&>();
    test_is_same_ref<const volatile int&>();
    test_is_same_ref<int&&>();
    test_is_same_ref<const int&&>();
    test_is_same_ref<volatile int&&>();
    test_is_same_ref<const volatile int&&>();
    test_is_same<int*>();
    test_is_same<const int*>();
    test_is_same<volatile int*>();
    test_is_same<const volatile int*>();
    test_is_same<int**>();
    test_is_same<const int**>();
    test_is_same<volatile int**>();
    test_is_same<const volatile int**>();
    test_is_same_ref<int*&>();
    test_is_same_ref<const int*&>();
    test_is_same_ref<volatile int*&>();
    test_is_same_ref<const volatile int*&>();
    test_is_same_ref<int*&&>();
    test_is_same_ref<const int*&&>();
    test_is_same_ref<volatile int*&&>();
    test_is_same_ref<const volatile int*&&>();
    test_is_same<void*>();
    test_is_same<char[3]>();
    test_is_same<char[]>();
    test_is_same<char* [3]>();
    test_is_same<char*[]>();
    test_is_same<int(*)[3]>();
    test_is_same<int(*)[]>();
    test_is_same_ref<int(&)[3]>();
    test_is_same_ref<int(&)[]>();
    test_is_same_ref<int(&&)[3]>();
    test_is_same_ref<int(&&)[]>();
    test_is_same<char[3][2]>();
    test_is_same<char[][2]>();
    test_is_same<char* [3][2]>();
    test_is_same<char*[][2]>();
    test_is_same<int(*)[3][2]>();
    test_is_same<int(*)[][2]>();
    test_is_same_ref<int(&)[3][2]>();
    test_is_same_ref<int(&)[][2]>();
    test_is_same_ref<int(&&)[3][2]>();
    test_is_same_ref<int(&&)[][2]>();
    test_is_same<class_type>();
    test_is_same<class_type[]>();
    test_is_same<class_type[2]>();
    test_is_same<template_type<void>>();
    test_is_same<template_type<int>>();
    test_is_same<template_type<class_type>>();
    test_is_same<template_type<incomplete_type>>();
    test_is_same<variadic_template<>>();
    test_is_same<variadic_template<void>>();
    test_is_same<variadic_template<int>>();
    test_is_same<variadic_template<class_type>>();
    test_is_same<variadic_template<incomplete_type>>();
    test_is_same<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_same<public_derived_from<base>>();
    test_is_same<public_derived_from<derived>>();
    test_is_same<public_derived_from<class_type>>();
    test_is_same<private_derived_from<base>>();
    test_is_same<private_derived_from<derived>>();
    test_is_same<private_derived_from<class_type>>();
    test_is_same<protected_derived_from<base>>();
    test_is_same<protected_derived_from<derived>>();
    test_is_same<protected_derived_from<class_type>>();
    test_is_same<virtual_derived_from<base>>();
    test_is_same<virtual_derived_from<derived>>();
    test_is_same<virtual_derived_from<class_type>>();
    test_is_same<union_type>();
    test_is_same<non_empty_union>();
    test_is_same<non_trivial_union>();
    test_is_same<empty>();
    test_is_same<not_empty>();
    test_is_same<non_trivial>();
    test_is_same<bit_zero>();
    test_is_same<bit_one>();
    test_is_same<base>();
    test_is_same<derived>();
    test_is_same<non_empty_base>();
    test_is_same<empty_base>();
    test_is_same<virtual_base>();
    test_is_same<polymorphic>();
    test_is_same<derived_polymorphic>();
    test_is_same<abstract>();
    test_is_same<public_abstract>();
    test_is_same<private_abstract>();
    test_is_same<protected_abstract>();
    test_is_same<abstract_template<int>>();
    test_is_same<abstract_template<double>>();
    test_is_same<abstract_template<class_type>>();
    test_is_same<abstract_template<incomplete_type>>();
    test_is_same<public_abstract_deleted_destructor>();
    test_is_same<protected_abstract_deleted_destructor>();
    test_is_same<private_abstract_deleted_destructor>();
    test_is_same<final_type>();
    test_is_same<final_derived>();
    test_is_same<public_destructor>();
    test_is_same<protected_destructor>();
    test_is_same<private_destructor>();
    test_is_same<virtual_public_destructor>();
    test_is_same<virtual_protected_destructor>();
    test_is_same<virtual_private_destructor>();
    test_is_same<pure_public_destructor>();
    test_is_same<pure_protected_destructor>();
    test_is_same<pure_private_destructor>();
    test_is_same<deleted_public_destructor>();
    test_is_same<deleted_protected_destructor>();
    test_is_same<deleted_private_destructor>();
    test_is_same<deleted_virtual_public_destructor>();
    test_is_same<deleted_virtual_protected_destructor>();
    test_is_same<deleted_virtual_private_destructor>();
    test_is_same<explicit_class>();
    test_is_same<nothrow_explicit_class>();
    test_is_same<throw_explicit_class>();
    test_is_same<throw_default_class>();
    test_is_same<throw_copy_constructible_class>();
    test_is_same<throw_move_constructible_class>();
    test_is_same<throw_destructor>();
    test_is_same<noexcept_explicit_class>();
    test_is_same<except_explicit_class>();
    test_is_same<noexcept_default_class>();
    test_is_same<except_default_class>();
    test_is_same<noexcept_copy_constructible_class>();
    test_is_same<except_copy_constructible_class>();
    test_is_same<noexcept_move_constructible_class>();
    test_is_same<except_move_constructible_class>();
    test_is_same<noexcept_copy_assign_class>();
    test_is_same<except_copy_assign_class>();
    test_is_same<noexcept_move_assign_class>();
    test_is_same<except_move_assign_class>();
    test_is_same<deleted_copy_assign_class>();
    test_is_same<deleted_move_assign_class>();
    test_is_same<noexcept_move_constructible_and_assignable_class>();
    test_is_same<except_move_constructible_noexcept_move_assign_class>();
    test_is_same<noexcept_move_constructible_except_move_assign_class>();
    test_is_same<except_move_constructible_and_assign_class>();
    test_is_same<implicit_to<int>>();
    test_is_same<implicit_to<float>>();
    test_is_same<implicit_to<class_type>>();
    test_is_same<deleted_implicit_to<int>>();
    test_is_same<deleted_implicit_to<float>>();
    test_is_same<deleted_implicit_to<class_type>>();
    test_is_same<explicit_to<int>>();
    test_is_same<explicit_to<float>>();
    test_is_same<explicit_to<class_type>>();
    test_is_same<deleted_explicit_to<int>>();
    test_is_same<deleted_explicit_to<float>>();
    test_is_same<deleted_explicit_to<class_type>>();
    test_is_same<ellipsis>();
    test_is_same<deleted_ellipsis>();
    test_is_same<copy_constructible_only_type>();
    test_is_same<move_constructible_only_type>();
    test_is_same<overloaded_operators>();
    test_is_same<public_int_member>();
    test_is_same<protected_int_member>();
    test_is_same<private_int_member>();
    test_is_same<public_static_int_member>();
    test_is_same<protected_static_int_member>();
    test_is_same<private_static_int_member>();
    test_is_same<public_template_member<int>>();
    test_is_same<public_template_member<float>>();
    test_is_same<public_template_member<class_type>>();
    test_is_same<protected_template_member<int>>();
    test_is_same<protected_template_member<float>>();
    test_is_same<protected_template_member<class_type>>();
    test_is_same<private_template_member<int>>();
    test_is_same<private_template_member<float>>();
    test_is_same<private_template_member<class_type>>();
    test_is_same<public_static_template_member<int>>();
    test_is_same<public_static_template_member<float>>();
    test_is_same<public_static_template_member<class_type>>();
    test_is_same<protected_static_template_member<int>>();
    test_is_same<protected_static_template_member<float>>();
    test_is_same<protected_static_template_member<class_type>>();
    test_is_same<private_static_template_member<int>>();
    test_is_same<private_static_template_member<float>>();
    test_is_same<private_static_template_member<class_type>>();
    test_is_same<cannot_instantiate<int>>();
    test_is_same<cannot_instantiate<float>>();
    test_is_same<cannot_instantiate<class_type>>();
    test_is_same<natural_alignment>();
    test_is_same<Enum>();
    test_is_same<EnumSigned>();
    test_is_same<EnumUnsigned>();
    test_is_same<EnumClass>();
    test_is_same<EnumStruct>();
    test_is_same_ref<function_type>();
    test_is_same<function_ptr>();
    test_is_same<member_object_ptr>();
    test_is_same<member_function_ptr>();
    test_is_same<lambda_type>();
    test_is_same<lambda_noexcept_type>();
    test_is_same<lambda_throws_type>();
    test_is_same<incomplete_type>();
    test_is_same<incomplete_template<void>>();
    test_is_same<incomplete_template<int>>();
    test_is_same<incomplete_template<class_type>>();
    test_is_same<incomplete_template<incomplete_type>>();
    test_is_same<incomplete_variadic_template<>>();
    test_is_same<incomplete_variadic_template<void>>();
    test_is_same<incomplete_variadic_template<int>>();
    test_is_same<incomplete_variadic_template<class_type>>();
    test_is_same<incomplete_variadic_template<incomplete_type>>();
    test_is_same<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_same<incomplete_union>();
    test_is_same<IncompleteEnumSigned>();
    test_is_same<IncompleteEnumUnsigned>();
    test_is_same<IncompleteEnumClass>();
    test_is_same<IncompleteEnumStruct>();
    test_is_same<int class_type::*>();
    test_is_same<float class_type::*>();
    test_is_same<void * class_type::*>();
    test_is_same<int * class_type::*>();
    test_is_same<Enum class_type::*>();
    test_is_same<not_empty class_type::*>();
    test_is_same_ref<int class_type::*&>();
    test_is_same_ref<float class_type::*&>();
    test_is_same_ref<void * class_type::*&>();
    test_is_same_ref<int * class_type::*&>();
    test_is_same_ref<Enum class_type::*&>();
    test_is_same_ref<not_empty class_type::*&>();
    test_is_same_ref<int class_type::*&&>();
    test_is_same_ref<float class_type::*&&>();
    test_is_same_ref<void * class_type::*&&>();
    test_is_same_ref<int * class_type::*&&>();
    test_is_same_ref<Enum class_type::*&&>();
    test_is_same_ref<not_empty class_type::*&&>();
    test_is_same<non_default_constructible>();
    test_is_same<non_copy_constructible>();
    test_is_same<non_move_constructible>();
    test_is_same<non_copy_assignable>();
    test_is_same<non_move_assignable>();
    test_is_same<non_assignable>();
    test_is_same<non_copyable>();
    test_is_same<non_moveable>();
    test_is_same<non_constructible>();
    test_is_same<non_destructible>();
    test_is_same<tracked>();
    test_is_same<trap_constructible>();
    test_is_same<trap_implicit_conversion>();
    test_is_same<trap_comma>();
    test_is_same<trap_call>();
    test_is_same<trap_self_assign>();
    test_is_same<trap_deref>();
    test_is_same<trap_array_subscript>();

#if PHI_HAS_EXTENSION_ZERO_SIZE_ARRAY()
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wzero-length-array")
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wpedantic")

    test_is_same<int[0]>();

    PHI_GCC_SUPPRESS_WARNING_POP()
    PHI_CLANG_SUPPRESS_WARNING_POP()
#endif

    test_is_same_ref<void()>();
    test_is_same_ref<void()&>();
    test_is_same_ref<void() &&>();
    test_is_same_ref<void() const>();
    test_is_same_ref<void() const&>();
    test_is_same_ref<void() const&&>();
    test_is_same_ref<void() volatile>();
    test_is_same_ref<void() volatile&>();
    test_is_same_ref<void() volatile&&>();
    test_is_same_ref<void() const volatile>();
    test_is_same_ref<void() const volatile&>();
    test_is_same_ref<void() const volatile&&>();
    test_is_same_ref<void() noexcept>();
    test_is_same_ref<void()& noexcept>();
    test_is_same_ref<void()&& noexcept>();
    test_is_same_ref<void() const noexcept>();
    test_is_same_ref<void() const& noexcept>();
    test_is_same_ref<void() const&& noexcept>();
    test_is_same_ref<void() volatile noexcept>();
    test_is_same_ref<void() volatile& noexcept>();
    test_is_same_ref<void() volatile&& noexcept>();
    test_is_same_ref<void() const volatile noexcept>();
    test_is_same_ref<void() const volatile& noexcept>();
    test_is_same_ref<void() const volatile&& noexcept>();

    test_is_same_ref<void(int)>();
    test_is_same_ref<void(int)&>();
    test_is_same_ref<void(int) &&>();
    test_is_same_ref<void(int) const>();
    test_is_same_ref<void(int) const&>();
    test_is_same_ref<void(int) const&&>();
    test_is_same_ref<void(int) volatile>();
    test_is_same_ref<void(int) volatile&>();
    test_is_same_ref<void(int) volatile&&>();
    test_is_same_ref<void(int) const volatile>();
    test_is_same_ref<void(int) const volatile&>();
    test_is_same_ref<void(int) const volatile&&>();
    test_is_same_ref<void(int) noexcept>();
    test_is_same_ref<void(int)& noexcept>();
    test_is_same_ref<void(int)&& noexcept>();
    test_is_same_ref<void(int) const noexcept>();
    test_is_same_ref<void(int) const& noexcept>();
    test_is_same_ref<void(int) const&& noexcept>();
    test_is_same_ref<void(int) volatile noexcept>();
    test_is_same_ref<void(int) volatile& noexcept>();
    test_is_same_ref<void(int) volatile&& noexcept>();
    test_is_same_ref<void(int) const volatile noexcept>();
    test_is_same_ref<void(int) const volatile& noexcept>();
    test_is_same_ref<void(int) const volatile&& noexcept>();

    test_is_same_ref<void(...)>();
    test_is_same_ref<void(...)&>();
    test_is_same_ref<void(...) &&>();
    test_is_same_ref<void(...) const>();
    test_is_same_ref<void(...) const&>();
    test_is_same_ref<void(...) const&&>();
    test_is_same_ref<void(...) volatile>();
    test_is_same_ref<void(...) volatile&>();
    test_is_same_ref<void(...) volatile&&>();
    test_is_same_ref<void(...) const volatile>();
    test_is_same_ref<void(...) const volatile&>();
    test_is_same_ref<void(...) const volatile&&>();
    test_is_same_ref<void(...) noexcept>();
    test_is_same_ref<void(...)& noexcept>();
    test_is_same_ref<void(...)&& noexcept>();
    test_is_same_ref<void(...) const noexcept>();
    test_is_same_ref<void(...) const& noexcept>();
    test_is_same_ref<void(...) const&& noexcept>();
    test_is_same_ref<void(...) volatile noexcept>();
    test_is_same_ref<void(...) volatile& noexcept>();
    test_is_same_ref<void(...) volatile&& noexcept>();
    test_is_same_ref<void(...) const volatile noexcept>();
    test_is_same_ref<void(...) const volatile& noexcept>();
    test_is_same_ref<void(...) const volatile&& noexcept>();

    test_is_same_ref<void(int, ...)>();
    test_is_same_ref<void(int, ...)&>();
    test_is_same_ref<void(int, ...) &&>();
    test_is_same_ref<void(int, ...) const>();
    test_is_same_ref<void(int, ...) const&>();
    test_is_same_ref<void(int, ...) const&&>();
    test_is_same_ref<void(int, ...) volatile>();
    test_is_same_ref<void(int, ...) volatile&>();
    test_is_same_ref<void(int, ...) volatile&&>();
    test_is_same_ref<void(int, ...) const volatile>();
    test_is_same_ref<void(int, ...) const volatile&>();
    test_is_same_ref<void(int, ...) const volatile&&>();
    test_is_same_ref<void(int, ...) noexcept>();
    test_is_same_ref<void(int, ...)& noexcept>();
    test_is_same_ref<void(int, ...)&& noexcept>();
    test_is_same_ref<void(int, ...) const noexcept>();
    test_is_same_ref<void(int, ...) const& noexcept>();
    test_is_same_ref<void(int, ...) const&& noexcept>();
    test_is_same_ref<void(int, ...) volatile noexcept>();
    test_is_same_ref<void(int, ...) volatile& noexcept>();
    test_is_same_ref<void(int, ...) volatile&& noexcept>();
    test_is_same_ref<void(int, ...) const volatile noexcept>();
    test_is_same_ref<void(int, ...) const volatile& noexcept>();
    test_is_same_ref<void(int, ...) const volatile&& noexcept>();

    test_is_same_ref<int()>();
    test_is_same_ref<int()&>();
    test_is_same_ref<int() &&>();
    test_is_same_ref<int() const>();
    test_is_same_ref<int() const&>();
    test_is_same_ref<int() const&&>();
    test_is_same_ref<int() volatile>();
    test_is_same_ref<int() volatile&>();
    test_is_same_ref<int() volatile&&>();
    test_is_same_ref<int() const volatile>();
    test_is_same_ref<int() const volatile&>();
    test_is_same_ref<int() const volatile&&>();
    test_is_same_ref<int() noexcept>();
    test_is_same_ref<int()& noexcept>();
    test_is_same_ref<int()&& noexcept>();
    test_is_same_ref<int() const noexcept>();
    test_is_same_ref<int() const& noexcept>();
    test_is_same_ref<int() const&& noexcept>();
    test_is_same_ref<int() volatile noexcept>();
    test_is_same_ref<int() volatile& noexcept>();
    test_is_same_ref<int() volatile&& noexcept>();
    test_is_same_ref<int() const volatile noexcept>();
    test_is_same_ref<int() const volatile& noexcept>();
    test_is_same_ref<int() const volatile&& noexcept>();

    test_is_same_ref<int(int)>();
    test_is_same_ref<int(int)&>();
    test_is_same_ref<int(int) &&>();
    test_is_same_ref<int(int) const>();
    test_is_same_ref<int(int) const&>();
    test_is_same_ref<int(int) const&&>();
    test_is_same_ref<int(int) volatile>();
    test_is_same_ref<int(int) volatile&>();
    test_is_same_ref<int(int) volatile&&>();
    test_is_same_ref<int(int) const volatile>();
    test_is_same_ref<int(int) const volatile&>();
    test_is_same_ref<int(int) const volatile&&>();
    test_is_same_ref<int(int) noexcept>();
    test_is_same_ref<int(int)& noexcept>();
    test_is_same_ref<int(int)&& noexcept>();
    test_is_same_ref<int(int) const noexcept>();
    test_is_same_ref<int(int) const& noexcept>();
    test_is_same_ref<int(int) const&& noexcept>();
    test_is_same_ref<int(int) volatile noexcept>();
    test_is_same_ref<int(int) volatile& noexcept>();
    test_is_same_ref<int(int) volatile&& noexcept>();
    test_is_same_ref<int(int) const volatile noexcept>();
    test_is_same_ref<int(int) const volatile& noexcept>();
    test_is_same_ref<int(int) const volatile&& noexcept>();

    test_is_same_ref<int(...)>();
    test_is_same_ref<int(...)&>();
    test_is_same_ref<int(...) &&>();
    test_is_same_ref<int(...) const>();
    test_is_same_ref<int(...) const&>();
    test_is_same_ref<int(...) const&&>();
    test_is_same_ref<int(...) volatile>();
    test_is_same_ref<int(...) volatile&>();
    test_is_same_ref<int(...) volatile&&>();
    test_is_same_ref<int(...) const volatile>();
    test_is_same_ref<int(...) const volatile&>();
    test_is_same_ref<int(...) const volatile&&>();
    test_is_same_ref<int(...) noexcept>();
    test_is_same_ref<int(...)& noexcept>();
    test_is_same_ref<int(...)&& noexcept>();
    test_is_same_ref<int(...) const noexcept>();
    test_is_same_ref<int(...) const& noexcept>();
    test_is_same_ref<int(...) const&& noexcept>();
    test_is_same_ref<int(...) volatile noexcept>();
    test_is_same_ref<int(...) volatile& noexcept>();
    test_is_same_ref<int(...) volatile&& noexcept>();
    test_is_same_ref<int(...) const volatile noexcept>();
    test_is_same_ref<int(...) const volatile& noexcept>();
    test_is_same_ref<int(...) const volatile&& noexcept>();

    test_is_same_ref<int(int, ...)>();
    test_is_same_ref<int(int, ...)&>();
    test_is_same_ref<int(int, ...) &&>();
    test_is_same_ref<int(int, ...) const>();
    test_is_same_ref<int(int, ...) const&>();
    test_is_same_ref<int(int, ...) const&&>();
    test_is_same_ref<int(int, ...) volatile>();
    test_is_same_ref<int(int, ...) volatile&>();
    test_is_same_ref<int(int, ...) volatile&&>();
    test_is_same_ref<int(int, ...) const volatile>();
    test_is_same_ref<int(int, ...) const volatile&>();
    test_is_same_ref<int(int, ...) const volatile&&>();
    test_is_same_ref<int(int, ...) noexcept>();
    test_is_same_ref<int(int, ...)& noexcept>();
    test_is_same_ref<int(int, ...)&& noexcept>();
    test_is_same_ref<int(int, ...) const noexcept>();
    test_is_same_ref<int(int, ...) const& noexcept>();
    test_is_same_ref<int(int, ...) const&& noexcept>();
    test_is_same_ref<int(int, ...) volatile noexcept>();
    test_is_same_ref<int(int, ...) volatile& noexcept>();
    test_is_same_ref<int(int, ...) volatile&& noexcept>();
    test_is_same_ref<int(int, ...) const volatile noexcept>();
    test_is_same_ref<int(int, ...) const volatile& noexcept>();
    test_is_same_ref<int(int, ...) const volatile&& noexcept>();

    test_is_same<void (*)()>();
    test_is_same<void (*)() noexcept>();

    test_is_same<void (*)(int)>();
    test_is_same<void (*)(int) noexcept>();

    test_is_same<void (*)(...)>();
    test_is_same<void (*)(...) noexcept>();

    test_is_same<void (*)(int, ...)>();
    test_is_same<void (*)(int, ...) noexcept>();

    test_is_same<int (*)()>();
    test_is_same<int (*)() noexcept>();

    test_is_same<int (*)(int)>();
    test_is_same<int (*)(int) noexcept>();

    test_is_same<int (*)(...)>();
    test_is_same<int (*)(...) noexcept>();

    test_is_same<int (*)(int, ...)>();
    test_is_same<int (*)(int, ...) noexcept>();

    test_is_same_ref<void (&)()>();
    test_is_same_ref<void (&)() noexcept>();

    test_is_same_ref<void (&)(int)>();
    test_is_same_ref<void (&)(int) noexcept>();

    test_is_same_ref<void (&)(...)>();
    test_is_same_ref<void (&)(...) noexcept>();

    test_is_same_ref<void (&)(int, ...)>();
    test_is_same_ref<void (&)(int, ...) noexcept>();

    test_is_same_ref<int (&)()>();
    test_is_same_ref<int (&)() noexcept>();

    test_is_same_ref<int (&)(int)>();
    test_is_same_ref<int (&)(int) noexcept>();

    test_is_same_ref<int (&)(...)>();
    test_is_same_ref<int (&)(...) noexcept>();

    test_is_same_ref<int (&)(int, ...)>();
    test_is_same_ref<int (&)(int, ...) noexcept>();

    test_is_same_ref<void(&&)()>();
    test_is_same_ref<void(&&)() noexcept>();

    test_is_same_ref<void(&&)(int)>();
    test_is_same_ref<void(&&)(int) noexcept>();

    test_is_same_ref<void(&&)(...)>();
    test_is_same_ref<void(&&)(...) noexcept>();

    test_is_same_ref<void(&&)(int, ...)>();
    test_is_same_ref<void(&&)(int, ...) noexcept>();

    test_is_same_ref<int(&&)()>();
    test_is_same_ref<int(&&)() noexcept>();

    test_is_same_ref<int(&&)(int)>();
    test_is_same_ref<int(&&)(int) noexcept>();

    test_is_same_ref<int(&&)(...)>();
    test_is_same_ref<int(&&)(...) noexcept>();

    test_is_same_ref<int(&&)(int, ...)>();
    test_is_same_ref<int(&&)(int, ...) noexcept>();

    test_is_same<void (class_type::*)()>();
    test_is_same<void (class_type::*)()&>();
    test_is_same<void (class_type::*)() &&>();
    test_is_same<void (class_type::*)() const>();
    test_is_same<void (class_type::*)() const&>();
    test_is_same<void (class_type::*)() const&&>();
    test_is_same<void (class_type::*)() noexcept>();
    test_is_same<void (class_type::*)()& noexcept>();
    test_is_same<void (class_type::*)()&& noexcept>();
    test_is_same<void (class_type::*)() const noexcept>();
    test_is_same<void (class_type::*)() const& noexcept>();
    test_is_same<void (class_type::*)() const&& noexcept>();

    test_is_same<void (class_type::*)(int)>();
    test_is_same<void (class_type::*)(int)&>();
    test_is_same<void (class_type::*)(int) &&>();
    test_is_same<void (class_type::*)(int) const>();
    test_is_same<void (class_type::*)(int) const&>();
    test_is_same<void (class_type::*)(int) const&&>();
    test_is_same<void (class_type::*)(int) noexcept>();
    test_is_same<void (class_type::*)(int)& noexcept>();
    test_is_same<void (class_type::*)(int)&& noexcept>();
    test_is_same<void (class_type::*)(int) const noexcept>();
    test_is_same<void (class_type::*)(int) const& noexcept>();
    test_is_same<void (class_type::*)(int) const&& noexcept>();

    test_is_same<void (class_type::*)(...)>();
    test_is_same<void (class_type::*)(...)&>();
    test_is_same<void (class_type::*)(...) &&>();
    test_is_same<void (class_type::*)(...) const>();
    test_is_same<void (class_type::*)(...) const&>();
    test_is_same<void (class_type::*)(...) const&&>();
    test_is_same<void (class_type::*)(...) noexcept>();
    test_is_same<void (class_type::*)(...)& noexcept>();
    test_is_same<void (class_type::*)(...)&& noexcept>();
    test_is_same<void (class_type::*)(...) const noexcept>();
    test_is_same<void (class_type::*)(...) const& noexcept>();
    test_is_same<void (class_type::*)(...) const&& noexcept>();

    test_is_same<void (class_type::*)(int, ...)>();
    test_is_same<void (class_type::*)(int, ...)&>();
    test_is_same<void (class_type::*)(int, ...) &&>();
    test_is_same<void (class_type::*)(int, ...) const>();
    test_is_same<void (class_type::*)(int, ...) const&>();
    test_is_same<void (class_type::*)(int, ...) const&&>();
    test_is_same<void (class_type::*)(int, ...) noexcept>();
    test_is_same<void (class_type::*)(int, ...)& noexcept>();
    test_is_same<void (class_type::*)(int, ...)&& noexcept>();
    test_is_same<void (class_type::*)(int, ...) const noexcept>();
    test_is_same<void (class_type::*)(int, ...) const& noexcept>();
    test_is_same<void (class_type::*)(int, ...) const&& noexcept>();

    test_is_same<int (class_type::*)()>();
    test_is_same<int (class_type::*)()&>();
    test_is_same<int (class_type::*)() &&>();
    test_is_same<int (class_type::*)() const>();
    test_is_same<int (class_type::*)() const&>();
    test_is_same<int (class_type::*)() const&&>();
    test_is_same<int (class_type::*)() noexcept>();
    test_is_same<int (class_type::*)()& noexcept>();
    test_is_same<int (class_type::*)()&& noexcept>();
    test_is_same<int (class_type::*)() const noexcept>();
    test_is_same<int (class_type::*)() const& noexcept>();
    test_is_same<int (class_type::*)() const&& noexcept>();

    test_is_same<int (class_type::*)(int)>();
    test_is_same<int (class_type::*)(int)&>();
    test_is_same<int (class_type::*)(int) &&>();
    test_is_same<int (class_type::*)(int) const>();
    test_is_same<int (class_type::*)(int) const&>();
    test_is_same<int (class_type::*)(int) const&&>();
    test_is_same<int (class_type::*)(int) noexcept>();
    test_is_same<int (class_type::*)(int)& noexcept>();
    test_is_same<int (class_type::*)(int)&& noexcept>();
    test_is_same<int (class_type::*)(int) const noexcept>();
    test_is_same<int (class_type::*)(int) const& noexcept>();
    test_is_same<int (class_type::*)(int) const&& noexcept>();

    test_is_same<int (class_type::*)(...)>();
    test_is_same<int (class_type::*)(...)&>();
    test_is_same<int (class_type::*)(...) &&>();
    test_is_same<int (class_type::*)(...) const>();
    test_is_same<int (class_type::*)(...) const&>();
    test_is_same<int (class_type::*)(...) const&&>();
    test_is_same<int (class_type::*)(...) noexcept>();
    test_is_same<int (class_type::*)(...)& noexcept>();
    test_is_same<int (class_type::*)(...)&& noexcept>();
    test_is_same<int (class_type::*)(...) const noexcept>();
    test_is_same<int (class_type::*)(...) const& noexcept>();
    test_is_same<int (class_type::*)(...) const&& noexcept>();

    test_is_same<int (class_type::*)(int, ...)>();
    test_is_same<int (class_type::*)(int, ...)&>();
    test_is_same<int (class_type::*)(int, ...) &&>();
    test_is_same<int (class_type::*)(int, ...) const>();
    test_is_same<int (class_type::*)(int, ...) const&>();
    test_is_same<int (class_type::*)(int, ...) const&&>();
    test_is_same<int (class_type::*)(int, ...) noexcept>();
    test_is_same<int (class_type::*)(int, ...)& noexcept>();
    test_is_same<int (class_type::*)(int, ...)&& noexcept>();
    test_is_same<int (class_type::*)(int, ...) const noexcept>();
    test_is_same<int (class_type::*)(int, ...) const& noexcept>();
    test_is_same<int (class_type::*)(int, ...) const&& noexcept>();
}
