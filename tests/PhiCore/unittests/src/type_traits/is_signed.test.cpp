#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_signed.hpp>
#include <phi/type_traits/make_unsafe.hpp>
#include <type_traits>
#include <vector>

struct A; // incomplete

template <typename T>
void test_is_signed_impl()
{
    STATIC_REQUIRE(phi::is_signed<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_signed<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_signed_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_signed_v<T>);
#endif

    // Standard compatibililty
    STATIC_REQUIRE(std::is_signed<phi::make_unsafe_t<T>>::value);
}

template <typename T>
void test_is_not_signed_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_signed<T>::value);
    STATIC_REQUIRE(phi::is_not_signed<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_signed_v<T>);
    STATIC_REQUIRE(phi::is_not_signed_v<T>);
#endif

    // Standard compatibililty
    STATIC_REQUIRE_FALSE(std::is_signed<T>::value);
}

template <typename T>
void test_is_signed()
{
    test_is_signed_impl<T>();
    test_is_signed_impl<const T>();
    test_is_signed_impl<volatile T>();
    test_is_signed_impl<const volatile T>();
}

template <typename T>
void test_is_not_signed()
{
    test_is_not_signed_impl<T>();
    test_is_not_signed_impl<const T>();
    test_is_not_signed_impl<volatile T>();
    test_is_not_signed_impl<const volatile T>();
}

TEST_CASE("is_signed")
{
    test_is_not_signed<void>();
    test_is_not_signed<phi::nullptr_t>();
    test_is_not_signed<bool>();
    //test_is_signed<char>();
    test_is_signed<signed char>();
    test_is_not_signed<unsigned char>();
    test_is_signed<short>();
    test_is_not_signed<unsigned short>();
    test_is_signed<int>();
    test_is_not_signed<unsigned int>();
    test_is_signed<long>();
    test_is_not_signed<unsigned long>();
    test_is_signed<long long>();
    test_is_not_signed<unsigned long long>();
    test_is_signed<float>();
    test_is_signed<double>();
    test_is_signed<long double>();
    test_is_not_signed<char8_t>();
    test_is_not_signed<char16_t>();
    test_is_not_signed<char32_t>();
    test_is_signed<wchar_t>();

    test_is_not_signed<phi::boolean>();
    test_is_signed<phi::integer<signed char>>();
    test_is_not_signed<phi::integer<unsigned char>>();
    test_is_signed<phi::integer<short>>();
    test_is_not_signed<phi::integer<unsigned short>>();
    test_is_signed<phi::integer<int>>();
    test_is_not_signed<phi::integer<unsigned int>>();
    test_is_signed<phi::integer<long>>();
    test_is_not_signed<phi::integer<unsigned long>>();
    test_is_signed<phi::integer<long long>>();
    test_is_not_signed<phi::integer<unsigned long long>>();
    test_is_signed<phi::floating_point<float>>();
    test_is_signed<phi::floating_point<double>>();
    test_is_signed<phi::floating_point<long double>>();

    test_is_not_signed<std::vector<int>>();
    test_is_not_signed<phi::scope_ptr<int>>();

    test_is_not_signed<int&>();
    test_is_not_signed<const int&>();
    test_is_not_signed<volatile int&>();
    test_is_not_signed<const volatile int&>();
    test_is_not_signed<int&&>();
    test_is_not_signed<const int&&>();
    test_is_not_signed<volatile int&&>();
    test_is_not_signed<const volatile int&&>();
    test_is_not_signed<int*>();
    test_is_not_signed<const int*>();
    test_is_not_signed<volatile int*>();
    test_is_not_signed<const volatile int*>();
    test_is_not_signed<int**>();
    test_is_not_signed<const int**>();
    test_is_not_signed<volatile int**>();
    test_is_not_signed<const volatile int**>();
    test_is_not_signed<int*&>();
    test_is_not_signed<const int*&>();
    test_is_not_signed<volatile int*&>();
    test_is_not_signed<const volatile int*&>();
    test_is_not_signed<int*&&>();
    test_is_not_signed<const int*&&>();
    test_is_not_signed<volatile int*&&>();
    test_is_not_signed<const volatile int*&&>();
    test_is_not_signed<void*>();
    test_is_not_signed<char[3]>();
    test_is_not_signed<char[]>();
    test_is_not_signed<char* [3]>();
    test_is_not_signed<char*[]>();
    test_is_not_signed<int(*)[3]>();
    test_is_not_signed<int(*)[]>();
    test_is_not_signed<int(&)[3]>();
    test_is_not_signed<int(&)[]>();
    test_is_not_signed<int(&&)[3]>();
    test_is_not_signed<int(&&)[]>();
    test_is_not_signed<char[3][2]>();
    test_is_not_signed<char[][2]>();
    test_is_not_signed<char* [3][2]>();
    test_is_not_signed<char*[][2]>();
    test_is_not_signed<int(*)[3][2]>();
    test_is_not_signed<int(*)[][2]>();
    test_is_not_signed<int(&)[3][2]>();
    test_is_not_signed<int(&)[][2]>();
    test_is_not_signed<int(&&)[3][2]>();
    test_is_not_signed<int(&&)[][2]>();
    test_is_not_signed<Class>();
    test_is_not_signed<Class[]>();
    test_is_not_signed<Class[2]>();
    test_is_not_signed<Template<void>>();
    test_is_not_signed<Template<int>>();
    test_is_not_signed<Template<Class>>();
    test_is_not_signed<Template<IncompleteType>>();
    test_is_not_signed<VariadicTemplate<>>();
    test_is_not_signed<VariadicTemplate<void>>();
    test_is_not_signed<VariadicTemplate<int>>();
    test_is_not_signed<VariadicTemplate<Class>>();
    test_is_not_signed<VariadicTemplate<IncompleteType>>();
    test_is_not_signed<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_signed<PublicDerivedFromTemplate<Base>>();
    test_is_not_signed<PublicDerivedFromTemplate<Derived>>();
    test_is_not_signed<PublicDerivedFromTemplate<Class>>();
    test_is_not_signed<PrivateDerivedFromTemplate<Base>>();
    test_is_not_signed<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_signed<PrivateDerivedFromTemplate<Class>>();
    test_is_not_signed<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_signed<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_signed<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_signed<Union>();
    test_is_not_signed<NonEmptyUnion>();
    test_is_not_signed<Empty>();
    test_is_not_signed<NotEmpty>();
    test_is_not_signed<BitZero>();
    test_is_not_signed<BitOne>();
    test_is_not_signed<Base>();
    test_is_not_signed<Derived>();
    test_is_not_signed<Abstract>();
    test_is_not_signed<PublicAbstract>();
    test_is_not_signed<PrivateAbstract>();
    test_is_not_signed<ProtectedAbstract>();
    test_is_not_signed<AbstractTemplate<int>>();
    test_is_not_signed<AbstractTemplate<double>>();
    test_is_not_signed<AbstractTemplate<Class>>();
    test_is_not_signed<AbstractTemplate<IncompleteType>>();
    test_is_not_signed<Final>();
    test_is_not_signed<PublicDestructor>();
    test_is_not_signed<ProtectedDestructor>();
    test_is_not_signed<PrivateDestructor>();
    test_is_not_signed<VirtualPublicDestructor>();
    test_is_not_signed<VirtualProtectedDestructor>();
    test_is_not_signed<VirtualPrivateDestructor>();
    test_is_not_signed<PurePublicDestructor>();
    test_is_not_signed<PureProtectedDestructor>();
    test_is_not_signed<PurePrivateDestructor>();
    test_is_not_signed<DeletedPublicDestructor>();
    test_is_not_signed<DeletedProtectedDestructor>();
    test_is_not_signed<DeletedPrivateDestructor>();
    test_is_not_signed<DeletedVirtualPublicDestructor>();
    test_is_not_signed<DeletedVirtualProtectedDestructor>();
    test_is_not_signed<DeletedVirtualPrivateDestructor>();
    test_is_not_signed<Enum>();
    test_is_not_signed<EnumSigned>();
    test_is_not_signed<EnumUnsigned>();
    test_is_not_signed<EnumClass>();
    test_is_not_signed<EnumStruct>();
    test_is_not_signed<Function>();
    test_is_not_signed<FunctionPtr>();
    test_is_not_signed<MemberObjectPtr>();
    test_is_not_signed<MemberFunctionPtr>();
    test_is_not_signed<IncompleteType>();
    test_is_not_signed<IncompleteTemplate<void>>();
    test_is_not_signed<IncompleteTemplate<int>>();
    test_is_not_signed<IncompleteTemplate<Class>>();
    test_is_not_signed<IncompleteTemplate<IncompleteType>>();
    test_is_not_signed<IncompleteVariadicTemplate<>>();
    test_is_not_signed<IncompleteVariadicTemplate<void>>();
    test_is_not_signed<IncompleteVariadicTemplate<int>>();
    test_is_not_signed<IncompleteVariadicTemplate<Class>>();
    test_is_not_signed<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_signed<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_signed<int Class::*>();
    test_is_not_signed<float Class::*>();
    test_is_not_signed<void * Class::*>();
    test_is_not_signed<int * Class::*>();
    test_is_not_signed<int Class::*&>();
    test_is_not_signed<float Class::*&>();
    test_is_not_signed<void * Class::*&>();
    test_is_not_signed<int * Class::*&>();
    test_is_not_signed<int Class::*&&>();
    test_is_not_signed<float Class::*&&>();
    test_is_not_signed<void * Class::*&&>();
    test_is_not_signed<int * Class::*&&>();
    test_is_not_signed<int Class::*const>();
    test_is_not_signed<float Class::*const>();
    test_is_not_signed<void * Class::*const>();
    test_is_not_signed<int Class::*const&>();
    test_is_not_signed<float Class::*const&>();
    test_is_not_signed<void * Class::*const&>();
    test_is_not_signed<int Class::*const&&>();
    test_is_not_signed<float Class::*const&&>();
    test_is_not_signed<void * Class::*const&&>();
    test_is_not_signed<int Class::*volatile>();
    test_is_not_signed<float Class::*volatile>();
    test_is_not_signed<void * Class::*volatile>();
    test_is_not_signed<int Class::*volatile&>();
    test_is_not_signed<float Class::*volatile&>();
    test_is_not_signed<void * Class::*volatile&>();
    test_is_not_signed<int Class::*volatile&&>();
    test_is_not_signed<float Class::*volatile&&>();
    test_is_not_signed<void * Class::*volatile&&>();
    test_is_not_signed<int Class::*const volatile>();
    test_is_not_signed<float Class::*const volatile>();
    test_is_not_signed<void * Class::*const volatile>();
    test_is_not_signed<int Class::*const volatile&>();
    test_is_not_signed<float Class::*const volatile&>();
    test_is_not_signed<void * Class::*const volatile&>();
    test_is_not_signed<int Class::*const volatile&&>();
    test_is_not_signed<float Class::*const volatile&&>();
    test_is_not_signed<void * Class::*const volatile&&>();
    test_is_not_signed<NonCopyable>();
    test_is_not_signed<NonMoveable>();
    test_is_not_signed<NonConstructible>();
    test_is_not_signed<Tracked>();
    test_is_not_signed<TrapConstructible>();
    test_is_not_signed<TrapImplicitConversion>();
    test_is_not_signed<TrapComma>();
    test_is_not_signed<TrapCall>();
    test_is_not_signed<TrapSelfAssign>();
    test_is_not_signed<TrapDeref>();
    test_is_not_signed<TrapArraySubscript>();

    test_is_not_signed<void()>();
    test_is_not_signed<void()&>();
    test_is_not_signed<void() &&>();
    test_is_not_signed<void() const>();
    test_is_not_signed<void() const&>();
    test_is_not_signed<void() const&&>();
    test_is_not_signed<void() volatile>();
    test_is_not_signed<void() volatile&>();
    test_is_not_signed<void() volatile&&>();
    test_is_not_signed<void() const volatile>();
    test_is_not_signed<void() const volatile&>();
    test_is_not_signed<void() const volatile&&>();
    test_is_not_signed<void() noexcept>();
    test_is_not_signed<void()& noexcept>();
    test_is_not_signed<void()&& noexcept>();
    test_is_not_signed<void() const noexcept>();
    test_is_not_signed<void() const& noexcept>();
    test_is_not_signed<void() const&& noexcept>();
    test_is_not_signed<void() volatile noexcept>();
    test_is_not_signed<void() volatile& noexcept>();
    test_is_not_signed<void() volatile&& noexcept>();
    test_is_not_signed<void() const volatile noexcept>();
    test_is_not_signed<void() const volatile& noexcept>();
    test_is_not_signed<void() const volatile&& noexcept>();

    test_is_not_signed<void(int)>();
    test_is_not_signed<void(int)&>();
    test_is_not_signed<void(int) &&>();
    test_is_not_signed<void(int) const>();
    test_is_not_signed<void(int) const&>();
    test_is_not_signed<void(int) const&&>();
    test_is_not_signed<void(int) volatile>();
    test_is_not_signed<void(int) volatile&>();
    test_is_not_signed<void(int) volatile&&>();
    test_is_not_signed<void(int) const volatile>();
    test_is_not_signed<void(int) const volatile&>();
    test_is_not_signed<void(int) const volatile&&>();
    test_is_not_signed<void(int) noexcept>();
    test_is_not_signed<void(int)& noexcept>();
    test_is_not_signed<void(int)&& noexcept>();
    test_is_not_signed<void(int) const noexcept>();
    test_is_not_signed<void(int) const& noexcept>();
    test_is_not_signed<void(int) const&& noexcept>();
    test_is_not_signed<void(int) volatile noexcept>();
    test_is_not_signed<void(int) volatile& noexcept>();
    test_is_not_signed<void(int) volatile&& noexcept>();
    test_is_not_signed<void(int) const volatile noexcept>();
    test_is_not_signed<void(int) const volatile& noexcept>();
    test_is_not_signed<void(int) const volatile&& noexcept>();

    test_is_not_signed<void(...)>();
    test_is_not_signed<void(...)&>();
    test_is_not_signed<void(...) &&>();
    test_is_not_signed<void(...) const>();
    test_is_not_signed<void(...) const&>();
    test_is_not_signed<void(...) const&&>();
    test_is_not_signed<void(...) volatile>();
    test_is_not_signed<void(...) volatile&>();
    test_is_not_signed<void(...) volatile&&>();
    test_is_not_signed<void(...) const volatile>();
    test_is_not_signed<void(...) const volatile&>();
    test_is_not_signed<void(...) const volatile&&>();
    test_is_not_signed<void(...) noexcept>();
    test_is_not_signed<void(...)& noexcept>();
    test_is_not_signed<void(...)&& noexcept>();
    test_is_not_signed<void(...) const noexcept>();
    test_is_not_signed<void(...) const& noexcept>();
    test_is_not_signed<void(...) const&& noexcept>();
    test_is_not_signed<void(...) volatile noexcept>();
    test_is_not_signed<void(...) volatile& noexcept>();
    test_is_not_signed<void(...) volatile&& noexcept>();
    test_is_not_signed<void(...) const volatile noexcept>();
    test_is_not_signed<void(...) const volatile& noexcept>();
    test_is_not_signed<void(...) const volatile&& noexcept>();

    test_is_not_signed<void(int, ...)>();
    test_is_not_signed<void(int, ...)&>();
    test_is_not_signed<void(int, ...) &&>();
    test_is_not_signed<void(int, ...) const>();
    test_is_not_signed<void(int, ...) const&>();
    test_is_not_signed<void(int, ...) const&&>();
    test_is_not_signed<void(int, ...) volatile>();
    test_is_not_signed<void(int, ...) volatile&>();
    test_is_not_signed<void(int, ...) volatile&&>();
    test_is_not_signed<void(int, ...) const volatile>();
    test_is_not_signed<void(int, ...) const volatile&>();
    test_is_not_signed<void(int, ...) const volatile&&>();
    test_is_not_signed<void(int, ...) noexcept>();
    test_is_not_signed<void(int, ...)& noexcept>();
    test_is_not_signed<void(int, ...)&& noexcept>();
    test_is_not_signed<void(int, ...) const noexcept>();
    test_is_not_signed<void(int, ...) const& noexcept>();
    test_is_not_signed<void(int, ...) const&& noexcept>();
    test_is_not_signed<void(int, ...) volatile noexcept>();
    test_is_not_signed<void(int, ...) volatile& noexcept>();
    test_is_not_signed<void(int, ...) volatile&& noexcept>();
    test_is_not_signed<void(int, ...) const volatile noexcept>();
    test_is_not_signed<void(int, ...) const volatile& noexcept>();
    test_is_not_signed<void(int, ...) const volatile&& noexcept>();

    test_is_not_signed<int()>();
    test_is_not_signed<int()&>();
    test_is_not_signed<int() &&>();
    test_is_not_signed<int() const>();
    test_is_not_signed<int() const&>();
    test_is_not_signed<int() const&&>();
    test_is_not_signed<int() volatile>();
    test_is_not_signed<int() volatile&>();
    test_is_not_signed<int() volatile&&>();
    test_is_not_signed<int() const volatile>();
    test_is_not_signed<int() const volatile&>();
    test_is_not_signed<int() const volatile&&>();
    test_is_not_signed<int() noexcept>();
    test_is_not_signed<int()& noexcept>();
    test_is_not_signed<int()&& noexcept>();
    test_is_not_signed<int() const noexcept>();
    test_is_not_signed<int() const& noexcept>();
    test_is_not_signed<int() const&& noexcept>();
    test_is_not_signed<int() volatile noexcept>();
    test_is_not_signed<int() volatile& noexcept>();
    test_is_not_signed<int() volatile&& noexcept>();
    test_is_not_signed<int() const volatile noexcept>();
    test_is_not_signed<int() const volatile& noexcept>();
    test_is_not_signed<int() const volatile&& noexcept>();

    test_is_not_signed<int(int)>();
    test_is_not_signed<int(int)&>();
    test_is_not_signed<int(int) &&>();
    test_is_not_signed<int(int) const>();
    test_is_not_signed<int(int) const&>();
    test_is_not_signed<int(int) const&&>();
    test_is_not_signed<int(int) volatile>();
    test_is_not_signed<int(int) volatile&>();
    test_is_not_signed<int(int) volatile&&>();
    test_is_not_signed<int(int) const volatile>();
    test_is_not_signed<int(int) const volatile&>();
    test_is_not_signed<int(int) const volatile&&>();
    test_is_not_signed<int(int) noexcept>();
    test_is_not_signed<int(int)& noexcept>();
    test_is_not_signed<int(int)&& noexcept>();
    test_is_not_signed<int(int) const noexcept>();
    test_is_not_signed<int(int) const& noexcept>();
    test_is_not_signed<int(int) const&& noexcept>();
    test_is_not_signed<int(int) volatile noexcept>();
    test_is_not_signed<int(int) volatile& noexcept>();
    test_is_not_signed<int(int) volatile&& noexcept>();
    test_is_not_signed<int(int) const volatile noexcept>();
    test_is_not_signed<int(int) const volatile& noexcept>();
    test_is_not_signed<int(int) const volatile&& noexcept>();

    test_is_not_signed<int(...)>();
    test_is_not_signed<int(...)&>();
    test_is_not_signed<int(...) &&>();
    test_is_not_signed<int(...) const>();
    test_is_not_signed<int(...) const&>();
    test_is_not_signed<int(...) const&&>();
    test_is_not_signed<int(...) volatile>();
    test_is_not_signed<int(...) volatile&>();
    test_is_not_signed<int(...) volatile&&>();
    test_is_not_signed<int(...) const volatile>();
    test_is_not_signed<int(...) const volatile&>();
    test_is_not_signed<int(...) const volatile&&>();
    test_is_not_signed<int(...) noexcept>();
    test_is_not_signed<int(...)& noexcept>();
    test_is_not_signed<int(...)&& noexcept>();
    test_is_not_signed<int(...) const noexcept>();
    test_is_not_signed<int(...) const& noexcept>();
    test_is_not_signed<int(...) const&& noexcept>();
    test_is_not_signed<int(...) volatile noexcept>();
    test_is_not_signed<int(...) volatile& noexcept>();
    test_is_not_signed<int(...) volatile&& noexcept>();
    test_is_not_signed<int(...) const volatile noexcept>();
    test_is_not_signed<int(...) const volatile& noexcept>();
    test_is_not_signed<int(...) const volatile&& noexcept>();

    test_is_not_signed<int(int, ...)>();
    test_is_not_signed<int(int, ...)&>();
    test_is_not_signed<int(int, ...) &&>();
    test_is_not_signed<int(int, ...) const>();
    test_is_not_signed<int(int, ...) const&>();
    test_is_not_signed<int(int, ...) const&&>();
    test_is_not_signed<int(int, ...) volatile>();
    test_is_not_signed<int(int, ...) volatile&>();
    test_is_not_signed<int(int, ...) volatile&&>();
    test_is_not_signed<int(int, ...) const volatile>();
    test_is_not_signed<int(int, ...) const volatile&>();
    test_is_not_signed<int(int, ...) const volatile&&>();
    test_is_not_signed<int(int, ...) noexcept>();
    test_is_not_signed<int(int, ...)& noexcept>();
    test_is_not_signed<int(int, ...)&& noexcept>();
    test_is_not_signed<int(int, ...) const noexcept>();
    test_is_not_signed<int(int, ...) const& noexcept>();
    test_is_not_signed<int(int, ...) const&& noexcept>();
    test_is_not_signed<int(int, ...) volatile noexcept>();
    test_is_not_signed<int(int, ...) volatile& noexcept>();
    test_is_not_signed<int(int, ...) volatile&& noexcept>();
    test_is_not_signed<int(int, ...) const volatile noexcept>();
    test_is_not_signed<int(int, ...) const volatile& noexcept>();
    test_is_not_signed<int(int, ...) const volatile&& noexcept>();

    test_is_not_signed<void (*)()>();
    test_is_not_signed<void (*)() noexcept>();

    test_is_not_signed<void (*)(int)>();
    test_is_not_signed<void (*)(int) noexcept>();

    test_is_not_signed<void (*)(...)>();
    test_is_not_signed<void (*)(...) noexcept>();

    test_is_not_signed<void (*)(int, ...)>();
    test_is_not_signed<void (*)(int, ...) noexcept>();

    test_is_not_signed<int (*)()>();
    test_is_not_signed<int (*)() noexcept>();

    test_is_not_signed<int (*)(int)>();
    test_is_not_signed<int (*)(int) noexcept>();

    test_is_not_signed<int (*)(...)>();
    test_is_not_signed<int (*)(...) noexcept>();

    test_is_not_signed<int (*)(int, ...)>();
    test_is_not_signed<int (*)(int, ...) noexcept>();

    test_is_not_signed<void (&)()>();
    test_is_not_signed<void (&)() noexcept>();

    test_is_not_signed<void (&)(int)>();
    test_is_not_signed<void (&)(int) noexcept>();

    test_is_not_signed<void (&)(...)>();
    test_is_not_signed<void (&)(...) noexcept>();

    test_is_not_signed<void (&)(int, ...)>();
    test_is_not_signed<void (&)(int, ...) noexcept>();

    test_is_not_signed<int (&)()>();
    test_is_not_signed<int (&)() noexcept>();

    test_is_not_signed<int (&)(int)>();
    test_is_not_signed<int (&)(int) noexcept>();

    test_is_not_signed<int (&)(...)>();
    test_is_not_signed<int (&)(...) noexcept>();

    test_is_not_signed<int (&)(int, ...)>();
    test_is_not_signed<int (&)(int, ...) noexcept>();

    test_is_not_signed<void(&&)()>();
    test_is_not_signed<void(&&)() noexcept>();

    test_is_not_signed<void(&&)(int)>();
    test_is_not_signed<void(&&)(int) noexcept>();

    test_is_not_signed<void(&&)(...)>();
    test_is_not_signed<void(&&)(...) noexcept>();

    test_is_not_signed<void(&&)(int, ...)>();
    test_is_not_signed<void(&&)(int, ...) noexcept>();

    test_is_not_signed<int(&&)()>();
    test_is_not_signed<int(&&)() noexcept>();

    test_is_not_signed<int(&&)(int)>();
    test_is_not_signed<int(&&)(int) noexcept>();

    test_is_not_signed<int(&&)(...)>();
    test_is_not_signed<int(&&)(...) noexcept>();

    test_is_not_signed<int(&&)(int, ...)>();
    test_is_not_signed<int(&&)(int, ...) noexcept>();

    test_is_not_signed<void (Class::*)()>();
    test_is_not_signed<void (Class::*)()&>();
    test_is_not_signed<void (Class::*)() &&>();
    test_is_not_signed<void (Class::*)() const>();
    test_is_not_signed<void (Class::*)() const&>();
    test_is_not_signed<void (Class::*)() const&&>();
    test_is_not_signed<void (Class::*)() noexcept>();
    test_is_not_signed<void (Class::*)()& noexcept>();
    test_is_not_signed<void (Class::*)()&& noexcept>();
    test_is_not_signed<void (Class::*)() const noexcept>();
    test_is_not_signed<void (Class::*)() const& noexcept>();
    test_is_not_signed<void (Class::*)() const&& noexcept>();

    test_is_not_signed<void (Class::*)(int)>();
    test_is_not_signed<void (Class::*)(int)&>();
    test_is_not_signed<void (Class::*)(int) &&>();
    test_is_not_signed<void (Class::*)(int) const>();
    test_is_not_signed<void (Class::*)(int) const&>();
    test_is_not_signed<void (Class::*)(int) const&&>();
    test_is_not_signed<void (Class::*)(int) noexcept>();
    test_is_not_signed<void (Class::*)(int)& noexcept>();
    test_is_not_signed<void (Class::*)(int)&& noexcept>();
    test_is_not_signed<void (Class::*)(int) const noexcept>();
    test_is_not_signed<void (Class::*)(int) const& noexcept>();
    test_is_not_signed<void (Class::*)(int) const&& noexcept>();

    test_is_not_signed<void (Class::*)(...)>();
    test_is_not_signed<void (Class::*)(...)&>();
    test_is_not_signed<void (Class::*)(...) &&>();
    test_is_not_signed<void (Class::*)(...) const>();
    test_is_not_signed<void (Class::*)(...) const&>();
    test_is_not_signed<void (Class::*)(...) const&&>();
    test_is_not_signed<void (Class::*)(...) noexcept>();
    test_is_not_signed<void (Class::*)(...)& noexcept>();
    test_is_not_signed<void (Class::*)(...)&& noexcept>();
    test_is_not_signed<void (Class::*)(...) const noexcept>();
    test_is_not_signed<void (Class::*)(...) const& noexcept>();
    test_is_not_signed<void (Class::*)(...) const&& noexcept>();

    test_is_not_signed<void (Class::*)(int, ...)>();
    test_is_not_signed<void (Class::*)(int, ...)&>();
    test_is_not_signed<void (Class::*)(int, ...) &&>();
    test_is_not_signed<void (Class::*)(int, ...) const>();
    test_is_not_signed<void (Class::*)(int, ...) const&>();
    test_is_not_signed<void (Class::*)(int, ...) const&&>();
    test_is_not_signed<void (Class::*)(int, ...) noexcept>();
    test_is_not_signed<void (Class::*)(int, ...)& noexcept>();
    test_is_not_signed<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_signed<void (Class::*)(int, ...) const noexcept>();
    test_is_not_signed<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_signed<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_signed<int (Class::*)()>();
    test_is_not_signed<int (Class::*)()&>();
    test_is_not_signed<int (Class::*)() &&>();
    test_is_not_signed<int (Class::*)() const>();
    test_is_not_signed<int (Class::*)() const&>();
    test_is_not_signed<int (Class::*)() const&&>();
    test_is_not_signed<int (Class::*)() noexcept>();
    test_is_not_signed<int (Class::*)()& noexcept>();
    test_is_not_signed<int (Class::*)()&& noexcept>();
    test_is_not_signed<int (Class::*)() const noexcept>();
    test_is_not_signed<int (Class::*)() const& noexcept>();
    test_is_not_signed<int (Class::*)() const&& noexcept>();

    test_is_not_signed<int (Class::*)(int)>();
    test_is_not_signed<int (Class::*)(int)&>();
    test_is_not_signed<int (Class::*)(int) &&>();
    test_is_not_signed<int (Class::*)(int) const>();
    test_is_not_signed<int (Class::*)(int) const&>();
    test_is_not_signed<int (Class::*)(int) const&&>();
    test_is_not_signed<int (Class::*)(int) noexcept>();
    test_is_not_signed<int (Class::*)(int)& noexcept>();
    test_is_not_signed<int (Class::*)(int)&& noexcept>();
    test_is_not_signed<int (Class::*)(int) const noexcept>();
    test_is_not_signed<int (Class::*)(int) const& noexcept>();
    test_is_not_signed<int (Class::*)(int) const&& noexcept>();

    test_is_not_signed<int (Class::*)(...)>();
    test_is_not_signed<int (Class::*)(...)&>();
    test_is_not_signed<int (Class::*)(...) &&>();
    test_is_not_signed<int (Class::*)(...) const>();
    test_is_not_signed<int (Class::*)(...) const&>();
    test_is_not_signed<int (Class::*)(...) const&&>();
    test_is_not_signed<int (Class::*)(...) noexcept>();
    test_is_not_signed<int (Class::*)(...)& noexcept>();
    test_is_not_signed<int (Class::*)(...)&& noexcept>();
    test_is_not_signed<int (Class::*)(...) const noexcept>();
    test_is_not_signed<int (Class::*)(...) const& noexcept>();
    test_is_not_signed<int (Class::*)(...) const&& noexcept>();

    test_is_not_signed<int (Class::*)(int, ...)>();
    test_is_not_signed<int (Class::*)(int, ...)&>();
    test_is_not_signed<int (Class::*)(int, ...) &&>();
    test_is_not_signed<int (Class::*)(int, ...) const>();
    test_is_not_signed<int (Class::*)(int, ...) const&>();
    test_is_not_signed<int (Class::*)(int, ...) const&&>();
    test_is_not_signed<int (Class::*)(int, ...) noexcept>();
    test_is_not_signed<int (Class::*)(int, ...)& noexcept>();
    test_is_not_signed<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_signed<int (Class::*)(int, ...) const noexcept>();
    test_is_not_signed<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_signed<int (Class::*)(int, ...) const&& noexcept>();
}
