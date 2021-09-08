#include <catch2/catch_test_macros.hpp>

#include <Phi/TypeTraits/conditional.hpp>
#include <Phi/TypeTraits/is_same.hpp>

TEST_CASE("type_traits.conditional")
{
    STATIC_REQUIRE(phi::is_same_v<phi::conditional<true, int, double>::type, int>);
    STATIC_REQUIRE(phi::is_same_v<phi::conditional<false, int, double>::type, double>);
    STATIC_REQUIRE(
            phi::is_same_v<phi::conditional<sizeof(int) >= sizeof(double), int, double>::type,
                           double>);
}

TEST_CASE("type_traits.conditional_v")
{
    STATIC_REQUIRE(phi::is_same_v<phi::conditional_t<true, int, double>, int>);
    STATIC_REQUIRE(phi::is_same_v<phi::conditional_t<false, int, double>, double>);
    STATIC_REQUIRE(
            phi::is_same_v<phi::conditional_t<sizeof(int) >= sizeof(double), int, double>, double>);
}
