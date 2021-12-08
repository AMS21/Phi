#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_const.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_const_impl()
{
    STATIC_REQUIRE(phi::is_const<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_const<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_const_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_const_v<T>);
#endif

    // Standard compatibility
    STATIC_REQUIRE(std::is_const<T>::value);
}

template <typename T>
void test_is_not_const_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_const<T>::value);
    STATIC_REQUIRE(phi::is_not_const<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_const_v<T>);
    STATIC_REQUIRE(phi::is_not_const_v<T>);
#endif

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_const<T>::value);
}

template <typename T>
void test_is_const()
{
    test_is_not_const_impl<T>();
    test_is_const_impl<const T>();
    test_is_not_const_impl<volatile T>();
    test_is_const_impl<const volatile T>();
}

template <typename T>
void test_is_const_always()
{
    test_is_const_impl<T>();
    test_is_const_impl<const T>();
    test_is_const_impl<volatile T>();
    test_is_const_impl<const volatile T>();
}

template <typename T>
void test_is_not_const()
{
    test_is_not_const_impl<T>();
    test_is_not_const_impl<const T>();
    test_is_not_const_impl<volatile T>();
    test_is_not_const_impl<const volatile T>();
}

TEST_CASE("is_const")
{
    test_is_const<void>();
    test_is_const<phi::nullptr_t>();
    test_is_const<bool>();
    test_is_const<char>();
    test_is_const<signed char>();
    test_is_const<unsigned char>();
    test_is_const<short>();
    test_is_const<unsigned short>();
    test_is_const<int>();
    test_is_const<unsigned int>();
    test_is_const<long>();
    test_is_const<unsigned long>();
    test_is_const<long long>();
    test_is_const<unsigned long long>();
    test_is_const<float>();
    test_is_const<double>();
    test_is_const<long double>();
    test_is_const<char8_t>();
    test_is_const<char16_t>();
    test_is_const<char32_t>();
    test_is_const<wchar_t>();

    test_is_const<phi::boolean>();
    test_is_const<phi::integer<signed char>>();
    test_is_const<phi::integer<unsigned char>>();
    test_is_const<phi::integer<short>>();
    test_is_const<phi::integer<unsigned short>>();
    test_is_const<phi::integer<int>>();
    test_is_const<phi::integer<unsigned int>>();
    test_is_const<phi::integer<long>>();
    test_is_const<phi::integer<unsigned long>>();
    test_is_const<phi::integer<long long>>();
    test_is_const<phi::integer<unsigned long long>>();
    test_is_const<phi::floating_point<float>>();
    test_is_const<phi::floating_point<double>>();
    test_is_const<phi::floating_point<long double>>();

    test_is_const<std::vector<int>>();
    test_is_const<phi::scope_ptr<int>>();

    test_is_not_const<int&>();
    test_is_not_const<const int&>();
    test_is_not_const<volatile int&>();
    test_is_not_const<const volatile int&>();
    test_is_not_const<int&&>();
    test_is_not_const<const int&&>();
    test_is_not_const<volatile int&&>();
    test_is_not_const<const volatile int&&>();
    test_is_const<int*>();
    test_is_const<const int*>();
    test_is_const<volatile int*>();
    test_is_const<const volatile int*>();
    test_is_const<int**>();
    test_is_const<const int**>();
    test_is_const<volatile int**>();
    test_is_const<const volatile int**>();
    test_is_not_const<int*&>();
    test_is_not_const<const int*&>();
    test_is_not_const<volatile int*&>();
    test_is_not_const<const volatile int*&>();
    test_is_not_const<int*&&>();
    test_is_not_const<const int*&&>();
    test_is_not_const<volatile int*&&>();
    test_is_not_const<const volatile int*&&>();
    test_is_const<void*>();
    test_is_const<char[3]>();
    test_is_const<char[]>();
    test_is_const<char* [3]>();
    test_is_const<char*[]>();
    test_is_const<int(*)[3]>();
    test_is_const<int(*)[]>();
    test_is_not_const<int(&)[3]>();
    test_is_not_const<int(&)[]>();
    test_is_not_const<int(&&)[3]>();
    test_is_not_const<int(&&)[]>();
    test_is_const<char[3][2]>();
    test_is_const<char[][2]>();
    test_is_const<char* [3][2]>();
    test_is_const<char*[][2]>();
    test_is_const<int(*)[3][2]>();
    test_is_const<int(*)[][2]>();
    test_is_not_const<int(&)[3][2]>();
    test_is_not_const<int(&)[][2]>();
    test_is_not_const<int(&&)[3][2]>();
    test_is_not_const<int(&&)[][2]>();
    test_is_const<Class>();
    test_is_const<Class[]>();
    test_is_const<Class[2]>();
    test_is_const<Template<void>>();
    test_is_const<Template<int>>();
    test_is_const<Template<Class>>();
    test_is_const<Template<incomplete_type>>();
    test_is_const<VariadicTemplate<>>();
    test_is_const<VariadicTemplate<void>>();
    test_is_const<VariadicTemplate<int>>();
    test_is_const<VariadicTemplate<Class>>();
    test_is_const<VariadicTemplate<incomplete_type>>();
    test_is_const<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_const<PublicDerviedFromTemplate<Base>>();
    test_is_const<PublicDerviedFromTemplate<Derived>>();
    test_is_const<PublicDerviedFromTemplate<Class>>();
    test_is_const<PrivateDerviedFromTemplate<Base>>();
    test_is_const<PrivateDerviedFromTemplate<Derived>>();
    test_is_const<PrivateDerviedFromTemplate<Class>>();
    test_is_const<ProtectedDerviedFromTemplate<Base>>();
    test_is_const<ProtectedDerviedFromTemplate<Derived>>();
    test_is_const<ProtectedDerviedFromTemplate<Class>>();
    test_is_const<Union>();
    test_is_const<NonEmptyUnion>();
    test_is_const<Empty>();
    test_is_const<NotEmpty>();
    test_is_const<bit_zero>();
    test_is_const<bit_one>();
    test_is_const<Base>();
    test_is_const<Derived>();
    test_is_const<Abstract>();
    test_is_const<PublicAbstract>();
    test_is_const<PrivateAbstract>();
    test_is_const<ProtectedAbstract>();
    test_is_const<AbstractTemplate<int>>();
    test_is_const<AbstractTemplate<double>>();
    test_is_const<AbstractTemplate<Class>>();
    test_is_const<AbstractTemplate<incomplete_type>>();
    test_is_const<Final>();
    test_is_const<PublicDestructor>();
    test_is_const<ProtectedDestructor>();
    test_is_const<PrivateDestructor>();
    test_is_const<VirtualPublicDestructor>();
    test_is_const<VirtualProtectedDestructor>();
    test_is_const<VirtualPrivateDestructor>();
    test_is_const<PurePublicDestructor>();
    test_is_const<PureProtectedDestructor>();
    test_is_const<PurePrivateDestructor>();
    test_is_const<DeletedPublicDestructor>();
    test_is_const<DeletedProtectedDestructor>();
    test_is_const<DeletedPrivateDestructor>();
    test_is_const<DeletedVirtualPublicDestructor>();
    test_is_const<DeletedVirtualProtectedDestructor>();
    test_is_const<DeletedVirtualPrivateDestructor>();
    test_is_const<Enum>();
    test_is_const<EnumSigned>();
    test_is_const<EnumUnsigned>();
    test_is_const<EnumClass>();
    test_is_const<EnumStruct>();
    test_is_not_const<Function>();
    test_is_const<FunctionPtr>();
    test_is_const<MemberObjectPtr>();
    test_is_const<MemberFunctionPtr>();
    test_is_const<incomplete_type>();
    test_is_const<IncompleteTemplate<void>>();
    test_is_const<IncompleteTemplate<int>>();
    test_is_const<IncompleteTemplate<Class>>();
    test_is_const<IncompleteTemplate<incomplete_type>>();
    test_is_const<IncompleteVariadicTemplate<>>();
    test_is_const<IncompleteVariadicTemplate<void>>();
    test_is_const<IncompleteVariadicTemplate<int>>();
    test_is_const<IncompleteVariadicTemplate<Class>>();
    test_is_const<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_const<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_const<int Class::*>();
    test_is_const<float Class::*>();
    test_is_const<void * Class::*>();
    test_is_const<int * Class::*>();
    test_is_not_const<int Class::*&>();
    test_is_not_const<float Class::*&>();
    test_is_not_const<void * Class::*&>();
    test_is_not_const<int * Class::*&>();
    test_is_not_const<int Class::*&&>();
    test_is_not_const<float Class::*&&>();
    test_is_not_const<void * Class::*&&>();
    test_is_not_const<int * Class::*&&>();
    test_is_const_always<int Class::*const>();
    test_is_const_always<float Class::*const>();
    test_is_const_always<void * Class::*const>();
    test_is_not_const<int Class::*const&>();
    test_is_not_const<float Class::*const&>();
    test_is_not_const<void * Class::*const&>();
    test_is_not_const<int Class::*const&&>();
    test_is_not_const<float Class::*const&&>();
    test_is_not_const<void * Class::*const&&>();
    test_is_const<int Class::*volatile>();
    test_is_const<float Class::*volatile>();
    test_is_const<void * Class::*volatile>();
    test_is_not_const<int Class::*volatile&>();
    test_is_not_const<float Class::*volatile&>();
    test_is_not_const<void * Class::*volatile&>();
    test_is_not_const<int Class::*volatile&&>();
    test_is_not_const<float Class::*volatile&&>();
    test_is_not_const<void * Class::*volatile&&>();
    test_is_const_always<int Class::*const volatile>();
    test_is_const_always<float Class::*const volatile>();
    test_is_const_always<void * Class::*const volatile>();
    test_is_not_const<int Class::*const volatile&>();
    test_is_not_const<float Class::*const volatile&>();
    test_is_not_const<void * Class::*const volatile&>();
    test_is_not_const<int Class::*const volatile&&>();
    test_is_not_const<float Class::*const volatile&&>();
    test_is_not_const<void * Class::*const volatile&&>();
    test_is_const<NonCopyable>();
    test_is_const<NonMoveable>();
    test_is_const<NonConstructible>();
    test_is_const<Tracked>();
    test_is_const<TrapConstructible>();
    test_is_const<TrapImplicitConversion>();
    test_is_const<TrapComma>();
    test_is_const<TrapCall>();
    test_is_const<TrapSelfAssign>();
    test_is_const<TrapDeref>();
    test_is_const<TrapArraySubscript>();

    test_is_not_const<void()>();
    test_is_not_const<void()&>();
    test_is_not_const<void() &&>();
    test_is_not_const<void() const>();
    test_is_not_const<void() const&>();
    test_is_not_const<void() const&&>();
    test_is_not_const<void() volatile>();
    test_is_not_const<void() volatile&>();
    test_is_not_const<void() volatile&&>();
    test_is_not_const<void() const volatile>();
    test_is_not_const<void() const volatile&>();
    test_is_not_const<void() const volatile&&>();
    test_is_not_const<void() noexcept>();
    test_is_not_const<void()& noexcept>();
    test_is_not_const<void()&& noexcept>();
    test_is_not_const<void() const noexcept>();
    test_is_not_const<void() const& noexcept>();
    test_is_not_const<void() const&& noexcept>();
    test_is_not_const<void() volatile noexcept>();
    test_is_not_const<void() volatile& noexcept>();
    test_is_not_const<void() volatile&& noexcept>();
    test_is_not_const<void() const volatile noexcept>();
    test_is_not_const<void() const volatile& noexcept>();
    test_is_not_const<void() const volatile&& noexcept>();

    test_is_not_const<void(int)>();
    test_is_not_const<void(int)&>();
    test_is_not_const<void(int) &&>();
    test_is_not_const<void(int) const>();
    test_is_not_const<void(int) const&>();
    test_is_not_const<void(int) const&&>();
    test_is_not_const<void(int) volatile>();
    test_is_not_const<void(int) volatile&>();
    test_is_not_const<void(int) volatile&&>();
    test_is_not_const<void(int) const volatile>();
    test_is_not_const<void(int) const volatile&>();
    test_is_not_const<void(int) const volatile&&>();
    test_is_not_const<void(int) noexcept>();
    test_is_not_const<void(int)& noexcept>();
    test_is_not_const<void(int)&& noexcept>();
    test_is_not_const<void(int) const noexcept>();
    test_is_not_const<void(int) const& noexcept>();
    test_is_not_const<void(int) const&& noexcept>();
    test_is_not_const<void(int) volatile noexcept>();
    test_is_not_const<void(int) volatile& noexcept>();
    test_is_not_const<void(int) volatile&& noexcept>();
    test_is_not_const<void(int) const volatile noexcept>();
    test_is_not_const<void(int) const volatile& noexcept>();
    test_is_not_const<void(int) const volatile&& noexcept>();

    test_is_not_const<void(...)>();
    test_is_not_const<void(...)&>();
    test_is_not_const<void(...) &&>();
    test_is_not_const<void(...) const>();
    test_is_not_const<void(...) const&>();
    test_is_not_const<void(...) const&&>();
    test_is_not_const<void(...) volatile>();
    test_is_not_const<void(...) volatile&>();
    test_is_not_const<void(...) volatile&&>();
    test_is_not_const<void(...) const volatile>();
    test_is_not_const<void(...) const volatile&>();
    test_is_not_const<void(...) const volatile&&>();
    test_is_not_const<void(...) noexcept>();
    test_is_not_const<void(...)& noexcept>();
    test_is_not_const<void(...)&& noexcept>();
    test_is_not_const<void(...) const noexcept>();
    test_is_not_const<void(...) const& noexcept>();
    test_is_not_const<void(...) const&& noexcept>();
    test_is_not_const<void(...) volatile noexcept>();
    test_is_not_const<void(...) volatile& noexcept>();
    test_is_not_const<void(...) volatile&& noexcept>();
    test_is_not_const<void(...) const volatile noexcept>();
    test_is_not_const<void(...) const volatile& noexcept>();
    test_is_not_const<void(...) const volatile&& noexcept>();

    test_is_not_const<void(int, ...)>();
    test_is_not_const<void(int, ...)&>();
    test_is_not_const<void(int, ...) &&>();
    test_is_not_const<void(int, ...) const>();
    test_is_not_const<void(int, ...) const&>();
    test_is_not_const<void(int, ...) const&&>();
    test_is_not_const<void(int, ...) volatile>();
    test_is_not_const<void(int, ...) volatile&>();
    test_is_not_const<void(int, ...) volatile&&>();
    test_is_not_const<void(int, ...) const volatile>();
    test_is_not_const<void(int, ...) const volatile&>();
    test_is_not_const<void(int, ...) const volatile&&>();
    test_is_not_const<void(int, ...) noexcept>();
    test_is_not_const<void(int, ...)& noexcept>();
    test_is_not_const<void(int, ...)&& noexcept>();
    test_is_not_const<void(int, ...) const noexcept>();
    test_is_not_const<void(int, ...) const& noexcept>();
    test_is_not_const<void(int, ...) const&& noexcept>();
    test_is_not_const<void(int, ...) volatile noexcept>();
    test_is_not_const<void(int, ...) volatile& noexcept>();
    test_is_not_const<void(int, ...) volatile&& noexcept>();
    test_is_not_const<void(int, ...) const volatile noexcept>();
    test_is_not_const<void(int, ...) const volatile& noexcept>();
    test_is_not_const<void(int, ...) const volatile&& noexcept>();

    test_is_not_const<int()>();
    test_is_not_const<int()&>();
    test_is_not_const<int() &&>();
    test_is_not_const<int() const>();
    test_is_not_const<int() const&>();
    test_is_not_const<int() const&&>();
    test_is_not_const<int() volatile>();
    test_is_not_const<int() volatile&>();
    test_is_not_const<int() volatile&&>();
    test_is_not_const<int() const volatile>();
    test_is_not_const<int() const volatile&>();
    test_is_not_const<int() const volatile&&>();
    test_is_not_const<int() noexcept>();
    test_is_not_const<int()& noexcept>();
    test_is_not_const<int()&& noexcept>();
    test_is_not_const<int() const noexcept>();
    test_is_not_const<int() const& noexcept>();
    test_is_not_const<int() const&& noexcept>();
    test_is_not_const<int() volatile noexcept>();
    test_is_not_const<int() volatile& noexcept>();
    test_is_not_const<int() volatile&& noexcept>();
    test_is_not_const<int() const volatile noexcept>();
    test_is_not_const<int() const volatile& noexcept>();
    test_is_not_const<int() const volatile&& noexcept>();

    test_is_not_const<int(int)>();
    test_is_not_const<int(int)&>();
    test_is_not_const<int(int) &&>();
    test_is_not_const<int(int) const>();
    test_is_not_const<int(int) const&>();
    test_is_not_const<int(int) const&&>();
    test_is_not_const<int(int) volatile>();
    test_is_not_const<int(int) volatile&>();
    test_is_not_const<int(int) volatile&&>();
    test_is_not_const<int(int) const volatile>();
    test_is_not_const<int(int) const volatile&>();
    test_is_not_const<int(int) const volatile&&>();
    test_is_not_const<int(int) noexcept>();
    test_is_not_const<int(int)& noexcept>();
    test_is_not_const<int(int)&& noexcept>();
    test_is_not_const<int(int) const noexcept>();
    test_is_not_const<int(int) const& noexcept>();
    test_is_not_const<int(int) const&& noexcept>();
    test_is_not_const<int(int) volatile noexcept>();
    test_is_not_const<int(int) volatile& noexcept>();
    test_is_not_const<int(int) volatile&& noexcept>();
    test_is_not_const<int(int) const volatile noexcept>();
    test_is_not_const<int(int) const volatile& noexcept>();
    test_is_not_const<int(int) const volatile&& noexcept>();

    test_is_not_const<int(...)>();
    test_is_not_const<int(...)&>();
    test_is_not_const<int(...) &&>();
    test_is_not_const<int(...) const>();
    test_is_not_const<int(...) const&>();
    test_is_not_const<int(...) const&&>();
    test_is_not_const<int(...) volatile>();
    test_is_not_const<int(...) volatile&>();
    test_is_not_const<int(...) volatile&&>();
    test_is_not_const<int(...) const volatile>();
    test_is_not_const<int(...) const volatile&>();
    test_is_not_const<int(...) const volatile&&>();
    test_is_not_const<int(...) noexcept>();
    test_is_not_const<int(...)& noexcept>();
    test_is_not_const<int(...)&& noexcept>();
    test_is_not_const<int(...) const noexcept>();
    test_is_not_const<int(...) const& noexcept>();
    test_is_not_const<int(...) const&& noexcept>();
    test_is_not_const<int(...) volatile noexcept>();
    test_is_not_const<int(...) volatile& noexcept>();
    test_is_not_const<int(...) volatile&& noexcept>();
    test_is_not_const<int(...) const volatile noexcept>();
    test_is_not_const<int(...) const volatile& noexcept>();
    test_is_not_const<int(...) const volatile&& noexcept>();

    test_is_not_const<int(int, ...)>();
    test_is_not_const<int(int, ...)&>();
    test_is_not_const<int(int, ...) &&>();
    test_is_not_const<int(int, ...) const>();
    test_is_not_const<int(int, ...) const&>();
    test_is_not_const<int(int, ...) const&&>();
    test_is_not_const<int(int, ...) volatile>();
    test_is_not_const<int(int, ...) volatile&>();
    test_is_not_const<int(int, ...) volatile&&>();
    test_is_not_const<int(int, ...) const volatile>();
    test_is_not_const<int(int, ...) const volatile&>();
    test_is_not_const<int(int, ...) const volatile&&>();
    test_is_not_const<int(int, ...) noexcept>();
    test_is_not_const<int(int, ...)& noexcept>();
    test_is_not_const<int(int, ...)&& noexcept>();
    test_is_not_const<int(int, ...) const noexcept>();
    test_is_not_const<int(int, ...) const& noexcept>();
    test_is_not_const<int(int, ...) const&& noexcept>();
    test_is_not_const<int(int, ...) volatile noexcept>();
    test_is_not_const<int(int, ...) volatile& noexcept>();
    test_is_not_const<int(int, ...) volatile&& noexcept>();
    test_is_not_const<int(int, ...) const volatile noexcept>();
    test_is_not_const<int(int, ...) const volatile& noexcept>();
    test_is_not_const<int(int, ...) const volatile&& noexcept>();

    test_is_const<void (*)()>();
    test_is_const<void (*)() noexcept>();

    test_is_const<void (*)(int)>();
    test_is_const<void (*)(int) noexcept>();

    test_is_const<void (*)(...)>();
    test_is_const<void (*)(...) noexcept>();

    test_is_const<void (*)(int, ...)>();
    test_is_const<void (*)(int, ...) noexcept>();

    test_is_const<int (*)()>();
    test_is_const<int (*)() noexcept>();

    test_is_const<int (*)(int)>();
    test_is_const<int (*)(int) noexcept>();

    test_is_const<int (*)(...)>();
    test_is_const<int (*)(...) noexcept>();

    test_is_const<int (*)(int, ...)>();
    test_is_const<int (*)(int, ...) noexcept>();

    test_is_not_const<void (&)()>();
    test_is_not_const<void (&)() noexcept>();

    test_is_not_const<void (&)(int)>();
    test_is_not_const<void (&)(int) noexcept>();

    test_is_not_const<void (&)(...)>();
    test_is_not_const<void (&)(...) noexcept>();

    test_is_not_const<void (&)(int, ...)>();
    test_is_not_const<void (&)(int, ...) noexcept>();

    test_is_not_const<int (&)()>();
    test_is_not_const<int (&)() noexcept>();

    test_is_not_const<int (&)(int)>();
    test_is_not_const<int (&)(int) noexcept>();

    test_is_not_const<int (&)(...)>();
    test_is_not_const<int (&)(...) noexcept>();

    test_is_not_const<int (&)(int, ...)>();
    test_is_not_const<int (&)(int, ...) noexcept>();

    test_is_not_const<void(&&)()>();
    test_is_not_const<void(&&)() noexcept>();

    test_is_not_const<void(&&)(int)>();
    test_is_not_const<void(&&)(int) noexcept>();

    test_is_not_const<void(&&)(...)>();
    test_is_not_const<void(&&)(...) noexcept>();

    test_is_not_const<void(&&)(int, ...)>();
    test_is_not_const<void(&&)(int, ...) noexcept>();

    test_is_not_const<int(&&)()>();
    test_is_not_const<int(&&)() noexcept>();

    test_is_not_const<int(&&)(int)>();
    test_is_not_const<int(&&)(int) noexcept>();

    test_is_not_const<int(&&)(...)>();
    test_is_not_const<int(&&)(...) noexcept>();

    test_is_not_const<int(&&)(int, ...)>();
    test_is_not_const<int(&&)(int, ...) noexcept>();

    test_is_const<void (Class::*)()>();
    test_is_const<void (Class::*)()&>();
    test_is_const<void (Class::*)() &&>();
    test_is_const<void (Class::*)() const>();
    test_is_const<void (Class::*)() const&>();
    test_is_const<void (Class::*)() const&&>();
    test_is_const<void (Class::*)() noexcept>();
    test_is_const<void (Class::*)()& noexcept>();
    test_is_const<void (Class::*)()&& noexcept>();
    test_is_const<void (Class::*)() const noexcept>();
    test_is_const<void (Class::*)() const& noexcept>();
    test_is_const<void (Class::*)() const&& noexcept>();

    test_is_const<void (Class::*)(int)>();
    test_is_const<void (Class::*)(int)&>();
    test_is_const<void (Class::*)(int) &&>();
    test_is_const<void (Class::*)(int) const>();
    test_is_const<void (Class::*)(int) const&>();
    test_is_const<void (Class::*)(int) const&&>();
    test_is_const<void (Class::*)(int) noexcept>();
    test_is_const<void (Class::*)(int)& noexcept>();
    test_is_const<void (Class::*)(int)&& noexcept>();
    test_is_const<void (Class::*)(int) const noexcept>();
    test_is_const<void (Class::*)(int) const& noexcept>();
    test_is_const<void (Class::*)(int) const&& noexcept>();

    test_is_const<void (Class::*)(...)>();
    test_is_const<void (Class::*)(...)&>();
    test_is_const<void (Class::*)(...) &&>();
    test_is_const<void (Class::*)(...) const>();
    test_is_const<void (Class::*)(...) const&>();
    test_is_const<void (Class::*)(...) const&&>();
    test_is_const<void (Class::*)(...) noexcept>();
    test_is_const<void (Class::*)(...)& noexcept>();
    test_is_const<void (Class::*)(...)&& noexcept>();
    test_is_const<void (Class::*)(...) const noexcept>();
    test_is_const<void (Class::*)(...) const& noexcept>();
    test_is_const<void (Class::*)(...) const&& noexcept>();

    test_is_const<void (Class::*)(int, ...)>();
    test_is_const<void (Class::*)(int, ...)&>();
    test_is_const<void (Class::*)(int, ...) &&>();
    test_is_const<void (Class::*)(int, ...) const>();
    test_is_const<void (Class::*)(int, ...) const&>();
    test_is_const<void (Class::*)(int, ...) const&&>();
    test_is_const<void (Class::*)(int, ...) noexcept>();
    test_is_const<void (Class::*)(int, ...)& noexcept>();
    test_is_const<void (Class::*)(int, ...)&& noexcept>();
    test_is_const<void (Class::*)(int, ...) const noexcept>();
    test_is_const<void (Class::*)(int, ...) const& noexcept>();
    test_is_const<void (Class::*)(int, ...) const&& noexcept>();

    test_is_const<int (Class::*)()>();
    test_is_const<int (Class::*)()&>();
    test_is_const<int (Class::*)() &&>();
    test_is_const<int (Class::*)() const>();
    test_is_const<int (Class::*)() const&>();
    test_is_const<int (Class::*)() const&&>();
    test_is_const<int (Class::*)() noexcept>();
    test_is_const<int (Class::*)()& noexcept>();
    test_is_const<int (Class::*)()&& noexcept>();
    test_is_const<int (Class::*)() const noexcept>();
    test_is_const<int (Class::*)() const& noexcept>();
    test_is_const<int (Class::*)() const&& noexcept>();

    test_is_const<int (Class::*)(int)>();
    test_is_const<int (Class::*)(int)&>();
    test_is_const<int (Class::*)(int) &&>();
    test_is_const<int (Class::*)(int) const>();
    test_is_const<int (Class::*)(int) const&>();
    test_is_const<int (Class::*)(int) const&&>();
    test_is_const<int (Class::*)(int) noexcept>();
    test_is_const<int (Class::*)(int)& noexcept>();
    test_is_const<int (Class::*)(int)&& noexcept>();
    test_is_const<int (Class::*)(int) const noexcept>();
    test_is_const<int (Class::*)(int) const& noexcept>();
    test_is_const<int (Class::*)(int) const&& noexcept>();

    test_is_const<int (Class::*)(...)>();
    test_is_const<int (Class::*)(...)&>();
    test_is_const<int (Class::*)(...) &&>();
    test_is_const<int (Class::*)(...) const>();
    test_is_const<int (Class::*)(...) const&>();
    test_is_const<int (Class::*)(...) const&&>();
    test_is_const<int (Class::*)(...) noexcept>();
    test_is_const<int (Class::*)(...)& noexcept>();
    test_is_const<int (Class::*)(...)&& noexcept>();
    test_is_const<int (Class::*)(...) const noexcept>();
    test_is_const<int (Class::*)(...) const& noexcept>();
    test_is_const<int (Class::*)(...) const&& noexcept>();

    test_is_const<int (Class::*)(int, ...)>();
    test_is_const<int (Class::*)(int, ...)&>();
    test_is_const<int (Class::*)(int, ...) &&>();
    test_is_const<int (Class::*)(int, ...) const>();
    test_is_const<int (Class::*)(int, ...) const&>();
    test_is_const<int (Class::*)(int, ...) const&&>();
    test_is_const<int (Class::*)(int, ...) noexcept>();
    test_is_const<int (Class::*)(int, ...)& noexcept>();
    test_is_const<int (Class::*)(int, ...)&& noexcept>();
    test_is_const<int (Class::*)(int, ...) const noexcept>();
    test_is_const<int (Class::*)(int, ...) const& noexcept>();
    test_is_const<int (Class::*)(int, ...) const&& noexcept>();
}
