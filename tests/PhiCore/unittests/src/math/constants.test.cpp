#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/warning.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/types.hpp>
#include <phi/math/constants.hpp>
#include <phi/preprocessor/glue.hpp>

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")

#define TEST_CONSTANT(name, val)                                                                   \
    STATIC_REQUIRE(bool(name() > (val)));                                                          \
    STATIC_REQUIRE(bool(PHI_GLUE(name, _64()) > PHI_GLUE(val, L)));                                \
    STATIC_REQUIRE(bool(PHI_GLUE(name, _32()) > PHI_GLUE(val, f)))

template <typename TypeT>
void test_constant()
{
    STATIC_REQUIRE(bool(phi::e_v<TypeT>() > TypeT(2.0f)));
    STATIC_REQUIRE(bool(phi::pi_v<TypeT>() > TypeT(3.0f)));
    STATIC_REQUIRE(bool(phi::two_pi_v<TypeT>() > TypeT(6.0f)));
    STATIC_REQUIRE(bool(phi::sqrt_pi_v<TypeT>() > TypeT(1.0f)));
    STATIC_REQUIRE(bool(phi::half_pi_v<TypeT>() > TypeT(1.0f)));
    STATIC_REQUIRE(bool(phi::three_over_two_pi_v<TypeT>() > TypeT(4.0f)));
    STATIC_REQUIRE(bool(phi::quarter_pi_v<TypeT>() > TypeT(0.0f)));
    STATIC_REQUIRE(bool(phi::one_over_pi_v<TypeT>() > TypeT(0.0f)));
    STATIC_REQUIRE(bool(phi::one_over_two_pi_v<TypeT>() > TypeT(0.0f)));
    STATIC_REQUIRE(bool(phi::two_over_pi_v<TypeT>() > TypeT(0.0f)));
    STATIC_REQUIRE(bool(phi::four_over_pi_v<TypeT>() > TypeT(1.0f)));
    STATIC_REQUIRE(bool(phi::two_over_sqrt_pi_v<TypeT>() > TypeT(1.0f)));
    STATIC_REQUIRE(bool(phi::one_over_sqrt_two_v<TypeT>() > TypeT(0.0f)));
    STATIC_REQUIRE(bool(phi::sqrt_half_pi_v<TypeT>() > TypeT(1.0f)));
    STATIC_REQUIRE(bool(phi::sqrt_two_pi_v<TypeT>() > TypeT(2.0f)));
    STATIC_REQUIRE(bool(phi::sqrt_two_v<TypeT>() > TypeT(1.0f)));
    STATIC_REQUIRE(bool(phi::sqrt_three_v<TypeT>() > TypeT(1.0f)));
    STATIC_REQUIRE(bool(phi::deg2rad_v<TypeT>() > TypeT(0.0f)));
    STATIC_REQUIRE(bool(phi::rad2deg_v<TypeT>() > TypeT(0.0f)));
    STATIC_REQUIRE(bool(phi::golden_ratio_v<TypeT>() > TypeT(1.0f)));
    STATIC_REQUIRE(bool(phi::cos_one_over_two_v<TypeT>() > TypeT(0.0f)));
}

TEST_CASE("Constants")
{
    test_constant<float>();
    test_constant<double>();
    test_constant<long double>();
    test_constant<phi::floating_point<float>>();
    test_constant<phi::floating_point<double>>();
    test_constant<phi::floating_point<long double>>();

    TEST_CONSTANT(phi::e, 2.0);
    TEST_CONSTANT(phi::pi, 3.0);
    TEST_CONSTANT(phi::two_pi, 6.0);
    TEST_CONSTANT(phi::sqrt_pi, 1.0);
    TEST_CONSTANT(phi::half_pi, 1.0);
    TEST_CONSTANT(phi::three_over_two_pi, 4.0);
    TEST_CONSTANT(phi::quarter_pi, 0.0);
    TEST_CONSTANT(phi::one_over_pi, 0.0);
    TEST_CONSTANT(phi::one_over_two_pi, 0.0);
    TEST_CONSTANT(phi::two_over_pi, 0.0);
    TEST_CONSTANT(phi::four_over_pi, 1.0);
    TEST_CONSTANT(phi::two_over_sqrt_pi, 1.0);
    TEST_CONSTANT(phi::one_over_sqrt_two, 0.0);
    TEST_CONSTANT(phi::sqrt_half_pi, 1.0);
    TEST_CONSTANT(phi::sqrt_two_pi, 2.0);
    TEST_CONSTANT(phi::sqrt_two, 1.0);
    TEST_CONSTANT(phi::sqrt_three, 1.0);
    TEST_CONSTANT(phi::deg2rad, 0.0);
    TEST_CONSTANT(phi::rad2deg, 0.0);
    TEST_CONSTANT(phi::golden_ratio, 1.0);
    TEST_CONSTANT(phi::cos_one_over_two, 0.0);
}

PHI_GCC_SUPPRESS_WARNING_POP()
