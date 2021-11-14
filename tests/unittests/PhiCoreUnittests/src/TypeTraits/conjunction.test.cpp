#include "Phi/TypeTraits/conditional.hpp"
#include <catch2/catch.hpp>

#include <Phi/Config/CPlusPlus.hpp>
#include <Phi/TypeTraits/conjunction.hpp>
#include <Phi/TypeTraits/integral_constant.hpp>
#include <type_traits>

template <typename... ArgsT>
void test_conjunction_true()
{
    STATIC_REQUIRE(phi::conjunction<ArgsT...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::conjunction_v<ArgsT...>);
#endif

// Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(phi::conjunction<ArgsT...>::value == std::conjunction<ArgsT...>::value);
#endif
}

template <typename... ArgsT>
void test_conjunction_false()
{
    STATIC_REQUIRE_FALSE(phi::conjunction<ArgsT...>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::conjunction_v<ArgsT...>);
#endif

// Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(phi::conjunction<ArgsT...>::value == std::conjunction<ArgsT...>::value);
#endif
}

struct True
{
    static constexpr bool value = true;
};

struct False
{
    static constexpr bool value = false;
};

TEST_CASE("conjunction")
{
    test_conjunction_true<>();

    // standard types
    test_conjunction_true<phi::true_type>();
    test_conjunction_false<phi::false_type>();

    test_conjunction_true<phi::true_type, phi::true_type>();
    test_conjunction_false<phi::true_type, phi::false_type>();
    test_conjunction_false<phi::false_type, phi::true_type>();
    test_conjunction_false<phi::false_type, phi::false_type>();

    test_conjunction_true<phi::true_type, phi::true_type, phi::true_type>();
    test_conjunction_false<phi::true_type, phi::true_type, phi::false_type>();
    test_conjunction_false<phi::true_type, phi::false_type, phi::true_type>();
    test_conjunction_false<phi::true_type, phi::false_type, phi::false_type>();
    test_conjunction_false<phi::false_type, phi::true_type, phi::true_type>();
    test_conjunction_false<phi::false_type, phi::true_type, phi::false_type>();
    test_conjunction_false<phi::false_type, phi::false_type, phi::true_type>();
    test_conjunction_false<phi::false_type, phi::false_type, phi::false_type>();

    test_conjunction_true<phi::true_type, phi::true_type, phi::true_type, phi::true_type>();
    test_conjunction_false<phi::true_type, phi::true_type, phi::true_type, phi::false_type>();
    test_conjunction_false<phi::true_type, phi::true_type, phi::false_type, phi::true_type>();
    test_conjunction_false<phi::true_type, phi::true_type, phi::false_type, phi::false_type>();
    test_conjunction_false<phi::true_type, phi::false_type, phi::true_type, phi::true_type>();
    test_conjunction_false<phi::true_type, phi::false_type, phi::true_type, phi::false_type>();
    test_conjunction_false<phi::true_type, phi::false_type, phi::false_type, phi::true_type>();
    test_conjunction_false<phi::true_type, phi::false_type, phi::false_type, phi::false_type>();
    test_conjunction_false<phi::false_type, phi::true_type, phi::true_type, phi::true_type>();
    test_conjunction_false<phi::false_type, phi::true_type, phi::true_type, phi::false_type>();
    test_conjunction_false<phi::false_type, phi::true_type, phi::false_type, phi::true_type>();
    test_conjunction_false<phi::false_type, phi::true_type, phi::false_type, phi::false_type>();
    test_conjunction_false<phi::false_type, phi::false_type, phi::true_type, phi::true_type>();
    test_conjunction_false<phi::false_type, phi::false_type, phi::true_type, phi::false_type>();
    test_conjunction_false<phi::false_type, phi::false_type, phi::false_type, phi::true_type>();
    test_conjunction_false<phi::false_type, phi::false_type, phi::false_type, phi::false_type>();

    // custome type
    test_conjunction_true<True>();
    test_conjunction_false<False>();

    test_conjunction_true<True, True>();
    test_conjunction_false<True, False>();
    test_conjunction_false<False, True>();
    test_conjunction_false<False, False>();

    test_conjunction_true<True, True, True>();
    test_conjunction_false<True, True, False>();
    test_conjunction_false<True, False, True>();
    test_conjunction_false<True, False, False>();
    test_conjunction_false<False, True, True>();
    test_conjunction_false<False, True, False>();
    test_conjunction_false<False, False, True>();
    test_conjunction_false<False, False, False>();

    test_conjunction_true<True, True, True, True>();
    test_conjunction_false<True, True, True, False>();
    test_conjunction_false<True, True, False, True>();
    test_conjunction_false<True, True, False, False>();
    test_conjunction_false<True, False, True, True>();
    test_conjunction_false<True, False, True, False>();
    test_conjunction_false<True, False, False, True>();
    test_conjunction_false<True, False, False, False>();
    test_conjunction_false<False, True, True, True>();
    test_conjunction_false<False, True, True, False>();
    test_conjunction_false<False, True, False, True>();
    test_conjunction_false<False, True, False, False>();
    test_conjunction_false<False, False, True, True>();
    test_conjunction_false<False, False, True, False>();
    test_conjunction_false<False, False, False, True>();
    test_conjunction_false<False, False, False, False>();

    // Non bool values
    STATIC_REQUIRE(phi::conjunction<phi::integral_constant<int, 2>>::value == 2);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::conjunction_v<phi::integral_constant<int, 2>>);
#endif

    STATIC_REQUIRE(phi::conjunction<phi::integral_constant<int, 2>,
                                    phi::integral_constant<int, 4>>::value == 4);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(
            phi::conjunction_v<phi::integral_constant<int, 2>, phi::integral_constant<int, 4>>);
#endif
}
