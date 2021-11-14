#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_union.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_union_impl()
{
    STATIC_REQUIRE(phi::is_union<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_union<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_union_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_union_v<T>);
#endif

    // Standard compatibility
    STATIC_REQUIRE(std::is_union<T>::value);
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(std::is_union_v<T>);
#endif
}

template <typename T>
void test_is_union()
{
    test_is_union_impl<T>();
    test_is_union_impl<const T>();
    test_is_union_impl<volatile T>();
    test_is_union_impl<const volatile T>();
}

template <typename T>
void test_is_not_union_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_union<T>::value);
    STATIC_REQUIRE(phi::is_not_union<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_union_v<T>);
    STATIC_REQUIRE(phi::is_not_union_v<T>);
#endif

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_union<T>::value);
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE_FALSE(std::is_union_v<T>);
#endif
}

template <typename T>
void test_is_not_union()
{
    test_is_not_union_impl<T>();
    test_is_not_union_impl<const T>();
    test_is_not_union_impl<volatile T>();
    test_is_not_union_impl<const volatile T>();
}

TEST_CASE("is_union")
{
    test_is_not_union<void>();
    test_is_not_union<phi::nullptr_t>();
    test_is_not_union<bool>();
    test_is_not_union<char>();
    test_is_not_union<signed char>();
    test_is_not_union<unsigned char>();
    test_is_not_union<short>();
    test_is_not_union<unsigned short>();
    test_is_not_union<int>();
    test_is_not_union<unsigned int>();
    test_is_not_union<long>();
    test_is_not_union<unsigned long>();
    test_is_not_union<long long>();
    test_is_not_union<unsigned long long>();
    test_is_not_union<float>();
    test_is_not_union<double>();
    test_is_not_union<long double>();
    test_is_not_union<char8_t>();
    test_is_not_union<char16_t>();
    test_is_not_union<char32_t>();
    test_is_not_union<wchar_t>();

    test_is_not_union<phi::Boolean>();
    test_is_not_union<phi::Integer<signed char>>();
    test_is_not_union<phi::Integer<unsigned char>>();
    test_is_not_union<phi::Integer<short>>();
    test_is_not_union<phi::Integer<unsigned short>>();
    test_is_not_union<phi::Integer<int>>();
    test_is_not_union<phi::Integer<unsigned int>>();
    test_is_not_union<phi::Integer<long>>();
    test_is_not_union<phi::Integer<unsigned long>>();
    test_is_not_union<phi::Integer<long long>>();
    test_is_not_union<phi::Integer<unsigned long long>>();
    test_is_not_union<phi::FloatingPoint<float>>();
    test_is_not_union<phi::FloatingPoint<double>>();
    test_is_not_union<phi::FloatingPoint<long double>>();

    test_is_not_union<std::vector<int>>();
    test_is_not_union<phi::ScopePtr<int>>();

    test_is_not_union<int&>();
    test_is_not_union<const int&>();
    test_is_not_union<volatile int&>();
    test_is_not_union<const volatile int&>();
    test_is_not_union<int&&>();
    test_is_not_union<const int&&>();
    test_is_not_union<volatile int&&>();
    test_is_not_union<const volatile int&&>();
    test_is_not_union<int*>();
    test_is_not_union<const int*>();
    test_is_not_union<volatile int*>();
    test_is_not_union<const volatile int*>();
    test_is_not_union<int**>();
    test_is_not_union<const int**>();
    test_is_not_union<volatile int**>();
    test_is_not_union<const volatile int**>();
    test_is_not_union<int*&>();
    test_is_not_union<const int*&>();
    test_is_not_union<volatile int*&>();
    test_is_not_union<const volatile int*&>();
    test_is_not_union<int*&&>();
    test_is_not_union<const int*&&>();
    test_is_not_union<volatile int*&&>();
    test_is_not_union<const volatile int*&&>();
    test_is_not_union<void*>();
    test_is_not_union<char[3]>();
    test_is_not_union<char[]>();
    test_is_not_union<char* [3]>();
    test_is_not_union<char*[]>();
    test_is_not_union<int(*)[3]>();
    test_is_not_union<int(*)[]>();
    test_is_not_union<int(&)[3]>();
    test_is_not_union<int(&)[]>();
    test_is_not_union<int(&&)[3]>();
    test_is_not_union<int(&&)[]>();
    test_is_not_union<char[3][2]>();
    test_is_not_union<char[][2]>();
    test_is_not_union<char* [3][2]>();
    test_is_not_union<char*[][2]>();
    test_is_not_union<int(*)[3][2]>();
    test_is_not_union<int(*)[][2]>();
    test_is_not_union<int(&)[3][2]>();
    test_is_not_union<int(&)[][2]>();
    test_is_not_union<int(&&)[3][2]>();
    test_is_not_union<int(&&)[][2]>();
    test_is_not_union<Class>();
    test_is_not_union<Class[]>();
    test_is_not_union<Class[2]>();
    test_is_not_union<Template<void>>();
    test_is_not_union<Template<int>>();
    test_is_not_union<Template<Class>>();
    test_is_not_union<Template<incomplete_type>>();
    test_is_not_union<VariadicTemplate<>>();
    test_is_not_union<VariadicTemplate<void>>();
    test_is_not_union<VariadicTemplate<int>>();
    test_is_not_union<VariadicTemplate<Class>>();
    test_is_not_union<VariadicTemplate<incomplete_type>>();
    test_is_not_union<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_union<PublicDerviedFromTemplate<Base>>();
    test_is_not_union<PublicDerviedFromTemplate<Derived>>();
    test_is_not_union<PublicDerviedFromTemplate<Class>>();
    test_is_not_union<PrivateDerviedFromTemplate<Base>>();
    test_is_not_union<PrivateDerviedFromTemplate<Derived>>();
    test_is_not_union<PrivateDerviedFromTemplate<Class>>();
    test_is_not_union<ProtectedDerviedFromTemplate<Base>>();
    test_is_not_union<ProtectedDerviedFromTemplate<Derived>>();
    test_is_not_union<ProtectedDerviedFromTemplate<Class>>();
    test_is_union<Union>();
    test_is_union<NonEmptyUnion>();
    test_is_not_union<Empty>();
    test_is_not_union<NotEmpty>();
    test_is_not_union<bit_zero>();
    test_is_not_union<bit_one>();
    test_is_not_union<Base>();
    test_is_not_union<Derived>();
    test_is_not_union<Abstract>();
    test_is_not_union<PublicAbstract>();
    test_is_not_union<PrivateAbstract>();
    test_is_not_union<ProtectedAbstract>();
    test_is_not_union<AbstractTemplate<int>>();
    test_is_not_union<AbstractTemplate<double>>();
    test_is_not_union<AbstractTemplate<Class>>();
    test_is_not_union<AbstractTemplate<incomplete_type>>();
    test_is_not_union<Final>();
    test_is_not_union<PublicDestructor>();
    test_is_not_union<ProtectedDestructor>();
    test_is_not_union<PrivateDestructor>();
    test_is_not_union<VirtualPublicDestructor>();
    test_is_not_union<VirtualProtectedDestructor>();
    test_is_not_union<VirtualPrivateDestructor>();
    test_is_not_union<PurePublicDestructor>();
    test_is_not_union<PureProtectedDestructor>();
    test_is_not_union<PurePrivateDestructor>();
    test_is_not_union<DeletedPublicDestructor>();
    test_is_not_union<DeletedProtectedDestructor>();
    test_is_not_union<DeletedPrivateDestructor>();
    test_is_not_union<DeletedVirtualPublicDestructor>();
    test_is_not_union<DeletedVirtualProtectedDestructor>();
    test_is_not_union<DeletedVirtualPrivateDestructor>();
    test_is_not_union<Final>();
    test_is_not_union<Enum>();
    test_is_not_union<EnumSigned>();
    test_is_not_union<EnumUnsigned>();
    test_is_not_union<EnumClass>();
    test_is_not_union<EnumStruct>();
    test_is_not_union<Function>();
    test_is_not_union<FunctionPtr>();
    test_is_not_union<MemberObjectPtr>();
    test_is_not_union<MemberFunctionPtr>();
    test_is_not_union<incomplete_type>();
    test_is_not_union<IncompleteTemplate<void>>();
    test_is_not_union<IncompleteTemplate<int>>();
    test_is_not_union<IncompleteTemplate<Class>>();
    test_is_not_union<IncompleteTemplate<incomplete_type>>();
    test_is_not_union<IncompleteVariadicTemplate<>>();
    test_is_not_union<IncompleteVariadicTemplate<void>>();
    test_is_not_union<IncompleteVariadicTemplate<int>>();
    test_is_not_union<IncompleteVariadicTemplate<Class>>();
    test_is_not_union<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_not_union<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_union<int Class::*>();
    test_is_not_union<float Class::*>();
    test_is_not_union<void * Class::*>();
    test_is_not_union<int * Class::*>();
    test_is_not_union<int Class::*&>();
    test_is_not_union<float Class::*&>();
    test_is_not_union<void * Class::*&>();
    test_is_not_union<int * Class::*&>();
    test_is_not_union<int Class::*&&>();
    test_is_not_union<float Class::*&&>();
    test_is_not_union<void * Class::*&&>();
    test_is_not_union<int * Class::*&&>();
    test_is_not_union<int Class::*const>();
    test_is_not_union<float Class::*const>();
    test_is_not_union<void * Class::*const>();
    test_is_not_union<int Class::*const&>();
    test_is_not_union<float Class::*const&>();
    test_is_not_union<void * Class::*const&>();
    test_is_not_union<int Class::*const&&>();
    test_is_not_union<float Class::*const&&>();
    test_is_not_union<void * Class::*const&&>();
    test_is_not_union<int Class::*volatile>();
    test_is_not_union<float Class::*volatile>();
    test_is_not_union<void * Class::*volatile>();
    test_is_not_union<int Class::*volatile&>();
    test_is_not_union<float Class::*volatile&>();
    test_is_not_union<void * Class::*volatile&>();
    test_is_not_union<int Class::*volatile&&>();
    test_is_not_union<float Class::*volatile&&>();
    test_is_not_union<void * Class::*volatile&&>();
    test_is_not_union<int Class::*const volatile>();
    test_is_not_union<float Class::*const volatile>();
    test_is_not_union<void * Class::*const volatile>();
    test_is_not_union<int Class::*const volatile&>();
    test_is_not_union<float Class::*const volatile&>();
    test_is_not_union<void * Class::*const volatile&>();
    test_is_not_union<int Class::*const volatile&&>();
    test_is_not_union<float Class::*const volatile&&>();
    test_is_not_union<void * Class::*const volatile&&>();
    test_is_not_union<NonCopyable>();
    test_is_not_union<NonMoveable>();
    test_is_not_union<NonConstructible>();
    test_is_not_union<Tracked>();
    test_is_not_union<TrapConstructible>();
    test_is_not_union<TrapImplicitConversion>();
    test_is_not_union<TrapComma>();
    test_is_not_union<TrapCall>();
    test_is_not_union<TrapSelfAssign>();
    test_is_not_union<TrapDeref>();
    test_is_not_union<TrapArraySubscript>();

    test_is_not_union<void()>();
    test_is_not_union<void()&>();
    test_is_not_union<void() &&>();
    test_is_not_union<void() const>();
    test_is_not_union<void() const&>();
    test_is_not_union<void() const&&>();
    test_is_not_union<void() volatile>();
    test_is_not_union<void() volatile&>();
    test_is_not_union<void() volatile&&>();
    test_is_not_union<void() const volatile>();
    test_is_not_union<void() const volatile&>();
    test_is_not_union<void() const volatile&&>();
    test_is_not_union<void() noexcept>();
    test_is_not_union<void()& noexcept>();
    test_is_not_union<void()&& noexcept>();
    test_is_not_union<void() const noexcept>();
    test_is_not_union<void() const& noexcept>();
    test_is_not_union<void() const&& noexcept>();
    test_is_not_union<void() volatile noexcept>();
    test_is_not_union<void() volatile& noexcept>();
    test_is_not_union<void() volatile&& noexcept>();
    test_is_not_union<void() const volatile noexcept>();
    test_is_not_union<void() const volatile& noexcept>();
    test_is_not_union<void() const volatile&& noexcept>();

    test_is_not_union<void(int)>();
    test_is_not_union<void(int)&>();
    test_is_not_union<void(int) &&>();
    test_is_not_union<void(int) const>();
    test_is_not_union<void(int) const&>();
    test_is_not_union<void(int) const&&>();
    test_is_not_union<void(int) volatile>();
    test_is_not_union<void(int) volatile&>();
    test_is_not_union<void(int) volatile&&>();
    test_is_not_union<void(int) const volatile>();
    test_is_not_union<void(int) const volatile&>();
    test_is_not_union<void(int) const volatile&&>();
    test_is_not_union<void(int) noexcept>();
    test_is_not_union<void(int)& noexcept>();
    test_is_not_union<void(int)&& noexcept>();
    test_is_not_union<void(int) const noexcept>();
    test_is_not_union<void(int) const& noexcept>();
    test_is_not_union<void(int) const&& noexcept>();
    test_is_not_union<void(int) volatile noexcept>();
    test_is_not_union<void(int) volatile& noexcept>();
    test_is_not_union<void(int) volatile&& noexcept>();
    test_is_not_union<void(int) const volatile noexcept>();
    test_is_not_union<void(int) const volatile& noexcept>();
    test_is_not_union<void(int) const volatile&& noexcept>();

    test_is_not_union<void(...)>();
    test_is_not_union<void(...)&>();
    test_is_not_union<void(...) &&>();
    test_is_not_union<void(...) const>();
    test_is_not_union<void(...) const&>();
    test_is_not_union<void(...) const&&>();
    test_is_not_union<void(...) volatile>();
    test_is_not_union<void(...) volatile&>();
    test_is_not_union<void(...) volatile&&>();
    test_is_not_union<void(...) const volatile>();
    test_is_not_union<void(...) const volatile&>();
    test_is_not_union<void(...) const volatile&&>();
    test_is_not_union<void(...) noexcept>();
    test_is_not_union<void(...)& noexcept>();
    test_is_not_union<void(...)&& noexcept>();
    test_is_not_union<void(...) const noexcept>();
    test_is_not_union<void(...) const& noexcept>();
    test_is_not_union<void(...) const&& noexcept>();
    test_is_not_union<void(...) volatile noexcept>();
    test_is_not_union<void(...) volatile& noexcept>();
    test_is_not_union<void(...) volatile&& noexcept>();
    test_is_not_union<void(...) const volatile noexcept>();
    test_is_not_union<void(...) const volatile& noexcept>();
    test_is_not_union<void(...) const volatile&& noexcept>();

    test_is_not_union<void(int, ...)>();
    test_is_not_union<void(int, ...)&>();
    test_is_not_union<void(int, ...) &&>();
    test_is_not_union<void(int, ...) const>();
    test_is_not_union<void(int, ...) const&>();
    test_is_not_union<void(int, ...) const&&>();
    test_is_not_union<void(int, ...) volatile>();
    test_is_not_union<void(int, ...) volatile&>();
    test_is_not_union<void(int, ...) volatile&&>();
    test_is_not_union<void(int, ...) const volatile>();
    test_is_not_union<void(int, ...) const volatile&>();
    test_is_not_union<void(int, ...) const volatile&&>();
    test_is_not_union<void(int, ...) noexcept>();
    test_is_not_union<void(int, ...)& noexcept>();
    test_is_not_union<void(int, ...)&& noexcept>();
    test_is_not_union<void(int, ...) const noexcept>();
    test_is_not_union<void(int, ...) const& noexcept>();
    test_is_not_union<void(int, ...) const&& noexcept>();
    test_is_not_union<void(int, ...) volatile noexcept>();
    test_is_not_union<void(int, ...) volatile& noexcept>();
    test_is_not_union<void(int, ...) volatile&& noexcept>();
    test_is_not_union<void(int, ...) const volatile noexcept>();
    test_is_not_union<void(int, ...) const volatile& noexcept>();
    test_is_not_union<void(int, ...) const volatile&& noexcept>();

    test_is_not_union<int()>();
    test_is_not_union<int()&>();
    test_is_not_union<int() &&>();
    test_is_not_union<int() const>();
    test_is_not_union<int() const&>();
    test_is_not_union<int() const&&>();
    test_is_not_union<int() volatile>();
    test_is_not_union<int() volatile&>();
    test_is_not_union<int() volatile&&>();
    test_is_not_union<int() const volatile>();
    test_is_not_union<int() const volatile&>();
    test_is_not_union<int() const volatile&&>();
    test_is_not_union<int() noexcept>();
    test_is_not_union<int()& noexcept>();
    test_is_not_union<int()&& noexcept>();
    test_is_not_union<int() const noexcept>();
    test_is_not_union<int() const& noexcept>();
    test_is_not_union<int() const&& noexcept>();
    test_is_not_union<int() volatile noexcept>();
    test_is_not_union<int() volatile& noexcept>();
    test_is_not_union<int() volatile&& noexcept>();
    test_is_not_union<int() const volatile noexcept>();
    test_is_not_union<int() const volatile& noexcept>();
    test_is_not_union<int() const volatile&& noexcept>();

    test_is_not_union<int(int)>();
    test_is_not_union<int(int)&>();
    test_is_not_union<int(int) &&>();
    test_is_not_union<int(int) const>();
    test_is_not_union<int(int) const&>();
    test_is_not_union<int(int) const&&>();
    test_is_not_union<int(int) volatile>();
    test_is_not_union<int(int) volatile&>();
    test_is_not_union<int(int) volatile&&>();
    test_is_not_union<int(int) const volatile>();
    test_is_not_union<int(int) const volatile&>();
    test_is_not_union<int(int) const volatile&&>();
    test_is_not_union<int(int) noexcept>();
    test_is_not_union<int(int)& noexcept>();
    test_is_not_union<int(int)&& noexcept>();
    test_is_not_union<int(int) const noexcept>();
    test_is_not_union<int(int) const& noexcept>();
    test_is_not_union<int(int) const&& noexcept>();
    test_is_not_union<int(int) volatile noexcept>();
    test_is_not_union<int(int) volatile& noexcept>();
    test_is_not_union<int(int) volatile&& noexcept>();
    test_is_not_union<int(int) const volatile noexcept>();
    test_is_not_union<int(int) const volatile& noexcept>();
    test_is_not_union<int(int) const volatile&& noexcept>();

    test_is_not_union<int(...)>();
    test_is_not_union<int(...)&>();
    test_is_not_union<int(...) &&>();
    test_is_not_union<int(...) const>();
    test_is_not_union<int(...) const&>();
    test_is_not_union<int(...) const&&>();
    test_is_not_union<int(...) volatile>();
    test_is_not_union<int(...) volatile&>();
    test_is_not_union<int(...) volatile&&>();
    test_is_not_union<int(...) const volatile>();
    test_is_not_union<int(...) const volatile&>();
    test_is_not_union<int(...) const volatile&&>();
    test_is_not_union<int(...) noexcept>();
    test_is_not_union<int(...)& noexcept>();
    test_is_not_union<int(...)&& noexcept>();
    test_is_not_union<int(...) const noexcept>();
    test_is_not_union<int(...) const& noexcept>();
    test_is_not_union<int(...) const&& noexcept>();
    test_is_not_union<int(...) volatile noexcept>();
    test_is_not_union<int(...) volatile& noexcept>();
    test_is_not_union<int(...) volatile&& noexcept>();
    test_is_not_union<int(...) const volatile noexcept>();
    test_is_not_union<int(...) const volatile& noexcept>();
    test_is_not_union<int(...) const volatile&& noexcept>();

    test_is_not_union<int(int, ...)>();
    test_is_not_union<int(int, ...)&>();
    test_is_not_union<int(int, ...) &&>();
    test_is_not_union<int(int, ...) const>();
    test_is_not_union<int(int, ...) const&>();
    test_is_not_union<int(int, ...) const&&>();
    test_is_not_union<int(int, ...) volatile>();
    test_is_not_union<int(int, ...) volatile&>();
    test_is_not_union<int(int, ...) volatile&&>();
    test_is_not_union<int(int, ...) const volatile>();
    test_is_not_union<int(int, ...) const volatile&>();
    test_is_not_union<int(int, ...) const volatile&&>();
    test_is_not_union<int(int, ...) noexcept>();
    test_is_not_union<int(int, ...)& noexcept>();
    test_is_not_union<int(int, ...)&& noexcept>();
    test_is_not_union<int(int, ...) const noexcept>();
    test_is_not_union<int(int, ...) const& noexcept>();
    test_is_not_union<int(int, ...) const&& noexcept>();
    test_is_not_union<int(int, ...) volatile noexcept>();
    test_is_not_union<int(int, ...) volatile& noexcept>();
    test_is_not_union<int(int, ...) volatile&& noexcept>();
    test_is_not_union<int(int, ...) const volatile noexcept>();
    test_is_not_union<int(int, ...) const volatile& noexcept>();
    test_is_not_union<int(int, ...) const volatile&& noexcept>();

    test_is_not_union<void (*)()>();
    test_is_not_union<void (*)() noexcept>();

    test_is_not_union<void (*)(int)>();
    test_is_not_union<void (*)(int) noexcept>();

    test_is_not_union<void (*)(...)>();
    test_is_not_union<void (*)(...) noexcept>();

    test_is_not_union<void (*)(int, ...)>();
    test_is_not_union<void (*)(int, ...) noexcept>();

    test_is_not_union<int (*)()>();
    test_is_not_union<int (*)() noexcept>();

    test_is_not_union<int (*)(int)>();
    test_is_not_union<int (*)(int) noexcept>();

    test_is_not_union<int (*)(...)>();
    test_is_not_union<int (*)(...) noexcept>();

    test_is_not_union<int (*)(int, ...)>();
    test_is_not_union<int (*)(int, ...) noexcept>();

    test_is_not_union<void (&)()>();
    test_is_not_union<void (&)() noexcept>();

    test_is_not_union<void (&)(int)>();
    test_is_not_union<void (&)(int) noexcept>();

    test_is_not_union<void (&)(...)>();
    test_is_not_union<void (&)(...) noexcept>();

    test_is_not_union<void (&)(int, ...)>();
    test_is_not_union<void (&)(int, ...) noexcept>();

    test_is_not_union<int (&)()>();
    test_is_not_union<int (&)() noexcept>();

    test_is_not_union<int (&)(int)>();
    test_is_not_union<int (&)(int) noexcept>();

    test_is_not_union<int (&)(...)>();
    test_is_not_union<int (&)(...) noexcept>();

    test_is_not_union<int (&)(int, ...)>();
    test_is_not_union<int (&)(int, ...) noexcept>();

    test_is_not_union<void(&&)()>();
    test_is_not_union<void(&&)() noexcept>();

    test_is_not_union<void(&&)(int)>();
    test_is_not_union<void(&&)(int) noexcept>();

    test_is_not_union<void(&&)(...)>();
    test_is_not_union<void(&&)(...) noexcept>();

    test_is_not_union<void(&&)(int, ...)>();
    test_is_not_union<void(&&)(int, ...) noexcept>();

    test_is_not_union<int(&&)()>();
    test_is_not_union<int(&&)() noexcept>();

    test_is_not_union<int(&&)(int)>();
    test_is_not_union<int(&&)(int) noexcept>();

    test_is_not_union<int(&&)(...)>();
    test_is_not_union<int(&&)(...) noexcept>();

    test_is_not_union<int(&&)(int, ...)>();
    test_is_not_union<int(&&)(int, ...) noexcept>();

    test_is_not_union<void (Class::*)()>();
    test_is_not_union<void (Class::*)()&>();
    test_is_not_union<void (Class::*)() &&>();
    test_is_not_union<void (Class::*)() const>();
    test_is_not_union<void (Class::*)() const&>();
    test_is_not_union<void (Class::*)() const&&>();
    test_is_not_union<void (Class::*)() noexcept>();
    test_is_not_union<void (Class::*)()& noexcept>();
    test_is_not_union<void (Class::*)()&& noexcept>();
    test_is_not_union<void (Class::*)() const noexcept>();
    test_is_not_union<void (Class::*)() const& noexcept>();
    test_is_not_union<void (Class::*)() const&& noexcept>();

    test_is_not_union<void (Class::*)(int)>();
    test_is_not_union<void (Class::*)(int)&>();
    test_is_not_union<void (Class::*)(int) &&>();
    test_is_not_union<void (Class::*)(int) const>();
    test_is_not_union<void (Class::*)(int) const&>();
    test_is_not_union<void (Class::*)(int) const&&>();
    test_is_not_union<void (Class::*)(int) noexcept>();
    test_is_not_union<void (Class::*)(int)& noexcept>();
    test_is_not_union<void (Class::*)(int)&& noexcept>();
    test_is_not_union<void (Class::*)(int) const noexcept>();
    test_is_not_union<void (Class::*)(int) const& noexcept>();
    test_is_not_union<void (Class::*)(int) const&& noexcept>();

    test_is_not_union<void (Class::*)(...)>();
    test_is_not_union<void (Class::*)(...)&>();
    test_is_not_union<void (Class::*)(...) &&>();
    test_is_not_union<void (Class::*)(...) const>();
    test_is_not_union<void (Class::*)(...) const&>();
    test_is_not_union<void (Class::*)(...) const&&>();
    test_is_not_union<void (Class::*)(...) noexcept>();
    test_is_not_union<void (Class::*)(...)& noexcept>();
    test_is_not_union<void (Class::*)(...)&& noexcept>();
    test_is_not_union<void (Class::*)(...) const noexcept>();
    test_is_not_union<void (Class::*)(...) const& noexcept>();
    test_is_not_union<void (Class::*)(...) const&& noexcept>();

    test_is_not_union<void (Class::*)(int, ...)>();
    test_is_not_union<void (Class::*)(int, ...)&>();
    test_is_not_union<void (Class::*)(int, ...) &&>();
    test_is_not_union<void (Class::*)(int, ...) const>();
    test_is_not_union<void (Class::*)(int, ...) const&>();
    test_is_not_union<void (Class::*)(int, ...) const&&>();
    test_is_not_union<void (Class::*)(int, ...) noexcept>();
    test_is_not_union<void (Class::*)(int, ...)& noexcept>();
    test_is_not_union<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_union<void (Class::*)(int, ...) const noexcept>();
    test_is_not_union<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_union<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_union<int (Class::*)()>();
    test_is_not_union<int (Class::*)()&>();
    test_is_not_union<int (Class::*)() &&>();
    test_is_not_union<int (Class::*)() const>();
    test_is_not_union<int (Class::*)() const&>();
    test_is_not_union<int (Class::*)() const&&>();
    test_is_not_union<int (Class::*)() noexcept>();
    test_is_not_union<int (Class::*)()& noexcept>();
    test_is_not_union<int (Class::*)()&& noexcept>();
    test_is_not_union<int (Class::*)() const noexcept>();
    test_is_not_union<int (Class::*)() const& noexcept>();
    test_is_not_union<int (Class::*)() const&& noexcept>();

    test_is_not_union<int (Class::*)(int)>();
    test_is_not_union<int (Class::*)(int)&>();
    test_is_not_union<int (Class::*)(int) &&>();
    test_is_not_union<int (Class::*)(int) const>();
    test_is_not_union<int (Class::*)(int) const&>();
    test_is_not_union<int (Class::*)(int) const&&>();
    test_is_not_union<int (Class::*)(int) noexcept>();
    test_is_not_union<int (Class::*)(int)& noexcept>();
    test_is_not_union<int (Class::*)(int)&& noexcept>();
    test_is_not_union<int (Class::*)(int) const noexcept>();
    test_is_not_union<int (Class::*)(int) const& noexcept>();
    test_is_not_union<int (Class::*)(int) const&& noexcept>();

    test_is_not_union<int (Class::*)(...)>();
    test_is_not_union<int (Class::*)(...)&>();
    test_is_not_union<int (Class::*)(...) &&>();
    test_is_not_union<int (Class::*)(...) const>();
    test_is_not_union<int (Class::*)(...) const&>();
    test_is_not_union<int (Class::*)(...) const&&>();
    test_is_not_union<int (Class::*)(...) noexcept>();
    test_is_not_union<int (Class::*)(...)& noexcept>();
    test_is_not_union<int (Class::*)(...)&& noexcept>();
    test_is_not_union<int (Class::*)(...) const noexcept>();
    test_is_not_union<int (Class::*)(...) const& noexcept>();
    test_is_not_union<int (Class::*)(...) const&& noexcept>();

    test_is_not_union<int (Class::*)(int, ...)>();
    test_is_not_union<int (Class::*)(int, ...)&>();
    test_is_not_union<int (Class::*)(int, ...) &&>();
    test_is_not_union<int (Class::*)(int, ...) const>();
    test_is_not_union<int (Class::*)(int, ...) const&>();
    test_is_not_union<int (Class::*)(int, ...) const&&>();
    test_is_not_union<int (Class::*)(int, ...) noexcept>();
    test_is_not_union<int (Class::*)(int, ...)& noexcept>();
    test_is_not_union<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_union<int (Class::*)(int, ...) const noexcept>();
    test_is_not_union<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_union<int (Class::*)(int, ...) const&& noexcept>();
}
