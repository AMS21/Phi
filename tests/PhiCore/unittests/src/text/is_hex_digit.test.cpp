#include "phi/test/test_macros.hpp"

#include "phi/text/is_hex_digit.hpp"
#include <cctype>

void test_is_hex_digit(const char c) noexcept
{
    CHECK(phi::is_hex_digit(c));
    CHECK(std::isxdigit(c));
}

void test_is_not_hex_digit(const char c) noexcept
{
    CHECK_FALSE(phi::is_hex_digit(c));
    CHECK_FALSE(std::isxdigit(c));
}

TEST_CASE("is_hex_digit")
{
    for (char c{0}; c <= 47; ++c)
    {
        test_is_not_hex_digit(c);
    }

    for (char c{48}; c <= 57; ++c)
    {
        test_is_hex_digit(c);
    }

    for (char c{58}; c <= 64; ++c)
    {
        test_is_not_hex_digit(c);
    }

    for (char c{65}; c <= 70; ++c)
    {
        test_is_hex_digit(c);
    }

    for (char c{71}; c <= 96; ++c)
    {
        test_is_not_hex_digit(c);
    }

    for (char c{97}; c <= 102; ++c)
    {
        test_is_hex_digit(c);
    }

    for (char c{103}; c <= 126; ++c)
    {
        test_is_not_hex_digit(c);
    }

    test_is_not_hex_digit(127);
}
