#include "phi/test/test_macros.hpp"

#include "phi/text/to_lower_case.hpp"
#include <cctype>

void test_to_lower_case(char original, char expected)
{
    CHECK(phi::to_lower_case(original) == expected);
    CHECK(std::tolower(original) == expected);
}

TEST_CASE("to_lower_case")
{
    for (char c{0}; c <= 64; ++c)
    {
        test_to_lower_case(c, c);
    }

    for (char c{65}; c <= 90; ++c)
    {
        test_to_lower_case(c, c + 32);
    }

    for (char c{91}; c <= 126; ++c)
    {
        test_to_lower_case(c, c);
    }

    test_to_lower_case(127, 127);
}
