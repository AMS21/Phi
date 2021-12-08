#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_safe_floating_point.hpp>
#include <vector>

template <typename T>
void test_is_safe_floating_point()
{
    STATIC_REQUIRE(phi::is_safe_floating_point<T>::value);
    STATIC_REQUIRE(phi::is_safe_floating_point<const T>::value);
    STATIC_REQUIRE(phi::is_safe_floating_point<volatile T>::value);
    STATIC_REQUIRE(phi::is_safe_floating_point<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_safe_floating_point_v<T>);
    STATIC_REQUIRE(phi::is_safe_floating_point_v<const T>);
    STATIC_REQUIRE(phi::is_safe_floating_point_v<volatile T>);
    STATIC_REQUIRE(phi::is_safe_floating_point_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_safe_floating_point()
{
    STATIC_REQUIRE_FALSE(phi::is_safe_floating_point<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_safe_floating_point<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_safe_floating_point<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_safe_floating_point<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_floating_point_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_safe_floating_point_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_safe_floating_point_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_safe_floating_point_v<const volatile T>);
#endif
}

TEST_CASE("is_safe_floating_point")
{
    test_is_safe_floating_point<phi::floating_point<float>>();
    test_is_safe_floating_point<phi::floating_point<double>>();
    test_is_safe_floating_point<phi::floating_point<long double>>();

    test_is_not_safe_floating_point<void>();
    test_is_not_safe_floating_point<phi::nullptr_t>();
    test_is_not_safe_floating_point<bool>();
    test_is_not_safe_floating_point<char>();
    test_is_not_safe_floating_point<signed char>();
    test_is_not_safe_floating_point<unsigned char>();
    test_is_not_safe_floating_point<short>();
    test_is_not_safe_floating_point<unsigned short>();
    test_is_not_safe_floating_point<int>();
    test_is_not_safe_floating_point<unsigned int>();
    test_is_not_safe_floating_point<long>();
    test_is_not_safe_floating_point<unsigned long>();
    test_is_not_safe_floating_point<long long>();
    test_is_not_safe_floating_point<unsigned long long>();
    test_is_not_safe_floating_point<float>();
    test_is_not_safe_floating_point<double>();
    test_is_not_safe_floating_point<long double>();
    test_is_not_safe_floating_point<char8_t>();
    test_is_not_safe_floating_point<char16_t>();
    test_is_not_safe_floating_point<char32_t>();
    test_is_not_safe_floating_point<wchar_t>();

    test_is_not_safe_floating_point<phi::boolean>();
    test_is_not_safe_floating_point<phi::integer<signed char>>();
    test_is_not_safe_floating_point<phi::integer<unsigned char>>();
    test_is_not_safe_floating_point<phi::integer<short>>();
    test_is_not_safe_floating_point<phi::integer<unsigned short>>();
    test_is_not_safe_floating_point<phi::integer<int>>();
    test_is_not_safe_floating_point<phi::integer<unsigned int>>();
    test_is_not_safe_floating_point<phi::integer<long>>();
    test_is_not_safe_floating_point<phi::integer<unsigned long>>();
    test_is_not_safe_floating_point<phi::integer<long long>>();
    test_is_not_safe_floating_point<phi::integer<unsigned long long>>();

    test_is_not_safe_floating_point<std::vector<int>>();
    test_is_not_safe_floating_point<phi::scope_ptr<int>>();

    test_is_not_safe_floating_point<int&>();
    test_is_not_safe_floating_point<int&&>();
    test_is_not_safe_floating_point<int*>();
    test_is_not_safe_floating_point<const int*>();
    test_is_not_safe_floating_point<volatile int*>();
    test_is_not_safe_floating_point<const volatile int*>();
    test_is_not_safe_floating_point<int**>();
    test_is_not_safe_floating_point<char[3]>();
    test_is_not_safe_floating_point<char[]>();
    test_is_not_safe_floating_point<char* [3]>();
    test_is_not_safe_floating_point<char*[]>();
    test_is_not_safe_floating_point<Class>();
    test_is_not_safe_floating_point<Union>();
    test_is_not_safe_floating_point<NonEmptyUnion>();
    test_is_not_safe_floating_point<Empty>();
    test_is_not_safe_floating_point<NotEmpty>();
    test_is_not_safe_floating_point<bit_zero>();
    test_is_not_safe_floating_point<bit_one>();
    test_is_not_safe_floating_point<Abstract>();
    test_is_not_safe_floating_point<AbstractTemplate<int>>();
    test_is_not_safe_floating_point<AbstractTemplate<double>>();
    test_is_not_safe_floating_point<AbstractTemplate<Class>>();
    test_is_not_safe_floating_point<AbstractTemplate<incomplete_type>>();
    test_is_not_safe_floating_point<Final>();
    test_is_not_safe_floating_point<Enum>();
    test_is_not_safe_floating_point<EnumSigned>();
    test_is_not_safe_floating_point<EnumUnsigned>();
    test_is_not_safe_floating_point<EnumClass>();
    test_is_not_safe_floating_point<Function>();
    test_is_not_safe_floating_point<FunctionPtr>();
    test_is_not_safe_floating_point<MemberObjectPtr>();
    test_is_not_safe_floating_point<MemberFunctionPtr>();
    test_is_not_safe_floating_point<incomplete_type>();
    test_is_not_safe_floating_point<int Class::*>();
    test_is_not_safe_floating_point<float Class::*>();

    test_is_not_safe_floating_point<void()>();
    test_is_not_safe_floating_point<void() noexcept>();
    test_is_not_safe_floating_point<void(int)>();
    test_is_not_safe_floating_point<void(int) noexcept>();

    test_is_not_safe_floating_point<void(...)>();
    test_is_not_safe_floating_point<void(...) noexcept>();
    test_is_not_safe_floating_point<void(int, ...)>();
    test_is_not_safe_floating_point<void(int, ...) noexcept>();

    test_is_not_safe_floating_point<void (*)()>();
    test_is_not_safe_floating_point<void (*)() noexcept>();
    test_is_not_safe_floating_point<void (*)(int)>();
    test_is_not_safe_floating_point<void (*)(int) noexcept>();

    test_is_not_safe_floating_point<void (*)(...)>();
    test_is_not_safe_floating_point<void (*)(...) noexcept>();
    test_is_not_safe_floating_point<void (*)(int, ...)>();
    test_is_not_safe_floating_point<void (*)(int, ...) noexcept>();

    test_is_not_safe_floating_point<void (Class::*)()>();
    test_is_not_safe_floating_point<void (Class::*)()&>();
    test_is_not_safe_floating_point<void (Class::*)() &&>();
    test_is_not_safe_floating_point<void (Class::*)() const>();
    test_is_not_safe_floating_point<void (Class::*)() const&>();
    test_is_not_safe_floating_point<void (Class::*)() const&&>();

    test_is_not_safe_floating_point<void (Class::*)() noexcept>();
    test_is_not_safe_floating_point<void (Class::*)()& noexcept>();
    test_is_not_safe_floating_point<void (Class::*)()&& noexcept>();
    test_is_not_safe_floating_point<void (Class::*)() const noexcept>();
    test_is_not_safe_floating_point<void (Class::*)() const& noexcept>();
    test_is_not_safe_floating_point<void (Class::*)() const&& noexcept>();

    test_is_not_safe_floating_point<void (Class::*)(int)>();
    test_is_not_safe_floating_point<void (Class::*)(int)&>();
    test_is_not_safe_floating_point<void (Class::*)(int) &&>();
    test_is_not_safe_floating_point<void (Class::*)(int) const>();
    test_is_not_safe_floating_point<void (Class::*)(int) const&>();
    test_is_not_safe_floating_point<void (Class::*)(int) const&&>();

    test_is_not_safe_floating_point<void (Class::*)(int) noexcept>();
    test_is_not_safe_floating_point<void (Class::*)(int)& noexcept>();
    test_is_not_safe_floating_point<void (Class::*)(int)&& noexcept>();
    test_is_not_safe_floating_point<void (Class::*)(int) const noexcept>();
    test_is_not_safe_floating_point<void (Class::*)(int) const& noexcept>();
    test_is_not_safe_floating_point<void (Class::*)(int) const&& noexcept>();

    test_is_not_safe_floating_point<void (Class::*)(...)>();
    test_is_not_safe_floating_point<void (Class::*)(...)&>();
    test_is_not_safe_floating_point<void (Class::*)(...) &&>();
    test_is_not_safe_floating_point<void (Class::*)(...) const>();
    test_is_not_safe_floating_point<void (Class::*)(...) const&>();
    test_is_not_safe_floating_point<void (Class::*)(...) const&&>();

    test_is_not_safe_floating_point<void (Class::*)(...) noexcept>();
    test_is_not_safe_floating_point<void (Class::*)(...)& noexcept>();
    test_is_not_safe_floating_point<void (Class::*)(...)&& noexcept>();
    test_is_not_safe_floating_point<void (Class::*)(...) const noexcept>();
    test_is_not_safe_floating_point<void (Class::*)(...) const& noexcept>();
    test_is_not_safe_floating_point<void (Class::*)(...) const&& noexcept>();
}
