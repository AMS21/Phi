#include "phi/test/test_macros.hpp"

#include <phi/text/is_graphical_character.hpp>
#include <cctype>

void test_is_graphical_character(const char character) noexcept
{
    CHECK(phi::is_graphical_character(character));
    CHECK(std::isgraph(character));
    CHECK_NOEXCEPT(phi::is_graphical_character(character));
}

void test_is_not_graphical_character(const char character) noexcept
{
    CHECK_FALSE(phi::is_graphical_character(character));
    CHECK_FALSE(std::isgraph(character));
    CHECK_NOEXCEPT(phi::is_graphical_character(character));
}

TEST_CASE("is_graphical_character")
{
    for (char character{0}; character <= 32; ++character)
    {
        test_is_not_graphical_character(character);
    }

    for (char character{33}; character <= 126; ++character)
    {
        test_is_graphical_character(character);
    }

    test_is_not_graphical_character(127);
}
