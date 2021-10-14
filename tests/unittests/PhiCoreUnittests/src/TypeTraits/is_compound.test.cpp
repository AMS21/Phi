#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_compound.hpp>

template <typename T>
void test_is_compound()
{
    STATIC_REQUIRE(phi::is_compound<T>::value);
    STATIC_REQUIRE(phi::is_compound<const T>::value);
    STATIC_REQUIRE(phi::is_compound<volatile T>::value);
    STATIC_REQUIRE(phi::is_compound<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_compound_v<T>);
    STATIC_REQUIRE(phi::is_compound_v<const T>);
    STATIC_REQUIRE(phi::is_compound_v<volatile T>);
    STATIC_REQUIRE(phi::is_compound_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_compound()
{
    STATIC_REQUIRE_FALSE(phi::is_compound<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_compound<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_compound<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_compound<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_compound_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_compound_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_compound_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_compound_v<const volatile T>);
#endif
}

TEST_CASE("is_compound")
{
    test_is_compound<char[3]>();
    test_is_compound<char[]>();
    test_is_compound<void*>();
    test_is_compound<FunctionPtr>();
    test_is_compound<int&>();
    test_is_compound<int&&>();
    test_is_compound<Union>();
    test_is_compound<Empty>();
    test_is_compound<incomplete_type>();
    test_is_compound<bit_zero>();
    test_is_compound<int*>();
    test_is_compound<const int*>();
    test_is_compound<volatile int*>();
    test_is_compound<const volatile int*>();
    test_is_compound<int**>();
    test_is_compound<Enum>();
    test_is_compound<EnumSigned>();
    test_is_compound<EnumUnsigned>();
    test_is_compound<EnumClass>();
    test_is_compound<NotEmpty>();
    test_is_compound<Abstract>();
    test_is_compound<Class>();
    test_is_compound<Struct>();
    test_is_compound<NonEmptyUnion>();
    test_is_compound<AbstractTemplate<int>>();
    test_is_compound<AbstractTemplate<double>>();
    test_is_compound<MemberObjectPtr>();
    test_is_compound<MemberFunctionPtr>();

    test_is_not_compound<phi::nullptr_t>();
    test_is_not_compound<void>();
    test_is_not_compound<bool>();
    test_is_not_compound<char>();
    test_is_not_compound<signed char>();
    test_is_not_compound<unsigned char>();
    test_is_not_compound<short>();
    test_is_not_compound<unsigned short>();
    test_is_not_compound<int>();
    test_is_not_compound<unsigned>();
    test_is_not_compound<long>();
    test_is_not_compound<unsigned long>();
    test_is_not_compound<long long>();
    test_is_not_compound<unsigned long long>();
    test_is_not_compound<float>();
    test_is_not_compound<double>();
    test_is_not_compound<long double>();
}
