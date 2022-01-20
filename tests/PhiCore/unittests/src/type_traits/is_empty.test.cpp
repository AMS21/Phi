#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_empty.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_empty_impl()
{
#if PHI_HAS_WORKING_IS_EMPTY()
    STATIC_REQUIRE(phi::is_empty<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_empty<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_empty_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_empty_v<T>);
#    endif

    // Standard compatibility
    STATIC_REQUIRE(std::is_empty<T>::value);
#endif
}

template <typename T>
void test_is_empty()
{
    test_is_empty_impl<T>();
    test_is_empty_impl<const T>();
    test_is_empty_impl<volatile T>();
    test_is_empty_impl<const volatile T>();
}

template <typename T>
void test_is_not_empty_impl()
{
#if PHI_HAS_WORKING_IS_EMPTY()
    STATIC_REQUIRE_FALSE(phi::is_empty<T>::value);
    STATIC_REQUIRE(phi::is_not_empty<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_empty_v<T>);
    STATIC_REQUIRE(phi::is_not_empty_v<T>);
#    endif

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_empty<T>::value);
#endif
}

template <typename T>
void test_is_not_empty()
{
    test_is_not_empty_impl<T>();
    test_is_not_empty_impl<const T>();
    test_is_not_empty_impl<volatile T>();
    test_is_not_empty_impl<const volatile T>();
}

class VirtualFn
{
    virtual ~VirtualFn();
};

struct NotEmptyBase : public NotEmpty
{};

struct EmptyBase : public Empty
{};

struct VirtualBase : virtual Empty
{};

struct StaticMember
{
    static int foo;
};

struct NonStaticMember
{
    int foo;
};

TEST_CASE("is_empty")
{
    test_is_not_empty<VirtualFn>();
    test_is_not_empty<VirtualBase>();
    test_is_not_empty<NotEmptyBase>();
    test_is_not_empty<NonStaticMember>();
    test_is_empty<EmptyBase>();
    test_is_empty<StaticMember>();

    test_is_not_empty<void>();
    test_is_not_empty<phi::nullptr_t>();
    test_is_not_empty<bool>();
    test_is_not_empty<char>();
    test_is_not_empty<signed char>();
    test_is_not_empty<unsigned char>();
    test_is_not_empty<short>();
    test_is_not_empty<unsigned short>();
    test_is_not_empty<int>();
    test_is_not_empty<unsigned int>();
    test_is_not_empty<long>();
    test_is_not_empty<unsigned long>();
    test_is_not_empty<long long>();
    test_is_not_empty<unsigned long long>();
    test_is_not_empty<float>();
    test_is_not_empty<double>();
    test_is_not_empty<long double>();
    test_is_not_empty<char8_t>();
    test_is_not_empty<char16_t>();
    test_is_not_empty<char32_t>();
    test_is_not_empty<wchar_t>();

    test_is_not_empty<phi::boolean>();
    test_is_not_empty<phi::integer<signed char>>();
    test_is_not_empty<phi::integer<unsigned char>>();
    test_is_not_empty<phi::integer<short>>();
    test_is_not_empty<phi::integer<unsigned short>>();
    test_is_not_empty<phi::integer<int>>();
    test_is_not_empty<phi::integer<unsigned int>>();
    test_is_not_empty<phi::integer<long>>();
    test_is_not_empty<phi::integer<unsigned long>>();
    test_is_not_empty<phi::integer<long long>>();
    test_is_not_empty<phi::integer<unsigned long long>>();
    test_is_not_empty<phi::floating_point<float>>();
    test_is_not_empty<phi::floating_point<double>>();
    test_is_not_empty<phi::floating_point<long double>>();

    test_is_not_empty<std::vector<int>>();
    test_is_not_empty<phi::scope_ptr<int>>();

    test_is_not_empty<int&>();
    test_is_not_empty<const int&>();
    test_is_not_empty<volatile int&>();
    test_is_not_empty<const volatile int&>();
    test_is_not_empty<int&&>();
    test_is_not_empty<const int&&>();
    test_is_not_empty<volatile int&&>();
    test_is_not_empty<const volatile int&&>();
    test_is_not_empty<int*>();
    test_is_not_empty<const int*>();
    test_is_not_empty<volatile int*>();
    test_is_not_empty<const volatile int*>();
    test_is_not_empty<int**>();
    test_is_not_empty<const int**>();
    test_is_not_empty<volatile int**>();
    test_is_not_empty<const volatile int**>();
    test_is_not_empty<int*&>();
    test_is_not_empty<const int*&>();
    test_is_not_empty<volatile int*&>();
    test_is_not_empty<const volatile int*&>();
    test_is_not_empty<int*&&>();
    test_is_not_empty<const int*&&>();
    test_is_not_empty<volatile int*&&>();
    test_is_not_empty<const volatile int*&&>();
    test_is_not_empty<void*>();
    test_is_not_empty<char[3]>();
    test_is_not_empty<char[]>();
    test_is_not_empty<char* [3]>();
    test_is_not_empty<char*[]>();
    test_is_not_empty<int(*)[3]>();
    test_is_not_empty<int(*)[]>();
    test_is_not_empty<int(&)[3]>();
    test_is_not_empty<int(&)[]>();
    test_is_not_empty<int(&&)[3]>();
    test_is_not_empty<int(&&)[]>();
    test_is_not_empty<char[3][2]>();
    test_is_not_empty<char[][2]>();
    test_is_not_empty<char* [3][2]>();
    test_is_not_empty<char*[][2]>();
    test_is_not_empty<int(*)[3][2]>();
    test_is_not_empty<int(*)[][2]>();
    test_is_not_empty<int(&)[3][2]>();
    test_is_not_empty<int(&)[][2]>();
    test_is_not_empty<int(&&)[3][2]>();
    test_is_not_empty<int(&&)[][2]>();
    test_is_empty<Class>();
    test_is_not_empty<Class[]>();
    test_is_not_empty<Class[2]>();
    test_is_empty<Template<void>>();
    test_is_empty<Template<int>>();
    test_is_empty<Template<Class>>();
    test_is_empty<Template<IncompleteType>>();
    test_is_empty<VariadicTemplate<>>();
    test_is_empty<VariadicTemplate<void>>();
    test_is_empty<VariadicTemplate<int>>();
    test_is_empty<VariadicTemplate<Class>>();
    test_is_empty<VariadicTemplate<IncompleteType>>();
    test_is_empty<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_empty<PublicDerivedFromTemplate<Base>>();
    test_is_empty<PublicDerivedFromTemplate<Derived>>();
    test_is_empty<PublicDerivedFromTemplate<Class>>();
    test_is_empty<PrivateDerivedFromTemplate<Base>>();
    test_is_empty<PrivateDerivedFromTemplate<Derived>>();
    test_is_empty<PrivateDerivedFromTemplate<Class>>();
    test_is_empty<ProtectedDerivedFromTemplate<Base>>();
    test_is_empty<ProtectedDerivedFromTemplate<Derived>>();
    test_is_empty<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_empty<Union>();
    test_is_not_empty<NonEmptyUnion>();
    test_is_empty<Empty>();
    test_is_not_empty<NotEmpty>();
    test_is_empty<BitZero>();
#if PHI_COMPILER_IS_BELOW(EMCC, 1, 39, 0)
    test_is_empty<BitOne>();
#else
    test_is_not_empty<BitOne>();
#endif
    test_is_empty<Base>();
    test_is_empty<Derived>();
    test_is_not_empty<Abstract>();
    test_is_not_empty<PublicAbstract>();
    test_is_not_empty<PrivateAbstract>();
    test_is_not_empty<ProtectedAbstract>();
    test_is_not_empty<AbstractTemplate<int>>();
    test_is_empty<AbstractTemplate<double>>();
    test_is_not_empty<AbstractTemplate<Class>>();
    test_is_not_empty<AbstractTemplate<IncompleteType>>();
    // Final can only be tests with the intrinsic version
#if PHI_SUPPORTS_IS_EMPTY()
    test_is_empty<Final>();
#endif
    test_is_empty<PublicDestructor>();
    test_is_empty<ProtectedDestructor>();
    test_is_empty<PrivateDestructor>();
    test_is_not_empty<VirtualPublicDestructor>();
    test_is_not_empty<VirtualProtectedDestructor>();
    test_is_not_empty<VirtualPrivateDestructor>();
    test_is_not_empty<PurePublicDestructor>();
    test_is_not_empty<PureProtectedDestructor>();
    test_is_not_empty<PurePrivateDestructor>();
    test_is_empty<DeletedPublicDestructor>();
    test_is_empty<DeletedProtectedDestructor>();
    test_is_empty<DeletedPrivateDestructor>();
    test_is_not_empty<DeletedVirtualPublicDestructor>();
    test_is_not_empty<DeletedVirtualProtectedDestructor>();
    test_is_not_empty<DeletedVirtualPrivateDestructor>();
    test_is_not_empty<Enum>();
    test_is_not_empty<EnumSigned>();
    test_is_not_empty<EnumUnsigned>();
    test_is_not_empty<EnumClass>();
    test_is_not_empty<EnumStruct>();
    test_is_not_empty<Function>();
    test_is_not_empty<FunctionPtr>();
    test_is_not_empty<MemberObjectPtr>();
    test_is_not_empty<MemberFunctionPtr>();
    test_is_not_empty<int Class::*>();
    test_is_not_empty<float Class::*>();
    test_is_not_empty<void * Class::*>();
    test_is_not_empty<int * Class::*>();
    test_is_not_empty<int Class::*&>();
    test_is_not_empty<float Class::*&>();
    test_is_not_empty<void * Class::*&>();
    test_is_not_empty<int * Class::*&>();
    test_is_not_empty<int Class::*&&>();
    test_is_not_empty<float Class::*&&>();
    test_is_not_empty<void * Class::*&&>();
    test_is_not_empty<int * Class::*&&>();
    test_is_not_empty<int Class::*const>();
    test_is_not_empty<float Class::*const>();
    test_is_not_empty<void * Class::*const>();
    test_is_not_empty<int Class::*const&>();
    test_is_not_empty<float Class::*const&>();
    test_is_not_empty<void * Class::*const&>();
    test_is_not_empty<int Class::*const&&>();
    test_is_not_empty<float Class::*const&&>();
    test_is_not_empty<void * Class::*const&&>();
    test_is_not_empty<int Class::*volatile>();
    test_is_not_empty<float Class::*volatile>();
    test_is_not_empty<void * Class::*volatile>();
    test_is_not_empty<int Class::*volatile&>();
    test_is_not_empty<float Class::*volatile&>();
    test_is_not_empty<void * Class::*volatile&>();
    test_is_not_empty<int Class::*volatile&&>();
    test_is_not_empty<float Class::*volatile&&>();
    test_is_not_empty<void * Class::*volatile&&>();
    test_is_not_empty<int Class::*const volatile>();
    test_is_not_empty<float Class::*const volatile>();
    test_is_not_empty<void * Class::*const volatile>();
    test_is_not_empty<int Class::*const volatile&>();
    test_is_not_empty<float Class::*const volatile&>();
    test_is_not_empty<void * Class::*const volatile&>();
    test_is_not_empty<int Class::*const volatile&&>();
    test_is_not_empty<float Class::*const volatile&&>();
    test_is_not_empty<void * Class::*const volatile&&>();
    test_is_empty<NonCopyable>();
    test_is_empty<NonMoveable>();
    test_is_empty<NonConstructible>();
    test_is_not_empty<Tracked>();
    test_is_empty<TrapConstructible>();
    test_is_empty<TrapImplicitConversion>();
    test_is_empty<TrapComma>();
    test_is_empty<TrapCall>();
    test_is_empty<TrapSelfAssign>();
    test_is_empty<TrapDeref>();
    test_is_empty<TrapArraySubscript>();

    test_is_not_empty<void()>();
    test_is_not_empty<void()&>();
    test_is_not_empty<void() &&>();
    test_is_not_empty<void() const>();
    test_is_not_empty<void() const&>();
    test_is_not_empty<void() const&&>();
    test_is_not_empty<void() volatile>();
    test_is_not_empty<void() volatile&>();
    test_is_not_empty<void() volatile&&>();
    test_is_not_empty<void() const volatile>();
    test_is_not_empty<void() const volatile&>();
    test_is_not_empty<void() const volatile&&>();
    test_is_not_empty<void() noexcept>();
    test_is_not_empty<void()& noexcept>();
    test_is_not_empty<void()&& noexcept>();
    test_is_not_empty<void() const noexcept>();
    test_is_not_empty<void() const& noexcept>();
    test_is_not_empty<void() const&& noexcept>();
    test_is_not_empty<void() volatile noexcept>();
    test_is_not_empty<void() volatile& noexcept>();
    test_is_not_empty<void() volatile&& noexcept>();
    test_is_not_empty<void() const volatile noexcept>();
    test_is_not_empty<void() const volatile& noexcept>();
    test_is_not_empty<void() const volatile&& noexcept>();

    test_is_not_empty<void(int)>();
    test_is_not_empty<void(int)&>();
    test_is_not_empty<void(int) &&>();
    test_is_not_empty<void(int) const>();
    test_is_not_empty<void(int) const&>();
    test_is_not_empty<void(int) const&&>();
    test_is_not_empty<void(int) volatile>();
    test_is_not_empty<void(int) volatile&>();
    test_is_not_empty<void(int) volatile&&>();
    test_is_not_empty<void(int) const volatile>();
    test_is_not_empty<void(int) const volatile&>();
    test_is_not_empty<void(int) const volatile&&>();
    test_is_not_empty<void(int) noexcept>();
    test_is_not_empty<void(int)& noexcept>();
    test_is_not_empty<void(int)&& noexcept>();
    test_is_not_empty<void(int) const noexcept>();
    test_is_not_empty<void(int) const& noexcept>();
    test_is_not_empty<void(int) const&& noexcept>();
    test_is_not_empty<void(int) volatile noexcept>();
    test_is_not_empty<void(int) volatile& noexcept>();
    test_is_not_empty<void(int) volatile&& noexcept>();
    test_is_not_empty<void(int) const volatile noexcept>();
    test_is_not_empty<void(int) const volatile& noexcept>();
    test_is_not_empty<void(int) const volatile&& noexcept>();

    test_is_not_empty<void(...)>();
    test_is_not_empty<void(...)&>();
    test_is_not_empty<void(...) &&>();
    test_is_not_empty<void(...) const>();
    test_is_not_empty<void(...) const&>();
    test_is_not_empty<void(...) const&&>();
    test_is_not_empty<void(...) volatile>();
    test_is_not_empty<void(...) volatile&>();
    test_is_not_empty<void(...) volatile&&>();
    test_is_not_empty<void(...) const volatile>();
    test_is_not_empty<void(...) const volatile&>();
    test_is_not_empty<void(...) const volatile&&>();
    test_is_not_empty<void(...) noexcept>();
    test_is_not_empty<void(...)& noexcept>();
    test_is_not_empty<void(...)&& noexcept>();
    test_is_not_empty<void(...) const noexcept>();
    test_is_not_empty<void(...) const& noexcept>();
    test_is_not_empty<void(...) const&& noexcept>();
    test_is_not_empty<void(...) volatile noexcept>();
    test_is_not_empty<void(...) volatile& noexcept>();
    test_is_not_empty<void(...) volatile&& noexcept>();
    test_is_not_empty<void(...) const volatile noexcept>();
    test_is_not_empty<void(...) const volatile& noexcept>();
    test_is_not_empty<void(...) const volatile&& noexcept>();

    test_is_not_empty<void(int, ...)>();
    test_is_not_empty<void(int, ...)&>();
    test_is_not_empty<void(int, ...) &&>();
    test_is_not_empty<void(int, ...) const>();
    test_is_not_empty<void(int, ...) const&>();
    test_is_not_empty<void(int, ...) const&&>();
    test_is_not_empty<void(int, ...) volatile>();
    test_is_not_empty<void(int, ...) volatile&>();
    test_is_not_empty<void(int, ...) volatile&&>();
    test_is_not_empty<void(int, ...) const volatile>();
    test_is_not_empty<void(int, ...) const volatile&>();
    test_is_not_empty<void(int, ...) const volatile&&>();
    test_is_not_empty<void(int, ...) noexcept>();
    test_is_not_empty<void(int, ...)& noexcept>();
    test_is_not_empty<void(int, ...)&& noexcept>();
    test_is_not_empty<void(int, ...) const noexcept>();
    test_is_not_empty<void(int, ...) const& noexcept>();
    test_is_not_empty<void(int, ...) const&& noexcept>();
    test_is_not_empty<void(int, ...) volatile noexcept>();
    test_is_not_empty<void(int, ...) volatile& noexcept>();
    test_is_not_empty<void(int, ...) volatile&& noexcept>();
    test_is_not_empty<void(int, ...) const volatile noexcept>();
    test_is_not_empty<void(int, ...) const volatile& noexcept>();
    test_is_not_empty<void(int, ...) const volatile&& noexcept>();

    test_is_not_empty<int()>();
    test_is_not_empty<int()&>();
    test_is_not_empty<int() &&>();
    test_is_not_empty<int() const>();
    test_is_not_empty<int() const&>();
    test_is_not_empty<int() const&&>();
    test_is_not_empty<int() volatile>();
    test_is_not_empty<int() volatile&>();
    test_is_not_empty<int() volatile&&>();
    test_is_not_empty<int() const volatile>();
    test_is_not_empty<int() const volatile&>();
    test_is_not_empty<int() const volatile&&>();
    test_is_not_empty<int() noexcept>();
    test_is_not_empty<int()& noexcept>();
    test_is_not_empty<int()&& noexcept>();
    test_is_not_empty<int() const noexcept>();
    test_is_not_empty<int() const& noexcept>();
    test_is_not_empty<int() const&& noexcept>();
    test_is_not_empty<int() volatile noexcept>();
    test_is_not_empty<int() volatile& noexcept>();
    test_is_not_empty<int() volatile&& noexcept>();
    test_is_not_empty<int() const volatile noexcept>();
    test_is_not_empty<int() const volatile& noexcept>();
    test_is_not_empty<int() const volatile&& noexcept>();

    test_is_not_empty<int(int)>();
    test_is_not_empty<int(int)&>();
    test_is_not_empty<int(int) &&>();
    test_is_not_empty<int(int) const>();
    test_is_not_empty<int(int) const&>();
    test_is_not_empty<int(int) const&&>();
    test_is_not_empty<int(int) volatile>();
    test_is_not_empty<int(int) volatile&>();
    test_is_not_empty<int(int) volatile&&>();
    test_is_not_empty<int(int) const volatile>();
    test_is_not_empty<int(int) const volatile&>();
    test_is_not_empty<int(int) const volatile&&>();
    test_is_not_empty<int(int) noexcept>();
    test_is_not_empty<int(int)& noexcept>();
    test_is_not_empty<int(int)&& noexcept>();
    test_is_not_empty<int(int) const noexcept>();
    test_is_not_empty<int(int) const& noexcept>();
    test_is_not_empty<int(int) const&& noexcept>();
    test_is_not_empty<int(int) volatile noexcept>();
    test_is_not_empty<int(int) volatile& noexcept>();
    test_is_not_empty<int(int) volatile&& noexcept>();
    test_is_not_empty<int(int) const volatile noexcept>();
    test_is_not_empty<int(int) const volatile& noexcept>();
    test_is_not_empty<int(int) const volatile&& noexcept>();

    test_is_not_empty<int(...)>();
    test_is_not_empty<int(...)&>();
    test_is_not_empty<int(...) &&>();
    test_is_not_empty<int(...) const>();
    test_is_not_empty<int(...) const&>();
    test_is_not_empty<int(...) const&&>();
    test_is_not_empty<int(...) volatile>();
    test_is_not_empty<int(...) volatile&>();
    test_is_not_empty<int(...) volatile&&>();
    test_is_not_empty<int(...) const volatile>();
    test_is_not_empty<int(...) const volatile&>();
    test_is_not_empty<int(...) const volatile&&>();
    test_is_not_empty<int(...) noexcept>();
    test_is_not_empty<int(...)& noexcept>();
    test_is_not_empty<int(...)&& noexcept>();
    test_is_not_empty<int(...) const noexcept>();
    test_is_not_empty<int(...) const& noexcept>();
    test_is_not_empty<int(...) const&& noexcept>();
    test_is_not_empty<int(...) volatile noexcept>();
    test_is_not_empty<int(...) volatile& noexcept>();
    test_is_not_empty<int(...) volatile&& noexcept>();
    test_is_not_empty<int(...) const volatile noexcept>();
    test_is_not_empty<int(...) const volatile& noexcept>();
    test_is_not_empty<int(...) const volatile&& noexcept>();

    test_is_not_empty<int(int, ...)>();
    test_is_not_empty<int(int, ...)&>();
    test_is_not_empty<int(int, ...) &&>();
    test_is_not_empty<int(int, ...) const>();
    test_is_not_empty<int(int, ...) const&>();
    test_is_not_empty<int(int, ...) const&&>();
    test_is_not_empty<int(int, ...) volatile>();
    test_is_not_empty<int(int, ...) volatile&>();
    test_is_not_empty<int(int, ...) volatile&&>();
    test_is_not_empty<int(int, ...) const volatile>();
    test_is_not_empty<int(int, ...) const volatile&>();
    test_is_not_empty<int(int, ...) const volatile&&>();
    test_is_not_empty<int(int, ...) noexcept>();
    test_is_not_empty<int(int, ...)& noexcept>();
    test_is_not_empty<int(int, ...)&& noexcept>();
    test_is_not_empty<int(int, ...) const noexcept>();
    test_is_not_empty<int(int, ...) const& noexcept>();
    test_is_not_empty<int(int, ...) const&& noexcept>();
    test_is_not_empty<int(int, ...) volatile noexcept>();
    test_is_not_empty<int(int, ...) volatile& noexcept>();
    test_is_not_empty<int(int, ...) volatile&& noexcept>();
    test_is_not_empty<int(int, ...) const volatile noexcept>();
    test_is_not_empty<int(int, ...) const volatile& noexcept>();
    test_is_not_empty<int(int, ...) const volatile&& noexcept>();

    test_is_not_empty<void (*)()>();
    test_is_not_empty<void (*)() noexcept>();

    test_is_not_empty<void (*)(int)>();
    test_is_not_empty<void (*)(int) noexcept>();

    test_is_not_empty<void (*)(...)>();
    test_is_not_empty<void (*)(...) noexcept>();

    test_is_not_empty<void (*)(int, ...)>();
    test_is_not_empty<void (*)(int, ...) noexcept>();

    test_is_not_empty<int (*)()>();
    test_is_not_empty<int (*)() noexcept>();

    test_is_not_empty<int (*)(int)>();
    test_is_not_empty<int (*)(int) noexcept>();

    test_is_not_empty<int (*)(...)>();
    test_is_not_empty<int (*)(...) noexcept>();

    test_is_not_empty<int (*)(int, ...)>();
    test_is_not_empty<int (*)(int, ...) noexcept>();

    test_is_not_empty<void (&)()>();
    test_is_not_empty<void (&)() noexcept>();

    test_is_not_empty<void (&)(int)>();
    test_is_not_empty<void (&)(int) noexcept>();

    test_is_not_empty<void (&)(...)>();
    test_is_not_empty<void (&)(...) noexcept>();

    test_is_not_empty<void (&)(int, ...)>();
    test_is_not_empty<void (&)(int, ...) noexcept>();

    test_is_not_empty<int (&)()>();
    test_is_not_empty<int (&)() noexcept>();

    test_is_not_empty<int (&)(int)>();
    test_is_not_empty<int (&)(int) noexcept>();

    test_is_not_empty<int (&)(...)>();
    test_is_not_empty<int (&)(...) noexcept>();

    test_is_not_empty<int (&)(int, ...)>();
    test_is_not_empty<int (&)(int, ...) noexcept>();

    test_is_not_empty<void(&&)()>();
    test_is_not_empty<void(&&)() noexcept>();

    test_is_not_empty<void(&&)(int)>();
    test_is_not_empty<void(&&)(int) noexcept>();

    test_is_not_empty<void(&&)(...)>();
    test_is_not_empty<void(&&)(...) noexcept>();

    test_is_not_empty<void(&&)(int, ...)>();
    test_is_not_empty<void(&&)(int, ...) noexcept>();

    test_is_not_empty<int(&&)()>();
    test_is_not_empty<int(&&)() noexcept>();

    test_is_not_empty<int(&&)(int)>();
    test_is_not_empty<int(&&)(int) noexcept>();

    test_is_not_empty<int(&&)(...)>();
    test_is_not_empty<int(&&)(...) noexcept>();

    test_is_not_empty<int(&&)(int, ...)>();
    test_is_not_empty<int(&&)(int, ...) noexcept>();

    test_is_not_empty<void (Class::*)()>();
    test_is_not_empty<void (Class::*)()&>();
    test_is_not_empty<void (Class::*)() &&>();
    test_is_not_empty<void (Class::*)() const>();
    test_is_not_empty<void (Class::*)() const&>();
    test_is_not_empty<void (Class::*)() const&&>();
    test_is_not_empty<void (Class::*)() noexcept>();
    test_is_not_empty<void (Class::*)()& noexcept>();
    test_is_not_empty<void (Class::*)()&& noexcept>();
    test_is_not_empty<void (Class::*)() const noexcept>();
    test_is_not_empty<void (Class::*)() const& noexcept>();
    test_is_not_empty<void (Class::*)() const&& noexcept>();

    test_is_not_empty<void (Class::*)(int)>();
    test_is_not_empty<void (Class::*)(int)&>();
    test_is_not_empty<void (Class::*)(int) &&>();
    test_is_not_empty<void (Class::*)(int) const>();
    test_is_not_empty<void (Class::*)(int) const&>();
    test_is_not_empty<void (Class::*)(int) const&&>();
    test_is_not_empty<void (Class::*)(int) noexcept>();
    test_is_not_empty<void (Class::*)(int)& noexcept>();
    test_is_not_empty<void (Class::*)(int)&& noexcept>();
    test_is_not_empty<void (Class::*)(int) const noexcept>();
    test_is_not_empty<void (Class::*)(int) const& noexcept>();
    test_is_not_empty<void (Class::*)(int) const&& noexcept>();

    test_is_not_empty<void (Class::*)(...)>();
    test_is_not_empty<void (Class::*)(...)&>();
    test_is_not_empty<void (Class::*)(...) &&>();
    test_is_not_empty<void (Class::*)(...) const>();
    test_is_not_empty<void (Class::*)(...) const&>();
    test_is_not_empty<void (Class::*)(...) const&&>();
    test_is_not_empty<void (Class::*)(...) noexcept>();
    test_is_not_empty<void (Class::*)(...)& noexcept>();
    test_is_not_empty<void (Class::*)(...)&& noexcept>();
    test_is_not_empty<void (Class::*)(...) const noexcept>();
    test_is_not_empty<void (Class::*)(...) const& noexcept>();
    test_is_not_empty<void (Class::*)(...) const&& noexcept>();

    test_is_not_empty<void (Class::*)(int, ...)>();
    test_is_not_empty<void (Class::*)(int, ...)&>();
    test_is_not_empty<void (Class::*)(int, ...) &&>();
    test_is_not_empty<void (Class::*)(int, ...) const>();
    test_is_not_empty<void (Class::*)(int, ...) const&>();
    test_is_not_empty<void (Class::*)(int, ...) const&&>();
    test_is_not_empty<void (Class::*)(int, ...) noexcept>();
    test_is_not_empty<void (Class::*)(int, ...)& noexcept>();
    test_is_not_empty<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_empty<void (Class::*)(int, ...) const noexcept>();
    test_is_not_empty<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_empty<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_empty<int (Class::*)()>();
    test_is_not_empty<int (Class::*)()&>();
    test_is_not_empty<int (Class::*)() &&>();
    test_is_not_empty<int (Class::*)() const>();
    test_is_not_empty<int (Class::*)() const&>();
    test_is_not_empty<int (Class::*)() const&&>();
    test_is_not_empty<int (Class::*)() noexcept>();
    test_is_not_empty<int (Class::*)()& noexcept>();
    test_is_not_empty<int (Class::*)()&& noexcept>();
    test_is_not_empty<int (Class::*)() const noexcept>();
    test_is_not_empty<int (Class::*)() const& noexcept>();
    test_is_not_empty<int (Class::*)() const&& noexcept>();

    test_is_not_empty<int (Class::*)(int)>();
    test_is_not_empty<int (Class::*)(int)&>();
    test_is_not_empty<int (Class::*)(int) &&>();
    test_is_not_empty<int (Class::*)(int) const>();
    test_is_not_empty<int (Class::*)(int) const&>();
    test_is_not_empty<int (Class::*)(int) const&&>();
    test_is_not_empty<int (Class::*)(int) noexcept>();
    test_is_not_empty<int (Class::*)(int)& noexcept>();
    test_is_not_empty<int (Class::*)(int)&& noexcept>();
    test_is_not_empty<int (Class::*)(int) const noexcept>();
    test_is_not_empty<int (Class::*)(int) const& noexcept>();
    test_is_not_empty<int (Class::*)(int) const&& noexcept>();

    test_is_not_empty<int (Class::*)(...)>();
    test_is_not_empty<int (Class::*)(...)&>();
    test_is_not_empty<int (Class::*)(...) &&>();
    test_is_not_empty<int (Class::*)(...) const>();
    test_is_not_empty<int (Class::*)(...) const&>();
    test_is_not_empty<int (Class::*)(...) const&&>();
    test_is_not_empty<int (Class::*)(...) noexcept>();
    test_is_not_empty<int (Class::*)(...)& noexcept>();
    test_is_not_empty<int (Class::*)(...)&& noexcept>();
    test_is_not_empty<int (Class::*)(...) const noexcept>();
    test_is_not_empty<int (Class::*)(...) const& noexcept>();
    test_is_not_empty<int (Class::*)(...) const&& noexcept>();

    test_is_not_empty<int (Class::*)(int, ...)>();
    test_is_not_empty<int (Class::*)(int, ...)&>();
    test_is_not_empty<int (Class::*)(int, ...) &&>();
    test_is_not_empty<int (Class::*)(int, ...) const>();
    test_is_not_empty<int (Class::*)(int, ...) const&>();
    test_is_not_empty<int (Class::*)(int, ...) const&&>();
    test_is_not_empty<int (Class::*)(int, ...) noexcept>();
    test_is_not_empty<int (Class::*)(int, ...)& noexcept>();
    test_is_not_empty<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_empty<int (Class::*)(int, ...) const noexcept>();
    test_is_not_empty<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_empty<int (Class::*)(int, ...) const&& noexcept>();
}
