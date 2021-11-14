#include <catch2/catch.hpp>

#include "ConstexprHelper.hpp"
#include <Phi/Algorithm/StringEquals.hpp>
#include <Phi/Config/Stringify.hpp>

TEST_CASE("Stringify", "[Config][Stringify]")
{
    EXT_STATIC_REQUIRE(phi::StringEquals(PHI_STRINGIFY(2 + 3), "2 + 3"));
    EXT_STATIC_REQUIRE(phi::StringEquals(PHI_STRINGIFY(test), "test"));
    EXT_STATIC_REQUIRE(phi::StringEquals(PHI_STRINGIFY(+-), "+-"));
}
