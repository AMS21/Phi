#include <catch2/catch.hpp>

#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Math/Constants.hpp>

TEMPLATE_TEST_CASE("Constants typed", "[Math][Constants]", float, double, long double,
                   phi::FloatingPoint<float>, phi::FloatingPoint<double>,
                   phi::FloatingPoint<long double>)
{
    STATIC_REQUIRE(bool(phi::e_v<TestType> > TestType(2.0f)));
    STATIC_REQUIRE(bool(phi::pi_v<TestType> > TestType(3.0f)));
    STATIC_REQUIRE(bool(phi::two_pi_v<TestType> > TestType(6.0f)));
    STATIC_REQUIRE(bool(phi::sqrt_pi_v<TestType> > TestType(1.0f)));
    STATIC_REQUIRE(bool(phi::half_pi_v<TestType> > TestType(1.0f)));
    STATIC_REQUIRE(bool(phi::three_over_two_pi_v<TestType> > TestType(4.0f)));
    STATIC_REQUIRE(bool(phi::quarter_pi_v<TestType> > TestType(0.0f)));
    STATIC_REQUIRE(bool(phi::one_over_pi_v<TestType> > TestType(0.0f)));
    STATIC_REQUIRE(bool(phi::one_over_two_pi_v<TestType> > TestType(0.0f)));
    STATIC_REQUIRE(bool(phi::two_over_pi_v<TestType> > TestType(0.0f)));
    STATIC_REQUIRE(bool(phi::four_over_pi_v<TestType> > TestType(1.0f)));
    STATIC_REQUIRE(bool(phi::two_over_sqrt_pi_v<TestType> > TestType(1.0f)));
    STATIC_REQUIRE(bool(phi::one_over_sqrt_two_v<TestType> > TestType(0.0f)));
    STATIC_REQUIRE(bool(phi::sqrt_half_pi_v<TestType> > TestType(1.0f)));
    STATIC_REQUIRE(bool(phi::sqrt_two_pi_v<TestType> > TestType(2.0f)));
    STATIC_REQUIRE(bool(phi::sqrt_two_v<TestType> > TestType(1.0f)));
    STATIC_REQUIRE(bool(phi::sqrt_three_v<TestType> > TestType(1.0f)));
    STATIC_REQUIRE(bool(phi::deg2rad_v<TestType> > TestType(0.0f)));
    STATIC_REQUIRE(bool(phi::rad2deg_v<TestType> > TestType(0.0f)));
    STATIC_REQUIRE(bool(phi::golden_ratio_v<TestType> > TestType(1.0f)));
    STATIC_REQUIRE(bool(phi::cos_one_over_two_v<TestType> > TestType(0.0f)));
}

#define TEST_CONSTANT(name, val)                                                                   \
    STATIC_REQUIRE(bool(name > val));                                                              \
    STATIC_REQUIRE(bool(PHI_GLUE(name, _64) > PHI_GLUE(val, L)));                                  \
    STATIC_REQUIRE(bool(PHI_GLUE(name, _32) > PHI_GLUE(val, f)))

TEST_CASE("Constants", "[Math][Constant]")
{
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
