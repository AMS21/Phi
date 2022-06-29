#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"

TEST_CASE("ConstexprHelper CONSTEXPR_RUNTIME", "[selftest][ConstexprHelper]")
{
    CONSTEXPR_RUNTIME int integer = 3;

    STATIC_REQUIRE(integer == 3);
}
