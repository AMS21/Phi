#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_safe_integer.hpp>
#include <vector>

template <typename T>
void test_is_safe_integer_impl()
{
    STATIC_REQUIRE(phi::is_safe_integer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_integer<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_safe_integer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_integer_v<T>);
#endif
}

template <typename T>
void test_is_not_safe_integer_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_safe_integer<T>::value);
    STATIC_REQUIRE(phi::is_not_safe_integer<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_integer_v<T>);
    STATIC_REQUIRE(phi::is_not_safe_integer_v<T>);
#endif
}

template <typename T>
void test_is_safe_integer()
{
    test_is_safe_integer_impl<T>();
    test_is_safe_integer_impl<const T>();
    test_is_safe_integer_impl<volatile T>();
    test_is_safe_integer_impl<const volatile T>();
}

template <typename T>
void test_is_not_safe_integer()
{
    test_is_not_safe_integer_impl<T>();
    test_is_not_safe_integer_impl<const T>();
    test_is_not_safe_integer_impl<volatile T>();
    test_is_not_safe_integer_impl<const volatile T>();
}

TEST_CASE("is_safe_integer")
{
    test_is_not_safe_integer<void>();
    test_is_not_safe_integer<phi::nullptr_t>();
    test_is_not_safe_integer<bool>();
    test_is_not_safe_integer<char>();
    test_is_not_safe_integer<signed char>();
    test_is_not_safe_integer<unsigned char>();
    test_is_not_safe_integer<short>();
    test_is_not_safe_integer<unsigned short>();
    test_is_not_safe_integer<int>();
    test_is_not_safe_integer<unsigned int>();
    test_is_not_safe_integer<long>();
    test_is_not_safe_integer<unsigned long>();
    test_is_not_safe_integer<long long>();
    test_is_not_safe_integer<unsigned long long>();
    test_is_not_safe_integer<float>();
    test_is_not_safe_integer<double>();
    test_is_not_safe_integer<long double>();
    test_is_not_safe_integer<char8_t>();
    test_is_not_safe_integer<char16_t>();
    test_is_not_safe_integer<char32_t>();
    test_is_not_safe_integer<wchar_t>();

    test_is_not_safe_integer<phi::boolean>();
    test_is_safe_integer<phi::integer<signed char>>();
    test_is_safe_integer<phi::integer<unsigned char>>();
    test_is_safe_integer<phi::integer<short>>();
    test_is_safe_integer<phi::integer<unsigned short>>();
    test_is_safe_integer<phi::integer<int>>();
    test_is_safe_integer<phi::integer<unsigned int>>();
    test_is_safe_integer<phi::integer<long>>();
    test_is_safe_integer<phi::integer<unsigned long>>();
    test_is_safe_integer<phi::integer<long long>>();
    test_is_safe_integer<phi::integer<unsigned long long>>();
    test_is_not_safe_integer<phi::floating_point<float>>();
    test_is_not_safe_integer<phi::floating_point<double>>();
    test_is_not_safe_integer<phi::floating_point<long double>>();

    test_is_not_safe_integer<std::vector<int>>();
    test_is_not_safe_integer<phi::scope_ptr<int>>();

    test_is_not_safe_integer<int&>();
    test_is_not_safe_integer<const int&>();
    test_is_not_safe_integer<volatile int&>();
    test_is_not_safe_integer<const volatile int&>();
    test_is_not_safe_integer<int&&>();
    test_is_not_safe_integer<const int&&>();
    test_is_not_safe_integer<volatile int&&>();
    test_is_not_safe_integer<const volatile int&&>();
    test_is_not_safe_integer<int*>();
    test_is_not_safe_integer<const int*>();
    test_is_not_safe_integer<volatile int*>();
    test_is_not_safe_integer<const volatile int*>();
    test_is_not_safe_integer<int**>();
    test_is_not_safe_integer<const int**>();
    test_is_not_safe_integer<volatile int**>();
    test_is_not_safe_integer<const volatile int**>();
    test_is_not_safe_integer<int*&>();
    test_is_not_safe_integer<const int*&>();
    test_is_not_safe_integer<volatile int*&>();
    test_is_not_safe_integer<const volatile int*&>();
    test_is_not_safe_integer<int*&&>();
    test_is_not_safe_integer<const int*&&>();
    test_is_not_safe_integer<volatile int*&&>();
    test_is_not_safe_integer<const volatile int*&&>();
    test_is_not_safe_integer<void*>();
    test_is_not_safe_integer<char[3]>();
    test_is_not_safe_integer<char[]>();
    test_is_not_safe_integer<char* [3]>();
    test_is_not_safe_integer<char*[]>();
    test_is_not_safe_integer<int(*)[3]>();
    test_is_not_safe_integer<int(*)[]>();
    test_is_not_safe_integer<int(&)[3]>();
    test_is_not_safe_integer<int(&)[]>();
    test_is_not_safe_integer<int(&&)[3]>();
    test_is_not_safe_integer<int(&&)[]>();
    test_is_not_safe_integer<char[3][2]>();
    test_is_not_safe_integer<char[][2]>();
    test_is_not_safe_integer<char* [3][2]>();
    test_is_not_safe_integer<char*[][2]>();
    test_is_not_safe_integer<int(*)[3][2]>();
    test_is_not_safe_integer<int(*)[][2]>();
    test_is_not_safe_integer<int(&)[3][2]>();
    test_is_not_safe_integer<int(&)[][2]>();
    test_is_not_safe_integer<int(&&)[3][2]>();
    test_is_not_safe_integer<int(&&)[][2]>();
    test_is_not_safe_integer<Class>();
    test_is_not_safe_integer<Class[]>();
    test_is_not_safe_integer<Class[2]>();
    test_is_not_safe_integer<Template<void>>();
    test_is_not_safe_integer<Template<int>>();
    test_is_not_safe_integer<Template<Class>>();
    test_is_not_safe_integer<Template<IncompleteType>>();
    test_is_not_safe_integer<VariadicTemplate<>>();
    test_is_not_safe_integer<VariadicTemplate<void>>();
    test_is_not_safe_integer<VariadicTemplate<int>>();
    test_is_not_safe_integer<VariadicTemplate<Class>>();
    test_is_not_safe_integer<VariadicTemplate<IncompleteType>>();
    test_is_not_safe_integer<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_safe_integer<PublicDerivedFromTemplate<Base>>();
    test_is_not_safe_integer<PublicDerivedFromTemplate<Derived>>();
    test_is_not_safe_integer<PublicDerivedFromTemplate<Class>>();
    test_is_not_safe_integer<PrivateDerivedFromTemplate<Base>>();
    test_is_not_safe_integer<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_safe_integer<PrivateDerivedFromTemplate<Class>>();
    test_is_not_safe_integer<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_safe_integer<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_safe_integer<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_safe_integer<Union>();
    test_is_not_safe_integer<NonEmptyUnion>();
    test_is_not_safe_integer<Empty>();
    test_is_not_safe_integer<NotEmpty>();
    test_is_not_safe_integer<BitZero>();
    test_is_not_safe_integer<BitOne>();
    test_is_not_safe_integer<Base>();
    test_is_not_safe_integer<Derived>();
    test_is_not_safe_integer<Abstract>();
    test_is_not_safe_integer<PublicAbstract>();
    test_is_not_safe_integer<PrivateAbstract>();
    test_is_not_safe_integer<ProtectedAbstract>();
    test_is_not_safe_integer<AbstractTemplate<int>>();
    test_is_not_safe_integer<AbstractTemplate<double>>();
    test_is_not_safe_integer<AbstractTemplate<Class>>();
    test_is_not_safe_integer<AbstractTemplate<IncompleteType>>();
    test_is_not_safe_integer<Final>();
    test_is_not_safe_integer<PublicDestructor>();
    test_is_not_safe_integer<ProtectedDestructor>();
    test_is_not_safe_integer<PrivateDestructor>();
    test_is_not_safe_integer<VirtualPublicDestructor>();
    test_is_not_safe_integer<VirtualProtectedDestructor>();
    test_is_not_safe_integer<VirtualPrivateDestructor>();
    test_is_not_safe_integer<PurePublicDestructor>();
    test_is_not_safe_integer<PureProtectedDestructor>();
    test_is_not_safe_integer<PurePrivateDestructor>();
    test_is_not_safe_integer<DeletedPublicDestructor>();
    test_is_not_safe_integer<DeletedProtectedDestructor>();
    test_is_not_safe_integer<DeletedPrivateDestructor>();
    test_is_not_safe_integer<DeletedVirtualPublicDestructor>();
    test_is_not_safe_integer<DeletedVirtualProtectedDestructor>();
    test_is_not_safe_integer<DeletedVirtualPrivateDestructor>();
    test_is_not_safe_integer<Enum>();
    test_is_not_safe_integer<EnumSigned>();
    test_is_not_safe_integer<EnumUnsigned>();
    test_is_not_safe_integer<EnumClass>();
    test_is_not_safe_integer<EnumStruct>();
    test_is_not_safe_integer<Function>();
    test_is_not_safe_integer<FunctionPtr>();
    test_is_not_safe_integer<MemberObjectPtr>();
    test_is_not_safe_integer<MemberFunctionPtr>();
    test_is_not_safe_integer<IncompleteType>();
    test_is_not_safe_integer<IncompleteTemplate<void>>();
    test_is_not_safe_integer<IncompleteTemplate<int>>();
    test_is_not_safe_integer<IncompleteTemplate<Class>>();
    test_is_not_safe_integer<IncompleteTemplate<IncompleteType>>();
    test_is_not_safe_integer<IncompleteVariadicTemplate<>>();
    test_is_not_safe_integer<IncompleteVariadicTemplate<void>>();
    test_is_not_safe_integer<IncompleteVariadicTemplate<int>>();
    test_is_not_safe_integer<IncompleteVariadicTemplate<Class>>();
    test_is_not_safe_integer<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_safe_integer<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_safe_integer<int Class::*>();
    test_is_not_safe_integer<float Class::*>();
    test_is_not_safe_integer<void * Class::*>();
    test_is_not_safe_integer<int * Class::*>();
    test_is_not_safe_integer<int Class::*&>();
    test_is_not_safe_integer<float Class::*&>();
    test_is_not_safe_integer<void * Class::*&>();
    test_is_not_safe_integer<int * Class::*&>();
    test_is_not_safe_integer<int Class::*&&>();
    test_is_not_safe_integer<float Class::*&&>();
    test_is_not_safe_integer<void * Class::*&&>();
    test_is_not_safe_integer<int * Class::*&&>();
    test_is_not_safe_integer<int Class::*const>();
    test_is_not_safe_integer<float Class::*const>();
    test_is_not_safe_integer<void * Class::*const>();
    test_is_not_safe_integer<int Class::*const&>();
    test_is_not_safe_integer<float Class::*const&>();
    test_is_not_safe_integer<void * Class::*const&>();
    test_is_not_safe_integer<int Class::*const&&>();
    test_is_not_safe_integer<float Class::*const&&>();
    test_is_not_safe_integer<void * Class::*const&&>();
    test_is_not_safe_integer<int Class::*volatile>();
    test_is_not_safe_integer<float Class::*volatile>();
    test_is_not_safe_integer<void * Class::*volatile>();
    test_is_not_safe_integer<int Class::*volatile&>();
    test_is_not_safe_integer<float Class::*volatile&>();
    test_is_not_safe_integer<void * Class::*volatile&>();
    test_is_not_safe_integer<int Class::*volatile&&>();
    test_is_not_safe_integer<float Class::*volatile&&>();
    test_is_not_safe_integer<void * Class::*volatile&&>();
    test_is_not_safe_integer<int Class::*const volatile>();
    test_is_not_safe_integer<float Class::*const volatile>();
    test_is_not_safe_integer<void * Class::*const volatile>();
    test_is_not_safe_integer<int Class::*const volatile&>();
    test_is_not_safe_integer<float Class::*const volatile&>();
    test_is_not_safe_integer<void * Class::*const volatile&>();
    test_is_not_safe_integer<int Class::*const volatile&&>();
    test_is_not_safe_integer<float Class::*const volatile&&>();
    test_is_not_safe_integer<void * Class::*const volatile&&>();
    test_is_not_safe_integer<NonCopyable>();
    test_is_not_safe_integer<NonMoveable>();
    test_is_not_safe_integer<NonConstructible>();
    test_is_not_safe_integer<Tracked>();
    test_is_not_safe_integer<TrapConstructible>();
    test_is_not_safe_integer<TrapImplicitConversion>();
    test_is_not_safe_integer<TrapComma>();
    test_is_not_safe_integer<TrapCall>();
    test_is_not_safe_integer<TrapSelfAssign>();
    test_is_not_safe_integer<TrapDeref>();
    test_is_not_safe_integer<TrapArraySubscript>();

    test_is_not_safe_integer<void()>();
    test_is_not_safe_integer<void()&>();
    test_is_not_safe_integer<void() &&>();
    test_is_not_safe_integer<void() const>();
    test_is_not_safe_integer<void() const&>();
    test_is_not_safe_integer<void() const&&>();
    test_is_not_safe_integer<void() volatile>();
    test_is_not_safe_integer<void() volatile&>();
    test_is_not_safe_integer<void() volatile&&>();
    test_is_not_safe_integer<void() const volatile>();
    test_is_not_safe_integer<void() const volatile&>();
    test_is_not_safe_integer<void() const volatile&&>();
    test_is_not_safe_integer<void() noexcept>();
    test_is_not_safe_integer<void()& noexcept>();
    test_is_not_safe_integer<void()&& noexcept>();
    test_is_not_safe_integer<void() const noexcept>();
    test_is_not_safe_integer<void() const& noexcept>();
    test_is_not_safe_integer<void() const&& noexcept>();
    test_is_not_safe_integer<void() volatile noexcept>();
    test_is_not_safe_integer<void() volatile& noexcept>();
    test_is_not_safe_integer<void() volatile&& noexcept>();
    test_is_not_safe_integer<void() const volatile noexcept>();
    test_is_not_safe_integer<void() const volatile& noexcept>();
    test_is_not_safe_integer<void() const volatile&& noexcept>();

    test_is_not_safe_integer<void(int)>();
    test_is_not_safe_integer<void(int)&>();
    test_is_not_safe_integer<void(int) &&>();
    test_is_not_safe_integer<void(int) const>();
    test_is_not_safe_integer<void(int) const&>();
    test_is_not_safe_integer<void(int) const&&>();
    test_is_not_safe_integer<void(int) volatile>();
    test_is_not_safe_integer<void(int) volatile&>();
    test_is_not_safe_integer<void(int) volatile&&>();
    test_is_not_safe_integer<void(int) const volatile>();
    test_is_not_safe_integer<void(int) const volatile&>();
    test_is_not_safe_integer<void(int) const volatile&&>();
    test_is_not_safe_integer<void(int) noexcept>();
    test_is_not_safe_integer<void(int)& noexcept>();
    test_is_not_safe_integer<void(int)&& noexcept>();
    test_is_not_safe_integer<void(int) const noexcept>();
    test_is_not_safe_integer<void(int) const& noexcept>();
    test_is_not_safe_integer<void(int) const&& noexcept>();
    test_is_not_safe_integer<void(int) volatile noexcept>();
    test_is_not_safe_integer<void(int) volatile& noexcept>();
    test_is_not_safe_integer<void(int) volatile&& noexcept>();
    test_is_not_safe_integer<void(int) const volatile noexcept>();
    test_is_not_safe_integer<void(int) const volatile& noexcept>();
    test_is_not_safe_integer<void(int) const volatile&& noexcept>();

    test_is_not_safe_integer<void(...)>();
    test_is_not_safe_integer<void(...)&>();
    test_is_not_safe_integer<void(...) &&>();
    test_is_not_safe_integer<void(...) const>();
    test_is_not_safe_integer<void(...) const&>();
    test_is_not_safe_integer<void(...) const&&>();
    test_is_not_safe_integer<void(...) volatile>();
    test_is_not_safe_integer<void(...) volatile&>();
    test_is_not_safe_integer<void(...) volatile&&>();
    test_is_not_safe_integer<void(...) const volatile>();
    test_is_not_safe_integer<void(...) const volatile&>();
    test_is_not_safe_integer<void(...) const volatile&&>();
    test_is_not_safe_integer<void(...) noexcept>();
    test_is_not_safe_integer<void(...)& noexcept>();
    test_is_not_safe_integer<void(...)&& noexcept>();
    test_is_not_safe_integer<void(...) const noexcept>();
    test_is_not_safe_integer<void(...) const& noexcept>();
    test_is_not_safe_integer<void(...) const&& noexcept>();
    test_is_not_safe_integer<void(...) volatile noexcept>();
    test_is_not_safe_integer<void(...) volatile& noexcept>();
    test_is_not_safe_integer<void(...) volatile&& noexcept>();
    test_is_not_safe_integer<void(...) const volatile noexcept>();
    test_is_not_safe_integer<void(...) const volatile& noexcept>();
    test_is_not_safe_integer<void(...) const volatile&& noexcept>();

    test_is_not_safe_integer<void(int, ...)>();
    test_is_not_safe_integer<void(int, ...)&>();
    test_is_not_safe_integer<void(int, ...) &&>();
    test_is_not_safe_integer<void(int, ...) const>();
    test_is_not_safe_integer<void(int, ...) const&>();
    test_is_not_safe_integer<void(int, ...) const&&>();
    test_is_not_safe_integer<void(int, ...) volatile>();
    test_is_not_safe_integer<void(int, ...) volatile&>();
    test_is_not_safe_integer<void(int, ...) volatile&&>();
    test_is_not_safe_integer<void(int, ...) const volatile>();
    test_is_not_safe_integer<void(int, ...) const volatile&>();
    test_is_not_safe_integer<void(int, ...) const volatile&&>();
    test_is_not_safe_integer<void(int, ...) noexcept>();
    test_is_not_safe_integer<void(int, ...)& noexcept>();
    test_is_not_safe_integer<void(int, ...)&& noexcept>();
    test_is_not_safe_integer<void(int, ...) const noexcept>();
    test_is_not_safe_integer<void(int, ...) const& noexcept>();
    test_is_not_safe_integer<void(int, ...) const&& noexcept>();
    test_is_not_safe_integer<void(int, ...) volatile noexcept>();
    test_is_not_safe_integer<void(int, ...) volatile& noexcept>();
    test_is_not_safe_integer<void(int, ...) volatile&& noexcept>();
    test_is_not_safe_integer<void(int, ...) const volatile noexcept>();
    test_is_not_safe_integer<void(int, ...) const volatile& noexcept>();
    test_is_not_safe_integer<void(int, ...) const volatile&& noexcept>();

    test_is_not_safe_integer<int()>();
    test_is_not_safe_integer<int()&>();
    test_is_not_safe_integer<int() &&>();
    test_is_not_safe_integer<int() const>();
    test_is_not_safe_integer<int() const&>();
    test_is_not_safe_integer<int() const&&>();
    test_is_not_safe_integer<int() volatile>();
    test_is_not_safe_integer<int() volatile&>();
    test_is_not_safe_integer<int() volatile&&>();
    test_is_not_safe_integer<int() const volatile>();
    test_is_not_safe_integer<int() const volatile&>();
    test_is_not_safe_integer<int() const volatile&&>();
    test_is_not_safe_integer<int() noexcept>();
    test_is_not_safe_integer<int()& noexcept>();
    test_is_not_safe_integer<int()&& noexcept>();
    test_is_not_safe_integer<int() const noexcept>();
    test_is_not_safe_integer<int() const& noexcept>();
    test_is_not_safe_integer<int() const&& noexcept>();
    test_is_not_safe_integer<int() volatile noexcept>();
    test_is_not_safe_integer<int() volatile& noexcept>();
    test_is_not_safe_integer<int() volatile&& noexcept>();
    test_is_not_safe_integer<int() const volatile noexcept>();
    test_is_not_safe_integer<int() const volatile& noexcept>();
    test_is_not_safe_integer<int() const volatile&& noexcept>();

    test_is_not_safe_integer<int(int)>();
    test_is_not_safe_integer<int(int)&>();
    test_is_not_safe_integer<int(int) &&>();
    test_is_not_safe_integer<int(int) const>();
    test_is_not_safe_integer<int(int) const&>();
    test_is_not_safe_integer<int(int) const&&>();
    test_is_not_safe_integer<int(int) volatile>();
    test_is_not_safe_integer<int(int) volatile&>();
    test_is_not_safe_integer<int(int) volatile&&>();
    test_is_not_safe_integer<int(int) const volatile>();
    test_is_not_safe_integer<int(int) const volatile&>();
    test_is_not_safe_integer<int(int) const volatile&&>();
    test_is_not_safe_integer<int(int) noexcept>();
    test_is_not_safe_integer<int(int)& noexcept>();
    test_is_not_safe_integer<int(int)&& noexcept>();
    test_is_not_safe_integer<int(int) const noexcept>();
    test_is_not_safe_integer<int(int) const& noexcept>();
    test_is_not_safe_integer<int(int) const&& noexcept>();
    test_is_not_safe_integer<int(int) volatile noexcept>();
    test_is_not_safe_integer<int(int) volatile& noexcept>();
    test_is_not_safe_integer<int(int) volatile&& noexcept>();
    test_is_not_safe_integer<int(int) const volatile noexcept>();
    test_is_not_safe_integer<int(int) const volatile& noexcept>();
    test_is_not_safe_integer<int(int) const volatile&& noexcept>();

    test_is_not_safe_integer<int(...)>();
    test_is_not_safe_integer<int(...)&>();
    test_is_not_safe_integer<int(...) &&>();
    test_is_not_safe_integer<int(...) const>();
    test_is_not_safe_integer<int(...) const&>();
    test_is_not_safe_integer<int(...) const&&>();
    test_is_not_safe_integer<int(...) volatile>();
    test_is_not_safe_integer<int(...) volatile&>();
    test_is_not_safe_integer<int(...) volatile&&>();
    test_is_not_safe_integer<int(...) const volatile>();
    test_is_not_safe_integer<int(...) const volatile&>();
    test_is_not_safe_integer<int(...) const volatile&&>();
    test_is_not_safe_integer<int(...) noexcept>();
    test_is_not_safe_integer<int(...)& noexcept>();
    test_is_not_safe_integer<int(...)&& noexcept>();
    test_is_not_safe_integer<int(...) const noexcept>();
    test_is_not_safe_integer<int(...) const& noexcept>();
    test_is_not_safe_integer<int(...) const&& noexcept>();
    test_is_not_safe_integer<int(...) volatile noexcept>();
    test_is_not_safe_integer<int(...) volatile& noexcept>();
    test_is_not_safe_integer<int(...) volatile&& noexcept>();
    test_is_not_safe_integer<int(...) const volatile noexcept>();
    test_is_not_safe_integer<int(...) const volatile& noexcept>();
    test_is_not_safe_integer<int(...) const volatile&& noexcept>();

    test_is_not_safe_integer<int(int, ...)>();
    test_is_not_safe_integer<int(int, ...)&>();
    test_is_not_safe_integer<int(int, ...) &&>();
    test_is_not_safe_integer<int(int, ...) const>();
    test_is_not_safe_integer<int(int, ...) const&>();
    test_is_not_safe_integer<int(int, ...) const&&>();
    test_is_not_safe_integer<int(int, ...) volatile>();
    test_is_not_safe_integer<int(int, ...) volatile&>();
    test_is_not_safe_integer<int(int, ...) volatile&&>();
    test_is_not_safe_integer<int(int, ...) const volatile>();
    test_is_not_safe_integer<int(int, ...) const volatile&>();
    test_is_not_safe_integer<int(int, ...) const volatile&&>();
    test_is_not_safe_integer<int(int, ...) noexcept>();
    test_is_not_safe_integer<int(int, ...)& noexcept>();
    test_is_not_safe_integer<int(int, ...)&& noexcept>();
    test_is_not_safe_integer<int(int, ...) const noexcept>();
    test_is_not_safe_integer<int(int, ...) const& noexcept>();
    test_is_not_safe_integer<int(int, ...) const&& noexcept>();
    test_is_not_safe_integer<int(int, ...) volatile noexcept>();
    test_is_not_safe_integer<int(int, ...) volatile& noexcept>();
    test_is_not_safe_integer<int(int, ...) volatile&& noexcept>();
    test_is_not_safe_integer<int(int, ...) const volatile noexcept>();
    test_is_not_safe_integer<int(int, ...) const volatile& noexcept>();
    test_is_not_safe_integer<int(int, ...) const volatile&& noexcept>();

    test_is_not_safe_integer<void (*)()>();
    test_is_not_safe_integer<void (*)() noexcept>();

    test_is_not_safe_integer<void (*)(int)>();
    test_is_not_safe_integer<void (*)(int) noexcept>();

    test_is_not_safe_integer<void (*)(...)>();
    test_is_not_safe_integer<void (*)(...) noexcept>();

    test_is_not_safe_integer<void (*)(int, ...)>();
    test_is_not_safe_integer<void (*)(int, ...) noexcept>();

    test_is_not_safe_integer<int (*)()>();
    test_is_not_safe_integer<int (*)() noexcept>();

    test_is_not_safe_integer<int (*)(int)>();
    test_is_not_safe_integer<int (*)(int) noexcept>();

    test_is_not_safe_integer<int (*)(...)>();
    test_is_not_safe_integer<int (*)(...) noexcept>();

    test_is_not_safe_integer<int (*)(int, ...)>();
    test_is_not_safe_integer<int (*)(int, ...) noexcept>();

    test_is_not_safe_integer<void (&)()>();
    test_is_not_safe_integer<void (&)() noexcept>();

    test_is_not_safe_integer<void (&)(int)>();
    test_is_not_safe_integer<void (&)(int) noexcept>();

    test_is_not_safe_integer<void (&)(...)>();
    test_is_not_safe_integer<void (&)(...) noexcept>();

    test_is_not_safe_integer<void (&)(int, ...)>();
    test_is_not_safe_integer<void (&)(int, ...) noexcept>();

    test_is_not_safe_integer<int (&)()>();
    test_is_not_safe_integer<int (&)() noexcept>();

    test_is_not_safe_integer<int (&)(int)>();
    test_is_not_safe_integer<int (&)(int) noexcept>();

    test_is_not_safe_integer<int (&)(...)>();
    test_is_not_safe_integer<int (&)(...) noexcept>();

    test_is_not_safe_integer<int (&)(int, ...)>();
    test_is_not_safe_integer<int (&)(int, ...) noexcept>();

    test_is_not_safe_integer<void(&&)()>();
    test_is_not_safe_integer<void(&&)() noexcept>();

    test_is_not_safe_integer<void(&&)(int)>();
    test_is_not_safe_integer<void(&&)(int) noexcept>();

    test_is_not_safe_integer<void(&&)(...)>();
    test_is_not_safe_integer<void(&&)(...) noexcept>();

    test_is_not_safe_integer<void(&&)(int, ...)>();
    test_is_not_safe_integer<void(&&)(int, ...) noexcept>();

    test_is_not_safe_integer<int(&&)()>();
    test_is_not_safe_integer<int(&&)() noexcept>();

    test_is_not_safe_integer<int(&&)(int)>();
    test_is_not_safe_integer<int(&&)(int) noexcept>();

    test_is_not_safe_integer<int(&&)(...)>();
    test_is_not_safe_integer<int(&&)(...) noexcept>();

    test_is_not_safe_integer<int(&&)(int, ...)>();
    test_is_not_safe_integer<int(&&)(int, ...) noexcept>();

    test_is_not_safe_integer<void (Class::*)()>();
    test_is_not_safe_integer<void (Class::*)()&>();
    test_is_not_safe_integer<void (Class::*)() &&>();
    test_is_not_safe_integer<void (Class::*)() const>();
    test_is_not_safe_integer<void (Class::*)() const&>();
    test_is_not_safe_integer<void (Class::*)() const&&>();
    test_is_not_safe_integer<void (Class::*)() noexcept>();
    test_is_not_safe_integer<void (Class::*)()& noexcept>();
    test_is_not_safe_integer<void (Class::*)()&& noexcept>();
    test_is_not_safe_integer<void (Class::*)() const noexcept>();
    test_is_not_safe_integer<void (Class::*)() const& noexcept>();
    test_is_not_safe_integer<void (Class::*)() const&& noexcept>();

    test_is_not_safe_integer<void (Class::*)(int)>();
    test_is_not_safe_integer<void (Class::*)(int)&>();
    test_is_not_safe_integer<void (Class::*)(int) &&>();
    test_is_not_safe_integer<void (Class::*)(int) const>();
    test_is_not_safe_integer<void (Class::*)(int) const&>();
    test_is_not_safe_integer<void (Class::*)(int) const&&>();
    test_is_not_safe_integer<void (Class::*)(int) noexcept>();
    test_is_not_safe_integer<void (Class::*)(int)& noexcept>();
    test_is_not_safe_integer<void (Class::*)(int)&& noexcept>();
    test_is_not_safe_integer<void (Class::*)(int) const noexcept>();
    test_is_not_safe_integer<void (Class::*)(int) const& noexcept>();
    test_is_not_safe_integer<void (Class::*)(int) const&& noexcept>();

    test_is_not_safe_integer<void (Class::*)(...)>();
    test_is_not_safe_integer<void (Class::*)(...)&>();
    test_is_not_safe_integer<void (Class::*)(...) &&>();
    test_is_not_safe_integer<void (Class::*)(...) const>();
    test_is_not_safe_integer<void (Class::*)(...) const&>();
    test_is_not_safe_integer<void (Class::*)(...) const&&>();
    test_is_not_safe_integer<void (Class::*)(...) noexcept>();
    test_is_not_safe_integer<void (Class::*)(...)& noexcept>();
    test_is_not_safe_integer<void (Class::*)(...)&& noexcept>();
    test_is_not_safe_integer<void (Class::*)(...) const noexcept>();
    test_is_not_safe_integer<void (Class::*)(...) const& noexcept>();
    test_is_not_safe_integer<void (Class::*)(...) const&& noexcept>();

    test_is_not_safe_integer<void (Class::*)(int, ...)>();
    test_is_not_safe_integer<void (Class::*)(int, ...)&>();
    test_is_not_safe_integer<void (Class::*)(int, ...) &&>();
    test_is_not_safe_integer<void (Class::*)(int, ...) const>();
    test_is_not_safe_integer<void (Class::*)(int, ...) const&>();
    test_is_not_safe_integer<void (Class::*)(int, ...) const&&>();
    test_is_not_safe_integer<void (Class::*)(int, ...) noexcept>();
    test_is_not_safe_integer<void (Class::*)(int, ...)& noexcept>();
    test_is_not_safe_integer<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_safe_integer<void (Class::*)(int, ...) const noexcept>();
    test_is_not_safe_integer<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_safe_integer<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_safe_integer<int (Class::*)()>();
    test_is_not_safe_integer<int (Class::*)()&>();
    test_is_not_safe_integer<int (Class::*)() &&>();
    test_is_not_safe_integer<int (Class::*)() const>();
    test_is_not_safe_integer<int (Class::*)() const&>();
    test_is_not_safe_integer<int (Class::*)() const&&>();
    test_is_not_safe_integer<int (Class::*)() noexcept>();
    test_is_not_safe_integer<int (Class::*)()& noexcept>();
    test_is_not_safe_integer<int (Class::*)()&& noexcept>();
    test_is_not_safe_integer<int (Class::*)() const noexcept>();
    test_is_not_safe_integer<int (Class::*)() const& noexcept>();
    test_is_not_safe_integer<int (Class::*)() const&& noexcept>();

    test_is_not_safe_integer<int (Class::*)(int)>();
    test_is_not_safe_integer<int (Class::*)(int)&>();
    test_is_not_safe_integer<int (Class::*)(int) &&>();
    test_is_not_safe_integer<int (Class::*)(int) const>();
    test_is_not_safe_integer<int (Class::*)(int) const&>();
    test_is_not_safe_integer<int (Class::*)(int) const&&>();
    test_is_not_safe_integer<int (Class::*)(int) noexcept>();
    test_is_not_safe_integer<int (Class::*)(int)& noexcept>();
    test_is_not_safe_integer<int (Class::*)(int)&& noexcept>();
    test_is_not_safe_integer<int (Class::*)(int) const noexcept>();
    test_is_not_safe_integer<int (Class::*)(int) const& noexcept>();
    test_is_not_safe_integer<int (Class::*)(int) const&& noexcept>();

    test_is_not_safe_integer<int (Class::*)(...)>();
    test_is_not_safe_integer<int (Class::*)(...)&>();
    test_is_not_safe_integer<int (Class::*)(...) &&>();
    test_is_not_safe_integer<int (Class::*)(...) const>();
    test_is_not_safe_integer<int (Class::*)(...) const&>();
    test_is_not_safe_integer<int (Class::*)(...) const&&>();
    test_is_not_safe_integer<int (Class::*)(...) noexcept>();
    test_is_not_safe_integer<int (Class::*)(...)& noexcept>();
    test_is_not_safe_integer<int (Class::*)(...)&& noexcept>();
    test_is_not_safe_integer<int (Class::*)(...) const noexcept>();
    test_is_not_safe_integer<int (Class::*)(...) const& noexcept>();
    test_is_not_safe_integer<int (Class::*)(...) const&& noexcept>();

    test_is_not_safe_integer<int (Class::*)(int, ...)>();
    test_is_not_safe_integer<int (Class::*)(int, ...)&>();
    test_is_not_safe_integer<int (Class::*)(int, ...) &&>();
    test_is_not_safe_integer<int (Class::*)(int, ...) const>();
    test_is_not_safe_integer<int (Class::*)(int, ...) const&>();
    test_is_not_safe_integer<int (Class::*)(int, ...) const&&>();
    test_is_not_safe_integer<int (Class::*)(int, ...) noexcept>();
    test_is_not_safe_integer<int (Class::*)(int, ...)& noexcept>();
    test_is_not_safe_integer<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_safe_integer<int (Class::*)(int, ...) const noexcept>();
    test_is_not_safe_integer<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_safe_integer<int (Class::*)(int, ...) const&& noexcept>();
}
