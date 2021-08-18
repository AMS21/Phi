#include <catch2/catch_template_test_macros.hpp>

#include <Phi/Math/Signum.hpp>
#include <cstdint>
#include <limits>

TEMPLATE_TEST_CASE("signum signed", "[Math][Signum]", char, signed char, short, int, long,
                   long long)
{
    STATIC_REQUIRE(bool(phi::signum(static_cast<TestType>(0)) == 0));
    STATIC_REQUIRE(bool(phi::signum(static_cast<TestType>(-1)) == -1));
    STATIC_REQUIRE(bool(phi::signum(static_cast<TestType>(1)) == 1));
    STATIC_REQUIRE(bool(phi::signum(static_cast<TestType>(21)) == 1));
    STATIC_REQUIRE(bool(phi::signum(static_cast<TestType>(-21)) == -1));
    STATIC_REQUIRE(
            bool(phi::signum(static_cast<TestType>(std::numeric_limits<TestType>::max())) == 1));
    STATIC_REQUIRE(
            bool(phi::signum(static_cast<TestType>(std::numeric_limits<TestType>::min())) == -1));
}

TEMPLATE_TEST_CASE("signum unsigned", "[Math][Signum]", unsigned char, unsigned short, unsigned,
                   unsigned long, unsigned long long, char16_t, char32_t)
{
    STATIC_REQUIRE(bool(phi::signum(static_cast<TestType>(0)) == 0));
    STATIC_REQUIRE(bool(phi::signum(static_cast<TestType>(1)) == 1));
    STATIC_REQUIRE(bool(phi::signum(static_cast<TestType>(21)) == 1));
    STATIC_REQUIRE(
            bool(phi::signum(static_cast<TestType>(std::numeric_limits<TestType>::max())) == 1));
    STATIC_REQUIRE(
            bool(phi::signum(static_cast<TestType>(std::numeric_limits<TestType>::min())) == 0));
}

TEMPLATE_TEST_CASE("signum floating point", "[Math][Signum]", float, double, long double)
{
    STATIC_REQUIRE(bool(phi::signum(static_cast<TestType>(0.0)) == 0));
    STATIC_REQUIRE(bool(phi::signum(static_cast<TestType>(-0.0)) == 0));
    STATIC_REQUIRE(bool(phi::signum(static_cast<TestType>(-1.0)) == -1));
    STATIC_REQUIRE(bool(phi::signum(static_cast<TestType>(1.0)) == 1));
    STATIC_REQUIRE(bool(phi::signum(static_cast<TestType>(21.0)) == 1));
    STATIC_REQUIRE(bool(phi::signum(static_cast<TestType>(-21.0)) == -1));
    STATIC_REQUIRE(
            bool(phi::signum(static_cast<TestType>(std::numeric_limits<TestType>::max())) == 1));
    STATIC_REQUIRE(
            bool(phi::signum(static_cast<TestType>(std::numeric_limits<TestType>::min())) == 1));
    STATIC_REQUIRE(bool(
            phi::signum(static_cast<TestType>(std::numeric_limits<TestType>::lowest())) == -1));
}
