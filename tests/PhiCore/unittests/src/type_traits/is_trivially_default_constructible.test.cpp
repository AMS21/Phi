#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_default_constructible.hpp>
#include <phi/type_traits/is_trivially_default_constructible.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_trivially_default_constructible_impl()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_trivially_default_constructible<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_default_constructible<T>::value);
    STATIC_REQUIRE(phi::is_default_constructible<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_default_constructible_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_default_constructible_v<T>);
    STATIC_REQUIRE(phi::is_default_constructible_v<T>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_trivially_default_constructible<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_trivially_default_constructible<T>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_trivially_default_constructible<T>::value);
    STATIC_REQUIRE(std::is_default_constructible<T>::value);
#endif
}

template <typename T>
void test_is_not_trivially_default_constructible_impl()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_default_constructible<T>::value);
    STATIC_REQUIRE(phi::is_not_trivially_default_constructible<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_default_constructible_v<T>);
    STATIC_REQUIRE(phi::is_not_trivially_default_constructible_v<T>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_trivially_default_constructible<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_trivially_default_constructible<T>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_trivially_default_constructible<T>::value);
#endif
}

template <typename T>
void test_is_trivially_default_constructible()
{
    test_is_trivially_default_constructible_impl<T>();
    test_is_trivially_default_constructible_impl<const T>();
    test_is_trivially_default_constructible_impl<volatile T>();
    test_is_trivially_default_constructible_impl<const volatile T>();
}

template <typename T>
void test_is_not_trivially_default_constructible()
{
    test_is_not_trivially_default_constructible_impl<T>();
    test_is_not_trivially_default_constructible_impl<const T>();
    test_is_not_trivially_default_constructible_impl<volatile T>();
    test_is_not_trivially_default_constructible_impl<const volatile T>();
}

struct A
{
    A();
};

struct B
{
    B() = default;
};

TEST_CASE("is_trivially_default_constructible")
{
    test_is_not_trivially_default_constructible<A>();
    test_is_trivially_default_constructible<B>();

    test_is_not_trivially_default_constructible<void>();
    test_is_trivially_default_constructible<phi::nullptr_t>();
    test_is_trivially_default_constructible<bool>();
    test_is_trivially_default_constructible<char>();
    test_is_trivially_default_constructible<signed char>();
    test_is_trivially_default_constructible<unsigned char>();
    test_is_trivially_default_constructible<short>();
    test_is_trivially_default_constructible<unsigned short>();
    test_is_trivially_default_constructible<int>();
    test_is_trivially_default_constructible<unsigned int>();
    test_is_trivially_default_constructible<long>();
    test_is_trivially_default_constructible<unsigned long>();
    test_is_trivially_default_constructible<long long>();
    test_is_trivially_default_constructible<unsigned long long>();
    test_is_trivially_default_constructible<float>();
    test_is_trivially_default_constructible<double>();
    test_is_trivially_default_constructible<long double>();
    test_is_trivially_default_constructible<char8_t>();
    test_is_trivially_default_constructible<char16_t>();
    test_is_trivially_default_constructible<char32_t>();
    test_is_trivially_default_constructible<wchar_t>();

    test_is_not_trivially_default_constructible<phi::boolean>();
    test_is_not_trivially_default_constructible<phi::integer<signed char>>();
    test_is_not_trivially_default_constructible<phi::integer<unsigned char>>();
    test_is_not_trivially_default_constructible<phi::integer<short>>();
    test_is_not_trivially_default_constructible<phi::integer<unsigned short>>();
    test_is_not_trivially_default_constructible<phi::integer<int>>();
    test_is_not_trivially_default_constructible<phi::integer<unsigned int>>();
    test_is_not_trivially_default_constructible<phi::integer<long>>();
    test_is_not_trivially_default_constructible<phi::integer<unsigned long>>();
    test_is_not_trivially_default_constructible<phi::integer<long long>>();
    test_is_not_trivially_default_constructible<phi::integer<unsigned long long>>();
    test_is_not_trivially_default_constructible<phi::floating_point<float>>();
    test_is_not_trivially_default_constructible<phi::floating_point<double>>();
    test_is_not_trivially_default_constructible<phi::floating_point<long double>>();

    test_is_not_trivially_default_constructible<std::vector<int>>();
    test_is_not_trivially_default_constructible<phi::scope_ptr<int>>();

    test_is_not_trivially_default_constructible<int&>();
    test_is_not_trivially_default_constructible<const int&>();
    test_is_not_trivially_default_constructible<volatile int&>();
    test_is_not_trivially_default_constructible<const volatile int&>();
    test_is_not_trivially_default_constructible<int&&>();
    test_is_not_trivially_default_constructible<const int&&>();
    test_is_not_trivially_default_constructible<volatile int&&>();
    test_is_not_trivially_default_constructible<const volatile int&&>();
    test_is_trivially_default_constructible<int*>();
    test_is_trivially_default_constructible<const int*>();
    test_is_trivially_default_constructible<volatile int*>();
    test_is_trivially_default_constructible<const volatile int*>();
    test_is_trivially_default_constructible<int**>();
    test_is_trivially_default_constructible<const int**>();
    test_is_trivially_default_constructible<volatile int**>();
    test_is_trivially_default_constructible<const volatile int**>();
    test_is_not_trivially_default_constructible<int*&>();
    test_is_not_trivially_default_constructible<const int*&>();
    test_is_not_trivially_default_constructible<volatile int*&>();
    test_is_not_trivially_default_constructible<const volatile int*&>();
    test_is_not_trivially_default_constructible<int*&&>();
    test_is_not_trivially_default_constructible<const int*&&>();
    test_is_not_trivially_default_constructible<volatile int*&&>();
    test_is_not_trivially_default_constructible<const volatile int*&&>();
    test_is_trivially_default_constructible<void*>();
    test_is_trivially_default_constructible<char[3]>();
    test_is_not_trivially_default_constructible<char[]>();
    test_is_trivially_default_constructible<char* [3]>();
    test_is_not_trivially_default_constructible<char*[]>();
    test_is_trivially_default_constructible<int(*)[3]>();
    test_is_trivially_default_constructible<int(*)[]>();
    test_is_not_trivially_default_constructible<int(&)[3]>();
    test_is_not_trivially_default_constructible<int(&)[]>();
    test_is_not_trivially_default_constructible<int(&&)[3]>();
    test_is_not_trivially_default_constructible<int(&&)[]>();
    test_is_trivially_default_constructible<char[3][2]>();
    test_is_not_trivially_default_constructible<char[][2]>();
    test_is_trivially_default_constructible<char* [3][2]>();
    test_is_not_trivially_default_constructible<char*[][2]>();
    test_is_trivially_default_constructible<int(*)[3][2]>();
    test_is_trivially_default_constructible<int(*)[][2]>();
    test_is_not_trivially_default_constructible<int(&)[3][2]>();
    test_is_not_trivially_default_constructible<int(&)[][2]>();
    test_is_not_trivially_default_constructible<int(&&)[3][2]>();
    test_is_not_trivially_default_constructible<int(&&)[][2]>();
    test_is_not_trivially_default_constructible<Class>();
    test_is_not_trivially_default_constructible<Class[]>();
#if PHI_COMPILER_IS(GCC)
    test_is_trivially_default_constructible<Class[2]>();
#else
    test_is_not_trivially_default_constructible<Class[2]>();
#endif
    test_is_trivially_default_constructible<Template<void>>();
    test_is_trivially_default_constructible<Template<int>>();
    test_is_trivially_default_constructible<Template<Class>>();
    test_is_trivially_default_constructible<Template<IncompleteType>>();
    test_is_trivially_default_constructible<VariadicTemplate<>>();
    test_is_trivially_default_constructible<VariadicTemplate<void>>();
    test_is_trivially_default_constructible<VariadicTemplate<int>>();
    test_is_trivially_default_constructible<VariadicTemplate<Class>>();
    test_is_trivially_default_constructible<VariadicTemplate<IncompleteType>>();
    test_is_trivially_default_constructible<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_trivially_default_constructible<PublicDerivedFromTemplate<Base>>();
    test_is_trivially_default_constructible<PublicDerivedFromTemplate<Derived>>();
    test_is_not_trivially_default_constructible<PublicDerivedFromTemplate<Class>>();
    test_is_trivially_default_constructible<PrivateDerivedFromTemplate<Base>>();
    test_is_trivially_default_constructible<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_trivially_default_constructible<PrivateDerivedFromTemplate<Class>>();
    test_is_trivially_default_constructible<ProtectedDerivedFromTemplate<Base>>();
    test_is_trivially_default_constructible<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_trivially_default_constructible<ProtectedDerivedFromTemplate<Class>>();
    test_is_trivially_default_constructible<Union>();
    test_is_trivially_default_constructible<NonEmptyUnion>();
    test_is_trivially_default_constructible<Empty>();
    test_is_not_trivially_default_constructible<NotEmpty>();
    test_is_trivially_default_constructible<BitZero>();
    test_is_trivially_default_constructible<BitOne>();
    test_is_trivially_default_constructible<Base>();
    test_is_trivially_default_constructible<Derived>();
    test_is_not_trivially_default_constructible<Abstract>();
    test_is_not_trivially_default_constructible<PublicAbstract>();
    test_is_not_trivially_default_constructible<PrivateAbstract>();
    test_is_not_trivially_default_constructible<ProtectedAbstract>();
    test_is_not_trivially_default_constructible<AbstractTemplate<int>>();
    test_is_trivially_default_constructible<AbstractTemplate<double>>();
    test_is_not_trivially_default_constructible<AbstractTemplate<Class>>();
    test_is_not_trivially_default_constructible<AbstractTemplate<IncompleteType>>();
    test_is_trivially_default_constructible<Final>();
    test_is_trivially_default_constructible<PublicDestructor>();
    test_is_not_trivially_default_constructible<ProtectedDestructor>();
    test_is_not_trivially_default_constructible<PrivateDestructor>();
    test_is_not_trivially_default_constructible<VirtualPublicDestructor>();
    test_is_not_trivially_default_constructible<VirtualProtectedDestructor>();
    test_is_not_trivially_default_constructible<VirtualPrivateDestructor>();
    test_is_not_trivially_default_constructible<PurePublicDestructor>();
    test_is_not_trivially_default_constructible<PureProtectedDestructor>();
    test_is_not_trivially_default_constructible<PurePrivateDestructor>();
    test_is_not_trivially_default_constructible<DeletedPublicDestructor>();
    test_is_not_trivially_default_constructible<DeletedProtectedDestructor>();
    test_is_not_trivially_default_constructible<DeletedPrivateDestructor>();
    test_is_not_trivially_default_constructible<DeletedVirtualPublicDestructor>();
    test_is_not_trivially_default_constructible<DeletedVirtualProtectedDestructor>();
    test_is_not_trivially_default_constructible<DeletedVirtualPrivateDestructor>();
    test_is_trivially_default_constructible<Enum>();
    test_is_trivially_default_constructible<EnumSigned>();
    test_is_trivially_default_constructible<EnumUnsigned>();
    test_is_trivially_default_constructible<EnumClass>();
    test_is_trivially_default_constructible<EnumStruct>();
    test_is_not_trivially_default_constructible<Function>();
    test_is_trivially_default_constructible<FunctionPtr>();
    test_is_trivially_default_constructible<MemberObjectPtr>();
    test_is_trivially_default_constructible<MemberFunctionPtr>();
    test_is_trivially_default_constructible<int Class::*>();
    test_is_trivially_default_constructible<float Class::*>();
    test_is_trivially_default_constructible<void * Class::*>();
    test_is_trivially_default_constructible<int * Class::*>();
    test_is_not_trivially_default_constructible<int Class::*&>();
    test_is_not_trivially_default_constructible<float Class::*&>();
    test_is_not_trivially_default_constructible<void * Class::*&>();
    test_is_not_trivially_default_constructible<int * Class::*&>();
    test_is_not_trivially_default_constructible<int Class::*&&>();
    test_is_not_trivially_default_constructible<float Class::*&&>();
    test_is_not_trivially_default_constructible<void * Class::*&&>();
    test_is_not_trivially_default_constructible<int * Class::*&&>();
    test_is_trivially_default_constructible<int Class::*const>();
    test_is_trivially_default_constructible<float Class::*const>();
    test_is_trivially_default_constructible<void * Class::*const>();
    test_is_not_trivially_default_constructible<int Class::*const&>();
    test_is_not_trivially_default_constructible<float Class::*const&>();
    test_is_not_trivially_default_constructible<void * Class::*const&>();
    test_is_not_trivially_default_constructible<int Class::*const&&>();
    test_is_not_trivially_default_constructible<float Class::*const&&>();
    test_is_not_trivially_default_constructible<void * Class::*const&&>();
    test_is_trivially_default_constructible<int Class::*volatile>();
    test_is_trivially_default_constructible<float Class::*volatile>();
    test_is_trivially_default_constructible<void * Class::*volatile>();
    test_is_not_trivially_default_constructible<int Class::*volatile&>();
    test_is_not_trivially_default_constructible<float Class::*volatile&>();
    test_is_not_trivially_default_constructible<void * Class::*volatile&>();
    test_is_not_trivially_default_constructible<int Class::*volatile&&>();
    test_is_not_trivially_default_constructible<float Class::*volatile&&>();
    test_is_not_trivially_default_constructible<void * Class::*volatile&&>();
    test_is_trivially_default_constructible<int Class::*const volatile>();
    test_is_trivially_default_constructible<float Class::*const volatile>();
    test_is_trivially_default_constructible<void * Class::*const volatile>();
    test_is_not_trivially_default_constructible<int Class::*const volatile&>();
    test_is_not_trivially_default_constructible<float Class::*const volatile&>();
    test_is_not_trivially_default_constructible<void * Class::*const volatile&>();
    test_is_not_trivially_default_constructible<int Class::*const volatile&&>();
    test_is_not_trivially_default_constructible<float Class::*const volatile&&>();
    test_is_not_trivially_default_constructible<void * Class::*const volatile&&>();
    test_is_trivially_default_constructible<NonCopyable>();
    test_is_trivially_default_constructible<NonMoveable>();
    test_is_not_trivially_default_constructible<NonConstructible>();
    test_is_not_trivially_default_constructible<Tracked>();
    test_is_trivially_default_constructible<TrapConstructible>();
    test_is_trivially_default_constructible<TrapImplicitConversion>();
    test_is_trivially_default_constructible<TrapComma>();
    test_is_trivially_default_constructible<TrapCall>();
    test_is_trivially_default_constructible<TrapSelfAssign>();
    test_is_trivially_default_constructible<TrapDeref>();
    test_is_trivially_default_constructible<TrapArraySubscript>();

    test_is_not_trivially_default_constructible<void()>();
    test_is_not_trivially_default_constructible<void()&>();
    test_is_not_trivially_default_constructible<void() &&>();
    test_is_not_trivially_default_constructible<void() const>();
    test_is_not_trivially_default_constructible<void() const&>();
    test_is_not_trivially_default_constructible<void() const&&>();
    test_is_not_trivially_default_constructible<void() volatile>();
    test_is_not_trivially_default_constructible<void() volatile&>();
    test_is_not_trivially_default_constructible<void() volatile&&>();
    test_is_not_trivially_default_constructible<void() const volatile>();
    test_is_not_trivially_default_constructible<void() const volatile&>();
    test_is_not_trivially_default_constructible<void() const volatile&&>();
    test_is_not_trivially_default_constructible<void() noexcept>();
    test_is_not_trivially_default_constructible<void()& noexcept>();
    test_is_not_trivially_default_constructible<void()&& noexcept>();
    test_is_not_trivially_default_constructible<void() const noexcept>();
    test_is_not_trivially_default_constructible<void() const& noexcept>();
    test_is_not_trivially_default_constructible<void() const&& noexcept>();
    test_is_not_trivially_default_constructible<void() volatile noexcept>();
    test_is_not_trivially_default_constructible<void() volatile& noexcept>();
    test_is_not_trivially_default_constructible<void() volatile&& noexcept>();
    test_is_not_trivially_default_constructible<void() const volatile noexcept>();
    test_is_not_trivially_default_constructible<void() const volatile& noexcept>();
    test_is_not_trivially_default_constructible<void() const volatile&& noexcept>();

    test_is_not_trivially_default_constructible<void(int)>();
    test_is_not_trivially_default_constructible<void(int)&>();
    test_is_not_trivially_default_constructible<void(int) &&>();
    test_is_not_trivially_default_constructible<void(int) const>();
    test_is_not_trivially_default_constructible<void(int) const&>();
    test_is_not_trivially_default_constructible<void(int) const&&>();
    test_is_not_trivially_default_constructible<void(int) volatile>();
    test_is_not_trivially_default_constructible<void(int) volatile&>();
    test_is_not_trivially_default_constructible<void(int) volatile&&>();
    test_is_not_trivially_default_constructible<void(int) const volatile>();
    test_is_not_trivially_default_constructible<void(int) const volatile&>();
    test_is_not_trivially_default_constructible<void(int) const volatile&&>();
    test_is_not_trivially_default_constructible<void(int) noexcept>();
    test_is_not_trivially_default_constructible<void(int)& noexcept>();
    test_is_not_trivially_default_constructible<void(int)&& noexcept>();
    test_is_not_trivially_default_constructible<void(int) const noexcept>();
    test_is_not_trivially_default_constructible<void(int) const& noexcept>();
    test_is_not_trivially_default_constructible<void(int) const&& noexcept>();
    test_is_not_trivially_default_constructible<void(int) volatile noexcept>();
    test_is_not_trivially_default_constructible<void(int) volatile& noexcept>();
    test_is_not_trivially_default_constructible<void(int) volatile&& noexcept>();
    test_is_not_trivially_default_constructible<void(int) const volatile noexcept>();
    test_is_not_trivially_default_constructible<void(int) const volatile& noexcept>();
    test_is_not_trivially_default_constructible<void(int) const volatile&& noexcept>();

    test_is_not_trivially_default_constructible<void(...)>();
    test_is_not_trivially_default_constructible<void(...)&>();
    test_is_not_trivially_default_constructible<void(...) &&>();
    test_is_not_trivially_default_constructible<void(...) const>();
    test_is_not_trivially_default_constructible<void(...) const&>();
    test_is_not_trivially_default_constructible<void(...) const&&>();
    test_is_not_trivially_default_constructible<void(...) volatile>();
    test_is_not_trivially_default_constructible<void(...) volatile&>();
    test_is_not_trivially_default_constructible<void(...) volatile&&>();
    test_is_not_trivially_default_constructible<void(...) const volatile>();
    test_is_not_trivially_default_constructible<void(...) const volatile&>();
    test_is_not_trivially_default_constructible<void(...) const volatile&&>();
    test_is_not_trivially_default_constructible<void(...) noexcept>();
    test_is_not_trivially_default_constructible<void(...)& noexcept>();
    test_is_not_trivially_default_constructible<void(...)&& noexcept>();
    test_is_not_trivially_default_constructible<void(...) const noexcept>();
    test_is_not_trivially_default_constructible<void(...) const& noexcept>();
    test_is_not_trivially_default_constructible<void(...) const&& noexcept>();
    test_is_not_trivially_default_constructible<void(...) volatile noexcept>();
    test_is_not_trivially_default_constructible<void(...) volatile& noexcept>();
    test_is_not_trivially_default_constructible<void(...) volatile&& noexcept>();
    test_is_not_trivially_default_constructible<void(...) const volatile noexcept>();
    test_is_not_trivially_default_constructible<void(...) const volatile& noexcept>();
    test_is_not_trivially_default_constructible<void(...) const volatile&& noexcept>();

    test_is_not_trivially_default_constructible<void(int, ...)>();
    test_is_not_trivially_default_constructible<void(int, ...)&>();
    test_is_not_trivially_default_constructible<void(int, ...) &&>();
    test_is_not_trivially_default_constructible<void(int, ...) const>();
    test_is_not_trivially_default_constructible<void(int, ...) const&>();
    test_is_not_trivially_default_constructible<void(int, ...) const&&>();
    test_is_not_trivially_default_constructible<void(int, ...) volatile>();
    test_is_not_trivially_default_constructible<void(int, ...) volatile&>();
    test_is_not_trivially_default_constructible<void(int, ...) volatile&&>();
    test_is_not_trivially_default_constructible<void(int, ...) const volatile>();
    test_is_not_trivially_default_constructible<void(int, ...) const volatile&>();
    test_is_not_trivially_default_constructible<void(int, ...) const volatile&&>();
    test_is_not_trivially_default_constructible<void(int, ...) noexcept>();
    test_is_not_trivially_default_constructible<void(int, ...)& noexcept>();
    test_is_not_trivially_default_constructible<void(int, ...)&& noexcept>();
    test_is_not_trivially_default_constructible<void(int, ...) const noexcept>();
    test_is_not_trivially_default_constructible<void(int, ...) const& noexcept>();
    test_is_not_trivially_default_constructible<void(int, ...) const&& noexcept>();
    test_is_not_trivially_default_constructible<void(int, ...) volatile noexcept>();
    test_is_not_trivially_default_constructible<void(int, ...) volatile& noexcept>();
    test_is_not_trivially_default_constructible<void(int, ...) volatile&& noexcept>();
    test_is_not_trivially_default_constructible<void(int, ...) const volatile noexcept>();
    test_is_not_trivially_default_constructible<void(int, ...) const volatile& noexcept>();
    test_is_not_trivially_default_constructible<void(int, ...) const volatile&& noexcept>();

    test_is_not_trivially_default_constructible<int()>();
    test_is_not_trivially_default_constructible<int()&>();
    test_is_not_trivially_default_constructible<int() &&>();
    test_is_not_trivially_default_constructible<int() const>();
    test_is_not_trivially_default_constructible<int() const&>();
    test_is_not_trivially_default_constructible<int() const&&>();
    test_is_not_trivially_default_constructible<int() volatile>();
    test_is_not_trivially_default_constructible<int() volatile&>();
    test_is_not_trivially_default_constructible<int() volatile&&>();
    test_is_not_trivially_default_constructible<int() const volatile>();
    test_is_not_trivially_default_constructible<int() const volatile&>();
    test_is_not_trivially_default_constructible<int() const volatile&&>();
    test_is_not_trivially_default_constructible<int() noexcept>();
    test_is_not_trivially_default_constructible<int()& noexcept>();
    test_is_not_trivially_default_constructible<int()&& noexcept>();
    test_is_not_trivially_default_constructible<int() const noexcept>();
    test_is_not_trivially_default_constructible<int() const& noexcept>();
    test_is_not_trivially_default_constructible<int() const&& noexcept>();
    test_is_not_trivially_default_constructible<int() volatile noexcept>();
    test_is_not_trivially_default_constructible<int() volatile& noexcept>();
    test_is_not_trivially_default_constructible<int() volatile&& noexcept>();
    test_is_not_trivially_default_constructible<int() const volatile noexcept>();
    test_is_not_trivially_default_constructible<int() const volatile& noexcept>();
    test_is_not_trivially_default_constructible<int() const volatile&& noexcept>();

    test_is_not_trivially_default_constructible<int(int)>();
    test_is_not_trivially_default_constructible<int(int)&>();
    test_is_not_trivially_default_constructible<int(int) &&>();
    test_is_not_trivially_default_constructible<int(int) const>();
    test_is_not_trivially_default_constructible<int(int) const&>();
    test_is_not_trivially_default_constructible<int(int) const&&>();
    test_is_not_trivially_default_constructible<int(int) volatile>();
    test_is_not_trivially_default_constructible<int(int) volatile&>();
    test_is_not_trivially_default_constructible<int(int) volatile&&>();
    test_is_not_trivially_default_constructible<int(int) const volatile>();
    test_is_not_trivially_default_constructible<int(int) const volatile&>();
    test_is_not_trivially_default_constructible<int(int) const volatile&&>();
    test_is_not_trivially_default_constructible<int(int) noexcept>();
    test_is_not_trivially_default_constructible<int(int)& noexcept>();
    test_is_not_trivially_default_constructible<int(int)&& noexcept>();
    test_is_not_trivially_default_constructible<int(int) const noexcept>();
    test_is_not_trivially_default_constructible<int(int) const& noexcept>();
    test_is_not_trivially_default_constructible<int(int) const&& noexcept>();
    test_is_not_trivially_default_constructible<int(int) volatile noexcept>();
    test_is_not_trivially_default_constructible<int(int) volatile& noexcept>();
    test_is_not_trivially_default_constructible<int(int) volatile&& noexcept>();
    test_is_not_trivially_default_constructible<int(int) const volatile noexcept>();
    test_is_not_trivially_default_constructible<int(int) const volatile& noexcept>();
    test_is_not_trivially_default_constructible<int(int) const volatile&& noexcept>();

    test_is_not_trivially_default_constructible<int(...)>();
    test_is_not_trivially_default_constructible<int(...)&>();
    test_is_not_trivially_default_constructible<int(...) &&>();
    test_is_not_trivially_default_constructible<int(...) const>();
    test_is_not_trivially_default_constructible<int(...) const&>();
    test_is_not_trivially_default_constructible<int(...) const&&>();
    test_is_not_trivially_default_constructible<int(...) volatile>();
    test_is_not_trivially_default_constructible<int(...) volatile&>();
    test_is_not_trivially_default_constructible<int(...) volatile&&>();
    test_is_not_trivially_default_constructible<int(...) const volatile>();
    test_is_not_trivially_default_constructible<int(...) const volatile&>();
    test_is_not_trivially_default_constructible<int(...) const volatile&&>();
    test_is_not_trivially_default_constructible<int(...) noexcept>();
    test_is_not_trivially_default_constructible<int(...)& noexcept>();
    test_is_not_trivially_default_constructible<int(...)&& noexcept>();
    test_is_not_trivially_default_constructible<int(...) const noexcept>();
    test_is_not_trivially_default_constructible<int(...) const& noexcept>();
    test_is_not_trivially_default_constructible<int(...) const&& noexcept>();
    test_is_not_trivially_default_constructible<int(...) volatile noexcept>();
    test_is_not_trivially_default_constructible<int(...) volatile& noexcept>();
    test_is_not_trivially_default_constructible<int(...) volatile&& noexcept>();
    test_is_not_trivially_default_constructible<int(...) const volatile noexcept>();
    test_is_not_trivially_default_constructible<int(...) const volatile& noexcept>();
    test_is_not_trivially_default_constructible<int(...) const volatile&& noexcept>();

    test_is_not_trivially_default_constructible<int(int, ...)>();
    test_is_not_trivially_default_constructible<int(int, ...)&>();
    test_is_not_trivially_default_constructible<int(int, ...) &&>();
    test_is_not_trivially_default_constructible<int(int, ...) const>();
    test_is_not_trivially_default_constructible<int(int, ...) const&>();
    test_is_not_trivially_default_constructible<int(int, ...) const&&>();
    test_is_not_trivially_default_constructible<int(int, ...) volatile>();
    test_is_not_trivially_default_constructible<int(int, ...) volatile&>();
    test_is_not_trivially_default_constructible<int(int, ...) volatile&&>();
    test_is_not_trivially_default_constructible<int(int, ...) const volatile>();
    test_is_not_trivially_default_constructible<int(int, ...) const volatile&>();
    test_is_not_trivially_default_constructible<int(int, ...) const volatile&&>();
    test_is_not_trivially_default_constructible<int(int, ...) noexcept>();
    test_is_not_trivially_default_constructible<int(int, ...)& noexcept>();
    test_is_not_trivially_default_constructible<int(int, ...)&& noexcept>();
    test_is_not_trivially_default_constructible<int(int, ...) const noexcept>();
    test_is_not_trivially_default_constructible<int(int, ...) const& noexcept>();
    test_is_not_trivially_default_constructible<int(int, ...) const&& noexcept>();
    test_is_not_trivially_default_constructible<int(int, ...) volatile noexcept>();
    test_is_not_trivially_default_constructible<int(int, ...) volatile& noexcept>();
    test_is_not_trivially_default_constructible<int(int, ...) volatile&& noexcept>();
    test_is_not_trivially_default_constructible<int(int, ...) const volatile noexcept>();
    test_is_not_trivially_default_constructible<int(int, ...) const volatile& noexcept>();
    test_is_not_trivially_default_constructible<int(int, ...) const volatile&& noexcept>();

    test_is_trivially_default_constructible<void (*)()>();
    test_is_trivially_default_constructible<void (*)() noexcept>();

    test_is_trivially_default_constructible<void (*)(int)>();
    test_is_trivially_default_constructible<void (*)(int) noexcept>();

    test_is_trivially_default_constructible<void (*)(...)>();
    test_is_trivially_default_constructible<void (*)(...) noexcept>();

    test_is_trivially_default_constructible<void (*)(int, ...)>();
    test_is_trivially_default_constructible<void (*)(int, ...) noexcept>();

    test_is_trivially_default_constructible<int (*)()>();
    test_is_trivially_default_constructible<int (*)() noexcept>();

    test_is_trivially_default_constructible<int (*)(int)>();
    test_is_trivially_default_constructible<int (*)(int) noexcept>();

    test_is_trivially_default_constructible<int (*)(...)>();
    test_is_trivially_default_constructible<int (*)(...) noexcept>();

    test_is_trivially_default_constructible<int (*)(int, ...)>();
    test_is_trivially_default_constructible<int (*)(int, ...) noexcept>();

    test_is_not_trivially_default_constructible<void (&)()>();
    test_is_not_trivially_default_constructible<void (&)() noexcept>();

    test_is_not_trivially_default_constructible<void (&)(int)>();
    test_is_not_trivially_default_constructible<void (&)(int) noexcept>();

    test_is_not_trivially_default_constructible<void (&)(...)>();
    test_is_not_trivially_default_constructible<void (&)(...) noexcept>();

    test_is_not_trivially_default_constructible<void (&)(int, ...)>();
    test_is_not_trivially_default_constructible<void (&)(int, ...) noexcept>();

    test_is_not_trivially_default_constructible<int (&)()>();
    test_is_not_trivially_default_constructible<int (&)() noexcept>();

    test_is_not_trivially_default_constructible<int (&)(int)>();
    test_is_not_trivially_default_constructible<int (&)(int) noexcept>();

    test_is_not_trivially_default_constructible<int (&)(...)>();
    test_is_not_trivially_default_constructible<int (&)(...) noexcept>();

    test_is_not_trivially_default_constructible<int (&)(int, ...)>();
    test_is_not_trivially_default_constructible<int (&)(int, ...) noexcept>();

    test_is_not_trivially_default_constructible<void(&&)()>();
    test_is_not_trivially_default_constructible<void(&&)() noexcept>();

    test_is_not_trivially_default_constructible<void(&&)(int)>();
    test_is_not_trivially_default_constructible<void(&&)(int) noexcept>();

    test_is_not_trivially_default_constructible<void(&&)(...)>();
    test_is_not_trivially_default_constructible<void(&&)(...) noexcept>();

    test_is_not_trivially_default_constructible<void(&&)(int, ...)>();
    test_is_not_trivially_default_constructible<void(&&)(int, ...) noexcept>();

    test_is_not_trivially_default_constructible<int(&&)()>();
    test_is_not_trivially_default_constructible<int(&&)() noexcept>();

    test_is_not_trivially_default_constructible<int(&&)(int)>();
    test_is_not_trivially_default_constructible<int(&&)(int) noexcept>();

    test_is_not_trivially_default_constructible<int(&&)(...)>();
    test_is_not_trivially_default_constructible<int(&&)(...) noexcept>();

    test_is_not_trivially_default_constructible<int(&&)(int, ...)>();
    test_is_not_trivially_default_constructible<int(&&)(int, ...) noexcept>();

    test_is_trivially_default_constructible<void (Class::*)()>();
    test_is_trivially_default_constructible<void (Class::*)()&>();
    test_is_trivially_default_constructible<void (Class::*)() &&>();
    test_is_trivially_default_constructible<void (Class::*)() const>();
    test_is_trivially_default_constructible<void (Class::*)() const&>();
    test_is_trivially_default_constructible<void (Class::*)() const&&>();
    test_is_trivially_default_constructible<void (Class::*)() noexcept>();
    test_is_trivially_default_constructible<void (Class::*)()& noexcept>();
    test_is_trivially_default_constructible<void (Class::*)()&& noexcept>();
    test_is_trivially_default_constructible<void (Class::*)() const noexcept>();
    test_is_trivially_default_constructible<void (Class::*)() const& noexcept>();
    test_is_trivially_default_constructible<void (Class::*)() const&& noexcept>();

    test_is_trivially_default_constructible<void (Class::*)(int)>();
    test_is_trivially_default_constructible<void (Class::*)(int)&>();
    test_is_trivially_default_constructible<void (Class::*)(int) &&>();
    test_is_trivially_default_constructible<void (Class::*)(int) const>();
    test_is_trivially_default_constructible<void (Class::*)(int) const&>();
    test_is_trivially_default_constructible<void (Class::*)(int) const&&>();
    test_is_trivially_default_constructible<void (Class::*)(int) noexcept>();
    test_is_trivially_default_constructible<void (Class::*)(int)& noexcept>();
    test_is_trivially_default_constructible<void (Class::*)(int)&& noexcept>();
    test_is_trivially_default_constructible<void (Class::*)(int) const noexcept>();
    test_is_trivially_default_constructible<void (Class::*)(int) const& noexcept>();
    test_is_trivially_default_constructible<void (Class::*)(int) const&& noexcept>();

    test_is_trivially_default_constructible<void (Class::*)(...)>();
    test_is_trivially_default_constructible<void (Class::*)(...)&>();
    test_is_trivially_default_constructible<void (Class::*)(...) &&>();
    test_is_trivially_default_constructible<void (Class::*)(...) const>();
    test_is_trivially_default_constructible<void (Class::*)(...) const&>();
    test_is_trivially_default_constructible<void (Class::*)(...) const&&>();
    test_is_trivially_default_constructible<void (Class::*)(...) noexcept>();
    test_is_trivially_default_constructible<void (Class::*)(...)& noexcept>();
    test_is_trivially_default_constructible<void (Class::*)(...)&& noexcept>();
    test_is_trivially_default_constructible<void (Class::*)(...) const noexcept>();
    test_is_trivially_default_constructible<void (Class::*)(...) const& noexcept>();
    test_is_trivially_default_constructible<void (Class::*)(...) const&& noexcept>();

    test_is_trivially_default_constructible<void (Class::*)(int, ...)>();
    test_is_trivially_default_constructible<void (Class::*)(int, ...)&>();
    test_is_trivially_default_constructible<void (Class::*)(int, ...) &&>();
    test_is_trivially_default_constructible<void (Class::*)(int, ...) const>();
    test_is_trivially_default_constructible<void (Class::*)(int, ...) const&>();
    test_is_trivially_default_constructible<void (Class::*)(int, ...) const&&>();
    test_is_trivially_default_constructible<void (Class::*)(int, ...) noexcept>();
    test_is_trivially_default_constructible<void (Class::*)(int, ...)& noexcept>();
    test_is_trivially_default_constructible<void (Class::*)(int, ...)&& noexcept>();
    test_is_trivially_default_constructible<void (Class::*)(int, ...) const noexcept>();
    test_is_trivially_default_constructible<void (Class::*)(int, ...) const& noexcept>();
    test_is_trivially_default_constructible<void (Class::*)(int, ...) const&& noexcept>();

    test_is_trivially_default_constructible<int (Class::*)()>();
    test_is_trivially_default_constructible<int (Class::*)()&>();
    test_is_trivially_default_constructible<int (Class::*)() &&>();
    test_is_trivially_default_constructible<int (Class::*)() const>();
    test_is_trivially_default_constructible<int (Class::*)() const&>();
    test_is_trivially_default_constructible<int (Class::*)() const&&>();
    test_is_trivially_default_constructible<int (Class::*)() noexcept>();
    test_is_trivially_default_constructible<int (Class::*)()& noexcept>();
    test_is_trivially_default_constructible<int (Class::*)()&& noexcept>();
    test_is_trivially_default_constructible<int (Class::*)() const noexcept>();
    test_is_trivially_default_constructible<int (Class::*)() const& noexcept>();
    test_is_trivially_default_constructible<int (Class::*)() const&& noexcept>();

    test_is_trivially_default_constructible<int (Class::*)(int)>();
    test_is_trivially_default_constructible<int (Class::*)(int)&>();
    test_is_trivially_default_constructible<int (Class::*)(int) &&>();
    test_is_trivially_default_constructible<int (Class::*)(int) const>();
    test_is_trivially_default_constructible<int (Class::*)(int) const&>();
    test_is_trivially_default_constructible<int (Class::*)(int) const&&>();
    test_is_trivially_default_constructible<int (Class::*)(int) noexcept>();
    test_is_trivially_default_constructible<int (Class::*)(int)& noexcept>();
    test_is_trivially_default_constructible<int (Class::*)(int)&& noexcept>();
    test_is_trivially_default_constructible<int (Class::*)(int) const noexcept>();
    test_is_trivially_default_constructible<int (Class::*)(int) const& noexcept>();
    test_is_trivially_default_constructible<int (Class::*)(int) const&& noexcept>();

    test_is_trivially_default_constructible<int (Class::*)(...)>();
    test_is_trivially_default_constructible<int (Class::*)(...)&>();
    test_is_trivially_default_constructible<int (Class::*)(...) &&>();
    test_is_trivially_default_constructible<int (Class::*)(...) const>();
    test_is_trivially_default_constructible<int (Class::*)(...) const&>();
    test_is_trivially_default_constructible<int (Class::*)(...) const&&>();
    test_is_trivially_default_constructible<int (Class::*)(...) noexcept>();
    test_is_trivially_default_constructible<int (Class::*)(...)& noexcept>();
    test_is_trivially_default_constructible<int (Class::*)(...)&& noexcept>();
    test_is_trivially_default_constructible<int (Class::*)(...) const noexcept>();
    test_is_trivially_default_constructible<int (Class::*)(...) const& noexcept>();
    test_is_trivially_default_constructible<int (Class::*)(...) const&& noexcept>();

    test_is_trivially_default_constructible<int (Class::*)(int, ...)>();
    test_is_trivially_default_constructible<int (Class::*)(int, ...)&>();
    test_is_trivially_default_constructible<int (Class::*)(int, ...) &&>();
    test_is_trivially_default_constructible<int (Class::*)(int, ...) const>();
    test_is_trivially_default_constructible<int (Class::*)(int, ...) const&>();
    test_is_trivially_default_constructible<int (Class::*)(int, ...) const&&>();
    test_is_trivially_default_constructible<int (Class::*)(int, ...) noexcept>();
    test_is_trivially_default_constructible<int (Class::*)(int, ...)& noexcept>();
    test_is_trivially_default_constructible<int (Class::*)(int, ...)&& noexcept>();
    test_is_trivially_default_constructible<int (Class::*)(int, ...) const noexcept>();
    test_is_trivially_default_constructible<int (Class::*)(int, ...) const& noexcept>();
    test_is_trivially_default_constructible<int (Class::*)(int, ...) const&& noexcept>();
}
