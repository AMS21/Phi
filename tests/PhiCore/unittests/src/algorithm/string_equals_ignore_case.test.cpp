#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/algorithm/string_equals_ignore_case.hpp>
#include <phi/container/string_view.hpp>
#include <phi/generated/compiler_support/libraries.hpp>
#include <string>

#if PHI_HAS_LIB_STRING_VIEW()
#    include <string_view>
#endif

static constexpr const char*            null = nullptr;
static constexpr const phi::string_view null_view;
#if PHI_HAS_LIB_STRING_VIEW()
static constexpr const std::string_view std_null_view;
#endif

TEST_CASE("string_equals_ignore_case - nullptr_t, nullptr_t")
{
    STATIC_REQUIRE(phi::string_equals_ignore_case(nullptr, nullptr));
}

TEST_CASE("string_equals_ignore_case - nullptr_t, char*")
{
    STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(nullptr, "Hello"));
    STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(nullptr, ""));
    STATIC_REQUIRE(phi::string_equals_ignore_case(nullptr, null));
}

TEST_CASE("string_equals_ignore_case - nullptr_t, phi::string_view")
{
    STATIC_REQUIRE(phi::string_equals_ignore_case(nullptr, null_view));
    STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(nullptr, phi::string_view("Hello")));
    STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(nullptr, phi::string_view("")));
}

#if PHI_HAS_LIB_STRING_VIEW()
TEST_CASE("string_equals_ignore_case - nullptr_t, std::string_view")
{
    STATIC_REQUIRE(phi::string_equals_ignore_case(nullptr, std_null_view));
    STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(nullptr, std::string_view("Hello")));
    STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(nullptr, std::string_view("")));
}
#endif

TEST_CASE("string_equals_ignore_case - nullptr_t, std::string")
{
    const std::string null_string;

    CHECK_FALSE(phi::string_equals_ignore_case(nullptr, null_string));
    CHECK_FALSE(phi::string_equals_ignore_case(nullptr, std::string("Hello")));
    CHECK_FALSE(phi::string_equals_ignore_case(nullptr, std::string("")));
}

TEST_CASE("string_equals_ignore_case - char*, nullptr_t")
{
    STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case("Hello", nullptr));
    STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case("", nullptr));
    STATIC_REQUIRE(phi::string_equals_ignore_case(null, nullptr));
}

TEST_CASE("string_equals_ignore_case - char*, char*")
{
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(null, null));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(null, "Hello"));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(null, ""));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case("Hello", null));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case("Hello", "Hello"));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case("hello", "Hello"));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case("Hello", "hello"));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case("HELLO", "hello"));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case("HELLo", "heLlO"));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case("Hello", ""));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case("", null));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case("", "Hello"));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case("", ""));

    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case("Hello", "hello"));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case("Hello", "Helli"));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case("Hello", "Hello "));
}

TEST_CASE("string_equals_ignore_case - char*, phi::string_view")
{
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(null, null_view));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(null, phi::string_view("Hello")));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(null, phi::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case("Hello", null_view));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case("Hello", phi::string_view("Hello")));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case("Hello", phi::string_view("hello")));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case("HELLO", phi::string_view("Hello")));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case("HELLO", phi::string_view("hello")));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case("Hello", phi::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case("", null_view));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case("", phi::string_view("Hello")));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case("", phi::string_view("")));
}

#if PHI_HAS_LIB_STRING_VIEW()
TEST_CASE("string_equals_ignore_case - char*, std::string_view")
{
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(null, std_null_view));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(null, std::string_view("Hello")));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(null, std::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case("Hello", std_null_view));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case("Hello", std::string_view("Hello")));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case("Hello", std::string_view("hello")));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case("HELLO", std::string_view("hellO")));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case("Hello", std::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case("", std_null_view));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case("", std::string_view("Hello")));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case("", std::string_view("")));
}
#endif

TEST_CASE("string_equals_ignore_case - char*, std::string")
{
    const std::string null_string;

    CHECK_FALSE(phi::string_equals_ignore_case(null, null_string));
    CHECK_FALSE(phi::string_equals_ignore_case(null, std::string("Hello")));
    CHECK_FALSE(phi::string_equals_ignore_case(null, std::string("")));

    CHECK_FALSE(phi::string_equals_ignore_case("Hello", null_string));
    CHECK(phi::string_equals_ignore_case("Hello", std::string("Hello")));
    CHECK(phi::string_equals_ignore_case("Hello", std::string("hello")));
    CHECK(phi::string_equals_ignore_case("HELLO", std::string("hello")));
    CHECK_FALSE(phi::string_equals_ignore_case("Hello", std::string("")));

    CHECK(phi::string_equals_ignore_case("", null_string));
    CHECK_FALSE(phi::string_equals_ignore_case("", std::string("Hello")));
    CHECK(phi::string_equals_ignore_case("", std::string("")));
}

TEST_CASE("string_equals_ignore_case - phi::string_view, nullptr_t")
{
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(null_view, nullptr));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(phi::string_view("Hello"), nullptr));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(phi::string_view(""), nullptr));
}

TEST_CASE("string_equals_ignore_case - phi::string_view, char*")
{
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(null_view, null));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(null_view, "Hello"));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(null_view, ""));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(phi::string_view("Hello"), null));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(phi::string_view("Hello"), "Hello"));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(phi::string_view("Hello"), "hello"));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(phi::string_view("HELLO"), "Hello"));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(phi::string_view("HelLO"), "hEllO"));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(phi::string_view("Hello"), ""));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(phi::string_view(""), null));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(phi::string_view(""), "Hello"));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(phi::string_view(""), ""));
}

TEST_CASE("string_equals_ignore_case - phi::string_view, phi::string_view")
{
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(null_view, null_view));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(null_view, phi::string_view("Hello")));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(null_view, phi::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(phi::string_view("Hello"), null_view));
    EXT_STATIC_REQUIRE(
            phi::string_equals_ignore_case(phi::string_view("Hello"), phi::string_view("Hello")));
    EXT_STATIC_REQUIRE(
            phi::string_equals_ignore_case(phi::string_view("hello"), phi::string_view("Hello")));
    EXT_STATIC_REQUIRE(
            phi::string_equals_ignore_case(phi::string_view("Hello"), phi::string_view("hello")));
    EXT_STATIC_REQUIRE(
            phi::string_equals_ignore_case(phi::string_view("HELLO"), phi::string_view("hElLo")));
    EXT_STATIC_REQUIRE_FALSE(
            phi::string_equals_ignore_case(phi::string_view("Hello"), phi::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(phi::string_view(""), null_view));
    EXT_STATIC_REQUIRE_FALSE(
            phi::string_equals_ignore_case(phi::string_view(""), phi::string_view("Hello")));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(phi::string_view(""), phi::string_view("")));
}

#if PHI_HAS_LIB_STRING_VIEW()
TEST_CASE("string_equals_ignore_case - phi::string_view, std::string_view")
{
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(null_view, std_null_view));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(null_view, std::string_view("Hello")));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(null_view, std::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(
            phi::string_equals_ignore_case(phi::string_view("Hello"), std_null_view));
    EXT_STATIC_REQUIRE(
            phi::string_equals_ignore_case(phi::string_view("Hello"), std::string_view("Hello")));
    EXT_STATIC_REQUIRE(
            phi::string_equals_ignore_case(phi::string_view("Hello"), std::string_view("hello")));
    EXT_STATIC_REQUIRE(
            phi::string_equals_ignore_case(phi::string_view("hello"), std::string_view("Hello")));
    EXT_STATIC_REQUIRE(
            phi::string_equals_ignore_case(phi::string_view("HELLO"), std::string_view("hello")));
    EXT_STATIC_REQUIRE_FALSE(
            phi::string_equals_ignore_case(phi::string_view("Hello"), std::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(phi::string_view(""), std_null_view));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(phi::string_view(""), std::string_view("")));
    EXT_STATIC_REQUIRE_FALSE(
            phi::string_equals_ignore_case(phi::string_view(""), std::string_view("Hello")));
}
#endif

TEST_CASE("string_equals_ignore_case - phi::string_view, std::string")
{
    const std::string null_string;

    CHECK(phi::string_equals_ignore_case(null_view, null));
    CHECK_FALSE(phi::string_equals_ignore_case(null_view, std::string("Hello")));
    CHECK_FALSE(phi::string_equals_ignore_case(null_view, std::string("")));

    CHECK_FALSE(phi::string_equals_ignore_case(phi::string_view("Hello"), null_string));
    CHECK(phi::string_equals_ignore_case(phi::string_view("Hello"), std::string("Hello")));
    CHECK(phi::string_equals_ignore_case(phi::string_view("Hello"), std::string("hello")));
    CHECK(phi::string_equals_ignore_case(phi::string_view("hello"), std::string("Hello")));
    CHECK(phi::string_equals_ignore_case(phi::string_view("HELLO"), std::string("hello")));
    CHECK_FALSE(phi::string_equals_ignore_case(phi::string_view("Hello"), std::string("")));

    CHECK(phi::string_equals_ignore_case(phi::string_view(""), null_string));
    CHECK_FALSE(phi::string_equals_ignore_case(phi::string_view(""), std::string("Hello")));
    CHECK(phi::string_equals_ignore_case(phi::string_view(""), std::string("")));
}

#if PHI_HAS_LIB_STRING_VIEW()
TEST_CASE("string_equals_ignore_case - std::string_view, nullptr_t")
{
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(std_null_view, nullptr));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(std::string_view("Hello"), nullptr));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(std::string_view(""), nullptr));
}

TEST_CASE("string_equals_ignore_case - std::string_view, char*")
{
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(std_null_view, null));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(std_null_view, "Hello"));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(std_null_view, ""));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(std::string_view("Hello"), null));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(std::string_view("Hello"), "Hello"));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(std::string_view("Hello"), "hello"));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(std::string_view("hello"), "Hello"));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(std::string_view("HELLO"), "hello"));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(std::string_view("Hello"), ""));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(std::string_view(""), null));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(std::string_view(""), "Hello"));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(std::string_view(""), ""));
}

TEST_CASE("string_equals_ignore_case - std::string_view, phi::string_view")
{
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(std_null_view, null_view));
    EXT_STATIC_REQUIRE_FALSE(
            phi::string_equals_ignore_case(std_null_view, phi::string_view("Hello")));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(std_null_view, phi::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(std::string_view("Hello"), null_view));
    EXT_STATIC_REQUIRE(
            phi::string_equals_ignore_case(std::string_view("Hello"), phi::string_view("Hello")));
    EXT_STATIC_REQUIRE(
            phi::string_equals_ignore_case(std::string_view("Hello"), phi::string_view("hello")));
    EXT_STATIC_REQUIRE(
            phi::string_equals_ignore_case(std::string_view("hello"), phi::string_view("Hello")));
    EXT_STATIC_REQUIRE(
            phi::string_equals_ignore_case(std::string_view("HELLO"), phi::string_view("hello")));
    EXT_STATIC_REQUIRE_FALSE(
            phi::string_equals_ignore_case(std::string_view("Hello"), phi::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals_ignore_case(std::string_view(""), null_view));
    EXT_STATIC_REQUIRE_FALSE(
            phi::string_equals_ignore_case(std::string_view(""), phi::string_view("Hello")));
    EXT_STATIC_REQUIRE(phi::string_equals_ignore_case(std::string_view(""), phi::string_view("")));
}

TEST_CASE("string_equals_ignore_case - std::string_view, std::string")
{
    const std::string null_string;

    CHECK_FALSE(phi::string_equals_ignore_case(std_null_view, null_string));
    CHECK_FALSE(phi::string_equals_ignore_case(std_null_view, std::string("Hello")));
    CHECK_FALSE(phi::string_equals_ignore_case(std_null_view, std::string("")));

    CHECK_FALSE(phi::string_equals_ignore_case(std::string_view("Hello"), null_string));
    CHECK(phi::string_equals_ignore_case(std::string_view("Hello"), std::string("Hello")));
    CHECK(phi::string_equals_ignore_case(std::string_view("Hello"), std::string("hello")));
    CHECK(phi::string_equals_ignore_case(std::string_view("hello"), std::string("Hello")));
    CHECK(phi::string_equals_ignore_case(std::string_view("HELLO"), std::string("hello")));
    CHECK_FALSE(phi::string_equals_ignore_case(std::string_view("Hello"), std::string("")));

    CHECK(phi::string_equals_ignore_case(std::string_view(""), null_string));
    CHECK_FALSE(phi::string_equals_ignore_case(std::string_view(""), std::string("Hello")));
    CHECK(phi::string_equals_ignore_case(std::string_view(""), std::string("")));
}
#endif

TEST_CASE("string_equals_ignore_case - std::string, nullptr_t")
{
    const std::string null_string;

    CHECK_FALSE(phi::string_equals_ignore_case(null_string, nullptr));
    CHECK_FALSE(phi::string_equals_ignore_case(std::string("Hello"), nullptr));
    CHECK_FALSE(phi::string_equals_ignore_case(std::string(""), nullptr));
}

TEST_CASE("string_equals_ignore_case - std::string, char*")
{
    const std::string null_string;

    CHECK_FALSE(phi::string_equals_ignore_case(null_string, null));
    CHECK_FALSE(phi::string_equals_ignore_case(null_string, "Hello"));
    CHECK(phi::string_equals_ignore_case(null_string, ""));

    CHECK_FALSE(phi::string_equals_ignore_case(std::string("Hello"), null));
    CHECK(phi::string_equals_ignore_case(std::string("Hello"), "Hello"));
    CHECK(phi::string_equals_ignore_case(std::string("Hello"), "hello"));
    CHECK(phi::string_equals_ignore_case(std::string("hello"), "Hello"));
    CHECK(phi::string_equals_ignore_case(std::string("HELLO"), "heLlO"));
    CHECK_FALSE(phi::string_equals_ignore_case(std::string("Hello"), ""));

    CHECK_FALSE(phi::string_equals_ignore_case(std::string(""), null));
    CHECK_FALSE(phi::string_equals_ignore_case(std::string(""), "Hello"));
    CHECK(phi::string_equals_ignore_case(std::string(""), ""));
}

TEST_CASE("string_equals_ignore_case - std::string, phi::string_view")
{
    const std::string null_string;

    CHECK_FALSE(phi::string_equals_ignore_case(null_string, null_view));
    CHECK_FALSE(phi::string_equals_ignore_case(null_string, phi::string_view("Hello")));
    CHECK(phi::string_equals_ignore_case(null_string, phi::string_view("")));

    CHECK_FALSE(phi::string_equals_ignore_case(std::string("Hello"), null_view));
    CHECK(phi::string_equals_ignore_case(std::string("Hello"), phi::string_view("Hello")));
    CHECK(phi::string_equals_ignore_case(std::string("Hello"), phi::string_view("hello")));
    CHECK(phi::string_equals_ignore_case(std::string("hello"), phi::string_view("Hello")));
    CHECK(phi::string_equals_ignore_case(std::string("HELLO"), phi::string_view("hello")));
    CHECK_FALSE(phi::string_equals_ignore_case(std::string("Hello"), phi::string_view("")));

    CHECK_FALSE(phi::string_equals_ignore_case(std::string(""), null_view));
    CHECK_FALSE(phi::string_equals_ignore_case(std::string(""), phi::string_view("Hello")));
    CHECK(phi::string_equals_ignore_case(std::string(""), phi::string_view("")));
}

#if PHI_HAS_LIB_STRING_VIEW()
TEST_CASE("string_equals_ignore_case - std::string, std::string_view")
{
    const std::string null_string;

    CHECK_FALSE(phi::string_equals_ignore_case(null_string, std_null_view));
    CHECK_FALSE(phi::string_equals_ignore_case(null_string, std::string_view("Hello")));
    CHECK(phi::string_equals_ignore_case(null_string, std::string_view("")));

    CHECK_FALSE(phi::string_equals_ignore_case(std::string("Hello"), std_null_view));
    CHECK(phi::string_equals_ignore_case(std::string("Hello"), std::string_view("Hello")));
    CHECK(phi::string_equals_ignore_case(std::string("hello"), std::string_view("Hello")));
    CHECK(phi::string_equals_ignore_case(std::string("Hello"), std::string_view("hello")));
    CHECK(phi::string_equals_ignore_case(std::string("HELLO"), std::string_view("Hello")));
    CHECK_FALSE(phi::string_equals_ignore_case(std::string("Hello"), std::string_view("")));

    CHECK_FALSE(phi::string_equals_ignore_case(std::string(""), std_null_view));
    CHECK_FALSE(phi::string_equals_ignore_case(std::string(""), std::string_view("Hello")));
    CHECK(phi::string_equals_ignore_case(std::string(""), std::string_view("")));
}
#endif

TEST_CASE("string_equals_ignore_case - std::string, std::string")
{
    const std::string null_string;

    CHECK(phi::string_equals_ignore_case(null_string, null_string));
    CHECK_FALSE(phi::string_equals_ignore_case(null_string, std::string("Hello")));
    CHECK(phi::string_equals_ignore_case(null_string, std::string("")));

    CHECK_FALSE(phi::string_equals_ignore_case(std::string("Hello"), null_string));
    CHECK(phi::string_equals_ignore_case(std::string("Hello"), std::string("Hello")));
    CHECK(phi::string_equals_ignore_case(std::string("Hello"), std::string("hello")));
    CHECK(phi::string_equals_ignore_case(std::string("hello"), std::string("Hello")));
    CHECK(phi::string_equals_ignore_case(std::string("HELLO"), std::string("Hello")));
    CHECK_FALSE(phi::string_equals_ignore_case(std::string("Hello"), std::string("")));

    CHECK(phi::string_equals_ignore_case(std::string(""), null_string));
    CHECK_FALSE(phi::string_equals_ignore_case(std::string(""), std::string("Hello")));
    CHECK(phi::string_equals_ignore_case(std::string(""), std::string("")));
}
