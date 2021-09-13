#include <catch2/catch_test_macros.hpp>

#include "TestTypes.hpp"
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_lvalue_reference.hpp>

template <typename T>
void test_is_lvalue_reference()
{
    STATIC_REQUIRE(phi::is_lvalue_reference<T>::value);
    STATIC_REQUIRE(phi::is_lvalue_reference<const T>::value);
    STATIC_REQUIRE(phi::is_lvalue_reference<volatile T>::value);
    STATIC_REQUIRE(phi::is_lvalue_reference<const volatile T>::value);

    STATIC_REQUIRE(phi::is_lvalue_reference_v<T>);
    STATIC_REQUIRE(phi::is_lvalue_reference_v<const T>);
    STATIC_REQUIRE(phi::is_lvalue_reference_v<volatile T>);
    STATIC_REQUIRE(phi::is_lvalue_reference_v<const volatile T>);
}

template <typename T>
void test_is_not_lvalue_reference()
{
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<const volatile T>::value);

    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<const volatile T>);
}

TEST_CASE("is_lvalue_reference")
{
    test_is_lvalue_reference<short&>();
    test_is_lvalue_reference<int&>();
    test_is_lvalue_reference<float&>();
    test_is_lvalue_reference<double&>();

    test_is_not_lvalue_reference<phi::nullptr_t>();
    test_is_not_lvalue_reference<void>();
    test_is_not_lvalue_reference<short>();
    test_is_not_lvalue_reference<int>();
    test_is_not_lvalue_reference<int*>();
    test_is_not_lvalue_reference<const int*>();
    test_is_not_lvalue_reference<volatile int*>();
    test_is_not_lvalue_reference<const volatile int*>();
    test_is_not_lvalue_reference<int**>();
    test_is_not_lvalue_reference<int&&>();
    test_is_not_lvalue_reference<float>();
    test_is_not_lvalue_reference<double>();
    test_is_not_lvalue_reference<char[3]>();
    test_is_not_lvalue_reference<char[]>();
    test_is_not_lvalue_reference<Class>();
    test_is_not_lvalue_reference<Struct>();
    test_is_not_lvalue_reference<Empty>();
    test_is_not_lvalue_reference<NotEmpty>();
    test_is_not_lvalue_reference<Union>();
    test_is_not_lvalue_reference<NonEmptyUnion>();
    test_is_not_lvalue_reference<bit_zero>();
    test_is_not_lvalue_reference<bit_one>();
    test_is_not_lvalue_reference<Abstract>();
    test_is_not_lvalue_reference<AbstractTemplate<int>>();
    test_is_not_lvalue_reference<AbstractTemplate<double>>();
    test_is_not_lvalue_reference<Enum>();
    test_is_not_lvalue_reference<EnumSigned>();
    test_is_not_lvalue_reference<EnumUnsigned>();
    test_is_not_lvalue_reference<EnumClass>();
    test_is_not_lvalue_reference<incomplete_type>();
    test_is_not_lvalue_reference<Function>();
    test_is_not_lvalue_reference<FunctionPtr>();
    test_is_not_lvalue_reference<MemberObjectPtr>();
    test_is_not_lvalue_reference<MemberFunctionPtr>();
}
