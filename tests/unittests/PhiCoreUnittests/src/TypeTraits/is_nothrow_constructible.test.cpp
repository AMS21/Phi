#include <catch2/catch_test_macros.hpp>

#include "TestTypes.hpp"
#include <Phi/TypeTraits/is_nothrow_constructible.hpp>

template <typename T>
void test_is_nothrow_constructible()
{
    STATIC_REQUIRE(phi::is_nothrow_constructible<T>::value);
    STATIC_REQUIRE(phi::is_nothrow_constructible_v<T>);
}

template <typename T, typename A0>
void test_is_nothrow_constructible()
{
    STATIC_REQUIRE(phi::is_nothrow_constructible<T, A0>::value);
    STATIC_REQUIRE(phi::is_nothrow_constructible_v<T, A0>);
}

template <typename T>
void test_is_not_nothrow_constructible()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_constructible<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_constructible_v<T>);
}

template <typename T, typename A0>
void test_is_not_nothrow_constructible()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_constructible<T, A0>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_constructible_v<T, A0>);
}

template <typename T, typename A0, typename A1>
void test_is_not_nothrow_constructible()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_constructible<T, A0, A1>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_constructible_v<T, A0, A1>);
}

struct A
{
    A(const A&);
};

struct C
{
    C(C&);              // not const
    void operator=(C&); // not const
};

struct Tuple
{
    Tuple(Empty&&) noexcept
    {}
};

TEST_CASE("is_nothrow_constructible")
{
    test_is_nothrow_constructible<int>();
    test_is_nothrow_constructible<int, const int&>();
    test_is_nothrow_constructible<Empty>();
    test_is_nothrow_constructible<Empty, const Empty&>();

    test_is_not_nothrow_constructible<A, int>();
    test_is_not_nothrow_constructible<A, int, double>();
    test_is_not_nothrow_constructible<A>();
    test_is_not_nothrow_constructible<C>();
    test_is_nothrow_constructible<Tuple&&, Empty>();

    STATIC_REQUIRE_FALSE(phi::is_constructible<Tuple&, Empty>::value);
    STATIC_REQUIRE_FALSE(phi::is_constructible_v<Tuple&, Empty>);
    test_is_not_nothrow_constructible<Tuple&, Empty>();
}
