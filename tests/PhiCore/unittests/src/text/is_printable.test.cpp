#include "phi/test/test_macros.hpp"

#include <phi/text/is_printable.hpp>
#include <cctype>

void test_is_printable(const char character)
{
    CHECK(phi::is_printable(character));
    CHECK(std::isprint(character));
    CHECK_NOEXCEPT(phi::is_printable(character));
}

void test_is_not_printable(const char character)
{
    CHECK_FALSE(phi::is_printable(character));
    CHECK_FALSE(std::isprint(character));
    CHECK_NOEXCEPT(phi::is_printable(character));
}

TEST_CASE("is_printable")
{
    for (char character{0}; character <= 31; ++character)
    {
        test_is_not_printable(character);
    }

    for (char character{32}; character <= 126; ++character)
    {
        test_is_printable(character);
    }

    test_is_not_printable(127);
}
