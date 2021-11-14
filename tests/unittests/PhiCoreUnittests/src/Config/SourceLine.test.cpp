#include <catch2/catch.hpp>

#include "ConstexprHelper.hpp"
#include <Phi/Algorithm/StringEquals.hpp>
#include <Phi/Config/SourceLine.hpp>

TEST_CASE("SourceLine")
{
    EXT_STATIC_REQUIRE(phi::StringEquals(PHI_SOURCE_LINE(), "9"));
    EXT_STATIC_REQUIRE(phi::StringEquals(PHI_SOURCE_LINE(), "10"));

    // Forcing line
#line 5
    EXT_STATIC_REQUIRE(phi::StringEquals(PHI_SOURCE_LINE(), "5"));
    EXT_STATIC_REQUIRE(phi::StringEquals(PHI_SOURCE_LINE(), "6"));
}
