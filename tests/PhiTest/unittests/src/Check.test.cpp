#include <Phi/Test/TestMacros.hpp>

TEST_CASE("CHECK")
{
    CHECK(true);
    // Automatically converted to boolean
    CHECK(1);
}
