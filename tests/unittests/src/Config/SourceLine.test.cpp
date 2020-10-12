#include <catch2/catch.hpp>

#include "StringHelper.hpp"
#include <Phi/Config/SourceLine.hpp>

TEST_CASE("SourceLine")
{
    STATIC_REQUIRE(string_equals(PHI_SOURCE_LINE(), "8"));
    STATIC_REQUIRE(string_equals(PHI_SOURCE_LINE(), "9"));

    // Forcing line
#line 5
    STATIC_REQUIRE(string_equals(PHI_SOURCE_LINE(), "5"));
    STATIC_REQUIRE(string_equals(PHI_SOURCE_LINE(), "6"));
}
