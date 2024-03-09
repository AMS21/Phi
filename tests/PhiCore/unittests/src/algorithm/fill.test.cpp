#include <phi/test/test_macros.hpp>

#include <phi/algorithm/at.hpp>
#include <phi/algorithm/fill.hpp>
#include <phi/compiler_support/constexpr.hpp>
#include <phi/container/array.hpp>
#include <phi/core/assert.hpp>
#include <phi/iterator/begin.hpp>
#include <phi/iterator/end.hpp>

PHI_EXTENDED_CONSTEXPR bool test_fill_constexpr()
{
    int array[3]{0, 1, 2};

    phi::fill(phi::begin(array), phi::end(array), -1);

    PHI_RELEASE_ASSERT(phi::at(array, 0u) == -1, "phi::at(array, 0u) == -1");
    PHI_RELEASE_ASSERT(phi::at(array, 1u) == -1, "phi::at(array, 1u) == -1");
    PHI_RELEASE_ASSERT(phi::at(array, 2u) == -1, "phi::at(array, 2u) == -1");

    return true;
}

TEST_CASE("algorithm.fill - c-array")
{
    int array[3]{0, 1, 2};

    phi::fill(phi::begin(array), phi::end(array), -1);
    CHECK_NOEXCEPT(phi::fill(phi::begin(array), phi::end(array), -1));

    CHECK(phi::at(array, 0u) == -1);
    CHECK(phi::at(array, 1u) == -1);
    CHECK(phi::at(array, 2u) == -1);

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    test_fill_constexpr();
#endif
}

TEST_CASE("algorithm.fill - phi::array")
{
    phi::array<int, 3u> array{0, 1, 2};

    phi::fill(phi::begin(array), phi::end(array), -1);
    CHECK_NOEXCEPT(phi::fill(phi::begin(array), phi::end(array), -1));

    CHECK(phi::at(array, 0u) == -1);
    CHECK(phi::at(array, 1u) == -1);
    CHECK(phi::at(array, 2u) == -1);
}
