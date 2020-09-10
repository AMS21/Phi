#include <catch2/catch.hpp>

#include "StringHelper.hpp"
#include <Phi/PhiConfig.hpp>
#include <cpp/Stringify.hpp>

TEST_CASE("PhiConfig.hpp macros", "[Config]")
{
    STATIC_REQUIRE(
            (PHI_VERSION_MAJOR() != 0 || PHI_VERSION_MINOR() != 0 || PHI_VERSION_PATCH() != 0));
    STATIC_REQUIRE(PHI_VERSION() != 0);

    STATIC_REQUIRE(string_length(PHI_VERSION_MAJOR_STR()) != 0);
    STATIC_REQUIRE(string_length(PHI_VERSION_MAJOR_STR()) ==
                   string_length(CPP_STRINGIFY(PHI_VERSION_MAJOR())));

    STATIC_REQUIRE(string_length(PHI_VERSION_MINOR_STR()) != 0);
    STATIC_REQUIRE(string_length(PHI_VERSION_MINOR_STR()) ==
                   string_length(CPP_STRINGIFY(PHI_VERSION_MINOR())));

    STATIC_REQUIRE(string_length(PHI_VERSION_PATCH_STR()) != 0);
    STATIC_REQUIRE(string_length(PHI_VERSION_PATCH_STR()) ==
                   string_length(CPP_STRINGIFY(PHI_VERSION_PATCH())));

    STATIC_REQUIRE(string_length(PHI_VERSION_STR()) != 0);
    STATIC_REQUIRE(string_length(PHI_VERSION_STR()) ==
                   (string_length(CPP_STRINGIFY(PHI_VERSION_MAJOR()) CPP_STRINGIFY(
                            PHI_VERSION_MINOR()) CPP_STRINGIFY(PHI_VERSION_PATCH())) +
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
