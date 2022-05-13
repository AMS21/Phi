#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_arithmetic.hpp>
#include <phi/type_traits/is_array.hpp>
#include <phi/type_traits/is_bool.hpp>
#include <phi/type_traits/is_class.hpp>
#include <phi/type_traits/is_compound.hpp>
#include <phi/type_traits/is_enum.hpp>
#include <phi/type_traits/is_floating_point.hpp>
#include <phi/type_traits/is_function.hpp>
#include <phi/type_traits/is_fundamental.hpp>
#include <phi/type_traits/is_integer.hpp>
#include <phi/type_traits/is_integral.hpp>
#include <phi/type_traits/is_lvalue_reference.hpp>
#include <phi/type_traits/is_member_function_pointer.hpp>
#include <phi/type_traits/is_member_object_pointer.hpp>
#include <phi/type_traits/is_member_pointer.hpp>
#include <phi/type_traits/is_null_pointer.hpp>
#include <phi/type_traits/is_object.hpp>
#include <phi/type_traits/is_pointer.hpp>
#include <phi/type_traits/is_reference.hpp>
#include <phi/type_traits/is_rvalue_reference.hpp>
#include <phi/type_traits/is_scalar.hpp>
#include <phi/type_traits/is_union.hpp>
#include <phi/type_traits/is_void.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_enum_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_bool<T>::value);
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
#endif
    STATIC_REQUIRE(phi::is_compound<T>::value);
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE(phi::is_enum<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_floating_point<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_fundamental<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_integer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_integral<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer<T>::value);
#if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE(phi::is_object<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<T>::value);
#if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE(phi::is_scalar<T>::value);
#endif
#if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);

#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_not_enum<T>::value);
#endif

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_bool_v<T>);
#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
#    endif
    STATIC_REQUIRE(phi::is_compound_v<T>);
#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE(phi::is_enum_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_floating_point_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_fundamental_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_integer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_integral_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<T>);
#    if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE(phi::is_object_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<T>);
#    if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE(phi::is_scalar_v<T>);
#    endif
#    if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);

#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_not_enum_v<T>);
#    endif
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_enum<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_enum<T>);

    // Standard compatibility
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE(std::is_enum<T>::value);
#    if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(std::is_enum_v<T>);
#    endif
#endif
}

template <typename T>
void test_is_enum()
{
    test_is_enum_impl<T>();
    test_is_enum_impl<const T>();
    test_is_enum_impl<volatile T>();
    test_is_enum_impl<const volatile T>();
}

template <typename T>
void test_is_not_enum_impl()
{
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
    STATIC_REQUIRE(phi::is_not_enum<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
    STATIC_REQUIRE(phi::is_not_enum_v<T>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_enum<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_enum<T>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_enum<T>::value);
#    if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE_FALSE(std::is_enum_v<T>);
#    endif
#endif
}

template <typename T>
void test_is_not_enum()
{
    test_is_not_enum_impl<T>();
    test_is_not_enum_impl<const T>();
    test_is_not_enum_impl<volatile T>();
    test_is_not_enum_impl<const volatile T>();
}

TEST_CASE("is_enum")
{
    test_is_not_enum<void>();
    test_is_not_enum<phi::nullptr_t>();
    test_is_not_enum<bool>();
    test_is_not_enum<char>();
    test_is_not_enum<signed char>();
    test_is_not_enum<unsigned char>();
    test_is_not_enum<short>();
    test_is_not_enum<unsigned short>();
    test_is_not_enum<int>();
    test_is_not_enum<unsigned int>();
    test_is_not_enum<long>();
    test_is_not_enum<unsigned long>();
    test_is_not_enum<long long>();
    test_is_not_enum<unsigned long long>();
    test_is_not_enum<float>();
    test_is_not_enum<double>();
    test_is_not_enum<long double>();
    test_is_not_enum<char8_t>();
    test_is_not_enum<char16_t>();
    test_is_not_enum<char32_t>();
    test_is_not_enum<wchar_t>();

    test_is_not_enum<phi::boolean>();
    test_is_not_enum<phi::integer<signed char>>();
    test_is_not_enum<phi::integer<unsigned char>>();
    test_is_not_enum<phi::integer<short>>();
    test_is_not_enum<phi::integer<unsigned short>>();
    test_is_not_enum<phi::integer<int>>();
    test_is_not_enum<phi::integer<unsigned int>>();
    test_is_not_enum<phi::integer<long>>();
    test_is_not_enum<phi::integer<unsigned long>>();
    test_is_not_enum<phi::integer<long long>>();
    test_is_not_enum<phi::integer<unsigned long long>>();
    test_is_not_enum<phi::floating_point<float>>();
    test_is_not_enum<phi::floating_point<double>>();
    test_is_not_enum<phi::floating_point<long double>>();

    test_is_not_enum<std::vector<int>>();
    test_is_not_enum<phi::scope_ptr<int>>();

    test_is_not_enum<int&>();
    test_is_not_enum<const int&>();
    test_is_not_enum<volatile int&>();
    test_is_not_enum<const volatile int&>();
    test_is_not_enum<int&&>();
    test_is_not_enum<const int&&>();
    test_is_not_enum<volatile int&&>();
    test_is_not_enum<const volatile int&&>();
    test_is_not_enum<int*>();
    test_is_not_enum<const int*>();
    test_is_not_enum<volatile int*>();
    test_is_not_enum<const volatile int*>();
    test_is_not_enum<int**>();
    test_is_not_enum<const int**>();
    test_is_not_enum<volatile int**>();
    test_is_not_enum<const volatile int**>();
    test_is_not_enum<int*&>();
    test_is_not_enum<const int*&>();
    test_is_not_enum<volatile int*&>();
    test_is_not_enum<const volatile int*&>();
    test_is_not_enum<int*&&>();
    test_is_not_enum<const int*&&>();
    test_is_not_enum<volatile int*&&>();
    test_is_not_enum<const volatile int*&&>();
    test_is_not_enum<void*>();
    test_is_not_enum<char[3]>();
    test_is_not_enum<char[]>();
    test_is_not_enum<char* [3]>();
    test_is_not_enum<char*[]>();
    test_is_not_enum<int(*)[3]>();
    test_is_not_enum<int(*)[]>();
    test_is_not_enum<int(&)[3]>();
    test_is_not_enum<int(&)[]>();
    test_is_not_enum<int(&&)[3]>();
    test_is_not_enum<int(&&)[]>();
    test_is_not_enum<char[3][2]>();
    test_is_not_enum<char[][2]>();
    test_is_not_enum<char* [3][2]>();
    test_is_not_enum<char*[][2]>();
    test_is_not_enum<int(*)[3][2]>();
    test_is_not_enum<int(*)[][2]>();
    test_is_not_enum<int(&)[3][2]>();
    test_is_not_enum<int(&)[][2]>();
    test_is_not_enum<int(&&)[3][2]>();
    test_is_not_enum<int(&&)[][2]>();
    test_is_not_enum<class_type>();
    test_is_not_enum<class_type[]>();
    test_is_not_enum<class_type[2]>();
    test_is_not_enum<template_type<void>>();
    test_is_not_enum<template_type<int>>();
    test_is_not_enum<template_type<class_type>>();
    test_is_not_enum<template_type<incomplete_type>>();
    test_is_not_enum<variadic_template<>>();
    test_is_not_enum<variadic_template<void>>();
    test_is_not_enum<variadic_template<int>>();
    test_is_not_enum<variadic_template<class_type>>();
    test_is_not_enum<variadic_template<incomplete_type>>();
    test_is_not_enum<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_enum<public_derived_from<base>>();
    test_is_not_enum<public_derived_from<derived>>();
    test_is_not_enum<public_derived_from<class_type>>();
    test_is_not_enum<private_derived_from<base>>();
    test_is_not_enum<private_derived_from<derived>>();
    test_is_not_enum<private_derived_from<class_type>>();
    test_is_not_enum<protected_derived_from<base>>();
    test_is_not_enum<protected_derived_from<derived>>();
    test_is_not_enum<protected_derived_from<class_type>>();
    test_is_not_enum<union_type>();
    test_is_not_enum<non_empty_union>();
    test_is_not_enum<empty>();
    test_is_not_enum<not_empty>();
    test_is_not_enum<bit_zero>();
    test_is_not_enum<bit_one>();
    test_is_not_enum<base>();
    test_is_not_enum<derived>();
    test_is_not_enum<abstract>();
    test_is_not_enum<public_abstract>();
    test_is_not_enum<private_abstract>();
    test_is_not_enum<protected_abstract>();
    test_is_not_enum<abstract_template<int>>();
    test_is_not_enum<abstract_template<double>>();
    test_is_not_enum<abstract_template<class_type>>();
    test_is_not_enum<abstract_template<incomplete_type>>();
    test_is_not_enum<final_type>();
    test_is_not_enum<public_destructor>();
    test_is_not_enum<protected_destructor>();
    test_is_not_enum<private_destructor>();
    test_is_not_enum<virtual_public_destructor>();
    test_is_not_enum<virtual_protected_destructor>();
    test_is_not_enum<virtual_private_destructor>();
    test_is_not_enum<pure_public_destructor>();
    test_is_not_enum<pure_protected_destructor>();
    test_is_not_enum<pure_private_destructor>();
    test_is_not_enum<deleted_public_destructor>();
    test_is_not_enum<deleted_protected_destructor>();
    test_is_not_enum<deleted_private_destructor>();
    test_is_not_enum<deleted_virtual_public_destructor>();
    test_is_not_enum<deleted_virtual_protected_destructor>();
    test_is_not_enum<deleted_virtual_private_destructor>();
    test_is_not_enum<final_type>();
    test_is_enum<enum_type>();
    test_is_enum<enum_signed>();
    test_is_enum<enum_unsigned>();
    test_is_enum<enum_class>();
    test_is_enum<enum_struct>();
    test_is_not_enum<function_type>();
    test_is_not_enum<function_ptr>();
    test_is_not_enum<member_object_ptr>();
    test_is_not_enum<member_function_ptr>();
    test_is_not_enum<incomplete_type>();
    test_is_not_enum<incomplete_template<void>>();
    test_is_not_enum<incomplete_template<int>>();
    test_is_not_enum<incomplete_template<class_type>>();
    test_is_not_enum<incomplete_template<incomplete_type>>();
    test_is_not_enum<IncompleteVariadicTemplate<>>();
    test_is_not_enum<IncompleteVariadicTemplate<void>>();
    test_is_not_enum<IncompleteVariadicTemplate<int>>();
    test_is_not_enum<IncompleteVariadicTemplate<class_type>>();
    test_is_not_enum<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_not_enum<IncompleteVariadicTemplate<int, void, class_type, volatile char[]>>();
    test_is_not_enum<int class_type::*>();
    test_is_not_enum<float class_type::*>();
    test_is_not_enum<void * class_type::*>();
    test_is_not_enum<int * class_type::*>();
    test_is_not_enum<int class_type::*&>();
    test_is_not_enum<float class_type::*&>();
    test_is_not_enum<void * class_type::*&>();
    test_is_not_enum<int * class_type::*&>();
    test_is_not_enum<int class_type::*&&>();
    test_is_not_enum<float class_type::*&&>();
    test_is_not_enum<void * class_type::*&&>();
    test_is_not_enum<int * class_type::*&&>();
    test_is_not_enum<int class_type::*const>();
    test_is_not_enum<float class_type::*const>();
    test_is_not_enum<void * class_type::*const>();
    test_is_not_enum<int class_type::*const&>();
    test_is_not_enum<float class_type::*const&>();
    test_is_not_enum<void * class_type::*const&>();
    test_is_not_enum<int class_type::*const&&>();
    test_is_not_enum<float class_type::*const&&>();
    test_is_not_enum<void * class_type::*const&&>();
    test_is_not_enum<int class_type::*volatile>();
    test_is_not_enum<float class_type::*volatile>();
    test_is_not_enum<void * class_type::*volatile>();
    test_is_not_enum<int class_type::*volatile&>();
    test_is_not_enum<float class_type::*volatile&>();
    test_is_not_enum<void * class_type::*volatile&>();
    test_is_not_enum<int class_type::*volatile&&>();
    test_is_not_enum<float class_type::*volatile&&>();
    test_is_not_enum<void * class_type::*volatile&&>();
    test_is_not_enum<int class_type::*const volatile>();
    test_is_not_enum<float class_type::*const volatile>();
    test_is_not_enum<void * class_type::*const volatile>();
    test_is_not_enum<int class_type::*const volatile&>();
    test_is_not_enum<float class_type::*const volatile&>();
    test_is_not_enum<void * class_type::*const volatile&>();
    test_is_not_enum<int class_type::*const volatile&&>();
    test_is_not_enum<float class_type::*const volatile&&>();
    test_is_not_enum<void * class_type::*const volatile&&>();
    test_is_not_enum<non_copyable>();
    test_is_not_enum<non_moveable>();
    test_is_not_enum<non_constructible>();
    test_is_not_enum<tracked>();
    test_is_not_enum<trap_constructible>();
    test_is_not_enum<trap_implicit_conversion>();
    test_is_not_enum<trap_comma>();
    test_is_not_enum<trap_call>();
    test_is_not_enum<trap_self_assign>();
    test_is_not_enum<trap_deref>();
    test_is_not_enum<trap_array_subscript>();

    test_is_not_enum<void()>();
    test_is_not_enum<void()&>();
    test_is_not_enum<void() &&>();
    test_is_not_enum<void() const>();
    test_is_not_enum<void() const&>();
    test_is_not_enum<void() const&&>();
    test_is_not_enum<void() volatile>();
    test_is_not_enum<void() volatile&>();
    test_is_not_enum<void() volatile&&>();
    test_is_not_enum<void() const volatile>();
    test_is_not_enum<void() const volatile&>();
    test_is_not_enum<void() const volatile&&>();
    test_is_not_enum<void() noexcept>();
    test_is_not_enum<void()& noexcept>();
    test_is_not_enum<void()&& noexcept>();
    test_is_not_enum<void() const noexcept>();
    test_is_not_enum<void() const& noexcept>();
    test_is_not_enum<void() const&& noexcept>();
    test_is_not_enum<void() volatile noexcept>();
    test_is_not_enum<void() volatile& noexcept>();
    test_is_not_enum<void() volatile&& noexcept>();
    test_is_not_enum<void() const volatile noexcept>();
    test_is_not_enum<void() const volatile& noexcept>();
    test_is_not_enum<void() const volatile&& noexcept>();

    test_is_not_enum<void(int)>();
    test_is_not_enum<void(int)&>();
    test_is_not_enum<void(int) &&>();
    test_is_not_enum<void(int) const>();
    test_is_not_enum<void(int) const&>();
    test_is_not_enum<void(int) const&&>();
    test_is_not_enum<void(int) volatile>();
    test_is_not_enum<void(int) volatile&>();
    test_is_not_enum<void(int) volatile&&>();
    test_is_not_enum<void(int) const volatile>();
    test_is_not_enum<void(int) const volatile&>();
    test_is_not_enum<void(int) const volatile&&>();
    test_is_not_enum<void(int) noexcept>();
    test_is_not_enum<void(int)& noexcept>();
    test_is_not_enum<void(int)&& noexcept>();
    test_is_not_enum<void(int) const noexcept>();
    test_is_not_enum<void(int) const& noexcept>();
    test_is_not_enum<void(int) const&& noexcept>();
    test_is_not_enum<void(int) volatile noexcept>();
    test_is_not_enum<void(int) volatile& noexcept>();
    test_is_not_enum<void(int) volatile&& noexcept>();
    test_is_not_enum<void(int) const volatile noexcept>();
    test_is_not_enum<void(int) const volatile& noexcept>();
    test_is_not_enum<void(int) const volatile&& noexcept>();

    test_is_not_enum<void(...)>();
    test_is_not_enum<void(...)&>();
    test_is_not_enum<void(...) &&>();
    test_is_not_enum<void(...) const>();
    test_is_not_enum<void(...) const&>();
    test_is_not_enum<void(...) const&&>();
    test_is_not_enum<void(...) volatile>();
    test_is_not_enum<void(...) volatile&>();
    test_is_not_enum<void(...) volatile&&>();
    test_is_not_enum<void(...) const volatile>();
    test_is_not_enum<void(...) const volatile&>();
    test_is_not_enum<void(...) const volatile&&>();
    test_is_not_enum<void(...) noexcept>();
    test_is_not_enum<void(...)& noexcept>();
    test_is_not_enum<void(...)&& noexcept>();
    test_is_not_enum<void(...) const noexcept>();
    test_is_not_enum<void(...) const& noexcept>();
    test_is_not_enum<void(...) const&& noexcept>();
    test_is_not_enum<void(...) volatile noexcept>();
    test_is_not_enum<void(...) volatile& noexcept>();
    test_is_not_enum<void(...) volatile&& noexcept>();
    test_is_not_enum<void(...) const volatile noexcept>();
    test_is_not_enum<void(...) const volatile& noexcept>();
    test_is_not_enum<void(...) const volatile&& noexcept>();

    test_is_not_enum<void(int, ...)>();
    test_is_not_enum<void(int, ...)&>();
    test_is_not_enum<void(int, ...) &&>();
    test_is_not_enum<void(int, ...) const>();
    test_is_not_enum<void(int, ...) const&>();
    test_is_not_enum<void(int, ...) const&&>();
    test_is_not_enum<void(int, ...) volatile>();
    test_is_not_enum<void(int, ...) volatile&>();
    test_is_not_enum<void(int, ...) volatile&&>();
    test_is_not_enum<void(int, ...) const volatile>();
    test_is_not_enum<void(int, ...) const volatile&>();
    test_is_not_enum<void(int, ...) const volatile&&>();
    test_is_not_enum<void(int, ...) noexcept>();
    test_is_not_enum<void(int, ...)& noexcept>();
    test_is_not_enum<void(int, ...)&& noexcept>();
    test_is_not_enum<void(int, ...) const noexcept>();
    test_is_not_enum<void(int, ...) const& noexcept>();
    test_is_not_enum<void(int, ...) const&& noexcept>();
    test_is_not_enum<void(int, ...) volatile noexcept>();
    test_is_not_enum<void(int, ...) volatile& noexcept>();
    test_is_not_enum<void(int, ...) volatile&& noexcept>();
    test_is_not_enum<void(int, ...) const volatile noexcept>();
    test_is_not_enum<void(int, ...) const volatile& noexcept>();
    test_is_not_enum<void(int, ...) const volatile&& noexcept>();

    test_is_not_enum<int()>();
    test_is_not_enum<int()&>();
    test_is_not_enum<int() &&>();
    test_is_not_enum<int() const>();
    test_is_not_enum<int() const&>();
    test_is_not_enum<int() const&&>();
    test_is_not_enum<int() volatile>();
    test_is_not_enum<int() volatile&>();
    test_is_not_enum<int() volatile&&>();
    test_is_not_enum<int() const volatile>();
    test_is_not_enum<int() const volatile&>();
    test_is_not_enum<int() const volatile&&>();
    test_is_not_enum<int() noexcept>();
    test_is_not_enum<int()& noexcept>();
    test_is_not_enum<int()&& noexcept>();
    test_is_not_enum<int() const noexcept>();
    test_is_not_enum<int() const& noexcept>();
    test_is_not_enum<int() const&& noexcept>();
    test_is_not_enum<int() volatile noexcept>();
    test_is_not_enum<int() volatile& noexcept>();
    test_is_not_enum<int() volatile&& noexcept>();
    test_is_not_enum<int() const volatile noexcept>();
    test_is_not_enum<int() const volatile& noexcept>();
    test_is_not_enum<int() const volatile&& noexcept>();

    test_is_not_enum<int(int)>();
    test_is_not_enum<int(int)&>();
    test_is_not_enum<int(int) &&>();
    test_is_not_enum<int(int) const>();
    test_is_not_enum<int(int) const&>();
    test_is_not_enum<int(int) const&&>();
    test_is_not_enum<int(int) volatile>();
    test_is_not_enum<int(int) volatile&>();
    test_is_not_enum<int(int) volatile&&>();
    test_is_not_enum<int(int) const volatile>();
    test_is_not_enum<int(int) const volatile&>();
    test_is_not_enum<int(int) const volatile&&>();
    test_is_not_enum<int(int) noexcept>();
    test_is_not_enum<int(int)& noexcept>();
    test_is_not_enum<int(int)&& noexcept>();
    test_is_not_enum<int(int) const noexcept>();
    test_is_not_enum<int(int) const& noexcept>();
    test_is_not_enum<int(int) const&& noexcept>();
    test_is_not_enum<int(int) volatile noexcept>();
    test_is_not_enum<int(int) volatile& noexcept>();
    test_is_not_enum<int(int) volatile&& noexcept>();
    test_is_not_enum<int(int) const volatile noexcept>();
    test_is_not_enum<int(int) const volatile& noexcept>();
    test_is_not_enum<int(int) const volatile&& noexcept>();

    test_is_not_enum<int(...)>();
    test_is_not_enum<int(...)&>();
    test_is_not_enum<int(...) &&>();
    test_is_not_enum<int(...) const>();
    test_is_not_enum<int(...) const&>();
    test_is_not_enum<int(...) const&&>();
    test_is_not_enum<int(...) volatile>();
    test_is_not_enum<int(...) volatile&>();
    test_is_not_enum<int(...) volatile&&>();
    test_is_not_enum<int(...) const volatile>();
    test_is_not_enum<int(...) const volatile&>();
    test_is_not_enum<int(...) const volatile&&>();
    test_is_not_enum<int(...) noexcept>();
    test_is_not_enum<int(...)& noexcept>();
    test_is_not_enum<int(...)&& noexcept>();
    test_is_not_enum<int(...) const noexcept>();
    test_is_not_enum<int(...) const& noexcept>();
    test_is_not_enum<int(...) const&& noexcept>();
    test_is_not_enum<int(...) volatile noexcept>();
    test_is_not_enum<int(...) volatile& noexcept>();
    test_is_not_enum<int(...) volatile&& noexcept>();
    test_is_not_enum<int(...) const volatile noexcept>();
    test_is_not_enum<int(...) const volatile& noexcept>();
    test_is_not_enum<int(...) const volatile&& noexcept>();

    test_is_not_enum<int(int, ...)>();
    test_is_not_enum<int(int, ...)&>();
    test_is_not_enum<int(int, ...) &&>();
    test_is_not_enum<int(int, ...) const>();
    test_is_not_enum<int(int, ...) const&>();
    test_is_not_enum<int(int, ...) const&&>();
    test_is_not_enum<int(int, ...) volatile>();
    test_is_not_enum<int(int, ...) volatile&>();
    test_is_not_enum<int(int, ...) volatile&&>();
    test_is_not_enum<int(int, ...) const volatile>();
    test_is_not_enum<int(int, ...) const volatile&>();
    test_is_not_enum<int(int, ...) const volatile&&>();
    test_is_not_enum<int(int, ...) noexcept>();
    test_is_not_enum<int(int, ...)& noexcept>();
    test_is_not_enum<int(int, ...)&& noexcept>();
    test_is_not_enum<int(int, ...) const noexcept>();
    test_is_not_enum<int(int, ...) const& noexcept>();
    test_is_not_enum<int(int, ...) const&& noexcept>();
    test_is_not_enum<int(int, ...) volatile noexcept>();
    test_is_not_enum<int(int, ...) volatile& noexcept>();
    test_is_not_enum<int(int, ...) volatile&& noexcept>();
    test_is_not_enum<int(int, ...) const volatile noexcept>();
    test_is_not_enum<int(int, ...) const volatile& noexcept>();
    test_is_not_enum<int(int, ...) const volatile&& noexcept>();

    test_is_not_enum<void (*)()>();
    test_is_not_enum<void (*)() noexcept>();

    test_is_not_enum<void (*)(int)>();
    test_is_not_enum<void (*)(int) noexcept>();

    test_is_not_enum<void (*)(...)>();
    test_is_not_enum<void (*)(...) noexcept>();

    test_is_not_enum<void (*)(int, ...)>();
    test_is_not_enum<void (*)(int, ...) noexcept>();

    test_is_not_enum<int (*)()>();
    test_is_not_enum<int (*)() noexcept>();

    test_is_not_enum<int (*)(int)>();
    test_is_not_enum<int (*)(int) noexcept>();

    test_is_not_enum<int (*)(...)>();
    test_is_not_enum<int (*)(...) noexcept>();

    test_is_not_enum<int (*)(int, ...)>();
    test_is_not_enum<int (*)(int, ...) noexcept>();

    test_is_not_enum<void (&)()>();
    test_is_not_enum<void (&)() noexcept>();

    test_is_not_enum<void (&)(int)>();
    test_is_not_enum<void (&)(int) noexcept>();

    test_is_not_enum<void (&)(...)>();
    test_is_not_enum<void (&)(...) noexcept>();

    test_is_not_enum<void (&)(int, ...)>();
    test_is_not_enum<void (&)(int, ...) noexcept>();

    test_is_not_enum<int (&)()>();
    test_is_not_enum<int (&)() noexcept>();

    test_is_not_enum<int (&)(int)>();
    test_is_not_enum<int (&)(int) noexcept>();

    test_is_not_enum<int (&)(...)>();
    test_is_not_enum<int (&)(...) noexcept>();

    test_is_not_enum<int (&)(int, ...)>();
    test_is_not_enum<int (&)(int, ...) noexcept>();

    test_is_not_enum<void(&&)()>();
    test_is_not_enum<void(&&)() noexcept>();

    test_is_not_enum<void(&&)(int)>();
    test_is_not_enum<void(&&)(int) noexcept>();

    test_is_not_enum<void(&&)(...)>();
    test_is_not_enum<void(&&)(...) noexcept>();

    test_is_not_enum<void(&&)(int, ...)>();
    test_is_not_enum<void(&&)(int, ...) noexcept>();

    test_is_not_enum<int(&&)()>();
    test_is_not_enum<int(&&)() noexcept>();

    test_is_not_enum<int(&&)(int)>();
    test_is_not_enum<int(&&)(int) noexcept>();

    test_is_not_enum<int(&&)(...)>();
    test_is_not_enum<int(&&)(...) noexcept>();

    test_is_not_enum<int(&&)(int, ...)>();
    test_is_not_enum<int(&&)(int, ...) noexcept>();

    test_is_not_enum<void (class_type::*)()>();
    test_is_not_enum<void (class_type::*)()&>();
    test_is_not_enum<void (class_type::*)() &&>();
    test_is_not_enum<void (class_type::*)() const>();
    test_is_not_enum<void (class_type::*)() const&>();
    test_is_not_enum<void (class_type::*)() const&&>();
    test_is_not_enum<void (class_type::*)() noexcept>();
    test_is_not_enum<void (class_type::*)()& noexcept>();
    test_is_not_enum<void (class_type::*)()&& noexcept>();
    test_is_not_enum<void (class_type::*)() const noexcept>();
    test_is_not_enum<void (class_type::*)() const& noexcept>();
    test_is_not_enum<void (class_type::*)() const&& noexcept>();

    test_is_not_enum<void (class_type::*)(int)>();
    test_is_not_enum<void (class_type::*)(int)&>();
    test_is_not_enum<void (class_type::*)(int) &&>();
    test_is_not_enum<void (class_type::*)(int) const>();
    test_is_not_enum<void (class_type::*)(int) const&>();
    test_is_not_enum<void (class_type::*)(int) const&&>();
    test_is_not_enum<void (class_type::*)(int) noexcept>();
    test_is_not_enum<void (class_type::*)(int)& noexcept>();
    test_is_not_enum<void (class_type::*)(int)&& noexcept>();
    test_is_not_enum<void (class_type::*)(int) const noexcept>();
    test_is_not_enum<void (class_type::*)(int) const& noexcept>();
    test_is_not_enum<void (class_type::*)(int) const&& noexcept>();

    test_is_not_enum<void (class_type::*)(...)>();
    test_is_not_enum<void (class_type::*)(...)&>();
    test_is_not_enum<void (class_type::*)(...) &&>();
    test_is_not_enum<void (class_type::*)(...) const>();
    test_is_not_enum<void (class_type::*)(...) const&>();
    test_is_not_enum<void (class_type::*)(...) const&&>();
    test_is_not_enum<void (class_type::*)(...) noexcept>();
    test_is_not_enum<void (class_type::*)(...)& noexcept>();
    test_is_not_enum<void (class_type::*)(...)&& noexcept>();
    test_is_not_enum<void (class_type::*)(...) const noexcept>();
    test_is_not_enum<void (class_type::*)(...) const& noexcept>();
    test_is_not_enum<void (class_type::*)(...) const&& noexcept>();

    test_is_not_enum<void (class_type::*)(int, ...)>();
    test_is_not_enum<void (class_type::*)(int, ...)&>();
    test_is_not_enum<void (class_type::*)(int, ...) &&>();
    test_is_not_enum<void (class_type::*)(int, ...) const>();
    test_is_not_enum<void (class_type::*)(int, ...) const&>();
    test_is_not_enum<void (class_type::*)(int, ...) const&&>();
    test_is_not_enum<void (class_type::*)(int, ...) noexcept>();
    test_is_not_enum<void (class_type::*)(int, ...)& noexcept>();
    test_is_not_enum<void (class_type::*)(int, ...)&& noexcept>();
    test_is_not_enum<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_enum<void (class_type::*)(int, ...) const& noexcept>();
    test_is_not_enum<void (class_type::*)(int, ...) const&& noexcept>();

    test_is_not_enum<int (class_type::*)()>();
    test_is_not_enum<int (class_type::*)()&>();
    test_is_not_enum<int (class_type::*)() &&>();
    test_is_not_enum<int (class_type::*)() const>();
    test_is_not_enum<int (class_type::*)() const&>();
    test_is_not_enum<int (class_type::*)() const&&>();
    test_is_not_enum<int (class_type::*)() noexcept>();
    test_is_not_enum<int (class_type::*)()& noexcept>();
    test_is_not_enum<int (class_type::*)()&& noexcept>();
    test_is_not_enum<int (class_type::*)() const noexcept>();
    test_is_not_enum<int (class_type::*)() const& noexcept>();
    test_is_not_enum<int (class_type::*)() const&& noexcept>();

    test_is_not_enum<int (class_type::*)(int)>();
    test_is_not_enum<int (class_type::*)(int)&>();
    test_is_not_enum<int (class_type::*)(int) &&>();
    test_is_not_enum<int (class_type::*)(int) const>();
    test_is_not_enum<int (class_type::*)(int) const&>();
    test_is_not_enum<int (class_type::*)(int) const&&>();
    test_is_not_enum<int (class_type::*)(int) noexcept>();
    test_is_not_enum<int (class_type::*)(int)& noexcept>();
    test_is_not_enum<int (class_type::*)(int)&& noexcept>();
    test_is_not_enum<int (class_type::*)(int) const noexcept>();
    test_is_not_enum<int (class_type::*)(int) const& noexcept>();
    test_is_not_enum<int (class_type::*)(int) const&& noexcept>();

    test_is_not_enum<int (class_type::*)(...)>();
    test_is_not_enum<int (class_type::*)(...)&>();
    test_is_not_enum<int (class_type::*)(...) &&>();
    test_is_not_enum<int (class_type::*)(...) const>();
    test_is_not_enum<int (class_type::*)(...) const&>();
    test_is_not_enum<int (class_type::*)(...) const&&>();
    test_is_not_enum<int (class_type::*)(...) noexcept>();
    test_is_not_enum<int (class_type::*)(...)& noexcept>();
    test_is_not_enum<int (class_type::*)(...)&& noexcept>();
    test_is_not_enum<int (class_type::*)(...) const noexcept>();
    test_is_not_enum<int (class_type::*)(...) const& noexcept>();
    test_is_not_enum<int (class_type::*)(...) const&& noexcept>();

    test_is_not_enum<int (class_type::*)(int, ...)>();
    test_is_not_enum<int (class_type::*)(int, ...)&>();
    test_is_not_enum<int (class_type::*)(int, ...) &&>();
    test_is_not_enum<int (class_type::*)(int, ...) const>();
    test_is_not_enum<int (class_type::*)(int, ...) const&>();
    test_is_not_enum<int (class_type::*)(int, ...) const&&>();
    test_is_not_enum<int (class_type::*)(int, ...) noexcept>();
    test_is_not_enum<int (class_type::*)(int, ...)& noexcept>();
    test_is_not_enum<int (class_type::*)(int, ...)&& noexcept>();
    test_is_not_enum<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_enum<int (class_type::*)(int, ...) const& noexcept>();
    test_is_not_enum<int (class_type::*)(int, ...) const&& noexcept>();
}
