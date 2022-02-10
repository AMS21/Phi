#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/compiler_support/warning.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/types.hpp>
#include <phi/type_traits/make_unsafe.hpp>
#include <phi/type_traits/to_unsafe.hpp>
#include <iterator>

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING_PUSH()

#if PHI_COMPILER_IS_ATLEAST(GCC, 10, 0, 0)
PHI_GCC_SUPPRESS_WARNING("-Warith-conversion")
#else
PHI_GCC_SUPPRESS_WARNING("-Wconversion")
#endif

#include <phi/math/vector2.hpp>

PHI_CLANG_SUPPRESS_WARNING("-Wfloat-equal")
PHI_GCC_SUPPRESS_WARNING("-Wfloat-equal")
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")

template <typename T>
void test_vector2()
{
    using base_t = phi::make_unsafe_t<T>;

    SECTION("Typedefs")
    {
        CHECK_SAME_TYPE(typename phi::vector2<T>::this_type, phi::vector2<T>);
        CHECK_SAME_TYPE(typename phi::vector2<T>::value_type, T);
        CHECK_SAME_TYPE(typename phi::vector2<T>::reference, T&);
        CHECK_SAME_TYPE(typename phi::vector2<T>::const_reference, const T&);
        CHECK_SAME_TYPE(typename phi::vector2<T>::pointer, T*);
        CHECK_SAME_TYPE(typename phi::vector2<T>::const_pointer, const T*);
        CHECK_SAME_TYPE(typename phi::vector2<T>::iterator, T*);
        CHECK_SAME_TYPE(typename phi::vector2<T>::const_iterator, const T*);
        CHECK_SAME_TYPE(typename phi::vector2<T>::reverse_iterator, std::reverse_iterator<T*>);
        CHECK_SAME_TYPE(typename phi::vector2<T>::const_reverse_iterator,
                        std::reverse_iterator<const T*>);
    }

    SECTION("vector2(x, y)")
    {
        CONSTEXPR_RUNTIME phi::vector2<T> vec(base_t(13), base_t(29));

        STATIC_REQUIRE(phi::to_unsafe(vec.x) == base_t(13));
        STATIC_REQUIRE(phi::to_unsafe(vec.y) == base_t(29));
    }

    SECTION("vector2(xy)")
    {
        CONSTEXPR_RUNTIME phi::vector2<T> vec(base_t(42));

        STATIC_REQUIRE(phi::to_unsafe(vec.x) == base_t(42));
        STATIC_REQUIRE(phi::to_unsafe(vec.y) == base_t(42));
    }

    SECTION("vector2(const vector2&)")
    {
        CONSTEXPR_RUNTIME phi::vector2<T> base(base_t(18), base_t(23));
        CONSTEXPR_RUNTIME phi::vector2<T> vec(base);

        STATIC_REQUIRE(phi::to_unsafe(vec.x) == base_t(18));
        STATIC_REQUIRE(phi::to_unsafe(vec.y) == base_t(23));
    }

    SECTION("vector2(vector2&&)")
    {
        CONSTEXPR_RUNTIME phi::vector2<T> vec(phi::vector2<T>(base_t(11), base_t(9)));

        STATIC_REQUIRE(phi::to_unsafe(vec.x) == base_t(11));
        STATIC_REQUIRE(phi::to_unsafe(vec.y) == base_t(9));
    }

    SECTION("operator=(const vector2&)")
    {
        phi::vector2<T> base(base_t(2), base_t(4));
        phi::vector2<T> other(base_t(0));

        phi::vector2<T> vec = (other = base);
        CHECK(phi::to_unsafe(vec.x) == 2);
        CHECK(phi::to_unsafe(vec.y) == 4);
        CHECK(phi::to_unsafe(other.x) == 2);
        CHECK(phi::to_unsafe(other.y) == 4);
    }

    SECTION("operator=(vector2&&)")
    {
        phi::vector2<T> base(base_t(0));

        phi::vector2<T> vec = (base = phi::vector2<T>(base_t(99), base_t(7)));
        CHECK(phi::to_unsafe(vec.x) == 99);
        CHECK(phi::to_unsafe(vec.y) == 7);
        CHECK(phi::to_unsafe(base.x) == 99);
        CHECK(phi::to_unsafe(base.y) == 7);
    }

    SECTION("operator+(const vector2&)")
    {
        CONSTEXPR_RUNTIME phi::vector2<T> base(base_t(0), base_t(12));

        CONSTEXPR_RUNTIME phi::vector2<T> vec = +base;
        STATIC_REQUIRE(phi::to_unsafe(vec.x) == base_t(0));
        STATIC_REQUIRE(phi::to_unsafe(vec.y) == base_t(12));
    }

    SECTION("operator+=(vector2&, const vector2&)")
    {
        phi::vector2<T> base(base_t(3), base_t(19));
        phi::vector2<T> other(base_t(9), base_t(17));

        phi::vector2<T> vec = (base += other);
        CHECK(phi::to_unsafe(base.x) == base_t(12));
        CHECK(phi::to_unsafe(base.y) == base_t(36));
        CHECK(phi::to_unsafe(vec.x) == base_t(12));
        CHECK(phi::to_unsafe(vec.y) == base_t(36));
    }

    SECTION("operator-=(vector2&, const vector2&)")
    {
        phi::vector2<T> base(base_t(30), base_t(40));
        phi::vector2<T> other(base_t(10), base_t(15));

        phi::vector2<T> vec = (base -= other);
        CHECK(phi::to_unsafe(base.x) == base_t(20));
        CHECK(phi::to_unsafe(base.y) == base_t(25));
        CHECK(phi::to_unsafe(vec.x) == base_t(20));
        CHECK(phi::to_unsafe(vec.y) == base_t(25));
    }

    SECTION("operator+(const vector2&, const vector2&)")
    {
        EXT_CONSTEXPR_RUNTIME phi::vector2<T> lhs(base_t(3), base_t(14));
        EXT_CONSTEXPR_RUNTIME phi::vector2<T> rhs(base_t(7), base_t(11));

        EXT_CONSTEXPR_RUNTIME phi::vector2<T> res = lhs + rhs;

        EXT_STATIC_REQUIRE(phi::to_unsafe(res.x) == base_t(10));
        EXT_STATIC_REQUIRE(phi::to_unsafe(res.y) == base_t(25));
    }

    SECTION("operator-(const vector2&, const vector2&)")
    {
        EXT_CONSTEXPR_RUNTIME phi::vector2<T> lhs(base_t(100), base_t(45));
        EXT_CONSTEXPR_RUNTIME phi::vector2<T> rhs(base_t(70), base_t(5));

        EXT_CONSTEXPR_RUNTIME phi::vector2<T> res = lhs - rhs;

        EXT_STATIC_REQUIRE(phi::to_unsafe(res.x) == base_t(30));
        EXT_STATIC_REQUIRE(phi::to_unsafe(res.y) == base_t(40));
    }

    SECTION("operator*(const vector2&, rhs)")
    {
        EXT_CONSTEXPR_RUNTIME phi::vector2<T> lhs(base_t(3), base_t(6));
        EXT_CONSTEXPR_RUNTIME T               rhs(base_t(2));

        EXT_CONSTEXPR_RUNTIME phi::vector2<T> res = (lhs * rhs);

        EXT_STATIC_REQUIRE(phi::to_unsafe(res.x) == base_t(6));
        EXT_STATIC_REQUIRE(phi::to_unsafe(res.y) == base_t(12));
    }

    SECTION("operator*=(const vector2&, rhs)")
    {
        phi::vector2<T> lhs(base_t(2), base_t(12));
        T               rhs(base_t(3));

        phi::vector2<T> vec = (lhs *= rhs);
        CHECK(phi::to_unsafe(lhs.x) == base_t(6));
        CHECK(phi::to_unsafe(lhs.y) == base_t(36));
        CHECK(phi::to_unsafe(vec.x) == base_t(6));
        CHECK(phi::to_unsafe(vec.y) == base_t(36));
    }

    SECTION("operator/(const vector2&, rhs)")
    {
        EXT_CONSTEXPR_RUNTIME phi::vector2<T> lhs(base_t(6), base_t(12));
        EXT_CONSTEXPR_RUNTIME T               rhs(base_t(2));

        EXT_CONSTEXPR_RUNTIME phi::vector2<T> res = (lhs / rhs);

        EXT_STATIC_REQUIRE(phi::to_unsafe(res.x) == base_t(3));
        EXT_STATIC_REQUIRE(phi::to_unsafe(res.y) == base_t(6));
    }

    SECTION("operator/=(const vector2&, rhs)")
    {
        phi::vector2<T> lhs(base_t(9), base_t(12));
        T               rhs(base_t(3));

        phi::vector2<T> vec = (lhs /= rhs);
        CHECK(phi::to_unsafe(lhs.x) == base_t(3));
        CHECK(phi::to_unsafe(lhs.y) == base_t(4));
        CHECK(phi::to_unsafe(vec.x) == base_t(3));
        CHECK(phi::to_unsafe(vec.y) == base_t(4));
    }
}

template <typename T>
void test_vector2_op()
{
    using base_t = phi::make_unsafe_t<T>;

    SECTION("operator==(const vector2&, const vector2&)")
    {
        CONSTEXPR_RUNTIME phi::vector2<T> vec0(base_t(3), base_t(4));
        CONSTEXPR_RUNTIME phi::vector2<T> vec1(base_t(4), base_t(3));
        CONSTEXPR_RUNTIME phi::vector2<T> vec2(base_t(7), base_t(2));

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

    SECTION("operator!=(const vector2&, const vector2&)")
    {
        CONSTEXPR_RUNTIME phi::vector2<T> vec0(base_t(3), base_t(4));
        CONSTEXPR_RUNTIME phi::vector2<T> vec1(base_t(4), base_t(3));
        CONSTEXPR_RUNTIME phi::vector2<T> vec2(base_t(7), base_t(2));

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

#define TEST_VEC2_TYPEDEF(vec_t, base_t)                                                           \
    STATIC_REQUIRE(sizeof(vec_t) == (sizeof(base_t) * 2));                                         \
    CHECK_SAME_TYPE(vec_t::value_type, base_t)

TEST_CASE("vector2")
{
    // General tests
    test_vector2<char>();
    test_vector2<signed char>();
    test_vector2<unsigned char>();
    test_vector2<short>();
    test_vector2<unsigned short>();
    test_vector2<int>();
    test_vector2<unsigned>();
    test_vector2<long>();
    test_vector2<unsigned long>();
    test_vector2<long long>();
    test_vector2<unsigned long long>();
    test_vector2<float>();
    test_vector2<double>();
    test_vector2<long double>();
    test_vector2<phi::i8>();
    test_vector2<phi::i16>();
    test_vector2<phi::i32>();
    test_vector2<phi::i64>();
    test_vector2<phi::u8>();
    test_vector2<phi::u16>();
    test_vector2<phi::u32>();
    test_vector2<phi::u64>();
    test_vector2<phi::floating_point<float>>();
    test_vector2<phi::floating_point<double>>();
    test_vector2<phi::floating_point<long double>>();

    // Test operators
    test_vector2_op<char>();
    test_vector2_op<signed char>();
    test_vector2_op<short>();
    test_vector2_op<int>();
    test_vector2_op<long>();
    test_vector2_op<long long>();
    test_vector2_op<unsigned char>();
    test_vector2_op<unsigned short>();
    test_vector2_op<unsigned int>();
    test_vector2_op<unsigned long>();
    test_vector2_op<unsigned long long>();
    test_vector2_op<phi::i8>();
    test_vector2_op<phi::i16>();
    test_vector2_op<phi::i32>();
    test_vector2_op<phi::i64>();
    test_vector2_op<phi::u8>();
    test_vector2_op<phi::u16>();
    test_vector2_op<phi::u32>();
    test_vector2_op<phi::u64>();

    // global typedefs
    TEST_VEC2_TYPEDEF(phi::vector2i8, phi::i8);
    TEST_VEC2_TYPEDEF(phi::vector2u8, phi::u8);
    TEST_VEC2_TYPEDEF(phi::vector2i16, phi::i16);
    TEST_VEC2_TYPEDEF(phi::vector2u16, phi::u16);
    TEST_VEC2_TYPEDEF(phi::vector2i32, phi::i32);
    TEST_VEC2_TYPEDEF(phi::vector2u32, phi::u32);
    TEST_VEC2_TYPEDEF(phi::vector2i64, phi::i64);
    TEST_VEC2_TYPEDEF(phi::vector2u64, phi::u64);
    TEST_VEC2_TYPEDEF(phi::vector2isize, phi::isize);
    TEST_VEC2_TYPEDEF(phi::vector2usize, phi::usize);

    TEST_VEC2_TYPEDEF(phi::vector2f32, phi::f32);
    TEST_VEC2_TYPEDEF(phi::vector2f64, phi::f64);

    // Fixed types
    SECTION("vector2(const vector2<Other>&)")
    {
        CONSTEXPR_RUNTIME phi::vector2<phi::i8> b1(std::int8_t(3), std::int8_t(1));
        CONSTEXPR_RUNTIME phi::vector2<phi::i16> r1(b1);

        STATIC_REQUIRE(bool(r1.x == std::int16_t(3)));
        STATIC_REQUIRE(bool(r1.y == std::int16_t(1)));

        CONSTEXPR_RUNTIME phi::vector2<phi::u16> b2(std::uint16_t(99u), std::uint16_t(257u));
        CONSTEXPR_RUNTIME phi::vector2<phi::i32> r2(b2);

        STATIC_REQUIRE(bool(r2.x == std::int32_t(99)));
        STATIC_REQUIRE(bool(r2.y == std::int32_t(257)));
    }

    SECTION("vector2(vector2<Other>&&)")
    {
        CONSTEXPR_RUNTIME phi::vector2<phi::i16> r1(
                phi::vector2<phi::i8>(std::int8_t(11), std::int8_t(17)));

        STATIC_REQUIRE(bool(r1.x == std::int16_t(11)));
        STATIC_REQUIRE(bool(r1.y == std::int16_t(17)));

        CONSTEXPR_RUNTIME phi::vector2<phi::i32> r2(
                phi::vector2<phi::u16>(std::uint16_t(4u), std::uint16_t(1u)));

        STATIC_REQUIRE(bool(r2.x == std::int32_t(4)));
        STATIC_REQUIRE(bool(r2.y == std::int32_t(1)));
    }

    SECTION("operator-(const vector2&)")
    {
        /*
        CONSTEXPR_RUNTIME phi::vector2<phi::i32> b1(12, 32);
        CONSTEXPR_RUNTIME phi::vector2<phi::i32> r1 = -b1;

        STATIC_REQUIRE(bool(r1.x == -12));
        STATIC_REQUIRE(bool(r1.y == -32));

        CONSTEXPR_RUNTIME phi::vector2<phi::i32> b2(-11, -9);
        CONSTEXPR_RUNTIME phi::vector2<phi::i32> r2 = -b2;

        STATIC_REQUIRE(bool(r2.x == 11));
        STATIC_REQUIRE(bool(r2.y == 9));

        CONSTEXPR_RUNTIME phi::vector2<phi::i32> b3(0, -19);
        CONSTEXPR_RUNTIME phi::vector2<phi::i32> r3 = -b3;

        STATIC_REQUIRE(bool(r3.x == 0));
        STATIC_REQUIRE(bool(r3.y == 19));

        CONSTEXPR_RUNTIME phi::vector2<phi::i32> b4(8, 0);
        CONSTEXPR_RUNTIME phi::vector2<phi::i32> r4 = -b4;

        STATIC_REQUIRE(bool(r4.x == -8));
        STATIC_REQUIRE(bool(r4.y == 0));
        */
    }
}

PHI_GCC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()
