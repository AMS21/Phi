#include "phi/test/test_macros.hpp"

#include "phi/text/is_graphical_character.hpp"
#include <cctype>

void test_is_graphical_character(const char c) noexcept
{
    CHECK(phi::is_graphical_character(c));
    CHECK(std::isgraph(c));
    CHECK_NOEXCEPT(phi::is_graphical_character(c));
}

void test_is_not_graphical_character(const char c) noexcept
{
    CHECK_FALSE(phi::is_graphical_character(c));
    CHECK_FALSE(std::isgraph(c));
    CHECK_NOEXCEPT(phi::is_graphical_character(c));
}

TEST_CASE("is_graphical_character")
{
    for (char c{0}; c <= 32; ++c)
    {
        test_is_not_graphical_character(c);
    }

    for (char c{33}; c <= 126; ++c)
    {
        test_is_graphical_character(c);
    }

    test_is_not_graphical_character(127);
}
