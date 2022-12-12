#include "phi/test/test_macros.hpp"

#include <phi/text/is_blank.hpp>
#include <cctype>

void test_is_blank(const char character) noexcept
{
    CHECK(phi::is_blank(character));
    CHECK(std::isblank(character));
    CHECK_NOEXCEPT(phi::is_blank(character));
}

void test_is_not_blank(const char character) noexcept
{
    CHECK_FALSE(phi::is_blank(character));
    CHECK_FALSE(std::isblank(character));
    CHECK_NOEXCEPT(phi::is_blank(character));
}

TEST_CASE("is_blank")
{
    for (char character{0}; character <= 8; ++character)
    {
        test_is_not_blank(character);
    }

    test_is_blank('\t');

    for (char character{10}; character <= 31; ++character)
    {
        test_is_not_blank(character);
    }

    test_is_blank(' ');

    for (char character{33}; character <= 126; ++character)
    {
        test_is_not_blank(character);
    }

    test_is_not_blank(127);
}
