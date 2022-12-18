#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include "phi/core/compare_result.hpp"
#include <phi/algorithm/string_compare_unsafe.hpp>

TEST_CASE("string_compare_unsafe - char*/char*")
{
    STATIC_REQUIRE(phi::string_compare_unsafe("", "") == phi::CompareResult::Equal);

    STATIC_REQUIRE(phi::string_compare_unsafe("a", "") == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare_unsafe("", "a") == phi::CompareResult::LessThan);

    STATIC_REQUIRE(phi::string_compare_unsafe("a", "a") == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare_unsafe("a", "b") == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare_unsafe("a", "c") == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare_unsafe("b", "a") == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare_unsafe("c", "a") == phi::CompareResult::GreaterThan);

    STATIC_REQUIRE(phi::string_compare_unsafe("ab", "ab") == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare_unsafe("ab", "a") == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare_unsafe("a", "ab") == phi::CompareResult::LessThan);

    STATIC_REQUIRE(phi::string_compare_unsafe("abc", "abc") == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare_unsafe("abc", "ab") == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare_unsafe("abc", "a") == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare_unsafe("abc", "") == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare_unsafe("ab", "abc") == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare_unsafe("a", "abc") == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare_unsafe("", "abc") == phi::CompareResult::LessThan);
}

TEST_CASE("string_compare_unsafe with size - char*/char*")
{
    STATIC_REQUIRE(phi::string_compare_unsafe("", "", 21u) == phi::CompareResult::Equal);

    STATIC_REQUIRE(phi::string_compare_unsafe("a", "", 1u) == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare_unsafe("", "a", 1u) == phi::CompareResult::LessThan);

    STATIC_REQUIRE(phi::string_compare_unsafe("a", "a", 1u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare_unsafe("a", "a", 2u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare_unsafe("a", "a", 21u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare_unsafe("a", "b", 1u) == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare_unsafe("a", "c", 1u) == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare_unsafe("b", "a", 1u) == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare_unsafe("c", "a", 1u) == phi::CompareResult::GreaterThan);

    STATIC_REQUIRE(phi::string_compare_unsafe("ab", "ab", 2u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare_unsafe("ab", "ab", 1u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare_unsafe("ab", "ab", 0u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare_unsafe("ab", "af", 0u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare_unsafe("ab", "a", 5u) == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare_unsafe("ab", "a", 0u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare_unsafe("a", "ab", 5u) == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare_unsafe("a", "ab", 0u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare_unsafe("f", "ab", 0u) == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare_unsafe("ab", "f", 0u) == phi::CompareResult::LessThan);
}
