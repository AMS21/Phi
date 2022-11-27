#include "phi/test/test_macros.hpp"

#include <phi/text/to_lower_case.hpp>

PHI_EXTERNAL_HEADERS_BEGIN()
#include <cctype>
PHI_EXTERNAL_HEADERS_END()

void test_to_lower_case(char original, char expected)
{
    CHECK(phi::to_lower_case(original) == expected);
    CHECK(std::tolower(original) == expected);
    CHECK_NOEXCEPT(phi::to_lower_case(original));
}

TEST_CASE("to_lower_case")
{
    for (char character{0}; character <= 64; ++character)
    {
        test_to_lower_case(character, character);
    }

    for (char character{65}; character <= 90; ++character)
    {
        test_to_lower_case(character, static_cast<char>(character + 32));
    }

    for (char character{91}; character <= 126; ++character)
    {
        test_to_lower_case(character, character);
    }

    test_to_lower_case(127, 127);
}
