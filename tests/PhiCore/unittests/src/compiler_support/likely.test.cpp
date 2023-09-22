#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/likely.hpp>

TEST_CASE("Likely", "[Likely]")
{
    int integer = 5;

    if (PHI_LIKELY(integer % 2 == 1))
    {
        CHECK(true);
    }

    if (PHI_UNLIKELY(integer % 2 == 1))
    {
        CHECK(true);
    }

    for (int index = 0; index < 10; ++index)
    {
        switch (index)
        {
        PHI_UNLIKELY_CASE case 3: {
            CHECK(index == 3);
            break;
        }
        PHI_LIKELY_CASE case 5: {
            CHECK(index == 5);
            break;
        }
        default: {
            CHECK(index < 10);
            break;
        }
        }
    }
}
