#include <phi/test/test_macros.hpp>

#include <phi/preprocessor/bool.hpp>

TEST_CASE("PHI_BOOL")
{
    STATIC_REQUIRE_FALSE(PHI_BOOL(0));
    STATIC_REQUIRE(PHI_BOOL(1));
}
