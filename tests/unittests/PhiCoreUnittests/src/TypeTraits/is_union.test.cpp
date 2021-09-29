#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_union.hpp>

template <typename T>
void test_is_union()
{
    STATIC_REQUIRE(phi::is_union<T>::value);
    STATIC_REQUIRE(phi::is_union<const T>::value);
    STATIC_REQUIRE(phi::is_union<volatile T>::value);
    STATIC_REQUIRE(phi::is_union<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_union_v<T>);
    STATIC_REQUIRE(phi::is_union_v<const T>);
    STATIC_REQUIRE(phi::is_union_v<volatile T>);
    STATIC_REQUIRE(phi::is_union_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_union()
{
    STATIC_REQUIRE_FALSE(phi::is_union<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_union<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_union<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_union<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_union_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_union_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_union_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_union_v<const volatile T>);
#endif
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
    test_is_not_union<void*>();
    test_is_not_union<char[3]>();
    test_is_not_union<char[]>();
    test_is_not_union<char* [3]>();
    test_is_not_union<char*[]>();
    test_is_not_union<Class>();
    test_is_not_union<Struct>();
    test_is_union<Union>();
    test_is_union<NonEmptyUnion>();
    test_is_not_union<Empty>();
    test_is_not_union<NotEmpty>();
    test_is_not_union<bit_zero>();
    test_is_not_union<bit_one>();
    test_is_not_union<Abstract>();
    test_is_not_union<AbstractTemplate<int>>();
    test_is_not_union<AbstractTemplate<double>>();
    test_is_not_union<AbstractTemplate<Class>>();
    test_is_not_union<AbstractTemplate<incomplete_type>>();
    test_is_not_union<Final>();
    test_is_not_union<Enum>();
    test_is_not_union<EnumSigned>();
    test_is_not_union<EnumUnsigned>();
    test_is_not_union<EnumClass>();
    test_is_not_union<Function>();
    test_is_not_union<FunctionPtr>();
    test_is_not_union<MemberObjectPtr>();
    test_is_not_union<MemberFunctionPtr>();
    test_is_not_union<incomplete_type>();
    test_is_not_union<int Class::*>();
    test_is_not_union<float Class::*>();

    test_is_not_union<void()>();
    test_is_not_union<void() noexcept>();
    test_is_not_union<void(int)>();
    test_is_not_union<void(int) noexcept>();

    test_is_not_union<void(...)>();
    test_is_not_union<void(...) noexcept>();
    test_is_not_union<void(int, ...)>();
    test_is_not_union<void(int, ...) noexcept>();

    test_is_not_union<void (*)()>();
    test_is_not_union<void (*)() noexcept>();
    test_is_not_union<void (*)(int)>();
    test_is_not_union<void (*)(int) noexcept>();

    test_is_not_union<void (*)(...)>();
    test_is_not_union<void (*)(...) noexcept>();
    test_is_not_union<void (*)(int, ...)>();
    test_is_not_union<void (*)(int, ...) noexcept>();

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
}
