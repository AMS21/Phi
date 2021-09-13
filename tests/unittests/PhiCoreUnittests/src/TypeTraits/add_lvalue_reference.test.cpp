#include <catch2/catch_test_macros.hpp>

#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/TypeTraits/add_lvalue_reference.hpp>

template <class T, class U>
void test_add_lvalue_reference()
{
    CHECK_SAME_TYPE(U, typename phi::add_lvalue_reference<T>::type);
    CHECK_SAME_TYPE(const U, const typename phi::add_lvalue_reference<T>::type);
    CHECK_SAME_TYPE(volatile U, volatile typename phi::add_lvalue_reference<T>::type);
    CHECK_SAME_TYPE(const volatile U, const volatile typename phi::add_lvalue_reference<T>::type);

    CHECK_SAME_TYPE(U, phi::add_lvalue_reference_t<T>);
    CHECK_SAME_TYPE(const U, const phi::add_lvalue_reference_t<T>);
    CHECK_SAME_TYPE(volatile U, volatile phi::add_lvalue_reference_t<T>);
    CHECK_SAME_TYPE(const volatile U, const volatile phi::add_lvalue_reference_t<T>);
}

template <class F>
void test_function0()
{
    CHECK_SAME_TYPE(F&, typename phi::add_lvalue_reference<F>::type);
    CHECK_SAME_TYPE(F&, phi::add_lvalue_reference_t<F>);
}

template <class F>
void test_function1()
{
    CHECK_SAME_TYPE(F, typename phi::add_lvalue_reference<F>::type);
    CHECK_SAME_TYPE(F, phi::add_lvalue_reference_t<F>);
}

struct A; // incomplete

struct Foo
{};

TEST_CASE("add_lvalue_reference")
{
    test_add_lvalue_reference<void, void>();
    test_add_lvalue_reference<int, int&>();
    test_add_lvalue_reference<int[], int(&)[]>();
    test_add_lvalue_reference<int[3], int(&)[3]>();
    test_add_lvalue_reference<int&, int&>();
    test_add_lvalue_reference<int&&, int&>();
    test_add_lvalue_reference<const int&, const int&>();
    test_add_lvalue_reference<volatile int&, volatile int&>();
    test_add_lvalue_reference<const volatile int&, const volatile int&>();
    test_add_lvalue_reference<int*, int*&>();
    test_add_lvalue_reference<const int*, const int*&>();
    test_add_lvalue_reference<volatile int*, volatile int*&>();
    test_add_lvalue_reference<const volatile int*, const volatile int*&>();
    test_add_lvalue_reference<double, double&>();
    test_add_lvalue_reference<Foo, Foo&>();
    test_add_lvalue_reference<Class, Class&>();
    test_add_lvalue_reference<Struct, Struct&>();
    test_add_lvalue_reference<A, A&>();
    test_add_lvalue_reference<incomplete_type, incomplete_type&>();
    test_add_lvalue_reference<Empty, Empty&>();
    test_add_lvalue_reference<NotEmpty, NotEmpty&>();
    test_add_lvalue_reference<Union, Union&>();
    test_add_lvalue_reference<bit_zero, bit_zero&>();
    test_add_lvalue_reference<Abstract, Abstract&>();
    test_add_lvalue_reference<Enum, Enum&>();
    test_add_lvalue_reference<EnumSigned, EnumSigned&>();
    test_add_lvalue_reference<EnumUnsigned, EnumUnsigned&>();
    test_add_lvalue_reference<EnumClass, EnumClass&>();
    test_add_lvalue_reference<MemberFunctionPtr, MemberFunctionPtr&>();

    //  LWG 2101 specifically talks about add_lvalue_reference and functions.
    //  The term of art is "a referenceable type", which a cv- or ref-qualified function is not.
    test_function0<FunctionPtr>();
    test_function0<void()>();
    test_function1<void() const>();
    test_function1<void()&>();
    test_function1<void() &&>();
    test_function1<void() const&>();
    test_function1<void() const&&>();

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
