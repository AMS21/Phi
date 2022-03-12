#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_standard_layout.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_standard_layout_impl()
{
#if PHI_HAS_WORKING_IS_STANDARD_LAYOUT()
    STATIC_REQUIRE(phi::is_standard_layout<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_standard_layout<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_standard_layout_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_standard_layout_v<T>);
#    endif

    // Standard compatbilility
    STATIC_REQUIRE(std::is_standard_layout<T>::value);
#endif
}

template <typename T>
void test_is_not_standard_layout_impl()
{
#if PHI_HAS_WORKING_IS_STANDARD_LAYOUT()
    STATIC_REQUIRE_FALSE(phi::is_standard_layout<T>::value);
    STATIC_REQUIRE(phi::is_not_standard_layout<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_standard_layout_v<T>);
    STATIC_REQUIRE(phi::is_not_standard_layout_v<T>);
#    endif

    // Standard compatbilility
    STATIC_REQUIRE_FALSE(std::is_standard_layout<T>::value);
#endif
}

template <typename T>
void test_is_standard_layout()
{
    test_is_standard_layout_impl<T>();
    test_is_standard_layout_impl<const T>();
    test_is_standard_layout_impl<volatile T>();
    test_is_standard_layout_impl<const volatile T>();
}

template <typename T>
void test_is_not_standard_layout()
{
    test_is_not_standard_layout_impl<T>();
    test_is_not_standard_layout_impl<const T>();
    test_is_not_standard_layout_impl<volatile T>();
    test_is_not_standard_layout_impl<const volatile T>();
}

template <typename T>
void test_is_standard_layout_function()
{
#if PHI_COMPILER_IS(MSVC)
    test_is_standard_layout<T>();
    test_is_standard_layout<const T>();
    test_is_standard_layout<volatile T>();
    test_is_standard_layout<const volatile T>();
#else
    test_is_not_standard_layout<T>();
    test_is_not_standard_layout<const T>();
    test_is_not_standard_layout<volatile T>();
    test_is_not_standard_layout<const volatile T>();
#endif
}

template <typename T1, typename T2>
struct pair
{
    T1 first;
    T2 second;
};

struct A
{
    int m;
};

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wunused-private-field")

struct B
{
    int m1;

private:
    int m2;
};

PHI_CLANG_SUPPRESS_WARNING_POP()

struct C
{
    virtual ~C();
    virtual void foo();
};

TEST_CASE("is_standard_layout")
{
    test_is_standard_layout<pair<int, double>>();
    test_is_standard_layout<pair<int, double>[5]>();
    test_is_standard_layout<pair<A, A>>();
    test_is_standard_layout<pair<A, A>[12]>();
    test_is_standard_layout<A>();
    test_is_standard_layout<A[3]>();

    test_is_not_standard_layout<B>();
    test_is_not_standard_layout<C>();

    test_is_not_standard_layout<void>();
    test_is_standard_layout<phi::nullptr_t>();
    test_is_standard_layout<bool>();
    test_is_standard_layout<char>();
    test_is_standard_layout<signed char>();
    test_is_standard_layout<unsigned char>();
    test_is_standard_layout<short>();
    test_is_standard_layout<unsigned short>();
    test_is_standard_layout<int>();
    test_is_standard_layout<unsigned int>();
    test_is_standard_layout<long>();
    test_is_standard_layout<unsigned long>();
    test_is_standard_layout<long long>();
    test_is_standard_layout<unsigned long long>();
    test_is_standard_layout<float>();
    test_is_standard_layout<double>();
    test_is_standard_layout<long double>();
    test_is_standard_layout<char8_t>();
    test_is_standard_layout<char16_t>();
    test_is_standard_layout<char32_t>();
    test_is_standard_layout<wchar_t>();

    test_is_standard_layout<phi::boolean>();
    test_is_standard_layout<phi::integer<signed char>>();
    test_is_standard_layout<phi::integer<unsigned char>>();
    test_is_standard_layout<phi::integer<short>>();
    test_is_standard_layout<phi::integer<unsigned short>>();
    test_is_standard_layout<phi::integer<int>>();
    test_is_standard_layout<phi::integer<unsigned int>>();
    test_is_standard_layout<phi::integer<long>>();
    test_is_standard_layout<phi::integer<unsigned long>>();
    test_is_standard_layout<phi::integer<long long>>();
    test_is_standard_layout<phi::integer<unsigned long long>>();
    test_is_standard_layout<phi::floating_point<float>>();
    test_is_standard_layout<phi::floating_point<double>>();
    test_is_standard_layout<phi::floating_point<long double>>();

#if PHI_COMPILER_IS(MSVC) || PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK();
#else
    test_is_standard_layout<std::vector<int>>();
#endif
    test_is_standard_layout<phi::scope_ptr<int>>();

    test_is_not_standard_layout<int&>();
    test_is_not_standard_layout<const int&>();
    test_is_not_standard_layout<volatile int&>();
    test_is_not_standard_layout<const volatile int&>();
    test_is_not_standard_layout<int&&>();
    test_is_not_standard_layout<const int&&>();
    test_is_not_standard_layout<volatile int&&>();
    test_is_not_standard_layout<const volatile int&&>();
    test_is_standard_layout<int*>();
    test_is_standard_layout<const int*>();
    test_is_standard_layout<volatile int*>();
    test_is_standard_layout<const volatile int*>();
    test_is_standard_layout<int**>();
    test_is_standard_layout<const int**>();
    test_is_standard_layout<volatile int**>();
    test_is_standard_layout<const volatile int**>();
    test_is_not_standard_layout<int*&>();
    test_is_not_standard_layout<const int*&>();
    test_is_not_standard_layout<volatile int*&>();
    test_is_not_standard_layout<const volatile int*&>();
    test_is_not_standard_layout<int*&&>();
    test_is_not_standard_layout<const int*&&>();
    test_is_not_standard_layout<volatile int*&&>();
    test_is_not_standard_layout<const volatile int*&&>();
    test_is_standard_layout<void*>();
    test_is_standard_layout<char[3]>();
    test_is_standard_layout<char[]>();
    test_is_standard_layout<char* [3]>();
    test_is_standard_layout<char*[]>();
    test_is_standard_layout<int(*)[3]>();
    test_is_standard_layout<int(*)[]>();
    test_is_not_standard_layout<int(&)[3]>();
    test_is_not_standard_layout<int(&)[]>();
    test_is_not_standard_layout<int(&&)[3]>();
    test_is_not_standard_layout<int(&&)[]>();
    test_is_standard_layout<char[3][2]>();
    test_is_standard_layout<char[][2]>();
    test_is_standard_layout<char* [3][2]>();
    test_is_standard_layout<char*[][2]>();
    test_is_standard_layout<int(*)[3][2]>();
    test_is_standard_layout<int(*)[][2]>();
    test_is_not_standard_layout<int(&)[3][2]>();
    test_is_not_standard_layout<int(&)[][2]>();
    test_is_not_standard_layout<int(&&)[3][2]>();
    test_is_not_standard_layout<int(&&)[][2]>();
    test_is_standard_layout<Class>();
    test_is_standard_layout<Class[]>();
    test_is_standard_layout<Class[2]>();
    test_is_standard_layout<Template<void>>();
    test_is_standard_layout<Template<int>>();
    test_is_standard_layout<Template<Class>>();
    test_is_standard_layout<Template<IncompleteType>>();
    test_is_standard_layout<VariadicTemplate<>>();
    test_is_standard_layout<VariadicTemplate<void>>();
    test_is_standard_layout<VariadicTemplate<int>>();
    test_is_standard_layout<VariadicTemplate<Class>>();
    test_is_standard_layout<VariadicTemplate<IncompleteType>>();
    test_is_standard_layout<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_standard_layout<PublicDerivedFromTemplate<Base>>();
    test_is_standard_layout<PublicDerivedFromTemplate<Derived>>();
    test_is_standard_layout<PublicDerivedFromTemplate<Class>>();
    test_is_standard_layout<PrivateDerivedFromTemplate<Base>>();
    test_is_standard_layout<PrivateDerivedFromTemplate<Derived>>();
    test_is_standard_layout<PrivateDerivedFromTemplate<Class>>();
    test_is_standard_layout<ProtectedDerivedFromTemplate<Base>>();
    test_is_standard_layout<ProtectedDerivedFromTemplate<Derived>>();
    test_is_standard_layout<ProtectedDerivedFromTemplate<Class>>();
    test_is_standard_layout<Union>();
    test_is_standard_layout<NonEmptyUnion>();
    test_is_standard_layout<Empty>();
    test_is_not_standard_layout<NotEmpty>();
    test_is_standard_layout<BitZero>();
    test_is_standard_layout<BitOne>();
    test_is_standard_layout<Base>();
    test_is_standard_layout<Derived>();
    test_is_not_standard_layout<Abstract>();
    test_is_not_standard_layout<PublicAbstract>();
    test_is_not_standard_layout<PrivateAbstract>();
    test_is_not_standard_layout<ProtectedAbstract>();
    test_is_not_standard_layout<AbstractTemplate<int>>();
    test_is_standard_layout<AbstractTemplate<double>>();
    test_is_not_standard_layout<AbstractTemplate<Class>>();
    test_is_not_standard_layout<AbstractTemplate<IncompleteType>>();
    test_is_standard_layout<Final>();
    test_is_standard_layout<PublicDestructor>();
    test_is_standard_layout<ProtectedDestructor>();
    test_is_standard_layout<PrivateDestructor>();
    test_is_not_standard_layout<VirtualPublicDestructor>();
    test_is_not_standard_layout<VirtualProtectedDestructor>();
    test_is_not_standard_layout<VirtualPrivateDestructor>();
    test_is_not_standard_layout<PurePublicDestructor>();
    test_is_not_standard_layout<PureProtectedDestructor>();
    test_is_not_standard_layout<PurePrivateDestructor>();
    test_is_standard_layout<DeletedPublicDestructor>();
    test_is_standard_layout<DeletedProtectedDestructor>();
    test_is_standard_layout<DeletedPrivateDestructor>();
    test_is_not_standard_layout<DeletedVirtualPublicDestructor>();
    test_is_not_standard_layout<DeletedVirtualProtectedDestructor>();
    test_is_not_standard_layout<DeletedVirtualPrivateDestructor>();
    test_is_standard_layout<Enum>();
    test_is_standard_layout<EnumSigned>();
    test_is_standard_layout<EnumUnsigned>();
    test_is_standard_layout<EnumClass>();
    test_is_standard_layout<EnumStruct>();
    test_is_standard_layout_function<Function>();
    test_is_standard_layout<FunctionPtr>();
    test_is_standard_layout<MemberObjectPtr>();
    test_is_standard_layout<MemberFunctionPtr>();
    test_is_standard_layout<int Class::*>();
    test_is_standard_layout<float Class::*>();
    test_is_standard_layout<void * Class::*>();
    test_is_standard_layout<int * Class::*>();
    test_is_not_standard_layout<int Class::*&>();
    test_is_not_standard_layout<float Class::*&>();
    test_is_not_standard_layout<void * Class::*&>();
    test_is_not_standard_layout<int * Class::*&>();
    test_is_not_standard_layout<int Class::*&&>();
    test_is_not_standard_layout<float Class::*&&>();
    test_is_not_standard_layout<void * Class::*&&>();
    test_is_not_standard_layout<int * Class::*&&>();
    test_is_standard_layout<int Class::*const>();
    test_is_standard_layout<float Class::*const>();
    test_is_standard_layout<void * Class::*const>();
    test_is_not_standard_layout<int Class::*const&>();
    test_is_not_standard_layout<float Class::*const&>();
    test_is_not_standard_layout<void * Class::*const&>();
    test_is_not_standard_layout<int Class::*const&&>();
    test_is_not_standard_layout<float Class::*const&&>();
    test_is_not_standard_layout<void * Class::*const&&>();
    test_is_standard_layout<int Class::*volatile>();
    test_is_standard_layout<float Class::*volatile>();
    test_is_standard_layout<void * Class::*volatile>();
    test_is_not_standard_layout<int Class::*volatile&>();
    test_is_not_standard_layout<float Class::*volatile&>();
    test_is_not_standard_layout<void * Class::*volatile&>();
    test_is_not_standard_layout<int Class::*volatile&&>();
    test_is_not_standard_layout<float Class::*volatile&&>();
    test_is_not_standard_layout<void * Class::*volatile&&>();
    test_is_standard_layout<int Class::*const volatile>();
    test_is_standard_layout<float Class::*const volatile>();
    test_is_standard_layout<void * Class::*const volatile>();
    test_is_not_standard_layout<int Class::*const volatile&>();
    test_is_not_standard_layout<float Class::*const volatile&>();
    test_is_not_standard_layout<void * Class::*const volatile&>();
    test_is_not_standard_layout<int Class::*const volatile&&>();
    test_is_not_standard_layout<float Class::*const volatile&&>();
    test_is_not_standard_layout<void * Class::*const volatile&&>();
    test_is_standard_layout<NonCopyable>();
    test_is_standard_layout<NonMoveable>();
    test_is_standard_layout<NonConstructible>();
    test_is_standard_layout<Tracked>();
    test_is_standard_layout<TrapConstructible>();
    test_is_standard_layout<TrapImplicitConversion>();
    test_is_standard_layout<TrapComma>();
    test_is_standard_layout<TrapCall>();
    test_is_standard_layout<TrapSelfAssign>();
    test_is_standard_layout<TrapDeref>();
    test_is_standard_layout<TrapArraySubscript>();

    test_is_standard_layout_function<void()>();
    test_is_standard_layout_function<void()&>();
    test_is_standard_layout_function<void() &&>();
    test_is_standard_layout_function<void() const>();
    test_is_standard_layout_function<void() const&>();
    test_is_standard_layout_function<void() const&&>();
    test_is_standard_layout_function<void() volatile>();
    test_is_standard_layout_function<void() volatile&>();
    test_is_standard_layout_function<void() volatile&&>();
    test_is_standard_layout_function<void() const volatile>();
    test_is_standard_layout_function<void() const volatile&>();
    test_is_standard_layout_function<void() const volatile&&>();
    test_is_standard_layout_function<void() noexcept>();
    test_is_standard_layout_function<void()& noexcept>();
    test_is_standard_layout_function<void()&& noexcept>();
    test_is_standard_layout_function<void() const noexcept>();
    test_is_standard_layout_function<void() const& noexcept>();
    test_is_standard_layout_function<void() const&& noexcept>();
    test_is_standard_layout_function<void() volatile noexcept>();
    test_is_standard_layout_function<void() volatile& noexcept>();
    test_is_standard_layout_function<void() volatile&& noexcept>();
    test_is_standard_layout_function<void() const volatile noexcept>();
    test_is_standard_layout_function<void() const volatile& noexcept>();
    test_is_standard_layout_function<void() const volatile&& noexcept>();

    test_is_standard_layout_function<void(int)>();
    test_is_standard_layout_function<void(int)&>();
    test_is_standard_layout_function<void(int) &&>();
    test_is_standard_layout_function<void(int) const>();
    test_is_standard_layout_function<void(int) const&>();
    test_is_standard_layout_function<void(int) const&&>();
    test_is_standard_layout_function<void(int) volatile>();
    test_is_standard_layout_function<void(int) volatile&>();
    test_is_standard_layout_function<void(int) volatile&&>();
    test_is_standard_layout_function<void(int) const volatile>();
    test_is_standard_layout_function<void(int) const volatile&>();
    test_is_standard_layout_function<void(int) const volatile&&>();
    test_is_standard_layout_function<void(int) noexcept>();
    test_is_standard_layout_function<void(int)& noexcept>();
    test_is_standard_layout_function<void(int)&& noexcept>();
    test_is_standard_layout_function<void(int) const noexcept>();
    test_is_standard_layout_function<void(int) const& noexcept>();
    test_is_standard_layout_function<void(int) const&& noexcept>();
    test_is_standard_layout_function<void(int) volatile noexcept>();
    test_is_standard_layout_function<void(int) volatile& noexcept>();
    test_is_standard_layout_function<void(int) volatile&& noexcept>();
    test_is_standard_layout_function<void(int) const volatile noexcept>();
    test_is_standard_layout_function<void(int) const volatile& noexcept>();
    test_is_standard_layout_function<void(int) const volatile&& noexcept>();

    test_is_standard_layout_function<void(...)>();
    test_is_standard_layout_function<void(...)&>();
    test_is_standard_layout_function<void(...) &&>();
    test_is_standard_layout_function<void(...) const>();
    test_is_standard_layout_function<void(...) const&>();
    test_is_standard_layout_function<void(...) const&&>();
    test_is_standard_layout_function<void(...) volatile>();
    test_is_standard_layout_function<void(...) volatile&>();
    test_is_standard_layout_function<void(...) volatile&&>();
    test_is_standard_layout_function<void(...) const volatile>();
    test_is_standard_layout_function<void(...) const volatile&>();
    test_is_standard_layout_function<void(...) const volatile&&>();
    test_is_standard_layout_function<void(...) noexcept>();
    test_is_standard_layout_function<void(...)& noexcept>();
    test_is_standard_layout_function<void(...)&& noexcept>();
    test_is_standard_layout_function<void(...) const noexcept>();
    test_is_standard_layout_function<void(...) const& noexcept>();
    test_is_standard_layout_function<void(...) const&& noexcept>();
    test_is_standard_layout_function<void(...) volatile noexcept>();
    test_is_standard_layout_function<void(...) volatile& noexcept>();
    test_is_standard_layout_function<void(...) volatile&& noexcept>();
    test_is_standard_layout_function<void(...) const volatile noexcept>();
    test_is_standard_layout_function<void(...) const volatile& noexcept>();
    test_is_standard_layout_function<void(...) const volatile&& noexcept>();

    test_is_standard_layout_function<void(int, ...)>();
    test_is_standard_layout_function<void(int, ...)&>();
    test_is_standard_layout_function<void(int, ...) &&>();
    test_is_standard_layout_function<void(int, ...) const>();
    test_is_standard_layout_function<void(int, ...) const&>();
    test_is_standard_layout_function<void(int, ...) const&&>();
    test_is_standard_layout_function<void(int, ...) volatile>();
    test_is_standard_layout_function<void(int, ...) volatile&>();
    test_is_standard_layout_function<void(int, ...) volatile&&>();
    test_is_standard_layout_function<void(int, ...) const volatile>();
    test_is_standard_layout_function<void(int, ...) const volatile&>();
    test_is_standard_layout_function<void(int, ...) const volatile&&>();
    test_is_standard_layout_function<void(int, ...) noexcept>();
    test_is_standard_layout_function<void(int, ...)& noexcept>();
    test_is_standard_layout_function<void(int, ...)&& noexcept>();
    test_is_standard_layout_function<void(int, ...) const noexcept>();
    test_is_standard_layout_function<void(int, ...) const& noexcept>();
    test_is_standard_layout_function<void(int, ...) const&& noexcept>();
    test_is_standard_layout_function<void(int, ...) volatile noexcept>();
    test_is_standard_layout_function<void(int, ...) volatile& noexcept>();
    test_is_standard_layout_function<void(int, ...) volatile&& noexcept>();
    test_is_standard_layout_function<void(int, ...) const volatile noexcept>();
    test_is_standard_layout_function<void(int, ...) const volatile& noexcept>();
    test_is_standard_layout_function<void(int, ...) const volatile&& noexcept>();

    test_is_standard_layout_function<int()>();
    test_is_standard_layout_function<int()&>();
    test_is_standard_layout_function<int() &&>();
    test_is_standard_layout_function<int() const>();
    test_is_standard_layout_function<int() const&>();
    test_is_standard_layout_function<int() const&&>();
    test_is_standard_layout_function<int() volatile>();
    test_is_standard_layout_function<int() volatile&>();
    test_is_standard_layout_function<int() volatile&&>();
    test_is_standard_layout_function<int() const volatile>();
    test_is_standard_layout_function<int() const volatile&>();
    test_is_standard_layout_function<int() const volatile&&>();
    test_is_standard_layout_function<int() noexcept>();
    test_is_standard_layout_function<int()& noexcept>();
    test_is_standard_layout_function<int()&& noexcept>();
    test_is_standard_layout_function<int() const noexcept>();
    test_is_standard_layout_function<int() const& noexcept>();
    test_is_standard_layout_function<int() const&& noexcept>();
    test_is_standard_layout_function<int() volatile noexcept>();
    test_is_standard_layout_function<int() volatile& noexcept>();
    test_is_standard_layout_function<int() volatile&& noexcept>();
    test_is_standard_layout_function<int() const volatile noexcept>();
    test_is_standard_layout_function<int() const volatile& noexcept>();
    test_is_standard_layout_function<int() const volatile&& noexcept>();

    test_is_standard_layout_function<int(int)>();
    test_is_standard_layout_function<int(int)&>();
    test_is_standard_layout_function<int(int) &&>();
    test_is_standard_layout_function<int(int) const>();
    test_is_standard_layout_function<int(int) const&>();
    test_is_standard_layout_function<int(int) const&&>();
    test_is_standard_layout_function<int(int) volatile>();
    test_is_standard_layout_function<int(int) volatile&>();
    test_is_standard_layout_function<int(int) volatile&&>();
    test_is_standard_layout_function<int(int) const volatile>();
    test_is_standard_layout_function<int(int) const volatile&>();
    test_is_standard_layout_function<int(int) const volatile&&>();
    test_is_standard_layout_function<int(int) noexcept>();
    test_is_standard_layout_function<int(int)& noexcept>();
    test_is_standard_layout_function<int(int)&& noexcept>();
    test_is_standard_layout_function<int(int) const noexcept>();
    test_is_standard_layout_function<int(int) const& noexcept>();
    test_is_standard_layout_function<int(int) const&& noexcept>();
    test_is_standard_layout_function<int(int) volatile noexcept>();
    test_is_standard_layout_function<int(int) volatile& noexcept>();
    test_is_standard_layout_function<int(int) volatile&& noexcept>();
    test_is_standard_layout_function<int(int) const volatile noexcept>();
    test_is_standard_layout_function<int(int) const volatile& noexcept>();
    test_is_standard_layout_function<int(int) const volatile&& noexcept>();

    test_is_standard_layout_function<int(...)>();
    test_is_standard_layout_function<int(...)&>();
    test_is_standard_layout_function<int(...) &&>();
    test_is_standard_layout_function<int(...) const>();
    test_is_standard_layout_function<int(...) const&>();
    test_is_standard_layout_function<int(...) const&&>();
    test_is_standard_layout_function<int(...) volatile>();
    test_is_standard_layout_function<int(...) volatile&>();
    test_is_standard_layout_function<int(...) volatile&&>();
    test_is_standard_layout_function<int(...) const volatile>();
    test_is_standard_layout_function<int(...) const volatile&>();
    test_is_standard_layout_function<int(...) const volatile&&>();
    test_is_standard_layout_function<int(...) noexcept>();
    test_is_standard_layout_function<int(...)& noexcept>();
    test_is_standard_layout_function<int(...)&& noexcept>();
    test_is_standard_layout_function<int(...) const noexcept>();
    test_is_standard_layout_function<int(...) const& noexcept>();
    test_is_standard_layout_function<int(...) const&& noexcept>();
    test_is_standard_layout_function<int(...) volatile noexcept>();
    test_is_standard_layout_function<int(...) volatile& noexcept>();
    test_is_standard_layout_function<int(...) volatile&& noexcept>();
    test_is_standard_layout_function<int(...) const volatile noexcept>();
    test_is_standard_layout_function<int(...) const volatile& noexcept>();
    test_is_standard_layout_function<int(...) const volatile&& noexcept>();

    test_is_standard_layout_function<int(int, ...)>();
    test_is_standard_layout_function<int(int, ...)&>();
    test_is_standard_layout_function<int(int, ...) &&>();
    test_is_standard_layout_function<int(int, ...) const>();
    test_is_standard_layout_function<int(int, ...) const&>();
    test_is_standard_layout_function<int(int, ...) const&&>();
    test_is_standard_layout_function<int(int, ...) volatile>();
    test_is_standard_layout_function<int(int, ...) volatile&>();
    test_is_standard_layout_function<int(int, ...) volatile&&>();
    test_is_standard_layout_function<int(int, ...) const volatile>();
    test_is_standard_layout_function<int(int, ...) const volatile&>();
    test_is_standard_layout_function<int(int, ...) const volatile&&>();
    test_is_standard_layout_function<int(int, ...) noexcept>();
    test_is_standard_layout_function<int(int, ...)& noexcept>();
    test_is_standard_layout_function<int(int, ...)&& noexcept>();
    test_is_standard_layout_function<int(int, ...) const noexcept>();
    test_is_standard_layout_function<int(int, ...) const& noexcept>();
    test_is_standard_layout_function<int(int, ...) const&& noexcept>();
    test_is_standard_layout_function<int(int, ...) volatile noexcept>();
    test_is_standard_layout_function<int(int, ...) volatile& noexcept>();
    test_is_standard_layout_function<int(int, ...) volatile&& noexcept>();
    test_is_standard_layout_function<int(int, ...) const volatile noexcept>();
    test_is_standard_layout_function<int(int, ...) const volatile& noexcept>();
    test_is_standard_layout_function<int(int, ...) const volatile&& noexcept>();

    test_is_standard_layout<void (*)()>();
    test_is_standard_layout<void (*)() noexcept>();

    test_is_standard_layout<void (*)(int)>();
    test_is_standard_layout<void (*)(int) noexcept>();

    test_is_standard_layout<void (*)(...)>();
    test_is_standard_layout<void (*)(...) noexcept>();

    test_is_standard_layout<void (*)(int, ...)>();
    test_is_standard_layout<void (*)(int, ...) noexcept>();

    test_is_standard_layout<int (*)()>();
    test_is_standard_layout<int (*)() noexcept>();

    test_is_standard_layout<int (*)(int)>();
    test_is_standard_layout<int (*)(int) noexcept>();

    test_is_standard_layout<int (*)(...)>();
    test_is_standard_layout<int (*)(...) noexcept>();

    test_is_standard_layout<int (*)(int, ...)>();
    test_is_standard_layout<int (*)(int, ...) noexcept>();

    test_is_not_standard_layout<void (&)()>();
    test_is_not_standard_layout<void (&)() noexcept>();

    test_is_not_standard_layout<void (&)(int)>();
    test_is_not_standard_layout<void (&)(int) noexcept>();

    test_is_not_standard_layout<void (&)(...)>();
    test_is_not_standard_layout<void (&)(...) noexcept>();

    test_is_not_standard_layout<void (&)(int, ...)>();
    test_is_not_standard_layout<void (&)(int, ...) noexcept>();

    test_is_not_standard_layout<int (&)()>();
    test_is_not_standard_layout<int (&)() noexcept>();

    test_is_not_standard_layout<int (&)(int)>();
    test_is_not_standard_layout<int (&)(int) noexcept>();

    test_is_not_standard_layout<int (&)(...)>();
    test_is_not_standard_layout<int (&)(...) noexcept>();

    test_is_not_standard_layout<int (&)(int, ...)>();
    test_is_not_standard_layout<int (&)(int, ...) noexcept>();

    test_is_not_standard_layout<void(&&)()>();
    test_is_not_standard_layout<void(&&)() noexcept>();

    test_is_not_standard_layout<void(&&)(int)>();
    test_is_not_standard_layout<void(&&)(int) noexcept>();

    test_is_not_standard_layout<void(&&)(...)>();
    test_is_not_standard_layout<void(&&)(...) noexcept>();

    test_is_not_standard_layout<void(&&)(int, ...)>();
    test_is_not_standard_layout<void(&&)(int, ...) noexcept>();

    test_is_not_standard_layout<int(&&)()>();
    test_is_not_standard_layout<int(&&)() noexcept>();

    test_is_not_standard_layout<int(&&)(int)>();
    test_is_not_standard_layout<int(&&)(int) noexcept>();

    test_is_not_standard_layout<int(&&)(...)>();
    test_is_not_standard_layout<int(&&)(...) noexcept>();

    test_is_not_standard_layout<int(&&)(int, ...)>();
    test_is_not_standard_layout<int(&&)(int, ...) noexcept>();

    test_is_standard_layout<void (Class::*)()>();
    test_is_standard_layout<void (Class::*)()&>();
    test_is_standard_layout<void (Class::*)() &&>();
    test_is_standard_layout<void (Class::*)() const>();
    test_is_standard_layout<void (Class::*)() const&>();
    test_is_standard_layout<void (Class::*)() const&&>();
    test_is_standard_layout<void (Class::*)() noexcept>();
    test_is_standard_layout<void (Class::*)()& noexcept>();
    test_is_standard_layout<void (Class::*)()&& noexcept>();
    test_is_standard_layout<void (Class::*)() const noexcept>();
    test_is_standard_layout<void (Class::*)() const& noexcept>();
    test_is_standard_layout<void (Class::*)() const&& noexcept>();

    test_is_standard_layout<void (Class::*)(int)>();
    test_is_standard_layout<void (Class::*)(int)&>();
    test_is_standard_layout<void (Class::*)(int) &&>();
    test_is_standard_layout<void (Class::*)(int) const>();
    test_is_standard_layout<void (Class::*)(int) const&>();
    test_is_standard_layout<void (Class::*)(int) const&&>();
    test_is_standard_layout<void (Class::*)(int) noexcept>();
    test_is_standard_layout<void (Class::*)(int)& noexcept>();
    test_is_standard_layout<void (Class::*)(int)&& noexcept>();
    test_is_standard_layout<void (Class::*)(int) const noexcept>();
    test_is_standard_layout<void (Class::*)(int) const& noexcept>();
    test_is_standard_layout<void (Class::*)(int) const&& noexcept>();

    test_is_standard_layout<void (Class::*)(...)>();
    test_is_standard_layout<void (Class::*)(...)&>();
    test_is_standard_layout<void (Class::*)(...) &&>();
    test_is_standard_layout<void (Class::*)(...) const>();
    test_is_standard_layout<void (Class::*)(...) const&>();
    test_is_standard_layout<void (Class::*)(...) const&&>();
    test_is_standard_layout<void (Class::*)(...) noexcept>();
    test_is_standard_layout<void (Class::*)(...)& noexcept>();
    test_is_standard_layout<void (Class::*)(...)&& noexcept>();
    test_is_standard_layout<void (Class::*)(...) const noexcept>();
    test_is_standard_layout<void (Class::*)(...) const& noexcept>();
    test_is_standard_layout<void (Class::*)(...) const&& noexcept>();

    test_is_standard_layout<void (Class::*)(int, ...)>();
    test_is_standard_layout<void (Class::*)(int, ...)&>();
    test_is_standard_layout<void (Class::*)(int, ...) &&>();
    test_is_standard_layout<void (Class::*)(int, ...) const>();
    test_is_standard_layout<void (Class::*)(int, ...) const&>();
    test_is_standard_layout<void (Class::*)(int, ...) const&&>();
    test_is_standard_layout<void (Class::*)(int, ...) noexcept>();
    test_is_standard_layout<void (Class::*)(int, ...)& noexcept>();
    test_is_standard_layout<void (Class::*)(int, ...)&& noexcept>();
    test_is_standard_layout<void (Class::*)(int, ...) const noexcept>();
    test_is_standard_layout<void (Class::*)(int, ...) const& noexcept>();
    test_is_standard_layout<void (Class::*)(int, ...) const&& noexcept>();

    test_is_standard_layout<int (Class::*)()>();
    test_is_standard_layout<int (Class::*)()&>();
    test_is_standard_layout<int (Class::*)() &&>();
    test_is_standard_layout<int (Class::*)() const>();
    test_is_standard_layout<int (Class::*)() const&>();
    test_is_standard_layout<int (Class::*)() const&&>();
    test_is_standard_layout<int (Class::*)() noexcept>();
    test_is_standard_layout<int (Class::*)()& noexcept>();
    test_is_standard_layout<int (Class::*)()&& noexcept>();
    test_is_standard_layout<int (Class::*)() const noexcept>();
    test_is_standard_layout<int (Class::*)() const& noexcept>();
    test_is_standard_layout<int (Class::*)() const&& noexcept>();

    test_is_standard_layout<int (Class::*)(int)>();
    test_is_standard_layout<int (Class::*)(int)&>();
    test_is_standard_layout<int (Class::*)(int) &&>();
    test_is_standard_layout<int (Class::*)(int) const>();
    test_is_standard_layout<int (Class::*)(int) const&>();
    test_is_standard_layout<int (Class::*)(int) const&&>();
    test_is_standard_layout<int (Class::*)(int) noexcept>();
    test_is_standard_layout<int (Class::*)(int)& noexcept>();
    test_is_standard_layout<int (Class::*)(int)&& noexcept>();
    test_is_standard_layout<int (Class::*)(int) const noexcept>();
    test_is_standard_layout<int (Class::*)(int) const& noexcept>();
    test_is_standard_layout<int (Class::*)(int) const&& noexcept>();

    test_is_standard_layout<int (Class::*)(...)>();
    test_is_standard_layout<int (Class::*)(...)&>();
    test_is_standard_layout<int (Class::*)(...) &&>();
    test_is_standard_layout<int (Class::*)(...) const>();
    test_is_standard_layout<int (Class::*)(...) const&>();
    test_is_standard_layout<int (Class::*)(...) const&&>();
    test_is_standard_layout<int (Class::*)(...) noexcept>();
    test_is_standard_layout<int (Class::*)(...)& noexcept>();
    test_is_standard_layout<int (Class::*)(...)&& noexcept>();
    test_is_standard_layout<int (Class::*)(...) const noexcept>();
    test_is_standard_layout<int (Class::*)(...) const& noexcept>();
    test_is_standard_layout<int (Class::*)(...) const&& noexcept>();

    test_is_standard_layout<int (Class::*)(int, ...)>();
    test_is_standard_layout<int (Class::*)(int, ...)&>();
    test_is_standard_layout<int (Class::*)(int, ...) &&>();
    test_is_standard_layout<int (Class::*)(int, ...) const>();
    test_is_standard_layout<int (Class::*)(int, ...) const&>();
    test_is_standard_layout<int (Class::*)(int, ...) const&&>();
    test_is_standard_layout<int (Class::*)(int, ...) noexcept>();
    test_is_standard_layout<int (Class::*)(int, ...)& noexcept>();
    test_is_standard_layout<int (Class::*)(int, ...)&& noexcept>();
    test_is_standard_layout<int (Class::*)(int, ...) const noexcept>();
    test_is_standard_layout<int (Class::*)(int, ...) const& noexcept>();
    test_is_standard_layout<int (Class::*)(int, ...) const&& noexcept>();
}
