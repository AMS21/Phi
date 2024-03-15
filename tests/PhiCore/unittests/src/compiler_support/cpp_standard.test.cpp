#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/cpp_standard.hpp>
#include <phi/compiler_support/warning.hpp>

// https://learn.microsoft.com/cpp/code-quality/c6285
PHI_MSVC_SUPPRESS_WARNING(
        6285) // ('non-zero constant' || 'non-zero constant') is always a non-zero constant. Did you intend to use the bitwise-and operator?

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wunreachable-code")

PHI_CONSTEXPR bool is_any_standard()
{
    return PHI_CPP_STANDARD() == PHI_CPLUSPLUS_98() || PHI_CPP_STANDARD() == PHI_CPLUSPLUS_11() ||
           PHI_CPP_STANDARD() == PHI_CPLUSPLUS_14() || PHI_CPP_STANDARD() == PHI_CPLUSPLUS_17() ||
           PHI_CPP_STANDARD() == PHI_CPLUSPLUS_20() || PHI_CPP_STANDARD() == PHI_CPLUSPLUS_23() ||
           PHI_CPP_STANDARD() == PHI_CPLUSPLUS_26();
}

PHI_CONSTEXPR bool is_any_short_standard()
{
    return PHI_CPP_STANDARD_SHORT() == 98 || PHI_CPP_STANDARD_SHORT() == 11 ||
           PHI_CPP_STANDARD_SHORT() == 14 || PHI_CPP_STANDARD_SHORT() == 17 ||
           PHI_CPP_STANDARD_SHORT() == 20 || PHI_CPP_STANDARD_SHORT() == 23 ||
           PHI_CPP_STANDARD_SHORT() == 26;
}

PHI_CLANG_AND_GCC_SUPPRESS_WARNING_POP()

TEST_CASE("PHI_CPLUSPLUS_X")
{
    STATIC_REQUIRE(PHI_CPLUSPLUS_98());
    STATIC_REQUIRE(PHI_CPLUSPLUS_11());
    STATIC_REQUIRE(PHI_CPLUSPLUS_14());
    STATIC_REQUIRE(PHI_CPLUSPLUS_17());
    STATIC_REQUIRE(PHI_CPLUSPLUS_20());
    STATIC_REQUIRE(PHI_CPLUSPLUS_23());
    STATIC_REQUIRE(PHI_CPLUSPLUS_26());

    STATIC_REQUIRE(PHI_CPLUSPLUS_LATEST());
    STATIC_REQUIRE(PHI_CPLUSPLUS_LATEST() == PHI_CPLUSPLUS_26());
}

TEST_CASE("PHI_CPP_STANDARD")
{
    STATIC_REQUIRE(is_any_standard() || PHI_CPP_STANDARD() == 0);
    STATIC_REQUIRE(PHI_CPP_STANDARD());
}

TEST_CASE("PHI_CPP_STANDARD_SHORT")
{
    STATIC_REQUIRE(is_any_short_standard() || PHI_CPP_STANDARD_SHORT() == 0);
    STATIC_REQUIRE(PHI_CPP_STANDARD_SHORT());
}
