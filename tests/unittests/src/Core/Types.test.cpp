#include <catch2/catch.hpp>

#include <Phi/Core/Types.hpp>
#include <climits>
#include <type_traits>

#define SIZE_IN_BITS(type) (sizeof(type) * CHAR_BIT)

TEST_CASE("Types", "[Utility][Types]")
{
    SECTION("integers")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::i8) == 8);
        STATIC_REQUIRE(std::is_signed_v<phi::i8::value_type>);
        STATIC_REQUIRE(SIZE_IN_BITS(phi::u8) == 8);
        STATIC_REQUIRE(std::is_unsigned_v<phi::u8::value_type>);

        STATIC_REQUIRE(SIZE_IN_BITS(phi::i16) == 16);
        STATIC_REQUIRE(std::is_signed_v<phi::i16::value_type>);
        STATIC_REQUIRE(SIZE_IN_BITS(phi::u16) == 16);
        STATIC_REQUIRE(std::is_unsigned_v<phi::u16::value_type>);

        STATIC_REQUIRE(SIZE_IN_BITS(phi::i32) == 32);
        STATIC_REQUIRE(std::is_signed_v<phi::i32::value_type>);
        STATIC_REQUIRE(SIZE_IN_BITS(phi::u32) == 32);
        STATIC_REQUIRE(std::is_unsigned_v<phi::u32::value_type>);

        STATIC_REQUIRE(SIZE_IN_BITS(phi::i64) == 64);
        STATIC_REQUIRE(std::is_signed_v<phi::i64::value_type>);
        STATIC_REQUIRE(SIZE_IN_BITS(phi::u64) == 64);
        STATIC_REQUIRE(std::is_unsigned_v<phi::u64::value_type>);

        STATIC_REQUIRE(SIZE_IN_BITS(phi::isize) == SIZE_IN_BITS(phi::usize));
        STATIC_REQUIRE(std::is_signed_v<phi::isize::value_type>);
        STATIC_REQUIRE(std::is_unsigned_v<phi::usize::value_type>);

        STATIC_REQUIRE(SIZE_IN_BITS(phi::imax) >= SIZE_IN_BITS(phi::i64));
        STATIC_REQUIRE(std::is_signed_v<phi::imax::value_type>);
        STATIC_REQUIRE(SIZE_IN_BITS(phi::umax) >= SIZE_IN_BITS(phi::u64));
        STATIC_REQUIRE(std::is_unsigned_v<phi::umax::value_type>);
    }

    SECTION("floats")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::f32) == 32);
        STATIC_REQUIRE(std::is_floating_point_v<phi::f32::value_type>);

        STATIC_REQUIRE(SIZE_IN_BITS(phi::f64) == 64);
        STATIC_REQUIRE(std::is_floating_point_v<phi::f64::value_type>);

        STATIC_REQUIRE(SIZE_IN_BITS(phi::fmax) >= SIZE_IN_BITS(phi::f64));
        STATIC_REQUIRE(std::is_floating_point_v<phi::fmax::value_type>);
    }
}
