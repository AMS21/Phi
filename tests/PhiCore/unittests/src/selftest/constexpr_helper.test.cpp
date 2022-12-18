#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"

TEST_CASE("ConstexprHelper constexpr", "[selftest][ConstexprHelper]")
{
    constexpr int integer = 3;

    STATIC_REQUIRE(integer == 3);
}
