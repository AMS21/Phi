#include <phi/test/test_macros.hpp>

#include <phi/algorithm/string_equals.hpp>
#include <phi/compiler_support/consteval.hpp>
#include <phi/preprocessor/stringify.hpp>

TEST_CASE("PHI_CONSTEVAL")
{
#if PHI_HAS_FEATURE_CONSTEVAL()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEVAL), "consteval"));
#else
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEVAL), ""));
#endif
}

TEST_CASE("PHI_CONSTEVAL_OR_CONSTEXPR")
{
#if PHI_HAS_FEATURE_CONSTEVAL()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEVAL_OR_CONSTEXPR), "consteval"));
#elif PHI_HAS_FEATURE_CONSTEXPR()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEVAL_OR_CONSTEXPR), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEVAL_OR_CONSTEXPR), ""));
#endif
}

TEST_CASE("PHI_CONSTEVAL_OR_EXTENDED_CONSTEXPR")
{
#if PHI_HAS_FEATURE_CONSTEVAL()
    STATIC_REQUIRE(
            phi::string_equals(PHI_STRINGIFY(PHI_CONSTEVAL_OR_EXTENDED_CONSTEXPR), "consteval"));
#elif PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    STATIC_REQUIRE(
            phi::string_equals(PHI_STRINGIFY(PHI_CONSTEVAL_OR_EXTENDED_CONSTEXPR), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEVAL_OR_EXTENDED_CONSTEXPR), ""));
#endif
}

TEST_CASE("PHI_CONSTEVAL_OR")
{
#if PHI_HAS_FEATURE_CONSTEVAL()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEVAL_OR(blub)), "consteval"));
#else
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEVAL_OR(blub)), "blub"));
#endif
}

TEST_CASE("PHI_CONSTEVAL_IF")
{
#if PHI_HAS_FEATURE_CONSTEVAL()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEVAL_IF(0)), ""));
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEVAL_IF(1)), "consteval"));
#else
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEVAL_IF(0)), ""));
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEVAL_IF(1)), ""));
#endif
}
