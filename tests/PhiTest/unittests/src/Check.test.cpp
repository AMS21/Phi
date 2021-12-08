#include <phi/test/test_macros.hpp>

TEST_CASE("CHECK")
{
    CHECK(true);
    // Automatically converted to boolean
    CHECK(1);
}
