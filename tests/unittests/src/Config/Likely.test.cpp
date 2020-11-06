#include <catch2/catch_test_macros.hpp>

#include <Phi/Config/Likely.hpp>

TEST_CASE("Likely", "[Config][Likely]")
{
    int i = 5;

    if (PHI_LIKELY(i % 2 == 1))
    {
        CHECK(true);
    }

    if (PHI_UNLIKELY(i % 2 == 1))
    {
        CHECK(true);
    }

    for (int j = 0; j < 10; ++j)
    {
        switch (j)
        {
            PHI_UNLIKELY_CASE case 3:
            {
                break;
            }
            PHI_LIKELY_CASE case 5:
            {
                CHECK(true);
                break;
            }
            default:
                break;
        }
    }
}
