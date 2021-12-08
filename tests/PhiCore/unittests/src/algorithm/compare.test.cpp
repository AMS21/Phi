#include <phi/test/test_macros.hpp>

#include <phi/algorithm/compare.hpp>

TEST_CASE("compare")
{
    STATIC_REQUIRE(phi::compare(1, 1) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::compare(0, 1) == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::compare(2, 1) == phi::CompareResult::GreaterThan);

    STATIC_REQUIRE(phi::compare(3u, 3u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::compare(0u, 3u) == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::compare(4u, 3u) == phi::CompareResult::GreaterThan);

    STATIC_REQUIRE(phi::compare(1, 1u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::compare(0, 1u) == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::compare(2, 1u) == phi::CompareResult::GreaterThan);

    STATIC_REQUIRE(phi::compare('a', 'a') == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::compare('a', 'b') == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::compare('b', 'a') == phi::CompareResult::GreaterThan);
}
