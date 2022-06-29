#include <phi/test/test_macros.hpp>

#include <phi/type_traits/array_size.hpp>

TEST_CASE("array_size")
{
    constexpr int array1[3]{};
    STATIC_REQUIRE(phi::array_size(array1) == 3u);
    CHECK_NOEXCEPT(phi::array_size(array1));
    STATIC_REQUIRE(phi::array_size<0u>(array1) == 3u);
    STATIC_REQUIRE(phi::array_size<1u>(array1) == 0u);
    STATIC_REQUIRE(phi::array_size<2u>(array1) == 0u);

    constexpr double array2[1]{};
    STATIC_REQUIRE(phi::array_size(array2) == 1u);
    CHECK_NOEXCEPT(phi::array_size(array2));
    STATIC_REQUIRE(phi::array_size<0u>(array2) == 1u);
    STATIC_REQUIRE(phi::array_size<1u>(array2) == 0u);
    STATIC_REQUIRE(phi::array_size<2u>(array2) == 0u);

    constexpr char array3[12][2]{};
    STATIC_REQUIRE(phi::array_size(array3) == 12u);
    CHECK_NOEXCEPT(phi::array_size(array3));
    STATIC_REQUIRE(phi::array_size<0u>(array3) == 12u);
    STATIC_REQUIRE(phi::array_size<1u>(array3) == 2u);
    STATIC_REQUIRE(phi::array_size<2u>(array3) == 0u);

    constexpr char array4[12][2][13]{};
    STATIC_REQUIRE(phi::array_size(array4) == 12u);
    CHECK_NOEXCEPT(phi::array_size(array4));
    STATIC_REQUIRE(phi::array_size<0u>(array4) == 12u);
    STATIC_REQUIRE(phi::array_size<1u>(array4) == 2u);
    STATIC_REQUIRE(phi::array_size<2u>(array4) == 13u);
}
