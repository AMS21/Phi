#include <catch2/catch_test_macros.hpp>

#include <Phi/Algorithm/StringEquals.hpp>
#include <Phi/Config/Stringify.hpp>

TEST_CASE("Stringify", "[Config][Stringify]")
{
    STATIC_REQUIRE(phi::StringEquals(PHI_STRINGIFY(2 + 3), "2 + 3"));
    STATIC_REQUIRE(phi::StringEquals(PHI_STRINGIFY(test), "test"));
    STATIC_REQUIRE(phi::StringEquals(PHI_STRINGIFY(+-), "+-"));
}
