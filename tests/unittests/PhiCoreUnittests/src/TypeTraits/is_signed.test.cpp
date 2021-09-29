#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_signed.hpp>

struct A; // incomplete

template <typename TypeT>
void test_is_signed()
{
    STATIC_REQUIRE(phi::is_signed<TypeT>::value);
    STATIC_REQUIRE(phi::is_signed<const TypeT>::value);
    STATIC_REQUIRE(phi::is_signed<volatile TypeT>::value);
    STATIC_REQUIRE(phi::is_signed<const volatile TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_signed_v<TypeT>);
    STATIC_REQUIRE(phi::is_signed_v<const TypeT>);
    STATIC_REQUIRE(phi::is_signed_v<volatile TypeT>);
    STATIC_REQUIRE(phi::is_signed_v<const volatile TypeT>);
#endif
}

template <typename TypeT>
void test_is_not_signed()
{
    STATIC_REQUIRE_FALSE(phi::is_signed<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_signed<const TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_signed<volatile TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_signed<const volatile TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_signed_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_signed_v<const TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_signed_v<volatile TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_signed_v<const volatile TypeT>);
#endif
}

TEST_CASE("is_signed", "[TypeTraits][is_signed]")
{
    // Cases where !is_arithmetic implies !is_signed
    test_is_not_signed<phi::nullptr_t>();
    test_is_not_signed<void>();
    test_is_not_signed<int&>();
    test_is_not_signed<int&&>();
    test_is_not_signed<Class>();
    test_is_not_signed<Struct>();
    test_is_not_signed<int*>();
    test_is_not_signed<const int*>();
    test_is_not_signed<volatile int*>();
    test_is_not_signed<const volatile int*>();
    test_is_not_signed<int**>();
    test_is_not_signed<char[3]>();
    test_is_not_signed<char[]>();
    test_is_not_signed<Union>();
    test_is_not_signed<NonEmptyUnion>();
    test_is_not_signed<Enum>();
    test_is_not_signed<EnumSigned>();
    test_is_not_signed<EnumUnsigned>();
    test_is_not_signed<EnumClass>();
    test_is_not_signed<FunctionPtr>();
    test_is_not_signed<Function>();
    test_is_not_signed<MemberObjectPtr>();
    test_is_not_signed<MemberFunctionPtr>();
    test_is_not_signed<Empty>();
    test_is_not_signed<incomplete_type>();
    test_is_not_signed<A>();
    test_is_not_signed<bit_zero>();
    test_is_not_signed<bit_one>();
    test_is_not_signed<NotEmpty>();
    test_is_not_signed<Abstract>();
    test_is_not_signed<AbstractTemplate<int>>();
    test_is_not_signed<AbstractTemplate<double>>();

    test_is_signed<signed char>();
    test_is_signed<short>();
    test_is_signed<int>();
    test_is_signed<long>();
    test_is_signed<long long>();

    test_is_signed<float>();
    test_is_signed<double>();
    test_is_signed<long double>();

    test_is_not_signed<unsigned char>();
    test_is_not_signed<unsigned short>();
    test_is_not_signed<unsigned int>();
    test_is_not_signed<unsigned long>();
    test_is_not_signed<unsigned long long>();

    // safe types
    test_is_signed<phi::Integer<signed char>>();
    test_is_signed<phi::Integer<short>>();
    test_is_signed<phi::Integer<int>>();
    test_is_signed<phi::Integer<long>>();
    test_is_signed<phi::Integer<long long>>();

    test_is_signed<phi::FloatingPoint<float>>();
    test_is_signed<phi::FloatingPoint<double>>();
    test_is_signed<phi::FloatingPoint<long double>>();

    test_is_not_signed<phi::Integer<unsigned char>>();
    test_is_not_signed<phi::Integer<unsigned short>>();
    test_is_not_signed<phi::Integer<unsigned int>>();
    test_is_not_signed<phi::Integer<unsigned long>>();
    test_is_not_signed<phi::Integer<unsigned long long>>();

    test_is_not_signed<phi::Boolean>();
    test_is_not_signed<bool>();
    test_is_not_signed<unsigned>();
    test_is_not_signed<phi::Integer<unsigned>>();

    test_is_not_signed<char8_t>();
    test_is_not_signed<char16_t>();
    test_is_not_signed<char32_t>();
}
