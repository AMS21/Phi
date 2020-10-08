#include <catch2/catch.hpp>

#include "StringHelper.hpp"
#include <Phi/Config/Stringify.hpp>

TEST_CASE("Stringify", "[Config][Stringify]")
{
    STATIC_REQUIRE(string_equals(PHI_STRINGIFY(2 + 3), "2 + 3"));
    STATIC_REQUIRE(string_equals(PHI_STRINGIFY(test), "test"));
    STATIC_REQUIRE(string_equals(PHI_STRINGIFY(+-), "+-"));
}
