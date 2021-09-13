#include <catch2/catch_test_macros.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_integral.hpp>

template <typename T>
void test_is_integral()
{
    STATIC_REQUIRE(phi::is_integral<T>::value);
    STATIC_REQUIRE(phi::is_integral<const T>::value);
    STATIC_REQUIRE(phi::is_integral<volatile T>::value);
    STATIC_REQUIRE(phi::is_integral<const volatile T>::value);

    STATIC_REQUIRE(phi::is_integral_v<T>);
    STATIC_REQUIRE(phi::is_integral_v<const T>);
    STATIC_REQUIRE(phi::is_integral_v<volatile T>);
    STATIC_REQUIRE(phi::is_integral_v<const volatile T>);
}

template <typename T>
void test_is_not_integral()
{
    STATIC_REQUIRE_FALSE(phi::is_integral<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_integral<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_integral<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_integral<const volatile T>::value);

    STATIC_REQUIRE_FALSE(phi::is_integral_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_integral_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_integral_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_integral_v<const volatile T>);
}

TEST_CASE("is_integral")
{
    test_is_integral<short>();
    test_is_integral<unsigned short>();
    test_is_integral<int>();
    test_is_integral<unsigned int>();
    test_is_integral<long>();
    test_is_integral<unsigned long>();
    test_is_integral<bool>();
    test_is_integral<char>();
    test_is_integral<signed char>();
    test_is_integral<unsigned char>();
    test_is_integral<wchar_t>();
#if PHI_HAS_FEATURE_CHAR8_T()
    test_is_integral<char8_t>();
#endif
    test_is_integral<char16_t>();
    test_is_integral<char32_t>();

    test_is_not_integral<phi::nullptr_t>();
    test_is_not_integral<void>();
    test_is_not_integral<int&>();
    test_is_not_integral<int&&>();
    test_is_not_integral<int*>();
    test_is_not_integral<const int*>();
    test_is_not_integral<volatile int*>();
    test_is_not_integral<const volatile int*>();
    test_is_not_integral<int**>();
    test_is_not_integral<float>();
    test_is_not_integral<double>();
    test_is_not_integral<char[3]>();
    test_is_not_integral<char[]>();
    test_is_not_integral<Class>();
    test_is_not_integral<Struct>();
    test_is_not_integral<Union>();
    test_is_not_integral<NonEmptyUnion>();
    test_is_not_integral<Enum>();
    test_is_not_integral<EnumSigned>();
    test_is_not_integral<EnumUnsigned>();
    test_is_not_integral<EnumClass>();
    test_is_not_integral<Function>();
    test_is_not_integral<FunctionPtr>();
    test_is_not_integral<MemberObjectPtr>();
    test_is_not_integral<MemberFunctionPtr>();
    test_is_not_integral<Empty>();
    test_is_not_integral<bit_zero>();
    test_is_not_integral<bit_one>();
    test_is_not_integral<NotEmpty>();
    test_is_not_integral<Abstract>();
    test_is_not_integral<AbstractTemplate<int>>();
    test_is_not_integral<AbstractTemplate<double>>();
    test_is_not_integral<incomplete_type>();
}
