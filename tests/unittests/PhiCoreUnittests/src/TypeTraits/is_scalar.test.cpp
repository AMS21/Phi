#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_scalar.hpp>
#include <vector>

template <typename T>
void test_is_scalar()
{
    STATIC_REQUIRE(phi::is_scalar<T>::value);
    STATIC_REQUIRE(phi::is_scalar<const T>::value);
    STATIC_REQUIRE(phi::is_scalar<volatile T>::value);
    STATIC_REQUIRE(phi::is_scalar<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_scalar_v<T>);
    STATIC_REQUIRE(phi::is_scalar_v<const T>);
    STATIC_REQUIRE(phi::is_scalar_v<volatile T>);
    STATIC_REQUIRE(phi::is_scalar_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_scalar()
{
    STATIC_REQUIRE_FALSE(phi::is_scalar<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_scalar<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_scalar<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_scalar<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_scalar_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_scalar_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_scalar_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_scalar_v<const volatile T>);
#endif
}

TEST_CASE("is_scalar")
{
    test_is_scalar<phi::nullptr_t>();
    test_is_scalar<bool>();
    test_is_scalar<char>();
    test_is_scalar<signed char>();
    test_is_scalar<unsigned char>();
    test_is_scalar<short>();
    test_is_scalar<unsigned short>();
    test_is_scalar<int>();
    test_is_scalar<unsigned int>();
    test_is_scalar<long>();
    test_is_scalar<unsigned long>();
    test_is_scalar<long long>();
    test_is_scalar<unsigned long long>();
    test_is_scalar<float>();
    test_is_scalar<double>();
    test_is_scalar<long double>();
    test_is_scalar<char8_t>();
    test_is_scalar<char16_t>();
    test_is_scalar<char32_t>();
    test_is_scalar<wchar_t>();

    test_is_scalar<phi::Boolean>();
    test_is_scalar<phi::Integer<signed char>>();
    test_is_scalar<phi::Integer<unsigned char>>();
    test_is_scalar<phi::Integer<short>>();
    test_is_scalar<phi::Integer<unsigned short>>();
    test_is_scalar<phi::Integer<int>>();
    test_is_scalar<phi::Integer<unsigned int>>();
    test_is_scalar<phi::Integer<long>>();
    test_is_scalar<phi::Integer<unsigned long>>();
    test_is_scalar<phi::Integer<long long>>();
    test_is_scalar<phi::Integer<unsigned long long>>();
    test_is_scalar<phi::FloatingPoint<float>>();
    test_is_scalar<phi::FloatingPoint<double>>();
    test_is_scalar<phi::FloatingPoint<long double>>();

    test_is_scalar<int*>();
    test_is_scalar<const int*>();
    test_is_scalar<volatile int*>();
    test_is_scalar<const volatile int*>();
    test_is_scalar<int**>();

    test_is_not_scalar<void>();
    test_is_not_scalar<std::vector<int>>();
    test_is_not_scalar<phi::ScopePtr<int>>();

    test_is_not_scalar<int&>();
    test_is_not_scalar<int&&>();
    test_is_not_scalar<char[3]>();
    test_is_not_scalar<char[]>();
    test_is_not_scalar<char* [3]>();
    test_is_not_scalar<char*[]>();
    test_is_not_scalar<Class>();
    test_is_not_scalar<Struct>();
    test_is_not_scalar<Union>();
    test_is_not_scalar<NonEmptyUnion>();
    test_is_not_scalar<Empty>();
    test_is_not_scalar<NotEmpty>();
    test_is_not_scalar<bit_zero>();
    test_is_not_scalar<bit_one>();
    test_is_not_scalar<Abstract>();
    test_is_not_scalar<AbstractTemplate<int>>();
    test_is_not_scalar<AbstractTemplate<double>>();
    test_is_not_scalar<AbstractTemplate<Class>>();
    test_is_not_scalar<AbstractTemplate<incomplete_type>>();
    test_is_not_scalar<Final>();
    test_is_scalar<Enum>();
    test_is_scalar<EnumSigned>();
    test_is_scalar<EnumUnsigned>();
    test_is_scalar<EnumClass>();
    test_is_not_scalar<Function>();
    test_is_scalar<FunctionPtr>();
    test_is_scalar<MemberObjectPtr>();
    test_is_scalar<MemberFunctionPtr>();
    test_is_not_scalar<incomplete_type>();
    test_is_scalar<int Class::*>();
    test_is_scalar<float Class::*>();

    test_is_not_scalar<void()>();
    test_is_not_scalar<void() noexcept>();
    test_is_not_scalar<void(int)>();
    test_is_not_scalar<void(int) noexcept>();

    test_is_not_scalar<void(...)>();
    test_is_not_scalar<void(...) noexcept>();
    test_is_not_scalar<void(int, ...)>();
    test_is_not_scalar<void(int, ...) noexcept>();

    test_is_scalar<void (*)()>();
    test_is_scalar<void (*)() noexcept>();
    test_is_scalar<void (*)(int)>();
    test_is_scalar<void (*)(int) noexcept>();

    test_is_scalar<void (*)(...)>();
    test_is_scalar<void (*)(...) noexcept>();
    test_is_scalar<void (*)(int, ...)>();
    test_is_scalar<void (*)(int, ...) noexcept>();

    test_is_scalar<void (Class::*)()>();
    test_is_scalar<void (Class::*)()&>();
    test_is_scalar<void (Class::*)() &&>();
    test_is_scalar<void (Class::*)() const>();
    test_is_scalar<void (Class::*)() const&>();
    test_is_scalar<void (Class::*)() const&&>();

    test_is_scalar<void (Class::*)() noexcept>();
    test_is_scalar<void (Class::*)()& noexcept>();
    test_is_scalar<void (Class::*)()&& noexcept>();
    test_is_scalar<void (Class::*)() const noexcept>();
    test_is_scalar<void (Class::*)() const& noexcept>();
    test_is_scalar<void (Class::*)() const&& noexcept>();

    test_is_scalar<void (Class::*)(int)>();
    test_is_scalar<void (Class::*)(int)&>();
    test_is_scalar<void (Class::*)(int) &&>();
    test_is_scalar<void (Class::*)(int) const>();
    test_is_scalar<void (Class::*)(int) const&>();
    test_is_scalar<void (Class::*)(int) const&&>();

    test_is_scalar<void (Class::*)(int) noexcept>();
    test_is_scalar<void (Class::*)(int)& noexcept>();
    test_is_scalar<void (Class::*)(int)&& noexcept>();
    test_is_scalar<void (Class::*)(int) const noexcept>();
    test_is_scalar<void (Class::*)(int) const& noexcept>();
    test_is_scalar<void (Class::*)(int) const&& noexcept>();

    test_is_scalar<void (Class::*)(...)>();
    test_is_scalar<void (Class::*)(...)&>();
    test_is_scalar<void (Class::*)(...) &&>();
    test_is_scalar<void (Class::*)(...) const>();
    test_is_scalar<void (Class::*)(...) const&>();
    test_is_scalar<void (Class::*)(...) const&&>();

    test_is_scalar<void (Class::*)(...) noexcept>();
    test_is_scalar<void (Class::*)(...)& noexcept>();
    test_is_scalar<void (Class::*)(...)&& noexcept>();
    test_is_scalar<void (Class::*)(...) const noexcept>();
    test_is_scalar<void (Class::*)(...) const& noexcept>();
    test_is_scalar<void (Class::*)(...) const&& noexcept>();
}
