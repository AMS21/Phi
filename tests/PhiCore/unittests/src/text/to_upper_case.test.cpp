#include "phi/test/test_macros.hpp"

#include "phi/text/to_upper_case.hpp"
#include <cctype>

void test_to_upper_case(char original, char expected)
{
    CHECK(phi::to_upper_case(original) == expected);
    CHECK(std::toupper(original) == expected);
    CHECK_NOEXCEPT(phi::to_upper_case(original));
}

TEST_CASE("to_upper_case")
{
    for (char c{0}; c <= 96; ++c)
    {
        test_to_upper_case(c, c);
    }

    for (char c{97}; c <= 122; ++c)
    {
        test_to_upper_case(c, static_cast<char>(c - 32));
    }

    for (char c{123}; c <= 126; ++c)
    {
        test_to_upper_case(c, c);
    }

    test_to_upper_case(127, 127);
}
