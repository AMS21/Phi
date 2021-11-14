#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_aggregate.hpp>

template <typename T>
void test_is_aggregate()
{
    STATIC_REQUIRE(phi::is_aggregate<T>::value);
    STATIC_REQUIRE(phi::is_aggregate<const T>::value);
    STATIC_REQUIRE(phi::is_aggregate<volatile T>::value);
    STATIC_REQUIRE(phi::is_aggregate<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_aggregate_v<T>);
    STATIC_REQUIRE(phi::is_aggregate_v<const T>);
    STATIC_REQUIRE(phi::is_aggregate_v<volatile T>);
    STATIC_REQUIRE(phi::is_aggregate_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_aggregate()
{
    STATIC_REQUIRE_FALSE(phi::is_aggregate<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_aggregate<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_aggregate<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_aggregate<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_aggregate_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_aggregate_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_aggregate_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_aggregate_v<const volatile T>);
#endif
}

struct Aggregate
{};

struct HasCons
{
    HasCons(int);
};
struct HasPriv
{
    void PreventUnusedPrivateMemberWarning();

private:
    int x;
};

TEST_CASE("is_aggregate")
{
    test_is_not_aggregate<phi::nullptr_t>();
    test_is_not_aggregate<void>();
    test_is_not_aggregate<int>();
    test_is_not_aggregate<int&>();
    test_is_not_aggregate<int&&>();
    test_is_not_aggregate<int*>();
    test_is_not_aggregate<const int*>();
    test_is_not_aggregate<volatile int*>();
    test_is_not_aggregate<const volatile int*>();
    test_is_not_aggregate<int**>();
    test_is_not_aggregate<float>();
    test_is_not_aggregate<void*>();
    test_is_not_aggregate<void()>();
    test_is_not_aggregate<void() const>();
    test_is_not_aggregate<void (Aggregate::*)(int) const>();
    test_is_not_aggregate<Aggregate&>();
    test_is_not_aggregate<HasCons>();
    test_is_not_aggregate<HasPriv>();
    test_is_not_aggregate<NotEmpty>();
    test_is_not_aggregate<AbstractTemplate<int>>();
    test_is_not_aggregate<Enum>();
    test_is_not_aggregate<EnumSigned>();
    test_is_not_aggregate<EnumUnsigned>();
    test_is_not_aggregate<EnumClass>();
    test_is_not_aggregate<FunctionPtr>();
    test_is_not_aggregate<MemberObjectPtr>();
    test_is_not_aggregate<MemberFunctionPtr>();

    test_is_aggregate<bit_zero>();
    test_is_aggregate<Empty>();
    test_is_aggregate<Class>();
    test_is_aggregate<Aggregate>();
    test_is_aggregate<Aggregate[]>();
    test_is_aggregate<Aggregate[2]>();
    test_is_aggregate<Aggregate[42][101]>();
    test_is_aggregate<Union>();
    test_is_aggregate<NonEmptyUnion>();
    test_is_aggregate<AbstractTemplate<double>>();
}
