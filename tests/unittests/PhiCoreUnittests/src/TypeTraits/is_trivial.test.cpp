#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_trivial.hpp>
#include <vector>

template <typename T>
void test_is_trivial()
{
    STATIC_REQUIRE(phi::is_trivial<T>::value);
    STATIC_REQUIRE(phi::is_trivial<const T>::value);
    STATIC_REQUIRE(phi::is_trivial<volatile T>::value);
    STATIC_REQUIRE(phi::is_trivial<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivial_v<T>);
    STATIC_REQUIRE(phi::is_trivial_v<const T>);
    STATIC_REQUIRE(phi::is_trivial_v<volatile T>);
    STATIC_REQUIRE(phi::is_trivial_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_trivial()
{
    STATIC_REQUIRE_FALSE(phi::is_trivial<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_trivial<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_trivial<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_trivial<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivial_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_trivial_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_trivial_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_trivial_v<const volatile T>);
#endif
}

struct A
{};

class B
{
public:
    B();
};

TEST_CASE("is_trivial")
{
    test_is_trivial<A>();

    test_is_not_trivial<B>();

    test_is_not_trivial<void>();
    test_is_trivial<phi::nullptr_t>();
    test_is_trivial<bool>();
    test_is_trivial<char>();
    test_is_trivial<signed char>();
    test_is_trivial<unsigned char>();
    test_is_trivial<short>();
    test_is_trivial<unsigned short>();
    test_is_trivial<int>();
    test_is_trivial<unsigned int>();
    test_is_trivial<long>();
    test_is_trivial<unsigned long>();
    test_is_trivial<long long>();
    test_is_trivial<unsigned long long>();
    test_is_trivial<float>();
    test_is_trivial<double>();
    test_is_trivial<long double>();
    test_is_trivial<char8_t>();
    test_is_trivial<char16_t>();
    test_is_trivial<char32_t>();
    test_is_trivial<wchar_t>();

    test_is_trivial<phi::Boolean>();
    test_is_trivial<phi::Integer<signed char>>();
    test_is_trivial<phi::Integer<unsigned char>>();
    test_is_trivial<phi::Integer<short>>();
    test_is_trivial<phi::Integer<unsigned short>>();
    test_is_trivial<phi::Integer<int>>();
    test_is_trivial<phi::Integer<unsigned int>>();
    test_is_trivial<phi::Integer<long>>();
    test_is_trivial<phi::Integer<unsigned long>>();
    test_is_trivial<phi::Integer<long long>>();
    test_is_trivial<phi::Integer<unsigned long long>>();
    test_is_trivial<phi::FloatingPoint<float>>();
    test_is_trivial<phi::FloatingPoint<double>>();
    test_is_trivial<phi::FloatingPoint<long double>>();

    test_is_not_trivial<std::vector<int>>();
    test_is_not_trivial<phi::ScopePtr<int>>();

    test_is_not_trivial<int&>();
    test_is_not_trivial<const int&>();
    test_is_not_trivial<volatile int&>();
    test_is_not_trivial<const volatile int&>();
    test_is_not_trivial<int&&>();
    test_is_not_trivial<const int&&>();
    test_is_not_trivial<volatile int&&>();
    test_is_not_trivial<const volatile int&&>();
    test_is_trivial<int*>();
    test_is_trivial<const int*>();
    test_is_trivial<volatile int*>();
    test_is_trivial<const volatile int*>();
    test_is_trivial<int**>();
    test_is_trivial<const int**>();
    test_is_trivial<volatile int**>();
    test_is_trivial<const volatile int**>();
    test_is_trivial<void*>();
    test_is_trivial<char[3]>();
    test_is_trivial<char[]>();
    test_is_trivial<char* [3]>();
    test_is_trivial<char*[]>();
    test_is_not_trivial<Class>();
    test_is_trivial<Union>();
    test_is_trivial<NonEmptyUnion>();
    test_is_trivial<Empty>();
    test_is_not_trivial<NotEmpty>();
    test_is_trivial<bit_zero>();
    test_is_trivial<bit_one>();
    test_is_not_trivial<Abstract>();
    test_is_not_trivial<AbstractTemplate<int>>();
    test_is_trivial<AbstractTemplate<double>>();
    test_is_not_trivial<AbstractTemplate<Class>>();
    test_is_trivial<Final>();
    test_is_trivial<Enum>();
    test_is_trivial<EnumSigned>();
    test_is_trivial<EnumUnsigned>();
    test_is_trivial<EnumClass>();
    test_is_not_trivial<Function>();
    test_is_trivial<FunctionPtr>();
    test_is_trivial<MemberObjectPtr>();
    test_is_trivial<MemberFunctionPtr>();
    test_is_trivial<int Class::*>();
    test_is_trivial<float Class::*>();

    test_is_not_trivial<void()>();
    test_is_not_trivial<void() noexcept>();
    test_is_not_trivial<void(int)>();
    test_is_not_trivial<void(int) noexcept>();

    test_is_not_trivial<void(...)>();
    test_is_not_trivial<void(...) noexcept>();
    test_is_not_trivial<void(int, ...)>();
    test_is_not_trivial<void(int, ...) noexcept>();

    test_is_trivial<void (*)()>();
    test_is_trivial<void (*)() noexcept>();
    test_is_trivial<void (*)(int)>();
    test_is_trivial<void (*)(int) noexcept>();

    test_is_trivial<void (*)(...)>();
    test_is_trivial<void (*)(...) noexcept>();
    test_is_trivial<void (*)(int, ...)>();
    test_is_trivial<void (*)(int, ...) noexcept>();

    test_is_trivial<void (Class::*)()>();
    test_is_trivial<void (Class::*)()&>();
    test_is_trivial<void (Class::*)() &&>();
    test_is_trivial<void (Class::*)() const>();
    test_is_trivial<void (Class::*)() const&>();
    test_is_trivial<void (Class::*)() const&&>();

    test_is_trivial<void (Class::*)() noexcept>();
    test_is_trivial<void (Class::*)()& noexcept>();
    test_is_trivial<void (Class::*)()&& noexcept>();
    test_is_trivial<void (Class::*)() const noexcept>();
    test_is_trivial<void (Class::*)() const& noexcept>();
    test_is_trivial<void (Class::*)() const&& noexcept>();

    test_is_trivial<void (Class::*)(int)>();
    test_is_trivial<void (Class::*)(int)&>();
    test_is_trivial<void (Class::*)(int) &&>();
    test_is_trivial<void (Class::*)(int) const>();
    test_is_trivial<void (Class::*)(int) const&>();
    test_is_trivial<void (Class::*)(int) const&&>();

    test_is_trivial<void (Class::*)(int) noexcept>();
    test_is_trivial<void (Class::*)(int)& noexcept>();
    test_is_trivial<void (Class::*)(int)&& noexcept>();
    test_is_trivial<void (Class::*)(int) const noexcept>();
    test_is_trivial<void (Class::*)(int) const& noexcept>();
    test_is_trivial<void (Class::*)(int) const&& noexcept>();

    test_is_trivial<void (Class::*)(...)>();
    test_is_trivial<void (Class::*)(...)&>();
    test_is_trivial<void (Class::*)(...) &&>();
    test_is_trivial<void (Class::*)(...) const>();
    test_is_trivial<void (Class::*)(...) const&>();
    test_is_trivial<void (Class::*)(...) const&&>();

    test_is_trivial<void (Class::*)(...) noexcept>();
    test_is_trivial<void (Class::*)(...)& noexcept>();
    test_is_trivial<void (Class::*)(...)&& noexcept>();
    test_is_trivial<void (Class::*)(...) const noexcept>();
    test_is_trivial<void (Class::*)(...) const& noexcept>();
    test_is_trivial<void (Class::*)(...) const&& noexcept>();
}
