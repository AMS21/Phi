#include <Phi/Test/TestMacros.hpp>

#include <Phi/TypeTraits/is_base_of.hpp>

template <typename T, typename U>
void test_is_base_of()
{
    // is_base_of
    STATIC_REQUIRE(phi::is_base_of<T, U>::value);
    STATIC_REQUIRE(phi::is_base_of<T, const U>::value);
    STATIC_REQUIRE(phi::is_base_of<T, volatile U>::value);
    STATIC_REQUIRE(phi::is_base_of<T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_base_of<const T, U>::value);
    STATIC_REQUIRE(phi::is_base_of<const T, const U>::value);
    STATIC_REQUIRE(phi::is_base_of<const T, volatile U>::value);
    STATIC_REQUIRE(phi::is_base_of<const T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_base_of<volatile T, U>::value);
    STATIC_REQUIRE(phi::is_base_of<volatile T, const U>::value);
    STATIC_REQUIRE(phi::is_base_of<volatile T, volatile U>::value);
    STATIC_REQUIRE(phi::is_base_of<volatile T, const volatile U>::value);

    STATIC_REQUIRE(phi::is_base_of<const volatile T, U>::value);
    STATIC_REQUIRE(phi::is_base_of<const volatile T, const U>::value);
    STATIC_REQUIRE(phi::is_base_of<const volatile T, volatile U>::value);
    STATIC_REQUIRE(phi::is_base_of<const volatile T, const volatile U>::value);

    // is_base_of_v
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_base_of_v<T, U>);
    STATIC_REQUIRE(phi::is_base_of_v<T, const U>);
    STATIC_REQUIRE(phi::is_base_of_v<T, volatile U>);
    STATIC_REQUIRE(phi::is_base_of_v<T, const volatile U>);

    STATIC_REQUIRE(phi::is_base_of_v<const T, U>);
    STATIC_REQUIRE(phi::is_base_of_v<const T, const U>);
    STATIC_REQUIRE(phi::is_base_of_v<const T, volatile U>);
    STATIC_REQUIRE(phi::is_base_of_v<const T, const volatile U>);

    STATIC_REQUIRE(phi::is_base_of_v<volatile T, U>);
    STATIC_REQUIRE(phi::is_base_of_v<volatile T, const U>);
    STATIC_REQUIRE(phi::is_base_of_v<volatile T, volatile U>);
    STATIC_REQUIRE(phi::is_base_of_v<volatile T, const volatile U>);

    STATIC_REQUIRE(phi::is_base_of_v<const volatile T, U>);
    STATIC_REQUIRE(phi::is_base_of_v<const volatile T, const U>);
    STATIC_REQUIRE(phi::is_base_of_v<const volatile T, volatile U>);
    STATIC_REQUIRE(phi::is_base_of_v<const volatile T, const volatile U>);
#endif
}

template <typename T, typename U>
void test_is_not_base_of()
{
    STATIC_REQUIRE_FALSE(phi::is_base_of<T, U>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_base_of_v<T, U>);
#endif
}

struct B
{};
struct B1 : B
{};
struct B2 : B
{};
struct D : private B1, private B2
{};
union U0;
union U1
{};
struct I0; // incomplete
struct I1
{};

TEST_CASE("is_base_of")
{
    test_is_base_of<B, D>();
    test_is_base_of<B1, D>();
    test_is_base_of<B2, D>();
    test_is_base_of<B, B1>();
    test_is_base_of<B, B2>();
    test_is_base_of<B, B>();

    test_is_not_base_of<D, B>();
    test_is_not_base_of<B&, D&>();
    test_is_not_base_of<B[3], D[3]>();
    test_is_not_base_of<int, int>();

    //  A scalar is never the base class of anything (including incomplete types)
    test_is_not_base_of<int, B>();
    test_is_not_base_of<int, B1>();
    test_is_not_base_of<int, B2>();
    test_is_not_base_of<int, D>();
    test_is_not_base_of<int, I0>();

    //  A scalar never has base classes (including incomplete types)
    test_is_not_base_of<B, int>();
    test_is_not_base_of<B1, int>();
    test_is_not_base_of<B2, int>();
    test_is_not_base_of<D, int>();
    test_is_not_base_of<I0, int>();

    // A union is never the base class of anything(including incomplete types)
    test_is_not_base_of<U0, B>();
    test_is_not_base_of<U0, B1>();
    test_is_not_base_of<U0, B2>();
    test_is_not_base_of<U0, D>();
    test_is_not_base_of<U1, B>();
    test_is_not_base_of<U1, B1>();
    test_is_not_base_of<U1, B2>();
    test_is_not_base_of<U1, D>();
    test_is_not_base_of<U0, I0>();
    test_is_not_base_of<U1, I1>();
    test_is_not_base_of<U0, U1>();
    test_is_not_base_of<U0, int>();
    test_is_not_base_of<U1, int>();
    test_is_not_base_of<I0, int>();
    test_is_not_base_of<I1, int>();

    // A union never has base classes (including incomplete types)
    test_is_not_base_of<B, U0>();
    test_is_not_base_of<B1, U0>();
    test_is_not_base_of<B2, U0>();
    test_is_not_base_of<D, U0>();
    test_is_not_base_of<B, U1>();
    test_is_not_base_of<B1, U1>();
    test_is_not_base_of<B2, U1>();
    test_is_not_base_of<D, U1>();
    test_is_not_base_of<I0, U0>();
    test_is_not_base_of<I1, U1>();
    test_is_not_base_of<U1, U0>();
    test_is_not_base_of<int, U0>();
    test_is_not_base_of<int, U1>();
    test_is_not_base_of<int, I0>();
    test_is_not_base_of<int, I1>();
}