#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/type_traits/is_convertible.hpp>
#include <type_traits>

// TODO: A bunch of tests here don't work correctly with MSVC

template <typename T, typename U>
void test_is_convertible_impl()
{
    STATIC_REQUIRE(phi::is_convertible<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_convertible<T, U>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_convertible_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_convertible_v<T, U>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_convertible<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_convertible<T, U>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_convertible<T, U>::value);
}

template <typename T, typename U>
void test_is_convertible()
{
    test_is_convertible_impl<T, U>();
    test_is_convertible_impl<T, const U>();
    test_is_convertible_impl<T, volatile U>();
    test_is_convertible_impl<T, const volatile U>();

    test_is_convertible_impl<const T, U>();
    test_is_convertible_impl<const T, const U>();
    test_is_convertible_impl<const T, volatile U>();
    test_is_convertible_impl<const T, const volatile U>();

    test_is_convertible_impl<volatile T, U>();
    test_is_convertible_impl<volatile T, const U>();
    test_is_convertible_impl<volatile T, volatile U>();
    test_is_convertible_impl<volatile T, const volatile U>();

    test_is_convertible_impl<const volatile T, U>();
    test_is_convertible_impl<const volatile T, const U>();
    test_is_convertible_impl<const volatile T, volatile U>();
    test_is_convertible_impl<const volatile T, const volatile U>();
}

template <typename T, typename U>
void test_is_not_convertible_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_convertible<T, U>::value);
    STATIC_REQUIRE(phi::is_not_convertible<T, U>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_convertible_v<T, U>);
    STATIC_REQUIRE(phi::is_not_convertible_v<T, U>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_convertible<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_convertible<T, U>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_convertible<T, U>::value);
}

template <typename T, typename U>
void test_is_not_convertible()
{
    test_is_not_convertible_impl<T, U>();
    test_is_not_convertible_impl<T, const U>();
    test_is_not_convertible_impl<T, volatile U>();
    test_is_not_convertible_impl<T, const volatile U>();

    test_is_not_convertible_impl<const T, U>();
    test_is_not_convertible_impl<const T, const U>();
    test_is_not_convertible_impl<const T, volatile U>();
    test_is_not_convertible_impl<const T, const volatile U>();

    test_is_not_convertible_impl<volatile T, U>();
    test_is_not_convertible_impl<volatile T, const U>();
    test_is_not_convertible_impl<volatile T, volatile U>();
    test_is_not_convertible_impl<volatile T, const volatile U>();

    test_is_not_convertible_impl<const volatile T, U>();
    test_is_not_convertible_impl<const volatile T, const U>();
    test_is_not_convertible_impl<const volatile T, volatile U>();
    test_is_not_convertible_impl<const volatile T, const volatile U>();
}

using ConstFunction = void() const;
using Array         = char[1];

struct StringType
{
    StringType(const char*)
    {}
};

struct A
{};

struct B : public A
{};

struct C
{};

struct D
{
    operator C()
    {
        return c;
    }

    C c;
};

struct E
{
    template <typename T>
    E(T&&)
    {}
};

struct F
{
    F(int) = delete;
};

TEST_CASE("is_convertible")
{
    // void
    test_is_convertible<void, void>();
    test_is_not_convertible<void, function_type>();
    test_is_not_convertible<void, function_type&>();
    test_is_not_convertible<void, function_type&&>();
    test_is_not_convertible<void, function_type*>();
    test_is_not_convertible<void, Array>();
    test_is_not_convertible<void, Array&>();
    test_is_not_convertible<void, Array&&>();
    test_is_not_convertible<void, char>();
    test_is_not_convertible<void, char&>();
    test_is_not_convertible<void, char&&>();
    test_is_not_convertible<void, char*>();

    test_is_not_convertible<function_type, void>();
    test_is_not_convertible<function_type&, void>();
    test_is_not_convertible<function_type&&, void>();
    test_is_not_convertible<function_type*, void>();
    test_is_not_convertible<Array, void>();
    test_is_not_convertible<Array&, void>();
    test_is_not_convertible<Array&&, void>();
    test_is_not_convertible<char, void>();
    test_is_not_convertible<char&, void>();
    test_is_not_convertible<char&&, void>();
    test_is_not_convertible<char*, void>();

    // function_type
    test_is_not_convertible<function_type, void>();
    test_is_not_convertible<function_type, function_type>();
    test_is_convertible<function_type, function_type&>();
    test_is_convertible<function_type, function_type&&>();
    test_is_convertible<function_type, function_type*>();
    test_is_convertible<function_type, function_type* const>();

    test_is_not_convertible<function_type, Array>();
    test_is_not_convertible<function_type, Array&>();
    test_is_not_convertible<function_type, Array&&>();
    test_is_not_convertible<function_type, char>();
    test_is_not_convertible<function_type, char&>();
    test_is_not_convertible<function_type, char&&>();
    test_is_not_convertible<function_type, char*>();

    // function_type&
    test_is_not_convertible<function_type&, void>();
    test_is_not_convertible<function_type&, function_type>();
    test_is_convertible<function_type&, function_type&>();
    test_is_convertible<function_type&, function_type&&>();

    test_is_convertible<function_type&, function_type*>();
    test_is_not_convertible<function_type&, Array>();
    test_is_not_convertible<function_type&, Array&>();
    test_is_not_convertible<function_type&, Array&&>();
    test_is_not_convertible<function_type&, char>();
    test_is_not_convertible<function_type&, char&>();
    test_is_not_convertible<function_type&, char&&>();
    test_is_not_convertible<function_type&, char*>();

    // function_type&&
    test_is_not_convertible<function_type&&, void>();
    test_is_not_convertible<function_type&&, function_type>();
    test_is_convertible<function_type&&, function_type&>();
    test_is_convertible<function_type&&, function_type&&>();

    test_is_convertible<function_type&&, function_type*>();
    test_is_not_convertible<function_type&&, Array>();
    test_is_not_convertible<function_type&&, Array&>();
    test_is_not_convertible<function_type&&, Array&&>();
    test_is_not_convertible<function_type&&, char>();
    test_is_not_convertible<function_type&&, char&>();
    test_is_not_convertible<function_type&&, char&&>();
    test_is_not_convertible<function_type&&, char*>();

    // function_type*
    test_is_not_convertible<function_type*, void>();
    test_is_not_convertible<function_type*, function_type>();
    test_is_not_convertible<function_type*, function_type&>();
    test_is_convertible<function_type*, function_type*>();

    test_is_not_convertible<function_type*, Array>();
    test_is_not_convertible<function_type*, Array&>();
    test_is_not_convertible<function_type*, Array&&>();
    test_is_not_convertible<function_type*, char>();
    test_is_not_convertible<function_type*, char&>();
    test_is_not_convertible<function_type*, char&&>();
    test_is_not_convertible<function_type*, char*>();

    // Non-referencable function_type type
    test_is_not_convertible<ConstFunction, function_type>();
    test_is_not_convertible<ConstFunction, function_type*>();
    test_is_not_convertible<ConstFunction, function_type&>();
    test_is_not_convertible<ConstFunction, function_type&&>();
    test_is_not_convertible<function_type*, ConstFunction>();
    test_is_not_convertible<function_type&, ConstFunction>();
    test_is_not_convertible<ConstFunction, ConstFunction>();
    test_is_not_convertible<ConstFunction, void>();

    // Array
    test_is_not_convertible<Array, void>();
    test_is_not_convertible<Array, function_type>();
    test_is_not_convertible<Array, function_type&>();
    test_is_not_convertible<Array, function_type*>();
    test_is_not_convertible<Array, Array>();

    test_is_not_convertible<Array, Array&>();
    test_is_convertible_impl<Array, const Array&>();
    test_is_not_convertible<Array, volatile Array&>();
#if PHI_COMPILER_IS_NOT(MSVC)
    test_is_not_convertible<Array, const volatile Array&>();
#endif

    test_is_not_convertible<const Array, Array&>();
    test_is_convertible_impl<const Array, const Array&>();
    test_is_not_convertible<const Array, volatile Array&>();
#if PHI_COMPILER_IS_NOT(MSVC)
    test_is_not_convertible<const Array, const volatile Array&>();
#endif

    test_is_convertible_impl<Array, Array&&>();
    test_is_convertible_impl<Array, const Array&&>();
    test_is_convertible_impl<Array, volatile Array&&>();
    test_is_convertible_impl<Array, const volatile Array&&>();

    test_is_not_convertible_impl<const Array, Array&&>();
    test_is_convertible_impl<const Array, const Array&&>();
    test_is_not_convertible_impl<const Array, volatile Array&&>();
    test_is_convertible_impl<const Array, const volatile Array&&>();

    test_is_not_convertible<Array&, Array&&>();
    test_is_not_convertible<Array&&, Array&>();

    test_is_not_convertible<Array, char>();
    test_is_not_convertible<Array, char&>();

    test_is_convertible_impl<Array, char*>();
    test_is_convertible_impl<Array, const char*>();
    test_is_convertible_impl<Array, char* const>();
    test_is_convertible_impl<Array, char* volatile>();
    test_is_convertible_impl<Array, char* const volatile>();

    test_is_not_convertible<const Array, char*>();
    test_is_convertible_impl<const Array, const char*>();

    test_is_not_convertible<char[42][42], char*>();
    test_is_not_convertible<char[][1], char*>();

    // Array&
    test_is_not_convertible<Array&, void>();
    test_is_not_convertible<Array&, function_type>();
    test_is_not_convertible<Array&, function_type&>();
    test_is_not_convertible<Array&, function_type*>();
    test_is_not_convertible<Array&, Array>();

    test_is_convertible<Array&, Array&>();
    test_is_convertible<Array&, const Array&>();
    test_is_not_convertible<const Array&, Array&>();
    test_is_convertible<const Array&, const Array&>();

    test_is_not_convertible<Array&, char>();
    test_is_not_convertible<Array&, char&>();
    test_is_not_convertible<Array&, char&&>();

    test_is_convertible<Array&, char*>();
    test_is_convertible<Array&, const char*>();
    test_is_not_convertible<const Array&, char*>();
    test_is_convertible<const Array&, const char*>();

    test_is_convertible_impl<Array, StringType>();
    test_is_convertible_impl<char(&)[], StringType>();

    // Array&&
    test_is_not_convertible<Array&&, void>();
    test_is_not_convertible<Array&&, function_type>();
    test_is_not_convertible<Array&&, function_type&>();
    test_is_not_convertible<Array&&, function_type*>();
    test_is_not_convertible<Array&&, Array>();

    test_is_convertible<Array&, Array&>();
    test_is_convertible<Array&, const Array&>();
    test_is_not_convertible<const Array&, Array&>();
    test_is_convertible<const Array&, const Array&>();

    test_is_not_convertible<Array&, char>();
    test_is_not_convertible<Array&, char&>();
    test_is_not_convertible<Array&, char&&>();

    test_is_convertible<Array&, char*>();
    test_is_convertible<Array&, const char*>();
    test_is_not_convertible<const Array&, char*>();
    test_is_convertible<const Array&, const char*>();

    test_is_convertible_impl<Array, StringType>();
    test_is_convertible_impl<char(&)[], StringType>();

    // char
    test_is_not_convertible<char, void>();
    test_is_not_convertible<char, function_type>();
    test_is_not_convertible<char, function_type&>();
    test_is_not_convertible<char, function_type&&>();
    test_is_not_convertible<char, function_type*>();
    test_is_not_convertible<char, Array>();
    test_is_not_convertible<char, Array&>();
    test_is_not_convertible<char, Array&&>();

    test_is_convertible<char, char>();

    test_is_not_convertible<char, char&>();
    test_is_convertible_impl<char, const char&>();
    test_is_not_convertible<const char, char&>();
    test_is_convertible_impl<const char, const char&>();

    test_is_convertible_impl<char, char&&>();
    test_is_convertible_impl<char, const char&&>();
    test_is_not_convertible<const char, char&&>();
    test_is_convertible_impl<const char, const char&&>();

    test_is_not_convertible<char, char*>();

    // char&
    test_is_not_convertible<char&, void>();
    test_is_not_convertible<char&, function_type>();
    test_is_not_convertible<char&, function_type&>();
    test_is_not_convertible<char&, function_type&&>();
    test_is_not_convertible<char&, function_type*>();
    test_is_not_convertible<char&, Array>();
    test_is_not_convertible<char&, Array&>();
    test_is_not_convertible<char&, Array&&>();

    test_is_convertible<char&, char>();

    test_is_convertible<char&, char&>();
    test_is_convertible<char&, const char&>();
    test_is_not_convertible<const char&, char&>();
    test_is_convertible<const char&, const char&>();

    test_is_not_convertible<char&, char&&>();
    test_is_not_convertible<char&, const char&&>();
    test_is_not_convertible<const char&, char&&>();
    test_is_not_convertible<const char&, const char&&>();

    test_is_not_convertible<char&, char*>();

    // char&&
    test_is_not_convertible<char&&, void>();
    test_is_not_convertible<char&&, function_type>();
    test_is_not_convertible<char&&, function_type&>();
    test_is_not_convertible<char&&, function_type&&>();
    test_is_not_convertible<char&&, function_type*>();
    test_is_not_convertible<char&&, Array>();
    test_is_not_convertible<char&&, Array&>();
    test_is_not_convertible<char&&, Array&&>();

    test_is_convertible<char&&, char>();

    test_is_not_convertible<char&&, char&>();
    test_is_convertible<char&&, const char&>();
    test_is_not_convertible<const char&&, char&>();
    test_is_convertible<const char&&, const char&>();

    test_is_convertible<char&&, char&&>();
    test_is_convertible_impl<char&&, const char&&>();
    test_is_not_convertible<const char&&, char&&>();
    test_is_convertible<const char&&, const char&&>();

    test_is_not_convertible<char&&, char*>();

    // char*
    test_is_not_convertible<char*, void>();
    test_is_not_convertible<char*, function_type>();
    test_is_not_convertible<char*, function_type&>();
    test_is_not_convertible<char*, function_type*>();
    test_is_not_convertible<char*, Array>();
    test_is_not_convertible<char*, Array&>();

    test_is_not_convertible<char*, char>();
    test_is_not_convertible<char*, char&>();

    test_is_convertible<char*, char*>();
    test_is_convertible<char*, const char*>();
    test_is_not_convertible<const char*, char*>();
    test_is_convertible<const char*, const char*>();

    // non_copyable
    test_is_convertible_impl<non_copyable&, non_copyable&>();
    test_is_convertible_impl<non_copyable&, const non_copyable&>();
    test_is_convertible_impl<non_copyable&, volatile non_copyable&>();
    test_is_convertible_impl<non_copyable&, const volatile non_copyable&>();

    test_is_not_convertible_impl<const non_copyable&, non_copyable&>();
    test_is_convertible_impl<const non_copyable&, const non_copyable&>();
    test_is_not_convertible_impl<const non_copyable&, volatile non_copyable&>();
    test_is_convertible_impl<const non_copyable&, const volatile non_copyable&>();

    test_is_not_convertible_impl<volatile non_copyable&, non_copyable&>();
    test_is_not_convertible_impl<volatile non_copyable&, const non_copyable&>();
    test_is_convertible_impl<volatile non_copyable&, volatile non_copyable&>();
    test_is_convertible_impl<volatile non_copyable&, const volatile non_copyable&>();

    test_is_not_convertible_impl<const volatile non_copyable&, non_copyable&>();
    test_is_not_convertible_impl<const volatile non_copyable&, const non_copyable&>();
    test_is_not_convertible_impl<const volatile non_copyable&, volatile non_copyable&>();
    test_is_convertible_impl<const volatile non_copyable&, const volatile non_copyable&>();

    // This test requires Access control SFINAE which we only have in C++11 or when
    // we are using the compiler builtin for is_convertible.
    test_is_not_convertible<non_copyable&, non_copyable>();

    // Ensure that cannot_instantiate is not instantiated by is_convertible when it is not needed.
    // For example cannot_instantiate is instantiated as a part of ADL lookup for arguments of type cannot_instantiate*.
    test_is_convertible<cannot_instantiate<int>*, cannot_instantiate<int>*>();

    // Test for PR13592
    test_is_not_convertible<abstract, abstract>();

    test_is_convertible<int, int>();
    test_is_convertible<int, const int>();
    test_is_convertible<volatile int, const int>();
    test_is_convertible<int, float>();
    test_is_convertible<double, float>();
    test_is_convertible<float, int>();
    test_is_convertible<int*, const int*>();
    test_is_convertible<int*, void*>();
    test_is_convertible_impl<int[4], int*>();
    test_is_convertible<float&, int>();
    test_is_convertible<int&, const int&>();
    test_is_not_convertible<int&, const int&&>();
    test_is_convertible<float&&, int>();
    test_is_convertible<int&&, const int&>();
    test_is_convertible<int&&, const int&&>();
    test_is_convertible<float, const int&>();
    test_is_convertible<float, const int&&>();
    test_is_not_convertible<int(int), int(int)>();
    test_is_convertible<int(int), int (*)(int)>();
    test_is_convertible<int(int), int (&)(int)>();
    test_is_convertible<int(int), int(&&)(int)>();
    test_is_not_convertible<int (*)(int), int(int)>();
    test_is_convertible<int (*)(int), int (*)(int)>();
    test_is_not_convertible<int (*)(int), int (&)(int)>();
    test_is_not_convertible<int (*)(int), int(&&)(int)>();
    test_is_not_convertible<int (&)(int), int(int)>();
    test_is_convertible<int (&)(int), int (*)(int)>();
    test_is_convertible<int (&)(int), int (&)(int)>();
    test_is_convertible<int (&)(int), int(&&)(int)>();
    test_is_not_convertible<int(&&)(int), int(int)>();
    test_is_convertible<int(&&)(int), int (*)(int)>();
    test_is_convertible<int(&&)(int), int (&)(int)>();
    test_is_convertible<int(&&)(int), int(&&)(int)>();
    test_is_convertible<enum_type, int>();
    test_is_not_convertible<int, enum_type>();
    test_is_convertible<enum_signed, int>();
    test_is_not_convertible<int, enum_signed>();
    test_is_convertible<enum_unsigned, unsigned>();
    test_is_not_convertible<unsigned, enum_unsigned>();
    test_is_convertible_impl<class_type, class_type>();
    test_is_convertible_impl<derived, base>();
    test_is_convertible<derived*, base*>();
    test_is_convertible<derived&, base&>();
    test_is_convertible<derived&&, base&&>();

    test_is_convertible_impl<const int, const int&>();
    test_is_convertible_impl<const int, const int&&>();

    test_is_convertible<double&, explicit_class>();

    test_is_not_convertible<const int*, int*>();
    test_is_not_convertible<int*, float*>();
    test_is_not_convertible<const int[4], int*>();
    test_is_not_convertible<int[4], int[4]>();
    test_is_not_convertible<const int&, int&>();
    test_is_not_convertible<float&, int&>();
    test_is_not_convertible<float&, volatile int&>();
    test_is_not_convertible<int(int), int (*)()>();
    test_is_not_convertible<int, enum_class>();
    test_is_not_convertible<int, enum_struct>();
    test_is_not_convertible<int, class_type>();
    test_is_not_convertible<base, derived>();
    test_is_not_convertible<base*, derived*>();
    test_is_not_convertible<base&, derived&>();
    test_is_not_convertible<base&&, derived&&>();
    test_is_not_convertible<void, int (*)(int)>();

    test_is_not_convertible<int, void>();
    test_is_not_convertible<int[4], void>();
    test_is_not_convertible<int, int&>();
    test_is_not_convertible<float, volatile float&>();
    test_is_not_convertible<volatile int, volatile int&>();
#if PHI_COMPILER_IS_NOT(MSVC)
    test_is_not_convertible<const volatile int, const volatile int&>();
#endif
    test_is_not_convertible<int&, explicit_class>();
    test_is_not_convertible<void*, explicit_class>();

    test_is_not_convertible<int, tracked>();
    test_is_convertible<int, trap_constructible>();
    test_is_not_convertible<int, trap_implicit_conversion>();
    test_is_not_convertible<int, trap_comma>();
    test_is_not_convertible<int, trap_call>();
    test_is_not_convertible<int, trap_self_assign>();
    test_is_not_convertible<int, trap_deref>();
    test_is_not_convertible<int, trap_array_subscript>();

    // Other tests
    test_is_convertible<B*, A*>();
    test_is_not_convertible<A*, B*>();
    test_is_convertible_impl<D, C>();
    test_is_not_convertible<B*, C*>();
    test_is_convertible<A, E>();
    test_is_convertible<B, E>();
    test_is_convertible<C, E>();
    test_is_convertible<D, E>();
    test_is_convertible<E, E>();
    test_is_convertible<bool, E>();
    test_is_convertible<int, E>();
    test_is_convertible<float, E>();
    test_is_convertible<int*, E>();
    test_is_convertible<int&, E>();
    test_is_convertible<int[], E>();
    test_is_convertible<int[2], E>();
    test_is_not_convertible<int, F>();
}
