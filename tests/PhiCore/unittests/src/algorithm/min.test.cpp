#include <phi/test/test_macros.hpp>

#include <phi/algorithm/min.hpp>

TEST_CASE("min")
{
    STATIC_REQUIRE(phi::min(0) == 0);
    STATIC_REQUIRE(phi::min(3) == 3);
    STATIC_REQUIRE(phi::min(35u) == 35u);

    STATIC_REQUIRE(phi::min(0, 1) == 0);
    STATIC_REQUIRE(phi::min(1, 0) == 0);
    STATIC_REQUIRE(phi::min(3) == 3);
    STATIC_REQUIRE(phi::min(3, 5) == 3);
    STATIC_REQUIRE(phi::min(3, 1) == 1);
    STATIC_REQUIRE(phi::min(35u, 49u) == 35u);
    STATIC_REQUIRE(phi::min(35u, 12u) == 12u);
    STATIC_REQUIRE(phi::min(35, 49u) == 35u);
    STATIC_REQUIRE(phi::min(35u, 12) == 12u);

    STATIC_REQUIRE(phi::min(0, 0, 0) == 0);
    STATIC_REQUIRE(phi::min(1, 0, 0) == 0);
    STATIC_REQUIRE(phi::min(0, 1, 0) == 0);
    STATIC_REQUIRE(phi::min(0, 0, 1) == 0);
    STATIC_REQUIRE(phi::min(1, 1, 0) == 0);
    STATIC_REQUIRE(phi::min(0, 1, 1) == 0);
    STATIC_REQUIRE(phi::min(1, 0, 1) == 0);
    STATIC_REQUIRE(phi::min(1, 1, 1) == 1);

    STATIC_REQUIRE(phi::min(0, 1, 2, 3, 4, 5, 6, 7, 8, 9) == 0);
}
