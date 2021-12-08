#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/unreachable.hpp>

static int func()
{
    return 12;

    PHI_UNREACHABLE();
}

TEST_CASE("unreachable", "[Config][Unreachable]")
{
    CHECK(func() == 12);

    if (func() == 12)
    {
        CHECK(true);
    }
    else
    {
        PHI_UNREACHABLE();
    }
}
