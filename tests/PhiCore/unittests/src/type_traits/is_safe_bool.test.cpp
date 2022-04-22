#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_safe_bool.hpp>
#include <vector>

template <typename T>
void test_is_safe_bool_impl()
{
    STATIC_REQUIRE(phi::is_safe_bool<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_bool<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_safe_bool_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_bool_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_safe_bool<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_safe_bool<T>);
}

template <typename T>
void test_is_not_safe_bool_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_safe_bool<T>::value);
    STATIC_REQUIRE(phi::is_not_safe_bool<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_bool_v<T>);
    STATIC_REQUIRE(phi::is_not_safe_bool_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_safe_bool<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_safe_bool<T>);
}

template <typename T>
void test_is_safe_bool()
{
    test_is_safe_bool_impl<T>();
    test_is_safe_bool_impl<const T>();
    test_is_safe_bool_impl<volatile T>();
    test_is_safe_bool_impl<const volatile T>();
}

template <typename T>
void test_is_not_safe_bool()
{
    test_is_not_safe_bool_impl<T>();
    test_is_not_safe_bool_impl<const T>();
    test_is_not_safe_bool_impl<volatile T>();
    test_is_not_safe_bool_impl<const volatile T>();
}

TEST_CASE("is_safe_bool")
{
    test_is_not_safe_bool<void>();
    test_is_not_safe_bool<phi::nullptr_t>();
    test_is_not_safe_bool<bool>();
    test_is_not_safe_bool<char>();
    test_is_not_safe_bool<signed char>();
    test_is_not_safe_bool<unsigned char>();
    test_is_not_safe_bool<short>();
    test_is_not_safe_bool<unsigned short>();
    test_is_not_safe_bool<int>();
    test_is_not_safe_bool<unsigned int>();
    test_is_not_safe_bool<long>();
    test_is_not_safe_bool<unsigned long>();
    test_is_not_safe_bool<long long>();
    test_is_not_safe_bool<unsigned long long>();
    test_is_not_safe_bool<float>();
    test_is_not_safe_bool<double>();
    test_is_not_safe_bool<long double>();
    test_is_not_safe_bool<char8_t>();
    test_is_not_safe_bool<char16_t>();
    test_is_not_safe_bool<char32_t>();
    test_is_not_safe_bool<wchar_t>();

    test_is_safe_bool<phi::boolean>();
    test_is_not_safe_bool<phi::integer<signed char>>();
    test_is_not_safe_bool<phi::integer<unsigned char>>();
    test_is_not_safe_bool<phi::integer<short>>();
    test_is_not_safe_bool<phi::integer<unsigned short>>();
    test_is_not_safe_bool<phi::integer<int>>();
    test_is_not_safe_bool<phi::integer<unsigned int>>();
    test_is_not_safe_bool<phi::integer<long>>();
    test_is_not_safe_bool<phi::integer<unsigned long>>();
    test_is_not_safe_bool<phi::integer<long long>>();
    test_is_not_safe_bool<phi::integer<unsigned long long>>();
    test_is_not_safe_bool<phi::floating_point<float>>();
    test_is_not_safe_bool<phi::floating_point<double>>();
    test_is_not_safe_bool<phi::floating_point<long double>>();

    test_is_not_safe_bool<std::vector<int>>();
    test_is_not_safe_bool<phi::scope_ptr<int>>();

    test_is_not_safe_bool<int&>();
    test_is_not_safe_bool<const int&>();
    test_is_not_safe_bool<volatile int&>();
    test_is_not_safe_bool<const volatile int&>();
    test_is_not_safe_bool<int&&>();
    test_is_not_safe_bool<const int&&>();
    test_is_not_safe_bool<volatile int&&>();
    test_is_not_safe_bool<const volatile int&&>();
    test_is_not_safe_bool<int*>();
    test_is_not_safe_bool<const int*>();
    test_is_not_safe_bool<volatile int*>();
    test_is_not_safe_bool<const volatile int*>();
    test_is_not_safe_bool<int**>();
    test_is_not_safe_bool<const int**>();
    test_is_not_safe_bool<volatile int**>();
    test_is_not_safe_bool<const volatile int**>();
    test_is_not_safe_bool<int*&>();
    test_is_not_safe_bool<const int*&>();
    test_is_not_safe_bool<volatile int*&>();
    test_is_not_safe_bool<const volatile int*&>();
    test_is_not_safe_bool<int*&&>();
    test_is_not_safe_bool<const int*&&>();
    test_is_not_safe_bool<volatile int*&&>();
    test_is_not_safe_bool<const volatile int*&&>();
    test_is_not_safe_bool<void*>();
    test_is_not_safe_bool<char[3]>();
    test_is_not_safe_bool<char[]>();
    test_is_not_safe_bool<char* [3]>();
    test_is_not_safe_bool<char*[]>();
    test_is_not_safe_bool<int(*)[3]>();
    test_is_not_safe_bool<int(*)[]>();
    test_is_not_safe_bool<int(&)[3]>();
    test_is_not_safe_bool<int(&)[]>();
    test_is_not_safe_bool<int(&&)[3]>();
    test_is_not_safe_bool<int(&&)[]>();
    test_is_not_safe_bool<char[3][2]>();
    test_is_not_safe_bool<char[][2]>();
    test_is_not_safe_bool<char* [3][2]>();
    test_is_not_safe_bool<char*[][2]>();
    test_is_not_safe_bool<int(*)[3][2]>();
    test_is_not_safe_bool<int(*)[][2]>();
    test_is_not_safe_bool<int(&)[3][2]>();
    test_is_not_safe_bool<int(&)[][2]>();
    test_is_not_safe_bool<int(&&)[3][2]>();
    test_is_not_safe_bool<int(&&)[][2]>();
    test_is_not_safe_bool<Class>();
    test_is_not_safe_bool<Class[]>();
    test_is_not_safe_bool<Class[2]>();
    test_is_not_safe_bool<Template<void>>();
    test_is_not_safe_bool<Template<int>>();
    test_is_not_safe_bool<Template<Class>>();
    test_is_not_safe_bool<Template<IncompleteType>>();
    test_is_not_safe_bool<VariadicTemplate<>>();
    test_is_not_safe_bool<VariadicTemplate<void>>();
    test_is_not_safe_bool<VariadicTemplate<int>>();
    test_is_not_safe_bool<VariadicTemplate<Class>>();
    test_is_not_safe_bool<VariadicTemplate<IncompleteType>>();
    test_is_not_safe_bool<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_safe_bool<PublicDerivedFromTemplate<Base>>();
    test_is_not_safe_bool<PublicDerivedFromTemplate<Derived>>();
    test_is_not_safe_bool<PublicDerivedFromTemplate<Class>>();
    test_is_not_safe_bool<PrivateDerivedFromTemplate<Base>>();
    test_is_not_safe_bool<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_safe_bool<PrivateDerivedFromTemplate<Class>>();
    test_is_not_safe_bool<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_safe_bool<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_safe_bool<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_safe_bool<Union>();
    test_is_not_safe_bool<NonEmptyUnion>();
    test_is_not_safe_bool<Empty>();
    test_is_not_safe_bool<NotEmpty>();
    test_is_not_safe_bool<BitZero>();
    test_is_not_safe_bool<BitOne>();
    test_is_not_safe_bool<Base>();
    test_is_not_safe_bool<Derived>();
    test_is_not_safe_bool<Abstract>();
    test_is_not_safe_bool<PublicAbstract>();
    test_is_not_safe_bool<PrivateAbstract>();
    test_is_not_safe_bool<ProtectedAbstract>();
    test_is_not_safe_bool<AbstractTemplate<int>>();
    test_is_not_safe_bool<AbstractTemplate<double>>();
    test_is_not_safe_bool<AbstractTemplate<Class>>();
    test_is_not_safe_bool<AbstractTemplate<IncompleteType>>();
    test_is_not_safe_bool<Final>();
    test_is_not_safe_bool<PublicDestructor>();
    test_is_not_safe_bool<ProtectedDestructor>();
    test_is_not_safe_bool<PrivateDestructor>();
    test_is_not_safe_bool<VirtualPublicDestructor>();
    test_is_not_safe_bool<VirtualProtectedDestructor>();
    test_is_not_safe_bool<VirtualPrivateDestructor>();
    test_is_not_safe_bool<PurePublicDestructor>();
    test_is_not_safe_bool<PureProtectedDestructor>();
    test_is_not_safe_bool<PurePrivateDestructor>();
    test_is_not_safe_bool<DeletedPublicDestructor>();
    test_is_not_safe_bool<DeletedProtectedDestructor>();
    test_is_not_safe_bool<DeletedPrivateDestructor>();
    test_is_not_safe_bool<DeletedVirtualPublicDestructor>();
    test_is_not_safe_bool<DeletedVirtualProtectedDestructor>();
    test_is_not_safe_bool<DeletedVirtualPrivateDestructor>();
    test_is_not_safe_bool<Enum>();
    test_is_not_safe_bool<EnumSigned>();
    test_is_not_safe_bool<EnumUnsigned>();
    test_is_not_safe_bool<EnumClass>();
    test_is_not_safe_bool<EnumStruct>();
    test_is_not_safe_bool<Function>();
    test_is_not_safe_bool<FunctionPtr>();
    test_is_not_safe_bool<MemberObjectPtr>();
    test_is_not_safe_bool<MemberFunctionPtr>();
    test_is_not_safe_bool<IncompleteType>();
    test_is_not_safe_bool<IncompleteTemplate<void>>();
    test_is_not_safe_bool<IncompleteTemplate<int>>();
    test_is_not_safe_bool<IncompleteTemplate<Class>>();
    test_is_not_safe_bool<IncompleteTemplate<IncompleteType>>();
    test_is_not_safe_bool<IncompleteVariadicTemplate<>>();
    test_is_not_safe_bool<IncompleteVariadicTemplate<void>>();
    test_is_not_safe_bool<IncompleteVariadicTemplate<int>>();
    test_is_not_safe_bool<IncompleteVariadicTemplate<Class>>();
    test_is_not_safe_bool<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_safe_bool<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_safe_bool<int Class::*>();
    test_is_not_safe_bool<float Class::*>();
    test_is_not_safe_bool<void * Class::*>();
    test_is_not_safe_bool<int * Class::*>();
    test_is_not_safe_bool<int Class::*&>();
    test_is_not_safe_bool<float Class::*&>();
    test_is_not_safe_bool<void * Class::*&>();
    test_is_not_safe_bool<int * Class::*&>();
    test_is_not_safe_bool<int Class::*&&>();
    test_is_not_safe_bool<float Class::*&&>();
    test_is_not_safe_bool<void * Class::*&&>();
    test_is_not_safe_bool<int * Class::*&&>();
    test_is_not_safe_bool<int Class::*const>();
    test_is_not_safe_bool<float Class::*const>();
    test_is_not_safe_bool<void * Class::*const>();
    test_is_not_safe_bool<int Class::*const&>();
    test_is_not_safe_bool<float Class::*const&>();
    test_is_not_safe_bool<void * Class::*const&>();
    test_is_not_safe_bool<int Class::*const&&>();
    test_is_not_safe_bool<float Class::*const&&>();
    test_is_not_safe_bool<void * Class::*const&&>();
    test_is_not_safe_bool<int Class::*volatile>();
    test_is_not_safe_bool<float Class::*volatile>();
    test_is_not_safe_bool<void * Class::*volatile>();
    test_is_not_safe_bool<int Class::*volatile&>();
    test_is_not_safe_bool<float Class::*volatile&>();
    test_is_not_safe_bool<void * Class::*volatile&>();
    test_is_not_safe_bool<int Class::*volatile&&>();
    test_is_not_safe_bool<float Class::*volatile&&>();
    test_is_not_safe_bool<void * Class::*volatile&&>();
    test_is_not_safe_bool<int Class::*const volatile>();
    test_is_not_safe_bool<float Class::*const volatile>();
    test_is_not_safe_bool<void * Class::*const volatile>();
    test_is_not_safe_bool<int Class::*const volatile&>();
    test_is_not_safe_bool<float Class::*const volatile&>();
    test_is_not_safe_bool<void * Class::*const volatile&>();
    test_is_not_safe_bool<int Class::*const volatile&&>();
    test_is_not_safe_bool<float Class::*const volatile&&>();
    test_is_not_safe_bool<void * Class::*const volatile&&>();
    test_is_not_safe_bool<NonCopyable>();
    test_is_not_safe_bool<NonMoveable>();
    test_is_not_safe_bool<NonConstructible>();
    test_is_not_safe_bool<Tracked>();
    test_is_not_safe_bool<TrapConstructible>();
    test_is_not_safe_bool<TrapImplicitConversion>();
    test_is_not_safe_bool<TrapComma>();
    test_is_not_safe_bool<TrapCall>();
    test_is_not_safe_bool<TrapSelfAssign>();
    test_is_not_safe_bool<TrapDeref>();
    test_is_not_safe_bool<TrapArraySubscript>();

    test_is_not_safe_bool<void()>();
    test_is_not_safe_bool<void()&>();
    test_is_not_safe_bool<void() &&>();
    test_is_not_safe_bool<void() const>();
    test_is_not_safe_bool<void() const&>();
    test_is_not_safe_bool<void() const&&>();
    test_is_not_safe_bool<void() volatile>();
    test_is_not_safe_bool<void() volatile&>();
    test_is_not_safe_bool<void() volatile&&>();
    test_is_not_safe_bool<void() const volatile>();
    test_is_not_safe_bool<void() const volatile&>();
    test_is_not_safe_bool<void() const volatile&&>();
    test_is_not_safe_bool<void() noexcept>();
    test_is_not_safe_bool<void()& noexcept>();
    test_is_not_safe_bool<void()&& noexcept>();
    test_is_not_safe_bool<void() const noexcept>();
    test_is_not_safe_bool<void() const& noexcept>();
    test_is_not_safe_bool<void() const&& noexcept>();
    test_is_not_safe_bool<void() volatile noexcept>();
    test_is_not_safe_bool<void() volatile& noexcept>();
    test_is_not_safe_bool<void() volatile&& noexcept>();
    test_is_not_safe_bool<void() const volatile noexcept>();
    test_is_not_safe_bool<void() const volatile& noexcept>();
    test_is_not_safe_bool<void() const volatile&& noexcept>();

    test_is_not_safe_bool<void(int)>();
    test_is_not_safe_bool<void(int)&>();
    test_is_not_safe_bool<void(int) &&>();
    test_is_not_safe_bool<void(int) const>();
    test_is_not_safe_bool<void(int) const&>();
    test_is_not_safe_bool<void(int) const&&>();
    test_is_not_safe_bool<void(int) volatile>();
    test_is_not_safe_bool<void(int) volatile&>();
    test_is_not_safe_bool<void(int) volatile&&>();
    test_is_not_safe_bool<void(int) const volatile>();
    test_is_not_safe_bool<void(int) const volatile&>();
    test_is_not_safe_bool<void(int) const volatile&&>();
    test_is_not_safe_bool<void(int) noexcept>();
    test_is_not_safe_bool<void(int)& noexcept>();
    test_is_not_safe_bool<void(int)&& noexcept>();
    test_is_not_safe_bool<void(int) const noexcept>();
    test_is_not_safe_bool<void(int) const& noexcept>();
    test_is_not_safe_bool<void(int) const&& noexcept>();
    test_is_not_safe_bool<void(int) volatile noexcept>();
    test_is_not_safe_bool<void(int) volatile& noexcept>();
    test_is_not_safe_bool<void(int) volatile&& noexcept>();
    test_is_not_safe_bool<void(int) const volatile noexcept>();
    test_is_not_safe_bool<void(int) const volatile& noexcept>();
    test_is_not_safe_bool<void(int) const volatile&& noexcept>();

    test_is_not_safe_bool<void(...)>();
    test_is_not_safe_bool<void(...)&>();
    test_is_not_safe_bool<void(...) &&>();
    test_is_not_safe_bool<void(...) const>();
    test_is_not_safe_bool<void(...) const&>();
    test_is_not_safe_bool<void(...) const&&>();
    test_is_not_safe_bool<void(...) volatile>();
    test_is_not_safe_bool<void(...) volatile&>();
    test_is_not_safe_bool<void(...) volatile&&>();
    test_is_not_safe_bool<void(...) const volatile>();
    test_is_not_safe_bool<void(...) const volatile&>();
    test_is_not_safe_bool<void(...) const volatile&&>();
    test_is_not_safe_bool<void(...) noexcept>();
    test_is_not_safe_bool<void(...)& noexcept>();
    test_is_not_safe_bool<void(...)&& noexcept>();
    test_is_not_safe_bool<void(...) const noexcept>();
    test_is_not_safe_bool<void(...) const& noexcept>();
    test_is_not_safe_bool<void(...) const&& noexcept>();
    test_is_not_safe_bool<void(...) volatile noexcept>();
    test_is_not_safe_bool<void(...) volatile& noexcept>();
    test_is_not_safe_bool<void(...) volatile&& noexcept>();
    test_is_not_safe_bool<void(...) const volatile noexcept>();
    test_is_not_safe_bool<void(...) const volatile& noexcept>();
    test_is_not_safe_bool<void(...) const volatile&& noexcept>();

    test_is_not_safe_bool<void(int, ...)>();
    test_is_not_safe_bool<void(int, ...)&>();
    test_is_not_safe_bool<void(int, ...) &&>();
    test_is_not_safe_bool<void(int, ...) const>();
    test_is_not_safe_bool<void(int, ...) const&>();
    test_is_not_safe_bool<void(int, ...) const&&>();
    test_is_not_safe_bool<void(int, ...) volatile>();
    test_is_not_safe_bool<void(int, ...) volatile&>();
    test_is_not_safe_bool<void(int, ...) volatile&&>();
    test_is_not_safe_bool<void(int, ...) const volatile>();
    test_is_not_safe_bool<void(int, ...) const volatile&>();
    test_is_not_safe_bool<void(int, ...) const volatile&&>();
    test_is_not_safe_bool<void(int, ...) noexcept>();
    test_is_not_safe_bool<void(int, ...)& noexcept>();
    test_is_not_safe_bool<void(int, ...)&& noexcept>();
    test_is_not_safe_bool<void(int, ...) const noexcept>();
    test_is_not_safe_bool<void(int, ...) const& noexcept>();
    test_is_not_safe_bool<void(int, ...) const&& noexcept>();
    test_is_not_safe_bool<void(int, ...) volatile noexcept>();
    test_is_not_safe_bool<void(int, ...) volatile& noexcept>();
    test_is_not_safe_bool<void(int, ...) volatile&& noexcept>();
    test_is_not_safe_bool<void(int, ...) const volatile noexcept>();
    test_is_not_safe_bool<void(int, ...) const volatile& noexcept>();
    test_is_not_safe_bool<void(int, ...) const volatile&& noexcept>();

    test_is_not_safe_bool<int()>();
    test_is_not_safe_bool<int()&>();
    test_is_not_safe_bool<int() &&>();
    test_is_not_safe_bool<int() const>();
    test_is_not_safe_bool<int() const&>();
    test_is_not_safe_bool<int() const&&>();
    test_is_not_safe_bool<int() volatile>();
    test_is_not_safe_bool<int() volatile&>();
    test_is_not_safe_bool<int() volatile&&>();
    test_is_not_safe_bool<int() const volatile>();
    test_is_not_safe_bool<int() const volatile&>();
    test_is_not_safe_bool<int() const volatile&&>();
    test_is_not_safe_bool<int() noexcept>();
    test_is_not_safe_bool<int()& noexcept>();
    test_is_not_safe_bool<int()&& noexcept>();
    test_is_not_safe_bool<int() const noexcept>();
    test_is_not_safe_bool<int() const& noexcept>();
    test_is_not_safe_bool<int() const&& noexcept>();
    test_is_not_safe_bool<int() volatile noexcept>();
    test_is_not_safe_bool<int() volatile& noexcept>();
    test_is_not_safe_bool<int() volatile&& noexcept>();
    test_is_not_safe_bool<int() const volatile noexcept>();
    test_is_not_safe_bool<int() const volatile& noexcept>();
    test_is_not_safe_bool<int() const volatile&& noexcept>();

    test_is_not_safe_bool<int(int)>();
    test_is_not_safe_bool<int(int)&>();
    test_is_not_safe_bool<int(int) &&>();
    test_is_not_safe_bool<int(int) const>();
    test_is_not_safe_bool<int(int) const&>();
    test_is_not_safe_bool<int(int) const&&>();
    test_is_not_safe_bool<int(int) volatile>();
    test_is_not_safe_bool<int(int) volatile&>();
    test_is_not_safe_bool<int(int) volatile&&>();
    test_is_not_safe_bool<int(int) const volatile>();
    test_is_not_safe_bool<int(int) const volatile&>();
    test_is_not_safe_bool<int(int) const volatile&&>();
    test_is_not_safe_bool<int(int) noexcept>();
    test_is_not_safe_bool<int(int)& noexcept>();
    test_is_not_safe_bool<int(int)&& noexcept>();
    test_is_not_safe_bool<int(int) const noexcept>();
    test_is_not_safe_bool<int(int) const& noexcept>();
    test_is_not_safe_bool<int(int) const&& noexcept>();
    test_is_not_safe_bool<int(int) volatile noexcept>();
    test_is_not_safe_bool<int(int) volatile& noexcept>();
    test_is_not_safe_bool<int(int) volatile&& noexcept>();
    test_is_not_safe_bool<int(int) const volatile noexcept>();
    test_is_not_safe_bool<int(int) const volatile& noexcept>();
    test_is_not_safe_bool<int(int) const volatile&& noexcept>();

    test_is_not_safe_bool<int(...)>();
    test_is_not_safe_bool<int(...)&>();
    test_is_not_safe_bool<int(...) &&>();
    test_is_not_safe_bool<int(...) const>();
    test_is_not_safe_bool<int(...) const&>();
    test_is_not_safe_bool<int(...) const&&>();
    test_is_not_safe_bool<int(...) volatile>();
    test_is_not_safe_bool<int(...) volatile&>();
    test_is_not_safe_bool<int(...) volatile&&>();
    test_is_not_safe_bool<int(...) const volatile>();
    test_is_not_safe_bool<int(...) const volatile&>();
    test_is_not_safe_bool<int(...) const volatile&&>();
    test_is_not_safe_bool<int(...) noexcept>();
    test_is_not_safe_bool<int(...)& noexcept>();
    test_is_not_safe_bool<int(...)&& noexcept>();
    test_is_not_safe_bool<int(...) const noexcept>();
    test_is_not_safe_bool<int(...) const& noexcept>();
    test_is_not_safe_bool<int(...) const&& noexcept>();
    test_is_not_safe_bool<int(...) volatile noexcept>();
    test_is_not_safe_bool<int(...) volatile& noexcept>();
    test_is_not_safe_bool<int(...) volatile&& noexcept>();
    test_is_not_safe_bool<int(...) const volatile noexcept>();
    test_is_not_safe_bool<int(...) const volatile& noexcept>();
    test_is_not_safe_bool<int(...) const volatile&& noexcept>();

    test_is_not_safe_bool<int(int, ...)>();
    test_is_not_safe_bool<int(int, ...)&>();
    test_is_not_safe_bool<int(int, ...) &&>();
    test_is_not_safe_bool<int(int, ...) const>();
    test_is_not_safe_bool<int(int, ...) const&>();
    test_is_not_safe_bool<int(int, ...) const&&>();
    test_is_not_safe_bool<int(int, ...) volatile>();
    test_is_not_safe_bool<int(int, ...) volatile&>();
    test_is_not_safe_bool<int(int, ...) volatile&&>();
    test_is_not_safe_bool<int(int, ...) const volatile>();
    test_is_not_safe_bool<int(int, ...) const volatile&>();
    test_is_not_safe_bool<int(int, ...) const volatile&&>();
    test_is_not_safe_bool<int(int, ...) noexcept>();
    test_is_not_safe_bool<int(int, ...)& noexcept>();
    test_is_not_safe_bool<int(int, ...)&& noexcept>();
    test_is_not_safe_bool<int(int, ...) const noexcept>();
    test_is_not_safe_bool<int(int, ...) const& noexcept>();
    test_is_not_safe_bool<int(int, ...) const&& noexcept>();
    test_is_not_safe_bool<int(int, ...) volatile noexcept>();
    test_is_not_safe_bool<int(int, ...) volatile& noexcept>();
    test_is_not_safe_bool<int(int, ...) volatile&& noexcept>();
    test_is_not_safe_bool<int(int, ...) const volatile noexcept>();
    test_is_not_safe_bool<int(int, ...) const volatile& noexcept>();
    test_is_not_safe_bool<int(int, ...) const volatile&& noexcept>();

    test_is_not_safe_bool<void (*)()>();
    test_is_not_safe_bool<void (*)() noexcept>();

    test_is_not_safe_bool<void (*)(int)>();
    test_is_not_safe_bool<void (*)(int) noexcept>();

    test_is_not_safe_bool<void (*)(...)>();
    test_is_not_safe_bool<void (*)(...) noexcept>();

    test_is_not_safe_bool<void (*)(int, ...)>();
    test_is_not_safe_bool<void (*)(int, ...) noexcept>();

    test_is_not_safe_bool<int (*)()>();
    test_is_not_safe_bool<int (*)() noexcept>();

    test_is_not_safe_bool<int (*)(int)>();
    test_is_not_safe_bool<int (*)(int) noexcept>();

    test_is_not_safe_bool<int (*)(...)>();
    test_is_not_safe_bool<int (*)(...) noexcept>();

    test_is_not_safe_bool<int (*)(int, ...)>();
    test_is_not_safe_bool<int (*)(int, ...) noexcept>();

    test_is_not_safe_bool<void (&)()>();
    test_is_not_safe_bool<void (&)() noexcept>();

    test_is_not_safe_bool<void (&)(int)>();
    test_is_not_safe_bool<void (&)(int) noexcept>();

    test_is_not_safe_bool<void (&)(...)>();
    test_is_not_safe_bool<void (&)(...) noexcept>();

    test_is_not_safe_bool<void (&)(int, ...)>();
    test_is_not_safe_bool<void (&)(int, ...) noexcept>();

    test_is_not_safe_bool<int (&)()>();
    test_is_not_safe_bool<int (&)() noexcept>();

    test_is_not_safe_bool<int (&)(int)>();
    test_is_not_safe_bool<int (&)(int) noexcept>();

    test_is_not_safe_bool<int (&)(...)>();
    test_is_not_safe_bool<int (&)(...) noexcept>();

    test_is_not_safe_bool<int (&)(int, ...)>();
    test_is_not_safe_bool<int (&)(int, ...) noexcept>();

    test_is_not_safe_bool<void(&&)()>();
    test_is_not_safe_bool<void(&&)() noexcept>();

    test_is_not_safe_bool<void(&&)(int)>();
    test_is_not_safe_bool<void(&&)(int) noexcept>();

    test_is_not_safe_bool<void(&&)(...)>();
    test_is_not_safe_bool<void(&&)(...) noexcept>();

    test_is_not_safe_bool<void(&&)(int, ...)>();
    test_is_not_safe_bool<void(&&)(int, ...) noexcept>();

    test_is_not_safe_bool<int(&&)()>();
    test_is_not_safe_bool<int(&&)() noexcept>();

    test_is_not_safe_bool<int(&&)(int)>();
    test_is_not_safe_bool<int(&&)(int) noexcept>();

    test_is_not_safe_bool<int(&&)(...)>();
    test_is_not_safe_bool<int(&&)(...) noexcept>();

    test_is_not_safe_bool<int(&&)(int, ...)>();
    test_is_not_safe_bool<int(&&)(int, ...) noexcept>();

    test_is_not_safe_bool<void (Class::*)()>();
    test_is_not_safe_bool<void (Class::*)()&>();
    test_is_not_safe_bool<void (Class::*)() &&>();
    test_is_not_safe_bool<void (Class::*)() const>();
    test_is_not_safe_bool<void (Class::*)() const&>();
    test_is_not_safe_bool<void (Class::*)() const&&>();
    test_is_not_safe_bool<void (Class::*)() noexcept>();
    test_is_not_safe_bool<void (Class::*)()& noexcept>();
    test_is_not_safe_bool<void (Class::*)()&& noexcept>();
    test_is_not_safe_bool<void (Class::*)() const noexcept>();
    test_is_not_safe_bool<void (Class::*)() const& noexcept>();
    test_is_not_safe_bool<void (Class::*)() const&& noexcept>();

    test_is_not_safe_bool<void (Class::*)(int)>();
    test_is_not_safe_bool<void (Class::*)(int)&>();
    test_is_not_safe_bool<void (Class::*)(int) &&>();
    test_is_not_safe_bool<void (Class::*)(int) const>();
    test_is_not_safe_bool<void (Class::*)(int) const&>();
    test_is_not_safe_bool<void (Class::*)(int) const&&>();
    test_is_not_safe_bool<void (Class::*)(int) noexcept>();
    test_is_not_safe_bool<void (Class::*)(int)& noexcept>();
    test_is_not_safe_bool<void (Class::*)(int)&& noexcept>();
    test_is_not_safe_bool<void (Class::*)(int) const noexcept>();
    test_is_not_safe_bool<void (Class::*)(int) const& noexcept>();
    test_is_not_safe_bool<void (Class::*)(int) const&& noexcept>();

    test_is_not_safe_bool<void (Class::*)(...)>();
    test_is_not_safe_bool<void (Class::*)(...)&>();
    test_is_not_safe_bool<void (Class::*)(...) &&>();
    test_is_not_safe_bool<void (Class::*)(...) const>();
    test_is_not_safe_bool<void (Class::*)(...) const&>();
    test_is_not_safe_bool<void (Class::*)(...) const&&>();
    test_is_not_safe_bool<void (Class::*)(...) noexcept>();
    test_is_not_safe_bool<void (Class::*)(...)& noexcept>();
    test_is_not_safe_bool<void (Class::*)(...)&& noexcept>();
    test_is_not_safe_bool<void (Class::*)(...) const noexcept>();
    test_is_not_safe_bool<void (Class::*)(...) const& noexcept>();
    test_is_not_safe_bool<void (Class::*)(...) const&& noexcept>();

    test_is_not_safe_bool<void (Class::*)(int, ...)>();
    test_is_not_safe_bool<void (Class::*)(int, ...)&>();
    test_is_not_safe_bool<void (Class::*)(int, ...) &&>();
    test_is_not_safe_bool<void (Class::*)(int, ...) const>();
    test_is_not_safe_bool<void (Class::*)(int, ...) const&>();
    test_is_not_safe_bool<void (Class::*)(int, ...) const&&>();
    test_is_not_safe_bool<void (Class::*)(int, ...) noexcept>();
    test_is_not_safe_bool<void (Class::*)(int, ...)& noexcept>();
    test_is_not_safe_bool<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_safe_bool<void (Class::*)(int, ...) const noexcept>();
    test_is_not_safe_bool<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_safe_bool<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_safe_bool<int (Class::*)()>();
    test_is_not_safe_bool<int (Class::*)()&>();
    test_is_not_safe_bool<int (Class::*)() &&>();
    test_is_not_safe_bool<int (Class::*)() const>();
    test_is_not_safe_bool<int (Class::*)() const&>();
    test_is_not_safe_bool<int (Class::*)() const&&>();
    test_is_not_safe_bool<int (Class::*)() noexcept>();
    test_is_not_safe_bool<int (Class::*)()& noexcept>();
    test_is_not_safe_bool<int (Class::*)()&& noexcept>();
    test_is_not_safe_bool<int (Class::*)() const noexcept>();
    test_is_not_safe_bool<int (Class::*)() const& noexcept>();
    test_is_not_safe_bool<int (Class::*)() const&& noexcept>();

    test_is_not_safe_bool<int (Class::*)(int)>();
    test_is_not_safe_bool<int (Class::*)(int)&>();
    test_is_not_safe_bool<int (Class::*)(int) &&>();
    test_is_not_safe_bool<int (Class::*)(int) const>();
    test_is_not_safe_bool<int (Class::*)(int) const&>();
    test_is_not_safe_bool<int (Class::*)(int) const&&>();
    test_is_not_safe_bool<int (Class::*)(int) noexcept>();
    test_is_not_safe_bool<int (Class::*)(int)& noexcept>();
    test_is_not_safe_bool<int (Class::*)(int)&& noexcept>();
    test_is_not_safe_bool<int (Class::*)(int) const noexcept>();
    test_is_not_safe_bool<int (Class::*)(int) const& noexcept>();
    test_is_not_safe_bool<int (Class::*)(int) const&& noexcept>();

    test_is_not_safe_bool<int (Class::*)(...)>();
    test_is_not_safe_bool<int (Class::*)(...)&>();
    test_is_not_safe_bool<int (Class::*)(...) &&>();
    test_is_not_safe_bool<int (Class::*)(...) const>();
    test_is_not_safe_bool<int (Class::*)(...) const&>();
    test_is_not_safe_bool<int (Class::*)(...) const&&>();
    test_is_not_safe_bool<int (Class::*)(...) noexcept>();
    test_is_not_safe_bool<int (Class::*)(...)& noexcept>();
    test_is_not_safe_bool<int (Class::*)(...)&& noexcept>();
    test_is_not_safe_bool<int (Class::*)(...) const noexcept>();
    test_is_not_safe_bool<int (Class::*)(...) const& noexcept>();
    test_is_not_safe_bool<int (Class::*)(...) const&& noexcept>();

    test_is_not_safe_bool<int (Class::*)(int, ...)>();
    test_is_not_safe_bool<int (Class::*)(int, ...)&>();
    test_is_not_safe_bool<int (Class::*)(int, ...) &&>();
    test_is_not_safe_bool<int (Class::*)(int, ...) const>();
    test_is_not_safe_bool<int (Class::*)(int, ...) const&>();
    test_is_not_safe_bool<int (Class::*)(int, ...) const&&>();
    test_is_not_safe_bool<int (Class::*)(int, ...) noexcept>();
    test_is_not_safe_bool<int (Class::*)(int, ...)& noexcept>();
    test_is_not_safe_bool<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_safe_bool<int (Class::*)(int, ...) const noexcept>();
    test_is_not_safe_bool<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_safe_bool<int (Class::*)(int, ...) const&& noexcept>();
}
