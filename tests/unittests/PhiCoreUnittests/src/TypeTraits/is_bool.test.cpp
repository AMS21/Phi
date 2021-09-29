#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_bool.hpp>

template <typename T>
void test_is_bool()
{
    STATIC_REQUIRE(phi::is_bool<T>::value);
    STATIC_REQUIRE(phi::is_bool<const T>::value);
    STATIC_REQUIRE(phi::is_bool<volatile T>::value);
    STATIC_REQUIRE(phi::is_bool<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_bool_v<T>);
    STATIC_REQUIRE(phi::is_bool_v<const T>);
    STATIC_REQUIRE(phi::is_bool_v<volatile T>);
    STATIC_REQUIRE(phi::is_bool_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_bool()
{
    STATIC_REQUIRE_FALSE(phi::is_bool<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_bool<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_bool<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_bool<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_bool_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_bool_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_bool_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_bool_v<const volatile T>);
#endif
}

TEST_CASE("is_bool")
{
    test_is_not_bool<phi::nullptr_t>();
    test_is_not_bool<void>();
    test_is_not_bool<int>();
    test_is_not_bool<float>();
    test_is_not_bool<char[]>();
    test_is_not_bool<char[3]>();
    test_is_not_bool<int&>();
    test_is_not_bool<int&&>();
    test_is_not_bool<int*>();
    test_is_not_bool<const int*>();
    test_is_not_bool<volatile int*>();
    test_is_not_bool<const volatile int*>();
    test_is_not_bool<int**>();
    test_is_not_bool<Class>();
    test_is_not_bool<Struct>();
    test_is_not_bool<Empty>();
    test_is_not_bool<NotEmpty>();
    test_is_not_bool<Union>();
    test_is_not_bool<NonEmptyUnion>();
    test_is_not_bool<bit_zero>();
    test_is_not_bool<Abstract>();
    test_is_not_bool<AbstractTemplate<int>>();
    test_is_not_bool<AbstractTemplate<double>>();
    test_is_not_bool<Enum>();
    test_is_not_bool<EnumSigned>();
    test_is_not_bool<EnumUnsigned>();
    test_is_not_bool<EnumClass>();
    test_is_not_bool<FunctionPtr>();
    test_is_not_bool<MemberObjectPtr>();
    test_is_not_bool<MemberFunctionPtr>();

    test_is_bool<bool>();
    test_is_bool<phi::Boolean>();
}
