#include "phi/test/test_macros.hpp"

#include "phi/text/is_blank.hpp"
#include <cctype>

void test_is_blank(const char c) noexcept
{
    CHECK(phi::is_blank(c));
    CHECK(std::isblank(c));
    CHECK_NOEXCEPT(phi::is_blank(c));
}

void test_is_not_blank(const char c) noexcept
{
    CHECK_FALSE(phi::is_blank(c));
    CHECK_FALSE(std::isblank(c));
    CHECK_NOEXCEPT(phi::is_blank(c));
}

TEST_CASE("is_blank")
{
    for (char c{0}; c <= 8; ++c)
    {
        test_is_not_blank(c);
    }

    test_is_blank('\t');

    for (char c{10}; c <= 31; ++c)
    {
        test_is_not_blank(c);
    }

    test_is_blank(' ');

    for (char c{33}; c <= 126; ++c)
    {
        test_is_not_blank(c);
    }

    test_is_not_blank(127);
}
