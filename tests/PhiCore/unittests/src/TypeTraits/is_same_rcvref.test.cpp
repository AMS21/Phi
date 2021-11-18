#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/TypeTraits/add_lvalue_reference.hpp>
#include <Phi/TypeTraits/add_rvalue_reference.hpp>
#include <Phi/TypeTraits/integral_constant.hpp>
#include <Phi/TypeTraits/is_same_rcvref.hpp>

template <typename T, typename U>
void test_is_same_rcvref_impl()
{
    // is_same_rcvref
    STATIC_REQUIRE(phi::is_same_rcvref<T, U>::value);
    STATIC_REQUIRE(phi::is_same_rcvref<T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rcvref<T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rcvref<T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_same_rcvref<const T, U>::value);
    STATIC_REQUIRE(phi::is_same_rcvref<const T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rcvref<const T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rcvref<const T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_same_rcvref<volatile T, U>::value);
    STATIC_REQUIRE(phi::is_same_rcvref<volatile T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rcvref<volatile T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rcvref<volatile T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_same_rcvref<const volatile T, U>::value);
    STATIC_REQUIRE(phi::is_same_rcvref<const volatile T, const U>::value);
    STATIC_REQUIRE(phi::is_same_rcvref<const volatile T, volatile U>::value);
    STATIC_REQUIRE(phi::is_same_rcvref<const volatile T, const volatile U>::value);

    // is_not_same_rcvref
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref<T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref<T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref<T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref<const T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref<const T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref<const T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref<const T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref<volatile T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref<volatile T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref<volatile T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref<volatile T, const volatile U>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref<const volatile T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref<const volatile T, const U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref<const volatile T, volatile U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref<const volatile T, const volatile U>::value);

    // is_same_rcvref_v
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_rcvref_v<T, U>);
    STATIC_REQUIRE(phi::is_same_rcvref_v<T, const U>);
    STATIC_REQUIRE(phi::is_same_rcvref_v<T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rcvref_v<T, const volatile U>);

    STATIC_REQUIRE(phi::is_same_rcvref_v<const T, U>);
    STATIC_REQUIRE(phi::is_same_rcvref_v<const T, const U>);
    STATIC_REQUIRE(phi::is_same_rcvref_v<const T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rcvref_v<const T, const volatile U>);

    STATIC_REQUIRE(phi::is_same_rcvref_v<volatile T, U>);
    STATIC_REQUIRE(phi::is_same_rcvref_v<volatile T, const U>);
    STATIC_REQUIRE(phi::is_same_rcvref_v<volatile T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rcvref_v<volatile T, const volatile U>);

    STATIC_REQUIRE(phi::is_same_rcvref_v<const volatile T, U>);
    STATIC_REQUIRE(phi::is_same_rcvref_v<const volatile T, const U>);
    STATIC_REQUIRE(phi::is_same_rcvref_v<const volatile T, volatile U>);
    STATIC_REQUIRE(phi::is_same_rcvref_v<const volatile T, const volatile U>);

    // is_not_same_rcvref_v
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref_v<T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref_v<T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref_v<T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref_v<const T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref_v<const T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref_v<const T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref_v<const T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref_v<volatile T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref_v<volatile T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref_v<volatile T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref_v<volatile T, const volatile U>);

    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref_v<const volatile T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref_v<const volatile T, const U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref_v<const volatile T, volatile U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref_v<const volatile T, const volatile U>);
#endif
}

template <typename T, typename U>
void test_is_same_rcvref()
{
    test_is_same_rcvref_impl<T, U>();
    test_is_same_rcvref_impl<T, phi::add_lvalue_reference_t<U>>();
    test_is_same_rcvref_impl<T, phi::add_rvalue_reference_t<U>>();

    test_is_same_rcvref_impl<phi::add_lvalue_reference_t<T>, U>();
    test_is_same_rcvref_impl<phi::add_lvalue_reference_t<T>, phi::add_lvalue_reference_t<U>>();
    test_is_same_rcvref_impl<phi::add_lvalue_reference_t<T>, phi::add_rvalue_reference_t<U>>();

    test_is_same_rcvref_impl<phi::add_rvalue_reference_t<T>, U>();
    test_is_same_rcvref_impl<phi::add_rvalue_reference_t<T>, phi::add_lvalue_reference_t<U>>();
    test_is_same_rcvref_impl<phi::add_rvalue_reference_t<T>, phi::add_rvalue_reference_t<U>>();
}

template <typename T, typename U>
void test_is_not_same_rcvref()
{
    STATIC_REQUIRE_FALSE(phi::is_same_rcvref<T, U>::value);
    STATIC_REQUIRE(phi::is_not_same_rcvref<T, U>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_same_rcvref_v<T, U>);
    STATIC_REQUIRE(phi::is_not_same_rcvref_v<T, U>);
#endif
}

template <typename T>
struct OverloadTest
{
    void fn(phi::is_same_rcvref<T, int>)
    {}
    void fn(phi::false_type)
    {}
    void x()
    {
        fn(phi::false_type());
    }
};

struct A; // incomplete

TEST_CASE("is_same_rcvref")
{
    test_is_same_rcvref<short, short>();
    test_is_same_rcvref<int, int>();
    test_is_same_rcvref<unsigned, unsigned>();
    test_is_same_rcvref<float, float>();
    test_is_same_rcvref<double, double>();
    test_is_same_rcvref<void, void>();
    test_is_same_rcvref<int*, int*>();
    test_is_same_rcvref<const int*, const int*>();
    test_is_same_rcvref<volatile int*, volatile int*>();
    test_is_same_rcvref<const volatile int*, const volatile int*>();
    test_is_same_rcvref<Class, Class>();
    test_is_same_rcvref<A, A>();
    test_is_same_rcvref<incomplete_type, incomplete_type>();
    test_is_same_rcvref<Empty, Empty>();
    test_is_same_rcvref<NotEmpty, NotEmpty>();
    test_is_same_rcvref<Union, Union>();
    test_is_same_rcvref<bit_zero, bit_zero>();
    test_is_same_rcvref<Abstract, Abstract>();
    test_is_same_rcvref<Enum, Enum>();
    test_is_same_rcvref<EnumSigned, EnumSigned>();
    test_is_same_rcvref<EnumUnsigned, EnumUnsigned>();
    test_is_same_rcvref<EnumClass, EnumClass>();

    test_is_same_rcvref<int&, int&>();
    test_is_same_rcvref<float&, float&>();
    test_is_same_rcvref<Class&, Class&>();

    test_is_not_same_rcvref<int, void>();
    test_is_not_same_rcvref<void, Class>();
    test_is_not_same_rcvref<Class, int*>();
    test_is_not_same_rcvref<int*, int&>();

    OverloadTest<char> t;
    (void)t;
}
