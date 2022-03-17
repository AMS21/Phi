#include <phi/test/test_macros.hpp>

#include <phi/type_traits/array_size.hpp>

TEST_CASE("array_size")
{
    constexpr int a[3]{};
    STATIC_REQUIRE(phi::array_size(a) == 3u);
    CHECK_NOEXCEPT(phi::array_size(a));
    STATIC_REQUIRE(phi::array_size<0u>(a) == 3u);
    STATIC_REQUIRE(phi::array_size<1u>(a) == 0u);
    STATIC_REQUIRE(phi::array_size<2u>(a) == 0u);

    constexpr double b[1]{};
    STATIC_REQUIRE(phi::array_size(b) == 1u);
    CHECK_NOEXCEPT(phi::array_size(b));
    STATIC_REQUIRE(phi::array_size<0u>(b) == 1u);
    STATIC_REQUIRE(phi::array_size<1u>(b) == 0u);
    STATIC_REQUIRE(phi::array_size<2u>(b) == 0u);

    constexpr char c[12][2]{};
    STATIC_REQUIRE(phi::array_size(c) == 12u);
    CHECK_NOEXCEPT(phi::array_size(c));
    STATIC_REQUIRE(phi::array_size<1u>(c) == 2u);
    STATIC_REQUIRE(phi::array_size<2u>(c) == 0u);

    constexpr char d[12][2][13]{};
    STATIC_REQUIRE(phi::array_size(d) == 12u);
    CHECK_NOEXCEPT(phi::array_size(d));
    STATIC_REQUIRE(phi::array_size<1u>(d) == 2u);
    STATIC_REQUIRE(phi::array_size<2u>(d) == 13u);
}
