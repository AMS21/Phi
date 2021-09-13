#include <catch2/catch_test_macros.hpp>

#include "Phi/Core/Nullptr.hpp"
#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/TypeTraits/add_pointer.hpp>

template <class T, class U>
void test_add_pointer()
{
    CHECK_SAME_TYPE(U, typename phi::add_pointer<T>::type);
    CHECK_SAME_TYPE(const U, const typename phi::add_pointer<T>::type);
    CHECK_SAME_TYPE(volatile U, volatile typename phi::add_pointer<T>::type);
    CHECK_SAME_TYPE(const volatile U, const volatile typename phi::add_pointer<T>::type);

    CHECK_SAME_TYPE(U, phi::add_pointer_t<T>);
    CHECK_SAME_TYPE(const U, const phi::add_pointer_t<T>);
    CHECK_SAME_TYPE(volatile U, volatile phi::add_pointer_t<T>);
    CHECK_SAME_TYPE(const volatile U, const volatile phi::add_pointer_t<T>);
}

template <class F>
void test_function0()
{
    CHECK_SAME_TYPE(F*, typename phi::add_pointer<F>::type);
    CHECK_SAME_TYPE(F*, phi::add_pointer_t<F>);
}

template <class F>
void test_function1()
{
    CHECK_SAME_TYPE(F, typename phi::add_pointer<F>::type);
    CHECK_SAME_TYPE(F, phi::add_pointer_t<F>);
}

struct Foo
{};

TEST_CASE("add_pointer")
{
    test_add_pointer<phi::nullptr_t, phi::nullptr_t*>();
    test_add_pointer<void, void*>();
    test_add_pointer<int, int*>();
    test_add_pointer<float, float*>();
    test_add_pointer<int[], int(*)[]>();
    test_add_pointer<int[3], int(*)[3]>();
    test_add_pointer<int&, int*>();
    test_add_pointer<const int&, const int*>();
    test_add_pointer<volatile int&, volatile int*>();
    test_add_pointer<const volatile int&, const volatile int*>();
    test_add_pointer<int*, int**>();
    test_add_pointer<const int*, const int**>();
    test_add_pointer<volatile int*, volatile int**>();
    test_add_pointer<const volatile int*, const volatile int**>();
    test_add_pointer<Foo, Foo*>();
    test_add_pointer<Class, Class*>();
    test_add_pointer<Struct, Struct*>();
    test_add_pointer<Empty, Empty*>();
    test_add_pointer<NotEmpty, NotEmpty*>();
    test_add_pointer<Union, Union*>();
    test_add_pointer<bit_zero, bit_zero*>();
    test_add_pointer<Abstract, Abstract*>();
    test_add_pointer<Enum, Enum*>();
    test_add_pointer<EnumSigned, EnumSigned*>();
    test_add_pointer<EnumUnsigned, EnumUnsigned*>();
    test_add_pointer<EnumClass, EnumClass*>();
    test_add_pointer<incomplete_type, incomplete_type*>();
    test_add_pointer<MemberObjectPtr, MemberObjectPtr*>();

    //  LWG 2101 specifically talks about add_pointer and functions.
    //  The term of art is "a referenceable type", which a cv- or ref-qualified function is not.
    test_function0<FunctionPtr>();
    test_function0<void()>();
    test_function1<void() const>();
    test_function1<void()&>();
    test_function1<void() &&>();
    test_function1<void() const&>();
    test_function1<void() const&&>();

    test_function0<void() noexcept>();
    test_function1<void() const noexcept>();
    test_function1<void()& noexcept>();
    test_function1<void()&& noexcept>();
    test_function1<void() const& noexcept>();
    test_function1<void() const&& noexcept>();

    //  But a cv- or ref-qualified member function *is* "a referenceable type"
    test_function0<MemberFunctionPtr>();
    test_function0<void (Foo::*)()>();
    test_function0<void (Foo::*)() const>();
    test_function0<void (Foo::*)()&>();
    test_function0<void (Foo::*)() &&>();
    test_function0<void (Foo::*)() const&>();
    test_function0<void (Foo::*)() const&&>();

    test_function0<void (Foo::*)() noexcept>();
    test_function0<void (Foo::*)() const noexcept>();
    test_function0<void (Foo::*)()& noexcept>();
    test_function0<void (Foo::*)()&& noexcept>();
    test_function0<void (Foo::*)() const& noexcept>();
    test_function0<void (Foo::*)() const&& noexcept>();
}
