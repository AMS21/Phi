#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"

TEST_CASE("ConstexprHelper CONSTEXPR_RUNTIME", "[selftest][ConstexprHelper]")
{
    CONSTEXPR_RUNTIME int a = 3;

    STATIC_REQUIRE(a == 3);
}
