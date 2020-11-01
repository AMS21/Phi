#include <catch2/catch_test_macros.hpp>

#include "ConstexprHelper.hpp"

TEST_CASE("ConstexprHelper CONSTEXPR_RUNTIME", "[selftest][ConstexprHelper]")
{
    CONSTEXPR_RUNTIME int a = 3;

    STATIC_REQUIRE(a == 3);
}
