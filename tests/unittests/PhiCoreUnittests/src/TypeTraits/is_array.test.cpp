#include <catch2/catch_test_macros.hpp>

#include "TestTypes.hpp"
#include <Phi/TypeTraits/is_array.hpp>

template <class T>
void test_is_array()
{
    STATIC_REQUIRE(phi::is_array<T>::value);
    STATIC_REQUIRE(phi::is_array<const T>::value);
    STATIC_REQUIRE(phi::is_array<volatile T>::value);
    STATIC_REQUIRE(phi::is_array<const volatile T>::value);

    STATIC_REQUIRE(phi::is_array_v<T>);
    STATIC_REQUIRE(phi::is_array_v<const T>);
    STATIC_REQUIRE(phi::is_array_v<volatile T>);
    STATIC_REQUIRE(phi::is_array_v<const volatile T>);
}

template <class T>
void test_is_not_array()
{
    STATIC_REQUIRE_FALSE(phi::is_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<const volatile T>::value);

    STATIC_REQUIRE_FALSE(phi::is_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<const volatile T>);
}

TEST_CASE("is_array")
{
    test_is_array<char[3]>();
    test_is_array<char[]>();
    test_is_array<char[][3]>();
    test_is_array<char[3][3]>();
    test_is_array<Union[]>();

    test_is_not_array<phi::nullptr_t>();
    test_is_not_array<void>();
    test_is_not_array<int&>();
    test_is_not_array<int&&>();
    test_is_not_array<int*>();
    test_is_not_array<const int*>();
    test_is_not_array<volatile int*>();
    test_is_not_array<const volatile int*>();
    test_is_not_array<int**>();
    test_is_not_array<double>();
    test_is_not_array<Enum>();
    test_is_not_array<EnumSigned>();
    test_is_not_array<EnumUnsigned>();
    test_is_not_array<EnumClass>();
    test_is_not_array<Union>();
    test_is_not_array<FunctionPtr>();
    test_is_not_array<Empty>();
    test_is_not_array<bit_zero>();
    test_is_not_array<NotEmpty>();
    test_is_not_array<incomplete_type>(); //  LWG#2582
    test_is_not_array<Class>();
    test_is_not_array<Struct>();
    test_is_not_array<NonEmptyUnion>();
    test_is_not_array<Abstract>();
    test_is_not_array<AbstractTemplate<int>>();
    test_is_not_array<AbstractTemplate<double>>();
    test_is_not_array<FunctionPtr>();
    test_is_not_array<MemberObjectPtr>();
    test_is_not_array<MemberFunctionPtr>();
}
