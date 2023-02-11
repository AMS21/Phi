#include <phi/test/test_macros.hpp>

#include <phi/limits/float_denorm_style.hpp>

TEST_CASE("float_denorm_style")
{
    STATIC_REQUIRE(phi::float_denorm_style::denorm_indeterminate == -1);
    STATIC_REQUIRE(phi::float_denorm_style::denorm_absent == 0);
    STATIC_REQUIRE(phi::float_denorm_style::denorm_present == 1);

    STATIC_REQUIRE(phi::denorm_indeterminate == -1);
    STATIC_REQUIRE(phi::denorm_absent == 0);
    STATIC_REQUIRE(phi::denorm_present == 1);
}
