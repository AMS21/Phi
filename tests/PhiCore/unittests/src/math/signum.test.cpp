#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/unsafe_cast.hpp>
#include <phi/math/signum.hpp>
#include <cstdint>
#include <limits>

template <typename TypeT>
void test_signum_signed()
{
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(0)) == 0);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(-1)) == -1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(1)) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(21)) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(-21)) == -1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(std::numeric_limits<TypeT>::max())) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(std::numeric_limits<TypeT>::min())) == -1);
}

template <typename TypeT>
void test_signum_unsigned()
{
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(0)) == 0);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(1)) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(21)) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(std::numeric_limits<TypeT>::max())) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(std::numeric_limits<TypeT>::min())) == 0);
}

template <typename TypeT>
void test_signum_float()
{
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(0.0)) == 0);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(-0.0)) == 0);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(-1.0)) == -1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(1.0)) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(21.0)) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(-21.0)) == -1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(std::numeric_limits<TypeT>::max())) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(std::numeric_limits<TypeT>::min())) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<TypeT>(std::numeric_limits<TypeT>::lowest())) ==
                   -1);
}

TEST_CASE("signum")
{
    // Signed
    test_signum_signed<signed char>();
    test_signum_signed<short>();
    test_signum_signed<int>();
    test_signum_signed<long>();
    test_signum_signed<long long>();
    test_signum_signed<phi::integer<signed char>>();
    test_signum_signed<phi::integer<short>>();
    test_signum_signed<phi::integer<int>>();
    test_signum_signed<phi::integer<long>>();
    test_signum_signed<phi::integer<long long>>();

    // Unsigned
    test_signum_unsigned<unsigned char>();
    test_signum_unsigned<unsigned short>();
    test_signum_unsigned<unsigned int>();
    test_signum_unsigned<unsigned long>();
    test_signum_unsigned<unsigned long long>();
    test_signum_unsigned<phi::integer<unsigned char>>();
    test_signum_unsigned<phi::integer<unsigned short>>();
    test_signum_unsigned<phi::integer<unsigned int>>();
    test_signum_unsigned<phi::integer<unsigned long>>();
    test_signum_unsigned<phi::integer<unsigned long long>>();

    // Float
    test_signum_float<float>();
    test_signum_float<double>();
    test_signum_float<long double>();
    test_signum_float<phi::floating_point<float>>();
    test_signum_float<phi::floating_point<double>>();
    test_signum_float<phi::floating_point<long double>>();
}
