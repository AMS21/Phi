#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_safe_type.hpp>
#include <vector>

template <typename T>
void test_is_safe_type()
{
    STATIC_REQUIRE(phi::is_safe_type<T>::value);
    STATIC_REQUIRE(phi::is_safe_type<const T>::value);
    STATIC_REQUIRE(phi::is_safe_type<volatile T>::value);
    STATIC_REQUIRE(phi::is_safe_type<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_safe_type_v<T>);
    STATIC_REQUIRE(phi::is_safe_type_v<const T>);
    STATIC_REQUIRE(phi::is_safe_type_v<volatile T>);
    STATIC_REQUIRE(phi::is_safe_type_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_safe_type()
{
    STATIC_REQUIRE_FALSE(phi::is_safe_type<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_safe_type<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_safe_type<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_safe_type<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_type_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_safe_type_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_safe_type_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_safe_type_v<const volatile T>);
#endif
}

TEST_CASE("is_safe_type")
{
    test_is_safe_type<phi::Boolean>();
    test_is_safe_type<phi::Integer<signed char>>();
    test_is_safe_type<phi::Integer<unsigned char>>();
    test_is_safe_type<phi::Integer<short>>();
    test_is_safe_type<phi::Integer<unsigned short>>();
    test_is_safe_type<phi::Integer<int>>();
    test_is_safe_type<phi::Integer<unsigned int>>();
    test_is_safe_type<phi::Integer<long>>();
    test_is_safe_type<phi::Integer<unsigned long>>();
    test_is_safe_type<phi::Integer<long long>>();
    test_is_safe_type<phi::Integer<unsigned long long>>();
    test_is_safe_type<phi::FloatingPoint<float>>();
    test_is_safe_type<phi::FloatingPoint<double>>();
    test_is_safe_type<phi::FloatingPoint<long double>>();

    test_is_not_safe_type<phi::Boolean&>();
    test_is_not_safe_type<phi::Integer<signed char>&>();
    test_is_not_safe_type<phi::Integer<unsigned char>&>();
    test_is_not_safe_type<phi::Integer<short>&>();
    test_is_not_safe_type<phi::Integer<unsigned short>&>();
    test_is_not_safe_type<phi::Integer<int>&>();
    test_is_not_safe_type<phi::Integer<unsigned int>&>();
    test_is_not_safe_type<phi::Integer<long>&>();
    test_is_not_safe_type<phi::Integer<unsigned long>&>();
    test_is_not_safe_type<phi::Integer<long long>&>();
    test_is_not_safe_type<phi::Integer<unsigned long long>&>();
    test_is_not_safe_type<phi::FloatingPoint<float>&>();
    test_is_not_safe_type<phi::FloatingPoint<double>&>();
    test_is_not_safe_type<phi::FloatingPoint<long double>&>();

    test_is_not_safe_type<phi::Boolean&&>();
    test_is_not_safe_type<phi::Integer<signed char>&&>();
    test_is_not_safe_type<phi::Integer<unsigned char>&&>();
    test_is_not_safe_type<phi::Integer<short>&&>();
    test_is_not_safe_type<phi::Integer<unsigned short>&&>();
    test_is_not_safe_type<phi::Integer<int>&&>();
    test_is_not_safe_type<phi::Integer<unsigned int>&&>();
    test_is_not_safe_type<phi::Integer<long>&&>();
    test_is_not_safe_type<phi::Integer<unsigned long>&&>();
    test_is_not_safe_type<phi::Integer<long long>&&>();
    test_is_not_safe_type<phi::Integer<unsigned long long>&&>();
    test_is_not_safe_type<phi::FloatingPoint<float>&&>();
    test_is_not_safe_type<phi::FloatingPoint<double>&&>();
    test_is_not_safe_type<phi::FloatingPoint<long double>&&>();

    test_is_not_safe_type<phi::Boolean*>();
    test_is_not_safe_type<phi::Integer<signed char>*>();
    test_is_not_safe_type<phi::Integer<unsigned char>*>();
    test_is_not_safe_type<phi::Integer<short>*>();
    test_is_not_safe_type<phi::Integer<unsigned short>*>();
    test_is_not_safe_type<phi::Integer<int>*>();
    test_is_not_safe_type<phi::Integer<unsigned int>*>();
    test_is_not_safe_type<phi::Integer<long>*>();
    test_is_not_safe_type<phi::Integer<unsigned long>*>();
    test_is_not_safe_type<phi::Integer<long long>*>();
    test_is_not_safe_type<phi::Integer<unsigned long long>*>();
    test_is_not_safe_type<phi::FloatingPoint<float>*>();
    test_is_not_safe_type<phi::FloatingPoint<double>*>();
    test_is_not_safe_type<phi::FloatingPoint<long double>*>();

    test_is_not_safe_type<void>();
    test_is_not_safe_type<phi::nullptr_t>();
    test_is_not_safe_type<bool>();
    test_is_not_safe_type<char>();
    test_is_not_safe_type<signed char>();
    test_is_not_safe_type<unsigned char>();
    test_is_not_safe_type<short>();
    test_is_not_safe_type<unsigned short>();
    test_is_not_safe_type<int>();
    test_is_not_safe_type<unsigned int>();
    test_is_not_safe_type<long>();
    test_is_not_safe_type<unsigned long>();
    test_is_not_safe_type<long long>();
    test_is_not_safe_type<unsigned long long>();
    test_is_not_safe_type<float>();
    test_is_not_safe_type<double>();
    test_is_not_safe_type<long double>();
    test_is_not_safe_type<char8_t>();
    test_is_not_safe_type<char16_t>();
    test_is_not_safe_type<char32_t>();
    test_is_not_safe_type<wchar_t>();

    test_is_not_safe_type<std::vector<int>>();
    test_is_not_safe_type<phi::ScopePtr<int>>();

    test_is_not_safe_type<int&>();
    test_is_not_safe_type<int&&>();
    test_is_not_safe_type<int*>();
    test_is_not_safe_type<const int*>();
    test_is_not_safe_type<volatile int*>();
    test_is_not_safe_type<const volatile int*>();
    test_is_not_safe_type<int**>();
    test_is_not_safe_type<char[3]>();
    test_is_not_safe_type<char[]>();
    test_is_not_safe_type<char* [3]>();
    test_is_not_safe_type<char*[]>();
    test_is_not_safe_type<Class>();
    test_is_not_safe_type<Union>();
    test_is_not_safe_type<NonEmptyUnion>();
    test_is_not_safe_type<Empty>();
    test_is_not_safe_type<NotEmpty>();
    test_is_not_safe_type<bit_zero>();
    test_is_not_safe_type<bit_one>();
    test_is_not_safe_type<Abstract>();
    test_is_not_safe_type<AbstractTemplate<int>>();
    test_is_not_safe_type<AbstractTemplate<double>>();
    test_is_not_safe_type<AbstractTemplate<Class>>();
    test_is_not_safe_type<AbstractTemplate<incomplete_type>>();
    test_is_not_safe_type<Final>();
    test_is_not_safe_type<Enum>();
    test_is_not_safe_type<EnumSigned>();
    test_is_not_safe_type<EnumUnsigned>();
    test_is_not_safe_type<EnumClass>();
    test_is_not_safe_type<Function>();
    test_is_not_safe_type<FunctionPtr>();
    test_is_not_safe_type<MemberObjectPtr>();
    test_is_not_safe_type<MemberFunctionPtr>();
    test_is_not_safe_type<incomplete_type>();
    test_is_not_safe_type<int Class::*>();
    test_is_not_safe_type<float Class::*>();

    test_is_not_safe_type<void()>();
    test_is_not_safe_type<void() noexcept>();
    test_is_not_safe_type<void(int)>();
    test_is_not_safe_type<void(int) noexcept>();

    test_is_not_safe_type<void(...)>();
    test_is_not_safe_type<void(...) noexcept>();
    test_is_not_safe_type<void(int, ...)>();
    test_is_not_safe_type<void(int, ...) noexcept>();

    test_is_not_safe_type<void (*)()>();
    test_is_not_safe_type<void (*)() noexcept>();
    test_is_not_safe_type<void (*)(int)>();
    test_is_not_safe_type<void (*)(int) noexcept>();

    test_is_not_safe_type<void (*)(...)>();
    test_is_not_safe_type<void (*)(...) noexcept>();
    test_is_not_safe_type<void (*)(int, ...)>();
    test_is_not_safe_type<void (*)(int, ...) noexcept>();

    test_is_not_safe_type<void (Class::*)()>();
    test_is_not_safe_type<void (Class::*)()&>();
    test_is_not_safe_type<void (Class::*)() &&>();
    test_is_not_safe_type<void (Class::*)() const>();
    test_is_not_safe_type<void (Class::*)() const&>();
    test_is_not_safe_type<void (Class::*)() const&&>();

    test_is_not_safe_type<void (Class::*)() noexcept>();
    test_is_not_safe_type<void (Class::*)()& noexcept>();
    test_is_not_safe_type<void (Class::*)()&& noexcept>();
    test_is_not_safe_type<void (Class::*)() const noexcept>();
    test_is_not_safe_type<void (Class::*)() const& noexcept>();
    test_is_not_safe_type<void (Class::*)() const&& noexcept>();

    test_is_not_safe_type<void (Class::*)(int)>();
    test_is_not_safe_type<void (Class::*)(int)&>();
    test_is_not_safe_type<void (Class::*)(int) &&>();
    test_is_not_safe_type<void (Class::*)(int) const>();
    test_is_not_safe_type<void (Class::*)(int) const&>();
    test_is_not_safe_type<void (Class::*)(int) const&&>();

    test_is_not_safe_type<void (Class::*)(int) noexcept>();
    test_is_not_safe_type<void (Class::*)(int)& noexcept>();
    test_is_not_safe_type<void (Class::*)(int)&& noexcept>();
    test_is_not_safe_type<void (Class::*)(int) const noexcept>();
    test_is_not_safe_type<void (Class::*)(int) const& noexcept>();
    test_is_not_safe_type<void (Class::*)(int) const&& noexcept>();

    test_is_not_safe_type<void (Class::*)(...)>();
    test_is_not_safe_type<void (Class::*)(...)&>();
    test_is_not_safe_type<void (Class::*)(...) &&>();
    test_is_not_safe_type<void (Class::*)(...) const>();
    test_is_not_safe_type<void (Class::*)(...) const&>();
    test_is_not_safe_type<void (Class::*)(...) const&&>();

    test_is_not_safe_type<void (Class::*)(...) noexcept>();
    test_is_not_safe_type<void (Class::*)(...)& noexcept>();
    test_is_not_safe_type<void (Class::*)(...)&& noexcept>();
    test_is_not_safe_type<void (Class::*)(...) const noexcept>();
    test_is_not_safe_type<void (Class::*)(...) const& noexcept>();
    test_is_not_safe_type<void (Class::*)(...) const&& noexcept>();
}
