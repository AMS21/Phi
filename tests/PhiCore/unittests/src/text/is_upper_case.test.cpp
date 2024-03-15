#include "phi/test/test_macros.hpp"

#include <phi/text/is_upper_case.hpp>
#include <cctype>

void test_is_upper_case(const char character)
{
    CHECK(phi::is_upper_case(character));
    CHECK(std::isupper(character));
    CHECK_NOEXCEPT(phi::is_upper_case(character));
}

void test_is_not_upper_case(const char character)
{
    CHECK_FALSE(phi::is_upper_case(character));
    CHECK_FALSE(std::isupper(character));
    CHECK_NOEXCEPT(phi::is_upper_case(character));
}

TEST_CASE("is_upper_case")
{
    for (char character{0}; character <= 64; ++character)
    {
        test_is_not_upper_case(character);
    }

    for (char character{65}; character <= 90; ++character)
    {
        test_is_upper_case(character);
    }

    for (char character{91}; character <= 126; ++character)
    {
        test_is_not_upper_case(character);
    }

    test_is_not_upper_case(127);
}
