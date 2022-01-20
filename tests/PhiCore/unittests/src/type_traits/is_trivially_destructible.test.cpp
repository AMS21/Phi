#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_destructible.hpp>
#include <phi/type_traits/is_trivially_destructible.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_trivially_destructible_impl()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_DESTRUCTIBLE()
    STATIC_REQUIRE(phi::is_trivially_destructible<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_destructible<T>::value);
    STATIC_REQUIRE(phi::is_destructible<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_destructible_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_destructible_v<T>);
    STATIC_REQUIRE(phi::is_destructible_v<T>);
#    endif

    // Standard compatibililty
    STATIC_REQUIRE(std::is_trivially_destructible<T>::value);
    STATIC_REQUIRE(std::is_destructible<T>::value);
#endif
}

template <typename T>
void test_is_not_trivially_destructible_impl()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_DESTRUCTIBLE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_destructible<T>::value);
    STATIC_REQUIRE(phi::is_not_trivially_destructible<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_destructible_v<T>);
    STATIC_REQUIRE(phi::is_not_trivially_destructible_v<T>);
#    endif

    // Standard compatibililty
    STATIC_REQUIRE_FALSE(std::is_trivially_destructible<T>::value);
#endif
}

template <typename T>
void test_is_trivially_destructible()
{
    test_is_trivially_destructible_impl<T>();
    test_is_trivially_destructible_impl<const T>();
    test_is_trivially_destructible_impl<volatile T>();
    test_is_trivially_destructible_impl<const volatile T>();
}

template <typename T>
void test_is_not_trivially_destructible()
{
    test_is_not_trivially_destructible_impl<T>();
    test_is_not_trivially_destructible_impl<const T>();
    test_is_not_trivially_destructible_impl<volatile T>();
    test_is_not_trivially_destructible_impl<const volatile T>();
}

struct A
{
    ~A();
};

struct B
{
    ~B() = default;
};

TEST_CASE("is_trivially_destructible")
{
    test_is_not_trivially_destructible<A>();
    test_is_trivially_destructible<B>();

    test_is_not_trivially_destructible<void>();
    test_is_trivially_destructible<phi::nullptr_t>();
    test_is_trivially_destructible<bool>();
    test_is_trivially_destructible<char>();
    test_is_trivially_destructible<signed char>();
    test_is_trivially_destructible<unsigned char>();
    test_is_trivially_destructible<short>();
    test_is_trivially_destructible<unsigned short>();
    test_is_trivially_destructible<int>();
    test_is_trivially_destructible<unsigned int>();
    test_is_trivially_destructible<long>();
    test_is_trivially_destructible<unsigned long>();
    test_is_trivially_destructible<long long>();
    test_is_trivially_destructible<unsigned long long>();
    test_is_trivially_destructible<float>();
    test_is_trivially_destructible<double>();
    test_is_trivially_destructible<long double>();
    test_is_trivially_destructible<char8_t>();
    test_is_trivially_destructible<char16_t>();
    test_is_trivially_destructible<char32_t>();
    test_is_trivially_destructible<wchar_t>();

    test_is_trivially_destructible<phi::boolean>();
    test_is_trivially_destructible<phi::integer<signed char>>();
    test_is_trivially_destructible<phi::integer<unsigned char>>();
    test_is_trivially_destructible<phi::integer<short>>();
    test_is_trivially_destructible<phi::integer<unsigned short>>();
    test_is_trivially_destructible<phi::integer<int>>();
    test_is_trivially_destructible<phi::integer<unsigned int>>();
    test_is_trivially_destructible<phi::integer<long>>();
    test_is_trivially_destructible<phi::integer<unsigned long>>();
    test_is_trivially_destructible<phi::integer<long long>>();
    test_is_trivially_destructible<phi::integer<unsigned long long>>();
    test_is_trivially_destructible<phi::floating_point<float>>();
    test_is_trivially_destructible<phi::floating_point<double>>();
    test_is_trivially_destructible<phi::floating_point<long double>>();

    test_is_not_trivially_destructible<std::vector<int>>();
    test_is_not_trivially_destructible<phi::scope_ptr<int>>();

    test_is_trivially_destructible<int&>();
    test_is_trivially_destructible<const int&>();
    test_is_trivially_destructible<volatile int&>();
    test_is_trivially_destructible<const volatile int&>();
    test_is_trivially_destructible<int&&>();
    test_is_trivially_destructible<const int&&>();
    test_is_trivially_destructible<volatile int&&>();
    test_is_trivially_destructible<const volatile int&&>();
    test_is_trivially_destructible<int*>();
    test_is_trivially_destructible<const int*>();
    test_is_trivially_destructible<volatile int*>();
    test_is_trivially_destructible<const volatile int*>();
    test_is_trivially_destructible<int**>();
    test_is_trivially_destructible<const int**>();
    test_is_trivially_destructible<volatile int**>();
    test_is_trivially_destructible<const volatile int**>();
    test_is_trivially_destructible<int*&>();
    test_is_trivially_destructible<const int*&>();
    test_is_trivially_destructible<volatile int*&>();
    test_is_trivially_destructible<const volatile int*&>();
    test_is_trivially_destructible<int*&&>();
    test_is_trivially_destructible<const int*&&>();
    test_is_trivially_destructible<volatile int*&&>();
    test_is_trivially_destructible<const volatile int*&&>();
    test_is_trivially_destructible<void*>();
    test_is_trivially_destructible<char[3]>();
    test_is_not_trivially_destructible<char[]>();
    test_is_trivially_destructible<char* [3]>();
    test_is_not_trivially_destructible<char*[]>();
    test_is_trivially_destructible<int(*)[3]>();
    test_is_trivially_destructible<int(*)[]>();
    test_is_trivially_destructible<int(&)[3]>();
    test_is_trivially_destructible<int(&)[]>();
    test_is_trivially_destructible<int(&&)[3]>();
    test_is_trivially_destructible<int(&&)[]>();
    test_is_trivially_destructible<char[3][2]>();
    test_is_not_trivially_destructible<char[][2]>();
    test_is_trivially_destructible<char* [3][2]>();
    test_is_not_trivially_destructible<char*[][2]>();
    test_is_trivially_destructible<int(*)[3][2]>();
    test_is_trivially_destructible<int(*)[][2]>();
    test_is_trivially_destructible<int(&)[3][2]>();
    test_is_trivially_destructible<int(&)[][2]>();
    test_is_trivially_destructible<int(&&)[3][2]>();
    test_is_trivially_destructible<int(&&)[][2]>();
    test_is_not_trivially_destructible<Class>();
    test_is_not_trivially_destructible<Class[]>();
    test_is_not_trivially_destructible<Class[2]>();
    test_is_trivially_destructible<Template<void>>();
    test_is_trivially_destructible<Template<int>>();
    test_is_trivially_destructible<Template<Class>>();
    test_is_trivially_destructible<Template<incomplete_type>>();
    test_is_trivially_destructible<VariadicTemplate<>>();
    test_is_trivially_destructible<VariadicTemplate<void>>();
    test_is_trivially_destructible<VariadicTemplate<int>>();
    test_is_trivially_destructible<VariadicTemplate<Class>>();
    test_is_trivially_destructible<VariadicTemplate<incomplete_type>>();
    test_is_trivially_destructible<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_trivially_destructible<PublicDerviedFromTemplate<Base>>();
    test_is_trivially_destructible<PublicDerviedFromTemplate<Derived>>();
    test_is_not_trivially_destructible<PublicDerviedFromTemplate<Class>>();
    test_is_trivially_destructible<PrivateDerviedFromTemplate<Base>>();
    test_is_trivially_destructible<PrivateDerviedFromTemplate<Derived>>();
    test_is_not_trivially_destructible<PrivateDerviedFromTemplate<Class>>();
    test_is_trivially_destructible<ProtectedDerviedFromTemplate<Base>>();
    test_is_trivially_destructible<ProtectedDerviedFromTemplate<Derived>>();
    test_is_not_trivially_destructible<ProtectedDerviedFromTemplate<Class>>();
    test_is_trivially_destructible<Union>();
    test_is_trivially_destructible<NonEmptyUnion>();
    test_is_trivially_destructible<Empty>();
    test_is_not_trivially_destructible<NotEmpty>();
    test_is_trivially_destructible<bit_zero>();
    test_is_trivially_destructible<bit_one>();
    test_is_trivially_destructible<Base>();
    test_is_trivially_destructible<Derived>();
    test_is_not_trivially_destructible<Abstract>();
    test_is_not_trivially_destructible<PublicAbstract>();
    test_is_not_trivially_destructible<PrivateAbstract>();
    test_is_not_trivially_destructible<ProtectedAbstract>();
    test_is_not_trivially_destructible<AbstractTemplate<int>>();
    test_is_trivially_destructible<AbstractTemplate<double>>();
    test_is_not_trivially_destructible<AbstractTemplate<Class>>();
    test_is_not_trivially_destructible<AbstractTemplate<incomplete_type>>();
    test_is_trivially_destructible<Final>();
    test_is_trivially_destructible<PublicDestructor>();
    test_is_not_trivially_destructible<ProtectedDestructor>();
    test_is_not_trivially_destructible<PrivateDestructor>();
    test_is_not_trivially_destructible<VirtualPublicDestructor>();
    test_is_not_trivially_destructible<VirtualProtectedDestructor>();
    test_is_not_trivially_destructible<VirtualPrivateDestructor>();
    test_is_not_trivially_destructible<PurePublicDestructor>();
    test_is_not_trivially_destructible<PureProtectedDestructor>();
    test_is_not_trivially_destructible<PurePrivateDestructor>();
    test_is_not_trivially_destructible<DeletedPublicDestructor>();
    test_is_not_trivially_destructible<DeletedProtectedDestructor>();
    test_is_not_trivially_destructible<DeletedPrivateDestructor>();
    test_is_not_trivially_destructible<DeletedVirtualPublicDestructor>();
    test_is_not_trivially_destructible<DeletedVirtualProtectedDestructor>();
    test_is_not_trivially_destructible<DeletedVirtualPrivateDestructor>();
    test_is_trivially_destructible<Enum>();
    test_is_trivially_destructible<EnumSigned>();
    test_is_trivially_destructible<EnumUnsigned>();
    test_is_trivially_destructible<EnumClass>();
    test_is_trivially_destructible<EnumStruct>();
    test_is_not_trivially_destructible<Function>();
    test_is_trivially_destructible<FunctionPtr>();
    test_is_trivially_destructible<MemberObjectPtr>();
    test_is_trivially_destructible<MemberFunctionPtr>();
    test_is_trivially_destructible<int Class::*>();
    test_is_trivially_destructible<float Class::*>();
    test_is_trivially_destructible<void * Class::*>();
    test_is_trivially_destructible<int * Class::*>();
    test_is_trivially_destructible<int Class::*&>();
    test_is_trivially_destructible<float Class::*&>();
    test_is_trivially_destructible<void * Class::*&>();
    test_is_trivially_destructible<int * Class::*&>();
    test_is_trivially_destructible<int Class::*&&>();
    test_is_trivially_destructible<float Class::*&&>();
    test_is_trivially_destructible<void * Class::*&&>();
    test_is_trivially_destructible<int * Class::*&&>();
    test_is_trivially_destructible<int Class::*const>();
    test_is_trivially_destructible<float Class::*const>();
    test_is_trivially_destructible<void * Class::*const>();
    test_is_trivially_destructible<int Class::*const&>();
    test_is_trivially_destructible<float Class::*const&>();
    test_is_trivially_destructible<void * Class::*const&>();
    test_is_trivially_destructible<int Class::*const&&>();
    test_is_trivially_destructible<float Class::*const&&>();
    test_is_trivially_destructible<void * Class::*const&&>();
    test_is_trivially_destructible<int Class::*volatile>();
    test_is_trivially_destructible<float Class::*volatile>();
    test_is_trivially_destructible<void * Class::*volatile>();
    test_is_trivially_destructible<int Class::*volatile&>();
    test_is_trivially_destructible<float Class::*volatile&>();
    test_is_trivially_destructible<void * Class::*volatile&>();
    test_is_trivially_destructible<int Class::*volatile&&>();
    test_is_trivially_destructible<float Class::*volatile&&>();
    test_is_trivially_destructible<void * Class::*volatile&&>();
    test_is_trivially_destructible<int Class::*const volatile>();
    test_is_trivially_destructible<float Class::*const volatile>();
    test_is_trivially_destructible<void * Class::*const volatile>();
    test_is_trivially_destructible<int Class::*const volatile&>();
    test_is_trivially_destructible<float Class::*const volatile&>();
    test_is_trivially_destructible<void * Class::*const volatile&>();
    test_is_trivially_destructible<int Class::*const volatile&&>();
    test_is_trivially_destructible<float Class::*const volatile&&>();
    test_is_trivially_destructible<void * Class::*const volatile&&>();
    test_is_trivially_destructible<NonCopyable>();
    test_is_trivially_destructible<NonMoveable>();
    test_is_trivially_destructible<NonConstructible>();
    test_is_not_trivially_destructible<Tracked>();
    test_is_trivially_destructible<TrapConstructible>();
    test_is_trivially_destructible<TrapImplicitConversion>();
    test_is_trivially_destructible<TrapComma>();
    test_is_trivially_destructible<TrapCall>();
    test_is_trivially_destructible<TrapSelfAssign>();
    test_is_trivially_destructible<TrapDeref>();
    test_is_trivially_destructible<TrapArraySubscript>();

    test_is_not_trivially_destructible<void()>();
    test_is_not_trivially_destructible<void()&>();
    test_is_not_trivially_destructible<void() &&>();
    test_is_not_trivially_destructible<void() const>();
    test_is_not_trivially_destructible<void() const&>();
    test_is_not_trivially_destructible<void() const&&>();
    test_is_not_trivially_destructible<void() volatile>();
    test_is_not_trivially_destructible<void() volatile&>();
    test_is_not_trivially_destructible<void() volatile&&>();
    test_is_not_trivially_destructible<void() const volatile>();
    test_is_not_trivially_destructible<void() const volatile&>();
    test_is_not_trivially_destructible<void() const volatile&&>();
    test_is_not_trivially_destructible<void() noexcept>();
    test_is_not_trivially_destructible<void()& noexcept>();
    test_is_not_trivially_destructible<void()&& noexcept>();
    test_is_not_trivially_destructible<void() const noexcept>();
    test_is_not_trivially_destructible<void() const& noexcept>();
    test_is_not_trivially_destructible<void() const&& noexcept>();
    test_is_not_trivially_destructible<void() volatile noexcept>();
    test_is_not_trivially_destructible<void() volatile& noexcept>();
    test_is_not_trivially_destructible<void() volatile&& noexcept>();
    test_is_not_trivially_destructible<void() const volatile noexcept>();
    test_is_not_trivially_destructible<void() const volatile& noexcept>();
    test_is_not_trivially_destructible<void() const volatile&& noexcept>();

    test_is_not_trivially_destructible<void(int)>();
    test_is_not_trivially_destructible<void(int)&>();
    test_is_not_trivially_destructible<void(int) &&>();
    test_is_not_trivially_destructible<void(int) const>();
    test_is_not_trivially_destructible<void(int) const&>();
    test_is_not_trivially_destructible<void(int) const&&>();
    test_is_not_trivially_destructible<void(int) volatile>();
    test_is_not_trivially_destructible<void(int) volatile&>();
    test_is_not_trivially_destructible<void(int) volatile&&>();
    test_is_not_trivially_destructible<void(int) const volatile>();
    test_is_not_trivially_destructible<void(int) const volatile&>();
    test_is_not_trivially_destructible<void(int) const volatile&&>();
    test_is_not_trivially_destructible<void(int) noexcept>();
    test_is_not_trivially_destructible<void(int)& noexcept>();
    test_is_not_trivially_destructible<void(int)&& noexcept>();
    test_is_not_trivially_destructible<void(int) const noexcept>();
    test_is_not_trivially_destructible<void(int) const& noexcept>();
    test_is_not_trivially_destructible<void(int) const&& noexcept>();
    test_is_not_trivially_destructible<void(int) volatile noexcept>();
    test_is_not_trivially_destructible<void(int) volatile& noexcept>();
    test_is_not_trivially_destructible<void(int) volatile&& noexcept>();
    test_is_not_trivially_destructible<void(int) const volatile noexcept>();
    test_is_not_trivially_destructible<void(int) const volatile& noexcept>();
    test_is_not_trivially_destructible<void(int) const volatile&& noexcept>();

    test_is_not_trivially_destructible<void(...)>();
    test_is_not_trivially_destructible<void(...)&>();
    test_is_not_trivially_destructible<void(...) &&>();
    test_is_not_trivially_destructible<void(...) const>();
    test_is_not_trivially_destructible<void(...) const&>();
    test_is_not_trivially_destructible<void(...) const&&>();
    test_is_not_trivially_destructible<void(...) volatile>();
    test_is_not_trivially_destructible<void(...) volatile&>();
    test_is_not_trivially_destructible<void(...) volatile&&>();
    test_is_not_trivially_destructible<void(...) const volatile>();
    test_is_not_trivially_destructible<void(...) const volatile&>();
    test_is_not_trivially_destructible<void(...) const volatile&&>();
    test_is_not_trivially_destructible<void(...) noexcept>();
    test_is_not_trivially_destructible<void(...)& noexcept>();
    test_is_not_trivially_destructible<void(...)&& noexcept>();
    test_is_not_trivially_destructible<void(...) const noexcept>();
    test_is_not_trivially_destructible<void(...) const& noexcept>();
    test_is_not_trivially_destructible<void(...) const&& noexcept>();
    test_is_not_trivially_destructible<void(...) volatile noexcept>();
    test_is_not_trivially_destructible<void(...) volatile& noexcept>();
    test_is_not_trivially_destructible<void(...) volatile&& noexcept>();
    test_is_not_trivially_destructible<void(...) const volatile noexcept>();
    test_is_not_trivially_destructible<void(...) const volatile& noexcept>();
    test_is_not_trivially_destructible<void(...) const volatile&& noexcept>();

    test_is_not_trivially_destructible<void(int, ...)>();
    test_is_not_trivially_destructible<void(int, ...)&>();
    test_is_not_trivially_destructible<void(int, ...) &&>();
    test_is_not_trivially_destructible<void(int, ...) const>();
    test_is_not_trivially_destructible<void(int, ...) const&>();
    test_is_not_trivially_destructible<void(int, ...) const&&>();
    test_is_not_trivially_destructible<void(int, ...) volatile>();
    test_is_not_trivially_destructible<void(int, ...) volatile&>();
    test_is_not_trivially_destructible<void(int, ...) volatile&&>();
    test_is_not_trivially_destructible<void(int, ...) const volatile>();
    test_is_not_trivially_destructible<void(int, ...) const volatile&>();
    test_is_not_trivially_destructible<void(int, ...) const volatile&&>();
    test_is_not_trivially_destructible<void(int, ...) noexcept>();
    test_is_not_trivially_destructible<void(int, ...)& noexcept>();
    test_is_not_trivially_destructible<void(int, ...)&& noexcept>();
    test_is_not_trivially_destructible<void(int, ...) const noexcept>();
    test_is_not_trivially_destructible<void(int, ...) const& noexcept>();
    test_is_not_trivially_destructible<void(int, ...) const&& noexcept>();
    test_is_not_trivially_destructible<void(int, ...) volatile noexcept>();
    test_is_not_trivially_destructible<void(int, ...) volatile& noexcept>();
    test_is_not_trivially_destructible<void(int, ...) volatile&& noexcept>();
    test_is_not_trivially_destructible<void(int, ...) const volatile noexcept>();
    test_is_not_trivially_destructible<void(int, ...) const volatile& noexcept>();
    test_is_not_trivially_destructible<void(int, ...) const volatile&& noexcept>();

    test_is_not_trivially_destructible<int()>();
    test_is_not_trivially_destructible<int()&>();
    test_is_not_trivially_destructible<int() &&>();
    test_is_not_trivially_destructible<int() const>();
    test_is_not_trivially_destructible<int() const&>();
    test_is_not_trivially_destructible<int() const&&>();
    test_is_not_trivially_destructible<int() volatile>();
    test_is_not_trivially_destructible<int() volatile&>();
    test_is_not_trivially_destructible<int() volatile&&>();
    test_is_not_trivially_destructible<int() const volatile>();
    test_is_not_trivially_destructible<int() const volatile&>();
    test_is_not_trivially_destructible<int() const volatile&&>();
    test_is_not_trivially_destructible<int() noexcept>();
    test_is_not_trivially_destructible<int()& noexcept>();
    test_is_not_trivially_destructible<int()&& noexcept>();
    test_is_not_trivially_destructible<int() const noexcept>();
    test_is_not_trivially_destructible<int() const& noexcept>();
    test_is_not_trivially_destructible<int() const&& noexcept>();
    test_is_not_trivially_destructible<int() volatile noexcept>();
    test_is_not_trivially_destructible<int() volatile& noexcept>();
    test_is_not_trivially_destructible<int() volatile&& noexcept>();
    test_is_not_trivially_destructible<int() const volatile noexcept>();
    test_is_not_trivially_destructible<int() const volatile& noexcept>();
    test_is_not_trivially_destructible<int() const volatile&& noexcept>();

    test_is_not_trivially_destructible<int(int)>();
    test_is_not_trivially_destructible<int(int)&>();
    test_is_not_trivially_destructible<int(int) &&>();
    test_is_not_trivially_destructible<int(int) const>();
    test_is_not_trivially_destructible<int(int) const&>();
    test_is_not_trivially_destructible<int(int) const&&>();
    test_is_not_trivially_destructible<int(int) volatile>();
    test_is_not_trivially_destructible<int(int) volatile&>();
    test_is_not_trivially_destructible<int(int) volatile&&>();
    test_is_not_trivially_destructible<int(int) const volatile>();
    test_is_not_trivially_destructible<int(int) const volatile&>();
    test_is_not_trivially_destructible<int(int) const volatile&&>();
    test_is_not_trivially_destructible<int(int) noexcept>();
    test_is_not_trivially_destructible<int(int)& noexcept>();
    test_is_not_trivially_destructible<int(int)&& noexcept>();
    test_is_not_trivially_destructible<int(int) const noexcept>();
    test_is_not_trivially_destructible<int(int) const& noexcept>();
    test_is_not_trivially_destructible<int(int) const&& noexcept>();
    test_is_not_trivially_destructible<int(int) volatile noexcept>();
    test_is_not_trivially_destructible<int(int) volatile& noexcept>();
    test_is_not_trivially_destructible<int(int) volatile&& noexcept>();
    test_is_not_trivially_destructible<int(int) const volatile noexcept>();
    test_is_not_trivially_destructible<int(int) const volatile& noexcept>();
    test_is_not_trivially_destructible<int(int) const volatile&& noexcept>();

    test_is_not_trivially_destructible<int(...)>();
    test_is_not_trivially_destructible<int(...)&>();
    test_is_not_trivially_destructible<int(...) &&>();
    test_is_not_trivially_destructible<int(...) const>();
    test_is_not_trivially_destructible<int(...) const&>();
    test_is_not_trivially_destructible<int(...) const&&>();
    test_is_not_trivially_destructible<int(...) volatile>();
    test_is_not_trivially_destructible<int(...) volatile&>();
    test_is_not_trivially_destructible<int(...) volatile&&>();
    test_is_not_trivially_destructible<int(...) const volatile>();
    test_is_not_trivially_destructible<int(...) const volatile&>();
    test_is_not_trivially_destructible<int(...) const volatile&&>();
    test_is_not_trivially_destructible<int(...) noexcept>();
    test_is_not_trivially_destructible<int(...)& noexcept>();
    test_is_not_trivially_destructible<int(...)&& noexcept>();
    test_is_not_trivially_destructible<int(...) const noexcept>();
    test_is_not_trivially_destructible<int(...) const& noexcept>();
    test_is_not_trivially_destructible<int(...) const&& noexcept>();
    test_is_not_trivially_destructible<int(...) volatile noexcept>();
    test_is_not_trivially_destructible<int(...) volatile& noexcept>();
    test_is_not_trivially_destructible<int(...) volatile&& noexcept>();
    test_is_not_trivially_destructible<int(...) const volatile noexcept>();
    test_is_not_trivially_destructible<int(...) const volatile& noexcept>();
    test_is_not_trivially_destructible<int(...) const volatile&& noexcept>();

    test_is_not_trivially_destructible<int(int, ...)>();
    test_is_not_trivially_destructible<int(int, ...)&>();
    test_is_not_trivially_destructible<int(int, ...) &&>();
    test_is_not_trivially_destructible<int(int, ...) const>();
    test_is_not_trivially_destructible<int(int, ...) const&>();
    test_is_not_trivially_destructible<int(int, ...) const&&>();
    test_is_not_trivially_destructible<int(int, ...) volatile>();
    test_is_not_trivially_destructible<int(int, ...) volatile&>();
    test_is_not_trivially_destructible<int(int, ...) volatile&&>();
    test_is_not_trivially_destructible<int(int, ...) const volatile>();
    test_is_not_trivially_destructible<int(int, ...) const volatile&>();
    test_is_not_trivially_destructible<int(int, ...) const volatile&&>();
    test_is_not_trivially_destructible<int(int, ...) noexcept>();
    test_is_not_trivially_destructible<int(int, ...)& noexcept>();
    test_is_not_trivially_destructible<int(int, ...)&& noexcept>();
    test_is_not_trivially_destructible<int(int, ...) const noexcept>();
    test_is_not_trivially_destructible<int(int, ...) const& noexcept>();
    test_is_not_trivially_destructible<int(int, ...) const&& noexcept>();
    test_is_not_trivially_destructible<int(int, ...) volatile noexcept>();
    test_is_not_trivially_destructible<int(int, ...) volatile& noexcept>();
    test_is_not_trivially_destructible<int(int, ...) volatile&& noexcept>();
    test_is_not_trivially_destructible<int(int, ...) const volatile noexcept>();
    test_is_not_trivially_destructible<int(int, ...) const volatile& noexcept>();
    test_is_not_trivially_destructible<int(int, ...) const volatile&& noexcept>();

    test_is_trivially_destructible<void (*)()>();
    test_is_trivially_destructible<void (*)() noexcept>();

    test_is_trivially_destructible<void (*)(int)>();
    test_is_trivially_destructible<void (*)(int) noexcept>();

    test_is_trivially_destructible<void (*)(...)>();
    test_is_trivially_destructible<void (*)(...) noexcept>();

    test_is_trivially_destructible<void (*)(int, ...)>();
    test_is_trivially_destructible<void (*)(int, ...) noexcept>();

    test_is_trivially_destructible<int (*)()>();
    test_is_trivially_destructible<int (*)() noexcept>();

    test_is_trivially_destructible<int (*)(int)>();
    test_is_trivially_destructible<int (*)(int) noexcept>();

    test_is_trivially_destructible<int (*)(...)>();
    test_is_trivially_destructible<int (*)(...) noexcept>();

    test_is_trivially_destructible<int (*)(int, ...)>();
    test_is_trivially_destructible<int (*)(int, ...) noexcept>();

    test_is_trivially_destructible<void (&)()>();
    test_is_trivially_destructible<void (&)() noexcept>();

    test_is_trivially_destructible<void (&)(int)>();
    test_is_trivially_destructible<void (&)(int) noexcept>();

    test_is_trivially_destructible<void (&)(...)>();
    test_is_trivially_destructible<void (&)(...) noexcept>();

    test_is_trivially_destructible<void (&)(int, ...)>();
    test_is_trivially_destructible<void (&)(int, ...) noexcept>();

    test_is_trivially_destructible<int (&)()>();
    test_is_trivially_destructible<int (&)() noexcept>();

    test_is_trivially_destructible<int (&)(int)>();
    test_is_trivially_destructible<int (&)(int) noexcept>();

    test_is_trivially_destructible<int (&)(...)>();
    test_is_trivially_destructible<int (&)(...) noexcept>();

    test_is_trivially_destructible<int (&)(int, ...)>();
    test_is_trivially_destructible<int (&)(int, ...) noexcept>();

    test_is_trivially_destructible<void(&&)()>();
    test_is_trivially_destructible<void(&&)() noexcept>();

    test_is_trivially_destructible<void(&&)(int)>();
    test_is_trivially_destructible<void(&&)(int) noexcept>();

    test_is_trivially_destructible<void(&&)(...)>();
    test_is_trivially_destructible<void(&&)(...) noexcept>();

    test_is_trivially_destructible<void(&&)(int, ...)>();
    test_is_trivially_destructible<void(&&)(int, ...) noexcept>();

    test_is_trivially_destructible<int(&&)()>();
    test_is_trivially_destructible<int(&&)() noexcept>();

    test_is_trivially_destructible<int(&&)(int)>();
    test_is_trivially_destructible<int(&&)(int) noexcept>();

    test_is_trivially_destructible<int(&&)(...)>();
    test_is_trivially_destructible<int(&&)(...) noexcept>();

    test_is_trivially_destructible<int(&&)(int, ...)>();
    test_is_trivially_destructible<int(&&)(int, ...) noexcept>();

    test_is_trivially_destructible<void (Class::*)()>();
    test_is_trivially_destructible<void (Class::*)()&>();
    test_is_trivially_destructible<void (Class::*)() &&>();
    test_is_trivially_destructible<void (Class::*)() const>();
    test_is_trivially_destructible<void (Class::*)() const&>();
    test_is_trivially_destructible<void (Class::*)() const&&>();
    test_is_trivially_destructible<void (Class::*)() noexcept>();
    test_is_trivially_destructible<void (Class::*)()& noexcept>();
    test_is_trivially_destructible<void (Class::*)()&& noexcept>();
    test_is_trivially_destructible<void (Class::*)() const noexcept>();
    test_is_trivially_destructible<void (Class::*)() const& noexcept>();
    test_is_trivially_destructible<void (Class::*)() const&& noexcept>();

    test_is_trivially_destructible<void (Class::*)(int)>();
    test_is_trivially_destructible<void (Class::*)(int)&>();
    test_is_trivially_destructible<void (Class::*)(int) &&>();
    test_is_trivially_destructible<void (Class::*)(int) const>();
    test_is_trivially_destructible<void (Class::*)(int) const&>();
    test_is_trivially_destructible<void (Class::*)(int) const&&>();
    test_is_trivially_destructible<void (Class::*)(int) noexcept>();
    test_is_trivially_destructible<void (Class::*)(int)& noexcept>();
    test_is_trivially_destructible<void (Class::*)(int)&& noexcept>();
    test_is_trivially_destructible<void (Class::*)(int) const noexcept>();
    test_is_trivially_destructible<void (Class::*)(int) const& noexcept>();
    test_is_trivially_destructible<void (Class::*)(int) const&& noexcept>();

    test_is_trivially_destructible<void (Class::*)(...)>();
    test_is_trivially_destructible<void (Class::*)(...)&>();
    test_is_trivially_destructible<void (Class::*)(...) &&>();
    test_is_trivially_destructible<void (Class::*)(...) const>();
    test_is_trivially_destructible<void (Class::*)(...) const&>();
    test_is_trivially_destructible<void (Class::*)(...) const&&>();
    test_is_trivially_destructible<void (Class::*)(...) noexcept>();
    test_is_trivially_destructible<void (Class::*)(...)& noexcept>();
    test_is_trivially_destructible<void (Class::*)(...)&& noexcept>();
    test_is_trivially_destructible<void (Class::*)(...) const noexcept>();
    test_is_trivially_destructible<void (Class::*)(...) const& noexcept>();
    test_is_trivially_destructible<void (Class::*)(...) const&& noexcept>();

    test_is_trivially_destructible<void (Class::*)(int, ...)>();
    test_is_trivially_destructible<void (Class::*)(int, ...)&>();
    test_is_trivially_destructible<void (Class::*)(int, ...) &&>();
    test_is_trivially_destructible<void (Class::*)(int, ...) const>();
    test_is_trivially_destructible<void (Class::*)(int, ...) const&>();
    test_is_trivially_destructible<void (Class::*)(int, ...) const&&>();
    test_is_trivially_destructible<void (Class::*)(int, ...) noexcept>();
    test_is_trivially_destructible<void (Class::*)(int, ...)& noexcept>();
    test_is_trivially_destructible<void (Class::*)(int, ...)&& noexcept>();
    test_is_trivially_destructible<void (Class::*)(int, ...) const noexcept>();
    test_is_trivially_destructible<void (Class::*)(int, ...) const& noexcept>();
    test_is_trivially_destructible<void (Class::*)(int, ...) const&& noexcept>();

    test_is_trivially_destructible<int (Class::*)()>();
    test_is_trivially_destructible<int (Class::*)()&>();
    test_is_trivially_destructible<int (Class::*)() &&>();
    test_is_trivially_destructible<int (Class::*)() const>();
    test_is_trivially_destructible<int (Class::*)() const&>();
    test_is_trivially_destructible<int (Class::*)() const&&>();
    test_is_trivially_destructible<int (Class::*)() noexcept>();
    test_is_trivially_destructible<int (Class::*)()& noexcept>();
    test_is_trivially_destructible<int (Class::*)()&& noexcept>();
    test_is_trivially_destructible<int (Class::*)() const noexcept>();
    test_is_trivially_destructible<int (Class::*)() const& noexcept>();
    test_is_trivially_destructible<int (Class::*)() const&& noexcept>();

    test_is_trivially_destructible<int (Class::*)(int)>();
    test_is_trivially_destructible<int (Class::*)(int)&>();
    test_is_trivially_destructible<int (Class::*)(int) &&>();
    test_is_trivially_destructible<int (Class::*)(int) const>();
    test_is_trivially_destructible<int (Class::*)(int) const&>();
    test_is_trivially_destructible<int (Class::*)(int) const&&>();
    test_is_trivially_destructible<int (Class::*)(int) noexcept>();
    test_is_trivially_destructible<int (Class::*)(int)& noexcept>();
    test_is_trivially_destructible<int (Class::*)(int)&& noexcept>();
    test_is_trivially_destructible<int (Class::*)(int) const noexcept>();
    test_is_trivially_destructible<int (Class::*)(int) const& noexcept>();
    test_is_trivially_destructible<int (Class::*)(int) const&& noexcept>();

    test_is_trivially_destructible<int (Class::*)(...)>();
    test_is_trivially_destructible<int (Class::*)(...)&>();
    test_is_trivially_destructible<int (Class::*)(...) &&>();
    test_is_trivially_destructible<int (Class::*)(...) const>();
    test_is_trivially_destructible<int (Class::*)(...) const&>();
    test_is_trivially_destructible<int (Class::*)(...) const&&>();
    test_is_trivially_destructible<int (Class::*)(...) noexcept>();
    test_is_trivially_destructible<int (Class::*)(...)& noexcept>();
    test_is_trivially_destructible<int (Class::*)(...)&& noexcept>();
    test_is_trivially_destructible<int (Class::*)(...) const noexcept>();
    test_is_trivially_destructible<int (Class::*)(...) const& noexcept>();
    test_is_trivially_destructible<int (Class::*)(...) const&& noexcept>();

    test_is_trivially_destructible<int (Class::*)(int, ...)>();
    test_is_trivially_destructible<int (Class::*)(int, ...)&>();
    test_is_trivially_destructible<int (Class::*)(int, ...) &&>();
    test_is_trivially_destructible<int (Class::*)(int, ...) const>();
    test_is_trivially_destructible<int (Class::*)(int, ...) const&>();
    test_is_trivially_destructible<int (Class::*)(int, ...) const&&>();
    test_is_trivially_destructible<int (Class::*)(int, ...) noexcept>();
    test_is_trivially_destructible<int (Class::*)(int, ...)& noexcept>();
    test_is_trivially_destructible<int (Class::*)(int, ...)&& noexcept>();
    test_is_trivially_destructible<int (Class::*)(int, ...) const noexcept>();
    test_is_trivially_destructible<int (Class::*)(int, ...) const& noexcept>();
    test_is_trivially_destructible<int (Class::*)(int, ...) const&& noexcept>();
}
