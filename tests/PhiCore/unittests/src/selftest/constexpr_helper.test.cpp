#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/compiler_support/constexpr.hpp>

TEST_CASE("ConstexprHelper constexpr", "[selftest][ConstexprHelper]")
{
    PHI_CONSTEXPR int integer = 3;

    STATIC_REQUIRE(integer == 3);
}
