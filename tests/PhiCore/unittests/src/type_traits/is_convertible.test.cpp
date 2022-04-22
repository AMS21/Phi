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
    test_is_not_convertible<void, Function>();
    test_is_not_convertible<void, Function&>();
    test_is_not_convertible<void, Function&&>();
    test_is_not_convertible<void, Function*>();
    test_is_not_convertible<void, Array>();
    test_is_not_convertible<void, Array&>();
    test_is_not_convertible<void, Array&&>();
    test_is_not_convertible<void, char>();
    test_is_not_convertible<void, char&>();
    test_is_not_convertible<void, char&&>();
    test_is_not_convertible<void, char*>();

    test_is_not_convertible<Function, void>();
    test_is_not_convertible<Function&, void>();
    test_is_not_convertible<Function&&, void>();
    test_is_not_convertible<Function*, void>();
    test_is_not_convertible<Array, void>();
    test_is_not_convertible<Array&, void>();
    test_is_not_convertible<Array&&, void>();
    test_is_not_convertible<char, void>();
    test_is_not_convertible<char&, void>();
    test_is_not_convertible<char&&, void>();
    test_is_not_convertible<char*, void>();

    // Function
    test_is_not_convertible<Function, void>();
    test_is_not_convertible<Function, Function>();
    test_is_convertible<Function, Function&>();
    test_is_convertible<Function, Function&&>();
    test_is_convertible<Function, Function*>();
    test_is_convertible<Function, Function* const>();

    test_is_not_convertible<Function, Array>();
    test_is_not_convertible<Function, Array&>();
    test_is_not_convertible<Function, Array&&>();
    test_is_not_convertible<Function, char>();
    test_is_not_convertible<Function, char&>();
    test_is_not_convertible<Function, char&&>();
    test_is_not_convertible<Function, char*>();

    // Function&
    test_is_not_convertible<Function&, void>();
    test_is_not_convertible<Function&, Function>();
    test_is_convertible<Function&, Function&>();
    test_is_convertible<Function&, Function&&>();

    test_is_convertible<Function&, Function*>();
    test_is_not_convertible<Function&, Array>();
    test_is_not_convertible<Function&, Array&>();
    test_is_not_convertible<Function&, Array&&>();
    test_is_not_convertible<Function&, char>();
    test_is_not_convertible<Function&, char&>();
    test_is_not_convertible<Function&, char&&>();
    test_is_not_convertible<Function&, char*>();

    // Function&&
    test_is_not_convertible<Function&&, void>();
    test_is_not_convertible<Function&&, Function>();
    test_is_convertible<Function&&, Function&>();
    test_is_convertible<Function&&, Function&&>();

    test_is_convertible<Function&&, Function*>();
    test_is_not_convertible<Function&&, Array>();
    test_is_not_convertible<Function&&, Array&>();
    test_is_not_convertible<Function&&, Array&&>();
    test_is_not_convertible<Function&&, char>();
    test_is_not_convertible<Function&&, char&>();
    test_is_not_convertible<Function&&, char&&>();
    test_is_not_convertible<Function&&, char*>();

    // Function*
    test_is_not_convertible<Function*, void>();
    test_is_not_convertible<Function*, Function>();
    test_is_not_convertible<Function*, Function&>();
    test_is_convertible<Function*, Function*>();

    test_is_not_convertible<Function*, Array>();
    test_is_not_convertible<Function*, Array&>();
    test_is_not_convertible<Function*, Array&&>();
    test_is_not_convertible<Function*, char>();
    test_is_not_convertible<Function*, char&>();
    test_is_not_convertible<Function*, char&&>();
    test_is_not_convertible<Function*, char*>();

    // Non-referencable function type
    test_is_not_convertible<ConstFunction, Function>();
    test_is_not_convertible<ConstFunction, Function*>();
    test_is_not_convertible<ConstFunction, Function&>();
    test_is_not_convertible<ConstFunction, Function&&>();
    test_is_not_convertible<Function*, ConstFunction>();
    test_is_not_convertible<Function&, ConstFunction>();
    test_is_not_convertible<ConstFunction, ConstFunction>();
    test_is_not_convertible<ConstFunction, void>();

    // Array
    test_is_not_convertible<Array, void>();
    test_is_not_convertible<Array, Function>();
    test_is_not_convertible<Array, Function&>();
    test_is_not_convertible<Array, Function*>();
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
    test_is_not_convertible<Array&, Function>();
    test_is_not_convertible<Array&, Function&>();
    test_is_not_convertible<Array&, Function*>();
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
    test_is_not_convertible<Array&&, Function>();
    test_is_not_convertible<Array&&, Function&>();
    test_is_not_convertible<Array&&, Function*>();
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
    test_is_not_convertible<char, Function>();
    test_is_not_convertible<char, Function&>();
    test_is_not_convertible<char, Function&&>();
    test_is_not_convertible<char, Function*>();
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
    test_is_not_convertible<char&, Function>();
    test_is_not_convertible<char&, Function&>();
    test_is_not_convertible<char&, Function&&>();
    test_is_not_convertible<char&, Function*>();
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
    test_is_not_convertible<char&&, Function>();
    test_is_not_convertible<char&&, Function&>();
    test_is_not_convertible<char&&, Function&&>();
    test_is_not_convertible<char&&, Function*>();
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
    test_is_not_convertible<char*, Function>();
    test_is_not_convertible<char*, Function&>();
    test_is_not_convertible<char*, Function*>();
    test_is_not_convertible<char*, Array>();
    test_is_not_convertible<char*, Array&>();

    test_is_not_convertible<char*, char>();
    test_is_not_convertible<char*, char&>();

    test_is_convertible<char*, char*>();
    test_is_convertible<char*, const char*>();
    test_is_not_convertible<const char*, char*>();
    test_is_convertible<const char*, const char*>();

    // NonCopyable
    test_is_convertible_impl<NonCopyable&, NonCopyable&>();
    test_is_convertible_impl<NonCopyable&, const NonCopyable&>();
    test_is_convertible_impl<NonCopyable&, volatile NonCopyable&>();
    test_is_convertible_impl<NonCopyable&, const volatile NonCopyable&>();

    test_is_not_convertible_impl<const NonCopyable&, NonCopyable&>();
    test_is_convertible_impl<const NonCopyable&, const NonCopyable&>();
    test_is_not_convertible_impl<const NonCopyable&, volatile NonCopyable&>();
    test_is_convertible_impl<const NonCopyable&, const volatile NonCopyable&>();

    test_is_not_convertible_impl<volatile NonCopyable&, NonCopyable&>();
    test_is_not_convertible_impl<volatile NonCopyable&, const NonCopyable&>();
    test_is_convertible_impl<volatile NonCopyable&, volatile NonCopyable&>();
    test_is_convertible_impl<volatile NonCopyable&, const volatile NonCopyable&>();

    test_is_not_convertible_impl<const volatile NonCopyable&, NonCopyable&>();
    test_is_not_convertible_impl<const volatile NonCopyable&, const NonCopyable&>();
    test_is_not_convertible_impl<const volatile NonCopyable&, volatile NonCopyable&>();
    test_is_convertible_impl<const volatile NonCopyable&, const volatile NonCopyable&>();

    // This test requires Access control SFINAE which we only have in C++11 or when
    // we are using the compiler builtin for is_convertible.
    test_is_not_convertible<NonCopyable&, NonCopyable>();

    // Ensure that CannotInstantiate is not instantiated by is_convertible when it is not needed.
    // For example CannotInstantiate is instantiated as a part of ADL lookup for arguments of type CannotInstantiate*.
    test_is_convertible<CannotInstantiate<int>*, CannotInstantiate<int>*>();

    // Test for PR13592
    test_is_not_convertible<Abstract, Abstract>();

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
    test_is_convertible<Enum, int>();
    test_is_not_convertible<int, Enum>();
    test_is_convertible<EnumSigned, int>();
    test_is_not_convertible<int, EnumSigned>();
    test_is_convertible<EnumUnsigned, unsigned>();
    test_is_not_convertible<unsigned, EnumUnsigned>();
    test_is_convertible_impl<Class, Class>();
    test_is_convertible_impl<Derived, Base>();
    test_is_convertible<Derived*, Base*>();
    test_is_convertible<Derived&, Base&>();
    test_is_convertible<Derived&&, Base&&>();

    test_is_convertible_impl<const int, const int&>();
    test_is_convertible_impl<const int, const int&&>();

    test_is_convertible<double&, ExplicitClass>();

    test_is_not_convertible<const int*, int*>();
    test_is_not_convertible<int*, float*>();
    test_is_not_convertible<const int[4], int*>();
    test_is_not_convertible<int[4], int[4]>();
    test_is_not_convertible<const int&, int&>();
    test_is_not_convertible<float&, int&>();
    test_is_not_convertible<float&, volatile int&>();
    test_is_not_convertible<int(int), int (*)()>();
    test_is_not_convertible<int, EnumClass>();
    test_is_not_convertible<int, EnumStruct>();
    test_is_not_convertible<int, Class>();
    test_is_not_convertible<Base, Derived>();
    test_is_not_convertible<Base*, Derived*>();
    test_is_not_convertible<Base&, Derived&>();
    test_is_not_convertible<Base&&, Derived&&>();
    test_is_not_convertible<void, int (*)(int)>();

    test_is_not_convertible<int, void>();
    test_is_not_convertible<int[4], void>();
    test_is_not_convertible<int, int&>();
    test_is_not_convertible<float, volatile float&>();
    test_is_not_convertible<volatile int, volatile int&>();
#if PHI_COMPILER_IS_NOT(MSVC)
    test_is_not_convertible<const volatile int, const volatile int&>();
#endif
    test_is_not_convertible<int&, ExplicitClass>();
    test_is_not_convertible<void*, ExplicitClass>();

    test_is_not_convertible<int, Tracked>();
    test_is_convertible<int, TrapConstructible>();
    test_is_not_convertible<int, TrapImplicitConversion>();
    test_is_not_convertible<int, TrapComma>();
    test_is_not_convertible<int, TrapCall>();
    test_is_not_convertible<int, TrapSelfAssign>();
    test_is_not_convertible<int, TrapDeref>();
    test_is_not_convertible<int, TrapArraySubscript>();

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
