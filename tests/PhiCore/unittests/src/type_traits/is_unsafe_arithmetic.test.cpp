#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_unsafe_arithmetic.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_unsafe_arithmetic_impl()
{
    STATIC_REQUIRE(phi::is_unsafe_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_arithmetic<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_arithmetic_v<T>);
#endif

    STATIC_REQUIRE(std::is_arithmetic<T>::value);
}

template <typename T>
void test_is_not_unsafe_arithmetic_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_unsafe_arithmetic<T>::value);
    STATIC_REQUIRE(phi::is_not_unsafe_arithmetic<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_arithmetic_v<T>);
    STATIC_REQUIRE(phi::is_not_unsafe_arithmetic_v<T>);
#endif

    STATIC_REQUIRE_FALSE(std::is_arithmetic<T>::value);
}

template <typename T>
void test_is_unsafe_arithmetic()
{
    test_is_unsafe_arithmetic_impl<T>();
    test_is_unsafe_arithmetic_impl<const T>();
    test_is_unsafe_arithmetic_impl<volatile T>();
    test_is_unsafe_arithmetic_impl<const volatile T>();
}

template <typename T>
void test_is_not_unsafe_arithmetic()
{
    test_is_not_unsafe_arithmetic_impl<T>();
    test_is_not_unsafe_arithmetic_impl<const T>();
    test_is_not_unsafe_arithmetic_impl<volatile T>();
    test_is_not_unsafe_arithmetic_impl<const volatile T>();
}

TEST_CASE("is_unsafe_arithmetic")
{
    test_is_not_unsafe_arithmetic<void>();
    test_is_not_unsafe_arithmetic<phi::nullptr_t>();
    test_is_unsafe_arithmetic<bool>();
    test_is_unsafe_arithmetic<char>();
    test_is_unsafe_arithmetic<signed char>();
    test_is_unsafe_arithmetic<unsigned char>();
    test_is_unsafe_arithmetic<short>();
    test_is_unsafe_arithmetic<unsigned short>();
    test_is_unsafe_arithmetic<int>();
    test_is_unsafe_arithmetic<unsigned int>();
    test_is_unsafe_arithmetic<long>();
    test_is_unsafe_arithmetic<unsigned long>();
    test_is_unsafe_arithmetic<long long>();
    test_is_unsafe_arithmetic<unsigned long long>();
    test_is_unsafe_arithmetic<float>();
    test_is_unsafe_arithmetic<double>();
    test_is_unsafe_arithmetic<long double>();
    test_is_unsafe_arithmetic<char8_t>();
    test_is_unsafe_arithmetic<char16_t>();
    test_is_unsafe_arithmetic<char32_t>();
    test_is_unsafe_arithmetic<wchar_t>();

    test_is_not_unsafe_arithmetic<phi::boolean>();
    test_is_not_unsafe_arithmetic<phi::integer<signed char>>();
    test_is_not_unsafe_arithmetic<phi::integer<unsigned char>>();
    test_is_not_unsafe_arithmetic<phi::integer<short>>();
    test_is_not_unsafe_arithmetic<phi::integer<unsigned short>>();
    test_is_not_unsafe_arithmetic<phi::integer<int>>();
    test_is_not_unsafe_arithmetic<phi::integer<unsigned int>>();
    test_is_not_unsafe_arithmetic<phi::integer<long>>();
    test_is_not_unsafe_arithmetic<phi::integer<unsigned long>>();
    test_is_not_unsafe_arithmetic<phi::integer<long long>>();
    test_is_not_unsafe_arithmetic<phi::integer<unsigned long long>>();
    test_is_not_unsafe_arithmetic<phi::floating_point<float>>();
    test_is_not_unsafe_arithmetic<phi::floating_point<double>>();
    test_is_not_unsafe_arithmetic<phi::floating_point<long double>>();

    test_is_not_unsafe_arithmetic<std::vector<int>>();
    test_is_not_unsafe_arithmetic<phi::scope_ptr<int>>();

    test_is_not_unsafe_arithmetic<int&>();
    test_is_not_unsafe_arithmetic<const int&>();
    test_is_not_unsafe_arithmetic<volatile int&>();
    test_is_not_unsafe_arithmetic<const volatile int&>();
    test_is_not_unsafe_arithmetic<int&&>();
    test_is_not_unsafe_arithmetic<const int&&>();
    test_is_not_unsafe_arithmetic<volatile int&&>();
    test_is_not_unsafe_arithmetic<const volatile int&&>();
    test_is_not_unsafe_arithmetic<int*>();
    test_is_not_unsafe_arithmetic<const int*>();
    test_is_not_unsafe_arithmetic<volatile int*>();
    test_is_not_unsafe_arithmetic<const volatile int*>();
    test_is_not_unsafe_arithmetic<int**>();
    test_is_not_unsafe_arithmetic<const int**>();
    test_is_not_unsafe_arithmetic<volatile int**>();
    test_is_not_unsafe_arithmetic<const volatile int**>();
    test_is_not_unsafe_arithmetic<int*&>();
    test_is_not_unsafe_arithmetic<const int*&>();
    test_is_not_unsafe_arithmetic<volatile int*&>();
    test_is_not_unsafe_arithmetic<const volatile int*&>();
    test_is_not_unsafe_arithmetic<int*&&>();
    test_is_not_unsafe_arithmetic<const int*&&>();
    test_is_not_unsafe_arithmetic<volatile int*&&>();
    test_is_not_unsafe_arithmetic<const volatile int*&&>();
    test_is_not_unsafe_arithmetic<void*>();
    test_is_not_unsafe_arithmetic<char[3]>();
    test_is_not_unsafe_arithmetic<char[]>();
    test_is_not_unsafe_arithmetic<char* [3]>();
    test_is_not_unsafe_arithmetic<char*[]>();
    test_is_not_unsafe_arithmetic<int(*)[3]>();
    test_is_not_unsafe_arithmetic<int(*)[]>();
    test_is_not_unsafe_arithmetic<int(&)[3]>();
    test_is_not_unsafe_arithmetic<int(&)[]>();
    test_is_not_unsafe_arithmetic<int(&&)[3]>();
    test_is_not_unsafe_arithmetic<int(&&)[]>();
    test_is_not_unsafe_arithmetic<char[3][2]>();
    test_is_not_unsafe_arithmetic<char[][2]>();
    test_is_not_unsafe_arithmetic<char* [3][2]>();
    test_is_not_unsafe_arithmetic<char*[][2]>();
    test_is_not_unsafe_arithmetic<int(*)[3][2]>();
    test_is_not_unsafe_arithmetic<int(*)[][2]>();
    test_is_not_unsafe_arithmetic<int(&)[3][2]>();
    test_is_not_unsafe_arithmetic<int(&)[][2]>();
    test_is_not_unsafe_arithmetic<int(&&)[3][2]>();
    test_is_not_unsafe_arithmetic<int(&&)[][2]>();
    test_is_not_unsafe_arithmetic<Class>();
    test_is_not_unsafe_arithmetic<Class[]>();
    test_is_not_unsafe_arithmetic<Class[2]>();
    test_is_not_unsafe_arithmetic<Template<void>>();
    test_is_not_unsafe_arithmetic<Template<int>>();
    test_is_not_unsafe_arithmetic<Template<Class>>();
    test_is_not_unsafe_arithmetic<Template<IncompleteType>>();
    test_is_not_unsafe_arithmetic<VariadicTemplate<>>();
    test_is_not_unsafe_arithmetic<VariadicTemplate<void>>();
    test_is_not_unsafe_arithmetic<VariadicTemplate<int>>();
    test_is_not_unsafe_arithmetic<VariadicTemplate<Class>>();
    test_is_not_unsafe_arithmetic<VariadicTemplate<IncompleteType>>();
    test_is_not_unsafe_arithmetic<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_unsafe_arithmetic<PublicDerivedFromTemplate<Base>>();
    test_is_not_unsafe_arithmetic<PublicDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_arithmetic<PublicDerivedFromTemplate<Class>>();
    test_is_not_unsafe_arithmetic<PrivateDerivedFromTemplate<Base>>();
    test_is_not_unsafe_arithmetic<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_arithmetic<PrivateDerivedFromTemplate<Class>>();
    test_is_not_unsafe_arithmetic<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_unsafe_arithmetic<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_arithmetic<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_unsafe_arithmetic<Union>();
    test_is_not_unsafe_arithmetic<NonEmptyUnion>();
    test_is_not_unsafe_arithmetic<Empty>();
    test_is_not_unsafe_arithmetic<NotEmpty>();
    test_is_not_unsafe_arithmetic<BitZero>();
    test_is_not_unsafe_arithmetic<BitOne>();
    test_is_not_unsafe_arithmetic<Base>();
    test_is_not_unsafe_arithmetic<Derived>();
    test_is_not_unsafe_arithmetic<Abstract>();
    test_is_not_unsafe_arithmetic<PublicAbstract>();
    test_is_not_unsafe_arithmetic<PrivateAbstract>();
    test_is_not_unsafe_arithmetic<ProtectedAbstract>();
    test_is_not_unsafe_arithmetic<AbstractTemplate<int>>();
    test_is_not_unsafe_arithmetic<AbstractTemplate<double>>();
    test_is_not_unsafe_arithmetic<AbstractTemplate<Class>>();
    test_is_not_unsafe_arithmetic<AbstractTemplate<IncompleteType>>();
    test_is_not_unsafe_arithmetic<Final>();
    test_is_not_unsafe_arithmetic<PublicDestructor>();
    test_is_not_unsafe_arithmetic<ProtectedDestructor>();
    test_is_not_unsafe_arithmetic<PrivateDestructor>();
    test_is_not_unsafe_arithmetic<VirtualPublicDestructor>();
    test_is_not_unsafe_arithmetic<VirtualProtectedDestructor>();
    test_is_not_unsafe_arithmetic<VirtualPrivateDestructor>();
    test_is_not_unsafe_arithmetic<PurePublicDestructor>();
    test_is_not_unsafe_arithmetic<PureProtectedDestructor>();
    test_is_not_unsafe_arithmetic<PurePrivateDestructor>();
    test_is_not_unsafe_arithmetic<DeletedPublicDestructor>();
    test_is_not_unsafe_arithmetic<DeletedProtectedDestructor>();
    test_is_not_unsafe_arithmetic<DeletedPrivateDestructor>();
    test_is_not_unsafe_arithmetic<DeletedVirtualPublicDestructor>();
    test_is_not_unsafe_arithmetic<DeletedVirtualProtectedDestructor>();
    test_is_not_unsafe_arithmetic<DeletedVirtualPrivateDestructor>();
    test_is_not_unsafe_arithmetic<Enum>();
    test_is_not_unsafe_arithmetic<EnumSigned>();
    test_is_not_unsafe_arithmetic<EnumUnsigned>();
    test_is_not_unsafe_arithmetic<EnumClass>();
    test_is_not_unsafe_arithmetic<EnumStruct>();
    test_is_not_unsafe_arithmetic<Function>();
    test_is_not_unsafe_arithmetic<FunctionPtr>();
    test_is_not_unsafe_arithmetic<MemberObjectPtr>();
    test_is_not_unsafe_arithmetic<MemberFunctionPtr>();
    test_is_not_unsafe_arithmetic<IncompleteType>();
    test_is_not_unsafe_arithmetic<IncompleteTemplate<void>>();
    test_is_not_unsafe_arithmetic<IncompleteTemplate<int>>();
    test_is_not_unsafe_arithmetic<IncompleteTemplate<Class>>();
    test_is_not_unsafe_arithmetic<IncompleteTemplate<IncompleteType>>();
    test_is_not_unsafe_arithmetic<IncompleteVariadicTemplate<>>();
    test_is_not_unsafe_arithmetic<IncompleteVariadicTemplate<void>>();
    test_is_not_unsafe_arithmetic<IncompleteVariadicTemplate<int>>();
    test_is_not_unsafe_arithmetic<IncompleteVariadicTemplate<Class>>();
    test_is_not_unsafe_arithmetic<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_unsafe_arithmetic<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_unsafe_arithmetic<int Class::*>();
    test_is_not_unsafe_arithmetic<float Class::*>();
    test_is_not_unsafe_arithmetic<void * Class::*>();
    test_is_not_unsafe_arithmetic<int * Class::*>();
    test_is_not_unsafe_arithmetic<int Class::*&>();
    test_is_not_unsafe_arithmetic<float Class::*&>();
    test_is_not_unsafe_arithmetic<void * Class::*&>();
    test_is_not_unsafe_arithmetic<int * Class::*&>();
    test_is_not_unsafe_arithmetic<int Class::*&&>();
    test_is_not_unsafe_arithmetic<float Class::*&&>();
    test_is_not_unsafe_arithmetic<void * Class::*&&>();
    test_is_not_unsafe_arithmetic<int * Class::*&&>();
    test_is_not_unsafe_arithmetic<int Class::*const>();
    test_is_not_unsafe_arithmetic<float Class::*const>();
    test_is_not_unsafe_arithmetic<void * Class::*const>();
    test_is_not_unsafe_arithmetic<int Class::*const&>();
    test_is_not_unsafe_arithmetic<float Class::*const&>();
    test_is_not_unsafe_arithmetic<void * Class::*const&>();
    test_is_not_unsafe_arithmetic<int Class::*const&&>();
    test_is_not_unsafe_arithmetic<float Class::*const&&>();
    test_is_not_unsafe_arithmetic<void * Class::*const&&>();
    test_is_not_unsafe_arithmetic<int Class::*volatile>();
    test_is_not_unsafe_arithmetic<float Class::*volatile>();
    test_is_not_unsafe_arithmetic<void * Class::*volatile>();
    test_is_not_unsafe_arithmetic<int Class::*volatile&>();
    test_is_not_unsafe_arithmetic<float Class::*volatile&>();
    test_is_not_unsafe_arithmetic<void * Class::*volatile&>();
    test_is_not_unsafe_arithmetic<int Class::*volatile&&>();
    test_is_not_unsafe_arithmetic<float Class::*volatile&&>();
    test_is_not_unsafe_arithmetic<void * Class::*volatile&&>();
    test_is_not_unsafe_arithmetic<int Class::*const volatile>();
    test_is_not_unsafe_arithmetic<float Class::*const volatile>();
    test_is_not_unsafe_arithmetic<void * Class::*const volatile>();
    test_is_not_unsafe_arithmetic<int Class::*const volatile&>();
    test_is_not_unsafe_arithmetic<float Class::*const volatile&>();
    test_is_not_unsafe_arithmetic<void * Class::*const volatile&>();
    test_is_not_unsafe_arithmetic<int Class::*const volatile&&>();
    test_is_not_unsafe_arithmetic<float Class::*const volatile&&>();
    test_is_not_unsafe_arithmetic<void * Class::*const volatile&&>();
    test_is_not_unsafe_arithmetic<NonCopyable>();
    test_is_not_unsafe_arithmetic<NonMoveable>();
    test_is_not_unsafe_arithmetic<NonConstructible>();
    test_is_not_unsafe_arithmetic<Tracked>();
    test_is_not_unsafe_arithmetic<TrapConstructible>();
    test_is_not_unsafe_arithmetic<TrapImplicitConversion>();
    test_is_not_unsafe_arithmetic<TrapComma>();
    test_is_not_unsafe_arithmetic<TrapCall>();
    test_is_not_unsafe_arithmetic<TrapSelfAssign>();
    test_is_not_unsafe_arithmetic<TrapDeref>();
    test_is_not_unsafe_arithmetic<TrapArraySubscript>();

    test_is_not_unsafe_arithmetic<void()>();
    test_is_not_unsafe_arithmetic<void()&>();
    test_is_not_unsafe_arithmetic<void() &&>();
    test_is_not_unsafe_arithmetic<void() const>();
    test_is_not_unsafe_arithmetic<void() const&>();
    test_is_not_unsafe_arithmetic<void() const&&>();
    test_is_not_unsafe_arithmetic<void() volatile>();
    test_is_not_unsafe_arithmetic<void() volatile&>();
    test_is_not_unsafe_arithmetic<void() volatile&&>();
    test_is_not_unsafe_arithmetic<void() const volatile>();
    test_is_not_unsafe_arithmetic<void() const volatile&>();
    test_is_not_unsafe_arithmetic<void() const volatile&&>();
    test_is_not_unsafe_arithmetic<void() noexcept>();
    test_is_not_unsafe_arithmetic<void()& noexcept>();
    test_is_not_unsafe_arithmetic<void()&& noexcept>();
    test_is_not_unsafe_arithmetic<void() const noexcept>();
    test_is_not_unsafe_arithmetic<void() const& noexcept>();
    test_is_not_unsafe_arithmetic<void() const&& noexcept>();
    test_is_not_unsafe_arithmetic<void() volatile noexcept>();
    test_is_not_unsafe_arithmetic<void() volatile& noexcept>();
    test_is_not_unsafe_arithmetic<void() volatile&& noexcept>();
    test_is_not_unsafe_arithmetic<void() const volatile noexcept>();
    test_is_not_unsafe_arithmetic<void() const volatile& noexcept>();
    test_is_not_unsafe_arithmetic<void() const volatile&& noexcept>();

    test_is_not_unsafe_arithmetic<void(int)>();
    test_is_not_unsafe_arithmetic<void(int)&>();
    test_is_not_unsafe_arithmetic<void(int) &&>();
    test_is_not_unsafe_arithmetic<void(int) const>();
    test_is_not_unsafe_arithmetic<void(int) const&>();
    test_is_not_unsafe_arithmetic<void(int) const&&>();
    test_is_not_unsafe_arithmetic<void(int) volatile>();
    test_is_not_unsafe_arithmetic<void(int) volatile&>();
    test_is_not_unsafe_arithmetic<void(int) volatile&&>();
    test_is_not_unsafe_arithmetic<void(int) const volatile>();
    test_is_not_unsafe_arithmetic<void(int) const volatile&>();
    test_is_not_unsafe_arithmetic<void(int) const volatile&&>();
    test_is_not_unsafe_arithmetic<void(int) noexcept>();
    test_is_not_unsafe_arithmetic<void(int)& noexcept>();
    test_is_not_unsafe_arithmetic<void(int)&& noexcept>();
    test_is_not_unsafe_arithmetic<void(int) const noexcept>();
    test_is_not_unsafe_arithmetic<void(int) const& noexcept>();
    test_is_not_unsafe_arithmetic<void(int) const&& noexcept>();
    test_is_not_unsafe_arithmetic<void(int) volatile noexcept>();
    test_is_not_unsafe_arithmetic<void(int) volatile& noexcept>();
    test_is_not_unsafe_arithmetic<void(int) volatile&& noexcept>();
    test_is_not_unsafe_arithmetic<void(int) const volatile noexcept>();
    test_is_not_unsafe_arithmetic<void(int) const volatile& noexcept>();
    test_is_not_unsafe_arithmetic<void(int) const volatile&& noexcept>();

    test_is_not_unsafe_arithmetic<void(...)>();
    test_is_not_unsafe_arithmetic<void(...)&>();
    test_is_not_unsafe_arithmetic<void(...) &&>();
    test_is_not_unsafe_arithmetic<void(...) const>();
    test_is_not_unsafe_arithmetic<void(...) const&>();
    test_is_not_unsafe_arithmetic<void(...) const&&>();
    test_is_not_unsafe_arithmetic<void(...) volatile>();
    test_is_not_unsafe_arithmetic<void(...) volatile&>();
    test_is_not_unsafe_arithmetic<void(...) volatile&&>();
    test_is_not_unsafe_arithmetic<void(...) const volatile>();
    test_is_not_unsafe_arithmetic<void(...) const volatile&>();
    test_is_not_unsafe_arithmetic<void(...) const volatile&&>();
    test_is_not_unsafe_arithmetic<void(...) noexcept>();
    test_is_not_unsafe_arithmetic<void(...)& noexcept>();
    test_is_not_unsafe_arithmetic<void(...)&& noexcept>();
    test_is_not_unsafe_arithmetic<void(...) const noexcept>();
    test_is_not_unsafe_arithmetic<void(...) const& noexcept>();
    test_is_not_unsafe_arithmetic<void(...) const&& noexcept>();
    test_is_not_unsafe_arithmetic<void(...) volatile noexcept>();
    test_is_not_unsafe_arithmetic<void(...) volatile& noexcept>();
    test_is_not_unsafe_arithmetic<void(...) volatile&& noexcept>();
    test_is_not_unsafe_arithmetic<void(...) const volatile noexcept>();
    test_is_not_unsafe_arithmetic<void(...) const volatile& noexcept>();
    test_is_not_unsafe_arithmetic<void(...) const volatile&& noexcept>();

    test_is_not_unsafe_arithmetic<void(int, ...)>();
    test_is_not_unsafe_arithmetic<void(int, ...)&>();
    test_is_not_unsafe_arithmetic<void(int, ...) &&>();
    test_is_not_unsafe_arithmetic<void(int, ...) const>();
    test_is_not_unsafe_arithmetic<void(int, ...) const&>();
    test_is_not_unsafe_arithmetic<void(int, ...) const&&>();
    test_is_not_unsafe_arithmetic<void(int, ...) volatile>();
    test_is_not_unsafe_arithmetic<void(int, ...) volatile&>();
    test_is_not_unsafe_arithmetic<void(int, ...) volatile&&>();
    test_is_not_unsafe_arithmetic<void(int, ...) const volatile>();
    test_is_not_unsafe_arithmetic<void(int, ...) const volatile&>();
    test_is_not_unsafe_arithmetic<void(int, ...) const volatile&&>();
    test_is_not_unsafe_arithmetic<void(int, ...) noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...)& noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...)&& noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) const noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) const& noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) const&& noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) volatile noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) volatile& noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) volatile&& noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) const volatile noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) const volatile& noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) const volatile&& noexcept>();

    test_is_not_unsafe_arithmetic<int()>();
    test_is_not_unsafe_arithmetic<int()&>();
    test_is_not_unsafe_arithmetic<int() &&>();
    test_is_not_unsafe_arithmetic<int() const>();
    test_is_not_unsafe_arithmetic<int() const&>();
    test_is_not_unsafe_arithmetic<int() const&&>();
    test_is_not_unsafe_arithmetic<int() volatile>();
    test_is_not_unsafe_arithmetic<int() volatile&>();
    test_is_not_unsafe_arithmetic<int() volatile&&>();
    test_is_not_unsafe_arithmetic<int() const volatile>();
    test_is_not_unsafe_arithmetic<int() const volatile&>();
    test_is_not_unsafe_arithmetic<int() const volatile&&>();
    test_is_not_unsafe_arithmetic<int() noexcept>();
    test_is_not_unsafe_arithmetic<int()& noexcept>();
    test_is_not_unsafe_arithmetic<int()&& noexcept>();
    test_is_not_unsafe_arithmetic<int() const noexcept>();
    test_is_not_unsafe_arithmetic<int() const& noexcept>();
    test_is_not_unsafe_arithmetic<int() const&& noexcept>();
    test_is_not_unsafe_arithmetic<int() volatile noexcept>();
    test_is_not_unsafe_arithmetic<int() volatile& noexcept>();
    test_is_not_unsafe_arithmetic<int() volatile&& noexcept>();
    test_is_not_unsafe_arithmetic<int() const volatile noexcept>();
    test_is_not_unsafe_arithmetic<int() const volatile& noexcept>();
    test_is_not_unsafe_arithmetic<int() const volatile&& noexcept>();

    test_is_not_unsafe_arithmetic<int(int)>();
    test_is_not_unsafe_arithmetic<int(int)&>();
    test_is_not_unsafe_arithmetic<int(int) &&>();
    test_is_not_unsafe_arithmetic<int(int) const>();
    test_is_not_unsafe_arithmetic<int(int) const&>();
    test_is_not_unsafe_arithmetic<int(int) const&&>();
    test_is_not_unsafe_arithmetic<int(int) volatile>();
    test_is_not_unsafe_arithmetic<int(int) volatile&>();
    test_is_not_unsafe_arithmetic<int(int) volatile&&>();
    test_is_not_unsafe_arithmetic<int(int) const volatile>();
    test_is_not_unsafe_arithmetic<int(int) const volatile&>();
    test_is_not_unsafe_arithmetic<int(int) const volatile&&>();
    test_is_not_unsafe_arithmetic<int(int) noexcept>();
    test_is_not_unsafe_arithmetic<int(int)& noexcept>();
    test_is_not_unsafe_arithmetic<int(int)&& noexcept>();
    test_is_not_unsafe_arithmetic<int(int) const noexcept>();
    test_is_not_unsafe_arithmetic<int(int) const& noexcept>();
    test_is_not_unsafe_arithmetic<int(int) const&& noexcept>();
    test_is_not_unsafe_arithmetic<int(int) volatile noexcept>();
    test_is_not_unsafe_arithmetic<int(int) volatile& noexcept>();
    test_is_not_unsafe_arithmetic<int(int) volatile&& noexcept>();
    test_is_not_unsafe_arithmetic<int(int) const volatile noexcept>();
    test_is_not_unsafe_arithmetic<int(int) const volatile& noexcept>();
    test_is_not_unsafe_arithmetic<int(int) const volatile&& noexcept>();

    test_is_not_unsafe_arithmetic<int(...)>();
    test_is_not_unsafe_arithmetic<int(...)&>();
    test_is_not_unsafe_arithmetic<int(...) &&>();
    test_is_not_unsafe_arithmetic<int(...) const>();
    test_is_not_unsafe_arithmetic<int(...) const&>();
    test_is_not_unsafe_arithmetic<int(...) const&&>();
    test_is_not_unsafe_arithmetic<int(...) volatile>();
    test_is_not_unsafe_arithmetic<int(...) volatile&>();
    test_is_not_unsafe_arithmetic<int(...) volatile&&>();
    test_is_not_unsafe_arithmetic<int(...) const volatile>();
    test_is_not_unsafe_arithmetic<int(...) const volatile&>();
    test_is_not_unsafe_arithmetic<int(...) const volatile&&>();
    test_is_not_unsafe_arithmetic<int(...) noexcept>();
    test_is_not_unsafe_arithmetic<int(...)& noexcept>();
    test_is_not_unsafe_arithmetic<int(...)&& noexcept>();
    test_is_not_unsafe_arithmetic<int(...) const noexcept>();
    test_is_not_unsafe_arithmetic<int(...) const& noexcept>();
    test_is_not_unsafe_arithmetic<int(...) const&& noexcept>();
    test_is_not_unsafe_arithmetic<int(...) volatile noexcept>();
    test_is_not_unsafe_arithmetic<int(...) volatile& noexcept>();
    test_is_not_unsafe_arithmetic<int(...) volatile&& noexcept>();
    test_is_not_unsafe_arithmetic<int(...) const volatile noexcept>();
    test_is_not_unsafe_arithmetic<int(...) const volatile& noexcept>();
    test_is_not_unsafe_arithmetic<int(...) const volatile&& noexcept>();

    test_is_not_unsafe_arithmetic<int(int, ...)>();
    test_is_not_unsafe_arithmetic<int(int, ...)&>();
    test_is_not_unsafe_arithmetic<int(int, ...) &&>();
    test_is_not_unsafe_arithmetic<int(int, ...) const>();
    test_is_not_unsafe_arithmetic<int(int, ...) const&>();
    test_is_not_unsafe_arithmetic<int(int, ...) const&&>();
    test_is_not_unsafe_arithmetic<int(int, ...) volatile>();
    test_is_not_unsafe_arithmetic<int(int, ...) volatile&>();
    test_is_not_unsafe_arithmetic<int(int, ...) volatile&&>();
    test_is_not_unsafe_arithmetic<int(int, ...) const volatile>();
    test_is_not_unsafe_arithmetic<int(int, ...) const volatile&>();
    test_is_not_unsafe_arithmetic<int(int, ...) const volatile&&>();
    test_is_not_unsafe_arithmetic<int(int, ...) noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...)& noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...)&& noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) const noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) const& noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) const&& noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) volatile noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) volatile& noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) volatile&& noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) const volatile noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) const volatile& noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) const volatile&& noexcept>();

    test_is_not_unsafe_arithmetic<void (*)()>();
    test_is_not_unsafe_arithmetic<void (*)() noexcept>();

    test_is_not_unsafe_arithmetic<void (*)(int)>();
    test_is_not_unsafe_arithmetic<void (*)(int) noexcept>();

    test_is_not_unsafe_arithmetic<void (*)(...)>();
    test_is_not_unsafe_arithmetic<void (*)(...) noexcept>();

    test_is_not_unsafe_arithmetic<void (*)(int, ...)>();
    test_is_not_unsafe_arithmetic<void (*)(int, ...) noexcept>();

    test_is_not_unsafe_arithmetic<int (*)()>();
    test_is_not_unsafe_arithmetic<int (*)() noexcept>();

    test_is_not_unsafe_arithmetic<int (*)(int)>();
    test_is_not_unsafe_arithmetic<int (*)(int) noexcept>();

    test_is_not_unsafe_arithmetic<int (*)(...)>();
    test_is_not_unsafe_arithmetic<int (*)(...) noexcept>();

    test_is_not_unsafe_arithmetic<int (*)(int, ...)>();
    test_is_not_unsafe_arithmetic<int (*)(int, ...) noexcept>();

    test_is_not_unsafe_arithmetic<void (&)()>();
    test_is_not_unsafe_arithmetic<void (&)() noexcept>();

    test_is_not_unsafe_arithmetic<void (&)(int)>();
    test_is_not_unsafe_arithmetic<void (&)(int) noexcept>();

    test_is_not_unsafe_arithmetic<void (&)(...)>();
    test_is_not_unsafe_arithmetic<void (&)(...) noexcept>();

    test_is_not_unsafe_arithmetic<void (&)(int, ...)>();
    test_is_not_unsafe_arithmetic<void (&)(int, ...) noexcept>();

    test_is_not_unsafe_arithmetic<int (&)()>();
    test_is_not_unsafe_arithmetic<int (&)() noexcept>();

    test_is_not_unsafe_arithmetic<int (&)(int)>();
    test_is_not_unsafe_arithmetic<int (&)(int) noexcept>();

    test_is_not_unsafe_arithmetic<int (&)(...)>();
    test_is_not_unsafe_arithmetic<int (&)(...) noexcept>();

    test_is_not_unsafe_arithmetic<int (&)(int, ...)>();
    test_is_not_unsafe_arithmetic<int (&)(int, ...) noexcept>();

    test_is_not_unsafe_arithmetic<void(&&)()>();
    test_is_not_unsafe_arithmetic<void(&&)() noexcept>();

    test_is_not_unsafe_arithmetic<void(&&)(int)>();
    test_is_not_unsafe_arithmetic<void(&&)(int) noexcept>();

    test_is_not_unsafe_arithmetic<void(&&)(...)>();
    test_is_not_unsafe_arithmetic<void(&&)(...) noexcept>();

    test_is_not_unsafe_arithmetic<void(&&)(int, ...)>();
    test_is_not_unsafe_arithmetic<void(&&)(int, ...) noexcept>();

    test_is_not_unsafe_arithmetic<int(&&)()>();
    test_is_not_unsafe_arithmetic<int(&&)() noexcept>();

    test_is_not_unsafe_arithmetic<int(&&)(int)>();
    test_is_not_unsafe_arithmetic<int(&&)(int) noexcept>();

    test_is_not_unsafe_arithmetic<int(&&)(...)>();
    test_is_not_unsafe_arithmetic<int(&&)(...) noexcept>();

    test_is_not_unsafe_arithmetic<int(&&)(int, ...)>();
    test_is_not_unsafe_arithmetic<int(&&)(int, ...) noexcept>();

    test_is_not_unsafe_arithmetic<void (Class::*)()>();
    test_is_not_unsafe_arithmetic<void (Class::*)()&>();
    test_is_not_unsafe_arithmetic<void (Class::*)() &&>();
    test_is_not_unsafe_arithmetic<void (Class::*)() const>();
    test_is_not_unsafe_arithmetic<void (Class::*)() const&>();
    test_is_not_unsafe_arithmetic<void (Class::*)() const&&>();
    test_is_not_unsafe_arithmetic<void (Class::*)() noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)()& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)()&& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)() const noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)() const& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)() const&& noexcept>();

    test_is_not_unsafe_arithmetic<void (Class::*)(int)>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int)&>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int) &&>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int) const>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int) const&>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int) const&&>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int) noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int)& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int)&& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int) const noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int) const& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int) const&& noexcept>();

    test_is_not_unsafe_arithmetic<void (Class::*)(...)>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...)&>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...) &&>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...) const>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...) const&>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...) const&&>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...) noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...)& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...)&& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...) const noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...) const& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...) const&& noexcept>();

    test_is_not_unsafe_arithmetic<void (Class::*)(int, ...)>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int, ...)&>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int, ...) &&>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int, ...) const>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int, ...) const&>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int, ...) const&&>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int, ...) noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int, ...)& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int, ...) const noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_unsafe_arithmetic<int (Class::*)()>();
    test_is_not_unsafe_arithmetic<int (Class::*)()&>();
    test_is_not_unsafe_arithmetic<int (Class::*)() &&>();
    test_is_not_unsafe_arithmetic<int (Class::*)() const>();
    test_is_not_unsafe_arithmetic<int (Class::*)() const&>();
    test_is_not_unsafe_arithmetic<int (Class::*)() const&&>();
    test_is_not_unsafe_arithmetic<int (Class::*)() noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)()& noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)()&& noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)() const noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)() const& noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)() const&& noexcept>();

    test_is_not_unsafe_arithmetic<int (Class::*)(int)>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int)&>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int) &&>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int) const>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int) const&>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int) const&&>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int) noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int)& noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int)&& noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int) const noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int) const& noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int) const&& noexcept>();

    test_is_not_unsafe_arithmetic<int (Class::*)(...)>();
    test_is_not_unsafe_arithmetic<int (Class::*)(...)&>();
    test_is_not_unsafe_arithmetic<int (Class::*)(...) &&>();
    test_is_not_unsafe_arithmetic<int (Class::*)(...) const>();
    test_is_not_unsafe_arithmetic<int (Class::*)(...) const&>();
    test_is_not_unsafe_arithmetic<int (Class::*)(...) const&&>();
    test_is_not_unsafe_arithmetic<int (Class::*)(...) noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)(...)& noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)(...)&& noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)(...) const noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)(...) const& noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)(...) const&& noexcept>();

    test_is_not_unsafe_arithmetic<int (Class::*)(int, ...)>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int, ...)&>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int, ...) &&>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int, ...) const>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int, ...) const&>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int, ...) const&&>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int, ...) noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int, ...)& noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int, ...) const noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_unsafe_arithmetic<int (Class::*)(int, ...) const&& noexcept>();
}
