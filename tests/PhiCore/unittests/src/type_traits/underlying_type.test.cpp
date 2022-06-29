#include <phi/test/test_macros.hpp>

#include "phi/compiler_support/warning.hpp"
#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/integral_constant.hpp>
#include <phi/type_traits/underlying_type.hpp>
#include <phi/type_traits/void_t.hpp>
#include <climits>
#include <type_traits>
#include <vector>

template <typename, typename = phi::void_t<>>
struct has_type_member : public phi::false_type
{};

template <typename TypeT>
struct has_type_member<TypeT, phi::void_t<typename phi::underlying_type<TypeT>::type>>
    : public phi::true_type
{};

template <typename TypeT, typename ExpectedT>
void test_underlying_type_impl()
{
#if PHI_HAS_WORKING_UNDERLYING_TYPE()
    STATIC_REQUIRE(has_type_member<TypeT>::value);

    CHECK_SAME_TYPE(typename phi::underlying_type<TypeT>::type, ExpectedT);
    CHECK_SAME_TYPE(phi::underlying_type_t<TypeT>, ExpectedT);

    // Standard compatibility
    CHECK_SAME_TYPE(typename std::underlying_type<TypeT>::type, ExpectedT);
#endif
}

template <typename TypeT, typename ExpectedT>
void test_underlying_type()
{
    test_underlying_type_impl<TypeT, ExpectedT>();
    test_underlying_type_impl<const TypeT, ExpectedT>();
    test_underlying_type_impl<volatile TypeT, ExpectedT>();
    test_underlying_type_impl<const volatile TypeT, ExpectedT>();
}

template <typename TypeT>
void test_no_underlying_type()
{
#if PHI_HAS_WORKING_UNDERLYING_TYPE()
    STATIC_REQUIRE_FALSE(has_type_member<TypeT>::value);
    STATIC_REQUIRE_FALSE(has_type_member<const TypeT>::value);
    STATIC_REQUIRE_FALSE(has_type_member<volatile TypeT>::value);
    STATIC_REQUIRE_FALSE(has_type_member<const volatile TypeT>::value);
#endif
}

enum E
{
    V = INT_MIN
};

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wmicrosoft-enum-value")

enum F
{
    W = UINT_MAX
};

PHI_CLANG_SUPPRESS_WARNING_POP()

enum G : char
{
};

enum class H
{
    red,
    green = 20,
    blue
};

enum class I : long
{
    red,
    green = 20,
    blue
};

enum struct J
{
    red,
    green = 20,
    blue
};

enum struct K : short
{
    red,
    green = 20,
    blue
};

TEST_CASE("is_void")
{
    test_underlying_type<E, int>();
#if PHI_COMPILER_IS(MSVC) || PHI_COMPILER_IS(WINCLANG)
    test_underlying_type<F, int>();
#else
    test_underlying_type<F, unsigned>();
#endif
    test_underlying_type<G, char>();
    test_underlying_type<H, int>();
    test_underlying_type<I, long>();
    test_underlying_type<J, int>();
    test_underlying_type<K, short>();

    test_no_underlying_type<void>();
    test_no_underlying_type<phi::nullptr_t>();
    test_no_underlying_type<bool>();
    test_no_underlying_type<char>();
    test_no_underlying_type<signed char>();
    test_no_underlying_type<unsigned char>();
    test_no_underlying_type<short>();
    test_no_underlying_type<unsigned short>();
    test_no_underlying_type<int>();
    test_no_underlying_type<unsigned int>();
    test_no_underlying_type<long>();
    test_no_underlying_type<unsigned long>();
    test_no_underlying_type<long long>();
    test_no_underlying_type<unsigned long long>();
    test_no_underlying_type<float>();
    test_no_underlying_type<double>();
    test_no_underlying_type<long double>();
    test_no_underlying_type<char8_t>();
    test_no_underlying_type<char16_t>();
    test_no_underlying_type<char32_t>();
    test_no_underlying_type<wchar_t>();

    test_no_underlying_type<phi::boolean>();
    test_no_underlying_type<phi::integer<signed char>>();
    test_no_underlying_type<phi::integer<unsigned char>>();
    test_no_underlying_type<phi::integer<short>>();
    test_no_underlying_type<phi::integer<unsigned short>>();
    test_no_underlying_type<phi::integer<int>>();
    test_no_underlying_type<phi::integer<unsigned int>>();
    test_no_underlying_type<phi::integer<long>>();
    test_no_underlying_type<phi::integer<unsigned long>>();
    test_no_underlying_type<phi::integer<long long>>();
    test_no_underlying_type<phi::integer<unsigned long long>>();
    test_no_underlying_type<phi::floating_point<float>>();
    test_no_underlying_type<phi::floating_point<double>>();
    test_no_underlying_type<phi::floating_point<long double>>();

    test_no_underlying_type<std::vector<int>>();
    test_no_underlying_type<phi::scope_ptr<int>>();

    test_no_underlying_type<int&>();
    test_no_underlying_type<const int&>();
    test_no_underlying_type<volatile int&>();
    test_no_underlying_type<const volatile int&>();
    test_no_underlying_type<int&&>();
    test_no_underlying_type<const int&&>();
    test_no_underlying_type<volatile int&&>();
    test_no_underlying_type<const volatile int&&>();
    test_no_underlying_type<int*>();
    test_no_underlying_type<const int*>();
    test_no_underlying_type<volatile int*>();
    test_no_underlying_type<const volatile int*>();
    test_no_underlying_type<int**>();
    test_no_underlying_type<const int**>();
    test_no_underlying_type<volatile int**>();
    test_no_underlying_type<const volatile int**>();
    test_no_underlying_type<int*&>();
    test_no_underlying_type<const int*&>();
    test_no_underlying_type<volatile int*&>();
    test_no_underlying_type<const volatile int*&>();
    test_no_underlying_type<int*&&>();
    test_no_underlying_type<const int*&&>();
    test_no_underlying_type<volatile int*&&>();
    test_no_underlying_type<const volatile int*&&>();
    test_no_underlying_type<void*>();
    test_no_underlying_type<char[3]>();
    test_no_underlying_type<char[]>();
    test_no_underlying_type<char* [3]>();
    test_no_underlying_type<char*[]>();
    test_no_underlying_type<int(*)[3]>();
    test_no_underlying_type<int(*)[]>();
    test_no_underlying_type<int(&)[3]>();
    test_no_underlying_type<int(&)[]>();
    test_no_underlying_type<int(&&)[3]>();
    test_no_underlying_type<int(&&)[]>();
    test_no_underlying_type<char[3][2]>();
    test_no_underlying_type<char[][2]>();
    test_no_underlying_type<char* [3][2]>();
    test_no_underlying_type<char*[][2]>();
    test_no_underlying_type<int(*)[3][2]>();
    test_no_underlying_type<int(*)[][2]>();
    test_no_underlying_type<int(&)[3][2]>();
    test_no_underlying_type<int(&)[][2]>();
    test_no_underlying_type<int(&&)[3][2]>();
    test_no_underlying_type<int(&&)[][2]>();
    test_no_underlying_type<class_type>();
    test_no_underlying_type<class_type[]>();
    test_no_underlying_type<class_type[2]>();
    test_no_underlying_type<template_type<void>>();
    test_no_underlying_type<template_type<int>>();
    test_no_underlying_type<template_type<class_type>>();
    test_no_underlying_type<template_type<incomplete_type>>();
    test_no_underlying_type<variadic_template<>>();
    test_no_underlying_type<variadic_template<void>>();
    test_no_underlying_type<variadic_template<int>>();
    test_no_underlying_type<variadic_template<class_type>>();
    test_no_underlying_type<variadic_template<incomplete_type>>();
    test_no_underlying_type<variadic_template<int, void, class_type, volatile char[]>>();
    test_no_underlying_type<public_derived_from<base>>();
    test_no_underlying_type<public_derived_from<derived>>();
    test_no_underlying_type<public_derived_from<class_type>>();
    test_no_underlying_type<private_derived_from<base>>();
    test_no_underlying_type<private_derived_from<derived>>();
    test_no_underlying_type<private_derived_from<class_type>>();
    test_no_underlying_type<protected_derived_from<base>>();
    test_no_underlying_type<protected_derived_from<derived>>();
    test_no_underlying_type<protected_derived_from<class_type>>();
    test_no_underlying_type<union_type>();
    test_no_underlying_type<non_empty_union>();
    test_no_underlying_type<empty>();
    test_no_underlying_type<not_empty>();
    test_no_underlying_type<bit_zero>();
    test_no_underlying_type<bit_one>();
    test_no_underlying_type<base>();
    test_no_underlying_type<derived>();
    test_no_underlying_type<abstract>();
    test_no_underlying_type<public_abstract>();
    test_no_underlying_type<private_abstract>();
    test_no_underlying_type<protected_abstract>();
    test_no_underlying_type<abstract_template<int>>();
    test_no_underlying_type<abstract_template<double>>();
    test_no_underlying_type<abstract_template<class_type>>();
    test_no_underlying_type<abstract_template<incomplete_type>>();
    test_no_underlying_type<final_type>();
    test_no_underlying_type<public_destructor>();
    test_no_underlying_type<protected_destructor>();
    test_no_underlying_type<private_destructor>();
    test_no_underlying_type<virtual_public_destructor>();
    test_no_underlying_type<virtual_protected_destructor>();
    test_no_underlying_type<virtual_private_destructor>();
    test_no_underlying_type<pure_public_destructor>();
    test_no_underlying_type<pure_protected_destructor>();
    test_no_underlying_type<pure_private_destructor>();
    test_no_underlying_type<deleted_public_destructor>();
    test_no_underlying_type<deleted_protected_destructor>();
    test_no_underlying_type<deleted_private_destructor>();
    test_no_underlying_type<deleted_virtual_public_destructor>();
    test_no_underlying_type<deleted_virtual_protected_destructor>();
    test_no_underlying_type<deleted_virtual_private_destructor>();
#if PHI_COMPILER_IS(MSVC) || PHI_COMPILER_IS(WINCLANG)
    test_underlying_type<Enum, int>();
#else
    test_underlying_type<Enum, unsigned int>();
#endif
    test_underlying_type<EnumSigned, int>();
    test_underlying_type<EnumUnsigned, unsigned int>();
    test_underlying_type<EnumClass, int>();
    test_underlying_type<EnumStruct, int>();
    test_no_underlying_type<function_type>();
    test_no_underlying_type<function_ptr>();
    test_no_underlying_type<member_object_ptr>();
    test_no_underlying_type<member_function_ptr>();
    test_no_underlying_type<incomplete_type>();
    test_no_underlying_type<incomplete_template<void>>();
    test_no_underlying_type<incomplete_template<int>>();
    test_no_underlying_type<incomplete_template<class_type>>();
    test_no_underlying_type<incomplete_template<incomplete_type>>();
    test_no_underlying_type<incomplete_variadic_template<>>();
    test_no_underlying_type<incomplete_variadic_template<void>>();
    test_no_underlying_type<incomplete_variadic_template<int>>();
    test_no_underlying_type<incomplete_variadic_template<class_type>>();
    test_no_underlying_type<incomplete_variadic_template<incomplete_type>>();
    test_no_underlying_type<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_no_underlying_type<int class_type::*>();
    test_no_underlying_type<float class_type::*>();
    test_no_underlying_type<void * class_type::*>();
    test_no_underlying_type<int * class_type::*>();
    test_no_underlying_type<int class_type::*&>();
    test_no_underlying_type<float class_type::*&>();
    test_no_underlying_type<void * class_type::*&>();
    test_no_underlying_type<int * class_type::*&>();
    test_no_underlying_type<int class_type::*&&>();
    test_no_underlying_type<float class_type::*&&>();
    test_no_underlying_type<void * class_type::*&&>();
    test_no_underlying_type<int * class_type::*&&>();
    test_no_underlying_type<int class_type::*const>();
    test_no_underlying_type<float class_type::*const>();
    test_no_underlying_type<void * class_type::*const>();
    test_no_underlying_type<int class_type::*const&>();
    test_no_underlying_type<float class_type::*const&>();
    test_no_underlying_type<void * class_type::*const&>();
    test_no_underlying_type<int class_type::*const&&>();
    test_no_underlying_type<float class_type::*const&&>();
    test_no_underlying_type<void * class_type::*const&&>();
    test_no_underlying_type<int class_type::*volatile>();
    test_no_underlying_type<float class_type::*volatile>();
    test_no_underlying_type<void * class_type::*volatile>();
    test_no_underlying_type<int class_type::*volatile&>();
    test_no_underlying_type<float class_type::*volatile&>();
    test_no_underlying_type<void * class_type::*volatile&>();
    test_no_underlying_type<int class_type::*volatile&&>();
    test_no_underlying_type<float class_type::*volatile&&>();
    test_no_underlying_type<void * class_type::*volatile&&>();
    test_no_underlying_type<int class_type::*const volatile>();
    test_no_underlying_type<float class_type::*const volatile>();
    test_no_underlying_type<void * class_type::*const volatile>();
    test_no_underlying_type<int class_type::*const volatile&>();
    test_no_underlying_type<float class_type::*const volatile&>();
    test_no_underlying_type<void * class_type::*const volatile&>();
    test_no_underlying_type<int class_type::*const volatile&&>();
    test_no_underlying_type<float class_type::*const volatile&&>();
    test_no_underlying_type<void * class_type::*const volatile&&>();
    test_no_underlying_type<non_copyable>();
    test_no_underlying_type<non_moveable>();
    test_no_underlying_type<non_constructible>();
    test_no_underlying_type<tracked>();
    test_no_underlying_type<trap_constructible>();
    test_no_underlying_type<trap_implicit_conversion>();
    test_no_underlying_type<trap_comma>();
    test_no_underlying_type<trap_call>();
    test_no_underlying_type<trap_self_assign>();
    test_no_underlying_type<trap_deref>();
    test_no_underlying_type<trap_array_subscript>();

    test_no_underlying_type<void()>();
    test_no_underlying_type<void()&>();
    test_no_underlying_type<void() &&>();
    test_no_underlying_type<void() const>();
    test_no_underlying_type<void() const&>();
    test_no_underlying_type<void() const&&>();
    test_no_underlying_type<void() volatile>();
    test_no_underlying_type<void() volatile&>();
    test_no_underlying_type<void() volatile&&>();
    test_no_underlying_type<void() const volatile>();
    test_no_underlying_type<void() const volatile&>();
    test_no_underlying_type<void() const volatile&&>();
    test_no_underlying_type<void() noexcept>();
    test_no_underlying_type<void()& noexcept>();
    test_no_underlying_type<void()&& noexcept>();
    test_no_underlying_type<void() const noexcept>();
    test_no_underlying_type<void() const& noexcept>();
    test_no_underlying_type<void() const&& noexcept>();
    test_no_underlying_type<void() volatile noexcept>();
    test_no_underlying_type<void() volatile& noexcept>();
    test_no_underlying_type<void() volatile&& noexcept>();
    test_no_underlying_type<void() const volatile noexcept>();
    test_no_underlying_type<void() const volatile& noexcept>();
    test_no_underlying_type<void() const volatile&& noexcept>();

    test_no_underlying_type<void(int)>();
    test_no_underlying_type<void(int)&>();
    test_no_underlying_type<void(int) &&>();
    test_no_underlying_type<void(int) const>();
    test_no_underlying_type<void(int) const&>();
    test_no_underlying_type<void(int) const&&>();
    test_no_underlying_type<void(int) volatile>();
    test_no_underlying_type<void(int) volatile&>();
    test_no_underlying_type<void(int) volatile&&>();
    test_no_underlying_type<void(int) const volatile>();
    test_no_underlying_type<void(int) const volatile&>();
    test_no_underlying_type<void(int) const volatile&&>();
    test_no_underlying_type<void(int) noexcept>();
    test_no_underlying_type<void(int)& noexcept>();
    test_no_underlying_type<void(int)&& noexcept>();
    test_no_underlying_type<void(int) const noexcept>();
    test_no_underlying_type<void(int) const& noexcept>();
    test_no_underlying_type<void(int) const&& noexcept>();
    test_no_underlying_type<void(int) volatile noexcept>();
    test_no_underlying_type<void(int) volatile& noexcept>();
    test_no_underlying_type<void(int) volatile&& noexcept>();
    test_no_underlying_type<void(int) const volatile noexcept>();
    test_no_underlying_type<void(int) const volatile& noexcept>();
    test_no_underlying_type<void(int) const volatile&& noexcept>();

    test_no_underlying_type<void(...)>();
    test_no_underlying_type<void(...)&>();
    test_no_underlying_type<void(...) &&>();
    test_no_underlying_type<void(...) const>();
    test_no_underlying_type<void(...) const&>();
    test_no_underlying_type<void(...) const&&>();
    test_no_underlying_type<void(...) volatile>();
    test_no_underlying_type<void(...) volatile&>();
    test_no_underlying_type<void(...) volatile&&>();
    test_no_underlying_type<void(...) const volatile>();
    test_no_underlying_type<void(...) const volatile&>();
    test_no_underlying_type<void(...) const volatile&&>();
    test_no_underlying_type<void(...) noexcept>();
    test_no_underlying_type<void(...)& noexcept>();
    test_no_underlying_type<void(...)&& noexcept>();
    test_no_underlying_type<void(...) const noexcept>();
    test_no_underlying_type<void(...) const& noexcept>();
    test_no_underlying_type<void(...) const&& noexcept>();
    test_no_underlying_type<void(...) volatile noexcept>();
    test_no_underlying_type<void(...) volatile& noexcept>();
    test_no_underlying_type<void(...) volatile&& noexcept>();
    test_no_underlying_type<void(...) const volatile noexcept>();
    test_no_underlying_type<void(...) const volatile& noexcept>();
    test_no_underlying_type<void(...) const volatile&& noexcept>();

    test_no_underlying_type<void(int, ...)>();
    test_no_underlying_type<void(int, ...)&>();
    test_no_underlying_type<void(int, ...) &&>();
    test_no_underlying_type<void(int, ...) const>();
    test_no_underlying_type<void(int, ...) const&>();
    test_no_underlying_type<void(int, ...) const&&>();
    test_no_underlying_type<void(int, ...) volatile>();
    test_no_underlying_type<void(int, ...) volatile&>();
    test_no_underlying_type<void(int, ...) volatile&&>();
    test_no_underlying_type<void(int, ...) const volatile>();
    test_no_underlying_type<void(int, ...) const volatile&>();
    test_no_underlying_type<void(int, ...) const volatile&&>();
    test_no_underlying_type<void(int, ...) noexcept>();
    test_no_underlying_type<void(int, ...)& noexcept>();
    test_no_underlying_type<void(int, ...)&& noexcept>();
    test_no_underlying_type<void(int, ...) const noexcept>();
    test_no_underlying_type<void(int, ...) const& noexcept>();
    test_no_underlying_type<void(int, ...) const&& noexcept>();
    test_no_underlying_type<void(int, ...) volatile noexcept>();
    test_no_underlying_type<void(int, ...) volatile& noexcept>();
    test_no_underlying_type<void(int, ...) volatile&& noexcept>();
    test_no_underlying_type<void(int, ...) const volatile noexcept>();
    test_no_underlying_type<void(int, ...) const volatile& noexcept>();
    test_no_underlying_type<void(int, ...) const volatile&& noexcept>();

    test_no_underlying_type<int()>();
    test_no_underlying_type<int()&>();
    test_no_underlying_type<int() &&>();
    test_no_underlying_type<int() const>();
    test_no_underlying_type<int() const&>();
    test_no_underlying_type<int() const&&>();
    test_no_underlying_type<int() volatile>();
    test_no_underlying_type<int() volatile&>();
    test_no_underlying_type<int() volatile&&>();
    test_no_underlying_type<int() const volatile>();
    test_no_underlying_type<int() const volatile&>();
    test_no_underlying_type<int() const volatile&&>();
    test_no_underlying_type<int() noexcept>();
    test_no_underlying_type<int()& noexcept>();
    test_no_underlying_type<int()&& noexcept>();
    test_no_underlying_type<int() const noexcept>();
    test_no_underlying_type<int() const& noexcept>();
    test_no_underlying_type<int() const&& noexcept>();
    test_no_underlying_type<int() volatile noexcept>();
    test_no_underlying_type<int() volatile& noexcept>();
    test_no_underlying_type<int() volatile&& noexcept>();
    test_no_underlying_type<int() const volatile noexcept>();
    test_no_underlying_type<int() const volatile& noexcept>();
    test_no_underlying_type<int() const volatile&& noexcept>();

    test_no_underlying_type<int(int)>();
    test_no_underlying_type<int(int)&>();
    test_no_underlying_type<int(int) &&>();
    test_no_underlying_type<int(int) const>();
    test_no_underlying_type<int(int) const&>();
    test_no_underlying_type<int(int) const&&>();
    test_no_underlying_type<int(int) volatile>();
    test_no_underlying_type<int(int) volatile&>();
    test_no_underlying_type<int(int) volatile&&>();
    test_no_underlying_type<int(int) const volatile>();
    test_no_underlying_type<int(int) const volatile&>();
    test_no_underlying_type<int(int) const volatile&&>();
    test_no_underlying_type<int(int) noexcept>();
    test_no_underlying_type<int(int)& noexcept>();
    test_no_underlying_type<int(int)&& noexcept>();
    test_no_underlying_type<int(int) const noexcept>();
    test_no_underlying_type<int(int) const& noexcept>();
    test_no_underlying_type<int(int) const&& noexcept>();
    test_no_underlying_type<int(int) volatile noexcept>();
    test_no_underlying_type<int(int) volatile& noexcept>();
    test_no_underlying_type<int(int) volatile&& noexcept>();
    test_no_underlying_type<int(int) const volatile noexcept>();
    test_no_underlying_type<int(int) const volatile& noexcept>();
    test_no_underlying_type<int(int) const volatile&& noexcept>();

    test_no_underlying_type<int(...)>();
    test_no_underlying_type<int(...)&>();
    test_no_underlying_type<int(...) &&>();
    test_no_underlying_type<int(...) const>();
    test_no_underlying_type<int(...) const&>();
    test_no_underlying_type<int(...) const&&>();
    test_no_underlying_type<int(...) volatile>();
    test_no_underlying_type<int(...) volatile&>();
    test_no_underlying_type<int(...) volatile&&>();
    test_no_underlying_type<int(...) const volatile>();
    test_no_underlying_type<int(...) const volatile&>();
    test_no_underlying_type<int(...) const volatile&&>();
    test_no_underlying_type<int(...) noexcept>();
    test_no_underlying_type<int(...)& noexcept>();
    test_no_underlying_type<int(...)&& noexcept>();
    test_no_underlying_type<int(...) const noexcept>();
    test_no_underlying_type<int(...) const& noexcept>();
    test_no_underlying_type<int(...) const&& noexcept>();
    test_no_underlying_type<int(...) volatile noexcept>();
    test_no_underlying_type<int(...) volatile& noexcept>();
    test_no_underlying_type<int(...) volatile&& noexcept>();
    test_no_underlying_type<int(...) const volatile noexcept>();
    test_no_underlying_type<int(...) const volatile& noexcept>();
    test_no_underlying_type<int(...) const volatile&& noexcept>();

    test_no_underlying_type<int(int, ...)>();
    test_no_underlying_type<int(int, ...)&>();
    test_no_underlying_type<int(int, ...) &&>();
    test_no_underlying_type<int(int, ...) const>();
    test_no_underlying_type<int(int, ...) const&>();
    test_no_underlying_type<int(int, ...) const&&>();
    test_no_underlying_type<int(int, ...) volatile>();
    test_no_underlying_type<int(int, ...) volatile&>();
    test_no_underlying_type<int(int, ...) volatile&&>();
    test_no_underlying_type<int(int, ...) const volatile>();
    test_no_underlying_type<int(int, ...) const volatile&>();
    test_no_underlying_type<int(int, ...) const volatile&&>();
    test_no_underlying_type<int(int, ...) noexcept>();
    test_no_underlying_type<int(int, ...)& noexcept>();
    test_no_underlying_type<int(int, ...)&& noexcept>();
    test_no_underlying_type<int(int, ...) const noexcept>();
    test_no_underlying_type<int(int, ...) const& noexcept>();
    test_no_underlying_type<int(int, ...) const&& noexcept>();
    test_no_underlying_type<int(int, ...) volatile noexcept>();
    test_no_underlying_type<int(int, ...) volatile& noexcept>();
    test_no_underlying_type<int(int, ...) volatile&& noexcept>();
    test_no_underlying_type<int(int, ...) const volatile noexcept>();
    test_no_underlying_type<int(int, ...) const volatile& noexcept>();
    test_no_underlying_type<int(int, ...) const volatile&& noexcept>();

    test_no_underlying_type<void (*)()>();
    test_no_underlying_type<void (*)() noexcept>();

    test_no_underlying_type<void (*)(int)>();
    test_no_underlying_type<void (*)(int) noexcept>();

    test_no_underlying_type<void (*)(...)>();
    test_no_underlying_type<void (*)(...) noexcept>();

    test_no_underlying_type<void (*)(int, ...)>();
    test_no_underlying_type<void (*)(int, ...) noexcept>();

    test_no_underlying_type<int (*)()>();
    test_no_underlying_type<int (*)() noexcept>();

    test_no_underlying_type<int (*)(int)>();
    test_no_underlying_type<int (*)(int) noexcept>();

    test_no_underlying_type<int (*)(...)>();
    test_no_underlying_type<int (*)(...) noexcept>();

    test_no_underlying_type<int (*)(int, ...)>();
    test_no_underlying_type<int (*)(int, ...) noexcept>();

    test_no_underlying_type<void (&)()>();
    test_no_underlying_type<void (&)() noexcept>();

    test_no_underlying_type<void (&)(int)>();
    test_no_underlying_type<void (&)(int) noexcept>();

    test_no_underlying_type<void (&)(...)>();
    test_no_underlying_type<void (&)(...) noexcept>();

    test_no_underlying_type<void (&)(int, ...)>();
    test_no_underlying_type<void (&)(int, ...) noexcept>();

    test_no_underlying_type<int (&)()>();
    test_no_underlying_type<int (&)() noexcept>();

    test_no_underlying_type<int (&)(int)>();
    test_no_underlying_type<int (&)(int) noexcept>();

    test_no_underlying_type<int (&)(...)>();
    test_no_underlying_type<int (&)(...) noexcept>();

    test_no_underlying_type<int (&)(int, ...)>();
    test_no_underlying_type<int (&)(int, ...) noexcept>();

    test_no_underlying_type<void (&&)()>();
    test_no_underlying_type<void (&&)() noexcept>();

    test_no_underlying_type<void (&&)(int)>();
    test_no_underlying_type<void (&&)(int) noexcept>();

    test_no_underlying_type<void (&&)(...)>();
    test_no_underlying_type<void (&&)(...) noexcept>();

    test_no_underlying_type<void (&&)(int, ...)>();
    test_no_underlying_type<void (&&)(int, ...) noexcept>();

    test_no_underlying_type<int (&&)()>();
    test_no_underlying_type<int (&&)() noexcept>();

    test_no_underlying_type<int (&&)(int)>();
    test_no_underlying_type<int (&&)(int) noexcept>();

    test_no_underlying_type<int (&&)(...)>();
    test_no_underlying_type<int (&&)(...) noexcept>();

    test_no_underlying_type<int (&&)(int, ...)>();
    test_no_underlying_type<int (&&)(int, ...) noexcept>();

    test_no_underlying_type<void (class_type::*)()>();
    test_no_underlying_type<void (class_type::*)()&>();
    test_no_underlying_type<void (class_type::*)() &&>();
    test_no_underlying_type<void (class_type::*)() const>();
    test_no_underlying_type<void (class_type::*)() const&>();
    test_no_underlying_type<void (class_type::*)() const&&>();
    test_no_underlying_type<void (class_type::*)() noexcept>();
    test_no_underlying_type<void (class_type::*)()& noexcept>();
    test_no_underlying_type<void (class_type::*)()&& noexcept>();
    test_no_underlying_type<void (class_type::*)() const noexcept>();
    test_no_underlying_type<void (class_type::*)() const& noexcept>();
    test_no_underlying_type<void (class_type::*)() const&& noexcept>();

    test_no_underlying_type<void (class_type::*)(int)>();
    test_no_underlying_type<void (class_type::*)(int)&>();
    test_no_underlying_type<void (class_type::*)(int) &&>();
    test_no_underlying_type<void (class_type::*)(int) const>();
    test_no_underlying_type<void (class_type::*)(int) const&>();
    test_no_underlying_type<void (class_type::*)(int) const&&>();
    test_no_underlying_type<void (class_type::*)(int) noexcept>();
    test_no_underlying_type<void (class_type::*)(int)& noexcept>();
    test_no_underlying_type<void (class_type::*)(int)&& noexcept>();
    test_no_underlying_type<void (class_type::*)(int) const noexcept>();
    test_no_underlying_type<void (class_type::*)(int) const& noexcept>();
    test_no_underlying_type<void (class_type::*)(int) const&& noexcept>();

    test_no_underlying_type<void (class_type::*)(...)>();
    test_no_underlying_type<void (class_type::*)(...)&>();
    test_no_underlying_type<void (class_type::*)(...) &&>();
    test_no_underlying_type<void (class_type::*)(...) const>();
    test_no_underlying_type<void (class_type::*)(...) const&>();
    test_no_underlying_type<void (class_type::*)(...) const&&>();
    test_no_underlying_type<void (class_type::*)(...) noexcept>();
    test_no_underlying_type<void (class_type::*)(...)& noexcept>();
    test_no_underlying_type<void (class_type::*)(...)&& noexcept>();
    test_no_underlying_type<void (class_type::*)(...) const noexcept>();
    test_no_underlying_type<void (class_type::*)(...) const& noexcept>();
    test_no_underlying_type<void (class_type::*)(...) const&& noexcept>();

    test_no_underlying_type<void (class_type::*)(int, ...)>();
    test_no_underlying_type<void (class_type::*)(int, ...)&>();
    test_no_underlying_type<void (class_type::*)(int, ...) &&>();
    test_no_underlying_type<void (class_type::*)(int, ...) const>();
    test_no_underlying_type<void (class_type::*)(int, ...) const&>();
    test_no_underlying_type<void (class_type::*)(int, ...) const&&>();
    test_no_underlying_type<void (class_type::*)(int, ...) noexcept>();
    test_no_underlying_type<void (class_type::*)(int, ...)& noexcept>();
    test_no_underlying_type<void (class_type::*)(int, ...)&& noexcept>();
    test_no_underlying_type<void (class_type::*)(int, ...) const noexcept>();
    test_no_underlying_type<void (class_type::*)(int, ...) const& noexcept>();
    test_no_underlying_type<void (class_type::*)(int, ...) const&& noexcept>();

    test_no_underlying_type<int (class_type::*)()>();
    test_no_underlying_type<int (class_type::*)()&>();
    test_no_underlying_type<int (class_type::*)() &&>();
    test_no_underlying_type<int (class_type::*)() const>();
    test_no_underlying_type<int (class_type::*)() const&>();
    test_no_underlying_type<int (class_type::*)() const&&>();
    test_no_underlying_type<int (class_type::*)() noexcept>();
    test_no_underlying_type<int (class_type::*)()& noexcept>();
    test_no_underlying_type<int (class_type::*)()&& noexcept>();
    test_no_underlying_type<int (class_type::*)() const noexcept>();
    test_no_underlying_type<int (class_type::*)() const& noexcept>();
    test_no_underlying_type<int (class_type::*)() const&& noexcept>();

    test_no_underlying_type<int (class_type::*)(int)>();
    test_no_underlying_type<int (class_type::*)(int)&>();
    test_no_underlying_type<int (class_type::*)(int) &&>();
    test_no_underlying_type<int (class_type::*)(int) const>();
    test_no_underlying_type<int (class_type::*)(int) const&>();
    test_no_underlying_type<int (class_type::*)(int) const&&>();
    test_no_underlying_type<int (class_type::*)(int) noexcept>();
    test_no_underlying_type<int (class_type::*)(int)& noexcept>();
    test_no_underlying_type<int (class_type::*)(int)&& noexcept>();
    test_no_underlying_type<int (class_type::*)(int) const noexcept>();
    test_no_underlying_type<int (class_type::*)(int) const& noexcept>();
    test_no_underlying_type<int (class_type::*)(int) const&& noexcept>();

    test_no_underlying_type<int (class_type::*)(...)>();
    test_no_underlying_type<int (class_type::*)(...)&>();
    test_no_underlying_type<int (class_type::*)(...) &&>();
    test_no_underlying_type<int (class_type::*)(...) const>();
    test_no_underlying_type<int (class_type::*)(...) const&>();
    test_no_underlying_type<int (class_type::*)(...) const&&>();
    test_no_underlying_type<int (class_type::*)(...) noexcept>();
    test_no_underlying_type<int (class_type::*)(...)& noexcept>();
    test_no_underlying_type<int (class_type::*)(...)&& noexcept>();
    test_no_underlying_type<int (class_type::*)(...) const noexcept>();
    test_no_underlying_type<int (class_type::*)(...) const& noexcept>();
    test_no_underlying_type<int (class_type::*)(...) const&& noexcept>();

    test_no_underlying_type<int (class_type::*)(int, ...)>();
    test_no_underlying_type<int (class_type::*)(int, ...)&>();
    test_no_underlying_type<int (class_type::*)(int, ...) &&>();
    test_no_underlying_type<int (class_type::*)(int, ...) const>();
    test_no_underlying_type<int (class_type::*)(int, ...) const&>();
    test_no_underlying_type<int (class_type::*)(int, ...) const&&>();
    test_no_underlying_type<int (class_type::*)(int, ...) noexcept>();
    test_no_underlying_type<int (class_type::*)(int, ...)& noexcept>();
    test_no_underlying_type<int (class_type::*)(int, ...)&& noexcept>();
    test_no_underlying_type<int (class_type::*)(int, ...) const noexcept>();
    test_no_underlying_type<int (class_type::*)(int, ...) const& noexcept>();
    test_no_underlying_type<int (class_type::*)(int, ...) const&& noexcept>();
}
