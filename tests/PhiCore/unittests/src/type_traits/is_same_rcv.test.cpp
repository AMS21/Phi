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
#include <phi/type_traits/is_same_rcv.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT, typename OtherT>
void test_is_same_rcv_impl()
{
    STATIC_REQUIRE(phi::is_same_rcv<TypeT, OtherT>::value);
    STATIC_REQUIRE(phi::is_same_rcv<OtherT, TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<TypeT, OtherT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<OtherT, TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_rcv_v<TypeT, OtherT>);
    STATIC_REQUIRE(phi::is_same_rcv_v<OtherT, TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<TypeT, OtherT>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<OtherT, TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same_rcv<TypeT, OtherT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same_rcv<TypeT, OtherT>);
}

template <typename TypeT, typename OtherT>
void test_is_not_same_rcv()
{
    STATIC_REQUIRE_FALSE(phi::is_same_rcv<TypeT, OtherT>::value);
    STATIC_REQUIRE_FALSE(phi::is_same_rcv<OtherT, TypeT>::value);
    STATIC_REQUIRE(phi::is_not_same_rcv<TypeT, OtherT>::value);
    STATIC_REQUIRE(phi::is_not_same_rcv<OtherT, TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_same_rcv_v<TypeT, OtherT>);
    STATIC_REQUIRE_FALSE(phi::is_same_rcv_v<OtherT, TypeT>);
    STATIC_REQUIRE(phi::is_not_same_rcv_v<TypeT, OtherT>);
    STATIC_REQUIRE(phi::is_not_same_rcv_v<OtherT, TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same_rcv<TypeT, OtherT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same_rcv<TypeT, OtherT>);
}

template <typename TypeT, typename OtherT = TypeT>
void test_is_same_rcv()
{
    test_is_same_rcv_impl<TypeT, OtherT>();
    test_is_same_rcv_impl<TypeT, const OtherT>();
    test_is_same_rcv_impl<TypeT, volatile OtherT>();
    test_is_same_rcv_impl<TypeT, const volatile OtherT>();

    test_is_same_rcv_impl<const TypeT, OtherT>();
    test_is_same_rcv_impl<const TypeT, const OtherT>();
    test_is_same_rcv_impl<const TypeT, volatile OtherT>();
    test_is_same_rcv_impl<const TypeT, const volatile OtherT>();

    test_is_same_rcv_impl<volatile TypeT, OtherT>();
    test_is_same_rcv_impl<volatile TypeT, const OtherT>();
    test_is_same_rcv_impl<volatile TypeT, volatile OtherT>();
    test_is_same_rcv_impl<volatile TypeT, const volatile OtherT>();

    test_is_same_rcv_impl<const volatile TypeT, OtherT>();
    test_is_same_rcv_impl<const volatile TypeT, const OtherT>();
    test_is_same_rcv_impl<const volatile TypeT, volatile OtherT>();
    test_is_same_rcv_impl<const volatile TypeT, const volatile OtherT>();
}

template <typename TypeT>
struct OverloadTest
{
    void fn(phi::is_same_rcv<TypeT, int> /*unused*/)
    {}
    void fn(phi::false_type /*unused*/)
    {}
    void x()
    {
        fn(phi::false_type());
    }
};

struct A; // incomplete

TEST_CASE("is_same_rcv")
{
    test_is_not_same_rcv<int, void>();
    test_is_not_same_rcv<void, class_type>();
    test_is_not_same_rcv<class_type, int*>();
    test_is_not_same_rcv<int*, int&>();
    test_is_not_same_rcv<int&, int>();

    test_is_not_same_rcv<int, int&>();
    test_is_not_same_rcv<int, const int&>();
    test_is_not_same_rcv<int, volatile int&>();
    test_is_not_same_rcv<int, const volatile int&>();
    test_is_not_same_rcv<int, int&&>();
    test_is_not_same_rcv<int, const int&&>();
    test_is_not_same_rcv<int, volatile int&&>();
    test_is_not_same_rcv<int, const volatile int&&>();

    OverloadTest<char> test;
    (void)test;

    test_is_same_rcv<void>();
    test_is_same_rcv<phi::nullptr_t>();
    test_is_same_rcv<bool>();
    test_is_same_rcv<char>();
    test_is_same_rcv<signed char>();
    test_is_same_rcv<unsigned char>();
    test_is_same_rcv<short>();
    test_is_same_rcv<unsigned short>();
    test_is_same_rcv<int>();
    test_is_same_rcv<unsigned int>();
    test_is_same_rcv<long>();
    test_is_same_rcv<unsigned long>();
    test_is_same_rcv<long long>();
    test_is_same_rcv<unsigned long long>();
    test_is_same_rcv<float>();
    test_is_same_rcv<double>();
    test_is_same_rcv<long double>();
    test_is_same_rcv<char8_t>();
    test_is_same_rcv<char16_t>();
    test_is_same_rcv<char32_t>();
    test_is_same_rcv<wchar_t>();

    test_is_same_rcv<phi::boolean>();
    test_is_same_rcv<phi::integer<signed char>>();
    test_is_same_rcv<phi::integer<unsigned char>>();
    test_is_same_rcv<phi::integer<short>>();
    test_is_same_rcv<phi::integer<unsigned short>>();
    test_is_same_rcv<phi::integer<int>>();
    test_is_same_rcv<phi::integer<unsigned int>>();
    test_is_same_rcv<phi::integer<long>>();
    test_is_same_rcv<phi::integer<unsigned long>>();
    test_is_same_rcv<phi::integer<long long>>();
    test_is_same_rcv<phi::integer<unsigned long long>>();
    test_is_same_rcv<phi::floating_point<float>>();
    test_is_same_rcv<phi::floating_point<double>>();
    test_is_same_rcv<phi::floating_point<long double>>();

    test_is_same_rcv<std::vector<int>>();
    test_is_same_rcv<phi::scope_ptr<int>>();

    test_is_same_rcv<int&>();
    test_is_same_rcv<const int&>();
    test_is_same_rcv<volatile int&>();
    test_is_same_rcv<const volatile int&>();
    test_is_same_rcv<int&&>();
    test_is_same_rcv<const int&&>();
    test_is_same_rcv<volatile int&&>();
    test_is_same_rcv<const volatile int&&>();
    test_is_same_rcv<int*>();
    test_is_same_rcv<const int*>();
    test_is_same_rcv<volatile int*>();
    test_is_same_rcv<const volatile int*>();
    test_is_same_rcv<int**>();
    test_is_same_rcv<const int**>();
    test_is_same_rcv<volatile int**>();
    test_is_same_rcv<const volatile int**>();
    test_is_same_rcv<int*&>();
    test_is_same_rcv<const int*&>();
    test_is_same_rcv<volatile int*&>();
    test_is_same_rcv<const volatile int*&>();
    test_is_same_rcv<int*&&>();
    test_is_same_rcv<const int*&&>();
    test_is_same_rcv<volatile int*&&>();
    test_is_same_rcv<const volatile int*&&>();
    test_is_same_rcv<void*>();
    test_is_same_rcv<char[3]>();
    test_is_same_rcv<char[]>();
    test_is_same_rcv<char* [3]>();
    test_is_same_rcv<char*[]>();
    test_is_same_rcv<int(*)[3]>();
    test_is_same_rcv<int(*)[]>();
    test_is_same_rcv<int(&)[3]>();
    test_is_same_rcv<int(&)[]>();
    test_is_same_rcv<int(&&)[3]>();
    test_is_same_rcv<int(&&)[]>();
    test_is_same_rcv<char[3][2]>();
    test_is_same_rcv<char[][2]>();
    test_is_same_rcv<char* [3][2]>();
    test_is_same_rcv<char*[][2]>();
    test_is_same_rcv<int(*)[3][2]>();
    test_is_same_rcv<int(*)[][2]>();
    test_is_same_rcv<int(&)[3][2]>();
    test_is_same_rcv<int(&)[][2]>();
    test_is_same_rcv<int(&&)[3][2]>();
    test_is_same_rcv<int(&&)[][2]>();
    test_is_same_rcv<class_type>();
    test_is_same_rcv<class_type[]>();
    test_is_same_rcv<class_type[2]>();
    test_is_same_rcv<template_type<void>>();
    test_is_same_rcv<template_type<int>>();
    test_is_same_rcv<template_type<class_type>>();
    test_is_same_rcv<template_type<incomplete_type>>();
    test_is_same_rcv<variadic_template<>>();
    test_is_same_rcv<variadic_template<void>>();
    test_is_same_rcv<variadic_template<int>>();
    test_is_same_rcv<variadic_template<class_type>>();
    test_is_same_rcv<variadic_template<incomplete_type>>();
    test_is_same_rcv<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_same_rcv<public_derived_from<base>>();
    test_is_same_rcv<public_derived_from<derived>>();
    test_is_same_rcv<public_derived_from<class_type>>();
    test_is_same_rcv<private_derived_from<base>>();
    test_is_same_rcv<private_derived_from<derived>>();
    test_is_same_rcv<private_derived_from<class_type>>();
    test_is_same_rcv<protected_derived_from<base>>();
    test_is_same_rcv<protected_derived_from<derived>>();
    test_is_same_rcv<protected_derived_from<class_type>>();
    test_is_same_rcv<virtual_derived_from<base>>();
    test_is_same_rcv<virtual_derived_from<derived>>();
    test_is_same_rcv<virtual_derived_from<class_type>>();
    test_is_same_rcv<union_type>();
    test_is_same_rcv<non_empty_union>();
    test_is_same_rcv<non_trivial_union>();
    test_is_same_rcv<empty>();
    test_is_same_rcv<not_empty>();
    test_is_same_rcv<non_trivial>();
    test_is_same_rcv<bit_zero>();
    test_is_same_rcv<bit_one>();
    test_is_same_rcv<base>();
    test_is_same_rcv<derived>();
    test_is_same_rcv<non_empty_base>();
    test_is_same_rcv<empty_base>();
    test_is_same_rcv<virtual_base>();
    test_is_same_rcv<polymorphic>();
    test_is_same_rcv<derived_polymorphic>();
    test_is_same_rcv<abstract>();
    test_is_same_rcv<public_abstract>();
    test_is_same_rcv<private_abstract>();
    test_is_same_rcv<protected_abstract>();
    test_is_same_rcv<abstract_template<int>>();
    test_is_same_rcv<abstract_template<double>>();
    test_is_same_rcv<abstract_template<class_type>>();
    test_is_same_rcv<abstract_template<incomplete_type>>();
    test_is_same_rcv<public_abstract_deleted_destructor>();
    test_is_same_rcv<protected_abstract_deleted_destructor>();
    test_is_same_rcv<private_abstract_deleted_destructor>();
    test_is_same_rcv<final_type>();
    test_is_same_rcv<final_derived>();
    test_is_same_rcv<public_destructor>();
    test_is_same_rcv<protected_destructor>();
    test_is_same_rcv<private_destructor>();
    test_is_same_rcv<virtual_public_destructor>();
    test_is_same_rcv<virtual_protected_destructor>();
    test_is_same_rcv<virtual_private_destructor>();
    test_is_same_rcv<pure_public_destructor>();
    test_is_same_rcv<pure_protected_destructor>();
    test_is_same_rcv<pure_private_destructor>();
    test_is_same_rcv<deleted_public_destructor>();
    test_is_same_rcv<deleted_protected_destructor>();
    test_is_same_rcv<deleted_private_destructor>();
    test_is_same_rcv<deleted_virtual_public_destructor>();
    test_is_same_rcv<deleted_virtual_protected_destructor>();
    test_is_same_rcv<deleted_virtual_private_destructor>();
    test_is_same_rcv<explicit_class>();
    test_is_same_rcv<nothrow_explicit_class>();
    test_is_same_rcv<throw_explicit_class>();
    test_is_same_rcv<throw_default_class>();
    test_is_same_rcv<throw_copy_constructible_class>();
    test_is_same_rcv<throw_move_constructible_class>();
    test_is_same_rcv<throw_destructor>();
    test_is_same_rcv<noexcept_explicit_class>();
    test_is_same_rcv<except_explicit_class>();
    test_is_same_rcv<noexcept_default_class>();
    test_is_same_rcv<except_default_class>();
    test_is_same_rcv<noexcept_copy_constructible_class>();
    test_is_same_rcv<except_copy_constructible_class>();
    test_is_same_rcv<noexcept_move_constructible_class>();
    test_is_same_rcv<except_move_constructible_class>();
    test_is_same_rcv<noexcept_copy_assign_class>();
    test_is_same_rcv<except_copy_assign_class>();
    test_is_same_rcv<noexcept_move_assign_class>();
    test_is_same_rcv<except_move_assign_class>();
    test_is_same_rcv<deleted_copy_assign_class>();
    test_is_same_rcv<deleted_move_assign_class>();
    test_is_same_rcv<noexcept_move_constructible_and_assignable_class>();
    test_is_same_rcv<except_move_constructible_noexcept_move_assign_class>();
    test_is_same_rcv<noexcept_move_constructible_except_move_assign_class>();
    test_is_same_rcv<except_move_constructible_and_assign_class>();
    test_is_same_rcv<implicit_to<int>>();
    test_is_same_rcv<implicit_to<float>>();
    test_is_same_rcv<implicit_to<class_type>>();
    test_is_same_rcv<deleted_implicit_to<int>>();
    test_is_same_rcv<deleted_implicit_to<float>>();
    test_is_same_rcv<deleted_implicit_to<class_type>>();
    test_is_same_rcv<explicit_to<int>>();
    test_is_same_rcv<explicit_to<float>>();
    test_is_same_rcv<explicit_to<class_type>>();
    test_is_same_rcv<deleted_explicit_to<int>>();
    test_is_same_rcv<deleted_explicit_to<float>>();
    test_is_same_rcv<deleted_explicit_to<class_type>>();
    test_is_same_rcv<ellipsis>();
    test_is_same_rcv<deleted_ellipsis>();
    test_is_same_rcv<copy_constructible_only_type>();
    test_is_same_rcv<move_constructible_only_type>();
    test_is_same_rcv<overloaded_operators>();
    test_is_same_rcv<public_int_member>();
    test_is_same_rcv<protected_int_member>();
    test_is_same_rcv<private_int_member>();
    test_is_same_rcv<public_static_int_member>();
    test_is_same_rcv<protected_static_int_member>();
    test_is_same_rcv<private_static_int_member>();
    test_is_same_rcv<public_template_member<int>>();
    test_is_same_rcv<public_template_member<float>>();
    test_is_same_rcv<public_template_member<class_type>>();
    test_is_same_rcv<protected_template_member<int>>();
    test_is_same_rcv<protected_template_member<float>>();
    test_is_same_rcv<protected_template_member<class_type>>();
    test_is_same_rcv<private_template_member<int>>();
    test_is_same_rcv<private_template_member<float>>();
    test_is_same_rcv<private_template_member<class_type>>();
    test_is_same_rcv<public_static_template_member<int>>();
    test_is_same_rcv<public_static_template_member<float>>();
    test_is_same_rcv<public_static_template_member<class_type>>();
    test_is_same_rcv<protected_static_template_member<int>>();
    test_is_same_rcv<protected_static_template_member<float>>();
    test_is_same_rcv<protected_static_template_member<class_type>>();
    test_is_same_rcv<private_static_template_member<int>>();
    test_is_same_rcv<private_static_template_member<float>>();
    test_is_same_rcv<private_static_template_member<class_type>>();
    test_is_same_rcv<cannot_instantiate<int>>();
    test_is_same_rcv<cannot_instantiate<float>>();
    test_is_same_rcv<cannot_instantiate<class_type>>();
    test_is_same_rcv<natural_alignment>();
    test_is_same_rcv<Enum>();
    test_is_same_rcv<EnumSigned>();
    test_is_same_rcv<EnumUnsigned>();
    test_is_same_rcv<EnumClass>();
    test_is_same_rcv<EnumStruct>();
    test_is_same_rcv<function_type>();
    test_is_same_rcv<function_ptr>();
    test_is_same_rcv<member_object_ptr>();
    test_is_same_rcv<member_function_ptr>();
    test_is_same_rcv<lambda_type>();
    test_is_same_rcv<lambda_noexcept_type>();
    test_is_same_rcv<lambda_throws_type>();
    test_is_same_rcv<incomplete_type>();
    test_is_same_rcv<incomplete_template<void>>();
    test_is_same_rcv<incomplete_template<int>>();
    test_is_same_rcv<incomplete_template<class_type>>();
    test_is_same_rcv<incomplete_template<incomplete_type>>();
    test_is_same_rcv<incomplete_variadic_template<>>();
    test_is_same_rcv<incomplete_variadic_template<void>>();
    test_is_same_rcv<incomplete_variadic_template<int>>();
    test_is_same_rcv<incomplete_variadic_template<class_type>>();
    test_is_same_rcv<incomplete_variadic_template<incomplete_type>>();
    test_is_same_rcv<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_same_rcv<incomplete_union>();
    test_is_same_rcv<IncompleteEnumSigned>();
    test_is_same_rcv<IncompleteEnumUnsigned>();
    test_is_same_rcv<IncompleteEnumClass>();
    test_is_same_rcv<IncompleteEnumStruct>();
    test_is_same_rcv<int class_type::*>();
    test_is_same_rcv<float class_type::*>();
    test_is_same_rcv<void * class_type::*>();
    test_is_same_rcv<int * class_type::*>();
    test_is_same_rcv<Enum class_type::*>();
    test_is_same_rcv<not_empty class_type::*>();
    test_is_same_rcv<int class_type::*&>();
    test_is_same_rcv<float class_type::*&>();
    test_is_same_rcv<void * class_type::*&>();
    test_is_same_rcv<int * class_type::*&>();
    test_is_same_rcv<Enum class_type::*&>();
    test_is_same_rcv<not_empty class_type::*&>();
    test_is_same_rcv<int class_type::*&&>();
    test_is_same_rcv<float class_type::*&&>();
    test_is_same_rcv<void * class_type::*&&>();
    test_is_same_rcv<int * class_type::*&&>();
    test_is_same_rcv<Enum class_type::*&&>();
    test_is_same_rcv<not_empty class_type::*&&>();
    test_is_same_rcv<non_default_constructible>();
    test_is_same_rcv<non_copy_constructible>();
    test_is_same_rcv<non_move_constructible>();
    test_is_same_rcv<non_copy_assignable>();
    test_is_same_rcv<non_move_assignable>();
    test_is_same_rcv<non_assignable>();
    test_is_same_rcv<non_copyable>();
    test_is_same_rcv<non_moveable>();
    test_is_same_rcv<non_constructible>();
    test_is_same_rcv<non_destructible>();
    test_is_same_rcv<tracked>();
    test_is_same_rcv<trap_constructible>();
    test_is_same_rcv<trap_implicit_conversion>();
    test_is_same_rcv<trap_comma>();
    test_is_same_rcv<trap_call>();
    test_is_same_rcv<trap_self_assign>();
    test_is_same_rcv<trap_deref>();
    test_is_same_rcv<trap_array_subscript>();

#if PHI_HAS_EXTENSION_ZERO_SIZE_ARRAY() && PHI_COMPILER_IS_NOT(MINGW)
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wzero-length-array")
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wpedantic")

    test_is_same_rcv<int[0]>();

    PHI_GCC_SUPPRESS_WARNING_POP()
    PHI_CLANG_SUPPRESS_WARNING_POP()
#endif

    test_is_same_rcv<void()>();
    test_is_same_rcv<void()&>();
    test_is_same_rcv<void() &&>();
    test_is_same_rcv<void() const>();
    test_is_same_rcv<void() const&>();
    test_is_same_rcv<void() const&&>();
    test_is_same_rcv<void() volatile>();
    test_is_same_rcv<void() volatile&>();
    test_is_same_rcv<void() volatile&&>();
    test_is_same_rcv<void() const volatile>();
    test_is_same_rcv<void() const volatile&>();
    test_is_same_rcv<void() const volatile&&>();
    test_is_same_rcv<void() noexcept>();
    test_is_same_rcv<void() & noexcept>();
    test_is_same_rcv<void() && noexcept>();
    test_is_same_rcv<void() const noexcept>();
    test_is_same_rcv<void() const & noexcept>();
    test_is_same_rcv<void() const && noexcept>();
    test_is_same_rcv<void() volatile noexcept>();
    test_is_same_rcv<void() volatile & noexcept>();
    test_is_same_rcv<void() volatile && noexcept>();
    test_is_same_rcv<void() const volatile noexcept>();
    test_is_same_rcv<void() const volatile & noexcept>();
    test_is_same_rcv<void() const volatile && noexcept>();

    test_is_same_rcv<void(int)>();
    test_is_same_rcv<void(int)&>();
    test_is_same_rcv<void(int) &&>();
    test_is_same_rcv<void(int) const>();
    test_is_same_rcv<void(int) const&>();
    test_is_same_rcv<void(int) const&&>();
    test_is_same_rcv<void(int) volatile>();
    test_is_same_rcv<void(int) volatile&>();
    test_is_same_rcv<void(int) volatile&&>();
    test_is_same_rcv<void(int) const volatile>();
    test_is_same_rcv<void(int) const volatile&>();
    test_is_same_rcv<void(int) const volatile&&>();
    test_is_same_rcv<void(int) noexcept>();
    test_is_same_rcv<void(int) & noexcept>();
    test_is_same_rcv<void(int) && noexcept>();
    test_is_same_rcv<void(int) const noexcept>();
    test_is_same_rcv<void(int) const & noexcept>();
    test_is_same_rcv<void(int) const && noexcept>();
    test_is_same_rcv<void(int) volatile noexcept>();
    test_is_same_rcv<void(int) volatile & noexcept>();
    test_is_same_rcv<void(int) volatile && noexcept>();
    test_is_same_rcv<void(int) const volatile noexcept>();
    test_is_same_rcv<void(int) const volatile & noexcept>();
    test_is_same_rcv<void(int) const volatile && noexcept>();

    test_is_same_rcv<void(...)>();
    test_is_same_rcv<void(...)&>();
    test_is_same_rcv<void(...) &&>();
    test_is_same_rcv<void(...) const>();
    test_is_same_rcv<void(...) const&>();
    test_is_same_rcv<void(...) const&&>();
    test_is_same_rcv<void(...) volatile>();
    test_is_same_rcv<void(...) volatile&>();
    test_is_same_rcv<void(...) volatile&&>();
    test_is_same_rcv<void(...) const volatile>();
    test_is_same_rcv<void(...) const volatile&>();
    test_is_same_rcv<void(...) const volatile&&>();
    test_is_same_rcv<void(...) noexcept>();
    test_is_same_rcv<void(...) & noexcept>();
    test_is_same_rcv<void(...) && noexcept>();
    test_is_same_rcv<void(...) const noexcept>();
    test_is_same_rcv<void(...) const & noexcept>();
    test_is_same_rcv<void(...) const && noexcept>();
    test_is_same_rcv<void(...) volatile noexcept>();
    test_is_same_rcv<void(...) volatile & noexcept>();
    test_is_same_rcv<void(...) volatile && noexcept>();
    test_is_same_rcv<void(...) const volatile noexcept>();
    test_is_same_rcv<void(...) const volatile & noexcept>();
    test_is_same_rcv<void(...) const volatile && noexcept>();

    test_is_same_rcv<void(int, ...)>();
    test_is_same_rcv<void(int, ...)&>();
    test_is_same_rcv<void(int, ...) &&>();
    test_is_same_rcv<void(int, ...) const>();
    test_is_same_rcv<void(int, ...) const&>();
    test_is_same_rcv<void(int, ...) const&&>();
    test_is_same_rcv<void(int, ...) volatile>();
    test_is_same_rcv<void(int, ...) volatile&>();
    test_is_same_rcv<void(int, ...) volatile&&>();
    test_is_same_rcv<void(int, ...) const volatile>();
    test_is_same_rcv<void(int, ...) const volatile&>();
    test_is_same_rcv<void(int, ...) const volatile&&>();
    test_is_same_rcv<void(int, ...) noexcept>();
    test_is_same_rcv<void(int, ...) & noexcept>();
    test_is_same_rcv<void(int, ...) && noexcept>();
    test_is_same_rcv<void(int, ...) const noexcept>();
    test_is_same_rcv<void(int, ...) const & noexcept>();
    test_is_same_rcv<void(int, ...) const && noexcept>();
    test_is_same_rcv<void(int, ...) volatile noexcept>();
    test_is_same_rcv<void(int, ...) volatile & noexcept>();
    test_is_same_rcv<void(int, ...) volatile && noexcept>();
    test_is_same_rcv<void(int, ...) const volatile noexcept>();
    test_is_same_rcv<void(int, ...) const volatile & noexcept>();
    test_is_same_rcv<void(int, ...) const volatile && noexcept>();

    test_is_same_rcv<int()>();
    test_is_same_rcv<int()&>();
    test_is_same_rcv<int() &&>();
    test_is_same_rcv<int() const>();
    test_is_same_rcv<int() const&>();
    test_is_same_rcv<int() const&&>();
    test_is_same_rcv<int() volatile>();
    test_is_same_rcv<int() volatile&>();
    test_is_same_rcv<int() volatile&&>();
    test_is_same_rcv<int() const volatile>();
    test_is_same_rcv<int() const volatile&>();
    test_is_same_rcv<int() const volatile&&>();
    test_is_same_rcv<int() noexcept>();
    test_is_same_rcv<int() & noexcept>();
    test_is_same_rcv<int() && noexcept>();
    test_is_same_rcv<int() const noexcept>();
    test_is_same_rcv<int() const & noexcept>();
    test_is_same_rcv<int() const && noexcept>();
    test_is_same_rcv<int() volatile noexcept>();
    test_is_same_rcv<int() volatile & noexcept>();
    test_is_same_rcv<int() volatile && noexcept>();
    test_is_same_rcv<int() const volatile noexcept>();
    test_is_same_rcv<int() const volatile & noexcept>();
    test_is_same_rcv<int() const volatile && noexcept>();

    test_is_same_rcv<int(int)>();
    test_is_same_rcv<int(int)&>();
    test_is_same_rcv<int(int) &&>();
    test_is_same_rcv<int(int) const>();
    test_is_same_rcv<int(int) const&>();
    test_is_same_rcv<int(int) const&&>();
    test_is_same_rcv<int(int) volatile>();
    test_is_same_rcv<int(int) volatile&>();
    test_is_same_rcv<int(int) volatile&&>();
    test_is_same_rcv<int(int) const volatile>();
    test_is_same_rcv<int(int) const volatile&>();
    test_is_same_rcv<int(int) const volatile&&>();
    test_is_same_rcv<int(int) noexcept>();
    test_is_same_rcv<int(int) & noexcept>();
    test_is_same_rcv<int(int) && noexcept>();
    test_is_same_rcv<int(int) const noexcept>();
    test_is_same_rcv<int(int) const & noexcept>();
    test_is_same_rcv<int(int) const && noexcept>();
    test_is_same_rcv<int(int) volatile noexcept>();
    test_is_same_rcv<int(int) volatile & noexcept>();
    test_is_same_rcv<int(int) volatile && noexcept>();
    test_is_same_rcv<int(int) const volatile noexcept>();
    test_is_same_rcv<int(int) const volatile & noexcept>();
    test_is_same_rcv<int(int) const volatile && noexcept>();

    test_is_same_rcv<int(...)>();
    test_is_same_rcv<int(...)&>();
    test_is_same_rcv<int(...) &&>();
    test_is_same_rcv<int(...) const>();
    test_is_same_rcv<int(...) const&>();
    test_is_same_rcv<int(...) const&&>();
    test_is_same_rcv<int(...) volatile>();
    test_is_same_rcv<int(...) volatile&>();
    test_is_same_rcv<int(...) volatile&&>();
    test_is_same_rcv<int(...) const volatile>();
    test_is_same_rcv<int(...) const volatile&>();
    test_is_same_rcv<int(...) const volatile&&>();
    test_is_same_rcv<int(...) noexcept>();
    test_is_same_rcv<int(...) & noexcept>();
    test_is_same_rcv<int(...) && noexcept>();
    test_is_same_rcv<int(...) const noexcept>();
    test_is_same_rcv<int(...) const & noexcept>();
    test_is_same_rcv<int(...) const && noexcept>();
    test_is_same_rcv<int(...) volatile noexcept>();
    test_is_same_rcv<int(...) volatile & noexcept>();
    test_is_same_rcv<int(...) volatile && noexcept>();
    test_is_same_rcv<int(...) const volatile noexcept>();
    test_is_same_rcv<int(...) const volatile & noexcept>();
    test_is_same_rcv<int(...) const volatile && noexcept>();

    test_is_same_rcv<int(int, ...)>();
    test_is_same_rcv<int(int, ...)&>();
    test_is_same_rcv<int(int, ...) &&>();
    test_is_same_rcv<int(int, ...) const>();
    test_is_same_rcv<int(int, ...) const&>();
    test_is_same_rcv<int(int, ...) const&&>();
    test_is_same_rcv<int(int, ...) volatile>();
    test_is_same_rcv<int(int, ...) volatile&>();
    test_is_same_rcv<int(int, ...) volatile&&>();
    test_is_same_rcv<int(int, ...) const volatile>();
    test_is_same_rcv<int(int, ...) const volatile&>();
    test_is_same_rcv<int(int, ...) const volatile&&>();
    test_is_same_rcv<int(int, ...) noexcept>();
    test_is_same_rcv<int(int, ...) & noexcept>();
    test_is_same_rcv<int(int, ...) && noexcept>();
    test_is_same_rcv<int(int, ...) const noexcept>();
    test_is_same_rcv<int(int, ...) const & noexcept>();
    test_is_same_rcv<int(int, ...) const && noexcept>();
    test_is_same_rcv<int(int, ...) volatile noexcept>();
    test_is_same_rcv<int(int, ...) volatile & noexcept>();
    test_is_same_rcv<int(int, ...) volatile && noexcept>();
    test_is_same_rcv<int(int, ...) const volatile noexcept>();
    test_is_same_rcv<int(int, ...) const volatile & noexcept>();
    test_is_same_rcv<int(int, ...) const volatile && noexcept>();

    test_is_same_rcv<void (*)()>();
    test_is_same_rcv<void (*)() noexcept>();

    test_is_same_rcv<void (*)(int)>();
    test_is_same_rcv<void (*)(int) noexcept>();

    test_is_same_rcv<void (*)(...)>();
    test_is_same_rcv<void (*)(...) noexcept>();

    test_is_same_rcv<void (*)(int, ...)>();
    test_is_same_rcv<void (*)(int, ...) noexcept>();

    test_is_same_rcv<int (*)()>();
    test_is_same_rcv<int (*)() noexcept>();

    test_is_same_rcv<int (*)(int)>();
    test_is_same_rcv<int (*)(int) noexcept>();

    test_is_same_rcv<int (*)(...)>();
    test_is_same_rcv<int (*)(...) noexcept>();

    test_is_same_rcv<int (*)(int, ...)>();
    test_is_same_rcv<int (*)(int, ...) noexcept>();

    test_is_same_rcv<void (&)()>();
    test_is_same_rcv<void (&)() noexcept>();

    test_is_same_rcv<void (&)(int)>();
    test_is_same_rcv<void (&)(int) noexcept>();

    test_is_same_rcv<void (&)(...)>();
    test_is_same_rcv<void (&)(...) noexcept>();

    test_is_same_rcv<void (&)(int, ...)>();
    test_is_same_rcv<void (&)(int, ...) noexcept>();

    test_is_same_rcv<int (&)()>();
    test_is_same_rcv<int (&)() noexcept>();

    test_is_same_rcv<int (&)(int)>();
    test_is_same_rcv<int (&)(int) noexcept>();

    test_is_same_rcv<int (&)(...)>();
    test_is_same_rcv<int (&)(...) noexcept>();

    test_is_same_rcv<int (&)(int, ...)>();
    test_is_same_rcv<int (&)(int, ...) noexcept>();

    test_is_same_rcv<void (&&)()>();
    test_is_same_rcv<void (&&)() noexcept>();

    test_is_same_rcv<void (&&)(int)>();
    test_is_same_rcv<void (&&)(int) noexcept>();

    test_is_same_rcv<void (&&)(...)>();
    test_is_same_rcv<void (&&)(...) noexcept>();

    test_is_same_rcv<void (&&)(int, ...)>();
    test_is_same_rcv<void (&&)(int, ...) noexcept>();

    test_is_same_rcv<int (&&)()>();
    test_is_same_rcv<int (&&)() noexcept>();

    test_is_same_rcv<int (&&)(int)>();
    test_is_same_rcv<int (&&)(int) noexcept>();

    test_is_same_rcv<int (&&)(...)>();
    test_is_same_rcv<int (&&)(...) noexcept>();

    test_is_same_rcv<int (&&)(int, ...)>();
    test_is_same_rcv<int (&&)(int, ...) noexcept>();

    test_is_same_rcv<void (class_type::*)()>();
    test_is_same_rcv<void (class_type::*)()&>();
    test_is_same_rcv<void (class_type::*)() &&>();
    test_is_same_rcv<void (class_type::*)() const>();
    test_is_same_rcv<void (class_type::*)() const&>();
    test_is_same_rcv<void (class_type::*)() const&&>();
    test_is_same_rcv<void (class_type::*)() noexcept>();
    test_is_same_rcv<void (class_type::*)() & noexcept>();
    test_is_same_rcv<void (class_type::*)() && noexcept>();
    test_is_same_rcv<void (class_type::*)() const noexcept>();
    test_is_same_rcv<void (class_type::*)() const & noexcept>();
    test_is_same_rcv<void (class_type::*)() const && noexcept>();

    test_is_same_rcv<void (class_type::*)(int)>();
    test_is_same_rcv<void (class_type::*)(int)&>();
    test_is_same_rcv<void (class_type::*)(int) &&>();
    test_is_same_rcv<void (class_type::*)(int) const>();
    test_is_same_rcv<void (class_type::*)(int) const&>();
    test_is_same_rcv<void (class_type::*)(int) const&&>();
    test_is_same_rcv<void (class_type::*)(int) noexcept>();
    test_is_same_rcv<void (class_type::*)(int) & noexcept>();
    test_is_same_rcv<void (class_type::*)(int) && noexcept>();
    test_is_same_rcv<void (class_type::*)(int) const noexcept>();
    test_is_same_rcv<void (class_type::*)(int) const & noexcept>();
    test_is_same_rcv<void (class_type::*)(int) const && noexcept>();

    test_is_same_rcv<void (class_type::*)(...)>();
    test_is_same_rcv<void (class_type::*)(...)&>();
    test_is_same_rcv<void (class_type::*)(...) &&>();
    test_is_same_rcv<void (class_type::*)(...) const>();
    test_is_same_rcv<void (class_type::*)(...) const&>();
    test_is_same_rcv<void (class_type::*)(...) const&&>();
    test_is_same_rcv<void (class_type::*)(...) noexcept>();
    test_is_same_rcv<void (class_type::*)(...) & noexcept>();
    test_is_same_rcv<void (class_type::*)(...) && noexcept>();
    test_is_same_rcv<void (class_type::*)(...) const noexcept>();
    test_is_same_rcv<void (class_type::*)(...) const & noexcept>();
    test_is_same_rcv<void (class_type::*)(...) const && noexcept>();

    test_is_same_rcv<void (class_type::*)(int, ...)>();
    test_is_same_rcv<void (class_type::*)(int, ...)&>();
    test_is_same_rcv<void (class_type::*)(int, ...) &&>();
    test_is_same_rcv<void (class_type::*)(int, ...) const>();
    test_is_same_rcv<void (class_type::*)(int, ...) const&>();
    test_is_same_rcv<void (class_type::*)(int, ...) const&&>();
    test_is_same_rcv<void (class_type::*)(int, ...) noexcept>();
    test_is_same_rcv<void (class_type::*)(int, ...) & noexcept>();
    test_is_same_rcv<void (class_type::*)(int, ...) && noexcept>();
    test_is_same_rcv<void (class_type::*)(int, ...) const noexcept>();
    test_is_same_rcv<void (class_type::*)(int, ...) const & noexcept>();
    test_is_same_rcv<void (class_type::*)(int, ...) const && noexcept>();

    test_is_same_rcv<int (class_type::*)()>();
    test_is_same_rcv<int (class_type::*)()&>();
    test_is_same_rcv<int (class_type::*)() &&>();
    test_is_same_rcv<int (class_type::*)() const>();
    test_is_same_rcv<int (class_type::*)() const&>();
    test_is_same_rcv<int (class_type::*)() const&&>();
    test_is_same_rcv<int (class_type::*)() noexcept>();
    test_is_same_rcv<int (class_type::*)() & noexcept>();
    test_is_same_rcv<int (class_type::*)() && noexcept>();
    test_is_same_rcv<int (class_type::*)() const noexcept>();
    test_is_same_rcv<int (class_type::*)() const & noexcept>();
    test_is_same_rcv<int (class_type::*)() const && noexcept>();

    test_is_same_rcv<int (class_type::*)(int)>();
    test_is_same_rcv<int (class_type::*)(int)&>();
    test_is_same_rcv<int (class_type::*)(int) &&>();
    test_is_same_rcv<int (class_type::*)(int) const>();
    test_is_same_rcv<int (class_type::*)(int) const&>();
    test_is_same_rcv<int (class_type::*)(int) const&&>();
    test_is_same_rcv<int (class_type::*)(int) noexcept>();
    test_is_same_rcv<int (class_type::*)(int) & noexcept>();
    test_is_same_rcv<int (class_type::*)(int) && noexcept>();
    test_is_same_rcv<int (class_type::*)(int) const noexcept>();
    test_is_same_rcv<int (class_type::*)(int) const & noexcept>();
    test_is_same_rcv<int (class_type::*)(int) const && noexcept>();

    test_is_same_rcv<int (class_type::*)(...)>();
    test_is_same_rcv<int (class_type::*)(...)&>();
    test_is_same_rcv<int (class_type::*)(...) &&>();
    test_is_same_rcv<int (class_type::*)(...) const>();
    test_is_same_rcv<int (class_type::*)(...) const&>();
    test_is_same_rcv<int (class_type::*)(...) const&&>();
    test_is_same_rcv<int (class_type::*)(...) noexcept>();
    test_is_same_rcv<int (class_type::*)(...) & noexcept>();
    test_is_same_rcv<int (class_type::*)(...) && noexcept>();
    test_is_same_rcv<int (class_type::*)(...) const noexcept>();
    test_is_same_rcv<int (class_type::*)(...) const & noexcept>();
    test_is_same_rcv<int (class_type::*)(...) const && noexcept>();

    test_is_same_rcv<int (class_type::*)(int, ...)>();
    test_is_same_rcv<int (class_type::*)(int, ...)&>();
    test_is_same_rcv<int (class_type::*)(int, ...) &&>();
    test_is_same_rcv<int (class_type::*)(int, ...) const>();
    test_is_same_rcv<int (class_type::*)(int, ...) const&>();
    test_is_same_rcv<int (class_type::*)(int, ...) const&&>();
    test_is_same_rcv<int (class_type::*)(int, ...) noexcept>();
    test_is_same_rcv<int (class_type::*)(int, ...) & noexcept>();
    test_is_same_rcv<int (class_type::*)(int, ...) && noexcept>();
    test_is_same_rcv<int (class_type::*)(int, ...) const noexcept>();
    test_is_same_rcv<int (class_type::*)(int, ...) const & noexcept>();
    test_is_same_rcv<int (class_type::*)(int, ...) const && noexcept>();
}
