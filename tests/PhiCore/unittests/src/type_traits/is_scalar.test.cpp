#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_scalar.hpp>
#include <vector>

template <typename T>
void test_is_scalar_impl()
{
#if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE(phi::is_scalar<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_scalar<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_scalar_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_scalar_v<T>);
#    endif
#endif
}

template <typename T>
void test_is_not_scalar_impl()
{
#if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE_FALSE(phi::is_scalar<T>::value);
    STATIC_REQUIRE(phi::is_not_scalar<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_scalar_v<T>);
    STATIC_REQUIRE(phi::is_not_scalar_v<T>);
#    endif
#endif
}

template <typename T>
void test_is_scalar()
{
    test_is_scalar_impl<T>();
    test_is_scalar_impl<const T>();
    test_is_scalar_impl<volatile T>();
    test_is_scalar_impl<const volatile T>();
}

template <typename T>
void test_is_not_scalar()
{
    test_is_not_scalar_impl<T>();
    test_is_not_scalar_impl<const T>();
    test_is_not_scalar_impl<volatile T>();
    test_is_not_scalar_impl<const volatile T>();
}

TEST_CASE("is_scalar")
{
    test_is_not_scalar<void>();
    test_is_scalar<phi::nullptr_t>();
    test_is_scalar<bool>();
    test_is_scalar<char>();
    test_is_scalar<signed char>();
    test_is_scalar<unsigned char>();
    test_is_scalar<short>();
    test_is_scalar<unsigned short>();
    test_is_scalar<int>();
    test_is_scalar<unsigned int>();
    test_is_scalar<long>();
    test_is_scalar<unsigned long>();
    test_is_scalar<long long>();
    test_is_scalar<unsigned long long>();
    test_is_scalar<float>();
    test_is_scalar<double>();
    test_is_scalar<long double>();
    test_is_scalar<char8_t>();
    test_is_scalar<char16_t>();
    test_is_scalar<char32_t>();
    test_is_scalar<wchar_t>();

    test_is_scalar<phi::boolean>();
    test_is_scalar<phi::integer<signed char>>();
    test_is_scalar<phi::integer<unsigned char>>();
    test_is_scalar<phi::integer<short>>();
    test_is_scalar<phi::integer<unsigned short>>();
    test_is_scalar<phi::integer<int>>();
    test_is_scalar<phi::integer<unsigned int>>();
    test_is_scalar<phi::integer<long>>();
    test_is_scalar<phi::integer<unsigned long>>();
    test_is_scalar<phi::integer<long long>>();
    test_is_scalar<phi::integer<unsigned long long>>();
    test_is_scalar<phi::floating_point<float>>();
    test_is_scalar<phi::floating_point<double>>();
    test_is_scalar<phi::floating_point<long double>>();

    test_is_not_scalar<std::vector<int>>();
    test_is_not_scalar<phi::scope_ptr<int>>();

    test_is_not_scalar<int&>();
    test_is_not_scalar<const int&>();
    test_is_not_scalar<volatile int&>();
    test_is_not_scalar<const volatile int&>();
    test_is_not_scalar<int&&>();
    test_is_not_scalar<const int&&>();
    test_is_not_scalar<volatile int&&>();
    test_is_not_scalar<const volatile int&&>();
    test_is_scalar<int*>();
    test_is_scalar<const int*>();
    test_is_scalar<volatile int*>();
    test_is_scalar<const volatile int*>();
    test_is_scalar<int**>();
    test_is_scalar<const int**>();
    test_is_scalar<volatile int**>();
    test_is_scalar<const volatile int**>();
    test_is_not_scalar<int*&>();
    test_is_not_scalar<const int*&>();
    test_is_not_scalar<volatile int*&>();
    test_is_not_scalar<const volatile int*&>();
    test_is_not_scalar<int*&&>();
    test_is_not_scalar<const int*&&>();
    test_is_not_scalar<volatile int*&&>();
    test_is_not_scalar<const volatile int*&&>();
    test_is_scalar<void*>();
    test_is_not_scalar<char[3]>();
    test_is_not_scalar<char[]>();
    test_is_not_scalar<char* [3]>();
    test_is_not_scalar<char*[]>();
    test_is_scalar<int(*)[3]>();
    test_is_scalar<int(*)[]>();
    test_is_not_scalar<int(&)[3]>();
    test_is_not_scalar<int(&)[]>();
    test_is_not_scalar<int(&&)[3]>();
    test_is_not_scalar<int(&&)[]>();
    test_is_not_scalar<char[3][2]>();
    test_is_not_scalar<char[][2]>();
    test_is_not_scalar<char* [3][2]>();
    test_is_not_scalar<char*[][2]>();
    test_is_scalar<int(*)[3][2]>();
    test_is_scalar<int(*)[][2]>();
    test_is_not_scalar<int(&)[3][2]>();
    test_is_not_scalar<int(&)[][2]>();
    test_is_not_scalar<int(&&)[3][2]>();
    test_is_not_scalar<int(&&)[][2]>();
    test_is_not_scalar<Class>();
    test_is_not_scalar<Class[]>();
    test_is_not_scalar<Class[2]>();
    test_is_not_scalar<Template<void>>();
    test_is_not_scalar<Template<int>>();
    test_is_not_scalar<Template<Class>>();
    test_is_not_scalar<Template<IncompleteType>>();
    test_is_not_scalar<VariadicTemplate<>>();
    test_is_not_scalar<VariadicTemplate<void>>();
    test_is_not_scalar<VariadicTemplate<int>>();
    test_is_not_scalar<VariadicTemplate<Class>>();
    test_is_not_scalar<VariadicTemplate<IncompleteType>>();
    test_is_not_scalar<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_scalar<PublicDerivedFromTemplate<Base>>();
    test_is_not_scalar<PublicDerivedFromTemplate<Derived>>();
    test_is_not_scalar<PublicDerivedFromTemplate<Class>>();
    test_is_not_scalar<PrivateDerivedFromTemplate<Base>>();
    test_is_not_scalar<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_scalar<PrivateDerivedFromTemplate<Class>>();
    test_is_not_scalar<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_scalar<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_scalar<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_scalar<Union>();
    test_is_not_scalar<NonEmptyUnion>();
    test_is_not_scalar<Empty>();
    test_is_not_scalar<NotEmpty>();
    test_is_not_scalar<BitZero>();
    test_is_not_scalar<BitOne>();
    test_is_not_scalar<Base>();
    test_is_not_scalar<Derived>();
    test_is_not_scalar<Abstract>();
    test_is_not_scalar<PublicAbstract>();
    test_is_not_scalar<PrivateAbstract>();
    test_is_not_scalar<ProtectedAbstract>();
    test_is_not_scalar<AbstractTemplate<int>>();
    test_is_not_scalar<AbstractTemplate<double>>();
    test_is_not_scalar<AbstractTemplate<Class>>();
    test_is_not_scalar<AbstractTemplate<IncompleteType>>();
    test_is_not_scalar<Final>();
    test_is_not_scalar<PublicDestructor>();
    test_is_not_scalar<ProtectedDestructor>();
    test_is_not_scalar<PrivateDestructor>();
    test_is_not_scalar<VirtualPublicDestructor>();
    test_is_not_scalar<VirtualProtectedDestructor>();
    test_is_not_scalar<VirtualPrivateDestructor>();
    test_is_not_scalar<PurePublicDestructor>();
    test_is_not_scalar<PureProtectedDestructor>();
    test_is_not_scalar<PurePrivateDestructor>();
    test_is_not_scalar<DeletedPublicDestructor>();
    test_is_not_scalar<DeletedProtectedDestructor>();
    test_is_not_scalar<DeletedPrivateDestructor>();
    test_is_not_scalar<DeletedVirtualPublicDestructor>();
    test_is_not_scalar<DeletedVirtualProtectedDestructor>();
    test_is_not_scalar<DeletedVirtualPrivateDestructor>();
    test_is_scalar<Enum>();
    test_is_scalar<EnumSigned>();
    test_is_scalar<EnumUnsigned>();
    test_is_scalar<EnumClass>();
    test_is_scalar<EnumStruct>();
    test_is_not_scalar<Function>();
    test_is_scalar<FunctionPtr>();
    test_is_scalar<MemberObjectPtr>();
    test_is_scalar<MemberFunctionPtr>();
    test_is_not_scalar<IncompleteType>();
    test_is_not_scalar<IncompleteTemplate<void>>();
    test_is_not_scalar<IncompleteTemplate<int>>();
    test_is_not_scalar<IncompleteTemplate<Class>>();
    test_is_not_scalar<IncompleteTemplate<IncompleteType>>();
    test_is_not_scalar<IncompleteVariadicTemplate<>>();
    test_is_not_scalar<IncompleteVariadicTemplate<void>>();
    test_is_not_scalar<IncompleteVariadicTemplate<int>>();
    test_is_not_scalar<IncompleteVariadicTemplate<Class>>();
    test_is_not_scalar<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_scalar<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_scalar<int Class::*>();
    test_is_scalar<float Class::*>();
    test_is_scalar<void * Class::*>();
    test_is_scalar<int * Class::*>();
    test_is_not_scalar<int Class::*&>();
    test_is_not_scalar<float Class::*&>();
    test_is_not_scalar<void * Class::*&>();
    test_is_not_scalar<int * Class::*&>();
    test_is_not_scalar<int Class::*&&>();
    test_is_not_scalar<float Class::*&&>();
    test_is_not_scalar<void * Class::*&&>();
    test_is_not_scalar<int * Class::*&&>();
    test_is_scalar<int Class::*const>();
    test_is_scalar<float Class::*const>();
    test_is_scalar<void * Class::*const>();
    test_is_not_scalar<int Class::*const&>();
    test_is_not_scalar<float Class::*const&>();
    test_is_not_scalar<void * Class::*const&>();
    test_is_not_scalar<int Class::*const&&>();
    test_is_not_scalar<float Class::*const&&>();
    test_is_not_scalar<void * Class::*const&&>();
    test_is_scalar<int Class::*volatile>();
    test_is_scalar<float Class::*volatile>();
    test_is_scalar<void * Class::*volatile>();
    test_is_not_scalar<int Class::*volatile&>();
    test_is_not_scalar<float Class::*volatile&>();
    test_is_not_scalar<void * Class::*volatile&>();
    test_is_not_scalar<int Class::*volatile&&>();
    test_is_not_scalar<float Class::*volatile&&>();
    test_is_not_scalar<void * Class::*volatile&&>();
    test_is_scalar<int Class::*const volatile>();
    test_is_scalar<float Class::*const volatile>();
    test_is_scalar<void * Class::*const volatile>();
    test_is_not_scalar<int Class::*const volatile&>();
    test_is_not_scalar<float Class::*const volatile&>();
    test_is_not_scalar<void * Class::*const volatile&>();
    test_is_not_scalar<int Class::*const volatile&&>();
    test_is_not_scalar<float Class::*const volatile&&>();
    test_is_not_scalar<void * Class::*const volatile&&>();
    test_is_not_scalar<NonCopyable>();
    test_is_not_scalar<NonMoveable>();
    test_is_not_scalar<NonConstructible>();
    test_is_not_scalar<Tracked>();
    test_is_not_scalar<TrapConstructible>();
    test_is_not_scalar<TrapImplicitConversion>();
    test_is_not_scalar<TrapComma>();
    test_is_not_scalar<TrapCall>();
    test_is_not_scalar<TrapSelfAssign>();
    test_is_not_scalar<TrapDeref>();
    test_is_not_scalar<TrapArraySubscript>();

    test_is_not_scalar<void()>();
    test_is_not_scalar<void()&>();
    test_is_not_scalar<void() &&>();
    test_is_not_scalar<void() const>();
    test_is_not_scalar<void() const&>();
    test_is_not_scalar<void() const&&>();
    test_is_not_scalar<void() volatile>();
    test_is_not_scalar<void() volatile&>();
    test_is_not_scalar<void() volatile&&>();
    test_is_not_scalar<void() const volatile>();
    test_is_not_scalar<void() const volatile&>();
    test_is_not_scalar<void() const volatile&&>();
    test_is_not_scalar<void() noexcept>();
    test_is_not_scalar<void()& noexcept>();
    test_is_not_scalar<void()&& noexcept>();
    test_is_not_scalar<void() const noexcept>();
    test_is_not_scalar<void() const& noexcept>();
    test_is_not_scalar<void() const&& noexcept>();
    test_is_not_scalar<void() volatile noexcept>();
    test_is_not_scalar<void() volatile& noexcept>();
    test_is_not_scalar<void() volatile&& noexcept>();
    test_is_not_scalar<void() const volatile noexcept>();
    test_is_not_scalar<void() const volatile& noexcept>();
    test_is_not_scalar<void() const volatile&& noexcept>();

    test_is_not_scalar<void(int)>();
    test_is_not_scalar<void(int)&>();
    test_is_not_scalar<void(int) &&>();
    test_is_not_scalar<void(int) const>();
    test_is_not_scalar<void(int) const&>();
    test_is_not_scalar<void(int) const&&>();
    test_is_not_scalar<void(int) volatile>();
    test_is_not_scalar<void(int) volatile&>();
    test_is_not_scalar<void(int) volatile&&>();
    test_is_not_scalar<void(int) const volatile>();
    test_is_not_scalar<void(int) const volatile&>();
    test_is_not_scalar<void(int) const volatile&&>();
    test_is_not_scalar<void(int) noexcept>();
    test_is_not_scalar<void(int)& noexcept>();
    test_is_not_scalar<void(int)&& noexcept>();
    test_is_not_scalar<void(int) const noexcept>();
    test_is_not_scalar<void(int) const& noexcept>();
    test_is_not_scalar<void(int) const&& noexcept>();
    test_is_not_scalar<void(int) volatile noexcept>();
    test_is_not_scalar<void(int) volatile& noexcept>();
    test_is_not_scalar<void(int) volatile&& noexcept>();
    test_is_not_scalar<void(int) const volatile noexcept>();
    test_is_not_scalar<void(int) const volatile& noexcept>();
    test_is_not_scalar<void(int) const volatile&& noexcept>();

    test_is_not_scalar<void(...)>();
    test_is_not_scalar<void(...)&>();
    test_is_not_scalar<void(...) &&>();
    test_is_not_scalar<void(...) const>();
    test_is_not_scalar<void(...) const&>();
    test_is_not_scalar<void(...) const&&>();
    test_is_not_scalar<void(...) volatile>();
    test_is_not_scalar<void(...) volatile&>();
    test_is_not_scalar<void(...) volatile&&>();
    test_is_not_scalar<void(...) const volatile>();
    test_is_not_scalar<void(...) const volatile&>();
    test_is_not_scalar<void(...) const volatile&&>();
    test_is_not_scalar<void(...) noexcept>();
    test_is_not_scalar<void(...)& noexcept>();
    test_is_not_scalar<void(...)&& noexcept>();
    test_is_not_scalar<void(...) const noexcept>();
    test_is_not_scalar<void(...) const& noexcept>();
    test_is_not_scalar<void(...) const&& noexcept>();
    test_is_not_scalar<void(...) volatile noexcept>();
    test_is_not_scalar<void(...) volatile& noexcept>();
    test_is_not_scalar<void(...) volatile&& noexcept>();
    test_is_not_scalar<void(...) const volatile noexcept>();
    test_is_not_scalar<void(...) const volatile& noexcept>();
    test_is_not_scalar<void(...) const volatile&& noexcept>();

    test_is_not_scalar<void(int, ...)>();
    test_is_not_scalar<void(int, ...)&>();
    test_is_not_scalar<void(int, ...) &&>();
    test_is_not_scalar<void(int, ...) const>();
    test_is_not_scalar<void(int, ...) const&>();
    test_is_not_scalar<void(int, ...) const&&>();
    test_is_not_scalar<void(int, ...) volatile>();
    test_is_not_scalar<void(int, ...) volatile&>();
    test_is_not_scalar<void(int, ...) volatile&&>();
    test_is_not_scalar<void(int, ...) const volatile>();
    test_is_not_scalar<void(int, ...) const volatile&>();
    test_is_not_scalar<void(int, ...) const volatile&&>();
    test_is_not_scalar<void(int, ...) noexcept>();
    test_is_not_scalar<void(int, ...)& noexcept>();
    test_is_not_scalar<void(int, ...)&& noexcept>();
    test_is_not_scalar<void(int, ...) const noexcept>();
    test_is_not_scalar<void(int, ...) const& noexcept>();
    test_is_not_scalar<void(int, ...) const&& noexcept>();
    test_is_not_scalar<void(int, ...) volatile noexcept>();
    test_is_not_scalar<void(int, ...) volatile& noexcept>();
    test_is_not_scalar<void(int, ...) volatile&& noexcept>();
    test_is_not_scalar<void(int, ...) const volatile noexcept>();
    test_is_not_scalar<void(int, ...) const volatile& noexcept>();
    test_is_not_scalar<void(int, ...) const volatile&& noexcept>();

    test_is_not_scalar<int()>();
    test_is_not_scalar<int()&>();
    test_is_not_scalar<int() &&>();
    test_is_not_scalar<int() const>();
    test_is_not_scalar<int() const&>();
    test_is_not_scalar<int() const&&>();
    test_is_not_scalar<int() volatile>();
    test_is_not_scalar<int() volatile&>();
    test_is_not_scalar<int() volatile&&>();
    test_is_not_scalar<int() const volatile>();
    test_is_not_scalar<int() const volatile&>();
    test_is_not_scalar<int() const volatile&&>();
    test_is_not_scalar<int() noexcept>();
    test_is_not_scalar<int()& noexcept>();
    test_is_not_scalar<int()&& noexcept>();
    test_is_not_scalar<int() const noexcept>();
    test_is_not_scalar<int() const& noexcept>();
    test_is_not_scalar<int() const&& noexcept>();
    test_is_not_scalar<int() volatile noexcept>();
    test_is_not_scalar<int() volatile& noexcept>();
    test_is_not_scalar<int() volatile&& noexcept>();
    test_is_not_scalar<int() const volatile noexcept>();
    test_is_not_scalar<int() const volatile& noexcept>();
    test_is_not_scalar<int() const volatile&& noexcept>();

    test_is_not_scalar<int(int)>();
    test_is_not_scalar<int(int)&>();
    test_is_not_scalar<int(int) &&>();
    test_is_not_scalar<int(int) const>();
    test_is_not_scalar<int(int) const&>();
    test_is_not_scalar<int(int) const&&>();
    test_is_not_scalar<int(int) volatile>();
    test_is_not_scalar<int(int) volatile&>();
    test_is_not_scalar<int(int) volatile&&>();
    test_is_not_scalar<int(int) const volatile>();
    test_is_not_scalar<int(int) const volatile&>();
    test_is_not_scalar<int(int) const volatile&&>();
    test_is_not_scalar<int(int) noexcept>();
    test_is_not_scalar<int(int)& noexcept>();
    test_is_not_scalar<int(int)&& noexcept>();
    test_is_not_scalar<int(int) const noexcept>();
    test_is_not_scalar<int(int) const& noexcept>();
    test_is_not_scalar<int(int) const&& noexcept>();
    test_is_not_scalar<int(int) volatile noexcept>();
    test_is_not_scalar<int(int) volatile& noexcept>();
    test_is_not_scalar<int(int) volatile&& noexcept>();
    test_is_not_scalar<int(int) const volatile noexcept>();
    test_is_not_scalar<int(int) const volatile& noexcept>();
    test_is_not_scalar<int(int) const volatile&& noexcept>();

    test_is_not_scalar<int(...)>();
    test_is_not_scalar<int(...)&>();
    test_is_not_scalar<int(...) &&>();
    test_is_not_scalar<int(...) const>();
    test_is_not_scalar<int(...) const&>();
    test_is_not_scalar<int(...) const&&>();
    test_is_not_scalar<int(...) volatile>();
    test_is_not_scalar<int(...) volatile&>();
    test_is_not_scalar<int(...) volatile&&>();
    test_is_not_scalar<int(...) const volatile>();
    test_is_not_scalar<int(...) const volatile&>();
    test_is_not_scalar<int(...) const volatile&&>();
    test_is_not_scalar<int(...) noexcept>();
    test_is_not_scalar<int(...)& noexcept>();
    test_is_not_scalar<int(...)&& noexcept>();
    test_is_not_scalar<int(...) const noexcept>();
    test_is_not_scalar<int(...) const& noexcept>();
    test_is_not_scalar<int(...) const&& noexcept>();
    test_is_not_scalar<int(...) volatile noexcept>();
    test_is_not_scalar<int(...) volatile& noexcept>();
    test_is_not_scalar<int(...) volatile&& noexcept>();
    test_is_not_scalar<int(...) const volatile noexcept>();
    test_is_not_scalar<int(...) const volatile& noexcept>();
    test_is_not_scalar<int(...) const volatile&& noexcept>();

    test_is_not_scalar<int(int, ...)>();
    test_is_not_scalar<int(int, ...)&>();
    test_is_not_scalar<int(int, ...) &&>();
    test_is_not_scalar<int(int, ...) const>();
    test_is_not_scalar<int(int, ...) const&>();
    test_is_not_scalar<int(int, ...) const&&>();
    test_is_not_scalar<int(int, ...) volatile>();
    test_is_not_scalar<int(int, ...) volatile&>();
    test_is_not_scalar<int(int, ...) volatile&&>();
    test_is_not_scalar<int(int, ...) const volatile>();
    test_is_not_scalar<int(int, ...) const volatile&>();
    test_is_not_scalar<int(int, ...) const volatile&&>();
    test_is_not_scalar<int(int, ...) noexcept>();
    test_is_not_scalar<int(int, ...)& noexcept>();
    test_is_not_scalar<int(int, ...)&& noexcept>();
    test_is_not_scalar<int(int, ...) const noexcept>();
    test_is_not_scalar<int(int, ...) const& noexcept>();
    test_is_not_scalar<int(int, ...) const&& noexcept>();
    test_is_not_scalar<int(int, ...) volatile noexcept>();
    test_is_not_scalar<int(int, ...) volatile& noexcept>();
    test_is_not_scalar<int(int, ...) volatile&& noexcept>();
    test_is_not_scalar<int(int, ...) const volatile noexcept>();
    test_is_not_scalar<int(int, ...) const volatile& noexcept>();
    test_is_not_scalar<int(int, ...) const volatile&& noexcept>();

    test_is_scalar<void (*)()>();
    test_is_scalar<void (*)() noexcept>();

    test_is_scalar<void (*)(int)>();
    test_is_scalar<void (*)(int) noexcept>();

    test_is_scalar<void (*)(...)>();
    test_is_scalar<void (*)(...) noexcept>();

    test_is_scalar<void (*)(int, ...)>();
    test_is_scalar<void (*)(int, ...) noexcept>();

    test_is_scalar<int (*)()>();
    test_is_scalar<int (*)() noexcept>();

    test_is_scalar<int (*)(int)>();
    test_is_scalar<int (*)(int) noexcept>();

    test_is_scalar<int (*)(...)>();
    test_is_scalar<int (*)(...) noexcept>();

    test_is_scalar<int (*)(int, ...)>();
    test_is_scalar<int (*)(int, ...) noexcept>();

    test_is_not_scalar<void (&)()>();
    test_is_not_scalar<void (&)() noexcept>();

    test_is_not_scalar<void (&)(int)>();
    test_is_not_scalar<void (&)(int) noexcept>();

    test_is_not_scalar<void (&)(...)>();
    test_is_not_scalar<void (&)(...) noexcept>();

    test_is_not_scalar<void (&)(int, ...)>();
    test_is_not_scalar<void (&)(int, ...) noexcept>();

    test_is_not_scalar<int (&)()>();
    test_is_not_scalar<int (&)() noexcept>();

    test_is_not_scalar<int (&)(int)>();
    test_is_not_scalar<int (&)(int) noexcept>();

    test_is_not_scalar<int (&)(...)>();
    test_is_not_scalar<int (&)(...) noexcept>();

    test_is_not_scalar<int (&)(int, ...)>();
    test_is_not_scalar<int (&)(int, ...) noexcept>();

    test_is_not_scalar<void(&&)()>();
    test_is_not_scalar<void(&&)() noexcept>();

    test_is_not_scalar<void(&&)(int)>();
    test_is_not_scalar<void(&&)(int) noexcept>();

    test_is_not_scalar<void(&&)(...)>();
    test_is_not_scalar<void(&&)(...) noexcept>();

    test_is_not_scalar<void(&&)(int, ...)>();
    test_is_not_scalar<void(&&)(int, ...) noexcept>();

    test_is_not_scalar<int(&&)()>();
    test_is_not_scalar<int(&&)() noexcept>();

    test_is_not_scalar<int(&&)(int)>();
    test_is_not_scalar<int(&&)(int) noexcept>();

    test_is_not_scalar<int(&&)(...)>();
    test_is_not_scalar<int(&&)(...) noexcept>();

    test_is_not_scalar<int(&&)(int, ...)>();
    test_is_not_scalar<int(&&)(int, ...) noexcept>();

    test_is_scalar<void (Class::*)()>();
    test_is_scalar<void (Class::*)()&>();
    test_is_scalar<void (Class::*)() &&>();
    test_is_scalar<void (Class::*)() const>();
    test_is_scalar<void (Class::*)() const&>();
    test_is_scalar<void (Class::*)() const&&>();
    test_is_scalar<void (Class::*)() noexcept>();
    test_is_scalar<void (Class::*)()& noexcept>();
    test_is_scalar<void (Class::*)()&& noexcept>();
    test_is_scalar<void (Class::*)() const noexcept>();
    test_is_scalar<void (Class::*)() const& noexcept>();
    test_is_scalar<void (Class::*)() const&& noexcept>();

    test_is_scalar<void (Class::*)(int)>();
    test_is_scalar<void (Class::*)(int)&>();
    test_is_scalar<void (Class::*)(int) &&>();
    test_is_scalar<void (Class::*)(int) const>();
    test_is_scalar<void (Class::*)(int) const&>();
    test_is_scalar<void (Class::*)(int) const&&>();
    test_is_scalar<void (Class::*)(int) noexcept>();
    test_is_scalar<void (Class::*)(int)& noexcept>();
    test_is_scalar<void (Class::*)(int)&& noexcept>();
    test_is_scalar<void (Class::*)(int) const noexcept>();
    test_is_scalar<void (Class::*)(int) const& noexcept>();
    test_is_scalar<void (Class::*)(int) const&& noexcept>();

    test_is_scalar<void (Class::*)(...)>();
    test_is_scalar<void (Class::*)(...)&>();
    test_is_scalar<void (Class::*)(...) &&>();
    test_is_scalar<void (Class::*)(...) const>();
    test_is_scalar<void (Class::*)(...) const&>();
    test_is_scalar<void (Class::*)(...) const&&>();
    test_is_scalar<void (Class::*)(...) noexcept>();
    test_is_scalar<void (Class::*)(...)& noexcept>();
    test_is_scalar<void (Class::*)(...)&& noexcept>();
    test_is_scalar<void (Class::*)(...) const noexcept>();
    test_is_scalar<void (Class::*)(...) const& noexcept>();
    test_is_scalar<void (Class::*)(...) const&& noexcept>();

    test_is_scalar<void (Class::*)(int, ...)>();
    test_is_scalar<void (Class::*)(int, ...)&>();
    test_is_scalar<void (Class::*)(int, ...) &&>();
    test_is_scalar<void (Class::*)(int, ...) const>();
    test_is_scalar<void (Class::*)(int, ...) const&>();
    test_is_scalar<void (Class::*)(int, ...) const&&>();
    test_is_scalar<void (Class::*)(int, ...) noexcept>();
    test_is_scalar<void (Class::*)(int, ...)& noexcept>();
    test_is_scalar<void (Class::*)(int, ...)&& noexcept>();
    test_is_scalar<void (Class::*)(int, ...) const noexcept>();
    test_is_scalar<void (Class::*)(int, ...) const& noexcept>();
    test_is_scalar<void (Class::*)(int, ...) const&& noexcept>();

    test_is_scalar<int (Class::*)()>();
    test_is_scalar<int (Class::*)()&>();
    test_is_scalar<int (Class::*)() &&>();
    test_is_scalar<int (Class::*)() const>();
    test_is_scalar<int (Class::*)() const&>();
    test_is_scalar<int (Class::*)() const&&>();
    test_is_scalar<int (Class::*)() noexcept>();
    test_is_scalar<int (Class::*)()& noexcept>();
    test_is_scalar<int (Class::*)()&& noexcept>();
    test_is_scalar<int (Class::*)() const noexcept>();
    test_is_scalar<int (Class::*)() const& noexcept>();
    test_is_scalar<int (Class::*)() const&& noexcept>();

    test_is_scalar<int (Class::*)(int)>();
    test_is_scalar<int (Class::*)(int)&>();
    test_is_scalar<int (Class::*)(int) &&>();
    test_is_scalar<int (Class::*)(int) const>();
    test_is_scalar<int (Class::*)(int) const&>();
    test_is_scalar<int (Class::*)(int) const&&>();
    test_is_scalar<int (Class::*)(int) noexcept>();
    test_is_scalar<int (Class::*)(int)& noexcept>();
    test_is_scalar<int (Class::*)(int)&& noexcept>();
    test_is_scalar<int (Class::*)(int) const noexcept>();
    test_is_scalar<int (Class::*)(int) const& noexcept>();
    test_is_scalar<int (Class::*)(int) const&& noexcept>();

    test_is_scalar<int (Class::*)(...)>();
    test_is_scalar<int (Class::*)(...)&>();
    test_is_scalar<int (Class::*)(...) &&>();
    test_is_scalar<int (Class::*)(...) const>();
    test_is_scalar<int (Class::*)(...) const&>();
    test_is_scalar<int (Class::*)(...) const&&>();
    test_is_scalar<int (Class::*)(...) noexcept>();
    test_is_scalar<int (Class::*)(...)& noexcept>();
    test_is_scalar<int (Class::*)(...)&& noexcept>();
    test_is_scalar<int (Class::*)(...) const noexcept>();
    test_is_scalar<int (Class::*)(...) const& noexcept>();
    test_is_scalar<int (Class::*)(...) const&& noexcept>();

    test_is_scalar<int (Class::*)(int, ...)>();
    test_is_scalar<int (Class::*)(int, ...)&>();
    test_is_scalar<int (Class::*)(int, ...) &&>();
    test_is_scalar<int (Class::*)(int, ...) const>();
    test_is_scalar<int (Class::*)(int, ...) const&>();
    test_is_scalar<int (Class::*)(int, ...) const&&>();
    test_is_scalar<int (Class::*)(int, ...) noexcept>();
    test_is_scalar<int (Class::*)(int, ...)& noexcept>();
    test_is_scalar<int (Class::*)(int, ...)&& noexcept>();
    test_is_scalar<int (Class::*)(int, ...) const noexcept>();
    test_is_scalar<int (Class::*)(int, ...) const& noexcept>();
    test_is_scalar<int (Class::*)(int, ...) const&& noexcept>();
}
