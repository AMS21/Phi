#include <phi/test/test_macros.hpp>

#include <phi/text/digit_value.hpp>

TEST_CASE("digit_value - constexpr")
{
    STATIC_REQUIRE(phi::digit_value('0').unsafe() == 0u);
    STATIC_REQUIRE(phi::digit_value('1').unsafe() == 1u);
    STATIC_REQUIRE(phi::digit_value('2').unsafe() == 2u);
    STATIC_REQUIRE(phi::digit_value('3').unsafe() == 3u);
    STATIC_REQUIRE(phi::digit_value('4').unsafe() == 4u);
    STATIC_REQUIRE(phi::digit_value('5').unsafe() == 5u);
    STATIC_REQUIRE(phi::digit_value('6').unsafe() == 6u);
    STATIC_REQUIRE(phi::digit_value('7').unsafe() == 7u);
    STATIC_REQUIRE(phi::digit_value('8').unsafe() == 8u);
    STATIC_REQUIRE(phi::digit_value('9').unsafe() == 9u);

    CHECK_NOEXCEPT(phi::digit_value('0'));
}

TEST_CASE("digit_value - runtime")
{
    CHECK(phi::digit_value('0').unsafe() == 0u);
    CHECK(phi::digit_value('1').unsafe() == 1u);
    CHECK(phi::digit_value('2').unsafe() == 2u);
    CHECK(phi::digit_value('3').unsafe() == 3u);
    CHECK(phi::digit_value('4').unsafe() == 4u);
    CHECK(phi::digit_value('5').unsafe() == 5u);
    CHECK(phi::digit_value('6').unsafe() == 6u);
    CHECK(phi::digit_value('7').unsafe() == 7u);
    CHECK(phi::digit_value('8').unsafe() == 8u);
    CHECK(phi::digit_value('9').unsafe() == 9u);
}
