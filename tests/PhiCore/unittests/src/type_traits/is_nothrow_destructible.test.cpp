#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_destructible.hpp>
#include <phi/type_traits/is_nothrow_destructible.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_nothrow_destructible_impl()
{
    STATIC_REQUIRE(phi::is_nothrow_destructible<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_destructible<T>::value);
    STATIC_REQUIRE(phi::is_destructible<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_destructible_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_destructible_v<T>);
    STATIC_REQUIRE(phi::is_destructible_v<T>);
#endif

    // Standard compatibililty
    STATIC_REQUIRE(std::is_nothrow_destructible<T>::value);
    STATIC_REQUIRE(std::is_destructible<T>::value);
}

template <typename T>
void test_is_not_nothrow_destructible_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_destructible<T>::value);
    STATIC_REQUIRE(phi::is_not_nothrow_destructible<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_destructible_v<T>);
    STATIC_REQUIRE(phi::is_not_nothrow_destructible_v<T>);
#endif

    // Standard compatibililty
    STATIC_REQUIRE_FALSE(std::is_nothrow_destructible<T>::value);
}

template <typename T>
void test_is_nothrow_destructible()
{
    test_is_nothrow_destructible_impl<T>();
    test_is_nothrow_destructible_impl<const T>();
    test_is_nothrow_destructible_impl<volatile T>();
    test_is_nothrow_destructible_impl<const volatile T>();
}

template <typename T>
void test_is_not_nothrow_destructible()
{
    test_is_not_nothrow_destructible_impl<T>();
    test_is_not_nothrow_destructible_impl<const T>();
    test_is_not_nothrow_destructible_impl<volatile T>();
    test_is_not_nothrow_destructible_impl<const volatile T>();
}

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wnon-virtual-dtor")
PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnon-virtual-dtor")

class A
{
    virtual void foo() = 0;
};

struct B
{
    ~B() noexcept(false);
};

struct C
{
    ~C() noexcept;
};

struct D
{
    ~D() = default;
};

struct E
{
    ~E() = delete;
};

PHI_GCC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()

TEST_CASE("is_nothrow_destructible")
{
    test_is_nothrow_destructible<A>();
    test_is_not_nothrow_destructible<B>();
    test_is_nothrow_destructible<C>();
    test_is_nothrow_destructible<D>();
    test_is_not_nothrow_destructible<E>();

    test_is_not_nothrow_destructible<void>();
    test_is_nothrow_destructible<phi::nullptr_t>();
    test_is_nothrow_destructible<bool>();
    test_is_nothrow_destructible<char>();
    test_is_nothrow_destructible<signed char>();
    test_is_nothrow_destructible<unsigned char>();
    test_is_nothrow_destructible<short>();
    test_is_nothrow_destructible<unsigned short>();
    test_is_nothrow_destructible<int>();
    test_is_nothrow_destructible<unsigned int>();
    test_is_nothrow_destructible<long>();
    test_is_nothrow_destructible<unsigned long>();
    test_is_nothrow_destructible<long long>();
    test_is_nothrow_destructible<unsigned long long>();
    test_is_nothrow_destructible<float>();
    test_is_nothrow_destructible<double>();
    test_is_nothrow_destructible<long double>();
    test_is_nothrow_destructible<char8_t>();
    test_is_nothrow_destructible<char16_t>();
    test_is_nothrow_destructible<char32_t>();
    test_is_nothrow_destructible<wchar_t>();

    test_is_nothrow_destructible<phi::boolean>();
    test_is_nothrow_destructible<phi::integer<signed char>>();
    test_is_nothrow_destructible<phi::integer<unsigned char>>();
    test_is_nothrow_destructible<phi::integer<short>>();
    test_is_nothrow_destructible<phi::integer<unsigned short>>();
    test_is_nothrow_destructible<phi::integer<int>>();
    test_is_nothrow_destructible<phi::integer<unsigned int>>();
    test_is_nothrow_destructible<phi::integer<long>>();
    test_is_nothrow_destructible<phi::integer<unsigned long>>();
    test_is_nothrow_destructible<phi::integer<long long>>();
    test_is_nothrow_destructible<phi::integer<unsigned long long>>();
    test_is_nothrow_destructible<phi::floating_point<float>>();
    test_is_nothrow_destructible<phi::floating_point<double>>();
    test_is_nothrow_destructible<phi::floating_point<long double>>();

    test_is_nothrow_destructible<std::vector<int>>();
    test_is_nothrow_destructible<phi::scope_ptr<int>>();

    test_is_nothrow_destructible<int&>();
    test_is_nothrow_destructible<const int&>();
    test_is_nothrow_destructible<volatile int&>();
    test_is_nothrow_destructible<const volatile int&>();
    test_is_nothrow_destructible<int&&>();
    test_is_nothrow_destructible<const int&&>();
    test_is_nothrow_destructible<volatile int&&>();
    test_is_nothrow_destructible<const volatile int&&>();
    test_is_nothrow_destructible<int*>();
    test_is_nothrow_destructible<const int*>();
    test_is_nothrow_destructible<volatile int*>();
    test_is_nothrow_destructible<const volatile int*>();
    test_is_nothrow_destructible<int**>();
    test_is_nothrow_destructible<const int**>();
    test_is_nothrow_destructible<volatile int**>();
    test_is_nothrow_destructible<const volatile int**>();
    test_is_nothrow_destructible<int*&>();
    test_is_nothrow_destructible<const int*&>();
    test_is_nothrow_destructible<volatile int*&>();
    test_is_nothrow_destructible<const volatile int*&>();
    test_is_nothrow_destructible<int*&&>();
    test_is_nothrow_destructible<const int*&&>();
    test_is_nothrow_destructible<volatile int*&&>();
    test_is_nothrow_destructible<const volatile int*&&>();
    test_is_nothrow_destructible<void*>();
    test_is_nothrow_destructible<char[3]>();
    test_is_not_nothrow_destructible<char[]>();
    test_is_nothrow_destructible<char* [3]>();
    test_is_not_nothrow_destructible<char*[]>();
    test_is_nothrow_destructible<int(*)[3]>();
    test_is_nothrow_destructible<int(*)[]>();
    test_is_nothrow_destructible<int(&)[3]>();
    test_is_nothrow_destructible<int(&)[]>();
    test_is_nothrow_destructible<int(&&)[3]>();
    test_is_nothrow_destructible<int(&&)[]>();
    test_is_nothrow_destructible<char[3][2]>();
    test_is_not_nothrow_destructible<char[][2]>();
    test_is_nothrow_destructible<char* [3][2]>();
    test_is_not_nothrow_destructible<char*[][2]>();
    test_is_nothrow_destructible<int(*)[3][2]>();
    test_is_nothrow_destructible<int(*)[][2]>();
    test_is_nothrow_destructible<int(&)[3][2]>();
    test_is_nothrow_destructible<int(&)[][2]>();
    test_is_nothrow_destructible<int(&&)[3][2]>();
    test_is_nothrow_destructible<int(&&)[][2]>();
    test_is_nothrow_destructible<Class>();
    test_is_not_nothrow_destructible<Class[]>();
    test_is_nothrow_destructible<Class[2]>();
    test_is_nothrow_destructible<Template<void>>();
    test_is_nothrow_destructible<Template<int>>();
    test_is_nothrow_destructible<Template<Class>>();
    test_is_nothrow_destructible<Template<incomplete_type>>();
    test_is_nothrow_destructible<VariadicTemplate<>>();
    test_is_nothrow_destructible<VariadicTemplate<void>>();
    test_is_nothrow_destructible<VariadicTemplate<int>>();
    test_is_nothrow_destructible<VariadicTemplate<Class>>();
    test_is_nothrow_destructible<VariadicTemplate<incomplete_type>>();
    test_is_nothrow_destructible<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_nothrow_destructible<PublicDerviedFromTemplate<Base>>();
    test_is_nothrow_destructible<PublicDerviedFromTemplate<Derived>>();
    test_is_nothrow_destructible<PublicDerviedFromTemplate<Class>>();
    test_is_nothrow_destructible<PrivateDerviedFromTemplate<Base>>();
    test_is_nothrow_destructible<PrivateDerviedFromTemplate<Derived>>();
    test_is_nothrow_destructible<PrivateDerviedFromTemplate<Class>>();
    test_is_nothrow_destructible<ProtectedDerviedFromTemplate<Base>>();
    test_is_nothrow_destructible<ProtectedDerviedFromTemplate<Derived>>();
    test_is_nothrow_destructible<ProtectedDerviedFromTemplate<Class>>();
    test_is_nothrow_destructible<Union>();
    test_is_nothrow_destructible<NonEmptyUnion>();
    test_is_nothrow_destructible<Empty>();
    test_is_nothrow_destructible<NotEmpty>();
    test_is_nothrow_destructible<bit_zero>();
    test_is_nothrow_destructible<bit_one>();
    test_is_nothrow_destructible<Base>();
    test_is_nothrow_destructible<Derived>();
    test_is_not_nothrow_destructible<Abstract>();
    test_is_nothrow_destructible<PublicAbstract>();
    test_is_nothrow_destructible<PrivateAbstract>();
    test_is_nothrow_destructible<ProtectedAbstract>();
    test_is_nothrow_destructible<AbstractTemplate<int>>();
    test_is_nothrow_destructible<AbstractTemplate<double>>();
    test_is_nothrow_destructible<AbstractTemplate<Class>>();
    test_is_nothrow_destructible<AbstractTemplate<incomplete_type>>();
    test_is_nothrow_destructible<Final>();
    test_is_nothrow_destructible<PublicDestructor>();
    test_is_not_nothrow_destructible<ProtectedDestructor>();
    test_is_not_nothrow_destructible<PrivateDestructor>();
    test_is_nothrow_destructible<VirtualPublicDestructor>();
    test_is_not_nothrow_destructible<VirtualProtectedDestructor>();
    test_is_not_nothrow_destructible<VirtualPrivateDestructor>();
    test_is_nothrow_destructible<PurePublicDestructor>();
    test_is_not_nothrow_destructible<PureProtectedDestructor>();
    test_is_not_nothrow_destructible<PurePrivateDestructor>();
    test_is_not_nothrow_destructible<DeletedPublicDestructor>();
    test_is_not_nothrow_destructible<DeletedProtectedDestructor>();
    test_is_not_nothrow_destructible<DeletedPrivateDestructor>();
    test_is_not_nothrow_destructible<DeletedVirtualPublicDestructor>();
    test_is_not_nothrow_destructible<DeletedVirtualProtectedDestructor>();
    test_is_not_nothrow_destructible<DeletedVirtualPrivateDestructor>();
    test_is_nothrow_destructible<Enum>();
    test_is_nothrow_destructible<EnumSigned>();
    test_is_nothrow_destructible<EnumUnsigned>();
    test_is_nothrow_destructible<EnumClass>();
    test_is_nothrow_destructible<EnumStruct>();
    test_is_not_nothrow_destructible<Function>();
    test_is_nothrow_destructible<FunctionPtr>();
    test_is_nothrow_destructible<MemberObjectPtr>();
    test_is_nothrow_destructible<MemberFunctionPtr>();
    test_is_nothrow_destructible<int Class::*>();
    test_is_nothrow_destructible<float Class::*>();
    test_is_nothrow_destructible<void * Class::*>();
    test_is_nothrow_destructible<int * Class::*>();
    test_is_nothrow_destructible<int Class::*&>();
    test_is_nothrow_destructible<float Class::*&>();
    test_is_nothrow_destructible<void * Class::*&>();
    test_is_nothrow_destructible<int * Class::*&>();
    test_is_nothrow_destructible<int Class::*&&>();
    test_is_nothrow_destructible<float Class::*&&>();
    test_is_nothrow_destructible<void * Class::*&&>();
    test_is_nothrow_destructible<int * Class::*&&>();
    test_is_nothrow_destructible<int Class::*const>();
    test_is_nothrow_destructible<float Class::*const>();
    test_is_nothrow_destructible<void * Class::*const>();
    test_is_nothrow_destructible<int Class::*const&>();
    test_is_nothrow_destructible<float Class::*const&>();
    test_is_nothrow_destructible<void * Class::*const&>();
    test_is_nothrow_destructible<int Class::*const&&>();
    test_is_nothrow_destructible<float Class::*const&&>();
    test_is_nothrow_destructible<void * Class::*const&&>();
    test_is_nothrow_destructible<int Class::*volatile>();
    test_is_nothrow_destructible<float Class::*volatile>();
    test_is_nothrow_destructible<void * Class::*volatile>();
    test_is_nothrow_destructible<int Class::*volatile&>();
    test_is_nothrow_destructible<float Class::*volatile&>();
    test_is_nothrow_destructible<void * Class::*volatile&>();
    test_is_nothrow_destructible<int Class::*volatile&&>();
    test_is_nothrow_destructible<float Class::*volatile&&>();
    test_is_nothrow_destructible<void * Class::*volatile&&>();
    test_is_nothrow_destructible<int Class::*const volatile>();
    test_is_nothrow_destructible<float Class::*const volatile>();
    test_is_nothrow_destructible<void * Class::*const volatile>();
    test_is_nothrow_destructible<int Class::*const volatile&>();
    test_is_nothrow_destructible<float Class::*const volatile&>();
    test_is_nothrow_destructible<void * Class::*const volatile&>();
    test_is_nothrow_destructible<int Class::*const volatile&&>();
    test_is_nothrow_destructible<float Class::*const volatile&&>();
    test_is_nothrow_destructible<void * Class::*const volatile&&>();
    test_is_nothrow_destructible<NonCopyable>();
    test_is_nothrow_destructible<NonMoveable>();
    test_is_nothrow_destructible<NonConstructible>();
    test_is_nothrow_destructible<Tracked>();
    test_is_nothrow_destructible<TrapConstructible>();
    test_is_nothrow_destructible<TrapImplicitConversion>();
    test_is_nothrow_destructible<TrapComma>();
    test_is_nothrow_destructible<TrapCall>();
    test_is_nothrow_destructible<TrapSelfAssign>();
    test_is_nothrow_destructible<TrapDeref>();
    test_is_nothrow_destructible<TrapArraySubscript>();

    test_is_not_nothrow_destructible<void()>();
    test_is_not_nothrow_destructible<void()&>();
    test_is_not_nothrow_destructible<void() &&>();
    test_is_not_nothrow_destructible<void() const>();
    test_is_not_nothrow_destructible<void() const&>();
    test_is_not_nothrow_destructible<void() const&&>();
    test_is_not_nothrow_destructible<void() volatile>();
    test_is_not_nothrow_destructible<void() volatile&>();
    test_is_not_nothrow_destructible<void() volatile&&>();
    test_is_not_nothrow_destructible<void() const volatile>();
    test_is_not_nothrow_destructible<void() const volatile&>();
    test_is_not_nothrow_destructible<void() const volatile&&>();
    test_is_not_nothrow_destructible<void() noexcept>();
    test_is_not_nothrow_destructible<void()& noexcept>();
    test_is_not_nothrow_destructible<void()&& noexcept>();
    test_is_not_nothrow_destructible<void() const noexcept>();
    test_is_not_nothrow_destructible<void() const& noexcept>();
    test_is_not_nothrow_destructible<void() const&& noexcept>();
    test_is_not_nothrow_destructible<void() volatile noexcept>();
    test_is_not_nothrow_destructible<void() volatile& noexcept>();
    test_is_not_nothrow_destructible<void() volatile&& noexcept>();
    test_is_not_nothrow_destructible<void() const volatile noexcept>();
    test_is_not_nothrow_destructible<void() const volatile& noexcept>();
    test_is_not_nothrow_destructible<void() const volatile&& noexcept>();

    test_is_not_nothrow_destructible<void(int)>();
    test_is_not_nothrow_destructible<void(int)&>();
    test_is_not_nothrow_destructible<void(int) &&>();
    test_is_not_nothrow_destructible<void(int) const>();
    test_is_not_nothrow_destructible<void(int) const&>();
    test_is_not_nothrow_destructible<void(int) const&&>();
    test_is_not_nothrow_destructible<void(int) volatile>();
    test_is_not_nothrow_destructible<void(int) volatile&>();
    test_is_not_nothrow_destructible<void(int) volatile&&>();
    test_is_not_nothrow_destructible<void(int) const volatile>();
    test_is_not_nothrow_destructible<void(int) const volatile&>();
    test_is_not_nothrow_destructible<void(int) const volatile&&>();
    test_is_not_nothrow_destructible<void(int) noexcept>();
    test_is_not_nothrow_destructible<void(int)& noexcept>();
    test_is_not_nothrow_destructible<void(int)&& noexcept>();
    test_is_not_nothrow_destructible<void(int) const noexcept>();
    test_is_not_nothrow_destructible<void(int) const& noexcept>();
    test_is_not_nothrow_destructible<void(int) const&& noexcept>();
    test_is_not_nothrow_destructible<void(int) volatile noexcept>();
    test_is_not_nothrow_destructible<void(int) volatile& noexcept>();
    test_is_not_nothrow_destructible<void(int) volatile&& noexcept>();
    test_is_not_nothrow_destructible<void(int) const volatile noexcept>();
    test_is_not_nothrow_destructible<void(int) const volatile& noexcept>();
    test_is_not_nothrow_destructible<void(int) const volatile&& noexcept>();

    test_is_not_nothrow_destructible<void(...)>();
    test_is_not_nothrow_destructible<void(...)&>();
    test_is_not_nothrow_destructible<void(...) &&>();
    test_is_not_nothrow_destructible<void(...) const>();
    test_is_not_nothrow_destructible<void(...) const&>();
    test_is_not_nothrow_destructible<void(...) const&&>();
    test_is_not_nothrow_destructible<void(...) volatile>();
    test_is_not_nothrow_destructible<void(...) volatile&>();
    test_is_not_nothrow_destructible<void(...) volatile&&>();
    test_is_not_nothrow_destructible<void(...) const volatile>();
    test_is_not_nothrow_destructible<void(...) const volatile&>();
    test_is_not_nothrow_destructible<void(...) const volatile&&>();
    test_is_not_nothrow_destructible<void(...) noexcept>();
    test_is_not_nothrow_destructible<void(...)& noexcept>();
    test_is_not_nothrow_destructible<void(...)&& noexcept>();
    test_is_not_nothrow_destructible<void(...) const noexcept>();
    test_is_not_nothrow_destructible<void(...) const& noexcept>();
    test_is_not_nothrow_destructible<void(...) const&& noexcept>();
    test_is_not_nothrow_destructible<void(...) volatile noexcept>();
    test_is_not_nothrow_destructible<void(...) volatile& noexcept>();
    test_is_not_nothrow_destructible<void(...) volatile&& noexcept>();
    test_is_not_nothrow_destructible<void(...) const volatile noexcept>();
    test_is_not_nothrow_destructible<void(...) const volatile& noexcept>();
    test_is_not_nothrow_destructible<void(...) const volatile&& noexcept>();

    test_is_not_nothrow_destructible<void(int, ...)>();
    test_is_not_nothrow_destructible<void(int, ...)&>();
    test_is_not_nothrow_destructible<void(int, ...) &&>();
    test_is_not_nothrow_destructible<void(int, ...) const>();
    test_is_not_nothrow_destructible<void(int, ...) const&>();
    test_is_not_nothrow_destructible<void(int, ...) const&&>();
    test_is_not_nothrow_destructible<void(int, ...) volatile>();
    test_is_not_nothrow_destructible<void(int, ...) volatile&>();
    test_is_not_nothrow_destructible<void(int, ...) volatile&&>();
    test_is_not_nothrow_destructible<void(int, ...) const volatile>();
    test_is_not_nothrow_destructible<void(int, ...) const volatile&>();
    test_is_not_nothrow_destructible<void(int, ...) const volatile&&>();
    test_is_not_nothrow_destructible<void(int, ...) noexcept>();
    test_is_not_nothrow_destructible<void(int, ...)& noexcept>();
    test_is_not_nothrow_destructible<void(int, ...)&& noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) const noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) const& noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) const&& noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) volatile noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) volatile& noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) volatile&& noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) const volatile noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) const volatile& noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) const volatile&& noexcept>();

    test_is_not_nothrow_destructible<int()>();
    test_is_not_nothrow_destructible<int()&>();
    test_is_not_nothrow_destructible<int() &&>();
    test_is_not_nothrow_destructible<int() const>();
    test_is_not_nothrow_destructible<int() const&>();
    test_is_not_nothrow_destructible<int() const&&>();
    test_is_not_nothrow_destructible<int() volatile>();
    test_is_not_nothrow_destructible<int() volatile&>();
    test_is_not_nothrow_destructible<int() volatile&&>();
    test_is_not_nothrow_destructible<int() const volatile>();
    test_is_not_nothrow_destructible<int() const volatile&>();
    test_is_not_nothrow_destructible<int() const volatile&&>();
    test_is_not_nothrow_destructible<int() noexcept>();
    test_is_not_nothrow_destructible<int()& noexcept>();
    test_is_not_nothrow_destructible<int()&& noexcept>();
    test_is_not_nothrow_destructible<int() const noexcept>();
    test_is_not_nothrow_destructible<int() const& noexcept>();
    test_is_not_nothrow_destructible<int() const&& noexcept>();
    test_is_not_nothrow_destructible<int() volatile noexcept>();
    test_is_not_nothrow_destructible<int() volatile& noexcept>();
    test_is_not_nothrow_destructible<int() volatile&& noexcept>();
    test_is_not_nothrow_destructible<int() const volatile noexcept>();
    test_is_not_nothrow_destructible<int() const volatile& noexcept>();
    test_is_not_nothrow_destructible<int() const volatile&& noexcept>();

    test_is_not_nothrow_destructible<int(int)>();
    test_is_not_nothrow_destructible<int(int)&>();
    test_is_not_nothrow_destructible<int(int) &&>();
    test_is_not_nothrow_destructible<int(int) const>();
    test_is_not_nothrow_destructible<int(int) const&>();
    test_is_not_nothrow_destructible<int(int) const&&>();
    test_is_not_nothrow_destructible<int(int) volatile>();
    test_is_not_nothrow_destructible<int(int) volatile&>();
    test_is_not_nothrow_destructible<int(int) volatile&&>();
    test_is_not_nothrow_destructible<int(int) const volatile>();
    test_is_not_nothrow_destructible<int(int) const volatile&>();
    test_is_not_nothrow_destructible<int(int) const volatile&&>();
    test_is_not_nothrow_destructible<int(int) noexcept>();
    test_is_not_nothrow_destructible<int(int)& noexcept>();
    test_is_not_nothrow_destructible<int(int)&& noexcept>();
    test_is_not_nothrow_destructible<int(int) const noexcept>();
    test_is_not_nothrow_destructible<int(int) const& noexcept>();
    test_is_not_nothrow_destructible<int(int) const&& noexcept>();
    test_is_not_nothrow_destructible<int(int) volatile noexcept>();
    test_is_not_nothrow_destructible<int(int) volatile& noexcept>();
    test_is_not_nothrow_destructible<int(int) volatile&& noexcept>();
    test_is_not_nothrow_destructible<int(int) const volatile noexcept>();
    test_is_not_nothrow_destructible<int(int) const volatile& noexcept>();
    test_is_not_nothrow_destructible<int(int) const volatile&& noexcept>();

    test_is_not_nothrow_destructible<int(...)>();
    test_is_not_nothrow_destructible<int(...)&>();
    test_is_not_nothrow_destructible<int(...) &&>();
    test_is_not_nothrow_destructible<int(...) const>();
    test_is_not_nothrow_destructible<int(...) const&>();
    test_is_not_nothrow_destructible<int(...) const&&>();
    test_is_not_nothrow_destructible<int(...) volatile>();
    test_is_not_nothrow_destructible<int(...) volatile&>();
    test_is_not_nothrow_destructible<int(...) volatile&&>();
    test_is_not_nothrow_destructible<int(...) const volatile>();
    test_is_not_nothrow_destructible<int(...) const volatile&>();
    test_is_not_nothrow_destructible<int(...) const volatile&&>();
    test_is_not_nothrow_destructible<int(...) noexcept>();
    test_is_not_nothrow_destructible<int(...)& noexcept>();
    test_is_not_nothrow_destructible<int(...)&& noexcept>();
    test_is_not_nothrow_destructible<int(...) const noexcept>();
    test_is_not_nothrow_destructible<int(...) const& noexcept>();
    test_is_not_nothrow_destructible<int(...) const&& noexcept>();
    test_is_not_nothrow_destructible<int(...) volatile noexcept>();
    test_is_not_nothrow_destructible<int(...) volatile& noexcept>();
    test_is_not_nothrow_destructible<int(...) volatile&& noexcept>();
    test_is_not_nothrow_destructible<int(...) const volatile noexcept>();
    test_is_not_nothrow_destructible<int(...) const volatile& noexcept>();
    test_is_not_nothrow_destructible<int(...) const volatile&& noexcept>();

    test_is_not_nothrow_destructible<int(int, ...)>();
    test_is_not_nothrow_destructible<int(int, ...)&>();
    test_is_not_nothrow_destructible<int(int, ...) &&>();
    test_is_not_nothrow_destructible<int(int, ...) const>();
    test_is_not_nothrow_destructible<int(int, ...) const&>();
    test_is_not_nothrow_destructible<int(int, ...) const&&>();
    test_is_not_nothrow_destructible<int(int, ...) volatile>();
    test_is_not_nothrow_destructible<int(int, ...) volatile&>();
    test_is_not_nothrow_destructible<int(int, ...) volatile&&>();
    test_is_not_nothrow_destructible<int(int, ...) const volatile>();
    test_is_not_nothrow_destructible<int(int, ...) const volatile&>();
    test_is_not_nothrow_destructible<int(int, ...) const volatile&&>();
    test_is_not_nothrow_destructible<int(int, ...) noexcept>();
    test_is_not_nothrow_destructible<int(int, ...)& noexcept>();
    test_is_not_nothrow_destructible<int(int, ...)&& noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) const noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) const& noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) const&& noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) volatile noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) volatile& noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) volatile&& noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) const volatile noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) const volatile& noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) const volatile&& noexcept>();

    test_is_nothrow_destructible<void (*)()>();
    test_is_nothrow_destructible<void (*)() noexcept>();

    test_is_nothrow_destructible<void (*)(int)>();
    test_is_nothrow_destructible<void (*)(int) noexcept>();

    test_is_nothrow_destructible<void (*)(...)>();
    test_is_nothrow_destructible<void (*)(...) noexcept>();

    test_is_nothrow_destructible<void (*)(int, ...)>();
    test_is_nothrow_destructible<void (*)(int, ...) noexcept>();

    test_is_nothrow_destructible<int (*)()>();
    test_is_nothrow_destructible<int (*)() noexcept>();

    test_is_nothrow_destructible<int (*)(int)>();
    test_is_nothrow_destructible<int (*)(int) noexcept>();

    test_is_nothrow_destructible<int (*)(...)>();
    test_is_nothrow_destructible<int (*)(...) noexcept>();

    test_is_nothrow_destructible<int (*)(int, ...)>();
    test_is_nothrow_destructible<int (*)(int, ...) noexcept>();

    test_is_nothrow_destructible<void (&)()>();
    test_is_nothrow_destructible<void (&)() noexcept>();

    test_is_nothrow_destructible<void (&)(int)>();
    test_is_nothrow_destructible<void (&)(int) noexcept>();

    test_is_nothrow_destructible<void (&)(...)>();
    test_is_nothrow_destructible<void (&)(...) noexcept>();

    test_is_nothrow_destructible<void (&)(int, ...)>();
    test_is_nothrow_destructible<void (&)(int, ...) noexcept>();

    test_is_nothrow_destructible<int (&)()>();
    test_is_nothrow_destructible<int (&)() noexcept>();

    test_is_nothrow_destructible<int (&)(int)>();
    test_is_nothrow_destructible<int (&)(int) noexcept>();

    test_is_nothrow_destructible<int (&)(...)>();
    test_is_nothrow_destructible<int (&)(...) noexcept>();

    test_is_nothrow_destructible<int (&)(int, ...)>();
    test_is_nothrow_destructible<int (&)(int, ...) noexcept>();

    test_is_nothrow_destructible<void(&&)()>();
    test_is_nothrow_destructible<void(&&)() noexcept>();

    test_is_nothrow_destructible<void(&&)(int)>();
    test_is_nothrow_destructible<void(&&)(int) noexcept>();

    test_is_nothrow_destructible<void(&&)(...)>();
    test_is_nothrow_destructible<void(&&)(...) noexcept>();

    test_is_nothrow_destructible<void(&&)(int, ...)>();
    test_is_nothrow_destructible<void(&&)(int, ...) noexcept>();

    test_is_nothrow_destructible<int(&&)()>();
    test_is_nothrow_destructible<int(&&)() noexcept>();

    test_is_nothrow_destructible<int(&&)(int)>();
    test_is_nothrow_destructible<int(&&)(int) noexcept>();

    test_is_nothrow_destructible<int(&&)(...)>();
    test_is_nothrow_destructible<int(&&)(...) noexcept>();

    test_is_nothrow_destructible<int(&&)(int, ...)>();
    test_is_nothrow_destructible<int(&&)(int, ...) noexcept>();

    test_is_nothrow_destructible<void (Class::*)()>();
    test_is_nothrow_destructible<void (Class::*)()&>();
    test_is_nothrow_destructible<void (Class::*)() &&>();
    test_is_nothrow_destructible<void (Class::*)() const>();
    test_is_nothrow_destructible<void (Class::*)() const&>();
    test_is_nothrow_destructible<void (Class::*)() const&&>();
    test_is_nothrow_destructible<void (Class::*)() noexcept>();
    test_is_nothrow_destructible<void (Class::*)()& noexcept>();
    test_is_nothrow_destructible<void (Class::*)()&& noexcept>();
    test_is_nothrow_destructible<void (Class::*)() const noexcept>();
    test_is_nothrow_destructible<void (Class::*)() const& noexcept>();
    test_is_nothrow_destructible<void (Class::*)() const&& noexcept>();

    test_is_nothrow_destructible<void (Class::*)(int)>();
    test_is_nothrow_destructible<void (Class::*)(int)&>();
    test_is_nothrow_destructible<void (Class::*)(int) &&>();
    test_is_nothrow_destructible<void (Class::*)(int) const>();
    test_is_nothrow_destructible<void (Class::*)(int) const&>();
    test_is_nothrow_destructible<void (Class::*)(int) const&&>();
    test_is_nothrow_destructible<void (Class::*)(int) noexcept>();
    test_is_nothrow_destructible<void (Class::*)(int)& noexcept>();
    test_is_nothrow_destructible<void (Class::*)(int)&& noexcept>();
    test_is_nothrow_destructible<void (Class::*)(int) const noexcept>();
    test_is_nothrow_destructible<void (Class::*)(int) const& noexcept>();
    test_is_nothrow_destructible<void (Class::*)(int) const&& noexcept>();

    test_is_nothrow_destructible<void (Class::*)(...)>();
    test_is_nothrow_destructible<void (Class::*)(...)&>();
    test_is_nothrow_destructible<void (Class::*)(...) &&>();
    test_is_nothrow_destructible<void (Class::*)(...) const>();
    test_is_nothrow_destructible<void (Class::*)(...) const&>();
    test_is_nothrow_destructible<void (Class::*)(...) const&&>();
    test_is_nothrow_destructible<void (Class::*)(...) noexcept>();
    test_is_nothrow_destructible<void (Class::*)(...)& noexcept>();
    test_is_nothrow_destructible<void (Class::*)(...)&& noexcept>();
    test_is_nothrow_destructible<void (Class::*)(...) const noexcept>();
    test_is_nothrow_destructible<void (Class::*)(...) const& noexcept>();
    test_is_nothrow_destructible<void (Class::*)(...) const&& noexcept>();

    test_is_nothrow_destructible<void (Class::*)(int, ...)>();
    test_is_nothrow_destructible<void (Class::*)(int, ...)&>();
    test_is_nothrow_destructible<void (Class::*)(int, ...) &&>();
    test_is_nothrow_destructible<void (Class::*)(int, ...) const>();
    test_is_nothrow_destructible<void (Class::*)(int, ...) const&>();
    test_is_nothrow_destructible<void (Class::*)(int, ...) const&&>();
    test_is_nothrow_destructible<void (Class::*)(int, ...) noexcept>();
    test_is_nothrow_destructible<void (Class::*)(int, ...)& noexcept>();
    test_is_nothrow_destructible<void (Class::*)(int, ...)&& noexcept>();
    test_is_nothrow_destructible<void (Class::*)(int, ...) const noexcept>();
    test_is_nothrow_destructible<void (Class::*)(int, ...) const& noexcept>();
    test_is_nothrow_destructible<void (Class::*)(int, ...) const&& noexcept>();

    test_is_nothrow_destructible<int (Class::*)()>();
    test_is_nothrow_destructible<int (Class::*)()&>();
    test_is_nothrow_destructible<int (Class::*)() &&>();
    test_is_nothrow_destructible<int (Class::*)() const>();
    test_is_nothrow_destructible<int (Class::*)() const&>();
    test_is_nothrow_destructible<int (Class::*)() const&&>();
    test_is_nothrow_destructible<int (Class::*)() noexcept>();
    test_is_nothrow_destructible<int (Class::*)()& noexcept>();
    test_is_nothrow_destructible<int (Class::*)()&& noexcept>();
    test_is_nothrow_destructible<int (Class::*)() const noexcept>();
    test_is_nothrow_destructible<int (Class::*)() const& noexcept>();
    test_is_nothrow_destructible<int (Class::*)() const&& noexcept>();

    test_is_nothrow_destructible<int (Class::*)(int)>();
    test_is_nothrow_destructible<int (Class::*)(int)&>();
    test_is_nothrow_destructible<int (Class::*)(int) &&>();
    test_is_nothrow_destructible<int (Class::*)(int) const>();
    test_is_nothrow_destructible<int (Class::*)(int) const&>();
    test_is_nothrow_destructible<int (Class::*)(int) const&&>();
    test_is_nothrow_destructible<int (Class::*)(int) noexcept>();
    test_is_nothrow_destructible<int (Class::*)(int)& noexcept>();
    test_is_nothrow_destructible<int (Class::*)(int)&& noexcept>();
    test_is_nothrow_destructible<int (Class::*)(int) const noexcept>();
    test_is_nothrow_destructible<int (Class::*)(int) const& noexcept>();
    test_is_nothrow_destructible<int (Class::*)(int) const&& noexcept>();

    test_is_nothrow_destructible<int (Class::*)(...)>();
    test_is_nothrow_destructible<int (Class::*)(...)&>();
    test_is_nothrow_destructible<int (Class::*)(...) &&>();
    test_is_nothrow_destructible<int (Class::*)(...) const>();
    test_is_nothrow_destructible<int (Class::*)(...) const&>();
    test_is_nothrow_destructible<int (Class::*)(...) const&&>();
    test_is_nothrow_destructible<int (Class::*)(...) noexcept>();
    test_is_nothrow_destructible<int (Class::*)(...)& noexcept>();
    test_is_nothrow_destructible<int (Class::*)(...)&& noexcept>();
    test_is_nothrow_destructible<int (Class::*)(...) const noexcept>();
    test_is_nothrow_destructible<int (Class::*)(...) const& noexcept>();
    test_is_nothrow_destructible<int (Class::*)(...) const&& noexcept>();

    test_is_nothrow_destructible<int (Class::*)(int, ...)>();
    test_is_nothrow_destructible<int (Class::*)(int, ...)&>();
    test_is_nothrow_destructible<int (Class::*)(int, ...) &&>();
    test_is_nothrow_destructible<int (Class::*)(int, ...) const>();
    test_is_nothrow_destructible<int (Class::*)(int, ...) const&>();
    test_is_nothrow_destructible<int (Class::*)(int, ...) const&&>();
    test_is_nothrow_destructible<int (Class::*)(int, ...) noexcept>();
    test_is_nothrow_destructible<int (Class::*)(int, ...)& noexcept>();
    test_is_nothrow_destructible<int (Class::*)(int, ...)&& noexcept>();
    test_is_nothrow_destructible<int (Class::*)(int, ...) const noexcept>();
    test_is_nothrow_destructible<int (Class::*)(int, ...) const& noexcept>();
    test_is_nothrow_destructible<int (Class::*)(int, ...) const&& noexcept>();
}
