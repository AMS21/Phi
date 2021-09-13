#include <catch2/catch_test_macros.hpp>

#include "Phi/Core/Nullptr.hpp"
#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/TypeTraits/add_cv.hpp>

template <typename T, typename U>
void test_add_cv_imp()
{
    CHECK_SAME_TYPE(const volatile U, typename phi::add_cv<T>::type);
    CHECK_SAME_TYPE(const volatile U, phi::add_cv_t<T>);
}

template <typename T>
void test_add_cv()
{
    test_add_cv_imp<T, const volatile T>();
    test_add_cv_imp<const T, const volatile T>();
    test_add_cv_imp<volatile T, const volatile T>();
    test_add_cv_imp<const volatile T, const volatile T>();
}

TEST_CASE("add_cv")
{
    test_add_cv<phi::nullptr_t>();
    test_add_cv<void>();
    test_add_cv<int>();
    test_add_cv<int[3]>();
    test_add_cv<int[]>();
    test_add_cv<float>();
    test_add_cv<int&>();
    test_add_cv<const int&>();
    test_add_cv<volatile int&>();
    test_add_cv<const volatile int&>();
    test_add_cv<int*>();
    test_add_cv<const int*>();
    test_add_cv<volatile int*>();
    test_add_cv<const volatile int*>();
    test_add_cv<Class>();
    test_add_cv<Struct>();
    test_add_cv<Empty>();
    test_add_cv<NotEmpty>();
    test_add_cv<Union>();
    test_add_cv<bit_zero>();
    test_add_cv<Abstract>();
    test_add_cv<Enum>();
    test_add_cv<EnumSigned>();
    test_add_cv<EnumUnsigned>();
    test_add_cv<EnumClass>();
    test_add_cv<incomplete_type>();
    test_add_cv<FunctionPtr>();
    test_add_cv<MemberObjectPtr>();
    test_add_cv<MemberFunctionPtr>();
}
