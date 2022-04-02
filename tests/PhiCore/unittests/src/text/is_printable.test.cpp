#include "phi/test/test_macros.hpp"

#include "phi/text/is_printable.hpp"
#include <cctype>

void test_is_printable(const char c) noexcept
{
    CHECK(phi::is_printable(c));
    CHECK(std::isprint(c));
    CHECK_NOEXCEPT(phi::is_printable(c));
}

void test_is_not_printable(const char c) noexcept
{
    CHECK_FALSE(phi::is_printable(c));
    CHECK_FALSE(std::isprint(c));
    CHECK_NOEXCEPT(phi::is_printable(c));
}

TEST_CASE("is_printable")
{
    for (char c{0}; c <= 31; ++c)
    {
        test_is_not_printable(c);
    }

    for (char c{32}; c <= 126; ++c)
    {
        test_is_printable(c);
    }

    test_is_not_printable(127);
}
