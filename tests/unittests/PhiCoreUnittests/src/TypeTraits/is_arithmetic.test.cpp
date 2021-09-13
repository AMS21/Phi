#include <catch2/catch_test_macros.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/TypeTraits/is_arithmetic.hpp>

template <class T>
void test_is_arithmetic()
{
    STATIC_REQUIRE(phi::is_arithmetic<T>::value);
    STATIC_REQUIRE(phi::is_arithmetic<const T>::value);
    STATIC_REQUIRE(phi::is_arithmetic<volatile T>::value);
    STATIC_REQUIRE(phi::is_arithmetic<const volatile T>::value);

    STATIC_REQUIRE(phi::is_arithmetic_v<T>);
    STATIC_REQUIRE(phi::is_arithmetic_v<const T>);
    STATIC_REQUIRE(phi::is_arithmetic_v<volatile T>);
    STATIC_REQUIRE(phi::is_arithmetic_v<const volatile T>);
}

template <class T>
void test_is_not_arithmetic()
{
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<const volatile T>::value);

    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<const volatile T>);
}

TEST_CASE("is_arithmetic")
{
    test_is_arithmetic<short>();
    test_is_arithmetic<unsigned short>();
    test_is_arithmetic<int>();
    test_is_arithmetic<unsigned int>();
    test_is_arithmetic<long>();
    test_is_arithmetic<unsigned long>();
    test_is_arithmetic<long long>();
    test_is_arithmetic<unsigned long long>();
    test_is_arithmetic<bool>();
    test_is_arithmetic<char>();
    test_is_arithmetic<signed char>();
    test_is_arithmetic<unsigned char>();
    test_is_arithmetic<wchar_t>();
    test_is_arithmetic<char8_t>();
    test_is_arithmetic<char16_t>();
    test_is_arithmetic<char32_t>();
    test_is_arithmetic<float>();
    test_is_arithmetic<double>();
    test_is_arithmetic<long double>();

    // Safe types
    test_is_arithmetic<phi::Boolean>();
    test_is_arithmetic<phi::Integer<signed char>>();
    test_is_arithmetic<phi::Integer<unsigned char>>();
    test_is_arithmetic<phi::Integer<short>>();
    test_is_arithmetic<phi::Integer<unsigned short>>();
    test_is_arithmetic<phi::Integer<int>>();
    test_is_arithmetic<phi::Integer<unsigned int>>();
    test_is_arithmetic<phi::Integer<long>>();
    test_is_arithmetic<phi::Integer<unsigned long>>();
    test_is_arithmetic<phi::Integer<long long>>();
    test_is_arithmetic<phi::Integer<unsigned long long>>();
    test_is_arithmetic<phi::FloatingPoint<float>>();
    test_is_arithmetic<phi::FloatingPoint<double>>();
    test_is_arithmetic<phi::FloatingPoint<long double>>();

    test_is_not_arithmetic<phi::nullptr_t>();
    test_is_not_arithmetic<void>();
    test_is_not_arithmetic<int&>();
    test_is_not_arithmetic<int&&>();
    test_is_not_arithmetic<int*>();
    test_is_not_arithmetic<const int*>();
    test_is_not_arithmetic<volatile int*>();
    test_is_not_arithmetic<const volatile int*>();
    test_is_not_arithmetic<int**>();
    test_is_not_arithmetic<char[3]>();
    test_is_not_arithmetic<char[]>();
    test_is_not_arithmetic<Union>();
    test_is_not_arithmetic<Enum>();
    test_is_not_arithmetic<EnumSigned>();
    test_is_not_arithmetic<EnumUnsigned>();
    test_is_not_arithmetic<EnumClass>();
    test_is_not_arithmetic<FunctionPtr>();
    test_is_not_arithmetic<Empty>();
    test_is_not_arithmetic<incomplete_type>();
    test_is_not_arithmetic<bit_zero>();
    test_is_not_arithmetic<NotEmpty>();
    test_is_not_arithmetic<Abstract>();
    test_is_not_arithmetic<Class>();
    test_is_not_arithmetic<Struct>();
    test_is_not_arithmetic<NonEmptyUnion>();
    test_is_not_arithmetic<AbstractTemplate<int>>();
    test_is_not_arithmetic<AbstractTemplate<double>>();
    test_is_not_arithmetic<MemberFunctionPtr>();
    test_is_not_arithmetic<MemberObjectPtr>();
}
