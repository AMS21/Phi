#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Features.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_integer.hpp>

struct A; // incomplete

template <typename TypeT>
void test_is_integer()
{
    STATIC_REQUIRE(phi::is_integer<TypeT>::value);
    STATIC_REQUIRE(phi::is_integer<const TypeT>::value);
    STATIC_REQUIRE(phi::is_integer<volatile TypeT>::value);
    STATIC_REQUIRE(phi::is_integer<const volatile TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_integer_v<TypeT>);
    STATIC_REQUIRE(phi::is_integer_v<const TypeT>);
    STATIC_REQUIRE(phi::is_integer_v<volatile TypeT>);
    STATIC_REQUIRE(phi::is_integer_v<const volatile TypeT>);
#endif
}

template <typename TypeT>
void test_is_not_integer()
{
    STATIC_REQUIRE_FALSE(phi::is_integer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_integer<const TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_integer<volatile TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_integer<const volatile TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_integer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_integer_v<const TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_integer_v<volatile TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_integer_v<const volatile TypeT>);
#endif
}

TEST_CASE("is_integer", "[TypeTraits][is_integer]")
{
    test_is_not_integer<phi::nullptr_t>();
    test_is_not_integer<void>();
    test_is_not_integer<int&>();
    test_is_not_integer<int&&>();
    test_is_not_integer<Class>();
    test_is_not_integer<Struct>();
    test_is_not_integer<int*>();
    test_is_not_integer<const int*>();
    test_is_not_integer<volatile int*>();
    test_is_not_integer<const volatile int*>();
    test_is_not_integer<int**>();
    test_is_not_integer<char[3]>();
    test_is_not_integer<char[]>();
    test_is_not_integer<Union>();
    test_is_not_integer<NonEmptyUnion>();
    test_is_not_integer<Enum>();
    test_is_not_integer<EnumSigned>();
    test_is_not_integer<EnumUnsigned>();
    test_is_not_integer<EnumClass>();
    test_is_not_integer<Function>();
    test_is_not_integer<FunctionPtr>();
    test_is_not_integer<MemberObjectPtr>();
    test_is_not_integer<MemberFunctionPtr>();
    test_is_not_integer<Empty>();
    test_is_not_integer<incomplete_type>();
    test_is_not_integer<A>();
    test_is_not_integer<bit_zero>();
    test_is_not_integer<bit_one>();
    test_is_not_integer<NotEmpty>();
    test_is_not_integer<Abstract>();
    test_is_not_integer<AbstractTemplate<int>>();
    test_is_not_integer<AbstractTemplate<double>>();

    // unsafe int types
    test_is_integer<signed char>();
    test_is_integer<short>();
    test_is_integer<int>();
    test_is_integer<long>();
    test_is_integer<long long>();

    test_is_integer<unsigned>();
    test_is_integer<unsigned char>();
    test_is_integer<unsigned short>();
    test_is_integer<unsigned int>();
    test_is_integer<unsigned long>();
    test_is_integer<unsigned long long>();

    // safe int types
    test_is_integer<phi::Integer<signed char>>();
    test_is_integer<phi::Integer<short>>();
    test_is_integer<phi::Integer<int>>();
    test_is_integer<phi::Integer<long>>();
    test_is_integer<phi::Integer<long long>>();

    test_is_integer<phi::Integer<unsigned>>();
    test_is_integer<phi::Integer<unsigned char>>();
    test_is_integer<phi::Integer<unsigned short>>();
    test_is_integer<phi::Integer<unsigned int>>();
    test_is_integer<phi::Integer<unsigned long>>();
    test_is_integer<phi::Integer<unsigned long long>>();

    // unsafe float
    test_is_not_integer<float>();
    test_is_not_integer<double>();
    test_is_not_integer<long double>();

    // safe float
    test_is_not_integer<phi::FloatingPoint<float>>();
    test_is_not_integer<phi::FloatingPoint<double>>();
    test_is_not_integer<phi::FloatingPoint<long double>>();

    test_is_not_integer<bool>();
    test_is_not_integer<phi::Boolean>();
    test_is_not_integer<char>();
    test_is_not_integer<wchar_t>();
#if PHI_HAS_FEATURE_CHAR8_T()
    test_is_not_integer<char8_t>();
#endif
    test_is_not_integer<char16_t>();
    test_is_not_integer<char32_t>();
}
