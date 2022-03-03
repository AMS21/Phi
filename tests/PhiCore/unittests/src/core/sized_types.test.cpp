#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/platform.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/sized_types.hpp>
#include <phi/type_traits/is_signed.hpp>
#include <phi/type_traits/is_unsigned.hpp>

PHI_EXTERNAL_HEADERS_BEGIN()
#include <climits>
#include <cstdint>
PHI_EXTERNAL_HEADERS_END()

#define SIZE_IN_BITS(x) (sizeof(x) * CHAR_BIT)

// TODO: MSVC and Apple seem to disagree with us on the actual type of some of these here

TEST_CASE("sized_types")
{
    SECTION("int8_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::int8_t) == 8);
        STATIC_REQUIRE(phi::is_signed<phi::int8_t>::value);
        STATIC_REQUIRE_FALSE(phi::is_unsigned<phi::int8_t>::value);
        CHECK_SAME_TYPE(phi::int8_t, std::int8_t);
    }

    SECTION("int16_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::int16_t) == 16);
        STATIC_REQUIRE(phi::is_signed<phi::int16_t>::value);
        STATIC_REQUIRE_FALSE(phi::is_unsigned<phi::int16_t>::value);
        CHECK_SAME_TYPE(phi::int16_t, std::int16_t);
    }

    SECTION("int32_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::int32_t) == 32);
        STATIC_REQUIRE(phi::is_signed<phi::int32_t>::value);
        STATIC_REQUIRE_FALSE(phi::is_unsigned<phi::int32_t>::value);
        CHECK_SAME_TYPE(phi::int32_t, std::int32_t);
    }

    SECTION("int64_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::int64_t) == 64);
        STATIC_REQUIRE(phi::is_signed<phi::int64_t>::value);
        STATIC_REQUIRE_FALSE(phi::is_unsigned<phi::int64_t>::value);

#if PHI_PLATFORM_IS_NOT(APPLE)
        CHECK_SAME_TYPE(phi::int64_t, std::int64_t);
#endif
    }

    SECTION("intmax_t")
    {
        CHECK_SAME_TYPE(phi::intmax_t, phi::int64_t);
        STATIC_REQUIRE(SIZE_IN_BITS(phi::intmax_t) == 64);
        STATIC_REQUIRE(phi::is_signed<phi::intmax_t>::value);
        STATIC_REQUIRE_FALSE(phi::is_unsigned<phi::intmax_t>::value);
        CHECK_SAME_TYPE(phi::intmax_t, std::intmax_t);
    }

    SECTION("uint8_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::uint8_t) == 8);
        STATIC_REQUIRE_FALSE(phi::is_signed<phi::uint8_t>::value);
        STATIC_REQUIRE(phi::is_unsigned<phi::uint8_t>::value);
        CHECK_SAME_TYPE(phi::uint8_t, std::uint8_t);
    }

    SECTION("uint16_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::uint16_t) == 16);
        STATIC_REQUIRE_FALSE(phi::is_signed<phi::uint16_t>::value);
        STATIC_REQUIRE(phi::is_unsigned<phi::uint16_t>::value);
        CHECK_SAME_TYPE(phi::uint16_t, std::uint16_t);
    }

    SECTION("uint32_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::uint32_t) == 32);
        STATIC_REQUIRE_FALSE(phi::is_signed<phi::uint32_t>::value);
        STATIC_REQUIRE(phi::is_unsigned<phi::uint32_t>::value);
        CHECK_SAME_TYPE(phi::uint32_t, std::uint32_t);
    }

    SECTION("uint64_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::uint64_t) == 64);
        STATIC_REQUIRE_FALSE(phi::is_signed<phi::uint64_t>::value);
        STATIC_REQUIRE(phi::is_unsigned<phi::uint64_t>::value);
#if PHI_PLATFORM_IS_NOT(APPLE)
        CHECK_SAME_TYPE(phi::uint64_t, std::uint64_t);
#endif
    }

    SECTION("uintmax_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::uintmax_t) == 64);
        STATIC_REQUIRE_FALSE(phi::is_signed<phi::uintmax_t>::value);
        STATIC_REQUIRE(phi::is_unsigned<phi::uintmax_t>::value);
        CHECK_SAME_TYPE(phi::uintmax_t, phi::uint64_t);
        CHECK_SAME_TYPE(phi::uintmax_t, std::uintmax_t);
    }

    SECTION("int_fast8_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::int_fast8_t) >= 8);
        STATIC_REQUIRE(phi::is_signed<phi::int_fast8_t>::value);
        STATIC_REQUIRE_FALSE(phi::is_unsigned<phi::int_fast8_t>::value);
        CHECK_SAME_TYPE(phi::int_fast8_t, std::int_fast8_t);
    }

    SECTION("int_fast16_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::int_fast16_t) >= 16);
        STATIC_REQUIRE(phi::is_signed<phi::int_fast16_t>::value);
        STATIC_REQUIRE_FALSE(phi::is_unsigned<phi::int_fast16_t>::value);
#if PHI_PLATFORM_IS(APPLE) || PHI_COMPILER_IS(MSVC)
#else
        CHECK_SAME_TYPE(phi::int_fast16_t, std::int_fast16_t);
#endif
    }

    SECTION("int_fast32_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::int_fast32_t) >= 32);
        STATIC_REQUIRE(phi::is_signed<phi::int_fast32_t>::value);
        STATIC_REQUIRE_FALSE(phi::is_unsigned<phi::int_fast32_t>::value);
#if PHI_PLATFORM_IS(APPLE) || PHI_COMPILER_IS(MSVC)
#else
        CHECK_SAME_TYPE(phi::int_fast32_t, std::int_fast32_t);
#endif
    }

    SECTION("int_fast64_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::int_fast64_t) >= 64);
        STATIC_REQUIRE(phi::is_signed<phi::int_fast64_t>::value);
        STATIC_REQUIRE_FALSE(phi::is_unsigned<phi::int_fast64_t>::value);
#if PHI_PLATFORM_IS(APPLE) || PHI_COMPILER_IS(MSVC)
#else
        CHECK_SAME_TYPE(phi::int_fast64_t, std::int_fast64_t);
#endif
    }

    SECTION("uint_fast8_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::uint_fast8_t) >= 8);
        STATIC_REQUIRE_FALSE(phi::is_signed<phi::uint_fast8_t>::value);
        STATIC_REQUIRE(phi::is_unsigned<phi::uint_fast8_t>::value);
        CHECK_SAME_TYPE(phi::uint_fast8_t, std::uint_fast8_t);
    }

    SECTION("uint_fast16_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::uint_fast16_t) >= 16);
        STATIC_REQUIRE_FALSE(phi::is_signed<phi::uint_fast16_t>::value);
        STATIC_REQUIRE(phi::is_unsigned<phi::uint_fast16_t>::value);
#if PHI_PLATFORM_IS(APPLE) || PHI_COMPILER_IS(MSVC)
#else
        CHECK_SAME_TYPE(phi::uint_fast16_t, std::uint_fast16_t);
#endif
    }

    SECTION("uint_fast32_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::uint_fast32_t) >= 32);
        STATIC_REQUIRE_FALSE(phi::is_signed<phi::uint_fast32_t>::value);
        STATIC_REQUIRE(phi::is_unsigned<phi::uint_fast32_t>::value);
#if PHI_PLATFORM_IS(APPLE) || PHI_COMPILER_IS(MSVC)
#else
        CHECK_SAME_TYPE(phi::uint_fast32_t, std::uint_fast32_t);
#endif
    }

    SECTION("uint_fast64_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::uint_fast64_t) >= 64);
        STATIC_REQUIRE_FALSE(phi::is_signed<phi::uint_fast64_t>::value);
        STATIC_REQUIRE(phi::is_unsigned<phi::uint_fast64_t>::value);
#if PHI_PLATFORM_IS_NOT(APPLE)
        CHECK_SAME_TYPE(phi::uint_fast64_t, std::uint_fast64_t);
#endif
    }

    SECTION("int_least8_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::int_least8_t) >= 8);
        STATIC_REQUIRE(phi::is_signed<phi::int_least8_t>::value);
        STATIC_REQUIRE_FALSE(phi::is_unsigned<phi::int_least8_t>::value);
        CHECK_SAME_TYPE(phi::int_least8_t, std::int_least8_t);
    }

    SECTION("int_least16_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::int_least16_t) >= 16);
        STATIC_REQUIRE(phi::is_signed<phi::int_least16_t>::value);
        STATIC_REQUIRE_FALSE(phi::is_unsigned<phi::int_least16_t>::value);
        CHECK_SAME_TYPE(phi::int_least16_t, std::int_least16_t);
    }

    SECTION("int_least32_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::int_least32_t) >= 32);
        STATIC_REQUIRE(phi::is_signed<phi::int_least32_t>::value);
        STATIC_REQUIRE_FALSE(phi::is_unsigned<phi::int_least32_t>::value);
        CHECK_SAME_TYPE(phi::int_least32_t, std::int_least32_t);
    }

    SECTION("int_least64_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::int_least64_t) >= 64);
        STATIC_REQUIRE(phi::is_signed<phi::int_least64_t>::value);
        STATIC_REQUIRE_FALSE(phi::is_unsigned<phi::int_least64_t>::value);
#if PHI_PLATFORM_IS(APPLE) || PHI_COMPILER_IS(MSVC)
#else
        CHECK_SAME_TYPE(phi::int_least64_t, std::int_least64_t);
#endif
    }

    SECTION("uint_least8_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::uint_least8_t) >= 8);
        STATIC_REQUIRE_FALSE(phi::is_signed<phi::uint_least8_t>::value);
        STATIC_REQUIRE(phi::is_unsigned<phi::uint_least8_t>::value);
#if PHI_PLATFORM_IS_NOT(APPLE)
        CHECK_SAME_TYPE(phi::uint_least8_t, std::uint_least8_t);
#endif
    }

    SECTION("uint_least16_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::uint_least16_t) >= 16);
        STATIC_REQUIRE_FALSE(phi::is_signed<phi::uint_least16_t>::value);
        STATIC_REQUIRE(phi::is_unsigned<phi::uint_least16_t>::value);
        CHECK_SAME_TYPE(phi::uint_least16_t, std::uint_least16_t);
    }

    SECTION("uint_least32_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::uint_least32_t) >= 32);
        STATIC_REQUIRE_FALSE(phi::is_signed<phi::uint_least32_t>::value);
        STATIC_REQUIRE(phi::is_unsigned<phi::uint_least32_t>::value);
        CHECK_SAME_TYPE(phi::uint_least32_t, std::uint_least32_t);
    }

    SECTION("uint_least64_t")
    {
        STATIC_REQUIRE(SIZE_IN_BITS(phi::uint_least64_t) >= 64);
        STATIC_REQUIRE_FALSE(phi::is_signed<phi::uint_least64_t>::value);
        STATIC_REQUIRE(phi::is_unsigned<phi::uint_least64_t>::value);
#if PHI_PLATFORM_IS_NOT(APPLE)
        CHECK_SAME_TYPE(phi::uint_least64_t, std::uint_least64_t);
#endif
    }
}
