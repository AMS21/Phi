#include "phi/test/test_macros.hpp"

#include "phi/text/is_ascii.hpp"

void test_is_ascii(const char c) noexcept
{
    CHECK(phi::is_ascii(c));
}

void test_is_not_ascii(const char c) noexcept
{
    CHECK_FALSE(phi::is_ascii(c));
}

TEST_CASE("is_ascii")
{
    for (char c{0}; c <= 126; ++c)
    {
        test_is_ascii(c);
    }

    test_is_ascii(127);
}
