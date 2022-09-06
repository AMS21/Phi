#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/add_lvalue_reference.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT, typename OtherT = TypeT&>
void test_add_lvalue_reference()
{
    CHECK_SAME_TYPE(typename phi::add_lvalue_reference<TypeT>::type, OtherT);
    CHECK_SAME_TYPE(const typename phi::add_lvalue_reference<TypeT>::type, const OtherT);
    CHECK_SAME_TYPE(volatile typename phi::add_lvalue_reference<TypeT>::type, volatile OtherT);
    CHECK_SAME_TYPE(const volatile typename phi::add_lvalue_reference<TypeT>::type,
                    const volatile OtherT);

    CHECK_SAME_TYPE(phi::add_lvalue_reference_t<TypeT>, OtherT);
    CHECK_SAME_TYPE(const phi::add_lvalue_reference_t<TypeT>, const OtherT);
    CHECK_SAME_TYPE(volatile phi::add_lvalue_reference_t<TypeT>, volatile OtherT);
    CHECK_SAME_TYPE(const volatile phi::add_lvalue_reference_t<TypeT>, const volatile OtherT);

    // Standard compatibility
    CHECK_SAME_TYPE(typename phi::add_lvalue_reference<TypeT>::type,
                    typename std::add_lvalue_reference<TypeT>::type);
    CHECK_SAME_TYPE(phi::add_lvalue_reference_t<TypeT>,
                    typename std::add_lvalue_reference<TypeT>::type);
    CHECK_SAME_TYPE(typename phi::add_lvalue_reference<const TypeT>::type,
                    typename std::add_lvalue_reference<const TypeT>::type);
    CHECK_SAME_TYPE(phi::add_lvalue_reference_t<const TypeT>,
                    typename std::add_lvalue_reference<const TypeT>::type);
    CHECK_SAME_TYPE(typename phi::add_lvalue_reference<volatile TypeT>::type,
                    typename std::add_lvalue_reference<volatile TypeT>::type);
    CHECK_SAME_TYPE(phi::add_lvalue_reference_t<volatile TypeT>,
                    typename std::add_lvalue_reference<volatile TypeT>::type);
    CHECK_SAME_TYPE(typename phi::add_lvalue_reference<const volatile TypeT>::type,
                    typename std::add_lvalue_reference<const volatile TypeT>::type);
    CHECK_SAME_TYPE(phi::add_lvalue_reference_t<const volatile TypeT>,
                    typename std::add_lvalue_reference<const volatile TypeT>::type);
}

template <typename FunctionT>
void test_add_lvalue_reference_function0()
{
    CHECK_SAME_TYPE(FunctionT&, typename phi::add_lvalue_reference<FunctionT>::type);
    CHECK_SAME_TYPE(FunctionT&, phi::add_lvalue_reference_t<FunctionT>);

    // Standard compatibility
    CHECK_SAME_TYPE(typename phi::add_lvalue_reference<FunctionT>::type,
                    typename std::add_lvalue_reference<FunctionT>::type);
    CHECK_SAME_TYPE(phi::add_lvalue_reference_t<FunctionT>,
                    typename std::add_lvalue_reference<FunctionT>::type);
}

template <typename FunctionT>
void test_add_lvalue_reference_function1()
{
    CHECK_SAME_TYPE(FunctionT, typename phi::add_lvalue_reference<FunctionT>::type);
    CHECK_SAME_TYPE(FunctionT, phi::add_lvalue_reference_t<FunctionT>);

    // Standard compatibility
    CHECK_SAME_TYPE(typename phi::add_lvalue_reference<FunctionT>::type,
                    typename std::add_lvalue_reference<FunctionT>::type);
    CHECK_SAME_TYPE(phi::add_lvalue_reference_t<FunctionT>,
                    typename std::add_lvalue_reference<FunctionT>::type);
}

struct A; // incomplete

struct Foo
{};

TEST_CASE("add_lvalue_reference")
{
    test_add_lvalue_reference<A, A&>();
    test_add_lvalue_reference<Foo, Foo&>();

    //  LWG 2101 specifically talks about add_lvalue_reference and functions.
    //  The term of art is "a referenceable type", which a cv- or ref-qualified function is not.
    test_add_lvalue_reference_function0<void()>();
    test_add_lvalue_reference_function1<void() const>();
    test_add_lvalue_reference_function1<void()&>();
    test_add_lvalue_reference_function1<void() &&>();
    test_add_lvalue_reference_function1<void() const&>();
    test_add_lvalue_reference_function1<void() const&&>();

    //  But a cv- or ref-qualified member function *is* "a referenceable type"
    test_add_lvalue_reference_function0<void (Foo::*)()>();
    test_add_lvalue_reference_function0<void (Foo::*)() const>();
    test_add_lvalue_reference_function0<void (Foo::*)()&>();
    test_add_lvalue_reference_function0<void (Foo::*)() &&>();
    test_add_lvalue_reference_function0<void (Foo::*)() const&>();
    test_add_lvalue_reference_function0<void (Foo::*)() const&&>();

    test_add_lvalue_reference<bool(int) const, bool(int) const>();
    test_add_lvalue_reference<bool(int)&, bool(int)&>();
    test_add_lvalue_reference<bool(int) const&, bool(int) const&>();
    test_add_lvalue_reference<bool(int)&&, bool(int) &&>();
    test_add_lvalue_reference<bool(int) const&&, bool(int) const&&>();
    test_add_lvalue_reference<bool(int)>();

    test_add_lvalue_reference<void, void>();
    test_add_lvalue_reference<phi::nullptr_t>();
    test_add_lvalue_reference<bool>();
    test_add_lvalue_reference<char>();
    test_add_lvalue_reference<signed char>();
    test_add_lvalue_reference<unsigned char>();
    test_add_lvalue_reference<short>();
    test_add_lvalue_reference<unsigned short>();
    test_add_lvalue_reference<int>();
    test_add_lvalue_reference<unsigned int>();
    test_add_lvalue_reference<long>();
    test_add_lvalue_reference<unsigned long>();
    test_add_lvalue_reference<long long>();
    test_add_lvalue_reference<unsigned long long>();
    test_add_lvalue_reference<float>();
    test_add_lvalue_reference<double>();
    test_add_lvalue_reference<long double>();
    test_add_lvalue_reference<char8_t>();
    test_add_lvalue_reference<char16_t>();
    test_add_lvalue_reference<char32_t>();
    test_add_lvalue_reference<wchar_t>();

    test_add_lvalue_reference<phi::boolean>();
    test_add_lvalue_reference<phi::integer<signed char>>();
    test_add_lvalue_reference<phi::integer<unsigned char>>();
    test_add_lvalue_reference<phi::integer<short>>();
    test_add_lvalue_reference<phi::integer<unsigned short>>();
    test_add_lvalue_reference<phi::integer<int>>();
    test_add_lvalue_reference<phi::integer<unsigned int>>();
    test_add_lvalue_reference<phi::integer<long>>();
    test_add_lvalue_reference<phi::integer<unsigned long>>();
    test_add_lvalue_reference<phi::integer<long long>>();
    test_add_lvalue_reference<phi::integer<unsigned long long>>();
    test_add_lvalue_reference<phi::floating_point<float>>();
    test_add_lvalue_reference<phi::floating_point<double>>();
    test_add_lvalue_reference<phi::floating_point<long double>>();

    test_add_lvalue_reference<std::vector<int>>();
    test_add_lvalue_reference<phi::scope_ptr<int>>();

    test_add_lvalue_reference<int&>();
    test_add_lvalue_reference<const int&>();
    test_add_lvalue_reference<volatile int&>();
    test_add_lvalue_reference<const volatile int&>();
    test_add_lvalue_reference<int&&>();
    test_add_lvalue_reference<const int&&>();
    test_add_lvalue_reference<volatile int&&>();
    test_add_lvalue_reference<const volatile int&&>();
    test_add_lvalue_reference<int*>();
    test_add_lvalue_reference<const int*>();
    test_add_lvalue_reference<volatile int*>();
    test_add_lvalue_reference<const volatile int*>();
    test_add_lvalue_reference<int**>();
    test_add_lvalue_reference<const int**>();
    test_add_lvalue_reference<volatile int**>();
    test_add_lvalue_reference<const volatile int**>();
    test_add_lvalue_reference<int*&>();
    test_add_lvalue_reference<const int*&>();
    test_add_lvalue_reference<volatile int*&>();
    test_add_lvalue_reference<const volatile int*&>();
    test_add_lvalue_reference<int*&&>();
    test_add_lvalue_reference<const int*&&>();
    test_add_lvalue_reference<volatile int*&&>();
    test_add_lvalue_reference<const volatile int*&&>();
    test_add_lvalue_reference<void*>();
    test_add_lvalue_reference<char[3]>();
    test_add_lvalue_reference<char[]>();
    test_add_lvalue_reference<char* [3]>();
    test_add_lvalue_reference<char*[]>();
    test_add_lvalue_reference<int(*)[3]>();
    test_add_lvalue_reference<int(*)[]>();
    test_add_lvalue_reference<int(&)[3]>();
    test_add_lvalue_reference<int(&)[]>();
    test_add_lvalue_reference<int(&&)[3]>();
    test_add_lvalue_reference<int(&&)[]>();
    test_add_lvalue_reference<char[3][2]>();
    test_add_lvalue_reference<char[][2]>();
    test_add_lvalue_reference<char* [3][2]>();
    test_add_lvalue_reference<char*[][2]>();
    test_add_lvalue_reference<int(*)[3][2]>();
    test_add_lvalue_reference<int(*)[][2]>();
    test_add_lvalue_reference<int(&)[3][2]>();
    test_add_lvalue_reference<int(&)[][2]>();
    test_add_lvalue_reference<int(&&)[3][2]>();
    test_add_lvalue_reference<int(&&)[][2]>();
    test_add_lvalue_reference<class_type>();
    test_add_lvalue_reference<class_type[]>();
    test_add_lvalue_reference<class_type[2]>();
    test_add_lvalue_reference<template_type<void>>();
    test_add_lvalue_reference<template_type<int>>();
    test_add_lvalue_reference<template_type<class_type>>();
    test_add_lvalue_reference<template_type<incomplete_type>>();
    test_add_lvalue_reference<variadic_template<>>();
    test_add_lvalue_reference<variadic_template<void>>();
    test_add_lvalue_reference<variadic_template<int>>();
    test_add_lvalue_reference<variadic_template<class_type>>();
    test_add_lvalue_reference<variadic_template<incomplete_type>>();
    test_add_lvalue_reference<variadic_template<int, void, class_type, volatile char[]>>();
    test_add_lvalue_reference<public_derived_from<base>>();
    test_add_lvalue_reference<public_derived_from<derived>>();
    test_add_lvalue_reference<public_derived_from<class_type>>();
    test_add_lvalue_reference<private_derived_from<base>>();
    test_add_lvalue_reference<private_derived_from<derived>>();
    test_add_lvalue_reference<private_derived_from<class_type>>();
    test_add_lvalue_reference<protected_derived_from<base>>();
    test_add_lvalue_reference<protected_derived_from<derived>>();
    test_add_lvalue_reference<protected_derived_from<class_type>>();
    test_add_lvalue_reference<virtual_derived_from<base>>();
    test_add_lvalue_reference<virtual_derived_from<derived>>();
    test_add_lvalue_reference<virtual_derived_from<class_type>>();
    test_add_lvalue_reference<union_type>();
    test_add_lvalue_reference<non_empty_union>();
    test_add_lvalue_reference<non_trivial_union>();
    test_add_lvalue_reference<empty>();
    test_add_lvalue_reference<not_empty>();
    test_add_lvalue_reference<non_trivial>();
    test_add_lvalue_reference<bit_zero>();
    test_add_lvalue_reference<bit_one>();
    test_add_lvalue_reference<base>();
    test_add_lvalue_reference<derived>();
    test_add_lvalue_reference<non_empty_base>();
    test_add_lvalue_reference<empty_base>();
    test_add_lvalue_reference<virtual_base>();
    test_add_lvalue_reference<polymorphic>();
    test_add_lvalue_reference<derived_polymorphic>();
    test_add_lvalue_reference<abstract>();
    test_add_lvalue_reference<public_abstract>();
    test_add_lvalue_reference<private_abstract>();
    test_add_lvalue_reference<protected_abstract>();
    test_add_lvalue_reference<abstract_template<int>>();
    test_add_lvalue_reference<abstract_template<double>>();
    test_add_lvalue_reference<abstract_template<class_type>>();
    test_add_lvalue_reference<abstract_template<incomplete_type>>();
    test_add_lvalue_reference<public_abstract_deleted_destructor>();
    test_add_lvalue_reference<protected_abstract_deleted_destructor>();
    test_add_lvalue_reference<private_abstract_deleted_destructor>();
    test_add_lvalue_reference<final_type>();
    test_add_lvalue_reference<final_derived>();
    test_add_lvalue_reference<public_destructor>();
    test_add_lvalue_reference<protected_destructor>();
    test_add_lvalue_reference<private_destructor>();
    test_add_lvalue_reference<virtual_public_destructor>();
    test_add_lvalue_reference<virtual_protected_destructor>();
    test_add_lvalue_reference<virtual_private_destructor>();
    test_add_lvalue_reference<pure_public_destructor>();
    test_add_lvalue_reference<pure_protected_destructor>();
    test_add_lvalue_reference<pure_private_destructor>();
    test_add_lvalue_reference<deleted_public_destructor>();
    test_add_lvalue_reference<deleted_protected_destructor>();
    test_add_lvalue_reference<deleted_private_destructor>();
    test_add_lvalue_reference<deleted_virtual_public_destructor>();
    test_add_lvalue_reference<deleted_virtual_protected_destructor>();
    test_add_lvalue_reference<deleted_virtual_private_destructor>();
    test_add_lvalue_reference<explicit_class>();
    test_add_lvalue_reference<nothrow_explicit_class>();
    test_add_lvalue_reference<throw_explicit_class>();
    test_add_lvalue_reference<throw_default_class>();
    test_add_lvalue_reference<throw_copy_constructible_class>();
    test_add_lvalue_reference<throw_move_constructible_class>();
    test_add_lvalue_reference<throw_destructor>();
    test_add_lvalue_reference<noexcept_explicit_class>();
    test_add_lvalue_reference<except_explicit_class>();
    test_add_lvalue_reference<noexcept_default_class>();
    test_add_lvalue_reference<except_default_class>();
    test_add_lvalue_reference<noexcept_copy_constructible_class>();
    test_add_lvalue_reference<except_copy_constructible_class>();
    test_add_lvalue_reference<noexcept_move_constructible_class>();
    test_add_lvalue_reference<except_move_constructible_class>();
    test_add_lvalue_reference<noexcept_copy_assign_class>();
    test_add_lvalue_reference<except_copy_assign_class>();
    test_add_lvalue_reference<noexcept_move_assign_class>();
    test_add_lvalue_reference<except_move_assign_class>();
    test_add_lvalue_reference<deleted_copy_assign_class>();
    test_add_lvalue_reference<deleted_move_assign_class>();
    test_add_lvalue_reference<noexcept_move_constructible_and_assignable_class>();
    test_add_lvalue_reference<except_move_constructible_noexcept_move_assign_class>();
    test_add_lvalue_reference<noexcept_move_constructible_except_move_assign_class>();
    test_add_lvalue_reference<except_move_constructible_and_assign_class>();
    test_add_lvalue_reference<implicit_to<int>>();
    test_add_lvalue_reference<implicit_to<float>>();
    test_add_lvalue_reference<implicit_to<class_type>>();
    test_add_lvalue_reference<deleted_implicit_to<int>>();
    test_add_lvalue_reference<deleted_implicit_to<float>>();
    test_add_lvalue_reference<deleted_implicit_to<class_type>>();
    test_add_lvalue_reference<explicit_to<int>>();
    test_add_lvalue_reference<explicit_to<float>>();
    test_add_lvalue_reference<explicit_to<class_type>>();
    test_add_lvalue_reference<deleted_explicit_to<int>>();
    test_add_lvalue_reference<deleted_explicit_to<float>>();
    test_add_lvalue_reference<deleted_explicit_to<class_type>>();
    test_add_lvalue_reference<ellipsis>();
    test_add_lvalue_reference<deleted_ellipsis>();
    test_add_lvalue_reference<copy_constructible_only_type>();
    test_add_lvalue_reference<move_constructible_only_type>();
    test_add_lvalue_reference<overloaded_operators>();
    test_add_lvalue_reference<public_int_member>();
    test_add_lvalue_reference<protected_int_member>();
    test_add_lvalue_reference<private_int_member>();
    test_add_lvalue_reference<public_static_int_member>();
    test_add_lvalue_reference<protected_static_int_member>();
    test_add_lvalue_reference<private_static_int_member>();
    test_add_lvalue_reference<public_template_member<int>>();
    test_add_lvalue_reference<public_template_member<float>>();
    test_add_lvalue_reference<public_template_member<class_type>>();
    test_add_lvalue_reference<protected_template_member<int>>();
    test_add_lvalue_reference<protected_template_member<float>>();
    test_add_lvalue_reference<protected_template_member<class_type>>();
    test_add_lvalue_reference<private_template_member<int>>();
    test_add_lvalue_reference<private_template_member<float>>();
    test_add_lvalue_reference<private_template_member<class_type>>();
    test_add_lvalue_reference<public_static_template_member<int>>();
    test_add_lvalue_reference<public_static_template_member<float>>();
    test_add_lvalue_reference<public_static_template_member<class_type>>();
    test_add_lvalue_reference<protected_static_template_member<int>>();
    test_add_lvalue_reference<protected_static_template_member<float>>();
    test_add_lvalue_reference<protected_static_template_member<class_type>>();
    test_add_lvalue_reference<private_static_template_member<int>>();
    test_add_lvalue_reference<private_static_template_member<float>>();
    test_add_lvalue_reference<private_static_template_member<class_type>>();
    test_add_lvalue_reference<cannot_instantiate<int>>();
    test_add_lvalue_reference<cannot_instantiate<float>>();
    test_add_lvalue_reference<cannot_instantiate<class_type>>();
    test_add_lvalue_reference<Enum>();
    test_add_lvalue_reference<EnumSigned>();
    test_add_lvalue_reference<EnumUnsigned>();
    test_add_lvalue_reference<EnumClass>();
    test_add_lvalue_reference<EnumStruct>();
    test_add_lvalue_reference<function_type>();
    test_add_lvalue_reference<function_ptr>();
    test_add_lvalue_reference<member_object_ptr>();
    test_add_lvalue_reference<member_function_ptr>();
    test_add_lvalue_reference<lambda_type>();
    test_add_lvalue_reference<lambda_noexcept_type>();
    test_add_lvalue_reference<lambda_throws_type>();
    test_add_lvalue_reference<incomplete_type>();
    test_add_lvalue_reference<incomplete_template<void>>();
    test_add_lvalue_reference<incomplete_template<int>>();
    test_add_lvalue_reference<incomplete_template<class_type>>();
    test_add_lvalue_reference<incomplete_template<incomplete_type>>();
    test_add_lvalue_reference<incomplete_variadic_template<>>();
    test_add_lvalue_reference<incomplete_variadic_template<void>>();
    test_add_lvalue_reference<incomplete_variadic_template<int>>();
    test_add_lvalue_reference<incomplete_variadic_template<class_type>>();
    test_add_lvalue_reference<incomplete_variadic_template<incomplete_type>>();
    test_add_lvalue_reference<
            incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_add_lvalue_reference<incomplete_union>();
    test_add_lvalue_reference<IncompleteEnumSigned>();
    test_add_lvalue_reference<IncompleteEnumUnsigned>();
    test_add_lvalue_reference<IncompleteEnumClass>();
    test_add_lvalue_reference<IncompleteEnumStruct>();
    test_add_lvalue_reference<int class_type::*>();
    test_add_lvalue_reference<float class_type::*>();
    test_add_lvalue_reference<void * class_type::*>();
    test_add_lvalue_reference<int * class_type::*>();
    test_add_lvalue_reference<Enum class_type::*>();
    test_add_lvalue_reference<not_empty class_type::*>();
    test_add_lvalue_reference<int class_type::*&>();
    test_add_lvalue_reference<float class_type::*&>();
    test_add_lvalue_reference<void * class_type::*&>();
    test_add_lvalue_reference<int * class_type::*&>();
    test_add_lvalue_reference<Enum class_type::*&>();
    test_add_lvalue_reference<not_empty class_type::*&>();
    test_add_lvalue_reference<int class_type::*&&>();
    test_add_lvalue_reference<float class_type::*&&>();
    test_add_lvalue_reference<void * class_type::*&&>();
    test_add_lvalue_reference<int * class_type::*&&>();
    test_add_lvalue_reference<Enum class_type::*&&>();
    test_add_lvalue_reference<not_empty class_type::*&&>();
    test_add_lvalue_reference<non_default_constructible>();
    test_add_lvalue_reference<non_copy_constructible>();
    test_add_lvalue_reference<non_move_constructible>();
    test_add_lvalue_reference<non_copy_assignable>();
    test_add_lvalue_reference<non_move_assignable>();
    test_add_lvalue_reference<non_assignable>();
    test_add_lvalue_reference<non_copyable>();
    test_add_lvalue_reference<non_moveable>();
    test_add_lvalue_reference<non_constructible>();
    test_add_lvalue_reference<non_destructible>();
    test_add_lvalue_reference<tracked>();
    test_add_lvalue_reference<trap_constructible>();
    test_add_lvalue_reference<trap_implicit_conversion>();
    test_add_lvalue_reference<trap_comma>();
    test_add_lvalue_reference<trap_call>();
    test_add_lvalue_reference<trap_self_assign>();
    test_add_lvalue_reference<trap_deref>();
    test_add_lvalue_reference<trap_array_subscript>();

    test_add_lvalue_reference<void()>();
    test_add_lvalue_reference_function1<void()&>();
    test_add_lvalue_reference_function1<void() &&>();
    test_add_lvalue_reference_function1<void() const>();
    test_add_lvalue_reference_function1<void() const&>();
    test_add_lvalue_reference_function1<void() const&&>();
    test_add_lvalue_reference_function1<void() volatile>();
    test_add_lvalue_reference_function1<void() volatile&>();
    test_add_lvalue_reference_function1<void() volatile&&>();
    test_add_lvalue_reference_function1<void() const volatile>();
    test_add_lvalue_reference_function1<void() const volatile&>();
    test_add_lvalue_reference_function1<void() const volatile&&>();
    test_add_lvalue_reference<void() noexcept>();
    test_add_lvalue_reference_function1<void() & noexcept>();
    test_add_lvalue_reference_function1<void() && noexcept>();
    test_add_lvalue_reference_function1<void() const noexcept>();
    test_add_lvalue_reference_function1<void() const & noexcept>();
    test_add_lvalue_reference_function1<void() const && noexcept>();
    test_add_lvalue_reference_function1<void() volatile noexcept>();
    test_add_lvalue_reference_function1<void() volatile & noexcept>();
    test_add_lvalue_reference_function1<void() volatile && noexcept>();
    test_add_lvalue_reference_function1<void() const volatile noexcept>();
    test_add_lvalue_reference_function1<void() const volatile & noexcept>();
    test_add_lvalue_reference_function1<void() const volatile && noexcept>();

    test_add_lvalue_reference<void(int)>();
    test_add_lvalue_reference_function1<void(int)&>();
    test_add_lvalue_reference_function1<void(int) &&>();
    test_add_lvalue_reference_function1<void(int) const>();
    test_add_lvalue_reference_function1<void(int) const&>();
    test_add_lvalue_reference_function1<void(int) const&&>();
    test_add_lvalue_reference_function1<void(int) volatile>();
    test_add_lvalue_reference_function1<void(int) volatile&>();
    test_add_lvalue_reference_function1<void(int) volatile&&>();
    test_add_lvalue_reference_function1<void(int) const volatile>();
    test_add_lvalue_reference_function1<void(int) const volatile&>();
    test_add_lvalue_reference_function1<void(int) const volatile&&>();
    test_add_lvalue_reference<void(int) noexcept>();
    test_add_lvalue_reference_function1<void(int) & noexcept>();
    test_add_lvalue_reference_function1<void(int) && noexcept>();
    test_add_lvalue_reference_function1<void(int) const noexcept>();
    test_add_lvalue_reference_function1<void(int) const & noexcept>();
    test_add_lvalue_reference_function1<void(int) const && noexcept>();
    test_add_lvalue_reference_function1<void(int) volatile noexcept>();
    test_add_lvalue_reference_function1<void(int) volatile & noexcept>();
    test_add_lvalue_reference_function1<void(int) volatile && noexcept>();
    test_add_lvalue_reference_function1<void(int) const volatile noexcept>();
    test_add_lvalue_reference_function1<void(int) const volatile & noexcept>();
    test_add_lvalue_reference_function1<void(int) const volatile && noexcept>();

    test_add_lvalue_reference<void(...)>();
    test_add_lvalue_reference_function1<void(...)&>();
    test_add_lvalue_reference_function1<void(...) &&>();
    test_add_lvalue_reference_function1<void(...) const>();
    test_add_lvalue_reference_function1<void(...) const&>();
    test_add_lvalue_reference_function1<void(...) const&&>();
    test_add_lvalue_reference_function1<void(...) volatile>();
    test_add_lvalue_reference_function1<void(...) volatile&>();
    test_add_lvalue_reference_function1<void(...) volatile&&>();
    test_add_lvalue_reference_function1<void(...) const volatile>();
    test_add_lvalue_reference_function1<void(...) const volatile&>();
    test_add_lvalue_reference_function1<void(...) const volatile&&>();
    test_add_lvalue_reference<void(...) noexcept>();
    test_add_lvalue_reference_function1<void(...) & noexcept>();
    test_add_lvalue_reference_function1<void(...) && noexcept>();
    test_add_lvalue_reference_function1<void(...) const noexcept>();
    test_add_lvalue_reference_function1<void(...) const & noexcept>();
    test_add_lvalue_reference_function1<void(...) const && noexcept>();
    test_add_lvalue_reference_function1<void(...) volatile noexcept>();
    test_add_lvalue_reference_function1<void(...) volatile & noexcept>();
    test_add_lvalue_reference_function1<void(...) volatile && noexcept>();
    test_add_lvalue_reference_function1<void(...) const volatile noexcept>();
    test_add_lvalue_reference_function1<void(...) const volatile & noexcept>();
    test_add_lvalue_reference_function1<void(...) const volatile && noexcept>();

    test_add_lvalue_reference<void(int, ...)>();
    test_add_lvalue_reference_function1<void(int, ...)&>();
    test_add_lvalue_reference_function1<void(int, ...) &&>();
    test_add_lvalue_reference_function1<void(int, ...) const>();
    test_add_lvalue_reference_function1<void(int, ...) const&>();
    test_add_lvalue_reference_function1<void(int, ...) const&&>();
    test_add_lvalue_reference_function1<void(int, ...) volatile>();
    test_add_lvalue_reference_function1<void(int, ...) volatile&>();
    test_add_lvalue_reference_function1<void(int, ...) volatile&&>();
    test_add_lvalue_reference_function1<void(int, ...) const volatile>();
    test_add_lvalue_reference_function1<void(int, ...) const volatile&>();
    test_add_lvalue_reference_function1<void(int, ...) const volatile&&>();
    test_add_lvalue_reference<void(int, ...) noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) & noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) && noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) const noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) const & noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) const && noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) volatile noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) volatile & noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) volatile && noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) const volatile noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) const volatile & noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) const volatile && noexcept>();

    test_add_lvalue_reference<int()>();
    test_add_lvalue_reference_function1<int()&>();
    test_add_lvalue_reference_function1<int() &&>();
    test_add_lvalue_reference_function1<int() const>();
    test_add_lvalue_reference_function1<int() const&>();
    test_add_lvalue_reference_function1<int() const&&>();
    test_add_lvalue_reference_function1<int() volatile>();
    test_add_lvalue_reference_function1<int() volatile&>();
    test_add_lvalue_reference_function1<int() volatile&&>();
    test_add_lvalue_reference_function1<int() const volatile>();
    test_add_lvalue_reference_function1<int() const volatile&>();
    test_add_lvalue_reference_function1<int() const volatile&&>();
    test_add_lvalue_reference<int() noexcept>();
    test_add_lvalue_reference_function1<int() & noexcept>();
    test_add_lvalue_reference_function1<int() && noexcept>();
    test_add_lvalue_reference_function1<int() const noexcept>();
    test_add_lvalue_reference_function1<int() const & noexcept>();
    test_add_lvalue_reference_function1<int() const && noexcept>();
    test_add_lvalue_reference_function1<int() volatile noexcept>();
    test_add_lvalue_reference_function1<int() volatile & noexcept>();
    test_add_lvalue_reference_function1<int() volatile && noexcept>();
    test_add_lvalue_reference_function1<int() const volatile noexcept>();
    test_add_lvalue_reference_function1<int() const volatile & noexcept>();
    test_add_lvalue_reference_function1<int() const volatile && noexcept>();

    test_add_lvalue_reference<int(int)>();
    test_add_lvalue_reference_function1<int(int)&>();
    test_add_lvalue_reference_function1<int(int) &&>();
    test_add_lvalue_reference_function1<int(int) const>();
    test_add_lvalue_reference_function1<int(int) const&>();
    test_add_lvalue_reference_function1<int(int) const&&>();
    test_add_lvalue_reference_function1<int(int) volatile>();
    test_add_lvalue_reference_function1<int(int) volatile&>();
    test_add_lvalue_reference_function1<int(int) volatile&&>();
    test_add_lvalue_reference_function1<int(int) const volatile>();
    test_add_lvalue_reference_function1<int(int) const volatile&>();
    test_add_lvalue_reference_function1<int(int) const volatile&&>();
    test_add_lvalue_reference<int(int) noexcept>();
    test_add_lvalue_reference_function1<int(int) & noexcept>();
    test_add_lvalue_reference_function1<int(int) && noexcept>();
    test_add_lvalue_reference_function1<int(int) const noexcept>();
    test_add_lvalue_reference_function1<int(int) const & noexcept>();
    test_add_lvalue_reference_function1<int(int) const && noexcept>();
    test_add_lvalue_reference_function1<int(int) volatile noexcept>();
    test_add_lvalue_reference_function1<int(int) volatile & noexcept>();
    test_add_lvalue_reference_function1<int(int) volatile && noexcept>();
    test_add_lvalue_reference_function1<int(int) const volatile noexcept>();
    test_add_lvalue_reference_function1<int(int) const volatile & noexcept>();
    test_add_lvalue_reference_function1<int(int) const volatile && noexcept>();

    test_add_lvalue_reference<int(...)>();
    test_add_lvalue_reference_function1<int(...)&>();
    test_add_lvalue_reference_function1<int(...) &&>();
    test_add_lvalue_reference_function1<int(...) const>();
    test_add_lvalue_reference_function1<int(...) const&>();
    test_add_lvalue_reference_function1<int(...) const&&>();
    test_add_lvalue_reference_function1<int(...) volatile>();
    test_add_lvalue_reference_function1<int(...) volatile&>();
    test_add_lvalue_reference_function1<int(...) volatile&&>();
    test_add_lvalue_reference_function1<int(...) const volatile>();
    test_add_lvalue_reference_function1<int(...) const volatile&>();
    test_add_lvalue_reference_function1<int(...) const volatile&&>();
    test_add_lvalue_reference<int(...) noexcept>();
    test_add_lvalue_reference_function1<int(...) & noexcept>();
    test_add_lvalue_reference_function1<int(...) && noexcept>();
    test_add_lvalue_reference_function1<int(...) const noexcept>();
    test_add_lvalue_reference_function1<int(...) const & noexcept>();
    test_add_lvalue_reference_function1<int(...) const && noexcept>();
    test_add_lvalue_reference_function1<int(...) volatile noexcept>();
    test_add_lvalue_reference_function1<int(...) volatile & noexcept>();
    test_add_lvalue_reference_function1<int(...) volatile && noexcept>();
    test_add_lvalue_reference_function1<int(...) const volatile noexcept>();
    test_add_lvalue_reference_function1<int(...) const volatile & noexcept>();
    test_add_lvalue_reference_function1<int(...) const volatile && noexcept>();

    test_add_lvalue_reference<int(int, ...)>();
    test_add_lvalue_reference_function1<int(int, ...)&>();
    test_add_lvalue_reference_function1<int(int, ...) &&>();
    test_add_lvalue_reference_function1<int(int, ...) const>();
    test_add_lvalue_reference_function1<int(int, ...) const&>();
    test_add_lvalue_reference_function1<int(int, ...) const&&>();
    test_add_lvalue_reference_function1<int(int, ...) volatile>();
    test_add_lvalue_reference_function1<int(int, ...) volatile&>();
    test_add_lvalue_reference_function1<int(int, ...) volatile&&>();
    test_add_lvalue_reference_function1<int(int, ...) const volatile>();
    test_add_lvalue_reference_function1<int(int, ...) const volatile&>();
    test_add_lvalue_reference_function1<int(int, ...) const volatile&&>();
    test_add_lvalue_reference<int(int, ...) noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) & noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) && noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) const noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) const & noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) const && noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) volatile noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) volatile & noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) volatile && noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) const volatile noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) const volatile & noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) const volatile && noexcept>();

    test_add_lvalue_reference<void (*)()>();
    test_add_lvalue_reference<void (*)() noexcept>();

    test_add_lvalue_reference<void (*)(int)>();
    test_add_lvalue_reference<void (*)(int) noexcept>();

    test_add_lvalue_reference<void (*)(...)>();
    test_add_lvalue_reference<void (*)(...) noexcept>();

    test_add_lvalue_reference<void (*)(int, ...)>();
    test_add_lvalue_reference<void (*)(int, ...) noexcept>();

    test_add_lvalue_reference<int (*)()>();
    test_add_lvalue_reference<int (*)() noexcept>();

    test_add_lvalue_reference<int (*)(int)>();
    test_add_lvalue_reference<int (*)(int) noexcept>();

    test_add_lvalue_reference<int (*)(...)>();
    test_add_lvalue_reference<int (*)(...) noexcept>();

    test_add_lvalue_reference<int (*)(int, ...)>();
    test_add_lvalue_reference<int (*)(int, ...) noexcept>();

    test_add_lvalue_reference<void (&)()>();
    test_add_lvalue_reference<void (&)() noexcept>();

    test_add_lvalue_reference<void (&)(int)>();
    test_add_lvalue_reference<void (&)(int) noexcept>();

    test_add_lvalue_reference<void (&)(...)>();
    test_add_lvalue_reference<void (&)(...) noexcept>();

    test_add_lvalue_reference<void (&)(int, ...)>();
    test_add_lvalue_reference<void (&)(int, ...) noexcept>();

    test_add_lvalue_reference<int (&)()>();
    test_add_lvalue_reference<int (&)() noexcept>();

    test_add_lvalue_reference<int (&)(int)>();
    test_add_lvalue_reference<int (&)(int) noexcept>();

    test_add_lvalue_reference<int (&)(...)>();
    test_add_lvalue_reference<int (&)(...) noexcept>();

    test_add_lvalue_reference<int (&)(int, ...)>();
    test_add_lvalue_reference<int (&)(int, ...) noexcept>();

    test_add_lvalue_reference<void (&&)()>();
    test_add_lvalue_reference<void (&&)() noexcept>();

    test_add_lvalue_reference<void (&&)(int)>();
    test_add_lvalue_reference<void (&&)(int) noexcept>();

    test_add_lvalue_reference<void (&&)(...)>();
    test_add_lvalue_reference<void (&&)(...) noexcept>();

    test_add_lvalue_reference<void (&&)(int, ...)>();
    test_add_lvalue_reference<void (&&)(int, ...) noexcept>();

    test_add_lvalue_reference<int (&&)()>();
    test_add_lvalue_reference<int (&&)() noexcept>();

    test_add_lvalue_reference<int (&&)(int)>();
    test_add_lvalue_reference<int (&&)(int) noexcept>();

    test_add_lvalue_reference<int (&&)(...)>();
    test_add_lvalue_reference<int (&&)(...) noexcept>();

    test_add_lvalue_reference<int (&&)(int, ...)>();
    test_add_lvalue_reference<int (&&)(int, ...) noexcept>();

    test_add_lvalue_reference<void (class_type::*)()>();
    test_add_lvalue_reference<void (class_type::*)()&>();
    test_add_lvalue_reference<void (class_type::*)() &&>();
    test_add_lvalue_reference<void (class_type::*)() const>();
    test_add_lvalue_reference<void (class_type::*)() const&>();
    test_add_lvalue_reference<void (class_type::*)() const&&>();
    test_add_lvalue_reference<void (class_type::*)() noexcept>();
    test_add_lvalue_reference<void (class_type::*)() & noexcept>();
    test_add_lvalue_reference<void (class_type::*)() && noexcept>();
    test_add_lvalue_reference<void (class_type::*)() const noexcept>();
    test_add_lvalue_reference<void (class_type::*)() const & noexcept>();
    test_add_lvalue_reference<void (class_type::*)() const && noexcept>();

    test_add_lvalue_reference<void (class_type::*)(int)>();
    test_add_lvalue_reference<void (class_type::*)(int)&>();
    test_add_lvalue_reference<void (class_type::*)(int) &&>();
    test_add_lvalue_reference<void (class_type::*)(int) const>();
    test_add_lvalue_reference<void (class_type::*)(int) const&>();
    test_add_lvalue_reference<void (class_type::*)(int) const&&>();
    test_add_lvalue_reference<void (class_type::*)(int) noexcept>();
    test_add_lvalue_reference<void (class_type::*)(int) & noexcept>();
    test_add_lvalue_reference<void (class_type::*)(int) && noexcept>();
    test_add_lvalue_reference<void (class_type::*)(int) const noexcept>();
    test_add_lvalue_reference<void (class_type::*)(int) const & noexcept>();
    test_add_lvalue_reference<void (class_type::*)(int) const && noexcept>();

    test_add_lvalue_reference<void (class_type::*)(...)>();
    test_add_lvalue_reference<void (class_type::*)(...)&>();
    test_add_lvalue_reference<void (class_type::*)(...) &&>();
    test_add_lvalue_reference<void (class_type::*)(...) const>();
    test_add_lvalue_reference<void (class_type::*)(...) const&>();
    test_add_lvalue_reference<void (class_type::*)(...) const&&>();
    test_add_lvalue_reference<void (class_type::*)(...) noexcept>();
    test_add_lvalue_reference<void (class_type::*)(...) & noexcept>();
    test_add_lvalue_reference<void (class_type::*)(...) && noexcept>();
    test_add_lvalue_reference<void (class_type::*)(...) const noexcept>();
    test_add_lvalue_reference<void (class_type::*)(...) const & noexcept>();
    test_add_lvalue_reference<void (class_type::*)(...) const && noexcept>();

    test_add_lvalue_reference<void (class_type::*)(int, ...)>();
    test_add_lvalue_reference<void (class_type::*)(int, ...)&>();
    test_add_lvalue_reference<void (class_type::*)(int, ...) &&>();
    test_add_lvalue_reference<void (class_type::*)(int, ...) const>();
    test_add_lvalue_reference<void (class_type::*)(int, ...) const&>();
    test_add_lvalue_reference<void (class_type::*)(int, ...) const&&>();
    test_add_lvalue_reference<void (class_type::*)(int, ...) noexcept>();
    test_add_lvalue_reference<void (class_type::*)(int, ...) & noexcept>();
    test_add_lvalue_reference<void (class_type::*)(int, ...) && noexcept>();
    test_add_lvalue_reference<void (class_type::*)(int, ...) const noexcept>();
    test_add_lvalue_reference<void (class_type::*)(int, ...) const & noexcept>();
    test_add_lvalue_reference<void (class_type::*)(int, ...) const && noexcept>();

    test_add_lvalue_reference<int (class_type::*)()>();
    test_add_lvalue_reference<int (class_type::*)()&>();
    test_add_lvalue_reference<int (class_type::*)() &&>();
    test_add_lvalue_reference<int (class_type::*)() const>();
    test_add_lvalue_reference<int (class_type::*)() const&>();
    test_add_lvalue_reference<int (class_type::*)() const&&>();
    test_add_lvalue_reference<int (class_type::*)() noexcept>();
    test_add_lvalue_reference<int (class_type::*)() & noexcept>();
    test_add_lvalue_reference<int (class_type::*)() && noexcept>();
    test_add_lvalue_reference<int (class_type::*)() const noexcept>();
    test_add_lvalue_reference<int (class_type::*)() const & noexcept>();
    test_add_lvalue_reference<int (class_type::*)() const && noexcept>();

    test_add_lvalue_reference<int (class_type::*)(int)>();
    test_add_lvalue_reference<int (class_type::*)(int)&>();
    test_add_lvalue_reference<int (class_type::*)(int) &&>();
    test_add_lvalue_reference<int (class_type::*)(int) const>();
    test_add_lvalue_reference<int (class_type::*)(int) const&>();
    test_add_lvalue_reference<int (class_type::*)(int) const&&>();
    test_add_lvalue_reference<int (class_type::*)(int) noexcept>();
    test_add_lvalue_reference<int (class_type::*)(int) & noexcept>();
    test_add_lvalue_reference<int (class_type::*)(int) && noexcept>();
    test_add_lvalue_reference<int (class_type::*)(int) const noexcept>();
    test_add_lvalue_reference<int (class_type::*)(int) const & noexcept>();
    test_add_lvalue_reference<int (class_type::*)(int) const && noexcept>();

    test_add_lvalue_reference<int (class_type::*)(...)>();
    test_add_lvalue_reference<int (class_type::*)(...)&>();
    test_add_lvalue_reference<int (class_type::*)(...) &&>();
    test_add_lvalue_reference<int (class_type::*)(...) const>();
    test_add_lvalue_reference<int (class_type::*)(...) const&>();
    test_add_lvalue_reference<int (class_type::*)(...) const&&>();
    test_add_lvalue_reference<int (class_type::*)(...) noexcept>();
    test_add_lvalue_reference<int (class_type::*)(...) & noexcept>();
    test_add_lvalue_reference<int (class_type::*)(...) && noexcept>();
    test_add_lvalue_reference<int (class_type::*)(...) const noexcept>();
    test_add_lvalue_reference<int (class_type::*)(...) const & noexcept>();
    test_add_lvalue_reference<int (class_type::*)(...) const && noexcept>();

    test_add_lvalue_reference<int (class_type::*)(int, ...)>();
    test_add_lvalue_reference<int (class_type::*)(int, ...)&>();
    test_add_lvalue_reference<int (class_type::*)(int, ...) &&>();
    test_add_lvalue_reference<int (class_type::*)(int, ...) const>();
    test_add_lvalue_reference<int (class_type::*)(int, ...) const&>();
    test_add_lvalue_reference<int (class_type::*)(int, ...) const&&>();
    test_add_lvalue_reference<int (class_type::*)(int, ...) noexcept>();
    test_add_lvalue_reference<int (class_type::*)(int, ...) & noexcept>();
    test_add_lvalue_reference<int (class_type::*)(int, ...) && noexcept>();
    test_add_lvalue_reference<int (class_type::*)(int, ...) const noexcept>();
    test_add_lvalue_reference<int (class_type::*)(int, ...) const & noexcept>();
    test_add_lvalue_reference<int (class_type::*)(int, ...) const && noexcept>();
}
