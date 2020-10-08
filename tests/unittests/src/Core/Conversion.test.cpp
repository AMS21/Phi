#include <catch2/catch.hpp>

#include "Phi/Config/Compiler.hpp"
#include "Phi/Config/Warning.hpp"
#include <Phi/Core/Conversion.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Types.hpp>
#include <Phi/PhiConfig.hpp>

#if defined(CATCH_CONFIG_RUNTIME_STATIC_REQUIRE) && PHI_COMPILER_IS(MSVC) && !defined(PHI_DEBUG)
#    define TEST_BUGGED_MSVC
#endif

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wfloat-equal")

TEST_CASE("unsafe_cast primitive types", "[Utility][Types][Conversion][unsafe_cast]")
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

TEMPLATE_TEST_CASE("unsafe_cast from FloatingPoint", "[Utility][Types][Conversion][unsafe_cast]",
                   float, double, long double)
{
    using FloatT = phi::FloatingPoint<TestType>;

    // from own type
    STATIC_REQUIRE(phi::unsafe_cast<FloatT>(FloatT(TestType(3.14f))).get() == TestType(3.14f));
    STATIC_REQUIRE(phi::unsafe_cast<FloatT>(FloatT(TestType(3.14))).get() == TestType(3.14));
    STATIC_REQUIRE(phi::unsafe_cast<FloatT>(FloatT(TestType(3.14L))).get() == TestType(3.14L));

    // To native type
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(phi::FloatingPoint<float>(3.14f)) == TestType(3.14f));
#if !defined(TEST_BUGGED_MSVC)
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(phi::FloatingPoint<double>(3.14)) == TestType(3.14));
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(phi::FloatingPoint<long double>(3.14L)) ==
                   TestType(3.14L));
#endif
}

TEMPLATE_TEST_CASE("unsafe_cast from Integer", "[Utility][Types][Conversion][unsafe_cast]",
                   std::int8_t, std::int16_t, std::int32_t, std::int64_t, std::uint8_t,
                   std::uint16_t, std::uint32_t, std::uint64_t)
{
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(phi::i8(std::int8_t(5))) == TestType(5));
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(phi::i16(std::int16_t(7))) == TestType(7));
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(phi::i32(std::int32_t(16))) == TestType(16));
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(phi::i64(std::int64_t(32))) == TestType(32));

    STATIC_REQUIRE(phi::unsafe_cast<TestType>(phi::u8(std::uint8_t(1))) == TestType(1));
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(phi::u16(std::uint16_t(3))) == TestType(3));
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(phi::u32(std::uint32_t(12))) == TestType(12));
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(phi::u64(std::uint64_t(27))) == TestType(27));
}

TEMPLATE_TEST_CASE("unsafe_cast to Integer", "[Utility][Types][Conversion][unsafe_cast]", phi::i8,
                   phi::i16, phi::i32, phi::i64, phi::u8, phi::u16, phi::u32, phi::u64)
{
    using vt = typename TestType::value_type;

    // From TestType to TestType
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(TestType(vt(5))).get() == TestType(vt(5)).get());

    // From own Type
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(vt(32)).get() == vt(32));

    // from unsafe types
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(std::int8_t(0)).get() == vt(0));
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(std::int16_t(1)).get() == vt(1));
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(std::int32_t(2)).get() == vt(2));
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(std::int64_t(3)).get() == vt(3));

    STATIC_REQUIRE(phi::unsafe_cast<TestType>(std::uint8_t(4)).get() == vt(4));
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(std::uint16_t(5)).get() == vt(5));
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(std::uint32_t(6)).get() == vt(6));
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(std::uint64_t(7)).get() == vt(7));
}

TEMPLATE_TEST_CASE("unsafe_cast to FloatingPoint", "[Utility][Types][Conversion][unsafe_cast]",
                   phi::FloatingPoint<float>, phi::FloatingPoint<double>,
                   phi::FloatingPoint<long double>)
{
    using vt = typename TestType::value_type;

    // from TestType to TestType
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(TestType(3.14f)).get() == TestType(3.14f).get());

    // from own type
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(vt(3.14)).get() == vt(3.14));

    // from unsafe type
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(3.14f).get() == vt(3.14f));
#if !defined(TEST_BUGGED_MSVC)
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(3.14).get() == vt(3.14));
    STATIC_REQUIRE(phi::unsafe_cast<TestType>(3.14L).get() == vt(3.14L));
#endif
}

TEMPLATE_TEST_CASE("narrow_cast", "[Utility][Types][Conversion][narrow_cast]", std::int8_t,
                   std::int16_t, std::int32_t, std::int64_t, std::uint8_t, std::uint16_t,
                   std::uint32_t, std::uint64_t)
{
    STATIC_REQUIRE(phi::narrow_cast<TestType>(std::int8_t(1)) == TestType(1));
    STATIC_REQUIRE(phi::narrow_cast<TestType>(std::int16_t(2)) == TestType(2));
    STATIC_REQUIRE(phi::narrow_cast<TestType>(std::int32_t(3)) == TestType(3));
    STATIC_REQUIRE(phi::narrow_cast<TestType>(std::int64_t(4)) == TestType(4));

    STATIC_REQUIRE(phi::narrow_cast<TestType>(std::uint8_t(1)) == TestType(1));
    STATIC_REQUIRE(phi::narrow_cast<TestType>(std::uint16_t(2)) == TestType(2));
    STATIC_REQUIRE(phi::narrow_cast<TestType>(std::uint32_t(3)) == TestType(3));
    STATIC_REQUIRE(phi::narrow_cast<TestType>(std::uint64_t(4)) == TestType(4));
}

PHI_CLANG_SUPPRESS_WARNING_POP()
