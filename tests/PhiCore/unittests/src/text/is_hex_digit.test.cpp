#include "phi/test/test_macros.hpp"

#include <phi/text/is_hex_digit.hpp>

PHI_EXTERNAL_HEADERS_BEGIN()
#include <cctype>
PHI_EXTERNAL_HEADERS_END()

void test_is_hex_digit(const char character) noexcept
{
    CHECK(phi::is_hex_digit(character));
    CHECK(std::isxdigit(character));
    CHECK_NOEXCEPT(phi::is_hex_digit(character));
}

void test_is_not_hex_digit(const char character) noexcept
{
    CHECK_FALSE(phi::is_hex_digit(character));
    CHECK_FALSE(std::isxdigit(character));
    CHECK_NOEXCEPT(phi::is_hex_digit(character));
}

TEST_CASE("is_hex_digit")
{
    for (char character{0}; character <= 47; ++character)
    {
        test_is_not_hex_digit(character);
    }

    for (char character{48}; character <= 57; ++character)
    {
        test_is_hex_digit(character);
    }

    for (char character{58}; character <= 64; ++character)
    {
        test_is_not_hex_digit(character);
    }

    for (char character{65}; character <= 70; ++character)
    {
        test_is_hex_digit(character);
    }

    for (char character{71}; character <= 96; ++character)
    {
        test_is_not_hex_digit(character);
    }

    for (char character{97}; character <= 102; ++character)
    {
        test_is_hex_digit(character);
    }

    for (char character{103}; character <= 126; ++character)
    {
        test_is_not_hex_digit(character);
    }

    test_is_not_hex_digit(127);
}
