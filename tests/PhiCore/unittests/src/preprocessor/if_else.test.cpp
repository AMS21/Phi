#include <phi/test/test_macros.hpp>

#include <phi/preprocessor/if_else.hpp>

TEST_CASE("PHI_IF_ELSE")
{
    STATIC_REQUIRE(PHI_IF_ELSE(0, 1, 0) == 0);
    STATIC_REQUIRE(PHI_IF_ELSE(1, 1, 0) == 1);
}
