#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_unbounded_array.hpp>
#include <vector>

template <typename T>
void test_is_unbounded_array()
{
    STATIC_REQUIRE(phi::is_unbounded_array<T>::value);
    STATIC_REQUIRE(phi::is_unbounded_array<const T>::value);
    STATIC_REQUIRE(phi::is_unbounded_array<volatile T>::value);
    STATIC_REQUIRE(phi::is_unbounded_array<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unbounded_array_v<T>);
    STATIC_REQUIRE(phi::is_unbounded_array_v<const T>);
    STATIC_REQUIRE(phi::is_unbounded_array_v<volatile T>);
    STATIC_REQUIRE(phi::is_unbounded_array_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_unbounded_array()
{
    STATIC_REQUIRE_FALSE(phi::is_unbounded_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unbounded_array<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unbounded_array<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unbounded_array<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unbounded_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_unbounded_array_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_unbounded_array_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_unbounded_array_v<const volatile T>);
#endif
}

class A
{};

TEST_CASE("type_traits is_unbounded_array", "[Core][TypeTraits][is_unbounded_array]")
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

    test_is_not_unbounded_array<phi::Boolean>();
    test_is_not_unbounded_array<phi::Integer<signed char>>();
    test_is_not_unbounded_array<phi::Integer<unsigned char>>();
    test_is_not_unbounded_array<phi::Integer<short>>();
    test_is_not_unbounded_array<phi::Integer<unsigned short>>();
    test_is_not_unbounded_array<phi::Integer<int>>();
    test_is_not_unbounded_array<phi::Integer<unsigned int>>();
    test_is_not_unbounded_array<phi::Integer<long>>();
    test_is_not_unbounded_array<phi::Integer<unsigned long>>();
    test_is_not_unbounded_array<phi::Integer<long long>>();
    test_is_not_unbounded_array<phi::Integer<unsigned long long>>();
    test_is_not_unbounded_array<phi::FloatingPoint<float>>();
    test_is_not_unbounded_array<phi::FloatingPoint<double>>();
    test_is_not_unbounded_array<phi::FloatingPoint<long double>>();

    test_is_not_unbounded_array<std::vector<int>>();
    test_is_not_unbounded_array<phi::ScopePtr<int>>();

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
    test_is_not_unbounded_array<void*>();
    test_is_not_unbounded_array<char[3]>();
    test_is_unbounded_array<char[]>();
    test_is_not_unbounded_array<char* [3]>();
    test_is_unbounded_array<char*[]>();
    test_is_not_unbounded_array<Class>();
    test_is_not_unbounded_array<Union>();
    test_is_not_unbounded_array<NonEmptyUnion>();
    test_is_not_unbounded_array<Empty>();
    test_is_not_unbounded_array<NotEmpty>();
    test_is_not_unbounded_array<bit_zero>();
    test_is_not_unbounded_array<bit_one>();
    test_is_not_unbounded_array<Abstract>();
    test_is_not_unbounded_array<AbstractTemplate<int>>();
    test_is_not_unbounded_array<AbstractTemplate<double>>();
    test_is_not_unbounded_array<AbstractTemplate<Class>>();
    test_is_not_unbounded_array<AbstractTemplate<incomplete_type>>();
    test_is_not_unbounded_array<Final>();
    test_is_not_unbounded_array<Enum>();
    test_is_not_unbounded_array<EnumSigned>();
    test_is_not_unbounded_array<EnumUnsigned>();
    test_is_not_unbounded_array<EnumClass>();
    test_is_not_unbounded_array<Function>();
    test_is_not_unbounded_array<FunctionPtr>();
    test_is_not_unbounded_array<MemberObjectPtr>();
    test_is_not_unbounded_array<MemberFunctionPtr>();
    test_is_not_unbounded_array<incomplete_type>();
    test_is_not_unbounded_array<int Class::*>();
    test_is_not_unbounded_array<float Class::*>();

    test_is_not_unbounded_array<void()>();
    test_is_not_unbounded_array<void() noexcept>();
    test_is_not_unbounded_array<void(int)>();
    test_is_not_unbounded_array<void(int) noexcept>();

    test_is_not_unbounded_array<void(...)>();
    test_is_not_unbounded_array<void(...) noexcept>();
    test_is_not_unbounded_array<void(int, ...)>();
    test_is_not_unbounded_array<void(int, ...) noexcept>();

    test_is_not_unbounded_array<void (*)()>();
    test_is_not_unbounded_array<void (*)() noexcept>();
    test_is_not_unbounded_array<void (*)(int)>();
    test_is_not_unbounded_array<void (*)(int) noexcept>();

    test_is_not_unbounded_array<void (*)(...)>();
    test_is_not_unbounded_array<void (*)(...) noexcept>();
    test_is_not_unbounded_array<void (*)(int, ...)>();
    test_is_not_unbounded_array<void (*)(int, ...) noexcept>();

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
}
