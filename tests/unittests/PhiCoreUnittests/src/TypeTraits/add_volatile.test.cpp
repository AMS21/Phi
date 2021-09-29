#include <catch2/catch.hpp>

#include "Phi/Core/Nullptr.hpp"
#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/TypeTraits/add_volatile.hpp>

template <class T, class U>
void test_add_volatile_imp()
{
    CHECK_SAME_TYPE(volatile U, typename phi::add_volatile<T>::type);
    CHECK_SAME_TYPE(volatile U, phi::add_volatile_t<T>);
}

template <class T>
void test_add_volatile()
{
    test_add_volatile_imp<T, volatile T>();
    test_add_volatile_imp<const T, const volatile T>();
    test_add_volatile_imp<volatile T, volatile T>();
    test_add_volatile_imp<const volatile T, const volatile T>();
}

TEST_CASE("add_volatile")
{
    test_add_volatile<phi::nullptr_t>();
    test_add_volatile<void>();
    test_add_volatile<int>();
    test_add_volatile<float>();
    test_add_volatile<int[]>();
    test_add_volatile<int[3]>();
    test_add_volatile<int&>();
    test_add_volatile<const int&>();
    test_add_volatile<volatile int&>();
    test_add_volatile<const volatile int&>();
    test_add_volatile<int*>();
    test_add_volatile<const int*>();
    test_add_volatile<volatile int*>();
    test_add_volatile<const volatile int*>();
    test_add_volatile<Class>();
    test_add_volatile<Struct>();
    test_add_volatile<Empty>();
    test_add_volatile<NotEmpty>();
    test_add_volatile<Union>();
    test_add_volatile<bit_zero>();
    test_add_volatile<Abstract>();
    test_add_volatile<Enum>();
    test_add_volatile<EnumSigned>();
    test_add_volatile<EnumUnsigned>();
    test_add_volatile<EnumClass>();
    test_add_volatile<incomplete_type>();
    test_add_volatile<FunctionPtr>();
    test_add_volatile<MemberObjectPtr>();
    test_add_volatile<MemberFunctionPtr>();
}
