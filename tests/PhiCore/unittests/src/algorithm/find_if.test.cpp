#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/algorithm/at.hpp>
#include <phi/algorithm/find_if.hpp>
#include <phi/container/array.hpp>
#include <phi/iterator/begin.hpp>
#include <phi/iterator/end.hpp>

static constexpr const auto lambda_eq0   = [](const int& value) noexcept { return value == 0; };
static constexpr const auto lambda_eq1   = [](const int& value) noexcept { return value == 1; };
static constexpr const auto lambda_eq9   = [](const int& value) noexcept { return value == 9; };
static constexpr const auto lambda_eq10  = [](const int& value) noexcept { return value == 10; };
static constexpr const auto lambda_even  = [](const int& value) noexcept { return value % 2 == 0; };
static constexpr const auto lambda_odd   = [](const int& value) noexcept { return value % 2 == 1; };
static constexpr const auto lambda_true  = [](const int& /*value*/) noexcept { return true; };
static constexpr const auto lambda_false = [](const int& /*value*/) noexcept { return false; };
static constexpr const auto lambda_false_throw = [](const int& /*value*/) -> bool { throw ""; };

TEST_CASE("algorithm.find_if - c-array")
{
    static constexpr const int array[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Runtime
    CHECK(phi::find_if(phi::begin(array), phi::end(array), lambda_eq0) == phi::begin(array));
    CHECK(phi::find_if(phi::begin(array), phi::end(array), lambda_eq1) == &phi::at(array, 1u));
    CHECK(phi::find_if(phi::begin(array), phi::end(array), lambda_eq9) == &phi::at(array, 9u));
    CHECK(phi::find_if(phi::begin(array), phi::end(array), lambda_eq10) == phi::end(array));
    CHECK(phi::find_if(phi::begin(array), phi::end(array), lambda_even) == &phi::at(array, 0u));
    CHECK(phi::find_if(phi::begin(array), phi::end(array), lambda_odd) == &phi::at(array, 1u));
    CHECK(phi::find_if(phi::begin(array), phi::end(array), lambda_true) == &phi::at(array, 0u));
    CHECK(phi::find_if(phi::begin(array), phi::end(array), lambda_false) == phi::end(array));

    // Constexpr
    EXT_STATIC_REQUIRE(phi::find_if(phi::begin(array), phi::end(array), lambda_eq0) ==
                       phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find_if(phi::begin(array), phi::end(array), lambda_eq1) ==
                       &phi::at(array, 1u));
    EXT_STATIC_REQUIRE(phi::find_if(phi::begin(array), phi::end(array), lambda_eq9) ==
                       &phi::at(array, 9u));
    EXT_STATIC_REQUIRE(phi::find_if(phi::begin(array), phi::end(array), lambda_eq10) ==
                       phi::end(array));
    EXT_STATIC_REQUIRE(phi::find_if(phi::begin(array), phi::end(array), lambda_even) ==
                       &phi::at(array, 0u));
    EXT_STATIC_REQUIRE(phi::find_if(phi::begin(array), phi::end(array), lambda_odd) ==
                       &phi::at(array, 1u));
    EXT_STATIC_REQUIRE(phi::find_if(phi::begin(array), phi::end(array), lambda_true) ==
                       &phi::at(array, 0u));
    EXT_STATIC_REQUIRE(phi::find_if(phi::begin(array), phi::end(array), lambda_false) ==
                       phi::end(array));

    // Noexcept
    CHECK_NOEXCEPT(phi::find_if(phi::begin(array), phi::end(array), lambda_eq0));
    CHECK_NOEXCEPT(phi::find_if(phi::begin(array), phi::end(array), lambda_eq1));
    CHECK_NOEXCEPT(phi::find_if(phi::begin(array), phi::end(array), lambda_eq9));
    CHECK_NOEXCEPT(phi::find_if(phi::begin(array), phi::end(array), lambda_eq10));
    CHECK_NOEXCEPT(phi::find_if(phi::begin(array), phi::end(array), lambda_even));
    CHECK_NOEXCEPT(phi::find_if(phi::begin(array), phi::end(array), lambda_odd));
    CHECK_NOEXCEPT(phi::find_if(phi::begin(array), phi::end(array), lambda_true));
    CHECK_NOEXCEPT(phi::find_if(phi::begin(array), phi::end(array), lambda_false));
    CHECK_NOT_NOEXCEPT(phi::find_if(phi::begin(array), phi::end(array), lambda_false_throw));
}

TEST_CASE("algorithm.find_if - phi::array")
{
    static constexpr const phi::array<int, 10u> array{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};

    // Runtime
    CHECK(phi::find_if(phi::begin(array), phi::end(array), lambda_eq0) == phi::begin(array));
    CHECK(phi::find_if(phi::begin(array), phi::end(array), lambda_eq1) == &phi::at(array, 1u));
    CHECK(phi::find_if(phi::begin(array), phi::end(array), lambda_eq9) == &phi::at(array, 9u));
    CHECK(phi::find_if(phi::begin(array), phi::end(array), lambda_eq10) == phi::end(array));
    CHECK(phi::find_if(phi::begin(array), phi::end(array), lambda_even) == &phi::at(array, 0u));
    CHECK(phi::find_if(phi::begin(array), phi::end(array), lambda_odd) == &phi::at(array, 1u));
    CHECK(phi::find_if(phi::begin(array), phi::end(array), lambda_true) == &phi::at(array, 0u));
    CHECK(phi::find_if(phi::begin(array), phi::end(array), lambda_false) == phi::end(array));

    // Constexpr
    EXT_STATIC_REQUIRE(phi::find_if(phi::begin(array), phi::end(array), lambda_eq0) ==
                       phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find_if(phi::begin(array), phi::end(array), lambda_eq1) ==
                       &phi::at(array, 1u));
    EXT_STATIC_REQUIRE(phi::find_if(phi::begin(array), phi::end(array), lambda_eq9) ==
                       &phi::at(array, 9u));
    EXT_STATIC_REQUIRE(phi::find_if(phi::begin(array), phi::end(array), lambda_eq10) ==
                       phi::end(array));
    EXT_STATIC_REQUIRE(phi::find_if(phi::begin(array), phi::end(array), lambda_even) ==
                       &phi::at(array, 0u));
    EXT_STATIC_REQUIRE(phi::find_if(phi::begin(array), phi::end(array), lambda_odd) ==
                       &phi::at(array, 1u));
    EXT_STATIC_REQUIRE(phi::find_if(phi::begin(array), phi::end(array), lambda_true) ==
                       &phi::at(array, 0u));
    EXT_STATIC_REQUIRE(phi::find_if(phi::begin(array), phi::end(array), lambda_false) ==
                       phi::end(array));

    // Noexcept
    CHECK_NOEXCEPT(phi::find_if(phi::begin(array), phi::end(array), lambda_eq0));
    CHECK_NOEXCEPT(phi::find_if(phi::begin(array), phi::end(array), lambda_eq1));
    CHECK_NOEXCEPT(phi::find_if(phi::begin(array), phi::end(array), lambda_eq9));
    CHECK_NOEXCEPT(phi::find_if(phi::begin(array), phi::end(array), lambda_eq10));
    CHECK_NOEXCEPT(phi::find_if(phi::begin(array), phi::end(array), lambda_even));
    CHECK_NOEXCEPT(phi::find_if(phi::begin(array), phi::end(array), lambda_odd));
    CHECK_NOEXCEPT(phi::find_if(phi::begin(array), phi::end(array), lambda_true));
    CHECK_NOEXCEPT(phi::find_if(phi::begin(array), phi::end(array), lambda_false));
    CHECK_NOT_NOEXCEPT(phi::find_if(phi::begin(array), phi::end(array), lambda_false_throw));
}
