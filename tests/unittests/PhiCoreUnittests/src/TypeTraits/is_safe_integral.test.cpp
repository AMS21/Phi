#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_safe_integral.hpp>
#include <vector>

template <typename T>
void test_is_safe_integral()
{
    STATIC_REQUIRE(phi::is_safe_integral<T>::value);
    STATIC_REQUIRE(phi::is_safe_integral<const T>::value);
    STATIC_REQUIRE(phi::is_safe_integral<volatile T>::value);
    STATIC_REQUIRE(phi::is_safe_integral<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_safe_integral_v<T>);
    STATIC_REQUIRE(phi::is_safe_integral_v<const T>);
    STATIC_REQUIRE(phi::is_safe_integral_v<volatile T>);
    STATIC_REQUIRE(phi::is_safe_integral_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_safe_integral()
{
    STATIC_REQUIRE_FALSE(phi::is_safe_integral<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_safe_integral<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_safe_integral<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_safe_integral<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_integral_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_safe_integral_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_safe_integral_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_safe_integral_v<const volatile T>);
#endif
}

TEST_CASE("is_safe_integral")
{
    test_is_safe_integral<phi::Boolean>();
    test_is_safe_integral<phi::Integer<signed char>>();
    test_is_safe_integral<phi::Integer<unsigned char>>();
    test_is_safe_integral<phi::Integer<short>>();
    test_is_safe_integral<phi::Integer<unsigned short>>();
    test_is_safe_integral<phi::Integer<int>>();
    test_is_safe_integral<phi::Integer<unsigned int>>();
    test_is_safe_integral<phi::Integer<long>>();
    test_is_safe_integral<phi::Integer<unsigned long>>();
    test_is_safe_integral<phi::Integer<long long>>();
    test_is_safe_integral<phi::Integer<unsigned long long>>();

    test_is_not_safe_integral<void>();
    test_is_not_safe_integral<phi::nullptr_t>();
    test_is_not_safe_integral<bool>();
    test_is_not_safe_integral<char>();
    test_is_not_safe_integral<signed char>();
    test_is_not_safe_integral<unsigned char>();
    test_is_not_safe_integral<short>();
    test_is_not_safe_integral<unsigned short>();
    test_is_not_safe_integral<int>();
    test_is_not_safe_integral<unsigned int>();
    test_is_not_safe_integral<long>();
    test_is_not_safe_integral<unsigned long>();
    test_is_not_safe_integral<long long>();
    test_is_not_safe_integral<unsigned long long>();
    test_is_not_safe_integral<float>();
    test_is_not_safe_integral<double>();
    test_is_not_safe_integral<long double>();
    test_is_not_safe_integral<char8_t>();
    test_is_not_safe_integral<char16_t>();
    test_is_not_safe_integral<char32_t>();
    test_is_not_safe_integral<wchar_t>();

    test_is_not_safe_integral<phi::FloatingPoint<float>>();
    test_is_not_safe_integral<phi::FloatingPoint<double>>();
    test_is_not_safe_integral<phi::FloatingPoint<long double>>();

    test_is_not_safe_integral<std::vector<int>>();
    test_is_not_safe_integral<phi::ScopePtr<int>>();

    test_is_not_safe_integral<int&>();
    test_is_not_safe_integral<int&&>();
    test_is_not_safe_integral<int*>();
    test_is_not_safe_integral<const int*>();
    test_is_not_safe_integral<volatile int*>();
    test_is_not_safe_integral<const volatile int*>();
    test_is_not_safe_integral<int**>();
    test_is_not_safe_integral<char[3]>();
    test_is_not_safe_integral<char[]>();
    test_is_not_safe_integral<char* [3]>();
    test_is_not_safe_integral<char*[]>();
    test_is_not_safe_integral<Class>();
    test_is_not_safe_integral<Struct>();
    test_is_not_safe_integral<Union>();
    test_is_not_safe_integral<NonEmptyUnion>();
    test_is_not_safe_integral<Empty>();
    test_is_not_safe_integral<NotEmpty>();
    test_is_not_safe_integral<bit_zero>();
    test_is_not_safe_integral<bit_one>();
    test_is_not_safe_integral<Abstract>();
    test_is_not_safe_integral<AbstractTemplate<int>>();
    test_is_not_safe_integral<AbstractTemplate<double>>();
    test_is_not_safe_integral<AbstractTemplate<Class>>();
    test_is_not_safe_integral<AbstractTemplate<incomplete_type>>();
    test_is_not_safe_integral<Final>();
    test_is_not_safe_integral<Enum>();
    test_is_not_safe_integral<EnumSigned>();
    test_is_not_safe_integral<EnumUnsigned>();
    test_is_not_safe_integral<EnumClass>();
    test_is_not_safe_integral<Function>();
    test_is_not_safe_integral<FunctionPtr>();
    test_is_not_safe_integral<MemberObjectPtr>();
    test_is_not_safe_integral<MemberFunctionPtr>();
    test_is_not_safe_integral<incomplete_type>();
    test_is_not_safe_integral<int Class::*>();
    test_is_not_safe_integral<float Class::*>();

    test_is_not_safe_integral<void()>();
    test_is_not_safe_integral<void() noexcept>();
    test_is_not_safe_integral<void(int)>();
    test_is_not_safe_integral<void(int) noexcept>();

    test_is_not_safe_integral<void(...)>();
    test_is_not_safe_integral<void(...) noexcept>();
    test_is_not_safe_integral<void(int, ...)>();
    test_is_not_safe_integral<void(int, ...) noexcept>();

    test_is_not_safe_integral<void (*)()>();
    test_is_not_safe_integral<void (*)() noexcept>();
    test_is_not_safe_integral<void (*)(int)>();
    test_is_not_safe_integral<void (*)(int) noexcept>();

    test_is_not_safe_integral<void (*)(...)>();
    test_is_not_safe_integral<void (*)(...) noexcept>();
    test_is_not_safe_integral<void (*)(int, ...)>();
    test_is_not_safe_integral<void (*)(int, ...) noexcept>();

    test_is_not_safe_integral<void (Class::*)()>();
    test_is_not_safe_integral<void (Class::*)()&>();
    test_is_not_safe_integral<void (Class::*)() &&>();
    test_is_not_safe_integral<void (Class::*)() const>();
    test_is_not_safe_integral<void (Class::*)() const&>();
    test_is_not_safe_integral<void (Class::*)() const&&>();

    test_is_not_safe_integral<void (Class::*)() noexcept>();
    test_is_not_safe_integral<void (Class::*)()& noexcept>();
    test_is_not_safe_integral<void (Class::*)()&& noexcept>();
    test_is_not_safe_integral<void (Class::*)() const noexcept>();
    test_is_not_safe_integral<void (Class::*)() const& noexcept>();
    test_is_not_safe_integral<void (Class::*)() const&& noexcept>();

    test_is_not_safe_integral<void (Class::*)(int)>();
    test_is_not_safe_integral<void (Class::*)(int)&>();
    test_is_not_safe_integral<void (Class::*)(int) &&>();
    test_is_not_safe_integral<void (Class::*)(int) const>();
    test_is_not_safe_integral<void (Class::*)(int) const&>();
    test_is_not_safe_integral<void (Class::*)(int) const&&>();

    test_is_not_safe_integral<void (Class::*)(int) noexcept>();
    test_is_not_safe_integral<void (Class::*)(int)& noexcept>();
    test_is_not_safe_integral<void (Class::*)(int)&& noexcept>();
    test_is_not_safe_integral<void (Class::*)(int) const noexcept>();
    test_is_not_safe_integral<void (Class::*)(int) const& noexcept>();
    test_is_not_safe_integral<void (Class::*)(int) const&& noexcept>();

    test_is_not_safe_integral<void (Class::*)(...)>();
    test_is_not_safe_integral<void (Class::*)(...)&>();
    test_is_not_safe_integral<void (Class::*)(...) &&>();
    test_is_not_safe_integral<void (Class::*)(...) const>();
    test_is_not_safe_integral<void (Class::*)(...) const&>();
    test_is_not_safe_integral<void (Class::*)(...) const&&>();

    test_is_not_safe_integral<void (Class::*)(...) noexcept>();
    test_is_not_safe_integral<void (Class::*)(...)& noexcept>();
    test_is_not_safe_integral<void (Class::*)(...)&& noexcept>();
    test_is_not_safe_integral<void (Class::*)(...) const noexcept>();
    test_is_not_safe_integral<void (Class::*)(...) const& noexcept>();
    test_is_not_safe_integral<void (Class::*)(...) const&& noexcept>();
}
