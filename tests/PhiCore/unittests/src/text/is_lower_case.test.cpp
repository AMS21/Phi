#include "phi/test/test_macros.hpp"

#include "phi/text/is_lower_case.hpp"
#include <cctype>

void test_is_lower_case(const char c) noexcept
{
    CHECK(phi::is_lower_case(c));
    CHECK(std::islower(c));
}

void test_is_not_lower_case(const char c) noexcept
{
    CHECK_FALSE(phi::is_lower_case(c));
    CHECK_FALSE(std::islower(c));
}

TEST_CASE("is_lower_case")
{
    for (char c{0}; c <= 96; ++c)
    {
        test_is_not_lower_case(c);
    }

    for (char c{97}; c <= 122; ++c)
    {
        test_is_lower_case(c);
    }

    for (char c{123}; c < 127; ++c)
    {
        test_is_not_lower_case(c);
    }

    test_is_not_lower_case(127);
}
