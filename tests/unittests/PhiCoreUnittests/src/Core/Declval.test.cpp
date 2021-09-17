#include <catch2/catch_test_macros.hpp>

#include "Noexcept.hpp"
#include <Phi/Core/Declval.hpp>
#include <Phi/TypeTraits/is_same.hpp>

class A
{
    A(const A&);
    A& operator=(const A&);
};

TEST_CASE("declval")
{
    STATIC_REQUIRE(phi::is_same_v<decltype(phi::declval<int>()), int&&>);
    STATIC_REQUIRE(phi::is_same_v<decltype(phi::declval<A>()), A&&>);
    CHECK_NOEXCEPT(phi::declval<int>());
    CHECK_NOEXCEPT(phi::declval<A>());
}
