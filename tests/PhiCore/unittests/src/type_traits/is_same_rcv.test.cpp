#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/type_traits/integral_constant.hpp>
#include <phi/type_traits/is_same_rcv.hpp>

template <typename T, typename U>
void test_is_same_rcv()
{
    // is_same_rcv
    STATIC_REQUIRE(phi::is_same_rcv<T, U>::value);
    STATIC_REQUIRE(phi::is_same_rcv<T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rcv<T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rcv<T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_same_rcv<const T, U>::value);
    STATIC_REQUIRE(phi::is_same_rcv<const T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rcv<const T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rcv<const T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_same_rcv<volatile T, U>::value);
    STATIC_REQUIRE(phi::is_same_rcv<volatile T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rcv<volatile T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rcv<volatile T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_same_rcv<const volatile T, U>::value);
    STATIC_REQUIRE(phi::is_same_rcv<const volatile T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rcv<const volatile T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rcv<const volatile T, const volatile U>::value);

    // is_not_same_rcv
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<const T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<const T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<const T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<const T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<volatile T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<volatile T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<volatile T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<volatile T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<const volatile T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<const volatile T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<const volatile T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<const volatile T, const volatile U>::value);

    // is_same_rcv_v
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_rcv_v<T, U>);
    STATIC_REQUIRE(phi::is_same_rcv_v<T, const U>);
    STATIC_REQUIRE(phi::is_same_rcv_v<T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rcv_v<T, const volatile U>);

    STATIC_REQUIRE(phi::is_same_rcv_v<const T, U>);
    STATIC_REQUIRE(phi::is_same_rcv_v<const T, const U>);
    STATIC_REQUIRE(phi::is_same_rcv_v<const T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rcv_v<const T, const volatile U>);

    STATIC_REQUIRE(phi::is_same_rcv_v<volatile T, U>);
    STATIC_REQUIRE(phi::is_same_rcv_v<volatile T, const U>);
    STATIC_REQUIRE(phi::is_same_rcv_v<volatile T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rcv_v<volatile T, const volatile U>);

    STATIC_REQUIRE(phi::is_same_rcv_v<const volatile T, U>);
    STATIC_REQUIRE(phi::is_same_rcv_v<const volatile T, const U>);
    STATIC_REQUIRE(phi::is_same_rcv_v<const volatile T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rcv_v<const volatile T, const volatile U>);

    // is_not_same_rcv_v
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<const T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<const T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<const T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<const T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<volatile T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<volatile T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<volatile T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<volatile T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<const volatile T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<const volatile T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<const volatile T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<const volatile T, const volatile U>);
#endif
}

template <typename T, typename U>
void test_is_not_same_rcv()
{
    STATIC_REQUIRE_FALSE(phi::is_same_rcv<T, U>::value);
    STATIC_REQUIRE(phi::is_not_same_rcv<T, U>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_same_rcv_v<T, U>);
    STATIC_REQUIRE(phi::is_not_same_rcv_v<T, U>);
#endif
}

template <typename T>
struct OverloadTest
{
    void fn(phi::is_same_rcv<T, int>)
    {}
    void fn(phi::false_type)
    {}
    void x()
    {
        fn(phi::false_type());
    }
};

struct A; // incomplete

TEST_CASE("is_same_rcv")
{
    test_is_same_rcv<short, short>();
    test_is_same_rcv<int, int>();
    test_is_same_rcv<unsigned, unsigned>();
    test_is_same_rcv<float, float>();
    test_is_same_rcv<double, double>();
    test_is_same_rcv<void, void>();
    test_is_same_rcv<int*, int*>();
    test_is_same_rcv<const int*, const int*>();
    test_is_same_rcv<volatile int*, volatile int*>();
    test_is_same_rcv<const volatile int*, const volatile int*>();
    test_is_same_rcv<Class, Class>();
    test_is_same_rcv<A, A>();
    test_is_same_rcv<IncompleteType, IncompleteType>();
    test_is_same_rcv<Empty, Empty>();
    test_is_same_rcv<NotEmpty, NotEmpty>();
    test_is_same_rcv<Union, Union>();
    test_is_same_rcv<BitZero, BitZero>();
    test_is_same_rcv<Abstract, Abstract>();
    test_is_same_rcv<Enum, Enum>();
    test_is_same_rcv<EnumSigned, EnumSigned>();
    test_is_same_rcv<EnumUnsigned, EnumUnsigned>();
    test_is_same_rcv<EnumClass, EnumClass>();

    test_is_same_rcv<int&, int&>();
    test_is_same_rcv<float&, float&>();
    test_is_same_rcv<Class&, Class&>();

    test_is_not_same_rcv<int, void>();
    test_is_not_same_rcv<void, Class>();
    test_is_not_same_rcv<Class, int*>();
    test_is_not_same_rcv<int*, int&>();
    test_is_not_same_rcv<int&, int>();

    OverloadTest<char> t;
    (void)t;
}
