#include "phi/test/test_macros.hpp"

#include "phi/text/is_upper_case.hpp"
#include <cctype>

void test_is_upper_case(const char c) noexcept
{
    CHECK(phi::is_upper_case(c));
    CHECK(std::isupper(c));
    CHECK_NOEXCEPT(phi::is_upper_case(c));
}

void test_is_not_upper_case(const char c) noexcept
{
    CHECK_FALSE(phi::is_upper_case(c));
    CHECK_FALSE(std::isupper(c));
    CHECK_NOEXCEPT(phi::is_upper_case(c));
}

TEST_CASE("is_upper_case")
{
    for (char c{0}; c <= 64; ++c)
    {
        test_is_not_upper_case(c);
    }

    for (char c{65}; c <= 90; ++c)
    {
        test_is_upper_case(c);
    }

    for (char c{91}; c <= 126; ++c)
    {
        test_is_not_upper_case(c);
    }

    test_is_not_upper_case(127);
}
