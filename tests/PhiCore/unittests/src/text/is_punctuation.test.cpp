#include "phi/test/test_macros.hpp"

#include "phi/text/is_punctuation.hpp"
#include <cctype>

void test_is_punctuation(const char c) noexcept
{
    CHECK(phi::is_punctuation(c));
    CHECK(std::ispunct(c));
    CHECK_NOEXCEPT(phi::is_punctuation(c));
}

void test_is_not_punctuation(const char c) noexcept
{
    CHECK_FALSE(phi::is_punctuation(c));
    CHECK_FALSE(std::ispunct(c));
    CHECK_NOEXCEPT(phi::is_punctuation(c));
}

TEST_CASE("is_punctuation")
{
    for (char c{0}; c <= 32; ++c)
    {
        test_is_not_punctuation(c);
    }

    for (char c{33}; c <= 47; ++c)
    {
        test_is_punctuation(c);
    }

    for (char c{48}; c <= 57; ++c)
    {
        test_is_not_punctuation(c);
    }

    for (char c{58}; c <= 64; ++c)
    {
        test_is_punctuation(c);
    }

    for (char c{65}; c <= 90; ++c)
    {
        test_is_not_punctuation(c);
    }

    for (char c{91}; c <= 96; ++c)
    {
        test_is_punctuation(c);
    }

    for (char c{97}; c <= 122; ++c)
    {
        test_is_not_punctuation(c);
    }

    for (char c{123}; c <= 126; ++c)
    {
        test_is_punctuation(c);
    }

    test_is_not_punctuation(127);
}
