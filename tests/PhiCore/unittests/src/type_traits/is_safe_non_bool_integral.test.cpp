#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_safe_non_bool_integral.hpp>
#include <vector>

template <typename T>
void test_is_safe_non_bool_integral_impl()
{
    STATIC_REQUIRE(phi::is_safe_non_bool_integral<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_non_bool_integral<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_safe_non_bool_integral_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_non_bool_integral_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_safe_non_bool_integral<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_safe_non_bool_integral<T>);
}

template <typename T>
void test_is_not_safe_non_bool_integral_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_safe_non_bool_integral<T>::value);
    STATIC_REQUIRE(phi::is_not_safe_non_bool_integral<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_non_bool_integral_v<T>);
    STATIC_REQUIRE(phi::is_not_safe_non_bool_integral_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_safe_non_bool_integral<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_safe_non_bool_integral<T>);
}

template <typename T>
void test_is_safe_non_bool_integral()
{
    test_is_safe_non_bool_integral_impl<T>();
    test_is_safe_non_bool_integral_impl<const T>();
    test_is_safe_non_bool_integral_impl<volatile T>();
    test_is_safe_non_bool_integral_impl<const volatile T>();
}

template <typename T>
void test_is_not_safe_non_bool_integral()
{
    test_is_not_safe_non_bool_integral_impl<T>();
    test_is_not_safe_non_bool_integral_impl<const T>();
    test_is_not_safe_non_bool_integral_impl<volatile T>();
    test_is_not_safe_non_bool_integral_impl<const volatile T>();
}

TEST_CASE("is_safe_non_bool_integral")
{
    test_is_not_safe_non_bool_integral<void>();
    test_is_not_safe_non_bool_integral<phi::nullptr_t>();
    test_is_not_safe_non_bool_integral<bool>();
    test_is_not_safe_non_bool_integral<char>();
    test_is_not_safe_non_bool_integral<signed char>();
    test_is_not_safe_non_bool_integral<unsigned char>();
    test_is_not_safe_non_bool_integral<short>();
    test_is_not_safe_non_bool_integral<unsigned short>();
    test_is_not_safe_non_bool_integral<int>();
    test_is_not_safe_non_bool_integral<unsigned int>();
    test_is_not_safe_non_bool_integral<long>();
    test_is_not_safe_non_bool_integral<unsigned long>();
    test_is_not_safe_non_bool_integral<long long>();
    test_is_not_safe_non_bool_integral<unsigned long long>();
    test_is_not_safe_non_bool_integral<float>();
    test_is_not_safe_non_bool_integral<double>();
    test_is_not_safe_non_bool_integral<long double>();
    test_is_not_safe_non_bool_integral<char8_t>();
    test_is_not_safe_non_bool_integral<char16_t>();
    test_is_not_safe_non_bool_integral<char32_t>();
    test_is_not_safe_non_bool_integral<wchar_t>();

    test_is_not_safe_non_bool_integral<phi::boolean>();
    test_is_safe_non_bool_integral<phi::integer<signed char>>();
    test_is_safe_non_bool_integral<phi::integer<unsigned char>>();
    test_is_safe_non_bool_integral<phi::integer<short>>();
    test_is_safe_non_bool_integral<phi::integer<unsigned short>>();
    test_is_safe_non_bool_integral<phi::integer<int>>();
    test_is_safe_non_bool_integral<phi::integer<unsigned int>>();
    test_is_safe_non_bool_integral<phi::integer<long>>();
    test_is_safe_non_bool_integral<phi::integer<unsigned long>>();
    test_is_safe_non_bool_integral<phi::integer<long long>>();
    test_is_safe_non_bool_integral<phi::integer<unsigned long long>>();
    test_is_not_safe_non_bool_integral<phi::floating_point<float>>();
    test_is_not_safe_non_bool_integral<phi::floating_point<double>>();
    test_is_not_safe_non_bool_integral<phi::floating_point<long double>>();

    test_is_not_safe_non_bool_integral<std::vector<int>>();
    test_is_not_safe_non_bool_integral<phi::scope_ptr<int>>();

    test_is_not_safe_non_bool_integral<int&>();
    test_is_not_safe_non_bool_integral<const int&>();
    test_is_not_safe_non_bool_integral<volatile int&>();
    test_is_not_safe_non_bool_integral<const volatile int&>();
    test_is_not_safe_non_bool_integral<int&&>();
    test_is_not_safe_non_bool_integral<const int&&>();
    test_is_not_safe_non_bool_integral<volatile int&&>();
    test_is_not_safe_non_bool_integral<const volatile int&&>();
    test_is_not_safe_non_bool_integral<int*>();
    test_is_not_safe_non_bool_integral<const int*>();
    test_is_not_safe_non_bool_integral<volatile int*>();
    test_is_not_safe_non_bool_integral<const volatile int*>();
    test_is_not_safe_non_bool_integral<int**>();
    test_is_not_safe_non_bool_integral<const int**>();
    test_is_not_safe_non_bool_integral<volatile int**>();
    test_is_not_safe_non_bool_integral<const volatile int**>();
    test_is_not_safe_non_bool_integral<int*&>();
    test_is_not_safe_non_bool_integral<const int*&>();
    test_is_not_safe_non_bool_integral<volatile int*&>();
    test_is_not_safe_non_bool_integral<const volatile int*&>();
    test_is_not_safe_non_bool_integral<int*&&>();
    test_is_not_safe_non_bool_integral<const int*&&>();
    test_is_not_safe_non_bool_integral<volatile int*&&>();
    test_is_not_safe_non_bool_integral<const volatile int*&&>();
    test_is_not_safe_non_bool_integral<void*>();
    test_is_not_safe_non_bool_integral<char[3]>();
    test_is_not_safe_non_bool_integral<char[]>();
    test_is_not_safe_non_bool_integral<char* [3]>();
    test_is_not_safe_non_bool_integral<char*[]>();
    test_is_not_safe_non_bool_integral<int(*)[3]>();
    test_is_not_safe_non_bool_integral<int(*)[]>();
    test_is_not_safe_non_bool_integral<int(&)[3]>();
    test_is_not_safe_non_bool_integral<int(&)[]>();
    test_is_not_safe_non_bool_integral<int(&&)[3]>();
    test_is_not_safe_non_bool_integral<int(&&)[]>();
    test_is_not_safe_non_bool_integral<char[3][2]>();
    test_is_not_safe_non_bool_integral<char[][2]>();
    test_is_not_safe_non_bool_integral<char* [3][2]>();
    test_is_not_safe_non_bool_integral<char*[][2]>();
    test_is_not_safe_non_bool_integral<int(*)[3][2]>();
    test_is_not_safe_non_bool_integral<int(*)[][2]>();
    test_is_not_safe_non_bool_integral<int(&)[3][2]>();
    test_is_not_safe_non_bool_integral<int(&)[][2]>();
    test_is_not_safe_non_bool_integral<int(&&)[3][2]>();
    test_is_not_safe_non_bool_integral<int(&&)[][2]>();
    test_is_not_safe_non_bool_integral<Class>();
    test_is_not_safe_non_bool_integral<Class[]>();
    test_is_not_safe_non_bool_integral<Class[2]>();
    test_is_not_safe_non_bool_integral<Template<void>>();
    test_is_not_safe_non_bool_integral<Template<int>>();
    test_is_not_safe_non_bool_integral<Template<Class>>();
    test_is_not_safe_non_bool_integral<Template<IncompleteType>>();
    test_is_not_safe_non_bool_integral<VariadicTemplate<>>();
    test_is_not_safe_non_bool_integral<VariadicTemplate<void>>();
    test_is_not_safe_non_bool_integral<VariadicTemplate<int>>();
    test_is_not_safe_non_bool_integral<VariadicTemplate<Class>>();
    test_is_not_safe_non_bool_integral<VariadicTemplate<IncompleteType>>();
    test_is_not_safe_non_bool_integral<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_safe_non_bool_integral<PublicDerivedFromTemplate<Base>>();
    test_is_not_safe_non_bool_integral<PublicDerivedFromTemplate<Derived>>();
    test_is_not_safe_non_bool_integral<PublicDerivedFromTemplate<Class>>();
    test_is_not_safe_non_bool_integral<PrivateDerivedFromTemplate<Base>>();
    test_is_not_safe_non_bool_integral<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_safe_non_bool_integral<PrivateDerivedFromTemplate<Class>>();
    test_is_not_safe_non_bool_integral<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_safe_non_bool_integral<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_safe_non_bool_integral<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_safe_non_bool_integral<Union>();
    test_is_not_safe_non_bool_integral<NonEmptyUnion>();
    test_is_not_safe_non_bool_integral<Empty>();
    test_is_not_safe_non_bool_integral<NotEmpty>();
    test_is_not_safe_non_bool_integral<BitZero>();
    test_is_not_safe_non_bool_integral<BitOne>();
    test_is_not_safe_non_bool_integral<Base>();
    test_is_not_safe_non_bool_integral<Derived>();
    test_is_not_safe_non_bool_integral<Abstract>();
    test_is_not_safe_non_bool_integral<PublicAbstract>();
    test_is_not_safe_non_bool_integral<PrivateAbstract>();
    test_is_not_safe_non_bool_integral<ProtectedAbstract>();
    test_is_not_safe_non_bool_integral<AbstractTemplate<int>>();
    test_is_not_safe_non_bool_integral<AbstractTemplate<double>>();
    test_is_not_safe_non_bool_integral<AbstractTemplate<Class>>();
    test_is_not_safe_non_bool_integral<AbstractTemplate<IncompleteType>>();
    test_is_not_safe_non_bool_integral<Final>();
    test_is_not_safe_non_bool_integral<PublicDestructor>();
    test_is_not_safe_non_bool_integral<ProtectedDestructor>();
    test_is_not_safe_non_bool_integral<PrivateDestructor>();
    test_is_not_safe_non_bool_integral<VirtualPublicDestructor>();
    test_is_not_safe_non_bool_integral<VirtualProtectedDestructor>();
    test_is_not_safe_non_bool_integral<VirtualPrivateDestructor>();
    test_is_not_safe_non_bool_integral<PurePublicDestructor>();
    test_is_not_safe_non_bool_integral<PureProtectedDestructor>();
    test_is_not_safe_non_bool_integral<PurePrivateDestructor>();
    test_is_not_safe_non_bool_integral<DeletedPublicDestructor>();
    test_is_not_safe_non_bool_integral<DeletedProtectedDestructor>();
    test_is_not_safe_non_bool_integral<DeletedPrivateDestructor>();
    test_is_not_safe_non_bool_integral<DeletedVirtualPublicDestructor>();
    test_is_not_safe_non_bool_integral<DeletedVirtualProtectedDestructor>();
    test_is_not_safe_non_bool_integral<DeletedVirtualPrivateDestructor>();
    test_is_not_safe_non_bool_integral<Final>();
    test_is_not_safe_non_bool_integral<Enum>();
    test_is_not_safe_non_bool_integral<EnumSigned>();
    test_is_not_safe_non_bool_integral<EnumUnsigned>();
    test_is_not_safe_non_bool_integral<EnumClass>();
    test_is_not_safe_non_bool_integral<EnumStruct>();
    test_is_not_safe_non_bool_integral<Function>();
    test_is_not_safe_non_bool_integral<FunctionPtr>();
    test_is_not_safe_non_bool_integral<MemberObjectPtr>();
    test_is_not_safe_non_bool_integral<MemberFunctionPtr>();
    test_is_not_safe_non_bool_integral<IncompleteType>();
    test_is_not_safe_non_bool_integral<IncompleteTemplate<void>>();
    test_is_not_safe_non_bool_integral<IncompleteTemplate<int>>();
    test_is_not_safe_non_bool_integral<IncompleteTemplate<Class>>();
    test_is_not_safe_non_bool_integral<IncompleteTemplate<IncompleteType>>();
    test_is_not_safe_non_bool_integral<IncompleteVariadicTemplate<>>();
    test_is_not_safe_non_bool_integral<IncompleteVariadicTemplate<void>>();
    test_is_not_safe_non_bool_integral<IncompleteVariadicTemplate<int>>();
    test_is_not_safe_non_bool_integral<IncompleteVariadicTemplate<Class>>();
    test_is_not_safe_non_bool_integral<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_safe_non_bool_integral<
            IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_safe_non_bool_integral<int Class::*>();
    test_is_not_safe_non_bool_integral<float Class::*>();
    test_is_not_safe_non_bool_integral<void * Class::*>();
    test_is_not_safe_non_bool_integral<int * Class::*>();
    test_is_not_safe_non_bool_integral<int Class::*&>();
    test_is_not_safe_non_bool_integral<float Class::*&>();
    test_is_not_safe_non_bool_integral<void * Class::*&>();
    test_is_not_safe_non_bool_integral<int * Class::*&>();
    test_is_not_safe_non_bool_integral<int Class::*&&>();
    test_is_not_safe_non_bool_integral<float Class::*&&>();
    test_is_not_safe_non_bool_integral<void * Class::*&&>();
    test_is_not_safe_non_bool_integral<int * Class::*&&>();
    test_is_not_safe_non_bool_integral<int Class::*const>();
    test_is_not_safe_non_bool_integral<float Class::*const>();
    test_is_not_safe_non_bool_integral<void * Class::*const>();
    test_is_not_safe_non_bool_integral<int Class::*const&>();
    test_is_not_safe_non_bool_integral<float Class::*const&>();
    test_is_not_safe_non_bool_integral<void * Class::*const&>();
    test_is_not_safe_non_bool_integral<int Class::*const&&>();
    test_is_not_safe_non_bool_integral<float Class::*const&&>();
    test_is_not_safe_non_bool_integral<void * Class::*const&&>();
    test_is_not_safe_non_bool_integral<int Class::*volatile>();
    test_is_not_safe_non_bool_integral<float Class::*volatile>();
    test_is_not_safe_non_bool_integral<void * Class::*volatile>();
    test_is_not_safe_non_bool_integral<int Class::*volatile&>();
    test_is_not_safe_non_bool_integral<float Class::*volatile&>();
    test_is_not_safe_non_bool_integral<void * Class::*volatile&>();
    test_is_not_safe_non_bool_integral<int Class::*volatile&&>();
    test_is_not_safe_non_bool_integral<float Class::*volatile&&>();
    test_is_not_safe_non_bool_integral<void * Class::*volatile&&>();
    test_is_not_safe_non_bool_integral<int Class::*const volatile>();
    test_is_not_safe_non_bool_integral<float Class::*const volatile>();
    test_is_not_safe_non_bool_integral<void * Class::*const volatile>();
    test_is_not_safe_non_bool_integral<int Class::*const volatile&>();
    test_is_not_safe_non_bool_integral<float Class::*const volatile&>();
    test_is_not_safe_non_bool_integral<void * Class::*const volatile&>();
    test_is_not_safe_non_bool_integral<int Class::*const volatile&&>();
    test_is_not_safe_non_bool_integral<float Class::*const volatile&&>();
    test_is_not_safe_non_bool_integral<void * Class::*const volatile&&>();
    test_is_not_safe_non_bool_integral<NonCopyable>();
    test_is_not_safe_non_bool_integral<NonMoveable>();
    test_is_not_safe_non_bool_integral<NonConstructible>();
    test_is_not_safe_non_bool_integral<Tracked>();
    test_is_not_safe_non_bool_integral<TrapConstructible>();
    test_is_not_safe_non_bool_integral<TrapImplicitConversion>();
    test_is_not_safe_non_bool_integral<TrapComma>();
    test_is_not_safe_non_bool_integral<TrapCall>();
    test_is_not_safe_non_bool_integral<TrapSelfAssign>();
    test_is_not_safe_non_bool_integral<TrapDeref>();
    test_is_not_safe_non_bool_integral<TrapArraySubscript>();

    test_is_not_safe_non_bool_integral<void()>();
    test_is_not_safe_non_bool_integral<void()&>();
    test_is_not_safe_non_bool_integral<void() &&>();
    test_is_not_safe_non_bool_integral<void() const>();
    test_is_not_safe_non_bool_integral<void() const&>();
    test_is_not_safe_non_bool_integral<void() const&&>();
    test_is_not_safe_non_bool_integral<void() volatile>();
    test_is_not_safe_non_bool_integral<void() volatile&>();
    test_is_not_safe_non_bool_integral<void() volatile&&>();
    test_is_not_safe_non_bool_integral<void() const volatile>();
    test_is_not_safe_non_bool_integral<void() const volatile&>();
    test_is_not_safe_non_bool_integral<void() const volatile&&>();
    test_is_not_safe_non_bool_integral<void() noexcept>();
    test_is_not_safe_non_bool_integral<void()& noexcept>();
    test_is_not_safe_non_bool_integral<void()&& noexcept>();
    test_is_not_safe_non_bool_integral<void() const noexcept>();
    test_is_not_safe_non_bool_integral<void() const& noexcept>();
    test_is_not_safe_non_bool_integral<void() const&& noexcept>();
    test_is_not_safe_non_bool_integral<void() volatile noexcept>();
    test_is_not_safe_non_bool_integral<void() volatile& noexcept>();
    test_is_not_safe_non_bool_integral<void() volatile&& noexcept>();
    test_is_not_safe_non_bool_integral<void() const volatile noexcept>();
    test_is_not_safe_non_bool_integral<void() const volatile& noexcept>();
    test_is_not_safe_non_bool_integral<void() const volatile&& noexcept>();

    test_is_not_safe_non_bool_integral<void(int)>();
    test_is_not_safe_non_bool_integral<void(int)&>();
    test_is_not_safe_non_bool_integral<void(int) &&>();
    test_is_not_safe_non_bool_integral<void(int) const>();
    test_is_not_safe_non_bool_integral<void(int) const&>();
    test_is_not_safe_non_bool_integral<void(int) const&&>();
    test_is_not_safe_non_bool_integral<void(int) volatile>();
    test_is_not_safe_non_bool_integral<void(int) volatile&>();
    test_is_not_safe_non_bool_integral<void(int) volatile&&>();
    test_is_not_safe_non_bool_integral<void(int) const volatile>();
    test_is_not_safe_non_bool_integral<void(int) const volatile&>();
    test_is_not_safe_non_bool_integral<void(int) const volatile&&>();
    test_is_not_safe_non_bool_integral<void(int) noexcept>();
    test_is_not_safe_non_bool_integral<void(int)& noexcept>();
    test_is_not_safe_non_bool_integral<void(int)&& noexcept>();
    test_is_not_safe_non_bool_integral<void(int) const noexcept>();
    test_is_not_safe_non_bool_integral<void(int) const& noexcept>();
    test_is_not_safe_non_bool_integral<void(int) const&& noexcept>();
    test_is_not_safe_non_bool_integral<void(int) volatile noexcept>();
    test_is_not_safe_non_bool_integral<void(int) volatile& noexcept>();
    test_is_not_safe_non_bool_integral<void(int) volatile&& noexcept>();
    test_is_not_safe_non_bool_integral<void(int) const volatile noexcept>();
    test_is_not_safe_non_bool_integral<void(int) const volatile& noexcept>();
    test_is_not_safe_non_bool_integral<void(int) const volatile&& noexcept>();

    test_is_not_safe_non_bool_integral<void(...)>();
    test_is_not_safe_non_bool_integral<void(...)&>();
    test_is_not_safe_non_bool_integral<void(...) &&>();
    test_is_not_safe_non_bool_integral<void(...) const>();
    test_is_not_safe_non_bool_integral<void(...) const&>();
    test_is_not_safe_non_bool_integral<void(...) const&&>();
    test_is_not_safe_non_bool_integral<void(...) volatile>();
    test_is_not_safe_non_bool_integral<void(...) volatile&>();
    test_is_not_safe_non_bool_integral<void(...) volatile&&>();
    test_is_not_safe_non_bool_integral<void(...) const volatile>();
    test_is_not_safe_non_bool_integral<void(...) const volatile&>();
    test_is_not_safe_non_bool_integral<void(...) const volatile&&>();
    test_is_not_safe_non_bool_integral<void(...) noexcept>();
    test_is_not_safe_non_bool_integral<void(...)& noexcept>();
    test_is_not_safe_non_bool_integral<void(...)&& noexcept>();
    test_is_not_safe_non_bool_integral<void(...) const noexcept>();
    test_is_not_safe_non_bool_integral<void(...) const& noexcept>();
    test_is_not_safe_non_bool_integral<void(...) const&& noexcept>();
    test_is_not_safe_non_bool_integral<void(...) volatile noexcept>();
    test_is_not_safe_non_bool_integral<void(...) volatile& noexcept>();
    test_is_not_safe_non_bool_integral<void(...) volatile&& noexcept>();
    test_is_not_safe_non_bool_integral<void(...) const volatile noexcept>();
    test_is_not_safe_non_bool_integral<void(...) const volatile& noexcept>();
    test_is_not_safe_non_bool_integral<void(...) const volatile&& noexcept>();

    test_is_not_safe_non_bool_integral<void(int, ...)>();
    test_is_not_safe_non_bool_integral<void(int, ...)&>();
    test_is_not_safe_non_bool_integral<void(int, ...) &&>();
    test_is_not_safe_non_bool_integral<void(int, ...) const>();
    test_is_not_safe_non_bool_integral<void(int, ...) const&>();
    test_is_not_safe_non_bool_integral<void(int, ...) const&&>();
    test_is_not_safe_non_bool_integral<void(int, ...) volatile>();
    test_is_not_safe_non_bool_integral<void(int, ...) volatile&>();
    test_is_not_safe_non_bool_integral<void(int, ...) volatile&&>();
    test_is_not_safe_non_bool_integral<void(int, ...) const volatile>();
    test_is_not_safe_non_bool_integral<void(int, ...) const volatile&>();
    test_is_not_safe_non_bool_integral<void(int, ...) const volatile&&>();
    test_is_not_safe_non_bool_integral<void(int, ...) noexcept>();
    test_is_not_safe_non_bool_integral<void(int, ...)& noexcept>();
    test_is_not_safe_non_bool_integral<void(int, ...)&& noexcept>();
    test_is_not_safe_non_bool_integral<void(int, ...) const noexcept>();
    test_is_not_safe_non_bool_integral<void(int, ...) const& noexcept>();
    test_is_not_safe_non_bool_integral<void(int, ...) const&& noexcept>();
    test_is_not_safe_non_bool_integral<void(int, ...) volatile noexcept>();
    test_is_not_safe_non_bool_integral<void(int, ...) volatile& noexcept>();
    test_is_not_safe_non_bool_integral<void(int, ...) volatile&& noexcept>();
    test_is_not_safe_non_bool_integral<void(int, ...) const volatile noexcept>();
    test_is_not_safe_non_bool_integral<void(int, ...) const volatile& noexcept>();
    test_is_not_safe_non_bool_integral<void(int, ...) const volatile&& noexcept>();

    test_is_not_safe_non_bool_integral<int()>();
    test_is_not_safe_non_bool_integral<int()&>();
    test_is_not_safe_non_bool_integral<int() &&>();
    test_is_not_safe_non_bool_integral<int() const>();
    test_is_not_safe_non_bool_integral<int() const&>();
    test_is_not_safe_non_bool_integral<int() const&&>();
    test_is_not_safe_non_bool_integral<int() volatile>();
    test_is_not_safe_non_bool_integral<int() volatile&>();
    test_is_not_safe_non_bool_integral<int() volatile&&>();
    test_is_not_safe_non_bool_integral<int() const volatile>();
    test_is_not_safe_non_bool_integral<int() const volatile&>();
    test_is_not_safe_non_bool_integral<int() const volatile&&>();
    test_is_not_safe_non_bool_integral<int() noexcept>();
    test_is_not_safe_non_bool_integral<int()& noexcept>();
    test_is_not_safe_non_bool_integral<int()&& noexcept>();
    test_is_not_safe_non_bool_integral<int() const noexcept>();
    test_is_not_safe_non_bool_integral<int() const& noexcept>();
    test_is_not_safe_non_bool_integral<int() const&& noexcept>();
    test_is_not_safe_non_bool_integral<int() volatile noexcept>();
    test_is_not_safe_non_bool_integral<int() volatile& noexcept>();
    test_is_not_safe_non_bool_integral<int() volatile&& noexcept>();
    test_is_not_safe_non_bool_integral<int() const volatile noexcept>();
    test_is_not_safe_non_bool_integral<int() const volatile& noexcept>();
    test_is_not_safe_non_bool_integral<int() const volatile&& noexcept>();

    test_is_not_safe_non_bool_integral<int(int)>();
    test_is_not_safe_non_bool_integral<int(int)&>();
    test_is_not_safe_non_bool_integral<int(int) &&>();
    test_is_not_safe_non_bool_integral<int(int) const>();
    test_is_not_safe_non_bool_integral<int(int) const&>();
    test_is_not_safe_non_bool_integral<int(int) const&&>();
    test_is_not_safe_non_bool_integral<int(int) volatile>();
    test_is_not_safe_non_bool_integral<int(int) volatile&>();
    test_is_not_safe_non_bool_integral<int(int) volatile&&>();
    test_is_not_safe_non_bool_integral<int(int) const volatile>();
    test_is_not_safe_non_bool_integral<int(int) const volatile&>();
    test_is_not_safe_non_bool_integral<int(int) const volatile&&>();
    test_is_not_safe_non_bool_integral<int(int) noexcept>();
    test_is_not_safe_non_bool_integral<int(int)& noexcept>();
    test_is_not_safe_non_bool_integral<int(int)&& noexcept>();
    test_is_not_safe_non_bool_integral<int(int) const noexcept>();
    test_is_not_safe_non_bool_integral<int(int) const& noexcept>();
    test_is_not_safe_non_bool_integral<int(int) const&& noexcept>();
    test_is_not_safe_non_bool_integral<int(int) volatile noexcept>();
    test_is_not_safe_non_bool_integral<int(int) volatile& noexcept>();
    test_is_not_safe_non_bool_integral<int(int) volatile&& noexcept>();
    test_is_not_safe_non_bool_integral<int(int) const volatile noexcept>();
    test_is_not_safe_non_bool_integral<int(int) const volatile& noexcept>();
    test_is_not_safe_non_bool_integral<int(int) const volatile&& noexcept>();

    test_is_not_safe_non_bool_integral<int(...)>();
    test_is_not_safe_non_bool_integral<int(...)&>();
    test_is_not_safe_non_bool_integral<int(...) &&>();
    test_is_not_safe_non_bool_integral<int(...) const>();
    test_is_not_safe_non_bool_integral<int(...) const&>();
    test_is_not_safe_non_bool_integral<int(...) const&&>();
    test_is_not_safe_non_bool_integral<int(...) volatile>();
    test_is_not_safe_non_bool_integral<int(...) volatile&>();
    test_is_not_safe_non_bool_integral<int(...) volatile&&>();
    test_is_not_safe_non_bool_integral<int(...) const volatile>();
    test_is_not_safe_non_bool_integral<int(...) const volatile&>();
    test_is_not_safe_non_bool_integral<int(...) const volatile&&>();
    test_is_not_safe_non_bool_integral<int(...) noexcept>();
    test_is_not_safe_non_bool_integral<int(...)& noexcept>();
    test_is_not_safe_non_bool_integral<int(...)&& noexcept>();
    test_is_not_safe_non_bool_integral<int(...) const noexcept>();
    test_is_not_safe_non_bool_integral<int(...) const& noexcept>();
    test_is_not_safe_non_bool_integral<int(...) const&& noexcept>();
    test_is_not_safe_non_bool_integral<int(...) volatile noexcept>();
    test_is_not_safe_non_bool_integral<int(...) volatile& noexcept>();
    test_is_not_safe_non_bool_integral<int(...) volatile&& noexcept>();
    test_is_not_safe_non_bool_integral<int(...) const volatile noexcept>();
    test_is_not_safe_non_bool_integral<int(...) const volatile& noexcept>();
    test_is_not_safe_non_bool_integral<int(...) const volatile&& noexcept>();

    test_is_not_safe_non_bool_integral<int(int, ...)>();
    test_is_not_safe_non_bool_integral<int(int, ...)&>();
    test_is_not_safe_non_bool_integral<int(int, ...) &&>();
    test_is_not_safe_non_bool_integral<int(int, ...) const>();
    test_is_not_safe_non_bool_integral<int(int, ...) const&>();
    test_is_not_safe_non_bool_integral<int(int, ...) const&&>();
    test_is_not_safe_non_bool_integral<int(int, ...) volatile>();
    test_is_not_safe_non_bool_integral<int(int, ...) volatile&>();
    test_is_not_safe_non_bool_integral<int(int, ...) volatile&&>();
    test_is_not_safe_non_bool_integral<int(int, ...) const volatile>();
    test_is_not_safe_non_bool_integral<int(int, ...) const volatile&>();
    test_is_not_safe_non_bool_integral<int(int, ...) const volatile&&>();
    test_is_not_safe_non_bool_integral<int(int, ...) noexcept>();
    test_is_not_safe_non_bool_integral<int(int, ...)& noexcept>();
    test_is_not_safe_non_bool_integral<int(int, ...)&& noexcept>();
    test_is_not_safe_non_bool_integral<int(int, ...) const noexcept>();
    test_is_not_safe_non_bool_integral<int(int, ...) const& noexcept>();
    test_is_not_safe_non_bool_integral<int(int, ...) const&& noexcept>();
    test_is_not_safe_non_bool_integral<int(int, ...) volatile noexcept>();
    test_is_not_safe_non_bool_integral<int(int, ...) volatile& noexcept>();
    test_is_not_safe_non_bool_integral<int(int, ...) volatile&& noexcept>();
    test_is_not_safe_non_bool_integral<int(int, ...) const volatile noexcept>();
    test_is_not_safe_non_bool_integral<int(int, ...) const volatile& noexcept>();
    test_is_not_safe_non_bool_integral<int(int, ...) const volatile&& noexcept>();

    test_is_not_safe_non_bool_integral<void (*)()>();
    test_is_not_safe_non_bool_integral<void (*)() noexcept>();

    test_is_not_safe_non_bool_integral<void (*)(int)>();
    test_is_not_safe_non_bool_integral<void (*)(int) noexcept>();

    test_is_not_safe_non_bool_integral<void (*)(...)>();
    test_is_not_safe_non_bool_integral<void (*)(...) noexcept>();

    test_is_not_safe_non_bool_integral<void (*)(int, ...)>();
    test_is_not_safe_non_bool_integral<void (*)(int, ...) noexcept>();

    test_is_not_safe_non_bool_integral<int (*)()>();
    test_is_not_safe_non_bool_integral<int (*)() noexcept>();

    test_is_not_safe_non_bool_integral<int (*)(int)>();
    test_is_not_safe_non_bool_integral<int (*)(int) noexcept>();

    test_is_not_safe_non_bool_integral<int (*)(...)>();
    test_is_not_safe_non_bool_integral<int (*)(...) noexcept>();

    test_is_not_safe_non_bool_integral<int (*)(int, ...)>();
    test_is_not_safe_non_bool_integral<int (*)(int, ...) noexcept>();

    test_is_not_safe_non_bool_integral<void (&)()>();
    test_is_not_safe_non_bool_integral<void (&)() noexcept>();

    test_is_not_safe_non_bool_integral<void (&)(int)>();
    test_is_not_safe_non_bool_integral<void (&)(int) noexcept>();

    test_is_not_safe_non_bool_integral<void (&)(...)>();
    test_is_not_safe_non_bool_integral<void (&)(...) noexcept>();

    test_is_not_safe_non_bool_integral<void (&)(int, ...)>();
    test_is_not_safe_non_bool_integral<void (&)(int, ...) noexcept>();

    test_is_not_safe_non_bool_integral<int (&)()>();
    test_is_not_safe_non_bool_integral<int (&)() noexcept>();

    test_is_not_safe_non_bool_integral<int (&)(int)>();
    test_is_not_safe_non_bool_integral<int (&)(int) noexcept>();

    test_is_not_safe_non_bool_integral<int (&)(...)>();
    test_is_not_safe_non_bool_integral<int (&)(...) noexcept>();

    test_is_not_safe_non_bool_integral<int (&)(int, ...)>();
    test_is_not_safe_non_bool_integral<int (&)(int, ...) noexcept>();

    test_is_not_safe_non_bool_integral<void(&&)()>();
    test_is_not_safe_non_bool_integral<void(&&)() noexcept>();

    test_is_not_safe_non_bool_integral<void(&&)(int)>();
    test_is_not_safe_non_bool_integral<void(&&)(int) noexcept>();

    test_is_not_safe_non_bool_integral<void(&&)(...)>();
    test_is_not_safe_non_bool_integral<void(&&)(...) noexcept>();

    test_is_not_safe_non_bool_integral<void(&&)(int, ...)>();
    test_is_not_safe_non_bool_integral<void(&&)(int, ...) noexcept>();

    test_is_not_safe_non_bool_integral<int(&&)()>();
    test_is_not_safe_non_bool_integral<int(&&)() noexcept>();

    test_is_not_safe_non_bool_integral<int(&&)(int)>();
    test_is_not_safe_non_bool_integral<int(&&)(int) noexcept>();

    test_is_not_safe_non_bool_integral<int(&&)(...)>();
    test_is_not_safe_non_bool_integral<int(&&)(...) noexcept>();

    test_is_not_safe_non_bool_integral<int(&&)(int, ...)>();
    test_is_not_safe_non_bool_integral<int(&&)(int, ...) noexcept>();

    test_is_not_safe_non_bool_integral<void (Class::*)()>();
    test_is_not_safe_non_bool_integral<void (Class::*)()&>();
    test_is_not_safe_non_bool_integral<void (Class::*)() &&>();
    test_is_not_safe_non_bool_integral<void (Class::*)() const>();
    test_is_not_safe_non_bool_integral<void (Class::*)() const&>();
    test_is_not_safe_non_bool_integral<void (Class::*)() const&&>();
    test_is_not_safe_non_bool_integral<void (Class::*)() noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)()& noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)()&& noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)() const noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)() const& noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)() const&& noexcept>();

    test_is_not_safe_non_bool_integral<void (Class::*)(int)>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int)&>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int) &&>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int) const>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int) const&>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int) const&&>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int) noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int)& noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int)&& noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int) const noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int) const& noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int) const&& noexcept>();

    test_is_not_safe_non_bool_integral<void (Class::*)(...)>();
    test_is_not_safe_non_bool_integral<void (Class::*)(...)&>();
    test_is_not_safe_non_bool_integral<void (Class::*)(...) &&>();
    test_is_not_safe_non_bool_integral<void (Class::*)(...) const>();
    test_is_not_safe_non_bool_integral<void (Class::*)(...) const&>();
    test_is_not_safe_non_bool_integral<void (Class::*)(...) const&&>();
    test_is_not_safe_non_bool_integral<void (Class::*)(...) noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)(...)& noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)(...)&& noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)(...) const noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)(...) const& noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)(...) const&& noexcept>();

    test_is_not_safe_non_bool_integral<void (Class::*)(int, ...)>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int, ...)&>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int, ...) &&>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int, ...) const>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int, ...) const&>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int, ...) const&&>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int, ...) noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int, ...)& noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int, ...) const noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_safe_non_bool_integral<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_safe_non_bool_integral<int (Class::*)()>();
    test_is_not_safe_non_bool_integral<int (Class::*)()&>();
    test_is_not_safe_non_bool_integral<int (Class::*)() &&>();
    test_is_not_safe_non_bool_integral<int (Class::*)() const>();
    test_is_not_safe_non_bool_integral<int (Class::*)() const&>();
    test_is_not_safe_non_bool_integral<int (Class::*)() const&&>();
    test_is_not_safe_non_bool_integral<int (Class::*)() noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)()& noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)()&& noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)() const noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)() const& noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)() const&& noexcept>();

    test_is_not_safe_non_bool_integral<int (Class::*)(int)>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int)&>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int) &&>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int) const>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int) const&>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int) const&&>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int) noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int)& noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int)&& noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int) const noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int) const& noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int) const&& noexcept>();

    test_is_not_safe_non_bool_integral<int (Class::*)(...)>();
    test_is_not_safe_non_bool_integral<int (Class::*)(...)&>();
    test_is_not_safe_non_bool_integral<int (Class::*)(...) &&>();
    test_is_not_safe_non_bool_integral<int (Class::*)(...) const>();
    test_is_not_safe_non_bool_integral<int (Class::*)(...) const&>();
    test_is_not_safe_non_bool_integral<int (Class::*)(...) const&&>();
    test_is_not_safe_non_bool_integral<int (Class::*)(...) noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)(...)& noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)(...)&& noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)(...) const noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)(...) const& noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)(...) const&& noexcept>();

    test_is_not_safe_non_bool_integral<int (Class::*)(int, ...)>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int, ...)&>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int, ...) &&>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int, ...) const>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int, ...) const&>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int, ...) const&&>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int, ...) noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int, ...)& noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int, ...) const noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_safe_non_bool_integral<int (Class::*)(int, ...) const&& noexcept>();
}
