#include <catch2/catch_test_macros.hpp>

#include "Phi/Core/Nullptr.hpp"
#include "TestTypes.hpp"
#include <Phi/TypeTraits/is_final.hpp>

struct A
{};

struct B final : public A
{};

struct C : public A
{};

struct P final
{};

union U1
{};

union U2 final
{};

template <typename T>
void test_is_final()
{
    STATIC_REQUIRE(phi::is_final<T>::value);
    STATIC_REQUIRE(phi::is_final<const T>::value);
    STATIC_REQUIRE(phi::is_final<volatile T>::value);
    STATIC_REQUIRE(phi::is_final<const volatile T>::value);

    STATIC_REQUIRE(phi::is_final_v<T>);
    STATIC_REQUIRE(phi::is_final_v<const T>);
    STATIC_REQUIRE(phi::is_final_v<volatile T>);
    STATIC_REQUIRE(phi::is_final_v<const volatile T>);
}

template <typename T>
void test_is_not_final()
{
    STATIC_REQUIRE_FALSE(phi::is_final<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_final<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_final<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_final<const volatile T>::value);

    STATIC_REQUIRE_FALSE(phi::is_final_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_final_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_final_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_final_v<const volatile T>);
}

TEST_CASE("is_final")
{
    test_is_final<B>();
    test_is_final<P>();
    test_is_final<U2>();

    test_is_not_final<phi::nullptr_t>();
    test_is_not_final<void>();
    test_is_not_final<int>();
    test_is_not_final<short>();
    test_is_not_final<float>();
    test_is_not_final<double>();
    test_is_not_final<int*>();
    test_is_not_final<const int*>();
    test_is_not_final<volatile int*>();
    test_is_not_final<const volatile int*>();
    test_is_not_final<int**>();
    test_is_not_final<int&>();
    test_is_not_final<int&&>();
    test_is_not_final<char[]>();
    test_is_not_final<char[3]>();
    test_is_not_final<P*>();
    test_is_not_final<U1>();
    test_is_not_final<U1*>();
    test_is_not_final<U2*>();
    test_is_not_final<Class>();
    test_is_not_final<Struct>();
    test_is_not_final<Empty>();
    test_is_not_final<NotEmpty>();
    test_is_not_final<Union>();
    test_is_not_final<NonEmptyUnion>();
    test_is_not_final<bit_zero>();
    test_is_not_final<bit_one>();
    test_is_not_final<Abstract>();
    test_is_not_final<AbstractTemplate<int>>();
    test_is_not_final<AbstractTemplate<double>>();
    test_is_not_final<Enum>();
    test_is_not_final<EnumSigned>();
    test_is_not_final<EnumUnsigned>();
    test_is_not_final<EnumClass>();
    test_is_not_final<Function>();
    test_is_not_final<FunctionPtr>();
    test_is_not_final<MemberObjectPtr>();
    test_is_not_final<MemberFunctionPtr>();
}
