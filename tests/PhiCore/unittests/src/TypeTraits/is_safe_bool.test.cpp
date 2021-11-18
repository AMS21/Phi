#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_safe_bool.hpp>

template <typename T>
void test_is_safe_bool()
{
    STATIC_REQUIRE(phi::is_safe_bool<T>::value);
    STATIC_REQUIRE(phi::is_safe_bool<const T>::value);
    STATIC_REQUIRE(phi::is_safe_bool<volatile T>::value);
    STATIC_REQUIRE(phi::is_safe_bool<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_safe_bool_v<T>);
    STATIC_REQUIRE(phi::is_safe_bool_v<const T>);
    STATIC_REQUIRE(phi::is_safe_bool_v<volatile T>);
    STATIC_REQUIRE(phi::is_safe_bool_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_safe_bool()
{
    STATIC_REQUIRE_FALSE(phi::is_safe_bool<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_safe_bool<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_safe_bool<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_safe_bool<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_bool_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_safe_bool_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_safe_bool_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_safe_bool_v<const volatile T>);
#endif
}

TEST_CASE("is_safe_bool")
{
    test_is_safe_bool<phi::Boolean>();

    test_is_not_safe_bool<void>();
    test_is_not_safe_bool<bool>();
    test_is_not_safe_bool<char>();
    test_is_not_safe_bool<signed char>();
    test_is_not_safe_bool<unsigned char>();
    test_is_not_safe_bool<short>();
    test_is_not_safe_bool<unsigned short>();
    test_is_not_safe_bool<int>();
    test_is_not_safe_bool<unsigned int>();
    test_is_not_safe_bool<long>();
    test_is_not_safe_bool<unsigned long>();
    test_is_not_safe_bool<long long>();
    test_is_not_safe_bool<unsigned long long>();
    test_is_not_safe_bool<float>();
    test_is_not_safe_bool<double>();
    test_is_not_safe_bool<long double>();
    test_is_not_safe_bool<char8_t>();
    test_is_not_safe_bool<char16_t>();
    test_is_not_safe_bool<char32_t>();
    test_is_not_safe_bool<wchar_t>();

    test_is_not_safe_bool<phi::Integer<signed char>>();
    test_is_not_safe_bool<phi::Integer<unsigned char>>();
    test_is_not_safe_bool<phi::Integer<short>>();
    test_is_not_safe_bool<phi::Integer<unsigned short>>();
    test_is_not_safe_bool<phi::Integer<int>>();
    test_is_not_safe_bool<phi::Integer<unsigned int>>();
    test_is_not_safe_bool<phi::Integer<long>>();
    test_is_not_safe_bool<phi::Integer<unsigned long>>();
    test_is_not_safe_bool<phi::Integer<long long>>();
    test_is_not_safe_bool<phi::Integer<unsigned long long>>();
    test_is_not_safe_bool<phi::FloatingPoint<float>>();
    test_is_not_safe_bool<phi::FloatingPoint<double>>();
    test_is_not_safe_bool<phi::FloatingPoint<long double>>();

    test_is_not_safe_bool<int&>();
    test_is_not_safe_bool<int&&>();
    test_is_not_safe_bool<int*>();
    test_is_not_safe_bool<const int*>();
    test_is_not_safe_bool<volatile int*>();
    test_is_not_safe_bool<const volatile int*>();
    test_is_not_safe_bool<int**>();
    test_is_not_safe_bool<char[3]>();
    test_is_not_safe_bool<char[]>();
    test_is_not_safe_bool<char* [3]>();
    test_is_not_safe_bool<char*[]>();
    test_is_not_safe_bool<Class>();
    test_is_not_safe_bool<Union>();
    test_is_not_safe_bool<NonEmptyUnion>();
    test_is_not_safe_bool<Empty>();
    test_is_not_safe_bool<NotEmpty>();
    test_is_not_safe_bool<bit_zero>();
    test_is_not_safe_bool<bit_one>();
    test_is_not_safe_bool<Abstract>();
    test_is_not_safe_bool<AbstractTemplate<int>>();
    test_is_not_safe_bool<AbstractTemplate<double>>();
    test_is_not_safe_bool<AbstractTemplate<Class>>();
    test_is_not_safe_bool<AbstractTemplate<incomplete_type>>();
    test_is_not_safe_bool<Final>();
    test_is_not_safe_bool<Enum>();
    test_is_not_safe_bool<EnumSigned>();
    test_is_not_safe_bool<EnumUnsigned>();
    test_is_not_safe_bool<EnumClass>();
    test_is_not_safe_bool<Function>();
    test_is_not_safe_bool<FunctionPtr>();
    test_is_not_safe_bool<MemberObjectPtr>();
    test_is_not_safe_bool<MemberFunctionPtr>();
    test_is_not_safe_bool<incomplete_type>();
    test_is_not_safe_bool<int Class::*>();
    test_is_not_safe_bool<float Class::*>();

    test_is_not_safe_bool<void()>();
    test_is_not_safe_bool<void() noexcept>();
    test_is_not_safe_bool<void(int)>();
    test_is_not_safe_bool<void(int) noexcept>();

    test_is_not_safe_bool<void(...)>();
    test_is_not_safe_bool<void(...) noexcept>();
    test_is_not_safe_bool<void(int, ...)>();
    test_is_not_safe_bool<void(int, ...) noexcept>();

    test_is_not_safe_bool<void (*)()>();
    test_is_not_safe_bool<void (*)() noexcept>();
    test_is_not_safe_bool<void (*)(int)>();
    test_is_not_safe_bool<void (*)(int) noexcept>();

    test_is_not_safe_bool<void (*)(...)>();
    test_is_not_safe_bool<void (*)(...) noexcept>();
    test_is_not_safe_bool<void (*)(int, ...)>();
    test_is_not_safe_bool<void (*)(int, ...) noexcept>();

    test_is_not_safe_bool<void (Class::*)()>();
    test_is_not_safe_bool<void (Class::*)()&>();
    test_is_not_safe_bool<void (Class::*)() &&>();
    test_is_not_safe_bool<void (Class::*)() const>();
    test_is_not_safe_bool<void (Class::*)() const&>();
    test_is_not_safe_bool<void (Class::*)() const&&>();

    test_is_not_safe_bool<void (Class::*)() noexcept>();
    test_is_not_safe_bool<void (Class::*)()& noexcept>();
    test_is_not_safe_bool<void (Class::*)()&& noexcept>();
    test_is_not_safe_bool<void (Class::*)() const noexcept>();
    test_is_not_safe_bool<void (Class::*)() const& noexcept>();
    test_is_not_safe_bool<void (Class::*)() const&& noexcept>();

    test_is_not_safe_bool<void (Class::*)(int)>();
    test_is_not_safe_bool<void (Class::*)(int)&>();
    test_is_not_safe_bool<void (Class::*)(int) &&>();
    test_is_not_safe_bool<void (Class::*)(int) const>();
    test_is_not_safe_bool<void (Class::*)(int) const&>();
    test_is_not_safe_bool<void (Class::*)(int) const&&>();

    test_is_not_safe_bool<void (Class::*)(int) noexcept>();
    test_is_not_safe_bool<void (Class::*)(int)& noexcept>();
    test_is_not_safe_bool<void (Class::*)(int)&& noexcept>();
    test_is_not_safe_bool<void (Class::*)(int) const noexcept>();
    test_is_not_safe_bool<void (Class::*)(int) const& noexcept>();
    test_is_not_safe_bool<void (Class::*)(int) const&& noexcept>();

    test_is_not_safe_bool<void (Class::*)(...)>();
    test_is_not_safe_bool<void (Class::*)(...)&>();
    test_is_not_safe_bool<void (Class::*)(...) &&>();
    test_is_not_safe_bool<void (Class::*)(...) const>();
    test_is_not_safe_bool<void (Class::*)(...) const&>();
    test_is_not_safe_bool<void (Class::*)(...) const&&>();

    test_is_not_safe_bool<void (Class::*)(...) noexcept>();
    test_is_not_safe_bool<void (Class::*)(...)& noexcept>();
    test_is_not_safe_bool<void (Class::*)(...)&& noexcept>();
    test_is_not_safe_bool<void (Class::*)(...) const noexcept>();
    test_is_not_safe_bool<void (Class::*)(...) const& noexcept>();
    test_is_not_safe_bool<void (Class::*)(...) const&& noexcept>();
}
