#include <phi/test/test_macros.hpp>

#include <phi/core/floating_point.hpp>
#include <phi/math/floor.hpp>

TEST_CASE("math.floor - float")
{
    STATIC_REQUIRE(phi::floor(0.0f) == 0);
    STATIC_REQUIRE(phi::floor(0.499999f) == 0);
    STATIC_REQUIRE(phi::floor(0.5f) == 0);
    STATIC_REQUIRE(phi::floor(0.99999f) == 0);
    STATIC_REQUIRE(phi::floor(1.0f) == 1);
    STATIC_REQUIRE(phi::floor(123.0f) == 123);
    STATIC_REQUIRE(phi::floor(123.4f) == 123);

    STATIC_REQUIRE(phi::floor(-0.0f) == 0);
    STATIC_REQUIRE(phi::floor(-0.499999f) == -1);
    STATIC_REQUIRE(phi::floor(-0.5f) == -1);
    STATIC_REQUIRE(phi::floor(-0.99999f) == -1);
    STATIC_REQUIRE(phi::floor(-1.0f) == -1);
    STATIC_REQUIRE(phi::floor(-123.0f) == -123);
    STATIC_REQUIRE(phi::floor(-123.4f) == -124);
}

TEST_CASE("math.floor - double")
{
    STATIC_REQUIRE(phi::floor(0.0) == 0);
    STATIC_REQUIRE(phi::floor(0.499999) == 0);
    STATIC_REQUIRE(phi::floor(0.5) == 0);
    STATIC_REQUIRE(phi::floor(0.99999) == 0);
    STATIC_REQUIRE(phi::floor(1.0) == 1);
    STATIC_REQUIRE(phi::floor(123.0) == 123);
    STATIC_REQUIRE(phi::floor(123.4) == 123);

    STATIC_REQUIRE(phi::floor(-0.0) == 0);
    STATIC_REQUIRE(phi::floor(-0.499999) == -1);
    STATIC_REQUIRE(phi::floor(-0.5) == -1);
    STATIC_REQUIRE(phi::floor(-0.99999) == -1);
    STATIC_REQUIRE(phi::floor(-1.0) == -1);
    STATIC_REQUIRE(phi::floor(-123.0) == -123);
    STATIC_REQUIRE(phi::floor(-123.4) == -124);
}

TEST_CASE("math.floor - long double")
{
    STATIC_REQUIRE(phi::floor(0.0l) == 0);
    STATIC_REQUIRE(phi::floor(0.499999l) == 0);
    STATIC_REQUIRE(phi::floor(0.5l) == 0);
    STATIC_REQUIRE(phi::floor(0.99999l) == 0);
    STATIC_REQUIRE(phi::floor(1.0l) == 1);
    STATIC_REQUIRE(phi::floor(123.0l) == 123);
    STATIC_REQUIRE(phi::floor(123.4l) == 123);

    STATIC_REQUIRE(phi::floor(-0.0l) == 0);
    STATIC_REQUIRE(phi::floor(-0.499999l) == -1);
    STATIC_REQUIRE(phi::floor(-0.5) == -1);
    STATIC_REQUIRE(phi::floor(-0.99999l) == -1);
    STATIC_REQUIRE(phi::floor(-1.0l) == -1);
    STATIC_REQUIRE(phi::floor(-123.0l) == -123);
    STATIC_REQUIRE(phi::floor(-123.4l) == -124);
}

TEST_CASE("math.floor - floating_point<float>")
{
    using sf = phi::floating_point<float>;

    STATIC_REQUIRE(phi::floor(sf(0.0f)) == 0);
    STATIC_REQUIRE(phi::floor(sf(0.499999f)) == 0);
    STATIC_REQUIRE(phi::floor(sf(0.5f)) == 0);
    STATIC_REQUIRE(phi::floor(sf(0.99999f)) == 0);
    STATIC_REQUIRE(phi::floor(sf(1.0f)) == 1);
    STATIC_REQUIRE(phi::floor(sf(123.0f)) == 123);
    STATIC_REQUIRE(phi::floor(sf(123.4f)) == 123);

    STATIC_REQUIRE(phi::floor(sf(-0.0f)) == 0);
    STATIC_REQUIRE(phi::floor(sf(-0.499999f)) == -1);
    STATIC_REQUIRE(phi::floor(sf(-0.5f)) == -1);
    STATIC_REQUIRE(phi::floor(sf(-0.99999f)) == -1);
    STATIC_REQUIRE(phi::floor(sf(-1.0f)) == -1);
    STATIC_REQUIRE(phi::floor(sf(-123.0f)) == -123);
    STATIC_REQUIRE(phi::floor(sf(-123.4f)) == -124);
}

TEST_CASE("math.floor - floating_point<double>")
{
    using sf = phi::floating_point<double>;

    STATIC_REQUIRE(phi::floor(sf(0.0)) == 0);
    STATIC_REQUIRE(phi::floor(sf(0.499999)) == 0);
    STATIC_REQUIRE(phi::floor(sf(0.5)) == 0);
    STATIC_REQUIRE(phi::floor(sf(0.99999)) == 0);
    STATIC_REQUIRE(phi::floor(sf(1.0)) == 1);
    STATIC_REQUIRE(phi::floor(sf(123.0)) == 123);
    STATIC_REQUIRE(phi::floor(sf(123.4)) == 123);

    STATIC_REQUIRE(phi::floor(sf(-0.0)) == 0);
    STATIC_REQUIRE(phi::floor(sf(-0.499999)) == -1);
    STATIC_REQUIRE(phi::floor(sf(-0.5)) == -1);
    STATIC_REQUIRE(phi::floor(sf(-0.99999)) == -1);
    STATIC_REQUIRE(phi::floor(sf(-1.0)) == -1);
    STATIC_REQUIRE(phi::floor(sf(-123.0)) == -123);
    STATIC_REQUIRE(phi::floor(sf(-123.4)) == -124);
}

TEST_CASE("math.floor - floating_point<long double>")
{
    using sf = phi::floating_point<long double>;

    STATIC_REQUIRE(phi::floor(sf(0.0l)) == 0);
    STATIC_REQUIRE(phi::floor(sf(0.499999l)) == 0);
    STATIC_REQUIRE(phi::floor(sf(0.5l)) == 0);
    STATIC_REQUIRE(phi::floor(sf(0.99999l)) == 0);
    STATIC_REQUIRE(phi::floor(sf(1.0l)) == 1);
    STATIC_REQUIRE(phi::floor(sf(123.0l)) == 123);
    STATIC_REQUIRE(phi::floor(sf(123.4l)) == 123);

    STATIC_REQUIRE(phi::floor(sf(-0.0l)) == 0);
    STATIC_REQUIRE(phi::floor(sf(-0.499999l)) == -1);
    STATIC_REQUIRE(phi::floor(sf(-0.5l)) == -1);
    STATIC_REQUIRE(phi::floor(sf(-0.99999l)) == -1);
    STATIC_REQUIRE(phi::floor(sf(-1.0l)) == -1);
    STATIC_REQUIRE(phi::floor(sf(-123.0l)) == -123);
    STATIC_REQUIRE(phi::floor(sf(-123.4l)) == -124);
}
