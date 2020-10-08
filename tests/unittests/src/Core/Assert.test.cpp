#include <catch2/catch.hpp>

#include "StringHelper.hpp"
#include <Phi/Core/Assert.hpp>

TEST_CASE("PHI_SIMPLE_ASSERT", "[Utility][Assert]")
{
    PHI_SIMPLE_ASSERT(true);
    PHI_SIMPLE_ASSERT(true, "Always passes");
}

TEST_CASE("PHI_DBG_SIMPLE_ASSERT", "[Utility][Assert]")
{
    PHI_DBG_SIMPLE_ASSERT(true);
    PHI_DBG_SIMPLE_ASSERT(true, "Always passes");
}

TEST_CASE("PHI_ASSERT", "[Utility][Assert]")
{
    PHI_ASSERT(true);
    PHI_ASSERT(true, "Always passes");
}

TEST_CASE("PHI_DBG_ASSERT", "[Utility][Assert]")
{
    PHI_DBG_ASSERT(true);
    PHI_DBG_ASSERT(true, "Always passes");
}

TEST_CASE("FormatArguments")
{
    CHECK(string_equals(phi::detail::FormatArgument(), "<None>"));
    CHECK(string_equals(phi::detail::FormatArgument("String").c_str(), "String"));
    CHECK(string_equals(phi::detail::FormatArgument("{}", 42).c_str(), "42"));
}
