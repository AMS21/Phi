#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/TypeTraits/integral_constant.hpp>
#include <Phi/TypeTraits/is_same.hpp>

template <typename T, typename U>
void test_is_same()
{
    // is_same
    STATIC_REQUIRE(phi::is_same<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same<T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same<T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same<T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_same<const T, U>::value);
    STATIC_REQUIRE(phi::is_same<const T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same<const T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same<const T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_same<volatile T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same<volatile T, const U>::value);
    STATIC_REQUIRE(phi::is_same<volatile T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same<volatile T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_same<const volatile T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same<const volatile T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same<const volatile T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same<const volatile T, const volatile U>::value);

    // is_not_same
    STATIC_REQUIRE_FALSE(phi::is_not_same<T, U>::value);
    STATIC_REQUIRE(phi::is_not_same<T, const U>::value);
    STATIC_REQUIRE(phi::is_not_same<T, volatile U>::value);
    STATIC_REQUIRE(phi::is_not_same<T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_not_same<const T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same<const T, const U>::value);
    STATIC_REQUIRE(phi::is_not_same<const T, volatile U>::value);
    STATIC_REQUIRE(phi::is_not_same<const T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_not_same<volatile T, U>::value);
    STATIC_REQUIRE(phi::is_not_same<volatile T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same<volatile T, volatile U>::value);
    STATIC_REQUIRE(phi::is_not_same<volatile T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_not_same<const volatile T, U>::value);
    STATIC_REQUIRE(phi::is_not_same<const volatile T, const U>::value);
    STATIC_REQUIRE(phi::is_not_same<const volatile T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same<const volatile T, const volatile U>::value);

    // is_same_v
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_same_v<T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_same_v<T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_same_v<T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_same_v<const T, U>);
    STATIC_REQUIRE(phi::is_same_v<const T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_same_v<const T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_same_v<const T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_same_v<volatile T, U>);
    STATIC_REQUIRE_FALSE(phi::is_same_v<volatile T, const U>);
    STATIC_REQUIRE(phi::is_same_v<volatile T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_same_v<volatile T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_same_v<const volatile T, U>);
    STATIC_REQUIRE_FALSE(phi::is_same_v<const volatile T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_same_v<const volatile T, volatile U>);
    STATIC_REQUIRE(phi::is_same_v<const volatile T, const volatile U>);

    // is_not_same_v
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<T, U>);
    STATIC_REQUIRE(phi::is_not_same_v<T, const U>);
    STATIC_REQUIRE(phi::is_not_same_v<T, volatile U>);
    STATIC_REQUIRE(phi::is_not_same_v<T, const volatile U>);

    STATIC_REQUIRE(phi::is_not_same_v<const T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<const T, const U>);
    STATIC_REQUIRE(phi::is_not_same_v<const T, volatile U>);
    STATIC_REQUIRE(phi::is_not_same_v<const T, const volatile U>);

    STATIC_REQUIRE(phi::is_not_same_v<volatile T, U>);
    STATIC_REQUIRE(phi::is_not_same_v<volatile T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<volatile T, volatile U>);
    STATIC_REQUIRE(phi::is_not_same_v<volatile T, const volatile U>);

    STATIC_REQUIRE(phi::is_not_same_v<const volatile T, U>);
    STATIC_REQUIRE(phi::is_not_same_v<const volatile T, const U>);
    STATIC_REQUIRE(phi::is_not_same_v<const volatile T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<const volatile T, const volatile U>);
#endif
}

template <typename T, typename U>
void test_is_same_ref()
{
    // is_same
    STATIC_REQUIRE(phi::is_same<T, U>::value);
    STATIC_REQUIRE(phi::is_same<T, const U>::value);
    STATIC_REQUIRE(phi::is_same<T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same<T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_same<const T, U>::value);
    STATIC_REQUIRE(phi::is_same<const T, const U>::value);
    STATIC_REQUIRE(phi::is_same<const T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same<const T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_same<volatile T, U>::value);
    STATIC_REQUIRE(phi::is_same<volatile T, const U>::value);
    STATIC_REQUIRE(phi::is_same<volatile T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same<volatile T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_same<const volatile T, U>::value);
    STATIC_REQUIRE(phi::is_same<const volatile T, const U>::value);
    STATIC_REQUIRE(phi::is_same<const volatile T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same<const volatile T, const volatile U>::value);

    // is_not_same
    STATIC_REQUIRE_FALSE(phi::is_not_same<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same<T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same<T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same<T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_same<const T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same<const T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same<const T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same<const T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_same<volatile T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same<volatile T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same<volatile T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same<volatile T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_same<const volatile T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same<const volatile T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same<const volatile T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same<const volatile T, const volatile U>::value);

    // is_same_v
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_v<T, U>);
    STATIC_REQUIRE(phi::is_same_v<T, const U>);
    STATIC_REQUIRE(phi::is_same_v<T, volatile U>);
    STATIC_REQUIRE(phi::is_same_v<T, const volatile U>);

    STATIC_REQUIRE(phi::is_same_v<const T, U>);
    STATIC_REQUIRE(phi::is_same_v<const T, const U>);
    STATIC_REQUIRE(phi::is_same_v<const T, volatile U>);
    STATIC_REQUIRE(phi::is_same_v<const T, const volatile U>);

    STATIC_REQUIRE(phi::is_same_v<volatile T, U>);
    STATIC_REQUIRE(phi::is_same_v<volatile T, const U>);
    STATIC_REQUIRE(phi::is_same_v<volatile T, volatile U>);
    STATIC_REQUIRE(phi::is_same_v<volatile T, const volatile U>);

    STATIC_REQUIRE(phi::is_same_v<const volatile T, U>);
    STATIC_REQUIRE(phi::is_same_v<const volatile T, const U>);
    STATIC_REQUIRE(phi::is_same_v<const volatile T, volatile U>);
    STATIC_REQUIRE(phi::is_same_v<const volatile T, const volatile U>);

    // is_same_not_v
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_not_same_v<const T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<const T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<const T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<const T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_not_same_v<volatile T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<volatile T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<volatile T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<volatile T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_not_same_v<const volatile T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<const volatile T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<const volatile T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<const volatile T, const volatile U>);
#endif
}

template <typename T, typename U>
void test_is_not_same()
{
    STATIC_REQUIRE_FALSE(phi::is_same<T, U>::value);
    STATIC_REQUIRE(phi::is_not_same<T, U>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_same_v<T, U>);
    STATIC_REQUIRE(phi::is_not_same_v<T, U>);
#endif
}

template <typename T>
struct OverloadTest
{
    void fn(phi::is_same<T, int>)
    {}
    void fn(phi::false_type)
    {}
    void x()
    {
        fn(phi::false_type());
    }
};

struct A; // incomplete

TEST_CASE("is_same")
{
    test_is_same<short, short>();
    test_is_same<int, int>();
    test_is_same<unsigned, unsigned>();
    test_is_same<float, float>();
    test_is_same<double, double>();
    test_is_same<void, void>();
    test_is_same<int*, int*>();
    test_is_same<const int*, const int*>();
    test_is_same<volatile int*, volatile int*>();
    test_is_same<const volatile int*, const volatile int*>();
    test_is_same<Class, Class>();
    test_is_same<A, A>();
    test_is_same<incomplete_type, incomplete_type>();
    test_is_same<Empty, Empty>();
    test_is_same<NotEmpty, NotEmpty>();
    test_is_same<Union, Union>();
    test_is_same<bit_zero, bit_zero>();
    test_is_same<Abstract, Abstract>();
    test_is_same<Enum, Enum>();
    test_is_same<EnumSigned, EnumSigned>();
    test_is_same<EnumUnsigned, EnumUnsigned>();
    test_is_same<EnumClass, EnumClass>();

    test_is_same_ref<int&, int&>();
    test_is_same_ref<float&, float&>();
    test_is_same_ref<Class&, Class&>();

    test_is_not_same<int, void>();
    test_is_not_same<void, Class>();
    test_is_not_same<Class, int*>();
    test_is_not_same<int*, int&>();
    test_is_not_same<int&, int>();

    OverloadTest<char> t;
    (void)t;
}
