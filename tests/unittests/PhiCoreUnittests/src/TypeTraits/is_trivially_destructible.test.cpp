#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_trivially_destructible.hpp>
#include <vector>

template <typename T>
void test_is_trivially_destructible()
{
    STATIC_REQUIRE(sizeof(phi::is_trivially_destructible<T>) == 1);
    STATIC_REQUIRE(sizeof(phi::is_trivially_destructible<const T>) == 1);
    STATIC_REQUIRE(sizeof(phi::is_trivially_destructible<volatile T>) == 1);
    STATIC_REQUIRE(sizeof(phi::is_trivially_destructible<const volatile T>) == 1);

    STATIC_REQUIRE(phi::is_trivially_destructible<T>::value);
    STATIC_REQUIRE(phi::is_trivially_destructible<const T>::value);
    STATIC_REQUIRE(phi::is_trivially_destructible<volatile T>::value);
    STATIC_REQUIRE(phi::is_trivially_destructible<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_destructible_v<T>);
    STATIC_REQUIRE(phi::is_trivially_destructible_v<const T>);
    STATIC_REQUIRE(phi::is_trivially_destructible_v<volatile T>);
    STATIC_REQUIRE(phi::is_trivially_destructible_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_trivially_destructible()
{
    STATIC_REQUIRE(sizeof(phi::is_trivially_destructible<T>) == 1);
    STATIC_REQUIRE(sizeof(phi::is_trivially_destructible<const T>) == 1);
    STATIC_REQUIRE(sizeof(phi::is_trivially_destructible<volatile T>) == 1);
    STATIC_REQUIRE(sizeof(phi::is_trivially_destructible<const volatile T>) == 1);

    STATIC_REQUIRE_FALSE(phi::is_trivially_destructible<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_trivially_destructible<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_trivially_destructible<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_trivially_destructible<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_destructible_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_trivially_destructible_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_trivially_destructible_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_trivially_destructible_v<const volatile T>);
#endif
}

struct A
{
    ~A();
};

struct B
{
    ~B() = default;
};

TEST_CASE("is_trivially_destructible")
{
    test_is_not_trivially_destructible<A>();
    test_is_trivially_destructible<B>();
    test_is_not_trivially_destructible<VirtualPublicDestructor>();
    test_is_not_trivially_destructible<PurePublicDestructor>();
    test_is_not_trivially_destructible<ProtectedDestructor>();
    test_is_not_trivially_destructible<PrivateDestructor>();
    test_is_not_trivially_destructible<VirtualProtectedDestructor>();
    test_is_not_trivially_destructible<VirtualPrivateDestructor>();
    test_is_not_trivially_destructible<PureProtectedDestructor>();
    test_is_not_trivially_destructible<PurePrivateDestructor>();

    test_is_not_trivially_destructible<void>();
    test_is_trivially_destructible<phi::nullptr_t>();
    test_is_trivially_destructible<bool>();
    test_is_trivially_destructible<char>();
    test_is_trivially_destructible<signed char>();
    test_is_trivially_destructible<unsigned char>();
    test_is_trivially_destructible<short>();
    test_is_trivially_destructible<unsigned short>();
    test_is_trivially_destructible<int>();
    test_is_trivially_destructible<unsigned int>();
    test_is_trivially_destructible<long>();
    test_is_trivially_destructible<unsigned long>();
    test_is_trivially_destructible<long long>();
    test_is_trivially_destructible<unsigned long long>();
    test_is_trivially_destructible<float>();
    test_is_trivially_destructible<double>();
    test_is_trivially_destructible<long double>();
    test_is_trivially_destructible<char8_t>();
    test_is_trivially_destructible<char16_t>();
    test_is_trivially_destructible<char32_t>();
    test_is_trivially_destructible<wchar_t>();

    test_is_trivially_destructible<phi::Boolean>();
    test_is_trivially_destructible<phi::Integer<signed char>>();
    test_is_trivially_destructible<phi::Integer<unsigned char>>();
    test_is_trivially_destructible<phi::Integer<short>>();
    test_is_trivially_destructible<phi::Integer<unsigned short>>();
    test_is_trivially_destructible<phi::Integer<int>>();
    test_is_trivially_destructible<phi::Integer<unsigned int>>();
    test_is_trivially_destructible<phi::Integer<long>>();
    test_is_trivially_destructible<phi::Integer<unsigned long>>();
    test_is_trivially_destructible<phi::Integer<long long>>();
    test_is_trivially_destructible<phi::Integer<unsigned long long>>();
    test_is_trivially_destructible<phi::FloatingPoint<float>>();
    test_is_trivially_destructible<phi::FloatingPoint<double>>();
    test_is_trivially_destructible<phi::FloatingPoint<long double>>();

    test_is_not_trivially_destructible<std::vector<int>>();
    test_is_not_trivially_destructible<phi::ScopePtr<int>>();

    test_is_trivially_destructible<int&>();
    test_is_trivially_destructible<const int&>();
    test_is_trivially_destructible<volatile int&>();
    test_is_trivially_destructible<const volatile int&>();
    test_is_trivially_destructible<int&&>();
    test_is_trivially_destructible<const int&&>();
    test_is_trivially_destructible<volatile int&&>();
    test_is_trivially_destructible<const volatile int&&>();
    test_is_trivially_destructible<int*>();
    test_is_trivially_destructible<const int*>();
    test_is_trivially_destructible<volatile int*>();
    test_is_trivially_destructible<const volatile int*>();
    test_is_trivially_destructible<int**>();
    test_is_trivially_destructible<const int**>();
    test_is_trivially_destructible<volatile int**>();
    test_is_trivially_destructible<const volatile int**>();
    test_is_trivially_destructible<void*>();
    test_is_trivially_destructible<char[3]>();
    test_is_not_trivially_destructible<char[]>();
    test_is_trivially_destructible<char* [3]>();
    test_is_not_trivially_destructible<char*[]>();
    test_is_not_trivially_destructible<Class>();
    test_is_trivially_destructible<Union>();
    test_is_trivially_destructible<NonEmptyUnion>();
    test_is_trivially_destructible<Empty>();
    test_is_not_trivially_destructible<NotEmpty>();
    test_is_trivially_destructible<bit_zero>();
    test_is_trivially_destructible<bit_one>();
    test_is_not_trivially_destructible<Abstract>();
    test_is_not_trivially_destructible<AbstractTemplate<int>>();
    test_is_trivially_destructible<AbstractTemplate<double>>();
    test_is_not_trivially_destructible<AbstractTemplate<Class>>();
    test_is_trivially_destructible<Final>();
    test_is_trivially_destructible<Enum>();
    test_is_trivially_destructible<EnumSigned>();
    test_is_trivially_destructible<EnumUnsigned>();
    test_is_trivially_destructible<EnumClass>();
    test_is_not_trivially_destructible<Function>();
    test_is_trivially_destructible<FunctionPtr>();
    test_is_trivially_destructible<MemberObjectPtr>();
    test_is_trivially_destructible<MemberFunctionPtr>();
    test_is_trivially_destructible<int Class::*>();
    test_is_trivially_destructible<float Class::*>();

    test_is_not_trivially_destructible<void()>();
    test_is_not_trivially_destructible<void() noexcept>();
    test_is_not_trivially_destructible<void(int)>();
    test_is_not_trivially_destructible<void(int) noexcept>();

    test_is_not_trivially_destructible<void(...)>();
    test_is_not_trivially_destructible<void(...) noexcept>();
    test_is_not_trivially_destructible<void(int, ...)>();
    test_is_not_trivially_destructible<void(int, ...) noexcept>();

    test_is_trivially_destructible<void (*)()>();
    test_is_trivially_destructible<void (*)() noexcept>();
    test_is_trivially_destructible<void (*)(int)>();
    test_is_trivially_destructible<void (*)(int) noexcept>();

    test_is_trivially_destructible<void (*)(...)>();
    test_is_trivially_destructible<void (*)(...) noexcept>();
    test_is_trivially_destructible<void (*)(int, ...)>();
    test_is_trivially_destructible<void (*)(int, ...) noexcept>();

    test_is_trivially_destructible<void (Class::*)()>();
    test_is_trivially_destructible<void (Class::*)()&>();
    test_is_trivially_destructible<void (Class::*)() &&>();
    test_is_trivially_destructible<void (Class::*)() const>();
    test_is_trivially_destructible<void (Class::*)() const&>();
    test_is_trivially_destructible<void (Class::*)() const&&>();

    test_is_trivially_destructible<void (Class::*)() noexcept>();
    test_is_trivially_destructible<void (Class::*)()& noexcept>();
    test_is_trivially_destructible<void (Class::*)()&& noexcept>();
    test_is_trivially_destructible<void (Class::*)() const noexcept>();
    test_is_trivially_destructible<void (Class::*)() const& noexcept>();
    test_is_trivially_destructible<void (Class::*)() const&& noexcept>();

    test_is_trivially_destructible<void (Class::*)(int)>();
    test_is_trivially_destructible<void (Class::*)(int)&>();
    test_is_trivially_destructible<void (Class::*)(int) &&>();
    test_is_trivially_destructible<void (Class::*)(int) const>();
    test_is_trivially_destructible<void (Class::*)(int) const&>();
    test_is_trivially_destructible<void (Class::*)(int) const&&>();

    test_is_trivially_destructible<void (Class::*)(int) noexcept>();
    test_is_trivially_destructible<void (Class::*)(int)& noexcept>();
    test_is_trivially_destructible<void (Class::*)(int)&& noexcept>();
    test_is_trivially_destructible<void (Class::*)(int) const noexcept>();
    test_is_trivially_destructible<void (Class::*)(int) const& noexcept>();
    test_is_trivially_destructible<void (Class::*)(int) const&& noexcept>();

    test_is_trivially_destructible<void (Class::*)(...)>();
    test_is_trivially_destructible<void (Class::*)(...)&>();
    test_is_trivially_destructible<void (Class::*)(...) &&>();
    test_is_trivially_destructible<void (Class::*)(...) const>();
    test_is_trivially_destructible<void (Class::*)(...) const&>();
    test_is_trivially_destructible<void (Class::*)(...) const&&>();

    test_is_trivially_destructible<void (Class::*)(...) noexcept>();
    test_is_trivially_destructible<void (Class::*)(...)& noexcept>();
    test_is_trivially_destructible<void (Class::*)(...)&& noexcept>();
    test_is_trivially_destructible<void (Class::*)(...) const noexcept>();
    test_is_trivially_destructible<void (Class::*)(...) const& noexcept>();
    test_is_trivially_destructible<void (Class::*)(...) const&& noexcept>();
}
