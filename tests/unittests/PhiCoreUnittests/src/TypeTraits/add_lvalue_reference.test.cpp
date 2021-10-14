#include <catch2/catch.hpp>

#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/add_lvalue_reference.hpp>

template <typename T, typename U = T>
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

template <typename F>
void test_function0()
{
    CHECK_SAME_TYPE(F&, typename phi::add_lvalue_reference<F>::type);
    CHECK_SAME_TYPE(F&, phi::add_lvalue_reference_t<F>);
}

template <typename F>
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
    test_add_lvalue_reference<A, A&>();
    test_add_lvalue_reference<Foo, Foo&>();

    test_add_lvalue_reference<void, void>();
    test_add_lvalue_reference<phi::nullptr_t, phi::nullptr_t&>();
    test_add_lvalue_reference<bool, bool&>();
    test_add_lvalue_reference<char, char&>();
    test_add_lvalue_reference<signed char, signed char&>();
    test_add_lvalue_reference<unsigned char, unsigned char&>();
    test_add_lvalue_reference<short, short&>();
    test_add_lvalue_reference<unsigned short, unsigned short&>();
    test_add_lvalue_reference<int, int&>();
    test_add_lvalue_reference<unsigned int, unsigned int&>();
    test_add_lvalue_reference<long, long&>();
    test_add_lvalue_reference<unsigned long, unsigned long&>();
    test_add_lvalue_reference<long long, long long&>();
    test_add_lvalue_reference<unsigned long long, unsigned long long&>();
    test_add_lvalue_reference<float, float&>();
    test_add_lvalue_reference<double, double&>();
    test_add_lvalue_reference<long double, long double&>();
    test_add_lvalue_reference<char8_t, char8_t&>();
    test_add_lvalue_reference<char16_t, char16_t&>();
    test_add_lvalue_reference<char32_t, char32_t&>();
    test_add_lvalue_reference<wchar_t, wchar_t&>();

    test_add_lvalue_reference<phi::Boolean, phi::Boolean&>();
    test_add_lvalue_reference<phi::Integer<signed char>, phi::Integer<signed char>&>();
    test_add_lvalue_reference<phi::Integer<unsigned char>, phi::Integer<unsigned char>&>();
    test_add_lvalue_reference<phi::Integer<short>, phi::Integer<short>&>();
    test_add_lvalue_reference<phi::Integer<unsigned short>, phi::Integer<unsigned short>&>();
    test_add_lvalue_reference<phi::Integer<int>, phi::Integer<int>&>();
    test_add_lvalue_reference<phi::Integer<unsigned int>, phi::Integer<unsigned int>&>();
    test_add_lvalue_reference<phi::Integer<long>, phi::Integer<long>&>();
    test_add_lvalue_reference<phi::Integer<unsigned long>, phi::Integer<unsigned long>&>();
    test_add_lvalue_reference<phi::Integer<long long>, phi::Integer<long long>&>();
    test_add_lvalue_reference<phi::Integer<unsigned long long>,
                              phi::Integer<unsigned long long>&>();
    test_add_lvalue_reference<phi::FloatingPoint<float>, phi::FloatingPoint<float>&>();
    test_add_lvalue_reference<phi::FloatingPoint<double>, phi::FloatingPoint<double>&>();
    test_add_lvalue_reference<phi::FloatingPoint<long double>, phi::FloatingPoint<long double>&>();

    test_add_lvalue_reference<std::vector<int>, std::vector<int>&>();
    test_add_lvalue_reference<phi::ScopePtr<int>, phi::ScopePtr<int>&>();

    test_add_lvalue_reference<int&, int&>();
    test_add_lvalue_reference<const int&, const int&>();
    test_add_lvalue_reference<volatile int&, volatile int&>();
    test_add_lvalue_reference<const volatile int&, const volatile int&>();
    test_add_lvalue_reference<int&&, int&>();
    test_add_lvalue_reference<const int&&, const int&>();
    test_add_lvalue_reference<volatile int&&, volatile int&>();
    test_add_lvalue_reference<const volatile int&&, const volatile int&>();
    test_add_lvalue_reference<int*, int*&>();
    test_add_lvalue_reference<const int*, const int*&>();
    test_add_lvalue_reference<volatile int*, volatile int*&>();
    test_add_lvalue_reference<const volatile int*, const volatile int*&>();
    test_add_lvalue_reference<int**, int**&>();
    test_add_lvalue_reference<const int**, const int**&>();
    test_add_lvalue_reference<volatile int**, volatile int**&>();
    test_add_lvalue_reference<const volatile int**, const volatile int**&>();
    test_add_lvalue_reference<int*&, int*&>();
    test_add_lvalue_reference<const int*&, const int*&>();
    test_add_lvalue_reference<volatile int*&, volatile int*&>();
    test_add_lvalue_reference<const volatile int*&, const volatile int*&>();
    test_add_lvalue_reference<int*&&, int*&>();
    test_add_lvalue_reference<const int*&&, const int*&>();
    test_add_lvalue_reference<volatile int*&&, volatile int*&>();
    test_add_lvalue_reference<const volatile int*&&, const volatile int*&>();
    test_add_lvalue_reference<void*, void*&>();
    test_add_lvalue_reference<char[3], char(&)[3]>();
    test_add_lvalue_reference<char[], char(&)[]>();
    test_add_lvalue_reference<char* [3], char*(&)[3]>();
    test_add_lvalue_reference<char*[], char*(&)[]>();
    test_add_lvalue_reference<int(*)[3], int(*&)[3]>();
    test_add_lvalue_reference<int(*)[], int(*&)[]>();
    test_add_lvalue_reference<int(&)[3], int(&)[3]>();
    test_add_lvalue_reference<int(&)[], int(&)[]>();
    test_add_lvalue_reference<int(&&)[3], int(&)[3]>();
    test_add_lvalue_reference<int(&&)[], int(&)[]>();
    test_add_lvalue_reference<char[3][2], char(&)[3][2]>();
    test_add_lvalue_reference<char[][2], char(&)[][2]>();
    test_add_lvalue_reference<char* [3][2], char*(&)[3][2]>();
    test_add_lvalue_reference<char*[][2], char*(&)[][2]>();
    test_add_lvalue_reference<int(*)[3][2], int(*&)[3][2]>();
    test_add_lvalue_reference<int(*)[][2], int(*&)[][2]>();
    test_add_lvalue_reference<int(&)[3][2], int(&)[3][2]>();
    test_add_lvalue_reference<int(&)[][2], int(&)[][2]>();
    test_add_lvalue_reference<int(&&)[3][2], int(&)[3][2]>();
    test_add_lvalue_reference<int(&&)[][2], int(&)[][2]>();
    test_add_lvalue_reference<Class, Class&>();
    test_add_lvalue_reference<Class[], Class(&)[]>();
    test_add_lvalue_reference<Class[2], Class(&)[2]>();
    test_add_lvalue_reference<Struct, Struct&>();
    test_add_lvalue_reference<TemplateClass<void>, TemplateClass<void>&>();
    test_add_lvalue_reference<TemplateClass<int>, TemplateClass<int>&>();
    test_add_lvalue_reference<TemplateClass<Class>, TemplateClass<Class>&>();
    test_add_lvalue_reference<TemplateClass<incomplete_type>, TemplateClass<incomplete_type>&>();
    test_add_lvalue_reference<TemplateStruct<void>, TemplateStruct<void>&>();
    test_add_lvalue_reference<TemplateStruct<int>, TemplateStruct<int>&>();
    test_add_lvalue_reference<TemplateStruct<Class>, TemplateStruct<Class>&>();
    test_add_lvalue_reference<TemplateStruct<incomplete_type>, TemplateStruct<incomplete_type>&>();
    test_add_lvalue_reference<VariadicTemplateClass<>, VariadicTemplateClass<>&>();
    test_add_lvalue_reference<VariadicTemplateClass<void>, VariadicTemplateClass<void>&>();
    test_add_lvalue_reference<VariadicTemplateClass<int>, VariadicTemplateClass<int>&>();
    test_add_lvalue_reference<VariadicTemplateClass<Class>, VariadicTemplateClass<Class>&>();
    test_add_lvalue_reference<VariadicTemplateClass<incomplete_type>,
                              VariadicTemplateClass<incomplete_type>&>();
    test_add_lvalue_reference<VariadicTemplateClass<int, void, Class, volatile char[]>,
                              VariadicTemplateClass<int, void, Class, volatile char[]>&>();
    test_add_lvalue_reference<VariadicTemplateStruct<>, VariadicTemplateStruct<>&>();
    test_add_lvalue_reference<VariadicTemplateStruct<void>, VariadicTemplateStruct<void>&>();
    test_add_lvalue_reference<VariadicTemplateStruct<int>, VariadicTemplateStruct<int>&>();
    test_add_lvalue_reference<VariadicTemplateStruct<Class>, VariadicTemplateStruct<Class>&>();
    test_add_lvalue_reference<VariadicTemplateStruct<incomplete_type>,
                              VariadicTemplateStruct<incomplete_type>&>();
    test_add_lvalue_reference<VariadicTemplateStruct<int, void, Class, volatile char[]>,
                              VariadicTemplateStruct<int, void, Class, volatile char[]>&>();
    test_add_lvalue_reference<PublicDerviedFromTemplate<Base>, PublicDerviedFromTemplate<Base>&>();
    test_add_lvalue_reference<PublicDerviedFromTemplate<Derived>,
                              PublicDerviedFromTemplate<Derived>&>();
    test_add_lvalue_reference<PublicDerviedFromTemplate<Class>,
                              PublicDerviedFromTemplate<Class>&>();
    test_add_lvalue_reference<PrivateDerviedFromTemplate<Base>,
                              PrivateDerviedFromTemplate<Base>&>();
    test_add_lvalue_reference<PrivateDerviedFromTemplate<Derived>,
                              PrivateDerviedFromTemplate<Derived>&>();
    test_add_lvalue_reference<PrivateDerviedFromTemplate<Class>,
                              PrivateDerviedFromTemplate<Class>&>();
    test_add_lvalue_reference<ProtectedDerviedFromTemplate<Base>,
                              ProtectedDerviedFromTemplate<Base>&>();
    test_add_lvalue_reference<ProtectedDerviedFromTemplate<Derived>,
                              ProtectedDerviedFromTemplate<Derived>&>();
    test_add_lvalue_reference<ProtectedDerviedFromTemplate<Class>,
                              ProtectedDerviedFromTemplate<Class>&>();
    test_add_lvalue_reference<Union, Union&>();
    test_add_lvalue_reference<NonEmptyUnion, NonEmptyUnion&>();
    test_add_lvalue_reference<Empty, Empty&>();
    test_add_lvalue_reference<NotEmpty, NotEmpty&>();
    test_add_lvalue_reference<bit_zero, bit_zero&>();
    test_add_lvalue_reference<bit_one, bit_one&>();
    test_add_lvalue_reference<Base, Base&>();
    test_add_lvalue_reference<Derived, Derived&>();
    test_add_lvalue_reference<Abstract, Abstract&>();
    test_add_lvalue_reference<AbstractTemplate<int>, AbstractTemplate<int>&>();
    test_add_lvalue_reference<AbstractTemplate<double>, AbstractTemplate<double>&>();
    test_add_lvalue_reference<AbstractTemplate<Class>, AbstractTemplate<Class>&>();
    test_add_lvalue_reference<AbstractTemplate<incomplete_type>,
                              AbstractTemplate<incomplete_type>&>();
    test_add_lvalue_reference<Final, Final&>();
    test_add_lvalue_reference<Enum, Enum&>();
    test_add_lvalue_reference<EnumSigned, EnumSigned&>();
    test_add_lvalue_reference<EnumUnsigned, EnumUnsigned&>();
    test_add_lvalue_reference<EnumClass, EnumClass&>();
    test_add_lvalue_reference<EnumStruct, EnumStruct&>();
    test_add_lvalue_reference<MemberObjectPtr, MemberObjectPtr&>();
    test_add_lvalue_reference<incomplete_type, incomplete_type&>();
    test_add_lvalue_reference<IncompleteTemplate<void>, IncompleteTemplate<void>&>();
    test_add_lvalue_reference<IncompleteTemplate<int>, IncompleteTemplate<int>&>();
    test_add_lvalue_reference<IncompleteTemplate<Class>, IncompleteTemplate<Class>&>();
    test_add_lvalue_reference<IncompleteTemplate<incomplete_type>,
                              IncompleteTemplate<incomplete_type>&>();
    test_add_lvalue_reference<IncompleteVariadicTemplate<>, IncompleteVariadicTemplate<>&>();
    test_add_lvalue_reference<IncompleteVariadicTemplate<void>,
                              IncompleteVariadicTemplate<void>&>();
    test_add_lvalue_reference<IncompleteVariadicTemplate<int>, IncompleteVariadicTemplate<int>&>();
    test_add_lvalue_reference<IncompleteVariadicTemplate<Class>,
                              IncompleteVariadicTemplate<Class>&>();
    test_add_lvalue_reference<IncompleteVariadicTemplate<incomplete_type>,
                              IncompleteVariadicTemplate<incomplete_type>&>();
    test_add_lvalue_reference<IncompleteVariadicTemplate<int, void, Class, volatile char[]>,
                              IncompleteVariadicTemplate<int, void, Class, volatile char[]>&>();
    test_add_lvalue_reference<int Class::*, int Class::*&>();
    test_add_lvalue_reference<float Class::*, float Class::*&>();
    test_add_lvalue_reference<void * Class::*, void * Class::*&>();
    test_add_lvalue_reference<int * Class::*, int * Class::*&>();
    test_add_lvalue_reference<int Class::*&, int Class::*&>();
    test_add_lvalue_reference<float Class::*&, float Class::*&>();
    test_add_lvalue_reference<void * Class::*&, void * Class::*&>();
    test_add_lvalue_reference<int * Class::*&, int * Class::*&>();
    test_add_lvalue_reference<int Class::*&&, int Class::*&>();
    test_add_lvalue_reference<float Class::*&&, float Class::*&>();
    test_add_lvalue_reference<void * Class::*&&, void * Class::*&>();
    test_add_lvalue_reference<int * Class::*&&, int * Class::*&>();
    test_add_lvalue_reference<int Class::*const, int Class::*const&>();
    test_add_lvalue_reference<float Class::*const, float Class::*const&>();
    test_add_lvalue_reference<void * Class::*const, void * Class::*const&>();
    test_add_lvalue_reference<int Class::*const&, int Class::*const&>();
    test_add_lvalue_reference<float Class::*const&, float Class::*const&>();
    test_add_lvalue_reference<void * Class::*const&, void * Class::*const&>();
    test_add_lvalue_reference<int Class::*const&&, int Class::*const&>();
    test_add_lvalue_reference<float Class::*const&&, float Class::*const&>();
    test_add_lvalue_reference<void * Class::*const&&, void * Class::*const&>();
    test_add_lvalue_reference<int Class::*volatile, int Class::*volatile&>();
    test_add_lvalue_reference<float Class::*volatile, float Class::*volatile&>();
    test_add_lvalue_reference<void * Class::*volatile, void * Class::*volatile&>();
    test_add_lvalue_reference<int Class::*volatile&, int Class::*volatile&>();
    test_add_lvalue_reference<float Class::*volatile&, float Class::*volatile&>();
    test_add_lvalue_reference<void * Class::*volatile&, void * Class::*volatile&>();
    test_add_lvalue_reference<int Class::*volatile&&, int Class::*volatile&>();
    test_add_lvalue_reference<float Class::*volatile&&, float Class::*volatile&>();
    test_add_lvalue_reference<void * Class::*volatile&&, void * Class::*volatile&>();
    test_add_lvalue_reference<int Class::*const volatile, int Class::*const volatile&>();
    test_add_lvalue_reference<float Class::*const volatile, float Class::*const volatile&>();
    test_add_lvalue_reference<void * Class::*const volatile, void * Class::*const volatile&>();
    test_add_lvalue_reference<int Class::*const volatile&, int Class::*const volatile&>();
    test_add_lvalue_reference<float Class::*const volatile&, float Class::*const volatile&>();
    test_add_lvalue_reference<void * Class::*const volatile&, void * Class::*const volatile&>();
    test_add_lvalue_reference<int Class::*const volatile&&, int Class::*const volatile&>();
    test_add_lvalue_reference<float Class::*const volatile&&, float Class::*const volatile&>();
    test_add_lvalue_reference<void * Class::*const volatile&&, void * Class::*const volatile&>();
    test_add_lvalue_reference<NonCopyable, NonCopyable&>();
    test_add_lvalue_reference<NonMoveable, NonMoveable&>();
    test_add_lvalue_reference<NonConstructible, NonConstructible&>();
    test_add_lvalue_reference<Tracked, Tracked&>();
    test_add_lvalue_reference<TrapConstructible, TrapConstructible&>();
    test_add_lvalue_reference<TrapImplicitConversion, TrapImplicitConversion&>();
    test_add_lvalue_reference<TrapComma, TrapComma&>();
    test_add_lvalue_reference<TrapCall, TrapCall&>();
    test_add_lvalue_reference<TrapSelfAssign, TrapSelfAssign&>();

    // LWG 2101 specifically talks about add_lvalue_reference and functions.
    // The term of art is "a referenceable type", which a cv- or ref-qualified function is not.
    test_function0<Function>();
    test_function0<FunctionPtr>();

    test_function0<void()>();
    test_function1<void()&>();
    test_function1<void() &&>();
    test_function1<void() const>();
    test_function1<void() const&>();
    test_function1<void() const&&>();
    test_function0<void() noexcept>();
    test_function1<void()& noexcept>();
    test_function1<void()&& noexcept>();
    test_function1<void() const noexcept>();
    test_function1<void() const& noexcept>();
    test_function1<void() const&& noexcept>();

    test_function0<void(int)>();
    test_function1<void(int)&>();
    test_function1<void(int) &&>();
    test_function1<void(int) const>();
    test_function1<void(int) const&>();
    test_function1<void(int) const&&>();
    test_function0<void(int) noexcept>();
    test_function1<void(int)& noexcept>();
    test_function1<void(int)&& noexcept>();
    test_function1<void(int) const noexcept>();
    test_function1<void(int) const& noexcept>();
    test_function1<void(int) const&& noexcept>();

    test_function0<void(...)>();
    test_function1<void(...)&>();
    test_function1<void(...) &&>();
    test_function1<void(...) const>();
    test_function1<void(...) const&>();
    test_function1<void(...) const&&>();
    test_function0<void(...) noexcept>();
    test_function1<void(...)& noexcept>();
    test_function1<void(...)&& noexcept>();
    test_function1<void(...) const noexcept>();
    test_function1<void(...) const& noexcept>();
    test_function1<void(...) const&& noexcept>();

    test_function0<void(int, ...)>();
    test_function1<void(int, ...)&>();
    test_function1<void(int, ...) &&>();
    test_function1<void(int, ...) const>();
    test_function1<void(int, ...) const&>();
    test_function1<void(int, ...) const&&>();
    test_function0<void(int, ...) noexcept>();
    test_function1<void(int, ...)& noexcept>();
    test_function1<void(int, ...)&& noexcept>();
    test_function1<void(int, ...) const noexcept>();
    test_function1<void(int, ...) const& noexcept>();
    test_function1<void(int, ...) const&& noexcept>();

    test_function0<int()>();
    test_function1<int()&>();
    test_function1<int() &&>();
    test_function1<int() const>();
    test_function1<int() const&>();
    test_function1<int() const&&>();
    test_function0<int() noexcept>();
    test_function1<int()& noexcept>();
    test_function1<int()&& noexcept>();
    test_function1<int() const noexcept>();
    test_function1<int() const& noexcept>();
    test_function1<int() const&& noexcept>();

    test_function0<int(int)>();
    test_function1<int(int)&>();
    test_function1<int(int) &&>();
    test_function1<int(int) const>();
    test_function1<int(int) const&>();
    test_function1<int(int) const&&>();
    test_function0<int(int) noexcept>();
    test_function1<int(int)& noexcept>();
    test_function1<int(int)&& noexcept>();
    test_function1<int(int) const noexcept>();
    test_function1<int(int) const& noexcept>();
    test_function1<int(int) const&& noexcept>();

    test_function0<int(...)>();
    test_function1<int(...)&>();
    test_function1<int(...) &&>();
    test_function1<int(...) const>();
    test_function1<int(...) const&>();
    test_function1<int(...) const&&>();
    test_function0<int(...) noexcept>();
    test_function1<int(...)& noexcept>();
    test_function1<int(...)&& noexcept>();
    test_function1<int(...) const noexcept>();
    test_function1<int(...) const& noexcept>();
    test_function1<int(...) const&& noexcept>();

    test_function0<int(int, ...)>();
    test_function1<int(int, ...)&>();
    test_function1<int(int, ...) &&>();
    test_function1<int(int, ...) const>();
    test_function1<int(int, ...) const&>();
    test_function1<int(int, ...) const&&>();
    test_function0<int(int, ...) noexcept>();
    test_function1<int(int, ...)& noexcept>();
    test_function1<int(int, ...)&& noexcept>();
    test_function1<int(int, ...) const noexcept>();
    test_function1<int(int, ...) const& noexcept>();
    test_function1<int(int, ...) const&& noexcept>();

    test_function0<void (*)()>();
    test_function0<void (*)() noexcept>();

    test_function0<void (*)(int)>();
    test_function0<void (*)(int) noexcept>();

    test_function0<void (*)(...)>();
    test_function0<void (*)(...) noexcept>();

    test_function0<void (*)(int, ...)>();
    test_function0<void (*)(int, ...) noexcept>();

    test_function0<int (*)()>();
    test_function0<int (*)() noexcept>();

    test_function0<int (*)(int)>();
    test_function0<int (*)(int) noexcept>();

    test_function0<int (*)(...)>();
    test_function0<int (*)(...) noexcept>();

    test_function0<int (*)(int, ...)>();
    test_function0<int (*)(int, ...) noexcept>();

    test_function0<void (&)()>();
    test_function0<void (&)() noexcept>();

    test_function0<void (&)(int)>();
    test_function0<void (&)(int) noexcept>();

    test_function0<void (&)(...)>();
    test_function0<void (&)(...) noexcept>();

    test_function0<void (&)(int, ...)>();
    test_function0<void (&)(int, ...) noexcept>();

    test_function0<int (&)()>();
    test_function0<int (&)() noexcept>();

    test_function0<int (&)(int)>();
    test_function0<int (&)(int) noexcept>();

    test_function0<int (&)(...)>();
    test_function0<int (&)(...) noexcept>();

    test_function0<int (&)(int, ...)>();
    test_function0<int (&)(int, ...) noexcept>();

    test_function0<void(&&)()>();
    test_function0<void(&&)() noexcept>();

    test_function0<void(&&)(int)>();
    test_function0<void(&&)(int) noexcept>();

    test_function0<void(&&)(...)>();
    test_function0<void(&&)(...) noexcept>();

    test_function0<void(&&)(int, ...)>();
    test_function0<void(&&)(int, ...) noexcept>();

    test_function0<int(&&)()>();
    test_function0<int(&&)() noexcept>();

    test_function0<int(&&)(int)>();
    test_function0<int(&&)(int) noexcept>();

    test_function0<int(&&)(...)>();
    test_function0<int(&&)(...) noexcept>();

    test_function0<int(&&)(int, ...)>();
    test_function0<int(&&)(int, ...) noexcept>();

    // But a cv- or ref-qualified member function *is* "a referenceable type"
    test_function0<MemberFunctionPtr>();
    test_function0<void (Class::*)()>();
    test_function0<void (Class::*)()&>();
    test_function0<void (Class::*)() &&>();
    test_function0<void (Class::*)() const>();
    test_function0<void (Class::*)() const&>();
    test_function0<void (Class::*)() const&&>();
    test_function0<void (Class::*)() noexcept>();
    test_function0<void (Class::*)()& noexcept>();
    test_function0<void (Class::*)()&& noexcept>();
    test_function0<void (Class::*)() const noexcept>();
    test_function0<void (Class::*)() const& noexcept>();
    test_function0<void (Class::*)() const&& noexcept>();

    test_function0<void (Class::*)(int)>();
    test_function0<void (Class::*)(int)&>();
    test_function0<void (Class::*)(int) &&>();
    test_function0<void (Class::*)(int) const>();
    test_function0<void (Class::*)(int) const&>();
    test_function0<void (Class::*)(int) const&&>();
    test_function0<void (Class::*)(int) noexcept>();
    test_function0<void (Class::*)(int)& noexcept>();
    test_function0<void (Class::*)(int)&& noexcept>();
    test_function0<void (Class::*)(int) const noexcept>();
    test_function0<void (Class::*)(int) const& noexcept>();
    test_function0<void (Class::*)(int) const&& noexcept>();

    test_function0<void (Class::*)(...)>();
    test_function0<void (Class::*)(...)&>();
    test_function0<void (Class::*)(...) &&>();
    test_function0<void (Class::*)(...) const>();
    test_function0<void (Class::*)(...) const&>();
    test_function0<void (Class::*)(...) const&&>();
    test_function0<void (Class::*)(...) noexcept>();
    test_function0<void (Class::*)(...)& noexcept>();
    test_function0<void (Class::*)(...)&& noexcept>();
    test_function0<void (Class::*)(...) const noexcept>();
    test_function0<void (Class::*)(...) const& noexcept>();
    test_function0<void (Class::*)(...) const&& noexcept>();

    test_function0<void (Class::*)(int, ...)>();
    test_function0<void (Class::*)(int, ...)&>();
    test_function0<void (Class::*)(int, ...) &&>();
    test_function0<void (Class::*)(int, ...) const>();
    test_function0<void (Class::*)(int, ...) const&>();
    test_function0<void (Class::*)(int, ...) const&&>();
    test_function0<void (Class::*)(int, ...) noexcept>();
    test_function0<void (Class::*)(int, ...)& noexcept>();
    test_function0<void (Class::*)(int, ...)&& noexcept>();
    test_function0<void (Class::*)(int, ...) const noexcept>();
    test_function0<void (Class::*)(int, ...) const& noexcept>();
    test_function0<void (Class::*)(int, ...) const&& noexcept>();

    test_function0<int (Class::*)()>();
    test_function0<int (Class::*)()&>();
    test_function0<int (Class::*)() &&>();
    test_function0<int (Class::*)() const>();
    test_function0<int (Class::*)() const&>();
    test_function0<int (Class::*)() const&&>();
    test_function0<int (Class::*)() noexcept>();
    test_function0<int (Class::*)()& noexcept>();
    test_function0<int (Class::*)()&& noexcept>();
    test_function0<int (Class::*)() const noexcept>();
    test_function0<int (Class::*)() const& noexcept>();
    test_function0<int (Class::*)() const&& noexcept>();

    test_function0<int (Class::*)(int)>();
    test_function0<int (Class::*)(int)&>();
    test_function0<int (Class::*)(int) &&>();
    test_function0<int (Class::*)(int) const>();
    test_function0<int (Class::*)(int) const&>();
    test_function0<int (Class::*)(int) const&&>();
    test_function0<int (Class::*)(int) noexcept>();
    test_function0<int (Class::*)(int)& noexcept>();
    test_function0<int (Class::*)(int)&& noexcept>();
    test_function0<int (Class::*)(int) const noexcept>();
    test_function0<int (Class::*)(int) const& noexcept>();
    test_function0<int (Class::*)(int) const&& noexcept>();

    test_function0<int (Class::*)(...)>();
    test_function0<int (Class::*)(...)&>();
    test_function0<int (Class::*)(...) &&>();
    test_function0<int (Class::*)(...) const>();
    test_function0<int (Class::*)(...) const&>();
    test_function0<int (Class::*)(...) const&&>();
    test_function0<int (Class::*)(...) noexcept>();
    test_function0<int (Class::*)(...)& noexcept>();
    test_function0<int (Class::*)(...)&& noexcept>();
    test_function0<int (Class::*)(...) const noexcept>();
    test_function0<int (Class::*)(...) const& noexcept>();
    test_function0<int (Class::*)(...) const&& noexcept>();

    test_function0<int (Class::*)(int, ...)>();
    test_function0<int (Class::*)(int, ...)&>();
    test_function0<int (Class::*)(int, ...) &&>();
    test_function0<int (Class::*)(int, ...) const>();
    test_function0<int (Class::*)(int, ...) const&>();
    test_function0<int (Class::*)(int, ...) const&&>();
    test_function0<int (Class::*)(int, ...) noexcept>();
    test_function0<int (Class::*)(int, ...)& noexcept>();
    test_function0<int (Class::*)(int, ...)&& noexcept>();
    test_function0<int (Class::*)(int, ...) const noexcept>();
    test_function0<int (Class::*)(int, ...) const& noexcept>();
    test_function0<int (Class::*)(int, ...) const&& noexcept>();
}
