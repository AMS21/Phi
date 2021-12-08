#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_unsafe_integer.hpp>
#include <vector>

template <typename T>
void test_is_unsafe_integer()
{
    STATIC_REQUIRE(phi::is_unsafe_integer<T>::value);
    STATIC_REQUIRE(phi::is_unsafe_integer<const T>::value);
    STATIC_REQUIRE(phi::is_unsafe_integer<volatile T>::value);
    STATIC_REQUIRE(phi::is_unsafe_integer<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_integer_v<T>);
    STATIC_REQUIRE(phi::is_unsafe_integer_v<const T>);
    STATIC_REQUIRE(phi::is_unsafe_integer_v<volatile T>);
    STATIC_REQUIRE(phi::is_unsafe_integer_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_unsafe_integer()
{
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integer<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integer<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integer<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integer_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integer_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integer_v<const volatile T>);
#endif
}

TEST_CASE("is_unsafe_integer")
{
    test_is_not_unsafe_integer<void>();
    test_is_not_unsafe_integer<phi::nullptr_t>();
    test_is_not_unsafe_integer<bool>();
    test_is_not_unsafe_integer<char>();
    test_is_unsafe_integer<signed char>();
    test_is_unsafe_integer<unsigned char>();
    test_is_unsafe_integer<short>();
    test_is_unsafe_integer<unsigned short>();
    test_is_unsafe_integer<int>();
    test_is_unsafe_integer<unsigned int>();
    test_is_unsafe_integer<long>();
    test_is_unsafe_integer<unsigned long>();
    test_is_unsafe_integer<long long>();
    test_is_unsafe_integer<unsigned long long>();
    test_is_not_unsafe_integer<float>();
    test_is_not_unsafe_integer<double>();
    test_is_not_unsafe_integer<long double>();
    //test_is_not_unsafe_integer<char8_t>();
    test_is_not_unsafe_integer<char16_t>();
    test_is_not_unsafe_integer<char32_t>();
    test_is_not_unsafe_integer<wchar_t>();

    test_is_not_unsafe_integer<phi::boolean>();
    test_is_not_unsafe_integer<phi::integer<signed char>>();
    test_is_not_unsafe_integer<phi::integer<unsigned char>>();
    test_is_not_unsafe_integer<phi::integer<short>>();
    test_is_not_unsafe_integer<phi::integer<unsigned short>>();
    test_is_not_unsafe_integer<phi::integer<int>>();
    test_is_not_unsafe_integer<phi::integer<unsigned int>>();
    test_is_not_unsafe_integer<phi::integer<long>>();
    test_is_not_unsafe_integer<phi::integer<unsigned long>>();
    test_is_not_unsafe_integer<phi::integer<long long>>();
    test_is_not_unsafe_integer<phi::integer<unsigned long long>>();
    test_is_not_unsafe_integer<phi::floating_point<float>>();
    test_is_not_unsafe_integer<phi::floating_point<double>>();
    test_is_not_unsafe_integer<phi::floating_point<long double>>();

    test_is_not_unsafe_integer<std::vector<int>>();
    test_is_not_unsafe_integer<phi::scope_ptr<int>>();

    test_is_not_unsafe_integer<int&>();
    test_is_not_unsafe_integer<const int&>();
    test_is_not_unsafe_integer<volatile int&>();
    test_is_not_unsafe_integer<const volatile int&>();
    test_is_not_unsafe_integer<int&&>();
    test_is_not_unsafe_integer<const int&&>();
    test_is_not_unsafe_integer<volatile int&&>();
    test_is_not_unsafe_integer<const volatile int&&>();
    test_is_not_unsafe_integer<int*>();
    test_is_not_unsafe_integer<const int*>();
    test_is_not_unsafe_integer<volatile int*>();
    test_is_not_unsafe_integer<const volatile int*>();
    test_is_not_unsafe_integer<int**>();
    test_is_not_unsafe_integer<const int**>();
    test_is_not_unsafe_integer<volatile int**>();
    test_is_not_unsafe_integer<const volatile int**>();
    test_is_not_unsafe_integer<void*>();
    test_is_not_unsafe_integer<char[3]>();
    test_is_not_unsafe_integer<char[]>();
    test_is_not_unsafe_integer<char* [3]>();
    test_is_not_unsafe_integer<char*[]>();
    test_is_not_unsafe_integer<Class>();
    test_is_not_unsafe_integer<Union>();
    test_is_not_unsafe_integer<NonEmptyUnion>();
    test_is_not_unsafe_integer<Empty>();
    test_is_not_unsafe_integer<NotEmpty>();
    test_is_not_unsafe_integer<bit_zero>();
    test_is_not_unsafe_integer<bit_one>();
    test_is_not_unsafe_integer<Abstract>();
    test_is_not_unsafe_integer<AbstractTemplate<int>>();
    test_is_not_unsafe_integer<AbstractTemplate<double>>();
    test_is_not_unsafe_integer<AbstractTemplate<Class>>();
    test_is_not_unsafe_integer<AbstractTemplate<incomplete_type>>();
    test_is_not_unsafe_integer<Final>();
    test_is_not_unsafe_integer<Enum>();
    test_is_not_unsafe_integer<EnumSigned>();
    test_is_not_unsafe_integer<EnumUnsigned>();
    test_is_not_unsafe_integer<EnumClass>();
    test_is_not_unsafe_integer<Function>();
    test_is_not_unsafe_integer<FunctionPtr>();
    test_is_not_unsafe_integer<MemberObjectPtr>();
    test_is_not_unsafe_integer<MemberFunctionPtr>();
    test_is_not_unsafe_integer<incomplete_type>();
    test_is_not_unsafe_integer<int Class::*>();
    test_is_not_unsafe_integer<float Class::*>();

    test_is_not_unsafe_integer<void()>();
    test_is_not_unsafe_integer<void() noexcept>();
    test_is_not_unsafe_integer<void(int)>();
    test_is_not_unsafe_integer<void(int) noexcept>();

    test_is_not_unsafe_integer<void(...)>();
    test_is_not_unsafe_integer<void(...) noexcept>();
    test_is_not_unsafe_integer<void(int, ...)>();
    test_is_not_unsafe_integer<void(int, ...) noexcept>();

    test_is_not_unsafe_integer<void (*)()>();
    test_is_not_unsafe_integer<void (*)() noexcept>();
    test_is_not_unsafe_integer<void (*)(int)>();
    test_is_not_unsafe_integer<void (*)(int) noexcept>();

    test_is_not_unsafe_integer<void (*)(...)>();
    test_is_not_unsafe_integer<void (*)(...) noexcept>();
    test_is_not_unsafe_integer<void (*)(int, ...)>();
    test_is_not_unsafe_integer<void (*)(int, ...) noexcept>();

    test_is_not_unsafe_integer<void (Class::*)()>();
    test_is_not_unsafe_integer<void (Class::*)()&>();
    test_is_not_unsafe_integer<void (Class::*)() &&>();
    test_is_not_unsafe_integer<void (Class::*)() const>();
    test_is_not_unsafe_integer<void (Class::*)() const&>();
    test_is_not_unsafe_integer<void (Class::*)() const&&>();

    test_is_not_unsafe_integer<void (Class::*)() noexcept>();
    test_is_not_unsafe_integer<void (Class::*)()& noexcept>();
    test_is_not_unsafe_integer<void (Class::*)()&& noexcept>();
    test_is_not_unsafe_integer<void (Class::*)() const noexcept>();
    test_is_not_unsafe_integer<void (Class::*)() const& noexcept>();
    test_is_not_unsafe_integer<void (Class::*)() const&& noexcept>();

    test_is_not_unsafe_integer<void (Class::*)(int)>();
    test_is_not_unsafe_integer<void (Class::*)(int)&>();
    test_is_not_unsafe_integer<void (Class::*)(int) &&>();
    test_is_not_unsafe_integer<void (Class::*)(int) const>();
    test_is_not_unsafe_integer<void (Class::*)(int) const&>();
    test_is_not_unsafe_integer<void (Class::*)(int) const&&>();

    test_is_not_unsafe_integer<void (Class::*)(int) noexcept>();
    test_is_not_unsafe_integer<void (Class::*)(int)& noexcept>();
    test_is_not_unsafe_integer<void (Class::*)(int)&& noexcept>();
    test_is_not_unsafe_integer<void (Class::*)(int) const noexcept>();
    test_is_not_unsafe_integer<void (Class::*)(int) const& noexcept>();
    test_is_not_unsafe_integer<void (Class::*)(int) const&& noexcept>();

    test_is_not_unsafe_integer<void (Class::*)(...)>();
    test_is_not_unsafe_integer<void (Class::*)(...)&>();
    test_is_not_unsafe_integer<void (Class::*)(...) &&>();
    test_is_not_unsafe_integer<void (Class::*)(...) const>();
    test_is_not_unsafe_integer<void (Class::*)(...) const&>();
    test_is_not_unsafe_integer<void (Class::*)(...) const&&>();

    test_is_not_unsafe_integer<void (Class::*)(...) noexcept>();
    test_is_not_unsafe_integer<void (Class::*)(...)& noexcept>();
    test_is_not_unsafe_integer<void (Class::*)(...)&& noexcept>();
    test_is_not_unsafe_integer<void (Class::*)(...) const noexcept>();
    test_is_not_unsafe_integer<void (Class::*)(...) const& noexcept>();
    test_is_not_unsafe_integer<void (Class::*)(...) const&& noexcept>();
}
