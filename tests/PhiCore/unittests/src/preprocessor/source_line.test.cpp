#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/algorithm/string_equals.hpp>
#include <phi/preprocessor/source_line.hpp>

TEST_CASE("SourceLine")
{
    EXT_STATIC_REQUIRE(phi::string_equals(PHI_SOURCE_LINE(), "9"));
    EXT_STATIC_REQUIRE(phi::string_equals(PHI_SOURCE_LINE(), "10"));

    // Forcing line
#line 5
    EXT_STATIC_REQUIRE(phi::string_equals(PHI_SOURCE_LINE(), "5"));
    EXT_STATIC_REQUIRE(phi::string_equals(PHI_SOURCE_LINE(), "6"));
}
