#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_array.hpp>
#include <phi/type_traits/is_class.hpp>
#include <phi/type_traits/is_compound.hpp>
#include <phi/type_traits/is_enum.hpp>
#include <phi/type_traits/is_function.hpp>
#include <phi/type_traits/is_lvalue_reference.hpp>
#include <phi/type_traits/is_member_function_pointer.hpp>
#include <phi/type_traits/is_member_object_pointer.hpp>
#include <phi/type_traits/is_member_pointer.hpp>
#include <phi/type_traits/is_null_pointer.hpp>
#include <phi/type_traits/is_object.hpp>
#include <phi/type_traits/is_pointer.hpp>
#include <phi/type_traits/is_reference.hpp>
#include <phi/type_traits/is_rvalue_reference.hpp>
#include <phi/type_traits/is_union.hpp>
#include <phi/type_traits/is_unsafe_arithmetic.hpp>
#include <phi/type_traits/is_unsafe_bool.hpp>
#include <phi/type_traits/is_unsafe_floating_point.hpp>
#include <phi/type_traits/is_unsafe_fundamental.hpp>
#include <phi/type_traits/is_unsafe_integer.hpp>
#include <phi/type_traits/is_unsafe_integral.hpp>
#include <phi/type_traits/is_unsafe_scalar.hpp>
#include <phi/type_traits/is_void.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_class_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_unsafe_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_bool<T>::value);
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE(phi::is_class<T>::value);
#endif
    STATIC_REQUIRE(phi::is_compound<T>::value);
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_fundamental<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integral<T>::value);
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
#if PHI_HAS_WORKING_IS_UNSAFE_SCALAR()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_scalar<T>::value);
#endif
#if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);

#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_not_class<T>::value);
#endif

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_bool_v<T>);
#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE(phi::is_class_v<T>);
#    endif
    STATIC_REQUIRE(phi::is_compound_v<T>);
#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_fundamental_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integral_v<T>);
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
#    if PHI_HAS_WORKING_IS_UNSAFE_SCALAR()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_scalar_v<T>);
#    endif
#    if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);

#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_not_class_v<T>);
#    endif
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_class<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_class<T>);

    // Standard compatibility
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE(std::is_class<T>::value);
#    if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(std::is_class_v<T>);
#    endif
#endif
}

template <typename T>
void test_is_class()
{
    test_is_class_impl<T>();
    test_is_class_impl<const T>();
    test_is_class_impl<volatile T>();
    test_is_class_impl<const volatile T>();
}

template <typename T>
void test_is_not_class_impl()
{
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
    STATIC_REQUIRE(phi::is_not_class<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
    STATIC_REQUIRE(phi::is_not_class_v<T>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_class<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_class<T>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_class<T>::value);
#    if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE_FALSE(std::is_class_v<T>);
#    endif
#endif
}

template <typename T>
void test_is_not_class()
{
    test_is_not_class_impl<T>();
    test_is_not_class_impl<const T>();
    test_is_not_class_impl<volatile T>();
    test_is_not_class_impl<const volatile T>();
}

TEST_CASE("is_class")
{
    test_is_not_class<void>();
    test_is_not_class<phi::nullptr_t>();
    test_is_not_class<bool>();
    test_is_not_class<char>();
    test_is_not_class<signed char>();
    test_is_not_class<unsigned char>();
    test_is_not_class<short>();
    test_is_not_class<unsigned short>();
    test_is_not_class<int>();
    test_is_not_class<unsigned int>();
    test_is_not_class<long>();
    test_is_not_class<unsigned long>();
    test_is_not_class<long long>();
    test_is_not_class<unsigned long long>();
    test_is_not_class<float>();
    test_is_not_class<double>();
    test_is_not_class<long double>();
    test_is_not_class<char8_t>();
    test_is_not_class<char16_t>();
    test_is_not_class<char32_t>();
    test_is_not_class<wchar_t>();

    test_is_class<phi::boolean>();
    test_is_class<phi::integer<signed char>>();
    test_is_class<phi::integer<unsigned char>>();
    test_is_class<phi::integer<short>>();
    test_is_class<phi::integer<unsigned short>>();
    test_is_class<phi::integer<int>>();
    test_is_class<phi::integer<unsigned int>>();
    test_is_class<phi::integer<long>>();
    test_is_class<phi::integer<unsigned long>>();
    test_is_class<phi::integer<long long>>();
    test_is_class<phi::integer<unsigned long long>>();
    test_is_class<phi::floating_point<float>>();
    test_is_class<phi::floating_point<double>>();
    test_is_class<phi::floating_point<long double>>();

    test_is_class<std::vector<int>>();
    test_is_class<phi::scope_ptr<int>>();

    test_is_not_class<int&>();
    test_is_not_class<const int&>();
    test_is_not_class<volatile int&>();
    test_is_not_class<const volatile int&>();
    test_is_not_class<int&&>();
    test_is_not_class<const int&&>();
    test_is_not_class<volatile int&&>();
    test_is_not_class<const volatile int&&>();
    test_is_not_class<int*>();
    test_is_not_class<const int*>();
    test_is_not_class<volatile int*>();
    test_is_not_class<const volatile int*>();
    test_is_not_class<int**>();
    test_is_not_class<const int**>();
    test_is_not_class<volatile int**>();
    test_is_not_class<const volatile int**>();
    test_is_not_class<int*&>();
    test_is_not_class<const int*&>();
    test_is_not_class<volatile int*&>();
    test_is_not_class<const volatile int*&>();
    test_is_not_class<int*&&>();
    test_is_not_class<const int*&&>();
    test_is_not_class<volatile int*&&>();
    test_is_not_class<const volatile int*&&>();
    test_is_not_class<void*>();
    test_is_not_class<char[3]>();
    test_is_not_class<char[]>();
    test_is_not_class<char* [3]>();
    test_is_not_class<char*[]>();
    test_is_not_class<int(*)[3]>();
    test_is_not_class<int(*)[]>();
    test_is_not_class<int(&)[3]>();
    test_is_not_class<int(&)[]>();
    test_is_not_class<int(&&)[3]>();
    test_is_not_class<int(&&)[]>();
    test_is_not_class<char[3][2]>();
    test_is_not_class<char[][2]>();
    test_is_not_class<char* [3][2]>();
    test_is_not_class<char*[][2]>();
    test_is_not_class<int(*)[3][2]>();
    test_is_not_class<int(*)[][2]>();
    test_is_not_class<int(&)[3][2]>();
    test_is_not_class<int(&)[][2]>();
    test_is_not_class<int(&&)[3][2]>();
    test_is_not_class<int(&&)[][2]>();
    test_is_class<class_type>();
    test_is_not_class<class_type[]>();
    test_is_not_class<class_type[2]>();
    test_is_class<template_type<void>>();
    test_is_class<template_type<int>>();
    test_is_class<template_type<class_type>>();
    test_is_class<template_type<incomplete_type>>();
    test_is_class<variadic_template<>>();
    test_is_class<variadic_template<void>>();
    test_is_class<variadic_template<int>>();
    test_is_class<variadic_template<class_type>>();
    test_is_class<variadic_template<incomplete_type>>();
    test_is_class<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_class<public_derived_from<base>>();
    test_is_class<public_derived_from<derived>>();
    test_is_class<public_derived_from<class_type>>();
    test_is_class<private_derived_from<base>>();
    test_is_class<private_derived_from<derived>>();
    test_is_class<private_derived_from<class_type>>();
    test_is_class<protected_derived_from<base>>();
    test_is_class<protected_derived_from<derived>>();
    test_is_class<protected_derived_from<class_type>>();
    test_is_not_class<union_type>();
    test_is_not_class<non_empty_union>();
    test_is_class<empty>();
    test_is_class<not_empty>();
    test_is_class<bit_zero>();
    test_is_class<bit_one>();
    test_is_class<base>();
    test_is_class<derived>();
    test_is_class<abstract>();
    test_is_class<public_abstract>();
    test_is_class<private_abstract>();
    test_is_class<protected_abstract>();
    test_is_class<abstract_template<int>>();
    test_is_class<abstract_template<double>>();
    test_is_class<abstract_template<class_type>>();
    test_is_class<abstract_template<incomplete_type>>();
    test_is_class<final_type>();
    test_is_class<public_destructor>();
    test_is_class<protected_destructor>();
    test_is_class<private_destructor>();
    test_is_class<virtual_public_destructor>();
    test_is_class<virtual_protected_destructor>();
    test_is_class<virtual_private_destructor>();
    test_is_class<pure_public_destructor>();
    test_is_class<pure_protected_destructor>();
    test_is_class<pure_private_destructor>();
    test_is_class<deleted_public_destructor>();
    test_is_class<deleted_protected_destructor>();
    test_is_class<deleted_private_destructor>();
    test_is_class<deleted_virtual_public_destructor>();
    test_is_class<deleted_virtual_protected_destructor>();
    test_is_class<deleted_virtual_private_destructor>();
    test_is_class<final_type>();
    test_is_not_class<enum_type>();
    test_is_not_class<enum_signed>();
    test_is_not_class<enum_unsigned>();
    test_is_not_class<enum_class>();
    test_is_not_class<enum_struct>();
    test_is_not_class<function_type>();
    test_is_not_class<function_ptr>();
    test_is_not_class<member_object_ptr>();
    test_is_not_class<member_function_ptr>();
    test_is_class<incomplete_type>();
    test_is_class<incomplete_template<void>>();
    test_is_class<incomplete_template<int>>();
    test_is_class<incomplete_template<class_type>>();
    test_is_class<incomplete_template<incomplete_type>>();
    test_is_class<IncompleteVariadicTemplate<>>();
    test_is_class<IncompleteVariadicTemplate<void>>();
    test_is_class<IncompleteVariadicTemplate<int>>();
    test_is_class<IncompleteVariadicTemplate<class_type>>();
    test_is_class<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_class<IncompleteVariadicTemplate<int, void, class_type, volatile char[]>>();
    test_is_not_class<int class_type::*>();
    test_is_not_class<float class_type::*>();
    test_is_not_class<void * class_type::*>();
    test_is_not_class<int * class_type::*>();
    test_is_not_class<int class_type::*&>();
    test_is_not_class<float class_type::*&>();
    test_is_not_class<void * class_type::*&>();
    test_is_not_class<int * class_type::*&>();
    test_is_not_class<int class_type::*&&>();
    test_is_not_class<float class_type::*&&>();
    test_is_not_class<void * class_type::*&&>();
    test_is_not_class<int * class_type::*&&>();
    test_is_not_class<int class_type::*const>();
    test_is_not_class<float class_type::*const>();
    test_is_not_class<void * class_type::*const>();
    test_is_not_class<int class_type::*const&>();
    test_is_not_class<float class_type::*const&>();
    test_is_not_class<void * class_type::*const&>();
    test_is_not_class<int class_type::*const&&>();
    test_is_not_class<float class_type::*const&&>();
    test_is_not_class<void * class_type::*const&&>();
    test_is_not_class<int class_type::*volatile>();
    test_is_not_class<float class_type::*volatile>();
    test_is_not_class<void * class_type::*volatile>();
    test_is_not_class<int class_type::*volatile&>();
    test_is_not_class<float class_type::*volatile&>();
    test_is_not_class<void * class_type::*volatile&>();
    test_is_not_class<int class_type::*volatile&&>();
    test_is_not_class<float class_type::*volatile&&>();
    test_is_not_class<void * class_type::*volatile&&>();
    test_is_not_class<int class_type::*const volatile>();
    test_is_not_class<float class_type::*const volatile>();
    test_is_not_class<void * class_type::*const volatile>();
    test_is_not_class<int class_type::*const volatile&>();
    test_is_not_class<float class_type::*const volatile&>();
    test_is_not_class<void * class_type::*const volatile&>();
    test_is_not_class<int class_type::*const volatile&&>();
    test_is_not_class<float class_type::*const volatile&&>();
    test_is_not_class<void * class_type::*const volatile&&>();
    test_is_class<non_copyable>();
    test_is_class<non_moveable>();
    test_is_class<non_constructible>();
    test_is_class<tracked>();
    test_is_class<trap_constructible>();
    test_is_class<trap_implicit_conversion>();
    test_is_class<trap_comma>();
    test_is_class<trap_call>();
    test_is_class<trap_self_assign>();
    test_is_class<trap_deref>();
    test_is_class<trap_array_subscript>();

    test_is_not_class<void()>();
    test_is_not_class<void()&>();
    test_is_not_class<void() &&>();
    test_is_not_class<void() const>();
    test_is_not_class<void() const&>();
    test_is_not_class<void() const&&>();
    test_is_not_class<void() volatile>();
    test_is_not_class<void() volatile&>();
    test_is_not_class<void() volatile&&>();
    test_is_not_class<void() const volatile>();
    test_is_not_class<void() const volatile&>();
    test_is_not_class<void() const volatile&&>();
    test_is_not_class<void() noexcept>();
    test_is_not_class<void()& noexcept>();
    test_is_not_class<void()&& noexcept>();
    test_is_not_class<void() const noexcept>();
    test_is_not_class<void() const& noexcept>();
    test_is_not_class<void() const&& noexcept>();
    test_is_not_class<void() volatile noexcept>();
    test_is_not_class<void() volatile& noexcept>();
    test_is_not_class<void() volatile&& noexcept>();
    test_is_not_class<void() const volatile noexcept>();
    test_is_not_class<void() const volatile& noexcept>();
    test_is_not_class<void() const volatile&& noexcept>();

    test_is_not_class<void(int)>();
    test_is_not_class<void(int)&>();
    test_is_not_class<void(int) &&>();
    test_is_not_class<void(int) const>();
    test_is_not_class<void(int) const&>();
    test_is_not_class<void(int) const&&>();
    test_is_not_class<void(int) volatile>();
    test_is_not_class<void(int) volatile&>();
    test_is_not_class<void(int) volatile&&>();
    test_is_not_class<void(int) const volatile>();
    test_is_not_class<void(int) const volatile&>();
    test_is_not_class<void(int) const volatile&&>();
    test_is_not_class<void(int) noexcept>();
    test_is_not_class<void(int)& noexcept>();
    test_is_not_class<void(int)&& noexcept>();
    test_is_not_class<void(int) const noexcept>();
    test_is_not_class<void(int) const& noexcept>();
    test_is_not_class<void(int) const&& noexcept>();
    test_is_not_class<void(int) volatile noexcept>();
    test_is_not_class<void(int) volatile& noexcept>();
    test_is_not_class<void(int) volatile&& noexcept>();
    test_is_not_class<void(int) const volatile noexcept>();
    test_is_not_class<void(int) const volatile& noexcept>();
    test_is_not_class<void(int) const volatile&& noexcept>();

    test_is_not_class<void(...)>();
    test_is_not_class<void(...)&>();
    test_is_not_class<void(...) &&>();
    test_is_not_class<void(...) const>();
    test_is_not_class<void(...) const&>();
    test_is_not_class<void(...) const&&>();
    test_is_not_class<void(...) volatile>();
    test_is_not_class<void(...) volatile&>();
    test_is_not_class<void(...) volatile&&>();
    test_is_not_class<void(...) const volatile>();
    test_is_not_class<void(...) const volatile&>();
    test_is_not_class<void(...) const volatile&&>();
    test_is_not_class<void(...) noexcept>();
    test_is_not_class<void(...)& noexcept>();
    test_is_not_class<void(...)&& noexcept>();
    test_is_not_class<void(...) const noexcept>();
    test_is_not_class<void(...) const& noexcept>();
    test_is_not_class<void(...) const&& noexcept>();
    test_is_not_class<void(...) volatile noexcept>();
    test_is_not_class<void(...) volatile& noexcept>();
    test_is_not_class<void(...) volatile&& noexcept>();
    test_is_not_class<void(...) const volatile noexcept>();
    test_is_not_class<void(...) const volatile& noexcept>();
    test_is_not_class<void(...) const volatile&& noexcept>();

    test_is_not_class<void(int, ...)>();
    test_is_not_class<void(int, ...)&>();
    test_is_not_class<void(int, ...) &&>();
    test_is_not_class<void(int, ...) const>();
    test_is_not_class<void(int, ...) const&>();
    test_is_not_class<void(int, ...) const&&>();
    test_is_not_class<void(int, ...) volatile>();
    test_is_not_class<void(int, ...) volatile&>();
    test_is_not_class<void(int, ...) volatile&&>();
    test_is_not_class<void(int, ...) const volatile>();
    test_is_not_class<void(int, ...) const volatile&>();
    test_is_not_class<void(int, ...) const volatile&&>();
    test_is_not_class<void(int, ...) noexcept>();
    test_is_not_class<void(int, ...)& noexcept>();
    test_is_not_class<void(int, ...)&& noexcept>();
    test_is_not_class<void(int, ...) const noexcept>();
    test_is_not_class<void(int, ...) const& noexcept>();
    test_is_not_class<void(int, ...) const&& noexcept>();
    test_is_not_class<void(int, ...) volatile noexcept>();
    test_is_not_class<void(int, ...) volatile& noexcept>();
    test_is_not_class<void(int, ...) volatile&& noexcept>();
    test_is_not_class<void(int, ...) const volatile noexcept>();
    test_is_not_class<void(int, ...) const volatile& noexcept>();
    test_is_not_class<void(int, ...) const volatile&& noexcept>();

    test_is_not_class<int()>();
    test_is_not_class<int()&>();
    test_is_not_class<int() &&>();
    test_is_not_class<int() const>();
    test_is_not_class<int() const&>();
    test_is_not_class<int() const&&>();
    test_is_not_class<int() volatile>();
    test_is_not_class<int() volatile&>();
    test_is_not_class<int() volatile&&>();
    test_is_not_class<int() const volatile>();
    test_is_not_class<int() const volatile&>();
    test_is_not_class<int() const volatile&&>();
    test_is_not_class<int() noexcept>();
    test_is_not_class<int()& noexcept>();
    test_is_not_class<int()&& noexcept>();
    test_is_not_class<int() const noexcept>();
    test_is_not_class<int() const& noexcept>();
    test_is_not_class<int() const&& noexcept>();
    test_is_not_class<int() volatile noexcept>();
    test_is_not_class<int() volatile& noexcept>();
    test_is_not_class<int() volatile&& noexcept>();
    test_is_not_class<int() const volatile noexcept>();
    test_is_not_class<int() const volatile& noexcept>();
    test_is_not_class<int() const volatile&& noexcept>();

    test_is_not_class<int(int)>();
    test_is_not_class<int(int)&>();
    test_is_not_class<int(int) &&>();
    test_is_not_class<int(int) const>();
    test_is_not_class<int(int) const&>();
    test_is_not_class<int(int) const&&>();
    test_is_not_class<int(int) volatile>();
    test_is_not_class<int(int) volatile&>();
    test_is_not_class<int(int) volatile&&>();
    test_is_not_class<int(int) const volatile>();
    test_is_not_class<int(int) const volatile&>();
    test_is_not_class<int(int) const volatile&&>();
    test_is_not_class<int(int) noexcept>();
    test_is_not_class<int(int)& noexcept>();
    test_is_not_class<int(int)&& noexcept>();
    test_is_not_class<int(int) const noexcept>();
    test_is_not_class<int(int) const& noexcept>();
    test_is_not_class<int(int) const&& noexcept>();
    test_is_not_class<int(int) volatile noexcept>();
    test_is_not_class<int(int) volatile& noexcept>();
    test_is_not_class<int(int) volatile&& noexcept>();
    test_is_not_class<int(int) const volatile noexcept>();
    test_is_not_class<int(int) const volatile& noexcept>();
    test_is_not_class<int(int) const volatile&& noexcept>();

    test_is_not_class<int(...)>();
    test_is_not_class<int(...)&>();
    test_is_not_class<int(...) &&>();
    test_is_not_class<int(...) const>();
    test_is_not_class<int(...) const&>();
    test_is_not_class<int(...) const&&>();
    test_is_not_class<int(...) volatile>();
    test_is_not_class<int(...) volatile&>();
    test_is_not_class<int(...) volatile&&>();
    test_is_not_class<int(...) const volatile>();
    test_is_not_class<int(...) const volatile&>();
    test_is_not_class<int(...) const volatile&&>();
    test_is_not_class<int(...) noexcept>();
    test_is_not_class<int(...)& noexcept>();
    test_is_not_class<int(...)&& noexcept>();
    test_is_not_class<int(...) const noexcept>();
    test_is_not_class<int(...) const& noexcept>();
    test_is_not_class<int(...) const&& noexcept>();
    test_is_not_class<int(...) volatile noexcept>();
    test_is_not_class<int(...) volatile& noexcept>();
    test_is_not_class<int(...) volatile&& noexcept>();
    test_is_not_class<int(...) const volatile noexcept>();
    test_is_not_class<int(...) const volatile& noexcept>();
    test_is_not_class<int(...) const volatile&& noexcept>();

    test_is_not_class<int(int, ...)>();
    test_is_not_class<int(int, ...)&>();
    test_is_not_class<int(int, ...) &&>();
    test_is_not_class<int(int, ...) const>();
    test_is_not_class<int(int, ...) const&>();
    test_is_not_class<int(int, ...) const&&>();
    test_is_not_class<int(int, ...) volatile>();
    test_is_not_class<int(int, ...) volatile&>();
    test_is_not_class<int(int, ...) volatile&&>();
    test_is_not_class<int(int, ...) const volatile>();
    test_is_not_class<int(int, ...) const volatile&>();
    test_is_not_class<int(int, ...) const volatile&&>();
    test_is_not_class<int(int, ...) noexcept>();
    test_is_not_class<int(int, ...)& noexcept>();
    test_is_not_class<int(int, ...)&& noexcept>();
    test_is_not_class<int(int, ...) const noexcept>();
    test_is_not_class<int(int, ...) const& noexcept>();
    test_is_not_class<int(int, ...) const&& noexcept>();
    test_is_not_class<int(int, ...) volatile noexcept>();
    test_is_not_class<int(int, ...) volatile& noexcept>();
    test_is_not_class<int(int, ...) volatile&& noexcept>();
    test_is_not_class<int(int, ...) const volatile noexcept>();
    test_is_not_class<int(int, ...) const volatile& noexcept>();
    test_is_not_class<int(int, ...) const volatile&& noexcept>();

    test_is_not_class<void (*)()>();
    test_is_not_class<void (*)() noexcept>();

    test_is_not_class<void (*)(int)>();
    test_is_not_class<void (*)(int) noexcept>();

    test_is_not_class<void (*)(...)>();
    test_is_not_class<void (*)(...) noexcept>();

    test_is_not_class<void (*)(int, ...)>();
    test_is_not_class<void (*)(int, ...) noexcept>();

    test_is_not_class<int (*)()>();
    test_is_not_class<int (*)() noexcept>();

    test_is_not_class<int (*)(int)>();
    test_is_not_class<int (*)(int) noexcept>();

    test_is_not_class<int (*)(...)>();
    test_is_not_class<int (*)(...) noexcept>();

    test_is_not_class<int (*)(int, ...)>();
    test_is_not_class<int (*)(int, ...) noexcept>();

    test_is_not_class<void (&)()>();
    test_is_not_class<void (&)() noexcept>();

    test_is_not_class<void (&)(int)>();
    test_is_not_class<void (&)(int) noexcept>();

    test_is_not_class<void (&)(...)>();
    test_is_not_class<void (&)(...) noexcept>();

    test_is_not_class<void (&)(int, ...)>();
    test_is_not_class<void (&)(int, ...) noexcept>();

    test_is_not_class<int (&)()>();
    test_is_not_class<int (&)() noexcept>();

    test_is_not_class<int (&)(int)>();
    test_is_not_class<int (&)(int) noexcept>();

    test_is_not_class<int (&)(...)>();
    test_is_not_class<int (&)(...) noexcept>();

    test_is_not_class<int (&)(int, ...)>();
    test_is_not_class<int (&)(int, ...) noexcept>();

    test_is_not_class<void(&&)()>();
    test_is_not_class<void(&&)() noexcept>();

    test_is_not_class<void(&&)(int)>();
    test_is_not_class<void(&&)(int) noexcept>();

    test_is_not_class<void(&&)(...)>();
    test_is_not_class<void(&&)(...) noexcept>();

    test_is_not_class<void(&&)(int, ...)>();
    test_is_not_class<void(&&)(int, ...) noexcept>();

    test_is_not_class<int(&&)()>();
    test_is_not_class<int(&&)() noexcept>();

    test_is_not_class<int(&&)(int)>();
    test_is_not_class<int(&&)(int) noexcept>();

    test_is_not_class<int(&&)(...)>();
    test_is_not_class<int(&&)(...) noexcept>();

    test_is_not_class<int(&&)(int, ...)>();
    test_is_not_class<int(&&)(int, ...) noexcept>();

    test_is_not_class<void (class_type::*)()>();
    test_is_not_class<void (class_type::*)()&>();
    test_is_not_class<void (class_type::*)() &&>();
    test_is_not_class<void (class_type::*)() const>();
    test_is_not_class<void (class_type::*)() const&>();
    test_is_not_class<void (class_type::*)() const&&>();
    test_is_not_class<void (class_type::*)() noexcept>();
    test_is_not_class<void (class_type::*)()& noexcept>();
    test_is_not_class<void (class_type::*)()&& noexcept>();
    test_is_not_class<void (class_type::*)() const noexcept>();
    test_is_not_class<void (class_type::*)() const& noexcept>();
    test_is_not_class<void (class_type::*)() const&& noexcept>();

    test_is_not_class<void (class_type::*)(int)>();
    test_is_not_class<void (class_type::*)(int)&>();
    test_is_not_class<void (class_type::*)(int) &&>();
    test_is_not_class<void (class_type::*)(int) const>();
    test_is_not_class<void (class_type::*)(int) const&>();
    test_is_not_class<void (class_type::*)(int) const&&>();
    test_is_not_class<void (class_type::*)(int) noexcept>();
    test_is_not_class<void (class_type::*)(int)& noexcept>();
    test_is_not_class<void (class_type::*)(int)&& noexcept>();
    test_is_not_class<void (class_type::*)(int) const noexcept>();
    test_is_not_class<void (class_type::*)(int) const& noexcept>();
    test_is_not_class<void (class_type::*)(int) const&& noexcept>();

    test_is_not_class<void (class_type::*)(...)>();
    test_is_not_class<void (class_type::*)(...)&>();
    test_is_not_class<void (class_type::*)(...) &&>();
    test_is_not_class<void (class_type::*)(...) const>();
    test_is_not_class<void (class_type::*)(...) const&>();
    test_is_not_class<void (class_type::*)(...) const&&>();
    test_is_not_class<void (class_type::*)(...) noexcept>();
    test_is_not_class<void (class_type::*)(...)& noexcept>();
    test_is_not_class<void (class_type::*)(...)&& noexcept>();
    test_is_not_class<void (class_type::*)(...) const noexcept>();
    test_is_not_class<void (class_type::*)(...) const& noexcept>();
    test_is_not_class<void (class_type::*)(...) const&& noexcept>();

    test_is_not_class<void (class_type::*)(int, ...)>();
    test_is_not_class<void (class_type::*)(int, ...)&>();
    test_is_not_class<void (class_type::*)(int, ...) &&>();
    test_is_not_class<void (class_type::*)(int, ...) const>();
    test_is_not_class<void (class_type::*)(int, ...) const&>();
    test_is_not_class<void (class_type::*)(int, ...) const&&>();
    test_is_not_class<void (class_type::*)(int, ...) noexcept>();
    test_is_not_class<void (class_type::*)(int, ...)& noexcept>();
    test_is_not_class<void (class_type::*)(int, ...)&& noexcept>();
    test_is_not_class<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_class<void (class_type::*)(int, ...) const& noexcept>();
    test_is_not_class<void (class_type::*)(int, ...) const&& noexcept>();

    test_is_not_class<int (class_type::*)()>();
    test_is_not_class<int (class_type::*)()&>();
    test_is_not_class<int (class_type::*)() &&>();
    test_is_not_class<int (class_type::*)() const>();
    test_is_not_class<int (class_type::*)() const&>();
    test_is_not_class<int (class_type::*)() const&&>();
    test_is_not_class<int (class_type::*)() noexcept>();
    test_is_not_class<int (class_type::*)()& noexcept>();
    test_is_not_class<int (class_type::*)()&& noexcept>();
    test_is_not_class<int (class_type::*)() const noexcept>();
    test_is_not_class<int (class_type::*)() const& noexcept>();
    test_is_not_class<int (class_type::*)() const&& noexcept>();

    test_is_not_class<int (class_type::*)(int)>();
    test_is_not_class<int (class_type::*)(int)&>();
    test_is_not_class<int (class_type::*)(int) &&>();
    test_is_not_class<int (class_type::*)(int) const>();
    test_is_not_class<int (class_type::*)(int) const&>();
    test_is_not_class<int (class_type::*)(int) const&&>();
    test_is_not_class<int (class_type::*)(int) noexcept>();
    test_is_not_class<int (class_type::*)(int)& noexcept>();
    test_is_not_class<int (class_type::*)(int)&& noexcept>();
    test_is_not_class<int (class_type::*)(int) const noexcept>();
    test_is_not_class<int (class_type::*)(int) const& noexcept>();
    test_is_not_class<int (class_type::*)(int) const&& noexcept>();

    test_is_not_class<int (class_type::*)(...)>();
    test_is_not_class<int (class_type::*)(...)&>();
    test_is_not_class<int (class_type::*)(...) &&>();
    test_is_not_class<int (class_type::*)(...) const>();
    test_is_not_class<int (class_type::*)(...) const&>();
    test_is_not_class<int (class_type::*)(...) const&&>();
    test_is_not_class<int (class_type::*)(...) noexcept>();
    test_is_not_class<int (class_type::*)(...)& noexcept>();
    test_is_not_class<int (class_type::*)(...)&& noexcept>();
    test_is_not_class<int (class_type::*)(...) const noexcept>();
    test_is_not_class<int (class_type::*)(...) const& noexcept>();
    test_is_not_class<int (class_type::*)(...) const&& noexcept>();

    test_is_not_class<int (class_type::*)(int, ...)>();
    test_is_not_class<int (class_type::*)(int, ...)&>();
    test_is_not_class<int (class_type::*)(int, ...) &&>();
    test_is_not_class<int (class_type::*)(int, ...) const>();
    test_is_not_class<int (class_type::*)(int, ...) const&>();
    test_is_not_class<int (class_type::*)(int, ...) const&&>();
    test_is_not_class<int (class_type::*)(int, ...) noexcept>();
    test_is_not_class<int (class_type::*)(int, ...)& noexcept>();
    test_is_not_class<int (class_type::*)(int, ...)&& noexcept>();
    test_is_not_class<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_class<int (class_type::*)(int, ...) const& noexcept>();
    test_is_not_class<int (class_type::*)(int, ...) const&& noexcept>();
}
