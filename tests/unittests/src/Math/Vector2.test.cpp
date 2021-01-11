#include <Phi/Config/Warning.hpp>

PHI_EXTERNAL_HEADERS_BEGIN()
#include <catch2/catch_template_test_macros.hpp>
PHI_EXTERNAL_HEADERS_END()

#include "ConstexprHelper.hpp"
#include "Unwrap.hpp"
#include <Phi/Config/Warning.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Types.hpp>
#include <Phi/Math/Vector2.hpp>
#include <iterator>
#include <type_traits>

PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wfloat-equal")
PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wfloat-equal")
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")

TEMPLATE_TEST_CASE("Vector2 templated", "[Math][Vector2]", char, signed char, unsigned char, short,
                   unsigned short, int, unsigned, long, unsigned long, long long,
                   unsigned long long, float, double, long double, phi::i8, phi::i16, phi::i32,
                   phi::i64, phi::u8, phi::u16, phi::u32, phi::u64, phi::FloatingPoint<float>,
                   phi::FloatingPoint<double>, phi::FloatingPoint<long double>)
{
    using base_t = unwrapped_t<TestType>;

    SECTION("Vector2(x, y)")
    {
        CONSTEXPR_RUNTIME phi::Vector2<TestType> vec(base_t(13), base_t(29));

        STATIC_REQUIRE(unwrap(vec.x) == base_t(13));
        STATIC_REQUIRE(unwrap(vec.y) == base_t(29));
    }

    SECTION("Vector2(xy)")
    {
        CONSTEXPR_RUNTIME phi::Vector2<TestType> vec(base_t(42));

        STATIC_REQUIRE(unwrap(vec.x) == base_t(42));
        STATIC_REQUIRE(unwrap(vec.y) == base_t(42));
    }

    SECTION("Vector2(const Vector2&)")
    {
        CONSTEXPR_RUNTIME phi::Vector2<TestType> base(base_t(18), base_t(23));
        CONSTEXPR_RUNTIME phi::Vector2<TestType> vec(base);

        STATIC_REQUIRE(unwrap(vec.x) == base_t(18));
        STATIC_REQUIRE(unwrap(vec.y) == base_t(23));
    }

    SECTION("Vector2(Vector2&&)")
    {
        CONSTEXPR_RUNTIME phi::Vector2<TestType> vec(phi::Vector2<TestType>(base_t(11), base_t(9)));

        STATIC_REQUIRE(unwrap(vec.x) == base_t(11));
        STATIC_REQUIRE(unwrap(vec.y) == base_t(9));
    }

    SECTION("operator=(const Vector2&)")
    {
        phi::Vector2<TestType> base(base_t(2), base_t(4));
        phi::Vector2<TestType> other(base_t(0));

        phi::Vector2<TestType> vec = (other = base);
        CHECK(unwrap(vec.x) == 2);
        CHECK(unwrap(vec.y) == 4);
        CHECK(unwrap(other.x) == 2);
        CHECK(unwrap(other.y) == 4);
    }

    SECTION("operator=(Vector2&&)")
    {
        phi::Vector2<TestType> base(base_t(0));

        phi::Vector2<TestType> vec = (base = phi::Vector2<TestType>(base_t(99), base_t(7)));
        CHECK(unwrap(vec.x) == 99);
        CHECK(unwrap(vec.y) == 7);
        CHECK(unwrap(base.x) == 99);
        CHECK(unwrap(base.y) == 7);
    }

    SECTION("operator+(const Vector2&)")
    {
        CONSTEXPR_RUNTIME phi::Vector2<TestType> base(base_t(0), base_t(12));

        CONSTEXPR_RUNTIME phi::Vector2<TestType> vec = +base;
        STATIC_REQUIRE(unwrap(vec.x) == base_t(0));
        STATIC_REQUIRE(unwrap(vec.y) == base_t(12));
    }

    SECTION("operator+=(Vector2&, const Vector2&)")
    {
        phi::Vector2<TestType> base(base_t(3), base_t(19));
        phi::Vector2<TestType> other(base_t(9), base_t(17));

        phi::Vector2<TestType> vec = (base += other);
        CHECK(unwrap(base.x) == base_t(12));
        CHECK(unwrap(base.y) == base_t(36));
        CHECK(unwrap(vec.x) == base_t(12));
        CHECK(unwrap(vec.y) == base_t(36));
    }

    SECTION("operator-=(Vector2&, const Vector2&)")
    {
        phi::Vector2<TestType> base(base_t(30), base_t(40));
        phi::Vector2<TestType> other(base_t(10), base_t(15));

        phi::Vector2<TestType> vec = (base -= other);
        CHECK(unwrap(base.x) == base_t(20));
        CHECK(unwrap(base.y) == base_t(25));
        CHECK(unwrap(vec.x) == base_t(20));
        CHECK(unwrap(vec.y) == base_t(25));
    }

    SECTION("operator+(const Vector2&, const Vector2&)")
    {
        CONSTEXPR_RUNTIME phi::Vector2<TestType> lhs(base_t(3), base_t(14));
        CONSTEXPR_RUNTIME phi::Vector2<TestType> rhs(base_t(7), base_t(11));

        CONSTEXPR_RUNTIME phi::Vector2<TestType> res = lhs + rhs;

        PHI_UNUSED_PARAMETER(res);
        STATIC_REQUIRE(unwrap(res.x) == base_t(10));
        STATIC_REQUIRE(unwrap(res.y) == base_t(25));
    }

    SECTION("operator-(const Vector2&, const Vector2&)")
    {
        CONSTEXPR_RUNTIME phi::Vector2<TestType> lhs(base_t(100), base_t(45));
        CONSTEXPR_RUNTIME phi::Vector2<TestType> rhs(base_t(70), base_t(5));

        CONSTEXPR_RUNTIME phi::Vector2<TestType> res = lhs - rhs;

        STATIC_REQUIRE(unwrap(res.x) == base_t(30));
        STATIC_REQUIRE(unwrap(res.y) == base_t(40));
    }

    SECTION("operator*(const Vector2&, rhs)")
    {
        CONSTEXPR_RUNTIME phi::Vector2<TestType> lhs(base_t(3), base_t(6));
        CONSTEXPR_RUNTIME TestType               rhs(base_t(2));

        CONSTEXPR_RUNTIME phi::Vector2<TestType> res = (lhs * rhs);

        STATIC_REQUIRE(unwrap(res.x) == base_t(6));
        STATIC_REQUIRE(unwrap(res.y) == base_t(12));
    }

    SECTION("operator*=(const Vector2&, rhs)")
    {
        phi::Vector2<TestType> lhs(base_t(2), base_t(12));
        TestType               rhs(base_t(3));

        phi::Vector2<TestType> vec = (lhs *= rhs);
        CHECK(unwrap(lhs.x) == base_t(6));
        CHECK(unwrap(lhs.y) == base_t(36));
        CHECK(unwrap(vec.x) == base_t(6));
        CHECK(unwrap(vec.y) == base_t(36));
    }

    SECTION("operator/(const Vector2&, rhs)")
    {
        CONSTEXPR_RUNTIME phi::Vector2<TestType> lhs(base_t(6), base_t(12));
        CONSTEXPR_RUNTIME TestType               rhs(base_t(2));

        CONSTEXPR_RUNTIME phi::Vector2<TestType> res = (lhs / rhs);

        STATIC_REQUIRE(unwrap(res.x) == base_t(3));
        STATIC_REQUIRE(unwrap(res.y) == base_t(6));
    }

    SECTION("operator/=(const Vector2&, rhs)")
    {
        phi::Vector2<TestType> lhs(base_t(9), base_t(12));
        TestType               rhs(base_t(3));

        phi::Vector2<TestType> vec = (lhs /= rhs);
        CHECK(unwrap(lhs.x) == base_t(3));
        CHECK(unwrap(lhs.y) == base_t(4));
        CHECK(unwrap(vec.x) == base_t(3));
        CHECK(unwrap(vec.y) == base_t(4));
    }
}

TEMPLATE_TEST_CASE("Vector2 integer types", "[Math][Vector2]", char, signed char, unsigned char,
                   short, unsigned short, int, unsigned, long, unsigned long, long long,
                   unsigned long long, phi::i8, phi::i16, phi::i32, phi::i64, phi::u8, phi::u16,
                   phi::u32, phi::u64)
{
    using base_t = unwrapped_t<TestType>;

    SECTION("operator==(const Vector2&, const Vector2&)")
    {
        CONSTEXPR_RUNTIME phi::Vector2<TestType> vec0(base_t(3), base_t(4));
        CONSTEXPR_RUNTIME phi::Vector2<TestType> vec1(base_t(4), base_t(3));
        CONSTEXPR_RUNTIME phi::Vector2<TestType> vec2(base_t(7), base_t(2));

        STATIC_REQUIRE(bool(vec0 == vec0));
        STATIC_REQUIRE_FALSE(bool(vec0 == vec1));
        STATIC_REQUIRE_FALSE(bool(vec0 == vec2));

        STATIC_REQUIRE_FALSE(bool(vec1 == vec0));
        STATIC_REQUIRE(bool(vec1 == vec1));
        STATIC_REQUIRE_FALSE(bool(vec1 == vec2));

        STATIC_REQUIRE_FALSE(bool(vec2 == vec0));
        STATIC_REQUIRE_FALSE(bool(vec2 == vec1));
        STATIC_REQUIRE(bool(vec2 == vec2));
    }

    SECTION("operator!=(const Vector2&, const Vector2&)")
    {
        CONSTEXPR_RUNTIME phi::Vector2<TestType> vec0(base_t(3), base_t(4));
        CONSTEXPR_RUNTIME phi::Vector2<TestType> vec1(base_t(4), base_t(3));
        CONSTEXPR_RUNTIME phi::Vector2<TestType> vec2(base_t(7), base_t(2));

        STATIC_REQUIRE_FALSE(bool(vec0 != vec0));
        STATIC_REQUIRE(bool(vec0 != vec1));
        STATIC_REQUIRE(bool(vec0 != vec2));

        STATIC_REQUIRE(bool(vec1 != vec0));
        STATIC_REQUIRE_FALSE(bool(vec1 != vec1));
        STATIC_REQUIRE(bool(vec1 != vec2));

        STATIC_REQUIRE(bool(vec2 != vec0));
        STATIC_REQUIRE(bool(vec2 != vec1));
        STATIC_REQUIRE_FALSE(bool(vec2 != vec2));
    }
}

TEST_CASE("Vector2 fixed types", "[Math][Vector2]")
{
    SECTION("Vector2(const Vector2<Other>&)")
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

    SECTION("Vector2(Vector2<Other>&&)")
    {
        CONSTEXPR_RUNTIME phi::Vector2<phi::i16> r1(
                phi::Vector2<phi::i8>(std::int8_t(11), std::int8_t(17)));

        STATIC_REQUIRE(bool(r1.x == std::int16_t(11)));
        STATIC_REQUIRE(bool(r1.y == std::int16_t(17)));

        CONSTEXPR_RUNTIME phi::Vector2<phi::i32> r2(
                phi::Vector2<phi::u16>(std::uint16_t(4u), std::uint16_t(1u)));

        STATIC_REQUIRE(bool(r2.x == std::int32_t(4)));
        STATIC_REQUIRE(bool(r2.y == std::int32_t(1)));
    }

    SECTION("operator-(const Vector2&)")
    {
        CONSTEXPR_RUNTIME phi::Vector2<phi::i32> b1(12, 32);
        CONSTEXPR_RUNTIME phi::Vector2<phi::i32> r1 = -b1;

        STATIC_REQUIRE(bool(r1.x == -12));
        STATIC_REQUIRE(bool(r1.y == -32));

        CONSTEXPR_RUNTIME phi::Vector2<phi::i32> b2(-11, -9);
        CONSTEXPR_RUNTIME phi::Vector2<phi::i32> r2 = -b2;

        STATIC_REQUIRE(bool(r2.x == 11));
        STATIC_REQUIRE(bool(r2.y == 9));

        CONSTEXPR_RUNTIME phi::Vector2<phi::i32> b3(0, -19);
        CONSTEXPR_RUNTIME phi::Vector2<phi::i32> r3 = -b3;

        STATIC_REQUIRE(bool(r3.x == 0));
        STATIC_REQUIRE(bool(r3.y == 19));

        CONSTEXPR_RUNTIME phi::Vector2<phi::i32> b4(8, 0);
        CONSTEXPR_RUNTIME phi::Vector2<phi::i32> r4 = -b4;

        STATIC_REQUIRE(bool(r4.x == -8));
        STATIC_REQUIRE(bool(r4.y == 0));
    }
}

PHI_GCC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()

TEMPLATE_TEST_CASE("Vector2 typedefs", "[Math][Vector2]", char, signed char, unsigned char, short,
                   unsigned short, int, unsigned, long, unsigned long, long long,
                   unsigned long long, float, double, long double, phi::i8, phi::i16, phi::i32,
                   phi::i64, phi::u8, phi::u16, phi::u32, phi::u64, phi::FloatingPoint<float>,
                   phi::FloatingPoint<double>, phi::FloatingPoint<long double>)
{
    STATIC_REQUIRE(
            std::is_same_v<typename phi::Vector2<TestType>::this_type, phi::Vector2<TestType>>);
    STATIC_REQUIRE(std::is_same_v<typename phi::Vector2<TestType>::value_type, TestType>);
    STATIC_REQUIRE(std::is_same_v<typename phi::Vector2<TestType>::reference, TestType&>);
    STATIC_REQUIRE(
            std::is_same_v<typename phi::Vector2<TestType>::const_reference, const TestType&>);
    STATIC_REQUIRE(std::is_same_v<typename phi::Vector2<TestType>::pointer, TestType*>);
    STATIC_REQUIRE(std::is_same_v<typename phi::Vector2<TestType>::const_pointer, const TestType*>);
    STATIC_REQUIRE(std::is_same_v<typename phi::Vector2<TestType>::iterator, TestType*>);
    STATIC_REQUIRE(
            std::is_same_v<typename phi::Vector2<TestType>::const_iterator, const TestType*>);
    STATIC_REQUIRE(std::is_same_v<typename phi::Vector2<TestType>::reverse_iterator,
                                  std::reverse_iterator<TestType*>>);
    STATIC_REQUIRE(std::is_same_v<typename phi::Vector2<TestType>::const_reverse_iterator,
                                  std::reverse_iterator<const TestType*>>);
}

#define TEST_VEC2_TYPEDEF(vec_t, base_t)                                                           \
    STATIC_REQUIRE(sizeof(vec_t) == (sizeof(base_t) * 2));                                         \
    STATIC_REQUIRE(std::is_same_v<vec_t::value_type, base_t>)

TEST_CASE("Vector2 global typedefs", "[Math][Vector2]")
{
    // global typedefs
    TEST_VEC2_TYPEDEF(phi::Vector2i8, phi::i8);
    TEST_VEC2_TYPEDEF(phi::Vector2u8, phi::u8);
    TEST_VEC2_TYPEDEF(phi::Vector2i16, phi::i16);
    TEST_VEC2_TYPEDEF(phi::Vector2u16, phi::u16);
    TEST_VEC2_TYPEDEF(phi::Vector2i32, phi::i32);
    TEST_VEC2_TYPEDEF(phi::Vector2u32, phi::u32);
    TEST_VEC2_TYPEDEF(phi::Vector2i64, phi::i64);
    TEST_VEC2_TYPEDEF(phi::Vector2u64, phi::u64);
    TEST_VEC2_TYPEDEF(phi::Vector2imax, phi::imax);
    TEST_VEC2_TYPEDEF(phi::Vector2umax, phi::umax);
    TEST_VEC2_TYPEDEF(phi::Vector2isize, phi::isize);
    TEST_VEC2_TYPEDEF(phi::Vector2usize, phi::usize);

    TEST_VEC2_TYPEDEF(phi::Vector2f32, phi::f32);
    TEST_VEC2_TYPEDEF(phi::Vector2f64, phi::f64);
    TEST_VEC2_TYPEDEF(phi::Vector2fmax, phi::fmax);
}
