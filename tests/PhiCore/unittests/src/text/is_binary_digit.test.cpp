#include "phi/test/test_macros.hpp"

#include "phi/text/is_binary_digit.hpp"
#include <cctype>

void test_is_binary_digit(const char c) noexcept
{
    CHECK(phi::is_binary_digit(c));
    CHECK(std::isdigit(c));
}

void test_is_not_binary_digit(const char c) noexcept
{
    CHECK_FALSE(phi::is_binary_digit(c));
}

TEST_CASE("is_binary_digit")
{
    for (char c{0}; c <= 47; ++c)
    {
        test_is_not_binary_digit(c);
    }

    for (char c{48}; c <= 49; ++c)
    {
        test_is_binary_digit(c);
    }

    for (char c{50}; c < 127; ++c)
    {
        test_is_not_binary_digit(c);
    }

    test_is_not_binary_digit(127);
}
