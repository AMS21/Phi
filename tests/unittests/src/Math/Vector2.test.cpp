#include <catch2/catch_template_test_macros.hpp>

#include <Phi/Math/Vector2.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Types.hpp>
#include <Phi/Config/Warning.hpp>
#include "Unwrap.hpp"
#include "ConstexprHelper.hpp"

#define TEST_ALL_TYPES() char, signed char, unsigned char, short, unsigned short, int, unsigned, long, unsigned long, long long, unsigned long long, float, double, long double, phi::i8, phi::i16, phi::i32, phi::i64, phi::u8, phi::u16, phi::u32, phi::u64, phi::FloatingPoint<float>, phi::FloatingPoint<double>, phi::FloatingPoint<long double>

PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wfloat-equal")
PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wfloat-equal")

TEMPLATE_TEST_CASE("Vector2(x, y)", "[Math][Vector2]", TEST_ALL_TYPES())
{
    using base_t = unwrapped_t<TestType>;

    CONSTEXPR_RUNTIME phi::Vector2<TestType> vec(base_t(13), base_t(29));

    STATIC_REQUIRE(unwrap(vec.x) == base_t(13));
    STATIC_REQUIRE(unwrap(vec.y) == base_t(29));
}

TEMPLATE_TEST_CASE("Vector2(xy)", "[Math][Vector2]", TEST_ALL_TYPES())
{
    using base_t = unwrapped_t<TestType>;

    CONSTEXPR_RUNTIME phi::Vector2<TestType> vec(base_t(42));

    STATIC_REQUIRE(unwrap(vec.x) == base_t(42));
    STATIC_REQUIRE(unwrap(vec.y) == base_t(42));
}

TEMPLATE_TEST_CASE("Vector2(const Vector2&)", "[Math][Vector2]", TEST_ALL_TYPES())
{
    using base_t = unwrapped_t<TestType>;

    CONSTEXPR_RUNTIME phi::Vector2<TestType> base(base_t(18), base_t(23));
    CONSTEXPR_RUNTIME phi::Vector2<TestType> vec(base);

    STATIC_REQUIRE(unwrap(vec.x) == base_t(18));
    STATIC_REQUIRE(unwrap(vec.y) == base_t(23));
}

TEMPLATE_TEST_CASE("Vector2(Vector2&&)", "[Math][Vector2]", TEST_ALL_TYPES())
{
    using base_t = unwrapped_t<TestType>;

    CONSTEXPR_RUNTIME phi::Vector2<TestType> vec(phi::Vector2<TestType>(base_t(11), base_t(9)));

    STATIC_REQUIRE(unwrap(vec.x) == base_t(11));
    STATIC_REQUIRE(unwrap(vec.y) == base_t(9));
}

TEST_CASE("Vector2(const Vector2<Other>&)", "[Math][Vector2]")
{
    CONSTEXPR_RUNTIME phi::Vector2<phi::i8> b1(std::int8_t(3), std::int8_t(1));
    CONSTEXPR_RUNTIME phi::Vector2<phi::i16> r1(b1);

    STATIC_REQUIRE(bool(r1.x == std::int16_t(3)));
    STATIC_REQUIRE(bool(r1.y == std::int16_t(1)));

    CONSTEXPR_RUNTIME phi::Vector2<phi::u16> b2(std::uint16_t(99u), std::uint16_t(257u));
    CONSTEXPR_RUNTIME phi::Vector2<phi::i32> r2(b2);

    STATIC_REQUIRE(bool(r2.x == std::int32_t(99)));
    STATIC_REQUIRE(bool(r2.y == std::int32_t(257)));
}

TEST_CASE("Vector2(Vector2<Other>&&)", "[Math][Vector2]")
{
    CONSTEXPR_RUNTIME phi::Vector2<phi::i16> r1(phi::Vector2<phi::i8>(std::int8_t(11), std::int8_t(17)));

    STATIC_REQUIRE(bool(r1.x == std::int16_t(11)));
    STATIC_REQUIRE(bool(r1.y == std::int16_t(17)));

    CONSTEXPR_RUNTIME phi::Vector2<phi::i32> r2(phi::Vector2<phi::u16>(std::uint16_t(4u), std::uint16_t(1u)));

    STATIC_REQUIRE(bool(r2.x == std::int32_t(4)));
    STATIC_REQUIRE(bool(r2.y == std::int32_t(1)));
}

PHI_GCC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()
