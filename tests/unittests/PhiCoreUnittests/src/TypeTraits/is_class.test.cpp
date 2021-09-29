#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/TypeTraits/is_class.hpp>

template <typename T>
void test_is_class()
{
    STATIC_REQUIRE(phi::is_class<T>::value);
    STATIC_REQUIRE(phi::is_class<const T>::value);
    STATIC_REQUIRE(phi::is_class<volatile T>::value);
    STATIC_REQUIRE(phi::is_class<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_class_v<T>);
    STATIC_REQUIRE(phi::is_class_v<const T>);
    STATIC_REQUIRE(phi::is_class_v<volatile T>);
    STATIC_REQUIRE(phi::is_class_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_class()
{
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_class<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_class<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_class<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_class_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_class_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_class_v<const volatile T>);
#endif
}

TEST_CASE("is_class")
{
    test_is_class<Class>();
    test_is_class<Struct>();
    test_is_class<Empty>();
    test_is_class<NotEmpty>();
    test_is_class<bit_zero>();
    test_is_class<NotEmpty>();
    test_is_class<Abstract>();
    test_is_class<AbstractTemplate<int>>();
    test_is_class<AbstractTemplate<double>>();
    test_is_class<incomplete_type>();

    test_is_not_class<phi::nullptr_t>();
    test_is_not_class<void>();
    test_is_not_class<int>();
    test_is_not_class<int&>();
    test_is_not_class<int&&>();
    test_is_not_class<int*>();
    test_is_not_class<const int*>();
    test_is_not_class<volatile int*>();
    test_is_not_class<const volatile int*>();
    test_is_not_class<int**>();
    test_is_not_class<double>();
    test_is_not_class<char[3]>();
    test_is_not_class<char[]>();
    test_is_not_class<Enum>();
    test_is_not_class<EnumSigned>();
    test_is_not_class<EnumUnsigned>();
    test_is_not_class<EnumClass>();
    test_is_not_class<Union>();
    test_is_not_class<NonEmptyUnion>();
    test_is_not_class<FunctionPtr>();
    test_is_not_class<MemberObjectPtr>();
    test_is_not_class<MemberFunctionPtr>();
}
