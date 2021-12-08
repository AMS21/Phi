#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/compiler_support/warning.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/move.hpp>
#include <phi/type_traits/to_unsafe.hpp>

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wfloat-equal")
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")

TEST_CASE("to_unsafe")
{
    // boolean
    STATIC_REQUIRE(phi::to_unsafe(phi::boolean(true)) == true);

    CONSTEXPR_RUNTIME phi::boolean a = true;
    STATIC_REQUIRE(phi::to_unsafe(a) == true);
    STATIC_REQUIRE(phi::to_unsafe(phi::move(a)) == true);

    // integer
    STATIC_REQUIRE(phi::to_unsafe(phi::integer<int>(3)) == 3);

    CONSTEXPR_RUNTIME phi::integer<int> b = 21;
    STATIC_REQUIRE(phi::to_unsafe(b) == 21);
    STATIC_REQUIRE(phi::to_unsafe(phi::move(b)) == 21);

    // Floating Point
    STATIC_REQUIRE(phi::to_unsafe(phi::floating_point<double>(3.0)) == 3.0);

    CONSTEXPR_RUNTIME phi::floating_point<double> c = 3.0;
    STATIC_REQUIRE(phi::to_unsafe(c) == 3.0);
    STATIC_REQUIRE(phi::to_unsafe(phi::move(c)) == 3.0);
}

PHI_GCC_SUPPRESS_WARNING_POP()
