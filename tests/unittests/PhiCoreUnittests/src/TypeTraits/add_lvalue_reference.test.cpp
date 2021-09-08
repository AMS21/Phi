#include <catch2/catch_test_macros.hpp>

#include <Phi/TypeTraits/add_lvalue_reference.hpp>
#include <Phi/TypeTraits/is_same.hpp>

TEST_CASE("add_lvalue_reference")
{
    STATIC_REQUIRE(phi::is_same_v<typename phi::add_lvalue_reference<int>::type, int&>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::add_lvalue_reference<int&>::type, int&>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::add_lvalue_reference<int&&>::type, int&>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::add_lvalue_reference<const int>::type, const int&>);
    STATIC_REQUIRE(
            phi::is_same_v<typename phi::add_lvalue_reference<volatile int>::type, volatile int&>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::add_lvalue_reference<const volatile int>::type,
                                  const volatile int&>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::add_lvalue_reference<double>::type, double&>);
}

TEST_CASE("add_lvalue_reference_t")
{
    STATIC_REQUIRE(phi::is_same_v<phi::add_lvalue_reference_t<int>, int&>);
    STATIC_REQUIRE(phi::is_same_v<phi::add_lvalue_reference_t<int&>, int&>);
    STATIC_REQUIRE(phi::is_same_v<phi::add_lvalue_reference_t<int&&>, int&>);
    STATIC_REQUIRE(phi::is_same_v<phi::add_lvalue_reference_t<const int>, const int&>);
    STATIC_REQUIRE(phi::is_same_v<phi::add_lvalue_reference_t<volatile int>, volatile int&>);
    STATIC_REQUIRE(
            phi::is_same_v<phi::add_lvalue_reference_t<const volatile int>, const volatile int&>);
    STATIC_REQUIRE(phi::is_same_v<phi::add_lvalue_reference_t<double>, double&>);
}
