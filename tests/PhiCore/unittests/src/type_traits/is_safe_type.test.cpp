#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_safe_type.hpp>
#include <vector>

template <typename T>
void test_is_safe_type_impl()
{
    STATIC_REQUIRE(phi::is_safe_type<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_type<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_safe_type_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_type_v<T>);
#endif
}

template <typename T>
void test_is_not_safe_type_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_safe_type<T>::value);
    STATIC_REQUIRE(phi::is_not_safe_type<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_type_v<T>);
    STATIC_REQUIRE(phi::is_not_safe_type_v<T>);
#endif
}

template <typename T>
void test_is_safe_type()
{
    test_is_safe_type_impl<T>();
    test_is_safe_type_impl<const T>();
    test_is_safe_type_impl<volatile T>();
    test_is_safe_type_impl<const volatile T>();
}

template <typename T>
void test_is_not_safe_type()
{
    test_is_not_safe_type_impl<T>();
    test_is_not_safe_type_impl<const T>();
    test_is_not_safe_type_impl<volatile T>();
    test_is_not_safe_type_impl<const volatile T>();
}

TEST_CASE("is_safe_type")
{
    test_is_safe_type<phi::boolean>();
    test_is_safe_type<phi::integer<signed char>>();
    test_is_safe_type<phi::integer<unsigned char>>();
    test_is_safe_type<phi::integer<short>>();
    test_is_safe_type<phi::integer<unsigned short>>();
    test_is_safe_type<phi::integer<int>>();
    test_is_safe_type<phi::integer<unsigned int>>();
    test_is_safe_type<phi::integer<long>>();
    test_is_safe_type<phi::integer<unsigned long>>();
    test_is_safe_type<phi::integer<long long>>();
    test_is_safe_type<phi::integer<unsigned long long>>();
    test_is_safe_type<phi::floating_point<float>>();
    test_is_safe_type<phi::floating_point<double>>();
    test_is_safe_type<phi::floating_point<long double>>();

    test_is_not_safe_type<phi::boolean&>();
    test_is_not_safe_type<phi::integer<signed char>&>();
    test_is_not_safe_type<phi::integer<unsigned char>&>();
    test_is_not_safe_type<phi::integer<short>&>();
    test_is_not_safe_type<phi::integer<unsigned short>&>();
    test_is_not_safe_type<phi::integer<int>&>();
    test_is_not_safe_type<phi::integer<unsigned int>&>();
    test_is_not_safe_type<phi::integer<long>&>();
    test_is_not_safe_type<phi::integer<unsigned long>&>();
    test_is_not_safe_type<phi::integer<long long>&>();
    test_is_not_safe_type<phi::integer<unsigned long long>&>();
    test_is_not_safe_type<phi::floating_point<float>&>();
    test_is_not_safe_type<phi::floating_point<double>&>();
    test_is_not_safe_type<phi::floating_point<long double>&>();

    test_is_not_safe_type<phi::boolean&&>();
    test_is_not_safe_type<phi::integer<signed char>&&>();
    test_is_not_safe_type<phi::integer<unsigned char>&&>();
    test_is_not_safe_type<phi::integer<short>&&>();
    test_is_not_safe_type<phi::integer<unsigned short>&&>();
    test_is_not_safe_type<phi::integer<int>&&>();
    test_is_not_safe_type<phi::integer<unsigned int>&&>();
    test_is_not_safe_type<phi::integer<long>&&>();
    test_is_not_safe_type<phi::integer<unsigned long>&&>();
    test_is_not_safe_type<phi::integer<long long>&&>();
    test_is_not_safe_type<phi::integer<unsigned long long>&&>();
    test_is_not_safe_type<phi::floating_point<float>&&>();
    test_is_not_safe_type<phi::floating_point<double>&&>();
    test_is_not_safe_type<phi::floating_point<long double>&&>();

    test_is_not_safe_type<phi::boolean*>();
    test_is_not_safe_type<phi::integer<signed char>*>();
    test_is_not_safe_type<phi::integer<unsigned char>*>();
    test_is_not_safe_type<phi::integer<short>*>();
    test_is_not_safe_type<phi::integer<unsigned short>*>();
    test_is_not_safe_type<phi::integer<int>*>();
    test_is_not_safe_type<phi::integer<unsigned int>*>();
    test_is_not_safe_type<phi::integer<long>*>();
    test_is_not_safe_type<phi::integer<unsigned long>*>();
    test_is_not_safe_type<phi::integer<long long>*>();
    test_is_not_safe_type<phi::integer<unsigned long long>*>();
    test_is_not_safe_type<phi::floating_point<float>*>();
    test_is_not_safe_type<phi::floating_point<double>*>();
    test_is_not_safe_type<phi::floating_point<long double>*>();

    test_is_not_safe_type<void>();
    test_is_not_safe_type<phi::nullptr_t>();
    test_is_not_safe_type<bool>();
    test_is_not_safe_type<char>();
    test_is_not_safe_type<signed char>();
    test_is_not_safe_type<unsigned char>();
    test_is_not_safe_type<short>();
    test_is_not_safe_type<unsigned short>();
    test_is_not_safe_type<int>();
    test_is_not_safe_type<unsigned int>();
    test_is_not_safe_type<long>();
    test_is_not_safe_type<unsigned long>();
    test_is_not_safe_type<long long>();
    test_is_not_safe_type<unsigned long long>();
    test_is_not_safe_type<float>();
    test_is_not_safe_type<double>();
    test_is_not_safe_type<long double>();
    test_is_not_safe_type<char8_t>();
    test_is_not_safe_type<char16_t>();
    test_is_not_safe_type<char32_t>();
    test_is_not_safe_type<wchar_t>();

    test_is_not_safe_type<std::vector<int>>();
    test_is_not_safe_type<phi::scope_ptr<int>>();

    test_is_not_safe_type<int&>();
    test_is_not_safe_type<const int&>();
    test_is_not_safe_type<volatile int&>();
    test_is_not_safe_type<const volatile int&>();
    test_is_not_safe_type<int&&>();
    test_is_not_safe_type<const int&&>();
    test_is_not_safe_type<volatile int&&>();
    test_is_not_safe_type<const volatile int&&>();
    test_is_not_safe_type<int*>();
    test_is_not_safe_type<const int*>();
    test_is_not_safe_type<volatile int*>();
    test_is_not_safe_type<const volatile int*>();
    test_is_not_safe_type<int**>();
    test_is_not_safe_type<const int**>();
    test_is_not_safe_type<volatile int**>();
    test_is_not_safe_type<const volatile int**>();
    test_is_not_safe_type<int*&>();
    test_is_not_safe_type<const int*&>();
    test_is_not_safe_type<volatile int*&>();
    test_is_not_safe_type<const volatile int*&>();
    test_is_not_safe_type<int*&&>();
    test_is_not_safe_type<const int*&&>();
    test_is_not_safe_type<volatile int*&&>();
    test_is_not_safe_type<const volatile int*&&>();
    test_is_not_safe_type<void*>();
    test_is_not_safe_type<char[3]>();
    test_is_not_safe_type<char[]>();
    test_is_not_safe_type<char* [3]>();
    test_is_not_safe_type<char*[]>();
    test_is_not_safe_type<int(*)[3]>();
    test_is_not_safe_type<int(*)[]>();
    test_is_not_safe_type<int(&)[3]>();
    test_is_not_safe_type<int(&)[]>();
    test_is_not_safe_type<int(&&)[3]>();
    test_is_not_safe_type<int(&&)[]>();
    test_is_not_safe_type<char[3][2]>();
    test_is_not_safe_type<char[][2]>();
    test_is_not_safe_type<char* [3][2]>();
    test_is_not_safe_type<char*[][2]>();
    test_is_not_safe_type<int(*)[3][2]>();
    test_is_not_safe_type<int(*)[][2]>();
    test_is_not_safe_type<int(&)[3][2]>();
    test_is_not_safe_type<int(&)[][2]>();
    test_is_not_safe_type<int(&&)[3][2]>();
    test_is_not_safe_type<int(&&)[][2]>();
    test_is_not_safe_type<Class>();
    test_is_not_safe_type<Class[]>();
    test_is_not_safe_type<Class[2]>();
    test_is_not_safe_type<Template<void>>();
    test_is_not_safe_type<Template<int>>();
    test_is_not_safe_type<Template<Class>>();
    test_is_not_safe_type<Template<incomplete_type>>();
    test_is_not_safe_type<VariadicTemplate<>>();
    test_is_not_safe_type<VariadicTemplate<void>>();
    test_is_not_safe_type<VariadicTemplate<int>>();
    test_is_not_safe_type<VariadicTemplate<Class>>();
    test_is_not_safe_type<VariadicTemplate<incomplete_type>>();
    test_is_not_safe_type<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_safe_type<PublicDerviedFromTemplate<Base>>();
    test_is_not_safe_type<PublicDerviedFromTemplate<Derived>>();
    test_is_not_safe_type<PublicDerviedFromTemplate<Class>>();
    test_is_not_safe_type<PrivateDerviedFromTemplate<Base>>();
    test_is_not_safe_type<PrivateDerviedFromTemplate<Derived>>();
    test_is_not_safe_type<PrivateDerviedFromTemplate<Class>>();
    test_is_not_safe_type<ProtectedDerviedFromTemplate<Base>>();
    test_is_not_safe_type<ProtectedDerviedFromTemplate<Derived>>();
    test_is_not_safe_type<ProtectedDerviedFromTemplate<Class>>();
    test_is_not_safe_type<Union>();
    test_is_not_safe_type<NonEmptyUnion>();
    test_is_not_safe_type<Empty>();
    test_is_not_safe_type<NotEmpty>();
    test_is_not_safe_type<bit_zero>();
    test_is_not_safe_type<bit_one>();
    test_is_not_safe_type<Base>();
    test_is_not_safe_type<Derived>();
    test_is_not_safe_type<Abstract>();
    test_is_not_safe_type<PublicAbstract>();
    test_is_not_safe_type<PrivateAbstract>();
    test_is_not_safe_type<ProtectedAbstract>();
    test_is_not_safe_type<AbstractTemplate<int>>();
    test_is_not_safe_type<AbstractTemplate<double>>();
    test_is_not_safe_type<AbstractTemplate<Class>>();
    test_is_not_safe_type<AbstractTemplate<incomplete_type>>();
    test_is_not_safe_type<Final>();
    test_is_not_safe_type<PublicDestructor>();
    test_is_not_safe_type<ProtectedDestructor>();
    test_is_not_safe_type<PrivateDestructor>();
    test_is_not_safe_type<VirtualPublicDestructor>();
    test_is_not_safe_type<VirtualProtectedDestructor>();
    test_is_not_safe_type<VirtualPrivateDestructor>();
    test_is_not_safe_type<PurePublicDestructor>();
    test_is_not_safe_type<PureProtectedDestructor>();
    test_is_not_safe_type<PurePrivateDestructor>();
    test_is_not_safe_type<DeletedPublicDestructor>();
    test_is_not_safe_type<DeletedProtectedDestructor>();
    test_is_not_safe_type<DeletedPrivateDestructor>();
    test_is_not_safe_type<DeletedVirtualPublicDestructor>();
    test_is_not_safe_type<DeletedVirtualProtectedDestructor>();
    test_is_not_safe_type<DeletedVirtualPrivateDestructor>();
    test_is_not_safe_type<Enum>();
    test_is_not_safe_type<EnumSigned>();
    test_is_not_safe_type<EnumUnsigned>();
    test_is_not_safe_type<EnumClass>();
    test_is_not_safe_type<EnumStruct>();
    test_is_not_safe_type<Function>();
    test_is_not_safe_type<FunctionPtr>();
    test_is_not_safe_type<MemberObjectPtr>();
    test_is_not_safe_type<MemberFunctionPtr>();
    test_is_not_safe_type<incomplete_type>();
    test_is_not_safe_type<IncompleteTemplate<void>>();
    test_is_not_safe_type<IncompleteTemplate<int>>();
    test_is_not_safe_type<IncompleteTemplate<Class>>();
    test_is_not_safe_type<IncompleteTemplate<incomplete_type>>();
    test_is_not_safe_type<IncompleteVariadicTemplate<>>();
    test_is_not_safe_type<IncompleteVariadicTemplate<void>>();
    test_is_not_safe_type<IncompleteVariadicTemplate<int>>();
    test_is_not_safe_type<IncompleteVariadicTemplate<Class>>();
    test_is_not_safe_type<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_not_safe_type<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_safe_type<int Class::*>();
    test_is_not_safe_type<float Class::*>();
    test_is_not_safe_type<void * Class::*>();
    test_is_not_safe_type<int * Class::*>();
    test_is_not_safe_type<int Class::*&>();
    test_is_not_safe_type<float Class::*&>();
    test_is_not_safe_type<void * Class::*&>();
    test_is_not_safe_type<int * Class::*&>();
    test_is_not_safe_type<int Class::*&&>();
    test_is_not_safe_type<float Class::*&&>();
    test_is_not_safe_type<void * Class::*&&>();
    test_is_not_safe_type<int * Class::*&&>();
    test_is_not_safe_type<int Class::*const>();
    test_is_not_safe_type<float Class::*const>();
    test_is_not_safe_type<void * Class::*const>();
    test_is_not_safe_type<int Class::*const&>();
    test_is_not_safe_type<float Class::*const&>();
    test_is_not_safe_type<void * Class::*const&>();
    test_is_not_safe_type<int Class::*const&&>();
    test_is_not_safe_type<float Class::*const&&>();
    test_is_not_safe_type<void * Class::*const&&>();
    test_is_not_safe_type<int Class::*volatile>();
    test_is_not_safe_type<float Class::*volatile>();
    test_is_not_safe_type<void * Class::*volatile>();
    test_is_not_safe_type<int Class::*volatile&>();
    test_is_not_safe_type<float Class::*volatile&>();
    test_is_not_safe_type<void * Class::*volatile&>();
    test_is_not_safe_type<int Class::*volatile&&>();
    test_is_not_safe_type<float Class::*volatile&&>();
    test_is_not_safe_type<void * Class::*volatile&&>();
    test_is_not_safe_type<int Class::*const volatile>();
    test_is_not_safe_type<float Class::*const volatile>();
    test_is_not_safe_type<void * Class::*const volatile>();
    test_is_not_safe_type<int Class::*const volatile&>();
    test_is_not_safe_type<float Class::*const volatile&>();
    test_is_not_safe_type<void * Class::*const volatile&>();
    test_is_not_safe_type<int Class::*const volatile&&>();
    test_is_not_safe_type<float Class::*const volatile&&>();
    test_is_not_safe_type<void * Class::*const volatile&&>();
    test_is_not_safe_type<NonCopyable>();
    test_is_not_safe_type<NonMoveable>();
    test_is_not_safe_type<NonConstructible>();
    test_is_not_safe_type<Tracked>();
    test_is_not_safe_type<TrapConstructible>();
    test_is_not_safe_type<TrapImplicitConversion>();
    test_is_not_safe_type<TrapComma>();
    test_is_not_safe_type<TrapCall>();
    test_is_not_safe_type<TrapSelfAssign>();
    test_is_not_safe_type<TrapDeref>();
    test_is_not_safe_type<TrapArraySubscript>();

    test_is_not_safe_type<void()>();
    test_is_not_safe_type<void()&>();
    test_is_not_safe_type<void() &&>();
    test_is_not_safe_type<void() const>();
    test_is_not_safe_type<void() const&>();
    test_is_not_safe_type<void() const&&>();
    test_is_not_safe_type<void() volatile>();
    test_is_not_safe_type<void() volatile&>();
    test_is_not_safe_type<void() volatile&&>();
    test_is_not_safe_type<void() const volatile>();
    test_is_not_safe_type<void() const volatile&>();
    test_is_not_safe_type<void() const volatile&&>();
    test_is_not_safe_type<void() noexcept>();
    test_is_not_safe_type<void()& noexcept>();
    test_is_not_safe_type<void()&& noexcept>();
    test_is_not_safe_type<void() const noexcept>();
    test_is_not_safe_type<void() const& noexcept>();
    test_is_not_safe_type<void() const&& noexcept>();
    test_is_not_safe_type<void() volatile noexcept>();
    test_is_not_safe_type<void() volatile& noexcept>();
    test_is_not_safe_type<void() volatile&& noexcept>();
    test_is_not_safe_type<void() const volatile noexcept>();
    test_is_not_safe_type<void() const volatile& noexcept>();
    test_is_not_safe_type<void() const volatile&& noexcept>();

    test_is_not_safe_type<void(int)>();
    test_is_not_safe_type<void(int)&>();
    test_is_not_safe_type<void(int) &&>();
    test_is_not_safe_type<void(int) const>();
    test_is_not_safe_type<void(int) const&>();
    test_is_not_safe_type<void(int) const&&>();
    test_is_not_safe_type<void(int) volatile>();
    test_is_not_safe_type<void(int) volatile&>();
    test_is_not_safe_type<void(int) volatile&&>();
    test_is_not_safe_type<void(int) const volatile>();
    test_is_not_safe_type<void(int) const volatile&>();
    test_is_not_safe_type<void(int) const volatile&&>();
    test_is_not_safe_type<void(int) noexcept>();
    test_is_not_safe_type<void(int)& noexcept>();
    test_is_not_safe_type<void(int)&& noexcept>();
    test_is_not_safe_type<void(int) const noexcept>();
    test_is_not_safe_type<void(int) const& noexcept>();
    test_is_not_safe_type<void(int) const&& noexcept>();
    test_is_not_safe_type<void(int) volatile noexcept>();
    test_is_not_safe_type<void(int) volatile& noexcept>();
    test_is_not_safe_type<void(int) volatile&& noexcept>();
    test_is_not_safe_type<void(int) const volatile noexcept>();
    test_is_not_safe_type<void(int) const volatile& noexcept>();
    test_is_not_safe_type<void(int) const volatile&& noexcept>();

    test_is_not_safe_type<void(...)>();
    test_is_not_safe_type<void(...)&>();
    test_is_not_safe_type<void(...) &&>();
    test_is_not_safe_type<void(...) const>();
    test_is_not_safe_type<void(...) const&>();
    test_is_not_safe_type<void(...) const&&>();
    test_is_not_safe_type<void(...) volatile>();
    test_is_not_safe_type<void(...) volatile&>();
    test_is_not_safe_type<void(...) volatile&&>();
    test_is_not_safe_type<void(...) const volatile>();
    test_is_not_safe_type<void(...) const volatile&>();
    test_is_not_safe_type<void(...) const volatile&&>();
    test_is_not_safe_type<void(...) noexcept>();
    test_is_not_safe_type<void(...)& noexcept>();
    test_is_not_safe_type<void(...)&& noexcept>();
    test_is_not_safe_type<void(...) const noexcept>();
    test_is_not_safe_type<void(...) const& noexcept>();
    test_is_not_safe_type<void(...) const&& noexcept>();
    test_is_not_safe_type<void(...) volatile noexcept>();
    test_is_not_safe_type<void(...) volatile& noexcept>();
    test_is_not_safe_type<void(...) volatile&& noexcept>();
    test_is_not_safe_type<void(...) const volatile noexcept>();
    test_is_not_safe_type<void(...) const volatile& noexcept>();
    test_is_not_safe_type<void(...) const volatile&& noexcept>();

    test_is_not_safe_type<void(int, ...)>();
    test_is_not_safe_type<void(int, ...)&>();
    test_is_not_safe_type<void(int, ...) &&>();
    test_is_not_safe_type<void(int, ...) const>();
    test_is_not_safe_type<void(int, ...) const&>();
    test_is_not_safe_type<void(int, ...) const&&>();
    test_is_not_safe_type<void(int, ...) volatile>();
    test_is_not_safe_type<void(int, ...) volatile&>();
    test_is_not_safe_type<void(int, ...) volatile&&>();
    test_is_not_safe_type<void(int, ...) const volatile>();
    test_is_not_safe_type<void(int, ...) const volatile&>();
    test_is_not_safe_type<void(int, ...) const volatile&&>();
    test_is_not_safe_type<void(int, ...) noexcept>();
    test_is_not_safe_type<void(int, ...)& noexcept>();
    test_is_not_safe_type<void(int, ...)&& noexcept>();
    test_is_not_safe_type<void(int, ...) const noexcept>();
    test_is_not_safe_type<void(int, ...) const& noexcept>();
    test_is_not_safe_type<void(int, ...) const&& noexcept>();
    test_is_not_safe_type<void(int, ...) volatile noexcept>();
    test_is_not_safe_type<void(int, ...) volatile& noexcept>();
    test_is_not_safe_type<void(int, ...) volatile&& noexcept>();
    test_is_not_safe_type<void(int, ...) const volatile noexcept>();
    test_is_not_safe_type<void(int, ...) const volatile& noexcept>();
    test_is_not_safe_type<void(int, ...) const volatile&& noexcept>();

    test_is_not_safe_type<int()>();
    test_is_not_safe_type<int()&>();
    test_is_not_safe_type<int() &&>();
    test_is_not_safe_type<int() const>();
    test_is_not_safe_type<int() const&>();
    test_is_not_safe_type<int() const&&>();
    test_is_not_safe_type<int() volatile>();
    test_is_not_safe_type<int() volatile&>();
    test_is_not_safe_type<int() volatile&&>();
    test_is_not_safe_type<int() const volatile>();
    test_is_not_safe_type<int() const volatile&>();
    test_is_not_safe_type<int() const volatile&&>();
    test_is_not_safe_type<int() noexcept>();
    test_is_not_safe_type<int()& noexcept>();
    test_is_not_safe_type<int()&& noexcept>();
    test_is_not_safe_type<int() const noexcept>();
    test_is_not_safe_type<int() const& noexcept>();
    test_is_not_safe_type<int() const&& noexcept>();
    test_is_not_safe_type<int() volatile noexcept>();
    test_is_not_safe_type<int() volatile& noexcept>();
    test_is_not_safe_type<int() volatile&& noexcept>();
    test_is_not_safe_type<int() const volatile noexcept>();
    test_is_not_safe_type<int() const volatile& noexcept>();
    test_is_not_safe_type<int() const volatile&& noexcept>();

    test_is_not_safe_type<int(int)>();
    test_is_not_safe_type<int(int)&>();
    test_is_not_safe_type<int(int) &&>();
    test_is_not_safe_type<int(int) const>();
    test_is_not_safe_type<int(int) const&>();
    test_is_not_safe_type<int(int) const&&>();
    test_is_not_safe_type<int(int) volatile>();
    test_is_not_safe_type<int(int) volatile&>();
    test_is_not_safe_type<int(int) volatile&&>();
    test_is_not_safe_type<int(int) const volatile>();
    test_is_not_safe_type<int(int) const volatile&>();
    test_is_not_safe_type<int(int) const volatile&&>();
    test_is_not_safe_type<int(int) noexcept>();
    test_is_not_safe_type<int(int)& noexcept>();
    test_is_not_safe_type<int(int)&& noexcept>();
    test_is_not_safe_type<int(int) const noexcept>();
    test_is_not_safe_type<int(int) const& noexcept>();
    test_is_not_safe_type<int(int) const&& noexcept>();
    test_is_not_safe_type<int(int) volatile noexcept>();
    test_is_not_safe_type<int(int) volatile& noexcept>();
    test_is_not_safe_type<int(int) volatile&& noexcept>();
    test_is_not_safe_type<int(int) const volatile noexcept>();
    test_is_not_safe_type<int(int) const volatile& noexcept>();
    test_is_not_safe_type<int(int) const volatile&& noexcept>();

    test_is_not_safe_type<int(...)>();
    test_is_not_safe_type<int(...)&>();
    test_is_not_safe_type<int(...) &&>();
    test_is_not_safe_type<int(...) const>();
    test_is_not_safe_type<int(...) const&>();
    test_is_not_safe_type<int(...) const&&>();
    test_is_not_safe_type<int(...) volatile>();
    test_is_not_safe_type<int(...) volatile&>();
    test_is_not_safe_type<int(...) volatile&&>();
    test_is_not_safe_type<int(...) const volatile>();
    test_is_not_safe_type<int(...) const volatile&>();
    test_is_not_safe_type<int(...) const volatile&&>();
    test_is_not_safe_type<int(...) noexcept>();
    test_is_not_safe_type<int(...)& noexcept>();
    test_is_not_safe_type<int(...)&& noexcept>();
    test_is_not_safe_type<int(...) const noexcept>();
    test_is_not_safe_type<int(...) const& noexcept>();
    test_is_not_safe_type<int(...) const&& noexcept>();
    test_is_not_safe_type<int(...) volatile noexcept>();
    test_is_not_safe_type<int(...) volatile& noexcept>();
    test_is_not_safe_type<int(...) volatile&& noexcept>();
    test_is_not_safe_type<int(...) const volatile noexcept>();
    test_is_not_safe_type<int(...) const volatile& noexcept>();
    test_is_not_safe_type<int(...) const volatile&& noexcept>();

    test_is_not_safe_type<int(int, ...)>();
    test_is_not_safe_type<int(int, ...)&>();
    test_is_not_safe_type<int(int, ...) &&>();
    test_is_not_safe_type<int(int, ...) const>();
    test_is_not_safe_type<int(int, ...) const&>();
    test_is_not_safe_type<int(int, ...) const&&>();
    test_is_not_safe_type<int(int, ...) volatile>();
    test_is_not_safe_type<int(int, ...) volatile&>();
    test_is_not_safe_type<int(int, ...) volatile&&>();
    test_is_not_safe_type<int(int, ...) const volatile>();
    test_is_not_safe_type<int(int, ...) const volatile&>();
    test_is_not_safe_type<int(int, ...) const volatile&&>();
    test_is_not_safe_type<int(int, ...) noexcept>();
    test_is_not_safe_type<int(int, ...)& noexcept>();
    test_is_not_safe_type<int(int, ...)&& noexcept>();
    test_is_not_safe_type<int(int, ...) const noexcept>();
    test_is_not_safe_type<int(int, ...) const& noexcept>();
    test_is_not_safe_type<int(int, ...) const&& noexcept>();
    test_is_not_safe_type<int(int, ...) volatile noexcept>();
    test_is_not_safe_type<int(int, ...) volatile& noexcept>();
    test_is_not_safe_type<int(int, ...) volatile&& noexcept>();
    test_is_not_safe_type<int(int, ...) const volatile noexcept>();
    test_is_not_safe_type<int(int, ...) const volatile& noexcept>();
    test_is_not_safe_type<int(int, ...) const volatile&& noexcept>();

    test_is_not_safe_type<void (*)()>();
    test_is_not_safe_type<void (*)() noexcept>();

    test_is_not_safe_type<void (*)(int)>();
    test_is_not_safe_type<void (*)(int) noexcept>();

    test_is_not_safe_type<void (*)(...)>();
    test_is_not_safe_type<void (*)(...) noexcept>();

    test_is_not_safe_type<void (*)(int, ...)>();
    test_is_not_safe_type<void (*)(int, ...) noexcept>();

    test_is_not_safe_type<int (*)()>();
    test_is_not_safe_type<int (*)() noexcept>();

    test_is_not_safe_type<int (*)(int)>();
    test_is_not_safe_type<int (*)(int) noexcept>();

    test_is_not_safe_type<int (*)(...)>();
    test_is_not_safe_type<int (*)(...) noexcept>();

    test_is_not_safe_type<int (*)(int, ...)>();
    test_is_not_safe_type<int (*)(int, ...) noexcept>();

    test_is_not_safe_type<void (&)()>();
    test_is_not_safe_type<void (&)() noexcept>();

    test_is_not_safe_type<void (&)(int)>();
    test_is_not_safe_type<void (&)(int) noexcept>();

    test_is_not_safe_type<void (&)(...)>();
    test_is_not_safe_type<void (&)(...) noexcept>();

    test_is_not_safe_type<void (&)(int, ...)>();
    test_is_not_safe_type<void (&)(int, ...) noexcept>();

    test_is_not_safe_type<int (&)()>();
    test_is_not_safe_type<int (&)() noexcept>();

    test_is_not_safe_type<int (&)(int)>();
    test_is_not_safe_type<int (&)(int) noexcept>();

    test_is_not_safe_type<int (&)(...)>();
    test_is_not_safe_type<int (&)(...) noexcept>();

    test_is_not_safe_type<int (&)(int, ...)>();
    test_is_not_safe_type<int (&)(int, ...) noexcept>();

    test_is_not_safe_type<void(&&)()>();
    test_is_not_safe_type<void(&&)() noexcept>();

    test_is_not_safe_type<void(&&)(int)>();
    test_is_not_safe_type<void(&&)(int) noexcept>();

    test_is_not_safe_type<void(&&)(...)>();
    test_is_not_safe_type<void(&&)(...) noexcept>();

    test_is_not_safe_type<void(&&)(int, ...)>();
    test_is_not_safe_type<void(&&)(int, ...) noexcept>();

    test_is_not_safe_type<int(&&)()>();
    test_is_not_safe_type<int(&&)() noexcept>();

    test_is_not_safe_type<int(&&)(int)>();
    test_is_not_safe_type<int(&&)(int) noexcept>();

    test_is_not_safe_type<int(&&)(...)>();
    test_is_not_safe_type<int(&&)(...) noexcept>();

    test_is_not_safe_type<int(&&)(int, ...)>();
    test_is_not_safe_type<int(&&)(int, ...) noexcept>();

    test_is_not_safe_type<void (Class::*)()>();
    test_is_not_safe_type<void (Class::*)()&>();
    test_is_not_safe_type<void (Class::*)() &&>();
    test_is_not_safe_type<void (Class::*)() const>();
    test_is_not_safe_type<void (Class::*)() const&>();
    test_is_not_safe_type<void (Class::*)() const&&>();
    test_is_not_safe_type<void (Class::*)() noexcept>();
    test_is_not_safe_type<void (Class::*)()& noexcept>();
    test_is_not_safe_type<void (Class::*)()&& noexcept>();
    test_is_not_safe_type<void (Class::*)() const noexcept>();
    test_is_not_safe_type<void (Class::*)() const& noexcept>();
    test_is_not_safe_type<void (Class::*)() const&& noexcept>();

    test_is_not_safe_type<void (Class::*)(int)>();
    test_is_not_safe_type<void (Class::*)(int)&>();
    test_is_not_safe_type<void (Class::*)(int) &&>();
    test_is_not_safe_type<void (Class::*)(int) const>();
    test_is_not_safe_type<void (Class::*)(int) const&>();
    test_is_not_safe_type<void (Class::*)(int) const&&>();
    test_is_not_safe_type<void (Class::*)(int) noexcept>();
    test_is_not_safe_type<void (Class::*)(int)& noexcept>();
    test_is_not_safe_type<void (Class::*)(int)&& noexcept>();
    test_is_not_safe_type<void (Class::*)(int) const noexcept>();
    test_is_not_safe_type<void (Class::*)(int) const& noexcept>();
    test_is_not_safe_type<void (Class::*)(int) const&& noexcept>();

    test_is_not_safe_type<void (Class::*)(...)>();
    test_is_not_safe_type<void (Class::*)(...)&>();
    test_is_not_safe_type<void (Class::*)(...) &&>();
    test_is_not_safe_type<void (Class::*)(...) const>();
    test_is_not_safe_type<void (Class::*)(...) const&>();
    test_is_not_safe_type<void (Class::*)(...) const&&>();
    test_is_not_safe_type<void (Class::*)(...) noexcept>();
    test_is_not_safe_type<void (Class::*)(...)& noexcept>();
    test_is_not_safe_type<void (Class::*)(...)&& noexcept>();
    test_is_not_safe_type<void (Class::*)(...) const noexcept>();
    test_is_not_safe_type<void (Class::*)(...) const& noexcept>();
    test_is_not_safe_type<void (Class::*)(...) const&& noexcept>();

    test_is_not_safe_type<void (Class::*)(int, ...)>();
    test_is_not_safe_type<void (Class::*)(int, ...)&>();
    test_is_not_safe_type<void (Class::*)(int, ...) &&>();
    test_is_not_safe_type<void (Class::*)(int, ...) const>();
    test_is_not_safe_type<void (Class::*)(int, ...) const&>();
    test_is_not_safe_type<void (Class::*)(int, ...) const&&>();
    test_is_not_safe_type<void (Class::*)(int, ...) noexcept>();
    test_is_not_safe_type<void (Class::*)(int, ...)& noexcept>();
    test_is_not_safe_type<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_safe_type<void (Class::*)(int, ...) const noexcept>();
    test_is_not_safe_type<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_safe_type<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_safe_type<int (Class::*)()>();
    test_is_not_safe_type<int (Class::*)()&>();
    test_is_not_safe_type<int (Class::*)() &&>();
    test_is_not_safe_type<int (Class::*)() const>();
    test_is_not_safe_type<int (Class::*)() const&>();
    test_is_not_safe_type<int (Class::*)() const&&>();
    test_is_not_safe_type<int (Class::*)() noexcept>();
    test_is_not_safe_type<int (Class::*)()& noexcept>();
    test_is_not_safe_type<int (Class::*)()&& noexcept>();
    test_is_not_safe_type<int (Class::*)() const noexcept>();
    test_is_not_safe_type<int (Class::*)() const& noexcept>();
    test_is_not_safe_type<int (Class::*)() const&& noexcept>();

    test_is_not_safe_type<int (Class::*)(int)>();
    test_is_not_safe_type<int (Class::*)(int)&>();
    test_is_not_safe_type<int (Class::*)(int) &&>();
    test_is_not_safe_type<int (Class::*)(int) const>();
    test_is_not_safe_type<int (Class::*)(int) const&>();
    test_is_not_safe_type<int (Class::*)(int) const&&>();
    test_is_not_safe_type<int (Class::*)(int) noexcept>();
    test_is_not_safe_type<int (Class::*)(int)& noexcept>();
    test_is_not_safe_type<int (Class::*)(int)&& noexcept>();
    test_is_not_safe_type<int (Class::*)(int) const noexcept>();
    test_is_not_safe_type<int (Class::*)(int) const& noexcept>();
    test_is_not_safe_type<int (Class::*)(int) const&& noexcept>();

    test_is_not_safe_type<int (Class::*)(...)>();
    test_is_not_safe_type<int (Class::*)(...)&>();
    test_is_not_safe_type<int (Class::*)(...) &&>();
    test_is_not_safe_type<int (Class::*)(...) const>();
    test_is_not_safe_type<int (Class::*)(...) const&>();
    test_is_not_safe_type<int (Class::*)(...) const&&>();
    test_is_not_safe_type<int (Class::*)(...) noexcept>();
    test_is_not_safe_type<int (Class::*)(...)& noexcept>();
    test_is_not_safe_type<int (Class::*)(...)&& noexcept>();
    test_is_not_safe_type<int (Class::*)(...) const noexcept>();
    test_is_not_safe_type<int (Class::*)(...) const& noexcept>();
    test_is_not_safe_type<int (Class::*)(...) const&& noexcept>();

    test_is_not_safe_type<int (Class::*)(int, ...)>();
    test_is_not_safe_type<int (Class::*)(int, ...)&>();
    test_is_not_safe_type<int (Class::*)(int, ...) &&>();
    test_is_not_safe_type<int (Class::*)(int, ...) const>();
    test_is_not_safe_type<int (Class::*)(int, ...) const&>();
    test_is_not_safe_type<int (Class::*)(int, ...) const&&>();
    test_is_not_safe_type<int (Class::*)(int, ...) noexcept>();
    test_is_not_safe_type<int (Class::*)(int, ...)& noexcept>();
    test_is_not_safe_type<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_safe_type<int (Class::*)(int, ...) const noexcept>();
    test_is_not_safe_type<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_safe_type<int (Class::*)(int, ...) const&& noexcept>();
}
