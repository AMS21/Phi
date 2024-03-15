#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/cpp_standard.hpp>
#include <phi/type_traits/disjunction.hpp>
#include <phi/type_traits/integral_constant.hpp>
#include <type_traits>

template <typename... ArgsT>
void test_disjunction_true()
{
    STATIC_REQUIRE(phi::disjunction<ArgsT...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::disjunction_v<ArgsT...>);
#endif

    // Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(phi::disjunction<ArgsT...>::value == std::disjunction<ArgsT...>::value);
#endif
}

template <typename... ArgsT>
void test_disjunction_false()
{
    STATIC_REQUIRE_FALSE(phi::disjunction<ArgsT...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::disjunction_v<ArgsT...>);
#endif

    // Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(phi::disjunction<ArgsT...>::value == std::disjunction<ArgsT...>::value);
#endif
}

struct True
{
    static PHI_CONSTEXPR_AND_CONST bool value = true;
};

struct False
{
    static PHI_CONSTEXPR_AND_CONST bool value = false;
};

TEST_CASE("disjunction")
{
    test_disjunction_false<>();

    // standard types
    test_disjunction_true<phi::true_type>();
    test_disjunction_false<phi::false_type>();

    test_disjunction_true<phi::true_type, phi::true_type>();
    test_disjunction_true<phi::true_type, phi::false_type>();
    test_disjunction_true<phi::false_type, phi::true_type>();
    test_disjunction_false<phi::false_type, phi::false_type>();

    test_disjunction_true<phi::true_type, phi::true_type, phi::true_type>();
    test_disjunction_true<phi::true_type, phi::true_type, phi::false_type>();
    test_disjunction_true<phi::true_type, phi::false_type, phi::true_type>();
    test_disjunction_true<phi::true_type, phi::false_type, phi::false_type>();
    test_disjunction_true<phi::false_type, phi::true_type, phi::true_type>();
    test_disjunction_true<phi::false_type, phi::true_type, phi::false_type>();
    test_disjunction_true<phi::false_type, phi::false_type, phi::true_type>();
    test_disjunction_false<phi::false_type, phi::false_type, phi::false_type>();

    test_disjunction_true<phi::true_type, phi::true_type, phi::true_type, phi::true_type>();
    test_disjunction_true<phi::true_type, phi::true_type, phi::true_type, phi::false_type>();
    test_disjunction_true<phi::true_type, phi::true_type, phi::false_type, phi::true_type>();
    test_disjunction_true<phi::true_type, phi::true_type, phi::false_type, phi::false_type>();
    test_disjunction_true<phi::true_type, phi::false_type, phi::true_type, phi::true_type>();
    test_disjunction_true<phi::true_type, phi::false_type, phi::true_type, phi::false_type>();
    test_disjunction_true<phi::true_type, phi::false_type, phi::false_type, phi::true_type>();
    test_disjunction_true<phi::true_type, phi::false_type, phi::false_type, phi::false_type>();
    test_disjunction_true<phi::false_type, phi::true_type, phi::true_type, phi::true_type>();
    test_disjunction_true<phi::false_type, phi::true_type, phi::true_type, phi::false_type>();
    test_disjunction_true<phi::false_type, phi::true_type, phi::false_type, phi::true_type>();
    test_disjunction_true<phi::false_type, phi::true_type, phi::false_type, phi::false_type>();
    test_disjunction_true<phi::false_type, phi::false_type, phi::true_type, phi::true_type>();
    test_disjunction_true<phi::false_type, phi::false_type, phi::true_type, phi::false_type>();
    test_disjunction_true<phi::false_type, phi::false_type, phi::false_type, phi::true_type>();
    test_disjunction_false<phi::false_type, phi::false_type, phi::false_type, phi::false_type>();

    // custome type
    test_disjunction_true<True>();
    test_disjunction_false<False>();

    test_disjunction_true<True, True>();
    test_disjunction_true<True, False>();
    test_disjunction_true<False, True>();
    test_disjunction_false<False, False>();

    test_disjunction_true<True, True, True>();
    test_disjunction_true<True, True, False>();
    test_disjunction_true<True, False, True>();
    test_disjunction_true<True, False, False>();
    test_disjunction_true<False, True, True>();
    test_disjunction_true<False, True, False>();
    test_disjunction_true<False, False, True>();
    test_disjunction_false<False, False, False>();

    test_disjunction_true<True, True, True, True>();
    test_disjunction_true<True, True, True, False>();
    test_disjunction_true<True, True, False, True>();
    test_disjunction_true<True, True, False, False>();
    test_disjunction_true<True, False, True, True>();
    test_disjunction_true<True, False, True, False>();
    test_disjunction_true<True, False, False, True>();
    test_disjunction_true<True, False, False, False>();
    test_disjunction_true<False, True, True, True>();
    test_disjunction_true<False, True, True, False>();
    test_disjunction_true<False, True, False, True>();
    test_disjunction_true<False, True, False, False>();
    test_disjunction_true<False, False, True, True>();
    test_disjunction_true<False, False, True, False>();
    test_disjunction_true<False, False, False, True>();
    test_disjunction_false<False, False, False, False>();

    // Non bool values
    STATIC_REQUIRE(phi::disjunction<phi::integral_constant<int, 2>>::value == 2);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::disjunction_v<phi::integral_constant<int, 2>>);
#endif

    STATIC_REQUIRE(phi::disjunction<phi::integral_constant<int, 2>,
                                    phi::integral_constant<int, 4>>::value == 2);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(
            phi::disjunction_v<phi::integral_constant<int, 2>, phi::integral_constant<int, 4>>);
#endif
}
