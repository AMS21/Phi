#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/remove_volatile.hpp>
#include <vector>

template <typename T, typename U>
void test_remove_volatile_impl()
{
    CHECK_SAME_TYPE(typename phi::remove_volatile<T>::type, U);
    CHECK_SAME_TYPE(phi::remove_volatile_t<T>, U);

    // Standard compatibililty
    CHECK_SAME_TYPE(typename std::remove_volatile<T>::type, U);
}

template <typename T, typename U = T>
void test_remove_volatile()
{
    test_remove_volatile_impl<T, U>();
    test_remove_volatile_impl<const T, const U>();
    test_remove_volatile_impl<volatile T, U>();
    test_remove_volatile_impl<const volatile T, const U>();
}

TEST_CASE("remove_volatile")
{
    test_remove_volatile<void>();
    test_remove_volatile<phi::nullptr_t>();
    test_remove_volatile<bool>();
    test_remove_volatile<char>();
    test_remove_volatile<signed char>();
    test_remove_volatile<unsigned char>();
    test_remove_volatile<short>();
    test_remove_volatile<unsigned short>();
    test_remove_volatile<int>();
    test_remove_volatile<unsigned int>();
    test_remove_volatile<long>();
    test_remove_volatile<unsigned long>();
    test_remove_volatile<long long>();
    test_remove_volatile<unsigned long long>();
    test_remove_volatile<float>();
    test_remove_volatile<double>();
    test_remove_volatile<long double>();
    test_remove_volatile<char8_t>();
    test_remove_volatile<char16_t>();
    test_remove_volatile<char32_t>();
    test_remove_volatile<wchar_t>();

    test_remove_volatile<phi::boolean>();
    test_remove_volatile<phi::integer<signed char>>();
    test_remove_volatile<phi::integer<unsigned char>>();
    test_remove_volatile<phi::integer<short>>();
    test_remove_volatile<phi::integer<unsigned short>>();
    test_remove_volatile<phi::integer<int>>();
    test_remove_volatile<phi::integer<unsigned int>>();
    test_remove_volatile<phi::integer<long>>();
    test_remove_volatile<phi::integer<unsigned long>>();
    test_remove_volatile<phi::integer<long long>>();
    test_remove_volatile<phi::integer<unsigned long long>>();
    test_remove_volatile<phi::floating_point<float>>();
    test_remove_volatile<phi::floating_point<double>>();
    test_remove_volatile<phi::floating_point<long double>>();

    test_remove_volatile<std::vector<int>>();
    test_remove_volatile<phi::scope_ptr<int>>();

    test_remove_volatile<int&>();
    test_remove_volatile<const int&>();
    test_remove_volatile<volatile int&>();
    test_remove_volatile<const volatile int&>();
    test_remove_volatile<int&&>();
    test_remove_volatile<const int&&>();
    test_remove_volatile<volatile int&&>();
    test_remove_volatile<const volatile int&&>();
    test_remove_volatile<int*>();
    test_remove_volatile<const int*>();
    test_remove_volatile<volatile int*>();
    test_remove_volatile<const volatile int*>();
    test_remove_volatile<int**>();
    test_remove_volatile<const int**>();
    test_remove_volatile<volatile int**>();
    test_remove_volatile<const volatile int**>();
    test_remove_volatile<int*&>();
    test_remove_volatile<const int*&>();
    test_remove_volatile<volatile int*&>();
    test_remove_volatile<const volatile int*&>();
    test_remove_volatile<int*&&>();
    test_remove_volatile<const int*&&>();
    test_remove_volatile<volatile int*&&>();
    test_remove_volatile<const volatile int*&&>();
    test_remove_volatile<void*>();
    test_remove_volatile<char[3]>();
    test_remove_volatile<char[]>();
    test_remove_volatile<char* [3]>();
    test_remove_volatile<char*[]>();
    test_remove_volatile<int(*)[3]>();
    test_remove_volatile<int(*)[]>();
    test_remove_volatile<int(&)[3]>();
    test_remove_volatile<int(&)[]>();
    test_remove_volatile<int(&&)[3]>();
    test_remove_volatile<int(&&)[]>();
    test_remove_volatile<char[3][2]>();
    test_remove_volatile<char[][2]>();
    test_remove_volatile<char* [3][2]>();
    test_remove_volatile<char*[][2]>();
    test_remove_volatile<int(*)[3][2]>();
    test_remove_volatile<int(*)[][2]>();
    test_remove_volatile<int(&)[3][2]>();
    test_remove_volatile<int(&)[][2]>();
    test_remove_volatile<int(&&)[3][2]>();
    test_remove_volatile<int(&&)[][2]>();
    test_remove_volatile<Class>();
    test_remove_volatile<Class[]>();
    test_remove_volatile<Class[2]>();
    test_remove_volatile<Template<void>>();
    test_remove_volatile<Template<int>>();
    test_remove_volatile<Template<Class>>();
    test_remove_volatile<Template<IncompleteType>>();
    test_remove_volatile<VariadicTemplate<>>();
    test_remove_volatile<VariadicTemplate<void>>();
    test_remove_volatile<VariadicTemplate<int>>();
    test_remove_volatile<VariadicTemplate<Class>>();
    test_remove_volatile<VariadicTemplate<IncompleteType>>();
    test_remove_volatile<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_remove_volatile<PublicDerivedFromTemplate<Base>>();
    test_remove_volatile<PublicDerivedFromTemplate<Derived>>();
    test_remove_volatile<PublicDerivedFromTemplate<Class>>();
    test_remove_volatile<PrivateDerivedFromTemplate<Base>>();
    test_remove_volatile<PrivateDerivedFromTemplate<Derived>>();
    test_remove_volatile<PrivateDerivedFromTemplate<Class>>();
    test_remove_volatile<ProtectedDerivedFromTemplate<Base>>();
    test_remove_volatile<ProtectedDerivedFromTemplate<Derived>>();
    test_remove_volatile<ProtectedDerivedFromTemplate<Class>>();
    test_remove_volatile<Union>();
    test_remove_volatile<NonEmptyUnion>();
    test_remove_volatile<Empty>();
    test_remove_volatile<NotEmpty>();
    test_remove_volatile<BitZero>();
    test_remove_volatile<BitOne>();
    test_remove_volatile<Base>();
    test_remove_volatile<Derived>();
    test_remove_volatile<Abstract>();
    test_remove_volatile<PublicAbstract>();
    test_remove_volatile<PrivateAbstract>();
    test_remove_volatile<ProtectedAbstract>();
    test_remove_volatile<AbstractTemplate<int>>();
    test_remove_volatile<AbstractTemplate<double>>();
    test_remove_volatile<AbstractTemplate<Class>>();
    test_remove_volatile<AbstractTemplate<IncompleteType>>();
    test_remove_volatile<Final>();
    test_remove_volatile<PublicDestructor>();
    test_remove_volatile<ProtectedDestructor>();
    test_remove_volatile<PrivateDestructor>();
    test_remove_volatile<VirtualPublicDestructor>();
    test_remove_volatile<VirtualProtectedDestructor>();
    test_remove_volatile<VirtualPrivateDestructor>();
    test_remove_volatile<PurePublicDestructor>();
    test_remove_volatile<PureProtectedDestructor>();
    test_remove_volatile<PurePrivateDestructor>();
    test_remove_volatile<DeletedPublicDestructor>();
    test_remove_volatile<DeletedProtectedDestructor>();
    test_remove_volatile<DeletedPrivateDestructor>();
    test_remove_volatile<DeletedVirtualPublicDestructor>();
    test_remove_volatile<DeletedVirtualProtectedDestructor>();
    test_remove_volatile<DeletedVirtualPrivateDestructor>();
    test_remove_volatile<Enum>();
    test_remove_volatile<EnumSigned>();
    test_remove_volatile<EnumUnsigned>();
    test_remove_volatile<EnumClass>();
    test_remove_volatile<EnumStruct>();
    test_remove_volatile<Function>();
    test_remove_volatile<FunctionPtr>();
    test_remove_volatile<MemberObjectPtr>();
    test_remove_volatile<MemberFunctionPtr>();
    test_remove_volatile<IncompleteType>();
    test_remove_volatile<IncompleteTemplate<void>>();
    test_remove_volatile<IncompleteTemplate<int>>();
    test_remove_volatile<IncompleteTemplate<Class>>();
    test_remove_volatile<IncompleteTemplate<IncompleteType>>();
    test_remove_volatile<IncompleteVariadicTemplate<>>();
    test_remove_volatile<IncompleteVariadicTemplate<void>>();
    test_remove_volatile<IncompleteVariadicTemplate<int>>();
    test_remove_volatile<IncompleteVariadicTemplate<Class>>();
    test_remove_volatile<IncompleteVariadicTemplate<IncompleteType>>();
    test_remove_volatile<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_remove_volatile<int Class::*>();
    test_remove_volatile<float Class::*>();
    test_remove_volatile<void * Class::*>();
    test_remove_volatile<int * Class::*>();
    test_remove_volatile<int Class::*&>();
    test_remove_volatile<float Class::*&>();
    test_remove_volatile<void * Class::*&>();
    test_remove_volatile<int * Class::*&>();
    test_remove_volatile<int Class::*&&>();
    test_remove_volatile<float Class::*&&>();
    test_remove_volatile<void * Class::*&&>();
    test_remove_volatile<int * Class::*&&>();
    test_remove_volatile<int Class::*const>();
    test_remove_volatile<float Class::*const>();
    test_remove_volatile<void * Class::*const>();
    test_remove_volatile<int Class::*const&>();
    test_remove_volatile<float Class::*const&>();
    test_remove_volatile<void * Class::*const&>();
    test_remove_volatile<int Class::*const&&>();
    test_remove_volatile<float Class::*const&&>();
    test_remove_volatile<void * Class::*const&&>();
    test_remove_volatile<int Class::*volatile, int Class::*>();
    test_remove_volatile<float Class::*volatile, float Class::*>();
    test_remove_volatile<void * Class::*volatile, void * Class::*>();
    test_remove_volatile<int Class::*volatile&>();
    test_remove_volatile<float Class::*volatile&>();
    test_remove_volatile<void * Class::*volatile&>();
    test_remove_volatile<int Class::*volatile&&>();
    test_remove_volatile<float Class::*volatile&&>();
    test_remove_volatile<void * Class::*volatile&&>();
    test_remove_volatile<int Class::*const volatile, int Class::*const>();
    test_remove_volatile<float Class::*const volatile, float Class::*const>();
    test_remove_volatile<void * Class::*const volatile, void * Class::*const>();
    test_remove_volatile<int Class::*const volatile&>();
    test_remove_volatile<float Class::*const volatile&>();
    test_remove_volatile<void * Class::*const volatile&>();
    test_remove_volatile<int Class::*const volatile&&>();
    test_remove_volatile<float Class::*const volatile&&>();
    test_remove_volatile<void * Class::*const volatile&&>();
    test_remove_volatile<NonCopyable>();
    test_remove_volatile<NonMoveable>();
    test_remove_volatile<NonConstructible>();
    test_remove_volatile<Tracked>();
    test_remove_volatile<TrapConstructible>();
    test_remove_volatile<TrapImplicitConversion>();
    test_remove_volatile<TrapComma>();
    test_remove_volatile<TrapCall>();
    test_remove_volatile<TrapSelfAssign>();
    test_remove_volatile<TrapDeref>();
    test_remove_volatile<TrapArraySubscript>();

    test_remove_volatile<void()>();
    test_remove_volatile<void()&>();
    test_remove_volatile<void() &&>();
    test_remove_volatile<void() const>();
    test_remove_volatile<void() const&>();
    test_remove_volatile<void() const&&>();
    test_remove_volatile<void() volatile>();
    test_remove_volatile<void() volatile&>();
    test_remove_volatile<void() volatile&&>();
    test_remove_volatile<void() const volatile>();
    test_remove_volatile<void() const volatile&>();
    test_remove_volatile<void() const volatile&&>();
    test_remove_volatile<void() noexcept>();
    test_remove_volatile<void()& noexcept>();
    test_remove_volatile<void()&& noexcept>();
    test_remove_volatile<void() const noexcept>();
    test_remove_volatile<void() const& noexcept>();
    test_remove_volatile<void() const&& noexcept>();
    test_remove_volatile<void() volatile noexcept>();
    test_remove_volatile<void() volatile& noexcept>();
    test_remove_volatile<void() volatile&& noexcept>();
    test_remove_volatile<void() const volatile noexcept>();
    test_remove_volatile<void() const volatile& noexcept>();
    test_remove_volatile<void() const volatile&& noexcept>();

    test_remove_volatile<void(int)>();
    test_remove_volatile<void(int)&>();
    test_remove_volatile<void(int) &&>();
    test_remove_volatile<void(int) const>();
    test_remove_volatile<void(int) const&>();
    test_remove_volatile<void(int) const&&>();
    test_remove_volatile<void(int) volatile>();
    test_remove_volatile<void(int) volatile&>();
    test_remove_volatile<void(int) volatile&&>();
    test_remove_volatile<void(int) const volatile>();
    test_remove_volatile<void(int) const volatile&>();
    test_remove_volatile<void(int) const volatile&&>();
    test_remove_volatile<void(int) noexcept>();
    test_remove_volatile<void(int)& noexcept>();
    test_remove_volatile<void(int)&& noexcept>();
    test_remove_volatile<void(int) const noexcept>();
    test_remove_volatile<void(int) const& noexcept>();
    test_remove_volatile<void(int) const&& noexcept>();
    test_remove_volatile<void(int) volatile noexcept>();
    test_remove_volatile<void(int) volatile& noexcept>();
    test_remove_volatile<void(int) volatile&& noexcept>();
    test_remove_volatile<void(int) const volatile noexcept>();
    test_remove_volatile<void(int) const volatile& noexcept>();
    test_remove_volatile<void(int) const volatile&& noexcept>();

    test_remove_volatile<void(...)>();
    test_remove_volatile<void(...)&>();
    test_remove_volatile<void(...) &&>();
    test_remove_volatile<void(...) const>();
    test_remove_volatile<void(...) const&>();
    test_remove_volatile<void(...) const&&>();
    test_remove_volatile<void(...) volatile>();
    test_remove_volatile<void(...) volatile&>();
    test_remove_volatile<void(...) volatile&&>();
    test_remove_volatile<void(...) const volatile>();
    test_remove_volatile<void(...) const volatile&>();
    test_remove_volatile<void(...) const volatile&&>();
    test_remove_volatile<void(...) noexcept>();
    test_remove_volatile<void(...)& noexcept>();
    test_remove_volatile<void(...)&& noexcept>();
    test_remove_volatile<void(...) const noexcept>();
    test_remove_volatile<void(...) const& noexcept>();
    test_remove_volatile<void(...) const&& noexcept>();
    test_remove_volatile<void(...) volatile noexcept>();
    test_remove_volatile<void(...) volatile& noexcept>();
    test_remove_volatile<void(...) volatile&& noexcept>();
    test_remove_volatile<void(...) const volatile noexcept>();
    test_remove_volatile<void(...) const volatile& noexcept>();
    test_remove_volatile<void(...) const volatile&& noexcept>();

    test_remove_volatile<void(int, ...)>();
    test_remove_volatile<void(int, ...)&>();
    test_remove_volatile<void(int, ...) &&>();
    test_remove_volatile<void(int, ...) const>();
    test_remove_volatile<void(int, ...) const&>();
    test_remove_volatile<void(int, ...) const&&>();
    test_remove_volatile<void(int, ...) volatile>();
    test_remove_volatile<void(int, ...) volatile&>();
    test_remove_volatile<void(int, ...) volatile&&>();
    test_remove_volatile<void(int, ...) const volatile>();
    test_remove_volatile<void(int, ...) const volatile&>();
    test_remove_volatile<void(int, ...) const volatile&&>();
    test_remove_volatile<void(int, ...) noexcept>();
    test_remove_volatile<void(int, ...)& noexcept>();
    test_remove_volatile<void(int, ...)&& noexcept>();
    test_remove_volatile<void(int, ...) const noexcept>();
    test_remove_volatile<void(int, ...) const& noexcept>();
    test_remove_volatile<void(int, ...) const&& noexcept>();
    test_remove_volatile<void(int, ...) volatile noexcept>();
    test_remove_volatile<void(int, ...) volatile& noexcept>();
    test_remove_volatile<void(int, ...) volatile&& noexcept>();
    test_remove_volatile<void(int, ...) const volatile noexcept>();
    test_remove_volatile<void(int, ...) const volatile& noexcept>();
    test_remove_volatile<void(int, ...) const volatile&& noexcept>();

    test_remove_volatile<int()>();
    test_remove_volatile<int()&>();
    test_remove_volatile<int() &&>();
    test_remove_volatile<int() const>();
    test_remove_volatile<int() const&>();
    test_remove_volatile<int() const&&>();
    test_remove_volatile<int() volatile>();
    test_remove_volatile<int() volatile&>();
    test_remove_volatile<int() volatile&&>();
    test_remove_volatile<int() const volatile>();
    test_remove_volatile<int() const volatile&>();
    test_remove_volatile<int() const volatile&&>();
    test_remove_volatile<int() noexcept>();
    test_remove_volatile<int()& noexcept>();
    test_remove_volatile<int()&& noexcept>();
    test_remove_volatile<int() const noexcept>();
    test_remove_volatile<int() const& noexcept>();
    test_remove_volatile<int() const&& noexcept>();
    test_remove_volatile<int() volatile noexcept>();
    test_remove_volatile<int() volatile& noexcept>();
    test_remove_volatile<int() volatile&& noexcept>();
    test_remove_volatile<int() const volatile noexcept>();
    test_remove_volatile<int() const volatile& noexcept>();
    test_remove_volatile<int() const volatile&& noexcept>();

    test_remove_volatile<int(int)>();
    test_remove_volatile<int(int)&>();
    test_remove_volatile<int(int) &&>();
    test_remove_volatile<int(int) const>();
    test_remove_volatile<int(int) const&>();
    test_remove_volatile<int(int) const&&>();
    test_remove_volatile<int(int) volatile>();
    test_remove_volatile<int(int) volatile&>();
    test_remove_volatile<int(int) volatile&&>();
    test_remove_volatile<int(int) const volatile>();
    test_remove_volatile<int(int) const volatile&>();
    test_remove_volatile<int(int) const volatile&&>();
    test_remove_volatile<int(int) noexcept>();
    test_remove_volatile<int(int)& noexcept>();
    test_remove_volatile<int(int)&& noexcept>();
    test_remove_volatile<int(int) const noexcept>();
    test_remove_volatile<int(int) const& noexcept>();
    test_remove_volatile<int(int) const&& noexcept>();
    test_remove_volatile<int(int) volatile noexcept>();
    test_remove_volatile<int(int) volatile& noexcept>();
    test_remove_volatile<int(int) volatile&& noexcept>();
    test_remove_volatile<int(int) const volatile noexcept>();
    test_remove_volatile<int(int) const volatile& noexcept>();
    test_remove_volatile<int(int) const volatile&& noexcept>();

    test_remove_volatile<int(...)>();
    test_remove_volatile<int(...)&>();
    test_remove_volatile<int(...) &&>();
    test_remove_volatile<int(...) const>();
    test_remove_volatile<int(...) const&>();
    test_remove_volatile<int(...) const&&>();
    test_remove_volatile<int(...) volatile>();
    test_remove_volatile<int(...) volatile&>();
    test_remove_volatile<int(...) volatile&&>();
    test_remove_volatile<int(...) const volatile>();
    test_remove_volatile<int(...) const volatile&>();
    test_remove_volatile<int(...) const volatile&&>();
    test_remove_volatile<int(...) noexcept>();
    test_remove_volatile<int(...)& noexcept>();
    test_remove_volatile<int(...)&& noexcept>();
    test_remove_volatile<int(...) const noexcept>();
    test_remove_volatile<int(...) const& noexcept>();
    test_remove_volatile<int(...) const&& noexcept>();
    test_remove_volatile<int(...) volatile noexcept>();
    test_remove_volatile<int(...) volatile& noexcept>();
    test_remove_volatile<int(...) volatile&& noexcept>();
    test_remove_volatile<int(...) const volatile noexcept>();
    test_remove_volatile<int(...) const volatile& noexcept>();
    test_remove_volatile<int(...) const volatile&& noexcept>();

    test_remove_volatile<int(int, ...)>();
    test_remove_volatile<int(int, ...)&>();
    test_remove_volatile<int(int, ...) &&>();
    test_remove_volatile<int(int, ...) const>();
    test_remove_volatile<int(int, ...) const&>();
    test_remove_volatile<int(int, ...) const&&>();
    test_remove_volatile<int(int, ...) volatile>();
    test_remove_volatile<int(int, ...) volatile&>();
    test_remove_volatile<int(int, ...) volatile&&>();
    test_remove_volatile<int(int, ...) const volatile>();
    test_remove_volatile<int(int, ...) const volatile&>();
    test_remove_volatile<int(int, ...) const volatile&&>();
    test_remove_volatile<int(int, ...) noexcept>();
    test_remove_volatile<int(int, ...)& noexcept>();
    test_remove_volatile<int(int, ...)&& noexcept>();
    test_remove_volatile<int(int, ...) const noexcept>();
    test_remove_volatile<int(int, ...) const& noexcept>();
    test_remove_volatile<int(int, ...) const&& noexcept>();
    test_remove_volatile<int(int, ...) volatile noexcept>();
    test_remove_volatile<int(int, ...) volatile& noexcept>();
    test_remove_volatile<int(int, ...) volatile&& noexcept>();
    test_remove_volatile<int(int, ...) const volatile noexcept>();
    test_remove_volatile<int(int, ...) const volatile& noexcept>();
    test_remove_volatile<int(int, ...) const volatile&& noexcept>();

    test_remove_volatile<void (*)()>();
    test_remove_volatile<void (*)() noexcept>();

    test_remove_volatile<void (*)(int)>();
    test_remove_volatile<void (*)(int) noexcept>();

    test_remove_volatile<void (*)(...)>();
    test_remove_volatile<void (*)(...) noexcept>();

    test_remove_volatile<void (*)(int, ...)>();
    test_remove_volatile<void (*)(int, ...) noexcept>();

    test_remove_volatile<int (*)()>();
    test_remove_volatile<int (*)() noexcept>();

    test_remove_volatile<int (*)(int)>();
    test_remove_volatile<int (*)(int) noexcept>();

    test_remove_volatile<int (*)(...)>();
    test_remove_volatile<int (*)(...) noexcept>();

    test_remove_volatile<int (*)(int, ...)>();
    test_remove_volatile<int (*)(int, ...) noexcept>();

    test_remove_volatile<void (&)()>();
    test_remove_volatile<void (&)() noexcept>();

    test_remove_volatile<void (&)(int)>();
    test_remove_volatile<void (&)(int) noexcept>();

    test_remove_volatile<void (&)(...)>();
    test_remove_volatile<void (&)(...) noexcept>();

    test_remove_volatile<void (&)(int, ...)>();
    test_remove_volatile<void (&)(int, ...) noexcept>();

    test_remove_volatile<int (&)()>();
    test_remove_volatile<int (&)() noexcept>();

    test_remove_volatile<int (&)(int)>();
    test_remove_volatile<int (&)(int) noexcept>();

    test_remove_volatile<int (&)(...)>();
    test_remove_volatile<int (&)(...) noexcept>();

    test_remove_volatile<int (&)(int, ...)>();
    test_remove_volatile<int (&)(int, ...) noexcept>();

    test_remove_volatile<void(&&)()>();
    test_remove_volatile<void(&&)() noexcept>();

    test_remove_volatile<void(&&)(int)>();
    test_remove_volatile<void(&&)(int) noexcept>();

    test_remove_volatile<void(&&)(...)>();
    test_remove_volatile<void(&&)(...) noexcept>();

    test_remove_volatile<void(&&)(int, ...)>();
    test_remove_volatile<void(&&)(int, ...) noexcept>();

    test_remove_volatile<int(&&)()>();
    test_remove_volatile<int(&&)() noexcept>();

    test_remove_volatile<int(&&)(int)>();
    test_remove_volatile<int(&&)(int) noexcept>();

    test_remove_volatile<int(&&)(...)>();
    test_remove_volatile<int(&&)(...) noexcept>();

    test_remove_volatile<int(&&)(int, ...)>();
    test_remove_volatile<int(&&)(int, ...) noexcept>();

    test_remove_volatile<void (Class::*)()>();
    test_remove_volatile<void (Class::*)()&>();
    test_remove_volatile<void (Class::*)() &&>();
    test_remove_volatile<void (Class::*)() const>();
    test_remove_volatile<void (Class::*)() const&>();
    test_remove_volatile<void (Class::*)() const&&>();
    test_remove_volatile<void (Class::*)() noexcept>();
    test_remove_volatile<void (Class::*)()& noexcept>();
    test_remove_volatile<void (Class::*)()&& noexcept>();
    test_remove_volatile<void (Class::*)() const noexcept>();
    test_remove_volatile<void (Class::*)() const& noexcept>();
    test_remove_volatile<void (Class::*)() const&& noexcept>();

    test_remove_volatile<void (Class::*)(int)>();
    test_remove_volatile<void (Class::*)(int)&>();
    test_remove_volatile<void (Class::*)(int) &&>();
    test_remove_volatile<void (Class::*)(int) const>();
    test_remove_volatile<void (Class::*)(int) const&>();
    test_remove_volatile<void (Class::*)(int) const&&>();
    test_remove_volatile<void (Class::*)(int) noexcept>();
    test_remove_volatile<void (Class::*)(int)& noexcept>();
    test_remove_volatile<void (Class::*)(int)&& noexcept>();
    test_remove_volatile<void (Class::*)(int) const noexcept>();
    test_remove_volatile<void (Class::*)(int) const& noexcept>();
    test_remove_volatile<void (Class::*)(int) const&& noexcept>();

    test_remove_volatile<void (Class::*)(...)>();
    test_remove_volatile<void (Class::*)(...)&>();
    test_remove_volatile<void (Class::*)(...) &&>();
    test_remove_volatile<void (Class::*)(...) const>();
    test_remove_volatile<void (Class::*)(...) const&>();
    test_remove_volatile<void (Class::*)(...) const&&>();
    test_remove_volatile<void (Class::*)(...) noexcept>();
    test_remove_volatile<void (Class::*)(...)& noexcept>();
    test_remove_volatile<void (Class::*)(...)&& noexcept>();
    test_remove_volatile<void (Class::*)(...) const noexcept>();
    test_remove_volatile<void (Class::*)(...) const& noexcept>();
    test_remove_volatile<void (Class::*)(...) const&& noexcept>();

    test_remove_volatile<void (Class::*)(int, ...)>();
    test_remove_volatile<void (Class::*)(int, ...)&>();
    test_remove_volatile<void (Class::*)(int, ...) &&>();
    test_remove_volatile<void (Class::*)(int, ...) const>();
    test_remove_volatile<void (Class::*)(int, ...) const&>();
    test_remove_volatile<void (Class::*)(int, ...) const&&>();
    test_remove_volatile<void (Class::*)(int, ...) noexcept>();
    test_remove_volatile<void (Class::*)(int, ...)& noexcept>();
    test_remove_volatile<void (Class::*)(int, ...)&& noexcept>();
    test_remove_volatile<void (Class::*)(int, ...) const noexcept>();
    test_remove_volatile<void (Class::*)(int, ...) const& noexcept>();
    test_remove_volatile<void (Class::*)(int, ...) const&& noexcept>();

    test_remove_volatile<int (Class::*)()>();
    test_remove_volatile<int (Class::*)()&>();
    test_remove_volatile<int (Class::*)() &&>();
    test_remove_volatile<int (Class::*)() const>();
    test_remove_volatile<int (Class::*)() const&>();
    test_remove_volatile<int (Class::*)() const&&>();
    test_remove_volatile<int (Class::*)() noexcept>();
    test_remove_volatile<int (Class::*)()& noexcept>();
    test_remove_volatile<int (Class::*)()&& noexcept>();
    test_remove_volatile<int (Class::*)() const noexcept>();
    test_remove_volatile<int (Class::*)() const& noexcept>();
    test_remove_volatile<int (Class::*)() const&& noexcept>();

    test_remove_volatile<int (Class::*)(int)>();
    test_remove_volatile<int (Class::*)(int)&>();
    test_remove_volatile<int (Class::*)(int) &&>();
    test_remove_volatile<int (Class::*)(int) const>();
    test_remove_volatile<int (Class::*)(int) const&>();
    test_remove_volatile<int (Class::*)(int) const&&>();
    test_remove_volatile<int (Class::*)(int) noexcept>();
    test_remove_volatile<int (Class::*)(int)& noexcept>();
    test_remove_volatile<int (Class::*)(int)&& noexcept>();
    test_remove_volatile<int (Class::*)(int) const noexcept>();
    test_remove_volatile<int (Class::*)(int) const& noexcept>();
    test_remove_volatile<int (Class::*)(int) const&& noexcept>();

    test_remove_volatile<int (Class::*)(...)>();
    test_remove_volatile<int (Class::*)(...)&>();
    test_remove_volatile<int (Class::*)(...) &&>();
    test_remove_volatile<int (Class::*)(...) const>();
    test_remove_volatile<int (Class::*)(...) const&>();
    test_remove_volatile<int (Class::*)(...) const&&>();
    test_remove_volatile<int (Class::*)(...) noexcept>();
    test_remove_volatile<int (Class::*)(...)& noexcept>();
    test_remove_volatile<int (Class::*)(...)&& noexcept>();
    test_remove_volatile<int (Class::*)(...) const noexcept>();
    test_remove_volatile<int (Class::*)(...) const& noexcept>();
    test_remove_volatile<int (Class::*)(...) const&& noexcept>();

    test_remove_volatile<int (Class::*)(int, ...)>();
    test_remove_volatile<int (Class::*)(int, ...)&>();
    test_remove_volatile<int (Class::*)(int, ...) &&>();
    test_remove_volatile<int (Class::*)(int, ...) const>();
    test_remove_volatile<int (Class::*)(int, ...) const&>();
    test_remove_volatile<int (Class::*)(int, ...) const&&>();
    test_remove_volatile<int (Class::*)(int, ...) noexcept>();
    test_remove_volatile<int (Class::*)(int, ...)& noexcept>();
    test_remove_volatile<int (Class::*)(int, ...)&& noexcept>();
    test_remove_volatile<int (Class::*)(int, ...) const noexcept>();
    test_remove_volatile<int (Class::*)(int, ...) const& noexcept>();
    test_remove_volatile<int (Class::*)(int, ...) const&& noexcept>();
}
