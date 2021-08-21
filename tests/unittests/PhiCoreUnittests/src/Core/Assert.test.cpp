#include <catch2/catch_test_macros.hpp>

#include <Phi/Algorithm/StringEquals.hpp>
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

static int func()
{
    return 21;
}

TEST_CASE("PHI_ASSERT_NOT_REACHED", "[Core][Assert]")
{
    if (func() == 21)
    {
        CHECK(true);
    }
    else
    {
        PHI_ASSERT_NOT_REACHED();
    }
}

TEST_CASE("PHI_DBG_ASSERT_NOT_REACHED", "[Core][Assert]")
{
    if (func() == 21)
    {
        CHECK(true);
    }
    else
    {
        PHI_DBG_ASSERT_NOT_REACHED();
    }
}

PHI_CLANG_SUPPRESS_WARNING_POP()

TEST_CASE("FormatArguments")
{
    CHECK(phi::StringEquals(phi::detail::FormatArgument(), "<None>"));
    CHECK(phi::StringEquals(phi::detail::FormatArgument("String").c_str(), "String"));
    CHECK(phi::StringEquals(phi::detail::FormatArgument("{}", 42).c_str(), "42"));
}
