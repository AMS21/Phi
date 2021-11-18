#include <Phi/Test/TestMacros.hpp>

#include <Phi/Config/Compiler.hpp>
#include <Phi/Config/Warning.hpp>
#include <Phi/Core/Conversion.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Types.hpp>
#include <Phi/PhiConfig.hpp>

#if defined(CATCH_CONFIG_RUNTIME_STATIC_REQUIRE) && PHI_COMPILER_IS(MSVC) && !defined(PHI_DEBUG)
#    define TEST_BUGGED_MSVC
#endif

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wfloat-equal")

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wfloat-equal")
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")

template <typename T>
void test_unsafe_cast_from_float()
{
    using FloatT = phi::FloatingPoint<T>;

    // from own type
    STATIC_REQUIRE(phi::unsafe_cast<FloatT>(FloatT(T(3.14f))).get() == T(3.14f));
    STATIC_REQUIRE(phi::unsafe_cast<FloatT>(FloatT(T(3.14))).get() == T(3.14));
    STATIC_REQUIRE(phi::unsafe_cast<FloatT>(FloatT(T(3.14L))).get() == T(3.14L));

    // To native type
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::FloatingPoint<float>(3.14f)) == T(3.14f));
#if !defined(TEST_BUGGED_MSVC)
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::FloatingPoint<double>(3.14)) == T(3.14));
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::FloatingPoint<long double>(3.14L)) == T(3.14L));
#endif
}

template <typename T>
void test_unsafe_cast_from_integer()
{
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::i8(std::int8_t(5))) == T(5));
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::i16(std::int16_t(7))) == T(7));
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::i32(std::int32_t(16))) == T(16));
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::i64(std::int64_t(32))) == T(32));

    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::u8(std::uint8_t(1))) == T(1));
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::u16(std::uint16_t(3))) == T(3));
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::u32(std::uint32_t(12))) == T(12));
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::u64(std::uint64_t(27))) == T(27));
}

template <typename T>
void test_unsafe_cast_to_integer()
{
    using vt = typename T::value_type;

    // From T to T
    STATIC_REQUIRE(phi::unsafe_cast<T>(T(vt(5))).get() == T(vt(5)).get());

    // From own Type
    STATIC_REQUIRE(phi::unsafe_cast<T>(vt(32)).get() == vt(32));

    // from unsafe types
    STATIC_REQUIRE(phi::unsafe_cast<T>(std::int8_t(0)).get() == vt(0));
    STATIC_REQUIRE(phi::unsafe_cast<T>(std::int16_t(1)).get() == vt(1));
    STATIC_REQUIRE(phi::unsafe_cast<T>(std::int32_t(2)).get() == vt(2));
    STATIC_REQUIRE(phi::unsafe_cast<T>(std::int64_t(3)).get() == vt(3));

    STATIC_REQUIRE(phi::unsafe_cast<T>(std::uint8_t(4)).get() == vt(4));
    STATIC_REQUIRE(phi::unsafe_cast<T>(std::uint16_t(5)).get() == vt(5));
    STATIC_REQUIRE(phi::unsafe_cast<T>(std::uint32_t(6)).get() == vt(6));
    STATIC_REQUIRE(phi::unsafe_cast<T>(std::uint64_t(7)).get() == vt(7));

    // Fron safe type
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::i8(std::int8_t(0))).get() == vt(0));
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::i16(std::int16_t(1))).get() == vt(1));
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::i32(std::int32_t(2))).get() == vt(2));
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::i64(std::int64_t(3))).get() == vt(3));

    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::u8(std::uint8_t(4))).get() == vt(4));
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::u16(std::uint16_t(5))).get() == vt(5));
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::u32(std::uint32_t(6))).get() == vt(6));
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::u64(std::uint64_t(7))).get() == vt(7));
}

template <typename T>
void test_unsafe_cast_to_float()
{
    using vt = typename T::value_type;

    // from T to T
    STATIC_REQUIRE(phi::unsafe_cast<T>(T(3.14f)).get() == T(3.14f).get());

    // from own type
    STATIC_REQUIRE(phi::unsafe_cast<T>(vt(3.14)).get() == vt(3.14));

    // from unsafe type
    STATIC_REQUIRE(phi::unsafe_cast<T>(3.14f).get() == vt(3.14f));
#if !defined(TEST_BUGGED_MSVC)
    STATIC_REQUIRE(phi::unsafe_cast<T>(3.14).get() == vt(3.14));
    STATIC_REQUIRE(phi::unsafe_cast<T>(3.14L).get() == vt(3.14L));
#endif

    // from safe type
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::FloatingPoint<float>(3.14f)).get() == vt(3.14f));
#if !defined(TEST_BUGGED_MSVC)
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::FloatingPoint<double>(3.14)).get() == vt(3.14));
    STATIC_REQUIRE(phi::unsafe_cast<T>(phi::FloatingPoint<long double>(3.14L)).get() == vt(3.14L));
#endif
}

template <typename T>
void test_narrow_cast()
{
    STATIC_REQUIRE(phi::narrow_cast<T>(std::int8_t(1)) == T(1));
    STATIC_REQUIRE(phi::narrow_cast<T>(std::int16_t(2)) == T(2));
    STATIC_REQUIRE(phi::narrow_cast<T>(std::int32_t(3)) == T(3));
    STATIC_REQUIRE(phi::narrow_cast<T>(std::int64_t(4)) == T(4));

    STATIC_REQUIRE(phi::narrow_cast<T>(std::uint8_t(1)) == T(1));
    STATIC_REQUIRE(phi::narrow_cast<T>(std::uint16_t(2)) == T(2));
    STATIC_REQUIRE(phi::narrow_cast<T>(std::uint32_t(3)) == T(3));
    STATIC_REQUIRE(phi::narrow_cast<T>(std::uint64_t(4)) == T(4));
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

        // Integer
        // Signed -> Signed
        STATIC_REQUIRE(phi::unsafe_cast<std::int8_t>(std::int8_t(-1)) == std::int8_t(-1));
        STATIC_REQUIRE(phi::unsafe_cast<std::int16_t>(std::int16_t(-2)) == std::int16_t(-2));
        STATIC_REQUIRE(phi::unsafe_cast<std::int32_t>(std::int32_t(-3)) == std::int32_t(-3));
        STATIC_REQUIRE(phi::unsafe_cast<std::int64_t>(std::int64_t(-4)) == std::int64_t(-4));

        // Unsigned -> Unsigned
        STATIC_REQUIRE(phi::unsafe_cast<std::uint8_t>(std::uint8_t(1)) == std::uint8_t(1));
        STATIC_REQUIRE(phi::unsafe_cast<std::uint16_t>(std::uint16_t(2)) == std::uint16_t(2));
        STATIC_REQUIRE(phi::unsafe_cast<std::uint32_t>(std::uint32_t(3)) == std::uint32_t(3));
        STATIC_REQUIRE(phi::unsafe_cast<std::uint64_t>(std::uint64_t(4)) == std::uint64_t(4));

        // Signed -> Unsigned
        STATIC_REQUIRE(phi::unsafe_cast<std::uint8_t>(std::int8_t(1)) == std::uint8_t(1));
        STATIC_REQUIRE(phi::unsafe_cast<std::uint16_t>(std::int16_t(2)) == std::uint16_t(2));
        STATIC_REQUIRE(phi::unsafe_cast<std::uint32_t>(std::int32_t(3)) == std::uint32_t(3));
        STATIC_REQUIRE(phi::unsafe_cast<std::uint64_t>(std::int64_t(4)) == std::uint64_t(4));

        // Unsigned -> Signed
        STATIC_REQUIRE(phi::unsafe_cast<std::int8_t>(std::uint8_t(1)) == std::int8_t(1));
        STATIC_REQUIRE(phi::unsafe_cast<std::int16_t>(std::uint16_t(2)) == std::int16_t(2));
        STATIC_REQUIRE(phi::unsafe_cast<std::int32_t>(std::uint32_t(3)) == std::int32_t(3));
        STATIC_REQUIRE(phi::unsafe_cast<std::int64_t>(std::uint64_t(4)) == std::int64_t(4));

        // Bool
        STATIC_REQUIRE(phi::unsafe_cast<bool>(true));
        STATIC_REQUIRE_FALSE(phi::unsafe_cast<bool>(false));

        STATIC_REQUIRE(phi::unsafe_cast<bool>(1));
        STATIC_REQUIRE(phi::unsafe_cast<bool>(2));
        STATIC_REQUIRE_FALSE(phi::unsafe_cast<bool>(0));
    }

    SECTION("unsafe_cast from FloatingPoint")
    {
        test_unsafe_cast_from_float<float>();
        test_unsafe_cast_from_float<double>();
        test_unsafe_cast_from_float<long double>();
    }

    SECTION("unsafe_cast from Integer")
    {
        test_unsafe_cast_from_integer<std::int8_t>();
        test_unsafe_cast_from_integer<std::int16_t>();
        test_unsafe_cast_from_integer<std::int32_t>();
        test_unsafe_cast_from_integer<std::int64_t>();

        test_unsafe_cast_from_integer<std::uint8_t>();
        test_unsafe_cast_from_integer<std::uint16_t>();
        test_unsafe_cast_from_integer<std::uint32_t>();
        test_unsafe_cast_from_integer<std::uint64_t>();
    }

    SECTION("unsafe_cast to Integer")
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

    SECTION("unsafe_cast to FloatingPoint")
    {
        test_unsafe_cast_to_float<phi::FloatingPoint<float>>();
        test_unsafe_cast_to_float<phi::FloatingPoint<double>>();
        test_unsafe_cast_to_float<phi::FloatingPoint<long double>>();
    }

    SECTION("narrow_cast")
    {
        test_narrow_cast<std::int8_t>();
        test_narrow_cast<std::int16_t>();
        test_narrow_cast<std::int32_t>();
        test_narrow_cast<std::int64_t>();

        test_narrow_cast<std::uint8_t>();
        test_narrow_cast<std::uint16_t>();
        test_narrow_cast<std::uint32_t>();
        test_narrow_cast<std::uint64_t>();
    }
}

PHI_GCC_SUPPRESS_WARNING_POP()

PHI_CLANG_SUPPRESS_WARNING_POP()
