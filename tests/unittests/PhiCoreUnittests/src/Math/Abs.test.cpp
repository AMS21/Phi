#include <catch2/catch.hpp>

#include "ConstexprHelper.hpp"
#include "SameType.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Config/Warning.hpp>
#include <Phi/Math/Abs.hpp>
#include <Phi/TypeTraits/is_floating_point.hpp>
#include <Phi/TypeTraits/is_signed.hpp>
#include <Phi/TypeTraits/is_unsigned.hpp>
#include <cmath>
#include <limits>

template <typename SourceT, typename ResultT>
void test_abs_signed()
{
    // Sanity checks
    STATIC_REQUIRE(phi::is_signed<SourceT>::value);
    STATIC_REQUIRE(phi::is_unsigned<ResultT>::value);

    CONSTEXPR_RUNTIME SourceT min_v = std::numeric_limits<SourceT>::min();
    CONSTEXPR_RUNTIME SourceT max_v = std::numeric_limits<SourceT>::max();

    CHECK_SAME_TYPE(decltype(phi::abs(SourceT(0))), ResultT);

    STATIC_REQUIRE(phi::abs(SourceT(0)) == ResultT(0));
    STATIC_REQUIRE(phi::abs(SourceT(-0)) == ResultT(0));
    STATIC_REQUIRE(phi::abs(SourceT(1)) == ResultT(1));
    STATIC_REQUIRE(phi::abs(SourceT(-1)) == ResultT(1));
    STATIC_REQUIRE(phi::abs(SourceT(3)) == ResultT(3));
    STATIC_REQUIRE(phi::abs(SourceT(-3)) == ResultT(3));
    STATIC_REQUIRE(phi::abs(SourceT(21)) == ResultT(21));
    STATIC_REQUIRE(phi::abs(SourceT(-21)) == ResultT(21));

    STATIC_REQUIRE(phi::abs(min_v + SourceT(1)) == ResultT(max_v));
    STATIC_REQUIRE(phi::abs(max_v) == ResultT(max_v));
}

template <typename TypeT>
void test_abs_unsigned()
{
    // Sanity checks
    STATIC_REQUIRE(phi::is_unsigned<TypeT>::value);

    CONSTEXPR_RUNTIME TypeT min_v = std::numeric_limits<TypeT>::min();
    CONSTEXPR_RUNTIME TypeT max_v = std::numeric_limits<TypeT>::max();

    CHECK_SAME_TYPE(decltype(phi::abs(TypeT(0))), TypeT);

    STATIC_REQUIRE(phi::abs(TypeT(0)) == TypeT(0));
    STATIC_REQUIRE(phi::abs(TypeT(1)) == TypeT(1));
    STATIC_REQUIRE(phi::abs(TypeT(3)) == TypeT(3));
    STATIC_REQUIRE(phi::abs(TypeT(21)) == TypeT(21));

    STATIC_REQUIRE(min_v == TypeT(0));
    STATIC_REQUIRE(phi::abs(min_v) == TypeT(0));
    STATIC_REQUIRE(phi::abs(max_v) == max_v);
}

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wfloat-equal")

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wfloat-equal")

template <typename TypeT>
void test_abs_float()
{
    // Sanity checks
    STATIC_REQUIRE(phi::is_floating_point<TypeT>::value);

    CONSTEXPR_RUNTIME TypeT inf  = std::numeric_limits<TypeT>::infinity();
    CONSTEXPR_RUNTIME TypeT qnan = std::numeric_limits<TypeT>::quiet_NaN();
    CONSTEXPR_RUNTIME TypeT snan = std::numeric_limits<TypeT>::signaling_NaN();

    CHECK_SAME_TYPE(decltype(phi::abs(TypeT(0.0L))), TypeT);

    STATIC_REQUIRE(phi::abs(TypeT(0.0L)) == TypeT(0.0L));
    STATIC_REQUIRE(phi::abs(TypeT(-0.0L)) == TypeT(0.0L));
    STATIC_REQUIRE(phi::abs(TypeT(0.5L)) == TypeT(0.5L));
    STATIC_REQUIRE(phi::abs(TypeT(-0.5L)) == TypeT(0.5L));
    STATIC_REQUIRE(phi::abs(TypeT(1.0L)) == TypeT(1.0L));
    STATIC_REQUIRE(phi::abs(TypeT(-1.0L)) == TypeT(1.0L));
    STATIC_REQUIRE(phi::abs(TypeT(3.0L)) == TypeT(3.0L));
    STATIC_REQUIRE(phi::abs(TypeT(-3.0L)) == TypeT(3.0L));
    STATIC_REQUIRE(phi::abs(TypeT(-21.0L)) == TypeT(21.0L));
    STATIC_REQUIRE(phi::abs(TypeT(21.0L)) == TypeT(21.0L));

    STATIC_REQUIRE(phi::abs(inf) == inf);
    STATIC_REQUIRE(phi::abs(-inf) == inf);

    STATIC_REQUIRE(std::isnan(phi::abs(qnan)));
    STATIC_REQUIRE(std::isnan(phi::abs(-qnan)));

    STATIC_REQUIRE(std::isnan(phi::abs(snan)));
    STATIC_REQUIRE(std::isnan(phi::abs(-snan)));
}

TEST_CASE("Abs signed", "[Math][Abs]")
{
    test_abs_signed<signed char, unsigned char>();
    test_abs_signed<signed short, unsigned short>();
    test_abs_signed<signed int, unsigned int>();
    test_abs_signed<signed long, unsigned long>();
    test_abs_signed<signed long long, unsigned long long>();
}

TEST_CASE("Abs unsigned", "[Math][Abs]")
{
    test_abs_unsigned<unsigned char>();
    test_abs_unsigned<unsigned short>();
    test_abs_unsigned<unsigned int>();
    test_abs_unsigned<unsigned long>();
    test_abs_unsigned<unsigned long long>();
    test_abs_unsigned<char8_t>();
    test_abs_unsigned<char16_t>();
    test_abs_unsigned<char32_t>();
}

PHI_GCC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()

TEST_CASE("Abs floating point", "[Math][Abs]")
{
    test_abs_float<float>();
    test_abs_float<double>();
    test_abs_float<long double>();
}
