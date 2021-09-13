#include <catch2/catch_test_macros.hpp>

#include "TestTypes.hpp"
#include <Phi/TypeTraits/is_enum.hpp>

template <typename T>
void test_is_enum()
{
    STATIC_REQUIRE(phi::is_enum<T>::value);
    STATIC_REQUIRE(phi::is_enum<const T>::value);
    STATIC_REQUIRE(phi::is_enum<volatile T>::value);
    STATIC_REQUIRE(phi::is_enum<const volatile T>::value);

    STATIC_REQUIRE(phi::is_enum_v<T>);
    STATIC_REQUIRE(phi::is_enum_v<const T>);
    STATIC_REQUIRE(phi::is_enum_v<volatile T>);
    STATIC_REQUIRE(phi::is_enum_v<const volatile T>);
}

template <typename T>
void test_is_not_enum()
{
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_enum<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_enum<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_enum<const volatile T>::value);

    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_enum_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_enum_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_enum_v<const volatile T>);
}

TEST_CASE("is_enum")
{
    test_is_enum<Enum>();
    test_is_enum<EnumSigned>();
    test_is_enum<EnumUnsigned>();
    test_is_enum<EnumClass>();

    test_is_not_enum<phi::nullptr_t>();
    test_is_not_enum<void>();
    test_is_not_enum<int>();
    test_is_not_enum<short>();
    test_is_not_enum<float>();
    test_is_not_enum<double>();
    test_is_not_enum<int&>();
    test_is_not_enum<int&&>();
    test_is_not_enum<int*>();
    test_is_not_enum<const int*>();
    test_is_not_enum<volatile int*>();
    test_is_not_enum<const volatile int*>();
    test_is_not_enum<char[3]>();
    test_is_not_enum<char[]>();
    test_is_not_enum<Class>();
    test_is_not_enum<Struct>();
    test_is_not_enum<Union>();
    test_is_not_enum<Empty>();
    test_is_not_enum<NonEmptyUnion>();
    test_is_not_enum<bit_zero>();
    test_is_not_enum<bit_one>();
    test_is_not_enum<NotEmpty>();
    test_is_not_enum<Abstract>();
    test_is_not_enum<AbstractTemplate<int>>();
    test_is_not_enum<AbstractTemplate<double>>();
    test_is_not_enum<Function>();
    test_is_not_enum<FunctionPtr>();
    test_is_not_enum<MemberObjectPtr>();
    test_is_not_enum<MemberFunctionPtr>();
    test_is_not_enum<incomplete_type>();
}
