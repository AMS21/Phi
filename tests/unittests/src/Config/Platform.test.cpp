#include <catch2/catch.hpp>

#include "StringHelper.hpp"
#include <Phi/Config/Platform.hpp>

TEST_CASE("Platform", "[Config][Platform]")
{
#if PHI_PLATFORM_IS(APPLE)
    STATIC_REQUIRE(PHI_PLATFORM_APPLE());
#endif
#if PHI_PLATFORM_IS(LINUX)
    STATIC_REQUIRE(PHI_PLATFORM_LINUX());
#endif
#if PHI_PLATFORM_IS(MACOS)
    STATIC_REQUIRE(PHI_PLATFORM_MACOS());
#endif
#if PHI_PLATFORM_IS(UNIX)
    STATIC_REQUIRE(PHI_PLATFORM_UNIX());
#endif
#if PHI_PLATFORM_IS(WINDOWS)
    STATIC_REQUIRE(PHI_PLATFORM_WINDOWS());
#endif

#if PHI_PLATFORM_IS_NOT(APPLE)
    STATIC_REQUIRE(true);
#endif
#if PHI_PLATFORM_IS_NOT(LINUX)
    STATIC_REQUIRE(true);
#endif
#if PHI_PLATFORM_IS_NOT(MACOS)
    STATIC_REQUIRE(true);
#endif
#if PHI_PLATFORM_IS_NOT(UNIX)
    STATIC_REQUIRE(true);
#endif
#if PHI_PLATFORM_IS_NOT(WINDOWS)
    STATIC_REQUIRE(true);
#endif

    STATIC_REQUIRE_FALSE(string_equals(PHI_PLATFORM_NAME(), "Unknown"));
}
