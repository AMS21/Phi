#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/type_traits/integral_constant.hpp>
#include <phi/type_traits/is_same_rv.hpp>

template <typename T, typename U>
void test_is_same_rv()
{
    // is_same_rv
    STATIC_REQUIRE(phi::is_same_rv<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same_rv<T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rv<T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same_rv<T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_same_rv<const T, U>::value);
    STATIC_REQUIRE(phi::is_same_rv<const T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same_rv<const T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rv<const T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_same_rv<volatile T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same_rv<volatile T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rv<volatile T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same_rv<volatile T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_same_rv<const volatile T, U>::value);
    STATIC_REQUIRE(phi::is_same_rv<const volatile T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same_rv<const volatile T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rv<const volatile T, const volatile U>::value);

    // is_not_same_rv
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<T, U>::value);
    STATIC_REQUIRE(phi::is_not_same_rv<T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<T, volatile U>::value);
    STATIC_REQUIRE(phi::is_not_same_rv<T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_not_same_rv<const T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<const T, const U>::value);
    STATIC_REQUIRE(phi::is_not_same_rv<const T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<const T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<volatile T, U>::value);
    STATIC_REQUIRE(phi::is_not_same_rv<volatile T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<volatile T, volatile U>::value);
    STATIC_REQUIRE(phi::is_not_same_rv<volatile T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_not_same_rv<const volatile T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<const volatile T, const U>::value);
    STATIC_REQUIRE(phi::is_not_same_rv<const volatile T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<const volatile T, const volatile U>::value);

    // is_same_rv_v
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_rv_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_same_rv_v<T, const U>);
    STATIC_REQUIRE(phi::is_same_rv_v<T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_same_rv_v<T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_same_rv_v<const T, U>);
    STATIC_REQUIRE(phi::is_same_rv_v<const T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_same_rv_v<const T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rv_v<const T, const volatile U>);

    STATIC_REQUIRE(phi::is_same_rv_v<volatile T, U>);
    STATIC_REQUIRE_FALSE(phi::is_same_rv_v<volatile T, const U>);
    STATIC_REQUIRE(phi::is_same_rv_v<volatile T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_same_rv_v<volatile T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_same_rv_v<const volatile T, U>);
    STATIC_REQUIRE(phi::is_same_rv_v<const volatile T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_same_rv_v<const volatile T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rv_v<const volatile T, const volatile U>);

    // is_not_same_rv_v
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<T, U>);
    STATIC_REQUIRE(phi::is_not_same_rv_v<T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<T, volatile U>);
    STATIC_REQUIRE(phi::is_not_same_rv_v<T, const volatile U>);

    STATIC_REQUIRE(phi::is_not_same_rv_v<const T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<const T, const U>);
    STATIC_REQUIRE(phi::is_not_same_rv_v<const T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<const T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<volatile T, U>);
    STATIC_REQUIRE(phi::is_not_same_rv_v<volatile T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<volatile T, volatile U>);
    STATIC_REQUIRE(phi::is_not_same_rv_v<volatile T, const volatile U>);

    STATIC_REQUIRE(phi::is_not_same_rv_v<const volatile T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<const volatile T, const U>);
    STATIC_REQUIRE(phi::is_not_same_rv_v<const volatile T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<const volatile T, const volatile U>);
#endif
}

template <typename T, typename U>
void test_is_same_rv_ref()
{
    // is_same_rv
    STATIC_REQUIRE(phi::is_same_rv<T, U>::value);
    STATIC_REQUIRE(phi::is_same_rv<T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rv<T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rv<T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_same_rv<const T, U>::value);
    STATIC_REQUIRE(phi::is_same_rv<const T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rv<const T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rv<const T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_same_rv<volatile T, U>::value);
    STATIC_REQUIRE(phi::is_same_rv<volatile T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rv<volatile T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rv<volatile T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_same_rv<const volatile T, U>::value);
    STATIC_REQUIRE(phi::is_same_rv<const volatile T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rv<const volatile T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rv<const volatile T, const volatile U>::value);

    // is_same_rv_not
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<const T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<const T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<const T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<const T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<volatile T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<volatile T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<volatile T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<volatile T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<const volatile T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<const volatile T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<const volatile T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<const volatile T, const volatile U>::value);

    // is_same_rv_v
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_rv_v<T, U>);
    STATIC_REQUIRE(phi::is_same_rv_v<T, const U>);
    STATIC_REQUIRE(phi::is_same_rv_v<T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rv_v<T, const volatile U>);

    STATIC_REQUIRE(phi::is_same_rv_v<const T, U>);
    STATIC_REQUIRE(phi::is_same_rv_v<const T, const U>);
    STATIC_REQUIRE(phi::is_same_rv_v<const T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rv_v<const T, const volatile U>);

    STATIC_REQUIRE(phi::is_same_rv_v<volatile T, U>);
    STATIC_REQUIRE(phi::is_same_rv_v<volatile T, const U>);
    STATIC_REQUIRE(phi::is_same_rv_v<volatile T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rv_v<volatile T, const volatile U>);

    STATIC_REQUIRE(phi::is_same_rv_v<const volatile T, U>);
    STATIC_REQUIRE(phi::is_same_rv_v<const volatile T, const U>);
    STATIC_REQUIRE(phi::is_same_rv_v<const volatile T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rv_v<const volatile T, const volatile U>);

    // is_same_rv_not_v
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<const T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<const T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<const T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<const T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<volatile T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<volatile T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<volatile T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<volatile T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<const volatile T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<const volatile T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<const volatile T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<const volatile T, const volatile U>);
#endif
}

template <typename T, typename U>
void test_is_not_same_rv()
{
    STATIC_REQUIRE_FALSE(phi::is_same_rv<T, U>::value);
    STATIC_REQUIRE(phi::is_not_same_rv<T, U>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_same_rv_v<T, U>);
    STATIC_REQUIRE(phi::is_not_same_rv_v<T, U>);
#endif
}

template <typename T>
struct OverloadTest
{
    void fn(phi::is_same_rv<T, int>)
    {}
    void fn(phi::false_type)
    {}
    void x()
    {
        fn(phi::false_type());
    }
};

struct A; // incomplete

TEST_CASE("is_same_rv")
{
    test_is_same_rv<short, short>();
    test_is_same_rv<int, int>();
    test_is_same_rv<unsigned, unsigned>();
    test_is_same_rv<float, float>();
    test_is_same_rv<double, double>();
    test_is_same_rv<void, void>();
    test_is_same_rv<int*, int*>();
    test_is_same_rv<const int*, const int*>();
    test_is_same_rv<volatile int*, volatile int*>();
    test_is_same_rv<const volatile int*, const volatile int*>();
    test_is_same_rv<Class, Class>();
    test_is_same_rv<A, A>();
    test_is_same_rv<IncompleteType, IncompleteType>();
    test_is_same_rv<Empty, Empty>();
    test_is_same_rv<NotEmpty, NotEmpty>();
    test_is_same_rv<Union, Union>();
    test_is_same_rv<BitZero, BitZero>();
    test_is_same_rv<Abstract, Abstract>();
    test_is_same_rv<Enum, Enum>();
    test_is_same_rv<EnumSigned, EnumSigned>();
    test_is_same_rv<EnumUnsigned, EnumUnsigned>();
    test_is_same_rv<EnumClass, EnumClass>();

    test_is_same_rv_ref<int&, int&>();
    test_is_same_rv_ref<float&, float&>();
    test_is_same_rv_ref<Class&, Class&>();

    test_is_not_same_rv<int, void>();
    test_is_not_same_rv<void, Class>();
    test_is_not_same_rv<Class, int*>();
    test_is_not_same_rv<int*, int&>();
    test_is_not_same_rv<int&, int>();

    OverloadTest<char> t;
    (void)t;
}
