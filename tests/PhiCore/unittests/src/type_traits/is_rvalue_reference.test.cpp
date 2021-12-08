#include <phi/test/test_macros.hpp>

#include "phi/compiler_support/char8_t.hpp"
#include "test_types.hpp"
#include <phi/type_traits/is_rvalue_reference.hpp>

template <typename T>
void test_is_rvalue_reference()
{
    STATIC_REQUIRE(phi::is_rvalue_reference<T>::value);
    STATIC_REQUIRE(phi::is_rvalue_reference<const T>::value);
    STATIC_REQUIRE(phi::is_rvalue_reference<volatile T>::value);
    STATIC_REQUIRE(phi::is_rvalue_reference<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_rvalue_reference_v<T>);
    STATIC_REQUIRE(phi::is_rvalue_reference_v<const T>);
    STATIC_REQUIRE(phi::is_rvalue_reference_v<volatile T>);
    STATIC_REQUIRE(phi::is_rvalue_reference_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_rvalue_reference()
{
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<const volatile T>);
#endif
}

TEST_CASE("is_rvalue_reference")
{
    test_is_rvalue_reference<int&&>();
    test_is_rvalue_reference<float&&>();
    test_is_rvalue_reference<bool&&>();

    test_is_not_rvalue_reference<void>();
    test_is_not_rvalue_reference<bool>();
    test_is_not_rvalue_reference<char>();
    test_is_not_rvalue_reference<signed char>();
    test_is_not_rvalue_reference<unsigned char>();
    test_is_not_rvalue_reference<short>();
    test_is_not_rvalue_reference<unsigned short>();
    test_is_not_rvalue_reference<int>();
    test_is_not_rvalue_reference<unsigned int>();
    test_is_not_rvalue_reference<long>();
    test_is_not_rvalue_reference<unsigned long>();
    test_is_not_rvalue_reference<long long>();
    test_is_not_rvalue_reference<unsigned long long>();
    test_is_not_rvalue_reference<float>();
    test_is_not_rvalue_reference<double>();
    test_is_not_rvalue_reference<long double>();
    test_is_not_rvalue_reference<char8_t>();
    test_is_not_rvalue_reference<char16_t>();
    test_is_not_rvalue_reference<char32_t>();
    test_is_not_rvalue_reference<wchar_t>();

    test_is_not_rvalue_reference<int&>();
    test_is_not_rvalue_reference<int*>();
    test_is_not_rvalue_reference<const int*>();
    test_is_not_rvalue_reference<volatile int*>();
    test_is_not_rvalue_reference<const volatile int*>();
    test_is_not_rvalue_reference<int**>();
    test_is_not_rvalue_reference<char[3]>();
    test_is_not_rvalue_reference<char[]>();
    test_is_not_rvalue_reference<char* [3]>();
    test_is_not_rvalue_reference<char*[]>();
    test_is_not_rvalue_reference<Class>();
    test_is_not_rvalue_reference<Union>();
    test_is_not_rvalue_reference<NonEmptyUnion>();
    test_is_not_rvalue_reference<Empty>();
    test_is_not_rvalue_reference<NotEmpty>();
    test_is_not_rvalue_reference<bit_zero>();
    test_is_not_rvalue_reference<bit_one>();
    test_is_not_rvalue_reference<Abstract>();
    test_is_not_rvalue_reference<AbstractTemplate<int>>();
    test_is_not_rvalue_reference<AbstractTemplate<double>>();
    test_is_not_rvalue_reference<AbstractTemplate<Class>>();
    test_is_not_rvalue_reference<AbstractTemplate<incomplete_type>>();
    test_is_not_rvalue_reference<Final>();
    test_is_not_rvalue_reference<Enum>();
    test_is_not_rvalue_reference<EnumSigned>();
    test_is_not_rvalue_reference<EnumUnsigned>();
    test_is_not_rvalue_reference<EnumClass>();
    test_is_not_rvalue_reference<Function>();
    test_is_not_rvalue_reference<FunctionPtr>();
    test_is_not_rvalue_reference<MemberObjectPtr>();
    test_is_not_rvalue_reference<MemberFunctionPtr>();
    test_is_not_rvalue_reference<incomplete_type>();

    test_is_not_rvalue_reference<void()>();
    test_is_not_rvalue_reference<void() noexcept>();
    test_is_not_rvalue_reference<void(int)>();
    test_is_not_rvalue_reference<void(int) noexcept>();

    test_is_not_rvalue_reference<void(...)>();
    test_is_not_rvalue_reference<void(...) noexcept>();
    test_is_not_rvalue_reference<void(int, ...)>();
    test_is_not_rvalue_reference<void(int, ...) noexcept>();

    test_is_not_rvalue_reference<void (*)()>();
    test_is_not_rvalue_reference<void (*)() noexcept>();
    test_is_not_rvalue_reference<void (*)(int)>();
    test_is_not_rvalue_reference<void (*)(int) noexcept>();

    test_is_not_rvalue_reference<void (*)(...)>();
    test_is_not_rvalue_reference<void (*)(...) noexcept>();
    test_is_not_rvalue_reference<void (*)(int, ...)>();
    test_is_not_rvalue_reference<void (*)(int, ...) noexcept>();

    test_is_not_rvalue_reference<void (Class::*)()>();
    test_is_not_rvalue_reference<void (Class::*)()&>();
    test_is_not_rvalue_reference<void (Class::*)() &&>();
    test_is_not_rvalue_reference<void (Class::*)() const>();
    test_is_not_rvalue_reference<void (Class::*)() const&>();
    test_is_not_rvalue_reference<void (Class::*)() const&&>();

    test_is_not_rvalue_reference<void (Class::*)() noexcept>();
    test_is_not_rvalue_reference<void (Class::*)()& noexcept>();
    test_is_not_rvalue_reference<void (Class::*)()&& noexcept>();
    test_is_not_rvalue_reference<void (Class::*)() const noexcept>();
    test_is_not_rvalue_reference<void (Class::*)() const& noexcept>();
    test_is_not_rvalue_reference<void (Class::*)() const&& noexcept>();

    test_is_not_rvalue_reference<void (Class::*)(int)>();
    test_is_not_rvalue_reference<void (Class::*)(int)&>();
    test_is_not_rvalue_reference<void (Class::*)(int) &&>();
    test_is_not_rvalue_reference<void (Class::*)(int) const>();
    test_is_not_rvalue_reference<void (Class::*)(int) const&>();
    test_is_not_rvalue_reference<void (Class::*)(int) const&&>();

    test_is_not_rvalue_reference<void (Class::*)(int) noexcept>();
    test_is_not_rvalue_reference<void (Class::*)(int)& noexcept>();
    test_is_not_rvalue_reference<void (Class::*)(int)&& noexcept>();
    test_is_not_rvalue_reference<void (Class::*)(int) const noexcept>();
    test_is_not_rvalue_reference<void (Class::*)(int) const& noexcept>();
    test_is_not_rvalue_reference<void (Class::*)(int) const&& noexcept>();

    test_is_not_rvalue_reference<void (Class::*)(...)>();
    test_is_not_rvalue_reference<void (Class::*)(...)&>();
    test_is_not_rvalue_reference<void (Class::*)(...) &&>();
    test_is_not_rvalue_reference<void (Class::*)(...) const>();
    test_is_not_rvalue_reference<void (Class::*)(...) const&>();
    test_is_not_rvalue_reference<void (Class::*)(...) const&&>();

    test_is_not_rvalue_reference<void (Class::*)(...) noexcept>();
    test_is_not_rvalue_reference<void (Class::*)(...)& noexcept>();
    test_is_not_rvalue_reference<void (Class::*)(...)&& noexcept>();
    test_is_not_rvalue_reference<void (Class::*)(...) const noexcept>();
    test_is_not_rvalue_reference<void (Class::*)(...) const& noexcept>();
    test_is_not_rvalue_reference<void (Class::*)(...) const&& noexcept>();
}
