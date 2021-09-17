#include <catch2/catch_test_macros.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_member_function_pointer.hpp>
#include <Phi/TypeTraits/is_void.hpp>

template <typename T>
void test_is_void()
{
    STATIC_REQUIRE(phi::is_void<T>::value);
    STATIC_REQUIRE(phi::is_void<const T>::value);
    STATIC_REQUIRE(phi::is_void<volatile T>::value);
    STATIC_REQUIRE(phi::is_void<const volatile T>::value);

    STATIC_REQUIRE(phi::is_void_v<T>);
    STATIC_REQUIRE(phi::is_void_v<const T>);
    STATIC_REQUIRE(phi::is_void_v<volatile T>);
    STATIC_REQUIRE(phi::is_void_v<const volatile T>);
}

template <typename T>
void test_is_not_void()
{
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_void<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_void<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_void<const volatile T>::value);

    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_void_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_void_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_void_v<const volatile T>);
}

TEST_CASE("is_void")
{
    test_is_void<void>();

    test_is_not_void<phi::nullptr_t>();
    test_is_not_void<bool>();
    test_is_not_void<char>();
    test_is_not_void<signed char>();
    test_is_not_void<unsigned char>();
    test_is_not_void<short>();
    test_is_not_void<unsigned short>();
    test_is_not_void<int>();
    test_is_not_void<unsigned int>();
    test_is_not_void<long>();
    test_is_not_void<unsigned long>();
    test_is_not_void<long long>();
    test_is_not_void<unsigned long long>();
    test_is_not_void<float>();
    test_is_not_void<double>();
    test_is_not_void<long double>();
    test_is_not_void<char8_t>();
    test_is_not_void<char16_t>();
    test_is_not_void<char32_t>();
    test_is_not_void<wchar_t>();

    test_is_not_void<int&>();
    test_is_not_void<int&&>();
    test_is_not_void<int*>();
    test_is_not_void<const int*>();
    test_is_not_void<volatile int*>();
    test_is_not_void<const volatile int*>();
    test_is_not_void<int**>();
    test_is_not_void<char[3]>();
    test_is_not_void<char[]>();
    test_is_not_void<char* [3]>();
    test_is_not_void<char*[]>();
    test_is_not_void<Class>();
    test_is_not_void<Struct>();
    test_is_not_void<Union>();
    test_is_not_void<NonEmptyUnion>();
    test_is_not_void<Empty>();
    test_is_not_void<bit_zero>();
    test_is_not_void<bit_one>();
    test_is_not_void<NotEmpty>();
    test_is_not_void<Abstract>();
    test_is_not_void<AbstractTemplate<int>>();
    test_is_not_void<AbstractTemplate<double>>();
    test_is_not_void<AbstractTemplate<Class>>();
    test_is_not_void<AbstractTemplate<incomplete_type>>();
    test_is_not_void<Enum>();
    test_is_not_void<EnumSigned>();
    test_is_not_void<EnumUnsigned>();
    test_is_not_void<EnumClass>();
    test_is_not_void<Function>();
    test_is_not_void<FunctionPtr>();
    test_is_not_void<MemberObjectPtr>();
    test_is_not_void<MemberFunctionPtr>();
    test_is_not_void<incomplete_type>();
    test_is_not_void<int Class::*>();
    test_is_not_void<float Class::*>();

    test_is_not_void<void()>();
    test_is_not_void<void() noexcept>();
    test_is_not_void<void(int)>();
    test_is_not_void<void(int) noexcept>();

    test_is_not_void<void(...)>();
    test_is_not_void<void(...) noexcept>();
    test_is_not_void<void(int, ...)>();
    test_is_not_void<void(int, ...) noexcept>();

    test_is_not_void<void (*)()>();
    test_is_not_void<void (*)() noexcept>();
    test_is_not_void<void (*)(int)>();
    test_is_not_void<void (*)(int) noexcept>();

    test_is_not_void<void (*)(...)>();
    test_is_not_void<void (*)(...) noexcept>();
    test_is_not_void<void (*)(int, ...)>();
    test_is_not_void<void (*)(int, ...) noexcept>();

    test_is_not_void<void (Class::*)()>();
    test_is_not_void<void (Class::*)()&>();
    test_is_not_void<void (Class::*)() &&>();
    test_is_not_void<void (Class::*)() const>();
    test_is_not_void<void (Class::*)() const&>();
    test_is_not_void<void (Class::*)() const&&>();

    test_is_not_void<void (Class::*)() noexcept>();
    test_is_not_void<void (Class::*)()& noexcept>();
    test_is_not_void<void (Class::*)()&& noexcept>();
    test_is_not_void<void (Class::*)() const noexcept>();
    test_is_not_void<void (Class::*)() const& noexcept>();
    test_is_not_void<void (Class::*)() const&& noexcept>();

    test_is_not_void<void (Class::*)(int)>();
    test_is_not_void<void (Class::*)(int)&>();
    test_is_not_void<void (Class::*)(int) &&>();
    test_is_not_void<void (Class::*)(int) const>();
    test_is_not_void<void (Class::*)(int) const&>();
    test_is_not_void<void (Class::*)(int) const&&>();

    test_is_not_void<void (Class::*)(int) noexcept>();
    test_is_not_void<void (Class::*)(int)& noexcept>();
    test_is_not_void<void (Class::*)(int)&& noexcept>();
    test_is_not_void<void (Class::*)(int) const noexcept>();
    test_is_not_void<void (Class::*)(int) const& noexcept>();
    test_is_not_void<void (Class::*)(int) const&& noexcept>();

    test_is_not_void<void (Class::*)(...)>();
    test_is_not_void<void (Class::*)(...)&>();
    test_is_not_void<void (Class::*)(...) &&>();
    test_is_not_void<void (Class::*)(...) const>();
    test_is_not_void<void (Class::*)(...) const&>();
    test_is_not_void<void (Class::*)(...) const&&>();
    test_is_not_void<void (Class::*)(...) noexcept>();
    test_is_not_void<void (Class::*)(...)& noexcept>();
    test_is_not_void<void (Class::*)(...)&& noexcept>();
    test_is_not_void<void (Class::*)(...) const noexcept>();
    test_is_not_void<void (Class::*)(...) const& noexcept>();
    test_is_not_void<void (Class::*)(...) const&& noexcept>();
}
