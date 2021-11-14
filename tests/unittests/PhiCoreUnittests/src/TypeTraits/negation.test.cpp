#include <catch2/catch.hpp>

#include <Phi/TypeTraits/negation.hpp>

struct True
{
    static constexpr bool value = true;
};
struct False
{
    static constexpr bool value = false;
};

TEST_CASE("negation")
{
    STATIC_REQUIRE_FALSE(phi::negation<phi::true_type>::value);
    STATIC_REQUIRE(phi::negation<phi::false_type>::value);

    STATIC_REQUIRE_FALSE(phi::negation<True>::value);
    STATIC_REQUIRE(phi::negation<False>::value);

    STATIC_REQUIRE(phi::negation<phi::negation<phi::true_type>>::value);
    STATIC_REQUIRE_FALSE(phi::negation<phi::negation<phi::false_type>>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::negation_v<True>);
    STATIC_REQUIRE(phi::negation_v<False>);

    STATIC_REQUIRE_FALSE(phi::negation_v<phi::true_type>);
    STATIC_REQUIRE(phi::negation_v<phi::false_type>);

    STATIC_REQUIRE(phi::negation_v<phi::negation<phi::true_type>>);
    STATIC_REQUIRE_FALSE(phi::negation_v<phi::negation<phi::false_type>>);
#endif
}
