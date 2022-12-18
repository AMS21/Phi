#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/algorithm/string_compare.hpp>
#include <phi/core/compare_result.hpp>

static constexpr const char* char_nullptr = nullptr;

TEST_CASE("string_compare - nullptr_t/nullptr_t")
{
    STATIC_REQUIRE(phi::string_compare(nullptr, nullptr) == phi::CompareResult::Equal);
}

TEST_CASE("string_compare - nullptr_t/char*")
{
    STATIC_REQUIRE(phi::string_compare(nullptr, "Hello") == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare(nullptr, "") == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare(nullptr, char_nullptr) == phi::CompareResult::Equal);
}

TEST_CASE("string_compare - char*/nullptr_t")
{
    STATIC_REQUIRE(phi::string_compare("Hello", nullptr) == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare("", nullptr) == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare(char_nullptr, nullptr) == phi::CompareResult::Equal);
}

TEST_CASE("string_compare - char*/char*")
{
    STATIC_REQUIRE(phi::string_compare(char_nullptr, char_nullptr) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare("", char_nullptr) == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare(char_nullptr, "") == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare("", "") == phi::CompareResult::Equal);

    STATIC_REQUIRE(phi::string_compare("a", "") == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare("", "a") == phi::CompareResult::LessThan);

    STATIC_REQUIRE(phi::string_compare(char_nullptr, "a") == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare("a", char_nullptr) == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare("a", "a") == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare("a", "b") == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare("a", "c") == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare("b", "a") == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare("c", "a") == phi::CompareResult::GreaterThan);

    STATIC_REQUIRE(phi::string_compare("ab", "ab") == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare("ab", "a") == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare("a", "ab") == phi::CompareResult::LessThan);

    STATIC_REQUIRE(phi::string_compare("abc", "abc") == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare("abc", "ab") == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare("abc", "a") == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare("abc", "") == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare("ab", "abc") == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare("a", "abc") == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare("", "abc") == phi::CompareResult::LessThan);
}

TEST_CASE("string_compare with size - nullptr_t/nullptr_t")
{
    STATIC_REQUIRE(phi::string_compare(nullptr, nullptr, 0u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare(nullptr, nullptr, 21u) == phi::CompareResult::Equal);
}

TEST_CASE("string_compare with size - nullptr_t/char*")
{
    STATIC_REQUIRE(phi::string_compare(nullptr, "Hello", 21u) == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare(nullptr, "", 21u) == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare(nullptr, char_nullptr, 21u) == phi::CompareResult::Equal);
}

TEST_CASE("string_compare with size - char*/nullptr_t")
{
    STATIC_REQUIRE(phi::string_compare("Hello", nullptr, 21u) == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare("", nullptr, 21u) == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare(char_nullptr, nullptr, 21u) == phi::CompareResult::Equal);
}

TEST_CASE("string_compare with size - char*/char*")
{
    STATIC_REQUIRE(phi::string_compare(char_nullptr, char_nullptr, 21u) ==
                   phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare(char_nullptr, char_nullptr, 1u) ==
                   phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare("", char_nullptr, 21u) == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare(char_nullptr, "", 21u) == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare("", "", 21u) == phi::CompareResult::Equal);

    STATIC_REQUIRE(phi::string_compare("a", "", 1u) == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare("", "a", 1u) == phi::CompareResult::LessThan);

    STATIC_REQUIRE(phi::string_compare(char_nullptr, "a", 1u) == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare("a", char_nullptr, 1u) == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare("a", "a", 1u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare("a", "a", 2u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare("a", "a", 21u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare("a", "b", 1u) == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare("a", "c", 1u) == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare("b", "a", 1u) == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare("c", "a", 1u) == phi::CompareResult::GreaterThan);

    STATIC_REQUIRE(phi::string_compare("ab", "ab", 2u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare("ab", "ab", 1u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare("ab", "ab", 0u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare("ab", "af", 0u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare("ab", "a", 5u) == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare("ab", "a", 0u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare("a", "ab", 5u) == phi::CompareResult::LessThan);
    STATIC_REQUIRE(phi::string_compare("a", "ab", 0u) == phi::CompareResult::Equal);
    STATIC_REQUIRE(phi::string_compare("f", "ab", 0u) == phi::CompareResult::GreaterThan);
    STATIC_REQUIRE(phi::string_compare("ab", "f", 0u) == phi::CompareResult::LessThan);
}
