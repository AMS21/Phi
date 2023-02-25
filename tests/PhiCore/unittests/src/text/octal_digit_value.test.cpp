#include <phi/test/test_macros.hpp>

#include <phi/text/octal_digit_value.hpp>

TEST_CASE("octal_digit_value - constexpr")
{
    STATIC_REQUIRE(phi::octal_digit_value('0').unsafe() == 0u);
    STATIC_REQUIRE(phi::octal_digit_value('1').unsafe() == 1u);
    STATIC_REQUIRE(phi::octal_digit_value('2').unsafe() == 2u);
    STATIC_REQUIRE(phi::octal_digit_value('3').unsafe() == 3u);
    STATIC_REQUIRE(phi::octal_digit_value('4').unsafe() == 4u);
    STATIC_REQUIRE(phi::octal_digit_value('5').unsafe() == 5u);
    STATIC_REQUIRE(phi::octal_digit_value('6').unsafe() == 6u);
    STATIC_REQUIRE(phi::octal_digit_value('7').unsafe() == 7u);

    CHECK_NOEXCEPT(phi::octal_digit_value('0'));
}

TEST_CASE("octal_digit_value - runtime")
{
    CHECK(phi::octal_digit_value('0').unsafe() == 0u);
    CHECK(phi::octal_digit_value('1').unsafe() == 1u);
    CHECK(phi::octal_digit_value('2').unsafe() == 2u);
    CHECK(phi::octal_digit_value('3').unsafe() == 3u);
    CHECK(phi::octal_digit_value('4').unsafe() == 4u);
    CHECK(phi::octal_digit_value('5').unsafe() == 5u);
    CHECK(phi::octal_digit_value('6').unsafe() == 6u);
    CHECK(phi::octal_digit_value('7').unsafe() == 7u);
}
