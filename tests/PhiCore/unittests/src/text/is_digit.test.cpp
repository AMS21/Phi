#include "phi/test/test_macros.hpp"

#include "phi/text/is_digit.hpp"
#include <cctype>

void test_is_digit(const char c) noexcept
{
    CHECK(phi::is_digit(c));
    CHECK(std::isdigit(c));
    CHECK_NOEXCEPT(phi::is_digit(c));
}

void test_is_not_digit(const char c) noexcept
{
    CHECK_FALSE(phi::is_digit(c));
    CHECK_FALSE(std::isdigit(c));
    CHECK_NOEXCEPT(phi::is_digit(c));
}

TEST_CASE("is_digit")
{
    for (char c{0}; c <= 47; ++c)
    {
        test_is_not_digit(c);
    }

    for (char c{48}; c <= 57; ++c)
    {
        test_is_digit(c);
    }

    for (char c{58}; c <= 126; ++c)
    {
        test_is_not_digit(c);
    }

    test_is_not_digit(127);
}
