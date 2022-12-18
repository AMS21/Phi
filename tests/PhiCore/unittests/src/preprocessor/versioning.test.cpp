#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/preprocessor/versioning.hpp>

TEST_CASE("Versioning", "[Config][Versioning]")
{
    SECTION("Random values")
    {
        constexpr int val = PHI_VERSION_CREATE(3, 1, 4);

        STATIC_REQUIRE(PHI_VERSION_EXTRACT_MAJOR(val) == 3);
        STATIC_REQUIRE(PHI_VERSION_EXTRACT_MINOR(val) == 1);
        STATIC_REQUIRE(PHI_VERSION_EXTRACT_PATCH(val) == 4);
    }

    SECTION("Zero")
    {
        constexpr int val = PHI_VERSION_CREATE(0, 0, 0);

        STATIC_REQUIRE(PHI_VERSION_EXTRACT_MAJOR(val) == 0);
        STATIC_REQUIRE(PHI_VERSION_EXTRACT_MINOR(val) == 0);
        STATIC_REQUIRE(PHI_VERSION_EXTRACT_PATCH(val) == 0);
    }

    SECTION("More random values")
    {
        constexpr int val = PHI_VERSION_CREATE(2, 55, 13);

        STATIC_REQUIRE(PHI_VERSION_EXTRACT_MAJOR(val) == 2);
        STATIC_REQUIRE(PHI_VERSION_EXTRACT_MINOR(val) == 55);
        STATIC_REQUIRE(PHI_VERSION_EXTRACT_PATCH(val) == 13);
    }

    SECTION("Max values")
    {
        constexpr int val = PHI_VERSION_CREATE(126, 126, 126);

        STATIC_REQUIRE(PHI_VERSION_EXTRACT_MAJOR(val) == 126);
        STATIC_REQUIRE(PHI_VERSION_EXTRACT_MINOR(val) == 126);
        STATIC_REQUIRE(PHI_VERSION_EXTRACT_PATCH(val) == 126);
    }
}
