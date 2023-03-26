#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/extensions/zero_size_array.hpp>
#include <phi/compiler_support/warning.hpp>
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

// unscoped enums
enum EnumEmpty
{
};

enum EnumWithMembers
{
    red,
    green = 20,
    blue
};

enum EnumBool : bool
{
};

enum EnumChar : char
{
};

enum EnumSignedChar : signed char
{
};

enum EnumUnsignedChar : unsigned char
{
};

enum EnumShort : short
{
};

enum EnumUnsignedShort : unsigned short
{
};

enum EnumInt : int
{
};

enum EnumUnsignedInt : unsigned
{
};

enum EnumLong : long
{
};

enum EnumUnsignedLong : unsigned long
{
};

enum EnumLongLong : long long
{
};

enum EnumUnsignedLongLong : unsigned long long
{
};

enum EnumChar8T : char8_t
{
};

enum EnumChar16T : char16_t
{
};

enum EnumChar32T : char32_t
{
};

enum EnumWCharT : wchar_t
{
};

// class enums
enum class EnumClassEmpty
{
};

enum class EnumClassWithMembers
{
    red,
    green = 20,
    blue
};

enum class EnumClassBool : bool
{
};

enum class EnumClassChar : char
{
};

enum class EnumClassSignedChar : signed char
{
};

enum class EnumClassUnsignedChar : unsigned char
{
};

enum class EnumClassShort : short
{
};

enum class EnumClassUnsignedShort : unsigned short
{
};

enum class EnumClassInt : int
{
};

enum class EnumClassUnsignedInt : unsigned
{
};

enum class EnumClassLong : long
{
};

enum class EnumClassUnsignedLong : unsigned long
{
};

enum class EnumClassLongLong : long long
{
};

enum class EnumClassUnsignedLongLong : unsigned long long
{
};

enum class EnumClassChar8T : char8_t
{
};

enum class EnumClassChar16T : char16_t
{
};

enum class EnumClassChar32T : char32_t
{
};

enum class EnumClassWCharT : wchar_t
{
};

// struct enums
enum struct EnumStructEmpty
{
};

enum struct EnumStructWithMembers
{
    red,
    green = 20,
    blue
};

enum struct EnumStructBool : bool
{
};

enum struct EnumStructChar : char
{
};

enum struct EnumStructSignedChar : signed char
{
};

enum struct EnumStructUnsignedChar : unsigned char
{
};

enum struct EnumStructShort : short
{
};

enum struct EnumStructUnsignedShort : unsigned short
{
};

enum struct EnumStructInt : int
{
};

enum struct EnumStructUnsignedInt : unsigned
{
};

enum struct EnumStructLong : long
{
};

enum struct EnumStructUnsignedLong : unsigned long
{
};

enum struct EnumStructLongLong : long long
{
};

enum struct EnumStructUnsignedLongLong : unsigned long long
{
};

enum struct EnumStructChar8T : char8_t
{
};

enum struct EnumStructChar16T : char16_t
{
};

enum struct EnumStructChar32T : char32_t
{
};

enum struct EnumStructWCharT : wchar_t
{
};

TEST_CASE("underlying_type")
{
    test_underlying_type<E, int>();
#if PHI_COMPILER_IS(MSVC) || PHI_COMPILER_IS(WINCLANG)
    test_underlying_type<F, int>();
#else
    test_underlying_type<F, unsigned>();
#endif

    // Unscoped enum
#if PHI_COMPILER_IS(MSVC) || PHI_COMPILER_IS(WINCLANG)
    test_underlying_type<EnumEmpty, int>();
    test_underlying_type<EnumWithMembers, int>();
#else
    test_underlying_type<EnumEmpty, unsigned>();
    test_underlying_type<EnumWithMembers, unsigned>();
#endif
    test_underlying_type<EnumBool, bool>();
    test_underlying_type<EnumChar, char>();
    test_underlying_type<EnumSignedChar, signed char>();
    test_underlying_type<EnumUnsignedChar, unsigned char>();
    test_underlying_type<EnumShort, short>();
    test_underlying_type<EnumUnsignedShort, unsigned short>();
    test_underlying_type<EnumInt, int>();
    test_underlying_type<EnumUnsignedInt, unsigned>();
    test_underlying_type<EnumLong, long>();
    test_underlying_type<EnumUnsignedLong, unsigned long>();
    test_underlying_type<EnumLongLong, long long>();
    test_underlying_type<EnumUnsignedLongLong, unsigned long long>();
    test_underlying_type<EnumChar8T, char8_t>();
    test_underlying_type<EnumChar16T, char16_t>();
    test_underlying_type<EnumChar32T, char32_t>();
    test_underlying_type<EnumWCharT, wchar_t>();

    // Class enum
    test_underlying_type<EnumClassEmpty, int>();
    test_underlying_type<EnumClassWithMembers, int>();
    test_underlying_type<EnumClassBool, bool>();
    test_underlying_type<EnumClassChar, char>();
    test_underlying_type<EnumClassSignedChar, signed char>();
    test_underlying_type<EnumClassUnsignedChar, unsigned char>();
    test_underlying_type<EnumClassShort, short>();
    test_underlying_type<EnumClassUnsignedShort, unsigned short>();
    test_underlying_type<EnumClassInt, int>();
    test_underlying_type<EnumClassUnsignedInt, unsigned>();
    test_underlying_type<EnumClassLong, long>();
    test_underlying_type<EnumClassUnsignedLong, unsigned long>();
    test_underlying_type<EnumClassLongLong, long long>();
    test_underlying_type<EnumClassUnsignedLongLong, unsigned long long>();
    test_underlying_type<EnumClassChar8T, char8_t>();
    test_underlying_type<EnumClassChar16T, char16_t>();
    test_underlying_type<EnumClassChar32T, char32_t>();
    test_underlying_type<EnumClassWCharT, wchar_t>();

    // Struct enum
    test_underlying_type<EnumStructEmpty, int>();
    test_underlying_type<EnumStructWithMembers, int>();
    test_underlying_type<EnumStructBool, bool>();
    test_underlying_type<EnumStructChar, char>();
    test_underlying_type<EnumStructSignedChar, signed char>();
    test_underlying_type<EnumStructUnsignedChar, unsigned char>();
    test_underlying_type<EnumStructShort, short>();
    test_underlying_type<EnumStructUnsignedShort, unsigned short>();
    test_underlying_type<EnumStructInt, int>();
    test_underlying_type<EnumStructUnsignedInt, unsigned>();
    test_underlying_type<EnumStructLong, long>();
    test_underlying_type<EnumStructUnsignedLong, unsigned long>();
    test_underlying_type<EnumStructLongLong, long long>();
    test_underlying_type<EnumStructUnsignedLongLong, unsigned long long>();
    test_underlying_type<EnumStructChar8T, char8_t>();
    test_underlying_type<EnumStructChar16T, char16_t>();
    test_underlying_type<EnumStructChar32T, char32_t>();
    test_underlying_type<EnumStructWCharT, wchar_t>();

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
    test_no_underlying_type<virtual_derived_from<base>>();
    test_no_underlying_type<virtual_derived_from<derived>>();
    test_no_underlying_type<virtual_derived_from<class_type>>();
    test_no_underlying_type<union_type>();
    test_no_underlying_type<non_empty_union>();
    test_no_underlying_type<non_trivial_union>();
    test_no_underlying_type<empty>();
    test_no_underlying_type<not_empty>();
    test_no_underlying_type<non_trivial>();
    test_no_underlying_type<bit_zero>();
    test_no_underlying_type<bit_one>();
    test_no_underlying_type<base>();
    test_no_underlying_type<derived>();
    test_no_underlying_type<non_empty_base>();
    test_no_underlying_type<empty_base>();
    test_no_underlying_type<virtual_base>();
    test_no_underlying_type<polymorphic>();
    test_no_underlying_type<derived_polymorphic>();
    test_no_underlying_type<abstract>();
    test_no_underlying_type<public_abstract>();
    test_no_underlying_type<private_abstract>();
    test_no_underlying_type<protected_abstract>();
    test_no_underlying_type<abstract_template<int>>();
    test_no_underlying_type<abstract_template<double>>();
    test_no_underlying_type<abstract_template<class_type>>();
    test_no_underlying_type<abstract_template<incomplete_type>>();
    test_no_underlying_type<public_abstract_deleted_destructor>();
    test_no_underlying_type<protected_abstract_deleted_destructor>();
    test_no_underlying_type<private_abstract_deleted_destructor>();
    test_no_underlying_type<final_type>();
    test_no_underlying_type<final_derived>();
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
    test_no_underlying_type<explicit_class>();
    test_no_underlying_type<nothrow_explicit_class>();
    test_no_underlying_type<throw_explicit_class>();
    test_no_underlying_type<throw_default_class>();
    test_no_underlying_type<throw_copy_constructible_class>();
    test_no_underlying_type<throw_move_constructible_class>();
    test_no_underlying_type<throw_destructor>();
    test_no_underlying_type<noexcept_explicit_class>();
    test_no_underlying_type<except_explicit_class>();
    test_no_underlying_type<noexcept_default_class>();
    test_no_underlying_type<except_default_class>();
    test_no_underlying_type<noexcept_copy_constructible_class>();
    test_no_underlying_type<except_copy_constructible_class>();
    test_no_underlying_type<noexcept_move_constructible_class>();
    test_no_underlying_type<except_move_constructible_class>();
    test_no_underlying_type<noexcept_copy_assign_class>();
    test_no_underlying_type<except_copy_assign_class>();
    test_no_underlying_type<noexcept_move_assign_class>();
    test_no_underlying_type<except_move_assign_class>();
    test_no_underlying_type<deleted_copy_assign_class>();
    test_no_underlying_type<deleted_move_assign_class>();
    test_no_underlying_type<noexcept_move_constructible_and_assignable_class>();
    test_no_underlying_type<except_move_constructible_noexcept_move_assign_class>();
    test_no_underlying_type<noexcept_move_constructible_except_move_assign_class>();
    test_no_underlying_type<except_move_constructible_and_assign_class>();
    test_no_underlying_type<implicit_to<int>>();
    test_no_underlying_type<implicit_to<float>>();
    test_no_underlying_type<implicit_to<class_type>>();
    test_no_underlying_type<deleted_implicit_to<int>>();
    test_no_underlying_type<deleted_implicit_to<float>>();
    test_no_underlying_type<deleted_implicit_to<class_type>>();
    test_no_underlying_type<explicit_to<int>>();
    test_no_underlying_type<explicit_to<float>>();
    test_no_underlying_type<explicit_to<class_type>>();
    test_no_underlying_type<deleted_explicit_to<int>>();
    test_no_underlying_type<deleted_explicit_to<float>>();
    test_no_underlying_type<deleted_explicit_to<class_type>>();
    test_no_underlying_type<ellipsis>();
    test_no_underlying_type<deleted_ellipsis>();
    test_no_underlying_type<copy_constructible_only_type>();
    test_no_underlying_type<move_constructible_only_type>();
    test_no_underlying_type<overloaded_operators>();
    test_no_underlying_type<public_int_member>();
    test_no_underlying_type<protected_int_member>();
    test_no_underlying_type<private_int_member>();
    test_no_underlying_type<public_static_int_member>();
    test_no_underlying_type<protected_static_int_member>();
    test_no_underlying_type<private_static_int_member>();
    test_no_underlying_type<public_template_member<int>>();
    test_no_underlying_type<public_template_member<float>>();
    test_no_underlying_type<public_template_member<class_type>>();
    test_no_underlying_type<protected_template_member<int>>();
    test_no_underlying_type<protected_template_member<float>>();
    test_no_underlying_type<protected_template_member<class_type>>();
    test_no_underlying_type<private_template_member<int>>();
    test_no_underlying_type<private_template_member<float>>();
    test_no_underlying_type<private_template_member<class_type>>();
    test_no_underlying_type<public_static_template_member<int>>();
    test_no_underlying_type<public_static_template_member<float>>();
    test_no_underlying_type<public_static_template_member<class_type>>();
    test_no_underlying_type<protected_static_template_member<int>>();
    test_no_underlying_type<protected_static_template_member<float>>();
    test_no_underlying_type<protected_static_template_member<class_type>>();
    test_no_underlying_type<private_static_template_member<int>>();
    test_no_underlying_type<private_static_template_member<float>>();
    test_no_underlying_type<private_static_template_member<class_type>>();
    test_no_underlying_type<cannot_instantiate<int>>();
    test_no_underlying_type<cannot_instantiate<float>>();
    test_no_underlying_type<cannot_instantiate<class_type>>();
    test_no_underlying_type<natural_alignment>();
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
    test_no_underlying_type<lambda_type>();
    test_no_underlying_type<lambda_noexcept_type>();
    test_no_underlying_type<lambda_throws_type>();
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
    test_no_underlying_type<incomplete_union>();
    test_underlying_type<IncompleteEnumSigned, int>();
    test_underlying_type<IncompleteEnumUnsigned, unsigned>();
    test_underlying_type<IncompleteEnumClass, int>();
    test_underlying_type<IncompleteEnumStruct, int>();
    test_no_underlying_type<int class_type::*>();
    test_no_underlying_type<float class_type::*>();
    test_no_underlying_type<void * class_type::*>();
    test_no_underlying_type<int * class_type::*>();
    test_no_underlying_type<Enum class_type::*>();
    test_no_underlying_type<not_empty class_type::*>();
    test_no_underlying_type<int class_type::*&>();
    test_no_underlying_type<float class_type::*&>();
    test_no_underlying_type<void * class_type::*&>();
    test_no_underlying_type<int * class_type::*&>();
    test_no_underlying_type<Enum class_type::*&>();
    test_no_underlying_type<not_empty class_type::*&>();
    test_no_underlying_type<int class_type::*&&>();
    test_no_underlying_type<float class_type::*&&>();
    test_no_underlying_type<void * class_type::*&&>();
    test_no_underlying_type<int * class_type::*&&>();
    test_no_underlying_type<Enum class_type::*&&>();
    test_no_underlying_type<not_empty class_type::*&&>();
    test_no_underlying_type<non_default_constructible>();
    test_no_underlying_type<non_copy_constructible>();
    test_no_underlying_type<non_move_constructible>();
    test_no_underlying_type<non_copy_assignable>();
    test_no_underlying_type<non_move_assignable>();
    test_no_underlying_type<non_assignable>();
    test_no_underlying_type<non_copyable>();
    test_no_underlying_type<non_moveable>();
    test_no_underlying_type<non_constructible>();
    test_no_underlying_type<non_destructible>();
    test_no_underlying_type<tracked>();
    test_no_underlying_type<trap_constructible>();
    test_no_underlying_type<trap_implicit_conversion>();
    test_no_underlying_type<trap_comma>();
    test_no_underlying_type<trap_call>();
    test_no_underlying_type<trap_self_assign>();
    test_no_underlying_type<trap_deref>();
    test_no_underlying_type<trap_array_subscript>();

#if PHI_HAS_EXTENSION_ZERO_SIZE_ARRAY() && PHI_SUPPORTS_IS_ENUM()
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wzero-length-array")
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wpedantic")

    test_no_underlying_type<int[0]>();

    PHI_GCC_SUPPRESS_WARNING_POP()
    PHI_CLANG_SUPPRESS_WARNING_POP()
#endif

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
    test_no_underlying_type<void() & noexcept>();
    test_no_underlying_type<void() && noexcept>();
    test_no_underlying_type<void() const noexcept>();
    test_no_underlying_type<void() const & noexcept>();
    test_no_underlying_type<void() const && noexcept>();
    test_no_underlying_type<void() volatile noexcept>();
    test_no_underlying_type<void() volatile & noexcept>();
    test_no_underlying_type<void() volatile && noexcept>();
    test_no_underlying_type<void() const volatile noexcept>();
    test_no_underlying_type<void() const volatile & noexcept>();
    test_no_underlying_type<void() const volatile && noexcept>();

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
    test_no_underlying_type<void(int) & noexcept>();
    test_no_underlying_type<void(int) && noexcept>();
    test_no_underlying_type<void(int) const noexcept>();
    test_no_underlying_type<void(int) const & noexcept>();
    test_no_underlying_type<void(int) const && noexcept>();
    test_no_underlying_type<void(int) volatile noexcept>();
    test_no_underlying_type<void(int) volatile & noexcept>();
    test_no_underlying_type<void(int) volatile && noexcept>();
    test_no_underlying_type<void(int) const volatile noexcept>();
    test_no_underlying_type<void(int) const volatile & noexcept>();
    test_no_underlying_type<void(int) const volatile && noexcept>();

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
    test_no_underlying_type<void(...) & noexcept>();
    test_no_underlying_type<void(...) && noexcept>();
    test_no_underlying_type<void(...) const noexcept>();
    test_no_underlying_type<void(...) const & noexcept>();
    test_no_underlying_type<void(...) const && noexcept>();
    test_no_underlying_type<void(...) volatile noexcept>();
    test_no_underlying_type<void(...) volatile & noexcept>();
    test_no_underlying_type<void(...) volatile && noexcept>();
    test_no_underlying_type<void(...) const volatile noexcept>();
    test_no_underlying_type<void(...) const volatile & noexcept>();
    test_no_underlying_type<void(...) const volatile && noexcept>();

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
    test_no_underlying_type<void(int, ...) & noexcept>();
    test_no_underlying_type<void(int, ...) && noexcept>();
    test_no_underlying_type<void(int, ...) const noexcept>();
    test_no_underlying_type<void(int, ...) const & noexcept>();
    test_no_underlying_type<void(int, ...) const && noexcept>();
    test_no_underlying_type<void(int, ...) volatile noexcept>();
    test_no_underlying_type<void(int, ...) volatile & noexcept>();
    test_no_underlying_type<void(int, ...) volatile && noexcept>();
    test_no_underlying_type<void(int, ...) const volatile noexcept>();
    test_no_underlying_type<void(int, ...) const volatile & noexcept>();
    test_no_underlying_type<void(int, ...) const volatile && noexcept>();

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
    test_no_underlying_type<int() & noexcept>();
    test_no_underlying_type<int() && noexcept>();
    test_no_underlying_type<int() const noexcept>();
    test_no_underlying_type<int() const & noexcept>();
    test_no_underlying_type<int() const && noexcept>();
    test_no_underlying_type<int() volatile noexcept>();
    test_no_underlying_type<int() volatile & noexcept>();
    test_no_underlying_type<int() volatile && noexcept>();
    test_no_underlying_type<int() const volatile noexcept>();
    test_no_underlying_type<int() const volatile & noexcept>();
    test_no_underlying_type<int() const volatile && noexcept>();

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
    test_no_underlying_type<int(int) & noexcept>();
    test_no_underlying_type<int(int) && noexcept>();
    test_no_underlying_type<int(int) const noexcept>();
    test_no_underlying_type<int(int) const & noexcept>();
    test_no_underlying_type<int(int) const && noexcept>();
    test_no_underlying_type<int(int) volatile noexcept>();
    test_no_underlying_type<int(int) volatile & noexcept>();
    test_no_underlying_type<int(int) volatile && noexcept>();
    test_no_underlying_type<int(int) const volatile noexcept>();
    test_no_underlying_type<int(int) const volatile & noexcept>();
    test_no_underlying_type<int(int) const volatile && noexcept>();

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
    test_no_underlying_type<int(...) & noexcept>();
    test_no_underlying_type<int(...) && noexcept>();
    test_no_underlying_type<int(...) const noexcept>();
    test_no_underlying_type<int(...) const & noexcept>();
    test_no_underlying_type<int(...) const && noexcept>();
    test_no_underlying_type<int(...) volatile noexcept>();
    test_no_underlying_type<int(...) volatile & noexcept>();
    test_no_underlying_type<int(...) volatile && noexcept>();
    test_no_underlying_type<int(...) const volatile noexcept>();
    test_no_underlying_type<int(...) const volatile & noexcept>();
    test_no_underlying_type<int(...) const volatile && noexcept>();

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
    test_no_underlying_type<int(int, ...) & noexcept>();
    test_no_underlying_type<int(int, ...) && noexcept>();
    test_no_underlying_type<int(int, ...) const noexcept>();
    test_no_underlying_type<int(int, ...) const & noexcept>();
    test_no_underlying_type<int(int, ...) const && noexcept>();
    test_no_underlying_type<int(int, ...) volatile noexcept>();
    test_no_underlying_type<int(int, ...) volatile & noexcept>();
    test_no_underlying_type<int(int, ...) volatile && noexcept>();
    test_no_underlying_type<int(int, ...) const volatile noexcept>();
    test_no_underlying_type<int(int, ...) const volatile & noexcept>();
    test_no_underlying_type<int(int, ...) const volatile && noexcept>();

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
    test_no_underlying_type<void (class_type::*)() & noexcept>();
    test_no_underlying_type<void (class_type::*)() && noexcept>();
    test_no_underlying_type<void (class_type::*)() const noexcept>();
    test_no_underlying_type<void (class_type::*)() const & noexcept>();
    test_no_underlying_type<void (class_type::*)() const && noexcept>();

    test_no_underlying_type<void (class_type::*)(int)>();
    test_no_underlying_type<void (class_type::*)(int)&>();
    test_no_underlying_type<void (class_type::*)(int) &&>();
    test_no_underlying_type<void (class_type::*)(int) const>();
    test_no_underlying_type<void (class_type::*)(int) const&>();
    test_no_underlying_type<void (class_type::*)(int) const&&>();
    test_no_underlying_type<void (class_type::*)(int) noexcept>();
    test_no_underlying_type<void (class_type::*)(int) & noexcept>();
    test_no_underlying_type<void (class_type::*)(int) && noexcept>();
    test_no_underlying_type<void (class_type::*)(int) const noexcept>();
    test_no_underlying_type<void (class_type::*)(int) const & noexcept>();
    test_no_underlying_type<void (class_type::*)(int) const && noexcept>();

    test_no_underlying_type<void (class_type::*)(...)>();
    test_no_underlying_type<void (class_type::*)(...)&>();
    test_no_underlying_type<void (class_type::*)(...) &&>();
    test_no_underlying_type<void (class_type::*)(...) const>();
    test_no_underlying_type<void (class_type::*)(...) const&>();
    test_no_underlying_type<void (class_type::*)(...) const&&>();
    test_no_underlying_type<void (class_type::*)(...) noexcept>();
    test_no_underlying_type<void (class_type::*)(...) & noexcept>();
    test_no_underlying_type<void (class_type::*)(...) && noexcept>();
    test_no_underlying_type<void (class_type::*)(...) const noexcept>();
    test_no_underlying_type<void (class_type::*)(...) const & noexcept>();
    test_no_underlying_type<void (class_type::*)(...) const && noexcept>();

    test_no_underlying_type<void (class_type::*)(int, ...)>();
    test_no_underlying_type<void (class_type::*)(int, ...)&>();
    test_no_underlying_type<void (class_type::*)(int, ...) &&>();
    test_no_underlying_type<void (class_type::*)(int, ...) const>();
    test_no_underlying_type<void (class_type::*)(int, ...) const&>();
    test_no_underlying_type<void (class_type::*)(int, ...) const&&>();
    test_no_underlying_type<void (class_type::*)(int, ...) noexcept>();
    test_no_underlying_type<void (class_type::*)(int, ...) & noexcept>();
    test_no_underlying_type<void (class_type::*)(int, ...) && noexcept>();
    test_no_underlying_type<void (class_type::*)(int, ...) const noexcept>();
    test_no_underlying_type<void (class_type::*)(int, ...) const & noexcept>();
    test_no_underlying_type<void (class_type::*)(int, ...) const && noexcept>();

    test_no_underlying_type<int (class_type::*)()>();
    test_no_underlying_type<int (class_type::*)()&>();
    test_no_underlying_type<int (class_type::*)() &&>();
    test_no_underlying_type<int (class_type::*)() const>();
    test_no_underlying_type<int (class_type::*)() const&>();
    test_no_underlying_type<int (class_type::*)() const&&>();
    test_no_underlying_type<int (class_type::*)() noexcept>();
    test_no_underlying_type<int (class_type::*)() & noexcept>();
    test_no_underlying_type<int (class_type::*)() && noexcept>();
    test_no_underlying_type<int (class_type::*)() const noexcept>();
    test_no_underlying_type<int (class_type::*)() const & noexcept>();
    test_no_underlying_type<int (class_type::*)() const && noexcept>();

    test_no_underlying_type<int (class_type::*)(int)>();
    test_no_underlying_type<int (class_type::*)(int)&>();
    test_no_underlying_type<int (class_type::*)(int) &&>();
    test_no_underlying_type<int (class_type::*)(int) const>();
    test_no_underlying_type<int (class_type::*)(int) const&>();
    test_no_underlying_type<int (class_type::*)(int) const&&>();
    test_no_underlying_type<int (class_type::*)(int) noexcept>();
    test_no_underlying_type<int (class_type::*)(int) & noexcept>();
    test_no_underlying_type<int (class_type::*)(int) && noexcept>();
    test_no_underlying_type<int (class_type::*)(int) const noexcept>();
    test_no_underlying_type<int (class_type::*)(int) const & noexcept>();
    test_no_underlying_type<int (class_type::*)(int) const && noexcept>();

    test_no_underlying_type<int (class_type::*)(...)>();
    test_no_underlying_type<int (class_type::*)(...)&>();
    test_no_underlying_type<int (class_type::*)(...) &&>();
    test_no_underlying_type<int (class_type::*)(...) const>();
    test_no_underlying_type<int (class_type::*)(...) const&>();
    test_no_underlying_type<int (class_type::*)(...) const&&>();
    test_no_underlying_type<int (class_type::*)(...) noexcept>();
    test_no_underlying_type<int (class_type::*)(...) & noexcept>();
    test_no_underlying_type<int (class_type::*)(...) && noexcept>();
    test_no_underlying_type<int (class_type::*)(...) const noexcept>();
    test_no_underlying_type<int (class_type::*)(...) const & noexcept>();
    test_no_underlying_type<int (class_type::*)(...) const && noexcept>();

    test_no_underlying_type<int (class_type::*)(int, ...)>();
    test_no_underlying_type<int (class_type::*)(int, ...)&>();
    test_no_underlying_type<int (class_type::*)(int, ...) &&>();
    test_no_underlying_type<int (class_type::*)(int, ...) const>();
    test_no_underlying_type<int (class_type::*)(int, ...) const&>();
    test_no_underlying_type<int (class_type::*)(int, ...) const&&>();
    test_no_underlying_type<int (class_type::*)(int, ...) noexcept>();
    test_no_underlying_type<int (class_type::*)(int, ...) & noexcept>();
    test_no_underlying_type<int (class_type::*)(int, ...) && noexcept>();
    test_no_underlying_type<int (class_type::*)(int, ...) const noexcept>();
    test_no_underlying_type<int (class_type::*)(int, ...) const & noexcept>();
    test_no_underlying_type<int (class_type::*)(int, ...) const && noexcept>();
}
