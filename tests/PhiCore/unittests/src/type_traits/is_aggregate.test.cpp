#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_aggregate.hpp>
#include <type_traits>
#include <vector>

// TODO: No idea why gcc thinks some types here are aggregate although they aren't

template <typename T>
void test_is_aggregate_impl()
{
    STATIC_REQUIRE(phi::is_aggregate<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_aggregate<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_aggregate_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_aggregate_v<T>);
#endif

#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    // standard compatbility
    STATIC_REQUIRE(std::is_aggregate<T>::value);
#endif
}

template <typename T>
void test_is_aggregate()
{
    test_is_aggregate_impl<T>();
    test_is_aggregate_impl<const T>();
    test_is_aggregate_impl<volatile T>();
    test_is_aggregate_impl<const volatile T>();
}

template <typename T>
void test_is_not_aggregate_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_aggregate<T>::value);
    STATIC_REQUIRE(phi::is_not_aggregate<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_aggregate_v<T>);
    STATIC_REQUIRE(phi::is_not_aggregate_v<T>);
#endif

#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    // standard compatbility
    STATIC_REQUIRE_FALSE(std::is_aggregate<T>::value);
#endif
}

template <typename T>
void test_is_not_aggregate()
{
    test_is_not_aggregate_impl<T>();
    test_is_not_aggregate_impl<const T>();
    test_is_not_aggregate_impl<volatile T>();
    test_is_not_aggregate_impl<const volatile T>();
}

struct Aggregate
{};

struct HasCons
{
    HasCons(int);
};

struct PublicMembers
{
    int    x;
    double y;
};

struct HasPriv
{
    void PreventUnusedPrivateMemberWarning();

private:
    int x;
};

TEST_CASE("is_aggregate")
{
    test_is_aggregate<Aggregate>();
    test_is_aggregate<Aggregate[]>();
    test_is_aggregate<Aggregate[2]>();
    test_is_aggregate<Aggregate[42][101]>();
    test_is_aggregate<PublicMembers>();

    test_is_not_aggregate<void (Aggregate::*)(int) const>();
    test_is_not_aggregate<Aggregate&>();
    test_is_not_aggregate<HasCons>();
    test_is_not_aggregate<HasPriv>();

    test_is_not_aggregate<void>();
    test_is_not_aggregate<phi::nullptr_t>();
    test_is_not_aggregate<bool>();
    test_is_not_aggregate<char>();
    test_is_not_aggregate<signed char>();
    test_is_not_aggregate<unsigned char>();
    test_is_not_aggregate<short>();
    test_is_not_aggregate<unsigned short>();
    test_is_not_aggregate<int>();
    test_is_not_aggregate<unsigned int>();
    test_is_not_aggregate<long>();
    test_is_not_aggregate<unsigned long>();
    test_is_not_aggregate<long long>();
    test_is_not_aggregate<unsigned long long>();
    test_is_not_aggregate<float>();
    test_is_not_aggregate<double>();
    test_is_not_aggregate<long double>();
    test_is_not_aggregate<char8_t>();
    test_is_not_aggregate<char16_t>();
    test_is_not_aggregate<char32_t>();
    test_is_not_aggregate<wchar_t>();

    test_is_not_aggregate<phi::boolean>();
    test_is_not_aggregate<phi::integer<signed char>>();
    test_is_not_aggregate<phi::integer<unsigned char>>();
    test_is_not_aggregate<phi::integer<short>>();
    test_is_not_aggregate<phi::integer<unsigned short>>();
    test_is_not_aggregate<phi::integer<int>>();
    test_is_not_aggregate<phi::integer<unsigned int>>();
    test_is_not_aggregate<phi::integer<long>>();
    test_is_not_aggregate<phi::integer<unsigned long>>();
    test_is_not_aggregate<phi::integer<long long>>();
    test_is_not_aggregate<phi::integer<unsigned long long>>();
    test_is_not_aggregate<phi::floating_point<float>>();
    test_is_not_aggregate<phi::floating_point<double>>();
    test_is_not_aggregate<phi::floating_point<long double>>();

    test_is_not_aggregate<std::vector<int>>();
    test_is_not_aggregate<phi::scope_ptr<int>>();

    test_is_not_aggregate<int&>();
    test_is_not_aggregate<const int&>();
    test_is_not_aggregate<volatile int&>();
    test_is_not_aggregate<const volatile int&>();
    test_is_not_aggregate<int&&>();
    test_is_not_aggregate<const int&&>();
    test_is_not_aggregate<volatile int&&>();
    test_is_not_aggregate<const volatile int&&>();
    test_is_not_aggregate<int*>();
    test_is_not_aggregate<const int*>();
    test_is_not_aggregate<volatile int*>();
    test_is_not_aggregate<const volatile int*>();
    test_is_not_aggregate<int**>();
    test_is_not_aggregate<const int**>();
    test_is_not_aggregate<volatile int**>();
    test_is_not_aggregate<const volatile int**>();
    test_is_not_aggregate<int*&>();
    test_is_not_aggregate<const int*&>();
    test_is_not_aggregate<volatile int*&>();
    test_is_not_aggregate<const volatile int*&>();
    test_is_not_aggregate<int*&&>();
    test_is_not_aggregate<const int*&&>();
    test_is_not_aggregate<volatile int*&&>();
    test_is_not_aggregate<const volatile int*&&>();
    test_is_not_aggregate<void*>();
    test_is_aggregate<char[3]>();
    test_is_aggregate<char[]>();
    test_is_aggregate<char[3]>();
    test_is_aggregate<char[]>();
    test_is_aggregate<char* [3]>();
    test_is_aggregate<char*[]>();
    test_is_not_aggregate<int(*)[3]>();
    test_is_not_aggregate<int(*)[]>();
    test_is_not_aggregate<int(&)[3]>();
    test_is_not_aggregate<int(&)[]>();
    test_is_not_aggregate<int(&&)[3]>();
    test_is_not_aggregate<int(&&)[]>();
    test_is_aggregate<char[3][2]>();
    test_is_aggregate<char[][2]>();
    test_is_aggregate<char* [3][2]>();
    test_is_aggregate<char*[][2]>();
    test_is_not_aggregate<int(*)[3][2]>();
    test_is_not_aggregate<int(*)[][2]>();
    test_is_not_aggregate<int(&)[3][2]>();
    test_is_not_aggregate<int(&)[][2]>();
    test_is_not_aggregate<int(&&)[3][2]>();
    test_is_not_aggregate<int(&&)[][2]>();
    test_is_aggregate<Class>();
    test_is_aggregate<Class[]>();
    test_is_aggregate<Class[2]>();
    test_is_aggregate<Template<void>>();
    test_is_aggregate<Template<int>>();
    test_is_aggregate<Template<Class>>();
    test_is_aggregate<Template<incomplete_type>>();
    test_is_aggregate<VariadicTemplate<>>();
    test_is_aggregate<VariadicTemplate<void>>();
    test_is_aggregate<VariadicTemplate<int>>();
    test_is_aggregate<VariadicTemplate<Class>>();
    test_is_aggregate<VariadicTemplate<incomplete_type>>();
    test_is_aggregate<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_aggregate<PublicDerviedFromTemplate<Base>>();
    test_is_aggregate<PublicDerviedFromTemplate<Derived>>();
    test_is_aggregate<PublicDerviedFromTemplate<Class>>();
    test_is_not_aggregate<PrivateDerviedFromTemplate<Base>>();
    test_is_not_aggregate<PrivateDerviedFromTemplate<Derived>>();
    test_is_not_aggregate<PrivateDerviedFromTemplate<Class>>();
    test_is_not_aggregate<ProtectedDerviedFromTemplate<Base>>();
    test_is_not_aggregate<ProtectedDerviedFromTemplate<Derived>>();
    test_is_not_aggregate<ProtectedDerviedFromTemplate<Class>>();
    test_is_aggregate<Union>();
    test_is_aggregate<NonEmptyUnion>();
    test_is_aggregate<Empty>();
    test_is_not_aggregate<NotEmpty>();
    test_is_aggregate<bit_zero>();
    test_is_aggregate<bit_one>();
    test_is_aggregate<Base>();
    test_is_aggregate<Derived>();
    test_is_not_aggregate<Abstract>();
    test_is_not_aggregate<PublicAbstract>();
    test_is_not_aggregate<PrivateAbstract>();
    test_is_not_aggregate<ProtectedAbstract>();
    test_is_not_aggregate<AbstractTemplate<int>>();
    test_is_aggregate<AbstractTemplate<double>>();
    test_is_not_aggregate<AbstractTemplate<Class>>();
    test_is_not_aggregate<AbstractTemplate<incomplete_type>>();
    test_is_aggregate<Final>();
    test_is_aggregate<PublicDestructor>();
    test_is_aggregate<ProtectedDestructor>();
    test_is_aggregate<PrivateDestructor>();
    test_is_not_aggregate<VirtualPublicDestructor>();
    test_is_not_aggregate<VirtualProtectedDestructor>();
    test_is_not_aggregate<VirtualPrivateDestructor>();
    test_is_not_aggregate<PurePublicDestructor>();
    test_is_not_aggregate<PureProtectedDestructor>();
    test_is_not_aggregate<PurePrivateDestructor>();
    test_is_aggregate<DeletedPublicDestructor>();
    test_is_aggregate<DeletedProtectedDestructor>();
    test_is_aggregate<DeletedPrivateDestructor>();
    test_is_not_aggregate<DeletedVirtualPublicDestructor>();
    test_is_not_aggregate<DeletedVirtualProtectedDestructor>();
    test_is_not_aggregate<DeletedVirtualPrivateDestructor>();
    test_is_not_aggregate<Enum>();
    test_is_not_aggregate<EnumSigned>();
    test_is_not_aggregate<EnumUnsigned>();
    test_is_not_aggregate<EnumClass>();
    test_is_not_aggregate<EnumStruct>();
    test_is_not_aggregate<Function>();
    test_is_not_aggregate<FunctionPtr>();
    test_is_not_aggregate<MemberObjectPtr>();
    test_is_not_aggregate<MemberFunctionPtr>();
    test_is_not_aggregate<int Class::*>();
    test_is_not_aggregate<float Class::*>();
    test_is_not_aggregate<void * Class::*>();
    test_is_not_aggregate<int * Class::*>();
    test_is_not_aggregate<int Class::*&>();
    test_is_not_aggregate<float Class::*&>();
    test_is_not_aggregate<void * Class::*&>();
    test_is_not_aggregate<int * Class::*&>();
    test_is_not_aggregate<int Class::*&&>();
    test_is_not_aggregate<float Class::*&&>();
    test_is_not_aggregate<void * Class::*&&>();
    test_is_not_aggregate<int * Class::*&&>();
    test_is_not_aggregate<int Class::*const>();
    test_is_not_aggregate<float Class::*const>();
    test_is_not_aggregate<void * Class::*const>();
    test_is_not_aggregate<int Class::*const&>();
    test_is_not_aggregate<float Class::*const&>();
    test_is_not_aggregate<void * Class::*const&>();
    test_is_not_aggregate<int Class::*const&&>();
    test_is_not_aggregate<float Class::*const&&>();
    test_is_not_aggregate<void * Class::*const&&>();
    test_is_not_aggregate<int Class::*volatile>();
    test_is_not_aggregate<float Class::*volatile>();
    test_is_not_aggregate<void * Class::*volatile>();
    test_is_not_aggregate<int Class::*volatile&>();
    test_is_not_aggregate<float Class::*volatile&>();
    test_is_not_aggregate<void * Class::*volatile&>();
    test_is_not_aggregate<int Class::*volatile&&>();
    test_is_not_aggregate<float Class::*volatile&&>();
    test_is_not_aggregate<void * Class::*volatile&&>();
    test_is_not_aggregate<int Class::*const volatile>();
    test_is_not_aggregate<float Class::*const volatile>();
    test_is_not_aggregate<void * Class::*const volatile>();
    test_is_not_aggregate<int Class::*const volatile&>();
    test_is_not_aggregate<float Class::*const volatile&>();
    test_is_not_aggregate<void * Class::*const volatile&>();
    test_is_not_aggregate<int Class::*const volatile&&>();
    test_is_not_aggregate<float Class::*const volatile&&>();
    test_is_not_aggregate<void * Class::*const volatile&&>();
    test_is_not_aggregate<NonCopyable>();
    test_is_not_aggregate<NonMoveable>();
    test_is_not_aggregate<NonConstructible>();
    test_is_not_aggregate<Tracked>();
    test_is_not_aggregate<TrapConstructible>();
    test_is_aggregate<TrapImplicitConversion>();
    test_is_aggregate<TrapComma>();
    test_is_aggregate<TrapCall>();
    test_is_not_aggregate<TrapSelfAssign>();
    test_is_aggregate<TrapDeref>();
    test_is_aggregate<TrapArraySubscript>();

    test_is_not_aggregate<void()>();
    test_is_not_aggregate<void()&>();
    test_is_not_aggregate<void() &&>();
    test_is_not_aggregate<void() const>();
    test_is_not_aggregate<void() const&>();
    test_is_not_aggregate<void() const&&>();
    test_is_not_aggregate<void() volatile>();
    test_is_not_aggregate<void() volatile&>();
    test_is_not_aggregate<void() volatile&&>();
    test_is_not_aggregate<void() const volatile>();
    test_is_not_aggregate<void() const volatile&>();
    test_is_not_aggregate<void() const volatile&&>();
    test_is_not_aggregate<void() noexcept>();
    test_is_not_aggregate<void()& noexcept>();
    test_is_not_aggregate<void()&& noexcept>();
    test_is_not_aggregate<void() const noexcept>();
    test_is_not_aggregate<void() const& noexcept>();
    test_is_not_aggregate<void() const&& noexcept>();
    test_is_not_aggregate<void() volatile noexcept>();
    test_is_not_aggregate<void() volatile& noexcept>();
    test_is_not_aggregate<void() volatile&& noexcept>();
    test_is_not_aggregate<void() const volatile noexcept>();
    test_is_not_aggregate<void() const volatile& noexcept>();
    test_is_not_aggregate<void() const volatile&& noexcept>();

    test_is_not_aggregate<void(int)>();
    test_is_not_aggregate<void(int)&>();
    test_is_not_aggregate<void(int) &&>();
    test_is_not_aggregate<void(int) const>();
    test_is_not_aggregate<void(int) const&>();
    test_is_not_aggregate<void(int) const&&>();
    test_is_not_aggregate<void(int) volatile>();
    test_is_not_aggregate<void(int) volatile&>();
    test_is_not_aggregate<void(int) volatile&&>();
    test_is_not_aggregate<void(int) const volatile>();
    test_is_not_aggregate<void(int) const volatile&>();
    test_is_not_aggregate<void(int) const volatile&&>();
    test_is_not_aggregate<void(int) noexcept>();
    test_is_not_aggregate<void(int)& noexcept>();
    test_is_not_aggregate<void(int)&& noexcept>();
    test_is_not_aggregate<void(int) const noexcept>();
    test_is_not_aggregate<void(int) const& noexcept>();
    test_is_not_aggregate<void(int) const&& noexcept>();
    test_is_not_aggregate<void(int) volatile noexcept>();
    test_is_not_aggregate<void(int) volatile& noexcept>();
    test_is_not_aggregate<void(int) volatile&& noexcept>();
    test_is_not_aggregate<void(int) const volatile noexcept>();
    test_is_not_aggregate<void(int) const volatile& noexcept>();
    test_is_not_aggregate<void(int) const volatile&& noexcept>();

    test_is_not_aggregate<void(...)>();
    test_is_not_aggregate<void(...)&>();
    test_is_not_aggregate<void(...) &&>();
    test_is_not_aggregate<void(...) const>();
    test_is_not_aggregate<void(...) const&>();
    test_is_not_aggregate<void(...) const&&>();
    test_is_not_aggregate<void(...) volatile>();
    test_is_not_aggregate<void(...) volatile&>();
    test_is_not_aggregate<void(...) volatile&&>();
    test_is_not_aggregate<void(...) const volatile>();
    test_is_not_aggregate<void(...) const volatile&>();
    test_is_not_aggregate<void(...) const volatile&&>();
    test_is_not_aggregate<void(...) noexcept>();
    test_is_not_aggregate<void(...)& noexcept>();
    test_is_not_aggregate<void(...)&& noexcept>();
    test_is_not_aggregate<void(...) const noexcept>();
    test_is_not_aggregate<void(...) const& noexcept>();
    test_is_not_aggregate<void(...) const&& noexcept>();
    test_is_not_aggregate<void(...) volatile noexcept>();
    test_is_not_aggregate<void(...) volatile& noexcept>();
    test_is_not_aggregate<void(...) volatile&& noexcept>();
    test_is_not_aggregate<void(...) const volatile noexcept>();
    test_is_not_aggregate<void(...) const volatile& noexcept>();
    test_is_not_aggregate<void(...) const volatile&& noexcept>();

    test_is_not_aggregate<void(int, ...)>();
    test_is_not_aggregate<void(int, ...)&>();
    test_is_not_aggregate<void(int, ...) &&>();
    test_is_not_aggregate<void(int, ...) const>();
    test_is_not_aggregate<void(int, ...) const&>();
    test_is_not_aggregate<void(int, ...) const&&>();
    test_is_not_aggregate<void(int, ...) volatile>();
    test_is_not_aggregate<void(int, ...) volatile&>();
    test_is_not_aggregate<void(int, ...) volatile&&>();
    test_is_not_aggregate<void(int, ...) const volatile>();
    test_is_not_aggregate<void(int, ...) const volatile&>();
    test_is_not_aggregate<void(int, ...) const volatile&&>();
    test_is_not_aggregate<void(int, ...) noexcept>();
    test_is_not_aggregate<void(int, ...)& noexcept>();
    test_is_not_aggregate<void(int, ...)&& noexcept>();
    test_is_not_aggregate<void(int, ...) const noexcept>();
    test_is_not_aggregate<void(int, ...) const& noexcept>();
    test_is_not_aggregate<void(int, ...) const&& noexcept>();
    test_is_not_aggregate<void(int, ...) volatile noexcept>();
    test_is_not_aggregate<void(int, ...) volatile& noexcept>();
    test_is_not_aggregate<void(int, ...) volatile&& noexcept>();
    test_is_not_aggregate<void(int, ...) const volatile noexcept>();
    test_is_not_aggregate<void(int, ...) const volatile& noexcept>();
    test_is_not_aggregate<void(int, ...) const volatile&& noexcept>();

    test_is_not_aggregate<int()>();
    test_is_not_aggregate<int()&>();
    test_is_not_aggregate<int() &&>();
    test_is_not_aggregate<int() const>();
    test_is_not_aggregate<int() const&>();
    test_is_not_aggregate<int() const&&>();
    test_is_not_aggregate<int() volatile>();
    test_is_not_aggregate<int() volatile&>();
    test_is_not_aggregate<int() volatile&&>();
    test_is_not_aggregate<int() const volatile>();
    test_is_not_aggregate<int() const volatile&>();
    test_is_not_aggregate<int() const volatile&&>();
    test_is_not_aggregate<int() noexcept>();
    test_is_not_aggregate<int()& noexcept>();
    test_is_not_aggregate<int()&& noexcept>();
    test_is_not_aggregate<int() const noexcept>();
    test_is_not_aggregate<int() const& noexcept>();
    test_is_not_aggregate<int() const&& noexcept>();
    test_is_not_aggregate<int() volatile noexcept>();
    test_is_not_aggregate<int() volatile& noexcept>();
    test_is_not_aggregate<int() volatile&& noexcept>();
    test_is_not_aggregate<int() const volatile noexcept>();
    test_is_not_aggregate<int() const volatile& noexcept>();
    test_is_not_aggregate<int() const volatile&& noexcept>();

    test_is_not_aggregate<int(int)>();
    test_is_not_aggregate<int(int)&>();
    test_is_not_aggregate<int(int) &&>();
    test_is_not_aggregate<int(int) const>();
    test_is_not_aggregate<int(int) const&>();
    test_is_not_aggregate<int(int) const&&>();
    test_is_not_aggregate<int(int) volatile>();
    test_is_not_aggregate<int(int) volatile&>();
    test_is_not_aggregate<int(int) volatile&&>();
    test_is_not_aggregate<int(int) const volatile>();
    test_is_not_aggregate<int(int) const volatile&>();
    test_is_not_aggregate<int(int) const volatile&&>();
    test_is_not_aggregate<int(int) noexcept>();
    test_is_not_aggregate<int(int)& noexcept>();
    test_is_not_aggregate<int(int)&& noexcept>();
    test_is_not_aggregate<int(int) const noexcept>();
    test_is_not_aggregate<int(int) const& noexcept>();
    test_is_not_aggregate<int(int) const&& noexcept>();
    test_is_not_aggregate<int(int) volatile noexcept>();
    test_is_not_aggregate<int(int) volatile& noexcept>();
    test_is_not_aggregate<int(int) volatile&& noexcept>();
    test_is_not_aggregate<int(int) const volatile noexcept>();
    test_is_not_aggregate<int(int) const volatile& noexcept>();
    test_is_not_aggregate<int(int) const volatile&& noexcept>();

    test_is_not_aggregate<int(...)>();
    test_is_not_aggregate<int(...)&>();
    test_is_not_aggregate<int(...) &&>();
    test_is_not_aggregate<int(...) const>();
    test_is_not_aggregate<int(...) const&>();
    test_is_not_aggregate<int(...) const&&>();
    test_is_not_aggregate<int(...) volatile>();
    test_is_not_aggregate<int(...) volatile&>();
    test_is_not_aggregate<int(...) volatile&&>();
    test_is_not_aggregate<int(...) const volatile>();
    test_is_not_aggregate<int(...) const volatile&>();
    test_is_not_aggregate<int(...) const volatile&&>();
    test_is_not_aggregate<int(...) noexcept>();
    test_is_not_aggregate<int(...)& noexcept>();
    test_is_not_aggregate<int(...)&& noexcept>();
    test_is_not_aggregate<int(...) const noexcept>();
    test_is_not_aggregate<int(...) const& noexcept>();
    test_is_not_aggregate<int(...) const&& noexcept>();
    test_is_not_aggregate<int(...) volatile noexcept>();
    test_is_not_aggregate<int(...) volatile& noexcept>();
    test_is_not_aggregate<int(...) volatile&& noexcept>();
    test_is_not_aggregate<int(...) const volatile noexcept>();
    test_is_not_aggregate<int(...) const volatile& noexcept>();
    test_is_not_aggregate<int(...) const volatile&& noexcept>();

    test_is_not_aggregate<int(int, ...)>();
    test_is_not_aggregate<int(int, ...)&>();
    test_is_not_aggregate<int(int, ...) &&>();
    test_is_not_aggregate<int(int, ...) const>();
    test_is_not_aggregate<int(int, ...) const&>();
    test_is_not_aggregate<int(int, ...) const&&>();
    test_is_not_aggregate<int(int, ...) volatile>();
    test_is_not_aggregate<int(int, ...) volatile&>();
    test_is_not_aggregate<int(int, ...) volatile&&>();
    test_is_not_aggregate<int(int, ...) const volatile>();
    test_is_not_aggregate<int(int, ...) const volatile&>();
    test_is_not_aggregate<int(int, ...) const volatile&&>();
    test_is_not_aggregate<int(int, ...) noexcept>();
    test_is_not_aggregate<int(int, ...)& noexcept>();
    test_is_not_aggregate<int(int, ...)&& noexcept>();
    test_is_not_aggregate<int(int, ...) const noexcept>();
    test_is_not_aggregate<int(int, ...) const& noexcept>();
    test_is_not_aggregate<int(int, ...) const&& noexcept>();
    test_is_not_aggregate<int(int, ...) volatile noexcept>();
    test_is_not_aggregate<int(int, ...) volatile& noexcept>();
    test_is_not_aggregate<int(int, ...) volatile&& noexcept>();
    test_is_not_aggregate<int(int, ...) const volatile noexcept>();
    test_is_not_aggregate<int(int, ...) const volatile& noexcept>();
    test_is_not_aggregate<int(int, ...) const volatile&& noexcept>();

    test_is_not_aggregate<void (*)()>();
    test_is_not_aggregate<void (*)() noexcept>();

    test_is_not_aggregate<void (*)(int)>();
    test_is_not_aggregate<void (*)(int) noexcept>();

    test_is_not_aggregate<void (*)(...)>();
    test_is_not_aggregate<void (*)(...) noexcept>();

    test_is_not_aggregate<void (*)(int, ...)>();
    test_is_not_aggregate<void (*)(int, ...) noexcept>();

    test_is_not_aggregate<int (*)()>();
    test_is_not_aggregate<int (*)() noexcept>();

    test_is_not_aggregate<int (*)(int)>();
    test_is_not_aggregate<int (*)(int) noexcept>();

    test_is_not_aggregate<int (*)(...)>();
    test_is_not_aggregate<int (*)(...) noexcept>();

    test_is_not_aggregate<int (*)(int, ...)>();
    test_is_not_aggregate<int (*)(int, ...) noexcept>();

    test_is_not_aggregate<void (&)()>();
    test_is_not_aggregate<void (&)() noexcept>();

    test_is_not_aggregate<void (&)(int)>();
    test_is_not_aggregate<void (&)(int) noexcept>();

    test_is_not_aggregate<void (&)(...)>();
    test_is_not_aggregate<void (&)(...) noexcept>();

    test_is_not_aggregate<void (&)(int, ...)>();
    test_is_not_aggregate<void (&)(int, ...) noexcept>();

    test_is_not_aggregate<int (&)()>();
    test_is_not_aggregate<int (&)() noexcept>();

    test_is_not_aggregate<int (&)(int)>();
    test_is_not_aggregate<int (&)(int) noexcept>();

    test_is_not_aggregate<int (&)(...)>();
    test_is_not_aggregate<int (&)(...) noexcept>();

    test_is_not_aggregate<int (&)(int, ...)>();
    test_is_not_aggregate<int (&)(int, ...) noexcept>();

    test_is_not_aggregate<void(&&)()>();
    test_is_not_aggregate<void(&&)() noexcept>();

    test_is_not_aggregate<void(&&)(int)>();
    test_is_not_aggregate<void(&&)(int) noexcept>();

    test_is_not_aggregate<void(&&)(...)>();
    test_is_not_aggregate<void(&&)(...) noexcept>();

    test_is_not_aggregate<void(&&)(int, ...)>();
    test_is_not_aggregate<void(&&)(int, ...) noexcept>();

    test_is_not_aggregate<int(&&)()>();
    test_is_not_aggregate<int(&&)() noexcept>();

    test_is_not_aggregate<int(&&)(int)>();
    test_is_not_aggregate<int(&&)(int) noexcept>();

    test_is_not_aggregate<int(&&)(...)>();
    test_is_not_aggregate<int(&&)(...) noexcept>();

    test_is_not_aggregate<int(&&)(int, ...)>();
    test_is_not_aggregate<int(&&)(int, ...) noexcept>();

    test_is_not_aggregate<void (Class::*)()>();
    test_is_not_aggregate<void (Class::*)()&>();
    test_is_not_aggregate<void (Class::*)() &&>();
    test_is_not_aggregate<void (Class::*)() const>();
    test_is_not_aggregate<void (Class::*)() const&>();
    test_is_not_aggregate<void (Class::*)() const&&>();
    test_is_not_aggregate<void (Class::*)() noexcept>();
    test_is_not_aggregate<void (Class::*)()& noexcept>();
    test_is_not_aggregate<void (Class::*)()&& noexcept>();
    test_is_not_aggregate<void (Class::*)() const noexcept>();
    test_is_not_aggregate<void (Class::*)() const& noexcept>();
    test_is_not_aggregate<void (Class::*)() const&& noexcept>();

    test_is_not_aggregate<void (Class::*)(int)>();
    test_is_not_aggregate<void (Class::*)(int)&>();
    test_is_not_aggregate<void (Class::*)(int) &&>();
    test_is_not_aggregate<void (Class::*)(int) const>();
    test_is_not_aggregate<void (Class::*)(int) const&>();
    test_is_not_aggregate<void (Class::*)(int) const&&>();
    test_is_not_aggregate<void (Class::*)(int) noexcept>();
    test_is_not_aggregate<void (Class::*)(int)& noexcept>();
    test_is_not_aggregate<void (Class::*)(int)&& noexcept>();
    test_is_not_aggregate<void (Class::*)(int) const noexcept>();
    test_is_not_aggregate<void (Class::*)(int) const& noexcept>();
    test_is_not_aggregate<void (Class::*)(int) const&& noexcept>();

    test_is_not_aggregate<void (Class::*)(...)>();
    test_is_not_aggregate<void (Class::*)(...)&>();
    test_is_not_aggregate<void (Class::*)(...) &&>();
    test_is_not_aggregate<void (Class::*)(...) const>();
    test_is_not_aggregate<void (Class::*)(...) const&>();
    test_is_not_aggregate<void (Class::*)(...) const&&>();
    test_is_not_aggregate<void (Class::*)(...) noexcept>();
    test_is_not_aggregate<void (Class::*)(...)& noexcept>();
    test_is_not_aggregate<void (Class::*)(...)&& noexcept>();
    test_is_not_aggregate<void (Class::*)(...) const noexcept>();
    test_is_not_aggregate<void (Class::*)(...) const& noexcept>();
    test_is_not_aggregate<void (Class::*)(...) const&& noexcept>();

    test_is_not_aggregate<void (Class::*)(int, ...)>();
    test_is_not_aggregate<void (Class::*)(int, ...)&>();
    test_is_not_aggregate<void (Class::*)(int, ...) &&>();
    test_is_not_aggregate<void (Class::*)(int, ...) const>();
    test_is_not_aggregate<void (Class::*)(int, ...) const&>();
    test_is_not_aggregate<void (Class::*)(int, ...) const&&>();
    test_is_not_aggregate<void (Class::*)(int, ...) noexcept>();
    test_is_not_aggregate<void (Class::*)(int, ...)& noexcept>();
    test_is_not_aggregate<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_aggregate<void (Class::*)(int, ...) const noexcept>();
    test_is_not_aggregate<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_aggregate<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_aggregate<int (Class::*)()>();
    test_is_not_aggregate<int (Class::*)()&>();
    test_is_not_aggregate<int (Class::*)() &&>();
    test_is_not_aggregate<int (Class::*)() const>();
    test_is_not_aggregate<int (Class::*)() const&>();
    test_is_not_aggregate<int (Class::*)() const&&>();
    test_is_not_aggregate<int (Class::*)() noexcept>();
    test_is_not_aggregate<int (Class::*)()& noexcept>();
    test_is_not_aggregate<int (Class::*)()&& noexcept>();
    test_is_not_aggregate<int (Class::*)() const noexcept>();
    test_is_not_aggregate<int (Class::*)() const& noexcept>();
    test_is_not_aggregate<int (Class::*)() const&& noexcept>();

    test_is_not_aggregate<int (Class::*)(int)>();
    test_is_not_aggregate<int (Class::*)(int)&>();
    test_is_not_aggregate<int (Class::*)(int) &&>();
    test_is_not_aggregate<int (Class::*)(int) const>();
    test_is_not_aggregate<int (Class::*)(int) const&>();
    test_is_not_aggregate<int (Class::*)(int) const&&>();
    test_is_not_aggregate<int (Class::*)(int) noexcept>();
    test_is_not_aggregate<int (Class::*)(int)& noexcept>();
    test_is_not_aggregate<int (Class::*)(int)&& noexcept>();
    test_is_not_aggregate<int (Class::*)(int) const noexcept>();
    test_is_not_aggregate<int (Class::*)(int) const& noexcept>();
    test_is_not_aggregate<int (Class::*)(int) const&& noexcept>();

    test_is_not_aggregate<int (Class::*)(...)>();
    test_is_not_aggregate<int (Class::*)(...)&>();
    test_is_not_aggregate<int (Class::*)(...) &&>();
    test_is_not_aggregate<int (Class::*)(...) const>();
    test_is_not_aggregate<int (Class::*)(...) const&>();
    test_is_not_aggregate<int (Class::*)(...) const&&>();
    test_is_not_aggregate<int (Class::*)(...) noexcept>();
    test_is_not_aggregate<int (Class::*)(...)& noexcept>();
    test_is_not_aggregate<int (Class::*)(...)&& noexcept>();
    test_is_not_aggregate<int (Class::*)(...) const noexcept>();
    test_is_not_aggregate<int (Class::*)(...) const& noexcept>();
    test_is_not_aggregate<int (Class::*)(...) const&& noexcept>();

    test_is_not_aggregate<int (Class::*)(int, ...)>();
    test_is_not_aggregate<int (Class::*)(int, ...)&>();
    test_is_not_aggregate<int (Class::*)(int, ...) &&>();
    test_is_not_aggregate<int (Class::*)(int, ...) const>();
    test_is_not_aggregate<int (Class::*)(int, ...) const&>();
    test_is_not_aggregate<int (Class::*)(int, ...) const&&>();
    test_is_not_aggregate<int (Class::*)(int, ...) noexcept>();
    test_is_not_aggregate<int (Class::*)(int, ...)& noexcept>();
    test_is_not_aggregate<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_aggregate<int (Class::*)(int, ...) const noexcept>();
    test_is_not_aggregate<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_aggregate<int (Class::*)(int, ...) const&& noexcept>();
}
