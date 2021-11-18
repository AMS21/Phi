#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/integral_constant.hpp>
#include <Phi/TypeTraits/underlying_type.hpp>
#include <Phi/TypeTraits/void_t.hpp>
#include <climits>
#include <vector>

template <typename, class = phi::void_t<>>
struct has_type_member : public phi::false_type
{};

template <typename T>
struct has_type_member<T, phi::void_t<typename phi::underlying_type<T>::type>>
    : public phi::true_type
{};

template <typename T, typename U>
void test_underlying_type()
{
    CHECK_SAME_TYPE(typename phi::underlying_type<T>::type, U);
    CHECK_SAME_TYPE(typename phi::underlying_type<const T>::type, U);
    CHECK_SAME_TYPE(typename phi::underlying_type<volatile T>::type, U);
    CHECK_SAME_TYPE(typename phi::underlying_type<const volatile T>::type, U);

    CHECK_SAME_TYPE(phi::underlying_type_t<T>, U);
    CHECK_SAME_TYPE(phi::underlying_type_t<const T>, U);
    CHECK_SAME_TYPE(phi::underlying_type_t<volatile T>, U);
    CHECK_SAME_TYPE(phi::underlying_type_t<const volatile T>, U);
}

template <typename T>
void test_no_underlying_type()
{
    STATIC_REQUIRE_FALSE(has_type_member<T>::value);
    STATIC_REQUIRE_FALSE(has_type_member<const T>::value);
    STATIC_REQUIRE_FALSE(has_type_member<volatile T>::value);
    STATIC_REQUIRE_FALSE(has_type_member<const volatile T>::value);
}

enum E
{
    V = INT_MIN
};

enum F
{
    W = UINT_MAX
};

enum G : char
{
};

enum class H
{
    red,
    green = 20,
    blue
};

enum class I : long
{
    red,
    green = 20,
    blue
};

enum struct J
{
    red,
    green = 20,
    blue
};

enum struct K : short
{
    red,
    green = 20,
    blue
};

TEST_CASE("is_void")
{
    test_underlying_type<E, int>();
    test_underlying_type<F, unsigned>();
    test_underlying_type<G, char>();
    test_underlying_type<H, int>();
    test_underlying_type<I, long>();
    test_underlying_type<J, int>();
    test_underlying_type<K, short>();

    test_no_underlying_type<void>();
    test_no_underlying_type<phi::nullptr_t>();
    test_no_underlying_type<bool>();
    test_no_underlying_type<char>();
    test_no_underlying_type<signed char>();
    test_no_underlying_type<unsigned char>();
    test_no_underlying_type<short>();
    test_no_underlying_type<unsigned short>();
    test_no_underlying_type<int>();
    test_no_underlying_type<unsigned int>();
    test_no_underlying_type<long>();
    test_no_underlying_type<unsigned long>();
    test_no_underlying_type<long long>();
    test_no_underlying_type<unsigned long long>();
    test_no_underlying_type<float>();
    test_no_underlying_type<double>();
    test_no_underlying_type<long double>();
    test_no_underlying_type<char8_t>();
    test_no_underlying_type<char16_t>();
    test_no_underlying_type<char32_t>();
    test_no_underlying_type<wchar_t>();

    test_no_underlying_type<phi::Boolean>();
    test_no_underlying_type<phi::Integer<signed char>>();
    test_no_underlying_type<phi::Integer<unsigned char>>();
    test_no_underlying_type<phi::Integer<short>>();
    test_no_underlying_type<phi::Integer<unsigned short>>();
    test_no_underlying_type<phi::Integer<int>>();
    test_no_underlying_type<phi::Integer<unsigned int>>();
    test_no_underlying_type<phi::Integer<long>>();
    test_no_underlying_type<phi::Integer<unsigned long>>();
    test_no_underlying_type<phi::Integer<long long>>();
    test_no_underlying_type<phi::Integer<unsigned long long>>();
    test_no_underlying_type<phi::FloatingPoint<float>>();
    test_no_underlying_type<phi::FloatingPoint<double>>();
    test_no_underlying_type<phi::FloatingPoint<long double>>();

    test_no_underlying_type<std::vector<int>>();
    test_no_underlying_type<phi::ScopePtr<int>>();

    test_no_underlying_type<int&>();
    test_no_underlying_type<const int&>();
    test_no_underlying_type<volatile int&>();
    test_no_underlying_type<const volatile int&>();
    test_no_underlying_type<int&&>();
    test_no_underlying_type<const int&&>();
    test_no_underlying_type<volatile int&&>();
    test_no_underlying_type<const volatile int&&>();
    test_no_underlying_type<int*>();
    test_no_underlying_type<const int*>();
    test_no_underlying_type<volatile int*>();
    test_no_underlying_type<const volatile int*>();
    test_no_underlying_type<int**>();
    test_no_underlying_type<const int**>();
    test_no_underlying_type<volatile int**>();
    test_no_underlying_type<const volatile int**>();
    test_no_underlying_type<int*&>();
    test_no_underlying_type<const int*&>();
    test_no_underlying_type<volatile int*&>();
    test_no_underlying_type<const volatile int*&>();
    test_no_underlying_type<void*>();
    test_no_underlying_type<char[3]>();
    test_no_underlying_type<char[]>();
    test_no_underlying_type<char* [3]>();
    test_no_underlying_type<char*[]>();
    test_no_underlying_type<int(*)[3]>();
    test_no_underlying_type<int(*)[]>();
    test_no_underlying_type<int(&)[3]>();
    test_no_underlying_type<int(&)[]>();
    test_no_underlying_type<Class>();
    test_no_underlying_type<Union>();
    test_no_underlying_type<NonEmptyUnion>();
    test_no_underlying_type<Empty>();
    test_no_underlying_type<NotEmpty>();
    test_no_underlying_type<bit_zero>();
    test_no_underlying_type<bit_one>();
    test_no_underlying_type<Abstract>();
    test_no_underlying_type<AbstractTemplate<int>>();
    test_no_underlying_type<AbstractTemplate<double>>();
    test_no_underlying_type<AbstractTemplate<Class>>();
    test_no_underlying_type<AbstractTemplate<incomplete_type>>();
    test_no_underlying_type<Final>();
    test_underlying_type<Enum, unsigned int>();
    test_underlying_type<EnumSigned, int>();
    test_underlying_type<EnumUnsigned, unsigned int>();
    test_underlying_type<EnumClass, int>();
    test_no_underlying_type<Function>();
    test_no_underlying_type<FunctionPtr>();
    test_no_underlying_type<MemberObjectPtr>();
    test_no_underlying_type<MemberFunctionPtr>();
    test_no_underlying_type<incomplete_type>();
    test_no_underlying_type<int Class::*>();
    test_no_underlying_type<float Class::*>();
    test_no_underlying_type<void * Class::*>();
    test_no_underlying_type<int * Class::*>();

    test_no_underlying_type<void()>();
    test_no_underlying_type<void() noexcept>();
    test_no_underlying_type<void(int)>();
    test_no_underlying_type<void(int) noexcept>();

    test_no_underlying_type<void(...)>();
    test_no_underlying_type<void(...) noexcept>();
    test_no_underlying_type<void(int, ...)>();
    test_no_underlying_type<void(int, ...) noexcept>();

    test_no_underlying_type<void (*)()>();
    test_no_underlying_type<void (*)() noexcept>();
    test_no_underlying_type<void (*)(int)>();
    test_no_underlying_type<void (*)(int) noexcept>();

    test_no_underlying_type<void (*)(...)>();
    test_no_underlying_type<void (*)(...) noexcept>();
    test_no_underlying_type<void (*)(int, ...)>();
    test_no_underlying_type<void (*)(int, ...) noexcept>();

    test_no_underlying_type<void (Class::*)()>();
    test_no_underlying_type<void (Class::*)()&>();
    test_no_underlying_type<void (Class::*)() &&>();
    test_no_underlying_type<void (Class::*)() const>();
    test_no_underlying_type<void (Class::*)() const&>();
    test_no_underlying_type<void (Class::*)() const&&>();

    test_no_underlying_type<void (Class::*)() noexcept>();
    test_no_underlying_type<void (Class::*)()& noexcept>();
    test_no_underlying_type<void (Class::*)()&& noexcept>();
    test_no_underlying_type<void (Class::*)() const noexcept>();
    test_no_underlying_type<void (Class::*)() const& noexcept>();
    test_no_underlying_type<void (Class::*)() const&& noexcept>();

    test_no_underlying_type<void (Class::*)(int)>();
    test_no_underlying_type<void (Class::*)(int)&>();
    test_no_underlying_type<void (Class::*)(int) &&>();
    test_no_underlying_type<void (Class::*)(int) const>();
    test_no_underlying_type<void (Class::*)(int) const&>();
    test_no_underlying_type<void (Class::*)(int) const&&>();

    test_no_underlying_type<void (Class::*)(int) noexcept>();
    test_no_underlying_type<void (Class::*)(int)& noexcept>();
    test_no_underlying_type<void (Class::*)(int)&& noexcept>();
    test_no_underlying_type<void (Class::*)(int) const noexcept>();
    test_no_underlying_type<void (Class::*)(int) const& noexcept>();
    test_no_underlying_type<void (Class::*)(int) const&& noexcept>();

    test_no_underlying_type<void (Class::*)(...)>();
    test_no_underlying_type<void (Class::*)(...)&>();
    test_no_underlying_type<void (Class::*)(...) &&>();
    test_no_underlying_type<void (Class::*)(...) const>();
    test_no_underlying_type<void (Class::*)(...) const&>();
    test_no_underlying_type<void (Class::*)(...) const&&>();

    test_no_underlying_type<void (Class::*)(...) noexcept>();
    test_no_underlying_type<void (Class::*)(...)& noexcept>();
    test_no_underlying_type<void (Class::*)(...)&& noexcept>();
    test_no_underlying_type<void (Class::*)(...) const noexcept>();
    test_no_underlying_type<void (Class::*)(...) const& noexcept>();
    test_no_underlying_type<void (Class::*)(...) const&& noexcept>();

    test_no_underlying_type<void (Class::*)(int, ...)>();
    test_no_underlying_type<void (Class::*)(int, ...)&>();
    test_no_underlying_type<void (Class::*)(int, ...) &&>();
    test_no_underlying_type<void (Class::*)(int, ...) const>();
    test_no_underlying_type<void (Class::*)(int, ...) const&>();
    test_no_underlying_type<void (Class::*)(int, ...) const&&>();

    test_no_underlying_type<void (Class::*)(int, ...) noexcept>();
    test_no_underlying_type<void (Class::*)(int, ...)& noexcept>();
    test_no_underlying_type<void (Class::*)(int, ...)&& noexcept>();
    test_no_underlying_type<void (Class::*)(int, ...) const noexcept>();
    test_no_underlying_type<void (Class::*)(int, ...) const& noexcept>();
    test_no_underlying_type<void (Class::*)(int, ...) const&& noexcept>();
}
