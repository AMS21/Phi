#include <catch2/catch_test_macros.hpp>

#include "StringHelper.hpp"
#include <Phi/Config/Stringify.hpp>
#include <Phi/PhiConfig.hpp>

TEST_CASE("PhiConfig.hpp macros", "[Config]")
{
    STATIC_REQUIRE(
            (PHI_VERSION_MAJOR() != 0 || PHI_VERSION_MINOR() != 0 || PHI_VERSION_PATCH() != 0));
    STATIC_REQUIRE(PHI_VERSION() != 0);

    STATIC_REQUIRE(string_length(PHI_VERSION_MAJOR_STR()) != 0);
    STATIC_REQUIRE(string_length(PHI_VERSION_MAJOR_STR()) ==
                   string_length(PHI_STRINGIFY(PHI_VERSION_MAJOR())));

    STATIC_REQUIRE(string_length(PHI_VERSION_MINOR_STR()) != 0);
    STATIC_REQUIRE(string_length(PHI_VERSION_MINOR_STR()) ==
                   string_length(PHI_STRINGIFY(PHI_VERSION_MINOR())));

    STATIC_REQUIRE(string_length(PHI_VERSION_PATCH_STR()) != 0);
    STATIC_REQUIRE(string_length(PHI_VERSION_PATCH_STR()) ==
                   string_length(PHI_STRINGIFY(PHI_VERSION_PATCH())));

    STATIC_REQUIRE(string_length(PHI_VERSION_STR()) != 0);
    STATIC_REQUIRE(string_length(PHI_VERSION_STR()) ==
                   (string_length(PHI_STRINGIFY(PHI_VERSION_MAJOR()) PHI_STRINGIFY(
                            PHI_VERSION_MINOR()) PHI_STRINGIFY(PHI_VERSION_PATCH())) +
                    2));
}

TEST_CASE("PhiConfig.hpp variables", "[Config]")
{
    STATIC_REQUIRE(PHI_VERSION_MAJOR() == phi::VersionMajor);
    STATIC_REQUIRE(PHI_VERSION_MINOR() == phi::VersionMinor);
    STATIC_REQUIRE(PHI_VERSION_PATCH() == phi::VersionPatch);
    STATIC_REQUIRE(PHI_VERSION() == phi::Version);

    STATIC_REQUIRE(string_equals(PHI_VERSION_STR(), phi::VersionString));
}

TEST_CASE("PhiConfig.hpp Static/Dynamic", "[Config]")
{
#if defined(PHI_STATIC_BUILD)
    STATIC_REQUIRE(true);
#else
    STATIC_REQUIRE(true);
#endif
}
