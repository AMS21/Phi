#include <catch2/catch.hpp>

#include "ConstexprHelper.hpp"
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Move.hpp>
#include <Phi/TypeTraits/to_safe.hpp>

TEST_CASE("to_safe")
{
    // Boolean
    STATIC_REQUIRE((phi::to_safe(true) == phi::Boolean(true)));

    CONSTEXPR_RUNTIME bool a = true;
    STATIC_REQUIRE((phi::to_safe(a) == phi::Boolean(true)));
    STATIC_REQUIRE((phi::to_safe(phi::move(a)) == phi::Boolean(true)));

    // Integer
    STATIC_REQUIRE((phi::to_safe(3) == phi::Integer<int>(3)));

    CONSTEXPR_RUNTIME int b = 21;
    STATIC_REQUIRE((phi::to_safe(b) == phi::Integer<int>(21)));
    STATIC_REQUIRE((phi::to_safe(phi::move(b)) == phi::Integer<int>(21)));

    // Floating Point
    STATIC_REQUIRE((phi::to_safe(3.0) >= phi::FloatingPoint<double>(3.0)));

    CONSTEXPR_RUNTIME float c = 3.0;
    STATIC_REQUIRE((phi::to_safe(c) >= phi::FloatingPoint<double>(3.0)));
    STATIC_REQUIRE((phi::to_safe(phi::move(c)) >= phi::FloatingPoint<double>(3.0)));
}
