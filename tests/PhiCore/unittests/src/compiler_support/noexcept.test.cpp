#include <phi/test/test_macros.hpp>

#include <phi/algorithm/string_equals.hpp>
#include <phi/compiler_support/noexcept.hpp>

TEST_CASE("PHI_NOEXCEPT")
{
#if PHI_HAS_FEATURE_NOEXCEPT()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_NOEXCEPT()), "noexcept"));
#else
    STATIC_REQUIRE(phi::string_equals("" PHI_STRINGIFY(PHI_NOEXCEPT()), ""));
#endif
}

TEST_CASE("PHI_NOEXCEPT_EXPR")
{
#if PHI_HAS_FEATURE_NOEXCEPT_EXPR()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_NOEXCEPT_EXPR(true)), "noexcept(true)"));
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_NOEXCEPT_EXPR(false)), "noexcept(false)"));
#else
    STATIC_REQUIRE(phi::string_equals("" PHI_STRINGIFY(PHI_NOEXCEPT_EXPR(true)), ""));
    STATIC_REQUIRE(phi::string_equals("" PHI_STRINGIFY(PHI_NOEXCEPT_EXPR(false)), ""));
#endif
}
