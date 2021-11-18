#include <Phi/Test/TestMacros.hpp>

TEST_CASE("REQUIRE_FALSE")
{
    REQUIRE_FALSE(false);

    REQUIRE_FALSE(0);
}
