#include "phi/test/test_macros.hpp"

#include "phi/text/is_space.hpp"
#include <cctype>

void test_is_space(const char character) noexcept
{
    CHECK(phi::is_space(character));
    CHECK(std::isspace(character));
    CHECK_NOEXCEPT(phi::is_space(character));
}

void test_is_not_space(const char character) noexcept
{
    CHECK_FALSE(phi::is_space(character));
    CHECK_FALSE(std::isspace(character));
    CHECK_NOEXCEPT(phi::is_space(character));
}

TEST_CASE("is_space")
{
    for (char character{0}; character <= 8; ++character)
    {
        test_is_not_space(character);
    }

    for (char character{9}; character <= 13; ++character)
    {
        test_is_space(character);
    }

    for (char character{14}; character <= 31; ++character)
    {
        test_is_not_space(character);
    }

    test_is_space(32);

    for (char character{33}; character <= 126; ++character)
    {
        test_is_not_space(character);
    }

    test_is_not_space(127);
}
