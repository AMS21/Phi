#include <catch2/catch_test_macros.hpp>

#include <Phi/Core/TypeTraits.hpp>

class A
{};

enum E
{
};

enum struct EStruct
{
};

enum class EClass
{
};

TEST_CASE("type_traits is_bounded_array", "[Core][TypeTraits][is_bounded_array]")
{
    STATIC_REQUIRE_FALSE(phi::is_bounded_array<A>::value);
    STATIC_REQUIRE_FALSE(phi::is_bounded_array<A[]>::value);
    STATIC_REQUIRE(phi::is_bounded_array<A[3]>::value);
    STATIC_REQUIRE_FALSE(phi::is_bounded_array<float>::value);
    STATIC_REQUIRE_FALSE(phi::is_bounded_array<int[]>::value);
    STATIC_REQUIRE(phi::is_bounded_array<int[3]>::value);

    STATIC_REQUIRE_FALSE(phi::is_bounded_array_v<A>);
    STATIC_REQUIRE_FALSE(phi::is_bounded_array_v<A[]>);
    STATIC_REQUIRE(phi::is_bounded_array_v<A[3]>);
    STATIC_REQUIRE_FALSE(phi::is_bounded_array_v<float>);
    STATIC_REQUIRE_FALSE(phi::is_bounded_array_v<int[]>);
    STATIC_REQUIRE(phi::is_bounded_array_v<int[3]>);
}

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

TEST_CASE("type_traits is_scoped_enum", "[Core][TypeTraits][is_scoped_enum]")
{
    STATIC_REQUIRE_FALSE(phi::is_scoped_enum<A>::value);
    STATIC_REQUIRE_FALSE(phi::is_scoped_enum<E>::value);
    STATIC_REQUIRE(phi::is_scoped_enum<EStruct>::value);
    STATIC_REQUIRE(phi::is_scoped_enum<EClass>::value);
    STATIC_REQUIRE_FALSE(phi::is_scoped_enum<int>::value);

    STATIC_REQUIRE_FALSE(phi::is_scoped_enum_v<A>);
    STATIC_REQUIRE_FALSE(phi::is_scoped_enum_v<E>);
    STATIC_REQUIRE(phi::is_scoped_enum_v<EStruct>);
    STATIC_REQUIRE(phi::is_scoped_enum_v<EClass>);
    STATIC_REQUIRE_FALSE(phi::is_scoped_enum_v<int>);
}

TEST_CASE("type_traits copy_const", "[Core][TypeTraits][copy_const]")
{
    STATIC_REQUIRE(std::is_same_v<typename phi::copy_const<int, float>::type, float>);
    STATIC_REQUIRE(std::is_same_v<typename phi::copy_const<int, const float>::type, const float>);
    STATIC_REQUIRE(std::is_same_v<typename phi::copy_const<const int, float>::type, const float>);
    STATIC_REQUIRE(
            std::is_same_v<typename phi::copy_const<const int, const float>::type, const float>);

    STATIC_REQUIRE(std::is_same_v<phi::copy_const_v<int, float>, float>);
    STATIC_REQUIRE(std::is_same_v<phi::copy_const_v<int, const float>, const float>);
    STATIC_REQUIRE(std::is_same_v<phi::copy_const_v<const int, float>, const float>);
    STATIC_REQUIRE(std::is_same_v<phi::copy_const_v<const int, const float>, const float>);
}
