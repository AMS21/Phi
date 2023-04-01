#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/core/memcmp.hpp>

TEST_CASE("memcmp")
{
    EXT_STATIC_REQUIRE(phi::memcmp(nullptr, nullptr, 0) == 0);

    // Equals (returns 0)
    EXT_STATIC_REQUIRE(phi::memcmp("123456", "123456", 7) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp("", "", 1) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp("abc", "abc", 4) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp("hello", "hello", 6) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp("1234567890", "123456000", 6) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp("hi", "hi", 2) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp("ha", "hb", 1) == 0);

    // left hand side is greater (returns negative value)
    EXT_STATIC_REQUIRE(phi::memcmp("ABC", "abc", 4) < 0);
    EXT_STATIC_REQUIRE(phi::memcmp("123", "124", 4) < 0);
    EXT_STATIC_REQUIRE(phi::memcmp("", "abc", 4) < 0);
    EXT_STATIC_REQUIRE(phi::memcmp("abc", "abd", 4) < 0);
    EXT_STATIC_REQUIRE(phi::memcmp("abc", "zyx", 1) < 0);

    // right hand side is greater (returns positive value)
    EXT_STATIC_REQUIRE(phi::memcmp("abc", "ABC", 4) > 0);
    EXT_STATIC_REQUIRE(phi::memcmp("124", "123", 4) > 0);
    EXT_STATIC_REQUIRE(phi::memcmp("abc", "", 4) > 0);
    EXT_STATIC_REQUIRE(phi::memcmp("abd", "abc", 4) > 0);
    EXT_STATIC_REQUIRE(phi::memcmp("zyx", "abc", 1) > 0);
}
