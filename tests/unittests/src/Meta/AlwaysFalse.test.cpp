#include <catch2/catch.hpp>

#include <Phi/Meta/AlwaysFalse.hpp>
#include <Phi/Utility/Types.hpp>

class CustomClass
{};

TEMPLATE_TEST_CASE("always_false types", "[Meta][always_false]", void, int, float, phi::i32,
                   phi::f64, CustomClass)
{
    STATIC_REQUIRE_FALSE(phi::always_false<TestType>);
    STATIC_REQUIRE(!phi::always_false<TestType>);
}

TEST_CASE("always_false", "[Meta][always_false]")
{
    STATIC_REQUIRE_FALSE(phi::always_false<int>);
    STATIC_REQUIRE_FALSE(phi::always_false<int, int>);
    STATIC_REQUIRE_FALSE(phi::always_false<int, int, int>);
    STATIC_REQUIRE_FALSE(phi::always_false<int, int, int, int>);
    STATIC_REQUIRE_FALSE(phi::always_false<int, int, int, int, int>);
}

template <typename TypeT>
void func()
{
    static_assert(phi::always_false<TypeT>, "Failure");
}

template <>
void func<int>()
{}

TEST_CASE("always_false two phase lookup", "[Meta][always_false]")
{
    func<int>();
}
