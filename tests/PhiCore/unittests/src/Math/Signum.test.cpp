#include <Phi/Test/TestMacros.hpp>

#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Conversion.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Math/Signum.hpp>
#include <cstdint>
#include <limits>

template <typename T>
void test_signum_signed()
{
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(0)) == 0);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(-1)) == -1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(1)) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(21)) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(-21)) == -1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(std::numeric_limits<T>::max())) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(std::numeric_limits<T>::min())) == -1);
}

template <typename T>
void test_signum_unsigned()
{
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(0)) == 0);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(1)) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(21)) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(std::numeric_limits<T>::max())) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(std::numeric_limits<T>::min())) == 0);
}

template <typename T>
void test_signum_float()
{
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(0.0)) == 0);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(-0.0)) == 0);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(-1.0)) == -1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(1.0)) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(21.0)) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(-21.0)) == -1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(std::numeric_limits<T>::max())) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(std::numeric_limits<T>::min())) == 1);
    STATIC_REQUIRE(phi::signum(phi::unsafe_cast<T>(std::numeric_limits<T>::lowest())) == -1);
}

TEST_CASE("signum")
{
    // Signed
    test_signum_signed<signed char>();
    test_signum_signed<short>();
    test_signum_signed<int>();
    test_signum_signed<long>();
    test_signum_signed<long long>();
    test_signum_signed<phi::Integer<signed char>>();
    test_signum_signed<phi::Integer<short>>();
    test_signum_signed<phi::Integer<int>>();
    test_signum_signed<phi::Integer<long>>();
    test_signum_signed<phi::Integer<long long>>();

    // Unsigned
    test_signum_unsigned<unsigned char>();
    test_signum_unsigned<unsigned short>();
    test_signum_unsigned<unsigned int>();
    test_signum_unsigned<unsigned long>();
    test_signum_unsigned<unsigned long long>();
    test_signum_unsigned<phi::Integer<unsigned char>>();
    test_signum_unsigned<phi::Integer<unsigned short>>();
    test_signum_unsigned<phi::Integer<unsigned int>>();
    test_signum_unsigned<phi::Integer<unsigned long>>();
    test_signum_unsigned<phi::Integer<unsigned long long>>();

    // Float
    test_signum_float<float>();
    test_signum_float<double>();
    test_signum_float<long double>();
    test_signum_float<phi::FloatingPoint<float>>();
    test_signum_float<phi::FloatingPoint<double>>();
    test_signum_float<phi::FloatingPoint<long double>>();
}
