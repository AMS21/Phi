#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/char8_t.hpp>
#include <climits>
#include <type_traits>

TEST_CASE("Compiler support - char8_t")
{
    STATIC_REQUIRE(sizeof(char8_t) * CHAR_BIT == 8);

    // Type traits
    STATIC_REQUIRE(std::is_unsigned<char8_t>::value);
    STATIC_REQUIRE_FALSE(std::is_signed<char8_t>::value);
    STATIC_REQUIRE(std::is_integral<char8_t>::value);
    STATIC_REQUIRE_FALSE(std::is_enum<char8_t>::value);
    STATIC_REQUIRE(std::is_fundamental<char8_t>::value);
    STATIC_REQUIRE(std::is_arithmetic<char8_t>::value);
    STATIC_REQUIRE(std::is_trivial<char8_t>::value);
    STATIC_REQUIRE_FALSE(std::is_class<char8_t>::value);
}
