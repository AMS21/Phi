#include <catch2/catch.hpp>

#include "Phi/Core/Nullptr.hpp"
#include "TestTypes.hpp"
#include <Phi/TypeTraits/has_virtual_destructor.hpp>

template <class T>
void test_has_virtual_destructor()
{
    STATIC_REQUIRE(phi::has_virtual_destructor<T>::value);
    STATIC_REQUIRE(phi::has_virtual_destructor<const T>::value);
    STATIC_REQUIRE(phi::has_virtual_destructor<volatile T>::value);
    STATIC_REQUIRE(phi::has_virtual_destructor<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::has_virtual_destructor_v<T>);
    STATIC_REQUIRE(phi::has_virtual_destructor_v<const T>);
    STATIC_REQUIRE(phi::has_virtual_destructor_v<volatile T>);
    STATIC_REQUIRE(phi::has_virtual_destructor_v<const volatile T>);
#endif
}

template <class T>
void test_has_not_virtual_destructor()
{
    STATIC_REQUIRE_FALSE(phi::has_virtual_destructor<T>::value);
    STATIC_REQUIRE_FALSE(phi::has_virtual_destructor<const T>::value);
    STATIC_REQUIRE_FALSE(phi::has_virtual_destructor<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::has_virtual_destructor<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::has_virtual_destructor_v<T>);
    STATIC_REQUIRE_FALSE(phi::has_virtual_destructor_v<const T>);
    STATIC_REQUIRE_FALSE(phi::has_virtual_destructor_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::has_virtual_destructor_v<const volatile T>);
#endif
}

struct A
{
    ~A();
};

TEST_CASE("has_virtual_destructor")
{
    test_has_not_virtual_destructor<phi::nullptr_t>();
    test_has_not_virtual_destructor<void>();
    test_has_not_virtual_destructor<A>();
    test_has_not_virtual_destructor<int&>();
    test_has_not_virtual_destructor<int&&>();
    test_has_not_virtual_destructor<Union>();
    test_has_not_virtual_destructor<Empty>();
    test_has_not_virtual_destructor<int>();
    test_has_not_virtual_destructor<float>();
    test_has_not_virtual_destructor<double>();
    test_has_not_virtual_destructor<int*>();
    test_has_not_virtual_destructor<const int*>();
    test_has_not_virtual_destructor<volatile int*>();
    test_has_not_virtual_destructor<const volatile int*>();
    test_has_not_virtual_destructor<int**>();
    test_has_not_virtual_destructor<char[3]>();
    test_has_not_virtual_destructor<char[]>();
    test_has_not_virtual_destructor<bit_zero>();
    test_has_not_virtual_destructor<Class>();
    test_has_not_virtual_destructor<Struct>();
    test_has_not_virtual_destructor<NonEmptyUnion>();
    test_has_not_virtual_destructor<Enum>();
    test_has_not_virtual_destructor<EnumSigned>();
    test_has_not_virtual_destructor<EnumUnsigned>();
    test_has_not_virtual_destructor<EnumClass>();
    test_has_not_virtual_destructor<FunctionPtr>();
    test_has_not_virtual_destructor<MemberObjectPtr>();
    test_has_not_virtual_destructor<MemberFunctionPtr>();

    test_has_virtual_destructor<Abstract>();
    test_has_virtual_destructor<NotEmpty>();
}
