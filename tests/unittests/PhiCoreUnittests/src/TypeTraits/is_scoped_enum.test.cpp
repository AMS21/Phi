#include <catch2/catch_test_macros.hpp>

#include <Phi/TypeTraits/is_scoped_enum.hpp>

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
