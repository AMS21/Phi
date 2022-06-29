#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/conversion.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/sized_types.hpp>
#include <phi/core/types.hpp>
#include <phi/phi_config.hpp>

#if defined(CATCH_CONFIG_RUNTIME_STATIC_REQUIRE) && PHI_COMPILER_IS(MSVC) && !defined(PHI_DEBUG)
#    define TEST_BUGGED_MSVC
#endif

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR() || !defined(PHI_DEBUG)
#    define TEST_NARROW_CAST(...) STATIC_REQUIRE(__VA_ARGS__)
#else
#    define TEST_NARROW_CAST(...) REQUIRE(__VA_ARGS__)
#endif

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wfloat-equal")

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wfloat-equal")
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")

template <typename TypeT>
void test_unsafe_cast_from_float()
{
    using FloatT = phi::floating_point<TypeT>;

    // from own type
    STATIC_REQUIRE(phi::unsafe_cast<FloatT>(FloatT(TypeT(3.14f))).unsafe() == TypeT(3.14f));
    STATIC_REQUIRE(phi::unsafe_cast<FloatT>(FloatT(TypeT(3.14))).unsafe() == TypeT(3.14));
    STATIC_REQUIRE(phi::unsafe_cast<FloatT>(FloatT(TypeT(3.14L))).unsafe() == TypeT(3.14L));

    // To native type
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::floating_point<float>(3.14f)) == TypeT(3.14f));
#if !defined(TEST_BUGGED_MSVC)
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::floating_point<double>(3.14)) == TypeT(3.14));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::floating_point<long double>(3.14L)) ==
                   TypeT(3.14L));
#endif
}

template <typename TypeT>
void test_unsafe_cast_from_integer()
{
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::i8(phi::int8_t(5))) == TypeT(5));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::i16(phi::int16_t(7))) == TypeT(7));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::i32(phi::int32_t(16))) == TypeT(16));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::i64(phi::int64_t(32))) == TypeT(32));

    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::u8(phi::uint8_t(1))) == TypeT(1));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::u16(phi::uint16_t(3))) == TypeT(3));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::u32(phi::uint32_t(12))) == TypeT(12));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::u64(phi::uint64_t(27))) == TypeT(27));
}

template <typename TypeT>
void test_unsafe_cast_to_integer()
{
    using vt = typename TypeT::value_type;

    // From T to T
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(TypeT(vt(5))).unsafe() == TypeT(vt(5)).unsafe());

    // From own Type
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(vt(32)).unsafe() == vt(32));

    // from unsafe types
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::int8_t(0)).unsafe() == vt(0));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::int16_t(1)).unsafe() == vt(1));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::int32_t(2)).unsafe() == vt(2));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::int64_t(3)).unsafe() == vt(3));

    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::uint8_t(4)).unsafe() == vt(4));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::uint16_t(5)).unsafe() == vt(5));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::uint32_t(6)).unsafe() == vt(6));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::uint64_t(7)).unsafe() == vt(7));

    // Fron safe type
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::i8(phi::int8_t(0))).unsafe() == vt(0));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::i16(phi::int16_t(1))).unsafe() == vt(1));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::i32(phi::int32_t(2))).unsafe() == vt(2));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::i64(phi::int64_t(3))).unsafe() == vt(3));

    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::u8(phi::uint8_t(4))).unsafe() == vt(4));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::u16(phi::uint16_t(5))).unsafe() == vt(5));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::u32(phi::uint32_t(6))).unsafe() == vt(6));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::u64(phi::uint64_t(7))).unsafe() == vt(7));
}

template <typename TypeT>
void test_unsafe_cast_to_float()
{
    using vt = typename TypeT::value_type;

    // from T to T
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(TypeT(3.14f)).unsafe() == TypeT(3.14f).unsafe());

    // from own type
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(vt(3.14)).unsafe() == vt(3.14));

    // from unsafe type
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(3.14f).unsafe() == vt(3.14f));
#if !defined(TEST_BUGGED_MSVC)
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(3.14).unsafe() == vt(3.14));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(3.14L).unsafe() == vt(3.14L));
#endif

    // from safe type
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::floating_point<float>(3.14f)).unsafe() ==
                   vt(3.14f));
#if !defined(TEST_BUGGED_MSVC)
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::floating_point<double>(3.14)).unsafe() == vt(3.14));
    STATIC_REQUIRE(phi::unsafe_cast<TypeT>(phi::floating_point<long double>(3.14L)).unsafe() ==
                   vt(3.14L));
#endif
}

template <typename TypeT>
void test_narrow_cast()
{
    TEST_NARROW_CAST(phi::narrow_cast<TypeT>(phi::int8_t(1)) == TypeT(1));
    TEST_NARROW_CAST(phi::narrow_cast<TypeT>(phi::int16_t(2)) == TypeT(2));
    TEST_NARROW_CAST(phi::narrow_cast<TypeT>(phi::int32_t(3)) == TypeT(3));
    TEST_NARROW_CAST(phi::narrow_cast<TypeT>(phi::int64_t(4)) == TypeT(4));

    TEST_NARROW_CAST(phi::narrow_cast<TypeT>(phi::uint8_t(1)) == TypeT(1));
    TEST_NARROW_CAST(phi::narrow_cast<TypeT>(phi::uint16_t(2)) == TypeT(2));
    TEST_NARROW_CAST(phi::narrow_cast<TypeT>(phi::uint32_t(3)) == TypeT(3));
    TEST_NARROW_CAST(phi::narrow_cast<TypeT>(phi::uint64_t(4)) == TypeT(4));
}

TEST_CASE("unsafe_cast")
{
    SECTION("unsafe_cast primitive types")
    {
        // Floats
        using ld = long double;

        STATIC_REQUIRE(phi::unsafe_cast<float>(3.14f) == 3.14f);
        STATIC_REQUIRE(phi::unsafe_cast<double>(3.14f) == double(3.14f));
        STATIC_REQUIRE(phi::unsafe_cast<ld>(3.14f) == ld(3.14f));

#if !defined(TEST_BUGGED_MSVC)
        STATIC_REQUIRE(phi::unsafe_cast<float>(3.14) == float(3.14));
#endif
        STATIC_REQUIRE(phi::unsafe_cast<double>(3.14) == 3.14);
        STATIC_REQUIRE(phi::unsafe_cast<ld>(3.14) == ld(3.14));

#if !defined(TEST_BUGGED_MSVC)
        STATIC_REQUIRE(phi::unsafe_cast<float>(3.14L) == float(3.14L));
#endif
        STATIC_REQUIRE(phi::unsafe_cast<double>(3.14L) == double(3.14L));
        STATIC_REQUIRE(phi::unsafe_cast<ld>(3.14L) == 3.14L);

        // integer
        // Signed -> Signed
        STATIC_REQUIRE(phi::unsafe_cast<phi::int8_t>(phi::int8_t(-1)) == phi::int8_t(-1));
        STATIC_REQUIRE(phi::unsafe_cast<phi::int16_t>(phi::int16_t(-2)) == phi::int16_t(-2));
        STATIC_REQUIRE(phi::unsafe_cast<phi::int32_t>(phi::int32_t(-3)) == phi::int32_t(-3));
        STATIC_REQUIRE(phi::unsafe_cast<phi::int64_t>(phi::int64_t(-4)) == phi::int64_t(-4));

        // Unsigned -> Unsigned
        STATIC_REQUIRE(phi::unsafe_cast<phi::uint8_t>(phi::uint8_t(1)) == phi::uint8_t(1));
        STATIC_REQUIRE(phi::unsafe_cast<phi::uint16_t>(phi::uint16_t(2)) == phi::uint16_t(2));
        STATIC_REQUIRE(phi::unsafe_cast<phi::uint32_t>(phi::uint32_t(3)) == phi::uint32_t(3));
        STATIC_REQUIRE(phi::unsafe_cast<phi::uint64_t>(phi::uint64_t(4)) == phi::uint64_t(4));

        // Signed -> Unsigned
        STATIC_REQUIRE(phi::unsafe_cast<phi::uint8_t>(phi::int8_t(1)) == phi::uint8_t(1));
        STATIC_REQUIRE(phi::unsafe_cast<phi::uint16_t>(phi::int16_t(2)) == phi::uint16_t(2));
        STATIC_REQUIRE(phi::unsafe_cast<phi::uint32_t>(phi::int32_t(3)) == phi::uint32_t(3));
        STATIC_REQUIRE(phi::unsafe_cast<phi::uint64_t>(phi::int64_t(4)) == phi::uint64_t(4));

        // Unsigned -> Signed
        STATIC_REQUIRE(phi::unsafe_cast<phi::int8_t>(phi::uint8_t(1)) == phi::int8_t(1));
        STATIC_REQUIRE(phi::unsafe_cast<phi::int16_t>(phi::uint16_t(2)) == phi::int16_t(2));
        STATIC_REQUIRE(phi::unsafe_cast<phi::int32_t>(phi::uint32_t(3)) == phi::int32_t(3));
        STATIC_REQUIRE(phi::unsafe_cast<phi::int64_t>(phi::uint64_t(4)) == phi::int64_t(4));

        // Bool
        STATIC_REQUIRE(phi::unsafe_cast<bool>(true));
        STATIC_REQUIRE_FALSE(phi::unsafe_cast<bool>(false));

        STATIC_REQUIRE(phi::unsafe_cast<bool>(1));
        STATIC_REQUIRE(phi::unsafe_cast<bool>(2));
        STATIC_REQUIRE_FALSE(phi::unsafe_cast<bool>(0));
    }

    SECTION("unsafe_cast from floating_point")
    {
        test_unsafe_cast_from_float<float>();
        test_unsafe_cast_from_float<double>();
        test_unsafe_cast_from_float<long double>();
    }

    SECTION("unsafe_cast from integer")
    {
        test_unsafe_cast_from_integer<phi::int8_t>();
        test_unsafe_cast_from_integer<phi::int16_t>();
        test_unsafe_cast_from_integer<phi::int32_t>();
        test_unsafe_cast_from_integer<phi::int64_t>();

        test_unsafe_cast_from_integer<phi::uint8_t>();
        test_unsafe_cast_from_integer<phi::uint16_t>();
        test_unsafe_cast_from_integer<phi::uint32_t>();
        test_unsafe_cast_from_integer<phi::uint64_t>();
    }

    SECTION("unsafe_cast to integer")
    {
        test_unsafe_cast_to_integer<phi::i8>();
        test_unsafe_cast_to_integer<phi::i16>();
        test_unsafe_cast_to_integer<phi::i32>();
        test_unsafe_cast_to_integer<phi::i64>();

        test_unsafe_cast_to_integer<phi::u8>();
        test_unsafe_cast_to_integer<phi::u16>();
        test_unsafe_cast_to_integer<phi::u32>();
        test_unsafe_cast_to_integer<phi::u64>();
    }

    SECTION("unsafe_cast to floating_point")
    {
        test_unsafe_cast_to_float<phi::floating_point<float>>();
        test_unsafe_cast_to_float<phi::floating_point<double>>();
        test_unsafe_cast_to_float<phi::floating_point<long double>>();
    }

    SECTION("narrow_cast")
    {
        test_narrow_cast<phi::int8_t>();
        test_narrow_cast<phi::int16_t>();
        test_narrow_cast<phi::int32_t>();
        test_narrow_cast<phi::int64_t>();

        test_narrow_cast<phi::uint8_t>();
        test_narrow_cast<phi::uint16_t>();
        test_narrow_cast<phi::uint32_t>();
        test_narrow_cast<phi::uint64_t>();
    }
}

PHI_GCC_SUPPRESS_WARNING_POP()

PHI_CLANG_SUPPRESS_WARNING_POP()
