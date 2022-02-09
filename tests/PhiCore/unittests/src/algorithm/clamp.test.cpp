#include <phi/test/test_macros.hpp>

#include <phi/algorithm/clamp.hpp>

TEST_CASE("clamp")
{
    STATIC_REQUIRE(phi::clamp(1, 1, 1) == 1);
    STATIC_REQUIRE(phi::clamp(2, 1, 1) == 1);
    STATIC_REQUIRE(phi::clamp(0, 0, 1) == 0);
    STATIC_REQUIRE(phi::clamp(1, 0, 1) == 1);
    STATIC_REQUIRE(phi::clamp(2, 0, 1) == 1);
    STATIC_REQUIRE(phi::clamp(-1, 0, 1) == 0);

    STATIC_REQUIRE(phi::clamp(1, 5, 10) == 5);
    STATIC_REQUIRE(phi::clamp(5, 5, 10) == 5);
    STATIC_REQUIRE(phi::clamp(6, 5, 10) == 6);
    STATIC_REQUIRE(phi::clamp(7, 5, 10) == 7);
    STATIC_REQUIRE(phi::clamp(8, 5, 10) == 8);
    STATIC_REQUIRE(phi::clamp(9, 5, 10) == 9);
    STATIC_REQUIRE(phi::clamp(10, 5, 10) == 10);
    STATIC_REQUIRE(phi::clamp(11, 5, 10) == 10);
}
