#include <catch2/catch_test_macros.hpp>

#include "Phi/Core/Nullptr.hpp"
#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/TypeTraits/add_const.hpp>

template <typename T, typename U>
void test_add_const_imp()
{
    CHECK_SAME_TYPE(const U, typename phi::add_const<T>::type);
    CHECK_SAME_TYPE(const U, phi::add_const_t<T>);
}

template <typename T>
void test_add_const()
{
    test_add_const_imp<T, const T>();
    test_add_const_imp<const T, const T>();
    test_add_const_imp<volatile T, volatile const T>();
    test_add_const_imp<const volatile T, const volatile T>();
}

TEST_CASE("add_const")
{
    test_add_const<phi::nullptr_t>();
    test_add_const<void>();
    test_add_const<bool>();
    test_add_const<char>();
    test_add_const<signed char>();
    test_add_const<unsigned char>();
    test_add_const<short>();
    test_add_const<unsigned short>();
    test_add_const<int>();
    test_add_const<unsigned int>();
    test_add_const<long>();
    test_add_const<unsigned long>();
    test_add_const<long long>();
    test_add_const<unsigned long long>();
    test_add_const<float>();
    test_add_const<double>();
    test_add_const<long double>();
    test_add_const<int[3]>();
    test_add_const<int[]>();
    test_add_const<int&>();
    test_add_const<const int&>();
    test_add_const<volatile int&>();
    test_add_const<const volatile int&>();
    test_add_const<int&&>();
    test_add_const<int*>();
    test_add_const<const int*>();
    test_add_const<volatile int*>();
    test_add_const<const volatile int*>();
    test_add_const<int**>();
    test_add_const<Class>();
    test_add_const<Struct>();
    test_add_const<Empty>();
    test_add_const<NotEmpty>();
    test_add_const<Union>();
    test_add_const<NonEmptyUnion>();
    test_add_const<bit_zero>();
    test_add_const<bit_one>();
    test_add_const<AbstractTemplate<int>>();
    test_add_const<AbstractTemplate<double>>();
    test_add_const<AbstractTemplate<Class>>();
    test_add_const<AbstractTemplate<incomplete_type>>();
    test_add_const<Enum>();
    test_add_const<EnumSigned>();
    test_add_const<EnumUnsigned>();
    test_add_const<EnumClass>();
    test_add_const<incomplete_type>();
    test_add_const<Function>();
    test_add_const<FunctionPtr>();
    test_add_const<MemberObjectPtr>();
    test_add_const<MemberFunctionPtr>();
}
