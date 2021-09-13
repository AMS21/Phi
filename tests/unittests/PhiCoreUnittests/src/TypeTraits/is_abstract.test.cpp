#include <catch2/catch_test_macros.hpp>

#include "Phi/Core/Nullptr.hpp"
#include "TestTypes.hpp"
#include <Phi/TypeTraits/is_abstract.hpp>

template <class T>
void test_is_abstract()
{
    STATIC_REQUIRE(phi::is_abstract<T>::value);
    STATIC_REQUIRE(phi::is_abstract<const T>::value);
    STATIC_REQUIRE(phi::is_abstract<volatile T>::value);
    STATIC_REQUIRE(phi::is_abstract<const volatile T>::value);

    STATIC_REQUIRE(phi::is_abstract_v<T>);
    STATIC_REQUIRE(phi::is_abstract_v<const T>);
    STATIC_REQUIRE(phi::is_abstract_v<volatile T>);
    STATIC_REQUIRE(phi::is_abstract_v<const volatile T>);
}

template <class T>
void test_is_not_abstract()
{
    STATIC_REQUIRE(!phi::is_abstract<T>::value);
    STATIC_REQUIRE(!phi::is_abstract<const T>::value);
    STATIC_REQUIRE(!phi::is_abstract<volatile T>::value);
    STATIC_REQUIRE(!phi::is_abstract<const volatile T>::value);

    STATIC_REQUIRE(!phi::is_abstract_v<T>);
    STATIC_REQUIRE(!phi::is_abstract_v<const T>);
    STATIC_REQUIRE(!phi::is_abstract_v<volatile T>);
    STATIC_REQUIRE(!phi::is_abstract_v<const volatile T>);
}

TEST_CASE("is_abstract")
{
    test_is_not_abstract<phi::nullptr_t>();
    test_is_not_abstract<void>();
    test_is_not_abstract<int&>();
    test_is_not_abstract<int&&>();
    test_is_not_abstract<int>();
    test_is_not_abstract<float>();
    test_is_not_abstract<double>();
    test_is_not_abstract<int*>();
    test_is_not_abstract<const int*>();
    test_is_not_abstract<volatile int*>();
    test_is_not_abstract<const volatile int*>();
    test_is_not_abstract<int**>();
    test_is_not_abstract<char[3]>();
    test_is_not_abstract<char[]>();
    test_is_not_abstract<Class>();
    test_is_not_abstract<Struct>();
    test_is_not_abstract<Union>();
    test_is_not_abstract<NonEmptyUnion>();
    test_is_not_abstract<Empty>();
    test_is_not_abstract<bit_zero>();
    test_is_not_abstract<NotEmpty>();
    test_is_not_abstract<Enum>();
    test_is_not_abstract<EnumSigned>();
    test_is_not_abstract<EnumUnsigned>();
    test_is_not_abstract<EnumClass>();
    test_is_not_abstract<FunctionPtr>();
    test_is_not_abstract<MemberObjectPtr>();
    test_is_not_abstract<MemberFunctionPtr>();

    test_is_abstract<Abstract>();
    test_is_abstract<AbstractTemplate<int>>();
    test_is_not_abstract<AbstractTemplate<double>>();
}
