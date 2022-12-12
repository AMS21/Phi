#include "phi/test/test_macros.hpp"

#include <phi/text/is_punctuation.hpp>
#include <cctype>

void test_is_punctuation(const char character) noexcept
{
    CHECK(phi::is_punctuation(character));
    CHECK(std::ispunct(character));
    CHECK_NOEXCEPT(phi::is_punctuation(character));
}

void test_is_not_punctuation(const char character) noexcept
{
    CHECK_FALSE(phi::is_punctuation(character));
    CHECK_FALSE(std::ispunct(character));
    CHECK_NOEXCEPT(phi::is_punctuation(character));
}

TEST_CASE("is_punctuation")
{
    for (char character{0}; character <= 32; ++character)
    {
        test_is_not_punctuation(character);
    }

    for (char character{33}; character <= 47; ++character)
    {
        test_is_punctuation(character);
    }

    for (char character{48}; character <= 57; ++character)
    {
        test_is_not_punctuation(character);
    }

    for (char character{58}; character <= 64; ++character)
    {
        test_is_punctuation(character);
    }

    for (char character{65}; character <= 90; ++character)
    {
        test_is_not_punctuation(character);
    }

    for (char character{91}; character <= 96; ++character)
    {
        test_is_punctuation(character);
    }

    for (char character{97}; character <= 122; ++character)
    {
        test_is_not_punctuation(character);
    }

    for (char character{123}; character <= 126; ++character)
    {
        test_is_punctuation(character);
    }

    test_is_not_punctuation(127);
}
