#include "phi/test/test_macros.hpp"

#include "phi/text/is_alpha_numeric.hpp"
#include <cctype>

void test_is_alpha_numeric(const char c) noexcept
{
    CHECK(phi::is_alpha_numeric(c));
    CHECK(std::isalnum(c));
    CHECK_NOEXCEPT(phi::is_alpha_numeric(c));
}

void test_is_not_alpha_numeric(const char c) noexcept
{
    CHECK_FALSE(phi::is_alpha_numeric(c));
    CHECK_FALSE(std::isalnum(c));
    CHECK_NOEXCEPT(phi::is_alpha_numeric(c));
}

TEST_CASE("is_alpha_numeric")
{
    for (char c{0}; c <= 47; ++c)
    {
        test_is_not_alpha_numeric(c);
    }

    for (char c{48}; c <= 57; ++c)
    {
        test_is_alpha_numeric(c);
    }

    for (char c{58}; c <= 64; ++c)
    {
        test_is_not_alpha_numeric(c);
    }

    for (char c{65}; c <= 90; ++c)
    {
        test_is_alpha_numeric(c);
    }

    for (char c{91}; c <= 96; ++c)
    {
        test_is_not_alpha_numeric(c);
    }

    for (char c{97}; c <= 122; ++c)
    {
        test_is_alpha_numeric(c);
    }

    for (char c{123}; c <= 126; ++c)
    {
        test_is_not_alpha_numeric(c);
    }

    test_is_not_alpha_numeric(127);
}
