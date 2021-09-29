#include <catch2/catch.hpp>

#include <Phi/TypeTraits/is_trivially_constructible.hpp>

template <typename T, typename... ArgsT>
void test_is_trivially_constructible()
{
    STATIC_REQUIRE(phi::is_trivially_constructible<T, ArgsT...>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_constructible_v<T, ArgsT...>);
#endif
}

template <typename T, typename... ArgsT>
void test_is_not_trivially_constructible()
{
    STATIC_REQUIRE_FALSE(phi::is_trivially_constructible<T, ArgsT...>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_constructible_v<T, ArgsT...>);
#endif
}

struct A
{
    explicit A(int);
    A(int, double);
};

struct B
{
    B() = default;

    B(int)
    {}
};

TEST_CASE("is_trivially_constructible")
{
    test_is_trivially_constructible<int>();
    test_is_trivially_constructible<int, int>();
    test_is_trivially_constructible<int, int&>();
    test_is_trivially_constructible<int, const int&>();

    test_is_not_trivially_constructible<A>();
    test_is_not_trivially_constructible<A, int>();
    test_is_not_trivially_constructible<A, int, double>();

    test_is_trivially_constructible<B>();
    test_is_not_trivially_constructible<B, int>();
}
