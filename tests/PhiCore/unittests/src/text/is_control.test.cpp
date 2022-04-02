#include "phi/test/test_macros.hpp"

#include "phi/text/is_control.hpp"
#include <cctype>

void test_is_control(const char c) noexcept
{
    CHECK(phi::is_control(c));
    CHECK(std::iscntrl(c));
    CHECK_NOEXCEPT(phi::is_control(c));
}

void test_is_not_control(const char c) noexcept
{
    CHECK_FALSE(phi::is_control(c));
    CHECK_FALSE(std::iscntrl(c));
    CHECK_NOEXCEPT(phi::is_control(c));
}

TEST_CASE("is_control")
{
    for (char c{0}; c <= 31; ++c)
    {
        test_is_control(c);
    }

    for (char c{32}; c <= 126; ++c)
    {
        test_is_not_control(c);
    }

    test_is_control(127);
}
