#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/compiler_support/constexpr.hpp>
#include <phi/core/memcmp.hpp>

static PHI_CONSTEXPR_AND_CONST int* int_nullptr   = nullptr;
static PHI_CONSTEXPR_AND_CONST int  integer_value = 21;
static PHI_CONSTEXPR_AND_CONST int* int_ptr       = &integer_value;

TEST_CASE("memcmp")
{
    // nullptr - nullptr
    EXT_STATIC_REQUIRE(phi::memcmp(nullptr, nullptr, 0) == 0);
    CHECK(phi::memcmp(nullptr, nullptr, 0) == 0);

    // nullptr - non-nullptr
    EXT_STATIC_REQUIRE(phi::memcmp(nullptr, int_nullptr, 0) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp(nullptr, int_ptr, 0) < 0);
    CHECK(phi::memcmp(nullptr, int_nullptr, 0) == 0);
    CHECK(phi::memcmp(nullptr, int_ptr, 0) < 0);

    // non-nullptr - nullptr
    EXT_STATIC_REQUIRE(phi::memcmp(int_nullptr, nullptr, 0) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp(int_ptr, nullptr, 0) > 0);
    CHECK(phi::memcmp(int_nullptr, nullptr, 0) == 0);
    CHECK(phi::memcmp(int_ptr, nullptr, 0) > 0);

    // Equals (returns 0)
    EXT_STATIC_REQUIRE(phi::memcmp("123456", "123456", 7) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp("", "", 1) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp("abc", "abc", 4) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp("hello", "hello", 6) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp("1234567890", "123456000", 6) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp("hi", "hi", 2) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp("ha", "hb", 1) == 0);

    CHECK(phi::memcmp("123456", "123456", 7) == 0);
    CHECK(phi::memcmp("", "", 1) == 0);
    CHECK(phi::memcmp("abc", "abc", 4) == 0);
    CHECK(phi::memcmp("hello", "hello", 6) == 0);
    CHECK(phi::memcmp("1234567890", "123456000", 6) == 0);
    CHECK(phi::memcmp("hi", "hi", 2) == 0);
    CHECK(phi::memcmp("ha", "hb", 1) == 0);

    // left hand side is greater (returns negative value)
    EXT_STATIC_REQUIRE(phi::memcmp("ABC", "abc", 4) < 0);
    EXT_STATIC_REQUIRE(phi::memcmp("123", "124", 4) < 0);
    EXT_STATIC_REQUIRE(phi::memcmp("", "abc", 1) < 0);
    EXT_STATIC_REQUIRE(phi::memcmp("abc", "abd", 4) < 0);
    EXT_STATIC_REQUIRE(phi::memcmp("abc", "zyx", 1) < 0);

    CHECK(phi::memcmp("ABC", "abc", 4) < 0);
    CHECK(phi::memcmp("123", "124", 4) < 0);
    CHECK(phi::memcmp("", "abc", 1) < 0);
    CHECK(phi::memcmp("abc", "abd", 4) < 0);
    CHECK(phi::memcmp("abc", "zyx", 1) < 0);

    // right hand side is greater (returns positive value)
    EXT_STATIC_REQUIRE(phi::memcmp("abc", "ABC", 4) > 0);
    EXT_STATIC_REQUIRE(phi::memcmp("124", "123", 4) > 0);
    EXT_STATIC_REQUIRE(phi::memcmp("abc", "", 1) > 0);
    EXT_STATIC_REQUIRE(phi::memcmp("abd", "abc", 4) > 0);
    EXT_STATIC_REQUIRE(phi::memcmp("zyx", "abc", 1) > 0);

    CHECK(phi::memcmp("abc", "ABC", 4) > 0);
    CHECK(phi::memcmp("124", "123", 4) > 0);
    CHECK(phi::memcmp("abc", "", 1) > 0);
    CHECK(phi::memcmp("abd", "abc", 4) > 0);
    CHECK(phi::memcmp("zyx", "abc", 1) > 0);
}
