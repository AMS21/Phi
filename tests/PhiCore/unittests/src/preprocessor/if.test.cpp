#include <phi/test/test_macros.hpp>

#include <phi/preprocessor/if.hpp>

TEST_CASE("PHI_IF_ELSE")
{
    STATIC_REQUIRE(PHI_IF(1, 0) == 0);
    STATIC_REQUIRE(PHI_IF(1, 1) == 1);

    int a = 3;
    PHI_IF(1, a = 4);

    CHECK(a == 4);

    PHI_IF(0, a = 5);
    CHECK(a == 4);
}
