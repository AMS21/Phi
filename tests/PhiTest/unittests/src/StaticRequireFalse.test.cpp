#include <Phi/Test/TestMacros.hpp>

TEST_CASE("STATIC_REQUIRE_FALSE")
{
    STATIC_REQUIRE_FALSE(false);
    STATIC_REQUIRE_FALSE(0);
}
