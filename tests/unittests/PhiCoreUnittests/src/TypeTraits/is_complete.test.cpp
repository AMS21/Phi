#include <catch2/catch.hpp>

#include "Phi/CompilerSupport/Char8_t.hpp"
#include "TestTypes.hpp"
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_complete.hpp>

template <typename TypeT>
void test_is_complete()
{
    STATIC_REQUIRE(phi::is_complete<TypeT>::value);
    STATIC_REQUIRE(phi::is_complete<const TypeT>::value);
    STATIC_REQUIRE(phi::is_complete<volatile TypeT>::value);
    STATIC_REQUIRE(phi::is_complete<const volatile TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_complete_v<TypeT>);
    STATIC_REQUIRE(phi::is_complete_v<const TypeT>);
    STATIC_REQUIRE(phi::is_complete_v<volatile TypeT>);
    STATIC_REQUIRE(phi::is_complete_v<const volatile TypeT>);
#endif
}

template <typename TypeT>
void test_is_not_complete()
{
    STATIC_REQUIRE_FALSE(phi::is_complete<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_complete<const TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_complete<volatile TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_complete<const volatile TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_complete_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_complete_v<const TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_complete_v<volatile TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_complete_v<const volatile TypeT>);
#endif
}

class A;

TEST_CASE("is_complete")
{
    test_is_complete<phi::nullptr_t>();
    test_is_complete<bool>();
    test_is_complete<char>();
    test_is_complete<signed char>();
    test_is_complete<unsigned char>();
    test_is_complete<short>();
    test_is_complete<unsigned short>();
    test_is_complete<int>();
    test_is_complete<unsigned int>();
    test_is_complete<long>();
    test_is_complete<unsigned long>();
    test_is_complete<long long>();
    test_is_complete<unsigned long long>();
    test_is_complete<float>();
    test_is_complete<double>();
    test_is_complete<long double>();
    test_is_complete<char8_t>();
    test_is_complete<char16_t>();
    test_is_complete<char32_t>();
    test_is_complete<wchar_t>();
    test_is_complete<int&>();
    test_is_complete<int&&>();
    test_is_complete<void*>();
    test_is_complete<int*>();
    test_is_complete<const int*>();
    test_is_complete<volatile int*>();
    test_is_complete<const volatile int*>();
    test_is_complete<int**>();
    test_is_complete<char[3]>();
    test_is_complete<char* [3]>();
    test_is_complete<char[3][4]>();
    test_is_complete<char[3][4][5]>();
    test_is_complete<Class>();
    test_is_complete<Union>();
    test_is_complete<NonEmptyUnion>();
    test_is_complete<bit_zero>();
    test_is_complete<bit_one>();
    test_is_complete<NotEmpty>();
    test_is_complete<Abstract>();
    test_is_complete<AbstractTemplate<int>>();
    test_is_complete<AbstractTemplate<double>>();
    test_is_complete<AbstractTemplate<Class>>();
    test_is_complete<Enum>();
    test_is_complete<EnumSigned>();
    test_is_complete<EnumUnsigned>();
    test_is_complete<EnumClass>();
    test_is_complete<Function>();
    test_is_complete<FunctionPtr>();
    test_is_complete<MemberObjectPtr>();
    test_is_complete<MemberFunctionPtr>();

    test_is_complete<int Class::*>();
    test_is_complete<float Class::*>();

    test_is_complete<void()>();
    test_is_complete<void() noexcept>();
    test_is_complete<void(int)>();
    test_is_complete<void(int) noexcept>();

    test_is_complete<void(...)>();
    test_is_complete<void(...) noexcept>();
    test_is_complete<void(int, ...)>();
    test_is_complete<void(int, ...) noexcept>();

    test_is_complete<void (*)()>();
    test_is_complete<void (*)() noexcept>();
    test_is_complete<void (*)(int)>();
    test_is_complete<void (*)(int) noexcept>();

    test_is_complete<void (*)(...)>();
    test_is_complete<void (*)(...) noexcept>();
    test_is_complete<void (*)(int, ...)>();
    test_is_complete<void (*)(int, ...) noexcept>();

    test_is_complete<void (Class::*)()>();
    test_is_complete<void (Class::*)()&>();
    test_is_complete<void (Class::*)() &&>();
    test_is_complete<void (Class::*)() const>();
    test_is_complete<void (Class::*)() const&>();
    test_is_complete<void (Class::*)() const&&>();

    test_is_complete<void (Class::*)() noexcept>();
    test_is_complete<void (Class::*)()& noexcept>();
    test_is_complete<void (Class::*)()&& noexcept>();
    test_is_complete<void (Class::*)() const noexcept>();
    test_is_complete<void (Class::*)() const& noexcept>();
    test_is_complete<void (Class::*)() const&& noexcept>();

    test_is_complete<void (Class::*)(int)>();
    test_is_complete<void (Class::*)(int)&>();
    test_is_complete<void (Class::*)(int) &&>();
    test_is_complete<void (Class::*)(int) const>();
    test_is_complete<void (Class::*)(int) const&>();
    test_is_complete<void (Class::*)(int) const&&>();

    test_is_complete<void (Class::*)(int) noexcept>();
    test_is_complete<void (Class::*)(int)& noexcept>();
    test_is_complete<void (Class::*)(int)&& noexcept>();
    test_is_complete<void (Class::*)(int) const noexcept>();
    test_is_complete<void (Class::*)(int) const& noexcept>();
    test_is_complete<void (Class::*)(int) const&& noexcept>();

    test_is_complete<void (Class::*)(...)>();
    test_is_complete<void (Class::*)(...)&>();
    test_is_complete<void (Class::*)(...) &&>();
    test_is_complete<void (Class::*)(...) const>();
    test_is_complete<void (Class::*)(...) const&>();
    test_is_complete<void (Class::*)(...) const&&>();

    test_is_complete<void (Class::*)(...) noexcept>();
    test_is_complete<void (Class::*)(...)& noexcept>();
    test_is_complete<void (Class::*)(...)&& noexcept>();
    test_is_complete<void (Class::*)(...) const noexcept>();
    test_is_complete<void (Class::*)(...) const& noexcept>();
    test_is_complete<void (Class::*)(...) const&& noexcept>();

    test_is_not_complete<void>();
    test_is_not_complete<char[]>();
    test_is_not_complete<char[][3]>();
    test_is_not_complete<char[][3][4]>();
    test_is_not_complete<char*[]>();
    test_is_not_complete<incomplete_type>();
    test_is_not_complete<A>();
}
