#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_copy_assignable.hpp>
#include <phi/type_traits/is_nothrow_copy_assignable.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_nothrow_copy_assignable_impl()
{
    STATIC_REQUIRE(phi::is_nothrow_copy_assignable<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_copy_assignable<T>::value);
    STATIC_REQUIRE(phi::is_copy_assignable<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_copy_assignable_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_copy_assignable_v<T>);
    STATIC_REQUIRE(phi::is_copy_assignable_v<T>);
#endif

    // Standard compatbililty
    STATIC_REQUIRE(std::is_nothrow_copy_assignable<T>::value);
}

template <typename T>
void test_is_not_nothrow_copy_assignable_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_copy_assignable<T>::value);
    STATIC_REQUIRE(phi::is_not_nothrow_copy_assignable<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_copy_assignable_v<T>);
    STATIC_REQUIRE(phi::is_not_nothrow_copy_assignable_v<T>);
#endif

    // Standard compatbililty
    STATIC_REQUIRE_FALSE(std::is_nothrow_copy_assignable<T>::value);
}

template <typename T>
void test_is_nothrow_copy_assignable()
{
    test_is_nothrow_copy_assignable_impl<T>();
    test_is_not_nothrow_copy_assignable_impl<const T>();
    test_is_not_nothrow_copy_assignable_impl<volatile T>();
    test_is_not_nothrow_copy_assignable_impl<const volatile T>();
}

template <typename T>
void test_is_nothrow_copy_assignable_v()
{
    test_is_nothrow_copy_assignable_impl<T>();
    test_is_not_nothrow_copy_assignable_impl<const T>();
    test_is_nothrow_copy_assignable_impl<volatile T>();
    test_is_not_nothrow_copy_assignable_impl<const volatile T>();
}

template <typename T>
void test_is_nothrow_copy_assignable_cv()
{
    test_is_nothrow_copy_assignable_impl<T>();
    test_is_nothrow_copy_assignable_impl<const T>();
    test_is_nothrow_copy_assignable_impl<volatile T>();
    test_is_nothrow_copy_assignable_impl<const volatile T>();
}

template <typename T>
void test_is_not_nothrow_copy_assignable_cv()
{
    test_is_not_nothrow_copy_assignable_impl<T>();
    test_is_not_nothrow_copy_assignable_impl<const T>();
    test_is_not_nothrow_copy_assignable_impl<volatile T>();
    test_is_not_nothrow_copy_assignable_impl<const volatile T>();
}

struct A
{
    A& operator=(const A&);
};

struct B
{
    B& operator=(const B&) noexcept;
};

struct C
{
    C& operator=(const C&) = delete;
};

struct D
{
    D& operator=(const D&) = default;
};

TEST_CASE("is_nothrow_copy_assignable")
{
    test_is_not_nothrow_copy_assignable_cv<A>();
    test_is_nothrow_copy_assignable<B>();
    test_is_not_nothrow_copy_assignable_cv<C>();
    test_is_nothrow_copy_assignable<D>();

    test_is_not_nothrow_copy_assignable_cv<void>();
    test_is_nothrow_copy_assignable_v<phi::nullptr_t>();
    test_is_nothrow_copy_assignable_v<bool>();
    test_is_nothrow_copy_assignable_v<char>();
    test_is_nothrow_copy_assignable_v<signed char>();
    test_is_nothrow_copy_assignable_v<unsigned char>();
    test_is_nothrow_copy_assignable_v<short>();
    test_is_nothrow_copy_assignable_v<unsigned short>();
    test_is_nothrow_copy_assignable_v<int>();
    test_is_nothrow_copy_assignable_v<unsigned int>();
    test_is_nothrow_copy_assignable_v<long>();
    test_is_nothrow_copy_assignable_v<unsigned long>();
    test_is_nothrow_copy_assignable_v<long long>();
    test_is_nothrow_copy_assignable_v<unsigned long long>();
    test_is_nothrow_copy_assignable_v<float>();
    test_is_nothrow_copy_assignable_v<double>();
    test_is_nothrow_copy_assignable_v<long double>();
    test_is_nothrow_copy_assignable_v<char8_t>();
    test_is_nothrow_copy_assignable_v<char16_t>();
    test_is_nothrow_copy_assignable_v<char32_t>();
    test_is_nothrow_copy_assignable_v<wchar_t>();

    test_is_nothrow_copy_assignable<phi::boolean>();
    test_is_nothrow_copy_assignable<phi::integer<signed char>>();
    test_is_nothrow_copy_assignable<phi::integer<unsigned char>>();
    test_is_nothrow_copy_assignable<phi::integer<short>>();
    test_is_nothrow_copy_assignable<phi::integer<unsigned short>>();
    test_is_nothrow_copy_assignable<phi::integer<int>>();
    test_is_nothrow_copy_assignable<phi::integer<unsigned int>>();
    test_is_nothrow_copy_assignable<phi::integer<long>>();
    test_is_nothrow_copy_assignable<phi::integer<unsigned long>>();
    test_is_nothrow_copy_assignable<phi::integer<long long>>();
    test_is_nothrow_copy_assignable<phi::integer<unsigned long long>>();
    test_is_nothrow_copy_assignable<phi::floating_point<float>>();
    test_is_nothrow_copy_assignable<phi::floating_point<double>>();
    test_is_nothrow_copy_assignable<phi::floating_point<long double>>();

    test_is_not_nothrow_copy_assignable_cv<std::vector<int>>();
    test_is_not_nothrow_copy_assignable_cv<phi::scope_ptr<int>>();

    test_is_nothrow_copy_assignable_cv<int&>();
    test_is_not_nothrow_copy_assignable_cv<const int&>();
    test_is_nothrow_copy_assignable_cv<volatile int&>();
    test_is_not_nothrow_copy_assignable_cv<const volatile int&>();
    test_is_nothrow_copy_assignable_cv<int&&>();
    test_is_not_nothrow_copy_assignable_cv<const int&&>();
    test_is_nothrow_copy_assignable_cv<volatile int&&>();
    test_is_not_nothrow_copy_assignable_cv<const volatile int&&>();
    test_is_nothrow_copy_assignable_v<int*>();
    test_is_nothrow_copy_assignable_v<const int*>();
    test_is_nothrow_copy_assignable_v<volatile int*>();
    test_is_nothrow_copy_assignable_v<const volatile int*>();
    test_is_nothrow_copy_assignable_v<int**>();
    test_is_nothrow_copy_assignable_v<const int**>();
    test_is_nothrow_copy_assignable_v<volatile int**>();
    test_is_nothrow_copy_assignable_v<const volatile int**>();
    test_is_nothrow_copy_assignable_cv<int*&>();
    test_is_nothrow_copy_assignable_cv<const int*&>();
    test_is_nothrow_copy_assignable_cv<volatile int*&>();
    test_is_nothrow_copy_assignable_cv<const volatile int*&>();
    test_is_nothrow_copy_assignable_cv<int*&&>();
    test_is_nothrow_copy_assignable_cv<const int*&&>();
    test_is_nothrow_copy_assignable_cv<volatile int*&&>();
    test_is_nothrow_copy_assignable_cv<const volatile int*&&>();
    test_is_nothrow_copy_assignable_v<void*>();
    test_is_not_nothrow_copy_assignable_cv<char[3]>();
    test_is_not_nothrow_copy_assignable_cv<char[]>();
    test_is_not_nothrow_copy_assignable_cv<char* [3]>();
    test_is_not_nothrow_copy_assignable_cv<char*[]>();
    test_is_nothrow_copy_assignable_v<int(*)[3]>();
    test_is_nothrow_copy_assignable_v<int(*)[]>();
    test_is_not_nothrow_copy_assignable_cv<int(&)[3]>();
    test_is_not_nothrow_copy_assignable_cv<int(&)[]>();
    test_is_not_nothrow_copy_assignable_cv<int(&&)[3]>();
    test_is_not_nothrow_copy_assignable_cv<int(&&)[]>();
    test_is_not_nothrow_copy_assignable_cv<char[3][2]>();
    test_is_not_nothrow_copy_assignable_cv<char[][2]>();
    test_is_not_nothrow_copy_assignable_cv<char* [3][2]>();
    test_is_not_nothrow_copy_assignable_cv<char*[][2]>();
    test_is_nothrow_copy_assignable_v<int(*)[3][2]>();
    test_is_nothrow_copy_assignable_v<int(*)[][2]>();
    test_is_not_nothrow_copy_assignable_cv<int(&)[3][2]>();
    test_is_not_nothrow_copy_assignable_cv<int(&)[][2]>();
    test_is_not_nothrow_copy_assignable_cv<int(&&)[3][2]>();
    test_is_not_nothrow_copy_assignable_cv<int(&&)[][2]>();
    test_is_nothrow_copy_assignable<Class>();
    test_is_not_nothrow_copy_assignable_cv<Class[]>();
    test_is_not_nothrow_copy_assignable_cv<Class[2]>();
    test_is_nothrow_copy_assignable<Template<void>>();
    test_is_nothrow_copy_assignable<Template<int>>();
    test_is_nothrow_copy_assignable<Template<Class>>();
    test_is_nothrow_copy_assignable<Template<incomplete_type>>();
    test_is_nothrow_copy_assignable<VariadicTemplate<>>();
    test_is_nothrow_copy_assignable<VariadicTemplate<void>>();
    test_is_nothrow_copy_assignable<VariadicTemplate<int>>();
    test_is_nothrow_copy_assignable<VariadicTemplate<Class>>();
    test_is_nothrow_copy_assignable<VariadicTemplate<incomplete_type>>();
    test_is_nothrow_copy_assignable<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_nothrow_copy_assignable<PublicDerviedFromTemplate<Base>>();
    test_is_nothrow_copy_assignable<PublicDerviedFromTemplate<Derived>>();
    test_is_nothrow_copy_assignable<PublicDerviedFromTemplate<Class>>();
    test_is_nothrow_copy_assignable<PrivateDerviedFromTemplate<Base>>();
    test_is_nothrow_copy_assignable<PrivateDerviedFromTemplate<Derived>>();
    test_is_nothrow_copy_assignable<PrivateDerviedFromTemplate<Class>>();
    test_is_nothrow_copy_assignable<ProtectedDerviedFromTemplate<Base>>();
    test_is_nothrow_copy_assignable<ProtectedDerviedFromTemplate<Derived>>();
    test_is_nothrow_copy_assignable<ProtectedDerviedFromTemplate<Class>>();
    test_is_nothrow_copy_assignable<Union>();
    test_is_nothrow_copy_assignable<NonEmptyUnion>();
    test_is_nothrow_copy_assignable<Empty>();
    test_is_nothrow_copy_assignable<NotEmpty>();
    test_is_nothrow_copy_assignable<bit_zero>();
    test_is_nothrow_copy_assignable<bit_one>();
    test_is_nothrow_copy_assignable<Base>();
    test_is_nothrow_copy_assignable<Derived>();
    test_is_nothrow_copy_assignable<Abstract>();
    test_is_nothrow_copy_assignable<PublicAbstract>();
    test_is_nothrow_copy_assignable<PrivateAbstract>();
    test_is_nothrow_copy_assignable<ProtectedAbstract>();
    test_is_nothrow_copy_assignable<AbstractTemplate<int>>();
    test_is_nothrow_copy_assignable<AbstractTemplate<double>>();
    test_is_nothrow_copy_assignable<AbstractTemplate<Class>>();
    test_is_nothrow_copy_assignable<AbstractTemplate<incomplete_type>>();
    test_is_nothrow_copy_assignable<Final>();
    test_is_nothrow_copy_assignable<PublicDestructor>();
    test_is_nothrow_copy_assignable<ProtectedDestructor>();
    test_is_nothrow_copy_assignable<PrivateDestructor>();
    test_is_nothrow_copy_assignable<VirtualPublicDestructor>();
    test_is_nothrow_copy_assignable<VirtualProtectedDestructor>();
    test_is_nothrow_copy_assignable<VirtualPrivateDestructor>();
    test_is_nothrow_copy_assignable<PurePublicDestructor>();
    test_is_nothrow_copy_assignable<PureProtectedDestructor>();
    test_is_nothrow_copy_assignable<PurePrivateDestructor>();
    test_is_nothrow_copy_assignable<DeletedPublicDestructor>();
    test_is_nothrow_copy_assignable<DeletedProtectedDestructor>();
    test_is_nothrow_copy_assignable<DeletedPrivateDestructor>();
    test_is_nothrow_copy_assignable<DeletedVirtualPublicDestructor>();
    test_is_nothrow_copy_assignable<DeletedVirtualProtectedDestructor>();
    test_is_nothrow_copy_assignable<DeletedVirtualPrivateDestructor>();
    test_is_nothrow_copy_assignable_v<Enum>();
    test_is_nothrow_copy_assignable_v<EnumSigned>();
    test_is_nothrow_copy_assignable_v<EnumUnsigned>();
    test_is_nothrow_copy_assignable_v<EnumClass>();
    test_is_nothrow_copy_assignable_v<EnumStruct>();
    test_is_not_nothrow_copy_assignable_cv<Function>();
    test_is_nothrow_copy_assignable_v<FunctionPtr>();
    test_is_nothrow_copy_assignable_v<MemberObjectPtr>();
    test_is_nothrow_copy_assignable_v<MemberFunctionPtr>();
    test_is_nothrow_copy_assignable_v<int Class::*>();
    test_is_nothrow_copy_assignable_v<float Class::*>();
    test_is_nothrow_copy_assignable_v<void * Class::*>();
    test_is_nothrow_copy_assignable_v<int * Class::*>();
    test_is_nothrow_copy_assignable_cv<int Class::*&>();
    test_is_nothrow_copy_assignable_cv<float Class::*&>();
    test_is_nothrow_copy_assignable_cv<void * Class::*&>();
    test_is_nothrow_copy_assignable_cv<int * Class::*&>();
    test_is_nothrow_copy_assignable_cv<int Class::*&&>();
    test_is_nothrow_copy_assignable_cv<float Class::*&&>();
    test_is_nothrow_copy_assignable_cv<void * Class::*&&>();
    test_is_nothrow_copy_assignable_cv<int * Class::*&&>();
    test_is_not_nothrow_copy_assignable_cv<int Class::*const>();
    test_is_not_nothrow_copy_assignable_cv<float Class::*const>();
    test_is_not_nothrow_copy_assignable_cv<void * Class::*const>();
    test_is_not_nothrow_copy_assignable_cv<int Class::*const&>();
    test_is_not_nothrow_copy_assignable_cv<float Class::*const&>();
    test_is_not_nothrow_copy_assignable_cv<void * Class::*const&>();
    test_is_not_nothrow_copy_assignable_cv<int Class::*const&&>();
    test_is_not_nothrow_copy_assignable_cv<float Class::*const&&>();
    test_is_not_nothrow_copy_assignable_cv<void * Class::*const&&>();
    test_is_nothrow_copy_assignable_v<int Class::*volatile>();
    test_is_nothrow_copy_assignable_v<float Class::*volatile>();
    test_is_nothrow_copy_assignable_v<void * Class::*volatile>();
    test_is_nothrow_copy_assignable_cv<int Class::*volatile&>();
    test_is_nothrow_copy_assignable_cv<float Class::*volatile&>();
    test_is_nothrow_copy_assignable_cv<void * Class::*volatile&>();
    test_is_nothrow_copy_assignable_cv<int Class::*volatile&&>();
    test_is_nothrow_copy_assignable_cv<float Class::*volatile&&>();
    test_is_nothrow_copy_assignable_cv<void * Class::*volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<int Class::*const volatile>();
    test_is_not_nothrow_copy_assignable_cv<float Class::*const volatile>();
    test_is_not_nothrow_copy_assignable_cv<void * Class::*const volatile>();
    test_is_not_nothrow_copy_assignable_cv<int Class::*const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<float Class::*const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<void * Class::*const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<int Class::*const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<float Class::*const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<void * Class::*const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<NonCopyable>();
    test_is_nothrow_copy_assignable<NonMoveable>();
    test_is_not_nothrow_copy_assignable_cv<NonConstructible>();
    test_is_nothrow_copy_assignable<Tracked>();
    test_is_nothrow_copy_assignable<TrapConstructible>();
    test_is_nothrow_copy_assignable<TrapImplicitConversion>();
    test_is_nothrow_copy_assignable<TrapComma>();
    test_is_nothrow_copy_assignable<TrapCall>();
    test_is_nothrow_copy_assignable<TrapSelfAssign>();
    test_is_nothrow_copy_assignable<TrapDeref>();
    test_is_nothrow_copy_assignable<TrapArraySubscript>();

    test_is_not_nothrow_copy_assignable_cv<void()>();
    test_is_not_nothrow_copy_assignable_cv<void()&>();
    test_is_not_nothrow_copy_assignable_cv<void() &&>();
    test_is_not_nothrow_copy_assignable_cv<void() const>();
    test_is_not_nothrow_copy_assignable_cv<void() const&>();
    test_is_not_nothrow_copy_assignable_cv<void() const&&>();
    test_is_not_nothrow_copy_assignable_cv<void() volatile>();
    test_is_not_nothrow_copy_assignable_cv<void() volatile&>();
    test_is_not_nothrow_copy_assignable_cv<void() volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<void() const volatile>();
    test_is_not_nothrow_copy_assignable_cv<void() const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<void() const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<void() noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void()& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void()&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() const noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() const& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() const&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() volatile& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() volatile&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() const volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() const volatile& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() const volatile&& noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void(int)>();
    test_is_not_nothrow_copy_assignable_cv<void(int)&>();
    test_is_not_nothrow_copy_assignable_cv<void(int) &&>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const&>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const&&>();
    test_is_not_nothrow_copy_assignable_cv<void(int) volatile>();
    test_is_not_nothrow_copy_assignable_cv<void(int) volatile&>();
    test_is_not_nothrow_copy_assignable_cv<void(int) volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const volatile>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<void(int) noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int)& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int)&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) volatile& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) volatile&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const volatile& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const volatile&& noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void(...)>();
    test_is_not_nothrow_copy_assignable_cv<void(...)&>();
    test_is_not_nothrow_copy_assignable_cv<void(...) &&>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const&>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const&&>();
    test_is_not_nothrow_copy_assignable_cv<void(...) volatile>();
    test_is_not_nothrow_copy_assignable_cv<void(...) volatile&>();
    test_is_not_nothrow_copy_assignable_cv<void(...) volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const volatile>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<void(...) noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...)& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...)&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) volatile& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) volatile&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const volatile& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const volatile&& noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void(int, ...)>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...)&>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) &&>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const&>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const&&>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) volatile>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) volatile&>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const volatile>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...)& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...)&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) volatile& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) volatile&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const volatile& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const volatile&& noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int()>();
    test_is_not_nothrow_copy_assignable_cv<int()&>();
    test_is_not_nothrow_copy_assignable_cv<int() &&>();
    test_is_not_nothrow_copy_assignable_cv<int() const>();
    test_is_not_nothrow_copy_assignable_cv<int() const&>();
    test_is_not_nothrow_copy_assignable_cv<int() const&&>();
    test_is_not_nothrow_copy_assignable_cv<int() volatile>();
    test_is_not_nothrow_copy_assignable_cv<int() volatile&>();
    test_is_not_nothrow_copy_assignable_cv<int() volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<int() const volatile>();
    test_is_not_nothrow_copy_assignable_cv<int() const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<int() const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<int() noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int()& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int()&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() const noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() const& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() const&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() volatile& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() volatile&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() const volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() const volatile& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() const volatile&& noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int(int)>();
    test_is_not_nothrow_copy_assignable_cv<int(int)&>();
    test_is_not_nothrow_copy_assignable_cv<int(int) &&>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const&>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const&&>();
    test_is_not_nothrow_copy_assignable_cv<int(int) volatile>();
    test_is_not_nothrow_copy_assignable_cv<int(int) volatile&>();
    test_is_not_nothrow_copy_assignable_cv<int(int) volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const volatile>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<int(int) noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int)& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int)&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) volatile& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) volatile&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const volatile& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const volatile&& noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int(...)>();
    test_is_not_nothrow_copy_assignable_cv<int(...)&>();
    test_is_not_nothrow_copy_assignable_cv<int(...) &&>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const&>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const&&>();
    test_is_not_nothrow_copy_assignable_cv<int(...) volatile>();
    test_is_not_nothrow_copy_assignable_cv<int(...) volatile&>();
    test_is_not_nothrow_copy_assignable_cv<int(...) volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const volatile>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<int(...) noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...)& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...)&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) volatile& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) volatile&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const volatile& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const volatile&& noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int(int, ...)>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...)&>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) &&>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const&>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const&&>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) volatile>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) volatile&>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const volatile>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...)& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...)&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) volatile& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) volatile&& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const volatile& noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const volatile&& noexcept>();

    test_is_nothrow_copy_assignable_v<void (*)()>();
    test_is_nothrow_copy_assignable_v<void (*)() noexcept>();

    test_is_nothrow_copy_assignable_v<void (*)(int)>();
    test_is_nothrow_copy_assignable_v<void (*)(int) noexcept>();

    test_is_nothrow_copy_assignable_v<void (*)(...)>();
    test_is_nothrow_copy_assignable_v<void (*)(...) noexcept>();

    test_is_nothrow_copy_assignable_v<void (*)(int, ...)>();
    test_is_nothrow_copy_assignable_v<void (*)(int, ...) noexcept>();

    test_is_nothrow_copy_assignable_v<int (*)()>();
    test_is_nothrow_copy_assignable_v<int (*)() noexcept>();

    test_is_nothrow_copy_assignable_v<int (*)(int)>();
    test_is_nothrow_copy_assignable_v<int (*)(int) noexcept>();

    test_is_nothrow_copy_assignable_v<int (*)(...)>();
    test_is_nothrow_copy_assignable_v<int (*)(...) noexcept>();

    test_is_nothrow_copy_assignable_v<int (*)(int, ...)>();
    test_is_nothrow_copy_assignable_v<int (*)(int, ...) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void (&)()>();
    test_is_not_nothrow_copy_assignable_cv<void (&)() noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void (&)(int)>();
    test_is_not_nothrow_copy_assignable_cv<void (&)(int) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void (&)(...)>();
    test_is_not_nothrow_copy_assignable_cv<void (&)(...) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void (&)(int, ...)>();
    test_is_not_nothrow_copy_assignable_cv<void (&)(int, ...) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int (&)()>();
    test_is_not_nothrow_copy_assignable_cv<int (&)() noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int (&)(int)>();
    test_is_not_nothrow_copy_assignable_cv<int (&)(int) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int (&)(...)>();
    test_is_not_nothrow_copy_assignable_cv<int (&)(...) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int (&)(int, ...)>();
    test_is_not_nothrow_copy_assignable_cv<int (&)(int, ...) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void(&&)()>();
    test_is_not_nothrow_copy_assignable_cv<void(&&)() noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void(&&)(int)>();
    test_is_not_nothrow_copy_assignable_cv<void(&&)(int) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void(&&)(...)>();
    test_is_not_nothrow_copy_assignable_cv<void(&&)(...) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void(&&)(int, ...)>();
    test_is_not_nothrow_copy_assignable_cv<void(&&)(int, ...) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int(&&)()>();
    test_is_not_nothrow_copy_assignable_cv<int(&&)() noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int(&&)(int)>();
    test_is_not_nothrow_copy_assignable_cv<int(&&)(int) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int(&&)(...)>();
    test_is_not_nothrow_copy_assignable_cv<int(&&)(...) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int(&&)(int, ...)>();
    test_is_not_nothrow_copy_assignable_cv<int(&&)(int, ...) noexcept>();

    test_is_nothrow_copy_assignable_v<void (Class::*)()>();
    test_is_nothrow_copy_assignable_v<void (Class::*)()&>();
    test_is_nothrow_copy_assignable_v<void (Class::*)() &&>();
    test_is_nothrow_copy_assignable_v<void (Class::*)() const>();
    test_is_nothrow_copy_assignable_v<void (Class::*)() const&>();
    test_is_nothrow_copy_assignable_v<void (Class::*)() const&&>();
    test_is_nothrow_copy_assignable_v<void (Class::*)() noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)()& noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)()&& noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)() const noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)() const& noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)() const&& noexcept>();

    test_is_nothrow_copy_assignable_v<void (Class::*)(int)>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int)&>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int) &&>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int) const>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int) const&>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int) const&&>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int) noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int)& noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int)&& noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int) const noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int) const& noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int) const&& noexcept>();

    test_is_nothrow_copy_assignable_v<void (Class::*)(...)>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(...)&>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(...) &&>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(...) const>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(...) const&>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(...) const&&>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(...) noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(...)& noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(...)&& noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(...) const noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(...) const& noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(...) const&& noexcept>();

    test_is_nothrow_copy_assignable_v<void (Class::*)(int, ...)>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int, ...)&>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int, ...) &&>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int, ...) const>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int, ...) const&>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int, ...) const&&>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int, ...) noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int, ...)& noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int, ...)&& noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int, ...) const noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int, ...) const& noexcept>();
    test_is_nothrow_copy_assignable_v<void (Class::*)(int, ...) const&& noexcept>();

    test_is_nothrow_copy_assignable_v<int (Class::*)()>();
    test_is_nothrow_copy_assignable_v<int (Class::*)()&>();
    test_is_nothrow_copy_assignable_v<int (Class::*)() &&>();
    test_is_nothrow_copy_assignable_v<int (Class::*)() const>();
    test_is_nothrow_copy_assignable_v<int (Class::*)() const&>();
    test_is_nothrow_copy_assignable_v<int (Class::*)() const&&>();
    test_is_nothrow_copy_assignable_v<int (Class::*)() noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)()& noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)()&& noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)() const noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)() const& noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)() const&& noexcept>();

    test_is_nothrow_copy_assignable_v<int (Class::*)(int)>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int)&>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int) &&>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int) const>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int) const&>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int) const&&>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int) noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int)& noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int)&& noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int) const noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int) const& noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int) const&& noexcept>();

    test_is_nothrow_copy_assignable_v<int (Class::*)(...)>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(...)&>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(...) &&>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(...) const>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(...) const&>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(...) const&&>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(...) noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(...)& noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(...)&& noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(...) const noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(...) const& noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(...) const&& noexcept>();

    test_is_nothrow_copy_assignable_v<int (Class::*)(int, ...)>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int, ...)&>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int, ...) &&>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int, ...) const>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int, ...) const&>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int, ...) const&&>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int, ...) noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int, ...)& noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int, ...)&& noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int, ...) const noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int, ...) const& noexcept>();
    test_is_nothrow_copy_assignable_v<int (Class::*)(int, ...) const&& noexcept>();
}
