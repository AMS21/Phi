#include <catch2/catch.hpp>

#include <Phi/Config/Unreachable.hpp>

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
