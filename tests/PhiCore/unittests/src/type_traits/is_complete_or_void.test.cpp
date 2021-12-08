#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_complete_or_void.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_complete_or_void_impl()
{
    STATIC_REQUIRE(phi::is_complete_or_void<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_complete_or_void<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_complete_or_void_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_complete_or_void_v<T>);
#endif
}

template <typename T>
void test_is_complete_or_void()
{
    test_is_complete_or_void_impl<T>();
    test_is_complete_or_void_impl<const T>();
    test_is_complete_or_void_impl<volatile T>();
    test_is_complete_or_void_impl<const volatile T>();
}

template <typename T>
void test_is_not_complete_or_void_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_complete_or_void<T>::value);
    STATIC_REQUIRE(phi::is_not_complete_or_void<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_complete_or_void_v<T>);
    STATIC_REQUIRE(phi::is_not_complete_or_void_v<T>);
#endif
}

template <typename T>
void test_is_not_complete_or_void()
{
    test_is_not_complete_or_void_impl<T>();
    test_is_not_complete_or_void_impl<const T>();
    test_is_not_complete_or_void_impl<volatile T>();
    test_is_not_complete_or_void_impl<const volatile T>();
}

class A;

TEST_CASE("is_complete_or_void")
{
    test_is_complete_or_void<void>();
    test_is_complete_or_void<phi::nullptr_t>();
    test_is_complete_or_void<bool>();
    test_is_complete_or_void<char>();
    test_is_complete_or_void<signed char>();
    test_is_complete_or_void<unsigned char>();
    test_is_complete_or_void<short>();
    test_is_complete_or_void<unsigned short>();
    test_is_complete_or_void<int>();
    test_is_complete_or_void<unsigned int>();
    test_is_complete_or_void<long>();
    test_is_complete_or_void<unsigned long>();
    test_is_complete_or_void<long long>();
    test_is_complete_or_void<unsigned long long>();
    test_is_complete_or_void<float>();
    test_is_complete_or_void<double>();
    test_is_complete_or_void<long double>();
    test_is_complete_or_void<char8_t>();
    test_is_complete_or_void<char16_t>();
    test_is_complete_or_void<char32_t>();
    test_is_complete_or_void<wchar_t>();

    test_is_complete_or_void<phi::boolean>();
    test_is_complete_or_void<phi::integer<signed char>>();
    test_is_complete_or_void<phi::integer<unsigned char>>();
    test_is_complete_or_void<phi::integer<short>>();
    test_is_complete_or_void<phi::integer<unsigned short>>();
    test_is_complete_or_void<phi::integer<int>>();
    test_is_complete_or_void<phi::integer<unsigned int>>();
    test_is_complete_or_void<phi::integer<long>>();
    test_is_complete_or_void<phi::integer<unsigned long>>();
    test_is_complete_or_void<phi::integer<long long>>();
    test_is_complete_or_void<phi::integer<unsigned long long>>();
    test_is_complete_or_void<phi::floating_point<float>>();
    test_is_complete_or_void<phi::floating_point<double>>();
    test_is_complete_or_void<phi::floating_point<long double>>();

    test_is_complete_or_void<std::vector<int>>();
    test_is_complete_or_void<phi::scope_ptr<int>>();

    test_is_complete_or_void<int&>();
    test_is_complete_or_void<const int&>();
    test_is_complete_or_void<volatile int&>();
    test_is_complete_or_void<const volatile int&>();
    test_is_complete_or_void<int&&>();
    test_is_complete_or_void<const int&&>();
    test_is_complete_or_void<volatile int&&>();
    test_is_complete_or_void<const volatile int&&>();
    test_is_complete_or_void<int*>();
    test_is_complete_or_void<const int*>();
    test_is_complete_or_void<volatile int*>();
    test_is_complete_or_void<const volatile int*>();
    test_is_complete_or_void<int**>();
    test_is_complete_or_void<const int**>();
    test_is_complete_or_void<volatile int**>();
    test_is_complete_or_void<const volatile int**>();
    test_is_complete_or_void<int*&>();
    test_is_complete_or_void<const int*&>();
    test_is_complete_or_void<volatile int*&>();
    test_is_complete_or_void<const volatile int*&>();
    test_is_complete_or_void<int*&&>();
    test_is_complete_or_void<const int*&&>();
    test_is_complete_or_void<volatile int*&&>();
    test_is_complete_or_void<const volatile int*&&>();
    test_is_complete_or_void<void*>();
    test_is_complete_or_void<char[3]>();
    test_is_not_complete_or_void<char[]>();
    test_is_complete_or_void<char* [3]>();
    test_is_not_complete_or_void<char*[]>();
    test_is_complete_or_void<int(*)[3]>();
    test_is_complete_or_void<int(*)[]>();
    test_is_complete_or_void<int(&)[3]>();
    test_is_not_complete_or_void<int(&)[]>();
    test_is_complete_or_void<int(&&)[3]>();
    test_is_complete_or_void<int(&&)[]>();
    test_is_complete_or_void<char[3][2]>();
    test_is_not_complete_or_void<char[][2]>();
    test_is_complete_or_void<char* [3][2]>();
    test_is_not_complete_or_void<char*[][2]>();
    test_is_complete_or_void<int(*)[3][2]>();
    test_is_complete_or_void<int(*)[][2]>();
    test_is_complete_or_void<int(&)[3][2]>();
    test_is_not_complete_or_void<int(&)[][2]>();
    test_is_complete_or_void<int(&&)[3][2]>();
    test_is_complete_or_void<int(&&)[][2]>();
    test_is_complete_or_void<Class>();
    test_is_not_complete_or_void<Class[]>();
    test_is_complete_or_void<Class[2]>();
    test_is_complete_or_void<Template<void>>();
    test_is_complete_or_void<Template<int>>();
    test_is_complete_or_void<Template<Class>>();
    test_is_complete_or_void<Template<incomplete_type>>();
    test_is_complete_or_void<VariadicTemplate<>>();
    test_is_complete_or_void<VariadicTemplate<void>>();
    test_is_complete_or_void<VariadicTemplate<int>>();
    test_is_complete_or_void<VariadicTemplate<Class>>();
    test_is_complete_or_void<VariadicTemplate<incomplete_type>>();
    test_is_complete_or_void<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_complete_or_void<PublicDerviedFromTemplate<Base>>();
    test_is_complete_or_void<PublicDerviedFromTemplate<Derived>>();
    test_is_complete_or_void<PublicDerviedFromTemplate<Class>>();
    test_is_complete_or_void<PrivateDerviedFromTemplate<Base>>();
    test_is_complete_or_void<PrivateDerviedFromTemplate<Derived>>();
    test_is_complete_or_void<PrivateDerviedFromTemplate<Class>>();
    test_is_complete_or_void<ProtectedDerviedFromTemplate<Base>>();
    test_is_complete_or_void<ProtectedDerviedFromTemplate<Derived>>();
    test_is_complete_or_void<ProtectedDerviedFromTemplate<Class>>();
    test_is_complete_or_void<Union>();
    test_is_complete_or_void<NonEmptyUnion>();
    test_is_complete_or_void<Empty>();
    test_is_complete_or_void<NotEmpty>();
    test_is_complete_or_void<bit_zero>();
    test_is_complete_or_void<bit_one>();
    test_is_complete_or_void<Base>();
    test_is_complete_or_void<Derived>();
    test_is_complete_or_void<Abstract>();
    test_is_complete_or_void<PublicAbstract>();
    test_is_complete_or_void<PrivateAbstract>();
    test_is_complete_or_void<ProtectedAbstract>();
    test_is_complete_or_void<AbstractTemplate<int>>();
    test_is_complete_or_void<AbstractTemplate<double>>();
    test_is_complete_or_void<AbstractTemplate<Class>>();
    test_is_complete_or_void<AbstractTemplate<incomplete_type>>();
    test_is_complete_or_void<Final>();
    test_is_complete_or_void<PublicDestructor>();
    test_is_complete_or_void<ProtectedDestructor>();
    test_is_complete_or_void<PrivateDestructor>();
    test_is_complete_or_void<VirtualPublicDestructor>();
    test_is_complete_or_void<VirtualProtectedDestructor>();
    test_is_complete_or_void<VirtualPrivateDestructor>();
    test_is_complete_or_void<PurePublicDestructor>();
    test_is_complete_or_void<PureProtectedDestructor>();
    test_is_complete_or_void<PurePrivateDestructor>();
    test_is_complete_or_void<DeletedPublicDestructor>();
    test_is_complete_or_void<DeletedProtectedDestructor>();
    test_is_complete_or_void<DeletedPrivateDestructor>();
    test_is_complete_or_void<DeletedVirtualPublicDestructor>();
    test_is_complete_or_void<DeletedVirtualProtectedDestructor>();
    test_is_complete_or_void<DeletedVirtualPrivateDestructor>();
    test_is_complete_or_void<Enum>();
    test_is_complete_or_void<EnumSigned>();
    test_is_complete_or_void<EnumUnsigned>();
    test_is_complete_or_void<EnumClass>();
    test_is_complete_or_void<EnumStruct>();
    test_is_complete_or_void<Function>();
    test_is_complete_or_void<FunctionPtr>();
    test_is_complete_or_void<MemberObjectPtr>();
    test_is_complete_or_void<MemberFunctionPtr>();
    test_is_not_complete_or_void<incomplete_type>();
    test_is_not_complete_or_void<IncompleteTemplate<void>>();
    test_is_not_complete_or_void<IncompleteTemplate<int>>();
    test_is_not_complete_or_void<IncompleteTemplate<Class>>();
    test_is_not_complete_or_void<IncompleteTemplate<incomplete_type>>();
    test_is_not_complete_or_void<IncompleteVariadicTemplate<>>();
    test_is_not_complete_or_void<IncompleteVariadicTemplate<void>>();
    test_is_not_complete_or_void<IncompleteVariadicTemplate<int>>();
    test_is_not_complete_or_void<IncompleteVariadicTemplate<Class>>();
    test_is_not_complete_or_void<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_not_complete_or_void<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_complete_or_void<int Class::*>();
    test_is_complete_or_void<float Class::*>();
    test_is_complete_or_void<void * Class::*>();
    test_is_complete_or_void<int * Class::*>();
    test_is_complete_or_void<int Class::*&>();
    test_is_complete_or_void<float Class::*&>();
    test_is_complete_or_void<void * Class::*&>();
    test_is_complete_or_void<int * Class::*&>();
    test_is_complete_or_void<int Class::*&&>();
    test_is_complete_or_void<float Class::*&&>();
    test_is_complete_or_void<void * Class::*&&>();
    test_is_complete_or_void<int * Class::*&&>();
    test_is_complete_or_void<int Class::*const>();
    test_is_complete_or_void<float Class::*const>();
    test_is_complete_or_void<void * Class::*const>();
    test_is_complete_or_void<int Class::*const&>();
    test_is_complete_or_void<float Class::*const&>();
    test_is_complete_or_void<void * Class::*const&>();
    test_is_complete_or_void<int Class::*const&&>();
    test_is_complete_or_void<float Class::*const&&>();
    test_is_complete_or_void<void * Class::*const&&>();
    test_is_complete_or_void<int Class::*volatile>();
    test_is_complete_or_void<float Class::*volatile>();
    test_is_complete_or_void<void * Class::*volatile>();
    test_is_complete_or_void<int Class::*volatile&>();
    test_is_complete_or_void<float Class::*volatile&>();
    test_is_complete_or_void<void * Class::*volatile&>();
    test_is_complete_or_void<int Class::*volatile&&>();
    test_is_complete_or_void<float Class::*volatile&&>();
    test_is_complete_or_void<void * Class::*volatile&&>();
    test_is_complete_or_void<int Class::*const volatile>();
    test_is_complete_or_void<float Class::*const volatile>();
    test_is_complete_or_void<void * Class::*const volatile>();
    test_is_complete_or_void<int Class::*const volatile&>();
    test_is_complete_or_void<float Class::*const volatile&>();
    test_is_complete_or_void<void * Class::*const volatile&>();
    test_is_complete_or_void<int Class::*const volatile&&>();
    test_is_complete_or_void<float Class::*const volatile&&>();
    test_is_complete_or_void<void * Class::*const volatile&&>();
    test_is_complete_or_void<NonCopyable>();
    test_is_complete_or_void<NonMoveable>();
    test_is_complete_or_void<NonConstructible>();
    test_is_complete_or_void<Tracked>();
    test_is_complete_or_void<TrapConstructible>();
    test_is_complete_or_void<TrapImplicitConversion>();
    test_is_complete_or_void<TrapComma>();
    test_is_complete_or_void<TrapCall>();
    test_is_complete_or_void<TrapSelfAssign>();
    test_is_complete_or_void<TrapDeref>();
    test_is_complete_or_void<TrapArraySubscript>();

    test_is_complete_or_void<void()>();
    test_is_complete_or_void<void()&>();
    test_is_complete_or_void<void() &&>();
    test_is_complete_or_void<void() const>();
    test_is_complete_or_void<void() const&>();
    test_is_complete_or_void<void() const&&>();
    test_is_complete_or_void<void() volatile>();
    test_is_complete_or_void<void() volatile&>();
    test_is_complete_or_void<void() volatile&&>();
    test_is_complete_or_void<void() const volatile>();
    test_is_complete_or_void<void() const volatile&>();
    test_is_complete_or_void<void() const volatile&&>();
    test_is_complete_or_void<void() noexcept>();
    test_is_complete_or_void<void()& noexcept>();
    test_is_complete_or_void<void()&& noexcept>();
    test_is_complete_or_void<void() const noexcept>();
    test_is_complete_or_void<void() const& noexcept>();
    test_is_complete_or_void<void() const&& noexcept>();
    test_is_complete_or_void<void() volatile noexcept>();
    test_is_complete_or_void<void() volatile& noexcept>();
    test_is_complete_or_void<void() volatile&& noexcept>();
    test_is_complete_or_void<void() const volatile noexcept>();
    test_is_complete_or_void<void() const volatile& noexcept>();
    test_is_complete_or_void<void() const volatile&& noexcept>();

    test_is_complete_or_void<void(int)>();
    test_is_complete_or_void<void(int)&>();
    test_is_complete_or_void<void(int) &&>();
    test_is_complete_or_void<void(int) const>();
    test_is_complete_or_void<void(int) const&>();
    test_is_complete_or_void<void(int) const&&>();
    test_is_complete_or_void<void(int) volatile>();
    test_is_complete_or_void<void(int) volatile&>();
    test_is_complete_or_void<void(int) volatile&&>();
    test_is_complete_or_void<void(int) const volatile>();
    test_is_complete_or_void<void(int) const volatile&>();
    test_is_complete_or_void<void(int) const volatile&&>();
    test_is_complete_or_void<void(int) noexcept>();
    test_is_complete_or_void<void(int)& noexcept>();
    test_is_complete_or_void<void(int)&& noexcept>();
    test_is_complete_or_void<void(int) const noexcept>();
    test_is_complete_or_void<void(int) const& noexcept>();
    test_is_complete_or_void<void(int) const&& noexcept>();
    test_is_complete_or_void<void(int) volatile noexcept>();
    test_is_complete_or_void<void(int) volatile& noexcept>();
    test_is_complete_or_void<void(int) volatile&& noexcept>();
    test_is_complete_or_void<void(int) const volatile noexcept>();
    test_is_complete_or_void<void(int) const volatile& noexcept>();
    test_is_complete_or_void<void(int) const volatile&& noexcept>();

    test_is_complete_or_void<void(...)>();
    test_is_complete_or_void<void(...)&>();
    test_is_complete_or_void<void(...) &&>();
    test_is_complete_or_void<void(...) const>();
    test_is_complete_or_void<void(...) const&>();
    test_is_complete_or_void<void(...) const&&>();
    test_is_complete_or_void<void(...) volatile>();
    test_is_complete_or_void<void(...) volatile&>();
    test_is_complete_or_void<void(...) volatile&&>();
    test_is_complete_or_void<void(...) const volatile>();
    test_is_complete_or_void<void(...) const volatile&>();
    test_is_complete_or_void<void(...) const volatile&&>();
    test_is_complete_or_void<void(...) noexcept>();
    test_is_complete_or_void<void(...)& noexcept>();
    test_is_complete_or_void<void(...)&& noexcept>();
    test_is_complete_or_void<void(...) const noexcept>();
    test_is_complete_or_void<void(...) const& noexcept>();
    test_is_complete_or_void<void(...) const&& noexcept>();
    test_is_complete_or_void<void(...) volatile noexcept>();
    test_is_complete_or_void<void(...) volatile& noexcept>();
    test_is_complete_or_void<void(...) volatile&& noexcept>();
    test_is_complete_or_void<void(...) const volatile noexcept>();
    test_is_complete_or_void<void(...) const volatile& noexcept>();
    test_is_complete_or_void<void(...) const volatile&& noexcept>();

    test_is_complete_or_void<void(int, ...)>();
    test_is_complete_or_void<void(int, ...)&>();
    test_is_complete_or_void<void(int, ...) &&>();
    test_is_complete_or_void<void(int, ...) const>();
    test_is_complete_or_void<void(int, ...) const&>();
    test_is_complete_or_void<void(int, ...) const&&>();
    test_is_complete_or_void<void(int, ...) volatile>();
    test_is_complete_or_void<void(int, ...) volatile&>();
    test_is_complete_or_void<void(int, ...) volatile&&>();
    test_is_complete_or_void<void(int, ...) const volatile>();
    test_is_complete_or_void<void(int, ...) const volatile&>();
    test_is_complete_or_void<void(int, ...) const volatile&&>();
    test_is_complete_or_void<void(int, ...) noexcept>();
    test_is_complete_or_void<void(int, ...)& noexcept>();
    test_is_complete_or_void<void(int, ...)&& noexcept>();
    test_is_complete_or_void<void(int, ...) const noexcept>();
    test_is_complete_or_void<void(int, ...) const& noexcept>();
    test_is_complete_or_void<void(int, ...) const&& noexcept>();
    test_is_complete_or_void<void(int, ...) volatile noexcept>();
    test_is_complete_or_void<void(int, ...) volatile& noexcept>();
    test_is_complete_or_void<void(int, ...) volatile&& noexcept>();
    test_is_complete_or_void<void(int, ...) const volatile noexcept>();
    test_is_complete_or_void<void(int, ...) const volatile& noexcept>();
    test_is_complete_or_void<void(int, ...) const volatile&& noexcept>();

    test_is_complete_or_void<int()>();
    test_is_complete_or_void<int()&>();
    test_is_complete_or_void<int() &&>();
    test_is_complete_or_void<int() const>();
    test_is_complete_or_void<int() const&>();
    test_is_complete_or_void<int() const&&>();
    test_is_complete_or_void<int() volatile>();
    test_is_complete_or_void<int() volatile&>();
    test_is_complete_or_void<int() volatile&&>();
    test_is_complete_or_void<int() const volatile>();
    test_is_complete_or_void<int() const volatile&>();
    test_is_complete_or_void<int() const volatile&&>();
    test_is_complete_or_void<int() noexcept>();
    test_is_complete_or_void<int()& noexcept>();
    test_is_complete_or_void<int()&& noexcept>();
    test_is_complete_or_void<int() const noexcept>();
    test_is_complete_or_void<int() const& noexcept>();
    test_is_complete_or_void<int() const&& noexcept>();
    test_is_complete_or_void<int() volatile noexcept>();
    test_is_complete_or_void<int() volatile& noexcept>();
    test_is_complete_or_void<int() volatile&& noexcept>();
    test_is_complete_or_void<int() const volatile noexcept>();
    test_is_complete_or_void<int() const volatile& noexcept>();
    test_is_complete_or_void<int() const volatile&& noexcept>();

    test_is_complete_or_void<int(int)>();
    test_is_complete_or_void<int(int)&>();
    test_is_complete_or_void<int(int) &&>();
    test_is_complete_or_void<int(int) const>();
    test_is_complete_or_void<int(int) const&>();
    test_is_complete_or_void<int(int) const&&>();
    test_is_complete_or_void<int(int) volatile>();
    test_is_complete_or_void<int(int) volatile&>();
    test_is_complete_or_void<int(int) volatile&&>();
    test_is_complete_or_void<int(int) const volatile>();
    test_is_complete_or_void<int(int) const volatile&>();
    test_is_complete_or_void<int(int) const volatile&&>();
    test_is_complete_or_void<int(int) noexcept>();
    test_is_complete_or_void<int(int)& noexcept>();
    test_is_complete_or_void<int(int)&& noexcept>();
    test_is_complete_or_void<int(int) const noexcept>();
    test_is_complete_or_void<int(int) const& noexcept>();
    test_is_complete_or_void<int(int) const&& noexcept>();
    test_is_complete_or_void<int(int) volatile noexcept>();
    test_is_complete_or_void<int(int) volatile& noexcept>();
    test_is_complete_or_void<int(int) volatile&& noexcept>();
    test_is_complete_or_void<int(int) const volatile noexcept>();
    test_is_complete_or_void<int(int) const volatile& noexcept>();
    test_is_complete_or_void<int(int) const volatile&& noexcept>();

    test_is_complete_or_void<int(...)>();
    test_is_complete_or_void<int(...)&>();
    test_is_complete_or_void<int(...) &&>();
    test_is_complete_or_void<int(...) const>();
    test_is_complete_or_void<int(...) const&>();
    test_is_complete_or_void<int(...) const&&>();
    test_is_complete_or_void<int(...) volatile>();
    test_is_complete_or_void<int(...) volatile&>();
    test_is_complete_or_void<int(...) volatile&&>();
    test_is_complete_or_void<int(...) const volatile>();
    test_is_complete_or_void<int(...) const volatile&>();
    test_is_complete_or_void<int(...) const volatile&&>();
    test_is_complete_or_void<int(...) noexcept>();
    test_is_complete_or_void<int(...)& noexcept>();
    test_is_complete_or_void<int(...)&& noexcept>();
    test_is_complete_or_void<int(...) const noexcept>();
    test_is_complete_or_void<int(...) const& noexcept>();
    test_is_complete_or_void<int(...) const&& noexcept>();
    test_is_complete_or_void<int(...) volatile noexcept>();
    test_is_complete_or_void<int(...) volatile& noexcept>();
    test_is_complete_or_void<int(...) volatile&& noexcept>();
    test_is_complete_or_void<int(...) const volatile noexcept>();
    test_is_complete_or_void<int(...) const volatile& noexcept>();
    test_is_complete_or_void<int(...) const volatile&& noexcept>();

    test_is_complete_or_void<int(int, ...)>();
    test_is_complete_or_void<int(int, ...)&>();
    test_is_complete_or_void<int(int, ...) &&>();
    test_is_complete_or_void<int(int, ...) const>();
    test_is_complete_or_void<int(int, ...) const&>();
    test_is_complete_or_void<int(int, ...) const&&>();
    test_is_complete_or_void<int(int, ...) volatile>();
    test_is_complete_or_void<int(int, ...) volatile&>();
    test_is_complete_or_void<int(int, ...) volatile&&>();
    test_is_complete_or_void<int(int, ...) const volatile>();
    test_is_complete_or_void<int(int, ...) const volatile&>();
    test_is_complete_or_void<int(int, ...) const volatile&&>();
    test_is_complete_or_void<int(int, ...) noexcept>();
    test_is_complete_or_void<int(int, ...)& noexcept>();
    test_is_complete_or_void<int(int, ...)&& noexcept>();
    test_is_complete_or_void<int(int, ...) const noexcept>();
    test_is_complete_or_void<int(int, ...) const& noexcept>();
    test_is_complete_or_void<int(int, ...) const&& noexcept>();
    test_is_complete_or_void<int(int, ...) volatile noexcept>();
    test_is_complete_or_void<int(int, ...) volatile& noexcept>();
    test_is_complete_or_void<int(int, ...) volatile&& noexcept>();
    test_is_complete_or_void<int(int, ...) const volatile noexcept>();
    test_is_complete_or_void<int(int, ...) const volatile& noexcept>();
    test_is_complete_or_void<int(int, ...) const volatile&& noexcept>();

    test_is_complete_or_void<void (*)()>();
    test_is_complete_or_void<void (*)() noexcept>();

    test_is_complete_or_void<void (*)(int)>();
    test_is_complete_or_void<void (*)(int) noexcept>();

    test_is_complete_or_void<void (*)(...)>();
    test_is_complete_or_void<void (*)(...) noexcept>();

    test_is_complete_or_void<void (*)(int, ...)>();
    test_is_complete_or_void<void (*)(int, ...) noexcept>();

    test_is_complete_or_void<int (*)()>();
    test_is_complete_or_void<int (*)() noexcept>();

    test_is_complete_or_void<int (*)(int)>();
    test_is_complete_or_void<int (*)(int) noexcept>();

    test_is_complete_or_void<int (*)(...)>();
    test_is_complete_or_void<int (*)(...) noexcept>();

    test_is_complete_or_void<int (*)(int, ...)>();
    test_is_complete_or_void<int (*)(int, ...) noexcept>();

    test_is_complete_or_void<void (&)()>();
    test_is_complete_or_void<void (&)() noexcept>();

    test_is_complete_or_void<void (&)(int)>();
    test_is_complete_or_void<void (&)(int) noexcept>();

    test_is_complete_or_void<void (&)(...)>();
    test_is_complete_or_void<void (&)(...) noexcept>();

    test_is_complete_or_void<void (&)(int, ...)>();
    test_is_complete_or_void<void (&)(int, ...) noexcept>();

    test_is_complete_or_void<int (&)()>();
    test_is_complete_or_void<int (&)() noexcept>();

    test_is_complete_or_void<int (&)(int)>();
    test_is_complete_or_void<int (&)(int) noexcept>();

    test_is_complete_or_void<int (&)(...)>();
    test_is_complete_or_void<int (&)(...) noexcept>();

    test_is_complete_or_void<int (&)(int, ...)>();
    test_is_complete_or_void<int (&)(int, ...) noexcept>();

    test_is_complete_or_void<void(&&)()>();
    test_is_complete_or_void<void(&&)() noexcept>();

    test_is_complete_or_void<void(&&)(int)>();
    test_is_complete_or_void<void(&&)(int) noexcept>();

    test_is_complete_or_void<void(&&)(...)>();
    test_is_complete_or_void<void(&&)(...) noexcept>();

    test_is_complete_or_void<void(&&)(int, ...)>();
    test_is_complete_or_void<void(&&)(int, ...) noexcept>();

    test_is_complete_or_void<int(&&)()>();
    test_is_complete_or_void<int(&&)() noexcept>();

    test_is_complete_or_void<int(&&)(int)>();
    test_is_complete_or_void<int(&&)(int) noexcept>();

    test_is_complete_or_void<int(&&)(...)>();
    test_is_complete_or_void<int(&&)(...) noexcept>();

    test_is_complete_or_void<int(&&)(int, ...)>();
    test_is_complete_or_void<int(&&)(int, ...) noexcept>();

    test_is_complete_or_void<void (Class::*)()>();
    test_is_complete_or_void<void (Class::*)()&>();
    test_is_complete_or_void<void (Class::*)() &&>();
    test_is_complete_or_void<void (Class::*)() const>();
    test_is_complete_or_void<void (Class::*)() const&>();
    test_is_complete_or_void<void (Class::*)() const&&>();
    test_is_complete_or_void<void (Class::*)() noexcept>();
    test_is_complete_or_void<void (Class::*)()& noexcept>();
    test_is_complete_or_void<void (Class::*)()&& noexcept>();
    test_is_complete_or_void<void (Class::*)() const noexcept>();
    test_is_complete_or_void<void (Class::*)() const& noexcept>();
    test_is_complete_or_void<void (Class::*)() const&& noexcept>();

    test_is_complete_or_void<void (Class::*)(int)>();
    test_is_complete_or_void<void (Class::*)(int)&>();
    test_is_complete_or_void<void (Class::*)(int) &&>();
    test_is_complete_or_void<void (Class::*)(int) const>();
    test_is_complete_or_void<void (Class::*)(int) const&>();
    test_is_complete_or_void<void (Class::*)(int) const&&>();
    test_is_complete_or_void<void (Class::*)(int) noexcept>();
    test_is_complete_or_void<void (Class::*)(int)& noexcept>();
    test_is_complete_or_void<void (Class::*)(int)&& noexcept>();
    test_is_complete_or_void<void (Class::*)(int) const noexcept>();
    test_is_complete_or_void<void (Class::*)(int) const& noexcept>();
    test_is_complete_or_void<void (Class::*)(int) const&& noexcept>();

    test_is_complete_or_void<void (Class::*)(...)>();
    test_is_complete_or_void<void (Class::*)(...)&>();
    test_is_complete_or_void<void (Class::*)(...) &&>();
    test_is_complete_or_void<void (Class::*)(...) const>();
    test_is_complete_or_void<void (Class::*)(...) const&>();
    test_is_complete_or_void<void (Class::*)(...) const&&>();
    test_is_complete_or_void<void (Class::*)(...) noexcept>();
    test_is_complete_or_void<void (Class::*)(...)& noexcept>();
    test_is_complete_or_void<void (Class::*)(...)&& noexcept>();
    test_is_complete_or_void<void (Class::*)(...) const noexcept>();
    test_is_complete_or_void<void (Class::*)(...) const& noexcept>();
    test_is_complete_or_void<void (Class::*)(...) const&& noexcept>();

    test_is_complete_or_void<void (Class::*)(int, ...)>();
    test_is_complete_or_void<void (Class::*)(int, ...)&>();
    test_is_complete_or_void<void (Class::*)(int, ...) &&>();
    test_is_complete_or_void<void (Class::*)(int, ...) const>();
    test_is_complete_or_void<void (Class::*)(int, ...) const&>();
    test_is_complete_or_void<void (Class::*)(int, ...) const&&>();
    test_is_complete_or_void<void (Class::*)(int, ...) noexcept>();
    test_is_complete_or_void<void (Class::*)(int, ...)& noexcept>();
    test_is_complete_or_void<void (Class::*)(int, ...)&& noexcept>();
    test_is_complete_or_void<void (Class::*)(int, ...) const noexcept>();
    test_is_complete_or_void<void (Class::*)(int, ...) const& noexcept>();
    test_is_complete_or_void<void (Class::*)(int, ...) const&& noexcept>();

    test_is_complete_or_void<int (Class::*)()>();
    test_is_complete_or_void<int (Class::*)()&>();
    test_is_complete_or_void<int (Class::*)() &&>();
    test_is_complete_or_void<int (Class::*)() const>();
    test_is_complete_or_void<int (Class::*)() const&>();
    test_is_complete_or_void<int (Class::*)() const&&>();
    test_is_complete_or_void<int (Class::*)() noexcept>();
    test_is_complete_or_void<int (Class::*)()& noexcept>();
    test_is_complete_or_void<int (Class::*)()&& noexcept>();
    test_is_complete_or_void<int (Class::*)() const noexcept>();
    test_is_complete_or_void<int (Class::*)() const& noexcept>();
    test_is_complete_or_void<int (Class::*)() const&& noexcept>();

    test_is_complete_or_void<int (Class::*)(int)>();
    test_is_complete_or_void<int (Class::*)(int)&>();
    test_is_complete_or_void<int (Class::*)(int) &&>();
    test_is_complete_or_void<int (Class::*)(int) const>();
    test_is_complete_or_void<int (Class::*)(int) const&>();
    test_is_complete_or_void<int (Class::*)(int) const&&>();
    test_is_complete_or_void<int (Class::*)(int) noexcept>();
    test_is_complete_or_void<int (Class::*)(int)& noexcept>();
    test_is_complete_or_void<int (Class::*)(int)&& noexcept>();
    test_is_complete_or_void<int (Class::*)(int) const noexcept>();
    test_is_complete_or_void<int (Class::*)(int) const& noexcept>();
    test_is_complete_or_void<int (Class::*)(int) const&& noexcept>();

    test_is_complete_or_void<int (Class::*)(...)>();
    test_is_complete_or_void<int (Class::*)(...)&>();
    test_is_complete_or_void<int (Class::*)(...) &&>();
    test_is_complete_or_void<int (Class::*)(...) const>();
    test_is_complete_or_void<int (Class::*)(...) const&>();
    test_is_complete_or_void<int (Class::*)(...) const&&>();
    test_is_complete_or_void<int (Class::*)(...) noexcept>();
    test_is_complete_or_void<int (Class::*)(...)& noexcept>();
    test_is_complete_or_void<int (Class::*)(...)&& noexcept>();
    test_is_complete_or_void<int (Class::*)(...) const noexcept>();
    test_is_complete_or_void<int (Class::*)(...) const& noexcept>();
    test_is_complete_or_void<int (Class::*)(...) const&& noexcept>();

    test_is_complete_or_void<int (Class::*)(int, ...)>();
    test_is_complete_or_void<int (Class::*)(int, ...)&>();
    test_is_complete_or_void<int (Class::*)(int, ...) &&>();
    test_is_complete_or_void<int (Class::*)(int, ...) const>();
    test_is_complete_or_void<int (Class::*)(int, ...) const&>();
    test_is_complete_or_void<int (Class::*)(int, ...) const&&>();
    test_is_complete_or_void<int (Class::*)(int, ...) noexcept>();
    test_is_complete_or_void<int (Class::*)(int, ...)& noexcept>();
    test_is_complete_or_void<int (Class::*)(int, ...)&& noexcept>();
    test_is_complete_or_void<int (Class::*)(int, ...) const noexcept>();
    test_is_complete_or_void<int (Class::*)(int, ...) const& noexcept>();
    test_is_complete_or_void<int (Class::*)(int, ...) const&& noexcept>();
}
