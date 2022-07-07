#include <phi/test/test_macros.hpp>

#include <phi/text/binary_digit_value.hpp>

TEST_CASE("binary_digit_value")
{
    STATIC_REQUIRE(phi::binary_digit_value('0').unsafe() == 0u);
    STATIC_REQUIRE(phi::binary_digit_value('1').unsafe() == 1u);
}
