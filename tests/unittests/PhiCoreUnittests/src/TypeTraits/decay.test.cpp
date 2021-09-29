#include <catch2/catch.hpp>

#include "Phi/Core/Nullptr.hpp"
#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/TypeTraits/decay.hpp>

template <typename T, typename U>
void test_decay()
{
    CHECK_SAME_TYPE(U, typename phi::decay<T>::type);
    CHECK_SAME_TYPE(U, phi::decay_t<T>);
}

class A
{};

TEST_CASE("decay")
{
    test_decay<phi::nullptr_t, phi::nullptr_t>();
    test_decay<void, void>();
    test_decay<int, int>();
    test_decay<float, float>();
    test_decay<A, A>();
    test_decay<Class, Class>();
    test_decay<Struct, Struct>();
    test_decay<Empty, Empty>();
    test_decay<NotEmpty, NotEmpty>();
    test_decay<Union, Union>();
    test_decay<bit_zero, bit_zero>();
    test_decay<Abstract, Abstract>();
    test_decay<Enum, Enum>();
    test_decay<EnumSigned, EnumSigned>();
    test_decay<EnumUnsigned, EnumUnsigned>();
    test_decay<EnumClass, EnumClass>();
    test_decay<incomplete_type, incomplete_type>();

    test_decay<const int, int>();
    test_decay<volatile int, int>();
    test_decay<const volatile int, int>();

    test_decay<int*, int*>();
    test_decay<const int*, const int*>();
    test_decay<volatile int*, volatile int*>();
    test_decay<const volatile int*, const volatile int*>();
    test_decay<int[], int*>();
    test_decay<const int[], const int*>();
    test_decay<volatile int[], volatile int*>();
    test_decay<const volatile int[], const volatile int*>();
    test_decay<int[3], int*>();
    test_decay<const int[3], const int*>();
    test_decay<volatile int[3], volatile int*>();
    test_decay<const volatile int[3], const volatile int*>();

    test_decay<int**, int**>();
    test_decay<const int**, const int**>();
    test_decay<volatile int**, volatile int**>();
    test_decay<const volatile int**, const volatile int**>();
    test_decay<int[3][2], int(*)[2]>();
    test_decay<const int[3][2], int const(*)[2]>();
    test_decay<volatile int[3][2], volatile int(*)[2]>();
    test_decay<const volatile int[3][2], const volatile int(*)[2]>();

    test_decay<FunctionPtr, FunctionPtr>();
    test_decay<MemberObjectPtr, MemberObjectPtr>();
    test_decay<MemberFunctionPtr, MemberFunctionPtr>();

    test_decay<void(), void (*)()>();
    test_decay<int(int) const, int(int) const>();
    test_decay<int(int) volatile, int(int) volatile>();
    test_decay<int(int)&, int(int)&>();
    test_decay<int(int)&&, int(int) &&>();
    test_decay<void() noexcept, void (*)() noexcept>();
    test_decay<int(int) const noexcept, int(int) const noexcept>();
    test_decay<int(int) volatile noexcept, int(int) volatile noexcept>();
    test_decay<int(int)& noexcept, int(int)& noexcept>();
    test_decay<int(int)&& noexcept, int(int)&& noexcept>();

    test_decay<void (Class::*)(), void (Class::*)()>();
    test_decay<void (Class::*)() const, void (Class::*)() const>();
    test_decay<void (Class::*)()&, void (Class::*)()&>();
    test_decay<void (Class::*)()&&, void (Class::*)() &&>();
    test_decay<void (Class::*)() const&, void (Class::*)() const&>();
    test_decay<void (Class::*)() const&&, void (Class::*)() const&&>();

    test_decay<void (Class::*)() noexcept, void (Class::*)() noexcept>();
    test_decay<void (Class::*)() const noexcept, void (Class::*)() const noexcept>();
    test_decay<void (Class::*)()& noexcept, void (Class::*)()& noexcept>();
    test_decay<void (Class::*)()&& noexcept, void (Class::*)()&& noexcept>();
    test_decay<void (Class::*)() const& noexcept, void (Class::*)() const& noexcept>();
    test_decay<void (Class::*)() const&& noexcept, void (Class::*)() const&& noexcept>();
}
