#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_unbounded_array.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_unbounded_array_impl()
{
    STATIC_REQUIRE(phi::is_unbounded_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_unbounded_array<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unbounded_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_unbounded_array_v<T>);
#endif

#if PHI_CPP_STANDARD_IS_ATLEAST(20) && !PHI_COMPILER_IS_BELOW(GCC, 9, 0, 0) &&                     \
        !PHI_COMPILER_IS_BELOW(EMCC, 1, 39, 0)
    STATIC_REQUIRE(std::is_unbounded_array<T>::value);
#endif
}

template <typename T>
void test_is_not_unbounded_array_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_unbounded_array<T>::value);
    STATIC_REQUIRE(phi::is_not_unbounded_array<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unbounded_array_v<T>);
    STATIC_REQUIRE(phi::is_not_unbounded_array_v<T>);
#endif

#if PHI_CPP_STANDARD_IS_ATLEAST(20) && !PHI_COMPILER_IS_BELOW(GCC, 9, 0, 0) &&                     \
        !PHI_COMPILER_IS_BELOW(EMCC, 1, 39, 0)
    STATIC_REQUIRE_FALSE(std::is_unbounded_array<T>::value);
#endif
}

template <typename T>
void test_is_unbounded_array()
{
    test_is_unbounded_array_impl<T>();
    test_is_unbounded_array_impl<const T>();
    test_is_unbounded_array_impl<volatile T>();
    test_is_unbounded_array_impl<const volatile T>();
}

template <typename T>
void test_is_not_unbounded_array()
{
    test_is_not_unbounded_array_impl<T>();
    test_is_not_unbounded_array_impl<const T>();
    test_is_not_unbounded_array_impl<volatile T>();
    test_is_not_unbounded_array_impl<const volatile T>();
}

class A
{};

TEST_CASE("is_unbounded_array")
{
    test_is_not_unbounded_array<void>();
    test_is_not_unbounded_array<phi::nullptr_t>();
    test_is_not_unbounded_array<bool>();
    test_is_not_unbounded_array<char>();
    test_is_not_unbounded_array<signed char>();
    test_is_not_unbounded_array<unsigned char>();
    test_is_not_unbounded_array<short>();
    test_is_not_unbounded_array<unsigned short>();
    test_is_not_unbounded_array<int>();
    test_is_not_unbounded_array<unsigned int>();
    test_is_not_unbounded_array<long>();
    test_is_not_unbounded_array<unsigned long>();
    test_is_not_unbounded_array<long long>();
    test_is_not_unbounded_array<unsigned long long>();
    test_is_not_unbounded_array<float>();
    test_is_not_unbounded_array<double>();
    test_is_not_unbounded_array<long double>();
    test_is_not_unbounded_array<char8_t>();
    test_is_not_unbounded_array<char16_t>();
    test_is_not_unbounded_array<char32_t>();
    test_is_not_unbounded_array<wchar_t>();

    test_is_not_unbounded_array<phi::boolean>();
    test_is_not_unbounded_array<phi::integer<signed char>>();
    test_is_not_unbounded_array<phi::integer<unsigned char>>();
    test_is_not_unbounded_array<phi::integer<short>>();
    test_is_not_unbounded_array<phi::integer<unsigned short>>();
    test_is_not_unbounded_array<phi::integer<int>>();
    test_is_not_unbounded_array<phi::integer<unsigned int>>();
    test_is_not_unbounded_array<phi::integer<long>>();
    test_is_not_unbounded_array<phi::integer<unsigned long>>();
    test_is_not_unbounded_array<phi::integer<long long>>();
    test_is_not_unbounded_array<phi::integer<unsigned long long>>();
    test_is_not_unbounded_array<phi::floating_point<float>>();
    test_is_not_unbounded_array<phi::floating_point<double>>();
    test_is_not_unbounded_array<phi::floating_point<long double>>();

    test_is_not_unbounded_array<std::vector<int>>();
    test_is_not_unbounded_array<phi::scope_ptr<int>>();

    test_is_not_unbounded_array<int&>();
    test_is_not_unbounded_array<const int&>();
    test_is_not_unbounded_array<volatile int&>();
    test_is_not_unbounded_array<const volatile int&>();
    test_is_not_unbounded_array<int&&>();
    test_is_not_unbounded_array<const int&&>();
    test_is_not_unbounded_array<volatile int&&>();
    test_is_not_unbounded_array<const volatile int&&>();
    test_is_not_unbounded_array<int*>();
    test_is_not_unbounded_array<const int*>();
    test_is_not_unbounded_array<volatile int*>();
    test_is_not_unbounded_array<const volatile int*>();
    test_is_not_unbounded_array<int**>();
    test_is_not_unbounded_array<const int**>();
    test_is_not_unbounded_array<volatile int**>();
    test_is_not_unbounded_array<const volatile int**>();
    test_is_not_unbounded_array<int*&>();
    test_is_not_unbounded_array<const int*&>();
    test_is_not_unbounded_array<volatile int*&>();
    test_is_not_unbounded_array<const volatile int*&>();
    test_is_not_unbounded_array<int*&&>();
    test_is_not_unbounded_array<const int*&&>();
    test_is_not_unbounded_array<volatile int*&&>();
    test_is_not_unbounded_array<const volatile int*&&>();
    test_is_not_unbounded_array<void*>();
    test_is_not_unbounded_array<char[3]>();
    test_is_unbounded_array<char[]>();
    test_is_not_unbounded_array<char* [3]>();
    test_is_unbounded_array<char*[]>();
    test_is_not_unbounded_array<int(*)[3]>();
    test_is_not_unbounded_array<int(*)[]>();
    test_is_not_unbounded_array<int(&)[3]>();
    test_is_not_unbounded_array<int(&)[]>();
    test_is_not_unbounded_array<int(&&)[3]>();
    test_is_not_unbounded_array<int(&&)[]>();
    test_is_not_unbounded_array<char[3][2]>();
    test_is_unbounded_array<char[][2]>();
    test_is_not_unbounded_array<char* [3][2]>();
    test_is_unbounded_array<char*[][2]>();
    test_is_not_unbounded_array<int(*)[3][2]>();
    test_is_not_unbounded_array<int(*)[][2]>();
    test_is_not_unbounded_array<int(&)[3][2]>();
    test_is_not_unbounded_array<int(&)[][2]>();
    test_is_not_unbounded_array<int(&&)[3][2]>();
    test_is_not_unbounded_array<int(&&)[][2]>();
    test_is_not_unbounded_array<Class>();
    test_is_unbounded_array<Class[]>();
    test_is_not_unbounded_array<Class[2]>();
    test_is_not_unbounded_array<Template<void>>();
    test_is_not_unbounded_array<Template<int>>();
    test_is_not_unbounded_array<Template<Class>>();
    test_is_not_unbounded_array<Template<IncompleteType>>();
    test_is_not_unbounded_array<VariadicTemplate<>>();
    test_is_not_unbounded_array<VariadicTemplate<void>>();
    test_is_not_unbounded_array<VariadicTemplate<int>>();
    test_is_not_unbounded_array<VariadicTemplate<Class>>();
    test_is_not_unbounded_array<VariadicTemplate<IncompleteType>>();
    test_is_not_unbounded_array<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_unbounded_array<PublicDerivedFromTemplate<Base>>();
    test_is_not_unbounded_array<PublicDerivedFromTemplate<Derived>>();
    test_is_not_unbounded_array<PublicDerivedFromTemplate<Class>>();
    test_is_not_unbounded_array<PrivateDerivedFromTemplate<Base>>();
    test_is_not_unbounded_array<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_unbounded_array<PrivateDerivedFromTemplate<Class>>();
    test_is_not_unbounded_array<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_unbounded_array<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_unbounded_array<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_unbounded_array<Union>();
    test_is_not_unbounded_array<NonEmptyUnion>();
    test_is_not_unbounded_array<Empty>();
    test_is_not_unbounded_array<NotEmpty>();
    test_is_not_unbounded_array<BitZero>();
    test_is_not_unbounded_array<BitOne>();
    test_is_not_unbounded_array<Base>();
    test_is_not_unbounded_array<Derived>();
    test_is_not_unbounded_array<Abstract>();
    test_is_not_unbounded_array<PublicAbstract>();
    test_is_not_unbounded_array<PrivateAbstract>();
    test_is_not_unbounded_array<ProtectedAbstract>();
    test_is_not_unbounded_array<AbstractTemplate<int>>();
    test_is_not_unbounded_array<AbstractTemplate<double>>();
    test_is_not_unbounded_array<AbstractTemplate<Class>>();
    test_is_not_unbounded_array<AbstractTemplate<IncompleteType>>();
    test_is_not_unbounded_array<Final>();
    test_is_not_unbounded_array<PublicDestructor>();
    test_is_not_unbounded_array<ProtectedDestructor>();
    test_is_not_unbounded_array<PrivateDestructor>();
    test_is_not_unbounded_array<VirtualPublicDestructor>();
    test_is_not_unbounded_array<VirtualProtectedDestructor>();
    test_is_not_unbounded_array<VirtualPrivateDestructor>();
    test_is_not_unbounded_array<PurePublicDestructor>();
    test_is_not_unbounded_array<PureProtectedDestructor>();
    test_is_not_unbounded_array<PurePrivateDestructor>();
    test_is_not_unbounded_array<DeletedPublicDestructor>();
    test_is_not_unbounded_array<DeletedProtectedDestructor>();
    test_is_not_unbounded_array<DeletedPrivateDestructor>();
    test_is_not_unbounded_array<DeletedVirtualPublicDestructor>();
    test_is_not_unbounded_array<DeletedVirtualProtectedDestructor>();
    test_is_not_unbounded_array<DeletedVirtualPrivateDestructor>();
    test_is_not_unbounded_array<Enum>();
    test_is_not_unbounded_array<EnumSigned>();
    test_is_not_unbounded_array<EnumUnsigned>();
    test_is_not_unbounded_array<EnumClass>();
    test_is_not_unbounded_array<EnumStruct>();
    test_is_not_unbounded_array<Function>();
    test_is_not_unbounded_array<FunctionPtr>();
    test_is_not_unbounded_array<MemberObjectPtr>();
    test_is_not_unbounded_array<MemberFunctionPtr>();
    test_is_not_unbounded_array<IncompleteType>();
    test_is_not_unbounded_array<IncompleteTemplate<void>>();
    test_is_not_unbounded_array<IncompleteTemplate<int>>();
    test_is_not_unbounded_array<IncompleteTemplate<Class>>();
    test_is_not_unbounded_array<IncompleteTemplate<IncompleteType>>();
    test_is_not_unbounded_array<IncompleteVariadicTemplate<>>();
    test_is_not_unbounded_array<IncompleteVariadicTemplate<void>>();
    test_is_not_unbounded_array<IncompleteVariadicTemplate<int>>();
    test_is_not_unbounded_array<IncompleteVariadicTemplate<Class>>();
    test_is_not_unbounded_array<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_unbounded_array<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_unbounded_array<int Class::*>();
    test_is_not_unbounded_array<float Class::*>();
    test_is_not_unbounded_array<void * Class::*>();
    test_is_not_unbounded_array<int * Class::*>();
    test_is_not_unbounded_array<int Class::*&>();
    test_is_not_unbounded_array<float Class::*&>();
    test_is_not_unbounded_array<void * Class::*&>();
    test_is_not_unbounded_array<int * Class::*&>();
    test_is_not_unbounded_array<int Class::*&&>();
    test_is_not_unbounded_array<float Class::*&&>();
    test_is_not_unbounded_array<void * Class::*&&>();
    test_is_not_unbounded_array<int * Class::*&&>();
    test_is_not_unbounded_array<int Class::*const>();
    test_is_not_unbounded_array<float Class::*const>();
    test_is_not_unbounded_array<void * Class::*const>();
    test_is_not_unbounded_array<int Class::*const&>();
    test_is_not_unbounded_array<float Class::*const&>();
    test_is_not_unbounded_array<void * Class::*const&>();
    test_is_not_unbounded_array<int Class::*const&&>();
    test_is_not_unbounded_array<float Class::*const&&>();
    test_is_not_unbounded_array<void * Class::*const&&>();
    test_is_not_unbounded_array<int Class::*volatile>();
    test_is_not_unbounded_array<float Class::*volatile>();
    test_is_not_unbounded_array<void * Class::*volatile>();
    test_is_not_unbounded_array<int Class::*volatile&>();
    test_is_not_unbounded_array<float Class::*volatile&>();
    test_is_not_unbounded_array<void * Class::*volatile&>();
    test_is_not_unbounded_array<int Class::*volatile&&>();
    test_is_not_unbounded_array<float Class::*volatile&&>();
    test_is_not_unbounded_array<void * Class::*volatile&&>();
    test_is_not_unbounded_array<int Class::*const volatile>();
    test_is_not_unbounded_array<float Class::*const volatile>();
    test_is_not_unbounded_array<void * Class::*const volatile>();
    test_is_not_unbounded_array<int Class::*const volatile&>();
    test_is_not_unbounded_array<float Class::*const volatile&>();
    test_is_not_unbounded_array<void * Class::*const volatile&>();
    test_is_not_unbounded_array<int Class::*const volatile&&>();
    test_is_not_unbounded_array<float Class::*const volatile&&>();
    test_is_not_unbounded_array<void * Class::*const volatile&&>();
    test_is_not_unbounded_array<NonCopyable>();
    test_is_not_unbounded_array<NonMoveable>();
    test_is_not_unbounded_array<NonConstructible>();
    test_is_not_unbounded_array<Tracked>();
    test_is_not_unbounded_array<TrapConstructible>();
    test_is_not_unbounded_array<TrapImplicitConversion>();
    test_is_not_unbounded_array<TrapComma>();
    test_is_not_unbounded_array<TrapCall>();
    test_is_not_unbounded_array<TrapSelfAssign>();
    test_is_not_unbounded_array<TrapDeref>();
    test_is_not_unbounded_array<TrapArraySubscript>();

    test_is_not_unbounded_array<void()>();
    test_is_not_unbounded_array<void()&>();
    test_is_not_unbounded_array<void() &&>();
    test_is_not_unbounded_array<void() const>();
    test_is_not_unbounded_array<void() const&>();
    test_is_not_unbounded_array<void() const&&>();
    test_is_not_unbounded_array<void() volatile>();
    test_is_not_unbounded_array<void() volatile&>();
    test_is_not_unbounded_array<void() volatile&&>();
    test_is_not_unbounded_array<void() const volatile>();
    test_is_not_unbounded_array<void() const volatile&>();
    test_is_not_unbounded_array<void() const volatile&&>();
    test_is_not_unbounded_array<void() noexcept>();
    test_is_not_unbounded_array<void()& noexcept>();
    test_is_not_unbounded_array<void()&& noexcept>();
    test_is_not_unbounded_array<void() const noexcept>();
    test_is_not_unbounded_array<void() const& noexcept>();
    test_is_not_unbounded_array<void() const&& noexcept>();
    test_is_not_unbounded_array<void() volatile noexcept>();
    test_is_not_unbounded_array<void() volatile& noexcept>();
    test_is_not_unbounded_array<void() volatile&& noexcept>();
    test_is_not_unbounded_array<void() const volatile noexcept>();
    test_is_not_unbounded_array<void() const volatile& noexcept>();
    test_is_not_unbounded_array<void() const volatile&& noexcept>();

    test_is_not_unbounded_array<void(int)>();
    test_is_not_unbounded_array<void(int)&>();
    test_is_not_unbounded_array<void(int) &&>();
    test_is_not_unbounded_array<void(int) const>();
    test_is_not_unbounded_array<void(int) const&>();
    test_is_not_unbounded_array<void(int) const&&>();
    test_is_not_unbounded_array<void(int) volatile>();
    test_is_not_unbounded_array<void(int) volatile&>();
    test_is_not_unbounded_array<void(int) volatile&&>();
    test_is_not_unbounded_array<void(int) const volatile>();
    test_is_not_unbounded_array<void(int) const volatile&>();
    test_is_not_unbounded_array<void(int) const volatile&&>();
    test_is_not_unbounded_array<void(int) noexcept>();
    test_is_not_unbounded_array<void(int)& noexcept>();
    test_is_not_unbounded_array<void(int)&& noexcept>();
    test_is_not_unbounded_array<void(int) const noexcept>();
    test_is_not_unbounded_array<void(int) const& noexcept>();
    test_is_not_unbounded_array<void(int) const&& noexcept>();
    test_is_not_unbounded_array<void(int) volatile noexcept>();
    test_is_not_unbounded_array<void(int) volatile& noexcept>();
    test_is_not_unbounded_array<void(int) volatile&& noexcept>();
    test_is_not_unbounded_array<void(int) const volatile noexcept>();
    test_is_not_unbounded_array<void(int) const volatile& noexcept>();
    test_is_not_unbounded_array<void(int) const volatile&& noexcept>();

    test_is_not_unbounded_array<void(...)>();
    test_is_not_unbounded_array<void(...)&>();
    test_is_not_unbounded_array<void(...) &&>();
    test_is_not_unbounded_array<void(...) const>();
    test_is_not_unbounded_array<void(...) const&>();
    test_is_not_unbounded_array<void(...) const&&>();
    test_is_not_unbounded_array<void(...) volatile>();
    test_is_not_unbounded_array<void(...) volatile&>();
    test_is_not_unbounded_array<void(...) volatile&&>();
    test_is_not_unbounded_array<void(...) const volatile>();
    test_is_not_unbounded_array<void(...) const volatile&>();
    test_is_not_unbounded_array<void(...) const volatile&&>();
    test_is_not_unbounded_array<void(...) noexcept>();
    test_is_not_unbounded_array<void(...)& noexcept>();
    test_is_not_unbounded_array<void(...)&& noexcept>();
    test_is_not_unbounded_array<void(...) const noexcept>();
    test_is_not_unbounded_array<void(...) const& noexcept>();
    test_is_not_unbounded_array<void(...) const&& noexcept>();
    test_is_not_unbounded_array<void(...) volatile noexcept>();
    test_is_not_unbounded_array<void(...) volatile& noexcept>();
    test_is_not_unbounded_array<void(...) volatile&& noexcept>();
    test_is_not_unbounded_array<void(...) const volatile noexcept>();
    test_is_not_unbounded_array<void(...) const volatile& noexcept>();
    test_is_not_unbounded_array<void(...) const volatile&& noexcept>();

    test_is_not_unbounded_array<void(int, ...)>();
    test_is_not_unbounded_array<void(int, ...)&>();
    test_is_not_unbounded_array<void(int, ...) &&>();
    test_is_not_unbounded_array<void(int, ...) const>();
    test_is_not_unbounded_array<void(int, ...) const&>();
    test_is_not_unbounded_array<void(int, ...) const&&>();
    test_is_not_unbounded_array<void(int, ...) volatile>();
    test_is_not_unbounded_array<void(int, ...) volatile&>();
    test_is_not_unbounded_array<void(int, ...) volatile&&>();
    test_is_not_unbounded_array<void(int, ...) const volatile>();
    test_is_not_unbounded_array<void(int, ...) const volatile&>();
    test_is_not_unbounded_array<void(int, ...) const volatile&&>();
    test_is_not_unbounded_array<void(int, ...) noexcept>();
    test_is_not_unbounded_array<void(int, ...)& noexcept>();
    test_is_not_unbounded_array<void(int, ...)&& noexcept>();
    test_is_not_unbounded_array<void(int, ...) const noexcept>();
    test_is_not_unbounded_array<void(int, ...) const& noexcept>();
    test_is_not_unbounded_array<void(int, ...) const&& noexcept>();
    test_is_not_unbounded_array<void(int, ...) volatile noexcept>();
    test_is_not_unbounded_array<void(int, ...) volatile& noexcept>();
    test_is_not_unbounded_array<void(int, ...) volatile&& noexcept>();
    test_is_not_unbounded_array<void(int, ...) const volatile noexcept>();
    test_is_not_unbounded_array<void(int, ...) const volatile& noexcept>();
    test_is_not_unbounded_array<void(int, ...) const volatile&& noexcept>();

    test_is_not_unbounded_array<int()>();
    test_is_not_unbounded_array<int()&>();
    test_is_not_unbounded_array<int() &&>();
    test_is_not_unbounded_array<int() const>();
    test_is_not_unbounded_array<int() const&>();
    test_is_not_unbounded_array<int() const&&>();
    test_is_not_unbounded_array<int() volatile>();
    test_is_not_unbounded_array<int() volatile&>();
    test_is_not_unbounded_array<int() volatile&&>();
    test_is_not_unbounded_array<int() const volatile>();
    test_is_not_unbounded_array<int() const volatile&>();
    test_is_not_unbounded_array<int() const volatile&&>();
    test_is_not_unbounded_array<int() noexcept>();
    test_is_not_unbounded_array<int()& noexcept>();
    test_is_not_unbounded_array<int()&& noexcept>();
    test_is_not_unbounded_array<int() const noexcept>();
    test_is_not_unbounded_array<int() const& noexcept>();
    test_is_not_unbounded_array<int() const&& noexcept>();
    test_is_not_unbounded_array<int() volatile noexcept>();
    test_is_not_unbounded_array<int() volatile& noexcept>();
    test_is_not_unbounded_array<int() volatile&& noexcept>();
    test_is_not_unbounded_array<int() const volatile noexcept>();
    test_is_not_unbounded_array<int() const volatile& noexcept>();
    test_is_not_unbounded_array<int() const volatile&& noexcept>();

    test_is_not_unbounded_array<int(int)>();
    test_is_not_unbounded_array<int(int)&>();
    test_is_not_unbounded_array<int(int) &&>();
    test_is_not_unbounded_array<int(int) const>();
    test_is_not_unbounded_array<int(int) const&>();
    test_is_not_unbounded_array<int(int) const&&>();
    test_is_not_unbounded_array<int(int) volatile>();
    test_is_not_unbounded_array<int(int) volatile&>();
    test_is_not_unbounded_array<int(int) volatile&&>();
    test_is_not_unbounded_array<int(int) const volatile>();
    test_is_not_unbounded_array<int(int) const volatile&>();
    test_is_not_unbounded_array<int(int) const volatile&&>();
    test_is_not_unbounded_array<int(int) noexcept>();
    test_is_not_unbounded_array<int(int)& noexcept>();
    test_is_not_unbounded_array<int(int)&& noexcept>();
    test_is_not_unbounded_array<int(int) const noexcept>();
    test_is_not_unbounded_array<int(int) const& noexcept>();
    test_is_not_unbounded_array<int(int) const&& noexcept>();
    test_is_not_unbounded_array<int(int) volatile noexcept>();
    test_is_not_unbounded_array<int(int) volatile& noexcept>();
    test_is_not_unbounded_array<int(int) volatile&& noexcept>();
    test_is_not_unbounded_array<int(int) const volatile noexcept>();
    test_is_not_unbounded_array<int(int) const volatile& noexcept>();
    test_is_not_unbounded_array<int(int) const volatile&& noexcept>();

    test_is_not_unbounded_array<int(...)>();
    test_is_not_unbounded_array<int(...)&>();
    test_is_not_unbounded_array<int(...) &&>();
    test_is_not_unbounded_array<int(...) const>();
    test_is_not_unbounded_array<int(...) const&>();
    test_is_not_unbounded_array<int(...) const&&>();
    test_is_not_unbounded_array<int(...) volatile>();
    test_is_not_unbounded_array<int(...) volatile&>();
    test_is_not_unbounded_array<int(...) volatile&&>();
    test_is_not_unbounded_array<int(...) const volatile>();
    test_is_not_unbounded_array<int(...) const volatile&>();
    test_is_not_unbounded_array<int(...) const volatile&&>();
    test_is_not_unbounded_array<int(...) noexcept>();
    test_is_not_unbounded_array<int(...)& noexcept>();
    test_is_not_unbounded_array<int(...)&& noexcept>();
    test_is_not_unbounded_array<int(...) const noexcept>();
    test_is_not_unbounded_array<int(...) const& noexcept>();
    test_is_not_unbounded_array<int(...) const&& noexcept>();
    test_is_not_unbounded_array<int(...) volatile noexcept>();
    test_is_not_unbounded_array<int(...) volatile& noexcept>();
    test_is_not_unbounded_array<int(...) volatile&& noexcept>();
    test_is_not_unbounded_array<int(...) const volatile noexcept>();
    test_is_not_unbounded_array<int(...) const volatile& noexcept>();
    test_is_not_unbounded_array<int(...) const volatile&& noexcept>();

    test_is_not_unbounded_array<int(int, ...)>();
    test_is_not_unbounded_array<int(int, ...)&>();
    test_is_not_unbounded_array<int(int, ...) &&>();
    test_is_not_unbounded_array<int(int, ...) const>();
    test_is_not_unbounded_array<int(int, ...) const&>();
    test_is_not_unbounded_array<int(int, ...) const&&>();
    test_is_not_unbounded_array<int(int, ...) volatile>();
    test_is_not_unbounded_array<int(int, ...) volatile&>();
    test_is_not_unbounded_array<int(int, ...) volatile&&>();
    test_is_not_unbounded_array<int(int, ...) const volatile>();
    test_is_not_unbounded_array<int(int, ...) const volatile&>();
    test_is_not_unbounded_array<int(int, ...) const volatile&&>();
    test_is_not_unbounded_array<int(int, ...) noexcept>();
    test_is_not_unbounded_array<int(int, ...)& noexcept>();
    test_is_not_unbounded_array<int(int, ...)&& noexcept>();
    test_is_not_unbounded_array<int(int, ...) const noexcept>();
    test_is_not_unbounded_array<int(int, ...) const& noexcept>();
    test_is_not_unbounded_array<int(int, ...) const&& noexcept>();
    test_is_not_unbounded_array<int(int, ...) volatile noexcept>();
    test_is_not_unbounded_array<int(int, ...) volatile& noexcept>();
    test_is_not_unbounded_array<int(int, ...) volatile&& noexcept>();
    test_is_not_unbounded_array<int(int, ...) const volatile noexcept>();
    test_is_not_unbounded_array<int(int, ...) const volatile& noexcept>();
    test_is_not_unbounded_array<int(int, ...) const volatile&& noexcept>();

    test_is_not_unbounded_array<void (*)()>();
    test_is_not_unbounded_array<void (*)() noexcept>();

    test_is_not_unbounded_array<void (*)(int)>();
    test_is_not_unbounded_array<void (*)(int) noexcept>();

    test_is_not_unbounded_array<void (*)(...)>();
    test_is_not_unbounded_array<void (*)(...) noexcept>();

    test_is_not_unbounded_array<void (*)(int, ...)>();
    test_is_not_unbounded_array<void (*)(int, ...) noexcept>();

    test_is_not_unbounded_array<int (*)()>();
    test_is_not_unbounded_array<int (*)() noexcept>();

    test_is_not_unbounded_array<int (*)(int)>();
    test_is_not_unbounded_array<int (*)(int) noexcept>();

    test_is_not_unbounded_array<int (*)(...)>();
    test_is_not_unbounded_array<int (*)(...) noexcept>();

    test_is_not_unbounded_array<int (*)(int, ...)>();
    test_is_not_unbounded_array<int (*)(int, ...) noexcept>();

    test_is_not_unbounded_array<void (&)()>();
    test_is_not_unbounded_array<void (&)() noexcept>();

    test_is_not_unbounded_array<void (&)(int)>();
    test_is_not_unbounded_array<void (&)(int) noexcept>();

    test_is_not_unbounded_array<void (&)(...)>();
    test_is_not_unbounded_array<void (&)(...) noexcept>();

    test_is_not_unbounded_array<void (&)(int, ...)>();
    test_is_not_unbounded_array<void (&)(int, ...) noexcept>();

    test_is_not_unbounded_array<int (&)()>();
    test_is_not_unbounded_array<int (&)() noexcept>();

    test_is_not_unbounded_array<int (&)(int)>();
    test_is_not_unbounded_array<int (&)(int) noexcept>();

    test_is_not_unbounded_array<int (&)(...)>();
    test_is_not_unbounded_array<int (&)(...) noexcept>();

    test_is_not_unbounded_array<int (&)(int, ...)>();
    test_is_not_unbounded_array<int (&)(int, ...) noexcept>();

    test_is_not_unbounded_array<void(&&)()>();
    test_is_not_unbounded_array<void(&&)() noexcept>();

    test_is_not_unbounded_array<void(&&)(int)>();
    test_is_not_unbounded_array<void(&&)(int) noexcept>();

    test_is_not_unbounded_array<void(&&)(...)>();
    test_is_not_unbounded_array<void(&&)(...) noexcept>();

    test_is_not_unbounded_array<void(&&)(int, ...)>();
    test_is_not_unbounded_array<void(&&)(int, ...) noexcept>();

    test_is_not_unbounded_array<int(&&)()>();
    test_is_not_unbounded_array<int(&&)() noexcept>();

    test_is_not_unbounded_array<int(&&)(int)>();
    test_is_not_unbounded_array<int(&&)(int) noexcept>();

    test_is_not_unbounded_array<int(&&)(...)>();
    test_is_not_unbounded_array<int(&&)(...) noexcept>();

    test_is_not_unbounded_array<int(&&)(int, ...)>();
    test_is_not_unbounded_array<int(&&)(int, ...) noexcept>();

    test_is_not_unbounded_array<void (Class::*)()>();
    test_is_not_unbounded_array<void (Class::*)()&>();
    test_is_not_unbounded_array<void (Class::*)() &&>();
    test_is_not_unbounded_array<void (Class::*)() const>();
    test_is_not_unbounded_array<void (Class::*)() const&>();
    test_is_not_unbounded_array<void (Class::*)() const&&>();
    test_is_not_unbounded_array<void (Class::*)() noexcept>();
    test_is_not_unbounded_array<void (Class::*)()& noexcept>();
    test_is_not_unbounded_array<void (Class::*)()&& noexcept>();
    test_is_not_unbounded_array<void (Class::*)() const noexcept>();
    test_is_not_unbounded_array<void (Class::*)() const& noexcept>();
    test_is_not_unbounded_array<void (Class::*)() const&& noexcept>();

    test_is_not_unbounded_array<void (Class::*)(int)>();
    test_is_not_unbounded_array<void (Class::*)(int)&>();
    test_is_not_unbounded_array<void (Class::*)(int) &&>();
    test_is_not_unbounded_array<void (Class::*)(int) const>();
    test_is_not_unbounded_array<void (Class::*)(int) const&>();
    test_is_not_unbounded_array<void (Class::*)(int) const&&>();
    test_is_not_unbounded_array<void (Class::*)(int) noexcept>();
    test_is_not_unbounded_array<void (Class::*)(int)& noexcept>();
    test_is_not_unbounded_array<void (Class::*)(int)&& noexcept>();
    test_is_not_unbounded_array<void (Class::*)(int) const noexcept>();
    test_is_not_unbounded_array<void (Class::*)(int) const& noexcept>();
    test_is_not_unbounded_array<void (Class::*)(int) const&& noexcept>();

    test_is_not_unbounded_array<void (Class::*)(...)>();
    test_is_not_unbounded_array<void (Class::*)(...)&>();
    test_is_not_unbounded_array<void (Class::*)(...) &&>();
    test_is_not_unbounded_array<void (Class::*)(...) const>();
    test_is_not_unbounded_array<void (Class::*)(...) const&>();
    test_is_not_unbounded_array<void (Class::*)(...) const&&>();
    test_is_not_unbounded_array<void (Class::*)(...) noexcept>();
    test_is_not_unbounded_array<void (Class::*)(...)& noexcept>();
    test_is_not_unbounded_array<void (Class::*)(...)&& noexcept>();
    test_is_not_unbounded_array<void (Class::*)(...) const noexcept>();
    test_is_not_unbounded_array<void (Class::*)(...) const& noexcept>();
    test_is_not_unbounded_array<void (Class::*)(...) const&& noexcept>();

    test_is_not_unbounded_array<void (Class::*)(int, ...)>();
    test_is_not_unbounded_array<void (Class::*)(int, ...)&>();
    test_is_not_unbounded_array<void (Class::*)(int, ...) &&>();
    test_is_not_unbounded_array<void (Class::*)(int, ...) const>();
    test_is_not_unbounded_array<void (Class::*)(int, ...) const&>();
    test_is_not_unbounded_array<void (Class::*)(int, ...) const&&>();
    test_is_not_unbounded_array<void (Class::*)(int, ...) noexcept>();
    test_is_not_unbounded_array<void (Class::*)(int, ...)& noexcept>();
    test_is_not_unbounded_array<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_unbounded_array<void (Class::*)(int, ...) const noexcept>();
    test_is_not_unbounded_array<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_unbounded_array<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_unbounded_array<int (Class::*)()>();
    test_is_not_unbounded_array<int (Class::*)()&>();
    test_is_not_unbounded_array<int (Class::*)() &&>();
    test_is_not_unbounded_array<int (Class::*)() const>();
    test_is_not_unbounded_array<int (Class::*)() const&>();
    test_is_not_unbounded_array<int (Class::*)() const&&>();
    test_is_not_unbounded_array<int (Class::*)() noexcept>();
    test_is_not_unbounded_array<int (Class::*)()& noexcept>();
    test_is_not_unbounded_array<int (Class::*)()&& noexcept>();
    test_is_not_unbounded_array<int (Class::*)() const noexcept>();
    test_is_not_unbounded_array<int (Class::*)() const& noexcept>();
    test_is_not_unbounded_array<int (Class::*)() const&& noexcept>();

    test_is_not_unbounded_array<int (Class::*)(int)>();
    test_is_not_unbounded_array<int (Class::*)(int)&>();
    test_is_not_unbounded_array<int (Class::*)(int) &&>();
    test_is_not_unbounded_array<int (Class::*)(int) const>();
    test_is_not_unbounded_array<int (Class::*)(int) const&>();
    test_is_not_unbounded_array<int (Class::*)(int) const&&>();
    test_is_not_unbounded_array<int (Class::*)(int) noexcept>();
    test_is_not_unbounded_array<int (Class::*)(int)& noexcept>();
    test_is_not_unbounded_array<int (Class::*)(int)&& noexcept>();
    test_is_not_unbounded_array<int (Class::*)(int) const noexcept>();
    test_is_not_unbounded_array<int (Class::*)(int) const& noexcept>();
    test_is_not_unbounded_array<int (Class::*)(int) const&& noexcept>();

    test_is_not_unbounded_array<int (Class::*)(...)>();
    test_is_not_unbounded_array<int (Class::*)(...)&>();
    test_is_not_unbounded_array<int (Class::*)(...) &&>();
    test_is_not_unbounded_array<int (Class::*)(...) const>();
    test_is_not_unbounded_array<int (Class::*)(...) const&>();
    test_is_not_unbounded_array<int (Class::*)(...) const&&>();
    test_is_not_unbounded_array<int (Class::*)(...) noexcept>();
    test_is_not_unbounded_array<int (Class::*)(...)& noexcept>();
    test_is_not_unbounded_array<int (Class::*)(...)&& noexcept>();
    test_is_not_unbounded_array<int (Class::*)(...) const noexcept>();
    test_is_not_unbounded_array<int (Class::*)(...) const& noexcept>();
    test_is_not_unbounded_array<int (Class::*)(...) const&& noexcept>();

    test_is_not_unbounded_array<int (Class::*)(int, ...)>();
    test_is_not_unbounded_array<int (Class::*)(int, ...)&>();
    test_is_not_unbounded_array<int (Class::*)(int, ...) &&>();
    test_is_not_unbounded_array<int (Class::*)(int, ...) const>();
    test_is_not_unbounded_array<int (Class::*)(int, ...) const&>();
    test_is_not_unbounded_array<int (Class::*)(int, ...) const&&>();
    test_is_not_unbounded_array<int (Class::*)(int, ...) noexcept>();
    test_is_not_unbounded_array<int (Class::*)(int, ...)& noexcept>();
    test_is_not_unbounded_array<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_unbounded_array<int (Class::*)(int, ...) const noexcept>();
    test_is_not_unbounded_array<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_unbounded_array<int (Class::*)(int, ...) const&& noexcept>();
}
