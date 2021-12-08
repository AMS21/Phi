#include <phi/test/test_macros.hpp>

TEST_CASE("REQUIRE")
{
    REQUIRE(true);

    // Automatically converted to boolean
    REQUIRE(1);
}
