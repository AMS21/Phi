#include <catch2/catch.hpp>

#include "StringHelper.hpp"
#include <Phi/Config/Warning.hpp>
#include <Phi/Core/Assert.hpp>
#include <string>

PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wgnu-zero-variadic-macro-arguments")

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

PHI_CLANG_SUPPRESS_WARNING_POP()

TEST_CASE("FormatArguments")
{
    CHECK(string_equals(phi::detail::FormatArgument(), "<None>"));
    CHECK(string_equals(phi::detail::FormatArgument("String").c_str(), "String"));
    CHECK(string_equals(phi::detail::FormatArgument("{}", 42).c_str(), "42"));
}
