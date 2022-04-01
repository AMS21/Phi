#include "phi/test/test_macros.hpp"

#include "phi/text/is_space.hpp"
#include <cctype>

void test_is_space(const char c) noexcept
{
    CHECK(phi::is_space(c));
    CHECK(std::isspace(c));
}

void test_is_not_space(const char c) noexcept
{
    CHECK_FALSE(phi::is_space(c));
    CHECK_FALSE(std::isspace(c));
}

TEST_CASE("is_space")
{
    for (char c{0}; c <= 8; ++c)
    {
        test_is_not_space(c);
    }

    for (char c{9}; c <= 13; ++c)
    {
        test_is_space(c);
    }

    for (char c{14}; c <= 31; ++c)
    {
        test_is_not_space(c);
    }

    test_is_space(32);

    for (char c{33}; c <= 126; ++c)
    {
        test_is_not_space(c);
    }

    test_is_not_space(127);
}
