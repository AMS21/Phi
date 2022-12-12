#include "phi/test/test_macros.hpp"

#include <phi/text/is_octal_digit.hpp>
#include <cctype>

void test_is_octal_digit(const char character) noexcept
{
    CHECK(phi::is_octal_digit(character));
    CHECK(std::isdigit(character));
    CHECK_NOEXCEPT(phi::is_octal_digit(character));
}

void test_is_not_octal_digit(const char character) noexcept
{
    CHECK_FALSE(phi::is_octal_digit(character));
    CHECK_NOEXCEPT(phi::is_octal_digit(character));
}

TEST_CASE("is_octal_digit")
{
    for (char character{0}; character <= 47; ++character)
    {
        test_is_not_octal_digit(character);
    }

    for (char character{48}; character <= 55; ++character)
    {
        test_is_octal_digit(character);
    }

    for (char character{56}; character <= 126; ++character)
    {
        test_is_not_octal_digit(character);
    }

    test_is_not_octal_digit(127);
}
