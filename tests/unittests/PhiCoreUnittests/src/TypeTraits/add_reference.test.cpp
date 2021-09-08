#include <catch2/catch_test_macros.hpp>

#include <Phi/TypeTraits/add_reference.hpp>
#include <Phi/TypeTraits/is_same.hpp>

TEST_CASE("add_reference")
{
    STATIC_REQUIRE(phi::is_same_v<typename phi::add_reference<int>::type, int&>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::add_reference<int&>::type, int&>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::add_reference<int&&>::type, int&&>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::add_reference<double>::type, double&>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::add_reference<const int>::type, const int&>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::add_reference<volatile int>::type, volatile int&>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::add_reference<const volatile int>::type,
                                  const volatile int&>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::add_reference<void>::type, void>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::add_reference<const void>::type, const void>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::add_reference<volatile void>::type, volatile void>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::add_reference<const volatile void>::type,
                                  const volatile void>);
}

TEST_CASE("add_reference_t")
{
    STATIC_REQUIRE(phi::is_same_v<phi::add_reference_t<int>, int&>);
    STATIC_REQUIRE(phi::is_same_v<phi::add_reference_t<int&>, int&>);
    STATIC_REQUIRE(phi::is_same_v<phi::add_reference_t<int&&>, int&&>);
    STATIC_REQUIRE(phi::is_same_v<phi::add_reference_t<double>, double&>);
    STATIC_REQUIRE(phi::is_same_v<phi::add_reference_t<const int>, const int&>);
    STATIC_REQUIRE(phi::is_same_v<phi::add_reference_t<volatile int>, volatile int&>);
    STATIC_REQUIRE(phi::is_same_v<phi::add_reference_t<const volatile int>, const volatile int&>);
    STATIC_REQUIRE(phi::is_same_v<phi::add_reference_t<void>, void>);
    STATIC_REQUIRE(phi::is_same_v<phi::add_reference_t<const void>, const void>);
    STATIC_REQUIRE(phi::is_same_v<phi::add_reference_t<volatile void>, volatile void>);
    STATIC_REQUIRE(phi::is_same_v<phi::add_reference_t<const volatile void>, const volatile void>);
}
