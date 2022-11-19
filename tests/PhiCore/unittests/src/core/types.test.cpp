#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/warning.hpp>
#include <phi/core/types.hpp>
#include <phi/type_traits/is_safe_integer.hpp>
#include <phi/type_traits/is_signed.hpp>
#include <climits>
#include <type_traits>

#define SIZE_IN_BITS(type) (sizeof(type) * CHAR_BIT)

TEST_CASE("Types", "[Utility][Types]")
{
    SECTION("integers")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::i8) == 8);
        STATIC_REQUIRE(std::is_signed<phi::i8::value_type>::value);
        STATIC_REQUIRE(SIZE_IN_BITS(phi::u8) == 8);
        STATIC_REQUIRE(std::is_unsigned<phi::u8::value_type>::value);

        STATIC_REQUIRE(SIZE_IN_BITS(phi::i16) == 16);
        STATIC_REQUIRE(std::is_signed<phi::i16::value_type>::value);
        STATIC_REQUIRE(SIZE_IN_BITS(phi::u16) == 16);
        STATIC_REQUIRE(std::is_unsigned<phi::u16::value_type>::value);

        STATIC_REQUIRE(SIZE_IN_BITS(phi::i32) == 32);
        STATIC_REQUIRE(std::is_signed<phi::i32::value_type>::value);
        STATIC_REQUIRE(SIZE_IN_BITS(phi::u32) == 32);
        STATIC_REQUIRE(std::is_unsigned<phi::u32::value_type>::value);

        STATIC_REQUIRE(SIZE_IN_BITS(phi::i64) == 64);
        STATIC_REQUIRE(std::is_signed<phi::i64::value_type>::value);
        STATIC_REQUIRE(SIZE_IN_BITS(phi::u64) == 64);
        STATIC_REQUIRE(std::is_unsigned<phi::u64::value_type>::value);

        STATIC_REQUIRE(SIZE_IN_BITS(phi::i8_fast) >= 8);
        STATIC_REQUIRE(std::is_signed<phi::i8_fast::value_type>::value);
        STATIC_REQUIRE(SIZE_IN_BITS(phi::u8_fast) >= 8);
        STATIC_REQUIRE(std::is_unsigned<phi::u8_fast::value_type>::value);

        STATIC_REQUIRE(SIZE_IN_BITS(phi::i16_fast) >= 16);
        STATIC_REQUIRE(std::is_signed<phi::i16_fast::value_type>::value);
        STATIC_REQUIRE(SIZE_IN_BITS(phi::u16_fast) >= 16);
        STATIC_REQUIRE(std::is_unsigned<phi::u16_fast::value_type>::value);

        STATIC_REQUIRE(SIZE_IN_BITS(phi::i32_fast) >= 32);
        STATIC_REQUIRE(std::is_signed<phi::i32_fast::value_type>::value);
        STATIC_REQUIRE(SIZE_IN_BITS(phi::u32_fast) >= 32);
        STATIC_REQUIRE(std::is_unsigned<phi::u32_fast::value_type>::value);

        STATIC_REQUIRE(SIZE_IN_BITS(phi::i64_fast) >= 64);
        STATIC_REQUIRE(std::is_signed<phi::i64_fast::value_type>::value);
        STATIC_REQUIRE(SIZE_IN_BITS(phi::u64_fast) >= 64);
        STATIC_REQUIRE(std::is_unsigned<phi::u64_fast::value_type>::value);

        STATIC_REQUIRE(SIZE_IN_BITS(phi::isize) == SIZE_IN_BITS(phi::usize));
        STATIC_REQUIRE(std::is_signed<phi::isize::value_type>::value);
        STATIC_REQUIRE(std::is_unsigned<phi::usize::value_type>::value);
    }

    SECTION("floats")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::f32) == 32);
        STATIC_REQUIRE(std::is_floating_point<phi::f32::value_type>::value);

        STATIC_REQUIRE(SIZE_IN_BITS(phi::f64) == 64);
        STATIC_REQUIRE(std::is_floating_point<phi::f64::value_type>::value);
    }
}

TEST_CASE("intptr")
{
    STATIC_REQUIRE(sizeof(phi::intptr) == sizeof(phi::intptr_t));
    STATIC_REQUIRE(sizeof(phi::intptr) == sizeof(phi::uintptr_t));
    STATIC_REQUIRE(sizeof(phi::intptr) == sizeof(void*));
    STATIC_REQUIRE(phi::is_safe_integer<phi::intptr>::value);

    STATIC_REQUIRE(std::is_signed<phi::intptr::value_type>::value);
    STATIC_REQUIRE_FALSE(std::is_unsigned<phi::intptr::value_type>::value);
    STATIC_REQUIRE(phi::is_signed<phi::intptr>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsigned<phi::intptr>::value);
}

TEST_CASE("uintptr")
{
    STATIC_REQUIRE(sizeof(phi::uintptr) == sizeof(phi::uintptr_t));
    STATIC_REQUIRE(sizeof(phi::uintptr) == sizeof(phi::intptr_t));
    STATIC_REQUIRE(sizeof(phi::uintptr) == sizeof(void*));
    STATIC_REQUIRE(phi::is_safe_integer<phi::uintptr>::value);

    STATIC_REQUIRE_FALSE(std::is_signed<phi::uintptr::value_type>::value);
    STATIC_REQUIRE(std::is_unsigned<phi::uintptr::value_type>::value);
    STATIC_REQUIRE_FALSE(phi::is_signed<phi::uintptr>::value);
    STATIC_REQUIRE(phi::is_unsigned<phi::uintptr>::value);
}
