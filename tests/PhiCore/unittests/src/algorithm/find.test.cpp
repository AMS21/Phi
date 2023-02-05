#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/algorithm/at.hpp>
#include <phi/algorithm/find.hpp>
#include <phi/container/array.hpp>
#include <phi/iterator/begin.hpp>
#include <phi/iterator/end.hpp>

TEST_CASE("algorithm.find - c-array")
{
    static constexpr const int array[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    CHECK(phi::find(phi::begin(array), phi::end(array), 0) == phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 0) == phi::begin(array));
    CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 0));

    CHECK(phi::find(phi::begin(array), phi::end(array), 5) == &phi::at(array, 5u));
    EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 5) == &phi::at(array, 5u));
    CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 5));

    CHECK(phi::find(phi::begin(array), phi::end(array), 9) == &phi::at(array, 9u));
    EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 9) == &phi::at(array, 9u));
    CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 9));

    CHECK(phi::find(phi::begin(array), phi::end(array), 10) == phi::end(array));
    EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 10) == phi::end(array));
    CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 10));
}

TEST_CASE("algorithm.find - phi::array")
{
    static constexpr const phi::array<int, 10u> array{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};

    CHECK(phi::find(phi::begin(array), phi::end(array), 0) == phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 0) == phi::begin(array));
    CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 0));

    CHECK(phi::find(phi::begin(array), phi::end(array), 5) == &phi::at(array, 5u));
    EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 5) == &phi::at(array, 5u));
    CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 5));

    CHECK(phi::find(phi::begin(array), phi::end(array), 9) == &phi::at(array, 9u));
    EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 9) == &phi::at(array, 9u));
    CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 9));

    CHECK(phi::find(phi::begin(array), phi::end(array), 10) == phi::end(array));
    EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 10) == phi::end(array));
    CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 10));
}
