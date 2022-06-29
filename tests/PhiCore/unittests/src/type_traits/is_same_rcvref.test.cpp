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
#include <phi/type_traits/is_same_rcvref.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT, typename OtherT>
void test_is_same_rcvref_impl2()
{
    STATIC_REQUIRE(phi::is_same_rcvref<TypeT, OtherT>::value);
    STATIC_REQUIRE(phi::is_same_rcvref<OtherT, TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref<TypeT, OtherT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref<OtherT, TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_rcvref_v<TypeT, OtherT>);
    STATIC_REQUIRE(phi::is_same_rcvref_v<OtherT, TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref_v<TypeT, OtherT>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref_v<OtherT, TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same_rcvref<TypeT, OtherT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same_rcvref<TypeT, OtherT>);
}

template <typename TypeT, typename OtherT>
void test_is_same_rcvref_impl()
{
    test_is_same_rcvref_impl2<TypeT, OtherT>();
    test_is_same_rcvref_impl2<TypeT, const OtherT>();
    test_is_same_rcvref_impl2<TypeT, volatile OtherT>();
    test_is_same_rcvref_impl2<TypeT, const volatile OtherT>();

    test_is_same_rcvref_impl2<const TypeT, OtherT>();
    test_is_same_rcvref_impl2<const TypeT, const OtherT>();
    test_is_same_rcvref_impl2<const TypeT, volatile OtherT>();
    test_is_same_rcvref_impl2<const TypeT, const volatile OtherT>();

    test_is_same_rcvref_impl2<volatile TypeT, OtherT>();
    test_is_same_rcvref_impl2<volatile TypeT, const OtherT>();
    test_is_same_rcvref_impl2<volatile TypeT, volatile OtherT>();
    test_is_same_rcvref_impl2<volatile TypeT, const volatile OtherT>();

    test_is_same_rcvref_impl2<const volatile TypeT, OtherT>();
    test_is_same_rcvref_impl2<const volatile TypeT, const OtherT>();
    test_is_same_rcvref_impl2<const volatile TypeT, volatile OtherT>();
    test_is_same_rcvref_impl2<const volatile TypeT, const volatile OtherT>();
}

template <typename TypeT, typename OtherT = TypeT>
void test_is_same_rcvref()
{
    test_is_same_rcvref_impl<TypeT, OtherT>();
    test_is_same_rcvref_impl<TypeT, phi::add_lvalue_reference_t<OtherT>>();
    test_is_same_rcvref_impl<TypeT, phi::add_rvalue_reference_t<OtherT>>();

    test_is_same_rcvref_impl<phi::add_lvalue_reference_t<TypeT>, OtherT>();
    test_is_same_rcvref_impl<phi::add_lvalue_reference_t<TypeT>,
                             phi::add_lvalue_reference_t<OtherT>>();
    test_is_same_rcvref_impl<phi::add_lvalue_reference_t<TypeT>,
                             phi::add_rvalue_reference_t<OtherT>>();

    test_is_same_rcvref_impl<phi::add_rvalue_reference_t<TypeT>, OtherT>();
    test_is_same_rcvref_impl<phi::add_rvalue_reference_t<TypeT>,
                             phi::add_lvalue_reference_t<OtherT>>();
    test_is_same_rcvref_impl<phi::add_rvalue_reference_t<TypeT>,
                             phi::add_rvalue_reference_t<OtherT>>();
}

template <typename TypeT, typename OtherT>
void test_is_not_same_rcvref()
{
    STATIC_REQUIRE_FALSE(phi::is_same_rcvref<TypeT, OtherT>::value);
    STATIC_REQUIRE_FALSE(phi::is_same_rcvref<OtherT, TypeT>::value);
    STATIC_REQUIRE(phi::is_not_same_rcvref<TypeT, OtherT>::value);
    STATIC_REQUIRE(phi::is_not_same_rcvref<OtherT, TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_same_rcvref_v<TypeT, OtherT>);
    STATIC_REQUIRE_FALSE(phi::is_same_rcvref_v<OtherT, TypeT>);
    STATIC_REQUIRE(phi::is_not_same_rcvref_v<TypeT, OtherT>);
    STATIC_REQUIRE(phi::is_not_same_rcvref_v<OtherT, TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same_rcvref<TypeT, OtherT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same_rcvref<TypeT, OtherT>);
}

template <typename TypeT>
struct OverloadTest
{
    void fn(phi::is_same_rcvref<TypeT, int> /*unused*/)
    {}
    void fn(phi::false_type /*unused*/)
    {}
    void x()
    {
        fn(phi::false_type());
    }
};

struct A; // incomplete

TEST_CASE("is_same_rcvref")
{
    test_is_not_same_rcvref<int, void>();
    test_is_not_same_rcvref<void, class_type>();
    test_is_not_same_rcvref<class_type, int*>();
    test_is_not_same_rcvref<int*, int&>();

    OverloadTest<char> test;
    (void)test;

    test_is_same_rcvref<void>();
    test_is_same_rcvref<phi::nullptr_t>();
    test_is_same_rcvref<bool>();
    test_is_same_rcvref<char>();
    test_is_same_rcvref<signed char>();
    test_is_same_rcvref<unsigned char>();
    test_is_same_rcvref<short>();
    test_is_same_rcvref<unsigned short>();
    test_is_same_rcvref<int>();
    test_is_same_rcvref<unsigned int>();
    test_is_same_rcvref<long>();
    test_is_same_rcvref<unsigned long>();
    test_is_same_rcvref<long long>();
    test_is_same_rcvref<unsigned long long>();
    test_is_same_rcvref<float>();
    test_is_same_rcvref<double>();
    test_is_same_rcvref<long double>();
    test_is_same_rcvref<char8_t>();
    test_is_same_rcvref<char16_t>();
    test_is_same_rcvref<char32_t>();
    test_is_same_rcvref<wchar_t>();

    test_is_same_rcvref<phi::boolean>();
    test_is_same_rcvref<phi::integer<signed char>>();
    test_is_same_rcvref<phi::integer<unsigned char>>();
    test_is_same_rcvref<phi::integer<short>>();
    test_is_same_rcvref<phi::integer<unsigned short>>();
    test_is_same_rcvref<phi::integer<int>>();
    test_is_same_rcvref<phi::integer<unsigned int>>();
    test_is_same_rcvref<phi::integer<long>>();
    test_is_same_rcvref<phi::integer<unsigned long>>();
    test_is_same_rcvref<phi::integer<long long>>();
    test_is_same_rcvref<phi::integer<unsigned long long>>();
    test_is_same_rcvref<phi::floating_point<float>>();
    test_is_same_rcvref<phi::floating_point<double>>();
    test_is_same_rcvref<phi::floating_point<long double>>();

    test_is_same_rcvref<std::vector<int>>();
    test_is_same_rcvref<phi::scope_ptr<int>>();

    test_is_same_rcvref<int&>();
    test_is_same_rcvref<const int&>();
    test_is_same_rcvref<volatile int&>();
    test_is_same_rcvref<const volatile int&>();
    test_is_same_rcvref<int&&>();
    test_is_same_rcvref<const int&&>();
    test_is_same_rcvref<volatile int&&>();
    test_is_same_rcvref<const volatile int&&>();
    test_is_same_rcvref<int*>();
    test_is_same_rcvref<const int*>();
    test_is_same_rcvref<volatile int*>();
    test_is_same_rcvref<const volatile int*>();
    test_is_same_rcvref<int**>();
    test_is_same_rcvref<const int**>();
    test_is_same_rcvref<volatile int**>();
    test_is_same_rcvref<const volatile int**>();
    test_is_same_rcvref<int*&>();
    test_is_same_rcvref<const int*&>();
    test_is_same_rcvref<volatile int*&>();
    test_is_same_rcvref<const volatile int*&>();
    test_is_same_rcvref<int*&&>();
    test_is_same_rcvref<const int*&&>();
    test_is_same_rcvref<volatile int*&&>();
    test_is_same_rcvref<const volatile int*&&>();
    test_is_same_rcvref<void*>();
    test_is_same_rcvref<char[3]>();
    test_is_same_rcvref<char[]>();
    test_is_same_rcvref<char* [3]>();
    test_is_same_rcvref<char*[]>();
    test_is_same_rcvref<int(*)[3]>();
    test_is_same_rcvref<int(*)[]>();
    test_is_same_rcvref<int(&)[3]>();
    test_is_same_rcvref<int(&)[]>();
    test_is_same_rcvref<int(&&)[3]>();
    test_is_same_rcvref<int(&&)[]>();
    test_is_same_rcvref<char[3][2]>();
    test_is_same_rcvref<char[][2]>();
    test_is_same_rcvref<char* [3][2]>();
    test_is_same_rcvref<char*[][2]>();
    test_is_same_rcvref<int(*)[3][2]>();
    test_is_same_rcvref<int(*)[][2]>();
    test_is_same_rcvref<int(&)[3][2]>();
    test_is_same_rcvref<int(&)[][2]>();
    test_is_same_rcvref<int(&&)[3][2]>();
    test_is_same_rcvref<int(&&)[][2]>();
    test_is_same_rcvref<class_type>();
    test_is_same_rcvref<class_type[]>();
    test_is_same_rcvref<class_type[2]>();
    test_is_same_rcvref<template_type<void>>();
    test_is_same_rcvref<template_type<int>>();
    test_is_same_rcvref<template_type<class_type>>();
    test_is_same_rcvref<template_type<incomplete_type>>();
    test_is_same_rcvref<variadic_template<>>();
    test_is_same_rcvref<variadic_template<void>>();
    test_is_same_rcvref<variadic_template<int>>();
    test_is_same_rcvref<variadic_template<class_type>>();
    test_is_same_rcvref<variadic_template<incomplete_type>>();
    test_is_same_rcvref<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_same_rcvref<public_derived_from<base>>();
    test_is_same_rcvref<public_derived_from<derived>>();
    test_is_same_rcvref<public_derived_from<class_type>>();
    test_is_same_rcvref<private_derived_from<base>>();
    test_is_same_rcvref<private_derived_from<derived>>();
    test_is_same_rcvref<private_derived_from<class_type>>();
    test_is_same_rcvref<protected_derived_from<base>>();
    test_is_same_rcvref<protected_derived_from<derived>>();
    test_is_same_rcvref<protected_derived_from<class_type>>();
    test_is_same_rcvref<virtual_derived_from<base>>();
    test_is_same_rcvref<virtual_derived_from<derived>>();
    test_is_same_rcvref<virtual_derived_from<class_type>>();
    test_is_same_rcvref<union_type>();
    test_is_same_rcvref<non_empty_union>();
    test_is_same_rcvref<non_trivial_union>();
    test_is_same_rcvref<empty>();
    test_is_same_rcvref<not_empty>();
    test_is_same_rcvref<non_trivial>();
    test_is_same_rcvref<bit_zero>();
    test_is_same_rcvref<bit_one>();
    test_is_same_rcvref<base>();
    test_is_same_rcvref<derived>();
    test_is_same_rcvref<non_empty_base>();
    test_is_same_rcvref<empty_base>();
    test_is_same_rcvref<virtual_base>();
    test_is_same_rcvref<polymorphic>();
    test_is_same_rcvref<derived_polymorphic>();
    test_is_same_rcvref<abstract>();
    test_is_same_rcvref<public_abstract>();
    test_is_same_rcvref<private_abstract>();
    test_is_same_rcvref<protected_abstract>();
    test_is_same_rcvref<abstract_template<int>>();
    test_is_same_rcvref<abstract_template<double>>();
    test_is_same_rcvref<abstract_template<class_type>>();
    test_is_same_rcvref<abstract_template<incomplete_type>>();
    test_is_same_rcvref<public_abstract_deleted_destructor>();
    test_is_same_rcvref<protected_abstract_deleted_destructor>();
    test_is_same_rcvref<private_abstract_deleted_destructor>();
    test_is_same_rcvref<final_type>();
    test_is_same_rcvref<final_derived>();
    test_is_same_rcvref<public_destructor>();
    test_is_same_rcvref<protected_destructor>();
    test_is_same_rcvref<private_destructor>();
    test_is_same_rcvref<virtual_public_destructor>();
    test_is_same_rcvref<virtual_protected_destructor>();
    test_is_same_rcvref<virtual_private_destructor>();
    test_is_same_rcvref<pure_public_destructor>();
    test_is_same_rcvref<pure_protected_destructor>();
    test_is_same_rcvref<pure_private_destructor>();
    test_is_same_rcvref<deleted_public_destructor>();
    test_is_same_rcvref<deleted_protected_destructor>();
    test_is_same_rcvref<deleted_private_destructor>();
    test_is_same_rcvref<deleted_virtual_public_destructor>();
    test_is_same_rcvref<deleted_virtual_protected_destructor>();
    test_is_same_rcvref<deleted_virtual_private_destructor>();
    test_is_same_rcvref<explicit_class>();
    test_is_same_rcvref<nothrow_explicit_class>();
    test_is_same_rcvref<throw_explicit_class>();
    test_is_same_rcvref<throw_default_class>();
    test_is_same_rcvref<throw_copy_constructible_class>();
    test_is_same_rcvref<throw_move_constructible_class>();
    test_is_same_rcvref<throw_destructor>();
    test_is_same_rcvref<noexcept_explicit_class>();
    test_is_same_rcvref<except_explicit_class>();
    test_is_same_rcvref<noexcept_default_class>();
    test_is_same_rcvref<except_default_class>();
    test_is_same_rcvref<noexcept_copy_constructible_class>();
    test_is_same_rcvref<except_copy_constructible_class>();
    test_is_same_rcvref<noexcept_move_constructible_class>();
    test_is_same_rcvref<except_move_constructible_class>();
    test_is_same_rcvref<noexcept_copy_assign_class>();
    test_is_same_rcvref<except_copy_assign_class>();
    test_is_same_rcvref<noexcept_move_assign_class>();
    test_is_same_rcvref<except_move_assign_class>();
    test_is_same_rcvref<deleted_copy_assign_class>();
    test_is_same_rcvref<deleted_move_assign_class>();
    test_is_same_rcvref<noexcept_move_constructible_and_assignable_class>();
    test_is_same_rcvref<except_move_constructible_noexcept_move_assign_class>();
    test_is_same_rcvref<noexcept_move_constructible_except_move_assign_class>();
    test_is_same_rcvref<except_move_constructible_and_assign_class>();
    test_is_same_rcvref<implicit_to<int>>();
    test_is_same_rcvref<implicit_to<float>>();
    test_is_same_rcvref<implicit_to<class_type>>();
    test_is_same_rcvref<deleted_implicit_to<int>>();
    test_is_same_rcvref<deleted_implicit_to<float>>();
    test_is_same_rcvref<deleted_implicit_to<class_type>>();
    test_is_same_rcvref<explicit_to<int>>();
    test_is_same_rcvref<explicit_to<float>>();
    test_is_same_rcvref<explicit_to<class_type>>();
    test_is_same_rcvref<deleted_explicit_to<int>>();
    test_is_same_rcvref<deleted_explicit_to<float>>();
    test_is_same_rcvref<deleted_explicit_to<class_type>>();
    test_is_same_rcvref<ellipsis>();
    test_is_same_rcvref<deleted_ellipsis>();
    test_is_same_rcvref<copy_constructible_only_type>();
    test_is_same_rcvref<move_constructible_only_type>();
    test_is_same_rcvref<overloaded_operators>();
    test_is_same_rcvref<public_int_member>();
    test_is_same_rcvref<protected_int_member>();
    test_is_same_rcvref<private_int_member>();
    test_is_same_rcvref<public_static_int_member>();
    test_is_same_rcvref<protected_static_int_member>();
    test_is_same_rcvref<private_static_int_member>();
    test_is_same_rcvref<public_template_member<int>>();
    test_is_same_rcvref<public_template_member<float>>();
    test_is_same_rcvref<public_template_member<class_type>>();
    test_is_same_rcvref<protected_template_member<int>>();
    test_is_same_rcvref<protected_template_member<float>>();
    test_is_same_rcvref<protected_template_member<class_type>>();
    test_is_same_rcvref<private_template_member<int>>();
    test_is_same_rcvref<private_template_member<float>>();
    test_is_same_rcvref<private_template_member<class_type>>();
    test_is_same_rcvref<public_static_template_member<int>>();
    test_is_same_rcvref<public_static_template_member<float>>();
    test_is_same_rcvref<public_static_template_member<class_type>>();
    test_is_same_rcvref<protected_static_template_member<int>>();
    test_is_same_rcvref<protected_static_template_member<float>>();
    test_is_same_rcvref<protected_static_template_member<class_type>>();
    test_is_same_rcvref<private_static_template_member<int>>();
    test_is_same_rcvref<private_static_template_member<float>>();
    test_is_same_rcvref<private_static_template_member<class_type>>();
    test_is_same_rcvref<cannot_instantiate<int>>();
    test_is_same_rcvref<cannot_instantiate<float>>();
    test_is_same_rcvref<cannot_instantiate<class_type>>();
    test_is_same_rcvref<natural_alignment>();
    test_is_same_rcvref<Enum>();
    test_is_same_rcvref<EnumSigned>();
    test_is_same_rcvref<EnumUnsigned>();
    test_is_same_rcvref<EnumClass>();
    test_is_same_rcvref<EnumStruct>();
    test_is_same_rcvref<function_type>();
    test_is_same_rcvref<function_ptr>();
    test_is_same_rcvref<member_object_ptr>();
    test_is_same_rcvref<member_function_ptr>();
    test_is_same_rcvref<lambda_type>();
    test_is_same_rcvref<lambda_noexcept_type>();
    test_is_same_rcvref<lambda_throws_type>();
    test_is_same_rcvref<incomplete_type>();
    test_is_same_rcvref<incomplete_template<void>>();
    test_is_same_rcvref<incomplete_template<int>>();
    test_is_same_rcvref<incomplete_template<class_type>>();
    test_is_same_rcvref<incomplete_template<incomplete_type>>();
    test_is_same_rcvref<incomplete_variadic_template<>>();
    test_is_same_rcvref<incomplete_variadic_template<void>>();
    test_is_same_rcvref<incomplete_variadic_template<int>>();
    test_is_same_rcvref<incomplete_variadic_template<class_type>>();
    test_is_same_rcvref<incomplete_variadic_template<incomplete_type>>();
    test_is_same_rcvref<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_same_rcvref<incomplete_union>();
    test_is_same_rcvref<IncompleteEnumSigned>();
    test_is_same_rcvref<IncompleteEnumUnsigned>();
    test_is_same_rcvref<IncompleteEnumClass>();
    test_is_same_rcvref<IncompleteEnumStruct>();
    test_is_same_rcvref<int class_type::*>();
    test_is_same_rcvref<float class_type::*>();
    test_is_same_rcvref<void * class_type::*>();
    test_is_same_rcvref<int * class_type::*>();
    test_is_same_rcvref<Enum class_type::*>();
    test_is_same_rcvref<not_empty class_type::*>();
    test_is_same_rcvref<int class_type::*&>();
    test_is_same_rcvref<float class_type::*&>();
    test_is_same_rcvref<void * class_type::*&>();
    test_is_same_rcvref<int * class_type::*&>();
    test_is_same_rcvref<Enum class_type::*&>();
    test_is_same_rcvref<not_empty class_type::*&>();
    test_is_same_rcvref<int class_type::*&&>();
    test_is_same_rcvref<float class_type::*&&>();
    test_is_same_rcvref<void * class_type::*&&>();
    test_is_same_rcvref<int * class_type::*&&>();
    test_is_same_rcvref<Enum class_type::*&&>();
    test_is_same_rcvref<not_empty class_type::*&&>();
    test_is_same_rcvref<non_default_constructible>();
    test_is_same_rcvref<non_copy_constructible>();
    test_is_same_rcvref<non_move_constructible>();
    test_is_same_rcvref<non_copy_assignable>();
    test_is_same_rcvref<non_move_assignable>();
    test_is_same_rcvref<non_assignable>();
    test_is_same_rcvref<non_copyable>();
    test_is_same_rcvref<non_moveable>();
    test_is_same_rcvref<non_constructible>();
    test_is_same_rcvref<non_destructible>();
    test_is_same_rcvref<tracked>();
    test_is_same_rcvref<trap_constructible>();
    test_is_same_rcvref<trap_implicit_conversion>();
    test_is_same_rcvref<trap_comma>();
    test_is_same_rcvref<trap_call>();
    test_is_same_rcvref<trap_self_assign>();
    test_is_same_rcvref<trap_deref>();
    test_is_same_rcvref<trap_array_subscript>();

#if PHI_HAS_EXTENSION_ZERO_SIZE_ARRAY() && PHI_COMPILER_IS_NOT(MINGW)
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wzero-length-array")
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wpedantic")

    test_is_same_rcvref<int[0]>();

    PHI_GCC_SUPPRESS_WARNING_POP()
    PHI_CLANG_SUPPRESS_WARNING_POP()
#endif

    test_is_same_rcvref<void()>();
    test_is_same_rcvref<void()&>();
    test_is_same_rcvref<void() &&>();
    test_is_same_rcvref<void() const>();
    test_is_same_rcvref<void() const&>();
    test_is_same_rcvref<void() const&&>();
    test_is_same_rcvref<void() volatile>();
    test_is_same_rcvref<void() volatile&>();
    test_is_same_rcvref<void() volatile&&>();
    test_is_same_rcvref<void() const volatile>();
    test_is_same_rcvref<void() const volatile&>();
    test_is_same_rcvref<void() const volatile&&>();
    test_is_same_rcvref<void() noexcept>();
    test_is_same_rcvref<void()& noexcept>();
    test_is_same_rcvref<void()&& noexcept>();
    test_is_same_rcvref<void() const noexcept>();
    test_is_same_rcvref<void() const& noexcept>();
    test_is_same_rcvref<void() const&& noexcept>();
    test_is_same_rcvref<void() volatile noexcept>();
    test_is_same_rcvref<void() volatile& noexcept>();
    test_is_same_rcvref<void() volatile&& noexcept>();
    test_is_same_rcvref<void() const volatile noexcept>();
    test_is_same_rcvref<void() const volatile& noexcept>();
    test_is_same_rcvref<void() const volatile&& noexcept>();

    test_is_same_rcvref<void(int)>();
    test_is_same_rcvref<void(int)&>();
    test_is_same_rcvref<void(int) &&>();
    test_is_same_rcvref<void(int) const>();
    test_is_same_rcvref<void(int) const&>();
    test_is_same_rcvref<void(int) const&&>();
    test_is_same_rcvref<void(int) volatile>();
    test_is_same_rcvref<void(int) volatile&>();
    test_is_same_rcvref<void(int) volatile&&>();
    test_is_same_rcvref<void(int) const volatile>();
    test_is_same_rcvref<void(int) const volatile&>();
    test_is_same_rcvref<void(int) const volatile&&>();
    test_is_same_rcvref<void(int) noexcept>();
    test_is_same_rcvref<void(int)& noexcept>();
    test_is_same_rcvref<void(int)&& noexcept>();
    test_is_same_rcvref<void(int) const noexcept>();
    test_is_same_rcvref<void(int) const& noexcept>();
    test_is_same_rcvref<void(int) const&& noexcept>();
    test_is_same_rcvref<void(int) volatile noexcept>();
    test_is_same_rcvref<void(int) volatile& noexcept>();
    test_is_same_rcvref<void(int) volatile&& noexcept>();
    test_is_same_rcvref<void(int) const volatile noexcept>();
    test_is_same_rcvref<void(int) const volatile& noexcept>();
    test_is_same_rcvref<void(int) const volatile&& noexcept>();

    test_is_same_rcvref<void(...)>();
    test_is_same_rcvref<void(...)&>();
    test_is_same_rcvref<void(...) &&>();
    test_is_same_rcvref<void(...) const>();
    test_is_same_rcvref<void(...) const&>();
    test_is_same_rcvref<void(...) const&&>();
    test_is_same_rcvref<void(...) volatile>();
    test_is_same_rcvref<void(...) volatile&>();
    test_is_same_rcvref<void(...) volatile&&>();
    test_is_same_rcvref<void(...) const volatile>();
    test_is_same_rcvref<void(...) const volatile&>();
    test_is_same_rcvref<void(...) const volatile&&>();
    test_is_same_rcvref<void(...) noexcept>();
    test_is_same_rcvref<void(...)& noexcept>();
    test_is_same_rcvref<void(...)&& noexcept>();
    test_is_same_rcvref<void(...) const noexcept>();
    test_is_same_rcvref<void(...) const& noexcept>();
    test_is_same_rcvref<void(...) const&& noexcept>();
    test_is_same_rcvref<void(...) volatile noexcept>();
    test_is_same_rcvref<void(...) volatile& noexcept>();
    test_is_same_rcvref<void(...) volatile&& noexcept>();
    test_is_same_rcvref<void(...) const volatile noexcept>();
    test_is_same_rcvref<void(...) const volatile& noexcept>();
    test_is_same_rcvref<void(...) const volatile&& noexcept>();

    test_is_same_rcvref<void(int, ...)>();
    test_is_same_rcvref<void(int, ...)&>();
    test_is_same_rcvref<void(int, ...) &&>();
    test_is_same_rcvref<void(int, ...) const>();
    test_is_same_rcvref<void(int, ...) const&>();
    test_is_same_rcvref<void(int, ...) const&&>();
    test_is_same_rcvref<void(int, ...) volatile>();
    test_is_same_rcvref<void(int, ...) volatile&>();
    test_is_same_rcvref<void(int, ...) volatile&&>();
    test_is_same_rcvref<void(int, ...) const volatile>();
    test_is_same_rcvref<void(int, ...) const volatile&>();
    test_is_same_rcvref<void(int, ...) const volatile&&>();
    test_is_same_rcvref<void(int, ...) noexcept>();
    test_is_same_rcvref<void(int, ...)& noexcept>();
    test_is_same_rcvref<void(int, ...)&& noexcept>();
    test_is_same_rcvref<void(int, ...) const noexcept>();
    test_is_same_rcvref<void(int, ...) const& noexcept>();
    test_is_same_rcvref<void(int, ...) const&& noexcept>();
    test_is_same_rcvref<void(int, ...) volatile noexcept>();
    test_is_same_rcvref<void(int, ...) volatile& noexcept>();
    test_is_same_rcvref<void(int, ...) volatile&& noexcept>();
    test_is_same_rcvref<void(int, ...) const volatile noexcept>();
    test_is_same_rcvref<void(int, ...) const volatile& noexcept>();
    test_is_same_rcvref<void(int, ...) const volatile&& noexcept>();

    test_is_same_rcvref<int()>();
    test_is_same_rcvref<int()&>();
    test_is_same_rcvref<int() &&>();
    test_is_same_rcvref<int() const>();
    test_is_same_rcvref<int() const&>();
    test_is_same_rcvref<int() const&&>();
    test_is_same_rcvref<int() volatile>();
    test_is_same_rcvref<int() volatile&>();
    test_is_same_rcvref<int() volatile&&>();
    test_is_same_rcvref<int() const volatile>();
    test_is_same_rcvref<int() const volatile&>();
    test_is_same_rcvref<int() const volatile&&>();
    test_is_same_rcvref<int() noexcept>();
    test_is_same_rcvref<int()& noexcept>();
    test_is_same_rcvref<int()&& noexcept>();
    test_is_same_rcvref<int() const noexcept>();
    test_is_same_rcvref<int() const& noexcept>();
    test_is_same_rcvref<int() const&& noexcept>();
    test_is_same_rcvref<int() volatile noexcept>();
    test_is_same_rcvref<int() volatile& noexcept>();
    test_is_same_rcvref<int() volatile&& noexcept>();
    test_is_same_rcvref<int() const volatile noexcept>();
    test_is_same_rcvref<int() const volatile& noexcept>();
    test_is_same_rcvref<int() const volatile&& noexcept>();

    test_is_same_rcvref<int(int)>();
    test_is_same_rcvref<int(int)&>();
    test_is_same_rcvref<int(int) &&>();
    test_is_same_rcvref<int(int) const>();
    test_is_same_rcvref<int(int) const&>();
    test_is_same_rcvref<int(int) const&&>();
    test_is_same_rcvref<int(int) volatile>();
    test_is_same_rcvref<int(int) volatile&>();
    test_is_same_rcvref<int(int) volatile&&>();
    test_is_same_rcvref<int(int) const volatile>();
    test_is_same_rcvref<int(int) const volatile&>();
    test_is_same_rcvref<int(int) const volatile&&>();
    test_is_same_rcvref<int(int) noexcept>();
    test_is_same_rcvref<int(int)& noexcept>();
    test_is_same_rcvref<int(int)&& noexcept>();
    test_is_same_rcvref<int(int) const noexcept>();
    test_is_same_rcvref<int(int) const& noexcept>();
    test_is_same_rcvref<int(int) const&& noexcept>();
    test_is_same_rcvref<int(int) volatile noexcept>();
    test_is_same_rcvref<int(int) volatile& noexcept>();
    test_is_same_rcvref<int(int) volatile&& noexcept>();
    test_is_same_rcvref<int(int) const volatile noexcept>();
    test_is_same_rcvref<int(int) const volatile& noexcept>();
    test_is_same_rcvref<int(int) const volatile&& noexcept>();

    test_is_same_rcvref<int(...)>();
    test_is_same_rcvref<int(...)&>();
    test_is_same_rcvref<int(...) &&>();
    test_is_same_rcvref<int(...) const>();
    test_is_same_rcvref<int(...) const&>();
    test_is_same_rcvref<int(...) const&&>();
    test_is_same_rcvref<int(...) volatile>();
    test_is_same_rcvref<int(...) volatile&>();
    test_is_same_rcvref<int(...) volatile&&>();
    test_is_same_rcvref<int(...) const volatile>();
    test_is_same_rcvref<int(...) const volatile&>();
    test_is_same_rcvref<int(...) const volatile&&>();
    test_is_same_rcvref<int(...) noexcept>();
    test_is_same_rcvref<int(...)& noexcept>();
    test_is_same_rcvref<int(...)&& noexcept>();
    test_is_same_rcvref<int(...) const noexcept>();
    test_is_same_rcvref<int(...) const& noexcept>();
    test_is_same_rcvref<int(...) const&& noexcept>();
    test_is_same_rcvref<int(...) volatile noexcept>();
    test_is_same_rcvref<int(...) volatile& noexcept>();
    test_is_same_rcvref<int(...) volatile&& noexcept>();
    test_is_same_rcvref<int(...) const volatile noexcept>();
    test_is_same_rcvref<int(...) const volatile& noexcept>();
    test_is_same_rcvref<int(...) const volatile&& noexcept>();

    test_is_same_rcvref<int(int, ...)>();
    test_is_same_rcvref<int(int, ...)&>();
    test_is_same_rcvref<int(int, ...) &&>();
    test_is_same_rcvref<int(int, ...) const>();
    test_is_same_rcvref<int(int, ...) const&>();
    test_is_same_rcvref<int(int, ...) const&&>();
    test_is_same_rcvref<int(int, ...) volatile>();
    test_is_same_rcvref<int(int, ...) volatile&>();
    test_is_same_rcvref<int(int, ...) volatile&&>();
    test_is_same_rcvref<int(int, ...) const volatile>();
    test_is_same_rcvref<int(int, ...) const volatile&>();
    test_is_same_rcvref<int(int, ...) const volatile&&>();
    test_is_same_rcvref<int(int, ...) noexcept>();
    test_is_same_rcvref<int(int, ...)& noexcept>();
    test_is_same_rcvref<int(int, ...)&& noexcept>();
    test_is_same_rcvref<int(int, ...) const noexcept>();
    test_is_same_rcvref<int(int, ...) const& noexcept>();
    test_is_same_rcvref<int(int, ...) const&& noexcept>();
    test_is_same_rcvref<int(int, ...) volatile noexcept>();
    test_is_same_rcvref<int(int, ...) volatile& noexcept>();
    test_is_same_rcvref<int(int, ...) volatile&& noexcept>();
    test_is_same_rcvref<int(int, ...) const volatile noexcept>();
    test_is_same_rcvref<int(int, ...) const volatile& noexcept>();
    test_is_same_rcvref<int(int, ...) const volatile&& noexcept>();

    test_is_same_rcvref<void (*)()>();
    test_is_same_rcvref<void (*)() noexcept>();

    test_is_same_rcvref<void (*)(int)>();
    test_is_same_rcvref<void (*)(int) noexcept>();

    test_is_same_rcvref<void (*)(...)>();
    test_is_same_rcvref<void (*)(...) noexcept>();

    test_is_same_rcvref<void (*)(int, ...)>();
    test_is_same_rcvref<void (*)(int, ...) noexcept>();

    test_is_same_rcvref<int (*)()>();
    test_is_same_rcvref<int (*)() noexcept>();

    test_is_same_rcvref<int (*)(int)>();
    test_is_same_rcvref<int (*)(int) noexcept>();

    test_is_same_rcvref<int (*)(...)>();
    test_is_same_rcvref<int (*)(...) noexcept>();

    test_is_same_rcvref<int (*)(int, ...)>();
    test_is_same_rcvref<int (*)(int, ...) noexcept>();

    test_is_same_rcvref<void (&)()>();
    test_is_same_rcvref<void (&)() noexcept>();

    test_is_same_rcvref<void (&)(int)>();
    test_is_same_rcvref<void (&)(int) noexcept>();

    test_is_same_rcvref<void (&)(...)>();
    test_is_same_rcvref<void (&)(...) noexcept>();

    test_is_same_rcvref<void (&)(int, ...)>();
    test_is_same_rcvref<void (&)(int, ...) noexcept>();

    test_is_same_rcvref<int (&)()>();
    test_is_same_rcvref<int (&)() noexcept>();

    test_is_same_rcvref<int (&)(int)>();
    test_is_same_rcvref<int (&)(int) noexcept>();

    test_is_same_rcvref<int (&)(...)>();
    test_is_same_rcvref<int (&)(...) noexcept>();

    test_is_same_rcvref<int (&)(int, ...)>();
    test_is_same_rcvref<int (&)(int, ...) noexcept>();

    test_is_same_rcvref<void (&&)()>();
    test_is_same_rcvref<void (&&)() noexcept>();

    test_is_same_rcvref<void (&&)(int)>();
    test_is_same_rcvref<void (&&)(int) noexcept>();

    test_is_same_rcvref<void (&&)(...)>();
    test_is_same_rcvref<void (&&)(...) noexcept>();

    test_is_same_rcvref<void (&&)(int, ...)>();
    test_is_same_rcvref<void (&&)(int, ...) noexcept>();

    test_is_same_rcvref<int (&&)()>();
    test_is_same_rcvref<int (&&)() noexcept>();

    test_is_same_rcvref<int (&&)(int)>();
    test_is_same_rcvref<int (&&)(int) noexcept>();

    test_is_same_rcvref<int (&&)(...)>();
    test_is_same_rcvref<int (&&)(...) noexcept>();

    test_is_same_rcvref<int (&&)(int, ...)>();
    test_is_same_rcvref<int (&&)(int, ...) noexcept>();

    test_is_same_rcvref<void (class_type::*)()>();
    test_is_same_rcvref<void (class_type::*)()&>();
    test_is_same_rcvref<void (class_type::*)() &&>();
    test_is_same_rcvref<void (class_type::*)() const>();
    test_is_same_rcvref<void (class_type::*)() const&>();
    test_is_same_rcvref<void (class_type::*)() const&&>();
    test_is_same_rcvref<void (class_type::*)() noexcept>();
    test_is_same_rcvref<void (class_type::*)()& noexcept>();
    test_is_same_rcvref<void (class_type::*)()&& noexcept>();
    test_is_same_rcvref<void (class_type::*)() const noexcept>();
    test_is_same_rcvref<void (class_type::*)() const& noexcept>();
    test_is_same_rcvref<void (class_type::*)() const&& noexcept>();

    test_is_same_rcvref<void (class_type::*)(int)>();
    test_is_same_rcvref<void (class_type::*)(int)&>();
    test_is_same_rcvref<void (class_type::*)(int) &&>();
    test_is_same_rcvref<void (class_type::*)(int) const>();
    test_is_same_rcvref<void (class_type::*)(int) const&>();
    test_is_same_rcvref<void (class_type::*)(int) const&&>();
    test_is_same_rcvref<void (class_type::*)(int) noexcept>();
    test_is_same_rcvref<void (class_type::*)(int)& noexcept>();
    test_is_same_rcvref<void (class_type::*)(int)&& noexcept>();
    test_is_same_rcvref<void (class_type::*)(int) const noexcept>();
    test_is_same_rcvref<void (class_type::*)(int) const& noexcept>();
    test_is_same_rcvref<void (class_type::*)(int) const&& noexcept>();

    test_is_same_rcvref<void (class_type::*)(...)>();
    test_is_same_rcvref<void (class_type::*)(...)&>();
    test_is_same_rcvref<void (class_type::*)(...) &&>();
    test_is_same_rcvref<void (class_type::*)(...) const>();
    test_is_same_rcvref<void (class_type::*)(...) const&>();
    test_is_same_rcvref<void (class_type::*)(...) const&&>();
    test_is_same_rcvref<void (class_type::*)(...) noexcept>();
    test_is_same_rcvref<void (class_type::*)(...)& noexcept>();
    test_is_same_rcvref<void (class_type::*)(...)&& noexcept>();
    test_is_same_rcvref<void (class_type::*)(...) const noexcept>();
    test_is_same_rcvref<void (class_type::*)(...) const& noexcept>();
    test_is_same_rcvref<void (class_type::*)(...) const&& noexcept>();

    test_is_same_rcvref<void (class_type::*)(int, ...)>();
    test_is_same_rcvref<void (class_type::*)(int, ...)&>();
    test_is_same_rcvref<void (class_type::*)(int, ...) &&>();
    test_is_same_rcvref<void (class_type::*)(int, ...) const>();
    test_is_same_rcvref<void (class_type::*)(int, ...) const&>();
    test_is_same_rcvref<void (class_type::*)(int, ...) const&&>();
    test_is_same_rcvref<void (class_type::*)(int, ...) noexcept>();
    test_is_same_rcvref<void (class_type::*)(int, ...)& noexcept>();
    test_is_same_rcvref<void (class_type::*)(int, ...)&& noexcept>();
    test_is_same_rcvref<void (class_type::*)(int, ...) const noexcept>();
    test_is_same_rcvref<void (class_type::*)(int, ...) const& noexcept>();
    test_is_same_rcvref<void (class_type::*)(int, ...) const&& noexcept>();

    test_is_same_rcvref<int (class_type::*)()>();
    test_is_same_rcvref<int (class_type::*)()&>();
    test_is_same_rcvref<int (class_type::*)() &&>();
    test_is_same_rcvref<int (class_type::*)() const>();
    test_is_same_rcvref<int (class_type::*)() const&>();
    test_is_same_rcvref<int (class_type::*)() const&&>();
    test_is_same_rcvref<int (class_type::*)() noexcept>();
    test_is_same_rcvref<int (class_type::*)()& noexcept>();
    test_is_same_rcvref<int (class_type::*)()&& noexcept>();
    test_is_same_rcvref<int (class_type::*)() const noexcept>();
    test_is_same_rcvref<int (class_type::*)() const& noexcept>();
    test_is_same_rcvref<int (class_type::*)() const&& noexcept>();

    test_is_same_rcvref<int (class_type::*)(int)>();
    test_is_same_rcvref<int (class_type::*)(int)&>();
    test_is_same_rcvref<int (class_type::*)(int) &&>();
    test_is_same_rcvref<int (class_type::*)(int) const>();
    test_is_same_rcvref<int (class_type::*)(int) const&>();
    test_is_same_rcvref<int (class_type::*)(int) const&&>();
    test_is_same_rcvref<int (class_type::*)(int) noexcept>();
    test_is_same_rcvref<int (class_type::*)(int)& noexcept>();
    test_is_same_rcvref<int (class_type::*)(int)&& noexcept>();
    test_is_same_rcvref<int (class_type::*)(int) const noexcept>();
    test_is_same_rcvref<int (class_type::*)(int) const& noexcept>();
    test_is_same_rcvref<int (class_type::*)(int) const&& noexcept>();

    test_is_same_rcvref<int (class_type::*)(...)>();
    test_is_same_rcvref<int (class_type::*)(...)&>();
    test_is_same_rcvref<int (class_type::*)(...) &&>();
    test_is_same_rcvref<int (class_type::*)(...) const>();
    test_is_same_rcvref<int (class_type::*)(...) const&>();
    test_is_same_rcvref<int (class_type::*)(...) const&&>();
    test_is_same_rcvref<int (class_type::*)(...) noexcept>();
    test_is_same_rcvref<int (class_type::*)(...)& noexcept>();
    test_is_same_rcvref<int (class_type::*)(...)&& noexcept>();
    test_is_same_rcvref<int (class_type::*)(...) const noexcept>();
    test_is_same_rcvref<int (class_type::*)(...) const& noexcept>();
    test_is_same_rcvref<int (class_type::*)(...) const&& noexcept>();

    test_is_same_rcvref<int (class_type::*)(int, ...)>();
    test_is_same_rcvref<int (class_type::*)(int, ...)&>();
    test_is_same_rcvref<int (class_type::*)(int, ...) &&>();
    test_is_same_rcvref<int (class_type::*)(int, ...) const>();
    test_is_same_rcvref<int (class_type::*)(int, ...) const&>();
    test_is_same_rcvref<int (class_type::*)(int, ...) const&&>();
    test_is_same_rcvref<int (class_type::*)(int, ...) noexcept>();
    test_is_same_rcvref<int (class_type::*)(int, ...)& noexcept>();
    test_is_same_rcvref<int (class_type::*)(int, ...)&& noexcept>();
    test_is_same_rcvref<int (class_type::*)(int, ...) const noexcept>();
    test_is_same_rcvref<int (class_type::*)(int, ...) const& noexcept>();
    test_is_same_rcvref<int (class_type::*)(int, ...) const&& noexcept>();
}
