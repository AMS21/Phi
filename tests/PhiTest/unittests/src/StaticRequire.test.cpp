#include <Phi/Test/TestMacros.hpp>

TEST_CASE("STATIC_REQUIRE")
{
    STATIC_REQUIRE(true);
    STATIC_REQUIRE(1);
}
