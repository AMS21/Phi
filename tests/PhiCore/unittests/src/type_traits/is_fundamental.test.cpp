#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_fundamental.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_fundamental_impl()
{
    STATIC_REQUIRE(phi::is_fundamental<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_fundamental<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_fundamental_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_fundamental_v<T>);
#endif
}

template <typename T>
void test_is_fundamental()
{
    test_is_fundamental_impl<T>();
    test_is_fundamental_impl<const T>();
    test_is_fundamental_impl<volatile T>();
    test_is_fundamental_impl<const volatile T>();
}

template <typename T>
void test_is_not_fundamental_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_fundamental<T>::value);
    STATIC_REQUIRE(phi::is_not_fundamental<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_fundamental_v<T>);
    STATIC_REQUIRE(phi::is_not_fundamental_v<T>);
#endif
}

template <typename T>
void test_is_not_fundamental()
{
    test_is_not_fundamental_impl<T>();
    test_is_not_fundamental_impl<const T>();
    test_is_not_fundamental_impl<volatile T>();
    test_is_not_fundamental_impl<const volatile T>();
}

TEST_CASE("is_fundamental")
{
    test_is_fundamental<void>();
    test_is_fundamental<phi::nullptr_t>();
    test_is_fundamental<bool>();
    test_is_fundamental<char>();
    test_is_fundamental<signed char>();
    test_is_fundamental<unsigned char>();
    test_is_fundamental<short>();
    test_is_fundamental<unsigned short>();
    test_is_fundamental<int>();
    test_is_fundamental<unsigned int>();
    test_is_fundamental<long>();
    test_is_fundamental<unsigned long>();
    test_is_fundamental<long long>();
    test_is_fundamental<unsigned long long>();
    test_is_fundamental<float>();
    test_is_fundamental<double>();
    test_is_fundamental<long double>();
    test_is_fundamental<char8_t>();
    test_is_fundamental<char16_t>();
    test_is_fundamental<char32_t>();
    test_is_fundamental<wchar_t>();

    test_is_fundamental<phi::boolean>();
    test_is_fundamental<phi::integer<signed char>>();
    test_is_fundamental<phi::integer<unsigned char>>();
    test_is_fundamental<phi::integer<short>>();
    test_is_fundamental<phi::integer<unsigned short>>();
    test_is_fundamental<phi::integer<int>>();
    test_is_fundamental<phi::integer<unsigned int>>();
    test_is_fundamental<phi::integer<long>>();
    test_is_fundamental<phi::integer<unsigned long>>();
    test_is_fundamental<phi::integer<long long>>();
    test_is_fundamental<phi::integer<unsigned long long>>();
    test_is_fundamental<phi::floating_point<float>>();
    test_is_fundamental<phi::floating_point<double>>();
    test_is_fundamental<phi::floating_point<long double>>();

    test_is_not_fundamental<std::vector<int>>();
    test_is_not_fundamental<phi::scope_ptr<int>>();

    test_is_not_fundamental<int&>();
    test_is_not_fundamental<const int&>();
    test_is_not_fundamental<volatile int&>();
    test_is_not_fundamental<const volatile int&>();
    test_is_not_fundamental<int&&>();
    test_is_not_fundamental<const int&&>();
    test_is_not_fundamental<volatile int&&>();
    test_is_not_fundamental<const volatile int&&>();
    test_is_not_fundamental<int*>();
    test_is_not_fundamental<const int*>();
    test_is_not_fundamental<volatile int*>();
    test_is_not_fundamental<const volatile int*>();
    test_is_not_fundamental<int**>();
    test_is_not_fundamental<const int**>();
    test_is_not_fundamental<volatile int**>();
    test_is_not_fundamental<const volatile int**>();
    test_is_not_fundamental<int*&>();
    test_is_not_fundamental<const int*&>();
    test_is_not_fundamental<volatile int*&>();
    test_is_not_fundamental<const volatile int*&>();
    test_is_not_fundamental<int*&&>();
    test_is_not_fundamental<const int*&&>();
    test_is_not_fundamental<volatile int*&&>();
    test_is_not_fundamental<const volatile int*&&>();
    test_is_not_fundamental<void*>();
    test_is_not_fundamental<char[3]>();
    test_is_not_fundamental<char[]>();
    test_is_not_fundamental<char* [3]>();
    test_is_not_fundamental<char*[]>();
    test_is_not_fundamental<int(*)[3]>();
    test_is_not_fundamental<int(*)[]>();
    test_is_not_fundamental<int(&)[3]>();
    test_is_not_fundamental<int(&)[]>();
    test_is_not_fundamental<int(&&)[3]>();
    test_is_not_fundamental<int(&&)[]>();
    test_is_not_fundamental<char[3][2]>();
    test_is_not_fundamental<char[][2]>();
    test_is_not_fundamental<char* [3][2]>();
    test_is_not_fundamental<char*[][2]>();
    test_is_not_fundamental<int(*)[3][2]>();
    test_is_not_fundamental<int(*)[][2]>();
    test_is_not_fundamental<int(&)[3][2]>();
    test_is_not_fundamental<int(&)[][2]>();
    test_is_not_fundamental<int(&&)[3][2]>();
    test_is_not_fundamental<int(&&)[][2]>();
    test_is_not_fundamental<Class>();
    test_is_not_fundamental<Class[]>();
    test_is_not_fundamental<Class[2]>();
    test_is_not_fundamental<Template<void>>();
    test_is_not_fundamental<Template<int>>();
    test_is_not_fundamental<Template<Class>>();
    test_is_not_fundamental<Template<IncompleteType>>();
    test_is_not_fundamental<VariadicTemplate<>>();
    test_is_not_fundamental<VariadicTemplate<void>>();
    test_is_not_fundamental<VariadicTemplate<int>>();
    test_is_not_fundamental<VariadicTemplate<Class>>();
    test_is_not_fundamental<VariadicTemplate<IncompleteType>>();
    test_is_not_fundamental<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_fundamental<PublicDerivedFromTemplate<Base>>();
    test_is_not_fundamental<PublicDerivedFromTemplate<Derived>>();
    test_is_not_fundamental<PublicDerivedFromTemplate<Class>>();
    test_is_not_fundamental<PrivateDerivedFromTemplate<Base>>();
    test_is_not_fundamental<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_fundamental<PrivateDerivedFromTemplate<Class>>();
    test_is_not_fundamental<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_fundamental<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_fundamental<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_fundamental<Union>();
    test_is_not_fundamental<NonEmptyUnion>();
    test_is_not_fundamental<Empty>();
    test_is_not_fundamental<NotEmpty>();
    test_is_not_fundamental<BitZero>();
    test_is_not_fundamental<BitOne>();
    test_is_not_fundamental<Base>();
    test_is_not_fundamental<Derived>();
    test_is_not_fundamental<Abstract>();
    test_is_not_fundamental<PublicAbstract>();
    test_is_not_fundamental<PrivateAbstract>();
    test_is_not_fundamental<ProtectedAbstract>();
    test_is_not_fundamental<AbstractTemplate<int>>();
    test_is_not_fundamental<AbstractTemplate<double>>();
    test_is_not_fundamental<AbstractTemplate<Class>>();
    test_is_not_fundamental<AbstractTemplate<IncompleteType>>();
    test_is_not_fundamental<Final>();
    test_is_not_fundamental<PublicDestructor>();
    test_is_not_fundamental<ProtectedDestructor>();
    test_is_not_fundamental<PrivateDestructor>();
    test_is_not_fundamental<VirtualPublicDestructor>();
    test_is_not_fundamental<VirtualProtectedDestructor>();
    test_is_not_fundamental<VirtualPrivateDestructor>();
    test_is_not_fundamental<PurePublicDestructor>();
    test_is_not_fundamental<PureProtectedDestructor>();
    test_is_not_fundamental<PurePrivateDestructor>();
    test_is_not_fundamental<DeletedPublicDestructor>();
    test_is_not_fundamental<DeletedProtectedDestructor>();
    test_is_not_fundamental<DeletedPrivateDestructor>();
    test_is_not_fundamental<DeletedVirtualPublicDestructor>();
    test_is_not_fundamental<DeletedVirtualProtectedDestructor>();
    test_is_not_fundamental<DeletedVirtualPrivateDestructor>();
    test_is_not_fundamental<Enum>();
    test_is_not_fundamental<EnumSigned>();
    test_is_not_fundamental<EnumUnsigned>();
    test_is_not_fundamental<EnumClass>();
    test_is_not_fundamental<EnumStruct>();
    test_is_not_fundamental<Function>();
    test_is_not_fundamental<FunctionPtr>();
    test_is_not_fundamental<MemberObjectPtr>();
    test_is_not_fundamental<MemberFunctionPtr>();
    test_is_not_fundamental<IncompleteType>();
    test_is_not_fundamental<IncompleteTemplate<void>>();
    test_is_not_fundamental<IncompleteTemplate<int>>();
    test_is_not_fundamental<IncompleteTemplate<Class>>();
    test_is_not_fundamental<IncompleteTemplate<IncompleteType>>();
    test_is_not_fundamental<IncompleteVariadicTemplate<>>();
    test_is_not_fundamental<IncompleteVariadicTemplate<void>>();
    test_is_not_fundamental<IncompleteVariadicTemplate<int>>();
    test_is_not_fundamental<IncompleteVariadicTemplate<Class>>();
    test_is_not_fundamental<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_fundamental<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_fundamental<int Class::*>();
    test_is_not_fundamental<float Class::*>();
    test_is_not_fundamental<void * Class::*>();
    test_is_not_fundamental<int * Class::*>();
    test_is_not_fundamental<int Class::*&>();
    test_is_not_fundamental<float Class::*&>();
    test_is_not_fundamental<void * Class::*&>();
    test_is_not_fundamental<int * Class::*&>();
    test_is_not_fundamental<int Class::*&&>();
    test_is_not_fundamental<float Class::*&&>();
    test_is_not_fundamental<void * Class::*&&>();
    test_is_not_fundamental<int * Class::*&&>();
    test_is_not_fundamental<int Class::*const>();
    test_is_not_fundamental<float Class::*const>();
    test_is_not_fundamental<void * Class::*const>();
    test_is_not_fundamental<int Class::*const&>();
    test_is_not_fundamental<float Class::*const&>();
    test_is_not_fundamental<void * Class::*const&>();
    test_is_not_fundamental<int Class::*const&&>();
    test_is_not_fundamental<float Class::*const&&>();
    test_is_not_fundamental<void * Class::*const&&>();
    test_is_not_fundamental<int Class::*volatile>();
    test_is_not_fundamental<float Class::*volatile>();
    test_is_not_fundamental<void * Class::*volatile>();
    test_is_not_fundamental<int Class::*volatile&>();
    test_is_not_fundamental<float Class::*volatile&>();
    test_is_not_fundamental<void * Class::*volatile&>();
    test_is_not_fundamental<int Class::*volatile&&>();
    test_is_not_fundamental<float Class::*volatile&&>();
    test_is_not_fundamental<void * Class::*volatile&&>();
    test_is_not_fundamental<int Class::*const volatile>();
    test_is_not_fundamental<float Class::*const volatile>();
    test_is_not_fundamental<void * Class::*const volatile>();
    test_is_not_fundamental<int Class::*const volatile&>();
    test_is_not_fundamental<float Class::*const volatile&>();
    test_is_not_fundamental<void * Class::*const volatile&>();
    test_is_not_fundamental<int Class::*const volatile&&>();
    test_is_not_fundamental<float Class::*const volatile&&>();
    test_is_not_fundamental<void * Class::*const volatile&&>();
    test_is_not_fundamental<NonCopyable>();
    test_is_not_fundamental<NonMoveable>();
    test_is_not_fundamental<NonConstructible>();
    test_is_not_fundamental<Tracked>();
    test_is_not_fundamental<TrapConstructible>();
    test_is_not_fundamental<TrapImplicitConversion>();
    test_is_not_fundamental<TrapComma>();
    test_is_not_fundamental<TrapCall>();
    test_is_not_fundamental<TrapSelfAssign>();
    test_is_not_fundamental<TrapDeref>();
    test_is_not_fundamental<TrapArraySubscript>();

    test_is_not_fundamental<void()>();
    test_is_not_fundamental<void()&>();
    test_is_not_fundamental<void() &&>();
    test_is_not_fundamental<void() const>();
    test_is_not_fundamental<void() const&>();
    test_is_not_fundamental<void() const&&>();
    test_is_not_fundamental<void() volatile>();
    test_is_not_fundamental<void() volatile&>();
    test_is_not_fundamental<void() volatile&&>();
    test_is_not_fundamental<void() const volatile>();
    test_is_not_fundamental<void() const volatile&>();
    test_is_not_fundamental<void() const volatile&&>();
    test_is_not_fundamental<void() noexcept>();
    test_is_not_fundamental<void()& noexcept>();
    test_is_not_fundamental<void()&& noexcept>();
    test_is_not_fundamental<void() const noexcept>();
    test_is_not_fundamental<void() const& noexcept>();
    test_is_not_fundamental<void() const&& noexcept>();
    test_is_not_fundamental<void() volatile noexcept>();
    test_is_not_fundamental<void() volatile& noexcept>();
    test_is_not_fundamental<void() volatile&& noexcept>();
    test_is_not_fundamental<void() const volatile noexcept>();
    test_is_not_fundamental<void() const volatile& noexcept>();
    test_is_not_fundamental<void() const volatile&& noexcept>();

    test_is_not_fundamental<void(int)>();
    test_is_not_fundamental<void(int)&>();
    test_is_not_fundamental<void(int) &&>();
    test_is_not_fundamental<void(int) const>();
    test_is_not_fundamental<void(int) const&>();
    test_is_not_fundamental<void(int) const&&>();
    test_is_not_fundamental<void(int) volatile>();
    test_is_not_fundamental<void(int) volatile&>();
    test_is_not_fundamental<void(int) volatile&&>();
    test_is_not_fundamental<void(int) const volatile>();
    test_is_not_fundamental<void(int) const volatile&>();
    test_is_not_fundamental<void(int) const volatile&&>();
    test_is_not_fundamental<void(int) noexcept>();
    test_is_not_fundamental<void(int)& noexcept>();
    test_is_not_fundamental<void(int)&& noexcept>();
    test_is_not_fundamental<void(int) const noexcept>();
    test_is_not_fundamental<void(int) const& noexcept>();
    test_is_not_fundamental<void(int) const&& noexcept>();
    test_is_not_fundamental<void(int) volatile noexcept>();
    test_is_not_fundamental<void(int) volatile& noexcept>();
    test_is_not_fundamental<void(int) volatile&& noexcept>();
    test_is_not_fundamental<void(int) const volatile noexcept>();
    test_is_not_fundamental<void(int) const volatile& noexcept>();
    test_is_not_fundamental<void(int) const volatile&& noexcept>();

    test_is_not_fundamental<void(...)>();
    test_is_not_fundamental<void(...)&>();
    test_is_not_fundamental<void(...) &&>();
    test_is_not_fundamental<void(...) const>();
    test_is_not_fundamental<void(...) const&>();
    test_is_not_fundamental<void(...) const&&>();
    test_is_not_fundamental<void(...) volatile>();
    test_is_not_fundamental<void(...) volatile&>();
    test_is_not_fundamental<void(...) volatile&&>();
    test_is_not_fundamental<void(...) const volatile>();
    test_is_not_fundamental<void(...) const volatile&>();
    test_is_not_fundamental<void(...) const volatile&&>();
    test_is_not_fundamental<void(...) noexcept>();
    test_is_not_fundamental<void(...)& noexcept>();
    test_is_not_fundamental<void(...)&& noexcept>();
    test_is_not_fundamental<void(...) const noexcept>();
    test_is_not_fundamental<void(...) const& noexcept>();
    test_is_not_fundamental<void(...) const&& noexcept>();
    test_is_not_fundamental<void(...) volatile noexcept>();
    test_is_not_fundamental<void(...) volatile& noexcept>();
    test_is_not_fundamental<void(...) volatile&& noexcept>();
    test_is_not_fundamental<void(...) const volatile noexcept>();
    test_is_not_fundamental<void(...) const volatile& noexcept>();
    test_is_not_fundamental<void(...) const volatile&& noexcept>();

    test_is_not_fundamental<void(int, ...)>();
    test_is_not_fundamental<void(int, ...)&>();
    test_is_not_fundamental<void(int, ...) &&>();
    test_is_not_fundamental<void(int, ...) const>();
    test_is_not_fundamental<void(int, ...) const&>();
    test_is_not_fundamental<void(int, ...) const&&>();
    test_is_not_fundamental<void(int, ...) volatile>();
    test_is_not_fundamental<void(int, ...) volatile&>();
    test_is_not_fundamental<void(int, ...) volatile&&>();
    test_is_not_fundamental<void(int, ...) const volatile>();
    test_is_not_fundamental<void(int, ...) const volatile&>();
    test_is_not_fundamental<void(int, ...) const volatile&&>();
    test_is_not_fundamental<void(int, ...) noexcept>();
    test_is_not_fundamental<void(int, ...)& noexcept>();
    test_is_not_fundamental<void(int, ...)&& noexcept>();
    test_is_not_fundamental<void(int, ...) const noexcept>();
    test_is_not_fundamental<void(int, ...) const& noexcept>();
    test_is_not_fundamental<void(int, ...) const&& noexcept>();
    test_is_not_fundamental<void(int, ...) volatile noexcept>();
    test_is_not_fundamental<void(int, ...) volatile& noexcept>();
    test_is_not_fundamental<void(int, ...) volatile&& noexcept>();
    test_is_not_fundamental<void(int, ...) const volatile noexcept>();
    test_is_not_fundamental<void(int, ...) const volatile& noexcept>();
    test_is_not_fundamental<void(int, ...) const volatile&& noexcept>();

    test_is_not_fundamental<int()>();
    test_is_not_fundamental<int()&>();
    test_is_not_fundamental<int() &&>();
    test_is_not_fundamental<int() const>();
    test_is_not_fundamental<int() const&>();
    test_is_not_fundamental<int() const&&>();
    test_is_not_fundamental<int() volatile>();
    test_is_not_fundamental<int() volatile&>();
    test_is_not_fundamental<int() volatile&&>();
    test_is_not_fundamental<int() const volatile>();
    test_is_not_fundamental<int() const volatile&>();
    test_is_not_fundamental<int() const volatile&&>();
    test_is_not_fundamental<int() noexcept>();
    test_is_not_fundamental<int()& noexcept>();
    test_is_not_fundamental<int()&& noexcept>();
    test_is_not_fundamental<int() const noexcept>();
    test_is_not_fundamental<int() const& noexcept>();
    test_is_not_fundamental<int() const&& noexcept>();
    test_is_not_fundamental<int() volatile noexcept>();
    test_is_not_fundamental<int() volatile& noexcept>();
    test_is_not_fundamental<int() volatile&& noexcept>();
    test_is_not_fundamental<int() const volatile noexcept>();
    test_is_not_fundamental<int() const volatile& noexcept>();
    test_is_not_fundamental<int() const volatile&& noexcept>();

    test_is_not_fundamental<int(int)>();
    test_is_not_fundamental<int(int)&>();
    test_is_not_fundamental<int(int) &&>();
    test_is_not_fundamental<int(int) const>();
    test_is_not_fundamental<int(int) const&>();
    test_is_not_fundamental<int(int) const&&>();
    test_is_not_fundamental<int(int) volatile>();
    test_is_not_fundamental<int(int) volatile&>();
    test_is_not_fundamental<int(int) volatile&&>();
    test_is_not_fundamental<int(int) const volatile>();
    test_is_not_fundamental<int(int) const volatile&>();
    test_is_not_fundamental<int(int) const volatile&&>();
    test_is_not_fundamental<int(int) noexcept>();
    test_is_not_fundamental<int(int)& noexcept>();
    test_is_not_fundamental<int(int)&& noexcept>();
    test_is_not_fundamental<int(int) const noexcept>();
    test_is_not_fundamental<int(int) const& noexcept>();
    test_is_not_fundamental<int(int) const&& noexcept>();
    test_is_not_fundamental<int(int) volatile noexcept>();
    test_is_not_fundamental<int(int) volatile& noexcept>();
    test_is_not_fundamental<int(int) volatile&& noexcept>();
    test_is_not_fundamental<int(int) const volatile noexcept>();
    test_is_not_fundamental<int(int) const volatile& noexcept>();
    test_is_not_fundamental<int(int) const volatile&& noexcept>();

    test_is_not_fundamental<int(...)>();
    test_is_not_fundamental<int(...)&>();
    test_is_not_fundamental<int(...) &&>();
    test_is_not_fundamental<int(...) const>();
    test_is_not_fundamental<int(...) const&>();
    test_is_not_fundamental<int(...) const&&>();
    test_is_not_fundamental<int(...) volatile>();
    test_is_not_fundamental<int(...) volatile&>();
    test_is_not_fundamental<int(...) volatile&&>();
    test_is_not_fundamental<int(...) const volatile>();
    test_is_not_fundamental<int(...) const volatile&>();
    test_is_not_fundamental<int(...) const volatile&&>();
    test_is_not_fundamental<int(...) noexcept>();
    test_is_not_fundamental<int(...)& noexcept>();
    test_is_not_fundamental<int(...)&& noexcept>();
    test_is_not_fundamental<int(...) const noexcept>();
    test_is_not_fundamental<int(...) const& noexcept>();
    test_is_not_fundamental<int(...) const&& noexcept>();
    test_is_not_fundamental<int(...) volatile noexcept>();
    test_is_not_fundamental<int(...) volatile& noexcept>();
    test_is_not_fundamental<int(...) volatile&& noexcept>();
    test_is_not_fundamental<int(...) const volatile noexcept>();
    test_is_not_fundamental<int(...) const volatile& noexcept>();
    test_is_not_fundamental<int(...) const volatile&& noexcept>();

    test_is_not_fundamental<int(int, ...)>();
    test_is_not_fundamental<int(int, ...)&>();
    test_is_not_fundamental<int(int, ...) &&>();
    test_is_not_fundamental<int(int, ...) const>();
    test_is_not_fundamental<int(int, ...) const&>();
    test_is_not_fundamental<int(int, ...) const&&>();
    test_is_not_fundamental<int(int, ...) volatile>();
    test_is_not_fundamental<int(int, ...) volatile&>();
    test_is_not_fundamental<int(int, ...) volatile&&>();
    test_is_not_fundamental<int(int, ...) const volatile>();
    test_is_not_fundamental<int(int, ...) const volatile&>();
    test_is_not_fundamental<int(int, ...) const volatile&&>();
    test_is_not_fundamental<int(int, ...) noexcept>();
    test_is_not_fundamental<int(int, ...)& noexcept>();
    test_is_not_fundamental<int(int, ...)&& noexcept>();
    test_is_not_fundamental<int(int, ...) const noexcept>();
    test_is_not_fundamental<int(int, ...) const& noexcept>();
    test_is_not_fundamental<int(int, ...) const&& noexcept>();
    test_is_not_fundamental<int(int, ...) volatile noexcept>();
    test_is_not_fundamental<int(int, ...) volatile& noexcept>();
    test_is_not_fundamental<int(int, ...) volatile&& noexcept>();
    test_is_not_fundamental<int(int, ...) const volatile noexcept>();
    test_is_not_fundamental<int(int, ...) const volatile& noexcept>();
    test_is_not_fundamental<int(int, ...) const volatile&& noexcept>();

    test_is_not_fundamental<void (*)()>();
    test_is_not_fundamental<void (*)() noexcept>();

    test_is_not_fundamental<void (*)(int)>();
    test_is_not_fundamental<void (*)(int) noexcept>();

    test_is_not_fundamental<void (*)(...)>();
    test_is_not_fundamental<void (*)(...) noexcept>();

    test_is_not_fundamental<void (*)(int, ...)>();
    test_is_not_fundamental<void (*)(int, ...) noexcept>();

    test_is_not_fundamental<int (*)()>();
    test_is_not_fundamental<int (*)() noexcept>();

    test_is_not_fundamental<int (*)(int)>();
    test_is_not_fundamental<int (*)(int) noexcept>();

    test_is_not_fundamental<int (*)(...)>();
    test_is_not_fundamental<int (*)(...) noexcept>();

    test_is_not_fundamental<int (*)(int, ...)>();
    test_is_not_fundamental<int (*)(int, ...) noexcept>();

    test_is_not_fundamental<void (&)()>();
    test_is_not_fundamental<void (&)() noexcept>();

    test_is_not_fundamental<void (&)(int)>();
    test_is_not_fundamental<void (&)(int) noexcept>();

    test_is_not_fundamental<void (&)(...)>();
    test_is_not_fundamental<void (&)(...) noexcept>();

    test_is_not_fundamental<void (&)(int, ...)>();
    test_is_not_fundamental<void (&)(int, ...) noexcept>();

    test_is_not_fundamental<int (&)()>();
    test_is_not_fundamental<int (&)() noexcept>();

    test_is_not_fundamental<int (&)(int)>();
    test_is_not_fundamental<int (&)(int) noexcept>();

    test_is_not_fundamental<int (&)(...)>();
    test_is_not_fundamental<int (&)(...) noexcept>();

    test_is_not_fundamental<int (&)(int, ...)>();
    test_is_not_fundamental<int (&)(int, ...) noexcept>();

    test_is_not_fundamental<void(&&)()>();
    test_is_not_fundamental<void(&&)() noexcept>();

    test_is_not_fundamental<void(&&)(int)>();
    test_is_not_fundamental<void(&&)(int) noexcept>();

    test_is_not_fundamental<void(&&)(...)>();
    test_is_not_fundamental<void(&&)(...) noexcept>();

    test_is_not_fundamental<void(&&)(int, ...)>();
    test_is_not_fundamental<void(&&)(int, ...) noexcept>();

    test_is_not_fundamental<int(&&)()>();
    test_is_not_fundamental<int(&&)() noexcept>();

    test_is_not_fundamental<int(&&)(int)>();
    test_is_not_fundamental<int(&&)(int) noexcept>();

    test_is_not_fundamental<int(&&)(...)>();
    test_is_not_fundamental<int(&&)(...) noexcept>();

    test_is_not_fundamental<int(&&)(int, ...)>();
    test_is_not_fundamental<int(&&)(int, ...) noexcept>();

    test_is_not_fundamental<void (Class::*)()>();
    test_is_not_fundamental<void (Class::*)()&>();
    test_is_not_fundamental<void (Class::*)() &&>();
    test_is_not_fundamental<void (Class::*)() const>();
    test_is_not_fundamental<void (Class::*)() const&>();
    test_is_not_fundamental<void (Class::*)() const&&>();
    test_is_not_fundamental<void (Class::*)() noexcept>();
    test_is_not_fundamental<void (Class::*)()& noexcept>();
    test_is_not_fundamental<void (Class::*)()&& noexcept>();
    test_is_not_fundamental<void (Class::*)() const noexcept>();
    test_is_not_fundamental<void (Class::*)() const& noexcept>();
    test_is_not_fundamental<void (Class::*)() const&& noexcept>();

    test_is_not_fundamental<void (Class::*)(int)>();
    test_is_not_fundamental<void (Class::*)(int)&>();
    test_is_not_fundamental<void (Class::*)(int) &&>();
    test_is_not_fundamental<void (Class::*)(int) const>();
    test_is_not_fundamental<void (Class::*)(int) const&>();
    test_is_not_fundamental<void (Class::*)(int) const&&>();
    test_is_not_fundamental<void (Class::*)(int) noexcept>();
    test_is_not_fundamental<void (Class::*)(int)& noexcept>();
    test_is_not_fundamental<void (Class::*)(int)&& noexcept>();
    test_is_not_fundamental<void (Class::*)(int) const noexcept>();
    test_is_not_fundamental<void (Class::*)(int) const& noexcept>();
    test_is_not_fundamental<void (Class::*)(int) const&& noexcept>();

    test_is_not_fundamental<void (Class::*)(...)>();
    test_is_not_fundamental<void (Class::*)(...)&>();
    test_is_not_fundamental<void (Class::*)(...) &&>();
    test_is_not_fundamental<void (Class::*)(...) const>();
    test_is_not_fundamental<void (Class::*)(...) const&>();
    test_is_not_fundamental<void (Class::*)(...) const&&>();
    test_is_not_fundamental<void (Class::*)(...) noexcept>();
    test_is_not_fundamental<void (Class::*)(...)& noexcept>();
    test_is_not_fundamental<void (Class::*)(...)&& noexcept>();
    test_is_not_fundamental<void (Class::*)(...) const noexcept>();
    test_is_not_fundamental<void (Class::*)(...) const& noexcept>();
    test_is_not_fundamental<void (Class::*)(...) const&& noexcept>();

    test_is_not_fundamental<void (Class::*)(int, ...)>();
    test_is_not_fundamental<void (Class::*)(int, ...)&>();
    test_is_not_fundamental<void (Class::*)(int, ...) &&>();
    test_is_not_fundamental<void (Class::*)(int, ...) const>();
    test_is_not_fundamental<void (Class::*)(int, ...) const&>();
    test_is_not_fundamental<void (Class::*)(int, ...) const&&>();
    test_is_not_fundamental<void (Class::*)(int, ...) noexcept>();
    test_is_not_fundamental<void (Class::*)(int, ...)& noexcept>();
    test_is_not_fundamental<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_fundamental<void (Class::*)(int, ...) const noexcept>();
    test_is_not_fundamental<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_fundamental<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_fundamental<int (Class::*)()>();
    test_is_not_fundamental<int (Class::*)()&>();
    test_is_not_fundamental<int (Class::*)() &&>();
    test_is_not_fundamental<int (Class::*)() const>();
    test_is_not_fundamental<int (Class::*)() const&>();
    test_is_not_fundamental<int (Class::*)() const&&>();
    test_is_not_fundamental<int (Class::*)() noexcept>();
    test_is_not_fundamental<int (Class::*)()& noexcept>();
    test_is_not_fundamental<int (Class::*)()&& noexcept>();
    test_is_not_fundamental<int (Class::*)() const noexcept>();
    test_is_not_fundamental<int (Class::*)() const& noexcept>();
    test_is_not_fundamental<int (Class::*)() const&& noexcept>();

    test_is_not_fundamental<int (Class::*)(int)>();
    test_is_not_fundamental<int (Class::*)(int)&>();
    test_is_not_fundamental<int (Class::*)(int) &&>();
    test_is_not_fundamental<int (Class::*)(int) const>();
    test_is_not_fundamental<int (Class::*)(int) const&>();
    test_is_not_fundamental<int (Class::*)(int) const&&>();
    test_is_not_fundamental<int (Class::*)(int) noexcept>();
    test_is_not_fundamental<int (Class::*)(int)& noexcept>();
    test_is_not_fundamental<int (Class::*)(int)&& noexcept>();
    test_is_not_fundamental<int (Class::*)(int) const noexcept>();
    test_is_not_fundamental<int (Class::*)(int) const& noexcept>();
    test_is_not_fundamental<int (Class::*)(int) const&& noexcept>();

    test_is_not_fundamental<int (Class::*)(...)>();
    test_is_not_fundamental<int (Class::*)(...)&>();
    test_is_not_fundamental<int (Class::*)(...) &&>();
    test_is_not_fundamental<int (Class::*)(...) const>();
    test_is_not_fundamental<int (Class::*)(...) const&>();
    test_is_not_fundamental<int (Class::*)(...) const&&>();
    test_is_not_fundamental<int (Class::*)(...) noexcept>();
    test_is_not_fundamental<int (Class::*)(...)& noexcept>();
    test_is_not_fundamental<int (Class::*)(...)&& noexcept>();
    test_is_not_fundamental<int (Class::*)(...) const noexcept>();
    test_is_not_fundamental<int (Class::*)(...) const& noexcept>();
    test_is_not_fundamental<int (Class::*)(...) const&& noexcept>();

    test_is_not_fundamental<int (Class::*)(int, ...)>();
    test_is_not_fundamental<int (Class::*)(int, ...)&>();
    test_is_not_fundamental<int (Class::*)(int, ...) &&>();
    test_is_not_fundamental<int (Class::*)(int, ...) const>();
    test_is_not_fundamental<int (Class::*)(int, ...) const&>();
    test_is_not_fundamental<int (Class::*)(int, ...) const&&>();
    test_is_not_fundamental<int (Class::*)(int, ...) noexcept>();
    test_is_not_fundamental<int (Class::*)(int, ...)& noexcept>();
    test_is_not_fundamental<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_fundamental<int (Class::*)(int, ...) const noexcept>();
    test_is_not_fundamental<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_fundamental<int (Class::*)(int, ...) const&& noexcept>();
}
