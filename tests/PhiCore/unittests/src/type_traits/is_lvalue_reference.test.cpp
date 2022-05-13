#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/add_lvalue_reference.hpp>
#include <phi/type_traits/add_rvalue_reference.hpp>
#include <phi/type_traits/is_arithmetic.hpp>
#include <phi/type_traits/is_array.hpp>
#include <phi/type_traits/is_bool.hpp>
#include <phi/type_traits/is_class.hpp>
#include <phi/type_traits/is_compound.hpp>
#include <phi/type_traits/is_enum.hpp>
#include <phi/type_traits/is_floating_point.hpp>
#include <phi/type_traits/is_function.hpp>
#include <phi/type_traits/is_integer.hpp>
#include <phi/type_traits/is_lvalue_reference.hpp>
#include <phi/type_traits/is_member_function_pointer.hpp>
#include <phi/type_traits/is_member_object_pointer.hpp>
#include <phi/type_traits/is_member_pointer.hpp>
#include <phi/type_traits/is_null_pointer.hpp>
#include <phi/type_traits/is_object.hpp>
#include <phi/type_traits/is_pointer.hpp>
#include <phi/type_traits/is_reference.hpp>
#include <phi/type_traits/is_referenceable.hpp>
#include <phi/type_traits/is_rvalue_reference.hpp>
#include <phi/type_traits/is_scalar.hpp>
#include <phi/type_traits/is_union.hpp>
#include <phi/type_traits/is_void.hpp>
#include <phi/type_traits/remove_reference.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_lvalue_reference_impl()
{
    // is_lvalue
    STATIC_REQUIRE(phi::is_lvalue_reference<T>::value);
    STATIC_REQUIRE(phi::is_lvalue_reference<typename phi::add_lvalue_reference<T>::type>::value);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<typename phi::remove_reference<T>::type>::value);
    STATIC_REQUIRE(phi::is_lvalue_reference<typename phi::add_rvalue_reference<T>::type>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_lvalue_reference<T>::value);
    STATIC_REQUIRE_FALSE(
            phi::is_not_lvalue_reference<typename phi::add_lvalue_reference<T>::type>::value);
    STATIC_REQUIRE(phi::is_not_lvalue_reference<typename phi::remove_reference<T>::type>::value);
    STATIC_REQUIRE_FALSE(
            phi::is_not_lvalue_reference<typename phi::add_rvalue_reference<T>::type>::value);

    STATIC_REQUIRE_FALSE(phi::is_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_bool<T>::value);
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
#endif
    STATIC_REQUIRE(phi::is_compound<T>::value);
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_floating_point<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_integer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_integral<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer<T>::value);
#if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE_FALSE(phi::is_object<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_pointer<T>::value);
    STATIC_REQUIRE(phi::is_reference<T>::value);
    STATIC_REQUIRE(phi::is_referenceable<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<T>::value);
#if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE_FALSE(phi::is_scalar<T>::value);
#endif
#if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    // is_lvalue_v
    STATIC_REQUIRE(phi::is_lvalue_reference_v<T>);
    STATIC_REQUIRE(phi::is_lvalue_reference_v<typename phi::add_lvalue_reference<T>::type>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<typename phi::remove_reference<T>::type>);
    STATIC_REQUIRE(phi::is_lvalue_reference_v<typename phi::add_rvalue_reference<T>::type>);

    STATIC_REQUIRE_FALSE(phi::is_not_lvalue_reference_v<T>);
    STATIC_REQUIRE_FALSE(
            phi::is_not_lvalue_reference_v<typename phi::add_lvalue_reference<T>::type>);
    STATIC_REQUIRE(phi::is_not_lvalue_reference_v<typename phi::remove_reference<T>::type>);
    STATIC_REQUIRE_FALSE(
            phi::is_not_lvalue_reference_v<typename phi::add_rvalue_reference<T>::type>);

    STATIC_REQUIRE_FALSE(phi::is_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_bool_v<T>);
#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
#    endif
    STATIC_REQUIRE(phi::is_compound_v<T>);
#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_floating_point_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_integer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_integral_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<T>);
#    if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE_FALSE(phi::is_object_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_pointer_v<T>);
    STATIC_REQUIRE(phi::is_reference_v<T>);
    STATIC_REQUIRE(phi::is_referenceable_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<T>);
#    if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE_FALSE(phi::is_scalar_v<T>);
#    endif
#    if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_unsafe_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_lvalue_reference<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_lvalue_reference<T>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_lvalue_reference<T>::value);
}

template <typename T>
void test_is_lvalue_reference()
{
    test_is_lvalue_reference_impl<T>();
    test_is_lvalue_reference_impl<const T>();
    test_is_lvalue_reference_impl<volatile T>();
    test_is_lvalue_reference_impl<const volatile T>();
}

template <typename T>
void test_is_not_lvalue_reference_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<T>::value);
    STATIC_REQUIRE(phi::is_not_referenceable<T>::value ||
                   phi::is_lvalue_reference<typename phi::add_lvalue_reference<T>::type>::value);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<typename phi::remove_reference<T>::type>::value);
    STATIC_REQUIRE_FALSE(
            phi::is_lvalue_reference<typename phi::add_rvalue_reference<T>::type>::value);

    STATIC_REQUIRE(phi::is_not_lvalue_reference<T>::value);
    STATIC_REQUIRE(phi::is_not_lvalue_reference<typename phi::remove_reference<T>::type>::value);
    STATIC_REQUIRE(
            phi::is_not_lvalue_reference<typename phi::add_rvalue_reference<T>::type>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<T>);
    STATIC_REQUIRE(phi::is_not_referenceable<T>::value ||
                   phi::is_lvalue_reference_v<typename phi::add_lvalue_reference<T>::type>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<typename phi::remove_reference<T>::type>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<typename phi::add_rvalue_reference<T>::type>);

    STATIC_REQUIRE(phi::is_not_lvalue_reference_v<T>);
    STATIC_REQUIRE(phi::is_not_lvalue_reference_v<typename phi::remove_reference<T>::type>);
    STATIC_REQUIRE(phi::is_not_lvalue_reference_v<typename phi::add_rvalue_reference<T>::type>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_lvalue_reference<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_lvalue_reference<T>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_lvalue_reference<T>::value);
}

template <typename T>
void test_is_not_lvalue_reference()
{
    test_is_not_lvalue_reference_impl<T>();
    test_is_not_lvalue_reference_impl<const T>();
    test_is_not_lvalue_reference_impl<volatile T>();
    test_is_not_lvalue_reference_impl<const volatile T>();
}

TEST_CASE("is_lvalue_reference")
{
    test_is_lvalue_reference<bool&>();
    test_is_lvalue_reference<char&>();
    test_is_lvalue_reference<signed char&>();
    test_is_lvalue_reference<unsigned char&>();
    test_is_lvalue_reference<short&>();
    test_is_lvalue_reference<unsigned short&>();
    test_is_lvalue_reference<int&>();
    test_is_lvalue_reference<unsigned int&>();
    test_is_lvalue_reference<long&>();
    test_is_lvalue_reference<unsigned long&>();
    test_is_lvalue_reference<long long&>();
    test_is_lvalue_reference<unsigned long long&>();
    test_is_lvalue_reference<float&>();
    test_is_lvalue_reference<double&>();
    test_is_lvalue_reference<long double&>();
    test_is_lvalue_reference<char8_t&>();
    test_is_lvalue_reference<char16_t&>();
    test_is_lvalue_reference<char32_t&>();
    test_is_lvalue_reference<wchar_t&>();

    test_is_not_lvalue_reference<bool&&>();
    test_is_not_lvalue_reference<char&&>();
    test_is_not_lvalue_reference<signed char&&>();
    test_is_not_lvalue_reference<unsigned char&&>();
    test_is_not_lvalue_reference<short&&>();
    test_is_not_lvalue_reference<unsigned short&&>();
    test_is_not_lvalue_reference<int&&>();
    test_is_not_lvalue_reference<unsigned int&&>();
    test_is_not_lvalue_reference<long&&>();
    test_is_not_lvalue_reference<unsigned long&&>();
    test_is_not_lvalue_reference<long long&&>();
    test_is_not_lvalue_reference<unsigned long long&&>();
    test_is_not_lvalue_reference<float&&>();
    test_is_not_lvalue_reference<double&&>();
    test_is_not_lvalue_reference<long double&&>();
    test_is_not_lvalue_reference<char8_t&&>();
    test_is_not_lvalue_reference<char16_t&&>();
    test_is_not_lvalue_reference<char32_t&&>();
    test_is_not_lvalue_reference<wchar_t&&>();

    test_is_not_lvalue_reference<void>();
    test_is_not_lvalue_reference<phi::nullptr_t>();
    test_is_not_lvalue_reference<bool>();
    test_is_not_lvalue_reference<char>();
    test_is_not_lvalue_reference<signed char>();
    test_is_not_lvalue_reference<unsigned char>();
    test_is_not_lvalue_reference<short>();
    test_is_not_lvalue_reference<unsigned short>();
    test_is_not_lvalue_reference<int>();
    test_is_not_lvalue_reference<unsigned int>();
    test_is_not_lvalue_reference<long>();
    test_is_not_lvalue_reference<unsigned long>();
    test_is_not_lvalue_reference<long long>();
    test_is_not_lvalue_reference<unsigned long long>();
    test_is_not_lvalue_reference<float>();
    test_is_not_lvalue_reference<double>();
    test_is_not_lvalue_reference<long double>();
    test_is_not_lvalue_reference<char8_t>();
    test_is_not_lvalue_reference<char16_t>();
    test_is_not_lvalue_reference<char32_t>();
    test_is_not_lvalue_reference<wchar_t>();

    test_is_not_lvalue_reference<phi::boolean>();
    test_is_not_lvalue_reference<phi::integer<signed char>>();
    test_is_not_lvalue_reference<phi::integer<unsigned char>>();
    test_is_not_lvalue_reference<phi::integer<short>>();
    test_is_not_lvalue_reference<phi::integer<unsigned short>>();
    test_is_not_lvalue_reference<phi::integer<int>>();
    test_is_not_lvalue_reference<phi::integer<unsigned int>>();
    test_is_not_lvalue_reference<phi::integer<long>>();
    test_is_not_lvalue_reference<phi::integer<unsigned long>>();
    test_is_not_lvalue_reference<phi::integer<long long>>();
    test_is_not_lvalue_reference<phi::integer<unsigned long long>>();
    test_is_not_lvalue_reference<phi::floating_point<float>>();
    test_is_not_lvalue_reference<phi::floating_point<double>>();
    test_is_not_lvalue_reference<phi::floating_point<long double>>();

    test_is_not_lvalue_reference<std::vector<int>>();
    test_is_not_lvalue_reference<phi::scope_ptr<int>>();

    test_is_lvalue_reference<int&>();
    test_is_lvalue_reference<const int&>();
    test_is_lvalue_reference<volatile int&>();
    test_is_lvalue_reference<const volatile int&>();
    test_is_not_lvalue_reference<int&&>();
    test_is_not_lvalue_reference<const int&&>();
    test_is_not_lvalue_reference<volatile int&&>();
    test_is_not_lvalue_reference<const volatile int&&>();
    test_is_not_lvalue_reference<int*>();
    test_is_not_lvalue_reference<const int*>();
    test_is_not_lvalue_reference<volatile int*>();
    test_is_not_lvalue_reference<const volatile int*>();
    test_is_not_lvalue_reference<int**>();
    test_is_not_lvalue_reference<const int**>();
    test_is_not_lvalue_reference<volatile int**>();
    test_is_not_lvalue_reference<const volatile int**>();
    test_is_lvalue_reference<int*&>();
    test_is_lvalue_reference<const int*&>();
    test_is_lvalue_reference<volatile int*&>();
    test_is_lvalue_reference<const volatile int*&>();
    test_is_not_lvalue_reference<int*&&>();
    test_is_not_lvalue_reference<const int*&&>();
    test_is_not_lvalue_reference<volatile int*&&>();
    test_is_not_lvalue_reference<const volatile int*&&>();
    test_is_not_lvalue_reference<void*>();
    test_is_not_lvalue_reference<char[3]>();
    test_is_not_lvalue_reference<char[]>();
    test_is_not_lvalue_reference<char* [3]>();
    test_is_not_lvalue_reference<char*[]>();
    test_is_not_lvalue_reference<int(*)[3]>();
    test_is_not_lvalue_reference<int(*)[]>();
    test_is_lvalue_reference<int(&)[3]>();
    test_is_lvalue_reference<int(&)[]>();
    test_is_not_lvalue_reference<int(&&)[3]>();
    test_is_not_lvalue_reference<int(&&)[]>();
    test_is_not_lvalue_reference<char[3][2]>();
    test_is_not_lvalue_reference<char[][2]>();
    test_is_not_lvalue_reference<char* [3][2]>();
    test_is_not_lvalue_reference<char*[][2]>();
    test_is_not_lvalue_reference<int(*)[3][2]>();
    test_is_not_lvalue_reference<int(*)[][2]>();
    test_is_lvalue_reference<int(&)[3][2]>();
    test_is_lvalue_reference<int(&)[][2]>();
    test_is_not_lvalue_reference<int(&&)[3][2]>();
    test_is_not_lvalue_reference<int(&&)[][2]>();
    test_is_not_lvalue_reference<class_type>();
    test_is_not_lvalue_reference<class_type[]>();
    test_is_not_lvalue_reference<class_type[2]>();
    test_is_not_lvalue_reference<template_type<void>>();
    test_is_not_lvalue_reference<template_type<int>>();
    test_is_not_lvalue_reference<template_type<class_type>>();
    test_is_not_lvalue_reference<template_type<incomplete_type>>();
    test_is_not_lvalue_reference<variadic_template<>>();
    test_is_not_lvalue_reference<variadic_template<void>>();
    test_is_not_lvalue_reference<variadic_template<int>>();
    test_is_not_lvalue_reference<variadic_template<class_type>>();
    test_is_not_lvalue_reference<variadic_template<incomplete_type>>();
    test_is_not_lvalue_reference<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_lvalue_reference<public_derived_from<base>>();
    test_is_not_lvalue_reference<public_derived_from<derived>>();
    test_is_not_lvalue_reference<public_derived_from<class_type>>();
    test_is_not_lvalue_reference<private_derived_from<base>>();
    test_is_not_lvalue_reference<private_derived_from<derived>>();
    test_is_not_lvalue_reference<private_derived_from<class_type>>();
    test_is_not_lvalue_reference<protected_derived_from<base>>();
    test_is_not_lvalue_reference<protected_derived_from<derived>>();
    test_is_not_lvalue_reference<protected_derived_from<class_type>>();
    test_is_not_lvalue_reference<union_type>();
    test_is_not_lvalue_reference<non_empty_union>();
    test_is_not_lvalue_reference<empty>();
    test_is_not_lvalue_reference<not_empty>();
    test_is_not_lvalue_reference<bit_zero>();
    test_is_not_lvalue_reference<bit_one>();
    test_is_not_lvalue_reference<base>();
    test_is_not_lvalue_reference<derived>();
    test_is_not_lvalue_reference<abstract>();
    test_is_not_lvalue_reference<public_abstract>();
    test_is_not_lvalue_reference<private_abstract>();
    test_is_not_lvalue_reference<protected_abstract>();
    test_is_not_lvalue_reference<abstract_template<int>>();
    test_is_not_lvalue_reference<abstract_template<double>>();
    test_is_not_lvalue_reference<abstract_template<class_type>>();
    test_is_not_lvalue_reference<abstract_template<incomplete_type>>();
    test_is_not_lvalue_reference<final_type>();
    test_is_not_lvalue_reference<public_destructor>();
    test_is_not_lvalue_reference<protected_destructor>();
    test_is_not_lvalue_reference<private_destructor>();
    test_is_not_lvalue_reference<virtual_public_destructor>();
    test_is_not_lvalue_reference<virtual_protected_destructor>();
    test_is_not_lvalue_reference<virtual_private_destructor>();
    test_is_not_lvalue_reference<pure_public_destructor>();
    test_is_not_lvalue_reference<pure_protected_destructor>();
    test_is_not_lvalue_reference<pure_private_destructor>();
    test_is_not_lvalue_reference<deleted_public_destructor>();
    test_is_not_lvalue_reference<deleted_protected_destructor>();
    test_is_not_lvalue_reference<deleted_private_destructor>();
    test_is_not_lvalue_reference<deleted_virtual_public_destructor>();
    test_is_not_lvalue_reference<deleted_virtual_protected_destructor>();
    test_is_not_lvalue_reference<deleted_virtual_private_destructor>();
    test_is_not_lvalue_reference<Enum>();
    test_is_not_lvalue_reference<EnumSigned>();
    test_is_not_lvalue_reference<EnumUnsigned>();
    test_is_not_lvalue_reference<EnumClass>();
    test_is_not_lvalue_reference<EnumStruct>();
    test_is_not_lvalue_reference<function_type>();
    test_is_not_lvalue_reference<function_ptr>();
    test_is_not_lvalue_reference<member_object_ptr>();
    test_is_not_lvalue_reference<member_function_ptr>();
    test_is_not_lvalue_reference<incomplete_type>();
    test_is_not_lvalue_reference<incomplete_template<void>>();
    test_is_not_lvalue_reference<incomplete_template<int>>();
    test_is_not_lvalue_reference<incomplete_template<class_type>>();
    test_is_not_lvalue_reference<incomplete_template<incomplete_type>>();
    test_is_not_lvalue_reference<incomplete_variadic_template<>>();
    test_is_not_lvalue_reference<incomplete_variadic_template<void>>();
    test_is_not_lvalue_reference<incomplete_variadic_template<int>>();
    test_is_not_lvalue_reference<incomplete_variadic_template<class_type>>();
    test_is_not_lvalue_reference<incomplete_variadic_template<incomplete_type>>();
    test_is_not_lvalue_reference<
            incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_lvalue_reference<int class_type::*>();
    test_is_not_lvalue_reference<float class_type::*>();
    test_is_not_lvalue_reference<void * class_type::*>();
    test_is_not_lvalue_reference<int * class_type::*>();
    test_is_lvalue_reference<int class_type::*&>();
    test_is_lvalue_reference<float class_type::*&>();
    test_is_lvalue_reference<void * class_type::*&>();
    test_is_lvalue_reference<int * class_type::*&>();
    test_is_not_lvalue_reference<int class_type::*&&>();
    test_is_not_lvalue_reference<float class_type::*&&>();
    test_is_not_lvalue_reference<void * class_type::*&&>();
    test_is_not_lvalue_reference<int * class_type::*&&>();
    test_is_not_lvalue_reference<int class_type::*const>();
    test_is_not_lvalue_reference<float class_type::*const>();
    test_is_not_lvalue_reference<void * class_type::*const>();
    test_is_lvalue_reference<int class_type::*const&>();
    test_is_lvalue_reference<float class_type::*const&>();
    test_is_lvalue_reference<void * class_type::*const&>();
    test_is_not_lvalue_reference<int class_type::*const&&>();
    test_is_not_lvalue_reference<float class_type::*const&&>();
    test_is_not_lvalue_reference<void * class_type::*const&&>();
    test_is_not_lvalue_reference<int class_type::*volatile>();
    test_is_not_lvalue_reference<float class_type::*volatile>();
    test_is_not_lvalue_reference<void * class_type::*volatile>();
    test_is_lvalue_reference<int class_type::*volatile&>();
    test_is_lvalue_reference<float class_type::*volatile&>();
    test_is_lvalue_reference<void * class_type::*volatile&>();
    test_is_not_lvalue_reference<int class_type::*volatile&&>();
    test_is_not_lvalue_reference<float class_type::*volatile&&>();
    test_is_not_lvalue_reference<void * class_type::*volatile&&>();
    test_is_not_lvalue_reference<int class_type::*const volatile>();
    test_is_not_lvalue_reference<float class_type::*const volatile>();
    test_is_not_lvalue_reference<void * class_type::*const volatile>();
    test_is_lvalue_reference<int class_type::*const volatile&>();
    test_is_lvalue_reference<float class_type::*const volatile&>();
    test_is_lvalue_reference<void * class_type::*const volatile&>();
    test_is_not_lvalue_reference<int class_type::*const volatile&&>();
    test_is_not_lvalue_reference<float class_type::*const volatile&&>();
    test_is_not_lvalue_reference<void * class_type::*const volatile&&>();
    test_is_not_lvalue_reference<non_copyable>();
    test_is_not_lvalue_reference<non_moveable>();
    test_is_not_lvalue_reference<non_constructible>();
    test_is_not_lvalue_reference<tracked>();
    test_is_not_lvalue_reference<trap_constructible>();
    test_is_not_lvalue_reference<trap_implicit_conversion>();
    test_is_not_lvalue_reference<trap_comma>();
    test_is_not_lvalue_reference<trap_call>();
    test_is_not_lvalue_reference<trap_self_assign>();
    test_is_not_lvalue_reference<trap_deref>();
    test_is_not_lvalue_reference<trap_array_subscript>();

    test_is_not_lvalue_reference<void()>();
    test_is_not_lvalue_reference<void()&>();
    test_is_not_lvalue_reference<void() &&>();
    test_is_not_lvalue_reference<void() const>();
    test_is_not_lvalue_reference<void() const&>();
    test_is_not_lvalue_reference<void() const&&>();
    test_is_not_lvalue_reference<void() volatile>();
    test_is_not_lvalue_reference<void() volatile&>();
    test_is_not_lvalue_reference<void() volatile&&>();
    test_is_not_lvalue_reference<void() const volatile>();
    test_is_not_lvalue_reference<void() const volatile&>();
    test_is_not_lvalue_reference<void() const volatile&&>();
    test_is_not_lvalue_reference<void() noexcept>();
    test_is_not_lvalue_reference<void()& noexcept>();
    test_is_not_lvalue_reference<void()&& noexcept>();
    test_is_not_lvalue_reference<void() const noexcept>();
    test_is_not_lvalue_reference<void() const& noexcept>();
    test_is_not_lvalue_reference<void() const&& noexcept>();
    test_is_not_lvalue_reference<void() volatile noexcept>();
    test_is_not_lvalue_reference<void() volatile& noexcept>();
    test_is_not_lvalue_reference<void() volatile&& noexcept>();
    test_is_not_lvalue_reference<void() const volatile noexcept>();
    test_is_not_lvalue_reference<void() const volatile& noexcept>();
    test_is_not_lvalue_reference<void() const volatile&& noexcept>();

    test_is_not_lvalue_reference<void(int)>();
    test_is_not_lvalue_reference<void(int)&>();
    test_is_not_lvalue_reference<void(int) &&>();
    test_is_not_lvalue_reference<void(int) const>();
    test_is_not_lvalue_reference<void(int) const&>();
    test_is_not_lvalue_reference<void(int) const&&>();
    test_is_not_lvalue_reference<void(int) volatile>();
    test_is_not_lvalue_reference<void(int) volatile&>();
    test_is_not_lvalue_reference<void(int) volatile&&>();
    test_is_not_lvalue_reference<void(int) const volatile>();
    test_is_not_lvalue_reference<void(int) const volatile&>();
    test_is_not_lvalue_reference<void(int) const volatile&&>();
    test_is_not_lvalue_reference<void(int) noexcept>();
    test_is_not_lvalue_reference<void(int)& noexcept>();
    test_is_not_lvalue_reference<void(int)&& noexcept>();
    test_is_not_lvalue_reference<void(int) const noexcept>();
    test_is_not_lvalue_reference<void(int) const& noexcept>();
    test_is_not_lvalue_reference<void(int) const&& noexcept>();
    test_is_not_lvalue_reference<void(int) volatile noexcept>();
    test_is_not_lvalue_reference<void(int) volatile& noexcept>();
    test_is_not_lvalue_reference<void(int) volatile&& noexcept>();
    test_is_not_lvalue_reference<void(int) const volatile noexcept>();
    test_is_not_lvalue_reference<void(int) const volatile& noexcept>();
    test_is_not_lvalue_reference<void(int) const volatile&& noexcept>();

    test_is_not_lvalue_reference<void(...)>();
    test_is_not_lvalue_reference<void(...)&>();
    test_is_not_lvalue_reference<void(...) &&>();
    test_is_not_lvalue_reference<void(...) const>();
    test_is_not_lvalue_reference<void(...) const&>();
    test_is_not_lvalue_reference<void(...) const&&>();
    test_is_not_lvalue_reference<void(...) volatile>();
    test_is_not_lvalue_reference<void(...) volatile&>();
    test_is_not_lvalue_reference<void(...) volatile&&>();
    test_is_not_lvalue_reference<void(...) const volatile>();
    test_is_not_lvalue_reference<void(...) const volatile&>();
    test_is_not_lvalue_reference<void(...) const volatile&&>();
    test_is_not_lvalue_reference<void(...) noexcept>();
    test_is_not_lvalue_reference<void(...)& noexcept>();
    test_is_not_lvalue_reference<void(...)&& noexcept>();
    test_is_not_lvalue_reference<void(...) const noexcept>();
    test_is_not_lvalue_reference<void(...) const& noexcept>();
    test_is_not_lvalue_reference<void(...) const&& noexcept>();
    test_is_not_lvalue_reference<void(...) volatile noexcept>();
    test_is_not_lvalue_reference<void(...) volatile& noexcept>();
    test_is_not_lvalue_reference<void(...) volatile&& noexcept>();
    test_is_not_lvalue_reference<void(...) const volatile noexcept>();
    test_is_not_lvalue_reference<void(...) const volatile& noexcept>();
    test_is_not_lvalue_reference<void(...) const volatile&& noexcept>();

    test_is_not_lvalue_reference<void(int, ...)>();
    test_is_not_lvalue_reference<void(int, ...)&>();
    test_is_not_lvalue_reference<void(int, ...) &&>();
    test_is_not_lvalue_reference<void(int, ...) const>();
    test_is_not_lvalue_reference<void(int, ...) const&>();
    test_is_not_lvalue_reference<void(int, ...) const&&>();
    test_is_not_lvalue_reference<void(int, ...) volatile>();
    test_is_not_lvalue_reference<void(int, ...) volatile&>();
    test_is_not_lvalue_reference<void(int, ...) volatile&&>();
    test_is_not_lvalue_reference<void(int, ...) const volatile>();
    test_is_not_lvalue_reference<void(int, ...) const volatile&>();
    test_is_not_lvalue_reference<void(int, ...) const volatile&&>();
    test_is_not_lvalue_reference<void(int, ...) noexcept>();
    test_is_not_lvalue_reference<void(int, ...)& noexcept>();
    test_is_not_lvalue_reference<void(int, ...)&& noexcept>();
    test_is_not_lvalue_reference<void(int, ...) const noexcept>();
    test_is_not_lvalue_reference<void(int, ...) const& noexcept>();
    test_is_not_lvalue_reference<void(int, ...) const&& noexcept>();
    test_is_not_lvalue_reference<void(int, ...) volatile noexcept>();
    test_is_not_lvalue_reference<void(int, ...) volatile& noexcept>();
    test_is_not_lvalue_reference<void(int, ...) volatile&& noexcept>();
    test_is_not_lvalue_reference<void(int, ...) const volatile noexcept>();
    test_is_not_lvalue_reference<void(int, ...) const volatile& noexcept>();
    test_is_not_lvalue_reference<void(int, ...) const volatile&& noexcept>();

    test_is_not_lvalue_reference<int()>();
    test_is_not_lvalue_reference<int()&>();
    test_is_not_lvalue_reference<int() &&>();
    test_is_not_lvalue_reference<int() const>();
    test_is_not_lvalue_reference<int() const&>();
    test_is_not_lvalue_reference<int() const&&>();
    test_is_not_lvalue_reference<int() volatile>();
    test_is_not_lvalue_reference<int() volatile&>();
    test_is_not_lvalue_reference<int() volatile&&>();
    test_is_not_lvalue_reference<int() const volatile>();
    test_is_not_lvalue_reference<int() const volatile&>();
    test_is_not_lvalue_reference<int() const volatile&&>();
    test_is_not_lvalue_reference<int() noexcept>();
    test_is_not_lvalue_reference<int()& noexcept>();
    test_is_not_lvalue_reference<int()&& noexcept>();
    test_is_not_lvalue_reference<int() const noexcept>();
    test_is_not_lvalue_reference<int() const& noexcept>();
    test_is_not_lvalue_reference<int() const&& noexcept>();
    test_is_not_lvalue_reference<int() volatile noexcept>();
    test_is_not_lvalue_reference<int() volatile& noexcept>();
    test_is_not_lvalue_reference<int() volatile&& noexcept>();
    test_is_not_lvalue_reference<int() const volatile noexcept>();
    test_is_not_lvalue_reference<int() const volatile& noexcept>();
    test_is_not_lvalue_reference<int() const volatile&& noexcept>();

    test_is_not_lvalue_reference<int(int)>();
    test_is_not_lvalue_reference<int(int)&>();
    test_is_not_lvalue_reference<int(int) &&>();
    test_is_not_lvalue_reference<int(int) const>();
    test_is_not_lvalue_reference<int(int) const&>();
    test_is_not_lvalue_reference<int(int) const&&>();
    test_is_not_lvalue_reference<int(int) volatile>();
    test_is_not_lvalue_reference<int(int) volatile&>();
    test_is_not_lvalue_reference<int(int) volatile&&>();
    test_is_not_lvalue_reference<int(int) const volatile>();
    test_is_not_lvalue_reference<int(int) const volatile&>();
    test_is_not_lvalue_reference<int(int) const volatile&&>();
    test_is_not_lvalue_reference<int(int) noexcept>();
    test_is_not_lvalue_reference<int(int)& noexcept>();
    test_is_not_lvalue_reference<int(int)&& noexcept>();
    test_is_not_lvalue_reference<int(int) const noexcept>();
    test_is_not_lvalue_reference<int(int) const& noexcept>();
    test_is_not_lvalue_reference<int(int) const&& noexcept>();
    test_is_not_lvalue_reference<int(int) volatile noexcept>();
    test_is_not_lvalue_reference<int(int) volatile& noexcept>();
    test_is_not_lvalue_reference<int(int) volatile&& noexcept>();
    test_is_not_lvalue_reference<int(int) const volatile noexcept>();
    test_is_not_lvalue_reference<int(int) const volatile& noexcept>();
    test_is_not_lvalue_reference<int(int) const volatile&& noexcept>();

    test_is_not_lvalue_reference<int(...)>();
    test_is_not_lvalue_reference<int(...)&>();
    test_is_not_lvalue_reference<int(...) &&>();
    test_is_not_lvalue_reference<int(...) const>();
    test_is_not_lvalue_reference<int(...) const&>();
    test_is_not_lvalue_reference<int(...) const&&>();
    test_is_not_lvalue_reference<int(...) volatile>();
    test_is_not_lvalue_reference<int(...) volatile&>();
    test_is_not_lvalue_reference<int(...) volatile&&>();
    test_is_not_lvalue_reference<int(...) const volatile>();
    test_is_not_lvalue_reference<int(...) const volatile&>();
    test_is_not_lvalue_reference<int(...) const volatile&&>();
    test_is_not_lvalue_reference<int(...) noexcept>();
    test_is_not_lvalue_reference<int(...)& noexcept>();
    test_is_not_lvalue_reference<int(...)&& noexcept>();
    test_is_not_lvalue_reference<int(...) const noexcept>();
    test_is_not_lvalue_reference<int(...) const& noexcept>();
    test_is_not_lvalue_reference<int(...) const&& noexcept>();
    test_is_not_lvalue_reference<int(...) volatile noexcept>();
    test_is_not_lvalue_reference<int(...) volatile& noexcept>();
    test_is_not_lvalue_reference<int(...) volatile&& noexcept>();
    test_is_not_lvalue_reference<int(...) const volatile noexcept>();
    test_is_not_lvalue_reference<int(...) const volatile& noexcept>();
    test_is_not_lvalue_reference<int(...) const volatile&& noexcept>();

    test_is_not_lvalue_reference<int(int, ...)>();
    test_is_not_lvalue_reference<int(int, ...)&>();
    test_is_not_lvalue_reference<int(int, ...) &&>();
    test_is_not_lvalue_reference<int(int, ...) const>();
    test_is_not_lvalue_reference<int(int, ...) const&>();
    test_is_not_lvalue_reference<int(int, ...) const&&>();
    test_is_not_lvalue_reference<int(int, ...) volatile>();
    test_is_not_lvalue_reference<int(int, ...) volatile&>();
    test_is_not_lvalue_reference<int(int, ...) volatile&&>();
    test_is_not_lvalue_reference<int(int, ...) const volatile>();
    test_is_not_lvalue_reference<int(int, ...) const volatile&>();
    test_is_not_lvalue_reference<int(int, ...) const volatile&&>();
    test_is_not_lvalue_reference<int(int, ...) noexcept>();
    test_is_not_lvalue_reference<int(int, ...)& noexcept>();
    test_is_not_lvalue_reference<int(int, ...)&& noexcept>();
    test_is_not_lvalue_reference<int(int, ...) const noexcept>();
    test_is_not_lvalue_reference<int(int, ...) const& noexcept>();
    test_is_not_lvalue_reference<int(int, ...) const&& noexcept>();
    test_is_not_lvalue_reference<int(int, ...) volatile noexcept>();
    test_is_not_lvalue_reference<int(int, ...) volatile& noexcept>();
    test_is_not_lvalue_reference<int(int, ...) volatile&& noexcept>();
    test_is_not_lvalue_reference<int(int, ...) const volatile noexcept>();
    test_is_not_lvalue_reference<int(int, ...) const volatile& noexcept>();
    test_is_not_lvalue_reference<int(int, ...) const volatile&& noexcept>();

    test_is_not_lvalue_reference<void (*)()>();
    test_is_not_lvalue_reference<void (*)() noexcept>();

    test_is_not_lvalue_reference<void (*)(int)>();
    test_is_not_lvalue_reference<void (*)(int) noexcept>();

    test_is_not_lvalue_reference<void (*)(...)>();
    test_is_not_lvalue_reference<void (*)(...) noexcept>();

    test_is_not_lvalue_reference<void (*)(int, ...)>();
    test_is_not_lvalue_reference<void (*)(int, ...) noexcept>();

    test_is_not_lvalue_reference<int (*)()>();
    test_is_not_lvalue_reference<int (*)() noexcept>();

    test_is_not_lvalue_reference<int (*)(int)>();
    test_is_not_lvalue_reference<int (*)(int) noexcept>();

    test_is_not_lvalue_reference<int (*)(...)>();
    test_is_not_lvalue_reference<int (*)(...) noexcept>();

    test_is_not_lvalue_reference<int (*)(int, ...)>();
    test_is_not_lvalue_reference<int (*)(int, ...) noexcept>();

    test_is_lvalue_reference<void (&)()>();
    test_is_lvalue_reference<void (&)() noexcept>();

    test_is_lvalue_reference<void (&)(int)>();
    test_is_lvalue_reference<void (&)(int) noexcept>();

    test_is_lvalue_reference<void (&)(...)>();
    test_is_lvalue_reference<void (&)(...) noexcept>();

    test_is_lvalue_reference<void (&)(int, ...)>();
    test_is_lvalue_reference<void (&)(int, ...) noexcept>();

    test_is_lvalue_reference<int (&)()>();
    test_is_lvalue_reference<int (&)() noexcept>();

    test_is_lvalue_reference<int (&)(int)>();
    test_is_lvalue_reference<int (&)(int) noexcept>();

    test_is_lvalue_reference<int (&)(...)>();
    test_is_lvalue_reference<int (&)(...) noexcept>();

    test_is_lvalue_reference<int (&)(int, ...)>();
    test_is_lvalue_reference<int (&)(int, ...) noexcept>();

    test_is_not_lvalue_reference<void(&&)()>();
    test_is_not_lvalue_reference<void(&&)() noexcept>();

    test_is_not_lvalue_reference<void(&&)(int)>();
    test_is_not_lvalue_reference<void(&&)(int) noexcept>();

    test_is_not_lvalue_reference<void(&&)(...)>();
    test_is_not_lvalue_reference<void(&&)(...) noexcept>();

    test_is_not_lvalue_reference<void(&&)(int, ...)>();
    test_is_not_lvalue_reference<void(&&)(int, ...) noexcept>();

    test_is_not_lvalue_reference<int(&&)()>();
    test_is_not_lvalue_reference<int(&&)() noexcept>();

    test_is_not_lvalue_reference<int(&&)(int)>();
    test_is_not_lvalue_reference<int(&&)(int) noexcept>();

    test_is_not_lvalue_reference<int(&&)(...)>();
    test_is_not_lvalue_reference<int(&&)(...) noexcept>();

    test_is_not_lvalue_reference<int(&&)(int, ...)>();
    test_is_not_lvalue_reference<int(&&)(int, ...) noexcept>();

    test_is_not_lvalue_reference<void (class_type::*)()>();
    test_is_not_lvalue_reference<void (class_type::*)()&>();
    test_is_not_lvalue_reference<void (class_type::*)() &&>();
    test_is_not_lvalue_reference<void (class_type::*)() const>();
    test_is_not_lvalue_reference<void (class_type::*)() const&>();
    test_is_not_lvalue_reference<void (class_type::*)() const&&>();
    test_is_not_lvalue_reference<void (class_type::*)() noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)()& noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)()&& noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)() const noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)() const& noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)() const&& noexcept>();

    test_is_not_lvalue_reference<void (class_type::*)(int)>();
    test_is_not_lvalue_reference<void (class_type::*)(int)&>();
    test_is_not_lvalue_reference<void (class_type::*)(int) &&>();
    test_is_not_lvalue_reference<void (class_type::*)(int) const>();
    test_is_not_lvalue_reference<void (class_type::*)(int) const&>();
    test_is_not_lvalue_reference<void (class_type::*)(int) const&&>();
    test_is_not_lvalue_reference<void (class_type::*)(int) noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)(int)& noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)(int)&& noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)(int) const noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)(int) const& noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)(int) const&& noexcept>();

    test_is_not_lvalue_reference<void (class_type::*)(...)>();
    test_is_not_lvalue_reference<void (class_type::*)(...)&>();
    test_is_not_lvalue_reference<void (class_type::*)(...) &&>();
    test_is_not_lvalue_reference<void (class_type::*)(...) const>();
    test_is_not_lvalue_reference<void (class_type::*)(...) const&>();
    test_is_not_lvalue_reference<void (class_type::*)(...) const&&>();
    test_is_not_lvalue_reference<void (class_type::*)(...) noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)(...)& noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)(...)&& noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)(...) const noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)(...) const& noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)(...) const&& noexcept>();

    test_is_not_lvalue_reference<void (class_type::*)(int, ...)>();
    test_is_not_lvalue_reference<void (class_type::*)(int, ...)&>();
    test_is_not_lvalue_reference<void (class_type::*)(int, ...) &&>();
    test_is_not_lvalue_reference<void (class_type::*)(int, ...) const>();
    test_is_not_lvalue_reference<void (class_type::*)(int, ...) const&>();
    test_is_not_lvalue_reference<void (class_type::*)(int, ...) const&&>();
    test_is_not_lvalue_reference<void (class_type::*)(int, ...) noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)(int, ...)& noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)(int, ...)&& noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)(int, ...) const& noexcept>();
    test_is_not_lvalue_reference<void (class_type::*)(int, ...) const&& noexcept>();

    test_is_not_lvalue_reference<int (class_type::*)()>();
    test_is_not_lvalue_reference<int (class_type::*)()&>();
    test_is_not_lvalue_reference<int (class_type::*)() &&>();
    test_is_not_lvalue_reference<int (class_type::*)() const>();
    test_is_not_lvalue_reference<int (class_type::*)() const&>();
    test_is_not_lvalue_reference<int (class_type::*)() const&&>();
    test_is_not_lvalue_reference<int (class_type::*)() noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)()& noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)()&& noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)() const noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)() const& noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)() const&& noexcept>();

    test_is_not_lvalue_reference<int (class_type::*)(int)>();
    test_is_not_lvalue_reference<int (class_type::*)(int)&>();
    test_is_not_lvalue_reference<int (class_type::*)(int) &&>();
    test_is_not_lvalue_reference<int (class_type::*)(int) const>();
    test_is_not_lvalue_reference<int (class_type::*)(int) const&>();
    test_is_not_lvalue_reference<int (class_type::*)(int) const&&>();
    test_is_not_lvalue_reference<int (class_type::*)(int) noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)(int)& noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)(int)&& noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)(int) const noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)(int) const& noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)(int) const&& noexcept>();

    test_is_not_lvalue_reference<int (class_type::*)(...)>();
    test_is_not_lvalue_reference<int (class_type::*)(...)&>();
    test_is_not_lvalue_reference<int (class_type::*)(...) &&>();
    test_is_not_lvalue_reference<int (class_type::*)(...) const>();
    test_is_not_lvalue_reference<int (class_type::*)(...) const&>();
    test_is_not_lvalue_reference<int (class_type::*)(...) const&&>();
    test_is_not_lvalue_reference<int (class_type::*)(...) noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)(...)& noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)(...)&& noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)(...) const noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)(...) const& noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)(...) const&& noexcept>();

    test_is_not_lvalue_reference<int (class_type::*)(int, ...)>();
    test_is_not_lvalue_reference<int (class_type::*)(int, ...)&>();
    test_is_not_lvalue_reference<int (class_type::*)(int, ...) &&>();
    test_is_not_lvalue_reference<int (class_type::*)(int, ...) const>();
    test_is_not_lvalue_reference<int (class_type::*)(int, ...) const&>();
    test_is_not_lvalue_reference<int (class_type::*)(int, ...) const&&>();
    test_is_not_lvalue_reference<int (class_type::*)(int, ...) noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)(int, ...)& noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)(int, ...)&& noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)(int, ...) const& noexcept>();
    test_is_not_lvalue_reference<int (class_type::*)(int, ...) const&& noexcept>();
}
