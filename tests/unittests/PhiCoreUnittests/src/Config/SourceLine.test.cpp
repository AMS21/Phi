#include <catch2/catch_test_macros.hpp>

#include <Phi/Algorithm/StringEquals.hpp>
#include <Phi/Config/SourceLine.hpp>

TEST_CASE("SourceLine")
{
    STATIC_REQUIRE(phi::StringEquals(PHI_SOURCE_LINE(), "8"));
    STATIC_REQUIRE(phi::StringEquals(PHI_SOURCE_LINE(), "9"));

    // Forcing line
#line 5
    STATIC_REQUIRE(phi::StringEquals(PHI_SOURCE_LINE(), "5"));
    STATIC_REQUIRE(phi::StringEquals(PHI_SOURCE_LINE(), "6"));
}
