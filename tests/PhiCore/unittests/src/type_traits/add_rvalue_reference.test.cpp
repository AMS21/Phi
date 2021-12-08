#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/add_rvalue_reference.hpp>
#include <type_traits>
#include <vector>

template <typename T, typename U = T&&>
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

    // Standard compatibility
    CHECK_SAME_TYPE(typename phi::add_rvalue_reference<T>::type,
                    typename std::add_rvalue_reference<T>::type);
    CHECK_SAME_TYPE(typename phi::add_rvalue_reference<const T>::type,
                    typename std::add_rvalue_reference<const T>::type);
    CHECK_SAME_TYPE(typename phi::add_rvalue_reference<volatile T>::type,
                    typename std::add_rvalue_reference<volatile T>::type);
    CHECK_SAME_TYPE(typename phi::add_rvalue_reference<const volatile T>::type,
                    typename std::add_rvalue_reference<const volatile T>::type);
}

template <typename F>
void test_function0()
{
    CHECK_SAME_TYPE(F&&, typename phi::add_rvalue_reference<F>::type);
    CHECK_SAME_TYPE(F&&, phi::add_rvalue_reference_t<F>);

    // Standard compatibility
    CHECK_SAME_TYPE(typename phi::add_rvalue_reference<F>::type,
                    typename std::add_rvalue_reference<F>::type);
}

template <typename F>
void test_function1()
{
    CHECK_SAME_TYPE(F, typename phi::add_rvalue_reference<F>::type);
    CHECK_SAME_TYPE(F, phi::add_rvalue_reference_t<F>);

    // Standard compatibility
    CHECK_SAME_TYPE(typename phi::add_rvalue_reference<F>::type,
                    typename std::add_rvalue_reference<F>::type);
}

struct Foo
{};

struct A; // incomplete

TEST_CASE("add_rvalue_reference")
{
    test_add_rvalue_reference<A, A&&>();
    test_add_rvalue_reference<Foo, Foo&&>();

    test_add_rvalue_reference<void, void>();
    test_add_rvalue_reference<phi::nullptr_t>();
    test_add_rvalue_reference<bool>();
    test_add_rvalue_reference<char>();
    test_add_rvalue_reference<signed char>();
    test_add_rvalue_reference<unsigned char>();
    test_add_rvalue_reference<short>();
    test_add_rvalue_reference<unsigned short>();
    test_add_rvalue_reference<int>();
    test_add_rvalue_reference<unsigned int>();
    test_add_rvalue_reference<long>();
    test_add_rvalue_reference<unsigned long>();
    test_add_rvalue_reference<long long>();
    test_add_rvalue_reference<unsigned long long>();
    test_add_rvalue_reference<float>();
    test_add_rvalue_reference<double>();
    test_add_rvalue_reference<long double>();
    test_add_rvalue_reference<char8_t>();
    test_add_rvalue_reference<char16_t>();
    test_add_rvalue_reference<char32_t>();
    test_add_rvalue_reference<wchar_t>();

    test_add_rvalue_reference<phi::boolean>();
    test_add_rvalue_reference<phi::integer<signed char>>();
    test_add_rvalue_reference<phi::integer<unsigned char>>();
    test_add_rvalue_reference<phi::integer<short>>();
    test_add_rvalue_reference<phi::integer<unsigned short>>();
    test_add_rvalue_reference<phi::integer<int>>();
    test_add_rvalue_reference<phi::integer<unsigned int>>();
    test_add_rvalue_reference<phi::integer<long>>();
    test_add_rvalue_reference<phi::integer<unsigned long>>();
    test_add_rvalue_reference<phi::integer<long long>>();
    test_add_rvalue_reference<phi::integer<unsigned long long>>();
    test_add_rvalue_reference<phi::floating_point<float>>();
    test_add_rvalue_reference<phi::floating_point<double>>();
    test_add_rvalue_reference<phi::floating_point<long double>>();

    test_add_rvalue_reference<std::vector<int>>();
    test_add_rvalue_reference<phi::scope_ptr<int>>();

    test_add_rvalue_reference<int&>();
    test_add_rvalue_reference<const int&>();
    test_add_rvalue_reference<volatile int&>();
    test_add_rvalue_reference<const volatile int&>();
    test_add_rvalue_reference<int&&>();
    test_add_rvalue_reference<const int&&>();
    test_add_rvalue_reference<volatile int&&>();
    test_add_rvalue_reference<const volatile int&&>();
    test_add_rvalue_reference<int*>();
    test_add_rvalue_reference<const int*>();
    test_add_rvalue_reference<volatile int*>();
    test_add_rvalue_reference<const volatile int*>();
    test_add_rvalue_reference<int**>();
    test_add_rvalue_reference<const int**>();
    test_add_rvalue_reference<volatile int**>();
    test_add_rvalue_reference<const volatile int**>();
    test_add_rvalue_reference<int*&>();
    test_add_rvalue_reference<const int*&>();
    test_add_rvalue_reference<volatile int*&>();
    test_add_rvalue_reference<const volatile int*&>();
    test_add_rvalue_reference<int*&&>();
    test_add_rvalue_reference<const int*&&>();
    test_add_rvalue_reference<volatile int*&&>();
    test_add_rvalue_reference<const volatile int*&&>();
    test_add_rvalue_reference<void*>();
    test_add_rvalue_reference<char[3]>();
    test_add_rvalue_reference<char[]>();
    test_add_rvalue_reference<char* [3]>();
    test_add_rvalue_reference<char*[]>();
    test_add_rvalue_reference<int(*)[3]>();
    test_add_rvalue_reference<int(*)[]>();
    test_add_rvalue_reference<int(&)[3]>();
    test_add_rvalue_reference<int(&)[]>();
    test_add_rvalue_reference<int(&&)[3]>();
    test_add_rvalue_reference<int(&&)[]>();
    test_add_rvalue_reference<char[3][2]>();
    test_add_rvalue_reference<char[][2]>();
    test_add_rvalue_reference<char* [3][2]>();
    test_add_rvalue_reference<char*[][2]>();
    test_add_rvalue_reference<int(*)[3][2]>();
    test_add_rvalue_reference<int(*)[][2]>();
    test_add_rvalue_reference<int(&)[3][2]>();
    test_add_rvalue_reference<int(&)[][2]>();
    test_add_rvalue_reference<int(&&)[3][2]>();
    test_add_rvalue_reference<int(&&)[][2]>();
    test_add_rvalue_reference<Class>();
    test_add_rvalue_reference<Class[]>();
    test_add_rvalue_reference<Class[2]>();
    test_add_rvalue_reference<Template<void>>();
    test_add_rvalue_reference<Template<int>>();
    test_add_rvalue_reference<Template<Class>>();
    test_add_rvalue_reference<Template<incomplete_type>>();
    test_add_rvalue_reference<VariadicTemplate<>>();
    test_add_rvalue_reference<VariadicTemplate<void>>();
    test_add_rvalue_reference<VariadicTemplate<int>>();
    test_add_rvalue_reference<VariadicTemplate<Class>>();
    test_add_rvalue_reference<VariadicTemplate<incomplete_type>>();
    test_add_rvalue_reference<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_add_rvalue_reference<PublicDerviedFromTemplate<Base>>();
    test_add_rvalue_reference<PublicDerviedFromTemplate<Derived>>();
    test_add_rvalue_reference<PublicDerviedFromTemplate<Class>>();
    test_add_rvalue_reference<PrivateDerviedFromTemplate<Base>>();
    test_add_rvalue_reference<PrivateDerviedFromTemplate<Derived>>();
    test_add_rvalue_reference<PrivateDerviedFromTemplate<Class>>();
    test_add_rvalue_reference<ProtectedDerviedFromTemplate<Base>>();
    test_add_rvalue_reference<ProtectedDerviedFromTemplate<Derived>>();
    test_add_rvalue_reference<ProtectedDerviedFromTemplate<Class>>();
    test_add_rvalue_reference<Union>();
    test_add_rvalue_reference<NonEmptyUnion>();
    test_add_rvalue_reference<Empty>();
    test_add_rvalue_reference<NotEmpty>();
    test_add_rvalue_reference<bit_zero>();
    test_add_rvalue_reference<bit_one>();
    test_add_rvalue_reference<Base>();
    test_add_rvalue_reference<Derived>();
    test_add_rvalue_reference<Abstract>();
    test_add_rvalue_reference<PublicAbstract>();
    test_add_rvalue_reference<PrivateAbstract>();
    test_add_rvalue_reference<ProtectedAbstract>();
    test_add_rvalue_reference<AbstractTemplate<int>>();
    test_add_rvalue_reference<AbstractTemplate<double>>();
    test_add_rvalue_reference<AbstractTemplate<Class>>();
    test_add_rvalue_reference<AbstractTemplate<incomplete_type>>();
    test_add_rvalue_reference<Final>();
    test_add_rvalue_reference<PublicDestructor>();
    test_add_rvalue_reference<ProtectedDestructor>();
    test_add_rvalue_reference<PrivateDestructor>();
    test_add_rvalue_reference<VirtualPublicDestructor>();
    test_add_rvalue_reference<VirtualProtectedDestructor>();
    test_add_rvalue_reference<VirtualPrivateDestructor>();
    test_add_rvalue_reference<PurePublicDestructor>();
    test_add_rvalue_reference<PureProtectedDestructor>();
    test_add_rvalue_reference<PurePrivateDestructor>();
    test_add_rvalue_reference<DeletedPublicDestructor>();
    test_add_rvalue_reference<DeletedProtectedDestructor>();
    test_add_rvalue_reference<DeletedPrivateDestructor>();
    test_add_rvalue_reference<DeletedVirtualPublicDestructor>();
    test_add_rvalue_reference<DeletedVirtualProtectedDestructor>();
    test_add_rvalue_reference<DeletedVirtualPrivateDestructor>();
    test_add_rvalue_reference<Enum>();
    test_add_rvalue_reference<EnumSigned>();
    test_add_rvalue_reference<EnumUnsigned>();
    test_add_rvalue_reference<EnumClass>();
    test_add_rvalue_reference<EnumStruct>();
    test_add_rvalue_reference<Function>();
    test_add_rvalue_reference<FunctionPtr>();
    test_add_rvalue_reference<MemberObjectPtr>();
    test_add_rvalue_reference<MemberFunctionPtr>();
    test_add_rvalue_reference<incomplete_type>();
    test_add_rvalue_reference<IncompleteTemplate<void>>();
    test_add_rvalue_reference<IncompleteTemplate<int>>();
    test_add_rvalue_reference<IncompleteTemplate<Class>>();
    test_add_rvalue_reference<IncompleteTemplate<incomplete_type>>();
    test_add_rvalue_reference<IncompleteVariadicTemplate<>>();
    test_add_rvalue_reference<IncompleteVariadicTemplate<void>>();
    test_add_rvalue_reference<IncompleteVariadicTemplate<int>>();
    test_add_rvalue_reference<IncompleteVariadicTemplate<Class>>();
    test_add_rvalue_reference<IncompleteVariadicTemplate<incomplete_type>>();
    test_add_rvalue_reference<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_add_rvalue_reference<int Class::*>();
    test_add_rvalue_reference<float Class::*>();
    test_add_rvalue_reference<void * Class::*>();
    test_add_rvalue_reference<int * Class::*>();
    test_add_rvalue_reference<int Class::*&>();
    test_add_rvalue_reference<float Class::*&>();
    test_add_rvalue_reference<void * Class::*&>();
    test_add_rvalue_reference<int * Class::*&>();
    test_add_rvalue_reference<int Class::*&&>();
    test_add_rvalue_reference<float Class::*&&>();
    test_add_rvalue_reference<void * Class::*&&>();
    test_add_rvalue_reference<int * Class::*&&>();
    test_add_rvalue_reference<int Class::*const>();
    test_add_rvalue_reference<float Class::*const>();
    test_add_rvalue_reference<void * Class::*const>();
    test_add_rvalue_reference<int Class::*const&>();
    test_add_rvalue_reference<float Class::*const&>();
    test_add_rvalue_reference<void * Class::*const&>();
    test_add_rvalue_reference<int Class::*const&&>();
    test_add_rvalue_reference<float Class::*const&&>();
    test_add_rvalue_reference<void * Class::*const&&>();
    test_add_rvalue_reference<int Class::*volatile>();
    test_add_rvalue_reference<float Class::*volatile>();
    test_add_rvalue_reference<void * Class::*volatile>();
    test_add_rvalue_reference<int Class::*volatile&>();
    test_add_rvalue_reference<float Class::*volatile&>();
    test_add_rvalue_reference<void * Class::*volatile&>();
    test_add_rvalue_reference<int Class::*volatile&&>();
    test_add_rvalue_reference<float Class::*volatile&&>();
    test_add_rvalue_reference<void * Class::*volatile&&>();
    test_add_rvalue_reference<int Class::*const volatile>();
    test_add_rvalue_reference<float Class::*const volatile>();
    test_add_rvalue_reference<void * Class::*const volatile>();
    test_add_rvalue_reference<int Class::*const volatile&>();
    test_add_rvalue_reference<float Class::*const volatile&>();
    test_add_rvalue_reference<void * Class::*const volatile&>();
    test_add_rvalue_reference<int Class::*const volatile&&>();
    test_add_rvalue_reference<float Class::*const volatile&&>();
    test_add_rvalue_reference<void * Class::*const volatile&&>();
    test_add_rvalue_reference<NonCopyable>();
    test_add_rvalue_reference<NonMoveable>();
    test_add_rvalue_reference<NonConstructible>();
    test_add_rvalue_reference<Tracked>();
    test_add_rvalue_reference<TrapConstructible>();
    test_add_rvalue_reference<TrapImplicitConversion>();
    test_add_rvalue_reference<TrapComma>();
    test_add_rvalue_reference<TrapCall>();
    test_add_rvalue_reference<TrapSelfAssign>();
    test_add_rvalue_reference<TrapDeref>();
    test_add_rvalue_reference<TrapArraySubscript>();

    test_function0<void()>();
    test_function1<void()&>();
    test_function1<void() &&>();
    test_function1<void() const>();
    test_function1<void() const&>();
    test_function1<void() const&&>();
    test_function1<void() volatile>();
    test_function1<void() volatile&>();
    test_function1<void() volatile&&>();
    test_function1<void() const volatile>();
    test_function1<void() const volatile&>();
    test_function1<void() const volatile&&>();
    test_function0<void() noexcept>();
    test_function1<void()& noexcept>();
    test_function1<void()&& noexcept>();
    test_function1<void() const noexcept>();
    test_function1<void() const& noexcept>();
    test_function1<void() const&& noexcept>();
    test_function1<void() volatile noexcept>();
    test_function1<void() volatile& noexcept>();
    test_function1<void() volatile&& noexcept>();
    test_function1<void() const volatile noexcept>();
    test_function1<void() const volatile& noexcept>();
    test_function1<void() const volatile&& noexcept>();

    test_function0<void(int)>();
    test_function1<void(int)&>();
    test_function1<void(int) &&>();
    test_function1<void(int) const>();
    test_function1<void(int) const&>();
    test_function1<void(int) const&&>();
    test_function1<void(int) volatile>();
    test_function1<void(int) volatile&>();
    test_function1<void(int) volatile&&>();
    test_function1<void(int) const volatile>();
    test_function1<void(int) const volatile&>();
    test_function1<void(int) const volatile&&>();
    test_function0<void(int) noexcept>();
    test_function1<void(int)& noexcept>();
    test_function1<void(int)&& noexcept>();
    test_function1<void(int) const noexcept>();
    test_function1<void(int) const& noexcept>();
    test_function1<void(int) const&& noexcept>();
    test_function1<void(int) volatile noexcept>();
    test_function1<void(int) volatile& noexcept>();
    test_function1<void(int) volatile&& noexcept>();
    test_function1<void(int) const volatile noexcept>();
    test_function1<void(int) const volatile& noexcept>();
    test_function1<void(int) const volatile&& noexcept>();

    test_function0<void(...)>();
    test_function1<void(...)&>();
    test_function1<void(...) &&>();
    test_function1<void(...) const>();
    test_function1<void(...) const&>();
    test_function1<void(...) const&&>();
    test_function1<void(...) volatile>();
    test_function1<void(...) volatile&>();
    test_function1<void(...) volatile&&>();
    test_function1<void(...) const volatile>();
    test_function1<void(...) const volatile&>();
    test_function1<void(...) const volatile&&>();
    test_function0<void(...) noexcept>();
    test_function1<void(...)& noexcept>();
    test_function1<void(...)&& noexcept>();
    test_function1<void(...) const noexcept>();
    test_function1<void(...) const& noexcept>();
    test_function1<void(...) const&& noexcept>();
    test_function1<void(...) volatile noexcept>();
    test_function1<void(...) volatile& noexcept>();
    test_function1<void(...) volatile&& noexcept>();
    test_function1<void(...) const volatile noexcept>();
    test_function1<void(...) const volatile& noexcept>();
    test_function1<void(...) const volatile&& noexcept>();

    test_function0<void(int, ...)>();
    test_function1<void(int, ...)&>();
    test_function1<void(int, ...) &&>();
    test_function1<void(int, ...) const>();
    test_function1<void(int, ...) const&>();
    test_function1<void(int, ...) const&&>();
    test_function1<void(int, ...) volatile>();
    test_function1<void(int, ...) volatile&>();
    test_function1<void(int, ...) volatile&&>();
    test_function1<void(int, ...) const volatile>();
    test_function1<void(int, ...) const volatile&>();
    test_function1<void(int, ...) const volatile&&>();
    test_function0<void(int, ...) noexcept>();
    test_function1<void(int, ...)& noexcept>();
    test_function1<void(int, ...)&& noexcept>();
    test_function1<void(int, ...) const noexcept>();
    test_function1<void(int, ...) const& noexcept>();
    test_function1<void(int, ...) const&& noexcept>();
    test_function1<void(int, ...) volatile noexcept>();
    test_function1<void(int, ...) volatile& noexcept>();
    test_function1<void(int, ...) volatile&& noexcept>();
    test_function1<void(int, ...) const volatile noexcept>();
    test_function1<void(int, ...) const volatile& noexcept>();
    test_function1<void(int, ...) const volatile&& noexcept>();

    test_function0<int()>();
    test_function1<int()&>();
    test_function1<int() &&>();
    test_function1<int() const>();
    test_function1<int() const&>();
    test_function1<int() const&&>();
    test_function1<int() volatile>();
    test_function1<int() volatile&>();
    test_function1<int() volatile&&>();
    test_function1<int() const volatile>();
    test_function1<int() const volatile&>();
    test_function1<int() const volatile&&>();
    test_function0<int() noexcept>();
    test_function1<int()& noexcept>();
    test_function1<int()&& noexcept>();
    test_function1<int() const noexcept>();
    test_function1<int() const& noexcept>();
    test_function1<int() const&& noexcept>();
    test_function1<int() volatile noexcept>();
    test_function1<int() volatile& noexcept>();
    test_function1<int() volatile&& noexcept>();
    test_function1<int() const volatile noexcept>();
    test_function1<int() const volatile& noexcept>();
    test_function1<int() const volatile&& noexcept>();

    test_function0<int(int)>();
    test_function1<int(int)&>();
    test_function1<int(int) &&>();
    test_function1<int(int) const>();
    test_function1<int(int) const&>();
    test_function1<int(int) const&&>();
    test_function1<int(int) volatile>();
    test_function1<int(int) volatile&>();
    test_function1<int(int) volatile&&>();
    test_function1<int(int) const volatile>();
    test_function1<int(int) const volatile&>();
    test_function1<int(int) const volatile&&>();
    test_function0<int(int) noexcept>();
    test_function1<int(int)& noexcept>();
    test_function1<int(int)&& noexcept>();
    test_function1<int(int) const noexcept>();
    test_function1<int(int) const& noexcept>();
    test_function1<int(int) const&& noexcept>();
    test_function1<int(int) volatile noexcept>();
    test_function1<int(int) volatile& noexcept>();
    test_function1<int(int) volatile&& noexcept>();
    test_function1<int(int) const volatile noexcept>();
    test_function1<int(int) const volatile& noexcept>();
    test_function1<int(int) const volatile&& noexcept>();

    test_function0<int(...)>();
    test_function1<int(...)&>();
    test_function1<int(...) &&>();
    test_function1<int(...) const>();
    test_function1<int(...) const&>();
    test_function1<int(...) const&&>();
    test_function1<int(...) volatile>();
    test_function1<int(...) volatile&>();
    test_function1<int(...) volatile&&>();
    test_function1<int(...) const volatile>();
    test_function1<int(...) const volatile&>();
    test_function1<int(...) const volatile&&>();
    test_function0<int(...) noexcept>();
    test_function1<int(...)& noexcept>();
    test_function1<int(...)&& noexcept>();
    test_function1<int(...) const noexcept>();
    test_function1<int(...) const& noexcept>();
    test_function1<int(...) const&& noexcept>();
    test_function1<int(...) volatile noexcept>();
    test_function1<int(...) volatile& noexcept>();
    test_function1<int(...) volatile&& noexcept>();
    test_function1<int(...) const volatile noexcept>();
    test_function1<int(...) const volatile& noexcept>();
    test_function1<int(...) const volatile&& noexcept>();

    test_function0<int(int, ...)>();
    test_function1<int(int, ...)&>();
    test_function1<int(int, ...) &&>();
    test_function1<int(int, ...) const>();
    test_function1<int(int, ...) const&>();
    test_function1<int(int, ...) const&&>();
    test_function1<int(int, ...) volatile>();
    test_function1<int(int, ...) volatile&>();
    test_function1<int(int, ...) volatile&&>();
    test_function1<int(int, ...) const volatile>();
    test_function1<int(int, ...) const volatile&>();
    test_function1<int(int, ...) const volatile&&>();
    test_function0<int(int, ...) noexcept>();
    test_function1<int(int, ...)& noexcept>();
    test_function1<int(int, ...)&& noexcept>();
    test_function1<int(int, ...) const noexcept>();
    test_function1<int(int, ...) const& noexcept>();
    test_function1<int(int, ...) const&& noexcept>();
    test_function1<int(int, ...) volatile noexcept>();
    test_function1<int(int, ...) volatile& noexcept>();
    test_function1<int(int, ...) volatile&& noexcept>();
    test_function1<int(int, ...) const volatile noexcept>();
    test_function1<int(int, ...) const volatile& noexcept>();
    test_function1<int(int, ...) const volatile&& noexcept>();

    test_add_rvalue_reference<void (*)()>();
    test_add_rvalue_reference<void (*)() noexcept>();

    test_add_rvalue_reference<void (*)(int)>();
    test_add_rvalue_reference<void (*)(int) noexcept>();

    test_add_rvalue_reference<void (*)(...)>();
    test_add_rvalue_reference<void (*)(...) noexcept>();

    test_add_rvalue_reference<void (*)(int, ...)>();
    test_add_rvalue_reference<void (*)(int, ...) noexcept>();

    test_add_rvalue_reference<int (*)()>();
    test_add_rvalue_reference<int (*)() noexcept>();

    test_add_rvalue_reference<int (*)(int)>();
    test_add_rvalue_reference<int (*)(int) noexcept>();

    test_add_rvalue_reference<int (*)(...)>();
    test_add_rvalue_reference<int (*)(...) noexcept>();

    test_add_rvalue_reference<int (*)(int, ...)>();
    test_add_rvalue_reference<int (*)(int, ...) noexcept>();

    test_add_rvalue_reference<void (&)()>();
    test_add_rvalue_reference<void (&)() noexcept>();

    test_add_rvalue_reference<void (&)(int)>();
    test_add_rvalue_reference<void (&)(int) noexcept>();

    test_add_rvalue_reference<void (&)(...)>();
    test_add_rvalue_reference<void (&)(...) noexcept>();

    test_add_rvalue_reference<void (&)(int, ...)>();
    test_add_rvalue_reference<void (&)(int, ...) noexcept>();

    test_add_rvalue_reference<int (&)()>();
    test_add_rvalue_reference<int (&)() noexcept>();

    test_add_rvalue_reference<int (&)(int)>();
    test_add_rvalue_reference<int (&)(int) noexcept>();

    test_add_rvalue_reference<int (&)(...)>();
    test_add_rvalue_reference<int (&)(...) noexcept>();

    test_add_rvalue_reference<int (&)(int, ...)>();
    test_add_rvalue_reference<int (&)(int, ...) noexcept>();

    test_add_rvalue_reference<void(&&)()>();
    test_add_rvalue_reference<void(&&)() noexcept>();

    test_add_rvalue_reference<void(&&)(int)>();
    test_add_rvalue_reference<void(&&)(int) noexcept>();

    test_add_rvalue_reference<void(&&)(...)>();
    test_add_rvalue_reference<void(&&)(...) noexcept>();

    test_add_rvalue_reference<void(&&)(int, ...)>();
    test_add_rvalue_reference<void(&&)(int, ...) noexcept>();

    test_add_rvalue_reference<int(&&)()>();
    test_add_rvalue_reference<int(&&)() noexcept>();

    test_add_rvalue_reference<int(&&)(int)>();
    test_add_rvalue_reference<int(&&)(int) noexcept>();

    test_add_rvalue_reference<int(&&)(...)>();
    test_add_rvalue_reference<int(&&)(...) noexcept>();

    test_add_rvalue_reference<int(&&)(int, ...)>();
    test_add_rvalue_reference<int(&&)(int, ...) noexcept>();

    test_add_rvalue_reference<void (Class::*)()>();
    test_add_rvalue_reference<void (Class::*)()&>();
    test_add_rvalue_reference<void (Class::*)() &&>();
    test_add_rvalue_reference<void (Class::*)() const>();
    test_add_rvalue_reference<void (Class::*)() const&>();
    test_add_rvalue_reference<void (Class::*)() const&&>();
    test_add_rvalue_reference<void (Class::*)() noexcept>();
    test_add_rvalue_reference<void (Class::*)()& noexcept>();
    test_add_rvalue_reference<void (Class::*)()&& noexcept>();
    test_add_rvalue_reference<void (Class::*)() const noexcept>();
    test_add_rvalue_reference<void (Class::*)() const& noexcept>();
    test_add_rvalue_reference<void (Class::*)() const&& noexcept>();

    test_add_rvalue_reference<void (Class::*)(int)>();
    test_add_rvalue_reference<void (Class::*)(int)&>();
    test_add_rvalue_reference<void (Class::*)(int) &&>();
    test_add_rvalue_reference<void (Class::*)(int) const>();
    test_add_rvalue_reference<void (Class::*)(int) const&>();
    test_add_rvalue_reference<void (Class::*)(int) const&&>();
    test_add_rvalue_reference<void (Class::*)(int) noexcept>();
    test_add_rvalue_reference<void (Class::*)(int)& noexcept>();
    test_add_rvalue_reference<void (Class::*)(int)&& noexcept>();
    test_add_rvalue_reference<void (Class::*)(int) const noexcept>();
    test_add_rvalue_reference<void (Class::*)(int) const& noexcept>();
    test_add_rvalue_reference<void (Class::*)(int) const&& noexcept>();

    test_add_rvalue_reference<void (Class::*)(...)>();
    test_add_rvalue_reference<void (Class::*)(...)&>();
    test_add_rvalue_reference<void (Class::*)(...) &&>();
    test_add_rvalue_reference<void (Class::*)(...) const>();
    test_add_rvalue_reference<void (Class::*)(...) const&>();
    test_add_rvalue_reference<void (Class::*)(...) const&&>();
    test_add_rvalue_reference<void (Class::*)(...) noexcept>();
    test_add_rvalue_reference<void (Class::*)(...)& noexcept>();
    test_add_rvalue_reference<void (Class::*)(...)&& noexcept>();
    test_add_rvalue_reference<void (Class::*)(...) const noexcept>();
    test_add_rvalue_reference<void (Class::*)(...) const& noexcept>();
    test_add_rvalue_reference<void (Class::*)(...) const&& noexcept>();

    test_add_rvalue_reference<void (Class::*)(int, ...)>();
    test_add_rvalue_reference<void (Class::*)(int, ...)&>();
    test_add_rvalue_reference<void (Class::*)(int, ...) &&>();
    test_add_rvalue_reference<void (Class::*)(int, ...) const>();
    test_add_rvalue_reference<void (Class::*)(int, ...) const&>();
    test_add_rvalue_reference<void (Class::*)(int, ...) const&&>();
    test_add_rvalue_reference<void (Class::*)(int, ...) noexcept>();
    test_add_rvalue_reference<void (Class::*)(int, ...)& noexcept>();
    test_add_rvalue_reference<void (Class::*)(int, ...)&& noexcept>();
    test_add_rvalue_reference<void (Class::*)(int, ...) const noexcept>();
    test_add_rvalue_reference<void (Class::*)(int, ...) const& noexcept>();
    test_add_rvalue_reference<void (Class::*)(int, ...) const&& noexcept>();

    test_add_rvalue_reference<int (Class::*)()>();
    test_add_rvalue_reference<int (Class::*)()&>();
    test_add_rvalue_reference<int (Class::*)() &&>();
    test_add_rvalue_reference<int (Class::*)() const>();
    test_add_rvalue_reference<int (Class::*)() const&>();
    test_add_rvalue_reference<int (Class::*)() const&&>();
    test_add_rvalue_reference<int (Class::*)() noexcept>();
    test_add_rvalue_reference<int (Class::*)()& noexcept>();
    test_add_rvalue_reference<int (Class::*)()&& noexcept>();
    test_add_rvalue_reference<int (Class::*)() const noexcept>();
    test_add_rvalue_reference<int (Class::*)() const& noexcept>();
    test_add_rvalue_reference<int (Class::*)() const&& noexcept>();

    test_add_rvalue_reference<int (Class::*)(int)>();
    test_add_rvalue_reference<int (Class::*)(int)&>();
    test_add_rvalue_reference<int (Class::*)(int) &&>();
    test_add_rvalue_reference<int (Class::*)(int) const>();
    test_add_rvalue_reference<int (Class::*)(int) const&>();
    test_add_rvalue_reference<int (Class::*)(int) const&&>();
    test_add_rvalue_reference<int (Class::*)(int) noexcept>();
    test_add_rvalue_reference<int (Class::*)(int)& noexcept>();
    test_add_rvalue_reference<int (Class::*)(int)&& noexcept>();
    test_add_rvalue_reference<int (Class::*)(int) const noexcept>();
    test_add_rvalue_reference<int (Class::*)(int) const& noexcept>();
    test_add_rvalue_reference<int (Class::*)(int) const&& noexcept>();

    test_add_rvalue_reference<int (Class::*)(...)>();
    test_add_rvalue_reference<int (Class::*)(...)&>();
    test_add_rvalue_reference<int (Class::*)(...) &&>();
    test_add_rvalue_reference<int (Class::*)(...) const>();
    test_add_rvalue_reference<int (Class::*)(...) const&>();
    test_add_rvalue_reference<int (Class::*)(...) const&&>();
    test_add_rvalue_reference<int (Class::*)(...) noexcept>();
    test_add_rvalue_reference<int (Class::*)(...)& noexcept>();
    test_add_rvalue_reference<int (Class::*)(...)&& noexcept>();
    test_add_rvalue_reference<int (Class::*)(...) const noexcept>();
    test_add_rvalue_reference<int (Class::*)(...) const& noexcept>();
    test_add_rvalue_reference<int (Class::*)(...) const&& noexcept>();

    test_add_rvalue_reference<int (Class::*)(int, ...)>();
    test_add_rvalue_reference<int (Class::*)(int, ...)&>();
    test_add_rvalue_reference<int (Class::*)(int, ...) &&>();
    test_add_rvalue_reference<int (Class::*)(int, ...) const>();
    test_add_rvalue_reference<int (Class::*)(int, ...) const&>();
    test_add_rvalue_reference<int (Class::*)(int, ...) const&&>();
    test_add_rvalue_reference<int (Class::*)(int, ...) noexcept>();
    test_add_rvalue_reference<int (Class::*)(int, ...)& noexcept>();
    test_add_rvalue_reference<int (Class::*)(int, ...)&& noexcept>();
    test_add_rvalue_reference<int (Class::*)(int, ...) const noexcept>();
    test_add_rvalue_reference<int (Class::*)(int, ...) const& noexcept>();
    test_add_rvalue_reference<int (Class::*)(int, ...) const&& noexcept>();

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
