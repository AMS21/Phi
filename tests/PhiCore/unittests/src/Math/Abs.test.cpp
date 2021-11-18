#include <Phi/Test/TestMacros.hpp>

#include "ConstexprHelper.hpp"

#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Config/Warning.hpp>
#include <Phi/Core/Conversion.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Math/Abs.hpp>
#include <Phi/Math/IsNan.hpp>
#include <Phi/TypeTraits/is_floating_point.hpp>
#include <Phi/TypeTraits/is_signed.hpp>
#include <Phi/TypeTraits/is_unsigned.hpp>
#include <Phi/TypeTraits/make_unsafe.hpp>
#include <Phi/TypeTraits/to_unsafe.hpp>
#include <limits>

template <typename SourceT, typename ResultT>
void test_abs_signed()
{
    // Sanity checks
    STATIC_REQUIRE(phi::is_signed<SourceT>::value);
    STATIC_REQUIRE(phi::is_unsigned<ResultT>::value);

    CONSTEXPR_RUNTIME SourceT min_v = std::numeric_limits<SourceT>::min();
    CONSTEXPR_RUNTIME SourceT min_p1_v =
            std::numeric_limits<SourceT>::min() + phi::unsafe_cast<SourceT>(1);
    CONSTEXPR_RUNTIME SourceT max_v = std::numeric_limits<SourceT>::max();

    CHECK_SAME_TYPE(decltype(phi::abs(phi::unsafe_cast<SourceT>(0))), ResultT);

    STATIC_REQUIRE(bool(phi::abs(phi::unsafe_cast<SourceT>(0)) == phi::unsafe_cast<ResultT>(0)));
    STATIC_REQUIRE(bool(phi::abs(phi::unsafe_cast<SourceT>(-0)) == phi::unsafe_cast<ResultT>(0)));
    STATIC_REQUIRE(bool(phi::abs(phi::unsafe_cast<SourceT>(1)) == phi::unsafe_cast<ResultT>(1)));
    STATIC_REQUIRE(bool(phi::abs(phi::unsafe_cast<SourceT>(-1)) == phi::unsafe_cast<ResultT>(1)));
    STATIC_REQUIRE(bool(phi::abs(phi::unsafe_cast<SourceT>(3)) == phi::unsafe_cast<ResultT>(3)));
    STATIC_REQUIRE(bool(phi::abs(phi::unsafe_cast<SourceT>(-3)) == phi::unsafe_cast<ResultT>(3)));
    STATIC_REQUIRE(bool(phi::abs(phi::unsafe_cast<SourceT>(21)) == phi::unsafe_cast<ResultT>(21)));
    STATIC_REQUIRE(bool(phi::abs(phi::unsafe_cast<SourceT>(-21)) == phi::unsafe_cast<ResultT>(21)));

    STATIC_REQUIRE(bool(phi::abs(min_p1_v) == phi::unsafe_cast<ResultT>(max_v)));
    STATIC_REQUIRE(bool(phi::abs(min_v) ==
                        phi::unsafe_cast<ResultT>(max_v) + phi::unsafe_cast<ResultT>(1)));
    STATIC_REQUIRE(bool(phi::abs(max_v) == phi::unsafe_cast<ResultT>(max_v)));
}

template <typename TypeT>
void test_abs_unsigned()
{
    // Sanity checks
    STATIC_REQUIRE(phi::is_unsigned<TypeT>::value);

    CONSTEXPR_RUNTIME TypeT min_v = std::numeric_limits<TypeT>::min();
    CONSTEXPR_RUNTIME TypeT max_v = std::numeric_limits<TypeT>::max();

    CHECK_SAME_TYPE(decltype(phi::abs(phi::unsafe_cast<TypeT>(0))), TypeT);

    STATIC_REQUIRE(bool(phi::abs(phi::unsafe_cast<TypeT>(0)) == phi::unsafe_cast<TypeT>(0)));
    STATIC_REQUIRE(bool(phi::abs(phi::unsafe_cast<TypeT>(1)) == phi::unsafe_cast<TypeT>(1)));
    STATIC_REQUIRE(bool(phi::abs(phi::unsafe_cast<TypeT>(3)) == phi::unsafe_cast<TypeT>(3)));
    STATIC_REQUIRE(bool(phi::abs(phi::unsafe_cast<TypeT>(21)) == phi::unsafe_cast<TypeT>(21)));

    STATIC_REQUIRE(bool(min_v == phi::unsafe_cast<TypeT>(0)));
    STATIC_REQUIRE(bool(phi::abs(min_v) == phi::unsafe_cast<TypeT>(0)));
    STATIC_REQUIRE(bool(phi::abs(max_v) == max_v));
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

    CONSTEXPR_RUNTIME TypeT inf  = std::numeric_limits<TypeT>::infinity();
    CONSTEXPR_RUNTIME TypeT qnan = std::numeric_limits<TypeT>::quiet_NaN();
    CONSTEXPR_RUNTIME TypeT snan = std::numeric_limits<TypeT>::signaling_NaN();

    CHECK_SAME_TYPE(decltype(phi::abs(phi::unsafe_cast<TypeT>(0.0L))), TypeT);

    STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(0.0L))) ==
                   phi::unsafe_cast<f>(0.0L));
    STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(-0.0L))) ==
                   phi::unsafe_cast<f>(0.0L));
    STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(0.5L))) ==
                   phi::unsafe_cast<f>(0.5L));
    STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(-0.5L))) ==
                   phi::unsafe_cast<f>(0.5L));
    STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(1.0L))) ==
                   phi::unsafe_cast<f>(1.0L));
    STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(-1.0L))) ==
                   phi::unsafe_cast<f>(1.0L));
    STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(3.0L))) ==
                   phi::unsafe_cast<f>(3.0L));
    STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(-3.0L))) ==
                   phi::unsafe_cast<f>(3.0L));
    STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(-21.0L))) ==
                   phi::unsafe_cast<f>(21.0L));
    STATIC_REQUIRE(phi::to_unsafe(phi::abs(phi::unsafe_cast<TypeT>(21.0L))) ==
                   phi::unsafe_cast<f>(21.0L));

    STATIC_REQUIRE(phi::to_unsafe(phi::abs(inf)) == phi::to_unsafe(inf));
    STATIC_REQUIRE(phi::to_unsafe(phi::abs(-inf)) == phi::to_unsafe(inf));

    STATIC_REQUIRE(phi::IsNaN(phi::abs(qnan)));
    STATIC_REQUIRE(phi::IsNaN(phi::abs(-qnan)));

    STATIC_REQUIRE(phi::IsNaN(phi::abs(snan)));
    STATIC_REQUIRE(phi::IsNaN(phi::abs(-snan)));
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

        test_abs_signed<phi::Integer<signed char>, phi::Integer<unsigned char>>();
        test_abs_signed<phi::Integer<signed short>, phi::Integer<unsigned short>>();
        test_abs_signed<phi::Integer<signed int>, phi::Integer<unsigned int>>();
        test_abs_signed<phi::Integer<signed long>, phi::Integer<unsigned long>>();
        test_abs_signed<phi::Integer<signed long long>, phi::Integer<unsigned long long>>();
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

        test_abs_unsigned<phi::Integer<unsigned char>>();
        test_abs_unsigned<phi::Integer<unsigned short>>();
        test_abs_unsigned<phi::Integer<unsigned int>>();
        test_abs_unsigned<phi::Integer<unsigned long>>();
        test_abs_unsigned<phi::Integer<unsigned long long>>();
    }

    SECTION("Abs floating point", "[Math][Abs]")
    {
        test_abs_float<float>();
        test_abs_float<double>();
        test_abs_float<long double>();

        test_abs_float<phi::FloatingPoint<float>>();
        test_abs_float<phi::FloatingPoint<double>>();
        test_abs_float<phi::FloatingPoint<long double>>();
    }
}

PHI_GCC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()
