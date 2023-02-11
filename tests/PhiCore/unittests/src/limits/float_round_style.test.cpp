#include <phi/test/test_macros.hpp>

#include <phi/limits/float_round_style.hpp>

TEST_CASE("float_round_style")
{
    STATIC_REQUIRE(phi::float_round_style::round_indeterminate == -1);
    STATIC_REQUIRE(phi::float_round_style::round_toward_zero == 0);
    STATIC_REQUIRE(phi::float_round_style::round_to_nearest == 1);
    STATIC_REQUIRE(phi::float_round_style::round_toward_infinity == 2);
    STATIC_REQUIRE(phi::float_round_style::round_toward_neg_infinity == 3);

    STATIC_REQUIRE(phi::round_indeterminate == -1);
    STATIC_REQUIRE(phi::round_toward_zero == 0);
    STATIC_REQUIRE(phi::round_to_nearest == 1);
    STATIC_REQUIRE(phi::round_toward_infinity == 2);
    STATIC_REQUIRE(phi::round_toward_neg_infinity == 3);
}
