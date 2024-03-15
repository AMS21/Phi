#include "phi/test/test_macros.hpp"

#include <phi/text/is_digit.hpp>
#include <cctype>

void test_is_digit(const char character)
{
    CHECK(phi::is_digit(character));
    CHECK(std::isdigit(character));
    CHECK_NOEXCEPT(phi::is_digit(character));
}

void test_is_not_digit(const char character)
{
    CHECK_FALSE(phi::is_digit(character));
    CHECK_FALSE(std::isdigit(character));
    CHECK_NOEXCEPT(phi::is_digit(character));
}

TEST_CASE("is_digit")
{
    for (char character{0}; character <= 47; ++character)
    {
        test_is_not_digit(character);
    }

    for (char character{48}; character <= 57; ++character)
    {
        test_is_digit(character);
    }

    for (char character{58}; character <= 126; ++character)
    {
        test_is_not_digit(character);
    }

    test_is_not_digit(127);
}
