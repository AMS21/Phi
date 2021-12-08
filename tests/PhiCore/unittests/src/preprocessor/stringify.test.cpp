#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/algorithm/string_equals.hpp>
#include <phi/preprocessor/stringify.hpp>

TEST_CASE("Stringify", "[Config][Stringify]")
{
    EXT_STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(2 + 3), "2 + 3"));
    EXT_STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(test), "test"));
    EXT_STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(+-), "+-"));
}
