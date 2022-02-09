#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/algorithm/max.hpp>

TEST_CASE("max")
{
    STATIC_REQUIRE(phi::max(0) == 0);
    STATIC_REQUIRE(phi::max(3) == 3);
    STATIC_REQUIRE(phi::max(35u) == 35u);

    STATIC_REQUIRE(phi::max(0, 1) == 1);
    STATIC_REQUIRE(phi::max(1, 0) == 1);
    STATIC_REQUIRE(phi::max(3) == 3);
    STATIC_REQUIRE(phi::max(3, 5) == 5);
    STATIC_REQUIRE(phi::max(3, 1) == 3);
    STATIC_REQUIRE(phi::max(35u, 49u) == 49u);
    STATIC_REQUIRE(phi::max(35u, 12u) == 35u);
    STATIC_REQUIRE(phi::max(35u, 49) == 49u);
    STATIC_REQUIRE(phi::max(35, 12u) == 35u);

    STATIC_REQUIRE(phi::max(0, 0, 0) == 0);
    STATIC_REQUIRE(phi::max(1, 0, 0) == 1);
    STATIC_REQUIRE(phi::max(0, 1, 0) == 1);
    STATIC_REQUIRE(phi::max(0, 0, 1) == 1);
    STATIC_REQUIRE(phi::max(1, 1, 0) == 1);
    STATIC_REQUIRE(phi::max(1, 0, 1) == 1);
    STATIC_REQUIRE(phi::max(0, 1, 1) == 1);
    STATIC_REQUIRE(phi::max(1, 1, 1) == 1);
}
