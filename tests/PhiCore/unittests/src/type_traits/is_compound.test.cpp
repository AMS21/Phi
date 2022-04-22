#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_compound.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_compound_impl()
{
    STATIC_REQUIRE(phi::is_compound<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_compound<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_compound_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_compound_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_compound<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_compound<T>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_compound<T>::value);
}

template <typename T>
void test_is_compound()
{
    test_is_compound_impl<T>();
    test_is_compound_impl<const T>();
    test_is_compound_impl<volatile T>();
    test_is_compound_impl<const volatile T>();
}

template <typename T>
void test_is_not_compound_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_compound<T>::value);
    STATIC_REQUIRE(phi::is_not_compound<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_compound_v<T>);
    STATIC_REQUIRE(phi::is_not_compound_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_compound<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_compound<T>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_compound<T>::value);
}

template <typename T>
void test_is_not_compound()
{
    test_is_not_compound_impl<T>();
    test_is_not_compound_impl<const T>();
    test_is_not_compound_impl<volatile T>();
    test_is_not_compound_impl<const volatile T>();
}

TEST_CASE("is_compound")
{
    test_is_not_compound<void>();
    test_is_not_compound<phi::nullptr_t>();
    test_is_not_compound<bool>();
    test_is_not_compound<char>();
    test_is_not_compound<signed char>();
    test_is_not_compound<unsigned char>();
    test_is_not_compound<short>();
    test_is_not_compound<unsigned short>();
    test_is_not_compound<int>();
    test_is_not_compound<unsigned int>();
    test_is_not_compound<long>();
    test_is_not_compound<unsigned long>();
    test_is_not_compound<long long>();
    test_is_not_compound<unsigned long long>();
    test_is_not_compound<float>();
    test_is_not_compound<double>();
    test_is_not_compound<long double>();
    test_is_not_compound<char8_t>();
    test_is_not_compound<char16_t>();
    test_is_not_compound<char32_t>();
    test_is_not_compound<wchar_t>();

    test_is_compound<phi::boolean>();
    test_is_compound<phi::integer<signed char>>();
    test_is_compound<phi::integer<unsigned char>>();
    test_is_compound<phi::integer<short>>();
    test_is_compound<phi::integer<unsigned short>>();
    test_is_compound<phi::integer<int>>();
    test_is_compound<phi::integer<unsigned int>>();
    test_is_compound<phi::integer<long>>();
    test_is_compound<phi::integer<unsigned long>>();
    test_is_compound<phi::integer<long long>>();
    test_is_compound<phi::integer<unsigned long long>>();
    test_is_compound<phi::floating_point<float>>();
    test_is_compound<phi::floating_point<double>>();
    test_is_compound<phi::floating_point<long double>>();

    test_is_compound<std::vector<int>>();
    test_is_compound<phi::scope_ptr<int>>();

    test_is_compound<int&>();
    test_is_compound<const int&>();
    test_is_compound<volatile int&>();
    test_is_compound<const volatile int&>();
    test_is_compound<int&&>();
    test_is_compound<const int&&>();
    test_is_compound<volatile int&&>();
    test_is_compound<const volatile int&&>();
    test_is_compound<int*>();
    test_is_compound<const int*>();
    test_is_compound<volatile int*>();
    test_is_compound<const volatile int*>();
    test_is_compound<int**>();
    test_is_compound<const int**>();
    test_is_compound<volatile int**>();
    test_is_compound<const volatile int**>();
    test_is_compound<int*&>();
    test_is_compound<const int*&>();
    test_is_compound<volatile int*&>();
    test_is_compound<const volatile int*&>();
    test_is_compound<int*&&>();
    test_is_compound<const int*&&>();
    test_is_compound<volatile int*&&>();
    test_is_compound<const volatile int*&&>();
    test_is_compound<void*>();
    test_is_compound<char[3]>();
    test_is_compound<char[]>();
    test_is_compound<char* [3]>();
    test_is_compound<char*[]>();
    test_is_compound<int(*)[3]>();
    test_is_compound<int(*)[]>();
    test_is_compound<int(&)[3]>();
    test_is_compound<int(&)[]>();
    test_is_compound<int(&&)[3]>();
    test_is_compound<int(&&)[]>();
    test_is_compound<char[3][2]>();
    test_is_compound<char[][2]>();
    test_is_compound<char* [3][2]>();
    test_is_compound<char*[][2]>();
    test_is_compound<int(*)[3][2]>();
    test_is_compound<int(*)[][2]>();
    test_is_compound<int(&)[3][2]>();
    test_is_compound<int(&)[][2]>();
    test_is_compound<int(&&)[3][2]>();
    test_is_compound<int(&&)[][2]>();
    test_is_compound<Class>();
    test_is_compound<Class[]>();
    test_is_compound<Class[2]>();
    test_is_compound<Template<void>>();
    test_is_compound<Template<int>>();
    test_is_compound<Template<Class>>();
    test_is_compound<Template<IncompleteType>>();
    test_is_compound<VariadicTemplate<>>();
    test_is_compound<VariadicTemplate<void>>();
    test_is_compound<VariadicTemplate<int>>();
    test_is_compound<VariadicTemplate<Class>>();
    test_is_compound<VariadicTemplate<IncompleteType>>();
    test_is_compound<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_compound<PublicDerivedFromTemplate<Base>>();
    test_is_compound<PublicDerivedFromTemplate<Derived>>();
    test_is_compound<PublicDerivedFromTemplate<Class>>();
    test_is_compound<PrivateDerivedFromTemplate<Base>>();
    test_is_compound<PrivateDerivedFromTemplate<Derived>>();
    test_is_compound<PrivateDerivedFromTemplate<Class>>();
    test_is_compound<ProtectedDerivedFromTemplate<Base>>();
    test_is_compound<ProtectedDerivedFromTemplate<Derived>>();
    test_is_compound<ProtectedDerivedFromTemplate<Class>>();
    test_is_compound<Union>();
    test_is_compound<NonEmptyUnion>();
    test_is_compound<Empty>();
    test_is_compound<NotEmpty>();
    test_is_compound<BitZero>();
    test_is_compound<BitOne>();
    test_is_compound<Base>();
    test_is_compound<Derived>();
    test_is_compound<Abstract>();
    test_is_compound<PublicAbstract>();
    test_is_compound<PrivateAbstract>();
    test_is_compound<ProtectedAbstract>();
    test_is_compound<AbstractTemplate<int>>();
    test_is_compound<AbstractTemplate<double>>();
    test_is_compound<AbstractTemplate<Class>>();
    test_is_compound<AbstractTemplate<IncompleteType>>();
    test_is_compound<Final>();
    test_is_compound<PublicDestructor>();
    test_is_compound<ProtectedDestructor>();
    test_is_compound<PrivateDestructor>();
    test_is_compound<VirtualPublicDestructor>();
    test_is_compound<VirtualProtectedDestructor>();
    test_is_compound<VirtualPrivateDestructor>();
    test_is_compound<PurePublicDestructor>();
    test_is_compound<PureProtectedDestructor>();
    test_is_compound<PurePrivateDestructor>();
    test_is_compound<DeletedPublicDestructor>();
    test_is_compound<DeletedProtectedDestructor>();
    test_is_compound<DeletedPrivateDestructor>();
    test_is_compound<DeletedVirtualPublicDestructor>();
    test_is_compound<DeletedVirtualProtectedDestructor>();
    test_is_compound<DeletedVirtualPrivateDestructor>();
    test_is_compound<Enum>();
    test_is_compound<EnumSigned>();
    test_is_compound<EnumUnsigned>();
    test_is_compound<EnumClass>();
    test_is_compound<EnumStruct>();
    test_is_compound<Function>();
    test_is_compound<FunctionPtr>();
    test_is_compound<MemberObjectPtr>();
    test_is_compound<MemberFunctionPtr>();
    test_is_compound<IncompleteType>();
    test_is_compound<IncompleteTemplate<void>>();
    test_is_compound<IncompleteTemplate<int>>();
    test_is_compound<IncompleteTemplate<Class>>();
    test_is_compound<IncompleteTemplate<IncompleteType>>();
    test_is_compound<IncompleteVariadicTemplate<>>();
    test_is_compound<IncompleteVariadicTemplate<void>>();
    test_is_compound<IncompleteVariadicTemplate<int>>();
    test_is_compound<IncompleteVariadicTemplate<Class>>();
    test_is_compound<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_compound<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_compound<int Class::*>();
    test_is_compound<float Class::*>();
    test_is_compound<void * Class::*>();
    test_is_compound<int * Class::*>();
    test_is_compound<int Class::*&>();
    test_is_compound<float Class::*&>();
    test_is_compound<void * Class::*&>();
    test_is_compound<int * Class::*&>();
    test_is_compound<int Class::*&&>();
    test_is_compound<float Class::*&&>();
    test_is_compound<void * Class::*&&>();
    test_is_compound<int * Class::*&&>();
    test_is_compound<int Class::*const>();
    test_is_compound<float Class::*const>();
    test_is_compound<void * Class::*const>();
    test_is_compound<int Class::*const&>();
    test_is_compound<float Class::*const&>();
    test_is_compound<void * Class::*const&>();
    test_is_compound<int Class::*const&&>();
    test_is_compound<float Class::*const&&>();
    test_is_compound<void * Class::*const&&>();
    test_is_compound<int Class::*volatile>();
    test_is_compound<float Class::*volatile>();
    test_is_compound<void * Class::*volatile>();
    test_is_compound<int Class::*volatile&>();
    test_is_compound<float Class::*volatile&>();
    test_is_compound<void * Class::*volatile&>();
    test_is_compound<int Class::*volatile&&>();
    test_is_compound<float Class::*volatile&&>();
    test_is_compound<void * Class::*volatile&&>();
    test_is_compound<int Class::*const volatile>();
    test_is_compound<float Class::*const volatile>();
    test_is_compound<void * Class::*const volatile>();
    test_is_compound<int Class::*const volatile&>();
    test_is_compound<float Class::*const volatile&>();
    test_is_compound<void * Class::*const volatile&>();
    test_is_compound<int Class::*const volatile&&>();
    test_is_compound<float Class::*const volatile&&>();
    test_is_compound<void * Class::*const volatile&&>();
    test_is_compound<NonCopyable>();
    test_is_compound<NonMoveable>();
    test_is_compound<NonConstructible>();
    test_is_compound<Tracked>();
    test_is_compound<TrapConstructible>();
    test_is_compound<TrapImplicitConversion>();
    test_is_compound<TrapComma>();
    test_is_compound<TrapCall>();
    test_is_compound<TrapSelfAssign>();
    test_is_compound<TrapDeref>();
    test_is_compound<TrapArraySubscript>();

    test_is_compound<void()>();
    test_is_compound<void()&>();
    test_is_compound<void() &&>();
    test_is_compound<void() const>();
    test_is_compound<void() const&>();
    test_is_compound<void() const&&>();
    test_is_compound<void() volatile>();
    test_is_compound<void() volatile&>();
    test_is_compound<void() volatile&&>();
    test_is_compound<void() const volatile>();
    test_is_compound<void() const volatile&>();
    test_is_compound<void() const volatile&&>();
    test_is_compound<void() noexcept>();
    test_is_compound<void()& noexcept>();
    test_is_compound<void()&& noexcept>();
    test_is_compound<void() const noexcept>();
    test_is_compound<void() const& noexcept>();
    test_is_compound<void() const&& noexcept>();
    test_is_compound<void() volatile noexcept>();
    test_is_compound<void() volatile& noexcept>();
    test_is_compound<void() volatile&& noexcept>();
    test_is_compound<void() const volatile noexcept>();
    test_is_compound<void() const volatile& noexcept>();
    test_is_compound<void() const volatile&& noexcept>();

    test_is_compound<void(int)>();
    test_is_compound<void(int)&>();
    test_is_compound<void(int) &&>();
    test_is_compound<void(int) const>();
    test_is_compound<void(int) const&>();
    test_is_compound<void(int) const&&>();
    test_is_compound<void(int) volatile>();
    test_is_compound<void(int) volatile&>();
    test_is_compound<void(int) volatile&&>();
    test_is_compound<void(int) const volatile>();
    test_is_compound<void(int) const volatile&>();
    test_is_compound<void(int) const volatile&&>();
    test_is_compound<void(int) noexcept>();
    test_is_compound<void(int)& noexcept>();
    test_is_compound<void(int)&& noexcept>();
    test_is_compound<void(int) const noexcept>();
    test_is_compound<void(int) const& noexcept>();
    test_is_compound<void(int) const&& noexcept>();
    test_is_compound<void(int) volatile noexcept>();
    test_is_compound<void(int) volatile& noexcept>();
    test_is_compound<void(int) volatile&& noexcept>();
    test_is_compound<void(int) const volatile noexcept>();
    test_is_compound<void(int) const volatile& noexcept>();
    test_is_compound<void(int) const volatile&& noexcept>();

    test_is_compound<void(...)>();
    test_is_compound<void(...)&>();
    test_is_compound<void(...) &&>();
    test_is_compound<void(...) const>();
    test_is_compound<void(...) const&>();
    test_is_compound<void(...) const&&>();
    test_is_compound<void(...) volatile>();
    test_is_compound<void(...) volatile&>();
    test_is_compound<void(...) volatile&&>();
    test_is_compound<void(...) const volatile>();
    test_is_compound<void(...) const volatile&>();
    test_is_compound<void(...) const volatile&&>();
    test_is_compound<void(...) noexcept>();
    test_is_compound<void(...)& noexcept>();
    test_is_compound<void(...)&& noexcept>();
    test_is_compound<void(...) const noexcept>();
    test_is_compound<void(...) const& noexcept>();
    test_is_compound<void(...) const&& noexcept>();
    test_is_compound<void(...) volatile noexcept>();
    test_is_compound<void(...) volatile& noexcept>();
    test_is_compound<void(...) volatile&& noexcept>();
    test_is_compound<void(...) const volatile noexcept>();
    test_is_compound<void(...) const volatile& noexcept>();
    test_is_compound<void(...) const volatile&& noexcept>();

    test_is_compound<void(int, ...)>();
    test_is_compound<void(int, ...)&>();
    test_is_compound<void(int, ...) &&>();
    test_is_compound<void(int, ...) const>();
    test_is_compound<void(int, ...) const&>();
    test_is_compound<void(int, ...) const&&>();
    test_is_compound<void(int, ...) volatile>();
    test_is_compound<void(int, ...) volatile&>();
    test_is_compound<void(int, ...) volatile&&>();
    test_is_compound<void(int, ...) const volatile>();
    test_is_compound<void(int, ...) const volatile&>();
    test_is_compound<void(int, ...) const volatile&&>();
    test_is_compound<void(int, ...) noexcept>();
    test_is_compound<void(int, ...)& noexcept>();
    test_is_compound<void(int, ...)&& noexcept>();
    test_is_compound<void(int, ...) const noexcept>();
    test_is_compound<void(int, ...) const& noexcept>();
    test_is_compound<void(int, ...) const&& noexcept>();
    test_is_compound<void(int, ...) volatile noexcept>();
    test_is_compound<void(int, ...) volatile& noexcept>();
    test_is_compound<void(int, ...) volatile&& noexcept>();
    test_is_compound<void(int, ...) const volatile noexcept>();
    test_is_compound<void(int, ...) const volatile& noexcept>();
    test_is_compound<void(int, ...) const volatile&& noexcept>();

    test_is_compound<int()>();
    test_is_compound<int()&>();
    test_is_compound<int() &&>();
    test_is_compound<int() const>();
    test_is_compound<int() const&>();
    test_is_compound<int() const&&>();
    test_is_compound<int() volatile>();
    test_is_compound<int() volatile&>();
    test_is_compound<int() volatile&&>();
    test_is_compound<int() const volatile>();
    test_is_compound<int() const volatile&>();
    test_is_compound<int() const volatile&&>();
    test_is_compound<int() noexcept>();
    test_is_compound<int()& noexcept>();
    test_is_compound<int()&& noexcept>();
    test_is_compound<int() const noexcept>();
    test_is_compound<int() const& noexcept>();
    test_is_compound<int() const&& noexcept>();
    test_is_compound<int() volatile noexcept>();
    test_is_compound<int() volatile& noexcept>();
    test_is_compound<int() volatile&& noexcept>();
    test_is_compound<int() const volatile noexcept>();
    test_is_compound<int() const volatile& noexcept>();
    test_is_compound<int() const volatile&& noexcept>();

    test_is_compound<int(int)>();
    test_is_compound<int(int)&>();
    test_is_compound<int(int) &&>();
    test_is_compound<int(int) const>();
    test_is_compound<int(int) const&>();
    test_is_compound<int(int) const&&>();
    test_is_compound<int(int) volatile>();
    test_is_compound<int(int) volatile&>();
    test_is_compound<int(int) volatile&&>();
    test_is_compound<int(int) const volatile>();
    test_is_compound<int(int) const volatile&>();
    test_is_compound<int(int) const volatile&&>();
    test_is_compound<int(int) noexcept>();
    test_is_compound<int(int)& noexcept>();
    test_is_compound<int(int)&& noexcept>();
    test_is_compound<int(int) const noexcept>();
    test_is_compound<int(int) const& noexcept>();
    test_is_compound<int(int) const&& noexcept>();
    test_is_compound<int(int) volatile noexcept>();
    test_is_compound<int(int) volatile& noexcept>();
    test_is_compound<int(int) volatile&& noexcept>();
    test_is_compound<int(int) const volatile noexcept>();
    test_is_compound<int(int) const volatile& noexcept>();
    test_is_compound<int(int) const volatile&& noexcept>();

    test_is_compound<int(...)>();
    test_is_compound<int(...)&>();
    test_is_compound<int(...) &&>();
    test_is_compound<int(...) const>();
    test_is_compound<int(...) const&>();
    test_is_compound<int(...) const&&>();
    test_is_compound<int(...) volatile>();
    test_is_compound<int(...) volatile&>();
    test_is_compound<int(...) volatile&&>();
    test_is_compound<int(...) const volatile>();
    test_is_compound<int(...) const volatile&>();
    test_is_compound<int(...) const volatile&&>();
    test_is_compound<int(...) noexcept>();
    test_is_compound<int(...)& noexcept>();
    test_is_compound<int(...)&& noexcept>();
    test_is_compound<int(...) const noexcept>();
    test_is_compound<int(...) const& noexcept>();
    test_is_compound<int(...) const&& noexcept>();
    test_is_compound<int(...) volatile noexcept>();
    test_is_compound<int(...) volatile& noexcept>();
    test_is_compound<int(...) volatile&& noexcept>();
    test_is_compound<int(...) const volatile noexcept>();
    test_is_compound<int(...) const volatile& noexcept>();
    test_is_compound<int(...) const volatile&& noexcept>();

    test_is_compound<int(int, ...)>();
    test_is_compound<int(int, ...)&>();
    test_is_compound<int(int, ...) &&>();
    test_is_compound<int(int, ...) const>();
    test_is_compound<int(int, ...) const&>();
    test_is_compound<int(int, ...) const&&>();
    test_is_compound<int(int, ...) volatile>();
    test_is_compound<int(int, ...) volatile&>();
    test_is_compound<int(int, ...) volatile&&>();
    test_is_compound<int(int, ...) const volatile>();
    test_is_compound<int(int, ...) const volatile&>();
    test_is_compound<int(int, ...) const volatile&&>();
    test_is_compound<int(int, ...) noexcept>();
    test_is_compound<int(int, ...)& noexcept>();
    test_is_compound<int(int, ...)&& noexcept>();
    test_is_compound<int(int, ...) const noexcept>();
    test_is_compound<int(int, ...) const& noexcept>();
    test_is_compound<int(int, ...) const&& noexcept>();
    test_is_compound<int(int, ...) volatile noexcept>();
    test_is_compound<int(int, ...) volatile& noexcept>();
    test_is_compound<int(int, ...) volatile&& noexcept>();
    test_is_compound<int(int, ...) const volatile noexcept>();
    test_is_compound<int(int, ...) const volatile& noexcept>();
    test_is_compound<int(int, ...) const volatile&& noexcept>();

    test_is_compound<void (*)()>();
    test_is_compound<void (*)() noexcept>();

    test_is_compound<void (*)(int)>();
    test_is_compound<void (*)(int) noexcept>();

    test_is_compound<void (*)(...)>();
    test_is_compound<void (*)(...) noexcept>();

    test_is_compound<void (*)(int, ...)>();
    test_is_compound<void (*)(int, ...) noexcept>();

    test_is_compound<int (*)()>();
    test_is_compound<int (*)() noexcept>();

    test_is_compound<int (*)(int)>();
    test_is_compound<int (*)(int) noexcept>();

    test_is_compound<int (*)(...)>();
    test_is_compound<int (*)(...) noexcept>();

    test_is_compound<int (*)(int, ...)>();
    test_is_compound<int (*)(int, ...) noexcept>();

    test_is_compound<void (&)()>();
    test_is_compound<void (&)() noexcept>();

    test_is_compound<void (&)(int)>();
    test_is_compound<void (&)(int) noexcept>();

    test_is_compound<void (&)(...)>();
    test_is_compound<void (&)(...) noexcept>();

    test_is_compound<void (&)(int, ...)>();
    test_is_compound<void (&)(int, ...) noexcept>();

    test_is_compound<int (&)()>();
    test_is_compound<int (&)() noexcept>();

    test_is_compound<int (&)(int)>();
    test_is_compound<int (&)(int) noexcept>();

    test_is_compound<int (&)(...)>();
    test_is_compound<int (&)(...) noexcept>();

    test_is_compound<int (&)(int, ...)>();
    test_is_compound<int (&)(int, ...) noexcept>();

    test_is_compound<void(&&)()>();
    test_is_compound<void(&&)() noexcept>();

    test_is_compound<void(&&)(int)>();
    test_is_compound<void(&&)(int) noexcept>();

    test_is_compound<void(&&)(...)>();
    test_is_compound<void(&&)(...) noexcept>();

    test_is_compound<void(&&)(int, ...)>();
    test_is_compound<void(&&)(int, ...) noexcept>();

    test_is_compound<int(&&)()>();
    test_is_compound<int(&&)() noexcept>();

    test_is_compound<int(&&)(int)>();
    test_is_compound<int(&&)(int) noexcept>();

    test_is_compound<int(&&)(...)>();
    test_is_compound<int(&&)(...) noexcept>();

    test_is_compound<int(&&)(int, ...)>();
    test_is_compound<int(&&)(int, ...) noexcept>();

    test_is_compound<void (Class::*)()>();
    test_is_compound<void (Class::*)()&>();
    test_is_compound<void (Class::*)() &&>();
    test_is_compound<void (Class::*)() const>();
    test_is_compound<void (Class::*)() const&>();
    test_is_compound<void (Class::*)() const&&>();
    test_is_compound<void (Class::*)() noexcept>();
    test_is_compound<void (Class::*)()& noexcept>();
    test_is_compound<void (Class::*)()&& noexcept>();
    test_is_compound<void (Class::*)() const noexcept>();
    test_is_compound<void (Class::*)() const& noexcept>();
    test_is_compound<void (Class::*)() const&& noexcept>();

    test_is_compound<void (Class::*)(int)>();
    test_is_compound<void (Class::*)(int)&>();
    test_is_compound<void (Class::*)(int) &&>();
    test_is_compound<void (Class::*)(int) const>();
    test_is_compound<void (Class::*)(int) const&>();
    test_is_compound<void (Class::*)(int) const&&>();
    test_is_compound<void (Class::*)(int) noexcept>();
    test_is_compound<void (Class::*)(int)& noexcept>();
    test_is_compound<void (Class::*)(int)&& noexcept>();
    test_is_compound<void (Class::*)(int) const noexcept>();
    test_is_compound<void (Class::*)(int) const& noexcept>();
    test_is_compound<void (Class::*)(int) const&& noexcept>();

    test_is_compound<void (Class::*)(...)>();
    test_is_compound<void (Class::*)(...)&>();
    test_is_compound<void (Class::*)(...) &&>();
    test_is_compound<void (Class::*)(...) const>();
    test_is_compound<void (Class::*)(...) const&>();
    test_is_compound<void (Class::*)(...) const&&>();
    test_is_compound<void (Class::*)(...) noexcept>();
    test_is_compound<void (Class::*)(...)& noexcept>();
    test_is_compound<void (Class::*)(...)&& noexcept>();
    test_is_compound<void (Class::*)(...) const noexcept>();
    test_is_compound<void (Class::*)(...) const& noexcept>();
    test_is_compound<void (Class::*)(...) const&& noexcept>();

    test_is_compound<void (Class::*)(int, ...)>();
    test_is_compound<void (Class::*)(int, ...)&>();
    test_is_compound<void (Class::*)(int, ...) &&>();
    test_is_compound<void (Class::*)(int, ...) const>();
    test_is_compound<void (Class::*)(int, ...) const&>();
    test_is_compound<void (Class::*)(int, ...) const&&>();
    test_is_compound<void (Class::*)(int, ...) noexcept>();
    test_is_compound<void (Class::*)(int, ...)& noexcept>();
    test_is_compound<void (Class::*)(int, ...)&& noexcept>();
    test_is_compound<void (Class::*)(int, ...) const noexcept>();
    test_is_compound<void (Class::*)(int, ...) const& noexcept>();
    test_is_compound<void (Class::*)(int, ...) const&& noexcept>();

    test_is_compound<int (Class::*)()>();
    test_is_compound<int (Class::*)()&>();
    test_is_compound<int (Class::*)() &&>();
    test_is_compound<int (Class::*)() const>();
    test_is_compound<int (Class::*)() const&>();
    test_is_compound<int (Class::*)() const&&>();
    test_is_compound<int (Class::*)() noexcept>();
    test_is_compound<int (Class::*)()& noexcept>();
    test_is_compound<int (Class::*)()&& noexcept>();
    test_is_compound<int (Class::*)() const noexcept>();
    test_is_compound<int (Class::*)() const& noexcept>();
    test_is_compound<int (Class::*)() const&& noexcept>();

    test_is_compound<int (Class::*)(int)>();
    test_is_compound<int (Class::*)(int)&>();
    test_is_compound<int (Class::*)(int) &&>();
    test_is_compound<int (Class::*)(int) const>();
    test_is_compound<int (Class::*)(int) const&>();
    test_is_compound<int (Class::*)(int) const&&>();
    test_is_compound<int (Class::*)(int) noexcept>();
    test_is_compound<int (Class::*)(int)& noexcept>();
    test_is_compound<int (Class::*)(int)&& noexcept>();
    test_is_compound<int (Class::*)(int) const noexcept>();
    test_is_compound<int (Class::*)(int) const& noexcept>();
    test_is_compound<int (Class::*)(int) const&& noexcept>();

    test_is_compound<int (Class::*)(...)>();
    test_is_compound<int (Class::*)(...)&>();
    test_is_compound<int (Class::*)(...) &&>();
    test_is_compound<int (Class::*)(...) const>();
    test_is_compound<int (Class::*)(...) const&>();
    test_is_compound<int (Class::*)(...) const&&>();
    test_is_compound<int (Class::*)(...) noexcept>();
    test_is_compound<int (Class::*)(...)& noexcept>();
    test_is_compound<int (Class::*)(...)&& noexcept>();
    test_is_compound<int (Class::*)(...) const noexcept>();
    test_is_compound<int (Class::*)(...) const& noexcept>();
    test_is_compound<int (Class::*)(...) const&& noexcept>();

    test_is_compound<int (Class::*)(int, ...)>();
    test_is_compound<int (Class::*)(int, ...)&>();
    test_is_compound<int (Class::*)(int, ...) &&>();
    test_is_compound<int (Class::*)(int, ...) const>();
    test_is_compound<int (Class::*)(int, ...) const&>();
    test_is_compound<int (Class::*)(int, ...) const&&>();
    test_is_compound<int (Class::*)(int, ...) noexcept>();
    test_is_compound<int (Class::*)(int, ...)& noexcept>();
    test_is_compound<int (Class::*)(int, ...)&& noexcept>();
    test_is_compound<int (Class::*)(int, ...) const noexcept>();
    test_is_compound<int (Class::*)(int, ...) const& noexcept>();
    test_is_compound<int (Class::*)(int, ...) const&& noexcept>();
}
