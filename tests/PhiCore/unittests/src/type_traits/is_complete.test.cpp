#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_complete.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_complete_impl()
{
    STATIC_REQUIRE(phi::is_complete<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_complete<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_complete_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_complete_v<T>);
#endif
}

template <typename T>
void test_is_complete()
{
    test_is_complete_impl<T>();
    test_is_complete_impl<const T>();
    test_is_complete_impl<volatile T>();
    test_is_complete_impl<const volatile T>();
}

template <typename T>
void test_is_not_complete_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_complete<T>::value);
    STATIC_REQUIRE(phi::is_not_complete<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_complete_v<T>);
    STATIC_REQUIRE(phi::is_not_complete_v<T>);
#endif
}

template <typename T>
void test_is_not_complete()
{
    test_is_not_complete_impl<T>();
    test_is_not_complete_impl<const T>();
    test_is_not_complete_impl<volatile T>();
    test_is_not_complete_impl<const volatile T>();
}

class A;

TEST_CASE("is_complete")
{
    test_is_not_complete<void>();
    test_is_complete<phi::nullptr_t>();
    test_is_complete<bool>();
    test_is_complete<char>();
    test_is_complete<signed char>();
    test_is_complete<unsigned char>();
    test_is_complete<short>();
    test_is_complete<unsigned short>();
    test_is_complete<int>();
    test_is_complete<unsigned int>();
    test_is_complete<long>();
    test_is_complete<unsigned long>();
    test_is_complete<long long>();
    test_is_complete<unsigned long long>();
    test_is_complete<float>();
    test_is_complete<double>();
    test_is_complete<long double>();
    test_is_complete<char8_t>();
    test_is_complete<char16_t>();
    test_is_complete<char32_t>();
    test_is_complete<wchar_t>();

    test_is_complete<phi::boolean>();
    test_is_complete<phi::integer<signed char>>();
    test_is_complete<phi::integer<unsigned char>>();
    test_is_complete<phi::integer<short>>();
    test_is_complete<phi::integer<unsigned short>>();
    test_is_complete<phi::integer<int>>();
    test_is_complete<phi::integer<unsigned int>>();
    test_is_complete<phi::integer<long>>();
    test_is_complete<phi::integer<unsigned long>>();
    test_is_complete<phi::integer<long long>>();
    test_is_complete<phi::integer<unsigned long long>>();
    test_is_complete<phi::floating_point<float>>();
    test_is_complete<phi::floating_point<double>>();
    test_is_complete<phi::floating_point<long double>>();

    test_is_complete<std::vector<int>>();
    test_is_complete<phi::scope_ptr<int>>();

    test_is_complete<int&>();
    test_is_complete<const int&>();
    test_is_complete<volatile int&>();
    test_is_complete<const volatile int&>();
    test_is_complete<int&&>();
    test_is_complete<const int&&>();
    test_is_complete<volatile int&&>();
    test_is_complete<const volatile int&&>();
    test_is_complete<int*>();
    test_is_complete<const int*>();
    test_is_complete<volatile int*>();
    test_is_complete<const volatile int*>();
    test_is_complete<int**>();
    test_is_complete<const int**>();
    test_is_complete<volatile int**>();
    test_is_complete<const volatile int**>();
    test_is_complete<int*&>();
    test_is_complete<const int*&>();
    test_is_complete<volatile int*&>();
    test_is_complete<const volatile int*&>();
    test_is_complete<int*&&>();
    test_is_complete<const int*&&>();
    test_is_complete<volatile int*&&>();
    test_is_complete<const volatile int*&&>();
    test_is_complete<void*>();
    test_is_complete<char[3]>();
    test_is_not_complete<char[]>();
    test_is_complete<char* [3]>();
    test_is_not_complete<char*[]>();
    test_is_complete<int(*)[3]>();
    test_is_complete<int(*)[]>();
    test_is_complete<int(&)[3]>();
    test_is_not_complete<int(&)[]>();
    test_is_complete<int(&&)[3]>();
    test_is_complete<int(&&)[]>();
    test_is_complete<char[3][2]>();
    test_is_not_complete<char[][2]>();
    test_is_complete<char* [3][2]>();
    test_is_not_complete<char*[][2]>();
    test_is_complete<int(*)[3][2]>();
    test_is_complete<int(*)[][2]>();
    test_is_complete<int(&)[3][2]>();
    test_is_not_complete<int(&)[][2]>();
    test_is_complete<int(&&)[3][2]>();
    test_is_complete<int(&&)[][2]>();
    test_is_complete<Class>();
    test_is_not_complete<Class[]>();
    test_is_complete<Class[2]>();
    test_is_complete<Template<void>>();
    test_is_complete<Template<int>>();
    test_is_complete<Template<Class>>();
    test_is_complete<Template<IncompleteType>>();
    test_is_complete<VariadicTemplate<>>();
    test_is_complete<VariadicTemplate<void>>();
    test_is_complete<VariadicTemplate<int>>();
    test_is_complete<VariadicTemplate<Class>>();
    test_is_complete<VariadicTemplate<IncompleteType>>();
    test_is_complete<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_complete<PublicDerivedFromTemplate<Base>>();
    test_is_complete<PublicDerivedFromTemplate<Derived>>();
    test_is_complete<PublicDerivedFromTemplate<Class>>();
    test_is_complete<PrivateDerivedFromTemplate<Base>>();
    test_is_complete<PrivateDerivedFromTemplate<Derived>>();
    test_is_complete<PrivateDerivedFromTemplate<Class>>();
    test_is_complete<ProtectedDerivedFromTemplate<Base>>();
    test_is_complete<ProtectedDerivedFromTemplate<Derived>>();
    test_is_complete<ProtectedDerivedFromTemplate<Class>>();
    test_is_complete<Union>();
    test_is_complete<NonEmptyUnion>();
    test_is_complete<Empty>();
    test_is_complete<NotEmpty>();
    test_is_complete<BitZero>();
    test_is_complete<BitOne>();
    test_is_complete<Base>();
    test_is_complete<Derived>();
    test_is_complete<Abstract>();
    test_is_complete<PublicAbstract>();
    test_is_complete<PrivateAbstract>();
    test_is_complete<ProtectedAbstract>();
    test_is_complete<AbstractTemplate<int>>();
    test_is_complete<AbstractTemplate<double>>();
    test_is_complete<AbstractTemplate<Class>>();
    test_is_complete<AbstractTemplate<IncompleteType>>();
    test_is_complete<Final>();
    test_is_complete<PublicDestructor>();
    test_is_complete<ProtectedDestructor>();
    test_is_complete<PrivateDestructor>();
    test_is_complete<VirtualPublicDestructor>();
    test_is_complete<VirtualProtectedDestructor>();
    test_is_complete<VirtualPrivateDestructor>();
    test_is_complete<PurePublicDestructor>();
    test_is_complete<PureProtectedDestructor>();
    test_is_complete<PurePrivateDestructor>();
    test_is_complete<DeletedPublicDestructor>();
    test_is_complete<DeletedProtectedDestructor>();
    test_is_complete<DeletedPrivateDestructor>();
    test_is_complete<DeletedVirtualPublicDestructor>();
    test_is_complete<DeletedVirtualProtectedDestructor>();
    test_is_complete<DeletedVirtualPrivateDestructor>();
    test_is_complete<Enum>();
    test_is_complete<EnumSigned>();
    test_is_complete<EnumUnsigned>();
    test_is_complete<EnumClass>();
    test_is_complete<EnumStruct>();
    test_is_complete<Function>();
    test_is_complete<FunctionPtr>();
    test_is_complete<MemberObjectPtr>();
    test_is_complete<MemberFunctionPtr>();
    test_is_not_complete<IncompleteType>();
    test_is_not_complete<IncompleteTemplate<void>>();
    test_is_not_complete<IncompleteTemplate<int>>();
    test_is_not_complete<IncompleteTemplate<Class>>();
    test_is_not_complete<IncompleteTemplate<IncompleteType>>();
    test_is_not_complete<IncompleteVariadicTemplate<>>();
    test_is_not_complete<IncompleteVariadicTemplate<void>>();
    test_is_not_complete<IncompleteVariadicTemplate<int>>();
    test_is_not_complete<IncompleteVariadicTemplate<Class>>();
    test_is_not_complete<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_complete<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_complete<int Class::*>();
    test_is_complete<float Class::*>();
    test_is_complete<void * Class::*>();
    test_is_complete<int * Class::*>();
    test_is_complete<int Class::*&>();
    test_is_complete<float Class::*&>();
    test_is_complete<void * Class::*&>();
    test_is_complete<int * Class::*&>();
    test_is_complete<int Class::*&&>();
    test_is_complete<float Class::*&&>();
    test_is_complete<void * Class::*&&>();
    test_is_complete<int * Class::*&&>();
    test_is_complete<int Class::*const>();
    test_is_complete<float Class::*const>();
    test_is_complete<void * Class::*const>();
    test_is_complete<int Class::*const&>();
    test_is_complete<float Class::*const&>();
    test_is_complete<void * Class::*const&>();
    test_is_complete<int Class::*const&&>();
    test_is_complete<float Class::*const&&>();
    test_is_complete<void * Class::*const&&>();
    test_is_complete<int Class::*volatile>();
    test_is_complete<float Class::*volatile>();
    test_is_complete<void * Class::*volatile>();
    test_is_complete<int Class::*volatile&>();
    test_is_complete<float Class::*volatile&>();
    test_is_complete<void * Class::*volatile&>();
    test_is_complete<int Class::*volatile&&>();
    test_is_complete<float Class::*volatile&&>();
    test_is_complete<void * Class::*volatile&&>();
    test_is_complete<int Class::*const volatile>();
    test_is_complete<float Class::*const volatile>();
    test_is_complete<void * Class::*const volatile>();
    test_is_complete<int Class::*const volatile&>();
    test_is_complete<float Class::*const volatile&>();
    test_is_complete<void * Class::*const volatile&>();
    test_is_complete<int Class::*const volatile&&>();
    test_is_complete<float Class::*const volatile&&>();
    test_is_complete<void * Class::*const volatile&&>();
    test_is_complete<NonCopyable>();
    test_is_complete<NonMoveable>();
    test_is_complete<NonConstructible>();
    test_is_complete<Tracked>();
    test_is_complete<TrapConstructible>();
    test_is_complete<TrapImplicitConversion>();
    test_is_complete<TrapComma>();
    test_is_complete<TrapCall>();
    test_is_complete<TrapSelfAssign>();
    test_is_complete<TrapDeref>();
    test_is_complete<TrapArraySubscript>();

    test_is_complete<void()>();
    test_is_complete<void()&>();
    test_is_complete<void() &&>();
    test_is_complete<void() const>();
    test_is_complete<void() const&>();
    test_is_complete<void() const&&>();
    test_is_complete<void() volatile>();
    test_is_complete<void() volatile&>();
    test_is_complete<void() volatile&&>();
    test_is_complete<void() const volatile>();
    test_is_complete<void() const volatile&>();
    test_is_complete<void() const volatile&&>();
    test_is_complete<void() noexcept>();
    test_is_complete<void()& noexcept>();
    test_is_complete<void()&& noexcept>();
    test_is_complete<void() const noexcept>();
    test_is_complete<void() const& noexcept>();
    test_is_complete<void() const&& noexcept>();
    test_is_complete<void() volatile noexcept>();
    test_is_complete<void() volatile& noexcept>();
    test_is_complete<void() volatile&& noexcept>();
    test_is_complete<void() const volatile noexcept>();
    test_is_complete<void() const volatile& noexcept>();
    test_is_complete<void() const volatile&& noexcept>();

    test_is_complete<void(int)>();
    test_is_complete<void(int)&>();
    test_is_complete<void(int) &&>();
    test_is_complete<void(int) const>();
    test_is_complete<void(int) const&>();
    test_is_complete<void(int) const&&>();
    test_is_complete<void(int) volatile>();
    test_is_complete<void(int) volatile&>();
    test_is_complete<void(int) volatile&&>();
    test_is_complete<void(int) const volatile>();
    test_is_complete<void(int) const volatile&>();
    test_is_complete<void(int) const volatile&&>();
    test_is_complete<void(int) noexcept>();
    test_is_complete<void(int)& noexcept>();
    test_is_complete<void(int)&& noexcept>();
    test_is_complete<void(int) const noexcept>();
    test_is_complete<void(int) const& noexcept>();
    test_is_complete<void(int) const&& noexcept>();
    test_is_complete<void(int) volatile noexcept>();
    test_is_complete<void(int) volatile& noexcept>();
    test_is_complete<void(int) volatile&& noexcept>();
    test_is_complete<void(int) const volatile noexcept>();
    test_is_complete<void(int) const volatile& noexcept>();
    test_is_complete<void(int) const volatile&& noexcept>();

    test_is_complete<void(...)>();
    test_is_complete<void(...)&>();
    test_is_complete<void(...) &&>();
    test_is_complete<void(...) const>();
    test_is_complete<void(...) const&>();
    test_is_complete<void(...) const&&>();
    test_is_complete<void(...) volatile>();
    test_is_complete<void(...) volatile&>();
    test_is_complete<void(...) volatile&&>();
    test_is_complete<void(...) const volatile>();
    test_is_complete<void(...) const volatile&>();
    test_is_complete<void(...) const volatile&&>();
    test_is_complete<void(...) noexcept>();
    test_is_complete<void(...)& noexcept>();
    test_is_complete<void(...)&& noexcept>();
    test_is_complete<void(...) const noexcept>();
    test_is_complete<void(...) const& noexcept>();
    test_is_complete<void(...) const&& noexcept>();
    test_is_complete<void(...) volatile noexcept>();
    test_is_complete<void(...) volatile& noexcept>();
    test_is_complete<void(...) volatile&& noexcept>();
    test_is_complete<void(...) const volatile noexcept>();
    test_is_complete<void(...) const volatile& noexcept>();
    test_is_complete<void(...) const volatile&& noexcept>();

    test_is_complete<void(int, ...)>();
    test_is_complete<void(int, ...)&>();
    test_is_complete<void(int, ...) &&>();
    test_is_complete<void(int, ...) const>();
    test_is_complete<void(int, ...) const&>();
    test_is_complete<void(int, ...) const&&>();
    test_is_complete<void(int, ...) volatile>();
    test_is_complete<void(int, ...) volatile&>();
    test_is_complete<void(int, ...) volatile&&>();
    test_is_complete<void(int, ...) const volatile>();
    test_is_complete<void(int, ...) const volatile&>();
    test_is_complete<void(int, ...) const volatile&&>();
    test_is_complete<void(int, ...) noexcept>();
    test_is_complete<void(int, ...)& noexcept>();
    test_is_complete<void(int, ...)&& noexcept>();
    test_is_complete<void(int, ...) const noexcept>();
    test_is_complete<void(int, ...) const& noexcept>();
    test_is_complete<void(int, ...) const&& noexcept>();
    test_is_complete<void(int, ...) volatile noexcept>();
    test_is_complete<void(int, ...) volatile& noexcept>();
    test_is_complete<void(int, ...) volatile&& noexcept>();
    test_is_complete<void(int, ...) const volatile noexcept>();
    test_is_complete<void(int, ...) const volatile& noexcept>();
    test_is_complete<void(int, ...) const volatile&& noexcept>();

    test_is_complete<int()>();
    test_is_complete<int()&>();
    test_is_complete<int() &&>();
    test_is_complete<int() const>();
    test_is_complete<int() const&>();
    test_is_complete<int() const&&>();
    test_is_complete<int() volatile>();
    test_is_complete<int() volatile&>();
    test_is_complete<int() volatile&&>();
    test_is_complete<int() const volatile>();
    test_is_complete<int() const volatile&>();
    test_is_complete<int() const volatile&&>();
    test_is_complete<int() noexcept>();
    test_is_complete<int()& noexcept>();
    test_is_complete<int()&& noexcept>();
    test_is_complete<int() const noexcept>();
    test_is_complete<int() const& noexcept>();
    test_is_complete<int() const&& noexcept>();
    test_is_complete<int() volatile noexcept>();
    test_is_complete<int() volatile& noexcept>();
    test_is_complete<int() volatile&& noexcept>();
    test_is_complete<int() const volatile noexcept>();
    test_is_complete<int() const volatile& noexcept>();
    test_is_complete<int() const volatile&& noexcept>();

    test_is_complete<int(int)>();
    test_is_complete<int(int)&>();
    test_is_complete<int(int) &&>();
    test_is_complete<int(int) const>();
    test_is_complete<int(int) const&>();
    test_is_complete<int(int) const&&>();
    test_is_complete<int(int) volatile>();
    test_is_complete<int(int) volatile&>();
    test_is_complete<int(int) volatile&&>();
    test_is_complete<int(int) const volatile>();
    test_is_complete<int(int) const volatile&>();
    test_is_complete<int(int) const volatile&&>();
    test_is_complete<int(int) noexcept>();
    test_is_complete<int(int)& noexcept>();
    test_is_complete<int(int)&& noexcept>();
    test_is_complete<int(int) const noexcept>();
    test_is_complete<int(int) const& noexcept>();
    test_is_complete<int(int) const&& noexcept>();
    test_is_complete<int(int) volatile noexcept>();
    test_is_complete<int(int) volatile& noexcept>();
    test_is_complete<int(int) volatile&& noexcept>();
    test_is_complete<int(int) const volatile noexcept>();
    test_is_complete<int(int) const volatile& noexcept>();
    test_is_complete<int(int) const volatile&& noexcept>();

    test_is_complete<int(...)>();
    test_is_complete<int(...)&>();
    test_is_complete<int(...) &&>();
    test_is_complete<int(...) const>();
    test_is_complete<int(...) const&>();
    test_is_complete<int(...) const&&>();
    test_is_complete<int(...) volatile>();
    test_is_complete<int(...) volatile&>();
    test_is_complete<int(...) volatile&&>();
    test_is_complete<int(...) const volatile>();
    test_is_complete<int(...) const volatile&>();
    test_is_complete<int(...) const volatile&&>();
    test_is_complete<int(...) noexcept>();
    test_is_complete<int(...)& noexcept>();
    test_is_complete<int(...)&& noexcept>();
    test_is_complete<int(...) const noexcept>();
    test_is_complete<int(...) const& noexcept>();
    test_is_complete<int(...) const&& noexcept>();
    test_is_complete<int(...) volatile noexcept>();
    test_is_complete<int(...) volatile& noexcept>();
    test_is_complete<int(...) volatile&& noexcept>();
    test_is_complete<int(...) const volatile noexcept>();
    test_is_complete<int(...) const volatile& noexcept>();
    test_is_complete<int(...) const volatile&& noexcept>();

    test_is_complete<int(int, ...)>();
    test_is_complete<int(int, ...)&>();
    test_is_complete<int(int, ...) &&>();
    test_is_complete<int(int, ...) const>();
    test_is_complete<int(int, ...) const&>();
    test_is_complete<int(int, ...) const&&>();
    test_is_complete<int(int, ...) volatile>();
    test_is_complete<int(int, ...) volatile&>();
    test_is_complete<int(int, ...) volatile&&>();
    test_is_complete<int(int, ...) const volatile>();
    test_is_complete<int(int, ...) const volatile&>();
    test_is_complete<int(int, ...) const volatile&&>();
    test_is_complete<int(int, ...) noexcept>();
    test_is_complete<int(int, ...)& noexcept>();
    test_is_complete<int(int, ...)&& noexcept>();
    test_is_complete<int(int, ...) const noexcept>();
    test_is_complete<int(int, ...) const& noexcept>();
    test_is_complete<int(int, ...) const&& noexcept>();
    test_is_complete<int(int, ...) volatile noexcept>();
    test_is_complete<int(int, ...) volatile& noexcept>();
    test_is_complete<int(int, ...) volatile&& noexcept>();
    test_is_complete<int(int, ...) const volatile noexcept>();
    test_is_complete<int(int, ...) const volatile& noexcept>();
    test_is_complete<int(int, ...) const volatile&& noexcept>();

    test_is_complete<void (*)()>();
    test_is_complete<void (*)() noexcept>();

    test_is_complete<void (*)(int)>();
    test_is_complete<void (*)(int) noexcept>();

    test_is_complete<void (*)(...)>();
    test_is_complete<void (*)(...) noexcept>();

    test_is_complete<void (*)(int, ...)>();
    test_is_complete<void (*)(int, ...) noexcept>();

    test_is_complete<int (*)()>();
    test_is_complete<int (*)() noexcept>();

    test_is_complete<int (*)(int)>();
    test_is_complete<int (*)(int) noexcept>();

    test_is_complete<int (*)(...)>();
    test_is_complete<int (*)(...) noexcept>();

    test_is_complete<int (*)(int, ...)>();
    test_is_complete<int (*)(int, ...) noexcept>();

    test_is_complete<void (&)()>();
    test_is_complete<void (&)() noexcept>();

    test_is_complete<void (&)(int)>();
    test_is_complete<void (&)(int) noexcept>();

    test_is_complete<void (&)(...)>();
    test_is_complete<void (&)(...) noexcept>();

    test_is_complete<void (&)(int, ...)>();
    test_is_complete<void (&)(int, ...) noexcept>();

    test_is_complete<int (&)()>();
    test_is_complete<int (&)() noexcept>();

    test_is_complete<int (&)(int)>();
    test_is_complete<int (&)(int) noexcept>();

    test_is_complete<int (&)(...)>();
    test_is_complete<int (&)(...) noexcept>();

    test_is_complete<int (&)(int, ...)>();
    test_is_complete<int (&)(int, ...) noexcept>();

    test_is_complete<void(&&)()>();
    test_is_complete<void(&&)() noexcept>();

    test_is_complete<void(&&)(int)>();
    test_is_complete<void(&&)(int) noexcept>();

    test_is_complete<void(&&)(...)>();
    test_is_complete<void(&&)(...) noexcept>();

    test_is_complete<void(&&)(int, ...)>();
    test_is_complete<void(&&)(int, ...) noexcept>();

    test_is_complete<int(&&)()>();
    test_is_complete<int(&&)() noexcept>();

    test_is_complete<int(&&)(int)>();
    test_is_complete<int(&&)(int) noexcept>();

    test_is_complete<int(&&)(...)>();
    test_is_complete<int(&&)(...) noexcept>();

    test_is_complete<int(&&)(int, ...)>();
    test_is_complete<int(&&)(int, ...) noexcept>();

    test_is_complete<void (Class::*)()>();
    test_is_complete<void (Class::*)()&>();
    test_is_complete<void (Class::*)() &&>();
    test_is_complete<void (Class::*)() const>();
    test_is_complete<void (Class::*)() const&>();
    test_is_complete<void (Class::*)() const&&>();
    test_is_complete<void (Class::*)() noexcept>();
    test_is_complete<void (Class::*)()& noexcept>();
    test_is_complete<void (Class::*)()&& noexcept>();
    test_is_complete<void (Class::*)() const noexcept>();
    test_is_complete<void (Class::*)() const& noexcept>();
    test_is_complete<void (Class::*)() const&& noexcept>();

    test_is_complete<void (Class::*)(int)>();
    test_is_complete<void (Class::*)(int)&>();
    test_is_complete<void (Class::*)(int) &&>();
    test_is_complete<void (Class::*)(int) const>();
    test_is_complete<void (Class::*)(int) const&>();
    test_is_complete<void (Class::*)(int) const&&>();
    test_is_complete<void (Class::*)(int) noexcept>();
    test_is_complete<void (Class::*)(int)& noexcept>();
    test_is_complete<void (Class::*)(int)&& noexcept>();
    test_is_complete<void (Class::*)(int) const noexcept>();
    test_is_complete<void (Class::*)(int) const& noexcept>();
    test_is_complete<void (Class::*)(int) const&& noexcept>();

    test_is_complete<void (Class::*)(...)>();
    test_is_complete<void (Class::*)(...)&>();
    test_is_complete<void (Class::*)(...) &&>();
    test_is_complete<void (Class::*)(...) const>();
    test_is_complete<void (Class::*)(...) const&>();
    test_is_complete<void (Class::*)(...) const&&>();
    test_is_complete<void (Class::*)(...) noexcept>();
    test_is_complete<void (Class::*)(...)& noexcept>();
    test_is_complete<void (Class::*)(...)&& noexcept>();
    test_is_complete<void (Class::*)(...) const noexcept>();
    test_is_complete<void (Class::*)(...) const& noexcept>();
    test_is_complete<void (Class::*)(...) const&& noexcept>();

    test_is_complete<void (Class::*)(int, ...)>();
    test_is_complete<void (Class::*)(int, ...)&>();
    test_is_complete<void (Class::*)(int, ...) &&>();
    test_is_complete<void (Class::*)(int, ...) const>();
    test_is_complete<void (Class::*)(int, ...) const&>();
    test_is_complete<void (Class::*)(int, ...) const&&>();
    test_is_complete<void (Class::*)(int, ...) noexcept>();
    test_is_complete<void (Class::*)(int, ...)& noexcept>();
    test_is_complete<void (Class::*)(int, ...)&& noexcept>();
    test_is_complete<void (Class::*)(int, ...) const noexcept>();
    test_is_complete<void (Class::*)(int, ...) const& noexcept>();
    test_is_complete<void (Class::*)(int, ...) const&& noexcept>();

    test_is_complete<int (Class::*)()>();
    test_is_complete<int (Class::*)()&>();
    test_is_complete<int (Class::*)() &&>();
    test_is_complete<int (Class::*)() const>();
    test_is_complete<int (Class::*)() const&>();
    test_is_complete<int (Class::*)() const&&>();
    test_is_complete<int (Class::*)() noexcept>();
    test_is_complete<int (Class::*)()& noexcept>();
    test_is_complete<int (Class::*)()&& noexcept>();
    test_is_complete<int (Class::*)() const noexcept>();
    test_is_complete<int (Class::*)() const& noexcept>();
    test_is_complete<int (Class::*)() const&& noexcept>();

    test_is_complete<int (Class::*)(int)>();
    test_is_complete<int (Class::*)(int)&>();
    test_is_complete<int (Class::*)(int) &&>();
    test_is_complete<int (Class::*)(int) const>();
    test_is_complete<int (Class::*)(int) const&>();
    test_is_complete<int (Class::*)(int) const&&>();
    test_is_complete<int (Class::*)(int) noexcept>();
    test_is_complete<int (Class::*)(int)& noexcept>();
    test_is_complete<int (Class::*)(int)&& noexcept>();
    test_is_complete<int (Class::*)(int) const noexcept>();
    test_is_complete<int (Class::*)(int) const& noexcept>();
    test_is_complete<int (Class::*)(int) const&& noexcept>();

    test_is_complete<int (Class::*)(...)>();
    test_is_complete<int (Class::*)(...)&>();
    test_is_complete<int (Class::*)(...) &&>();
    test_is_complete<int (Class::*)(...) const>();
    test_is_complete<int (Class::*)(...) const&>();
    test_is_complete<int (Class::*)(...) const&&>();
    test_is_complete<int (Class::*)(...) noexcept>();
    test_is_complete<int (Class::*)(...)& noexcept>();
    test_is_complete<int (Class::*)(...)&& noexcept>();
    test_is_complete<int (Class::*)(...) const noexcept>();
    test_is_complete<int (Class::*)(...) const& noexcept>();
    test_is_complete<int (Class::*)(...) const&& noexcept>();

    test_is_complete<int (Class::*)(int, ...)>();
    test_is_complete<int (Class::*)(int, ...)&>();
    test_is_complete<int (Class::*)(int, ...) &&>();
    test_is_complete<int (Class::*)(int, ...) const>();
    test_is_complete<int (Class::*)(int, ...) const&>();
    test_is_complete<int (Class::*)(int, ...) const&&>();
    test_is_complete<int (Class::*)(int, ...) noexcept>();
    test_is_complete<int (Class::*)(int, ...)& noexcept>();
    test_is_complete<int (Class::*)(int, ...)&& noexcept>();
    test_is_complete<int (Class::*)(int, ...) const noexcept>();
    test_is_complete<int (Class::*)(int, ...) const& noexcept>();
    test_is_complete<int (Class::*)(int, ...) const&& noexcept>();
}
