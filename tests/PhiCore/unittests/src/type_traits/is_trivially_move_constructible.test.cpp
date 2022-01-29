#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_move_constructible.hpp>
#include <phi/type_traits/is_trivially_move_constructible.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_trivially_move_constructible_impl()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_trivially_move_constructible<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_move_constructible<T>::value);
    STATIC_REQUIRE(phi::is_move_constructible<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_move_constructible_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_move_constructible_v<T>);
    STATIC_REQUIRE(phi::is_move_constructible_v<T>);
#    endif

    // Standard compatibililty
    STATIC_REQUIRE(std::is_trivially_move_constructible<T>::value);
    STATIC_REQUIRE(std::is_move_constructible<T>::value);
#endif
}

template <typename T>
void test_is_not_trivially_move_constructible_impl()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_move_constructible<T>::value);
    STATIC_REQUIRE(phi::is_not_trivially_move_constructible<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_move_constructible_v<T>);
    STATIC_REQUIRE(phi::is_not_trivially_move_constructible_v<T>);
#    endif

    // Standard compatibililty
    STATIC_REQUIRE_FALSE(std::is_trivially_move_constructible<T>::value);
#endif
}

template <typename T>
void test_is_trivially_move_constructible()
{
    test_is_trivially_move_constructible_impl<T>();
    test_is_not_trivially_move_constructible_impl<const T>();
    test_is_not_trivially_move_constructible_impl<volatile T>();
    test_is_not_trivially_move_constructible_impl<const volatile T>();
}

template <typename T>
void test_is_trivially_move_constructible_c()
{
    test_is_trivially_move_constructible_impl<T>();
    test_is_trivially_move_constructible_impl<const T>();
    test_is_not_trivially_move_constructible_impl<volatile T>();
    test_is_not_trivially_move_constructible_impl<const volatile T>();
}

template <typename T>
void test_is_trivially_move_constructible_only_c()
{
    test_is_not_trivially_move_constructible_impl<T>();
    test_is_trivially_move_constructible_impl<const T>();
    test_is_not_trivially_move_constructible_impl<volatile T>();
    test_is_not_trivially_move_constructible_impl<const volatile T>();
}

template <typename T>
void test_is_trivially_move_constructible_cv()
{
    test_is_trivially_move_constructible_impl<T>();
    test_is_trivially_move_constructible_impl<const T>();
    test_is_trivially_move_constructible_impl<volatile T>();
    test_is_trivially_move_constructible_impl<const volatile T>();
}

template <typename T>
void test_is_not_trivially_move_constructible()
{
    test_is_not_trivially_move_constructible_impl<T>();
    test_is_not_trivially_move_constructible_impl<const T>();
    test_is_not_trivially_move_constructible_impl<volatile T>();
    test_is_not_trivially_move_constructible_impl<const volatile T>();
}

struct A
{
    A(const A&);
};

struct MoveOnly1
{
    MoveOnly1(MoveOnly1&&);
};

struct MoveOnly2
{
    MoveOnly2(MoveOnly2&&) = default;
};

struct B
{
    B(const B&) = default;
};

struct C
{
    C(const C&) = delete;
};

TEST_CASE("is_trivially_move_constructible")
{
    test_is_not_trivially_move_constructible<A>();
    test_is_not_trivially_move_constructible<MoveOnly1>();
    test_is_trivially_move_constructible<MoveOnly2>();
    test_is_trivially_move_constructible_c<B>();
    test_is_not_trivially_move_constructible<C>();

    test_is_not_trivially_move_constructible<void>();
    test_is_trivially_move_constructible_cv<phi::nullptr_t>();
    test_is_trivially_move_constructible_cv<bool>();
    test_is_trivially_move_constructible_cv<char>();
    test_is_trivially_move_constructible_cv<signed char>();
    test_is_trivially_move_constructible_cv<unsigned char>();
    test_is_trivially_move_constructible_cv<short>();
    test_is_trivially_move_constructible_cv<unsigned short>();
    test_is_trivially_move_constructible_cv<int>();
    test_is_trivially_move_constructible_cv<unsigned int>();
    test_is_trivially_move_constructible_cv<long>();
    test_is_trivially_move_constructible_cv<unsigned long>();
    test_is_trivially_move_constructible_cv<long long>();
    test_is_trivially_move_constructible_cv<unsigned long long>();
    test_is_trivially_move_constructible_cv<float>();
    test_is_trivially_move_constructible_cv<double>();
    test_is_trivially_move_constructible_cv<long double>();
    test_is_trivially_move_constructible_cv<char8_t>();
    test_is_trivially_move_constructible_cv<char16_t>();
    test_is_trivially_move_constructible_cv<char32_t>();
    test_is_trivially_move_constructible_cv<wchar_t>();

    test_is_trivially_move_constructible_c<phi::boolean>();
    test_is_trivially_move_constructible_c<phi::integer<signed char>>();
    test_is_trivially_move_constructible_c<phi::integer<unsigned char>>();
    test_is_trivially_move_constructible_c<phi::integer<short>>();
    test_is_trivially_move_constructible_c<phi::integer<unsigned short>>();
    test_is_trivially_move_constructible_c<phi::integer<int>>();
    test_is_trivially_move_constructible_c<phi::integer<unsigned int>>();
    test_is_trivially_move_constructible_c<phi::integer<long>>();
    test_is_trivially_move_constructible_c<phi::integer<unsigned long>>();
    test_is_trivially_move_constructible_c<phi::integer<long long>>();
    test_is_trivially_move_constructible_c<phi::integer<unsigned long long>>();
    test_is_trivially_move_constructible_c<phi::floating_point<float>>();
    test_is_trivially_move_constructible_c<phi::floating_point<double>>();
    test_is_trivially_move_constructible_c<phi::floating_point<long double>>();

    test_is_not_trivially_move_constructible<std::vector<int>>();
    test_is_not_trivially_move_constructible<phi::scope_ptr<int>>();

    test_is_trivially_move_constructible_cv<int&>();
    test_is_trivially_move_constructible_cv<const int&>();
    test_is_trivially_move_constructible_cv<volatile int&>();
    test_is_trivially_move_constructible_cv<const volatile int&>();
    test_is_trivially_move_constructible_cv<int&&>();
    test_is_trivially_move_constructible_cv<const int&&>();
    test_is_trivially_move_constructible_cv<volatile int&&>();
    test_is_trivially_move_constructible_cv<const volatile int&&>();
    test_is_trivially_move_constructible_cv<int*>();
    test_is_trivially_move_constructible_cv<const int*>();
    test_is_trivially_move_constructible_cv<volatile int*>();
    test_is_trivially_move_constructible_cv<const volatile int*>();
    test_is_trivially_move_constructible_cv<int**>();
    test_is_trivially_move_constructible_cv<const int**>();
    test_is_trivially_move_constructible_cv<volatile int**>();
    test_is_trivially_move_constructible_cv<const volatile int**>();
    test_is_trivially_move_constructible_cv<int*&>();
    test_is_trivially_move_constructible_cv<const int*&>();
    test_is_trivially_move_constructible_cv<volatile int*&>();
    test_is_trivially_move_constructible_cv<const volatile int*&>();
    test_is_trivially_move_constructible_cv<int*&&>();
    test_is_trivially_move_constructible_cv<const int*&&>();
    test_is_trivially_move_constructible_cv<volatile int*&&>();
    test_is_trivially_move_constructible_cv<const volatile int*&&>();
    test_is_trivially_move_constructible_cv<void*>();
    test_is_not_trivially_move_constructible<char[3]>();
    test_is_not_trivially_move_constructible<char[]>();
    test_is_not_trivially_move_constructible<char* [3]>();
    test_is_not_trivially_move_constructible<char*[]>();
    test_is_trivially_move_constructible_cv<int(*)[3]>();
    test_is_trivially_move_constructible_cv<int(*)[]>();
    test_is_trivially_move_constructible_cv<int(&)[3]>();
    test_is_trivially_move_constructible_cv<int(&)[]>();
    test_is_trivially_move_constructible_cv<int(&&)[3]>();
    test_is_trivially_move_constructible_cv<int(&&)[]>();
    test_is_not_trivially_move_constructible<char[3][2]>();
    test_is_not_trivially_move_constructible<char[][2]>();
    test_is_not_trivially_move_constructible<char* [3][2]>();
    test_is_not_trivially_move_constructible<char*[][2]>();
    test_is_trivially_move_constructible_cv<int(*)[3][2]>();
    test_is_trivially_move_constructible_cv<int(*)[][2]>();
    test_is_trivially_move_constructible_cv<int(&)[3][2]>();
    test_is_trivially_move_constructible_cv<int(&)[][2]>();
    test_is_trivially_move_constructible_cv<int(&&)[3][2]>();
    test_is_trivially_move_constructible_cv<int(&&)[][2]>();
    test_is_not_trivially_move_constructible<Class>();
    test_is_not_trivially_move_constructible<Class[]>();
    test_is_not_trivially_move_constructible<Class[2]>();
    test_is_trivially_move_constructible_c<Template<void>>();
    test_is_trivially_move_constructible_c<Template<int>>();
    test_is_trivially_move_constructible_c<Template<Class>>();
    test_is_trivially_move_constructible_c<Template<IncompleteType>>();
    test_is_trivially_move_constructible_c<VariadicTemplate<>>();
    test_is_trivially_move_constructible_c<VariadicTemplate<void>>();
    test_is_trivially_move_constructible_c<VariadicTemplate<int>>();
    test_is_trivially_move_constructible_c<VariadicTemplate<Class>>();
    test_is_trivially_move_constructible_c<VariadicTemplate<IncompleteType>>();
    test_is_trivially_move_constructible_c<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_trivially_move_constructible_c<PublicDerivedFromTemplate<Base>>();
    test_is_trivially_move_constructible_c<PublicDerivedFromTemplate<Derived>>();
    test_is_not_trivially_move_constructible<PublicDerivedFromTemplate<Class>>();
    test_is_trivially_move_constructible_c<PrivateDerivedFromTemplate<Base>>();
    test_is_trivially_move_constructible_c<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_trivially_move_constructible<PrivateDerivedFromTemplate<Class>>();
    test_is_trivially_move_constructible_c<ProtectedDerivedFromTemplate<Base>>();
    test_is_trivially_move_constructible_c<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_trivially_move_constructible<ProtectedDerivedFromTemplate<Class>>();
    test_is_trivially_move_constructible_c<Union>();
    test_is_trivially_move_constructible_c<NonEmptyUnion>();
    test_is_trivially_move_constructible_c<Empty>();
    test_is_not_trivially_move_constructible<NotEmpty>();
    test_is_trivially_move_constructible_c<BitZero>();
    test_is_trivially_move_constructible_c<BitOne>();
    test_is_trivially_move_constructible_c<Base>();
    test_is_trivially_move_constructible_c<Derived>();
    test_is_not_trivially_move_constructible<Abstract>();
    test_is_not_trivially_move_constructible<PublicAbstract>();
    test_is_not_trivially_move_constructible<PrivateAbstract>();
    test_is_not_trivially_move_constructible<ProtectedAbstract>();
    test_is_not_trivially_move_constructible<AbstractTemplate<int>>();
    test_is_trivially_move_constructible_c<AbstractTemplate<double>>();
    test_is_not_trivially_move_constructible<AbstractTemplate<Class>>();
    test_is_not_trivially_move_constructible<AbstractTemplate<IncompleteType>>();
    test_is_trivially_move_constructible_c<Final>();
    test_is_trivially_move_constructible_c<PublicDestructor>();
    test_is_not_trivially_move_constructible<ProtectedDestructor>();
    test_is_not_trivially_move_constructible<PrivateDestructor>();
    test_is_not_trivially_move_constructible<VirtualPublicDestructor>();
    test_is_not_trivially_move_constructible<VirtualProtectedDestructor>();
    test_is_not_trivially_move_constructible<VirtualPrivateDestructor>();
    test_is_not_trivially_move_constructible<PurePublicDestructor>();
    test_is_not_trivially_move_constructible<PureProtectedDestructor>();
    test_is_not_trivially_move_constructible<PurePrivateDestructor>();
    test_is_not_trivially_move_constructible<DeletedPublicDestructor>();
    test_is_not_trivially_move_constructible<DeletedProtectedDestructor>();
    test_is_not_trivially_move_constructible<DeletedPrivateDestructor>();
    test_is_not_trivially_move_constructible<DeletedVirtualPublicDestructor>();
    test_is_not_trivially_move_constructible<DeletedVirtualProtectedDestructor>();
    test_is_not_trivially_move_constructible<DeletedVirtualPrivateDestructor>();
    test_is_trivially_move_constructible_cv<Enum>();
    test_is_trivially_move_constructible_cv<EnumSigned>();
    test_is_trivially_move_constructible_cv<EnumUnsigned>();
    test_is_trivially_move_constructible_cv<EnumClass>();
    test_is_trivially_move_constructible_cv<EnumStruct>();
    test_is_not_trivially_move_constructible<Function>();
    test_is_trivially_move_constructible_cv<FunctionPtr>();
    test_is_trivially_move_constructible_cv<MemberObjectPtr>();
    test_is_trivially_move_constructible_cv<MemberFunctionPtr>();
    test_is_trivially_move_constructible_cv<int Class::*>();
    test_is_trivially_move_constructible_cv<float Class::*>();
    test_is_trivially_move_constructible_cv<void * Class::*>();
    test_is_trivially_move_constructible_cv<int * Class::*>();
    test_is_trivially_move_constructible_cv<int Class::*&>();
    test_is_trivially_move_constructible_cv<float Class::*&>();
    test_is_trivially_move_constructible_cv<void * Class::*&>();
    test_is_trivially_move_constructible_cv<int * Class::*&>();
    test_is_trivially_move_constructible_cv<int Class::*&&>();
    test_is_trivially_move_constructible_cv<float Class::*&&>();
    test_is_trivially_move_constructible_cv<void * Class::*&&>();
    test_is_trivially_move_constructible_cv<int * Class::*&&>();
    test_is_trivially_move_constructible_cv<int Class::*const>();
    test_is_trivially_move_constructible_cv<float Class::*const>();
    test_is_trivially_move_constructible_cv<void * Class::*const>();
    test_is_trivially_move_constructible_cv<int Class::*const&>();
    test_is_trivially_move_constructible_cv<float Class::*const&>();
    test_is_trivially_move_constructible_cv<void * Class::*const&>();
    test_is_trivially_move_constructible_cv<int Class::*const&&>();
    test_is_trivially_move_constructible_cv<float Class::*const&&>();
    test_is_trivially_move_constructible_cv<void * Class::*const&&>();
    test_is_trivially_move_constructible_cv<int Class::*volatile>();
    test_is_trivially_move_constructible_cv<float Class::*volatile>();
    test_is_trivially_move_constructible_cv<void * Class::*volatile>();
    test_is_trivially_move_constructible_cv<int Class::*volatile&>();
    test_is_trivially_move_constructible_cv<float Class::*volatile&>();
    test_is_trivially_move_constructible_cv<void * Class::*volatile&>();
    test_is_trivially_move_constructible_cv<int Class::*volatile&&>();
    test_is_trivially_move_constructible_cv<float Class::*volatile&&>();
    test_is_trivially_move_constructible_cv<void * Class::*volatile&&>();
    test_is_trivially_move_constructible_cv<int Class::*const volatile>();
    test_is_trivially_move_constructible_cv<float Class::*const volatile>();
    test_is_trivially_move_constructible_cv<void * Class::*const volatile>();
    test_is_trivially_move_constructible_cv<int Class::*const volatile&>();
    test_is_trivially_move_constructible_cv<float Class::*const volatile&>();
    test_is_trivially_move_constructible_cv<void * Class::*const volatile&>();
    test_is_trivially_move_constructible_cv<int Class::*const volatile&&>();
    test_is_trivially_move_constructible_cv<float Class::*const volatile&&>();
    test_is_trivially_move_constructible_cv<void * Class::*const volatile&&>();
    test_is_trivially_move_constructible<NonCopyable>();
    test_is_trivially_move_constructible_only_c<NonMoveable>();
    test_is_not_trivially_move_constructible<NonConstructible>();
    test_is_not_trivially_move_constructible<Tracked>();
    test_is_trivially_move_constructible<TrapConstructible>();
    test_is_trivially_move_constructible_c<TrapImplicitConversion>();
    test_is_trivially_move_constructible_c<TrapComma>();
    test_is_trivially_move_constructible_c<TrapCall>();
    test_is_trivially_move_constructible_c<TrapSelfAssign>();
    test_is_trivially_move_constructible_c<TrapDeref>();
    test_is_trivially_move_constructible_c<TrapArraySubscript>();

    test_is_not_trivially_move_constructible<void()>();
    test_is_not_trivially_move_constructible<void()&>();
    test_is_not_trivially_move_constructible<void() &&>();
    test_is_not_trivially_move_constructible<void() const>();
    test_is_not_trivially_move_constructible<void() const&>();
    test_is_not_trivially_move_constructible<void() const&&>();
    test_is_not_trivially_move_constructible<void() volatile>();
    test_is_not_trivially_move_constructible<void() volatile&>();
    test_is_not_trivially_move_constructible<void() volatile&&>();
    test_is_not_trivially_move_constructible<void() const volatile>();
    test_is_not_trivially_move_constructible<void() const volatile&>();
    test_is_not_trivially_move_constructible<void() const volatile&&>();
    test_is_not_trivially_move_constructible<void() noexcept>();
    test_is_not_trivially_move_constructible<void()& noexcept>();
    test_is_not_trivially_move_constructible<void()&& noexcept>();
    test_is_not_trivially_move_constructible<void() const noexcept>();
    test_is_not_trivially_move_constructible<void() const& noexcept>();
    test_is_not_trivially_move_constructible<void() const&& noexcept>();
    test_is_not_trivially_move_constructible<void() volatile noexcept>();
    test_is_not_trivially_move_constructible<void() volatile& noexcept>();
    test_is_not_trivially_move_constructible<void() volatile&& noexcept>();
    test_is_not_trivially_move_constructible<void() const volatile noexcept>();
    test_is_not_trivially_move_constructible<void() const volatile& noexcept>();
    test_is_not_trivially_move_constructible<void() const volatile&& noexcept>();

    test_is_not_trivially_move_constructible<void(int)>();
    test_is_not_trivially_move_constructible<void(int)&>();
    test_is_not_trivially_move_constructible<void(int) &&>();
    test_is_not_trivially_move_constructible<void(int) const>();
    test_is_not_trivially_move_constructible<void(int) const&>();
    test_is_not_trivially_move_constructible<void(int) const&&>();
    test_is_not_trivially_move_constructible<void(int) volatile>();
    test_is_not_trivially_move_constructible<void(int) volatile&>();
    test_is_not_trivially_move_constructible<void(int) volatile&&>();
    test_is_not_trivially_move_constructible<void(int) const volatile>();
    test_is_not_trivially_move_constructible<void(int) const volatile&>();
    test_is_not_trivially_move_constructible<void(int) const volatile&&>();
    test_is_not_trivially_move_constructible<void(int) noexcept>();
    test_is_not_trivially_move_constructible<void(int)& noexcept>();
    test_is_not_trivially_move_constructible<void(int)&& noexcept>();
    test_is_not_trivially_move_constructible<void(int) const noexcept>();
    test_is_not_trivially_move_constructible<void(int) const& noexcept>();
    test_is_not_trivially_move_constructible<void(int) const&& noexcept>();
    test_is_not_trivially_move_constructible<void(int) volatile noexcept>();
    test_is_not_trivially_move_constructible<void(int) volatile& noexcept>();
    test_is_not_trivially_move_constructible<void(int) volatile&& noexcept>();
    test_is_not_trivially_move_constructible<void(int) const volatile noexcept>();
    test_is_not_trivially_move_constructible<void(int) const volatile& noexcept>();
    test_is_not_trivially_move_constructible<void(int) const volatile&& noexcept>();

    test_is_not_trivially_move_constructible<void(...)>();
    test_is_not_trivially_move_constructible<void(...)&>();
    test_is_not_trivially_move_constructible<void(...) &&>();
    test_is_not_trivially_move_constructible<void(...) const>();
    test_is_not_trivially_move_constructible<void(...) const&>();
    test_is_not_trivially_move_constructible<void(...) const&&>();
    test_is_not_trivially_move_constructible<void(...) volatile>();
    test_is_not_trivially_move_constructible<void(...) volatile&>();
    test_is_not_trivially_move_constructible<void(...) volatile&&>();
    test_is_not_trivially_move_constructible<void(...) const volatile>();
    test_is_not_trivially_move_constructible<void(...) const volatile&>();
    test_is_not_trivially_move_constructible<void(...) const volatile&&>();
    test_is_not_trivially_move_constructible<void(...) noexcept>();
    test_is_not_trivially_move_constructible<void(...)& noexcept>();
    test_is_not_trivially_move_constructible<void(...)&& noexcept>();
    test_is_not_trivially_move_constructible<void(...) const noexcept>();
    test_is_not_trivially_move_constructible<void(...) const& noexcept>();
    test_is_not_trivially_move_constructible<void(...) const&& noexcept>();
    test_is_not_trivially_move_constructible<void(...) volatile noexcept>();
    test_is_not_trivially_move_constructible<void(...) volatile& noexcept>();
    test_is_not_trivially_move_constructible<void(...) volatile&& noexcept>();
    test_is_not_trivially_move_constructible<void(...) const volatile noexcept>();
    test_is_not_trivially_move_constructible<void(...) const volatile& noexcept>();
    test_is_not_trivially_move_constructible<void(...) const volatile&& noexcept>();

    test_is_not_trivially_move_constructible<void(int, ...)>();
    test_is_not_trivially_move_constructible<void(int, ...)&>();
    test_is_not_trivially_move_constructible<void(int, ...) &&>();
    test_is_not_trivially_move_constructible<void(int, ...) const>();
    test_is_not_trivially_move_constructible<void(int, ...) const&>();
    test_is_not_trivially_move_constructible<void(int, ...) const&&>();
    test_is_not_trivially_move_constructible<void(int, ...) volatile>();
    test_is_not_trivially_move_constructible<void(int, ...) volatile&>();
    test_is_not_trivially_move_constructible<void(int, ...) volatile&&>();
    test_is_not_trivially_move_constructible<void(int, ...) const volatile>();
    test_is_not_trivially_move_constructible<void(int, ...) const volatile&>();
    test_is_not_trivially_move_constructible<void(int, ...) const volatile&&>();
    test_is_not_trivially_move_constructible<void(int, ...) noexcept>();
    test_is_not_trivially_move_constructible<void(int, ...)& noexcept>();
    test_is_not_trivially_move_constructible<void(int, ...)&& noexcept>();
    test_is_not_trivially_move_constructible<void(int, ...) const noexcept>();
    test_is_not_trivially_move_constructible<void(int, ...) const& noexcept>();
    test_is_not_trivially_move_constructible<void(int, ...) const&& noexcept>();
    test_is_not_trivially_move_constructible<void(int, ...) volatile noexcept>();
    test_is_not_trivially_move_constructible<void(int, ...) volatile& noexcept>();
    test_is_not_trivially_move_constructible<void(int, ...) volatile&& noexcept>();
    test_is_not_trivially_move_constructible<void(int, ...) const volatile noexcept>();
    test_is_not_trivially_move_constructible<void(int, ...) const volatile& noexcept>();
    test_is_not_trivially_move_constructible<void(int, ...) const volatile&& noexcept>();

    test_is_not_trivially_move_constructible<int()>();
    test_is_not_trivially_move_constructible<int()&>();
    test_is_not_trivially_move_constructible<int() &&>();
    test_is_not_trivially_move_constructible<int() const>();
    test_is_not_trivially_move_constructible<int() const&>();
    test_is_not_trivially_move_constructible<int() const&&>();
    test_is_not_trivially_move_constructible<int() volatile>();
    test_is_not_trivially_move_constructible<int() volatile&>();
    test_is_not_trivially_move_constructible<int() volatile&&>();
    test_is_not_trivially_move_constructible<int() const volatile>();
    test_is_not_trivially_move_constructible<int() const volatile&>();
    test_is_not_trivially_move_constructible<int() const volatile&&>();
    test_is_not_trivially_move_constructible<int() noexcept>();
    test_is_not_trivially_move_constructible<int()& noexcept>();
    test_is_not_trivially_move_constructible<int()&& noexcept>();
    test_is_not_trivially_move_constructible<int() const noexcept>();
    test_is_not_trivially_move_constructible<int() const& noexcept>();
    test_is_not_trivially_move_constructible<int() const&& noexcept>();
    test_is_not_trivially_move_constructible<int() volatile noexcept>();
    test_is_not_trivially_move_constructible<int() volatile& noexcept>();
    test_is_not_trivially_move_constructible<int() volatile&& noexcept>();
    test_is_not_trivially_move_constructible<int() const volatile noexcept>();
    test_is_not_trivially_move_constructible<int() const volatile& noexcept>();
    test_is_not_trivially_move_constructible<int() const volatile&& noexcept>();

    test_is_not_trivially_move_constructible<int(int)>();
    test_is_not_trivially_move_constructible<int(int)&>();
    test_is_not_trivially_move_constructible<int(int) &&>();
    test_is_not_trivially_move_constructible<int(int) const>();
    test_is_not_trivially_move_constructible<int(int) const&>();
    test_is_not_trivially_move_constructible<int(int) const&&>();
    test_is_not_trivially_move_constructible<int(int) volatile>();
    test_is_not_trivially_move_constructible<int(int) volatile&>();
    test_is_not_trivially_move_constructible<int(int) volatile&&>();
    test_is_not_trivially_move_constructible<int(int) const volatile>();
    test_is_not_trivially_move_constructible<int(int) const volatile&>();
    test_is_not_trivially_move_constructible<int(int) const volatile&&>();
    test_is_not_trivially_move_constructible<int(int) noexcept>();
    test_is_not_trivially_move_constructible<int(int)& noexcept>();
    test_is_not_trivially_move_constructible<int(int)&& noexcept>();
    test_is_not_trivially_move_constructible<int(int) const noexcept>();
    test_is_not_trivially_move_constructible<int(int) const& noexcept>();
    test_is_not_trivially_move_constructible<int(int) const&& noexcept>();
    test_is_not_trivially_move_constructible<int(int) volatile noexcept>();
    test_is_not_trivially_move_constructible<int(int) volatile& noexcept>();
    test_is_not_trivially_move_constructible<int(int) volatile&& noexcept>();
    test_is_not_trivially_move_constructible<int(int) const volatile noexcept>();
    test_is_not_trivially_move_constructible<int(int) const volatile& noexcept>();
    test_is_not_trivially_move_constructible<int(int) const volatile&& noexcept>();

    test_is_not_trivially_move_constructible<int(...)>();
    test_is_not_trivially_move_constructible<int(...)&>();
    test_is_not_trivially_move_constructible<int(...) &&>();
    test_is_not_trivially_move_constructible<int(...) const>();
    test_is_not_trivially_move_constructible<int(...) const&>();
    test_is_not_trivially_move_constructible<int(...) const&&>();
    test_is_not_trivially_move_constructible<int(...) volatile>();
    test_is_not_trivially_move_constructible<int(...) volatile&>();
    test_is_not_trivially_move_constructible<int(...) volatile&&>();
    test_is_not_trivially_move_constructible<int(...) const volatile>();
    test_is_not_trivially_move_constructible<int(...) const volatile&>();
    test_is_not_trivially_move_constructible<int(...) const volatile&&>();
    test_is_not_trivially_move_constructible<int(...) noexcept>();
    test_is_not_trivially_move_constructible<int(...)& noexcept>();
    test_is_not_trivially_move_constructible<int(...)&& noexcept>();
    test_is_not_trivially_move_constructible<int(...) const noexcept>();
    test_is_not_trivially_move_constructible<int(...) const& noexcept>();
    test_is_not_trivially_move_constructible<int(...) const&& noexcept>();
    test_is_not_trivially_move_constructible<int(...) volatile noexcept>();
    test_is_not_trivially_move_constructible<int(...) volatile& noexcept>();
    test_is_not_trivially_move_constructible<int(...) volatile&& noexcept>();
    test_is_not_trivially_move_constructible<int(...) const volatile noexcept>();
    test_is_not_trivially_move_constructible<int(...) const volatile& noexcept>();
    test_is_not_trivially_move_constructible<int(...) const volatile&& noexcept>();

    test_is_not_trivially_move_constructible<int(int, ...)>();
    test_is_not_trivially_move_constructible<int(int, ...)&>();
    test_is_not_trivially_move_constructible<int(int, ...) &&>();
    test_is_not_trivially_move_constructible<int(int, ...) const>();
    test_is_not_trivially_move_constructible<int(int, ...) const&>();
    test_is_not_trivially_move_constructible<int(int, ...) const&&>();
    test_is_not_trivially_move_constructible<int(int, ...) volatile>();
    test_is_not_trivially_move_constructible<int(int, ...) volatile&>();
    test_is_not_trivially_move_constructible<int(int, ...) volatile&&>();
    test_is_not_trivially_move_constructible<int(int, ...) const volatile>();
    test_is_not_trivially_move_constructible<int(int, ...) const volatile&>();
    test_is_not_trivially_move_constructible<int(int, ...) const volatile&&>();
    test_is_not_trivially_move_constructible<int(int, ...) noexcept>();
    test_is_not_trivially_move_constructible<int(int, ...)& noexcept>();
    test_is_not_trivially_move_constructible<int(int, ...)&& noexcept>();
    test_is_not_trivially_move_constructible<int(int, ...) const noexcept>();
    test_is_not_trivially_move_constructible<int(int, ...) const& noexcept>();
    test_is_not_trivially_move_constructible<int(int, ...) const&& noexcept>();
    test_is_not_trivially_move_constructible<int(int, ...) volatile noexcept>();
    test_is_not_trivially_move_constructible<int(int, ...) volatile& noexcept>();
    test_is_not_trivially_move_constructible<int(int, ...) volatile&& noexcept>();
    test_is_not_trivially_move_constructible<int(int, ...) const volatile noexcept>();
    test_is_not_trivially_move_constructible<int(int, ...) const volatile& noexcept>();
    test_is_not_trivially_move_constructible<int(int, ...) const volatile&& noexcept>();

    test_is_trivially_move_constructible_cv<void (*)()>();
    test_is_trivially_move_constructible_cv<void (*)() noexcept>();

    test_is_trivially_move_constructible_cv<void (*)(int)>();
    test_is_trivially_move_constructible_cv<void (*)(int) noexcept>();

    test_is_trivially_move_constructible_cv<void (*)(...)>();
    test_is_trivially_move_constructible_cv<void (*)(...) noexcept>();

    test_is_trivially_move_constructible_cv<void (*)(int, ...)>();
    test_is_trivially_move_constructible_cv<void (*)(int, ...) noexcept>();

    test_is_trivially_move_constructible_cv<int (*)()>();
    test_is_trivially_move_constructible_cv<int (*)() noexcept>();

    test_is_trivially_move_constructible_cv<int (*)(int)>();
    test_is_trivially_move_constructible_cv<int (*)(int) noexcept>();

    test_is_trivially_move_constructible_cv<int (*)(...)>();
    test_is_trivially_move_constructible_cv<int (*)(...) noexcept>();

    test_is_trivially_move_constructible_cv<int (*)(int, ...)>();
    test_is_trivially_move_constructible_cv<int (*)(int, ...) noexcept>();

    test_is_trivially_move_constructible_cv<void (&)()>();
    test_is_trivially_move_constructible_cv<void (&)() noexcept>();

    test_is_trivially_move_constructible_cv<void (&)(int)>();
    test_is_trivially_move_constructible_cv<void (&)(int) noexcept>();

    test_is_trivially_move_constructible_cv<void (&)(...)>();
    test_is_trivially_move_constructible_cv<void (&)(...) noexcept>();

    test_is_trivially_move_constructible_cv<void (&)(int, ...)>();
    test_is_trivially_move_constructible_cv<void (&)(int, ...) noexcept>();

    test_is_trivially_move_constructible_cv<int (&)()>();
    test_is_trivially_move_constructible_cv<int (&)() noexcept>();

    test_is_trivially_move_constructible_cv<int (&)(int)>();
    test_is_trivially_move_constructible_cv<int (&)(int) noexcept>();

    test_is_trivially_move_constructible_cv<int (&)(...)>();
    test_is_trivially_move_constructible_cv<int (&)(...) noexcept>();

    test_is_trivially_move_constructible_cv<int (&)(int, ...)>();
    test_is_trivially_move_constructible_cv<int (&)(int, ...) noexcept>();

    test_is_trivially_move_constructible_cv<void(&&)()>();
    test_is_trivially_move_constructible_cv<void(&&)() noexcept>();

    test_is_trivially_move_constructible_cv<void(&&)(int)>();
    test_is_trivially_move_constructible_cv<void(&&)(int) noexcept>();

    test_is_trivially_move_constructible_cv<void(&&)(...)>();
    test_is_trivially_move_constructible_cv<void(&&)(...) noexcept>();

    test_is_trivially_move_constructible_cv<void(&&)(int, ...)>();
    test_is_trivially_move_constructible_cv<void(&&)(int, ...) noexcept>();

    test_is_trivially_move_constructible_cv<int(&&)()>();
    test_is_trivially_move_constructible_cv<int(&&)() noexcept>();

    test_is_trivially_move_constructible_cv<int(&&)(int)>();
    test_is_trivially_move_constructible_cv<int(&&)(int) noexcept>();

    test_is_trivially_move_constructible_cv<int(&&)(...)>();
    test_is_trivially_move_constructible_cv<int(&&)(...) noexcept>();

    test_is_trivially_move_constructible_cv<int(&&)(int, ...)>();
    test_is_trivially_move_constructible_cv<int(&&)(int, ...) noexcept>();

    test_is_trivially_move_constructible_cv<void (Class::*)()>();
    test_is_trivially_move_constructible_cv<void (Class::*)()&>();
    test_is_trivially_move_constructible_cv<void (Class::*)() &&>();
    test_is_trivially_move_constructible_cv<void (Class::*)() const>();
    test_is_trivially_move_constructible_cv<void (Class::*)() const&>();
    test_is_trivially_move_constructible_cv<void (Class::*)() const&&>();
    test_is_trivially_move_constructible_cv<void (Class::*)() noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)()& noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)()&& noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)() const noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)() const& noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)() const&& noexcept>();

    test_is_trivially_move_constructible_cv<void (Class::*)(int)>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int)&>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int) &&>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int) const>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int) const&>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int) const&&>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int) noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int)& noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int)&& noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int) const noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int) const& noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int) const&& noexcept>();

    test_is_trivially_move_constructible_cv<void (Class::*)(...)>();
    test_is_trivially_move_constructible_cv<void (Class::*)(...)&>();
    test_is_trivially_move_constructible_cv<void (Class::*)(...) &&>();
    test_is_trivially_move_constructible_cv<void (Class::*)(...) const>();
    test_is_trivially_move_constructible_cv<void (Class::*)(...) const&>();
    test_is_trivially_move_constructible_cv<void (Class::*)(...) const&&>();
    test_is_trivially_move_constructible_cv<void (Class::*)(...) noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)(...)& noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)(...)&& noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)(...) const noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)(...) const& noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)(...) const&& noexcept>();

    test_is_trivially_move_constructible_cv<void (Class::*)(int, ...)>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int, ...)&>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int, ...) &&>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int, ...) const>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int, ...) const&>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int, ...) const&&>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int, ...) noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int, ...)& noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int, ...)&& noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int, ...) const noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int, ...) const& noexcept>();
    test_is_trivially_move_constructible_cv<void (Class::*)(int, ...) const&& noexcept>();

    test_is_trivially_move_constructible_cv<int (Class::*)()>();
    test_is_trivially_move_constructible_cv<int (Class::*)()&>();
    test_is_trivially_move_constructible_cv<int (Class::*)() &&>();
    test_is_trivially_move_constructible_cv<int (Class::*)() const>();
    test_is_trivially_move_constructible_cv<int (Class::*)() const&>();
    test_is_trivially_move_constructible_cv<int (Class::*)() const&&>();
    test_is_trivially_move_constructible_cv<int (Class::*)() noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)()& noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)()&& noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)() const noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)() const& noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)() const&& noexcept>();

    test_is_trivially_move_constructible_cv<int (Class::*)(int)>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int)&>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int) &&>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int) const>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int) const&>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int) const&&>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int) noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int)& noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int)&& noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int) const noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int) const& noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int) const&& noexcept>();

    test_is_trivially_move_constructible_cv<int (Class::*)(...)>();
    test_is_trivially_move_constructible_cv<int (Class::*)(...)&>();
    test_is_trivially_move_constructible_cv<int (Class::*)(...) &&>();
    test_is_trivially_move_constructible_cv<int (Class::*)(...) const>();
    test_is_trivially_move_constructible_cv<int (Class::*)(...) const&>();
    test_is_trivially_move_constructible_cv<int (Class::*)(...) const&&>();
    test_is_trivially_move_constructible_cv<int (Class::*)(...) noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)(...)& noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)(...)&& noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)(...) const noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)(...) const& noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)(...) const&& noexcept>();

    test_is_trivially_move_constructible_cv<int (Class::*)(int, ...)>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int, ...)&>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int, ...) &&>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int, ...) const>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int, ...) const&>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int, ...) const&&>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int, ...) noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int, ...)& noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int, ...)&& noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int, ...) const noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int, ...) const& noexcept>();
    test_is_trivially_move_constructible_cv<int (Class::*)(int, ...) const&& noexcept>();
}
