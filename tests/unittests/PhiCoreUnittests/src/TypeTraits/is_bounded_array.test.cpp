#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_bounded_array.hpp>

template <typename T>
void test_is_bounded_array()
{
    STATIC_REQUIRE(phi::is_bounded_array<T>::value);
    STATIC_REQUIRE(phi::is_bounded_array<const T>::value);
    STATIC_REQUIRE(phi::is_bounded_array<volatile T>::value);
    STATIC_REQUIRE(phi::is_bounded_array<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_bounded_array_v<T>);
    STATIC_REQUIRE(phi::is_bounded_array_v<const T>);
    STATIC_REQUIRE(phi::is_bounded_array_v<volatile T>);
    STATIC_REQUIRE(phi::is_bounded_array_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_bounded_array()
{
    STATIC_REQUIRE_FALSE(phi::is_bounded_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_bounded_array<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_bounded_array<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_bounded_array<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_bounded_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_bounded_array_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_bounded_array_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_bounded_array_v<const volatile T>);
#endif
}

class A
{};

TEST_CASE("is_bounded_array")
{
    test_is_not_bounded_array<phi::nullptr_t>();
    test_is_not_bounded_array<void>();
    test_is_not_bounded_array<int>();
    test_is_not_bounded_array<float>();
    test_is_not_bounded_array<int&>();
    test_is_not_bounded_array<int&&>();
    test_is_not_bounded_array<int*>();
    test_is_not_bounded_array<const int*>();
    test_is_not_bounded_array<volatile int*>();
    test_is_not_bounded_array<const volatile int*>();
    test_is_not_bounded_array<int**>();
    test_is_not_bounded_array<Class>();
    test_is_not_bounded_array<Struct>();
    test_is_not_bounded_array<Empty>();
    test_is_not_bounded_array<NotEmpty>();
    test_is_not_bounded_array<Union>();
    test_is_not_bounded_array<NonEmptyUnion>();
    test_is_not_bounded_array<bit_zero>();
    test_is_not_bounded_array<Abstract>();
    test_is_not_bounded_array<AbstractTemplate<int>>();
    test_is_not_bounded_array<AbstractTemplate<double>>();
    test_is_not_bounded_array<Enum>();
    test_is_not_bounded_array<EnumSigned>();
    test_is_not_bounded_array<EnumUnsigned>();
    test_is_not_bounded_array<EnumClass>();
    test_is_not_bounded_array<FunctionPtr>();
    test_is_not_bounded_array<MemberObjectPtr>();
    test_is_not_bounded_array<MemberFunctionPtr>();

    test_is_not_bounded_array<char[]>();
    test_is_not_bounded_array<char[][3]>();
    test_is_bounded_array<char[3]>();
    test_is_bounded_array<char[3][3]>();
}
