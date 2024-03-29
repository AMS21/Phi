#include "phi/test/test_macros.hpp"

#include <phi/text/is_control.hpp>
#include <cctype>

void test_is_control(const char character)
{
    CHECK(phi::is_control(character));
    CHECK(std::iscntrl(character));
    CHECK_NOEXCEPT(phi::is_control(character));
}

void test_is_not_control(const char character)
{
    CHECK_FALSE(phi::is_control(character));
    CHECK_FALSE(std::iscntrl(character));
    CHECK_NOEXCEPT(phi::is_control(character));
}

TEST_CASE("is_control")
{
    for (char character{0}; character <= 31; ++character)
    {
        test_is_control(character);
    }

    for (char character{32}; character <= 126; ++character)
    {
        test_is_not_control(character);
    }

    test_is_control(127);
}
