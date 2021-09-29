#include <catch2/catch.hpp>

#include <Phi/Core/Types.hpp>
#include <Phi/TypeTraits/always_false.hpp>

class CustomClass
{};

TEMPLATE_TEST_CASE("always_false types", "[Meta][always_false]", void, int, float, phi::i32,
                   phi::f64, CustomClass)
{
    STATIC_REQUIRE_FALSE(phi::always_false<TestType>::value);
    STATIC_REQUIRE(!phi::always_false<TestType>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::always_false_v<TestType>);
    STATIC_REQUIRE(!phi::always_false_v<TestType>);
#endif
}

TEST_CASE("always_false", "[Meta][always_false]")
{
    STATIC_REQUIRE_FALSE(phi::always_false<int>::value);
    STATIC_REQUIRE_FALSE(phi::always_false<int, int>::value);
    STATIC_REQUIRE_FALSE(phi::always_false<int, int, int>::value);
    STATIC_REQUIRE_FALSE(phi::always_false<int, int, int, int>::value);
    STATIC_REQUIRE_FALSE(phi::always_false<int, int, int, int, int>::value);
}

template <typename TypeT>
void func()
{
    static_assert(phi::always_false<TypeT>::value, "Failure");
}

template <>
void func<int>()
{}

TEST_CASE("always_false two phase lookup", "[Meta][always_false]")
{
    func<int>();
}
