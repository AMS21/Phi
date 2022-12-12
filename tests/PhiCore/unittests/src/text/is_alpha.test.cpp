#include "phi/test/test_macros.hpp"

#include <phi/text/is_alpha.hpp>
#include <cctype>

void test_is_alpha(const char character) noexcept
{
    CHECK(phi::is_alpha(character));
    CHECK(std::isalpha(character));
    CHECK_NOEXCEPT(phi::is_alpha(character));
}

void test_is_not_alpha(const char character) noexcept
{
    CHECK_FALSE(phi::is_alpha(character));
    CHECK_FALSE(std::isalpha(character));
    CHECK_NOEXCEPT(phi::is_alpha(character));
}

TEST_CASE("is_alpha")
{
    for (char character{0}; character <= 64; ++character)
    {
        test_is_not_alpha(character);
    }

    for (char character{65}; character <= 90; ++character)
    {
        test_is_alpha(character);
    }

    for (char character{91}; character <= 96; ++character)
    {
        test_is_not_alpha(character);
    }

    for (char character{97}; character <= 122; ++character)
    {
        test_is_alpha(character);
    }

    for (char character{123}; character <= 126; ++character)
    {
        test_is_not_alpha(character);
    }

    test_is_not_alpha(127);
}
