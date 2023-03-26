#include <phi/test/test_macros.hpp>

#include <phi/core/floating_point.hpp>
#include <phi/math/is_infinity.hpp>
#include <phi/type_traits/to_unsafe.hpp>
#include <cfloat>
#include <cmath>
#include <limits>

template <typename TypeT>
void test_is_infinity(TypeT val)
{
    CHECK(phi::is_infinity(val));
    CHECK_NOEXCEPT(phi::is_infinity(val));

    // Standard compatibility
    CHECK(std::isinf(phi::to_unsafe(val)));
}

template <typename TypeT>
void test_is_not_infinity(TypeT val)
{
    CHECK_FALSE(phi::is_infinity(val));
    CHECK_NOEXCEPT(phi::is_infinity(val));

    // Standard compatibility
    CHECK_FALSE(std::isinf(phi::to_unsafe(val)));
}

#define STATIC_TEST_IS_INFINITY(val)                                                               \
    STATIC_REQUIRE(phi::is_infinity(val));                                                         \
    CHECK_NOEXCEPT(phi::is_infinity(val));                                                         \
    /* Standard compatibility */                                                                   \
    CHECK(std::isinf(phi::to_unsafe(val)))

#define STATIC_TEST_IS_NOT_INFINITY(val)                                                           \
    STATIC_REQUIRE_FALSE(phi::is_infinity(val));                                                   \
    CHECK_NOEXCEPT(phi::is_infinity(val));                                                         \
    /* Standard compatibility */                                                                   \
    CHECK_FALSE(std::isinf(phi::to_unsafe(val)))

using sf = phi::floating_point<float>;
using sd = phi::floating_point<double>;
using sl = phi::floating_point<long double>;

TEST_CASE("math.is_infinity - float")
{
    STATIC_TEST_IS_INFINITY(INFINITY);
    STATIC_TEST_IS_INFINITY(-INFINITY);
    STATIC_TEST_IS_INFINITY(HUGE_VALF);
    STATIC_TEST_IS_INFINITY(std::numeric_limits<float>::infinity());
    STATIC_TEST_IS_INFINITY(-std::numeric_limits<float>::infinity());

    STATIC_TEST_IS_NOT_INFINITY(0.0f);
    STATIC_TEST_IS_NOT_INFINITY(-0.0f);
    STATIC_TEST_IS_NOT_INFINITY(1.0f);
    STATIC_TEST_IS_NOT_INFINITY(-1.0f);
    STATIC_TEST_IS_NOT_INFINITY(FLT_MIN / 2.0f);
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<float>::quiet_NaN());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<float>::signaling_NaN());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<float>::epsilon());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<float>::min());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<float>::max());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<float>::lowest());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<float>::denorm_min());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<float>::round_error());
}

TEST_CASE("math.is_infinity - double")
{
    STATIC_TEST_IS_INFINITY(std::numeric_limits<double>::infinity());
    STATIC_TEST_IS_INFINITY(-std::numeric_limits<double>::infinity());

    STATIC_TEST_IS_NOT_INFINITY(0.0);
    STATIC_TEST_IS_NOT_INFINITY(-0.0);
    STATIC_TEST_IS_NOT_INFINITY(1.0);
    STATIC_TEST_IS_NOT_INFINITY(-1.0);
    STATIC_TEST_IS_NOT_INFINITY(DBL_MIN / 2.0);
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<double>::quiet_NaN());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<double>::signaling_NaN());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<double>::epsilon());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<double>::min());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<double>::max());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<double>::lowest());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<double>::denorm_min());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<double>::round_error());
}

TEST_CASE("math.is_infinity - long double")
{
    STATIC_TEST_IS_INFINITY(std::numeric_limits<long double>::infinity());
    STATIC_TEST_IS_INFINITY(-std::numeric_limits<long double>::infinity());

    STATIC_TEST_IS_NOT_INFINITY(0.0L);
    STATIC_TEST_IS_NOT_INFINITY(-0.0L);
    STATIC_TEST_IS_NOT_INFINITY(1.0L);
    STATIC_TEST_IS_NOT_INFINITY(-1.0L);
    STATIC_TEST_IS_NOT_INFINITY(LDBL_MIN / 2.0L);
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<long double>::quiet_NaN());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<long double>::signaling_NaN());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<long double>::epsilon());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<long double>::min());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<long double>::max());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<long double>::lowest());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<long double>::denorm_min());
    STATIC_TEST_IS_NOT_INFINITY(std::numeric_limits<long double>::round_error());
}

TEST_CASE("math.is_infinity - floating_point<float>")
{
    STATIC_TEST_IS_INFINITY(sf(INFINITY));
    STATIC_TEST_IS_INFINITY(sf(-INFINITY));
    STATIC_TEST_IS_INFINITY(sf(HUGE_VALF));
    STATIC_TEST_IS_INFINITY(sf(std::numeric_limits<float>::infinity()));
    STATIC_TEST_IS_INFINITY(sf(-std::numeric_limits<float>::infinity()));

    STATIC_TEST_IS_NOT_INFINITY(sf(0.0f));
    STATIC_TEST_IS_NOT_INFINITY(sf(-0.0f));
    STATIC_TEST_IS_NOT_INFINITY(sf(1.0f));
    STATIC_TEST_IS_NOT_INFINITY(sf(-1.0f));
    STATIC_TEST_IS_NOT_INFINITY(sf(FLT_MIN / 2.0f));
    STATIC_TEST_IS_NOT_INFINITY(sf(std::numeric_limits<float>::quiet_NaN()));
    STATIC_TEST_IS_NOT_INFINITY(sf(std::numeric_limits<float>::signaling_NaN()));
    STATIC_TEST_IS_NOT_INFINITY(sf(std::numeric_limits<float>::epsilon()));
    STATIC_TEST_IS_NOT_INFINITY(sf(std::numeric_limits<float>::min()));
    STATIC_TEST_IS_NOT_INFINITY(sf(std::numeric_limits<float>::max()));
    STATIC_TEST_IS_NOT_INFINITY(sf(std::numeric_limits<float>::lowest()));
    STATIC_TEST_IS_NOT_INFINITY(sf(std::numeric_limits<float>::denorm_min()));
    STATIC_TEST_IS_NOT_INFINITY(sf(std::numeric_limits<float>::round_error()));
}

TEST_CASE("math.is_infinity - floating_point<double>")
{
    STATIC_TEST_IS_INFINITY(sd(std::numeric_limits<double>::infinity()));
    STATIC_TEST_IS_INFINITY(sd(-std::numeric_limits<double>::infinity()));

    STATIC_TEST_IS_NOT_INFINITY(sd(0.0));
    STATIC_TEST_IS_NOT_INFINITY(sd(-0.0));
    STATIC_TEST_IS_NOT_INFINITY(sd(1.0));
    STATIC_TEST_IS_NOT_INFINITY(sd(-1.0));
    STATIC_TEST_IS_NOT_INFINITY(sd(DBL_MIN / 2.0));
    STATIC_TEST_IS_NOT_INFINITY(sd(std::numeric_limits<double>::quiet_NaN()));
    STATIC_TEST_IS_NOT_INFINITY(sd(std::numeric_limits<double>::signaling_NaN()));
    STATIC_TEST_IS_NOT_INFINITY(sd(std::numeric_limits<double>::epsilon()));
    STATIC_TEST_IS_NOT_INFINITY(sd(std::numeric_limits<double>::min()));
    STATIC_TEST_IS_NOT_INFINITY(sd(std::numeric_limits<double>::max()));
    STATIC_TEST_IS_NOT_INFINITY(sd(std::numeric_limits<double>::lowest()));
    STATIC_TEST_IS_NOT_INFINITY(sd(std::numeric_limits<double>::denorm_min()));
    STATIC_TEST_IS_NOT_INFINITY(sd(std::numeric_limits<double>::round_error()));
}

TEST_CASE("math.is_infinity - floating_point<long double>")
{
    STATIC_TEST_IS_INFINITY(sl(std::numeric_limits<long double>::infinity()));
    STATIC_TEST_IS_INFINITY(sl(-std::numeric_limits<long double>::infinity()));

    STATIC_TEST_IS_NOT_INFINITY(sl(0.0L));
    STATIC_TEST_IS_NOT_INFINITY(sl(-0.0L));
    STATIC_TEST_IS_NOT_INFINITY(sl(1.0L));
    STATIC_TEST_IS_NOT_INFINITY(sl(-1.0L));
    STATIC_TEST_IS_NOT_INFINITY(sl(LDBL_MIN / 2.0L));
    STATIC_TEST_IS_NOT_INFINITY(sl(std::numeric_limits<long double>::quiet_NaN()));
    STATIC_TEST_IS_NOT_INFINITY(sl(std::numeric_limits<long double>::signaling_NaN()));
    STATIC_TEST_IS_NOT_INFINITY(sl(std::numeric_limits<long double>::epsilon()));
    STATIC_TEST_IS_NOT_INFINITY(sl(std::numeric_limits<long double>::min()));
    STATIC_TEST_IS_NOT_INFINITY(sl(std::numeric_limits<long double>::max()));
    STATIC_TEST_IS_NOT_INFINITY(sl(std::numeric_limits<long double>::lowest()));
    STATIC_TEST_IS_NOT_INFINITY(sl(std::numeric_limits<long double>::denorm_min()));
    STATIC_TEST_IS_NOT_INFINITY(sl(std::numeric_limits<long double>::round_error()));
}
