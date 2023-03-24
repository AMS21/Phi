#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/algorithm/string_equals.hpp>
#include <phi/container/string_view.hpp>
#include <phi/core/boolean.hpp>
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

TEST_CASE("string_equals - nullptr_t, nullptr_t")
{
    STATIC_REQUIRE(phi::string_equals(nullptr, nullptr));

    CHECK(phi::string_equals(nullptr, nullptr));
}

TEST_CASE("string_equals - nullptr_t, char*")
{
    STATIC_REQUIRE_FALSE(phi::string_equals(nullptr, "Hello"));
    STATIC_REQUIRE_FALSE(phi::string_equals(nullptr, ""));
    STATIC_REQUIRE(phi::string_equals(nullptr, null));

    CHECK_FALSE(phi::string_equals(nullptr, "Hello"));
    CHECK_FALSE(phi::string_equals(nullptr, ""));
    CHECK(phi::string_equals(nullptr, null));
}

TEST_CASE("string_equals - nullptr_t, phi::string_view")
{
    STATIC_REQUIRE(phi::string_equals(nullptr, null_view));
    STATIC_REQUIRE_FALSE(phi::string_equals(nullptr, phi::string_view("Hello")));
    STATIC_REQUIRE_FALSE(phi::string_equals(nullptr, phi::string_view("")));

    CHECK(phi::string_equals(nullptr, null_view));
    CHECK_FALSE(phi::string_equals(nullptr, phi::string_view("Hello")));
    CHECK_FALSE(phi::string_equals(nullptr, phi::string_view("")));
}

#if PHI_HAS_LIB_STRING_VIEW()
TEST_CASE("string_equals - nullptr_t, std::string_view")
{
    STATIC_REQUIRE(phi::string_equals(nullptr, std_null_view));
    STATIC_REQUIRE_FALSE(phi::string_equals(nullptr, std::string_view("Hello")));
    STATIC_REQUIRE_FALSE(phi::string_equals(nullptr, std::string_view("")));

    CHECK(phi::string_equals(nullptr, std_null_view));
    CHECK_FALSE(phi::string_equals(nullptr, std::string_view("Hello")));
    CHECK_FALSE(phi::string_equals(nullptr, std::string_view("")));
}
#endif

TEST_CASE("string_equals - nullptr_t, std::string")
{
    const std::string null_string;

    CHECK_FALSE(phi::string_equals(nullptr, null_string));
    CHECK_FALSE(phi::string_equals(nullptr, std::string("Hello")));
    CHECK_FALSE(phi::string_equals(nullptr, std::string("")));
}

TEST_CASE("string_equals - char*, nullptr_t")
{
    STATIC_REQUIRE_FALSE(phi::string_equals("Hello", nullptr));
    STATIC_REQUIRE_FALSE(phi::string_equals("", nullptr));
    STATIC_REQUIRE(phi::string_equals(null, nullptr));

    CHECK_FALSE(phi::string_equals("Hello", nullptr));
    CHECK_FALSE(phi::string_equals("", nullptr));
    CHECK(phi::string_equals(null, nullptr));
}

TEST_CASE("string_equals - char*, char*")
{
    EXT_STATIC_REQUIRE(phi::string_equals(null, null));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(null, "Hello"));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(null, ""));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals("Hello", null));
    EXT_STATIC_REQUIRE(phi::string_equals("Hello", "Hello"));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals("Hello", ""));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals("", null));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals("", "Hello"));
    EXT_STATIC_REQUIRE(phi::string_equals("", ""));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals("Hello", "hello"));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals("Hello", "Helli"));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals("Hello", "Hello "));

    CHECK(phi::string_equals(null, null));
    CHECK_FALSE(phi::string_equals(null, "Hello"));
    CHECK_FALSE(phi::string_equals(null, ""));

    CHECK_FALSE(phi::string_equals("Hello", null));
    CHECK(phi::string_equals("Hello", "Hello"));
    CHECK_FALSE(phi::string_equals("Hello", ""));

    CHECK_FALSE(phi::string_equals("", null));
    CHECK_FALSE(phi::string_equals("", "Hello"));
    CHECK(phi::string_equals("", ""));

    CHECK_FALSE(phi::string_equals("Hello", "hello"));
    CHECK_FALSE(phi::string_equals("Hello", "Helli"));
    CHECK_FALSE(phi::string_equals("Hello", "Hello "));
}

TEST_CASE("string_equals - char*, phi::string_view")
{
    EXT_STATIC_REQUIRE(phi::string_equals(null, null_view));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(null, phi::string_view("Hello")));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(null, phi::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals("Hello", null_view));
    EXT_STATIC_REQUIRE(phi::string_equals("Hello", phi::string_view("Hello")));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals("Hello", phi::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals("", null_view));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals("", phi::string_view("Hello")));
    EXT_STATIC_REQUIRE(phi::string_equals("", phi::string_view("")));

    CHECK(phi::string_equals(null, null_view));
    CHECK_FALSE(phi::string_equals(null, phi::string_view("Hello")));
    CHECK_FALSE(phi::string_equals(null, phi::string_view("")));

    CHECK_FALSE(phi::string_equals("Hello", null_view));
    CHECK(phi::string_equals("Hello", phi::string_view("Hello")));
    CHECK_FALSE(phi::string_equals("Hello", phi::string_view("")));

    CHECK_FALSE(phi::string_equals("", null_view));
    CHECK_FALSE(phi::string_equals("", phi::string_view("Hello")));
    CHECK(phi::string_equals("", phi::string_view("")));
}

#if PHI_HAS_LIB_STRING_VIEW()
TEST_CASE("string_equals - char*, std::string_view")
{
    EXT_STATIC_REQUIRE(phi::string_equals(null, std_null_view));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(null, std::string_view("Hello")));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(null, std::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals("Hello", std_null_view));
    EXT_STATIC_REQUIRE(phi::string_equals("Hello", std::string_view("Hello")));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals("Hello", std::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals("", std_null_view));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals("", std::string_view("Hello")));
    EXT_STATIC_REQUIRE(phi::string_equals("", std::string_view("")));

    CHECK(phi::string_equals(null, std_null_view));
    CHECK_FALSE(phi::string_equals(null, std::string_view("Hello")));
    CHECK_FALSE(phi::string_equals(null, std::string_view("")));

    CHECK_FALSE(phi::string_equals("Hello", std_null_view));
    CHECK(phi::string_equals("Hello", std::string_view("Hello")));
    CHECK_FALSE(phi::string_equals("Hello", std::string_view("")));

    CHECK_FALSE(phi::string_equals("", std_null_view));
    CHECK_FALSE(phi::string_equals("", std::string_view("Hello")));
    CHECK(phi::string_equals("", std::string_view("")));
}
#endif

TEST_CASE("string_equals - char*, std::string")
{
    const std::string null_string;

    CHECK_FALSE(phi::string_equals(null, null_string));
    CHECK_FALSE(phi::string_equals(null, std::string("Hello")));
    CHECK_FALSE(phi::string_equals(null, std::string("")));

    CHECK_FALSE(phi::string_equals("Hello", null_string));
    CHECK(phi::string_equals("Hello", std::string("Hello")));
    CHECK_FALSE(phi::string_equals("Hello", std::string("")));

    CHECK(phi::string_equals("", null_string));
    CHECK_FALSE(phi::string_equals("", std::string("Hello")));
    CHECK(phi::string_equals("", std::string("")));
}

TEST_CASE("string_equals - phi::string_view, nullptr_t")
{
    EXT_STATIC_REQUIRE(phi::string_equals(null_view, nullptr));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(phi::string_view("Hello"), nullptr));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(phi::string_view(""), nullptr));

    CHECK(phi::string_equals(null_view, nullptr));
    CHECK_FALSE(phi::string_equals(phi::string_view("Hello"), nullptr));
    CHECK_FALSE(phi::string_equals(phi::string_view(""), nullptr));
}

TEST_CASE("string_equals - phi::string_view, char*")
{
    EXT_STATIC_REQUIRE(phi::string_equals(null_view, null));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(null_view, "Hello"));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(null_view, ""));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(phi::string_view("Hello"), null));
    EXT_STATIC_REQUIRE(phi::string_equals(phi::string_view("Hello"), "Hello"));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(phi::string_view("Hello"), ""));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(phi::string_view(""), null));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(phi::string_view(""), "Hello"));
    EXT_STATIC_REQUIRE(phi::string_equals(phi::string_view(""), ""));

    CHECK(phi::string_equals(null_view, null));
    CHECK_FALSE(phi::string_equals(null_view, "Hello"));
    CHECK_FALSE(phi::string_equals(null_view, ""));

    CHECK_FALSE(phi::string_equals(phi::string_view("Hello"), null));
    CHECK(phi::string_equals(phi::string_view("Hello"), "Hello"));
    CHECK_FALSE(phi::string_equals(phi::string_view("Hello"), ""));

    CHECK_FALSE(phi::string_equals(phi::string_view(""), null));
    CHECK_FALSE(phi::string_equals(phi::string_view(""), "Hello"));
    CHECK(phi::string_equals(phi::string_view(""), ""));
}

TEST_CASE("string_equals - phi::string_view, phi::string_view")
{
    EXT_STATIC_REQUIRE(phi::string_equals(null_view, null_view));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(null_view, phi::string_view("Hello")));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(null_view, phi::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(phi::string_view("Hello"), null_view));
    EXT_STATIC_REQUIRE(phi::string_equals(phi::string_view("Hello"), phi::string_view("Hello")));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(phi::string_view("Hello"), phi::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(phi::string_view(""), null_view));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(phi::string_view(""), phi::string_view("Hello")));
    EXT_STATIC_REQUIRE(phi::string_equals(phi::string_view(""), phi::string_view("")));

    CHECK(phi::string_equals(null_view, null_view));
    CHECK_FALSE(phi::string_equals(null_view, phi::string_view("Hello")));
    CHECK_FALSE(phi::string_equals(null_view, phi::string_view("")));

    CHECK_FALSE(phi::string_equals(phi::string_view("Hello"), null_view));
    CHECK(phi::string_equals(phi::string_view("Hello"), phi::string_view("Hello")));
    CHECK_FALSE(phi::string_equals(phi::string_view("Hello"), phi::string_view("")));

    CHECK_FALSE(phi::string_equals(phi::string_view(""), null_view));
    CHECK_FALSE(phi::string_equals(phi::string_view(""), phi::string_view("Hello")));
    CHECK(phi::string_equals(phi::string_view(""), phi::string_view("")));
}

#if PHI_HAS_LIB_STRING_VIEW()
TEST_CASE("string_equals - phi::string_view, std::string_view")
{
    EXT_STATIC_REQUIRE(phi::string_equals(null_view, std_null_view));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(null_view, std::string_view("Hello")));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(null_view, std::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(phi::string_view("Hello"), std_null_view));
    EXT_STATIC_REQUIRE(phi::string_equals(phi::string_view("Hello"), std::string_view("Hello")));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(phi::string_view("Hello"), std::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(phi::string_view(""), std_null_view));
    EXT_STATIC_REQUIRE(phi::string_equals(phi::string_view(""), std::string_view("")));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(phi::string_view(""), std::string_view("Hello")));

    CHECK(phi::string_equals(null_view, std_null_view));
    CHECK_FALSE(phi::string_equals(null_view, std::string_view("Hello")));
    CHECK_FALSE(phi::string_equals(null_view, std::string_view("")));

    CHECK_FALSE(phi::string_equals(phi::string_view("Hello"), std_null_view));
    CHECK(phi::string_equals(phi::string_view("Hello"), std::string_view("Hello")));
    CHECK_FALSE(phi::string_equals(phi::string_view("Hello"), std::string_view("")));

    CHECK_FALSE(phi::string_equals(phi::string_view(""), std_null_view));
    CHECK(phi::string_equals(phi::string_view(""), std::string_view("")));
    CHECK_FALSE(phi::string_equals(phi::string_view(""), std::string_view("Hello")));
}
#endif

TEST_CASE("string_equals - phi::string_view, std::string")
{
    const std::string null_string;

    CHECK(phi::string_equals(null_view, null));
    CHECK_FALSE(phi::string_equals(null_view, std::string("Hello")));
    CHECK_FALSE(phi::string_equals(null_view, std::string("")));

    CHECK_FALSE(phi::string_equals(phi::string_view("Hello"), null_string));
    CHECK(phi::string_equals(phi::string_view("Hello"), std::string("Hello")));
    CHECK_FALSE(phi::string_equals(phi::string_view("Hello"), std::string("")));

    CHECK(phi::string_equals(phi::string_view(""), null_string));
    CHECK_FALSE(phi::string_equals(phi::string_view(""), std::string("Hello")));
    CHECK(phi::string_equals(phi::string_view(""), std::string("")));
}

#if PHI_HAS_LIB_STRING_VIEW()
TEST_CASE("string_equals - std::string_view, nullptr_t")
{
    EXT_STATIC_REQUIRE(phi::string_equals(std_null_view, nullptr));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(std::string_view("Hello"), nullptr));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(std::string_view(""), nullptr));

    CHECK(phi::string_equals(std_null_view, nullptr));
    CHECK_FALSE(phi::string_equals(std::string_view("Hello"), nullptr));
    CHECK_FALSE(phi::string_equals(std::string_view(""), nullptr));
}

TEST_CASE("string_equals - std::string_view, char*")
{
    EXT_STATIC_REQUIRE(phi::string_equals(std_null_view, null));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(std_null_view, "Hello"));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(std_null_view, ""));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(std::string_view("Hello"), null));
    EXT_STATIC_REQUIRE(phi::string_equals(std::string_view("Hello"), "Hello"));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(std::string_view("Hello"), ""));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(std::string_view(""), null));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(std::string_view(""), "Hello"));
    EXT_STATIC_REQUIRE(phi::string_equals(std::string_view(""), ""));

    CHECK(phi::string_equals(std_null_view, null));
    CHECK_FALSE(phi::string_equals(std_null_view, "Hello"));
    CHECK_FALSE(phi::string_equals(std_null_view, ""));

    CHECK_FALSE(phi::string_equals(std::string_view("Hello"), null));
    CHECK(phi::string_equals(std::string_view("Hello"), "Hello"));
    CHECK_FALSE(phi::string_equals(std::string_view("Hello"), ""));

    CHECK_FALSE(phi::string_equals(std::string_view(""), null));
    CHECK_FALSE(phi::string_equals(std::string_view(""), "Hello"));
    CHECK(phi::string_equals(std::string_view(""), ""));
}

TEST_CASE("string_equals - std::string_view, phi::string_view")
{
    EXT_STATIC_REQUIRE(phi::string_equals(std_null_view, null_view));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(std_null_view, phi::string_view("Hello")));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(std_null_view, phi::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(std::string_view("Hello"), null_view));
    EXT_STATIC_REQUIRE(phi::string_equals(std::string_view("Hello"), phi::string_view("Hello")));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(std::string_view("Hello"), phi::string_view("")));

    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(std::string_view(""), null_view));
    EXT_STATIC_REQUIRE_FALSE(phi::string_equals(std::string_view(""), phi::string_view("Hello")));
    EXT_STATIC_REQUIRE(phi::string_equals(std::string_view(""), phi::string_view("")));

    CHECK(phi::string_equals(std_null_view, null_view));
    CHECK_FALSE(phi::string_equals(std_null_view, phi::string_view("Hello")));
    CHECK_FALSE(phi::string_equals(std_null_view, phi::string_view("")));

    CHECK_FALSE(phi::string_equals(std::string_view("Hello"), null_view));
    CHECK(phi::string_equals(std::string_view("Hello"), phi::string_view("Hello")));
    CHECK_FALSE(phi::string_equals(std::string_view("Hello"), phi::string_view("")));

    CHECK_FALSE(phi::string_equals(std::string_view(""), null_view));
    CHECK_FALSE(phi::string_equals(std::string_view(""), phi::string_view("Hello")));
    CHECK(phi::string_equals(std::string_view(""), phi::string_view("")));
}

TEST_CASE("string_equals - std::string_view, std::string")
{
    const std::string null_string;

    CHECK_FALSE(phi::string_equals(std_null_view, null_string));
    CHECK_FALSE(phi::string_equals(std_null_view, std::string("Hello")));
    CHECK_FALSE(phi::string_equals(std_null_view, std::string("")));

    CHECK_FALSE(phi::string_equals(std::string_view("Hello"), null_string));
    CHECK(phi::string_equals(std::string_view("Hello"), std::string("Hello")));
    CHECK_FALSE(phi::string_equals(std::string_view("Hello"), std::string("")));

    CHECK(phi::string_equals(std::string_view(""), null_string));
    CHECK_FALSE(phi::string_equals(std::string_view(""), std::string("Hello")));
    CHECK(phi::string_equals(std::string_view(""), std::string("")));
}
#endif

TEST_CASE("string_equals - std::string, nullptr_t")
{
    const std::string null_string;

    CHECK_FALSE(phi::string_equals(null_string, nullptr));
    CHECK_FALSE(phi::string_equals(std::string("Hello"), nullptr));
    CHECK_FALSE(phi::string_equals(std::string(""), nullptr));
}

TEST_CASE("string_equals - std::string, char*")
{
    const std::string null_string;

    CHECK_FALSE(phi::string_equals(null_string, null));
    CHECK_FALSE(phi::string_equals(null_string, "Hello"));
    CHECK(phi::string_equals(null_string, ""));

    CHECK_FALSE(phi::string_equals(std::string("Hello"), null));
    CHECK(phi::string_equals(std::string("Hello"), "Hello"));
    CHECK_FALSE(phi::string_equals(std::string("Hello"), ""));

    CHECK_FALSE(phi::string_equals(std::string(""), null));
    CHECK_FALSE(phi::string_equals(std::string(""), "Hello"));
    CHECK(phi::string_equals(std::string(""), ""));
}

TEST_CASE("string_equals - std::string, phi::string_view")
{
    const std::string null_string;

    CHECK_FALSE(phi::string_equals(null_string, null_view));
    CHECK_FALSE(phi::string_equals(null_string, phi::string_view("Hello")));
    CHECK(phi::string_equals(null_string, phi::string_view("")));

    CHECK_FALSE(phi::string_equals(std::string("Hello"), null_view));
    CHECK(phi::string_equals(std::string("Hello"), phi::string_view("Hello")));
    CHECK_FALSE(phi::string_equals(std::string("Hello"), phi::string_view("")));

    CHECK_FALSE(phi::string_equals(std::string(""), null_view));
    CHECK_FALSE(phi::string_equals(std::string(""), phi::string_view("Hello")));
    CHECK(phi::string_equals(std::string(""), phi::string_view("")));
}

#if PHI_HAS_LIB_STRING_VIEW()
TEST_CASE("string_equals - std::string, std::string_view")
{
    const std::string null_string;

    CHECK(phi::string_equals(null_string, std_null_view));
    CHECK_FALSE(phi::string_equals(null_string, std::string_view("Hello")));
    CHECK(phi::string_equals(null_string, std::string_view("")));

    CHECK_FALSE(phi::string_equals(std::string("Hello"), std_null_view));
    CHECK(phi::string_equals(std::string("Hello"), std::string_view("Hello")));
    CHECK_FALSE(phi::string_equals(std::string("Hello"), std::string_view("")));

    CHECK(phi::string_equals(std::string(""), std_null_view));
    CHECK_FALSE(phi::string_equals(std::string(""), std::string_view("Hello")));
    CHECK(phi::string_equals(std::string(""), std::string_view("")));
}
#endif

TEST_CASE("string_equals - std::string, std::string")
{
    const std::string null_string;

    CHECK(phi::string_equals(null_string, null_string));
    CHECK_FALSE(phi::string_equals(null_string, std::string("Hello")));
    CHECK(phi::string_equals(null_string, std::string("")));

    CHECK_FALSE(phi::string_equals(std::string("Hello"), null_string));
    CHECK(phi::string_equals(std::string("Hello"), std::string("Hello")));
    CHECK_FALSE(phi::string_equals(std::string("Hello"), std::string("")));

    CHECK(phi::string_equals(std::string(""), null_string));
    CHECK_FALSE(phi::string_equals(std::string(""), std::string("Hello")));
    CHECK(phi::string_equals(std::string(""), std::string("")));
}
