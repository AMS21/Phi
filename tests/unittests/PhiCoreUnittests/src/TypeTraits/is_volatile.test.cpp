#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_volatile.hpp>

template <typename T>
void test_is_volatile()
{
    STATIC_REQUIRE_FALSE(phi::is_volatile<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_volatile<const T>::value);
    STATIC_REQUIRE(phi::is_volatile<volatile T>::value);
    STATIC_REQUIRE(phi::is_volatile<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_volatile_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_volatile_v<const T>);
    STATIC_REQUIRE(phi::is_volatile_v<volatile T>);
    STATIC_REQUIRE(phi::is_volatile_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_volatile()
{
    STATIC_REQUIRE_FALSE(phi::is_volatile<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_volatile<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_volatile<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_volatile<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_volatile_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_volatile_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_volatile_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_volatile_v<const volatile T>);
#endif
}

TEST_CASE("is_volatile")
{
    test_is_volatile<void>();
    test_is_volatile<phi::nullptr_t>();
    test_is_volatile<bool>();
    test_is_volatile<char>();
    test_is_volatile<signed char>();
    test_is_volatile<unsigned char>();
    test_is_volatile<short>();
    test_is_volatile<unsigned short>();
    test_is_volatile<int>();
    test_is_volatile<unsigned int>();
    test_is_volatile<long>();
    test_is_volatile<unsigned long>();
    test_is_volatile<long long>();
    test_is_volatile<unsigned long long>();
    test_is_volatile<float>();
    test_is_volatile<double>();
    test_is_volatile<long double>();
    test_is_volatile<char8_t>();
    test_is_volatile<char16_t>();
    test_is_volatile<char32_t>();
    test_is_volatile<wchar_t>();

    test_is_volatile<phi::Boolean>();
    test_is_volatile<phi::Integer<signed char>>();
    test_is_volatile<phi::Integer<unsigned char>>();
    test_is_volatile<phi::Integer<short>>();
    test_is_volatile<phi::Integer<unsigned short>>();
    test_is_volatile<phi::Integer<int>>();
    test_is_volatile<phi::Integer<unsigned int>>();
    test_is_volatile<phi::Integer<long>>();
    test_is_volatile<phi::Integer<unsigned long>>();
    test_is_volatile<phi::Integer<long long>>();
    test_is_volatile<phi::Integer<unsigned long long>>();
    test_is_volatile<phi::FloatingPoint<float>>();
    test_is_volatile<phi::FloatingPoint<double>>();
    test_is_volatile<phi::FloatingPoint<long double>>();

    test_is_volatile<std::vector<int>>();
    test_is_volatile<phi::ScopePtr<int>>();

    test_is_not_volatile<int&>();
    test_is_not_volatile<int&&>();
    test_is_not_volatile<float&>();
    test_is_not_volatile<float&&>();
    test_is_not_volatile<Class&>();
    test_is_not_volatile<Class&&>();
    test_is_volatile<int*>();
    test_is_volatile<const int*>();
    test_is_volatile<volatile int*>();
    test_is_volatile<const volatile int*>();
    test_is_volatile<int**>();
    test_is_volatile<const int**>();
    test_is_volatile<volatile int**>();
    test_is_volatile<const volatile int**>();
    test_is_volatile<void*>();
    test_is_volatile<char[3]>();
    test_is_volatile<char[]>();
    test_is_volatile<char* [3]>();
    test_is_volatile<char*[]>();
    test_is_volatile<Class>();
    test_is_volatile<Struct>();
    test_is_volatile<Union>();
    test_is_volatile<NonEmptyUnion>();
    test_is_volatile<Empty>();
    test_is_volatile<NotEmpty>();
    test_is_volatile<bit_zero>();
    test_is_volatile<bit_one>();
    test_is_volatile<Abstract>();
    test_is_volatile<AbstractTemplate<int>>();
    test_is_volatile<AbstractTemplate<double>>();
    test_is_volatile<AbstractTemplate<Class>>();
    test_is_volatile<AbstractTemplate<incomplete_type>>();
    test_is_volatile<Final>();
    test_is_volatile<Enum>();
    test_is_volatile<EnumSigned>();
    test_is_volatile<EnumUnsigned>();
    test_is_volatile<EnumClass>();
    test_is_not_volatile<Function>();
    test_is_volatile<FunctionPtr>();
    test_is_volatile<MemberObjectPtr>();
    test_is_volatile<MemberFunctionPtr>();
    test_is_volatile<incomplete_type>();
    test_is_volatile<int Class::*>();
    test_is_volatile<float Class::*>();

    test_is_not_volatile<void()>();
    test_is_not_volatile<void() noexcept>();
    test_is_not_volatile<void(int)>();
    test_is_not_volatile<void(int) noexcept>();

    test_is_not_volatile<void(...)>();
    test_is_not_volatile<void(...) noexcept>();
    test_is_not_volatile<void(int, ...)>();
    test_is_not_volatile<void(int, ...) noexcept>();

    test_is_volatile<void (*)()>();
    test_is_volatile<void (*)() noexcept>();
    test_is_volatile<void (*)(int)>();
    test_is_volatile<void (*)(int) noexcept>();

    test_is_volatile<void (*)(...)>();
    test_is_volatile<void (*)(...) noexcept>();
    test_is_volatile<void (*)(int, ...)>();
    test_is_volatile<void (*)(int, ...) noexcept>();

    test_is_volatile<void (Class::*)()>();
    test_is_volatile<void (Class::*)()&>();
    test_is_volatile<void (Class::*)() &&>();
    test_is_volatile<void (Class::*)() const>();
    test_is_volatile<void (Class::*)() const&>();
    test_is_volatile<void (Class::*)() const&&>();

    test_is_volatile<void (Class::*)() noexcept>();
    test_is_volatile<void (Class::*)()& noexcept>();
    test_is_volatile<void (Class::*)()&& noexcept>();
    test_is_volatile<void (Class::*)() const noexcept>();
    test_is_volatile<void (Class::*)() const& noexcept>();
    test_is_volatile<void (Class::*)() const&& noexcept>();

    test_is_volatile<void (Class::*)(int)>();
    test_is_volatile<void (Class::*)(int)&>();
    test_is_volatile<void (Class::*)(int) &&>();
    test_is_volatile<void (Class::*)(int) const>();
    test_is_volatile<void (Class::*)(int) const&>();
    test_is_volatile<void (Class::*)(int) const&&>();

    test_is_volatile<void (Class::*)(int) noexcept>();
    test_is_volatile<void (Class::*)(int)& noexcept>();
    test_is_volatile<void (Class::*)(int)&& noexcept>();
    test_is_volatile<void (Class::*)(int) const noexcept>();
    test_is_volatile<void (Class::*)(int) const& noexcept>();
    test_is_volatile<void (Class::*)(int) const&& noexcept>();

    test_is_volatile<void (Class::*)(...)>();
    test_is_volatile<void (Class::*)(...)&>();
    test_is_volatile<void (Class::*)(...) &&>();
    test_is_volatile<void (Class::*)(...) const>();
    test_is_volatile<void (Class::*)(...) const&>();
    test_is_volatile<void (Class::*)(...) const&&>();

    test_is_volatile<void (Class::*)(...) noexcept>();
    test_is_volatile<void (Class::*)(...)& noexcept>();
    test_is_volatile<void (Class::*)(...)&& noexcept>();
    test_is_volatile<void (Class::*)(...) const noexcept>();
    test_is_volatile<void (Class::*)(...) const& noexcept>();
    test_is_volatile<void (Class::*)(...) const&& noexcept>();
}
