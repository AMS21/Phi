#include "phi/test/test_macros.hpp"

#include "phi/text/is_alpha.hpp"
#include <cctype>

void test_is_alpha(const char c) noexcept
{
    CHECK(phi::is_alpha(c));
    CHECK(std::isalpha(c));
    CHECK_NOEXCEPT(phi::is_alpha(c));
}

void test_is_not_alpha(const char c) noexcept
{
    CHECK_FALSE(phi::is_alpha(c));
    CHECK_FALSE(std::isalpha(c));
    CHECK_NOEXCEPT(phi::is_alpha(c));
}

TEST_CASE("is_alpha")
{
    for (char c{0}; c <= 64; ++c)
    {
        test_is_not_alpha(c);
    }

    for (char c{65}; c <= 90; ++c)
    {
        test_is_alpha(c);
    }

    for (char c{91}; c <= 96; ++c)
    {
        test_is_not_alpha(c);
    }

    for (char c{97}; c <= 122; ++c)
    {
        test_is_alpha(c);
    }

    for (char c{123}; c <= 126; ++c)
    {
        test_is_not_alpha(c);
    }

    test_is_not_alpha(127);
}
