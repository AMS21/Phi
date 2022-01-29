#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/type_traits/integral_constant.hpp>
#include <phi/type_traits/is_same_rc.hpp>

template <typename T, typename U>
void test_is_same_rc()
{
    // is_same_rc
    STATIC_REQUIRE(phi::is_same_rc<T, U>::value);
    STATIC_REQUIRE(phi::is_same_rc<T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same_rc<T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same_rc<T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_same_rc<const T, U>::value);
    STATIC_REQUIRE(phi::is_same_rc<const T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same_rc<const T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same_rc<const T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_same_rc<volatile T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same_rc<volatile T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rc<volatile T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rc<volatile T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_same_rc<const volatile T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same_rc<const volatile T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rc<const volatile T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rc<const volatile T, const volatile U>::value);

    // is_not_same_rc
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<T, const U>::value);
    STATIC_REQUIRE(phi::is_not_same_rc<T, volatile U>::value);
    STATIC_REQUIRE(phi::is_not_same_rc<T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<const T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<const T, const U>::value);
    STATIC_REQUIRE(phi::is_not_same_rc<const T, volatile U>::value);
    STATIC_REQUIRE(phi::is_not_same_rc<const T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_not_same_rc<volatile T, U>::value);
    STATIC_REQUIRE(phi::is_not_same_rc<volatile T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<volatile T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<volatile T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_not_same_rc<const volatile T, U>::value);
    STATIC_REQUIRE(phi::is_not_same_rc<const volatile T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<const volatile T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<const volatile T, const volatile U>::value);

    // is_same_rc_v
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_rc_v<T, U>);
    STATIC_REQUIRE(phi::is_same_rc_v<T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_same_rc_v<T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_same_rc_v<T, const volatile U>);

    STATIC_REQUIRE(phi::is_same_rc_v<const T, U>);
    STATIC_REQUIRE(phi::is_same_rc_v<const T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_same_rc_v<const T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_same_rc_v<const T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_same_rc_v<volatile T, U>);
    STATIC_REQUIRE_FALSE(phi::is_same_rc_v<volatile T, const U>);
    STATIC_REQUIRE(phi::is_same_rc_v<volatile T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rc_v<volatile T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_same_rc_v<const volatile T, U>);
    STATIC_REQUIRE_FALSE(phi::is_same_rc_v<const volatile T, const U>);
    STATIC_REQUIRE(phi::is_same_rc_v<const volatile T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rc_v<const volatile T, const volatile U>);

    // is_not_same_rc_v
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<T, const U>);
    STATIC_REQUIRE(phi::is_not_same_rc_v<T, volatile U>);
    STATIC_REQUIRE(phi::is_not_same_rc_v<T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<const T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<const T, const U>);
    STATIC_REQUIRE(phi::is_not_same_rc_v<const T, volatile U>);
    STATIC_REQUIRE(phi::is_not_same_rc_v<const T, const volatile U>);

    STATIC_REQUIRE(phi::is_not_same_rc_v<volatile T, U>);
    STATIC_REQUIRE(phi::is_not_same_rc_v<volatile T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<volatile T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<volatile T, const volatile U>);

    STATIC_REQUIRE(phi::is_not_same_rc_v<const volatile T, U>);
    STATIC_REQUIRE(phi::is_not_same_rc_v<const volatile T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<const volatile T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<const volatile T, const volatile U>);
#endif
}

template <typename T, typename U>
void test_is_same_rc_ref()
{
    // is_same_rc
    STATIC_REQUIRE(phi::is_same_rc<T, U>::value);
    STATIC_REQUIRE(phi::is_same_rc<T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rc<T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rc<T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_same_rc<const T, U>::value);
    STATIC_REQUIRE(phi::is_same_rc<const T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rc<const T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rc<const T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_same_rc<volatile T, U>::value);
    STATIC_REQUIRE(phi::is_same_rc<volatile T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rc<volatile T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rc<volatile T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_same_rc<const volatile T, U>::value);
    STATIC_REQUIRE(phi::is_same_rc<const volatile T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rc<const volatile T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rc<const volatile T, const volatile U>::value);

    // is_same_rc_not
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<const T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<const T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<const T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<const T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<volatile T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<volatile T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<volatile T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<volatile T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<const volatile T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<const volatile T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<const volatile T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<const volatile T, const volatile U>::value);

    // is_same_rc_v
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_rc_v<T, U>);
    STATIC_REQUIRE(phi::is_same_rc_v<T, const U>);
    STATIC_REQUIRE(phi::is_same_rc_v<T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rc_v<T, const volatile U>);

    STATIC_REQUIRE(phi::is_same_rc_v<const T, U>);
    STATIC_REQUIRE(phi::is_same_rc_v<const T, const U>);
    STATIC_REQUIRE(phi::is_same_rc_v<const T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rc_v<const T, const volatile U>);

    STATIC_REQUIRE(phi::is_same_rc_v<volatile T, U>);
    STATIC_REQUIRE(phi::is_same_rc_v<volatile T, const U>);
    STATIC_REQUIRE(phi::is_same_rc_v<volatile T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rc_v<volatile T, const volatile U>);

    STATIC_REQUIRE(phi::is_same_rc_v<const volatile T, U>);
    STATIC_REQUIRE(phi::is_same_rc_v<const volatile T, const U>);
    STATIC_REQUIRE(phi::is_same_rc_v<const volatile T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rc_v<const volatile T, const volatile U>);

    // is_same_rc_not_v
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<const T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<const T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<const T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<const T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<volatile T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<volatile T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<volatile T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<volatile T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<const volatile T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<const volatile T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<const volatile T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<const volatile T, const volatile U>);
#endif
}

template <typename T, typename U>
void test_is_not_same_rc()
{
    STATIC_REQUIRE_FALSE(phi::is_same_rc<T, U>::value);
    STATIC_REQUIRE(phi::is_not_same_rc<T, U>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_same_rc_v<T, U>);
    STATIC_REQUIRE(phi::is_not_same_rc_v<T, U>);
#endif
}

template <typename T>
struct OverloadTest
{
    void fn(phi::is_same_rc<T, int>)
    {}
    void fn(phi::false_type)
    {}
    void x()
    {
        fn(phi::false_type());
    }
};

struct A; // incomplete

TEST_CASE("is_same_rc")
{
    test_is_same_rc<short, short>();
    test_is_same_rc<int, int>();
    test_is_same_rc<unsigned, unsigned>();
    test_is_same_rc<float, float>();
    test_is_same_rc<double, double>();
    test_is_same_rc<void, void>();
    test_is_same_rc<int*, int*>();
    test_is_same_rc<const int*, const int*>();
    test_is_same_rc<volatile int*, volatile int*>();
    test_is_same_rc<const volatile int*, const volatile int*>();
    test_is_same_rc<Class, Class>();
    test_is_same_rc<A, A>();
    test_is_same_rc<IncompleteType, IncompleteType>();
    test_is_same_rc<Empty, Empty>();
    test_is_same_rc<NotEmpty, NotEmpty>();
    test_is_same_rc<Union, Union>();
    test_is_same_rc<BitZero, BitZero>();
    test_is_same_rc<Abstract, Abstract>();
    test_is_same_rc<Enum, Enum>();
    test_is_same_rc<EnumSigned, EnumSigned>();
    test_is_same_rc<EnumUnsigned, EnumUnsigned>();
    test_is_same_rc<EnumClass, EnumClass>();

    test_is_same_rc_ref<int&, int&>();
    test_is_same_rc_ref<float&, float&>();
    test_is_same_rc_ref<Class&, Class&>();

    test_is_not_same_rc<int, void>();
    test_is_not_same_rc<void, Class>();
    test_is_not_same_rc<Class, int*>();
    test_is_not_same_rc<int*, int&>();
    test_is_not_same_rc<int&, int>();

    OverloadTest<char> t;
    (void)t;
}
