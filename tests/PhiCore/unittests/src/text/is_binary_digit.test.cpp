#include "phi/test/test_macros.hpp"

#include "phi/text/is_binary_digit.hpp"
#include <cctype>

void test_is_binary_digit(const char character) noexcept
{
    CHECK(phi::is_binary_digit(character));
    CHECK(std::isdigit(character));
    CHECK_NOEXCEPT(phi::is_binary_digit(character));
}

void test_is_not_binary_digit(const char character) noexcept
{
    CHECK_FALSE(phi::is_binary_digit(character));
    CHECK_NOEXCEPT(phi::is_binary_digit(character));
}

TEST_CASE("is_binary_digit")
{
    for (char character{0}; character <= 47; ++character)
    {
        test_is_not_binary_digit(character);
    }

    for (char character{48}; character <= 49; ++character)
    {
        test_is_binary_digit(character);
    }

    for (char character{50}; character < 127; ++character)
    {
        test_is_not_binary_digit(character);
    }

    test_is_not_binary_digit(127);
}
