#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_volatile.hpp>
#include <vector>

template <typename T>
void test_is_volatile_impl()
{
    STATIC_REQUIRE(phi::is_volatile<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_volatile<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_volatile_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_volatile_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_volatile<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_volatile<T>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_volatile<T>::value);
}

template <typename T>
void test_is_not_volatile_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_volatile<T>::value);
    STATIC_REQUIRE(phi::is_not_volatile<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_volatile_v<T>);
    STATIC_REQUIRE(phi::is_not_volatile_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_volatile<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_volatile<T>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_volatile<T>::value);
}

template <typename T>
void test_is_volatile()
{
    test_is_not_volatile_impl<T>();
    test_is_not_volatile_impl<const T>();
    test_is_volatile_impl<volatile T>();
    test_is_volatile_impl<const volatile T>();
}

template <typename T>
void test_is_volatile_cv()
{
    test_is_volatile_impl<T>();
    test_is_volatile_impl<const T>();
    test_is_volatile_impl<volatile T>();
    test_is_volatile_impl<const volatile T>();
}

template <typename T>
void test_is_not_volatile()
{
    test_is_not_volatile_impl<T>();
    test_is_not_volatile_impl<const T>();
    test_is_not_volatile_impl<volatile T>();
    test_is_not_volatile_impl<const volatile T>();
}

TEST_CASE("is_volatile")
{
    test_is_volatile<void>();
    test_is_volatile<phi::nullptr_t>();
    test_is_volatile<bool>();
    test_is_volatile<char>();
    test_is_volatile<signed char>();
    test_is_volatile<unsigned char>();
    test_is_volatile<short>();
    test_is_volatile<unsigned short>();
    test_is_volatile<int>();
    test_is_volatile<unsigned int>();
    test_is_volatile<long>();
    test_is_volatile<unsigned long>();
    test_is_volatile<long long>();
    test_is_volatile<unsigned long long>();
    test_is_volatile<float>();
    test_is_volatile<double>();
    test_is_volatile<long double>();
    test_is_volatile<char8_t>();
    test_is_volatile<char16_t>();
    test_is_volatile<char32_t>();
    test_is_volatile<wchar_t>();

    test_is_volatile<phi::boolean>();
    test_is_volatile<phi::integer<signed char>>();
    test_is_volatile<phi::integer<unsigned char>>();
    test_is_volatile<phi::integer<short>>();
    test_is_volatile<phi::integer<unsigned short>>();
    test_is_volatile<phi::integer<int>>();
    test_is_volatile<phi::integer<unsigned int>>();
    test_is_volatile<phi::integer<long>>();
    test_is_volatile<phi::integer<unsigned long>>();
    test_is_volatile<phi::integer<long long>>();
    test_is_volatile<phi::integer<unsigned long long>>();
    test_is_volatile<phi::floating_point<float>>();
    test_is_volatile<phi::floating_point<double>>();
    test_is_volatile<phi::floating_point<long double>>();

    test_is_volatile<std::vector<int>>();
    test_is_volatile<phi::scope_ptr<int>>();

    test_is_not_volatile<int&>();
    test_is_not_volatile<const int&>();
    test_is_not_volatile<volatile int&>();
    test_is_not_volatile<const volatile int&>();
    test_is_not_volatile<int&&>();
    test_is_not_volatile<const int&&>();
    test_is_not_volatile<volatile int&&>();
    test_is_not_volatile<const volatile int&&>();
    test_is_volatile<int*>();
    test_is_volatile<const int*>();
    test_is_volatile<volatile int*>();
    test_is_volatile<const volatile int*>();
    test_is_volatile<int**>();
    test_is_volatile<const int**>();
    test_is_volatile<volatile int**>();
    test_is_volatile<const volatile int**>();
    test_is_not_volatile<int*&>();
    test_is_not_volatile<const int*&>();
    test_is_not_volatile<volatile int*&>();
    test_is_not_volatile<const volatile int*&>();
    test_is_not_volatile<int*&&>();
    test_is_not_volatile<const int*&&>();
    test_is_not_volatile<volatile int*&&>();
    test_is_not_volatile<const volatile int*&&>();
    test_is_volatile<void*>();
    test_is_volatile<char[3]>();
    test_is_volatile<char[]>();
    test_is_volatile<char* [3]>();
    test_is_volatile<char*[]>();
    test_is_volatile<int(*)[3]>();
    test_is_volatile<int(*)[]>();
    test_is_not_volatile<int(&)[3]>();
    test_is_not_volatile<int(&)[]>();
    test_is_not_volatile<int(&&)[3]>();
    test_is_not_volatile<int(&&)[]>();
    test_is_volatile<char[3][2]>();
    test_is_volatile<char[][2]>();
    test_is_volatile<char* [3][2]>();
    test_is_volatile<char*[][2]>();
    test_is_volatile<int(*)[3][2]>();
    test_is_volatile<int(*)[][2]>();
    test_is_not_volatile<int(&)[3][2]>();
    test_is_not_volatile<int(&)[][2]>();
    test_is_not_volatile<int(&&)[3][2]>();
    test_is_not_volatile<int(&&)[][2]>();
    test_is_volatile<Class>();
    test_is_volatile<Class[]>();
    test_is_volatile<Class[2]>();
    test_is_volatile<Template<void>>();
    test_is_volatile<Template<int>>();
    test_is_volatile<Template<Class>>();
    test_is_volatile<Template<IncompleteType>>();
    test_is_volatile<VariadicTemplate<>>();
    test_is_volatile<VariadicTemplate<void>>();
    test_is_volatile<VariadicTemplate<int>>();
    test_is_volatile<VariadicTemplate<Class>>();
    test_is_volatile<VariadicTemplate<IncompleteType>>();
    test_is_volatile<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_volatile<PublicDerivedFromTemplate<Base>>();
    test_is_volatile<PublicDerivedFromTemplate<Derived>>();
    test_is_volatile<PublicDerivedFromTemplate<Class>>();
    test_is_volatile<PrivateDerivedFromTemplate<Base>>();
    test_is_volatile<PrivateDerivedFromTemplate<Derived>>();
    test_is_volatile<PrivateDerivedFromTemplate<Class>>();
    test_is_volatile<ProtectedDerivedFromTemplate<Base>>();
    test_is_volatile<ProtectedDerivedFromTemplate<Derived>>();
    test_is_volatile<ProtectedDerivedFromTemplate<Class>>();
    test_is_volatile<Union>();
    test_is_volatile<NonEmptyUnion>();
    test_is_volatile<Empty>();
    test_is_volatile<NotEmpty>();
    test_is_volatile<BitZero>();
    test_is_volatile<BitOne>();
    test_is_volatile<Base>();
    test_is_volatile<Derived>();
    test_is_volatile<Abstract>();
    test_is_volatile<PublicAbstract>();
    test_is_volatile<PrivateAbstract>();
    test_is_volatile<ProtectedAbstract>();
    test_is_volatile<AbstractTemplate<int>>();
    test_is_volatile<AbstractTemplate<double>>();
    test_is_volatile<AbstractTemplate<Class>>();
    test_is_volatile<AbstractTemplate<IncompleteType>>();
    test_is_volatile<Final>();
    test_is_volatile<PublicDestructor>();
    test_is_volatile<ProtectedDestructor>();
    test_is_volatile<PrivateDestructor>();
    test_is_volatile<VirtualPublicDestructor>();
    test_is_volatile<VirtualProtectedDestructor>();
    test_is_volatile<VirtualPrivateDestructor>();
    test_is_volatile<PurePublicDestructor>();
    test_is_volatile<PureProtectedDestructor>();
    test_is_volatile<PurePrivateDestructor>();
    test_is_volatile<DeletedPublicDestructor>();
    test_is_volatile<DeletedProtectedDestructor>();
    test_is_volatile<DeletedPrivateDestructor>();
    test_is_volatile<DeletedVirtualPublicDestructor>();
    test_is_volatile<DeletedVirtualProtectedDestructor>();
    test_is_volatile<DeletedVirtualPrivateDestructor>();
    test_is_volatile<Enum>();
    test_is_volatile<EnumSigned>();
    test_is_volatile<EnumUnsigned>();
    test_is_volatile<EnumClass>();
    test_is_volatile<EnumStruct>();
    test_is_not_volatile<Function>();
    test_is_volatile<FunctionPtr>();
    test_is_volatile<MemberObjectPtr>();
    test_is_volatile<MemberFunctionPtr>();
    test_is_volatile<IncompleteType>();
    test_is_volatile<IncompleteTemplate<void>>();
    test_is_volatile<IncompleteTemplate<int>>();
    test_is_volatile<IncompleteTemplate<Class>>();
    test_is_volatile<IncompleteTemplate<IncompleteType>>();
    test_is_volatile<IncompleteVariadicTemplate<>>();
    test_is_volatile<IncompleteVariadicTemplate<void>>();
    test_is_volatile<IncompleteVariadicTemplate<int>>();
    test_is_volatile<IncompleteVariadicTemplate<Class>>();
    test_is_volatile<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_volatile<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_volatile<int Class::*>();
    test_is_volatile<float Class::*>();
    test_is_volatile<void * Class::*>();
    test_is_volatile<int * Class::*>();
    test_is_not_volatile<int Class::*&>();
    test_is_not_volatile<float Class::*&>();
    test_is_not_volatile<void * Class::*&>();
    test_is_not_volatile<int * Class::*&>();
    test_is_not_volatile<int Class::*&&>();
    test_is_not_volatile<float Class::*&&>();
    test_is_not_volatile<void * Class::*&&>();
    test_is_not_volatile<int * Class::*&&>();
    test_is_volatile<int Class::*const>();
    test_is_volatile<float Class::*const>();
    test_is_volatile<void * Class::*const>();
    test_is_not_volatile<int Class::*const&>();
    test_is_not_volatile<float Class::*const&>();
    test_is_not_volatile<void * Class::*const&>();
    test_is_not_volatile<int Class::*const&&>();
    test_is_not_volatile<float Class::*const&&>();
    test_is_not_volatile<void * Class::*const&&>();
    test_is_volatile_cv<int Class::*volatile>();
    test_is_volatile_cv<float Class::*volatile>();
    test_is_volatile_cv<void * Class::*volatile>();
    test_is_not_volatile<int Class::*volatile&>();
    test_is_not_volatile<float Class::*volatile&>();
    test_is_not_volatile<void * Class::*volatile&>();
    test_is_not_volatile<int Class::*volatile&&>();
    test_is_not_volatile<float Class::*volatile&&>();
    test_is_not_volatile<void * Class::*volatile&&>();
    test_is_volatile_cv<int Class::*const volatile>();
    test_is_volatile_cv<float Class::*const volatile>();
    test_is_volatile_cv<void * Class::*const volatile>();
    test_is_not_volatile<int Class::*const volatile&>();
    test_is_not_volatile<float Class::*const volatile&>();
    test_is_not_volatile<void * Class::*const volatile&>();
    test_is_not_volatile<int Class::*const volatile&&>();
    test_is_not_volatile<float Class::*const volatile&&>();
    test_is_not_volatile<void * Class::*const volatile&&>();
    test_is_volatile<NonCopyable>();
    test_is_volatile<NonMoveable>();
    test_is_volatile<NonConstructible>();
    test_is_volatile<Tracked>();
    test_is_volatile<TrapConstructible>();
    test_is_volatile<TrapImplicitConversion>();
    test_is_volatile<TrapComma>();
    test_is_volatile<TrapCall>();
    test_is_volatile<TrapSelfAssign>();
    test_is_volatile<TrapDeref>();
    test_is_volatile<TrapArraySubscript>();

    test_is_not_volatile<void()>();
    test_is_not_volatile<void()&>();
    test_is_not_volatile<void() &&>();
    test_is_not_volatile<void() const>();
    test_is_not_volatile<void() const&>();
    test_is_not_volatile<void() const&&>();
    test_is_not_volatile<void() volatile>();
    test_is_not_volatile<void() volatile&>();
    test_is_not_volatile<void() volatile&&>();
    test_is_not_volatile<void() const volatile>();
    test_is_not_volatile<void() const volatile&>();
    test_is_not_volatile<void() const volatile&&>();
    test_is_not_volatile<void() noexcept>();
    test_is_not_volatile<void()& noexcept>();
    test_is_not_volatile<void()&& noexcept>();
    test_is_not_volatile<void() const noexcept>();
    test_is_not_volatile<void() const& noexcept>();
    test_is_not_volatile<void() const&& noexcept>();
    test_is_not_volatile<void() volatile noexcept>();
    test_is_not_volatile<void() volatile& noexcept>();
    test_is_not_volatile<void() volatile&& noexcept>();
    test_is_not_volatile<void() const volatile noexcept>();
    test_is_not_volatile<void() const volatile& noexcept>();
    test_is_not_volatile<void() const volatile&& noexcept>();

    test_is_not_volatile<void(int)>();
    test_is_not_volatile<void(int)&>();
    test_is_not_volatile<void(int) &&>();
    test_is_not_volatile<void(int) const>();
    test_is_not_volatile<void(int) const&>();
    test_is_not_volatile<void(int) const&&>();
    test_is_not_volatile<void(int) volatile>();
    test_is_not_volatile<void(int) volatile&>();
    test_is_not_volatile<void(int) volatile&&>();
    test_is_not_volatile<void(int) const volatile>();
    test_is_not_volatile<void(int) const volatile&>();
    test_is_not_volatile<void(int) const volatile&&>();
    test_is_not_volatile<void(int) noexcept>();
    test_is_not_volatile<void(int)& noexcept>();
    test_is_not_volatile<void(int)&& noexcept>();
    test_is_not_volatile<void(int) const noexcept>();
    test_is_not_volatile<void(int) const& noexcept>();
    test_is_not_volatile<void(int) const&& noexcept>();
    test_is_not_volatile<void(int) volatile noexcept>();
    test_is_not_volatile<void(int) volatile& noexcept>();
    test_is_not_volatile<void(int) volatile&& noexcept>();
    test_is_not_volatile<void(int) const volatile noexcept>();
    test_is_not_volatile<void(int) const volatile& noexcept>();
    test_is_not_volatile<void(int) const volatile&& noexcept>();

    test_is_not_volatile<void(...)>();
    test_is_not_volatile<void(...)&>();
    test_is_not_volatile<void(...) &&>();
    test_is_not_volatile<void(...) const>();
    test_is_not_volatile<void(...) const&>();
    test_is_not_volatile<void(...) const&&>();
    test_is_not_volatile<void(...) volatile>();
    test_is_not_volatile<void(...) volatile&>();
    test_is_not_volatile<void(...) volatile&&>();
    test_is_not_volatile<void(...) const volatile>();
    test_is_not_volatile<void(...) const volatile&>();
    test_is_not_volatile<void(...) const volatile&&>();
    test_is_not_volatile<void(...) noexcept>();
    test_is_not_volatile<void(...)& noexcept>();
    test_is_not_volatile<void(...)&& noexcept>();
    test_is_not_volatile<void(...) const noexcept>();
    test_is_not_volatile<void(...) const& noexcept>();
    test_is_not_volatile<void(...) const&& noexcept>();
    test_is_not_volatile<void(...) volatile noexcept>();
    test_is_not_volatile<void(...) volatile& noexcept>();
    test_is_not_volatile<void(...) volatile&& noexcept>();
    test_is_not_volatile<void(...) const volatile noexcept>();
    test_is_not_volatile<void(...) const volatile& noexcept>();
    test_is_not_volatile<void(...) const volatile&& noexcept>();

    test_is_not_volatile<void(int, ...)>();
    test_is_not_volatile<void(int, ...)&>();
    test_is_not_volatile<void(int, ...) &&>();
    test_is_not_volatile<void(int, ...) const>();
    test_is_not_volatile<void(int, ...) const&>();
    test_is_not_volatile<void(int, ...) const&&>();
    test_is_not_volatile<void(int, ...) volatile>();
    test_is_not_volatile<void(int, ...) volatile&>();
    test_is_not_volatile<void(int, ...) volatile&&>();
    test_is_not_volatile<void(int, ...) const volatile>();
    test_is_not_volatile<void(int, ...) const volatile&>();
    test_is_not_volatile<void(int, ...) const volatile&&>();
    test_is_not_volatile<void(int, ...) noexcept>();
    test_is_not_volatile<void(int, ...)& noexcept>();
    test_is_not_volatile<void(int, ...)&& noexcept>();
    test_is_not_volatile<void(int, ...) const noexcept>();
    test_is_not_volatile<void(int, ...) const& noexcept>();
    test_is_not_volatile<void(int, ...) const&& noexcept>();
    test_is_not_volatile<void(int, ...) volatile noexcept>();
    test_is_not_volatile<void(int, ...) volatile& noexcept>();
    test_is_not_volatile<void(int, ...) volatile&& noexcept>();
    test_is_not_volatile<void(int, ...) const volatile noexcept>();
    test_is_not_volatile<void(int, ...) const volatile& noexcept>();
    test_is_not_volatile<void(int, ...) const volatile&& noexcept>();

    test_is_not_volatile<int()>();
    test_is_not_volatile<int()&>();
    test_is_not_volatile<int() &&>();
    test_is_not_volatile<int() const>();
    test_is_not_volatile<int() const&>();
    test_is_not_volatile<int() const&&>();
    test_is_not_volatile<int() volatile>();
    test_is_not_volatile<int() volatile&>();
    test_is_not_volatile<int() volatile&&>();
    test_is_not_volatile<int() const volatile>();
    test_is_not_volatile<int() const volatile&>();
    test_is_not_volatile<int() const volatile&&>();
    test_is_not_volatile<int() noexcept>();
    test_is_not_volatile<int()& noexcept>();
    test_is_not_volatile<int()&& noexcept>();
    test_is_not_volatile<int() const noexcept>();
    test_is_not_volatile<int() const& noexcept>();
    test_is_not_volatile<int() const&& noexcept>();
    test_is_not_volatile<int() volatile noexcept>();
    test_is_not_volatile<int() volatile& noexcept>();
    test_is_not_volatile<int() volatile&& noexcept>();
    test_is_not_volatile<int() const volatile noexcept>();
    test_is_not_volatile<int() const volatile& noexcept>();
    test_is_not_volatile<int() const volatile&& noexcept>();

    test_is_not_volatile<int(int)>();
    test_is_not_volatile<int(int)&>();
    test_is_not_volatile<int(int) &&>();
    test_is_not_volatile<int(int) const>();
    test_is_not_volatile<int(int) const&>();
    test_is_not_volatile<int(int) const&&>();
    test_is_not_volatile<int(int) volatile>();
    test_is_not_volatile<int(int) volatile&>();
    test_is_not_volatile<int(int) volatile&&>();
    test_is_not_volatile<int(int) const volatile>();
    test_is_not_volatile<int(int) const volatile&>();
    test_is_not_volatile<int(int) const volatile&&>();
    test_is_not_volatile<int(int) noexcept>();
    test_is_not_volatile<int(int)& noexcept>();
    test_is_not_volatile<int(int)&& noexcept>();
    test_is_not_volatile<int(int) const noexcept>();
    test_is_not_volatile<int(int) const& noexcept>();
    test_is_not_volatile<int(int) const&& noexcept>();
    test_is_not_volatile<int(int) volatile noexcept>();
    test_is_not_volatile<int(int) volatile& noexcept>();
    test_is_not_volatile<int(int) volatile&& noexcept>();
    test_is_not_volatile<int(int) const volatile noexcept>();
    test_is_not_volatile<int(int) const volatile& noexcept>();
    test_is_not_volatile<int(int) const volatile&& noexcept>();

    test_is_not_volatile<int(...)>();
    test_is_not_volatile<int(...)&>();
    test_is_not_volatile<int(...) &&>();
    test_is_not_volatile<int(...) const>();
    test_is_not_volatile<int(...) const&>();
    test_is_not_volatile<int(...) const&&>();
    test_is_not_volatile<int(...) volatile>();
    test_is_not_volatile<int(...) volatile&>();
    test_is_not_volatile<int(...) volatile&&>();
    test_is_not_volatile<int(...) const volatile>();
    test_is_not_volatile<int(...) const volatile&>();
    test_is_not_volatile<int(...) const volatile&&>();
    test_is_not_volatile<int(...) noexcept>();
    test_is_not_volatile<int(...)& noexcept>();
    test_is_not_volatile<int(...)&& noexcept>();
    test_is_not_volatile<int(...) const noexcept>();
    test_is_not_volatile<int(...) const& noexcept>();
    test_is_not_volatile<int(...) const&& noexcept>();
    test_is_not_volatile<int(...) volatile noexcept>();
    test_is_not_volatile<int(...) volatile& noexcept>();
    test_is_not_volatile<int(...) volatile&& noexcept>();
    test_is_not_volatile<int(...) const volatile noexcept>();
    test_is_not_volatile<int(...) const volatile& noexcept>();
    test_is_not_volatile<int(...) const volatile&& noexcept>();

    test_is_not_volatile<int(int, ...)>();
    test_is_not_volatile<int(int, ...)&>();
    test_is_not_volatile<int(int, ...) &&>();
    test_is_not_volatile<int(int, ...) const>();
    test_is_not_volatile<int(int, ...) const&>();
    test_is_not_volatile<int(int, ...) const&&>();
    test_is_not_volatile<int(int, ...) volatile>();
    test_is_not_volatile<int(int, ...) volatile&>();
    test_is_not_volatile<int(int, ...) volatile&&>();
    test_is_not_volatile<int(int, ...) const volatile>();
    test_is_not_volatile<int(int, ...) const volatile&>();
    test_is_not_volatile<int(int, ...) const volatile&&>();
    test_is_not_volatile<int(int, ...) noexcept>();
    test_is_not_volatile<int(int, ...)& noexcept>();
    test_is_not_volatile<int(int, ...)&& noexcept>();
    test_is_not_volatile<int(int, ...) const noexcept>();
    test_is_not_volatile<int(int, ...) const& noexcept>();
    test_is_not_volatile<int(int, ...) const&& noexcept>();
    test_is_not_volatile<int(int, ...) volatile noexcept>();
    test_is_not_volatile<int(int, ...) volatile& noexcept>();
    test_is_not_volatile<int(int, ...) volatile&& noexcept>();
    test_is_not_volatile<int(int, ...) const volatile noexcept>();
    test_is_not_volatile<int(int, ...) const volatile& noexcept>();
    test_is_not_volatile<int(int, ...) const volatile&& noexcept>();

    test_is_volatile<void (*)()>();
    test_is_volatile<void (*)() noexcept>();

    test_is_volatile<void (*)(int)>();
    test_is_volatile<void (*)(int) noexcept>();

    test_is_volatile<void (*)(...)>();
    test_is_volatile<void (*)(...) noexcept>();

    test_is_volatile<void (*)(int, ...)>();
    test_is_volatile<void (*)(int, ...) noexcept>();

    test_is_volatile<int (*)()>();
    test_is_volatile<int (*)() noexcept>();

    test_is_volatile<int (*)(int)>();
    test_is_volatile<int (*)(int) noexcept>();

    test_is_volatile<int (*)(...)>();
    test_is_volatile<int (*)(...) noexcept>();

    test_is_volatile<int (*)(int, ...)>();
    test_is_volatile<int (*)(int, ...) noexcept>();

    test_is_not_volatile<void (&)()>();
    test_is_not_volatile<void (&)() noexcept>();

    test_is_not_volatile<void (&)(int)>();
    test_is_not_volatile<void (&)(int) noexcept>();

    test_is_not_volatile<void (&)(...)>();
    test_is_not_volatile<void (&)(...) noexcept>();

    test_is_not_volatile<void (&)(int, ...)>();
    test_is_not_volatile<void (&)(int, ...) noexcept>();

    test_is_not_volatile<int (&)()>();
    test_is_not_volatile<int (&)() noexcept>();

    test_is_not_volatile<int (&)(int)>();
    test_is_not_volatile<int (&)(int) noexcept>();

    test_is_not_volatile<int (&)(...)>();
    test_is_not_volatile<int (&)(...) noexcept>();

    test_is_not_volatile<int (&)(int, ...)>();
    test_is_not_volatile<int (&)(int, ...) noexcept>();

    test_is_not_volatile<void(&&)()>();
    test_is_not_volatile<void(&&)() noexcept>();

    test_is_not_volatile<void(&&)(int)>();
    test_is_not_volatile<void(&&)(int) noexcept>();

    test_is_not_volatile<void(&&)(...)>();
    test_is_not_volatile<void(&&)(...) noexcept>();

    test_is_not_volatile<void(&&)(int, ...)>();
    test_is_not_volatile<void(&&)(int, ...) noexcept>();

    test_is_not_volatile<int(&&)()>();
    test_is_not_volatile<int(&&)() noexcept>();

    test_is_not_volatile<int(&&)(int)>();
    test_is_not_volatile<int(&&)(int) noexcept>();

    test_is_not_volatile<int(&&)(...)>();
    test_is_not_volatile<int(&&)(...) noexcept>();

    test_is_not_volatile<int(&&)(int, ...)>();
    test_is_not_volatile<int(&&)(int, ...) noexcept>();

    test_is_volatile<void (Class::*)()>();
    test_is_volatile<void (Class::*)()&>();
    test_is_volatile<void (Class::*)() &&>();
    test_is_volatile<void (Class::*)() const>();
    test_is_volatile<void (Class::*)() const&>();
    test_is_volatile<void (Class::*)() const&&>();
    test_is_volatile<void (Class::*)() noexcept>();
    test_is_volatile<void (Class::*)()& noexcept>();
    test_is_volatile<void (Class::*)()&& noexcept>();
    test_is_volatile<void (Class::*)() const noexcept>();
    test_is_volatile<void (Class::*)() const& noexcept>();
    test_is_volatile<void (Class::*)() const&& noexcept>();

    test_is_volatile<void (Class::*)(int)>();
    test_is_volatile<void (Class::*)(int)&>();
    test_is_volatile<void (Class::*)(int) &&>();
    test_is_volatile<void (Class::*)(int) const>();
    test_is_volatile<void (Class::*)(int) const&>();
    test_is_volatile<void (Class::*)(int) const&&>();
    test_is_volatile<void (Class::*)(int) noexcept>();
    test_is_volatile<void (Class::*)(int)& noexcept>();
    test_is_volatile<void (Class::*)(int)&& noexcept>();
    test_is_volatile<void (Class::*)(int) const noexcept>();
    test_is_volatile<void (Class::*)(int) const& noexcept>();
    test_is_volatile<void (Class::*)(int) const&& noexcept>();

    test_is_volatile<void (Class::*)(...)>();
    test_is_volatile<void (Class::*)(...)&>();
    test_is_volatile<void (Class::*)(...) &&>();
    test_is_volatile<void (Class::*)(...) const>();
    test_is_volatile<void (Class::*)(...) const&>();
    test_is_volatile<void (Class::*)(...) const&&>();
    test_is_volatile<void (Class::*)(...) noexcept>();
    test_is_volatile<void (Class::*)(...)& noexcept>();
    test_is_volatile<void (Class::*)(...)&& noexcept>();
    test_is_volatile<void (Class::*)(...) const noexcept>();
    test_is_volatile<void (Class::*)(...) const& noexcept>();
    test_is_volatile<void (Class::*)(...) const&& noexcept>();

    test_is_volatile<void (Class::*)(int, ...)>();
    test_is_volatile<void (Class::*)(int, ...)&>();
    test_is_volatile<void (Class::*)(int, ...) &&>();
    test_is_volatile<void (Class::*)(int, ...) const>();
    test_is_volatile<void (Class::*)(int, ...) const&>();
    test_is_volatile<void (Class::*)(int, ...) const&&>();
    test_is_volatile<void (Class::*)(int, ...) noexcept>();
    test_is_volatile<void (Class::*)(int, ...)& noexcept>();
    test_is_volatile<void (Class::*)(int, ...)&& noexcept>();
    test_is_volatile<void (Class::*)(int, ...) const noexcept>();
    test_is_volatile<void (Class::*)(int, ...) const& noexcept>();
    test_is_volatile<void (Class::*)(int, ...) const&& noexcept>();

    test_is_volatile<int (Class::*)()>();
    test_is_volatile<int (Class::*)()&>();
    test_is_volatile<int (Class::*)() &&>();
    test_is_volatile<int (Class::*)() const>();
    test_is_volatile<int (Class::*)() const&>();
    test_is_volatile<int (Class::*)() const&&>();
    test_is_volatile<int (Class::*)() noexcept>();
    test_is_volatile<int (Class::*)()& noexcept>();
    test_is_volatile<int (Class::*)()&& noexcept>();
    test_is_volatile<int (Class::*)() const noexcept>();
    test_is_volatile<int (Class::*)() const& noexcept>();
    test_is_volatile<int (Class::*)() const&& noexcept>();

    test_is_volatile<int (Class::*)(int)>();
    test_is_volatile<int (Class::*)(int)&>();
    test_is_volatile<int (Class::*)(int) &&>();
    test_is_volatile<int (Class::*)(int) const>();
    test_is_volatile<int (Class::*)(int) const&>();
    test_is_volatile<int (Class::*)(int) const&&>();
    test_is_volatile<int (Class::*)(int) noexcept>();
    test_is_volatile<int (Class::*)(int)& noexcept>();
    test_is_volatile<int (Class::*)(int)&& noexcept>();
    test_is_volatile<int (Class::*)(int) const noexcept>();
    test_is_volatile<int (Class::*)(int) const& noexcept>();
    test_is_volatile<int (Class::*)(int) const&& noexcept>();

    test_is_volatile<int (Class::*)(...)>();
    test_is_volatile<int (Class::*)(...)&>();
    test_is_volatile<int (Class::*)(...) &&>();
    test_is_volatile<int (Class::*)(...) const>();
    test_is_volatile<int (Class::*)(...) const&>();
    test_is_volatile<int (Class::*)(...) const&&>();
    test_is_volatile<int (Class::*)(...) noexcept>();
    test_is_volatile<int (Class::*)(...)& noexcept>();
    test_is_volatile<int (Class::*)(...)&& noexcept>();
    test_is_volatile<int (Class::*)(...) const noexcept>();
    test_is_volatile<int (Class::*)(...) const& noexcept>();
    test_is_volatile<int (Class::*)(...) const&& noexcept>();

    test_is_volatile<int (Class::*)(int, ...)>();
    test_is_volatile<int (Class::*)(int, ...)&>();
    test_is_volatile<int (Class::*)(int, ...) &&>();
    test_is_volatile<int (Class::*)(int, ...) const>();
    test_is_volatile<int (Class::*)(int, ...) const&>();
    test_is_volatile<int (Class::*)(int, ...) const&&>();
    test_is_volatile<int (Class::*)(int, ...) noexcept>();
    test_is_volatile<int (Class::*)(int, ...)& noexcept>();
    test_is_volatile<int (Class::*)(int, ...)&& noexcept>();
    test_is_volatile<int (Class::*)(int, ...) const noexcept>();
    test_is_volatile<int (Class::*)(int, ...) const& noexcept>();
    test_is_volatile<int (Class::*)(int, ...) const&& noexcept>();
}
