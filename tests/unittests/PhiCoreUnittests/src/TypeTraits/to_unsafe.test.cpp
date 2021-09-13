#include <catch2/catch_test_macros.hpp>

#include "ConstexprHelper.hpp"
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Move.hpp>
#include <Phi/TypeTraits/to_unsafe.hpp>

TEST_CASE("to_unsafe")
{
    // Boolean
    STATIC_REQUIRE(phi::to_unsafe(phi::Boolean(true)) == true);

    CONSTEXPR_RUNTIME phi::Boolean a = true;
    STATIC_REQUIRE(phi::to_unsafe(a) == true);
    STATIC_REQUIRE(phi::to_unsafe(phi::move(a)) == true);

    // Integer
    STATIC_REQUIRE(phi::to_unsafe(phi::Integer<int>(3)) == 3);

    CONSTEXPR_RUNTIME phi::Integer<int> b = 21;
    STATIC_REQUIRE(phi::to_unsafe(b) == 21);
    STATIC_REQUIRE(phi::to_unsafe(phi::move(b)) == 21);

    // Floating Point
    STATIC_REQUIRE(phi::to_unsafe(phi::FloatingPoint<double>(3.0)) == 3.0);

    CONSTEXPR_RUNTIME phi::FloatingPoint<double> c = 3.0;
    STATIC_REQUIRE(phi::to_unsafe(c) == 3.0);
    STATIC_REQUIRE(phi::to_unsafe(phi::move(c)) == 3.0);
}
