#include <catch2/catch_test_macros.hpp>

#include <Phi/Config/Unreachable.hpp>

int func()
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
