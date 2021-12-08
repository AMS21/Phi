#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_unsigned.hpp>
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

    test_is_unsigned<phi::boolean>();
    test_is_not_unsigned<phi::integer<signed char>>();
    test_is_unsigned<phi::integer<unsigned char>>();
    test_is_not_unsigned<phi::integer<short>>();
    test_is_unsigned<phi::integer<unsigned short>>();
    test_is_not_unsigned<phi::integer<int>>();
    test_is_unsigned<phi::integer<unsigned int>>();
    test_is_not_unsigned<phi::integer<long>>();
    test_is_unsigned<phi::integer<unsigned long>>();
    test_is_not_unsigned<phi::integer<long long>>();
    test_is_unsigned<phi::integer<unsigned long long>>();
    test_is_not_unsigned<phi::floating_point<float>>();
    test_is_not_unsigned<phi::floating_point<double>>();
    test_is_not_unsigned<phi::floating_point<long double>>();

    test_is_not_unsigned<std::vector<int>>();
    test_is_not_unsigned<phi::scope_ptr<int>>();

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
