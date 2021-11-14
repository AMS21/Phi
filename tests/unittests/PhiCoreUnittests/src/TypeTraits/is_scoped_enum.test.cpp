#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_scoped_enum.hpp>
#include <vector>

template <typename T>
void test_is_scoped_enum()
{
    STATIC_REQUIRE(phi::is_scoped_enum<T>::value);
    STATIC_REQUIRE(phi::is_scoped_enum<const T>::value);
    STATIC_REQUIRE(phi::is_scoped_enum<volatile T>::value);
    STATIC_REQUIRE(phi::is_scoped_enum<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_scoped_enum_v<T>);
    STATIC_REQUIRE(phi::is_scoped_enum_v<const T>);
    STATIC_REQUIRE(phi::is_scoped_enum_v<volatile T>);
    STATIC_REQUIRE(phi::is_scoped_enum_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_scoped_enum()
{
    STATIC_REQUIRE_FALSE(phi::is_scoped_enum<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_scoped_enum<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_scoped_enum<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_scoped_enum<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_scoped_enum_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_scoped_enum_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_scoped_enum_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_scoped_enum_v<const volatile T>);
#endif
}

class A
{};

enum E
{
};

enum struct EStruct
{
};

enum class EClass
{
};

TEST_CASE("type_traits is_scoped_enum", "[Core][TypeTraits][is_scoped_enum]")
{
    test_is_scoped_enum<EStruct>();
    test_is_scoped_enum<EClass>();

    test_is_not_scoped_enum<A>();
    test_is_not_scoped_enum<E>();

    test_is_not_scoped_enum<void>();
    test_is_not_scoped_enum<phi::nullptr_t>();
    test_is_not_scoped_enum<bool>();
    test_is_not_scoped_enum<char>();
    test_is_not_scoped_enum<signed char>();
    test_is_not_scoped_enum<unsigned char>();
    test_is_not_scoped_enum<short>();
    test_is_not_scoped_enum<unsigned short>();
    test_is_not_scoped_enum<int>();
    test_is_not_scoped_enum<unsigned int>();
    test_is_not_scoped_enum<long>();
    test_is_not_scoped_enum<unsigned long>();
    test_is_not_scoped_enum<long long>();
    test_is_not_scoped_enum<unsigned long long>();
    test_is_not_scoped_enum<float>();
    test_is_not_scoped_enum<double>();
    test_is_not_scoped_enum<long double>();
    test_is_not_scoped_enum<char8_t>();
    test_is_not_scoped_enum<char16_t>();
    test_is_not_scoped_enum<char32_t>();
    test_is_not_scoped_enum<wchar_t>();

    test_is_not_scoped_enum<phi::Boolean>();
    test_is_not_scoped_enum<phi::Integer<signed char>>();
    test_is_not_scoped_enum<phi::Integer<unsigned char>>();
    test_is_not_scoped_enum<phi::Integer<short>>();
    test_is_not_scoped_enum<phi::Integer<unsigned short>>();
    test_is_not_scoped_enum<phi::Integer<int>>();
    test_is_not_scoped_enum<phi::Integer<unsigned int>>();
    test_is_not_scoped_enum<phi::Integer<long>>();
    test_is_not_scoped_enum<phi::Integer<unsigned long>>();
    test_is_not_scoped_enum<phi::Integer<long long>>();
    test_is_not_scoped_enum<phi::Integer<unsigned long long>>();
    test_is_not_scoped_enum<phi::FloatingPoint<float>>();
    test_is_not_scoped_enum<phi::FloatingPoint<double>>();
    test_is_not_scoped_enum<phi::FloatingPoint<long double>>();

    test_is_not_scoped_enum<std::vector<int>>();
    test_is_not_scoped_enum<phi::ScopePtr<int>>();

    test_is_not_scoped_enum<int&>();
    test_is_not_scoped_enum<int&&>();
    test_is_not_scoped_enum<int*>();
    test_is_not_scoped_enum<const int*>();
    test_is_not_scoped_enum<volatile int*>();
    test_is_not_scoped_enum<const volatile int*>();
    test_is_not_scoped_enum<int**>();
    test_is_not_scoped_enum<char[3]>();
    test_is_not_scoped_enum<char[]>();
    test_is_not_scoped_enum<char* [3]>();
    test_is_not_scoped_enum<char*[]>();
    test_is_not_scoped_enum<Class>();
    test_is_not_scoped_enum<Union>();
    test_is_not_scoped_enum<NonEmptyUnion>();
    test_is_not_scoped_enum<Empty>();
    test_is_not_scoped_enum<NotEmpty>();
    test_is_not_scoped_enum<bit_zero>();
    test_is_not_scoped_enum<bit_one>();
    test_is_not_scoped_enum<Abstract>();
    test_is_not_scoped_enum<AbstractTemplate<int>>();
    test_is_not_scoped_enum<AbstractTemplate<double>>();
    test_is_not_scoped_enum<AbstractTemplate<Class>>();
    test_is_not_scoped_enum<AbstractTemplate<incomplete_type>>();
    test_is_not_scoped_enum<Final>();
    test_is_not_scoped_enum<Enum>();
    test_is_not_scoped_enum<EnumSigned>();
    test_is_not_scoped_enum<EnumUnsigned>();
    test_is_scoped_enum<EnumClass>();
    test_is_not_scoped_enum<Function>();
    test_is_not_scoped_enum<FunctionPtr>();
    test_is_not_scoped_enum<MemberObjectPtr>();
    test_is_not_scoped_enum<MemberFunctionPtr>();
    test_is_not_scoped_enum<incomplete_type>();
    test_is_not_scoped_enum<int Class::*>();
    test_is_not_scoped_enum<float Class::*>();

    test_is_not_scoped_enum<void()>();
    test_is_not_scoped_enum<void() noexcept>();
    test_is_not_scoped_enum<void(int)>();
    test_is_not_scoped_enum<void(int) noexcept>();

    test_is_not_scoped_enum<void(...)>();
    test_is_not_scoped_enum<void(...) noexcept>();
    test_is_not_scoped_enum<void(int, ...)>();
    test_is_not_scoped_enum<void(int, ...) noexcept>();

    test_is_not_scoped_enum<void (*)()>();
    test_is_not_scoped_enum<void (*)() noexcept>();
    test_is_not_scoped_enum<void (*)(int)>();
    test_is_not_scoped_enum<void (*)(int) noexcept>();

    test_is_not_scoped_enum<void (*)(...)>();
    test_is_not_scoped_enum<void (*)(...) noexcept>();
    test_is_not_scoped_enum<void (*)(int, ...)>();
    test_is_not_scoped_enum<void (*)(int, ...) noexcept>();

    test_is_not_scoped_enum<void (Class::*)()>();
    test_is_not_scoped_enum<void (Class::*)()&>();
    test_is_not_scoped_enum<void (Class::*)() &&>();
    test_is_not_scoped_enum<void (Class::*)() const>();
    test_is_not_scoped_enum<void (Class::*)() const&>();
    test_is_not_scoped_enum<void (Class::*)() const&&>();

    test_is_not_scoped_enum<void (Class::*)() noexcept>();
    test_is_not_scoped_enum<void (Class::*)()& noexcept>();
    test_is_not_scoped_enum<void (Class::*)()&& noexcept>();
    test_is_not_scoped_enum<void (Class::*)() const noexcept>();
    test_is_not_scoped_enum<void (Class::*)() const& noexcept>();
    test_is_not_scoped_enum<void (Class::*)() const&& noexcept>();

    test_is_not_scoped_enum<void (Class::*)(int)>();
    test_is_not_scoped_enum<void (Class::*)(int)&>();
    test_is_not_scoped_enum<void (Class::*)(int) &&>();
    test_is_not_scoped_enum<void (Class::*)(int) const>();
    test_is_not_scoped_enum<void (Class::*)(int) const&>();
    test_is_not_scoped_enum<void (Class::*)(int) const&&>();

    test_is_not_scoped_enum<void (Class::*)(int) noexcept>();
    test_is_not_scoped_enum<void (Class::*)(int)& noexcept>();
    test_is_not_scoped_enum<void (Class::*)(int)&& noexcept>();
    test_is_not_scoped_enum<void (Class::*)(int) const noexcept>();
    test_is_not_scoped_enum<void (Class::*)(int) const& noexcept>();
    test_is_not_scoped_enum<void (Class::*)(int) const&& noexcept>();

    test_is_not_scoped_enum<void (Class::*)(...)>();
    test_is_not_scoped_enum<void (Class::*)(...)&>();
    test_is_not_scoped_enum<void (Class::*)(...) &&>();
    test_is_not_scoped_enum<void (Class::*)(...) const>();
    test_is_not_scoped_enum<void (Class::*)(...) const&>();
    test_is_not_scoped_enum<void (Class::*)(...) const&&>();

    test_is_not_scoped_enum<void (Class::*)(...) noexcept>();
    test_is_not_scoped_enum<void (Class::*)(...)& noexcept>();
    test_is_not_scoped_enum<void (Class::*)(...)&& noexcept>();
    test_is_not_scoped_enum<void (Class::*)(...) const noexcept>();
    test_is_not_scoped_enum<void (Class::*)(...) const& noexcept>();
    test_is_not_scoped_enum<void (Class::*)(...) const&& noexcept>();
}
