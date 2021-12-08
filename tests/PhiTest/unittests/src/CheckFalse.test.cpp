#include <phi/test/test_macros.hpp>

TEST_CASE("CHECK_FALSE")
{
    CHECK_FALSE(false);
    CHECK_FALSE(0);
}
