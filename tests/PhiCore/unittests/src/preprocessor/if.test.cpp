#include <phi/test/test_macros.hpp>

#include <phi/preprocessor/if.hpp>

TEST_CASE("PHI_IF_ELSE")
{
    STATIC_REQUIRE(PHI_IF(1, 0) == 0);
    STATIC_REQUIRE(PHI_IF(1, 1) == 1);

    int integer = 3;
    PHI_IF(1, integer = 4;)

    CHECK(integer == 4);

    PHI_IF(0, a = 5;)
    CHECK(integer == 4);
}
