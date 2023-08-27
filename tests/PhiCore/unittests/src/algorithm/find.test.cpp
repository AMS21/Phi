#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/algorithm/at.hpp>
#include <phi/algorithm/find.hpp>
#include <phi/container/array.hpp>
#include <phi/iterator/begin.hpp>
#include <phi/iterator/end.hpp>

TEST_CASE("algorithm.find - c-array")
{
    // first == last
    {
        static constexpr const int array[1]{0};

        CHECK(phi::find(phi::end(array), phi::end(array), 0) == phi::end(array));
        EXT_STATIC_REQUIRE(phi::find(phi::end(array), phi::end(array), 0) == phi::end(array));
        CHECK_NOEXCEPT(phi::find(phi::end(array), phi::end(array), 0));

        CHECK(phi::find(phi::begin(array), phi::begin(array), 0) == phi::begin(array));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::begin(array), 0) == phi::begin(array));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::begin(array), 0));
    }

    // Size 1
    {
        static constexpr const int array[1]{0};

        CHECK(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 0));

        CHECK(phi::find(phi::begin(array), phi::end(array), 1) == phi::end(array));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 1) == phi::end(array));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 1));
    }

    // Size 2
    {
        static constexpr const int array[2]{0, 1};

        CHECK(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 0));

        CHECK(phi::find(phi::begin(array), phi::end(array), 1) == &phi::at(array, 1u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 1) == &phi::at(array, 1u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 1));

        CHECK(phi::find(phi::begin(array), phi::end(array), 2) == phi::end(array));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 2) == phi::end(array));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 2));
    }

    {
        static constexpr const int array[2]{0, 0};

        CHECK(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 0));

        CHECK(phi::find(phi::begin(array), phi::end(array), 1) == phi::end(array));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 1) == phi::end(array));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 1));
    }

    // Size 3
    {
        static constexpr const int array[3]{0, 1, 2};

        CHECK(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 0));

        CHECK(phi::find(phi::begin(array), phi::end(array), 1) == &phi::at(array, 1u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 1) == &phi::at(array, 1u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 1));

        CHECK(phi::find(phi::begin(array), phi::end(array), 2) == &phi::at(array, 2u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 2) == &phi::at(array, 2u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 2));

        CHECK(phi::find(phi::begin(array), phi::end(array), 3) == phi::end(array));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 3) == phi::end(array));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 3));
    }

    {
        static constexpr const int array[3]{0, 1, 0};

        CHECK(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 0));

        CHECK(phi::find(phi::begin(array), phi::end(array), 1) == &phi::at(array, 1u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 1) == &phi::at(array, 1u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 1));

        CHECK(phi::find(phi::begin(array), phi::end(array), 2) == phi::end(array));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 2) == phi::end(array));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 2));
    }

    {
        static constexpr const int array[3]{0, 0, 1};

        CHECK(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 0));

        CHECK(phi::find(phi::begin(array), phi::end(array), 1) == &phi::at(array, 2u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 1) == &phi::at(array, 2u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 1));

        CHECK(phi::find(phi::begin(array), phi::end(array), 2) == phi::end(array));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 2) == phi::end(array));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 2));
    }

    {
        static constexpr const int array[3]{0, 0, 0};

        CHECK(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 0));

        CHECK(phi::find(phi::begin(array), phi::end(array), 1) == phi::end(array));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 1) == phi::end(array));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 1));
    }
}

TEST_CASE("algorithm.find - phi::array")
{
    // first == last
    {
        static constexpr const phi::array<int, 1u> array{0};

        CHECK(phi::find(phi::end(array), phi::end(array), 0) == phi::end(array));
        EXT_STATIC_REQUIRE(phi::find(phi::end(array), phi::end(array), 0) == phi::end(array));
        CHECK_NOEXCEPT(phi::find(phi::end(array), phi::end(array), 0));

        CHECK(phi::find(phi::begin(array), phi::begin(array), 0) == phi::begin(array));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::begin(array), 0) == phi::begin(array));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::begin(array), 0));
    }

    // Size 0
    {
        static constexpr const phi::array<int, 0u> array;

        CHECK(phi::find(array.begin(), array.end(), 0) == array.end());
        EXT_STATIC_REQUIRE(phi::find(array.begin(), array.end(), 0) == array.end());
        CHECK_NOEXCEPT(phi::find(array.begin(), array.end(), 0));
    }

    // Size 1
    {
        static constexpr const phi::array<int, 1u> array{0};

        CHECK(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 0));

        CHECK(phi::find(phi::begin(array), phi::end(array), 1) == phi::end(array));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 1) == phi::end(array));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 1));
    }

    // Size 2
    {
        static constexpr const phi::array<int, 2u> array{0, 1};

        CHECK(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 0));

        CHECK(phi::find(phi::begin(array), phi::end(array), 1) == &phi::at(array, 1u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 1) == &phi::at(array, 1u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 1));

        CHECK(phi::find(phi::begin(array), phi::end(array), 2) == phi::end(array));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 2) == phi::end(array));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 2));
    }

    {
        static constexpr const phi::array<int, 2u> array{0, 0};

        CHECK(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 0));

        CHECK(phi::find(phi::begin(array), phi::end(array), 1) == phi::end(array));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 1) == phi::end(array));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 1));
    }

    // Size 3
    {
        static constexpr const phi::array<int, 3u> array{0, 1, 2};

        CHECK(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 0));

        CHECK(phi::find(phi::begin(array), phi::end(array), 1) == &phi::at(array, 1u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 1) == &phi::at(array, 1u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 1));

        CHECK(phi::find(phi::begin(array), phi::end(array), 2) == &phi::at(array, 2u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 2) == &phi::at(array, 2u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 2));

        CHECK(phi::find(phi::begin(array), phi::end(array), 3) == phi::end(array));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 3) == phi::end(array));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 3));
    }

    {
        static constexpr const phi::array<int, 3u> array{0, 1, 0};

        CHECK(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 0));

        CHECK(phi::find(phi::begin(array), phi::end(array), 1) == &phi::at(array, 1u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 1) == &phi::at(array, 1u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 1));

        CHECK(phi::find(phi::begin(array), phi::end(array), 2) == phi::end(array));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 2) == phi::end(array));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 2));
    }

    {
        static constexpr const phi::array<int, 3u> array{0, 0, 1};

        CHECK(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 0));

        CHECK(phi::find(phi::begin(array), phi::end(array), 1) == &phi::at(array, 2u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 1) == &phi::at(array, 2u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 1));

        CHECK(phi::find(phi::begin(array), phi::end(array), 2) == phi::end(array));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 2) == phi::end(array));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 2));
    }

    {
        static constexpr const phi::array<int, 3u> array{0, 0, 0};

        CHECK(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 0) == &phi::at(array, 0u));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 0));

        CHECK(phi::find(phi::begin(array), phi::end(array), 1) == phi::end(array));
        EXT_STATIC_REQUIRE(phi::find(phi::begin(array), phi::end(array), 1) == phi::end(array));
        CHECK_NOEXCEPT(phi::find(phi::begin(array), phi::end(array), 1));
    }
}
