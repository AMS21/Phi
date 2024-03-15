#include "phi/test/test_macros.hpp"

#include <phi/text/is_ascii.hpp>

void test_is_ascii(const char character)
{
    CHECK(phi::is_ascii(character));
    CHECK_NOEXCEPT(phi::is_ascii(character));
}

void test_is_not_ascii(const char character)
{
    CHECK_FALSE(phi::is_ascii(character));
    CHECK_NOEXCEPT(phi::is_ascii(character));
}

TEST_CASE("is_ascii")
{
    for (char character{0}; character <= 126; ++character)
    {
        test_is_ascii(character);
    }

    test_is_ascii(127);

    test_is_not_ascii(-1);
}
