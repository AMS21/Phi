#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/warning.hpp>
#include <phi/core/narrow_cast.hpp>
#include <phi/core/types.hpp>
#include <phi/type_traits/make_unsafe.hpp>
#include <phi/type_traits/to_unsafe.hpp>

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR() || !defined(PHI_DEBUG)
#    define TEST_NARROW_CAST(...) STATIC_REQUIRE(__VA_ARGS__)
#else
#    define TEST_NARROW_CAST(...) REQUIRE(__VA_ARGS__)
#endif

using namespace phi::literals;

PHI_CLANG_AND_GCC_SUPPRESS_WARNING_PUSH()
PHI_CLANG_AND_GCC_SUPPRESS_WARNING("-Wfloat-equal")

template <typename TypeT>
void test_narrow_cast()
{
    using UnsafeT = phi::make_unsafe_t<TypeT>;

    // From unsafe signed int
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::int8_t(1))) == UnsafeT(1));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::int16_t(2))) == UnsafeT(2));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::int32_t(3))) == UnsafeT(3));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::int64_t(4))) == UnsafeT(4));

    // From unsafe unph)i::to_unsafe(signed int
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::uint8_t(1))) == UnsafeT(1));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::uint16_t(2))) == UnsafeT(2));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::uint32_t(3))) == UnsafeT(3));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::uint64_t(4))) == UnsafeT(4));

    // From safe signph)i::to_unsafe(ed int
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(1_i8)) == UnsafeT(1));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(2_i16)) == UnsafeT(2));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(3_i32)) == UnsafeT(3));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(4_i64)) == UnsafeT(4));

    // From safe unsiph)i::to_unsafe(gned int
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(1_u8)) == UnsafeT(1));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(2_u16)) == UnsafeT(2));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(3_u32)) == UnsafeT(3));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(4_u64)) == UnsafeT(4));

    // From unsafe flph)i::to_unsafe(oating point
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(1.0f)) == UnsafeT(1));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(2.0)) == UnsafeT(2));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(3.0l)) == UnsafeT(3));

    // From safe floaph)i::to_unsafe(ting point
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::floating_point<float>(1.0f))) ==
                     UnsafeT(1));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::floating_point<double>(2.0))) ==
                     UnsafeT(2));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(
                             phi::floating_point<long double>(3.0l))) == UnsafeT(3));
}

TEST_CASE("narrow_cast")
{
    // From unsafe signed int
    test_narrow_cast<phi::int8_t>();
    test_narrow_cast<phi::int16_t>();
    test_narrow_cast<phi::int32_t>();
    test_narrow_cast<phi::int64_t>();

    // From unsafe unsigned int
    test_narrow_cast<phi::uint8_t>();
    test_narrow_cast<phi::uint16_t>();
    test_narrow_cast<phi::uint32_t>();
    test_narrow_cast<phi::uint64_t>();

    // From safe signed int
    test_narrow_cast<phi::i8>();
    test_narrow_cast<phi::i16>();
    test_narrow_cast<phi::i32>();
    test_narrow_cast<phi::i64>();

    // From safe unsigned int
    test_narrow_cast<phi::u8>();
    test_narrow_cast<phi::u16>();
    test_narrow_cast<phi::u32>();
    test_narrow_cast<phi::u64>();

    // From unsafe floating point
    test_narrow_cast<float>();
    test_narrow_cast<double>();
    test_narrow_cast<long double>();

    // From safe floating point
    test_narrow_cast<phi::floating_point<float>>();
    test_narrow_cast<phi::floating_point<double>>();
    test_narrow_cast<phi::floating_point<long double>>();
}

TEST_CASE("narrow_cast const usage")
{
    // not const - not const
    {
        phi::i32 large = 21;

        phi::i8 small = phi::narrow_cast<phi::i8>(large);
        CHECK(small.unsafe() == 21);
    }

    // const - not const
    {
        const phi::i32 large = 21;

        phi::i8 small = phi::narrow_cast<phi::i8>(large);
        CHECK(small.unsafe() == 21);
    }

    // not const - const
    {
        phi::i32 large = 21;

        const phi::i8 small = phi::narrow_cast<phi::i8>(large);
        CHECK(small.unsafe() == 21);
    }

    // const - const
    {
        const phi::i32 large = 21;

        const phi::i8 small = phi::narrow_cast<phi::i8>(large);
        CHECK(small.unsafe() == 21);
    }
}

PHI_CLANG_AND_GCC_SUPPRESS_WARNING_POP()
