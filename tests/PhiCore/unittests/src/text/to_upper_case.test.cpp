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
    for (char character{0}; character <= 96; ++character)
    {
        test_to_upper_case(character, character);
    }

    for (char character{97}; character <= 122; ++character)
    {
        test_to_upper_case(character, static_cast<char>(character - 32));
    }

    for (char character{123}; character <= 126; ++character)
    {
        test_to_upper_case(character, character);
    }

    test_to_upper_case(127, 127);
}
