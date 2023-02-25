#include <phi/test/test_macros.hpp>

#include <phi/text/hex_digit_value.hpp>

TEST_CASE("hex_digit_value - constexpr")
{
    STATIC_REQUIRE(phi::hex_digit_value('0').unsafe() == 0u);
    STATIC_REQUIRE(phi::hex_digit_value('1').unsafe() == 1u);
    STATIC_REQUIRE(phi::hex_digit_value('2').unsafe() == 2u);
    STATIC_REQUIRE(phi::hex_digit_value('3').unsafe() == 3u);
    STATIC_REQUIRE(phi::hex_digit_value('4').unsafe() == 4u);
    STATIC_REQUIRE(phi::hex_digit_value('5').unsafe() == 5u);
    STATIC_REQUIRE(phi::hex_digit_value('6').unsafe() == 6u);
    STATIC_REQUIRE(phi::hex_digit_value('7').unsafe() == 7u);
    STATIC_REQUIRE(phi::hex_digit_value('8').unsafe() == 8u);
    STATIC_REQUIRE(phi::hex_digit_value('9').unsafe() == 9u);

    STATIC_REQUIRE(phi::hex_digit_value('a').unsafe() == 10u);
    STATIC_REQUIRE(phi::hex_digit_value('b').unsafe() == 11u);
    STATIC_REQUIRE(phi::hex_digit_value('c').unsafe() == 12u);
    STATIC_REQUIRE(phi::hex_digit_value('d').unsafe() == 13u);
    STATIC_REQUIRE(phi::hex_digit_value('e').unsafe() == 14u);
    STATIC_REQUIRE(phi::hex_digit_value('f').unsafe() == 15u);

    STATIC_REQUIRE(phi::hex_digit_value('A').unsafe() == 10u);
    STATIC_REQUIRE(phi::hex_digit_value('B').unsafe() == 11u);
    STATIC_REQUIRE(phi::hex_digit_value('C').unsafe() == 12u);
    STATIC_REQUIRE(phi::hex_digit_value('D').unsafe() == 13u);
    STATIC_REQUIRE(phi::hex_digit_value('E').unsafe() == 14u);
    STATIC_REQUIRE(phi::hex_digit_value('F').unsafe() == 15u);

    CHECK_NOEXCEPT(phi::hex_digit_value('0'));
}

TEST_CASE("hex_digit_value - runtime")
{
    CHECK(phi::hex_digit_value('0').unsafe() == 0u);
    CHECK(phi::hex_digit_value('1').unsafe() == 1u);
    CHECK(phi::hex_digit_value('2').unsafe() == 2u);
    CHECK(phi::hex_digit_value('3').unsafe() == 3u);
    CHECK(phi::hex_digit_value('4').unsafe() == 4u);
    CHECK(phi::hex_digit_value('5').unsafe() == 5u);
    CHECK(phi::hex_digit_value('6').unsafe() == 6u);
    CHECK(phi::hex_digit_value('7').unsafe() == 7u);
    CHECK(phi::hex_digit_value('8').unsafe() == 8u);
    CHECK(phi::hex_digit_value('9').unsafe() == 9u);

    CHECK(phi::hex_digit_value('a').unsafe() == 10u);
    CHECK(phi::hex_digit_value('b').unsafe() == 11u);
    CHECK(phi::hex_digit_value('c').unsafe() == 12u);
    CHECK(phi::hex_digit_value('d').unsafe() == 13u);
    CHECK(phi::hex_digit_value('e').unsafe() == 14u);
    CHECK(phi::hex_digit_value('f').unsafe() == 15u);

    CHECK(phi::hex_digit_value('A').unsafe() == 10u);
    CHECK(phi::hex_digit_value('B').unsafe() == 11u);
    CHECK(phi::hex_digit_value('C').unsafe() == 12u);
    CHECK(phi::hex_digit_value('D').unsafe() == 13u);
    CHECK(phi::hex_digit_value('E').unsafe() == 14u);
    CHECK(phi::hex_digit_value('F').unsafe() == 15u);
}
