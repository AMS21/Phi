#include <phi/test/test_macros.hpp>

#include <phi/algorithm/compare.hpp>

TEST_CASE("compare")
{
    STATIC_REQUIRE(phi::compare(1, 1) == phi::compare_result::Equal);
    STATIC_REQUIRE(phi::compare(0, 1) == phi::compare_result::LessThan);
    STATIC_REQUIRE(phi::compare(2, 1) == phi::compare_result::GreaterThan);

    STATIC_REQUIRE(phi::compare(3u, 3u) == phi::compare_result::Equal);
    STATIC_REQUIRE(phi::compare(0u, 3u) == phi::compare_result::LessThan);
    STATIC_REQUIRE(phi::compare(4u, 3u) == phi::compare_result::GreaterThan);

    STATIC_REQUIRE(phi::compare(1, 1u) == phi::compare_result::Equal);
    STATIC_REQUIRE(phi::compare(0, 1u) == phi::compare_result::LessThan);
    STATIC_REQUIRE(phi::compare(2, 1u) == phi::compare_result::GreaterThan);

    STATIC_REQUIRE(phi::compare('a', 'a') == phi::compare_result::Equal);
    STATIC_REQUIRE(phi::compare('a', 'b') == phi::compare_result::LessThan);
    STATIC_REQUIRE(phi::compare('b', 'a') == phi::compare_result::GreaterThan);
}
