#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/conditional.hpp>
#include <phi/type_traits/make_unsigned.hpp>
#include <cstdint>
#include <vector>

template <typename T, typename U = T>
void test_make_unsigned_impl()
{
    CHECK_SAME_TYPE(typename phi::make_unsigned<T>::type, U);
    CHECK_SAME_TYPE(phi::make_unsigned_t<T>, U);
}

template <typename T, typename U = T>
void test_make_unsigned()
{
    test_make_unsigned_impl<T, U>();
    test_make_unsigned_impl<const T, const U>();
    test_make_unsigned_impl<volatile T, volatile U>();
    test_make_unsigned_impl<const volatile T, const volatile U>();
}

enum BigEnum : unsigned long long
{
    bigzero,
    big = 0xFFFFFFFFFFFFFFFFULL
};

TEST_CASE("make_unsigned")
{
    // test_make_unsigned<
    //         Enum, phi::conditional<sizeof(Enum) == sizeof(int), unsigned int, unsigned char>>();

    test_make_unsigned<void>();
    test_make_unsigned<phi::nullptr_t>();
    test_make_unsigned<bool>();
    test_make_unsigned<char, unsigned char>();
    test_make_unsigned<signed char, unsigned char>();
    test_make_unsigned<unsigned char, unsigned char>();
    test_make_unsigned<short, unsigned short>();
    test_make_unsigned<unsigned short, unsigned short>();
    test_make_unsigned<int, unsigned int>();
    test_make_unsigned<unsigned int, unsigned int>();
    test_make_unsigned<long, unsigned long>();
    test_make_unsigned<unsigned long, unsigned long>();
    test_make_unsigned<long long, unsigned long long>();
    test_make_unsigned<unsigned long long, unsigned long long>();
    test_make_unsigned<float>();
    test_make_unsigned<double>();
    test_make_unsigned<long double>();
    //test_make_unsigned<char8_t, std::uint8_t>();
    //test_make_unsigned<char16_t, std::uint16_t>();
    //test_make_unsigned<char32_t, std::uint32_t>();
    //test_make_unsigned<wchar_t,
    //                   phi::conditional<sizeof(wchar_t) == 4, std::uint32_t, std::uint16_t>>();

    test_make_unsigned<phi::boolean>();
    test_make_unsigned<phi::integer<signed char>, phi::integer<unsigned char>>();
    test_make_unsigned<phi::integer<unsigned char>, phi::integer<unsigned char>>();
    test_make_unsigned<phi::integer<short>, phi::integer<unsigned short>>();
    test_make_unsigned<phi::integer<unsigned short>, phi::integer<unsigned short>>();
    test_make_unsigned<phi::integer<int>, phi::integer<unsigned int>>();
    test_make_unsigned<phi::integer<unsigned int>, phi::integer<unsigned int>>();
    test_make_unsigned<phi::integer<long>, phi::integer<unsigned long>>();
    test_make_unsigned<phi::integer<unsigned long>, phi::integer<unsigned long>>();
    test_make_unsigned<phi::integer<long long>, phi::integer<unsigned long long>>();
    test_make_unsigned<phi::integer<unsigned long long>, phi::integer<unsigned long long>>();
    test_make_unsigned<phi::floating_point<float>>();
    test_make_unsigned<phi::floating_point<double>>();
    test_make_unsigned<phi::floating_point<long double>>();

    test_make_unsigned<std::vector<int>>();
    test_make_unsigned<phi::scope_ptr<int>>();

    test_make_unsigned<int&>();
    test_make_unsigned<const int&>();
    test_make_unsigned<volatile int&>();
    test_make_unsigned<const volatile int&>();
    test_make_unsigned<int&&>();
    test_make_unsigned<const int&&>();
    test_make_unsigned<volatile int&&>();
    test_make_unsigned<const volatile int&&>();
    test_make_unsigned<int*>();
    test_make_unsigned<const int*>();
    test_make_unsigned<volatile int*>();
    test_make_unsigned<const volatile int*>();
    test_make_unsigned<int**>();
    test_make_unsigned<const int**>();
    test_make_unsigned<volatile int**>();
    test_make_unsigned<const volatile int**>();
    test_make_unsigned<int*&>();
    test_make_unsigned<const int*&>();
    test_make_unsigned<volatile int*&>();
    test_make_unsigned<const volatile int*&>();
    test_make_unsigned<int*&&>();
    test_make_unsigned<const int*&&>();
    test_make_unsigned<volatile int*&&>();
    test_make_unsigned<const volatile int*&&>();
    test_make_unsigned<void*>();
    test_make_unsigned<char[3]>();
    test_make_unsigned<char[]>();
    test_make_unsigned<char* [3]>();
    test_make_unsigned<char*[]>();
    test_make_unsigned<int(*)[3]>();
    test_make_unsigned<int(*)[]>();
    test_make_unsigned<int(&)[3]>();
    test_make_unsigned<int(&)[]>();
    test_make_unsigned<int(&&)[3]>();
    test_make_unsigned<int(&&)[]>();
    test_make_unsigned<char[3][2]>();
    test_make_unsigned<char[][2]>();
    test_make_unsigned<char* [3][2]>();
    test_make_unsigned<char*[][2]>();
    test_make_unsigned<int(*)[3][2]>();
    test_make_unsigned<int(*)[][2]>();
    test_make_unsigned<int(&)[3][2]>();
    test_make_unsigned<int(&)[][2]>();
    test_make_unsigned<int(&&)[3][2]>();
    test_make_unsigned<int(&&)[][2]>();
    test_make_unsigned<class_type>();
    test_make_unsigned<class_type[]>();
    test_make_unsigned<class_type[2]>();
    test_make_unsigned<template_type<void>>();
    test_make_unsigned<template_type<int>>();
    test_make_unsigned<template_type<class_type>>();
    test_make_unsigned<template_type<incomplete_type>>();
    test_make_unsigned<variadic_template<>>();
    test_make_unsigned<variadic_template<void>>();
    test_make_unsigned<variadic_template<int>>();
    test_make_unsigned<variadic_template<class_type>>();
    test_make_unsigned<variadic_template<incomplete_type>>();
    test_make_unsigned<variadic_template<int, void, class_type, volatile char[]>>();
    test_make_unsigned<public_derived_from<base>>();
    test_make_unsigned<public_derived_from<derived>>();
    test_make_unsigned<public_derived_from<class_type>>();
    test_make_unsigned<private_derived_from<base>>();
    test_make_unsigned<private_derived_from<derived>>();
    test_make_unsigned<private_derived_from<class_type>>();
    test_make_unsigned<protected_derived_from<base>>();
    test_make_unsigned<protected_derived_from<derived>>();
    test_make_unsigned<protected_derived_from<class_type>>();
    test_make_unsigned<union_type>();
    test_make_unsigned<non_empty_union>();
    test_make_unsigned<empty>();
    test_make_unsigned<not_empty>();
    test_make_unsigned<bit_zero>();
    test_make_unsigned<bit_one>();
    test_make_unsigned<base>();
    test_make_unsigned<derived>();
    test_make_unsigned<abstract>();
    test_make_unsigned<abstract_template<int>>();
    test_make_unsigned<abstract_template<double>>();
    test_make_unsigned<abstract_template<class_type>>();
    test_make_unsigned<abstract_template<incomplete_type>>();
    test_make_unsigned<final_type>();
    //test_make_unsigned<Enum, unsigned>();
    //test_make_unsigned<EnumSigned, unsigned>();
    //test_make_unsigned<EnumUnsigned, unsigned>();
    //test_make_unsigned<EnumClass, unsigned>();
    //test_make_unsigned<EnumStruct, unsigned>();
    test_make_unsigned<function_type>();
    test_make_unsigned<function_ptr>();
    test_make_unsigned<member_object_ptr>();
    test_make_unsigned<member_function_ptr>();
    test_make_unsigned<incomplete_type>();
    test_make_unsigned<incomplete_template<void>>();
    test_make_unsigned<incomplete_template<int>>();
    test_make_unsigned<incomplete_template<class_type>>();
    test_make_unsigned<incomplete_template<incomplete_type>>();
    test_make_unsigned<incomplete_variadic_template<>>();
    test_make_unsigned<incomplete_variadic_template<void>>();
    test_make_unsigned<incomplete_variadic_template<int>>();
    test_make_unsigned<incomplete_variadic_template<class_type>>();
    test_make_unsigned<incomplete_variadic_template<incomplete_type>>();
    test_make_unsigned<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_make_unsigned<int class_type::*>();
    test_make_unsigned<float class_type::*>();
    test_make_unsigned<void * class_type::*>();
    test_make_unsigned<int * class_type::*>();
    test_make_unsigned<int class_type::*&>();
    test_make_unsigned<float class_type::*&>();
    test_make_unsigned<void * class_type::*&>();
    test_make_unsigned<int * class_type::*&>();
    test_make_unsigned<int class_type::*&&>();
    test_make_unsigned<float class_type::*&&>();
    test_make_unsigned<void * class_type::*&&>();
    test_make_unsigned<int * class_type::*&&>();
    test_make_unsigned<non_copyable>();
    test_make_unsigned<non_moveable>();
    test_make_unsigned<non_constructible>();
    test_make_unsigned<tracked>();
    test_make_unsigned<trap_constructible>();
    test_make_unsigned<trap_implicit_conversion>();
    test_make_unsigned<trap_comma>();
    test_make_unsigned<trap_call>();
    test_make_unsigned<trap_self_assign>();

    test_make_unsigned<void()>();
    test_make_unsigned<void()&>();
    test_make_unsigned<void() &&>();
    test_make_unsigned<void() const>();
    test_make_unsigned<void() const&>();
    test_make_unsigned<void() const&&>();
    test_make_unsigned<void() noexcept>();
    test_make_unsigned<void()& noexcept>();
    test_make_unsigned<void()&& noexcept>();
    test_make_unsigned<void() const noexcept>();
    test_make_unsigned<void() const& noexcept>();
    test_make_unsigned<void() const&& noexcept>();

    test_make_unsigned<void(int)>();
    test_make_unsigned<void(int)&>();
    test_make_unsigned<void(int) &&>();
    test_make_unsigned<void(int) const>();
    test_make_unsigned<void(int) const&>();
    test_make_unsigned<void(int) const&&>();
    test_make_unsigned<void(int) noexcept>();
    test_make_unsigned<void(int)& noexcept>();
    test_make_unsigned<void(int)&& noexcept>();
    test_make_unsigned<void(int) const noexcept>();
    test_make_unsigned<void(int) const& noexcept>();
    test_make_unsigned<void(int) const&& noexcept>();

    test_make_unsigned<void(...)>();
    test_make_unsigned<void(...)&>();
    test_make_unsigned<void(...) &&>();
    test_make_unsigned<void(...) const>();
    test_make_unsigned<void(...) const&>();
    test_make_unsigned<void(...) const&&>();
    test_make_unsigned<void(...) noexcept>();
    test_make_unsigned<void(...)& noexcept>();
    test_make_unsigned<void(...)&& noexcept>();
    test_make_unsigned<void(...) const noexcept>();
    test_make_unsigned<void(...) const& noexcept>();
    test_make_unsigned<void(...) const&& noexcept>();

    test_make_unsigned<void(int, ...)>();
    test_make_unsigned<void(int, ...)&>();
    test_make_unsigned<void(int, ...) &&>();
    test_make_unsigned<void(int, ...) const>();
    test_make_unsigned<void(int, ...) const&>();
    test_make_unsigned<void(int, ...) const&&>();
    test_make_unsigned<void(int, ...) noexcept>();
    test_make_unsigned<void(int, ...)& noexcept>();
    test_make_unsigned<void(int, ...)&& noexcept>();
    test_make_unsigned<void(int, ...) const noexcept>();
    test_make_unsigned<void(int, ...) const& noexcept>();
    test_make_unsigned<void(int, ...) const&& noexcept>();

    test_make_unsigned<int()>();
    test_make_unsigned<int()&>();
    test_make_unsigned<int() &&>();
    test_make_unsigned<int() const>();
    test_make_unsigned<int() const&>();
    test_make_unsigned<int() const&&>();
    test_make_unsigned<int() noexcept>();
    test_make_unsigned<int()& noexcept>();
    test_make_unsigned<int()&& noexcept>();
    test_make_unsigned<int() const noexcept>();
    test_make_unsigned<int() const& noexcept>();
    test_make_unsigned<int() const&& noexcept>();

    test_make_unsigned<int(int)>();
    test_make_unsigned<int(int)&>();
    test_make_unsigned<int(int) &&>();
    test_make_unsigned<int(int) const>();
    test_make_unsigned<int(int) const&>();
    test_make_unsigned<int(int) const&&>();
    test_make_unsigned<int(int) noexcept>();
    test_make_unsigned<int(int)& noexcept>();
    test_make_unsigned<int(int)&& noexcept>();
    test_make_unsigned<int(int) const noexcept>();
    test_make_unsigned<int(int) const& noexcept>();
    test_make_unsigned<int(int) const&& noexcept>();

    test_make_unsigned<int(...)>();
    test_make_unsigned<int(...)&>();
    test_make_unsigned<int(...) &&>();
    test_make_unsigned<int(...) const>();
    test_make_unsigned<int(...) const&>();
    test_make_unsigned<int(...) const&&>();
    test_make_unsigned<int(...) noexcept>();
    test_make_unsigned<int(...)& noexcept>();
    test_make_unsigned<int(...)&& noexcept>();
    test_make_unsigned<int(...) const noexcept>();
    test_make_unsigned<int(...) const& noexcept>();
    test_make_unsigned<int(...) const&& noexcept>();

    test_make_unsigned<int(int, ...)>();
    test_make_unsigned<int(int, ...)&>();
    test_make_unsigned<int(int, ...) &&>();
    test_make_unsigned<int(int, ...) const>();
    test_make_unsigned<int(int, ...) const&>();
    test_make_unsigned<int(int, ...) const&&>();
    test_make_unsigned<int(int, ...) noexcept>();
    test_make_unsigned<int(int, ...)& noexcept>();
    test_make_unsigned<int(int, ...)&& noexcept>();
    test_make_unsigned<int(int, ...) const noexcept>();
    test_make_unsigned<int(int, ...) const& noexcept>();
    test_make_unsigned<int(int, ...) const&& noexcept>();

    test_make_unsigned<void (*)()>();
    test_make_unsigned<void (*)() noexcept>();

    test_make_unsigned<void (*)(int)>();
    test_make_unsigned<void (*)(int) noexcept>();

    test_make_unsigned<void (*)(...)>();
    test_make_unsigned<void (*)(...) noexcept>();

    test_make_unsigned<void (*)(int, ...)>();
    test_make_unsigned<void (*)(int, ...) noexcept>();

    test_make_unsigned<int (*)()>();
    test_make_unsigned<int (*)() noexcept>();

    test_make_unsigned<int (*)(int)>();
    test_make_unsigned<int (*)(int) noexcept>();

    test_make_unsigned<int (*)(...)>();
    test_make_unsigned<int (*)(...) noexcept>();

    test_make_unsigned<int (*)(int, ...)>();
    test_make_unsigned<int (*)(int, ...) noexcept>();

    test_make_unsigned<void (&)()>();
    test_make_unsigned<void (&)() noexcept>();

    test_make_unsigned<void (&)(int)>();
    test_make_unsigned<void (&)(int) noexcept>();

    test_make_unsigned<void (&)(...)>();
    test_make_unsigned<void (&)(...) noexcept>();

    test_make_unsigned<void (&)(int, ...)>();
    test_make_unsigned<void (&)(int, ...) noexcept>();

    test_make_unsigned<int (&)()>();
    test_make_unsigned<int (&)() noexcept>();

    test_make_unsigned<int (&)(int)>();
    test_make_unsigned<int (&)(int) noexcept>();

    test_make_unsigned<int (&)(...)>();
    test_make_unsigned<int (&)(...) noexcept>();

    test_make_unsigned<int (&)(int, ...)>();
    test_make_unsigned<int (&)(int, ...) noexcept>();

    test_make_unsigned<void (&&)()>();
    test_make_unsigned<void (&&)() noexcept>();

    test_make_unsigned<void (&&)(int)>();
    test_make_unsigned<void (&&)(int) noexcept>();

    test_make_unsigned<void (&&)(...)>();
    test_make_unsigned<void (&&)(...) noexcept>();

    test_make_unsigned<void (&&)(int, ...)>();
    test_make_unsigned<void (&&)(int, ...) noexcept>();

    test_make_unsigned<int (&&)()>();
    test_make_unsigned<int (&&)() noexcept>();

    test_make_unsigned<int (&&)(int)>();
    test_make_unsigned<int (&&)(int) noexcept>();

    test_make_unsigned<int (&&)(...)>();
    test_make_unsigned<int (&&)(...) noexcept>();

    test_make_unsigned<int (&&)(int, ...)>();
    test_make_unsigned<int (&&)(int, ...) noexcept>();

    test_make_unsigned<void (class_type::*)()>();
    test_make_unsigned<void (class_type::*)()&>();
    test_make_unsigned<void (class_type::*)() &&>();
    test_make_unsigned<void (class_type::*)() const>();
    test_make_unsigned<void (class_type::*)() const&>();
    test_make_unsigned<void (class_type::*)() const&&>();
    test_make_unsigned<void (class_type::*)() noexcept>();
    test_make_unsigned<void (class_type::*)()& noexcept>();
    test_make_unsigned<void (class_type::*)()&& noexcept>();
    test_make_unsigned<void (class_type::*)() const noexcept>();
    test_make_unsigned<void (class_type::*)() const& noexcept>();
    test_make_unsigned<void (class_type::*)() const&& noexcept>();

    test_make_unsigned<void (class_type::*)(int)>();
    test_make_unsigned<void (class_type::*)(int)&>();
    test_make_unsigned<void (class_type::*)(int) &&>();
    test_make_unsigned<void (class_type::*)(int) const>();
    test_make_unsigned<void (class_type::*)(int) const&>();
    test_make_unsigned<void (class_type::*)(int) const&&>();
    test_make_unsigned<void (class_type::*)(int) noexcept>();
    test_make_unsigned<void (class_type::*)(int)& noexcept>();
    test_make_unsigned<void (class_type::*)(int)&& noexcept>();
    test_make_unsigned<void (class_type::*)(int) const noexcept>();
    test_make_unsigned<void (class_type::*)(int) const& noexcept>();
    test_make_unsigned<void (class_type::*)(int) const&& noexcept>();

    test_make_unsigned<void (class_type::*)(...)>();
    test_make_unsigned<void (class_type::*)(...)&>();
    test_make_unsigned<void (class_type::*)(...) &&>();
    test_make_unsigned<void (class_type::*)(...) const>();
    test_make_unsigned<void (class_type::*)(...) const&>();
    test_make_unsigned<void (class_type::*)(...) const&&>();
    test_make_unsigned<void (class_type::*)(...) noexcept>();
    test_make_unsigned<void (class_type::*)(...)& noexcept>();
    test_make_unsigned<void (class_type::*)(...)&& noexcept>();
    test_make_unsigned<void (class_type::*)(...) const noexcept>();
    test_make_unsigned<void (class_type::*)(...) const& noexcept>();
    test_make_unsigned<void (class_type::*)(...) const&& noexcept>();

    test_make_unsigned<void (class_type::*)(int, ...)>();
    test_make_unsigned<void (class_type::*)(int, ...)&>();
    test_make_unsigned<void (class_type::*)(int, ...) &&>();
    test_make_unsigned<void (class_type::*)(int, ...) const>();
    test_make_unsigned<void (class_type::*)(int, ...) const&>();
    test_make_unsigned<void (class_type::*)(int, ...) const&&>();
    test_make_unsigned<void (class_type::*)(int, ...) noexcept>();
    test_make_unsigned<void (class_type::*)(int, ...)& noexcept>();
    test_make_unsigned<void (class_type::*)(int, ...)&& noexcept>();
    test_make_unsigned<void (class_type::*)(int, ...) const noexcept>();
    test_make_unsigned<void (class_type::*)(int, ...) const& noexcept>();
    test_make_unsigned<void (class_type::*)(int, ...) const&& noexcept>();

    test_make_unsigned<int (class_type::*)()>();
    test_make_unsigned<int (class_type::*)()&>();
    test_make_unsigned<int (class_type::*)() &&>();
    test_make_unsigned<int (class_type::*)() const>();
    test_make_unsigned<int (class_type::*)() const&>();
    test_make_unsigned<int (class_type::*)() const&&>();
    test_make_unsigned<int (class_type::*)() noexcept>();
    test_make_unsigned<int (class_type::*)()& noexcept>();
    test_make_unsigned<int (class_type::*)()&& noexcept>();
    test_make_unsigned<int (class_type::*)() const noexcept>();
    test_make_unsigned<int (class_type::*)() const& noexcept>();
    test_make_unsigned<int (class_type::*)() const&& noexcept>();

    test_make_unsigned<int (class_type::*)(int)>();
    test_make_unsigned<int (class_type::*)(int)&>();
    test_make_unsigned<int (class_type::*)(int) &&>();
    test_make_unsigned<int (class_type::*)(int) const>();
    test_make_unsigned<int (class_type::*)(int) const&>();
    test_make_unsigned<int (class_type::*)(int) const&&>();
    test_make_unsigned<int (class_type::*)(int) noexcept>();
    test_make_unsigned<int (class_type::*)(int)& noexcept>();
    test_make_unsigned<int (class_type::*)(int)&& noexcept>();
    test_make_unsigned<int (class_type::*)(int) const noexcept>();
    test_make_unsigned<int (class_type::*)(int) const& noexcept>();
    test_make_unsigned<int (class_type::*)(int) const&& noexcept>();

    test_make_unsigned<int (class_type::*)(...)>();
    test_make_unsigned<int (class_type::*)(...)&>();
    test_make_unsigned<int (class_type::*)(...) &&>();
    test_make_unsigned<int (class_type::*)(...) const>();
    test_make_unsigned<int (class_type::*)(...) const&>();
    test_make_unsigned<int (class_type::*)(...) const&&>();
    test_make_unsigned<int (class_type::*)(...) noexcept>();
    test_make_unsigned<int (class_type::*)(...)& noexcept>();
    test_make_unsigned<int (class_type::*)(...)&& noexcept>();
    test_make_unsigned<int (class_type::*)(...) const noexcept>();
    test_make_unsigned<int (class_type::*)(...) const& noexcept>();
    test_make_unsigned<int (class_type::*)(...) const&& noexcept>();

    test_make_unsigned<int (class_type::*)(int, ...)>();
    test_make_unsigned<int (class_type::*)(int, ...)&>();
    test_make_unsigned<int (class_type::*)(int, ...) &&>();
    test_make_unsigned<int (class_type::*)(int, ...) const>();
    test_make_unsigned<int (class_type::*)(int, ...) const&>();
    test_make_unsigned<int (class_type::*)(int, ...) const&&>();
    test_make_unsigned<int (class_type::*)(int, ...) noexcept>();
    test_make_unsigned<int (class_type::*)(int, ...)& noexcept>();
    test_make_unsigned<int (class_type::*)(int, ...)&& noexcept>();
    test_make_unsigned<int (class_type::*)(int, ...) const noexcept>();
    test_make_unsigned<int (class_type::*)(int, ...) const& noexcept>();
    test_make_unsigned<int (class_type::*)(int, ...) const&& noexcept>();
}
