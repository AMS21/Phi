#include <Phi/Test/TestMacros.hpp>

TEST_CASE("REQUIRE")
{
    REQUIRE(true);

    // Automatically converted to boolean
    REQUIRE(1);
}
