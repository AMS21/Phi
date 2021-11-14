#include <catch2/catch.hpp>

#include <Phi/Algorithm/StringEquals.hpp>
#include <Phi/Algorithm/StringLength.hpp>
#include <Phi/Config/Stringify.hpp>
#include <Phi/PhiConfig.hpp>

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
#    define STATIC_REQUIRE_EXT(...) STATIC_REQUIRE(__VA_ARGS__)
#else
#    define STATIC_REQUIRE_EXT(...) CHECK(__VA_ARGS__)
#endif

TEST_CASE("PhiConfig.hpp macros", "[Config]")
{
    STATIC_REQUIRE(
            (PHI_VERSION_MAJOR() != 0 || PHI_VERSION_MINOR() != 0 || PHI_VERSION_PATCH() != 0));
    STATIC_REQUIRE(PHI_VERSION() != 0);

    STATIC_REQUIRE_EXT(bool(phi::StringLength(PHI_VERSION_MAJOR_STR()) != 0u));
    STATIC_REQUIRE_EXT(bool(phi::StringLength(PHI_VERSION_MAJOR_STR()) ==
                            phi::StringLength(PHI_STRINGIFY(PHI_VERSION_MAJOR()))));

    STATIC_REQUIRE_EXT(bool(phi::StringLength(PHI_VERSION_MINOR_STR()) != 0u));
    STATIC_REQUIRE_EXT(bool(phi::StringLength(PHI_VERSION_MINOR_STR()) ==
                            phi::StringLength(PHI_STRINGIFY(PHI_VERSION_MINOR()))));

    STATIC_REQUIRE_EXT(bool(phi::StringLength(PHI_VERSION_PATCH_STR()) != 0u));
    STATIC_REQUIRE_EXT(bool(phi::StringLength(PHI_VERSION_PATCH_STR()) ==
                            phi::StringLength(PHI_STRINGIFY(PHI_VERSION_PATCH()))));

    STATIC_REQUIRE_EXT(bool(phi::StringLength(PHI_VERSION_STR()) != 0u));
    STATIC_REQUIRE_EXT(bool(phi::StringLength(PHI_VERSION_STR()) ==
                            (phi::StringLength(PHI_STRINGIFY(PHI_VERSION_MAJOR()) PHI_STRINGIFY(
                                     PHI_VERSION_MINOR()) PHI_STRINGIFY(PHI_VERSION_PATCH())) +
                             2u)));
}

TEST_CASE("PhiConfig.hpp variables", "[Config]")
{
    STATIC_REQUIRE(PHI_VERSION_MAJOR() == phi::VersionMajor);
    STATIC_REQUIRE(PHI_VERSION_MINOR() == phi::VersionMinor);
    STATIC_REQUIRE(PHI_VERSION_PATCH() == phi::VersionPatch);
    STATIC_REQUIRE(PHI_VERSION() == phi::Version);

    STATIC_REQUIRE_EXT(phi::StringEquals(PHI_VERSION_STR(), phi::VersionString));
}

TEST_CASE("PhiConfig.hpp Static/Dynamic", "[Config]")
{
#if defined(PHI_STATIC_BUILD)
    STATIC_REQUIRE(true);
#else
    STATIC_REQUIRE(true);
#endif
}
