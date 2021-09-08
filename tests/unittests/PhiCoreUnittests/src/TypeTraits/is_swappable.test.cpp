#include <catch2/catch_test_macros.hpp>

#include <Phi/TypeTraits/is_swappable.hpp>

TEST_CASE("is_swappable")
{
    STATIC_REQUIRE(phi::is_swappable<int>::value);
}
