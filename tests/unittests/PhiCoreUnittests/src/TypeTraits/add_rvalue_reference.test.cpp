#include <catch2/catch.hpp>

#include "Phi/Core/Nullptr.hpp"
#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/TypeTraits/add_rvalue_reference.hpp>

template <class T, class U>
void test_add_rvalue_reference()
{
    CHECK_SAME_TYPE(U, typename phi::add_rvalue_reference<T>::type);
    CHECK_SAME_TYPE(const U, const typename phi::add_rvalue_reference<T>::type);
    CHECK_SAME_TYPE(volatile U, volatile typename phi::add_rvalue_reference<T>::type);
    CHECK_SAME_TYPE(const volatile U, const volatile typename phi::add_rvalue_reference<T>::type);

    CHECK_SAME_TYPE(U, phi::add_rvalue_reference_t<T>);
    CHECK_SAME_TYPE(const U, const phi::add_rvalue_reference_t<T>);
    CHECK_SAME_TYPE(volatile U, volatile phi::add_rvalue_reference_t<T>);
    CHECK_SAME_TYPE(const volatile U, const volatile phi::add_rvalue_reference_t<T>);
}

template <class F>
void test_function0()
{
    CHECK_SAME_TYPE(F&&, typename phi::add_rvalue_reference<F>::type);
    CHECK_SAME_TYPE(F&&, phi::add_rvalue_reference_t<F>);
}

template <class F>
void test_function1()
{
    CHECK_SAME_TYPE(F, typename phi::add_rvalue_reference<F>::type);
    CHECK_SAME_TYPE(F, phi::add_rvalue_reference_t<F>);
}

struct Foo
{};

struct A; // incomplete

TEST_CASE("add_rvalue_reference")
{
    test_add_rvalue_reference<phi::nullptr_t, phi::nullptr_t&&>();
    test_add_rvalue_reference<void, void>();
    test_add_rvalue_reference<int, int&&>();
    test_add_rvalue_reference<int[], int(&&)[]>();
    test_add_rvalue_reference<int[3], int(&&)[3]>();
    test_add_rvalue_reference<int&&, int&&>();
    test_add_rvalue_reference<int&, int&>();
    test_add_rvalue_reference<const int&, const int&>();
    test_add_rvalue_reference<volatile int&, volatile int&>();
    test_add_rvalue_reference<const volatile int&, const volatile int&>();
    test_add_rvalue_reference<int*, int*&&>();
    test_add_rvalue_reference<const int*, const int*&&>();
    test_add_rvalue_reference<double, double&&>();
    test_add_rvalue_reference<Foo, Foo&&>();
    test_add_rvalue_reference<Struct, Struct&&>();
    test_add_rvalue_reference<Class, Class&&>();
    test_add_rvalue_reference<A, A&&>();
    test_add_rvalue_reference<incomplete_type, incomplete_type&&>();
    test_add_rvalue_reference<Empty, Empty&&>();
    test_add_rvalue_reference<NotEmpty, NotEmpty&&>();
    test_add_rvalue_reference<Union, Union&&>();
    test_add_rvalue_reference<bit_zero, bit_zero&&>();
    test_add_rvalue_reference<Abstract, Abstract&&>();
    test_add_rvalue_reference<Enum, Enum&&>();
    test_add_rvalue_reference<EnumSigned, EnumSigned&&>();
    test_add_rvalue_reference<EnumUnsigned, EnumUnsigned&&>();
    test_add_rvalue_reference<EnumClass, EnumClass&&>();
    test_add_rvalue_reference<MemberObjectPtr, MemberObjectPtr&&>();

    //  LWG 2101 specifically talks about add_rvalue_reference and functions.
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
