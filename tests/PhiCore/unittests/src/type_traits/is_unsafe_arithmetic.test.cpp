#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_unsafe_arithmetic.hpp>
#include <vector>

template <typename T>
void test_is_unsafe_arithmetic()
{
    STATIC_REQUIRE(phi::is_unsafe_arithmetic<T>::value);
    STATIC_REQUIRE(phi::is_unsafe_arithmetic<const T>::value);
    STATIC_REQUIRE(phi::is_unsafe_arithmetic<volatile T>::value);
    STATIC_REQUIRE(phi::is_unsafe_arithmetic<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_arithmetic_v<T>);
    STATIC_REQUIRE(phi::is_unsafe_arithmetic_v<const T>);
    STATIC_REQUIRE(phi::is_unsafe_arithmetic_v<volatile T>);
    STATIC_REQUIRE(phi::is_unsafe_arithmetic_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_unsafe_arithmetic()
{
    STATIC_REQUIRE_FALSE(phi::is_unsafe_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_arithmetic<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_arithmetic<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_arithmetic<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_arithmetic_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_arithmetic_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_arithmetic_v<const volatile T>);
#endif
}

TEST_CASE("is_unsafe_arithmetic")
{
    test_is_not_unsafe_arithmetic<void>();
    test_is_not_unsafe_arithmetic<phi::nullptr_t>();
    test_is_unsafe_arithmetic<bool>();
    test_is_unsafe_arithmetic<char>();
    test_is_unsafe_arithmetic<signed char>();
    test_is_unsafe_arithmetic<unsigned char>();
    test_is_unsafe_arithmetic<short>();
    test_is_unsafe_arithmetic<unsigned short>();
    test_is_unsafe_arithmetic<int>();
    test_is_unsafe_arithmetic<unsigned int>();
    test_is_unsafe_arithmetic<long>();
    test_is_unsafe_arithmetic<unsigned long>();
    test_is_unsafe_arithmetic<long long>();
    test_is_unsafe_arithmetic<unsigned long long>();
    test_is_unsafe_arithmetic<float>();
    test_is_unsafe_arithmetic<double>();
    test_is_unsafe_arithmetic<long double>();
    test_is_unsafe_arithmetic<char8_t>();
    test_is_unsafe_arithmetic<char16_t>();
    test_is_unsafe_arithmetic<char32_t>();
    test_is_unsafe_arithmetic<wchar_t>();

    test_is_not_unsafe_arithmetic<phi::boolean>();
    test_is_not_unsafe_arithmetic<phi::integer<signed char>>();
    test_is_not_unsafe_arithmetic<phi::integer<unsigned char>>();
    test_is_not_unsafe_arithmetic<phi::integer<short>>();
    test_is_not_unsafe_arithmetic<phi::integer<unsigned short>>();
    test_is_not_unsafe_arithmetic<phi::integer<int>>();
    test_is_not_unsafe_arithmetic<phi::integer<unsigned int>>();
    test_is_not_unsafe_arithmetic<phi::integer<long>>();
    test_is_not_unsafe_arithmetic<phi::integer<unsigned long>>();
    test_is_not_unsafe_arithmetic<phi::integer<long long>>();
    test_is_not_unsafe_arithmetic<phi::integer<unsigned long long>>();
    test_is_not_unsafe_arithmetic<phi::floating_point<float>>();
    test_is_not_unsafe_arithmetic<phi::floating_point<double>>();
    test_is_not_unsafe_arithmetic<phi::floating_point<long double>>();

    test_is_not_unsafe_arithmetic<std::vector<int>>();
    test_is_not_unsafe_arithmetic<phi::scope_ptr<int>>();

    test_is_not_unsafe_arithmetic<int&>();
    test_is_not_unsafe_arithmetic<const int&>();
    test_is_not_unsafe_arithmetic<volatile int&>();
    test_is_not_unsafe_arithmetic<const volatile int&>();
    test_is_not_unsafe_arithmetic<int&&>();
    test_is_not_unsafe_arithmetic<const int&&>();
    test_is_not_unsafe_arithmetic<volatile int&&>();
    test_is_not_unsafe_arithmetic<const volatile int&&>();
    test_is_not_unsafe_arithmetic<int*>();
    test_is_not_unsafe_arithmetic<const int*>();
    test_is_not_unsafe_arithmetic<volatile int*>();
    test_is_not_unsafe_arithmetic<const volatile int*>();
    test_is_not_unsafe_arithmetic<int**>();
    test_is_not_unsafe_arithmetic<const int**>();
    test_is_not_unsafe_arithmetic<volatile int**>();
    test_is_not_unsafe_arithmetic<const volatile int**>();
    test_is_not_unsafe_arithmetic<void*>();
    test_is_not_unsafe_arithmetic<char[3]>();
    test_is_not_unsafe_arithmetic<char[]>();
    test_is_not_unsafe_arithmetic<char* [3]>();
    test_is_not_unsafe_arithmetic<char*[]>();
    test_is_not_unsafe_arithmetic<Class>();
    test_is_not_unsafe_arithmetic<Union>();
    test_is_not_unsafe_arithmetic<NonEmptyUnion>();
    test_is_not_unsafe_arithmetic<Empty>();
    test_is_not_unsafe_arithmetic<NotEmpty>();
    test_is_not_unsafe_arithmetic<bit_zero>();
    test_is_not_unsafe_arithmetic<bit_one>();
    test_is_not_unsafe_arithmetic<Abstract>();
    test_is_not_unsafe_arithmetic<AbstractTemplate<int>>();
    test_is_not_unsafe_arithmetic<AbstractTemplate<double>>();
    test_is_not_unsafe_arithmetic<AbstractTemplate<Class>>();
    test_is_not_unsafe_arithmetic<AbstractTemplate<incomplete_type>>();
    test_is_not_unsafe_arithmetic<Final>();
    test_is_not_unsafe_arithmetic<Enum>();
    test_is_not_unsafe_arithmetic<EnumSigned>();
    test_is_not_unsafe_arithmetic<EnumUnsigned>();
    test_is_not_unsafe_arithmetic<EnumClass>();
    test_is_not_unsafe_arithmetic<Function>();
    test_is_not_unsafe_arithmetic<FunctionPtr>();
    test_is_not_unsafe_arithmetic<MemberObjectPtr>();
    test_is_not_unsafe_arithmetic<MemberFunctionPtr>();
    test_is_not_unsafe_arithmetic<incomplete_type>();
    test_is_not_unsafe_arithmetic<int Class::*>();
    test_is_not_unsafe_arithmetic<float Class::*>();

    test_is_not_unsafe_arithmetic<void()>();
    test_is_not_unsafe_arithmetic<void() noexcept>();
    test_is_not_unsafe_arithmetic<void(int)>();
    test_is_not_unsafe_arithmetic<void(int) noexcept>();

    test_is_not_unsafe_arithmetic<void(...)>();
    test_is_not_unsafe_arithmetic<void(...) noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...)>();
    test_is_not_unsafe_arithmetic<void(int, ...) noexcept>();

    test_is_not_unsafe_arithmetic<void (*)()>();
    test_is_not_unsafe_arithmetic<void (*)() noexcept>();
    test_is_not_unsafe_arithmetic<void (*)(int)>();
    test_is_not_unsafe_arithmetic<void (*)(int) noexcept>();

    test_is_not_unsafe_arithmetic<void (*)(...)>();
    test_is_not_unsafe_arithmetic<void (*)(...) noexcept>();
    test_is_not_unsafe_arithmetic<void (*)(int, ...)>();
    test_is_not_unsafe_arithmetic<void (*)(int, ...) noexcept>();

    test_is_not_unsafe_arithmetic<void (Class::*)()>();
    test_is_not_unsafe_arithmetic<void (Class::*)()&>();
    test_is_not_unsafe_arithmetic<void (Class::*)() &&>();
    test_is_not_unsafe_arithmetic<void (Class::*)() const>();
    test_is_not_unsafe_arithmetic<void (Class::*)() const&>();
    test_is_not_unsafe_arithmetic<void (Class::*)() const&&>();

    test_is_not_unsafe_arithmetic<void (Class::*)() noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)()& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)()&& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)() const noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)() const& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)() const&& noexcept>();

    test_is_not_unsafe_arithmetic<void (Class::*)(int)>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int)&>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int) &&>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int) const>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int) const&>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int) const&&>();

    test_is_not_unsafe_arithmetic<void (Class::*)(int) noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int)& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int)&& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int) const noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int) const& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(int) const&& noexcept>();

    test_is_not_unsafe_arithmetic<void (Class::*)(...)>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...)&>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...) &&>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...) const>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...) const&>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...) const&&>();

    test_is_not_unsafe_arithmetic<void (Class::*)(...) noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...)& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...)&& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...) const noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...) const& noexcept>();
    test_is_not_unsafe_arithmetic<void (Class::*)(...) const&& noexcept>();
}
