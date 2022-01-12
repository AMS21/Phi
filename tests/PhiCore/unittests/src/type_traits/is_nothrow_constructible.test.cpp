#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_constructible.hpp>
#include <phi/type_traits/is_nothrow_constructible.hpp>
#include <type_traits>
#include <vector>

template <typename T, typename... Args>
void test_is_nothrow_constructible()
{
    STATIC_REQUIRE(phi::is_nothrow_constructible<T, Args...>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_constructible<T, Args...>::value);
    STATIC_REQUIRE(phi::is_constructible<T, Args...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_constructible_v<T, Args...>);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_constructible_v<T, Args...>);
    STATIC_REQUIRE(phi::is_constructible_v<T, Args...>);
#endif

    // Standard compatibililty
    STATIC_REQUIRE(std::is_nothrow_constructible<T, Args...>::value);
}

template <typename T, typename... Args>
void test_is_not_nothrow_constructible()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_constructible<T, Args...>::value);
    STATIC_REQUIRE(phi::is_not_nothrow_constructible<T, Args...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_constructible_v<T, Args...>);
    STATIC_REQUIRE(phi::is_not_nothrow_constructible_v<T, Args...>);
#endif

    // Standard compatibililty
    STATIC_REQUIRE_FALSE(std::is_nothrow_constructible<T, Args...>::value);
}

struct A
{
    A(const A&);
};

struct B
{
    B(const B&) noexcept;
};

struct C
{
    C(C&);              // not const
    void operator=(C&); // not const
};

struct D
{
    D();
};

struct E
{
    E() noexcept;
};

struct F
{
    F(int, double, char) noexcept;
};

struct Tuple
{
    Tuple(Empty&&) noexcept
    {}
};

TEST_CASE("is_nothrow_constructible")
{
    test_is_nothrow_constructible<int>();
    test_is_nothrow_constructible<int, const int&>();
    test_is_nothrow_constructible<Empty>();
    test_is_nothrow_constructible<Empty, const Empty&>();

    test_is_not_nothrow_constructible<A, int>();
    test_is_not_nothrow_constructible<A, int, double>();
    test_is_not_nothrow_constructible<A>();
    test_is_nothrow_constructible<B, const B&>();
    test_is_not_nothrow_constructible<C>();
    test_is_not_nothrow_constructible<D>();
    test_is_not_nothrow_constructible<F>();
    test_is_not_nothrow_constructible<F, int>();
    test_is_not_nothrow_constructible<F, int, double>();
    test_is_nothrow_constructible<F, int, double, char>();
    test_is_nothrow_constructible<F, int, float, char>();
    test_is_nothrow_constructible<Tuple&&, Empty>();

    STATIC_REQUIRE_FALSE(phi::is_constructible<Tuple&, Empty>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_constructible_v<Tuple&, Empty>);
#endif
    test_is_not_nothrow_constructible<Tuple&, Empty>();

    test_is_not_nothrow_constructible<void>();
    test_is_nothrow_constructible<phi::nullptr_t>();
    test_is_nothrow_constructible<bool>();
    test_is_nothrow_constructible<char>();
    test_is_nothrow_constructible<signed char>();
    test_is_nothrow_constructible<unsigned char>();
    test_is_nothrow_constructible<short>();
    test_is_nothrow_constructible<unsigned short>();
    test_is_nothrow_constructible<int>();
    test_is_nothrow_constructible<unsigned int>();
    test_is_nothrow_constructible<long>();
    test_is_nothrow_constructible<unsigned long>();
    test_is_nothrow_constructible<long long>();
    test_is_nothrow_constructible<unsigned long long>();
    test_is_nothrow_constructible<float>();
    test_is_nothrow_constructible<double>();
    test_is_nothrow_constructible<long double>();
    test_is_nothrow_constructible<char8_t>();
    test_is_nothrow_constructible<char16_t>();
    test_is_nothrow_constructible<char32_t>();
    test_is_nothrow_constructible<wchar_t>();

    test_is_not_nothrow_constructible<phi::boolean>();
    test_is_not_nothrow_constructible<phi::integer<signed char>>();
    test_is_not_nothrow_constructible<phi::integer<unsigned char>>();
    test_is_not_nothrow_constructible<phi::integer<short>>();
    test_is_not_nothrow_constructible<phi::integer<unsigned short>>();
    test_is_not_nothrow_constructible<phi::integer<int>>();
    test_is_not_nothrow_constructible<phi::integer<unsigned int>>();
    test_is_not_nothrow_constructible<phi::integer<long>>();
    test_is_not_nothrow_constructible<phi::integer<unsigned long>>();
    test_is_not_nothrow_constructible<phi::integer<long long>>();
    test_is_not_nothrow_constructible<phi::integer<unsigned long long>>();
    test_is_not_nothrow_constructible<phi::floating_point<float>>();
    test_is_not_nothrow_constructible<phi::floating_point<double>>();
    test_is_not_nothrow_constructible<phi::floating_point<long double>>();

    test_is_nothrow_constructible<std::vector<int>>();
    test_is_nothrow_constructible<phi::scope_ptr<int>>();

    test_is_not_nothrow_constructible<int&>();
    test_is_not_nothrow_constructible<const int&>();
    test_is_not_nothrow_constructible<volatile int&>();
    test_is_not_nothrow_constructible<const volatile int&>();
    test_is_not_nothrow_constructible<int&&>();
    test_is_not_nothrow_constructible<const int&&>();
    test_is_not_nothrow_constructible<volatile int&&>();
    test_is_not_nothrow_constructible<const volatile int&&>();
    test_is_nothrow_constructible<int*>();
    test_is_nothrow_constructible<const int*>();
    test_is_nothrow_constructible<volatile int*>();
    test_is_nothrow_constructible<const volatile int*>();
    test_is_nothrow_constructible<int**>();
    test_is_nothrow_constructible<const int**>();
    test_is_nothrow_constructible<volatile int**>();
    test_is_nothrow_constructible<const volatile int**>();
    test_is_not_nothrow_constructible<int*&>();
    test_is_not_nothrow_constructible<const int*&>();
    test_is_not_nothrow_constructible<volatile int*&>();
    test_is_not_nothrow_constructible<const volatile int*&>();
    test_is_not_nothrow_constructible<int*&&>();
    test_is_not_nothrow_constructible<const int*&&>();
    test_is_not_nothrow_constructible<volatile int*&&>();
    test_is_not_nothrow_constructible<const volatile int*&&>();
    test_is_nothrow_constructible<void*>();
    test_is_nothrow_constructible<char[3]>();
    test_is_not_nothrow_constructible<char[]>();
    test_is_nothrow_constructible<char* [3]>();
    test_is_not_nothrow_constructible<char*[]>();
    test_is_nothrow_constructible<int(*)[3]>();
    test_is_nothrow_constructible<int(*)[]>();
    test_is_not_nothrow_constructible<int(&)[3]>();
    test_is_not_nothrow_constructible<int(&)[]>();
    test_is_not_nothrow_constructible<int(&&)[3]>();
    test_is_not_nothrow_constructible<int(&&)[]>();
    test_is_nothrow_constructible<char[3][2]>();
    test_is_not_nothrow_constructible<char[][2]>();
    test_is_nothrow_constructible<char* [3][2]>();
    test_is_not_nothrow_constructible<char*[][2]>();
    test_is_nothrow_constructible<int(*)[3][2]>();
    test_is_nothrow_constructible<int(*)[][2]>();
    test_is_not_nothrow_constructible<int(&)[3][2]>();
    test_is_not_nothrow_constructible<int(&)[][2]>();
    test_is_not_nothrow_constructible<int(&&)[3][2]>();
    test_is_not_nothrow_constructible<int(&&)[][2]>();
    test_is_nothrow_constructible<Class>();
    test_is_not_nothrow_constructible<Class[]>();
    test_is_nothrow_constructible<Class[2]>();
    test_is_nothrow_constructible<Template<void>>();
    test_is_nothrow_constructible<Template<int>>();
    test_is_nothrow_constructible<Template<Class>>();
    test_is_nothrow_constructible<Template<incomplete_type>>();
    test_is_nothrow_constructible<VariadicTemplate<>>();
    test_is_nothrow_constructible<VariadicTemplate<void>>();
    test_is_nothrow_constructible<VariadicTemplate<int>>();
    test_is_nothrow_constructible<VariadicTemplate<Class>>();
    test_is_nothrow_constructible<VariadicTemplate<incomplete_type>>();
    test_is_nothrow_constructible<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_nothrow_constructible<PublicDerviedFromTemplate<Base>>();
    test_is_nothrow_constructible<PublicDerviedFromTemplate<Derived>>();
    test_is_nothrow_constructible<PublicDerviedFromTemplate<Class>>();
    test_is_nothrow_constructible<PrivateDerviedFromTemplate<Base>>();
    test_is_nothrow_constructible<PrivateDerviedFromTemplate<Derived>>();
    test_is_nothrow_constructible<PrivateDerviedFromTemplate<Class>>();
    test_is_nothrow_constructible<ProtectedDerviedFromTemplate<Base>>();
    test_is_nothrow_constructible<ProtectedDerviedFromTemplate<Derived>>();
    test_is_nothrow_constructible<ProtectedDerviedFromTemplate<Class>>();
    test_is_nothrow_constructible<Union>();
    test_is_nothrow_constructible<NonEmptyUnion>();
    test_is_nothrow_constructible<Empty>();
    test_is_nothrow_constructible<NotEmpty>();
    test_is_nothrow_constructible<bit_zero>();
    test_is_nothrow_constructible<bit_one>();
    test_is_nothrow_constructible<Base>();
    test_is_nothrow_constructible<Derived>();
    test_is_not_nothrow_constructible<Abstract>();
    test_is_not_nothrow_constructible<PublicAbstract>();
    test_is_not_nothrow_constructible<PrivateAbstract>();
    test_is_not_nothrow_constructible<ProtectedAbstract>();
    test_is_not_nothrow_constructible<AbstractTemplate<int>>();
    test_is_nothrow_constructible<AbstractTemplate<double>>();
    test_is_not_nothrow_constructible<AbstractTemplate<Class>>();
    test_is_not_nothrow_constructible<AbstractTemplate<incomplete_type>>();
    test_is_nothrow_constructible<Final>();
    test_is_nothrow_constructible<PublicDestructor>();
    test_is_not_nothrow_constructible<ProtectedDestructor>();
    test_is_not_nothrow_constructible<PrivateDestructor>();
    test_is_nothrow_constructible<VirtualPublicDestructor>();
    test_is_not_nothrow_constructible<VirtualProtectedDestructor>();
    test_is_not_nothrow_constructible<VirtualPrivateDestructor>();
    test_is_not_nothrow_constructible<PurePublicDestructor>();
    test_is_not_nothrow_constructible<PureProtectedDestructor>();
    test_is_not_nothrow_constructible<PurePrivateDestructor>();
    test_is_not_nothrow_constructible<DeletedPublicDestructor>();
    test_is_not_nothrow_constructible<DeletedProtectedDestructor>();
    test_is_not_nothrow_constructible<DeletedPrivateDestructor>();
    test_is_not_nothrow_constructible<DeletedVirtualPublicDestructor>();
    test_is_not_nothrow_constructible<DeletedVirtualProtectedDestructor>();
    test_is_not_nothrow_constructible<DeletedVirtualPrivateDestructor>();
    test_is_nothrow_constructible<Enum>();
    test_is_nothrow_constructible<EnumSigned>();
    test_is_nothrow_constructible<EnumUnsigned>();
    test_is_nothrow_constructible<EnumClass>();
    test_is_nothrow_constructible<EnumStruct>();
    test_is_not_nothrow_constructible<Function>();
    test_is_nothrow_constructible<FunctionPtr>();
    test_is_nothrow_constructible<MemberObjectPtr>();
    test_is_nothrow_constructible<MemberFunctionPtr>();
    test_is_nothrow_constructible<int Class::*>();
    test_is_nothrow_constructible<float Class::*>();
    test_is_nothrow_constructible<void * Class::*>();
    test_is_nothrow_constructible<int * Class::*>();
    test_is_not_nothrow_constructible<int Class::*&>();
    test_is_not_nothrow_constructible<float Class::*&>();
    test_is_not_nothrow_constructible<void * Class::*&>();
    test_is_not_nothrow_constructible<int * Class::*&>();
    test_is_not_nothrow_constructible<int Class::*&&>();
    test_is_not_nothrow_constructible<float Class::*&&>();
    test_is_not_nothrow_constructible<void * Class::*&&>();
    test_is_not_nothrow_constructible<int * Class::*&&>();
    test_is_nothrow_constructible<int Class::*const>();
    test_is_nothrow_constructible<float Class::*const>();
    test_is_nothrow_constructible<void * Class::*const>();
    test_is_not_nothrow_constructible<int Class::*const&>();
    test_is_not_nothrow_constructible<float Class::*const&>();
    test_is_not_nothrow_constructible<void * Class::*const&>();
    test_is_not_nothrow_constructible<int Class::*const&&>();
    test_is_not_nothrow_constructible<float Class::*const&&>();
    test_is_not_nothrow_constructible<void * Class::*const&&>();
    test_is_nothrow_constructible<int Class::*volatile>();
    test_is_nothrow_constructible<float Class::*volatile>();
    test_is_nothrow_constructible<void * Class::*volatile>();
    test_is_not_nothrow_constructible<int Class::*volatile&>();
    test_is_not_nothrow_constructible<float Class::*volatile&>();
    test_is_not_nothrow_constructible<void * Class::*volatile&>();
    test_is_not_nothrow_constructible<int Class::*volatile&&>();
    test_is_not_nothrow_constructible<float Class::*volatile&&>();
    test_is_not_nothrow_constructible<void * Class::*volatile&&>();
    test_is_nothrow_constructible<int Class::*const volatile>();
    test_is_nothrow_constructible<float Class::*const volatile>();
    test_is_nothrow_constructible<void * Class::*const volatile>();
    test_is_not_nothrow_constructible<int Class::*const volatile&>();
    test_is_not_nothrow_constructible<float Class::*const volatile&>();
    test_is_not_nothrow_constructible<void * Class::*const volatile&>();
    test_is_not_nothrow_constructible<int Class::*const volatile&&>();
    test_is_not_nothrow_constructible<float Class::*const volatile&&>();
    test_is_not_nothrow_constructible<void * Class::*const volatile&&>();
    test_is_nothrow_constructible<NonCopyable>();
    test_is_nothrow_constructible<NonMoveable>();
    test_is_not_nothrow_constructible<NonConstructible>();
    test_is_nothrow_constructible<Tracked>();
    test_is_nothrow_constructible<TrapConstructible>();
    test_is_nothrow_constructible<TrapImplicitConversion>();
    test_is_nothrow_constructible<TrapComma>();
    test_is_nothrow_constructible<TrapCall>();
    test_is_nothrow_constructible<TrapSelfAssign>();
    test_is_nothrow_constructible<TrapDeref>();
    test_is_nothrow_constructible<TrapArraySubscript>();

    test_is_not_nothrow_constructible<void()>();
    test_is_not_nothrow_constructible<void()&>();
    test_is_not_nothrow_constructible<void() &&>();
    test_is_not_nothrow_constructible<void() const>();
    test_is_not_nothrow_constructible<void() const&>();
    test_is_not_nothrow_constructible<void() const&&>();
    test_is_not_nothrow_constructible<void() volatile>();
    test_is_not_nothrow_constructible<void() volatile&>();
    test_is_not_nothrow_constructible<void() volatile&&>();
    test_is_not_nothrow_constructible<void() const volatile>();
    test_is_not_nothrow_constructible<void() const volatile&>();
    test_is_not_nothrow_constructible<void() const volatile&&>();
    test_is_not_nothrow_constructible<void() noexcept>();
    test_is_not_nothrow_constructible<void()& noexcept>();
    test_is_not_nothrow_constructible<void()&& noexcept>();
    test_is_not_nothrow_constructible<void() const noexcept>();
    test_is_not_nothrow_constructible<void() const& noexcept>();
    test_is_not_nothrow_constructible<void() const&& noexcept>();
    test_is_not_nothrow_constructible<void() volatile noexcept>();
    test_is_not_nothrow_constructible<void() volatile& noexcept>();
    test_is_not_nothrow_constructible<void() volatile&& noexcept>();
    test_is_not_nothrow_constructible<void() const volatile noexcept>();
    test_is_not_nothrow_constructible<void() const volatile& noexcept>();
    test_is_not_nothrow_constructible<void() const volatile&& noexcept>();

    test_is_not_nothrow_constructible<void(int)>();
    test_is_not_nothrow_constructible<void(int)&>();
    test_is_not_nothrow_constructible<void(int) &&>();
    test_is_not_nothrow_constructible<void(int) const>();
    test_is_not_nothrow_constructible<void(int) const&>();
    test_is_not_nothrow_constructible<void(int) const&&>();
    test_is_not_nothrow_constructible<void(int) volatile>();
    test_is_not_nothrow_constructible<void(int) volatile&>();
    test_is_not_nothrow_constructible<void(int) volatile&&>();
    test_is_not_nothrow_constructible<void(int) const volatile>();
    test_is_not_nothrow_constructible<void(int) const volatile&>();
    test_is_not_nothrow_constructible<void(int) const volatile&&>();
    test_is_not_nothrow_constructible<void(int) noexcept>();
    test_is_not_nothrow_constructible<void(int)& noexcept>();
    test_is_not_nothrow_constructible<void(int)&& noexcept>();
    test_is_not_nothrow_constructible<void(int) const noexcept>();
    test_is_not_nothrow_constructible<void(int) const& noexcept>();
    test_is_not_nothrow_constructible<void(int) const&& noexcept>();
    test_is_not_nothrow_constructible<void(int) volatile noexcept>();
    test_is_not_nothrow_constructible<void(int) volatile& noexcept>();
    test_is_not_nothrow_constructible<void(int) volatile&& noexcept>();
    test_is_not_nothrow_constructible<void(int) const volatile noexcept>();
    test_is_not_nothrow_constructible<void(int) const volatile& noexcept>();
    test_is_not_nothrow_constructible<void(int) const volatile&& noexcept>();

    test_is_not_nothrow_constructible<void(...)>();
    test_is_not_nothrow_constructible<void(...)&>();
    test_is_not_nothrow_constructible<void(...) &&>();
    test_is_not_nothrow_constructible<void(...) const>();
    test_is_not_nothrow_constructible<void(...) const&>();
    test_is_not_nothrow_constructible<void(...) const&&>();
    test_is_not_nothrow_constructible<void(...) volatile>();
    test_is_not_nothrow_constructible<void(...) volatile&>();
    test_is_not_nothrow_constructible<void(...) volatile&&>();
    test_is_not_nothrow_constructible<void(...) const volatile>();
    test_is_not_nothrow_constructible<void(...) const volatile&>();
    test_is_not_nothrow_constructible<void(...) const volatile&&>();
    test_is_not_nothrow_constructible<void(...) noexcept>();
    test_is_not_nothrow_constructible<void(...)& noexcept>();
    test_is_not_nothrow_constructible<void(...)&& noexcept>();
    test_is_not_nothrow_constructible<void(...) const noexcept>();
    test_is_not_nothrow_constructible<void(...) const& noexcept>();
    test_is_not_nothrow_constructible<void(...) const&& noexcept>();
    test_is_not_nothrow_constructible<void(...) volatile noexcept>();
    test_is_not_nothrow_constructible<void(...) volatile& noexcept>();
    test_is_not_nothrow_constructible<void(...) volatile&& noexcept>();
    test_is_not_nothrow_constructible<void(...) const volatile noexcept>();
    test_is_not_nothrow_constructible<void(...) const volatile& noexcept>();
    test_is_not_nothrow_constructible<void(...) const volatile&& noexcept>();

    test_is_not_nothrow_constructible<void(int, ...)>();
    test_is_not_nothrow_constructible<void(int, ...)&>();
    test_is_not_nothrow_constructible<void(int, ...) &&>();
    test_is_not_nothrow_constructible<void(int, ...) const>();
    test_is_not_nothrow_constructible<void(int, ...) const&>();
    test_is_not_nothrow_constructible<void(int, ...) const&&>();
    test_is_not_nothrow_constructible<void(int, ...) volatile>();
    test_is_not_nothrow_constructible<void(int, ...) volatile&>();
    test_is_not_nothrow_constructible<void(int, ...) volatile&&>();
    test_is_not_nothrow_constructible<void(int, ...) const volatile>();
    test_is_not_nothrow_constructible<void(int, ...) const volatile&>();
    test_is_not_nothrow_constructible<void(int, ...) const volatile&&>();
    test_is_not_nothrow_constructible<void(int, ...) noexcept>();
    test_is_not_nothrow_constructible<void(int, ...)& noexcept>();
    test_is_not_nothrow_constructible<void(int, ...)&& noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) const noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) const& noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) const&& noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) volatile noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) volatile& noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) volatile&& noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) const volatile noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) const volatile& noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) const volatile&& noexcept>();

    test_is_not_nothrow_constructible<int()>();
    test_is_not_nothrow_constructible<int()&>();
    test_is_not_nothrow_constructible<int() &&>();
    test_is_not_nothrow_constructible<int() const>();
    test_is_not_nothrow_constructible<int() const&>();
    test_is_not_nothrow_constructible<int() const&&>();
    test_is_not_nothrow_constructible<int() volatile>();
    test_is_not_nothrow_constructible<int() volatile&>();
    test_is_not_nothrow_constructible<int() volatile&&>();
    test_is_not_nothrow_constructible<int() const volatile>();
    test_is_not_nothrow_constructible<int() const volatile&>();
    test_is_not_nothrow_constructible<int() const volatile&&>();
    test_is_not_nothrow_constructible<int() noexcept>();
    test_is_not_nothrow_constructible<int()& noexcept>();
    test_is_not_nothrow_constructible<int()&& noexcept>();
    test_is_not_nothrow_constructible<int() const noexcept>();
    test_is_not_nothrow_constructible<int() const& noexcept>();
    test_is_not_nothrow_constructible<int() const&& noexcept>();
    test_is_not_nothrow_constructible<int() volatile noexcept>();
    test_is_not_nothrow_constructible<int() volatile& noexcept>();
    test_is_not_nothrow_constructible<int() volatile&& noexcept>();
    test_is_not_nothrow_constructible<int() const volatile noexcept>();
    test_is_not_nothrow_constructible<int() const volatile& noexcept>();
    test_is_not_nothrow_constructible<int() const volatile&& noexcept>();

    test_is_not_nothrow_constructible<int(int)>();
    test_is_not_nothrow_constructible<int(int)&>();
    test_is_not_nothrow_constructible<int(int) &&>();
    test_is_not_nothrow_constructible<int(int) const>();
    test_is_not_nothrow_constructible<int(int) const&>();
    test_is_not_nothrow_constructible<int(int) const&&>();
    test_is_not_nothrow_constructible<int(int) volatile>();
    test_is_not_nothrow_constructible<int(int) volatile&>();
    test_is_not_nothrow_constructible<int(int) volatile&&>();
    test_is_not_nothrow_constructible<int(int) const volatile>();
    test_is_not_nothrow_constructible<int(int) const volatile&>();
    test_is_not_nothrow_constructible<int(int) const volatile&&>();
    test_is_not_nothrow_constructible<int(int) noexcept>();
    test_is_not_nothrow_constructible<int(int)& noexcept>();
    test_is_not_nothrow_constructible<int(int)&& noexcept>();
    test_is_not_nothrow_constructible<int(int) const noexcept>();
    test_is_not_nothrow_constructible<int(int) const& noexcept>();
    test_is_not_nothrow_constructible<int(int) const&& noexcept>();
    test_is_not_nothrow_constructible<int(int) volatile noexcept>();
    test_is_not_nothrow_constructible<int(int) volatile& noexcept>();
    test_is_not_nothrow_constructible<int(int) volatile&& noexcept>();
    test_is_not_nothrow_constructible<int(int) const volatile noexcept>();
    test_is_not_nothrow_constructible<int(int) const volatile& noexcept>();
    test_is_not_nothrow_constructible<int(int) const volatile&& noexcept>();

    test_is_not_nothrow_constructible<int(...)>();
    test_is_not_nothrow_constructible<int(...)&>();
    test_is_not_nothrow_constructible<int(...) &&>();
    test_is_not_nothrow_constructible<int(...) const>();
    test_is_not_nothrow_constructible<int(...) const&>();
    test_is_not_nothrow_constructible<int(...) const&&>();
    test_is_not_nothrow_constructible<int(...) volatile>();
    test_is_not_nothrow_constructible<int(...) volatile&>();
    test_is_not_nothrow_constructible<int(...) volatile&&>();
    test_is_not_nothrow_constructible<int(...) const volatile>();
    test_is_not_nothrow_constructible<int(...) const volatile&>();
    test_is_not_nothrow_constructible<int(...) const volatile&&>();
    test_is_not_nothrow_constructible<int(...) noexcept>();
    test_is_not_nothrow_constructible<int(...)& noexcept>();
    test_is_not_nothrow_constructible<int(...)&& noexcept>();
    test_is_not_nothrow_constructible<int(...) const noexcept>();
    test_is_not_nothrow_constructible<int(...) const& noexcept>();
    test_is_not_nothrow_constructible<int(...) const&& noexcept>();
    test_is_not_nothrow_constructible<int(...) volatile noexcept>();
    test_is_not_nothrow_constructible<int(...) volatile& noexcept>();
    test_is_not_nothrow_constructible<int(...) volatile&& noexcept>();
    test_is_not_nothrow_constructible<int(...) const volatile noexcept>();
    test_is_not_nothrow_constructible<int(...) const volatile& noexcept>();
    test_is_not_nothrow_constructible<int(...) const volatile&& noexcept>();

    test_is_not_nothrow_constructible<int(int, ...)>();
    test_is_not_nothrow_constructible<int(int, ...)&>();
    test_is_not_nothrow_constructible<int(int, ...) &&>();
    test_is_not_nothrow_constructible<int(int, ...) const>();
    test_is_not_nothrow_constructible<int(int, ...) const&>();
    test_is_not_nothrow_constructible<int(int, ...) const&&>();
    test_is_not_nothrow_constructible<int(int, ...) volatile>();
    test_is_not_nothrow_constructible<int(int, ...) volatile&>();
    test_is_not_nothrow_constructible<int(int, ...) volatile&&>();
    test_is_not_nothrow_constructible<int(int, ...) const volatile>();
    test_is_not_nothrow_constructible<int(int, ...) const volatile&>();
    test_is_not_nothrow_constructible<int(int, ...) const volatile&&>();
    test_is_not_nothrow_constructible<int(int, ...) noexcept>();
    test_is_not_nothrow_constructible<int(int, ...)& noexcept>();
    test_is_not_nothrow_constructible<int(int, ...)&& noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) const noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) const& noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) const&& noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) volatile noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) volatile& noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) volatile&& noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) const volatile noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) const volatile& noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) const volatile&& noexcept>();

    test_is_nothrow_constructible<void (*)()>();
    test_is_nothrow_constructible<void (*)() noexcept>();

    test_is_nothrow_constructible<void (*)(int)>();
    test_is_nothrow_constructible<void (*)(int) noexcept>();

    test_is_nothrow_constructible<void (*)(...)>();
    test_is_nothrow_constructible<void (*)(...) noexcept>();

    test_is_nothrow_constructible<void (*)(int, ...)>();
    test_is_nothrow_constructible<void (*)(int, ...) noexcept>();

    test_is_nothrow_constructible<int (*)()>();
    test_is_nothrow_constructible<int (*)() noexcept>();

    test_is_nothrow_constructible<int (*)(int)>();
    test_is_nothrow_constructible<int (*)(int) noexcept>();

    test_is_nothrow_constructible<int (*)(...)>();
    test_is_nothrow_constructible<int (*)(...) noexcept>();

    test_is_nothrow_constructible<int (*)(int, ...)>();
    test_is_nothrow_constructible<int (*)(int, ...) noexcept>();

    test_is_not_nothrow_constructible<void (&)()>();
    test_is_not_nothrow_constructible<void (&)() noexcept>();

    test_is_not_nothrow_constructible<void (&)(int)>();
    test_is_not_nothrow_constructible<void (&)(int) noexcept>();

    test_is_not_nothrow_constructible<void (&)(...)>();
    test_is_not_nothrow_constructible<void (&)(...) noexcept>();

    test_is_not_nothrow_constructible<void (&)(int, ...)>();
    test_is_not_nothrow_constructible<void (&)(int, ...) noexcept>();

    test_is_not_nothrow_constructible<int (&)()>();
    test_is_not_nothrow_constructible<int (&)() noexcept>();

    test_is_not_nothrow_constructible<int (&)(int)>();
    test_is_not_nothrow_constructible<int (&)(int) noexcept>();

    test_is_not_nothrow_constructible<int (&)(...)>();
    test_is_not_nothrow_constructible<int (&)(...) noexcept>();

    test_is_not_nothrow_constructible<int (&)(int, ...)>();
    test_is_not_nothrow_constructible<int (&)(int, ...) noexcept>();

    test_is_not_nothrow_constructible<void(&&)()>();
    test_is_not_nothrow_constructible<void(&&)() noexcept>();

    test_is_not_nothrow_constructible<void(&&)(int)>();
    test_is_not_nothrow_constructible<void(&&)(int) noexcept>();

    test_is_not_nothrow_constructible<void(&&)(...)>();
    test_is_not_nothrow_constructible<void(&&)(...) noexcept>();

    test_is_not_nothrow_constructible<void(&&)(int, ...)>();
    test_is_not_nothrow_constructible<void(&&)(int, ...) noexcept>();

    test_is_not_nothrow_constructible<int(&&)()>();
    test_is_not_nothrow_constructible<int(&&)() noexcept>();

    test_is_not_nothrow_constructible<int(&&)(int)>();
    test_is_not_nothrow_constructible<int(&&)(int) noexcept>();

    test_is_not_nothrow_constructible<int(&&)(...)>();
    test_is_not_nothrow_constructible<int(&&)(...) noexcept>();

    test_is_not_nothrow_constructible<int(&&)(int, ...)>();
    test_is_not_nothrow_constructible<int(&&)(int, ...) noexcept>();

    test_is_nothrow_constructible<void (Class::*)()>();
    test_is_nothrow_constructible<void (Class::*)()&>();
    test_is_nothrow_constructible<void (Class::*)() &&>();
    test_is_nothrow_constructible<void (Class::*)() const>();
    test_is_nothrow_constructible<void (Class::*)() const&>();
    test_is_nothrow_constructible<void (Class::*)() const&&>();
    test_is_nothrow_constructible<void (Class::*)() noexcept>();
    test_is_nothrow_constructible<void (Class::*)()& noexcept>();
    test_is_nothrow_constructible<void (Class::*)()&& noexcept>();
    test_is_nothrow_constructible<void (Class::*)() const noexcept>();
    test_is_nothrow_constructible<void (Class::*)() const& noexcept>();
    test_is_nothrow_constructible<void (Class::*)() const&& noexcept>();

    test_is_nothrow_constructible<void (Class::*)(int)>();
    test_is_nothrow_constructible<void (Class::*)(int)&>();
    test_is_nothrow_constructible<void (Class::*)(int) &&>();
    test_is_nothrow_constructible<void (Class::*)(int) const>();
    test_is_nothrow_constructible<void (Class::*)(int) const&>();
    test_is_nothrow_constructible<void (Class::*)(int) const&&>();
    test_is_nothrow_constructible<void (Class::*)(int) noexcept>();
    test_is_nothrow_constructible<void (Class::*)(int)& noexcept>();
    test_is_nothrow_constructible<void (Class::*)(int)&& noexcept>();
    test_is_nothrow_constructible<void (Class::*)(int) const noexcept>();
    test_is_nothrow_constructible<void (Class::*)(int) const& noexcept>();
    test_is_nothrow_constructible<void (Class::*)(int) const&& noexcept>();

    test_is_nothrow_constructible<void (Class::*)(...)>();
    test_is_nothrow_constructible<void (Class::*)(...)&>();
    test_is_nothrow_constructible<void (Class::*)(...) &&>();
    test_is_nothrow_constructible<void (Class::*)(...) const>();
    test_is_nothrow_constructible<void (Class::*)(...) const&>();
    test_is_nothrow_constructible<void (Class::*)(...) const&&>();
    test_is_nothrow_constructible<void (Class::*)(...) noexcept>();
    test_is_nothrow_constructible<void (Class::*)(...)& noexcept>();
    test_is_nothrow_constructible<void (Class::*)(...)&& noexcept>();
    test_is_nothrow_constructible<void (Class::*)(...) const noexcept>();
    test_is_nothrow_constructible<void (Class::*)(...) const& noexcept>();
    test_is_nothrow_constructible<void (Class::*)(...) const&& noexcept>();

    test_is_nothrow_constructible<void (Class::*)(int, ...)>();
    test_is_nothrow_constructible<void (Class::*)(int, ...)&>();
    test_is_nothrow_constructible<void (Class::*)(int, ...) &&>();
    test_is_nothrow_constructible<void (Class::*)(int, ...) const>();
    test_is_nothrow_constructible<void (Class::*)(int, ...) const&>();
    test_is_nothrow_constructible<void (Class::*)(int, ...) const&&>();
    test_is_nothrow_constructible<void (Class::*)(int, ...) noexcept>();
    test_is_nothrow_constructible<void (Class::*)(int, ...)& noexcept>();
    test_is_nothrow_constructible<void (Class::*)(int, ...)&& noexcept>();
    test_is_nothrow_constructible<void (Class::*)(int, ...) const noexcept>();
    test_is_nothrow_constructible<void (Class::*)(int, ...) const& noexcept>();
    test_is_nothrow_constructible<void (Class::*)(int, ...) const&& noexcept>();

    test_is_nothrow_constructible<int (Class::*)()>();
    test_is_nothrow_constructible<int (Class::*)()&>();
    test_is_nothrow_constructible<int (Class::*)() &&>();
    test_is_nothrow_constructible<int (Class::*)() const>();
    test_is_nothrow_constructible<int (Class::*)() const&>();
    test_is_nothrow_constructible<int (Class::*)() const&&>();
    test_is_nothrow_constructible<int (Class::*)() noexcept>();
    test_is_nothrow_constructible<int (Class::*)()& noexcept>();
    test_is_nothrow_constructible<int (Class::*)()&& noexcept>();
    test_is_nothrow_constructible<int (Class::*)() const noexcept>();
    test_is_nothrow_constructible<int (Class::*)() const& noexcept>();
    test_is_nothrow_constructible<int (Class::*)() const&& noexcept>();

    test_is_nothrow_constructible<int (Class::*)(int)>();
    test_is_nothrow_constructible<int (Class::*)(int)&>();
    test_is_nothrow_constructible<int (Class::*)(int) &&>();
    test_is_nothrow_constructible<int (Class::*)(int) const>();
    test_is_nothrow_constructible<int (Class::*)(int) const&>();
    test_is_nothrow_constructible<int (Class::*)(int) const&&>();
    test_is_nothrow_constructible<int (Class::*)(int) noexcept>();
    test_is_nothrow_constructible<int (Class::*)(int)& noexcept>();
    test_is_nothrow_constructible<int (Class::*)(int)&& noexcept>();
    test_is_nothrow_constructible<int (Class::*)(int) const noexcept>();
    test_is_nothrow_constructible<int (Class::*)(int) const& noexcept>();
    test_is_nothrow_constructible<int (Class::*)(int) const&& noexcept>();

    test_is_nothrow_constructible<int (Class::*)(...)>();
    test_is_nothrow_constructible<int (Class::*)(...)&>();
    test_is_nothrow_constructible<int (Class::*)(...) &&>();
    test_is_nothrow_constructible<int (Class::*)(...) const>();
    test_is_nothrow_constructible<int (Class::*)(...) const&>();
    test_is_nothrow_constructible<int (Class::*)(...) const&&>();
    test_is_nothrow_constructible<int (Class::*)(...) noexcept>();
    test_is_nothrow_constructible<int (Class::*)(...)& noexcept>();
    test_is_nothrow_constructible<int (Class::*)(...)&& noexcept>();
    test_is_nothrow_constructible<int (Class::*)(...) const noexcept>();
    test_is_nothrow_constructible<int (Class::*)(...) const& noexcept>();
    test_is_nothrow_constructible<int (Class::*)(...) const&& noexcept>();

    test_is_nothrow_constructible<int (Class::*)(int, ...)>();
    test_is_nothrow_constructible<int (Class::*)(int, ...)&>();
    test_is_nothrow_constructible<int (Class::*)(int, ...) &&>();
    test_is_nothrow_constructible<int (Class::*)(int, ...) const>();
    test_is_nothrow_constructible<int (Class::*)(int, ...) const&>();
    test_is_nothrow_constructible<int (Class::*)(int, ...) const&&>();
    test_is_nothrow_constructible<int (Class::*)(int, ...) noexcept>();
    test_is_nothrow_constructible<int (Class::*)(int, ...)& noexcept>();
    test_is_nothrow_constructible<int (Class::*)(int, ...)&& noexcept>();
    test_is_nothrow_constructible<int (Class::*)(int, ...) const noexcept>();
    test_is_nothrow_constructible<int (Class::*)(int, ...) const& noexcept>();
    test_is_nothrow_constructible<int (Class::*)(int, ...) const&& noexcept>();
}
