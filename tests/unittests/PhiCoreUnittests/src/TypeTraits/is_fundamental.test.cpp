#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_fundamental.hpp>

template <typename T>
void test_is_fundamental()
{
    STATIC_REQUIRE(phi::is_fundamental<T>::value);
    STATIC_REQUIRE(phi::is_fundamental<const T>::value);
    STATIC_REQUIRE(phi::is_fundamental<volatile T>::value);
    STATIC_REQUIRE(phi::is_fundamental<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_fundamental_v<T>);
    STATIC_REQUIRE(phi::is_fundamental_v<const T>);
    STATIC_REQUIRE(phi::is_fundamental_v<volatile T>);
    STATIC_REQUIRE(phi::is_fundamental_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_fundamental()
{
    STATIC_REQUIRE_FALSE(phi::is_fundamental<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_fundamental<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_fundamental<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_fundamental<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_fundamental_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_fundamental_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_fundamental_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_fundamental_v<const volatile T>);
#endif
}

TEST_CASE("is_fundamental")
{
    test_is_fundamental<phi::nullptr_t>();
    test_is_fundamental<void>();
    test_is_fundamental<short>();
    test_is_fundamental<unsigned short>();
    test_is_fundamental<int>();
    test_is_fundamental<unsigned int>();
    test_is_fundamental<long>();
    test_is_fundamental<unsigned long>();
    test_is_fundamental<long long>();
    test_is_fundamental<unsigned long long>();
    test_is_fundamental<bool>();
    test_is_fundamental<char>();
    test_is_fundamental<signed char>();
    test_is_fundamental<unsigned char>();
    test_is_fundamental<wchar_t>();
    test_is_fundamental<double>();
    test_is_fundamental<float>();
    test_is_fundamental<double>();
    test_is_fundamental<long double>();
    test_is_fundamental<char8_t>();
    test_is_fundamental<char16_t>();
    test_is_fundamental<char32_t>();

    test_is_fundamental<phi::Boolean>();
    test_is_fundamental<phi::Integer<signed char>>();
    test_is_fundamental<phi::Integer<unsigned char>>();
    test_is_fundamental<phi::Integer<short>>();
    test_is_fundamental<phi::Integer<unsigned short>>();
    test_is_fundamental<phi::Integer<int>>();
    test_is_fundamental<phi::Integer<unsigned int>>();
    test_is_fundamental<phi::Integer<long>>();
    test_is_fundamental<phi::Integer<unsigned long>>();
    test_is_fundamental<phi::Integer<long long>>();
    test_is_fundamental<phi::Integer<unsigned long long>>();
    test_is_fundamental<phi::FloatingPoint<float>>();
    test_is_fundamental<phi::FloatingPoint<double>>();
    test_is_fundamental<phi::FloatingPoint<long double>>();

    test_is_not_fundamental<char[3]>();
    test_is_not_fundamental<char[]>();
    test_is_not_fundamental<void*>();
    test_is_not_fundamental<Function>();
    test_is_not_fundamental<FunctionPtr>();
    test_is_not_fundamental<MemberObjectPtr>();
    test_is_not_fundamental<MemberFunctionPtr>();
    test_is_not_fundamental<int&>();
    test_is_not_fundamental<int&&>();
    test_is_not_fundamental<Union>();
    test_is_not_fundamental<Empty>();
    test_is_not_fundamental<incomplete_type>();
    test_is_not_fundamental<bit_zero>();
    test_is_not_fundamental<bit_one>();
    test_is_not_fundamental<int*>();
    test_is_not_fundamental<const int*>();
    test_is_not_fundamental<volatile int*>();
    test_is_not_fundamental<const volatile int*>();
    test_is_not_fundamental<int**>();
    test_is_not_fundamental<Enum>();
    test_is_not_fundamental<EnumSigned>();
    test_is_not_fundamental<EnumUnsigned>();
    test_is_not_fundamental<EnumClass>();
    test_is_not_fundamental<NotEmpty>();
    test_is_not_fundamental<Abstract>();
    test_is_not_fundamental<Class>();
    test_is_not_fundamental<Struct>();
    test_is_not_fundamental<NonEmptyUnion>();
    test_is_not_fundamental<AbstractTemplate<int>>();
    test_is_not_fundamental<AbstractTemplate<double>>();
}
