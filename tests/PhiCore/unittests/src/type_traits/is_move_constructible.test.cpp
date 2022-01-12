#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/compiler.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_move_constructible.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_move_constructible_impl()
{
    STATIC_REQUIRE(phi::is_move_constructible<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_move_constructible<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_move_constructible_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_move_constructible_v<T>);
#endif

    // Standard compatibililty
    STATIC_REQUIRE(std::is_move_constructible<T>::value);
}

template <typename T>
void test_is_not_move_constructible_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_move_constructible<T>::value);
    STATIC_REQUIRE(phi::is_not_move_constructible<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_move_constructible_v<T>);
    STATIC_REQUIRE(phi::is_not_move_constructible_v<T>);
#endif

    // Standard compatibililty
    STATIC_REQUIRE_FALSE(std::is_move_constructible<T>::value);
}

template <typename T>
void test_is_move_constructible()
{
    test_is_move_constructible_impl<T>();
    test_is_not_move_constructible_impl<const T>();
    test_is_not_move_constructible_impl<volatile T>();
    test_is_not_move_constructible_impl<const volatile T>();
}

template <typename T>
void test_is_move_constructible_c()
{
    test_is_move_constructible_impl<T>();
    test_is_not_move_constructible_impl<volatile T>();
    test_is_move_constructible_impl<const T>();
    test_is_not_move_constructible_impl<const volatile T>();
}

template <typename T>
void test_is_move_constructible_cv()
{
    test_is_move_constructible_impl<T>();
    test_is_move_constructible_impl<const T>();
    test_is_move_constructible_impl<volatile T>();
    test_is_move_constructible_impl<const volatile T>();
}

template <typename T>
void test_is_not_move_constructible_cv()
{
    test_is_not_move_constructible_impl<T>();
    test_is_not_move_constructible_impl<const T>();
    test_is_not_move_constructible_impl<volatile T>();
    test_is_not_move_constructible_impl<const volatile T>();
}

template <typename T>
void test_is_not_move_constructible_c()
{
    test_is_not_move_constructible_impl<T>();
    test_is_move_constructible_impl<const T>();
    test_is_not_move_constructible_impl<volatile T>();
    test_is_not_move_constructible_impl<const volatile T>();
}

struct A
{
    A(const A&);
};

struct B
{
    B(B&&);
};

struct C
{
    C() = delete;
};

struct D
{
    D(const D&) = delete;
};

struct E
{
    E(E&&) = delete;
};

struct F
{
    F& operator=(const F&) = delete;
};

struct G
{
    G& operator=(G&&) = delete;
};

struct H
{
    H() = default;

    H(const H&) = default;
    H(H&&)      = default;

    H& operator=(const H&) = default;
    H& operator=(H&&) = default;
};

TEST_CASE("is_move_constructible")
{
    test_is_move_constructible_c<A>();
    test_is_move_constructible<B>();
    test_is_move_constructible_c<C>();
    test_is_not_move_constructible_cv<D>();
    test_is_not_move_constructible_cv<E>();
    test_is_move_constructible_c<F>();
    test_is_not_move_constructible_cv<G>();
    test_is_move_constructible_c<H>();

    // Incomplete types only work with the intrinsic functions
#if PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_not_move_constructible_cv<void>();
#endif
    test_is_move_constructible_cv<phi::nullptr_t>();
    test_is_move_constructible_cv<bool>();
    test_is_move_constructible_cv<char>();
    test_is_move_constructible_cv<signed char>();
    test_is_move_constructible_cv<unsigned char>();
    test_is_move_constructible_cv<short>();
    test_is_move_constructible_cv<unsigned short>();
    test_is_move_constructible_cv<int>();
    test_is_move_constructible_cv<unsigned int>();
    test_is_move_constructible_cv<long>();
    test_is_move_constructible_cv<unsigned long>();
    test_is_move_constructible_cv<long long>();
    test_is_move_constructible_cv<unsigned long long>();
    test_is_move_constructible_cv<float>();
    test_is_move_constructible_cv<double>();
    test_is_move_constructible_cv<long double>();
    test_is_move_constructible_cv<char8_t>();
    test_is_move_constructible_cv<char16_t>();
    test_is_move_constructible_cv<char32_t>();
    test_is_move_constructible_cv<wchar_t>();

    test_is_move_constructible_c<phi::boolean>();
    test_is_move_constructible_c<phi::integer<signed char>>();
    test_is_move_constructible_c<phi::integer<unsigned char>>();
    test_is_move_constructible_c<phi::integer<short>>();
    test_is_move_constructible_c<phi::integer<unsigned short>>();
    test_is_move_constructible_c<phi::integer<int>>();
    test_is_move_constructible_c<phi::integer<unsigned int>>();
    test_is_move_constructible_c<phi::integer<long>>();
    test_is_move_constructible_c<phi::integer<unsigned long>>();
    test_is_move_constructible_c<phi::integer<long long>>();
    test_is_move_constructible_c<phi::integer<unsigned long long>>();
    test_is_move_constructible_c<phi::floating_point<float>>();
    test_is_move_constructible_c<phi::floating_point<double>>();
    test_is_move_constructible_c<phi::floating_point<long double>>();

    test_is_move_constructible_c<std::vector<int>>();
    test_is_move_constructible<phi::scope_ptr<int>>();

    test_is_move_constructible_cv<int&>();
    test_is_move_constructible_cv<const int&>();
    test_is_move_constructible_cv<volatile int&>();
    test_is_move_constructible_cv<const volatile int&>();
    test_is_move_constructible_cv<int&&>();
    test_is_move_constructible_cv<const int&&>();
    test_is_move_constructible_cv<volatile int&&>();
    test_is_move_constructible_cv<const volatile int&&>();
    test_is_move_constructible_cv<int*>();
    test_is_move_constructible_cv<const int*>();
    test_is_move_constructible_cv<volatile int*>();
    test_is_move_constructible_cv<const volatile int*>();
    test_is_move_constructible_cv<int**>();
    test_is_move_constructible_cv<const int**>();
    test_is_move_constructible_cv<volatile int**>();
    test_is_move_constructible_cv<const volatile int**>();
    test_is_move_constructible_cv<int*&>();
    test_is_move_constructible_cv<const int*&>();
    test_is_move_constructible_cv<volatile int*&>();
    test_is_move_constructible_cv<const volatile int*&>();
    test_is_move_constructible_cv<int*&&>();
    test_is_move_constructible_cv<const int*&&>();
    test_is_move_constructible_cv<volatile int*&&>();
    test_is_move_constructible_cv<const volatile int*&&>();
    test_is_move_constructible_cv<void*>();
    test_is_not_move_constructible_cv<char[3]>();
    test_is_not_move_constructible_cv<char* [3]>();
    test_is_move_constructible_cv<int(*)[3]>();
    test_is_move_constructible_cv<int(&)[3]>();
    test_is_move_constructible_cv<int(&&)[3]>();
    test_is_not_move_constructible_cv<char[3][2]>();
    test_is_not_move_constructible_cv<char* [3][2]>();
    test_is_move_constructible_cv<int(*)[3][2]>();
    test_is_move_constructible_cv<int(&)[3][2]>();
    test_is_move_constructible_cv<int(&&)[3][2]>();
#if PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_not_move_constructible_cv<char[]>();
    test_is_not_move_constructible_cv<char*[]>();
    test_is_move_constructible_cv<int(*)[]>();
    test_is_move_constructible_cv<int(&)[]>();
    test_is_move_constructible_cv<int(&&)[]>();
    test_is_not_move_constructible_cv<char[][2]>();
    test_is_not_move_constructible_cv<char*[][2]>();
    test_is_move_constructible_cv<int(*)[][2]>();
    test_is_move_constructible_cv<int(&)[][2]>();
    test_is_move_constructible_cv<int(&&)[][2]>();
#endif
    test_is_move_constructible_c<Class>();
    test_is_not_move_constructible_cv<Class[]>();
    test_is_not_move_constructible_cv<Class[2]>();
    test_is_move_constructible_c<Template<void>>();
    test_is_move_constructible_c<Template<int>>();
    test_is_move_constructible_c<Template<Class>>();
    test_is_move_constructible_c<Template<incomplete_type>>();
    test_is_move_constructible_c<VariadicTemplate<>>();
    test_is_move_constructible_c<VariadicTemplate<void>>();
    test_is_move_constructible_c<VariadicTemplate<int>>();
    test_is_move_constructible_c<VariadicTemplate<Class>>();
    test_is_move_constructible_c<VariadicTemplate<incomplete_type>>();
    test_is_move_constructible_c<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_move_constructible_c<PublicDerviedFromTemplate<Base>>();
    test_is_move_constructible_c<PublicDerviedFromTemplate<Derived>>();
    test_is_move_constructible_c<PublicDerviedFromTemplate<Class>>();
    test_is_move_constructible_c<PrivateDerviedFromTemplate<Base>>();
    test_is_move_constructible_c<PrivateDerviedFromTemplate<Derived>>();
    test_is_move_constructible_c<PrivateDerviedFromTemplate<Class>>();
    test_is_move_constructible_c<ProtectedDerviedFromTemplate<Base>>();
    test_is_move_constructible_c<ProtectedDerviedFromTemplate<Derived>>();
    test_is_move_constructible_c<ProtectedDerviedFromTemplate<Class>>();
    test_is_move_constructible_c<Union>();
    test_is_move_constructible_c<NonEmptyUnion>();
    test_is_move_constructible_c<Empty>();
    test_is_move_constructible_c<NotEmpty>();
    test_is_move_constructible_c<bit_zero>();
    test_is_move_constructible_c<bit_one>();
    test_is_move_constructible_c<Base>();
    test_is_move_constructible_c<Derived>();
    test_is_not_move_constructible_cv<Abstract>();
    test_is_not_move_constructible_cv<PublicAbstract>();
    test_is_not_move_constructible_cv<PrivateAbstract>();
    test_is_not_move_constructible_cv<ProtectedAbstract>();
#if !PHI_HAS_BUG_GCC_102305()
    // Test GCC bug 102305 (https://gcc.gnu.org/bugzilla/show_bug.cgi?id=102305)
    test_is_not_move_constructible_cv<AbstractTemplate<int>>();
#endif
    test_is_move_constructible_c<AbstractTemplate<double>>();
    test_is_not_move_constructible_cv<AbstractTemplate<Class>>();
    test_is_not_move_constructible_cv<AbstractTemplate<incomplete_type>>();
    test_is_move_constructible_c<Final>();
    test_is_move_constructible_c<PublicDestructor>();
    test_is_not_move_constructible_cv<ProtectedDestructor>();
    test_is_not_move_constructible_cv<PrivateDestructor>();
    test_is_move_constructible_c<VirtualPublicDestructor>();
    test_is_not_move_constructible_cv<VirtualProtectedDestructor>();
    test_is_not_move_constructible_cv<VirtualPrivateDestructor>();
    test_is_not_move_constructible_cv<PurePublicDestructor>();
    test_is_not_move_constructible_cv<PureProtectedDestructor>();
    test_is_not_move_constructible_cv<PurePrivateDestructor>();
    test_is_not_move_constructible_cv<DeletedPublicDestructor>();
    test_is_not_move_constructible_cv<DeletedProtectedDestructor>();
    test_is_not_move_constructible_cv<DeletedPrivateDestructor>();
    test_is_not_move_constructible_cv<DeletedVirtualPublicDestructor>();
    test_is_not_move_constructible_cv<DeletedVirtualProtectedDestructor>();
    test_is_not_move_constructible_cv<DeletedVirtualPrivateDestructor>();
    test_is_move_constructible_cv<Enum>();
    test_is_move_constructible_cv<EnumSigned>();
    test_is_move_constructible_cv<EnumUnsigned>();
    test_is_move_constructible_cv<EnumClass>();
    test_is_move_constructible_cv<EnumStruct>();
    test_is_not_move_constructible_cv<Function>();
    test_is_move_constructible_cv<FunctionPtr>();
    test_is_move_constructible_cv<MemberObjectPtr>();
    test_is_move_constructible_cv<MemberFunctionPtr>();
    test_is_move_constructible_cv<int Class::*>();
    test_is_move_constructible_cv<float Class::*>();
    test_is_move_constructible_cv<void * Class::*>();
    test_is_move_constructible_cv<int * Class::*>();
    test_is_move_constructible_cv<int Class::*&>();
    test_is_move_constructible_cv<float Class::*&>();
    test_is_move_constructible_cv<void * Class::*&>();
    test_is_move_constructible_cv<int * Class::*&>();
    test_is_move_constructible_cv<int Class::*&&>();
    test_is_move_constructible_cv<float Class::*&&>();
    test_is_move_constructible_cv<void * Class::*&&>();
    test_is_move_constructible_cv<int * Class::*&&>();
    test_is_move_constructible_cv<int Class::*const>();
    test_is_move_constructible_cv<float Class::*const>();
    test_is_move_constructible_cv<void * Class::*const>();
    test_is_move_constructible_cv<int Class::*const&>();
    test_is_move_constructible_cv<float Class::*const&>();
    test_is_move_constructible_cv<void * Class::*const&>();
    test_is_move_constructible_cv<int Class::*const&&>();
    test_is_move_constructible_cv<float Class::*const&&>();
    test_is_move_constructible_cv<void * Class::*const&&>();
    test_is_move_constructible_cv<int Class::*volatile>();
    test_is_move_constructible_cv<float Class::*volatile>();
    test_is_move_constructible_cv<void * Class::*volatile>();
    test_is_move_constructible_cv<int Class::*volatile&>();
    test_is_move_constructible_cv<float Class::*volatile&>();
    test_is_move_constructible_cv<void * Class::*volatile&>();
    test_is_move_constructible_cv<int Class::*volatile&&>();
    test_is_move_constructible_cv<float Class::*volatile&&>();
    test_is_move_constructible_cv<void * Class::*volatile&&>();
    test_is_move_constructible_cv<int Class::*const volatile>();
    test_is_move_constructible_cv<float Class::*const volatile>();
    test_is_move_constructible_cv<void * Class::*const volatile>();
    test_is_move_constructible_cv<int Class::*const volatile&>();
    test_is_move_constructible_cv<float Class::*const volatile&>();
    test_is_move_constructible_cv<void * Class::*const volatile&>();
    test_is_move_constructible_cv<int Class::*const volatile&&>();
    test_is_move_constructible_cv<float Class::*const volatile&&>();
    test_is_move_constructible_cv<void * Class::*const volatile&&>();
    test_is_move_constructible<NonCopyable>();
    test_is_not_move_constructible_c<NonMoveable>();
    test_is_not_move_constructible_cv<NonConstructible>();
    test_is_move_constructible_c<Tracked>();
    test_is_move_constructible_cv<TrapConstructible>();
    test_is_move_constructible_c<TrapImplicitConversion>();
    test_is_move_constructible_c<TrapComma>();
    test_is_move_constructible_c<TrapCall>();
    test_is_move_constructible_c<TrapSelfAssign>();
    test_is_move_constructible_c<TrapDeref>();
    test_is_move_constructible_c<TrapArraySubscript>();

    test_is_not_move_constructible_cv<void()>();
    test_is_not_move_constructible_cv<void()&>();
    test_is_not_move_constructible_cv<void() &&>();
    test_is_not_move_constructible_cv<void() const>();
    test_is_not_move_constructible_cv<void() const&>();
    test_is_not_move_constructible_cv<void() const&&>();
    test_is_not_move_constructible_cv<void() volatile>();
    test_is_not_move_constructible_cv<void() volatile&>();
    test_is_not_move_constructible_cv<void() volatile&&>();
    test_is_not_move_constructible_cv<void() const volatile>();
    test_is_not_move_constructible_cv<void() const volatile&>();
    test_is_not_move_constructible_cv<void() const volatile&&>();
    test_is_not_move_constructible_cv<void() noexcept>();
    test_is_not_move_constructible_cv<void()& noexcept>();
    test_is_not_move_constructible_cv<void()&& noexcept>();
    test_is_not_move_constructible_cv<void() const noexcept>();
    test_is_not_move_constructible_cv<void() const& noexcept>();
    test_is_not_move_constructible_cv<void() const&& noexcept>();
    test_is_not_move_constructible_cv<void() volatile noexcept>();
    test_is_not_move_constructible_cv<void() volatile& noexcept>();
    test_is_not_move_constructible_cv<void() volatile&& noexcept>();
    test_is_not_move_constructible_cv<void() const volatile noexcept>();
    test_is_not_move_constructible_cv<void() const volatile& noexcept>();
    test_is_not_move_constructible_cv<void() const volatile&& noexcept>();

    test_is_not_move_constructible_cv<void(int)>();
    test_is_not_move_constructible_cv<void(int)&>();
    test_is_not_move_constructible_cv<void(int) &&>();
    test_is_not_move_constructible_cv<void(int) const>();
    test_is_not_move_constructible_cv<void(int) const&>();
    test_is_not_move_constructible_cv<void(int) const&&>();
    test_is_not_move_constructible_cv<void(int) volatile>();
    test_is_not_move_constructible_cv<void(int) volatile&>();
    test_is_not_move_constructible_cv<void(int) volatile&&>();
    test_is_not_move_constructible_cv<void(int) const volatile>();
    test_is_not_move_constructible_cv<void(int) const volatile&>();
    test_is_not_move_constructible_cv<void(int) const volatile&&>();
    test_is_not_move_constructible_cv<void(int) noexcept>();
    test_is_not_move_constructible_cv<void(int)& noexcept>();
    test_is_not_move_constructible_cv<void(int)&& noexcept>();
    test_is_not_move_constructible_cv<void(int) const noexcept>();
    test_is_not_move_constructible_cv<void(int) const& noexcept>();
    test_is_not_move_constructible_cv<void(int) const&& noexcept>();
    test_is_not_move_constructible_cv<void(int) volatile noexcept>();
    test_is_not_move_constructible_cv<void(int) volatile& noexcept>();
    test_is_not_move_constructible_cv<void(int) volatile&& noexcept>();
    test_is_not_move_constructible_cv<void(int) const volatile noexcept>();
    test_is_not_move_constructible_cv<void(int) const volatile& noexcept>();
    test_is_not_move_constructible_cv<void(int) const volatile&& noexcept>();

    test_is_not_move_constructible_cv<void(...)>();
    test_is_not_move_constructible_cv<void(...)&>();
    test_is_not_move_constructible_cv<void(...) &&>();
    test_is_not_move_constructible_cv<void(...) const>();
    test_is_not_move_constructible_cv<void(...) const&>();
    test_is_not_move_constructible_cv<void(...) const&&>();
    test_is_not_move_constructible_cv<void(...) volatile>();
    test_is_not_move_constructible_cv<void(...) volatile&>();
    test_is_not_move_constructible_cv<void(...) volatile&&>();
    test_is_not_move_constructible_cv<void(...) const volatile>();
    test_is_not_move_constructible_cv<void(...) const volatile&>();
    test_is_not_move_constructible_cv<void(...) const volatile&&>();
    test_is_not_move_constructible_cv<void(...) noexcept>();
    test_is_not_move_constructible_cv<void(...)& noexcept>();
    test_is_not_move_constructible_cv<void(...)&& noexcept>();
    test_is_not_move_constructible_cv<void(...) const noexcept>();
    test_is_not_move_constructible_cv<void(...) const& noexcept>();
    test_is_not_move_constructible_cv<void(...) const&& noexcept>();
    test_is_not_move_constructible_cv<void(...) volatile noexcept>();
    test_is_not_move_constructible_cv<void(...) volatile& noexcept>();
    test_is_not_move_constructible_cv<void(...) volatile&& noexcept>();
    test_is_not_move_constructible_cv<void(...) const volatile noexcept>();
    test_is_not_move_constructible_cv<void(...) const volatile& noexcept>();
    test_is_not_move_constructible_cv<void(...) const volatile&& noexcept>();

    test_is_not_move_constructible_cv<void(int, ...)>();
    test_is_not_move_constructible_cv<void(int, ...)&>();
    test_is_not_move_constructible_cv<void(int, ...) &&>();
    test_is_not_move_constructible_cv<void(int, ...) const>();
    test_is_not_move_constructible_cv<void(int, ...) const&>();
    test_is_not_move_constructible_cv<void(int, ...) const&&>();
    test_is_not_move_constructible_cv<void(int, ...) volatile>();
    test_is_not_move_constructible_cv<void(int, ...) volatile&>();
    test_is_not_move_constructible_cv<void(int, ...) volatile&&>();
    test_is_not_move_constructible_cv<void(int, ...) const volatile>();
    test_is_not_move_constructible_cv<void(int, ...) const volatile&>();
    test_is_not_move_constructible_cv<void(int, ...) const volatile&&>();
    test_is_not_move_constructible_cv<void(int, ...) noexcept>();
    test_is_not_move_constructible_cv<void(int, ...)& noexcept>();
    test_is_not_move_constructible_cv<void(int, ...)&& noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) const noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) const& noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) const&& noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) volatile noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) volatile& noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) volatile&& noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) const volatile noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) const volatile& noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) const volatile&& noexcept>();

    test_is_not_move_constructible_cv<int()>();
    test_is_not_move_constructible_cv<int()&>();
    test_is_not_move_constructible_cv<int() &&>();
    test_is_not_move_constructible_cv<int() const>();
    test_is_not_move_constructible_cv<int() const&>();
    test_is_not_move_constructible_cv<int() const&&>();
    test_is_not_move_constructible_cv<int() volatile>();
    test_is_not_move_constructible_cv<int() volatile&>();
    test_is_not_move_constructible_cv<int() volatile&&>();
    test_is_not_move_constructible_cv<int() const volatile>();
    test_is_not_move_constructible_cv<int() const volatile&>();
    test_is_not_move_constructible_cv<int() const volatile&&>();
    test_is_not_move_constructible_cv<int() noexcept>();
    test_is_not_move_constructible_cv<int()& noexcept>();
    test_is_not_move_constructible_cv<int()&& noexcept>();
    test_is_not_move_constructible_cv<int() const noexcept>();
    test_is_not_move_constructible_cv<int() const& noexcept>();
    test_is_not_move_constructible_cv<int() const&& noexcept>();
    test_is_not_move_constructible_cv<int() volatile noexcept>();
    test_is_not_move_constructible_cv<int() volatile& noexcept>();
    test_is_not_move_constructible_cv<int() volatile&& noexcept>();
    test_is_not_move_constructible_cv<int() const volatile noexcept>();
    test_is_not_move_constructible_cv<int() const volatile& noexcept>();
    test_is_not_move_constructible_cv<int() const volatile&& noexcept>();

    test_is_not_move_constructible_cv<int(int)>();
    test_is_not_move_constructible_cv<int(int)&>();
    test_is_not_move_constructible_cv<int(int) &&>();
    test_is_not_move_constructible_cv<int(int) const>();
    test_is_not_move_constructible_cv<int(int) const&>();
    test_is_not_move_constructible_cv<int(int) const&&>();
    test_is_not_move_constructible_cv<int(int) volatile>();
    test_is_not_move_constructible_cv<int(int) volatile&>();
    test_is_not_move_constructible_cv<int(int) volatile&&>();
    test_is_not_move_constructible_cv<int(int) const volatile>();
    test_is_not_move_constructible_cv<int(int) const volatile&>();
    test_is_not_move_constructible_cv<int(int) const volatile&&>();
    test_is_not_move_constructible_cv<int(int) noexcept>();
    test_is_not_move_constructible_cv<int(int)& noexcept>();
    test_is_not_move_constructible_cv<int(int)&& noexcept>();
    test_is_not_move_constructible_cv<int(int) const noexcept>();
    test_is_not_move_constructible_cv<int(int) const& noexcept>();
    test_is_not_move_constructible_cv<int(int) const&& noexcept>();
    test_is_not_move_constructible_cv<int(int) volatile noexcept>();
    test_is_not_move_constructible_cv<int(int) volatile& noexcept>();
    test_is_not_move_constructible_cv<int(int) volatile&& noexcept>();
    test_is_not_move_constructible_cv<int(int) const volatile noexcept>();
    test_is_not_move_constructible_cv<int(int) const volatile& noexcept>();
    test_is_not_move_constructible_cv<int(int) const volatile&& noexcept>();

    test_is_not_move_constructible_cv<int(...)>();
    test_is_not_move_constructible_cv<int(...)&>();
    test_is_not_move_constructible_cv<int(...) &&>();
    test_is_not_move_constructible_cv<int(...) const>();
    test_is_not_move_constructible_cv<int(...) const&>();
    test_is_not_move_constructible_cv<int(...) const&&>();
    test_is_not_move_constructible_cv<int(...) volatile>();
    test_is_not_move_constructible_cv<int(...) volatile&>();
    test_is_not_move_constructible_cv<int(...) volatile&&>();
    test_is_not_move_constructible_cv<int(...) const volatile>();
    test_is_not_move_constructible_cv<int(...) const volatile&>();
    test_is_not_move_constructible_cv<int(...) const volatile&&>();
    test_is_not_move_constructible_cv<int(...) noexcept>();
    test_is_not_move_constructible_cv<int(...)& noexcept>();
    test_is_not_move_constructible_cv<int(...)&& noexcept>();
    test_is_not_move_constructible_cv<int(...) const noexcept>();
    test_is_not_move_constructible_cv<int(...) const& noexcept>();
    test_is_not_move_constructible_cv<int(...) const&& noexcept>();
    test_is_not_move_constructible_cv<int(...) volatile noexcept>();
    test_is_not_move_constructible_cv<int(...) volatile& noexcept>();
    test_is_not_move_constructible_cv<int(...) volatile&& noexcept>();
    test_is_not_move_constructible_cv<int(...) const volatile noexcept>();
    test_is_not_move_constructible_cv<int(...) const volatile& noexcept>();
    test_is_not_move_constructible_cv<int(...) const volatile&& noexcept>();

    test_is_not_move_constructible_cv<int(int, ...)>();
    test_is_not_move_constructible_cv<int(int, ...)&>();
    test_is_not_move_constructible_cv<int(int, ...) &&>();
    test_is_not_move_constructible_cv<int(int, ...) const>();
    test_is_not_move_constructible_cv<int(int, ...) const&>();
    test_is_not_move_constructible_cv<int(int, ...) const&&>();
    test_is_not_move_constructible_cv<int(int, ...) volatile>();
    test_is_not_move_constructible_cv<int(int, ...) volatile&>();
    test_is_not_move_constructible_cv<int(int, ...) volatile&&>();
    test_is_not_move_constructible_cv<int(int, ...) const volatile>();
    test_is_not_move_constructible_cv<int(int, ...) const volatile&>();
    test_is_not_move_constructible_cv<int(int, ...) const volatile&&>();
    test_is_not_move_constructible_cv<int(int, ...) noexcept>();
    test_is_not_move_constructible_cv<int(int, ...)& noexcept>();
    test_is_not_move_constructible_cv<int(int, ...)&& noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) const noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) const& noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) const&& noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) volatile noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) volatile& noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) volatile&& noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) const volatile noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) const volatile& noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) const volatile&& noexcept>();

    test_is_move_constructible_cv<void (*)()>();
    test_is_move_constructible_cv<void (*)() noexcept>();

    test_is_move_constructible_cv<void (*)(int)>();
    test_is_move_constructible_cv<void (*)(int) noexcept>();

    test_is_move_constructible_cv<void (*)(...)>();
    test_is_move_constructible_cv<void (*)(...) noexcept>();

    test_is_move_constructible_cv<void (*)(int, ...)>();
    test_is_move_constructible_cv<void (*)(int, ...) noexcept>();

    test_is_move_constructible_cv<int (*)()>();
    test_is_move_constructible_cv<int (*)() noexcept>();

    test_is_move_constructible_cv<int (*)(int)>();
    test_is_move_constructible_cv<int (*)(int) noexcept>();

    test_is_move_constructible_cv<int (*)(...)>();
    test_is_move_constructible_cv<int (*)(...) noexcept>();

    test_is_move_constructible_cv<int (*)(int, ...)>();
    test_is_move_constructible_cv<int (*)(int, ...) noexcept>();

    test_is_move_constructible_cv<void (&)()>();
    test_is_move_constructible_cv<void (&)() noexcept>();

    test_is_move_constructible_cv<void (&)(int)>();
    test_is_move_constructible_cv<void (&)(int) noexcept>();

    test_is_move_constructible_cv<void (&)(...)>();
    test_is_move_constructible_cv<void (&)(...) noexcept>();

    test_is_move_constructible_cv<void (&)(int, ...)>();
    test_is_move_constructible_cv<void (&)(int, ...) noexcept>();

    test_is_move_constructible_cv<int (&)()>();
    test_is_move_constructible_cv<int (&)() noexcept>();

    test_is_move_constructible_cv<int (&)(int)>();
    test_is_move_constructible_cv<int (&)(int) noexcept>();

    test_is_move_constructible_cv<int (&)(...)>();
    test_is_move_constructible_cv<int (&)(...) noexcept>();

    test_is_move_constructible_cv<int (&)(int, ...)>();
    test_is_move_constructible_cv<int (&)(int, ...) noexcept>();

    test_is_move_constructible_cv<void(&&)()>();
    test_is_move_constructible_cv<void(&&)() noexcept>();

    test_is_move_constructible_cv<void(&&)(int)>();
    test_is_move_constructible_cv<void(&&)(int) noexcept>();

    test_is_move_constructible_cv<void(&&)(...)>();
    test_is_move_constructible_cv<void(&&)(...) noexcept>();

    test_is_move_constructible_cv<void(&&)(int, ...)>();
    test_is_move_constructible_cv<void(&&)(int, ...) noexcept>();

    test_is_move_constructible_cv<int(&&)()>();
    test_is_move_constructible_cv<int(&&)() noexcept>();

    test_is_move_constructible_cv<int(&&)(int)>();
    test_is_move_constructible_cv<int(&&)(int) noexcept>();

    test_is_move_constructible_cv<int(&&)(...)>();
    test_is_move_constructible_cv<int(&&)(...) noexcept>();

    test_is_move_constructible_cv<int(&&)(int, ...)>();
    test_is_move_constructible_cv<int(&&)(int, ...) noexcept>();

    test_is_move_constructible_cv<void (Class::*)()>();
    test_is_move_constructible_cv<void (Class::*)()&>();
    test_is_move_constructible_cv<void (Class::*)() &&>();
    test_is_move_constructible_cv<void (Class::*)() const>();
    test_is_move_constructible_cv<void (Class::*)() const&>();
    test_is_move_constructible_cv<void (Class::*)() const&&>();
    test_is_move_constructible_cv<void (Class::*)() noexcept>();
    test_is_move_constructible_cv<void (Class::*)()& noexcept>();
    test_is_move_constructible_cv<void (Class::*)()&& noexcept>();
    test_is_move_constructible_cv<void (Class::*)() const noexcept>();
    test_is_move_constructible_cv<void (Class::*)() const& noexcept>();
    test_is_move_constructible_cv<void (Class::*)() const&& noexcept>();

    test_is_move_constructible_cv<void (Class::*)(int)>();
    test_is_move_constructible_cv<void (Class::*)(int)&>();
    test_is_move_constructible_cv<void (Class::*)(int) &&>();
    test_is_move_constructible_cv<void (Class::*)(int) const>();
    test_is_move_constructible_cv<void (Class::*)(int) const&>();
    test_is_move_constructible_cv<void (Class::*)(int) const&&>();
    test_is_move_constructible_cv<void (Class::*)(int) noexcept>();
    test_is_move_constructible_cv<void (Class::*)(int)& noexcept>();
    test_is_move_constructible_cv<void (Class::*)(int)&& noexcept>();
    test_is_move_constructible_cv<void (Class::*)(int) const noexcept>();
    test_is_move_constructible_cv<void (Class::*)(int) const& noexcept>();
    test_is_move_constructible_cv<void (Class::*)(int) const&& noexcept>();

    test_is_move_constructible_cv<void (Class::*)(...)>();
    test_is_move_constructible_cv<void (Class::*)(...)&>();
    test_is_move_constructible_cv<void (Class::*)(...) &&>();
    test_is_move_constructible_cv<void (Class::*)(...) const>();
    test_is_move_constructible_cv<void (Class::*)(...) const&>();
    test_is_move_constructible_cv<void (Class::*)(...) const&&>();
    test_is_move_constructible_cv<void (Class::*)(...) noexcept>();
    test_is_move_constructible_cv<void (Class::*)(...)& noexcept>();
    test_is_move_constructible_cv<void (Class::*)(...)&& noexcept>();
    test_is_move_constructible_cv<void (Class::*)(...) const noexcept>();
    test_is_move_constructible_cv<void (Class::*)(...) const& noexcept>();
    test_is_move_constructible_cv<void (Class::*)(...) const&& noexcept>();

    test_is_move_constructible_cv<void (Class::*)(int, ...)>();
    test_is_move_constructible_cv<void (Class::*)(int, ...)&>();
    test_is_move_constructible_cv<void (Class::*)(int, ...) &&>();
    test_is_move_constructible_cv<void (Class::*)(int, ...) const>();
    test_is_move_constructible_cv<void (Class::*)(int, ...) const&>();
    test_is_move_constructible_cv<void (Class::*)(int, ...) const&&>();
    test_is_move_constructible_cv<void (Class::*)(int, ...) noexcept>();
    test_is_move_constructible_cv<void (Class::*)(int, ...)& noexcept>();
    test_is_move_constructible_cv<void (Class::*)(int, ...)&& noexcept>();
    test_is_move_constructible_cv<void (Class::*)(int, ...) const noexcept>();
    test_is_move_constructible_cv<void (Class::*)(int, ...) const& noexcept>();
    test_is_move_constructible_cv<void (Class::*)(int, ...) const&& noexcept>();

    test_is_move_constructible_cv<int (Class::*)()>();
    test_is_move_constructible_cv<int (Class::*)()&>();
    test_is_move_constructible_cv<int (Class::*)() &&>();
    test_is_move_constructible_cv<int (Class::*)() const>();
    test_is_move_constructible_cv<int (Class::*)() const&>();
    test_is_move_constructible_cv<int (Class::*)() const&&>();
    test_is_move_constructible_cv<int (Class::*)() noexcept>();
    test_is_move_constructible_cv<int (Class::*)()& noexcept>();
    test_is_move_constructible_cv<int (Class::*)()&& noexcept>();
    test_is_move_constructible_cv<int (Class::*)() const noexcept>();
    test_is_move_constructible_cv<int (Class::*)() const& noexcept>();
    test_is_move_constructible_cv<int (Class::*)() const&& noexcept>();

    test_is_move_constructible_cv<int (Class::*)(int)>();
    test_is_move_constructible_cv<int (Class::*)(int)&>();
    test_is_move_constructible_cv<int (Class::*)(int) &&>();
    test_is_move_constructible_cv<int (Class::*)(int) const>();
    test_is_move_constructible_cv<int (Class::*)(int) const&>();
    test_is_move_constructible_cv<int (Class::*)(int) const&&>();
    test_is_move_constructible_cv<int (Class::*)(int) noexcept>();
    test_is_move_constructible_cv<int (Class::*)(int)& noexcept>();
    test_is_move_constructible_cv<int (Class::*)(int)&& noexcept>();
    test_is_move_constructible_cv<int (Class::*)(int) const noexcept>();
    test_is_move_constructible_cv<int (Class::*)(int) const& noexcept>();
    test_is_move_constructible_cv<int (Class::*)(int) const&& noexcept>();

    test_is_move_constructible_cv<int (Class::*)(...)>();
    test_is_move_constructible_cv<int (Class::*)(...)&>();
    test_is_move_constructible_cv<int (Class::*)(...) &&>();
    test_is_move_constructible_cv<int (Class::*)(...) const>();
    test_is_move_constructible_cv<int (Class::*)(...) const&>();
    test_is_move_constructible_cv<int (Class::*)(...) const&&>();
    test_is_move_constructible_cv<int (Class::*)(...) noexcept>();
    test_is_move_constructible_cv<int (Class::*)(...)& noexcept>();
    test_is_move_constructible_cv<int (Class::*)(...)&& noexcept>();
    test_is_move_constructible_cv<int (Class::*)(...) const noexcept>();
    test_is_move_constructible_cv<int (Class::*)(...) const& noexcept>();
    test_is_move_constructible_cv<int (Class::*)(...) const&& noexcept>();

    test_is_move_constructible_cv<int (Class::*)(int, ...)>();
    test_is_move_constructible_cv<int (Class::*)(int, ...)&>();
    test_is_move_constructible_cv<int (Class::*)(int, ...) &&>();
    test_is_move_constructible_cv<int (Class::*)(int, ...) const>();
    test_is_move_constructible_cv<int (Class::*)(int, ...) const&>();
    test_is_move_constructible_cv<int (Class::*)(int, ...) const&&>();
    test_is_move_constructible_cv<int (Class::*)(int, ...) noexcept>();
    test_is_move_constructible_cv<int (Class::*)(int, ...)& noexcept>();
    test_is_move_constructible_cv<int (Class::*)(int, ...)&& noexcept>();
    test_is_move_constructible_cv<int (Class::*)(int, ...) const noexcept>();
    test_is_move_constructible_cv<int (Class::*)(int, ...) const& noexcept>();
    test_is_move_constructible_cv<int (Class::*)(int, ...) const&& noexcept>();
}
