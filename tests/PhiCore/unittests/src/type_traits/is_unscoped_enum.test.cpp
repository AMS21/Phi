#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_unscoped_enum.hpp>

PHI_EXTERNAL_HEADERS_BEGIN()
#include <type_traits>
#include <vector>
PHI_EXTERNAL_HEADERS_END()

template <typename TypeT>
void test_is_unscoped_enum_impl()
{
#if PHI_HAS_WORKING_IS_UNSCOPED_ENUM()
    STATIC_REQUIRE(phi::is_unscoped_enum<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_unscoped_enum<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unscoped_enum_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_unscoped_enum_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unscoped_enum<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unscoped_enum<TypeT>);
#endif
}

template <typename TypeT>
void test_is_not_unscoped_enum_impl()
{
#if PHI_HAS_WORKING_IS_UNSCOPED_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_unscoped_enum<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_unscoped_enum<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unscoped_enum_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_unscoped_enum_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unscoped_enum<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unscoped_enum<TypeT>);
#endif
}

template <typename TypeT>
void test_is_unscoped_enum()
{
    test_is_unscoped_enum_impl<TypeT>();
    test_is_unscoped_enum_impl<const TypeT>();
    test_is_unscoped_enum_impl<volatile TypeT>();
    test_is_unscoped_enum_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_unscoped_enum()
{
    test_is_not_unscoped_enum_impl<TypeT>();
    test_is_not_unscoped_enum_impl<const TypeT>();
    test_is_not_unscoped_enum_impl<volatile TypeT>();
    test_is_not_unscoped_enum_impl<const volatile TypeT>();
}

struct A
{};

enum E
{
};

enum struct EStruct
{
};

enum class EClass
{
};

TEST_CASE("is_unscoped_enum")
{
    test_is_unscoped_enum<E>();
    test_is_not_unscoped_enum<EStruct>();
    test_is_not_unscoped_enum<EClass>();
    test_is_not_unscoped_enum<A>();

    test_is_not_unscoped_enum<void>();
    test_is_not_unscoped_enum<phi::nullptr_t>();
    test_is_not_unscoped_enum<bool>();
    test_is_not_unscoped_enum<char>();
    test_is_not_unscoped_enum<signed char>();
    test_is_not_unscoped_enum<unsigned char>();
    test_is_not_unscoped_enum<short>();
    test_is_not_unscoped_enum<unsigned short>();
    test_is_not_unscoped_enum<int>();
    test_is_not_unscoped_enum<unsigned int>();
    test_is_not_unscoped_enum<long>();
    test_is_not_unscoped_enum<unsigned long>();
    test_is_not_unscoped_enum<long long>();
    test_is_not_unscoped_enum<unsigned long long>();
    test_is_not_unscoped_enum<float>();
    test_is_not_unscoped_enum<double>();
    test_is_not_unscoped_enum<long double>();
    test_is_not_unscoped_enum<char8_t>();
    test_is_not_unscoped_enum<char16_t>();
    test_is_not_unscoped_enum<char32_t>();
    test_is_not_unscoped_enum<wchar_t>();

    test_is_not_unscoped_enum<phi::boolean>();
    test_is_not_unscoped_enum<phi::integer<signed char>>();
    test_is_not_unscoped_enum<phi::integer<unsigned char>>();
    test_is_not_unscoped_enum<phi::integer<short>>();
    test_is_not_unscoped_enum<phi::integer<unsigned short>>();
    test_is_not_unscoped_enum<phi::integer<int>>();
    test_is_not_unscoped_enum<phi::integer<unsigned int>>();
    test_is_not_unscoped_enum<phi::integer<long>>();
    test_is_not_unscoped_enum<phi::integer<unsigned long>>();
    test_is_not_unscoped_enum<phi::integer<long long>>();
    test_is_not_unscoped_enum<phi::integer<unsigned long long>>();
    test_is_not_unscoped_enum<phi::floating_point<float>>();
    test_is_not_unscoped_enum<phi::floating_point<double>>();
    test_is_not_unscoped_enum<phi::floating_point<long double>>();

    test_is_not_unscoped_enum<std::vector<int>>();
    test_is_not_unscoped_enum<phi::scope_ptr<int>>();

    test_is_not_unscoped_enum<int&>();
    test_is_not_unscoped_enum<const int&>();
    test_is_not_unscoped_enum<volatile int&>();
    test_is_not_unscoped_enum<const volatile int&>();
    test_is_not_unscoped_enum<int&&>();
    test_is_not_unscoped_enum<const int&&>();
    test_is_not_unscoped_enum<volatile int&&>();
    test_is_not_unscoped_enum<const volatile int&&>();
    test_is_not_unscoped_enum<int*>();
    test_is_not_unscoped_enum<const int*>();
    test_is_not_unscoped_enum<volatile int*>();
    test_is_not_unscoped_enum<const volatile int*>();
    test_is_not_unscoped_enum<int**>();
    test_is_not_unscoped_enum<const int**>();
    test_is_not_unscoped_enum<volatile int**>();
    test_is_not_unscoped_enum<const volatile int**>();
    test_is_not_unscoped_enum<int*&>();
    test_is_not_unscoped_enum<const int*&>();
    test_is_not_unscoped_enum<volatile int*&>();
    test_is_not_unscoped_enum<const volatile int*&>();
    test_is_not_unscoped_enum<int*&&>();
    test_is_not_unscoped_enum<const int*&&>();
    test_is_not_unscoped_enum<volatile int*&&>();
    test_is_not_unscoped_enum<const volatile int*&&>();
    test_is_not_unscoped_enum<void*>();
    test_is_not_unscoped_enum<char[3]>();
    test_is_not_unscoped_enum<char[]>();
    test_is_not_unscoped_enum<char* [3]>();
    test_is_not_unscoped_enum<char*[]>();
    test_is_not_unscoped_enum<int(*)[3]>();
    test_is_not_unscoped_enum<int(*)[]>();
    test_is_not_unscoped_enum<int(&)[3]>();
    test_is_not_unscoped_enum<int(&)[]>();
    test_is_not_unscoped_enum<int(&&)[3]>();
    test_is_not_unscoped_enum<int(&&)[]>();
    test_is_not_unscoped_enum<char[3][2]>();
    test_is_not_unscoped_enum<char[][2]>();
    test_is_not_unscoped_enum<char* [3][2]>();
    test_is_not_unscoped_enum<char*[][2]>();
    test_is_not_unscoped_enum<int(*)[3][2]>();
    test_is_not_unscoped_enum<int(*)[][2]>();
    test_is_not_unscoped_enum<int(&)[3][2]>();
    test_is_not_unscoped_enum<int(&)[][2]>();
    test_is_not_unscoped_enum<int(&&)[3][2]>();
    test_is_not_unscoped_enum<int(&&)[][2]>();
    test_is_not_unscoped_enum<class_type>();
    test_is_not_unscoped_enum<class_type[]>();
    test_is_not_unscoped_enum<class_type[2]>();
    test_is_not_unscoped_enum<template_type<void>>();
    test_is_not_unscoped_enum<template_type<int>>();
    test_is_not_unscoped_enum<template_type<class_type>>();
    test_is_not_unscoped_enum<template_type<incomplete_type>>();
    test_is_not_unscoped_enum<variadic_template<>>();
    test_is_not_unscoped_enum<variadic_template<void>>();
    test_is_not_unscoped_enum<variadic_template<int>>();
    test_is_not_unscoped_enum<variadic_template<class_type>>();
    test_is_not_unscoped_enum<variadic_template<incomplete_type>>();
    test_is_not_unscoped_enum<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_unscoped_enum<public_derived_from<base>>();
    test_is_not_unscoped_enum<public_derived_from<derived>>();
    test_is_not_unscoped_enum<public_derived_from<class_type>>();
    test_is_not_unscoped_enum<private_derived_from<base>>();
    test_is_not_unscoped_enum<private_derived_from<derived>>();
    test_is_not_unscoped_enum<private_derived_from<class_type>>();
    test_is_not_unscoped_enum<protected_derived_from<base>>();
    test_is_not_unscoped_enum<protected_derived_from<derived>>();
    test_is_not_unscoped_enum<protected_derived_from<class_type>>();
    test_is_not_unscoped_enum<union_type>();
    test_is_not_unscoped_enum<non_empty_union>();
    test_is_not_unscoped_enum<empty>();
    test_is_not_unscoped_enum<not_empty>();
    test_is_not_unscoped_enum<bit_zero>();
    test_is_not_unscoped_enum<bit_one>();
    test_is_not_unscoped_enum<base>();
    test_is_not_unscoped_enum<derived>();
    test_is_not_unscoped_enum<abstract>();
    test_is_not_unscoped_enum<public_abstract>();
    test_is_not_unscoped_enum<private_abstract>();
    test_is_not_unscoped_enum<protected_abstract>();
    test_is_not_unscoped_enum<abstract_template<int>>();
    test_is_not_unscoped_enum<abstract_template<double>>();
    test_is_not_unscoped_enum<abstract_template<class_type>>();
    test_is_not_unscoped_enum<abstract_template<incomplete_type>>();
    test_is_not_unscoped_enum<final_type>();
    test_is_not_unscoped_enum<public_destructor>();
    test_is_not_unscoped_enum<protected_destructor>();
    test_is_not_unscoped_enum<private_destructor>();
    test_is_not_unscoped_enum<virtual_public_destructor>();
    test_is_not_unscoped_enum<virtual_protected_destructor>();
    test_is_not_unscoped_enum<virtual_private_destructor>();
    test_is_not_unscoped_enum<pure_public_destructor>();
    test_is_not_unscoped_enum<pure_protected_destructor>();
    test_is_not_unscoped_enum<pure_private_destructor>();
    test_is_not_unscoped_enum<deleted_public_destructor>();
    test_is_not_unscoped_enum<deleted_protected_destructor>();
    test_is_not_unscoped_enum<deleted_private_destructor>();
    test_is_not_unscoped_enum<deleted_virtual_public_destructor>();
    test_is_not_unscoped_enum<deleted_virtual_protected_destructor>();
    test_is_not_unscoped_enum<deleted_virtual_private_destructor>();
    test_is_unscoped_enum<Enum>();
    test_is_unscoped_enum<EnumSigned>();
    test_is_unscoped_enum<EnumUnsigned>();
    test_is_not_unscoped_enum<EnumClass>();
    test_is_not_unscoped_enum<EnumStruct>();
    test_is_not_unscoped_enum<function_type>();
    test_is_not_unscoped_enum<function_ptr>();
    test_is_not_unscoped_enum<member_object_ptr>();
    test_is_not_unscoped_enum<member_function_ptr>();
    test_is_not_unscoped_enum<incomplete_type>();
    test_is_not_unscoped_enum<incomplete_template<void>>();
    test_is_not_unscoped_enum<incomplete_template<int>>();
    test_is_not_unscoped_enum<incomplete_template<class_type>>();
    test_is_not_unscoped_enum<incomplete_template<incomplete_type>>();
    test_is_not_unscoped_enum<incomplete_variadic_template<>>();
    test_is_not_unscoped_enum<incomplete_variadic_template<void>>();
    test_is_not_unscoped_enum<incomplete_variadic_template<int>>();
    test_is_not_unscoped_enum<incomplete_variadic_template<class_type>>();
    test_is_not_unscoped_enum<incomplete_variadic_template<incomplete_type>>();
    test_is_not_unscoped_enum<
            incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_unscoped_enum<int class_type::*>();
    test_is_not_unscoped_enum<float class_type::*>();
    test_is_not_unscoped_enum<void * class_type::*>();
    test_is_not_unscoped_enum<int * class_type::*>();
    test_is_not_unscoped_enum<int class_type::*&>();
    test_is_not_unscoped_enum<float class_type::*&>();
    test_is_not_unscoped_enum<void * class_type::*&>();
    test_is_not_unscoped_enum<int * class_type::*&>();
    test_is_not_unscoped_enum<int class_type::*&&>();
    test_is_not_unscoped_enum<float class_type::*&&>();
    test_is_not_unscoped_enum<void * class_type::*&&>();
    test_is_not_unscoped_enum<int * class_type::*&&>();
    test_is_not_unscoped_enum<int class_type::*const>();
    test_is_not_unscoped_enum<float class_type::*const>();
    test_is_not_unscoped_enum<void * class_type::*const>();
    test_is_not_unscoped_enum<int class_type::*const&>();
    test_is_not_unscoped_enum<float class_type::*const&>();
    test_is_not_unscoped_enum<void * class_type::*const&>();
    test_is_not_unscoped_enum<int class_type::*const&&>();
    test_is_not_unscoped_enum<float class_type::*const&&>();
    test_is_not_unscoped_enum<void * class_type::*const&&>();
    test_is_not_unscoped_enum<int class_type::*volatile>();
    test_is_not_unscoped_enum<float class_type::*volatile>();
    test_is_not_unscoped_enum<void * class_type::*volatile>();
    test_is_not_unscoped_enum<int class_type::*volatile&>();
    test_is_not_unscoped_enum<float class_type::*volatile&>();
    test_is_not_unscoped_enum<void * class_type::*volatile&>();
    test_is_not_unscoped_enum<int class_type::*volatile&&>();
    test_is_not_unscoped_enum<float class_type::*volatile&&>();
    test_is_not_unscoped_enum<void * class_type::*volatile&&>();
    test_is_not_unscoped_enum<int class_type::*const volatile>();
    test_is_not_unscoped_enum<float class_type::*const volatile>();
    test_is_not_unscoped_enum<void * class_type::*const volatile>();
    test_is_not_unscoped_enum<int class_type::*const volatile&>();
    test_is_not_unscoped_enum<float class_type::*const volatile&>();
    test_is_not_unscoped_enum<void * class_type::*const volatile&>();
    test_is_not_unscoped_enum<int class_type::*const volatile&&>();
    test_is_not_unscoped_enum<float class_type::*const volatile&&>();
    test_is_not_unscoped_enum<void * class_type::*const volatile&&>();
    test_is_not_unscoped_enum<non_copyable>();
    test_is_not_unscoped_enum<non_moveable>();
    test_is_not_unscoped_enum<non_constructible>();
    test_is_not_unscoped_enum<tracked>();
    test_is_not_unscoped_enum<trap_constructible>();
    test_is_not_unscoped_enum<trap_implicit_conversion>();
    test_is_not_unscoped_enum<trap_comma>();
    test_is_not_unscoped_enum<trap_call>();
    test_is_not_unscoped_enum<trap_self_assign>();
    test_is_not_unscoped_enum<trap_deref>();
    test_is_not_unscoped_enum<trap_array_subscript>();

    test_is_not_unscoped_enum<void()>();
    test_is_not_unscoped_enum<void()&>();
    test_is_not_unscoped_enum<void() &&>();
    test_is_not_unscoped_enum<void() const>();
    test_is_not_unscoped_enum<void() const&>();
    test_is_not_unscoped_enum<void() const&&>();
    test_is_not_unscoped_enum<void() volatile>();
    test_is_not_unscoped_enum<void() volatile&>();
    test_is_not_unscoped_enum<void() volatile&&>();
    test_is_not_unscoped_enum<void() const volatile>();
    test_is_not_unscoped_enum<void() const volatile&>();
    test_is_not_unscoped_enum<void() const volatile&&>();
    test_is_not_unscoped_enum<void() noexcept>();
    test_is_not_unscoped_enum<void() & noexcept>();
    test_is_not_unscoped_enum<void() && noexcept>();
    test_is_not_unscoped_enum<void() const noexcept>();
    test_is_not_unscoped_enum<void() const & noexcept>();
    test_is_not_unscoped_enum<void() const && noexcept>();
    test_is_not_unscoped_enum<void() volatile noexcept>();
    test_is_not_unscoped_enum<void() volatile & noexcept>();
    test_is_not_unscoped_enum<void() volatile && noexcept>();
    test_is_not_unscoped_enum<void() const volatile noexcept>();
    test_is_not_unscoped_enum<void() const volatile & noexcept>();
    test_is_not_unscoped_enum<void() const volatile && noexcept>();

    test_is_not_unscoped_enum<void(int)>();
    test_is_not_unscoped_enum<void(int)&>();
    test_is_not_unscoped_enum<void(int) &&>();
    test_is_not_unscoped_enum<void(int) const>();
    test_is_not_unscoped_enum<void(int) const&>();
    test_is_not_unscoped_enum<void(int) const&&>();
    test_is_not_unscoped_enum<void(int) volatile>();
    test_is_not_unscoped_enum<void(int) volatile&>();
    test_is_not_unscoped_enum<void(int) volatile&&>();
    test_is_not_unscoped_enum<void(int) const volatile>();
    test_is_not_unscoped_enum<void(int) const volatile&>();
    test_is_not_unscoped_enum<void(int) const volatile&&>();
    test_is_not_unscoped_enum<void(int) noexcept>();
    test_is_not_unscoped_enum<void(int) & noexcept>();
    test_is_not_unscoped_enum<void(int) && noexcept>();
    test_is_not_unscoped_enum<void(int) const noexcept>();
    test_is_not_unscoped_enum<void(int) const & noexcept>();
    test_is_not_unscoped_enum<void(int) const && noexcept>();
    test_is_not_unscoped_enum<void(int) volatile noexcept>();
    test_is_not_unscoped_enum<void(int) volatile & noexcept>();
    test_is_not_unscoped_enum<void(int) volatile && noexcept>();
    test_is_not_unscoped_enum<void(int) const volatile noexcept>();
    test_is_not_unscoped_enum<void(int) const volatile & noexcept>();
    test_is_not_unscoped_enum<void(int) const volatile && noexcept>();

    test_is_not_unscoped_enum<void(...)>();
    test_is_not_unscoped_enum<void(...)&>();
    test_is_not_unscoped_enum<void(...) &&>();
    test_is_not_unscoped_enum<void(...) const>();
    test_is_not_unscoped_enum<void(...) const&>();
    test_is_not_unscoped_enum<void(...) const&&>();
    test_is_not_unscoped_enum<void(...) volatile>();
    test_is_not_unscoped_enum<void(...) volatile&>();
    test_is_not_unscoped_enum<void(...) volatile&&>();
    test_is_not_unscoped_enum<void(...) const volatile>();
    test_is_not_unscoped_enum<void(...) const volatile&>();
    test_is_not_unscoped_enum<void(...) const volatile&&>();
    test_is_not_unscoped_enum<void(...) noexcept>();
    test_is_not_unscoped_enum<void(...) & noexcept>();
    test_is_not_unscoped_enum<void(...) && noexcept>();
    test_is_not_unscoped_enum<void(...) const noexcept>();
    test_is_not_unscoped_enum<void(...) const & noexcept>();
    test_is_not_unscoped_enum<void(...) const && noexcept>();
    test_is_not_unscoped_enum<void(...) volatile noexcept>();
    test_is_not_unscoped_enum<void(...) volatile & noexcept>();
    test_is_not_unscoped_enum<void(...) volatile && noexcept>();
    test_is_not_unscoped_enum<void(...) const volatile noexcept>();
    test_is_not_unscoped_enum<void(...) const volatile & noexcept>();
    test_is_not_unscoped_enum<void(...) const volatile && noexcept>();

    test_is_not_unscoped_enum<void(int, ...)>();
    test_is_not_unscoped_enum<void(int, ...)&>();
    test_is_not_unscoped_enum<void(int, ...) &&>();
    test_is_not_unscoped_enum<void(int, ...) const>();
    test_is_not_unscoped_enum<void(int, ...) const&>();
    test_is_not_unscoped_enum<void(int, ...) const&&>();
    test_is_not_unscoped_enum<void(int, ...) volatile>();
    test_is_not_unscoped_enum<void(int, ...) volatile&>();
    test_is_not_unscoped_enum<void(int, ...) volatile&&>();
    test_is_not_unscoped_enum<void(int, ...) const volatile>();
    test_is_not_unscoped_enum<void(int, ...) const volatile&>();
    test_is_not_unscoped_enum<void(int, ...) const volatile&&>();
    test_is_not_unscoped_enum<void(int, ...) noexcept>();
    test_is_not_unscoped_enum<void(int, ...) & noexcept>();
    test_is_not_unscoped_enum<void(int, ...) && noexcept>();
    test_is_not_unscoped_enum<void(int, ...) const noexcept>();
    test_is_not_unscoped_enum<void(int, ...) const & noexcept>();
    test_is_not_unscoped_enum<void(int, ...) const && noexcept>();
    test_is_not_unscoped_enum<void(int, ...) volatile noexcept>();
    test_is_not_unscoped_enum<void(int, ...) volatile & noexcept>();
    test_is_not_unscoped_enum<void(int, ...) volatile && noexcept>();
    test_is_not_unscoped_enum<void(int, ...) const volatile noexcept>();
    test_is_not_unscoped_enum<void(int, ...) const volatile & noexcept>();
    test_is_not_unscoped_enum<void(int, ...) const volatile && noexcept>();

    test_is_not_unscoped_enum<int()>();
    test_is_not_unscoped_enum<int()&>();
    test_is_not_unscoped_enum<int() &&>();
    test_is_not_unscoped_enum<int() const>();
    test_is_not_unscoped_enum<int() const&>();
    test_is_not_unscoped_enum<int() const&&>();
    test_is_not_unscoped_enum<int() volatile>();
    test_is_not_unscoped_enum<int() volatile&>();
    test_is_not_unscoped_enum<int() volatile&&>();
    test_is_not_unscoped_enum<int() const volatile>();
    test_is_not_unscoped_enum<int() const volatile&>();
    test_is_not_unscoped_enum<int() const volatile&&>();
    test_is_not_unscoped_enum<int() noexcept>();
    test_is_not_unscoped_enum<int() & noexcept>();
    test_is_not_unscoped_enum<int() && noexcept>();
    test_is_not_unscoped_enum<int() const noexcept>();
    test_is_not_unscoped_enum<int() const & noexcept>();
    test_is_not_unscoped_enum<int() const && noexcept>();
    test_is_not_unscoped_enum<int() volatile noexcept>();
    test_is_not_unscoped_enum<int() volatile & noexcept>();
    test_is_not_unscoped_enum<int() volatile && noexcept>();
    test_is_not_unscoped_enum<int() const volatile noexcept>();
    test_is_not_unscoped_enum<int() const volatile & noexcept>();
    test_is_not_unscoped_enum<int() const volatile && noexcept>();

    test_is_not_unscoped_enum<int(int)>();
    test_is_not_unscoped_enum<int(int)&>();
    test_is_not_unscoped_enum<int(int) &&>();
    test_is_not_unscoped_enum<int(int) const>();
    test_is_not_unscoped_enum<int(int) const&>();
    test_is_not_unscoped_enum<int(int) const&&>();
    test_is_not_unscoped_enum<int(int) volatile>();
    test_is_not_unscoped_enum<int(int) volatile&>();
    test_is_not_unscoped_enum<int(int) volatile&&>();
    test_is_not_unscoped_enum<int(int) const volatile>();
    test_is_not_unscoped_enum<int(int) const volatile&>();
    test_is_not_unscoped_enum<int(int) const volatile&&>();
    test_is_not_unscoped_enum<int(int) noexcept>();
    test_is_not_unscoped_enum<int(int) & noexcept>();
    test_is_not_unscoped_enum<int(int) && noexcept>();
    test_is_not_unscoped_enum<int(int) const noexcept>();
    test_is_not_unscoped_enum<int(int) const & noexcept>();
    test_is_not_unscoped_enum<int(int) const && noexcept>();
    test_is_not_unscoped_enum<int(int) volatile noexcept>();
    test_is_not_unscoped_enum<int(int) volatile & noexcept>();
    test_is_not_unscoped_enum<int(int) volatile && noexcept>();
    test_is_not_unscoped_enum<int(int) const volatile noexcept>();
    test_is_not_unscoped_enum<int(int) const volatile & noexcept>();
    test_is_not_unscoped_enum<int(int) const volatile && noexcept>();

    test_is_not_unscoped_enum<int(...)>();
    test_is_not_unscoped_enum<int(...)&>();
    test_is_not_unscoped_enum<int(...) &&>();
    test_is_not_unscoped_enum<int(...) const>();
    test_is_not_unscoped_enum<int(...) const&>();
    test_is_not_unscoped_enum<int(...) const&&>();
    test_is_not_unscoped_enum<int(...) volatile>();
    test_is_not_unscoped_enum<int(...) volatile&>();
    test_is_not_unscoped_enum<int(...) volatile&&>();
    test_is_not_unscoped_enum<int(...) const volatile>();
    test_is_not_unscoped_enum<int(...) const volatile&>();
    test_is_not_unscoped_enum<int(...) const volatile&&>();
    test_is_not_unscoped_enum<int(...) noexcept>();
    test_is_not_unscoped_enum<int(...) & noexcept>();
    test_is_not_unscoped_enum<int(...) && noexcept>();
    test_is_not_unscoped_enum<int(...) const noexcept>();
    test_is_not_unscoped_enum<int(...) const & noexcept>();
    test_is_not_unscoped_enum<int(...) const && noexcept>();
    test_is_not_unscoped_enum<int(...) volatile noexcept>();
    test_is_not_unscoped_enum<int(...) volatile & noexcept>();
    test_is_not_unscoped_enum<int(...) volatile && noexcept>();
    test_is_not_unscoped_enum<int(...) const volatile noexcept>();
    test_is_not_unscoped_enum<int(...) const volatile & noexcept>();
    test_is_not_unscoped_enum<int(...) const volatile && noexcept>();

    test_is_not_unscoped_enum<int(int, ...)>();
    test_is_not_unscoped_enum<int(int, ...)&>();
    test_is_not_unscoped_enum<int(int, ...) &&>();
    test_is_not_unscoped_enum<int(int, ...) const>();
    test_is_not_unscoped_enum<int(int, ...) const&>();
    test_is_not_unscoped_enum<int(int, ...) const&&>();
    test_is_not_unscoped_enum<int(int, ...) volatile>();
    test_is_not_unscoped_enum<int(int, ...) volatile&>();
    test_is_not_unscoped_enum<int(int, ...) volatile&&>();
    test_is_not_unscoped_enum<int(int, ...) const volatile>();
    test_is_not_unscoped_enum<int(int, ...) const volatile&>();
    test_is_not_unscoped_enum<int(int, ...) const volatile&&>();
    test_is_not_unscoped_enum<int(int, ...) noexcept>();
    test_is_not_unscoped_enum<int(int, ...) & noexcept>();
    test_is_not_unscoped_enum<int(int, ...) && noexcept>();
    test_is_not_unscoped_enum<int(int, ...) const noexcept>();
    test_is_not_unscoped_enum<int(int, ...) const & noexcept>();
    test_is_not_unscoped_enum<int(int, ...) const && noexcept>();
    test_is_not_unscoped_enum<int(int, ...) volatile noexcept>();
    test_is_not_unscoped_enum<int(int, ...) volatile & noexcept>();
    test_is_not_unscoped_enum<int(int, ...) volatile && noexcept>();
    test_is_not_unscoped_enum<int(int, ...) const volatile noexcept>();
    test_is_not_unscoped_enum<int(int, ...) const volatile & noexcept>();
    test_is_not_unscoped_enum<int(int, ...) const volatile && noexcept>();

    test_is_not_unscoped_enum<void (*)()>();
    test_is_not_unscoped_enum<void (*)() noexcept>();

    test_is_not_unscoped_enum<void (*)(int)>();
    test_is_not_unscoped_enum<void (*)(int) noexcept>();

    test_is_not_unscoped_enum<void (*)(...)>();
    test_is_not_unscoped_enum<void (*)(...) noexcept>();

    test_is_not_unscoped_enum<void (*)(int, ...)>();
    test_is_not_unscoped_enum<void (*)(int, ...) noexcept>();

    test_is_not_unscoped_enum<int (*)()>();
    test_is_not_unscoped_enum<int (*)() noexcept>();

    test_is_not_unscoped_enum<int (*)(int)>();
    test_is_not_unscoped_enum<int (*)(int) noexcept>();

    test_is_not_unscoped_enum<int (*)(...)>();
    test_is_not_unscoped_enum<int (*)(...) noexcept>();

    test_is_not_unscoped_enum<int (*)(int, ...)>();
    test_is_not_unscoped_enum<int (*)(int, ...) noexcept>();

    test_is_not_unscoped_enum<void (&)()>();
    test_is_not_unscoped_enum<void (&)() noexcept>();

    test_is_not_unscoped_enum<void (&)(int)>();
    test_is_not_unscoped_enum<void (&)(int) noexcept>();

    test_is_not_unscoped_enum<void (&)(...)>();
    test_is_not_unscoped_enum<void (&)(...) noexcept>();

    test_is_not_unscoped_enum<void (&)(int, ...)>();
    test_is_not_unscoped_enum<void (&)(int, ...) noexcept>();

    test_is_not_unscoped_enum<int (&)()>();
    test_is_not_unscoped_enum<int (&)() noexcept>();

    test_is_not_unscoped_enum<int (&)(int)>();
    test_is_not_unscoped_enum<int (&)(int) noexcept>();

    test_is_not_unscoped_enum<int (&)(...)>();
    test_is_not_unscoped_enum<int (&)(...) noexcept>();

    test_is_not_unscoped_enum<int (&)(int, ...)>();
    test_is_not_unscoped_enum<int (&)(int, ...) noexcept>();

    test_is_not_unscoped_enum<void (&&)()>();
    test_is_not_unscoped_enum<void (&&)() noexcept>();

    test_is_not_unscoped_enum<void (&&)(int)>();
    test_is_not_unscoped_enum<void (&&)(int) noexcept>();

    test_is_not_unscoped_enum<void (&&)(...)>();
    test_is_not_unscoped_enum<void (&&)(...) noexcept>();

    test_is_not_unscoped_enum<void (&&)(int, ...)>();
    test_is_not_unscoped_enum<void (&&)(int, ...) noexcept>();

    test_is_not_unscoped_enum<int (&&)()>();
    test_is_not_unscoped_enum<int (&&)() noexcept>();

    test_is_not_unscoped_enum<int (&&)(int)>();
    test_is_not_unscoped_enum<int (&&)(int) noexcept>();

    test_is_not_unscoped_enum<int (&&)(...)>();
    test_is_not_unscoped_enum<int (&&)(...) noexcept>();

    test_is_not_unscoped_enum<int (&&)(int, ...)>();
    test_is_not_unscoped_enum<int (&&)(int, ...) noexcept>();

    test_is_not_unscoped_enum<void (class_type::*)()>();
    test_is_not_unscoped_enum<void (class_type::*)()&>();
    test_is_not_unscoped_enum<void (class_type::*)() &&>();
    test_is_not_unscoped_enum<void (class_type::*)() const>();
    test_is_not_unscoped_enum<void (class_type::*)() const&>();
    test_is_not_unscoped_enum<void (class_type::*)() const&&>();
    test_is_not_unscoped_enum<void (class_type::*)() noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)() & noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)() && noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)() const noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)() const & noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)() const && noexcept>();

    test_is_not_unscoped_enum<void (class_type::*)(int)>();
    test_is_not_unscoped_enum<void (class_type::*)(int)&>();
    test_is_not_unscoped_enum<void (class_type::*)(int) &&>();
    test_is_not_unscoped_enum<void (class_type::*)(int) const>();
    test_is_not_unscoped_enum<void (class_type::*)(int) const&>();
    test_is_not_unscoped_enum<void (class_type::*)(int) const&&>();
    test_is_not_unscoped_enum<void (class_type::*)(int) noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)(int) & noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)(int) && noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)(int) const noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)(int) const & noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)(int) const && noexcept>();

    test_is_not_unscoped_enum<void (class_type::*)(...)>();
    test_is_not_unscoped_enum<void (class_type::*)(...)&>();
    test_is_not_unscoped_enum<void (class_type::*)(...) &&>();
    test_is_not_unscoped_enum<void (class_type::*)(...) const>();
    test_is_not_unscoped_enum<void (class_type::*)(...) const&>();
    test_is_not_unscoped_enum<void (class_type::*)(...) const&&>();
    test_is_not_unscoped_enum<void (class_type::*)(...) noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)(...) & noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)(...) && noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)(...) const noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)(...) const & noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)(...) const && noexcept>();

    test_is_not_unscoped_enum<void (class_type::*)(int, ...)>();
    test_is_not_unscoped_enum<void (class_type::*)(int, ...)&>();
    test_is_not_unscoped_enum<void (class_type::*)(int, ...) &&>();
    test_is_not_unscoped_enum<void (class_type::*)(int, ...) const>();
    test_is_not_unscoped_enum<void (class_type::*)(int, ...) const&>();
    test_is_not_unscoped_enum<void (class_type::*)(int, ...) const&&>();
    test_is_not_unscoped_enum<void (class_type::*)(int, ...) noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_unscoped_enum<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_unscoped_enum<int (class_type::*)()>();
    test_is_not_unscoped_enum<int (class_type::*)()&>();
    test_is_not_unscoped_enum<int (class_type::*)() &&>();
    test_is_not_unscoped_enum<int (class_type::*)() const>();
    test_is_not_unscoped_enum<int (class_type::*)() const&>();
    test_is_not_unscoped_enum<int (class_type::*)() const&&>();
    test_is_not_unscoped_enum<int (class_type::*)() noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)() & noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)() && noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)() const noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)() const & noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)() const && noexcept>();

    test_is_not_unscoped_enum<int (class_type::*)(int)>();
    test_is_not_unscoped_enum<int (class_type::*)(int)&>();
    test_is_not_unscoped_enum<int (class_type::*)(int) &&>();
    test_is_not_unscoped_enum<int (class_type::*)(int) const>();
    test_is_not_unscoped_enum<int (class_type::*)(int) const&>();
    test_is_not_unscoped_enum<int (class_type::*)(int) const&&>();
    test_is_not_unscoped_enum<int (class_type::*)(int) noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)(int) & noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)(int) && noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)(int) const noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)(int) const & noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)(int) const && noexcept>();

    test_is_not_unscoped_enum<int (class_type::*)(...)>();
    test_is_not_unscoped_enum<int (class_type::*)(...)&>();
    test_is_not_unscoped_enum<int (class_type::*)(...) &&>();
    test_is_not_unscoped_enum<int (class_type::*)(...) const>();
    test_is_not_unscoped_enum<int (class_type::*)(...) const&>();
    test_is_not_unscoped_enum<int (class_type::*)(...) const&&>();
    test_is_not_unscoped_enum<int (class_type::*)(...) noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)(...) & noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)(...) && noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)(...) const noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)(...) const & noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)(...) const && noexcept>();

    test_is_not_unscoped_enum<int (class_type::*)(int, ...)>();
    test_is_not_unscoped_enum<int (class_type::*)(int, ...)&>();
    test_is_not_unscoped_enum<int (class_type::*)(int, ...) &&>();
    test_is_not_unscoped_enum<int (class_type::*)(int, ...) const>();
    test_is_not_unscoped_enum<int (class_type::*)(int, ...) const&>();
    test_is_not_unscoped_enum<int (class_type::*)(int, ...) const&&>();
    test_is_not_unscoped_enum<int (class_type::*)(int, ...) noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_unscoped_enum<int (class_type::*)(int, ...) const && noexcept>();
}
