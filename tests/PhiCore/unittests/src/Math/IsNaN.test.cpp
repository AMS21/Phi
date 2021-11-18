#include <Phi/Test/TestMacros.hpp>

#include <Phi/CompilerSupport/Features.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Math/IsNan.hpp>
#include <cfloat>
#include <cmath>
#include <limits>

using sf = phi::FloatingPoint<float>;
using sd = phi::FloatingPoint<double>;
using sl = phi::FloatingPoint<long double>;

TEST_CASE("IsNaN")
{
    // Float
    CHECK(phi::IsNaN(std::nanf("")));
    CHECK(phi::IsNaN(std::nanf("0")));
    CHECK(phi::IsNaN(std::nanf("1")));
    CHECK(phi::IsNaN(std::nanf("21")));
#if PHI_HAS_EXTENSION_ALLOW_DIVIDE_BY_ZERO_CONSTANT()
    CHECK(phi::IsNaN(0.0f / 0.0f));
#endif
    CHECK(phi::IsNaN(INFINITY - INFINITY));
    STATIC_REQUIRE(phi::IsNaN(NAN));
    STATIC_REQUIRE(phi::IsNaN(std::numeric_limits<float>::quiet_NaN()));
    STATIC_REQUIRE(phi::IsNaN(std::numeric_limits<float>::signaling_NaN()));

    STATIC_REQUIRE_FALSE(phi::IsNaN(0.0f));
    STATIC_REQUIRE_FALSE(phi::IsNaN(-0.0f));
    STATIC_REQUIRE_FALSE(phi::IsNaN(1.0f));
    STATIC_REQUIRE_FALSE(phi::IsNaN(-1.0f));
    STATIC_REQUIRE_FALSE(phi::IsNaN(INFINITY));
    STATIC_REQUIRE_FALSE(phi::IsNaN(-INFINITY));
    STATIC_REQUIRE_FALSE(phi::IsNaN(HUGE_VALF));
    STATIC_REQUIRE_FALSE(phi::IsNaN(FLT_MIN / 2.0f));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<float>::epsilon()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<float>::infinity()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(-std::numeric_limits<float>::infinity()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<float>::min()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<float>::max()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<float>::lowest()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<float>::denorm_min()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<float>::round_error()));

    // double
    CHECK(phi::IsNaN(std::nan("")));
    CHECK(phi::IsNaN(std::nan("0")));
    CHECK(phi::IsNaN(std::nan("1")));
    CHECK(phi::IsNaN(std::nan("21")));
#if PHI_HAS_EXTENSION_ALLOW_DIVIDE_BY_ZERO_CONSTANT()
    CHECK(phi::IsNaN(0.0 / 0.0));
#endif
    STATIC_REQUIRE(phi::IsNaN(std::numeric_limits<double>::quiet_NaN()));
    STATIC_REQUIRE(phi::IsNaN(std::numeric_limits<double>::signaling_NaN()));

    STATIC_REQUIRE_FALSE(phi::IsNaN(0.0));
    STATIC_REQUIRE_FALSE(phi::IsNaN(-0.0));
    STATIC_REQUIRE_FALSE(phi::IsNaN(1.0));
    STATIC_REQUIRE_FALSE(phi::IsNaN(-1.0));
    STATIC_REQUIRE_FALSE(phi::IsNaN(HUGE_VAL));
    STATIC_REQUIRE_FALSE(phi::IsNaN(DBL_MIN / 2.0));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<double>::epsilon()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<double>::infinity()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(-std::numeric_limits<double>::infinity()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<double>::min()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<double>::max()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<double>::lowest()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<double>::denorm_min()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<double>::round_error()));

    // long double
    CHECK(phi::IsNaN(std::nanl("")));
    CHECK(phi::IsNaN(std::nanl("0")));
    CHECK(phi::IsNaN(std::nanl("1")));
    CHECK(phi::IsNaN(std::nanl("21")));
#if PHI_HAS_EXTENSION_ALLOW_DIVIDE_BY_ZERO_CONSTANT()
    CHECK(phi::IsNaN(0.0L / 0.0L));
#endif
    STATIC_REQUIRE(phi::IsNaN(std::numeric_limits<long double>::quiet_NaN()));
    STATIC_REQUIRE(phi::IsNaN(std::numeric_limits<long double>::signaling_NaN()));

    STATIC_REQUIRE_FALSE(phi::IsNaN(0.0L));
    STATIC_REQUIRE_FALSE(phi::IsNaN(-0.0L));
    STATIC_REQUIRE_FALSE(phi::IsNaN(1.0L));
    STATIC_REQUIRE_FALSE(phi::IsNaN(-1.0L));
    STATIC_REQUIRE_FALSE(phi::IsNaN(HUGE_VALL));
    STATIC_REQUIRE_FALSE(phi::IsNaN(LDBL_MIN / 2.0L));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<long double>::epsilon()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<long double>::infinity()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(-std::numeric_limits<long double>::infinity()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<long double>::min()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<long double>::max()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<long double>::lowest()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<long double>::denorm_min()));
    STATIC_REQUIRE_FALSE(phi::IsNaN(std::numeric_limits<long double>::round_error()));

    // FloatingPoint<float>
    CHECK(phi::IsNaN(sf(std::nanf(""))));
    CHECK(phi::IsNaN(sf(std::nanf("0"))));
    CHECK(phi::IsNaN(sf(std::nanf("1"))));
    CHECK(phi::IsNaN(sf(std::nanf("21"))));
#if PHI_HAS_EXTENSION_ALLOW_DIVIDE_BY_ZERO_CONSTANT()
    CHECK(phi::IsNaN(sf(0.0f / 0.0f)));
#endif
    CHECK(phi::IsNaN(sf(INFINITY - INFINITY)));
    CHECK(phi::IsNaN(sf(NAN)));
    STATIC_REQUIRE(phi::IsNaN(sf(std::numeric_limits<float>::quiet_NaN())));
    STATIC_REQUIRE(phi::IsNaN(sf(std::numeric_limits<float>::signaling_NaN())));

    STATIC_REQUIRE_FALSE(phi::IsNaN(sf(0.0f)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sf(-0.0f)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sf(1.0f)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sf(-1.0f)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sf(INFINITY)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sf(-INFINITY)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sf(HUGE_VALF)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sf(FLT_MIN / 2.0f)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sf(std::numeric_limits<float>::epsilon())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sf(std::numeric_limits<float>::infinity())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sf(-std::numeric_limits<float>::infinity())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sf(std::numeric_limits<float>::min())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sf(std::numeric_limits<float>::max())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sf(std::numeric_limits<float>::lowest())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sf(std::numeric_limits<float>::denorm_min())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sf(std::numeric_limits<float>::round_error())));

    // FloatingPoint<double>
    CHECK(phi::IsNaN(sd(std::nan(""))));
    CHECK(phi::IsNaN(sd(std::nan("0"))));
    CHECK(phi::IsNaN(sd(std::nan("1"))));
    CHECK(phi::IsNaN(sd(std::nan("21"))));
#if PHI_HAS_EXTENSION_ALLOW_DIVIDE_BY_ZERO_CONSTANT()
    CHECK(phi::IsNaN(sd(0.0 / 0.0)));
#endif
    STATIC_REQUIRE(phi::IsNaN(sd(std::numeric_limits<double>::quiet_NaN())));
    STATIC_REQUIRE(phi::IsNaN(sd(std::numeric_limits<double>::signaling_NaN())));

    STATIC_REQUIRE_FALSE(phi::IsNaN(sd(0.0)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sd(-0.0)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sd(1.0)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sd(-1.0)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sd(HUGE_VAL)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sd(DBL_MIN / 2.0)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sd(std::numeric_limits<double>::epsilon())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sd(std::numeric_limits<double>::infinity())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sd(-std::numeric_limits<double>::infinity())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sd(std::numeric_limits<double>::min())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sd(std::numeric_limits<double>::max())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sd(std::numeric_limits<double>::lowest())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sd(std::numeric_limits<double>::denorm_min())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sd(std::numeric_limits<double>::round_error())));

    // FloatingPoint<long double>
    CHECK(phi::IsNaN(sl(std::nanl(""))));
    CHECK(phi::IsNaN(sl(std::nanl("0"))));
    CHECK(phi::IsNaN(sl(std::nanl("1"))));
    CHECK(phi::IsNaN(sl(std::nanl("21"))));
#if PHI_HAS_EXTENSION_ALLOW_DIVIDE_BY_ZERO_CONSTANT()
    CHECK(phi::IsNaN(sl(0.0L / 0.0L)));
#endif
    STATIC_REQUIRE(phi::IsNaN(sl(std::numeric_limits<long double>::quiet_NaN())));
    STATIC_REQUIRE(phi::IsNaN(sl(std::numeric_limits<long double>::signaling_NaN())));

    STATIC_REQUIRE_FALSE(phi::IsNaN(sl(0.0L)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sl(-0.0L)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sl(1.0L)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sl(-1.0L)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sl(HUGE_VALL)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sl(LDBL_MIN / 2.0L)));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sl(std::numeric_limits<long double>::epsilon())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sl(std::numeric_limits<long double>::infinity())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sl(-std::numeric_limits<long double>::infinity())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sl(std::numeric_limits<long double>::min())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sl(std::numeric_limits<long double>::max())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sl(std::numeric_limits<long double>::lowest())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sl(std::numeric_limits<long double>::denorm_min())));
    STATIC_REQUIRE_FALSE(phi::IsNaN(sl(std::numeric_limits<long double>::round_error())));

    // Noexcept
    CHECK_NOEXCEPT(phi::IsNaN(std::nanf("")));
    CHECK_NOEXCEPT(phi::IsNaN(std::nan("")));
    CHECK_NOEXCEPT(phi::IsNaN(std::nanl("")));
    CHECK_NOEXCEPT(phi::IsNaN(sf(std::nanf(""))));
    CHECK_NOEXCEPT(phi::IsNaN(sd(std::nan(""))));
    CHECK_NOEXCEPT(phi::IsNaN(sl(std::nanl(""))));
}
