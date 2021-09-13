#include <catch2/catch_test_macros.hpp>

#include "TestTypes.hpp"
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_const.hpp>

template <typename T>
void test_is_const()
{
    STATIC_REQUIRE_FALSE(phi::is_const<T>::value);
    STATIC_REQUIRE(phi::is_const<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_const<volatile T>::value);
    STATIC_REQUIRE(phi::is_const<const volatile T>::value);

    STATIC_REQUIRE_FALSE(phi::is_const_v<T>);
    STATIC_REQUIRE(phi::is_const_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_const_v<volatile T>);
    STATIC_REQUIRE(phi::is_const_v<const volatile T>);
}

template <typename T>
void test_is_not_const()
{
    STATIC_REQUIRE_FALSE(phi::is_const<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_const<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_const<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_const<const volatile T>::value);

    STATIC_REQUIRE_FALSE(phi::is_const_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_const_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_const_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_const_v<const volatile T>);
}

struct A; // incomplete

TEST_CASE("is_const")
{
    test_is_const<phi::nullptr_t>();
    test_is_const<void>();
    test_is_const<int>();
    test_is_const<double>();
    test_is_const<int*>();
    test_is_const<const int*>();
    test_is_const<volatile int*>();
    test_is_const<const volatile int*>();
    test_is_const<int**>();
    test_is_const<char[3]>();
    test_is_const<char[]>();

    test_is_const<Class>();
    test_is_const<Struct>();
    test_is_const<Empty>();
    test_is_const<NotEmpty>();
    test_is_const<Union>();
    test_is_const<NonEmptyUnion>();
    test_is_const<bit_zero>();
    test_is_const<Abstract>();
    test_is_const<AbstractTemplate<int>>();
    test_is_const<AbstractTemplate<double>>();
    test_is_const<Enum>();
    test_is_const<EnumSigned>();
    test_is_const<EnumUnsigned>();
    test_is_const<EnumClass>();
    test_is_const<incomplete_type>();
    test_is_const<FunctionPtr>();
    test_is_const<MemberObjectPtr>();
    test_is_const<MemberFunctionPtr>();
    test_is_const<A>();

    test_is_not_const<int&>();
    test_is_not_const<int&&>();
    test_is_not_const<float&>();
    test_is_not_const<float&&>();
    test_is_not_const<Class&>();
    test_is_not_const<Class&&>();
}
