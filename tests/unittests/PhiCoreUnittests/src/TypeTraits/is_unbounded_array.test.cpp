#include <catch2/catch_test_macros.hpp>

#include <Phi/TypeTraits/is_unbounded_array.hpp>

class A
{};

TEST_CASE("type_traits is_unbounded_array", "[Core][TypeTraits][is_unbounded_array]")
{
    STATIC_REQUIRE_FALSE(phi::is_unbounded_array<A>::value);
    STATIC_REQUIRE(phi::is_unbounded_array<A[]>::value);
    STATIC_REQUIRE_FALSE(phi::is_unbounded_array<A[3]>::value);
    STATIC_REQUIRE_FALSE(phi::is_unbounded_array<float>::value);
    STATIC_REQUIRE(phi::is_unbounded_array<int[]>::value);
    STATIC_REQUIRE_FALSE(phi::is_unbounded_array<int[3]>::value);

    STATIC_REQUIRE_FALSE(phi::is_unbounded_array_v<A>);
    STATIC_REQUIRE(phi::is_unbounded_array_v<A[]>);
    STATIC_REQUIRE_FALSE(phi::is_unbounded_array_v<A[3]>);
    STATIC_REQUIRE_FALSE(phi::is_unbounded_array_v<float>);
    STATIC_REQUIRE(phi::is_unbounded_array_v<int[]>);
    STATIC_REQUIRE_FALSE(phi::is_unbounded_array_v<int[3]>);
}
