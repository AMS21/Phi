#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_bounded_array.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_bounded_array_impl()
{
    STATIC_REQUIRE(phi::is_bounded_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_bounded_array<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_bounded_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_bounded_array_v<T>);
#endif

// Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(20) && !PHI_COMPILER_IS_BELOW(GCC, 9, 0, 0)
    STATIC_REQUIRE(std::is_bounded_array<T>::value);
#endif
}

template <typename T>
void test_is_bounded_array()
{
    test_is_bounded_array_impl<T>();
    test_is_bounded_array_impl<const T>();
    test_is_bounded_array_impl<volatile T>();
    test_is_bounded_array_impl<const volatile T>();
}

template <typename T>
void test_is_not_bounded_array_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_bounded_array<T>::value);
    STATIC_REQUIRE(phi::is_not_bounded_array<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_bounded_array_v<T>);
    STATIC_REQUIRE(phi::is_not_bounded_array_v<T>);
#endif

// Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(20) && !PHI_COMPILER_IS_BELOW(GCC, 9, 0, 0)
    STATIC_REQUIRE_FALSE(std::is_bounded_array<T>::value);
#endif
}

template <typename T>
void test_is_not_bounded_array()
{
    test_is_not_bounded_array_impl<T>();
    test_is_not_bounded_array_impl<const T>();
    test_is_not_bounded_array_impl<volatile T>();
    test_is_not_bounded_array_impl<const volatile T>();
}

class A
{};

TEST_CASE("is_bounded_array")
{
    test_is_not_bounded_array<void>();
    test_is_not_bounded_array<phi::nullptr_t>();
    test_is_not_bounded_array<bool>();
    test_is_not_bounded_array<char>();
    test_is_not_bounded_array<signed char>();
    test_is_not_bounded_array<unsigned char>();
    test_is_not_bounded_array<short>();
    test_is_not_bounded_array<unsigned short>();
    test_is_not_bounded_array<int>();
    test_is_not_bounded_array<unsigned int>();
    test_is_not_bounded_array<long>();
    test_is_not_bounded_array<unsigned long>();
    test_is_not_bounded_array<long long>();
    test_is_not_bounded_array<unsigned long long>();
    test_is_not_bounded_array<float>();
    test_is_not_bounded_array<double>();
    test_is_not_bounded_array<long double>();
    test_is_not_bounded_array<char8_t>();
    test_is_not_bounded_array<char16_t>();
    test_is_not_bounded_array<char32_t>();
    test_is_not_bounded_array<wchar_t>();

    test_is_not_bounded_array<phi::boolean>();
    test_is_not_bounded_array<phi::integer<signed char>>();
    test_is_not_bounded_array<phi::integer<unsigned char>>();
    test_is_not_bounded_array<phi::integer<short>>();
    test_is_not_bounded_array<phi::integer<unsigned short>>();
    test_is_not_bounded_array<phi::integer<int>>();
    test_is_not_bounded_array<phi::integer<unsigned int>>();
    test_is_not_bounded_array<phi::integer<long>>();
    test_is_not_bounded_array<phi::integer<unsigned long>>();
    test_is_not_bounded_array<phi::integer<long long>>();
    test_is_not_bounded_array<phi::integer<unsigned long long>>();
    test_is_not_bounded_array<phi::floating_point<float>>();
    test_is_not_bounded_array<phi::floating_point<double>>();
    test_is_not_bounded_array<phi::floating_point<long double>>();

    test_is_not_bounded_array<std::vector<int>>();
    test_is_not_bounded_array<phi::scope_ptr<int>>();

    test_is_not_bounded_array<int&>();
    test_is_not_bounded_array<const int&>();
    test_is_not_bounded_array<volatile int&>();
    test_is_not_bounded_array<const volatile int&>();
    test_is_not_bounded_array<int&&>();
    test_is_not_bounded_array<const int&&>();
    test_is_not_bounded_array<volatile int&&>();
    test_is_not_bounded_array<const volatile int&&>();
    test_is_not_bounded_array<int*>();
    test_is_not_bounded_array<const int*>();
    test_is_not_bounded_array<volatile int*>();
    test_is_not_bounded_array<const volatile int*>();
    test_is_not_bounded_array<int**>();
    test_is_not_bounded_array<const int**>();
    test_is_not_bounded_array<volatile int**>();
    test_is_not_bounded_array<const volatile int**>();
    test_is_not_bounded_array<int*&>();
    test_is_not_bounded_array<const int*&>();
    test_is_not_bounded_array<volatile int*&>();
    test_is_not_bounded_array<const volatile int*&>();
    test_is_not_bounded_array<int*&&>();
    test_is_not_bounded_array<const int*&&>();
    test_is_not_bounded_array<volatile int*&&>();
    test_is_not_bounded_array<const volatile int*&&>();
    test_is_not_bounded_array<void*>();
    test_is_bounded_array<char[3]>();
    test_is_not_bounded_array<char[]>();
    test_is_bounded_array<char* [3]>();
    test_is_not_bounded_array<char*[]>();
    test_is_not_bounded_array<int(*)[3]>();
    test_is_not_bounded_array<int(*)[]>();
    test_is_not_bounded_array<int(&)[3]>();
    test_is_not_bounded_array<int(&)[]>();
    test_is_not_bounded_array<int(&&)[3]>();
    test_is_not_bounded_array<int(&&)[]>();
    test_is_bounded_array<char[3][2]>();
    test_is_not_bounded_array<char[][2]>();
    test_is_bounded_array<char* [3][2]>();
    test_is_not_bounded_array<char*[][2]>();
    test_is_not_bounded_array<int(*)[3][2]>();
    test_is_not_bounded_array<int(*)[][2]>();
    test_is_not_bounded_array<int(&)[3][2]>();
    test_is_not_bounded_array<int(&)[][2]>();
    test_is_not_bounded_array<int(&&)[3][2]>();
    test_is_not_bounded_array<int(&&)[][2]>();
    test_is_not_bounded_array<Class>();
    test_is_not_bounded_array<Class[]>();
    test_is_bounded_array<Class[2]>();
    test_is_not_bounded_array<Template<void>>();
    test_is_not_bounded_array<Template<int>>();
    test_is_not_bounded_array<Template<Class>>();
    test_is_not_bounded_array<Template<incomplete_type>>();
    test_is_not_bounded_array<VariadicTemplate<>>();
    test_is_not_bounded_array<VariadicTemplate<void>>();
    test_is_not_bounded_array<VariadicTemplate<int>>();
    test_is_not_bounded_array<VariadicTemplate<Class>>();
    test_is_not_bounded_array<VariadicTemplate<incomplete_type>>();
    test_is_not_bounded_array<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_bounded_array<PublicDerviedFromTemplate<Base>>();
    test_is_not_bounded_array<PublicDerviedFromTemplate<Derived>>();
    test_is_not_bounded_array<PublicDerviedFromTemplate<Class>>();
    test_is_not_bounded_array<PrivateDerviedFromTemplate<Base>>();
    test_is_not_bounded_array<PrivateDerviedFromTemplate<Derived>>();
    test_is_not_bounded_array<PrivateDerviedFromTemplate<Class>>();
    test_is_not_bounded_array<ProtectedDerviedFromTemplate<Base>>();
    test_is_not_bounded_array<ProtectedDerviedFromTemplate<Derived>>();
    test_is_not_bounded_array<ProtectedDerviedFromTemplate<Class>>();
    test_is_not_bounded_array<Union>();
    test_is_not_bounded_array<NonEmptyUnion>();
    test_is_not_bounded_array<Empty>();
    test_is_not_bounded_array<NotEmpty>();
    test_is_not_bounded_array<bit_zero>();
    test_is_not_bounded_array<bit_one>();
    test_is_not_bounded_array<Base>();
    test_is_not_bounded_array<Derived>();
    test_is_not_bounded_array<Abstract>();
    test_is_not_bounded_array<PublicAbstract>();
    test_is_not_bounded_array<PrivateAbstract>();
    test_is_not_bounded_array<ProtectedAbstract>();
    test_is_not_bounded_array<AbstractTemplate<int>>();
    test_is_not_bounded_array<AbstractTemplate<double>>();
    test_is_not_bounded_array<AbstractTemplate<Class>>();
    test_is_not_bounded_array<AbstractTemplate<incomplete_type>>();
    test_is_not_bounded_array<Final>();
    test_is_not_bounded_array<PublicDestructor>();
    test_is_not_bounded_array<ProtectedDestructor>();
    test_is_not_bounded_array<PrivateDestructor>();
    test_is_not_bounded_array<VirtualPublicDestructor>();
    test_is_not_bounded_array<VirtualProtectedDestructor>();
    test_is_not_bounded_array<VirtualPrivateDestructor>();
    test_is_not_bounded_array<PurePublicDestructor>();
    test_is_not_bounded_array<PureProtectedDestructor>();
    test_is_not_bounded_array<PurePrivateDestructor>();
    test_is_not_bounded_array<DeletedPublicDestructor>();
    test_is_not_bounded_array<DeletedProtectedDestructor>();
    test_is_not_bounded_array<DeletedPrivateDestructor>();
    test_is_not_bounded_array<DeletedVirtualPublicDestructor>();
    test_is_not_bounded_array<DeletedVirtualProtectedDestructor>();
    test_is_not_bounded_array<DeletedVirtualPrivateDestructor>();
    test_is_not_bounded_array<Enum>();
    test_is_not_bounded_array<EnumSigned>();
    test_is_not_bounded_array<EnumUnsigned>();
    test_is_not_bounded_array<EnumClass>();
    test_is_not_bounded_array<EnumStruct>();
    test_is_not_bounded_array<Function>();
    test_is_not_bounded_array<FunctionPtr>();
    test_is_not_bounded_array<MemberObjectPtr>();
    test_is_not_bounded_array<MemberFunctionPtr>();
    test_is_not_bounded_array<incomplete_type>();
    test_is_not_bounded_array<IncompleteTemplate<void>>();
    test_is_not_bounded_array<IncompleteTemplate<int>>();
    test_is_not_bounded_array<IncompleteTemplate<Class>>();
    test_is_not_bounded_array<IncompleteTemplate<incomplete_type>>();
    test_is_not_bounded_array<IncompleteVariadicTemplate<>>();
    test_is_not_bounded_array<IncompleteVariadicTemplate<void>>();
    test_is_not_bounded_array<IncompleteVariadicTemplate<int>>();
    test_is_not_bounded_array<IncompleteVariadicTemplate<Class>>();
    test_is_not_bounded_array<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_not_bounded_array<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_bounded_array<int Class::*>();
    test_is_not_bounded_array<float Class::*>();
    test_is_not_bounded_array<void * Class::*>();
    test_is_not_bounded_array<int * Class::*>();
    test_is_not_bounded_array<int Class::*&>();
    test_is_not_bounded_array<float Class::*&>();
    test_is_not_bounded_array<void * Class::*&>();
    test_is_not_bounded_array<int * Class::*&>();
    test_is_not_bounded_array<int Class::*&&>();
    test_is_not_bounded_array<float Class::*&&>();
    test_is_not_bounded_array<void * Class::*&&>();
    test_is_not_bounded_array<int * Class::*&&>();
    test_is_not_bounded_array<int Class::*const>();
    test_is_not_bounded_array<float Class::*const>();
    test_is_not_bounded_array<void * Class::*const>();
    test_is_not_bounded_array<int Class::*const&>();
    test_is_not_bounded_array<float Class::*const&>();
    test_is_not_bounded_array<void * Class::*const&>();
    test_is_not_bounded_array<int Class::*const&&>();
    test_is_not_bounded_array<float Class::*const&&>();
    test_is_not_bounded_array<void * Class::*const&&>();
    test_is_not_bounded_array<int Class::*volatile>();
    test_is_not_bounded_array<float Class::*volatile>();
    test_is_not_bounded_array<void * Class::*volatile>();
    test_is_not_bounded_array<int Class::*volatile&>();
    test_is_not_bounded_array<float Class::*volatile&>();
    test_is_not_bounded_array<void * Class::*volatile&>();
    test_is_not_bounded_array<int Class::*volatile&&>();
    test_is_not_bounded_array<float Class::*volatile&&>();
    test_is_not_bounded_array<void * Class::*volatile&&>();
    test_is_not_bounded_array<int Class::*const volatile>();
    test_is_not_bounded_array<float Class::*const volatile>();
    test_is_not_bounded_array<void * Class::*const volatile>();
    test_is_not_bounded_array<int Class::*const volatile&>();
    test_is_not_bounded_array<float Class::*const volatile&>();
    test_is_not_bounded_array<void * Class::*const volatile&>();
    test_is_not_bounded_array<int Class::*const volatile&&>();
    test_is_not_bounded_array<float Class::*const volatile&&>();
    test_is_not_bounded_array<void * Class::*const volatile&&>();
    test_is_not_bounded_array<NonCopyable>();
    test_is_not_bounded_array<NonMoveable>();
    test_is_not_bounded_array<NonConstructible>();
    test_is_not_bounded_array<Tracked>();
    test_is_not_bounded_array<TrapConstructible>();
    test_is_not_bounded_array<TrapImplicitConversion>();
    test_is_not_bounded_array<TrapComma>();
    test_is_not_bounded_array<TrapCall>();
    test_is_not_bounded_array<TrapSelfAssign>();
    test_is_not_bounded_array<TrapDeref>();
    test_is_not_bounded_array<TrapArraySubscript>();

    test_is_not_bounded_array<void()>();
    test_is_not_bounded_array<void()&>();
    test_is_not_bounded_array<void() &&>();
    test_is_not_bounded_array<void() const>();
    test_is_not_bounded_array<void() const&>();
    test_is_not_bounded_array<void() const&&>();
    test_is_not_bounded_array<void() volatile>();
    test_is_not_bounded_array<void() volatile&>();
    test_is_not_bounded_array<void() volatile&&>();
    test_is_not_bounded_array<void() const volatile>();
    test_is_not_bounded_array<void() const volatile&>();
    test_is_not_bounded_array<void() const volatile&&>();
    test_is_not_bounded_array<void() noexcept>();
    test_is_not_bounded_array<void()& noexcept>();
    test_is_not_bounded_array<void()&& noexcept>();
    test_is_not_bounded_array<void() const noexcept>();
    test_is_not_bounded_array<void() const& noexcept>();
    test_is_not_bounded_array<void() const&& noexcept>();
    test_is_not_bounded_array<void() volatile noexcept>();
    test_is_not_bounded_array<void() volatile& noexcept>();
    test_is_not_bounded_array<void() volatile&& noexcept>();
    test_is_not_bounded_array<void() const volatile noexcept>();
    test_is_not_bounded_array<void() const volatile& noexcept>();
    test_is_not_bounded_array<void() const volatile&& noexcept>();

    test_is_not_bounded_array<void(int)>();
    test_is_not_bounded_array<void(int)&>();
    test_is_not_bounded_array<void(int) &&>();
    test_is_not_bounded_array<void(int) const>();
    test_is_not_bounded_array<void(int) const&>();
    test_is_not_bounded_array<void(int) const&&>();
    test_is_not_bounded_array<void(int) volatile>();
    test_is_not_bounded_array<void(int) volatile&>();
    test_is_not_bounded_array<void(int) volatile&&>();
    test_is_not_bounded_array<void(int) const volatile>();
    test_is_not_bounded_array<void(int) const volatile&>();
    test_is_not_bounded_array<void(int) const volatile&&>();
    test_is_not_bounded_array<void(int) noexcept>();
    test_is_not_bounded_array<void(int)& noexcept>();
    test_is_not_bounded_array<void(int)&& noexcept>();
    test_is_not_bounded_array<void(int) const noexcept>();
    test_is_not_bounded_array<void(int) const& noexcept>();
    test_is_not_bounded_array<void(int) const&& noexcept>();
    test_is_not_bounded_array<void(int) volatile noexcept>();
    test_is_not_bounded_array<void(int) volatile& noexcept>();
    test_is_not_bounded_array<void(int) volatile&& noexcept>();
    test_is_not_bounded_array<void(int) const volatile noexcept>();
    test_is_not_bounded_array<void(int) const volatile& noexcept>();
    test_is_not_bounded_array<void(int) const volatile&& noexcept>();

    test_is_not_bounded_array<void(...)>();
    test_is_not_bounded_array<void(...)&>();
    test_is_not_bounded_array<void(...) &&>();
    test_is_not_bounded_array<void(...) const>();
    test_is_not_bounded_array<void(...) const&>();
    test_is_not_bounded_array<void(...) const&&>();
    test_is_not_bounded_array<void(...) volatile>();
    test_is_not_bounded_array<void(...) volatile&>();
    test_is_not_bounded_array<void(...) volatile&&>();
    test_is_not_bounded_array<void(...) const volatile>();
    test_is_not_bounded_array<void(...) const volatile&>();
    test_is_not_bounded_array<void(...) const volatile&&>();
    test_is_not_bounded_array<void(...) noexcept>();
    test_is_not_bounded_array<void(...)& noexcept>();
    test_is_not_bounded_array<void(...)&& noexcept>();
    test_is_not_bounded_array<void(...) const noexcept>();
    test_is_not_bounded_array<void(...) const& noexcept>();
    test_is_not_bounded_array<void(...) const&& noexcept>();
    test_is_not_bounded_array<void(...) volatile noexcept>();
    test_is_not_bounded_array<void(...) volatile& noexcept>();
    test_is_not_bounded_array<void(...) volatile&& noexcept>();
    test_is_not_bounded_array<void(...) const volatile noexcept>();
    test_is_not_bounded_array<void(...) const volatile& noexcept>();
    test_is_not_bounded_array<void(...) const volatile&& noexcept>();

    test_is_not_bounded_array<void(int, ...)>();
    test_is_not_bounded_array<void(int, ...)&>();
    test_is_not_bounded_array<void(int, ...) &&>();
    test_is_not_bounded_array<void(int, ...) const>();
    test_is_not_bounded_array<void(int, ...) const&>();
    test_is_not_bounded_array<void(int, ...) const&&>();
    test_is_not_bounded_array<void(int, ...) volatile>();
    test_is_not_bounded_array<void(int, ...) volatile&>();
    test_is_not_bounded_array<void(int, ...) volatile&&>();
    test_is_not_bounded_array<void(int, ...) const volatile>();
    test_is_not_bounded_array<void(int, ...) const volatile&>();
    test_is_not_bounded_array<void(int, ...) const volatile&&>();
    test_is_not_bounded_array<void(int, ...) noexcept>();
    test_is_not_bounded_array<void(int, ...)& noexcept>();
    test_is_not_bounded_array<void(int, ...)&& noexcept>();
    test_is_not_bounded_array<void(int, ...) const noexcept>();
    test_is_not_bounded_array<void(int, ...) const& noexcept>();
    test_is_not_bounded_array<void(int, ...) const&& noexcept>();
    test_is_not_bounded_array<void(int, ...) volatile noexcept>();
    test_is_not_bounded_array<void(int, ...) volatile& noexcept>();
    test_is_not_bounded_array<void(int, ...) volatile&& noexcept>();
    test_is_not_bounded_array<void(int, ...) const volatile noexcept>();
    test_is_not_bounded_array<void(int, ...) const volatile& noexcept>();
    test_is_not_bounded_array<void(int, ...) const volatile&& noexcept>();

    test_is_not_bounded_array<int()>();
    test_is_not_bounded_array<int()&>();
    test_is_not_bounded_array<int() &&>();
    test_is_not_bounded_array<int() const>();
    test_is_not_bounded_array<int() const&>();
    test_is_not_bounded_array<int() const&&>();
    test_is_not_bounded_array<int() volatile>();
    test_is_not_bounded_array<int() volatile&>();
    test_is_not_bounded_array<int() volatile&&>();
    test_is_not_bounded_array<int() const volatile>();
    test_is_not_bounded_array<int() const volatile&>();
    test_is_not_bounded_array<int() const volatile&&>();
    test_is_not_bounded_array<int() noexcept>();
    test_is_not_bounded_array<int()& noexcept>();
    test_is_not_bounded_array<int()&& noexcept>();
    test_is_not_bounded_array<int() const noexcept>();
    test_is_not_bounded_array<int() const& noexcept>();
    test_is_not_bounded_array<int() const&& noexcept>();
    test_is_not_bounded_array<int() volatile noexcept>();
    test_is_not_bounded_array<int() volatile& noexcept>();
    test_is_not_bounded_array<int() volatile&& noexcept>();
    test_is_not_bounded_array<int() const volatile noexcept>();
    test_is_not_bounded_array<int() const volatile& noexcept>();
    test_is_not_bounded_array<int() const volatile&& noexcept>();

    test_is_not_bounded_array<int(int)>();
    test_is_not_bounded_array<int(int)&>();
    test_is_not_bounded_array<int(int) &&>();
    test_is_not_bounded_array<int(int) const>();
    test_is_not_bounded_array<int(int) const&>();
    test_is_not_bounded_array<int(int) const&&>();
    test_is_not_bounded_array<int(int) volatile>();
    test_is_not_bounded_array<int(int) volatile&>();
    test_is_not_bounded_array<int(int) volatile&&>();
    test_is_not_bounded_array<int(int) const volatile>();
    test_is_not_bounded_array<int(int) const volatile&>();
    test_is_not_bounded_array<int(int) const volatile&&>();
    test_is_not_bounded_array<int(int) noexcept>();
    test_is_not_bounded_array<int(int)& noexcept>();
    test_is_not_bounded_array<int(int)&& noexcept>();
    test_is_not_bounded_array<int(int) const noexcept>();
    test_is_not_bounded_array<int(int) const& noexcept>();
    test_is_not_bounded_array<int(int) const&& noexcept>();
    test_is_not_bounded_array<int(int) volatile noexcept>();
    test_is_not_bounded_array<int(int) volatile& noexcept>();
    test_is_not_bounded_array<int(int) volatile&& noexcept>();
    test_is_not_bounded_array<int(int) const volatile noexcept>();
    test_is_not_bounded_array<int(int) const volatile& noexcept>();
    test_is_not_bounded_array<int(int) const volatile&& noexcept>();

    test_is_not_bounded_array<int(...)>();
    test_is_not_bounded_array<int(...)&>();
    test_is_not_bounded_array<int(...) &&>();
    test_is_not_bounded_array<int(...) const>();
    test_is_not_bounded_array<int(...) const&>();
    test_is_not_bounded_array<int(...) const&&>();
    test_is_not_bounded_array<int(...) volatile>();
    test_is_not_bounded_array<int(...) volatile&>();
    test_is_not_bounded_array<int(...) volatile&&>();
    test_is_not_bounded_array<int(...) const volatile>();
    test_is_not_bounded_array<int(...) const volatile&>();
    test_is_not_bounded_array<int(...) const volatile&&>();
    test_is_not_bounded_array<int(...) noexcept>();
    test_is_not_bounded_array<int(...)& noexcept>();
    test_is_not_bounded_array<int(...)&& noexcept>();
    test_is_not_bounded_array<int(...) const noexcept>();
    test_is_not_bounded_array<int(...) const& noexcept>();
    test_is_not_bounded_array<int(...) const&& noexcept>();
    test_is_not_bounded_array<int(...) volatile noexcept>();
    test_is_not_bounded_array<int(...) volatile& noexcept>();
    test_is_not_bounded_array<int(...) volatile&& noexcept>();
    test_is_not_bounded_array<int(...) const volatile noexcept>();
    test_is_not_bounded_array<int(...) const volatile& noexcept>();
    test_is_not_bounded_array<int(...) const volatile&& noexcept>();

    test_is_not_bounded_array<int(int, ...)>();
    test_is_not_bounded_array<int(int, ...)&>();
    test_is_not_bounded_array<int(int, ...) &&>();
    test_is_not_bounded_array<int(int, ...) const>();
    test_is_not_bounded_array<int(int, ...) const&>();
    test_is_not_bounded_array<int(int, ...) const&&>();
    test_is_not_bounded_array<int(int, ...) volatile>();
    test_is_not_bounded_array<int(int, ...) volatile&>();
    test_is_not_bounded_array<int(int, ...) volatile&&>();
    test_is_not_bounded_array<int(int, ...) const volatile>();
    test_is_not_bounded_array<int(int, ...) const volatile&>();
    test_is_not_bounded_array<int(int, ...) const volatile&&>();
    test_is_not_bounded_array<int(int, ...) noexcept>();
    test_is_not_bounded_array<int(int, ...)& noexcept>();
    test_is_not_bounded_array<int(int, ...)&& noexcept>();
    test_is_not_bounded_array<int(int, ...) const noexcept>();
    test_is_not_bounded_array<int(int, ...) const& noexcept>();
    test_is_not_bounded_array<int(int, ...) const&& noexcept>();
    test_is_not_bounded_array<int(int, ...) volatile noexcept>();
    test_is_not_bounded_array<int(int, ...) volatile& noexcept>();
    test_is_not_bounded_array<int(int, ...) volatile&& noexcept>();
    test_is_not_bounded_array<int(int, ...) const volatile noexcept>();
    test_is_not_bounded_array<int(int, ...) const volatile& noexcept>();
    test_is_not_bounded_array<int(int, ...) const volatile&& noexcept>();

    test_is_not_bounded_array<void (*)()>();
    test_is_not_bounded_array<void (*)() noexcept>();

    test_is_not_bounded_array<void (*)(int)>();
    test_is_not_bounded_array<void (*)(int) noexcept>();

    test_is_not_bounded_array<void (*)(...)>();
    test_is_not_bounded_array<void (*)(...) noexcept>();

    test_is_not_bounded_array<void (*)(int, ...)>();
    test_is_not_bounded_array<void (*)(int, ...) noexcept>();

    test_is_not_bounded_array<int (*)()>();
    test_is_not_bounded_array<int (*)() noexcept>();

    test_is_not_bounded_array<int (*)(int)>();
    test_is_not_bounded_array<int (*)(int) noexcept>();

    test_is_not_bounded_array<int (*)(...)>();
    test_is_not_bounded_array<int (*)(...) noexcept>();

    test_is_not_bounded_array<int (*)(int, ...)>();
    test_is_not_bounded_array<int (*)(int, ...) noexcept>();

    test_is_not_bounded_array<void (&)()>();
    test_is_not_bounded_array<void (&)() noexcept>();

    test_is_not_bounded_array<void (&)(int)>();
    test_is_not_bounded_array<void (&)(int) noexcept>();

    test_is_not_bounded_array<void (&)(...)>();
    test_is_not_bounded_array<void (&)(...) noexcept>();

    test_is_not_bounded_array<void (&)(int, ...)>();
    test_is_not_bounded_array<void (&)(int, ...) noexcept>();

    test_is_not_bounded_array<int (&)()>();
    test_is_not_bounded_array<int (&)() noexcept>();

    test_is_not_bounded_array<int (&)(int)>();
    test_is_not_bounded_array<int (&)(int) noexcept>();

    test_is_not_bounded_array<int (&)(...)>();
    test_is_not_bounded_array<int (&)(...) noexcept>();

    test_is_not_bounded_array<int (&)(int, ...)>();
    test_is_not_bounded_array<int (&)(int, ...) noexcept>();

    test_is_not_bounded_array<void(&&)()>();
    test_is_not_bounded_array<void(&&)() noexcept>();

    test_is_not_bounded_array<void(&&)(int)>();
    test_is_not_bounded_array<void(&&)(int) noexcept>();

    test_is_not_bounded_array<void(&&)(...)>();
    test_is_not_bounded_array<void(&&)(...) noexcept>();

    test_is_not_bounded_array<void(&&)(int, ...)>();
    test_is_not_bounded_array<void(&&)(int, ...) noexcept>();

    test_is_not_bounded_array<int(&&)()>();
    test_is_not_bounded_array<int(&&)() noexcept>();

    test_is_not_bounded_array<int(&&)(int)>();
    test_is_not_bounded_array<int(&&)(int) noexcept>();

    test_is_not_bounded_array<int(&&)(...)>();
    test_is_not_bounded_array<int(&&)(...) noexcept>();

    test_is_not_bounded_array<int(&&)(int, ...)>();
    test_is_not_bounded_array<int(&&)(int, ...) noexcept>();

    test_is_not_bounded_array<void (Class::*)()>();
    test_is_not_bounded_array<void (Class::*)()&>();
    test_is_not_bounded_array<void (Class::*)() &&>();
    test_is_not_bounded_array<void (Class::*)() const>();
    test_is_not_bounded_array<void (Class::*)() const&>();
    test_is_not_bounded_array<void (Class::*)() const&&>();
    test_is_not_bounded_array<void (Class::*)() noexcept>();
    test_is_not_bounded_array<void (Class::*)()& noexcept>();
    test_is_not_bounded_array<void (Class::*)()&& noexcept>();
    test_is_not_bounded_array<void (Class::*)() const noexcept>();
    test_is_not_bounded_array<void (Class::*)() const& noexcept>();
    test_is_not_bounded_array<void (Class::*)() const&& noexcept>();

    test_is_not_bounded_array<void (Class::*)(int)>();
    test_is_not_bounded_array<void (Class::*)(int)&>();
    test_is_not_bounded_array<void (Class::*)(int) &&>();
    test_is_not_bounded_array<void (Class::*)(int) const>();
    test_is_not_bounded_array<void (Class::*)(int) const&>();
    test_is_not_bounded_array<void (Class::*)(int) const&&>();
    test_is_not_bounded_array<void (Class::*)(int) noexcept>();
    test_is_not_bounded_array<void (Class::*)(int)& noexcept>();
    test_is_not_bounded_array<void (Class::*)(int)&& noexcept>();
    test_is_not_bounded_array<void (Class::*)(int) const noexcept>();
    test_is_not_bounded_array<void (Class::*)(int) const& noexcept>();
    test_is_not_bounded_array<void (Class::*)(int) const&& noexcept>();

    test_is_not_bounded_array<void (Class::*)(...)>();
    test_is_not_bounded_array<void (Class::*)(...)&>();
    test_is_not_bounded_array<void (Class::*)(...) &&>();
    test_is_not_bounded_array<void (Class::*)(...) const>();
    test_is_not_bounded_array<void (Class::*)(...) const&>();
    test_is_not_bounded_array<void (Class::*)(...) const&&>();
    test_is_not_bounded_array<void (Class::*)(...) noexcept>();
    test_is_not_bounded_array<void (Class::*)(...)& noexcept>();
    test_is_not_bounded_array<void (Class::*)(...)&& noexcept>();
    test_is_not_bounded_array<void (Class::*)(...) const noexcept>();
    test_is_not_bounded_array<void (Class::*)(...) const& noexcept>();
    test_is_not_bounded_array<void (Class::*)(...) const&& noexcept>();

    test_is_not_bounded_array<void (Class::*)(int, ...)>();
    test_is_not_bounded_array<void (Class::*)(int, ...)&>();
    test_is_not_bounded_array<void (Class::*)(int, ...) &&>();
    test_is_not_bounded_array<void (Class::*)(int, ...) const>();
    test_is_not_bounded_array<void (Class::*)(int, ...) const&>();
    test_is_not_bounded_array<void (Class::*)(int, ...) const&&>();
    test_is_not_bounded_array<void (Class::*)(int, ...) noexcept>();
    test_is_not_bounded_array<void (Class::*)(int, ...)& noexcept>();
    test_is_not_bounded_array<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_bounded_array<void (Class::*)(int, ...) const noexcept>();
    test_is_not_bounded_array<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_bounded_array<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_bounded_array<int (Class::*)()>();
    test_is_not_bounded_array<int (Class::*)()&>();
    test_is_not_bounded_array<int (Class::*)() &&>();
    test_is_not_bounded_array<int (Class::*)() const>();
    test_is_not_bounded_array<int (Class::*)() const&>();
    test_is_not_bounded_array<int (Class::*)() const&&>();
    test_is_not_bounded_array<int (Class::*)() noexcept>();
    test_is_not_bounded_array<int (Class::*)()& noexcept>();
    test_is_not_bounded_array<int (Class::*)()&& noexcept>();
    test_is_not_bounded_array<int (Class::*)() const noexcept>();
    test_is_not_bounded_array<int (Class::*)() const& noexcept>();
    test_is_not_bounded_array<int (Class::*)() const&& noexcept>();

    test_is_not_bounded_array<int (Class::*)(int)>();
    test_is_not_bounded_array<int (Class::*)(int)&>();
    test_is_not_bounded_array<int (Class::*)(int) &&>();
    test_is_not_bounded_array<int (Class::*)(int) const>();
    test_is_not_bounded_array<int (Class::*)(int) const&>();
    test_is_not_bounded_array<int (Class::*)(int) const&&>();
    test_is_not_bounded_array<int (Class::*)(int) noexcept>();
    test_is_not_bounded_array<int (Class::*)(int)& noexcept>();
    test_is_not_bounded_array<int (Class::*)(int)&& noexcept>();
    test_is_not_bounded_array<int (Class::*)(int) const noexcept>();
    test_is_not_bounded_array<int (Class::*)(int) const& noexcept>();
    test_is_not_bounded_array<int (Class::*)(int) const&& noexcept>();

    test_is_not_bounded_array<int (Class::*)(...)>();
    test_is_not_bounded_array<int (Class::*)(...)&>();
    test_is_not_bounded_array<int (Class::*)(...) &&>();
    test_is_not_bounded_array<int (Class::*)(...) const>();
    test_is_not_bounded_array<int (Class::*)(...) const&>();
    test_is_not_bounded_array<int (Class::*)(...) const&&>();
    test_is_not_bounded_array<int (Class::*)(...) noexcept>();
    test_is_not_bounded_array<int (Class::*)(...)& noexcept>();
    test_is_not_bounded_array<int (Class::*)(...)&& noexcept>();
    test_is_not_bounded_array<int (Class::*)(...) const noexcept>();
    test_is_not_bounded_array<int (Class::*)(...) const& noexcept>();
    test_is_not_bounded_array<int (Class::*)(...) const&& noexcept>();

    test_is_not_bounded_array<int (Class::*)(int, ...)>();
    test_is_not_bounded_array<int (Class::*)(int, ...)&>();
    test_is_not_bounded_array<int (Class::*)(int, ...) &&>();
    test_is_not_bounded_array<int (Class::*)(int, ...) const>();
    test_is_not_bounded_array<int (Class::*)(int, ...) const&>();
    test_is_not_bounded_array<int (Class::*)(int, ...) const&&>();
    test_is_not_bounded_array<int (Class::*)(int, ...) noexcept>();
    test_is_not_bounded_array<int (Class::*)(int, ...)& noexcept>();
    test_is_not_bounded_array<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_bounded_array<int (Class::*)(int, ...) const noexcept>();
    test_is_not_bounded_array<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_bounded_array<int (Class::*)(int, ...) const&& noexcept>();
}
