#include <catch2/catch.hpp>

#include <Phi/TypeTraits/is_trivially_assignable.hpp>

template <typename T, typename U>
void test_is_trivially_assignable()
{
    STATIC_REQUIRE(phi::is_trivially_assignable<T, U>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_assignable_v<T, U>);
#endif
}

template <typename T, typename U>
void test_is_not_trivially_assignable()
{
    STATIC_REQUIRE_FALSE(phi::is_trivially_assignable<T, U>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_assignable_v<T, U>);
#endif
}

struct A
{};

struct B
{
    B& operator=(A);
};

struct C
{
    C& operator=(C&); // not const
};

struct D
{
    D& operator=(const D&) = default;
};

struct E
{
    E& operator=(const E&);
};

TEST_CASE("is_trivially_assignable")
{
    test_is_trivially_assignable<int&, int>();
    test_is_trivially_assignable<int&, int&>();
    test_is_trivially_assignable<int&, double>();

    test_is_not_trivially_assignable<int, int&>();
    test_is_not_trivially_assignable<int, int>();
    test_is_not_trivially_assignable<B, A>();
    test_is_not_trivially_assignable<A, B>();
    test_is_not_trivially_assignable<C&, C&>();
    test_is_trivially_assignable<D&, const D&>();
    test_is_not_trivially_assignable<E&, const E&>();
}
