#include <Phi/Test/TestMacros.hpp>

#include <Phi/CompilerSupport/Likely.hpp>

TEST_CASE("Likely", "[Likely]")
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
                CHECK(j == 3);
                break;
            }
            PHI_LIKELY_CASE case 5:
            {
                CHECK(j == 5);
                break;
            }
            default: {
                CHECK(j < 10);
                break;
            }
        }
    }
}
