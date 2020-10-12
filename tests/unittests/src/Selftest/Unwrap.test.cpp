#include <catch2/catch.hpp>

#include "Unwrap.hpp"
#include <Phi/Config/Warning.hpp>
#include <Phi/Core/Types.hpp>
#include <cstdint>
#include <type_traits>

TEST_CASE("unwrapped", "[selftest][Unwrapped]")
{
    STATIC_REQUIRE(std::is_same_v<unwrapped<bool>::value_type, bool>);
    STATIC_REQUIRE(std::is_same_v<unwrapped<int>::value_type, int>);
    STATIC_REQUIRE(std::is_same_v<unwrapped<float>::value_type, float>);

    STATIC_REQUIRE(std::is_same_v<unwrapped<phi::Boolean>::value_type, bool>);

    STATIC_REQUIRE(std::is_same_v<unwrapped<phi::i8>::value_type, std::int8_t>);
    STATIC_REQUIRE(std::is_same_v<unwrapped<phi::i16>::value_type, std::int16_t>);
    STATIC_REQUIRE(std::is_same_v<unwrapped<phi::i32>::value_type, std::int32_t>);
    STATIC_REQUIRE(std::is_same_v<unwrapped<phi::i64>::value_type, std::int64_t>);

    STATIC_REQUIRE(std::is_same_v<unwrapped<phi::u8>::value_type, std::uint8_t>);
    STATIC_REQUIRE(std::is_same_v<unwrapped<phi::u16>::value_type, std::uint16_t>);
    STATIC_REQUIRE(std::is_same_v<unwrapped<phi::u32>::value_type, std::uint32_t>);
    STATIC_REQUIRE(std::is_same_v<unwrapped<phi::u64>::value_type, std::uint64_t>);

    STATIC_REQUIRE(std::is_same_v<unwrapped<phi::FloatingPoint<float>>::value_type, float>);
    STATIC_REQUIRE(std::is_same_v<unwrapped<phi::FloatingPoint<double>>::value_type, double>);
    STATIC_REQUIRE(
            std::is_same_v<unwrapped<phi::FloatingPoint<long double>>::value_type, long double>);
}

TEST_CASE("unwrapped_t", "[selftest][Unwrapped]")
{
    STATIC_REQUIRE(std::is_same_v<unwrapped_t<bool>, bool>);
    STATIC_REQUIRE(std::is_same_v<unwrapped_t<int>, int>);
    STATIC_REQUIRE(std::is_same_v<unwrapped_t<float>, float>);

    STATIC_REQUIRE(std::is_same_v<unwrapped_t<phi::Boolean>, bool>);

    STATIC_REQUIRE(std::is_same_v<unwrapped_t<phi::i8>, std::int8_t>);
    STATIC_REQUIRE(std::is_same_v<unwrapped_t<phi::i16>, std::int16_t>);
    STATIC_REQUIRE(std::is_same_v<unwrapped_t<phi::i32>, std::int32_t>);
    STATIC_REQUIRE(std::is_same_v<unwrapped_t<phi::i64>, std::int64_t>);

    STATIC_REQUIRE(std::is_same_v<unwrapped_t<phi::u8>, std::uint8_t>);
    STATIC_REQUIRE(std::is_same_v<unwrapped_t<phi::u16>, std::uint16_t>);
    STATIC_REQUIRE(std::is_same_v<unwrapped_t<phi::u32>, std::uint32_t>);
    STATIC_REQUIRE(std::is_same_v<unwrapped_t<phi::u64>, std::uint64_t>);

    STATIC_REQUIRE(std::is_same_v<unwrapped_t<phi::FloatingPoint<float>>, float>);
    STATIC_REQUIRE(std::is_same_v<unwrapped_t<phi::FloatingPoint<double>>, double>);
    STATIC_REQUIRE(std::is_same_v<unwrapped_t<phi::FloatingPoint<long double>>, long double>);
}

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wfloat-equal")

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wfloat-equal")

TEMPLATE_TEST_CASE("unwrap", "[selftest][unwrap]", std::int8_t, std::int16_t, std::int32_t,
                   std::int64_t, std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t, phi::i8,
                   phi::i16, phi::i32, phi::i64, phi::u8, phi::u16, phi::u32, phi::u64, float,
                   double, long double, phi::FloatingPoint<float>, phi::FloatingPoint<double>,
                   phi::FloatingPoint<long double>)
{
    using base_t = unwrapped_t<TestType>;

    STATIC_REQUIRE(unwrap(TestType(base_t(5))) == base_t(5));
    STATIC_REQUIRE(unwrap(TestType(base_t(7))) == base_t(7));
    STATIC_REQUIRE(unwrap(TestType(base_t(3))) == base_t(3));
    STATIC_REQUIRE(unwrap(TestType(base_t(12))) == base_t(12));
}

PHI_GCC_SUPPRESS_WARNING_POP()

PHI_CLANG_SUPPRESS_WARNING_POP()

TEST_CASE("unwrap boolean", "[selftest][unwrap]")
{
    STATIC_REQUIRE(unwrap(phi::Boolean(true)) == true);
    STATIC_REQUIRE(unwrap(phi::Boolean(false)) == false);
}
