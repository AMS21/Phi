#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/conversion.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/math/abs.hpp>
#include <phi/math/is_nan.hpp>
#include <phi/type_traits/is_floating_point.hpp>
#include <phi/type_traits/is_signed.hpp>
#include <phi/type_traits/is_unsigned.hpp>
#include <phi/type_traits/make_unsafe.hpp>
#include <phi/type_traits/to_unsafe.hpp>

#ifndef __STDC_WANT_SECURE_LIB__
#define __STDC_WANT_SECURE_LIB__
#endif
#include <limits>

template <typename SourceT, typename ResultT>
void test_abs_signed()
{
    // Sanity checks
    STATIC_REQUIRE(phi::is_signed<SourceT>::value);
    STATIC_REQUIRE(phi::is_unsigned<ResultT>::value);

    EXT_CONSTEXPR_RUNTIME SourceT min_v = std::numeric_limits<SourceT>::min();
    EXT_CONSTEXPR_RUNTIME SourceT min_p1_v =
            std::numeric_limits<SourceT>::min() + phi::unsafe_cast<SourceT>(1);
    EXT_CONSTEXPR_RUNTIME SourceT max_v = std::numeric_limits<SourceT>::max();

    CHECK_SAME_TYPE(decltype(phi::abs(phi::unsafe_cast<SourceT>(0))), ResultT);

    EXT_STATIC_REQUIRE(phi::abs(phi::unsafe_cast<SourceT>(0)) == phi::unsafe_cast<ResultT>(0));
    EXT_STATIC_REQUIRE(phi::abs(phi::unsafe_cast<SourceT>(-0)) == phi::unsafe_cast<ResultT>(0));
    EXT_STATIC_REQUIRE(phi::abs(phi::unsafe_cast<SourceT>(1)) == phi::unsafe_cast<ResultT>(1));
    EXT_STATIC_REQUIRE(phi::abs(phi::unsafe_cast<SourceT>(-1)) == phi::unsafe_cast<ResultT>(1));
    EXT_STATIC_REQUIRE(phi::abs(phi::unsafe_cast<SourceT>(3)) == phi::unsafe_cast<ResultT>(3));
    EXT_STATIC_REQUIRE(phi::abs(phi::unsafe_cast<SourceT>(-3)) == phi::unsafe_cast<ResultT>(3));
    EXT_STATIC_REQUIRE(phi::abs(phi::unsafe_cast<SourceT>(21)) == phi::unsafe_cast<ResultT>(21));
    EXT_STATIC_REQUIRE(phi::abs(phi::unsafe_cast<SourceT>(-21)) == phi::unsafe_cast<ResultT>(21));

    EXT_STATIC_REQUIRE(phi::abs(min_p1_v) == phi::unsafe_cast<ResultT>(max_v));
    EXT_STATIC_REQUIRE(phi::abs(min_v) ==
                       phi::unsafe_cast<ResultT>(max_v) + phi::unsafe_cast<ResultT>(1));
    EXT_STATIC_REQUIRE(phi::abs(max_v) == phi::unsafe_cast<ResultT>(max_v));
}

template <typename TypeT>
void test_abs_unsigned()
{
    // Sanity checks
    STATIC_REQUIRE(phi::is_unsigned<TypeT>::value);

    EXT_CONSTEXPR_RUNTIME TypeT min_v = std::numeric_limits<TypeT>::min();
    EXT_CONSTEXPR_RUNTIME TypeT max_v = std::numeric_limits<TypeT>::max();

    CHECK_SAME_TYPE(decltype(phi::abs(phi::unsafe_cast<TypeT>(0))), TypeT);

    EXT_STATIC_REQUIRE(phi::abs(phi::unsafe_cast<TypeT>(0)) == phi::unsafe_cast<TypeT>(0));
    EXT_STATIC_REQUIRE(phi::abs(phi::unsafe_cast<TypeT>(1)) == phi::unsafe_cast<TypeT>(1));
    EXT_STATIC_REQUIRE(phi::abs(phi::unsafe_cast<TypeT>(3)) == phi::unsafe_cast<TypeT>(3));
    EXT_STATIC_REQUIRE(phi::abs(phi::unsafe_cast<TypeT>(21)) == phi::unsafe_cast<TypeT>(21));

    EXT_STATIC_REQUIRE(min_v == phi::unsafe_cast<TypeT>(0));
    EXT_STATIC_REQUIRE(phi::abs(min_v) == phi::unsafe_cast<TypeT>(0));
    EXT_STATIC_REQUIRE(phi::abs(max_v) == max_v);
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

    using f = phi::make_unsafe_t<TypeT>;

    EXT_CONSTEXPR_RUNTIME TypeT inf  = std::numeric_limits<TypeT>::infinity();
    EXT_CONSTEXPR_RUNTIME TypeT qnan = std::numeric_limits<TypeT>::quiet_NaN();
    EXT_CONSTEXPR_RUNTIME TypeT snan = std::numeric_limits<TypeT>::signaling_NaN();

    CHECK_SAME_TYPE(decltype(phi::abs(phi::unsafe_cast<TypeT>(0.0L))), TypeT);

    EXT_STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(0.0L))) ==
                       phi::unsafe_cast<f>(0.0L));
    EXT_STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(-0.0L))) ==
                       phi::unsafe_cast<f>(0.0L));
    EXT_STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(0.5L))) ==
                       phi::unsafe_cast<f>(0.5L));
    EXT_STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(-0.5L))) ==
                       phi::unsafe_cast<f>(0.5L));
    EXT_STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(1.0L))) ==
                       phi::unsafe_cast<f>(1.0L));
    EXT_STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(-1.0L))) ==
                       phi::unsafe_cast<f>(1.0L));
    EXT_STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(3.0L))) ==
                       phi::unsafe_cast<f>(3.0L));
    EXT_STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(-3.0L))) ==
                       phi::unsafe_cast<f>(3.0L));
    EXT_STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(-21.0L))) ==
                       phi::unsafe_cast<f>(21.0L));
    EXT_STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(21.0L))) ==
                       phi::unsafe_cast<f>(21.0L));

    EXT_STATIC_REQUIRE(phi::to_unsafe(phi::abs(inf)) == phi::to_unsafe(inf));
    EXT_STATIC_REQUIRE(phi::to_unsafe(phi::abs(-inf)) == phi::to_unsafe(inf));

    EXT_STATIC_REQUIRE(phi::is_nan(phi::abs(qnan)));
    EXT_STATIC_REQUIRE(phi::is_nan(phi::abs(-qnan)));

    EXT_STATIC_REQUIRE(phi::is_nan(phi::abs(snan)));
    EXT_STATIC_REQUIRE(phi::is_nan(phi::abs(-snan)));
}

TEST_CASE("abs")
{
    SECTION("Abs signed", "[Math][Abs]")
    {
        test_abs_signed<signed char, unsigned char>();
        test_abs_signed<signed short, unsigned short>();
        test_abs_signed<signed int, unsigned int>();
        test_abs_signed<signed long, unsigned long>();
        test_abs_signed<signed long long, unsigned long long>();

        test_abs_signed<phi::integer<signed char>, phi::integer<unsigned char>>();
        test_abs_signed<phi::integer<signed short>, phi::integer<unsigned short>>();
        test_abs_signed<phi::integer<signed int>, phi::integer<unsigned int>>();
        test_abs_signed<phi::integer<signed long>, phi::integer<unsigned long>>();
        test_abs_signed<phi::integer<signed long long>, phi::integer<unsigned long long>>();
    }

    SECTION("Abs unsigned", "[Math][Abs]")
    {
        test_abs_unsigned<unsigned char>();
        test_abs_unsigned<unsigned short>();
        test_abs_unsigned<unsigned int>();
        test_abs_unsigned<unsigned long>();
        test_abs_unsigned<unsigned long long>();
        test_abs_unsigned<char8_t>();
        test_abs_unsigned<char16_t>();
        test_abs_unsigned<char32_t>();

        test_abs_unsigned<phi::integer<unsigned char>>();
        test_abs_unsigned<phi::integer<unsigned short>>();
        test_abs_unsigned<phi::integer<unsigned int>>();
        test_abs_unsigned<phi::integer<unsigned long>>();
        test_abs_unsigned<phi::integer<unsigned long long>>();
    }

    SECTION("Abs floating point", "[Math][Abs]")
    {
        test_abs_float<float>();
        test_abs_float<double>();
        test_abs_float<long double>();

        test_abs_float<phi::floating_point<float>>();
        test_abs_float<phi::floating_point<double>>();
        test_abs_float<phi::floating_point<long double>>();
    }
}

PHI_GCC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()
