#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_unsigned.hpp>
#include <vector>

template <typename T>
void test_is_unsigned()
{
    STATIC_REQUIRE(phi::is_unsigned<T>::value);
    STATIC_REQUIRE(phi::is_unsigned<const T>::value);
    STATIC_REQUIRE(phi::is_unsigned<volatile T>::value);
    STATIC_REQUIRE(phi::is_unsigned<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsigned_v<T>);
    STATIC_REQUIRE(phi::is_unsigned_v<const T>);
    STATIC_REQUIRE(phi::is_unsigned_v<volatile T>);
    STATIC_REQUIRE(phi::is_unsigned_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_unsigned()
{
    STATIC_REQUIRE_FALSE(phi::is_unsigned<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsigned<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsigned<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsigned<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsigned_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_unsigned_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_unsigned_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_unsigned_v<const volatile T>);
#endif
}

TEST_CASE("is_unsigned")
{
    test_is_not_unsigned<void>();
    test_is_not_unsigned<phi::nullptr_t>();
    test_is_unsigned<bool>();
    //test_is_unsigned<char>();
    test_is_not_unsigned<signed char>();
    test_is_unsigned<unsigned char>();
    test_is_not_unsigned<short>();
    test_is_unsigned<unsigned short>();
    test_is_not_unsigned<int>();
    test_is_unsigned<unsigned int>();
    test_is_not_unsigned<long>();
    test_is_unsigned<unsigned long>();
    test_is_not_unsigned<long long>();
    test_is_unsigned<unsigned long long>();
    test_is_not_unsigned<float>();
    test_is_not_unsigned<double>();
    test_is_not_unsigned<long double>();
    test_is_unsigned<char8_t>();
    test_is_unsigned<char16_t>();
    test_is_unsigned<char32_t>();
    test_is_not_unsigned<wchar_t>();

    test_is_unsigned<phi::Boolean>();
    test_is_not_unsigned<phi::Integer<signed char>>();
    test_is_unsigned<phi::Integer<unsigned char>>();
    test_is_not_unsigned<phi::Integer<short>>();
    test_is_unsigned<phi::Integer<unsigned short>>();
    test_is_not_unsigned<phi::Integer<int>>();
    test_is_unsigned<phi::Integer<unsigned int>>();
    test_is_not_unsigned<phi::Integer<long>>();
    test_is_unsigned<phi::Integer<unsigned long>>();
    test_is_not_unsigned<phi::Integer<long long>>();
    test_is_unsigned<phi::Integer<unsigned long long>>();
    test_is_not_unsigned<phi::FloatingPoint<float>>();
    test_is_not_unsigned<phi::FloatingPoint<double>>();
    test_is_not_unsigned<phi::FloatingPoint<long double>>();

    test_is_not_unsigned<std::vector<int>>();
    test_is_not_unsigned<phi::ScopePtr<int>>();

    test_is_not_unsigned<int&>();
    test_is_not_unsigned<const int&>();
    test_is_not_unsigned<volatile int&>();
    test_is_not_unsigned<const volatile int&>();
    test_is_not_unsigned<int&&>();
    test_is_not_unsigned<const int&&>();
    test_is_not_unsigned<volatile int&&>();
    test_is_not_unsigned<const volatile int&&>();
    test_is_not_unsigned<int*>();
    test_is_not_unsigned<const int*>();
    test_is_not_unsigned<volatile int*>();
    test_is_not_unsigned<const volatile int*>();
    test_is_not_unsigned<int**>();
    test_is_not_unsigned<const int**>();
    test_is_not_unsigned<volatile int**>();
    test_is_not_unsigned<const volatile int**>();
    test_is_not_unsigned<void*>();
    test_is_not_unsigned<char[3]>();
    test_is_not_unsigned<char[]>();
    test_is_not_unsigned<char* [3]>();
    test_is_not_unsigned<char*[]>();
    test_is_not_unsigned<Class>();
    test_is_not_unsigned<Union>();
    test_is_not_unsigned<NonEmptyUnion>();
    test_is_not_unsigned<Empty>();
    test_is_not_unsigned<NotEmpty>();
    test_is_not_unsigned<bit_zero>();
    test_is_not_unsigned<bit_one>();
    test_is_not_unsigned<Abstract>();
    test_is_not_unsigned<AbstractTemplate<int>>();
    test_is_not_unsigned<AbstractTemplate<double>>();
    test_is_not_unsigned<AbstractTemplate<Class>>();
    test_is_not_unsigned<AbstractTemplate<incomplete_type>>();
    test_is_not_unsigned<Final>();
    test_is_not_unsigned<Enum>();
    test_is_not_unsigned<EnumSigned>();
    test_is_not_unsigned<EnumUnsigned>();
    test_is_not_unsigned<EnumClass>();
    test_is_not_unsigned<Function>();
    test_is_not_unsigned<FunctionPtr>();
    test_is_not_unsigned<MemberObjectPtr>();
    test_is_not_unsigned<MemberFunctionPtr>();
    test_is_not_unsigned<incomplete_type>();
    test_is_not_unsigned<int Class::*>();
    test_is_not_unsigned<float Class::*>();

    test_is_not_unsigned<void()>();
    test_is_not_unsigned<void() noexcept>();
    test_is_not_unsigned<void(int)>();
    test_is_not_unsigned<void(int) noexcept>();

    test_is_not_unsigned<void(...)>();
    test_is_not_unsigned<void(...) noexcept>();
    test_is_not_unsigned<void(int, ...)>();
    test_is_not_unsigned<void(int, ...) noexcept>();

    test_is_not_unsigned<void (*)()>();
    test_is_not_unsigned<void (*)() noexcept>();
    test_is_not_unsigned<void (*)(int)>();
    test_is_not_unsigned<void (*)(int) noexcept>();

    test_is_not_unsigned<void (*)(...)>();
    test_is_not_unsigned<void (*)(...) noexcept>();
    test_is_not_unsigned<void (*)(int, ...)>();
    test_is_not_unsigned<void (*)(int, ...) noexcept>();

    test_is_not_unsigned<void (Class::*)()>();
    test_is_not_unsigned<void (Class::*)()&>();
    test_is_not_unsigned<void (Class::*)() &&>();
    test_is_not_unsigned<void (Class::*)() const>();
    test_is_not_unsigned<void (Class::*)() const&>();
    test_is_not_unsigned<void (Class::*)() const&&>();

    test_is_not_unsigned<void (Class::*)() noexcept>();
    test_is_not_unsigned<void (Class::*)()& noexcept>();
    test_is_not_unsigned<void (Class::*)()&& noexcept>();
    test_is_not_unsigned<void (Class::*)() const noexcept>();
    test_is_not_unsigned<void (Class::*)() const& noexcept>();
    test_is_not_unsigned<void (Class::*)() const&& noexcept>();

    test_is_not_unsigned<void (Class::*)(int)>();
    test_is_not_unsigned<void (Class::*)(int)&>();
    test_is_not_unsigned<void (Class::*)(int) &&>();
    test_is_not_unsigned<void (Class::*)(int) const>();
    test_is_not_unsigned<void (Class::*)(int) const&>();
    test_is_not_unsigned<void (Class::*)(int) const&&>();

    test_is_not_unsigned<void (Class::*)(int) noexcept>();
    test_is_not_unsigned<void (Class::*)(int)& noexcept>();
    test_is_not_unsigned<void (Class::*)(int)&& noexcept>();
    test_is_not_unsigned<void (Class::*)(int) const noexcept>();
    test_is_not_unsigned<void (Class::*)(int) const& noexcept>();
    test_is_not_unsigned<void (Class::*)(int) const&& noexcept>();

    test_is_not_unsigned<void (Class::*)(...)>();
    test_is_not_unsigned<void (Class::*)(...)&>();
    test_is_not_unsigned<void (Class::*)(...) &&>();
    test_is_not_unsigned<void (Class::*)(...) const>();
    test_is_not_unsigned<void (Class::*)(...) const&>();
    test_is_not_unsigned<void (Class::*)(...) const&&>();

    test_is_not_unsigned<void (Class::*)(...) noexcept>();
    test_is_not_unsigned<void (Class::*)(...)& noexcept>();
    test_is_not_unsigned<void (Class::*)(...)&& noexcept>();
    test_is_not_unsigned<void (Class::*)(...) const noexcept>();
    test_is_not_unsigned<void (Class::*)(...) const& noexcept>();
    test_is_not_unsigned<void (Class::*)(...) const&& noexcept>();
}
