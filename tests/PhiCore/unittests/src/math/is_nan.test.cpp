#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/features.hpp>
#include <phi/compiler_support/platform.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/math/is_nan.hpp>
#include <phi/type_traits/to_safe.hpp>
#include <phi/type_traits/to_unsafe.hpp>
#include <cfloat>
#include <cmath>
#include <limits>

template <typename T>
void test_is_nan(T val)
{
    CHECK(phi::is_nan(val));

    // Standard compatibility
    CHECK(std::isnan(phi::to_unsafe(val)));
}

using sf = phi::floating_point<float>;
using sd = phi::floating_point<double>;
using sl = phi::floating_point<long double>;

TEST_CASE("is_nan")
{
    // Test if the compiler floats support NaN values
    // See godbolt link for an example: https://godbolt.org/z/vWM8zdn97
    volatile float n1 = NAN;
    if (n1 == n1 || !std::numeric_limits<float>::has_quiet_NaN ||
        !std::numeric_limits<float>::has_signaling_NaN)
    {
        return;
    }

    // Float
    test_is_nan(std::nanf(""));
    test_is_nan(std::nanf("0"));
    test_is_nan(std::nanf("1"));
    test_is_nan(std::nanf("21"));
#if PHI_HAS_EXTENSION_ALLOW_DIVIDE_BY_ZERO_CONSTANT()
    test_is_nan(0.0f / 0.0f);
#endif
    test_is_nan(INFINITY - INFINITY);
    test_is_nan(INFINITY * 0.0f);
    test_is_nan(std::numeric_limits<float>::infinity() * 0.0f);
#if PHI_PLATFORM_IS(WINDOWS)
    test_is_nan(phi::is_nan(NAN));
#else
    STATIC_REQUIRE(phi::is_nan(NAN));
#endif
    STATIC_REQUIRE(phi::is_nan(std::numeric_limits<float>::quiet_NaN()));
    STATIC_REQUIRE(phi::is_nan(std::numeric_limits<float>::signaling_NaN()));

    STATIC_REQUIRE_FALSE(phi::is_nan(0.0f));
    STATIC_REQUIRE_FALSE(phi::is_nan(-0.0f));
    STATIC_REQUIRE_FALSE(phi::is_nan(1.0f));
    STATIC_REQUIRE_FALSE(phi::is_nan(-1.0f));
    STATIC_REQUIRE_FALSE(phi::is_nan(INFINITY));
    STATIC_REQUIRE_FALSE(phi::is_nan(-INFINITY));
    STATIC_REQUIRE_FALSE(phi::is_nan(HUGE_VALF));
    STATIC_REQUIRE_FALSE(phi::is_nan(FLT_MIN / 2.0f));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<float>::epsilon()));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<float>::infinity()));
    STATIC_REQUIRE_FALSE(phi::is_nan(-std::numeric_limits<float>::infinity()));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<float>::min()));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<float>::max()));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<float>::lowest()));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<float>::denorm_min()));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<float>::round_error()));

    // double
    test_is_nan(std::nan(""));
    test_is_nan(std::nan("0"));
    test_is_nan(std::nan("1"));
    test_is_nan(std::nan("21"));
#if PHI_HAS_EXTENSION_ALLOW_DIVIDE_BY_ZERO_CONSTANT()
    test_is_nan(0.0 / 0.0);
#endif
    test_is_nan(std::numeric_limits<double>::infinity() * 0.0);
    STATIC_REQUIRE(phi::is_nan(std::numeric_limits<double>::quiet_NaN()));
    STATIC_REQUIRE(phi::is_nan(std::numeric_limits<double>::signaling_NaN()));

    STATIC_REQUIRE_FALSE(phi::is_nan(0.0));
    STATIC_REQUIRE_FALSE(phi::is_nan(-0.0));
    STATIC_REQUIRE_FALSE(phi::is_nan(1.0));
    STATIC_REQUIRE_FALSE(phi::is_nan(-1.0));
    STATIC_REQUIRE_FALSE(phi::is_nan(HUGE_VAL));
    STATIC_REQUIRE_FALSE(phi::is_nan(DBL_MIN / 2.0));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<double>::epsilon()));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<double>::infinity()));
    STATIC_REQUIRE_FALSE(phi::is_nan(-std::numeric_limits<double>::infinity()));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<double>::min()));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<double>::max()));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<double>::lowest()));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<double>::denorm_min()));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<double>::round_error()));

    // long double
    test_is_nan(std::nanl(""));
    test_is_nan(std::nanl("0"));
    test_is_nan(std::nanl("1"));
    test_is_nan(std::nanl("21"));
#if PHI_HAS_EXTENSION_ALLOW_DIVIDE_BY_ZERO_CONSTANT()
    test_is_nan(0.0L / 0.0L);
#endif
    test_is_nan(std::numeric_limits<long double>::infinity() * 0.0L);
    STATIC_REQUIRE(phi::is_nan(std::numeric_limits<long double>::quiet_NaN()));
    STATIC_REQUIRE(phi::is_nan(std::numeric_limits<long double>::signaling_NaN()));

    STATIC_REQUIRE_FALSE(phi::is_nan(0.0L));
    STATIC_REQUIRE_FALSE(phi::is_nan(-0.0L));
    STATIC_REQUIRE_FALSE(phi::is_nan(1.0L));
    STATIC_REQUIRE_FALSE(phi::is_nan(-1.0L));
    STATIC_REQUIRE_FALSE(phi::is_nan(HUGE_VALL));
    STATIC_REQUIRE_FALSE(phi::is_nan(LDBL_MIN / 2.0L));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<long double>::epsilon()));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<long double>::infinity()));
    STATIC_REQUIRE_FALSE(phi::is_nan(-std::numeric_limits<long double>::infinity()));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<long double>::min()));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<long double>::max()));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<long double>::lowest()));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<long double>::denorm_min()));
    STATIC_REQUIRE_FALSE(phi::is_nan(std::numeric_limits<long double>::round_error()));

    // floating_point<float>
    test_is_nan(sf(std::nanf("")));
    test_is_nan(sf(std::nanf("0")));
    test_is_nan(sf(std::nanf("1")));
    test_is_nan(sf(std::nanf("21")));
#if PHI_HAS_EXTENSION_ALLOW_DIVIDE_BY_ZERO_CONSTANT()
    test_is_nan(sf(0.0f / 0.0f));
#endif
    test_is_nan(sf(INFINITY - INFINITY));
    test_is_nan(sf(NAN));
    test_is_nan(sf(INFINITY) * sf(0.0f));
    test_is_nan(std::numeric_limits<sf>::infinity() * sf(0.0f));
    STATIC_REQUIRE(phi::is_nan(sf(std::numeric_limits<float>::quiet_NaN())));
    STATIC_REQUIRE(phi::is_nan(sf(std::numeric_limits<float>::signaling_NaN())));

    STATIC_REQUIRE_FALSE(phi::is_nan(sf(0.0f)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sf(-0.0f)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sf(1.0f)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sf(-1.0f)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sf(INFINITY)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sf(-INFINITY)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sf(HUGE_VALF)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sf(FLT_MIN / 2.0f)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sf(std::numeric_limits<float>::epsilon())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sf(std::numeric_limits<float>::infinity())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sf(-std::numeric_limits<float>::infinity())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sf(std::numeric_limits<float>::min())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sf(std::numeric_limits<float>::max())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sf(std::numeric_limits<float>::lowest())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sf(std::numeric_limits<float>::denorm_min())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sf(std::numeric_limits<float>::round_error())));

    // floating_point<double>
    test_is_nan(sd(std::nan("")));
    test_is_nan(sd(std::nan("0")));
    test_is_nan(sd(std::nan("1")));
    test_is_nan(sd(std::nan("21")));
#if PHI_HAS_EXTENSION_ALLOW_DIVIDE_BY_ZERO_CONSTANT()
    test_is_nan(sd(0.0 / 0.0));
#endif
    test_is_nan(std::numeric_limits<sd>::infinity() * sd(0.0));
    STATIC_REQUIRE(phi::is_nan(sd(std::numeric_limits<double>::quiet_NaN())));
    STATIC_REQUIRE(phi::is_nan(sd(std::numeric_limits<double>::signaling_NaN())));

    STATIC_REQUIRE_FALSE(phi::is_nan(sd(0.0)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sd(-0.0)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sd(1.0)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sd(-1.0)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sd(HUGE_VAL)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sd(DBL_MIN / 2.0)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sd(std::numeric_limits<double>::epsilon())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sd(std::numeric_limits<double>::infinity())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sd(-std::numeric_limits<double>::infinity())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sd(std::numeric_limits<double>::min())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sd(std::numeric_limits<double>::max())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sd(std::numeric_limits<double>::lowest())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sd(std::numeric_limits<double>::denorm_min())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sd(std::numeric_limits<double>::round_error())));

    // floating_point<long double>
    test_is_nan(sl(std::nanl("")));
    test_is_nan(sl(std::nanl("0")));
    test_is_nan(sl(std::nanl("1")));
    test_is_nan(sl(std::nanl("21")));
#if PHI_HAS_EXTENSION_ALLOW_DIVIDE_BY_ZERO_CONSTANT()
    test_is_nan(sl(0.0L / 0.0L));
#endif
    test_is_nan(std::numeric_limits<sl>::infinity() * sl(0.0L));
    STATIC_REQUIRE(phi::is_nan(sl(std::numeric_limits<long double>::quiet_NaN())));
    STATIC_REQUIRE(phi::is_nan(sl(std::numeric_limits<long double>::signaling_NaN())));

    STATIC_REQUIRE_FALSE(phi::is_nan(sl(0.0L)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sl(-0.0L)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sl(1.0L)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sl(-1.0L)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sl(HUGE_VALL)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sl(LDBL_MIN / 2.0L)));
    STATIC_REQUIRE_FALSE(phi::is_nan(sl(std::numeric_limits<long double>::epsilon())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sl(std::numeric_limits<long double>::infinity())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sl(-std::numeric_limits<long double>::infinity())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sl(std::numeric_limits<long double>::min())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sl(std::numeric_limits<long double>::max())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sl(std::numeric_limits<long double>::lowest())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sl(std::numeric_limits<long double>::denorm_min())));
    STATIC_REQUIRE_FALSE(phi::is_nan(sl(std::numeric_limits<long double>::round_error())));

    // Noexcept
    CHECK_NOEXCEPT(phi::is_nan(std::nanf("")));
    CHECK_NOEXCEPT(phi::is_nan(std::nan("")));
    CHECK_NOEXCEPT(phi::is_nan(std::nanl("")));
    CHECK_NOEXCEPT(phi::is_nan(sf(std::nanf(""))));
    CHECK_NOEXCEPT(phi::is_nan(sd(std::nan(""))));
    CHECK_NOEXCEPT(phi::is_nan(sl(std::nanl(""))));
}
