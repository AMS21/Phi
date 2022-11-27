#include "phi/test/test_macros.hpp"

#include <phi/text/is_alpha_numeric.hpp>

PHI_EXTERNAL_HEADERS_BEGIN()
#include <cctype>
PHI_EXTERNAL_HEADERS_END()

// TODO: Test with constexpr

void test_is_alpha_numeric(const char character) noexcept
{
    CHECK(phi::is_alpha_numeric(character));
    CHECK(std::isalnum(character));
    CHECK_NOEXCEPT(phi::is_alpha_numeric(character));
}

void test_is_not_alpha_numeric(const char character) noexcept
{
    CHECK_FALSE(phi::is_alpha_numeric(character));
    CHECK_FALSE(std::isalnum(character));
    CHECK_NOEXCEPT(phi::is_alpha_numeric(character));
}

TEST_CASE("is_alpha_numeric")
{
    for (char character{0}; character <= 47; ++character)
    {
        test_is_not_alpha_numeric(character);
    }

    for (char character{48}; character <= 57; ++character)
    {
        test_is_alpha_numeric(character);
    }

    for (char character{58}; character <= 64; ++character)
    {
        test_is_not_alpha_numeric(character);
    }

    for (char character{65}; character <= 90; ++character)
    {
        test_is_alpha_numeric(character);
    }

    for (char character{91}; character <= 96; ++character)
    {
        test_is_not_alpha_numeric(character);
    }

    for (char character{97}; character <= 122; ++character)
    {
        test_is_alpha_numeric(character);
    }

    for (char character{123}; character <= 126; ++character)
    {
        test_is_not_alpha_numeric(character);
    }

    test_is_not_alpha_numeric(127);
}
