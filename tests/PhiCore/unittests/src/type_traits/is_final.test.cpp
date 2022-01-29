#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/cpp_standard.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_final.hpp>
#include <type_traits>
#include <vector>

struct A
{};

struct B final : public A
{};

struct C : public A
{};

struct P final
{};

union U1
{};

union U2 final
{};

template <typename T>
void test_is_final_impl()
{
#if PHI_HAS_WORKING_IS_FINAL()
    STATIC_REQUIRE(phi::is_final<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_final<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_final_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_final_v<T>);
#    endif

    // Standard compatibility
#    if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(std::is_final<T>::value);
#    endif
#endif
}

template <typename T>
void test_is_final()
{
    test_is_final_impl<T>();
    test_is_final_impl<const T>();
    test_is_final_impl<volatile T>();
    test_is_final_impl<const volatile T>();
}

template <typename T>
void test_is_not_final_impl()
{
#if PHI_HAS_WORKING_IS_FINAL()
    STATIC_REQUIRE_FALSE(phi::is_final<T>::value);
    STATIC_REQUIRE(phi::is_not_final<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_final_v<T>);
    STATIC_REQUIRE(phi::is_not_final_v<T>);
#    endif

    // Standard compatibility
#    if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE_FALSE(std::is_final<T>::value);
#    endif
#endif
}

template <typename T>
void test_is_not_final()
{
    test_is_not_final_impl<T>();
    test_is_not_final_impl<const T>();
    test_is_not_final_impl<volatile T>();
    test_is_not_final_impl<const volatile T>();
}

TEST_CASE("is_final")
{
    test_is_final<B>();
    test_is_final<P>();
    test_is_final<U2>();
    test_is_not_final<A>();
    test_is_not_final<C>();
    test_is_not_final<P*>();
    test_is_not_final<U1>();
    test_is_not_final<U1*>();
    test_is_not_final<U2*>();

    test_is_not_final<void>();
    test_is_not_final<phi::nullptr_t>();
    test_is_not_final<bool>();
    test_is_not_final<char>();
    test_is_not_final<signed char>();
    test_is_not_final<unsigned char>();
    test_is_not_final<short>();
    test_is_not_final<unsigned short>();
    test_is_not_final<int>();
    test_is_not_final<unsigned int>();
    test_is_not_final<long>();
    test_is_not_final<unsigned long>();
    test_is_not_final<long long>();
    test_is_not_final<unsigned long long>();
    test_is_not_final<float>();
    test_is_not_final<double>();
    test_is_not_final<long double>();
    test_is_not_final<char8_t>();
    test_is_not_final<char16_t>();
    test_is_not_final<char32_t>();
    test_is_not_final<wchar_t>();

    test_is_not_final<phi::boolean>();
    test_is_not_final<phi::integer<signed char>>();
    test_is_not_final<phi::integer<unsigned char>>();
    test_is_not_final<phi::integer<short>>();
    test_is_not_final<phi::integer<unsigned short>>();
    test_is_not_final<phi::integer<int>>();
    test_is_not_final<phi::integer<unsigned int>>();
    test_is_not_final<phi::integer<long>>();
    test_is_not_final<phi::integer<unsigned long>>();
    test_is_not_final<phi::integer<long long>>();
    test_is_not_final<phi::integer<unsigned long long>>();
    test_is_not_final<phi::floating_point<float>>();
    test_is_not_final<phi::floating_point<double>>();
    test_is_not_final<phi::floating_point<long double>>();

    test_is_not_final<std::vector<int>>();
    test_is_not_final<phi::scope_ptr<int>>();

    test_is_not_final<int&>();
    test_is_not_final<const int&>();
    test_is_not_final<volatile int&>();
    test_is_not_final<const volatile int&>();
    test_is_not_final<int&&>();
    test_is_not_final<const int&&>();
    test_is_not_final<volatile int&&>();
    test_is_not_final<const volatile int&&>();
    test_is_not_final<int*>();
    test_is_not_final<const int*>();
    test_is_not_final<volatile int*>();
    test_is_not_final<const volatile int*>();
    test_is_not_final<int**>();
    test_is_not_final<const int**>();
    test_is_not_final<volatile int**>();
    test_is_not_final<const volatile int**>();
    test_is_not_final<int*&>();
    test_is_not_final<const int*&>();
    test_is_not_final<volatile int*&>();
    test_is_not_final<const volatile int*&>();
    test_is_not_final<int*&&>();
    test_is_not_final<const int*&&>();
    test_is_not_final<volatile int*&&>();
    test_is_not_final<const volatile int*&&>();
    test_is_not_final<void*>();
    test_is_not_final<char[3]>();
    test_is_not_final<char[]>();
    test_is_not_final<char* [3]>();
    test_is_not_final<char*[]>();
    test_is_not_final<int(*)[3]>();
    test_is_not_final<int(*)[]>();
    test_is_not_final<int(&)[3]>();
    test_is_not_final<int(&)[]>();
    test_is_not_final<int(&&)[3]>();
    test_is_not_final<int(&&)[]>();
    test_is_not_final<char[3][2]>();
    test_is_not_final<char[][2]>();
    test_is_not_final<char* [3][2]>();
    test_is_not_final<char*[][2]>();
    test_is_not_final<int(*)[3][2]>();
    test_is_not_final<int(*)[][2]>();
    test_is_not_final<int(&)[3][2]>();
    test_is_not_final<int(&)[][2]>();
    test_is_not_final<int(&&)[3][2]>();
    test_is_not_final<int(&&)[][2]>();
    test_is_not_final<Class>();
    test_is_not_final<Class[]>();
    test_is_not_final<Class[2]>();
    test_is_not_final<Template<void>>();
    test_is_not_final<Template<int>>();
    test_is_not_final<Template<Class>>();
    test_is_not_final<Template<IncompleteType>>();
    test_is_not_final<VariadicTemplate<>>();
    test_is_not_final<VariadicTemplate<void>>();
    test_is_not_final<VariadicTemplate<int>>();
    test_is_not_final<VariadicTemplate<Class>>();
    test_is_not_final<VariadicTemplate<IncompleteType>>();
    test_is_not_final<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_final<PublicDerivedFromTemplate<Base>>();
    test_is_not_final<PublicDerivedFromTemplate<Derived>>();
    test_is_not_final<PublicDerivedFromTemplate<Class>>();
    test_is_not_final<PrivateDerivedFromTemplate<Base>>();
    test_is_not_final<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_final<PrivateDerivedFromTemplate<Class>>();
    test_is_not_final<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_final<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_final<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_final<Union>();
    test_is_not_final<NonEmptyUnion>();
    test_is_not_final<Empty>();
    test_is_not_final<NotEmpty>();
    test_is_not_final<BitZero>();
    test_is_not_final<BitOne>();
    test_is_not_final<Base>();
    test_is_not_final<Derived>();
    test_is_not_final<Abstract>();
    test_is_not_final<PublicAbstract>();
    test_is_not_final<PrivateAbstract>();
    test_is_not_final<ProtectedAbstract>();
    test_is_not_final<AbstractTemplate<int>>();
    test_is_not_final<AbstractTemplate<double>>();
    test_is_not_final<AbstractTemplate<Class>>();
    test_is_not_final<AbstractTemplate<IncompleteType>>();
    test_is_final<Final>();
    test_is_not_final<PublicDestructor>();
    test_is_not_final<ProtectedDestructor>();
    test_is_not_final<PrivateDestructor>();
    test_is_not_final<VirtualPublicDestructor>();
    test_is_not_final<VirtualProtectedDestructor>();
    test_is_not_final<VirtualPrivateDestructor>();
    test_is_not_final<PurePublicDestructor>();
    test_is_not_final<PureProtectedDestructor>();
    test_is_not_final<PurePrivateDestructor>();
    test_is_not_final<DeletedPublicDestructor>();
    test_is_not_final<DeletedProtectedDestructor>();
    test_is_not_final<DeletedPrivateDestructor>();
    test_is_not_final<DeletedVirtualPublicDestructor>();
    test_is_not_final<DeletedVirtualProtectedDestructor>();
    test_is_not_final<DeletedVirtualPrivateDestructor>();
    test_is_not_final<Enum>();
    test_is_not_final<EnumSigned>();
    test_is_not_final<EnumUnsigned>();
    test_is_not_final<EnumClass>();
    test_is_not_final<EnumStruct>();
    test_is_not_final<Function>();
    test_is_not_final<FunctionPtr>();
    test_is_not_final<MemberObjectPtr>();
    test_is_not_final<MemberFunctionPtr>();
    test_is_not_final<int Class::*>();
    test_is_not_final<float Class::*>();
    test_is_not_final<void * Class::*>();
    test_is_not_final<int * Class::*>();
    test_is_not_final<int Class::*&>();
    test_is_not_final<float Class::*&>();
    test_is_not_final<void * Class::*&>();
    test_is_not_final<int * Class::*&>();
    test_is_not_final<int Class::*&&>();
    test_is_not_final<float Class::*&&>();
    test_is_not_final<void * Class::*&&>();
    test_is_not_final<int * Class::*&&>();
    test_is_not_final<int Class::*const>();
    test_is_not_final<float Class::*const>();
    test_is_not_final<void * Class::*const>();
    test_is_not_final<int Class::*const&>();
    test_is_not_final<float Class::*const&>();
    test_is_not_final<void * Class::*const&>();
    test_is_not_final<int Class::*const&&>();
    test_is_not_final<float Class::*const&&>();
    test_is_not_final<void * Class::*const&&>();
    test_is_not_final<int Class::*volatile>();
    test_is_not_final<float Class::*volatile>();
    test_is_not_final<void * Class::*volatile>();
    test_is_not_final<int Class::*volatile&>();
    test_is_not_final<float Class::*volatile&>();
    test_is_not_final<void * Class::*volatile&>();
    test_is_not_final<int Class::*volatile&&>();
    test_is_not_final<float Class::*volatile&&>();
    test_is_not_final<void * Class::*volatile&&>();
    test_is_not_final<int Class::*const volatile>();
    test_is_not_final<float Class::*const volatile>();
    test_is_not_final<void * Class::*const volatile>();
    test_is_not_final<int Class::*const volatile&>();
    test_is_not_final<float Class::*const volatile&>();
    test_is_not_final<void * Class::*const volatile&>();
    test_is_not_final<int Class::*const volatile&&>();
    test_is_not_final<float Class::*const volatile&&>();
    test_is_not_final<void * Class::*const volatile&&>();
    test_is_not_final<NonCopyable>();
    test_is_not_final<NonMoveable>();
    test_is_not_final<NonConstructible>();
    test_is_not_final<Tracked>();
    test_is_not_final<TrapConstructible>();
    test_is_not_final<TrapImplicitConversion>();
    test_is_not_final<TrapComma>();
    test_is_not_final<TrapCall>();
    test_is_not_final<TrapSelfAssign>();
    test_is_not_final<TrapDeref>();
    test_is_not_final<TrapArraySubscript>();

    test_is_not_final<void()>();
    test_is_not_final<void()&>();
    test_is_not_final<void() &&>();
    test_is_not_final<void() const>();
    test_is_not_final<void() const&>();
    test_is_not_final<void() const&&>();
    test_is_not_final<void() volatile>();
    test_is_not_final<void() volatile&>();
    test_is_not_final<void() volatile&&>();
    test_is_not_final<void() const volatile>();
    test_is_not_final<void() const volatile&>();
    test_is_not_final<void() const volatile&&>();
    test_is_not_final<void() noexcept>();
    test_is_not_final<void()& noexcept>();
    test_is_not_final<void()&& noexcept>();
    test_is_not_final<void() const noexcept>();
    test_is_not_final<void() const& noexcept>();
    test_is_not_final<void() const&& noexcept>();
    test_is_not_final<void() volatile noexcept>();
    test_is_not_final<void() volatile& noexcept>();
    test_is_not_final<void() volatile&& noexcept>();
    test_is_not_final<void() const volatile noexcept>();
    test_is_not_final<void() const volatile& noexcept>();
    test_is_not_final<void() const volatile&& noexcept>();

    test_is_not_final<void(int)>();
    test_is_not_final<void(int)&>();
    test_is_not_final<void(int) &&>();
    test_is_not_final<void(int) const>();
    test_is_not_final<void(int) const&>();
    test_is_not_final<void(int) const&&>();
    test_is_not_final<void(int) volatile>();
    test_is_not_final<void(int) volatile&>();
    test_is_not_final<void(int) volatile&&>();
    test_is_not_final<void(int) const volatile>();
    test_is_not_final<void(int) const volatile&>();
    test_is_not_final<void(int) const volatile&&>();
    test_is_not_final<void(int) noexcept>();
    test_is_not_final<void(int)& noexcept>();
    test_is_not_final<void(int)&& noexcept>();
    test_is_not_final<void(int) const noexcept>();
    test_is_not_final<void(int) const& noexcept>();
    test_is_not_final<void(int) const&& noexcept>();
    test_is_not_final<void(int) volatile noexcept>();
    test_is_not_final<void(int) volatile& noexcept>();
    test_is_not_final<void(int) volatile&& noexcept>();
    test_is_not_final<void(int) const volatile noexcept>();
    test_is_not_final<void(int) const volatile& noexcept>();
    test_is_not_final<void(int) const volatile&& noexcept>();

    test_is_not_final<void(...)>();
    test_is_not_final<void(...)&>();
    test_is_not_final<void(...) &&>();
    test_is_not_final<void(...) const>();
    test_is_not_final<void(...) const&>();
    test_is_not_final<void(...) const&&>();
    test_is_not_final<void(...) volatile>();
    test_is_not_final<void(...) volatile&>();
    test_is_not_final<void(...) volatile&&>();
    test_is_not_final<void(...) const volatile>();
    test_is_not_final<void(...) const volatile&>();
    test_is_not_final<void(...) const volatile&&>();
    test_is_not_final<void(...) noexcept>();
    test_is_not_final<void(...)& noexcept>();
    test_is_not_final<void(...)&& noexcept>();
    test_is_not_final<void(...) const noexcept>();
    test_is_not_final<void(...) const& noexcept>();
    test_is_not_final<void(...) const&& noexcept>();
    test_is_not_final<void(...) volatile noexcept>();
    test_is_not_final<void(...) volatile& noexcept>();
    test_is_not_final<void(...) volatile&& noexcept>();
    test_is_not_final<void(...) const volatile noexcept>();
    test_is_not_final<void(...) const volatile& noexcept>();
    test_is_not_final<void(...) const volatile&& noexcept>();

    test_is_not_final<void(int, ...)>();
    test_is_not_final<void(int, ...)&>();
    test_is_not_final<void(int, ...) &&>();
    test_is_not_final<void(int, ...) const>();
    test_is_not_final<void(int, ...) const&>();
    test_is_not_final<void(int, ...) const&&>();
    test_is_not_final<void(int, ...) volatile>();
    test_is_not_final<void(int, ...) volatile&>();
    test_is_not_final<void(int, ...) volatile&&>();
    test_is_not_final<void(int, ...) const volatile>();
    test_is_not_final<void(int, ...) const volatile&>();
    test_is_not_final<void(int, ...) const volatile&&>();
    test_is_not_final<void(int, ...) noexcept>();
    test_is_not_final<void(int, ...)& noexcept>();
    test_is_not_final<void(int, ...)&& noexcept>();
    test_is_not_final<void(int, ...) const noexcept>();
    test_is_not_final<void(int, ...) const& noexcept>();
    test_is_not_final<void(int, ...) const&& noexcept>();
    test_is_not_final<void(int, ...) volatile noexcept>();
    test_is_not_final<void(int, ...) volatile& noexcept>();
    test_is_not_final<void(int, ...) volatile&& noexcept>();
    test_is_not_final<void(int, ...) const volatile noexcept>();
    test_is_not_final<void(int, ...) const volatile& noexcept>();
    test_is_not_final<void(int, ...) const volatile&& noexcept>();

    test_is_not_final<int()>();
    test_is_not_final<int()&>();
    test_is_not_final<int() &&>();
    test_is_not_final<int() const>();
    test_is_not_final<int() const&>();
    test_is_not_final<int() const&&>();
    test_is_not_final<int() volatile>();
    test_is_not_final<int() volatile&>();
    test_is_not_final<int() volatile&&>();
    test_is_not_final<int() const volatile>();
    test_is_not_final<int() const volatile&>();
    test_is_not_final<int() const volatile&&>();
    test_is_not_final<int() noexcept>();
    test_is_not_final<int()& noexcept>();
    test_is_not_final<int()&& noexcept>();
    test_is_not_final<int() const noexcept>();
    test_is_not_final<int() const& noexcept>();
    test_is_not_final<int() const&& noexcept>();
    test_is_not_final<int() volatile noexcept>();
    test_is_not_final<int() volatile& noexcept>();
    test_is_not_final<int() volatile&& noexcept>();
    test_is_not_final<int() const volatile noexcept>();
    test_is_not_final<int() const volatile& noexcept>();
    test_is_not_final<int() const volatile&& noexcept>();

    test_is_not_final<int(int)>();
    test_is_not_final<int(int)&>();
    test_is_not_final<int(int) &&>();
    test_is_not_final<int(int) const>();
    test_is_not_final<int(int) const&>();
    test_is_not_final<int(int) const&&>();
    test_is_not_final<int(int) volatile>();
    test_is_not_final<int(int) volatile&>();
    test_is_not_final<int(int) volatile&&>();
    test_is_not_final<int(int) const volatile>();
    test_is_not_final<int(int) const volatile&>();
    test_is_not_final<int(int) const volatile&&>();
    test_is_not_final<int(int) noexcept>();
    test_is_not_final<int(int)& noexcept>();
    test_is_not_final<int(int)&& noexcept>();
    test_is_not_final<int(int) const noexcept>();
    test_is_not_final<int(int) const& noexcept>();
    test_is_not_final<int(int) const&& noexcept>();
    test_is_not_final<int(int) volatile noexcept>();
    test_is_not_final<int(int) volatile& noexcept>();
    test_is_not_final<int(int) volatile&& noexcept>();
    test_is_not_final<int(int) const volatile noexcept>();
    test_is_not_final<int(int) const volatile& noexcept>();
    test_is_not_final<int(int) const volatile&& noexcept>();

    test_is_not_final<int(...)>();
    test_is_not_final<int(...)&>();
    test_is_not_final<int(...) &&>();
    test_is_not_final<int(...) const>();
    test_is_not_final<int(...) const&>();
    test_is_not_final<int(...) const&&>();
    test_is_not_final<int(...) volatile>();
    test_is_not_final<int(...) volatile&>();
    test_is_not_final<int(...) volatile&&>();
    test_is_not_final<int(...) const volatile>();
    test_is_not_final<int(...) const volatile&>();
    test_is_not_final<int(...) const volatile&&>();
    test_is_not_final<int(...) noexcept>();
    test_is_not_final<int(...)& noexcept>();
    test_is_not_final<int(...)&& noexcept>();
    test_is_not_final<int(...) const noexcept>();
    test_is_not_final<int(...) const& noexcept>();
    test_is_not_final<int(...) const&& noexcept>();
    test_is_not_final<int(...) volatile noexcept>();
    test_is_not_final<int(...) volatile& noexcept>();
    test_is_not_final<int(...) volatile&& noexcept>();
    test_is_not_final<int(...) const volatile noexcept>();
    test_is_not_final<int(...) const volatile& noexcept>();
    test_is_not_final<int(...) const volatile&& noexcept>();

    test_is_not_final<int(int, ...)>();
    test_is_not_final<int(int, ...)&>();
    test_is_not_final<int(int, ...) &&>();
    test_is_not_final<int(int, ...) const>();
    test_is_not_final<int(int, ...) const&>();
    test_is_not_final<int(int, ...) const&&>();
    test_is_not_final<int(int, ...) volatile>();
    test_is_not_final<int(int, ...) volatile&>();
    test_is_not_final<int(int, ...) volatile&&>();
    test_is_not_final<int(int, ...) const volatile>();
    test_is_not_final<int(int, ...) const volatile&>();
    test_is_not_final<int(int, ...) const volatile&&>();
    test_is_not_final<int(int, ...) noexcept>();
    test_is_not_final<int(int, ...)& noexcept>();
    test_is_not_final<int(int, ...)&& noexcept>();
    test_is_not_final<int(int, ...) const noexcept>();
    test_is_not_final<int(int, ...) const& noexcept>();
    test_is_not_final<int(int, ...) const&& noexcept>();
    test_is_not_final<int(int, ...) volatile noexcept>();
    test_is_not_final<int(int, ...) volatile& noexcept>();
    test_is_not_final<int(int, ...) volatile&& noexcept>();
    test_is_not_final<int(int, ...) const volatile noexcept>();
    test_is_not_final<int(int, ...) const volatile& noexcept>();
    test_is_not_final<int(int, ...) const volatile&& noexcept>();

    test_is_not_final<void (*)()>();
    test_is_not_final<void (*)() noexcept>();

    test_is_not_final<void (*)(int)>();
    test_is_not_final<void (*)(int) noexcept>();

    test_is_not_final<void (*)(...)>();
    test_is_not_final<void (*)(...) noexcept>();

    test_is_not_final<void (*)(int, ...)>();
    test_is_not_final<void (*)(int, ...) noexcept>();

    test_is_not_final<int (*)()>();
    test_is_not_final<int (*)() noexcept>();

    test_is_not_final<int (*)(int)>();
    test_is_not_final<int (*)(int) noexcept>();

    test_is_not_final<int (*)(...)>();
    test_is_not_final<int (*)(...) noexcept>();

    test_is_not_final<int (*)(int, ...)>();
    test_is_not_final<int (*)(int, ...) noexcept>();

    test_is_not_final<void (&)()>();
    test_is_not_final<void (&)() noexcept>();

    test_is_not_final<void (&)(int)>();
    test_is_not_final<void (&)(int) noexcept>();

    test_is_not_final<void (&)(...)>();
    test_is_not_final<void (&)(...) noexcept>();

    test_is_not_final<void (&)(int, ...)>();
    test_is_not_final<void (&)(int, ...) noexcept>();

    test_is_not_final<int (&)()>();
    test_is_not_final<int (&)() noexcept>();

    test_is_not_final<int (&)(int)>();
    test_is_not_final<int (&)(int) noexcept>();

    test_is_not_final<int (&)(...)>();
    test_is_not_final<int (&)(...) noexcept>();

    test_is_not_final<int (&)(int, ...)>();
    test_is_not_final<int (&)(int, ...) noexcept>();

    test_is_not_final<void(&&)()>();
    test_is_not_final<void(&&)() noexcept>();

    test_is_not_final<void(&&)(int)>();
    test_is_not_final<void(&&)(int) noexcept>();

    test_is_not_final<void(&&)(...)>();
    test_is_not_final<void(&&)(...) noexcept>();

    test_is_not_final<void(&&)(int, ...)>();
    test_is_not_final<void(&&)(int, ...) noexcept>();

    test_is_not_final<int(&&)()>();
    test_is_not_final<int(&&)() noexcept>();

    test_is_not_final<int(&&)(int)>();
    test_is_not_final<int(&&)(int) noexcept>();

    test_is_not_final<int(&&)(...)>();
    test_is_not_final<int(&&)(...) noexcept>();

    test_is_not_final<int(&&)(int, ...)>();
    test_is_not_final<int(&&)(int, ...) noexcept>();

    test_is_not_final<void (Class::*)()>();
    test_is_not_final<void (Class::*)()&>();
    test_is_not_final<void (Class::*)() &&>();
    test_is_not_final<void (Class::*)() const>();
    test_is_not_final<void (Class::*)() const&>();
    test_is_not_final<void (Class::*)() const&&>();
    test_is_not_final<void (Class::*)() noexcept>();
    test_is_not_final<void (Class::*)()& noexcept>();
    test_is_not_final<void (Class::*)()&& noexcept>();
    test_is_not_final<void (Class::*)() const noexcept>();
    test_is_not_final<void (Class::*)() const& noexcept>();
    test_is_not_final<void (Class::*)() const&& noexcept>();

    test_is_not_final<void (Class::*)(int)>();
    test_is_not_final<void (Class::*)(int)&>();
    test_is_not_final<void (Class::*)(int) &&>();
    test_is_not_final<void (Class::*)(int) const>();
    test_is_not_final<void (Class::*)(int) const&>();
    test_is_not_final<void (Class::*)(int) const&&>();
    test_is_not_final<void (Class::*)(int) noexcept>();
    test_is_not_final<void (Class::*)(int)& noexcept>();
    test_is_not_final<void (Class::*)(int)&& noexcept>();
    test_is_not_final<void (Class::*)(int) const noexcept>();
    test_is_not_final<void (Class::*)(int) const& noexcept>();
    test_is_not_final<void (Class::*)(int) const&& noexcept>();

    test_is_not_final<void (Class::*)(...)>();
    test_is_not_final<void (Class::*)(...)&>();
    test_is_not_final<void (Class::*)(...) &&>();
    test_is_not_final<void (Class::*)(...) const>();
    test_is_not_final<void (Class::*)(...) const&>();
    test_is_not_final<void (Class::*)(...) const&&>();
    test_is_not_final<void (Class::*)(...) noexcept>();
    test_is_not_final<void (Class::*)(...)& noexcept>();
    test_is_not_final<void (Class::*)(...)&& noexcept>();
    test_is_not_final<void (Class::*)(...) const noexcept>();
    test_is_not_final<void (Class::*)(...) const& noexcept>();
    test_is_not_final<void (Class::*)(...) const&& noexcept>();

    test_is_not_final<void (Class::*)(int, ...)>();
    test_is_not_final<void (Class::*)(int, ...)&>();
    test_is_not_final<void (Class::*)(int, ...) &&>();
    test_is_not_final<void (Class::*)(int, ...) const>();
    test_is_not_final<void (Class::*)(int, ...) const&>();
    test_is_not_final<void (Class::*)(int, ...) const&&>();
    test_is_not_final<void (Class::*)(int, ...) noexcept>();
    test_is_not_final<void (Class::*)(int, ...)& noexcept>();
    test_is_not_final<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_final<void (Class::*)(int, ...) const noexcept>();
    test_is_not_final<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_final<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_final<int (Class::*)()>();
    test_is_not_final<int (Class::*)()&>();
    test_is_not_final<int (Class::*)() &&>();
    test_is_not_final<int (Class::*)() const>();
    test_is_not_final<int (Class::*)() const&>();
    test_is_not_final<int (Class::*)() const&&>();
    test_is_not_final<int (Class::*)() noexcept>();
    test_is_not_final<int (Class::*)()& noexcept>();
    test_is_not_final<int (Class::*)()&& noexcept>();
    test_is_not_final<int (Class::*)() const noexcept>();
    test_is_not_final<int (Class::*)() const& noexcept>();
    test_is_not_final<int (Class::*)() const&& noexcept>();

    test_is_not_final<int (Class::*)(int)>();
    test_is_not_final<int (Class::*)(int)&>();
    test_is_not_final<int (Class::*)(int) &&>();
    test_is_not_final<int (Class::*)(int) const>();
    test_is_not_final<int (Class::*)(int) const&>();
    test_is_not_final<int (Class::*)(int) const&&>();
    test_is_not_final<int (Class::*)(int) noexcept>();
    test_is_not_final<int (Class::*)(int)& noexcept>();
    test_is_not_final<int (Class::*)(int)&& noexcept>();
    test_is_not_final<int (Class::*)(int) const noexcept>();
    test_is_not_final<int (Class::*)(int) const& noexcept>();
    test_is_not_final<int (Class::*)(int) const&& noexcept>();

    test_is_not_final<int (Class::*)(...)>();
    test_is_not_final<int (Class::*)(...)&>();
    test_is_not_final<int (Class::*)(...) &&>();
    test_is_not_final<int (Class::*)(...) const>();
    test_is_not_final<int (Class::*)(...) const&>();
    test_is_not_final<int (Class::*)(...) const&&>();
    test_is_not_final<int (Class::*)(...) noexcept>();
    test_is_not_final<int (Class::*)(...)& noexcept>();
    test_is_not_final<int (Class::*)(...)&& noexcept>();
    test_is_not_final<int (Class::*)(...) const noexcept>();
    test_is_not_final<int (Class::*)(...) const& noexcept>();
    test_is_not_final<int (Class::*)(...) const&& noexcept>();

    test_is_not_final<int (Class::*)(int, ...)>();
    test_is_not_final<int (Class::*)(int, ...)&>();
    test_is_not_final<int (Class::*)(int, ...) &&>();
    test_is_not_final<int (Class::*)(int, ...) const>();
    test_is_not_final<int (Class::*)(int, ...) const&>();
    test_is_not_final<int (Class::*)(int, ...) const&&>();
    test_is_not_final<int (Class::*)(int, ...) noexcept>();
    test_is_not_final<int (Class::*)(int, ...)& noexcept>();
    test_is_not_final<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_final<int (Class::*)(int, ...) const noexcept>();
    test_is_not_final<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_final<int (Class::*)(int, ...) const&& noexcept>();
}
