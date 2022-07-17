#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/warning.hpp>
#include <phi/core/assert.hpp>

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wgnu-zero-variadic-macro-arguments")
PHI_CLANG_SUPPRESS_WARNING("-Wunreachable-code")

TEST_CASE("PHI_ASSERT", "[Utility][Assert]")
{
    //PHI_ASSERT(true);
    PHI_ASSERT(true, "Always passes");
}

TEST_CASE("PHI_RELEASE_ASSERT", "[Utility][Assert]")
{
    //PHI_RELEASE_ASSERT(true);
    PHI_RELEASE_ASSERT(true, "Always passes");
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

TEST_CASE("PHI_RELEASE_ASSERT_NOT_REACHED", "[Core][Assert]")
{
    if (func() == 21)
    {
        CHECK(true);
    }
    else
    {
        PHI_RELEASE_ASSERT_NOT_REACHED();
    }
}

PHI_CLANG_SUPPRESS_WARNING_POP()
