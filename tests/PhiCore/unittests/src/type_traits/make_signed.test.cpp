#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/conditional.hpp>
#include <phi/type_traits/make_signed.hpp>
#include <cstdint>
#include <vector>

template <typename T, typename U>
void test_make_signed_impl()
{
    CHECK_SAME_TYPE(typename phi::make_signed<T>::type, U);
    CHECK_SAME_TYPE(phi::make_signed_t<T>, U);
}

template <typename T, typename U = T>
void test_make_signed()
{
    test_make_signed_impl<T, U>();
    test_make_signed_impl<const T, const U>();
    test_make_signed_impl<volatile T, volatile U>();
    test_make_signed_impl<const volatile T, const volatile U>();
}

enum BigEnum : long long
{
    bigzero,
    big = 0xFFFFFFFFFFFFFFFLL
};

TEST_CASE("make_signed")
{
    // test_make_signed<
    //         Enum, phi::conditional<sizeof(Enum) == sizeof(int), int,  char>>();

    test_make_signed<void>();
    test_make_signed<phi::nullptr_t>();
    test_make_signed<bool>();
    test_make_signed<char, signed char>();
    test_make_signed<signed char>();
    test_make_signed<unsigned char, signed char>();
    test_make_signed<short>();
    test_make_signed<unsigned short, short>();
    test_make_signed<int>();
    test_make_signed<unsigned int, int>();
    test_make_signed<long>();
    test_make_signed<unsigned long, long>();
    test_make_signed<long long>();
    test_make_signed<unsigned long long, long long>();
    test_make_signed<float>();
    test_make_signed<double>();
    test_make_signed<long double>();
    //test_make_signed<char8_t>();
    //test_make_signed<char16_t>();
    //test_make_signed<char32_t>();
    //test_make_signed<wchar_t>();

    test_make_signed<phi::boolean>();
    test_make_signed<phi::integer<signed char>>();
    test_make_signed<phi::integer<unsigned char>, phi::integer<signed char>>();
    test_make_signed<phi::integer<short>>();
    test_make_signed<phi::integer<unsigned short>, phi::integer<short>>();
    test_make_signed<phi::integer<int>>();
    test_make_signed<phi::integer<unsigned int>, phi::integer<int>>();
    test_make_signed<phi::integer<long>>();
    test_make_signed<phi::integer<unsigned long>, phi::integer<long>>();
    test_make_signed<phi::integer<long long>>();
    test_make_signed<phi::integer<unsigned long long>, phi::integer<long long>>();
    test_make_signed<phi::floating_point<float>>();
    test_make_signed<phi::floating_point<double>>();
    test_make_signed<phi::floating_point<long double>>();

    test_make_signed<std::vector<int>>();
    test_make_signed<phi::scope_ptr<int>>();

    test_make_signed<int&>();
    test_make_signed<const int&>();
    test_make_signed<volatile int&>();
    test_make_signed<const volatile int&>();
    test_make_signed<int&&>();
    test_make_signed<const int&&>();
    test_make_signed<volatile int&&>();
    test_make_signed<const volatile int&&>();
    test_make_signed<int*>();
    test_make_signed<const int*>();
    test_make_signed<volatile int*>();
    test_make_signed<const volatile int*>();
    test_make_signed<int**>();
    test_make_signed<const int**>();
    test_make_signed<volatile int**>();
    test_make_signed<const volatile int**>();
    test_make_signed<int*&>();
    test_make_signed<const int*&>();
    test_make_signed<volatile int*&>();
    test_make_signed<const volatile int*&>();
    test_make_signed<int*&&>();
    test_make_signed<const int*&&>();
    test_make_signed<volatile int*&&>();
    test_make_signed<const volatile int*&&>();
    test_make_signed<void*>();
    test_make_signed<char[3]>();
    test_make_signed<char[]>();
    test_make_signed<char* [3]>();
    test_make_signed<char*[]>();
    test_make_signed<int(*)[3]>();
    test_make_signed<int(*)[]>();
    test_make_signed<int(&)[3]>();
    test_make_signed<int(&)[]>();
    test_make_signed<int(&&)[3]>();
    test_make_signed<int(&&)[]>();
    test_make_signed<char[3][2]>();
    test_make_signed<char[][2]>();
    test_make_signed<char* [3][2]>();
    test_make_signed<char*[][2]>();
    test_make_signed<int(*)[3][2]>();
    test_make_signed<int(*)[][2]>();
    test_make_signed<int(&)[3][2]>();
    test_make_signed<int(&)[][2]>();
    test_make_signed<int(&&)[3][2]>();
    test_make_signed<int(&&)[][2]>();
    test_make_signed<Class>();
    test_make_signed<Class[]>();
    test_make_signed<Class[2]>();
    test_make_signed<Template<void>>();
    test_make_signed<Template<int>>();
    test_make_signed<Template<Class>>();
    test_make_signed<Template<incomplete_type>>();
    test_make_signed<VariadicTemplate<>>();
    test_make_signed<VariadicTemplate<void>>();
    test_make_signed<VariadicTemplate<int>>();
    test_make_signed<VariadicTemplate<Class>>();
    test_make_signed<VariadicTemplate<incomplete_type>>();
    test_make_signed<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_make_signed<PublicDerviedFromTemplate<Base>>();
    test_make_signed<PublicDerviedFromTemplate<Derived>>();
    test_make_signed<PublicDerviedFromTemplate<Class>>();
    test_make_signed<PrivateDerviedFromTemplate<Base>>();
    test_make_signed<PrivateDerviedFromTemplate<Derived>>();
    test_make_signed<PrivateDerviedFromTemplate<Class>>();
    test_make_signed<ProtectedDerviedFromTemplate<Base>>();
    test_make_signed<ProtectedDerviedFromTemplate<Derived>>();
    test_make_signed<ProtectedDerviedFromTemplate<Class>>();
    test_make_signed<Union>();
    test_make_signed<NonEmptyUnion>();
    test_make_signed<Empty>();
    test_make_signed<NotEmpty>();
    test_make_signed<bit_zero>();
    test_make_signed<bit_one>();
    test_make_signed<Base>();
    test_make_signed<Derived>();
    test_make_signed<Abstract>();
    test_make_signed<PublicAbstract>();
    test_make_signed<PrivateAbstract>();
    test_make_signed<ProtectedAbstract>();
    test_make_signed<AbstractTemplate<int>>();
    test_make_signed<AbstractTemplate<double>>();
    test_make_signed<AbstractTemplate<Class>>();
    test_make_signed<AbstractTemplate<incomplete_type>>();
    test_make_signed<Final>();
    test_make_signed<PublicDestructor>();
    test_make_signed<ProtectedDestructor>();
    test_make_signed<PrivateDestructor>();
    test_make_signed<VirtualPublicDestructor>();
    test_make_signed<VirtualProtectedDestructor>();
    test_make_signed<VirtualPrivateDestructor>();
    test_make_signed<PurePublicDestructor>();
    test_make_signed<PureProtectedDestructor>();
    test_make_signed<PurePrivateDestructor>();
    test_make_signed<DeletedPublicDestructor>();
    test_make_signed<DeletedProtectedDestructor>();
    test_make_signed<DeletedPrivateDestructor>();
    test_make_signed<DeletedVirtualPublicDestructor>();
    test_make_signed<DeletedVirtualProtectedDestructor>();
    test_make_signed<DeletedVirtualPrivateDestructor>();
    //test_make_signed<Enum>();
    //test_make_signed<EnumSigned>();
    //test_make_signed<EnumUnsigned>();
    //test_make_signed<EnumClass>();
    //test_make_signed<EnumStruct>();
    test_make_signed<Function>();
    test_make_signed<FunctionPtr>();
    test_make_signed<MemberObjectPtr>();
    test_make_signed<MemberFunctionPtr>();
    test_make_signed<incomplete_type>();
    test_make_signed<IncompleteTemplate<void>>();
    test_make_signed<IncompleteTemplate<int>>();
    test_make_signed<IncompleteTemplate<Class>>();
    test_make_signed<IncompleteTemplate<incomplete_type>>();
    test_make_signed<IncompleteVariadicTemplate<>>();
    test_make_signed<IncompleteVariadicTemplate<void>>();
    test_make_signed<IncompleteVariadicTemplate<int>>();
    test_make_signed<IncompleteVariadicTemplate<Class>>();
    test_make_signed<IncompleteVariadicTemplate<incomplete_type>>();
    test_make_signed<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_make_signed<int Class::*>();
    test_make_signed<float Class::*>();
    test_make_signed<void * Class::*>();
    test_make_signed<int * Class::*>();
    test_make_signed<int Class::*&>();
    test_make_signed<float Class::*&>();
    test_make_signed<void * Class::*&>();
    test_make_signed<int * Class::*&>();
    test_make_signed<int Class::*&&>();
    test_make_signed<float Class::*&&>();
    test_make_signed<void * Class::*&&>();
    test_make_signed<int * Class::*&&>();
    test_make_signed<int Class::*const>();
    test_make_signed<float Class::*const>();
    test_make_signed<void * Class::*const>();
    test_make_signed<int Class::*const&>();
    test_make_signed<float Class::*const&>();
    test_make_signed<void * Class::*const&>();
    test_make_signed<int Class::*const&&>();
    test_make_signed<float Class::*const&&>();
    test_make_signed<void * Class::*const&&>();
    test_make_signed<int Class::*volatile>();
    test_make_signed<float Class::*volatile>();
    test_make_signed<void * Class::*volatile>();
    test_make_signed<int Class::*volatile&>();
    test_make_signed<float Class::*volatile&>();
    test_make_signed<void * Class::*volatile&>();
    test_make_signed<int Class::*volatile&&>();
    test_make_signed<float Class::*volatile&&>();
    test_make_signed<void * Class::*volatile&&>();
    test_make_signed<int Class::*const volatile>();
    test_make_signed<float Class::*const volatile>();
    test_make_signed<void * Class::*const volatile>();
    test_make_signed<int Class::*const volatile&>();
    test_make_signed<float Class::*const volatile&>();
    test_make_signed<void * Class::*const volatile&>();
    test_make_signed<int Class::*const volatile&&>();
    test_make_signed<float Class::*const volatile&&>();
    test_make_signed<void * Class::*const volatile&&>();
    test_make_signed<NonCopyable>();
    test_make_signed<NonMoveable>();
    test_make_signed<NonConstructible>();
    test_make_signed<Tracked>();
    test_make_signed<TrapConstructible>();
    test_make_signed<TrapImplicitConversion>();
    test_make_signed<TrapComma>();
    test_make_signed<TrapCall>();
    test_make_signed<TrapSelfAssign>();
    test_make_signed<TrapDeref>();
    test_make_signed<TrapArraySubscript>();

    test_make_signed<void()>();
    test_make_signed<void()&>();
    test_make_signed<void() &&>();
    test_make_signed<void() const>();
    test_make_signed<void() const&>();
    test_make_signed<void() const&&>();
    test_make_signed<void() volatile>();
    test_make_signed<void() volatile&>();
    test_make_signed<void() volatile&&>();
    test_make_signed<void() const volatile>();
    test_make_signed<void() const volatile&>();
    test_make_signed<void() const volatile&&>();
    test_make_signed<void() noexcept>();
    test_make_signed<void()& noexcept>();
    test_make_signed<void()&& noexcept>();
    test_make_signed<void() const noexcept>();
    test_make_signed<void() const& noexcept>();
    test_make_signed<void() const&& noexcept>();
    test_make_signed<void() volatile noexcept>();
    test_make_signed<void() volatile& noexcept>();
    test_make_signed<void() volatile&& noexcept>();
    test_make_signed<void() const volatile noexcept>();
    test_make_signed<void() const volatile& noexcept>();
    test_make_signed<void() const volatile&& noexcept>();

    test_make_signed<void(int)>();
    test_make_signed<void(int)&>();
    test_make_signed<void(int) &&>();
    test_make_signed<void(int) const>();
    test_make_signed<void(int) const&>();
    test_make_signed<void(int) const&&>();
    test_make_signed<void(int) volatile>();
    test_make_signed<void(int) volatile&>();
    test_make_signed<void(int) volatile&&>();
    test_make_signed<void(int) const volatile>();
    test_make_signed<void(int) const volatile&>();
    test_make_signed<void(int) const volatile&&>();
    test_make_signed<void(int) noexcept>();
    test_make_signed<void(int)& noexcept>();
    test_make_signed<void(int)&& noexcept>();
    test_make_signed<void(int) const noexcept>();
    test_make_signed<void(int) const& noexcept>();
    test_make_signed<void(int) const&& noexcept>();
    test_make_signed<void(int) volatile noexcept>();
    test_make_signed<void(int) volatile& noexcept>();
    test_make_signed<void(int) volatile&& noexcept>();
    test_make_signed<void(int) const volatile noexcept>();
    test_make_signed<void(int) const volatile& noexcept>();
    test_make_signed<void(int) const volatile&& noexcept>();

    test_make_signed<void(...)>();
    test_make_signed<void(...)&>();
    test_make_signed<void(...) &&>();
    test_make_signed<void(...) const>();
    test_make_signed<void(...) const&>();
    test_make_signed<void(...) const&&>();
    test_make_signed<void(...) volatile>();
    test_make_signed<void(...) volatile&>();
    test_make_signed<void(...) volatile&&>();
    test_make_signed<void(...) const volatile>();
    test_make_signed<void(...) const volatile&>();
    test_make_signed<void(...) const volatile&&>();
    test_make_signed<void(...) noexcept>();
    test_make_signed<void(...)& noexcept>();
    test_make_signed<void(...)&& noexcept>();
    test_make_signed<void(...) const noexcept>();
    test_make_signed<void(...) const& noexcept>();
    test_make_signed<void(...) const&& noexcept>();
    test_make_signed<void(...) volatile noexcept>();
    test_make_signed<void(...) volatile& noexcept>();
    test_make_signed<void(...) volatile&& noexcept>();
    test_make_signed<void(...) const volatile noexcept>();
    test_make_signed<void(...) const volatile& noexcept>();
    test_make_signed<void(...) const volatile&& noexcept>();

    test_make_signed<void(int, ...)>();
    test_make_signed<void(int, ...)&>();
    test_make_signed<void(int, ...) &&>();
    test_make_signed<void(int, ...) const>();
    test_make_signed<void(int, ...) const&>();
    test_make_signed<void(int, ...) const&&>();
    test_make_signed<void(int, ...) volatile>();
    test_make_signed<void(int, ...) volatile&>();
    test_make_signed<void(int, ...) volatile&&>();
    test_make_signed<void(int, ...) const volatile>();
    test_make_signed<void(int, ...) const volatile&>();
    test_make_signed<void(int, ...) const volatile&&>();
    test_make_signed<void(int, ...) noexcept>();
    test_make_signed<void(int, ...)& noexcept>();
    test_make_signed<void(int, ...)&& noexcept>();
    test_make_signed<void(int, ...) const noexcept>();
    test_make_signed<void(int, ...) const& noexcept>();
    test_make_signed<void(int, ...) const&& noexcept>();
    test_make_signed<void(int, ...) volatile noexcept>();
    test_make_signed<void(int, ...) volatile& noexcept>();
    test_make_signed<void(int, ...) volatile&& noexcept>();
    test_make_signed<void(int, ...) const volatile noexcept>();
    test_make_signed<void(int, ...) const volatile& noexcept>();
    test_make_signed<void(int, ...) const volatile&& noexcept>();

    test_make_signed<int()>();
    test_make_signed<int()&>();
    test_make_signed<int() &&>();
    test_make_signed<int() const>();
    test_make_signed<int() const&>();
    test_make_signed<int() const&&>();
    test_make_signed<int() volatile>();
    test_make_signed<int() volatile&>();
    test_make_signed<int() volatile&&>();
    test_make_signed<int() const volatile>();
    test_make_signed<int() const volatile&>();
    test_make_signed<int() const volatile&&>();
    test_make_signed<int() noexcept>();
    test_make_signed<int()& noexcept>();
    test_make_signed<int()&& noexcept>();
    test_make_signed<int() const noexcept>();
    test_make_signed<int() const& noexcept>();
    test_make_signed<int() const&& noexcept>();
    test_make_signed<int() volatile noexcept>();
    test_make_signed<int() volatile& noexcept>();
    test_make_signed<int() volatile&& noexcept>();
    test_make_signed<int() const volatile noexcept>();
    test_make_signed<int() const volatile& noexcept>();
    test_make_signed<int() const volatile&& noexcept>();

    test_make_signed<int(int)>();
    test_make_signed<int(int)&>();
    test_make_signed<int(int) &&>();
    test_make_signed<int(int) const>();
    test_make_signed<int(int) const&>();
    test_make_signed<int(int) const&&>();
    test_make_signed<int(int) volatile>();
    test_make_signed<int(int) volatile&>();
    test_make_signed<int(int) volatile&&>();
    test_make_signed<int(int) const volatile>();
    test_make_signed<int(int) const volatile&>();
    test_make_signed<int(int) const volatile&&>();
    test_make_signed<int(int) noexcept>();
    test_make_signed<int(int)& noexcept>();
    test_make_signed<int(int)&& noexcept>();
    test_make_signed<int(int) const noexcept>();
    test_make_signed<int(int) const& noexcept>();
    test_make_signed<int(int) const&& noexcept>();
    test_make_signed<int(int) volatile noexcept>();
    test_make_signed<int(int) volatile& noexcept>();
    test_make_signed<int(int) volatile&& noexcept>();
    test_make_signed<int(int) const volatile noexcept>();
    test_make_signed<int(int) const volatile& noexcept>();
    test_make_signed<int(int) const volatile&& noexcept>();

    test_make_signed<int(...)>();
    test_make_signed<int(...)&>();
    test_make_signed<int(...) &&>();
    test_make_signed<int(...) const>();
    test_make_signed<int(...) const&>();
    test_make_signed<int(...) const&&>();
    test_make_signed<int(...) volatile>();
    test_make_signed<int(...) volatile&>();
    test_make_signed<int(...) volatile&&>();
    test_make_signed<int(...) const volatile>();
    test_make_signed<int(...) const volatile&>();
    test_make_signed<int(...) const volatile&&>();
    test_make_signed<int(...) noexcept>();
    test_make_signed<int(...)& noexcept>();
    test_make_signed<int(...)&& noexcept>();
    test_make_signed<int(...) const noexcept>();
    test_make_signed<int(...) const& noexcept>();
    test_make_signed<int(...) const&& noexcept>();
    test_make_signed<int(...) volatile noexcept>();
    test_make_signed<int(...) volatile& noexcept>();
    test_make_signed<int(...) volatile&& noexcept>();
    test_make_signed<int(...) const volatile noexcept>();
    test_make_signed<int(...) const volatile& noexcept>();
    test_make_signed<int(...) const volatile&& noexcept>();

    test_make_signed<int(int, ...)>();
    test_make_signed<int(int, ...)&>();
    test_make_signed<int(int, ...) &&>();
    test_make_signed<int(int, ...) const>();
    test_make_signed<int(int, ...) const&>();
    test_make_signed<int(int, ...) const&&>();
    test_make_signed<int(int, ...) volatile>();
    test_make_signed<int(int, ...) volatile&>();
    test_make_signed<int(int, ...) volatile&&>();
    test_make_signed<int(int, ...) const volatile>();
    test_make_signed<int(int, ...) const volatile&>();
    test_make_signed<int(int, ...) const volatile&&>();
    test_make_signed<int(int, ...) noexcept>();
    test_make_signed<int(int, ...)& noexcept>();
    test_make_signed<int(int, ...)&& noexcept>();
    test_make_signed<int(int, ...) const noexcept>();
    test_make_signed<int(int, ...) const& noexcept>();
    test_make_signed<int(int, ...) const&& noexcept>();
    test_make_signed<int(int, ...) volatile noexcept>();
    test_make_signed<int(int, ...) volatile& noexcept>();
    test_make_signed<int(int, ...) volatile&& noexcept>();
    test_make_signed<int(int, ...) const volatile noexcept>();
    test_make_signed<int(int, ...) const volatile& noexcept>();
    test_make_signed<int(int, ...) const volatile&& noexcept>();

    test_make_signed<void (*)()>();
    test_make_signed<void (*)() noexcept>();

    test_make_signed<void (*)(int)>();
    test_make_signed<void (*)(int) noexcept>();

    test_make_signed<void (*)(...)>();
    test_make_signed<void (*)(...) noexcept>();

    test_make_signed<void (*)(int, ...)>();
    test_make_signed<void (*)(int, ...) noexcept>();

    test_make_signed<int (*)()>();
    test_make_signed<int (*)() noexcept>();

    test_make_signed<int (*)(int)>();
    test_make_signed<int (*)(int) noexcept>();

    test_make_signed<int (*)(...)>();
    test_make_signed<int (*)(...) noexcept>();

    test_make_signed<int (*)(int, ...)>();
    test_make_signed<int (*)(int, ...) noexcept>();

    test_make_signed<void (&)()>();
    test_make_signed<void (&)() noexcept>();

    test_make_signed<void (&)(int)>();
    test_make_signed<void (&)(int) noexcept>();

    test_make_signed<void (&)(...)>();
    test_make_signed<void (&)(...) noexcept>();

    test_make_signed<void (&)(int, ...)>();
    test_make_signed<void (&)(int, ...) noexcept>();

    test_make_signed<int (&)()>();
    test_make_signed<int (&)() noexcept>();

    test_make_signed<int (&)(int)>();
    test_make_signed<int (&)(int) noexcept>();

    test_make_signed<int (&)(...)>();
    test_make_signed<int (&)(...) noexcept>();

    test_make_signed<int (&)(int, ...)>();
    test_make_signed<int (&)(int, ...) noexcept>();

    test_make_signed<void(&&)()>();
    test_make_signed<void(&&)() noexcept>();

    test_make_signed<void(&&)(int)>();
    test_make_signed<void(&&)(int) noexcept>();

    test_make_signed<void(&&)(...)>();
    test_make_signed<void(&&)(...) noexcept>();

    test_make_signed<void(&&)(int, ...)>();
    test_make_signed<void(&&)(int, ...) noexcept>();

    test_make_signed<int(&&)()>();
    test_make_signed<int(&&)() noexcept>();

    test_make_signed<int(&&)(int)>();
    test_make_signed<int(&&)(int) noexcept>();

    test_make_signed<int(&&)(...)>();
    test_make_signed<int(&&)(...) noexcept>();

    test_make_signed<int(&&)(int, ...)>();
    test_make_signed<int(&&)(int, ...) noexcept>();

    test_make_signed<void (Class::*)()>();
    test_make_signed<void (Class::*)()&>();
    test_make_signed<void (Class::*)() &&>();
    test_make_signed<void (Class::*)() const>();
    test_make_signed<void (Class::*)() const&>();
    test_make_signed<void (Class::*)() const&&>();
    test_make_signed<void (Class::*)() noexcept>();
    test_make_signed<void (Class::*)()& noexcept>();
    test_make_signed<void (Class::*)()&& noexcept>();
    test_make_signed<void (Class::*)() const noexcept>();
    test_make_signed<void (Class::*)() const& noexcept>();
    test_make_signed<void (Class::*)() const&& noexcept>();

    test_make_signed<void (Class::*)(int)>();
    test_make_signed<void (Class::*)(int)&>();
    test_make_signed<void (Class::*)(int) &&>();
    test_make_signed<void (Class::*)(int) const>();
    test_make_signed<void (Class::*)(int) const&>();
    test_make_signed<void (Class::*)(int) const&&>();
    test_make_signed<void (Class::*)(int) noexcept>();
    test_make_signed<void (Class::*)(int)& noexcept>();
    test_make_signed<void (Class::*)(int)&& noexcept>();
    test_make_signed<void (Class::*)(int) const noexcept>();
    test_make_signed<void (Class::*)(int) const& noexcept>();
    test_make_signed<void (Class::*)(int) const&& noexcept>();

    test_make_signed<void (Class::*)(...)>();
    test_make_signed<void (Class::*)(...)&>();
    test_make_signed<void (Class::*)(...) &&>();
    test_make_signed<void (Class::*)(...) const>();
    test_make_signed<void (Class::*)(...) const&>();
    test_make_signed<void (Class::*)(...) const&&>();
    test_make_signed<void (Class::*)(...) noexcept>();
    test_make_signed<void (Class::*)(...)& noexcept>();
    test_make_signed<void (Class::*)(...)&& noexcept>();
    test_make_signed<void (Class::*)(...) const noexcept>();
    test_make_signed<void (Class::*)(...) const& noexcept>();
    test_make_signed<void (Class::*)(...) const&& noexcept>();

    test_make_signed<void (Class::*)(int, ...)>();
    test_make_signed<void (Class::*)(int, ...)&>();
    test_make_signed<void (Class::*)(int, ...) &&>();
    test_make_signed<void (Class::*)(int, ...) const>();
    test_make_signed<void (Class::*)(int, ...) const&>();
    test_make_signed<void (Class::*)(int, ...) const&&>();
    test_make_signed<void (Class::*)(int, ...) noexcept>();
    test_make_signed<void (Class::*)(int, ...)& noexcept>();
    test_make_signed<void (Class::*)(int, ...)&& noexcept>();
    test_make_signed<void (Class::*)(int, ...) const noexcept>();
    test_make_signed<void (Class::*)(int, ...) const& noexcept>();
    test_make_signed<void (Class::*)(int, ...) const&& noexcept>();

    test_make_signed<int (Class::*)()>();
    test_make_signed<int (Class::*)()&>();
    test_make_signed<int (Class::*)() &&>();
    test_make_signed<int (Class::*)() const>();
    test_make_signed<int (Class::*)() const&>();
    test_make_signed<int (Class::*)() const&&>();
    test_make_signed<int (Class::*)() noexcept>();
    test_make_signed<int (Class::*)()& noexcept>();
    test_make_signed<int (Class::*)()&& noexcept>();
    test_make_signed<int (Class::*)() const noexcept>();
    test_make_signed<int (Class::*)() const& noexcept>();
    test_make_signed<int (Class::*)() const&& noexcept>();

    test_make_signed<int (Class::*)(int)>();
    test_make_signed<int (Class::*)(int)&>();
    test_make_signed<int (Class::*)(int) &&>();
    test_make_signed<int (Class::*)(int) const>();
    test_make_signed<int (Class::*)(int) const&>();
    test_make_signed<int (Class::*)(int) const&&>();
    test_make_signed<int (Class::*)(int) noexcept>();
    test_make_signed<int (Class::*)(int)& noexcept>();
    test_make_signed<int (Class::*)(int)&& noexcept>();
    test_make_signed<int (Class::*)(int) const noexcept>();
    test_make_signed<int (Class::*)(int) const& noexcept>();
    test_make_signed<int (Class::*)(int) const&& noexcept>();

    test_make_signed<int (Class::*)(...)>();
    test_make_signed<int (Class::*)(...)&>();
    test_make_signed<int (Class::*)(...) &&>();
    test_make_signed<int (Class::*)(...) const>();
    test_make_signed<int (Class::*)(...) const&>();
    test_make_signed<int (Class::*)(...) const&&>();
    test_make_signed<int (Class::*)(...) noexcept>();
    test_make_signed<int (Class::*)(...)& noexcept>();
    test_make_signed<int (Class::*)(...)&& noexcept>();
    test_make_signed<int (Class::*)(...) const noexcept>();
    test_make_signed<int (Class::*)(...) const& noexcept>();
    test_make_signed<int (Class::*)(...) const&& noexcept>();

    test_make_signed<int (Class::*)(int, ...)>();
    test_make_signed<int (Class::*)(int, ...)&>();
    test_make_signed<int (Class::*)(int, ...) &&>();
    test_make_signed<int (Class::*)(int, ...) const>();
    test_make_signed<int (Class::*)(int, ...) const&>();
    test_make_signed<int (Class::*)(int, ...) const&&>();
    test_make_signed<int (Class::*)(int, ...) noexcept>();
    test_make_signed<int (Class::*)(int, ...)& noexcept>();
    test_make_signed<int (Class::*)(int, ...)&& noexcept>();
    test_make_signed<int (Class::*)(int, ...) const noexcept>();
    test_make_signed<int (Class::*)(int, ...) const& noexcept>();
    test_make_signed<int (Class::*)(int, ...) const&& noexcept>();
}
