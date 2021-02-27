#include <catch2/catch_test_macros.hpp>

#include <Phi/Config/Unreachable.hpp>

// file deepcode ignore CppDeadCode: It's the hole purpose of the unreachable macro

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
