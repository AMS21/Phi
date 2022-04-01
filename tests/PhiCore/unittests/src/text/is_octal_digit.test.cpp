#include "phi/test/test_macros.hpp"

#include "phi/text/is_octal_digit.hpp"
#include <cctype>

void test_is_octal_digit(const char c) noexcept
{
    CHECK(phi::is_octal_digit(c));
    CHECK(std::isdigit(c));
}

void test_is_not_octal_digit(const char c) noexcept
{
    CHECK_FALSE(phi::is_octal_digit(c));
}

TEST_CASE("is_octal_digit")
{
    for (char c{0}; c <= 47; ++c)
    {
        test_is_not_octal_digit(c);
    }

    for (char c{48}; c <= 55; ++c)
    {
        test_is_octal_digit(c);
    }

    for (char c{56}; c < 127; ++c)
    {
        test_is_not_octal_digit(c);
    }

    test_is_not_octal_digit(127);
}
