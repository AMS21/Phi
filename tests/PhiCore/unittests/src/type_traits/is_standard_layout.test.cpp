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
    STATIC_REQUIRE(phi::is_standard_layout<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_standard_layout<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_standard_layout_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_standard_layout_v<T>);
#endif

    // Standard compatbilility
    STATIC_REQUIRE(std::is_standard_layout<T>::value);
}

template <typename T>
void test_is_not_standard_layout_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_standard_layout<T>::value);
    STATIC_REQUIRE(phi::is_not_standard_layout<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_standard_layout_v<T>);
    STATIC_REQUIRE(phi::is_not_standard_layout_v<T>);
#endif

    // Standard compatbilility
    STATIC_REQUIRE_FALSE(std::is_standard_layout<T>::value);
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

    test_is_standard_layout<std::vector<int>>();
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
    test_is_standard_layout<Template<incomplete_type>>();
    test_is_standard_layout<VariadicTemplate<>>();
    test_is_standard_layout<VariadicTemplate<void>>();
    test_is_standard_layout<VariadicTemplate<int>>();
    test_is_standard_layout<VariadicTemplate<Class>>();
    test_is_standard_layout<VariadicTemplate<incomplete_type>>();
    test_is_standard_layout<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_standard_layout<PublicDerviedFromTemplate<Base>>();
    test_is_standard_layout<PublicDerviedFromTemplate<Derived>>();
    test_is_standard_layout<PublicDerviedFromTemplate<Class>>();
    test_is_standard_layout<PrivateDerviedFromTemplate<Base>>();
    test_is_standard_layout<PrivateDerviedFromTemplate<Derived>>();
    test_is_standard_layout<PrivateDerviedFromTemplate<Class>>();
    test_is_standard_layout<ProtectedDerviedFromTemplate<Base>>();
    test_is_standard_layout<ProtectedDerviedFromTemplate<Derived>>();
    test_is_standard_layout<ProtectedDerviedFromTemplate<Class>>();
    test_is_standard_layout<Union>();
    test_is_standard_layout<NonEmptyUnion>();
    test_is_standard_layout<Empty>();
    test_is_not_standard_layout<NotEmpty>();
    test_is_standard_layout<bit_zero>();
    test_is_standard_layout<bit_one>();
    test_is_standard_layout<Base>();
    test_is_standard_layout<Derived>();
    test_is_not_standard_layout<Abstract>();
    test_is_not_standard_layout<PublicAbstract>();
    test_is_not_standard_layout<PrivateAbstract>();
    test_is_not_standard_layout<ProtectedAbstract>();
    test_is_not_standard_layout<AbstractTemplate<int>>();
    test_is_standard_layout<AbstractTemplate<double>>();
    test_is_not_standard_layout<AbstractTemplate<Class>>();
    test_is_not_standard_layout<AbstractTemplate<incomplete_type>>();
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
    test_is_not_standard_layout<Function>();
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

    test_is_not_standard_layout<void()>();
    test_is_not_standard_layout<void()&>();
    test_is_not_standard_layout<void() &&>();
    test_is_not_standard_layout<void() const>();
    test_is_not_standard_layout<void() const&>();
    test_is_not_standard_layout<void() const&&>();
    test_is_not_standard_layout<void() volatile>();
    test_is_not_standard_layout<void() volatile&>();
    test_is_not_standard_layout<void() volatile&&>();
    test_is_not_standard_layout<void() const volatile>();
    test_is_not_standard_layout<void() const volatile&>();
    test_is_not_standard_layout<void() const volatile&&>();
    test_is_not_standard_layout<void() noexcept>();
    test_is_not_standard_layout<void()& noexcept>();
    test_is_not_standard_layout<void()&& noexcept>();
    test_is_not_standard_layout<void() const noexcept>();
    test_is_not_standard_layout<void() const& noexcept>();
    test_is_not_standard_layout<void() const&& noexcept>();
    test_is_not_standard_layout<void() volatile noexcept>();
    test_is_not_standard_layout<void() volatile& noexcept>();
    test_is_not_standard_layout<void() volatile&& noexcept>();
    test_is_not_standard_layout<void() const volatile noexcept>();
    test_is_not_standard_layout<void() const volatile& noexcept>();
    test_is_not_standard_layout<void() const volatile&& noexcept>();

    test_is_not_standard_layout<void(int)>();
    test_is_not_standard_layout<void(int)&>();
    test_is_not_standard_layout<void(int) &&>();
    test_is_not_standard_layout<void(int) const>();
    test_is_not_standard_layout<void(int) const&>();
    test_is_not_standard_layout<void(int) const&&>();
    test_is_not_standard_layout<void(int) volatile>();
    test_is_not_standard_layout<void(int) volatile&>();
    test_is_not_standard_layout<void(int) volatile&&>();
    test_is_not_standard_layout<void(int) const volatile>();
    test_is_not_standard_layout<void(int) const volatile&>();
    test_is_not_standard_layout<void(int) const volatile&&>();
    test_is_not_standard_layout<void(int) noexcept>();
    test_is_not_standard_layout<void(int)& noexcept>();
    test_is_not_standard_layout<void(int)&& noexcept>();
    test_is_not_standard_layout<void(int) const noexcept>();
    test_is_not_standard_layout<void(int) const& noexcept>();
    test_is_not_standard_layout<void(int) const&& noexcept>();
    test_is_not_standard_layout<void(int) volatile noexcept>();
    test_is_not_standard_layout<void(int) volatile& noexcept>();
    test_is_not_standard_layout<void(int) volatile&& noexcept>();
    test_is_not_standard_layout<void(int) const volatile noexcept>();
    test_is_not_standard_layout<void(int) const volatile& noexcept>();
    test_is_not_standard_layout<void(int) const volatile&& noexcept>();

    test_is_not_standard_layout<void(...)>();
    test_is_not_standard_layout<void(...)&>();
    test_is_not_standard_layout<void(...) &&>();
    test_is_not_standard_layout<void(...) const>();
    test_is_not_standard_layout<void(...) const&>();
    test_is_not_standard_layout<void(...) const&&>();
    test_is_not_standard_layout<void(...) volatile>();
    test_is_not_standard_layout<void(...) volatile&>();
    test_is_not_standard_layout<void(...) volatile&&>();
    test_is_not_standard_layout<void(...) const volatile>();
    test_is_not_standard_layout<void(...) const volatile&>();
    test_is_not_standard_layout<void(...) const volatile&&>();
    test_is_not_standard_layout<void(...) noexcept>();
    test_is_not_standard_layout<void(...)& noexcept>();
    test_is_not_standard_layout<void(...)&& noexcept>();
    test_is_not_standard_layout<void(...) const noexcept>();
    test_is_not_standard_layout<void(...) const& noexcept>();
    test_is_not_standard_layout<void(...) const&& noexcept>();
    test_is_not_standard_layout<void(...) volatile noexcept>();
    test_is_not_standard_layout<void(...) volatile& noexcept>();
    test_is_not_standard_layout<void(...) volatile&& noexcept>();
    test_is_not_standard_layout<void(...) const volatile noexcept>();
    test_is_not_standard_layout<void(...) const volatile& noexcept>();
    test_is_not_standard_layout<void(...) const volatile&& noexcept>();

    test_is_not_standard_layout<void(int, ...)>();
    test_is_not_standard_layout<void(int, ...)&>();
    test_is_not_standard_layout<void(int, ...) &&>();
    test_is_not_standard_layout<void(int, ...) const>();
    test_is_not_standard_layout<void(int, ...) const&>();
    test_is_not_standard_layout<void(int, ...) const&&>();
    test_is_not_standard_layout<void(int, ...) volatile>();
    test_is_not_standard_layout<void(int, ...) volatile&>();
    test_is_not_standard_layout<void(int, ...) volatile&&>();
    test_is_not_standard_layout<void(int, ...) const volatile>();
    test_is_not_standard_layout<void(int, ...) const volatile&>();
    test_is_not_standard_layout<void(int, ...) const volatile&&>();
    test_is_not_standard_layout<void(int, ...) noexcept>();
    test_is_not_standard_layout<void(int, ...)& noexcept>();
    test_is_not_standard_layout<void(int, ...)&& noexcept>();
    test_is_not_standard_layout<void(int, ...) const noexcept>();
    test_is_not_standard_layout<void(int, ...) const& noexcept>();
    test_is_not_standard_layout<void(int, ...) const&& noexcept>();
    test_is_not_standard_layout<void(int, ...) volatile noexcept>();
    test_is_not_standard_layout<void(int, ...) volatile& noexcept>();
    test_is_not_standard_layout<void(int, ...) volatile&& noexcept>();
    test_is_not_standard_layout<void(int, ...) const volatile noexcept>();
    test_is_not_standard_layout<void(int, ...) const volatile& noexcept>();
    test_is_not_standard_layout<void(int, ...) const volatile&& noexcept>();

    test_is_not_standard_layout<int()>();
    test_is_not_standard_layout<int()&>();
    test_is_not_standard_layout<int() &&>();
    test_is_not_standard_layout<int() const>();
    test_is_not_standard_layout<int() const&>();
    test_is_not_standard_layout<int() const&&>();
    test_is_not_standard_layout<int() volatile>();
    test_is_not_standard_layout<int() volatile&>();
    test_is_not_standard_layout<int() volatile&&>();
    test_is_not_standard_layout<int() const volatile>();
    test_is_not_standard_layout<int() const volatile&>();
    test_is_not_standard_layout<int() const volatile&&>();
    test_is_not_standard_layout<int() noexcept>();
    test_is_not_standard_layout<int()& noexcept>();
    test_is_not_standard_layout<int()&& noexcept>();
    test_is_not_standard_layout<int() const noexcept>();
    test_is_not_standard_layout<int() const& noexcept>();
    test_is_not_standard_layout<int() const&& noexcept>();
    test_is_not_standard_layout<int() volatile noexcept>();
    test_is_not_standard_layout<int() volatile& noexcept>();
    test_is_not_standard_layout<int() volatile&& noexcept>();
    test_is_not_standard_layout<int() const volatile noexcept>();
    test_is_not_standard_layout<int() const volatile& noexcept>();
    test_is_not_standard_layout<int() const volatile&& noexcept>();

    test_is_not_standard_layout<int(int)>();
    test_is_not_standard_layout<int(int)&>();
    test_is_not_standard_layout<int(int) &&>();
    test_is_not_standard_layout<int(int) const>();
    test_is_not_standard_layout<int(int) const&>();
    test_is_not_standard_layout<int(int) const&&>();
    test_is_not_standard_layout<int(int) volatile>();
    test_is_not_standard_layout<int(int) volatile&>();
    test_is_not_standard_layout<int(int) volatile&&>();
    test_is_not_standard_layout<int(int) const volatile>();
    test_is_not_standard_layout<int(int) const volatile&>();
    test_is_not_standard_layout<int(int) const volatile&&>();
    test_is_not_standard_layout<int(int) noexcept>();
    test_is_not_standard_layout<int(int)& noexcept>();
    test_is_not_standard_layout<int(int)&& noexcept>();
    test_is_not_standard_layout<int(int) const noexcept>();
    test_is_not_standard_layout<int(int) const& noexcept>();
    test_is_not_standard_layout<int(int) const&& noexcept>();
    test_is_not_standard_layout<int(int) volatile noexcept>();
    test_is_not_standard_layout<int(int) volatile& noexcept>();
    test_is_not_standard_layout<int(int) volatile&& noexcept>();
    test_is_not_standard_layout<int(int) const volatile noexcept>();
    test_is_not_standard_layout<int(int) const volatile& noexcept>();
    test_is_not_standard_layout<int(int) const volatile&& noexcept>();

    test_is_not_standard_layout<int(...)>();
    test_is_not_standard_layout<int(...)&>();
    test_is_not_standard_layout<int(...) &&>();
    test_is_not_standard_layout<int(...) const>();
    test_is_not_standard_layout<int(...) const&>();
    test_is_not_standard_layout<int(...) const&&>();
    test_is_not_standard_layout<int(...) volatile>();
    test_is_not_standard_layout<int(...) volatile&>();
    test_is_not_standard_layout<int(...) volatile&&>();
    test_is_not_standard_layout<int(...) const volatile>();
    test_is_not_standard_layout<int(...) const volatile&>();
    test_is_not_standard_layout<int(...) const volatile&&>();
    test_is_not_standard_layout<int(...) noexcept>();
    test_is_not_standard_layout<int(...)& noexcept>();
    test_is_not_standard_layout<int(...)&& noexcept>();
    test_is_not_standard_layout<int(...) const noexcept>();
    test_is_not_standard_layout<int(...) const& noexcept>();
    test_is_not_standard_layout<int(...) const&& noexcept>();
    test_is_not_standard_layout<int(...) volatile noexcept>();
    test_is_not_standard_layout<int(...) volatile& noexcept>();
    test_is_not_standard_layout<int(...) volatile&& noexcept>();
    test_is_not_standard_layout<int(...) const volatile noexcept>();
    test_is_not_standard_layout<int(...) const volatile& noexcept>();
    test_is_not_standard_layout<int(...) const volatile&& noexcept>();

    test_is_not_standard_layout<int(int, ...)>();
    test_is_not_standard_layout<int(int, ...)&>();
    test_is_not_standard_layout<int(int, ...) &&>();
    test_is_not_standard_layout<int(int, ...) const>();
    test_is_not_standard_layout<int(int, ...) const&>();
    test_is_not_standard_layout<int(int, ...) const&&>();
    test_is_not_standard_layout<int(int, ...) volatile>();
    test_is_not_standard_layout<int(int, ...) volatile&>();
    test_is_not_standard_layout<int(int, ...) volatile&&>();
    test_is_not_standard_layout<int(int, ...) const volatile>();
    test_is_not_standard_layout<int(int, ...) const volatile&>();
    test_is_not_standard_layout<int(int, ...) const volatile&&>();
    test_is_not_standard_layout<int(int, ...) noexcept>();
    test_is_not_standard_layout<int(int, ...)& noexcept>();
    test_is_not_standard_layout<int(int, ...)&& noexcept>();
    test_is_not_standard_layout<int(int, ...) const noexcept>();
    test_is_not_standard_layout<int(int, ...) const& noexcept>();
    test_is_not_standard_layout<int(int, ...) const&& noexcept>();
    test_is_not_standard_layout<int(int, ...) volatile noexcept>();
    test_is_not_standard_layout<int(int, ...) volatile& noexcept>();
    test_is_not_standard_layout<int(int, ...) volatile&& noexcept>();
    test_is_not_standard_layout<int(int, ...) const volatile noexcept>();
    test_is_not_standard_layout<int(int, ...) const volatile& noexcept>();
    test_is_not_standard_layout<int(int, ...) const volatile&& noexcept>();

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
