#include <Phi/Test/TestMacros.hpp>

#include "Phi/CompilerSupport/Char8_t.hpp"
#include "Phi/Core/Nullptr.hpp"
#include "Phi/Math/Abs.hpp"
#include "TestTypes.hpp"
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/TypeTraits/is_safe_arithmetic.hpp>

template <typename T>
void test_is_safe_arithmetic()
{
    STATIC_REQUIRE(phi::is_safe_arithmetic<T>::value);
    STATIC_REQUIRE(phi::is_safe_arithmetic<const T>::value);
    STATIC_REQUIRE(phi::is_safe_arithmetic<volatile T>::value);
    STATIC_REQUIRE(phi::is_safe_arithmetic<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_safe_arithmetic_v<T>);
    STATIC_REQUIRE(phi::is_safe_arithmetic_v<const T>);
    STATIC_REQUIRE(phi::is_safe_arithmetic_v<volatile T>);
    STATIC_REQUIRE(phi::is_safe_arithmetic_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_safe_arithmetic()
{
    STATIC_REQUIRE_FALSE(phi::is_safe_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_safe_arithmetic<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_safe_arithmetic<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_safe_arithmetic<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_safe_arithmetic_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_safe_arithmetic_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_safe_arithmetic_v<const volatile T>);
#endif
}

TEST_CASE("is_safe_arithmetic")
{
    test_is_safe_arithmetic<phi::Boolean>();
    test_is_safe_arithmetic<phi::Integer<signed char>>();
    test_is_safe_arithmetic<phi::Integer<unsigned char>>();
    test_is_safe_arithmetic<phi::Integer<short>>();
    test_is_safe_arithmetic<phi::Integer<unsigned short>>();
    test_is_safe_arithmetic<phi::Integer<int>>();
    test_is_safe_arithmetic<phi::Integer<unsigned int>>();
    test_is_safe_arithmetic<phi::Integer<long>>();
    test_is_safe_arithmetic<phi::Integer<unsigned long>>();
    test_is_safe_arithmetic<phi::Integer<long long>>();
    test_is_safe_arithmetic<phi::Integer<unsigned long long>>();
    test_is_safe_arithmetic<phi::FloatingPoint<float>>();
    test_is_safe_arithmetic<phi::FloatingPoint<double>>();
    test_is_safe_arithmetic<phi::FloatingPoint<long double>>();

    test_is_not_safe_arithmetic<void>();
    test_is_not_safe_arithmetic<phi::nullptr_t>();
    test_is_not_safe_arithmetic<bool>();
    test_is_not_safe_arithmetic<char>();
    test_is_not_safe_arithmetic<signed char>();
    test_is_not_safe_arithmetic<unsigned char>();
    test_is_not_safe_arithmetic<short>();
    test_is_not_safe_arithmetic<unsigned short>();
    test_is_not_safe_arithmetic<int>();
    test_is_not_safe_arithmetic<unsigned int>();
    test_is_not_safe_arithmetic<long>();
    test_is_not_safe_arithmetic<unsigned long>();
    test_is_not_safe_arithmetic<long long>();
    test_is_not_safe_arithmetic<unsigned long long>();
    test_is_not_safe_arithmetic<float>();
    test_is_not_safe_arithmetic<double>();
    test_is_not_safe_arithmetic<long double>();
    test_is_not_safe_arithmetic<char8_t>();
    test_is_not_safe_arithmetic<char16_t>();
    test_is_not_safe_arithmetic<char32_t>();
    test_is_not_safe_arithmetic<wchar_t>();

    test_is_not_safe_arithmetic<int&>();
    test_is_not_safe_arithmetic<int&&>();
    test_is_not_safe_arithmetic<int*>();
    test_is_not_safe_arithmetic<const int*>();
    test_is_not_safe_arithmetic<volatile int*>();
    test_is_not_safe_arithmetic<const volatile int*>();
    test_is_not_safe_arithmetic<int**>();
    test_is_not_safe_arithmetic<char[3]>();
    test_is_not_safe_arithmetic<char[]>();
    test_is_not_safe_arithmetic<char* [3]>();
    test_is_not_safe_arithmetic<char*[]>();
    test_is_not_safe_arithmetic<Class>();
    test_is_not_safe_arithmetic<Union>();
    test_is_not_safe_arithmetic<NonEmptyUnion>();
    test_is_not_safe_arithmetic<Empty>();
    test_is_not_safe_arithmetic<NotEmpty>();
    test_is_not_safe_arithmetic<bit_zero>();
    test_is_not_safe_arithmetic<bit_one>();
    test_is_not_safe_arithmetic<Abstract>();
    test_is_not_safe_arithmetic<AbstractTemplate<int>>();
    test_is_not_safe_arithmetic<AbstractTemplate<double>>();
    test_is_not_safe_arithmetic<AbstractTemplate<Class>>();
    test_is_not_safe_arithmetic<AbstractTemplate<incomplete_type>>();
    test_is_not_safe_arithmetic<Final>();
    test_is_not_safe_arithmetic<Enum>();
    test_is_not_safe_arithmetic<EnumSigned>();
    test_is_not_safe_arithmetic<EnumUnsigned>();
    test_is_not_safe_arithmetic<EnumClass>();
    test_is_not_safe_arithmetic<Function>();
    test_is_not_safe_arithmetic<FunctionPtr>();
    test_is_not_safe_arithmetic<MemberObjectPtr>();
    test_is_not_safe_arithmetic<MemberFunctionPtr>();
    test_is_not_safe_arithmetic<incomplete_type>();

    test_is_not_safe_arithmetic<void()>();
    test_is_not_safe_arithmetic<void() noexcept>();
    test_is_not_safe_arithmetic<void(int)>();
    test_is_not_safe_arithmetic<void(int) noexcept>();

    test_is_not_safe_arithmetic<void(...)>();
    test_is_not_safe_arithmetic<void(...) noexcept>();
    test_is_not_safe_arithmetic<void(int, ...)>();
    test_is_not_safe_arithmetic<void(int, ...) noexcept>();

    test_is_not_safe_arithmetic<void (*)()>();
    test_is_not_safe_arithmetic<void (*)() noexcept>();
    test_is_not_safe_arithmetic<void (*)(int)>();
    test_is_not_safe_arithmetic<void (*)(int) noexcept>();

    test_is_not_safe_arithmetic<void (*)(...)>();
    test_is_not_safe_arithmetic<void (*)(...) noexcept>();
    test_is_not_safe_arithmetic<void (*)(int, ...)>();
    test_is_not_safe_arithmetic<void (*)(int, ...) noexcept>();

    test_is_not_safe_arithmetic<void (Class::*)()>();
    test_is_not_safe_arithmetic<void (Class::*)()&>();
    test_is_not_safe_arithmetic<void (Class::*)() &&>();
    test_is_not_safe_arithmetic<void (Class::*)() const>();
    test_is_not_safe_arithmetic<void (Class::*)() const&>();
    test_is_not_safe_arithmetic<void (Class::*)() const&&>();

    test_is_not_safe_arithmetic<void (Class::*)() noexcept>();
    test_is_not_safe_arithmetic<void (Class::*)()& noexcept>();
    test_is_not_safe_arithmetic<void (Class::*)()&& noexcept>();
    test_is_not_safe_arithmetic<void (Class::*)() const noexcept>();
    test_is_not_safe_arithmetic<void (Class::*)() const& noexcept>();
    test_is_not_safe_arithmetic<void (Class::*)() const&& noexcept>();

    test_is_not_safe_arithmetic<void (Class::*)(int)>();
    test_is_not_safe_arithmetic<void (Class::*)(int)&>();
    test_is_not_safe_arithmetic<void (Class::*)(int) &&>();
    test_is_not_safe_arithmetic<void (Class::*)(int) const>();
    test_is_not_safe_arithmetic<void (Class::*)(int) const&>();
    test_is_not_safe_arithmetic<void (Class::*)(int) const&&>();

    test_is_not_safe_arithmetic<void (Class::*)(int) noexcept>();
    test_is_not_safe_arithmetic<void (Class::*)(int)& noexcept>();
    test_is_not_safe_arithmetic<void (Class::*)(int)&& noexcept>();
    test_is_not_safe_arithmetic<void (Class::*)(int) const noexcept>();
    test_is_not_safe_arithmetic<void (Class::*)(int) const& noexcept>();
    test_is_not_safe_arithmetic<void (Class::*)(int) const&& noexcept>();

    test_is_not_safe_arithmetic<void (Class::*)(...)>();
    test_is_not_safe_arithmetic<void (Class::*)(...)&>();
    test_is_not_safe_arithmetic<void (Class::*)(...) &&>();
    test_is_not_safe_arithmetic<void (Class::*)(...) const>();
    test_is_not_safe_arithmetic<void (Class::*)(...) const&>();
    test_is_not_safe_arithmetic<void (Class::*)(...) const&&>();

    test_is_not_safe_arithmetic<void (Class::*)(...) noexcept>();
    test_is_not_safe_arithmetic<void (Class::*)(...)& noexcept>();
    test_is_not_safe_arithmetic<void (Class::*)(...)&& noexcept>();
    test_is_not_safe_arithmetic<void (Class::*)(...) const noexcept>();
    test_is_not_safe_arithmetic<void (Class::*)(...) const& noexcept>();
    test_is_not_safe_arithmetic<void (Class::*)(...) const&& noexcept>();
}