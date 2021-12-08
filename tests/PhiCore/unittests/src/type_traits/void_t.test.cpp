#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/void_t.hpp>
#include <vector>

template <typename T>
void test_void_t()
{
    CHECK_SAME_TYPE(void, phi::void_t<T>);
    CHECK_SAME_TYPE(void, phi::void_t<const T>);
    CHECK_SAME_TYPE(void, phi::void_t<volatile T>);
    CHECK_SAME_TYPE(void, phi::void_t<const volatile T>);
}

template <typename T, typename U>
void test_void_t()
{
    CHECK_SAME_TYPE(void, phi::void_t<T, U>);
    CHECK_SAME_TYPE(void, phi::void_t<T, const U>);
    CHECK_SAME_TYPE(void, phi::void_t<T, volatile U>);
    CHECK_SAME_TYPE(void, phi::void_t<T, const volatile U>);

    CHECK_SAME_TYPE(void, phi::void_t<const T, U>);
    CHECK_SAME_TYPE(void, phi::void_t<const T, const U>);
    CHECK_SAME_TYPE(void, phi::void_t<const T, volatile U>);
    CHECK_SAME_TYPE(void, phi::void_t<const T, const volatile U>);

    CHECK_SAME_TYPE(void, phi::void_t<volatile T, U>);
    CHECK_SAME_TYPE(void, phi::void_t<volatile T, const U>);
    CHECK_SAME_TYPE(void, phi::void_t<volatile T, volatile U>);
    CHECK_SAME_TYPE(void, phi::void_t<volatile T, const volatile U>);

    CHECK_SAME_TYPE(void, phi::void_t<const volatile T, U>);
    CHECK_SAME_TYPE(void, phi::void_t<const volatile T, const U>);
    CHECK_SAME_TYPE(void, phi::void_t<const volatile T, volatile U>);
    CHECK_SAME_TYPE(void, phi::void_t<const volatile T, const volatile U>);
}

TEST_CASE("is_void")
{
    CHECK_SAME_TYPE(void, phi::void_t<>);

    test_void_t<void, void>();
    test_void_t<void, void*>();
    test_void_t<void, int>();
    test_void_t<void, double>();
    test_void_t<int, void>();
    test_void_t<double, void>();
    test_void_t<double, int>();
    test_void_t<int&, void>();
    test_void_t<int&, void*>();
    test_void_t<int&, int>();
    test_void_t<int&&, void>();
    test_void_t<int&&, void*>();
    test_void_t<int&&, int>();
    test_void_t<Class, void>();
    test_void_t<Class, int>();
    test_void_t<Class&, void>();
    test_void_t<Class&, int>();
    test_void_t<Class&&, void>();
    test_void_t<Class&&, int>();
    test_void_t<Class[], void>();
    test_void_t<Class[], int>();
    test_void_t<Class[3], void>();
    test_void_t<Class[3], int>();
    test_void_t<void*, void>();
    test_void_t<void*, void*>();
    test_void_t<void*, int&>();
    test_void_t<void*, int&&>();

    CHECK_SAME_TYPE(void, phi::void_t<int, int, int>);
    CHECK_SAME_TYPE(void, phi::void_t<int, int, int, int>);
    CHECK_SAME_TYPE(void, phi::void_t<int, int, int, int, int>);
    CHECK_SAME_TYPE(void, phi::void_t<int, double const&, Class, volatile int[], void>);
    CHECK_SAME_TYPE(
            void,
            phi::void_t<int, double const&, Class, volatile int[], void, int (*)(double, float)>);

    test_void_t<void>();
    test_void_t<phi::nullptr_t>();
    test_void_t<bool>();
    test_void_t<char>();
    test_void_t<signed char>();
    test_void_t<unsigned char>();
    test_void_t<short>();
    test_void_t<unsigned short>();
    test_void_t<int>();
    test_void_t<unsigned int>();
    test_void_t<long>();
    test_void_t<unsigned long>();
    test_void_t<long long>();
    test_void_t<unsigned long long>();
    test_void_t<float>();
    test_void_t<double>();
    test_void_t<long double>();
    test_void_t<char8_t>();
    test_void_t<char16_t>();
    test_void_t<char32_t>();
    test_void_t<wchar_t>();

    test_void_t<phi::boolean>();
    test_void_t<phi::integer<signed char>>();
    test_void_t<phi::integer<unsigned char>>();
    test_void_t<phi::integer<short>>();
    test_void_t<phi::integer<unsigned short>>();
    test_void_t<phi::integer<int>>();
    test_void_t<phi::integer<unsigned int>>();
    test_void_t<phi::integer<long>>();
    test_void_t<phi::integer<unsigned long>>();
    test_void_t<phi::integer<long long>>();
    test_void_t<phi::integer<unsigned long long>>();
    test_void_t<phi::floating_point<float>>();
    test_void_t<phi::floating_point<double>>();
    test_void_t<phi::floating_point<long double>>();

    test_void_t<std::vector<int>>();
    test_void_t<phi::scope_ptr<int>>();

    test_void_t<int&>();
    test_void_t<const int&>();
    test_void_t<volatile int&>();
    test_void_t<const volatile int&>();
    test_void_t<int&&>();
    test_void_t<const int&&>();
    test_void_t<volatile int&&>();
    test_void_t<const volatile int&&>();
    test_void_t<int*>();
    test_void_t<const int*>();
    test_void_t<volatile int*>();
    test_void_t<const volatile int*>();
    test_void_t<int**>();
    test_void_t<const int**>();
    test_void_t<volatile int**>();
    test_void_t<const volatile int**>();
    test_void_t<int*&>();
    test_void_t<const int*&>();
    test_void_t<volatile int*&>();
    test_void_t<const volatile int*&>();
    test_void_t<void*>();
    test_void_t<char[3]>();
    test_void_t<char[]>();
    test_void_t<char* [3]>();
    test_void_t<char*[]>();
    test_void_t<int(*)[3]>();
    test_void_t<int(*)[]>();
    test_void_t<int(&)[3]>();
    test_void_t<int(&)[]>();
    test_void_t<Class>();
    test_void_t<Union>();
    test_void_t<NonEmptyUnion>();
    test_void_t<Empty>();
    test_void_t<NotEmpty>();
    test_void_t<bit_zero>();
    test_void_t<bit_one>();
    test_void_t<Abstract>();
    test_void_t<AbstractTemplate<int>>();
    test_void_t<AbstractTemplate<double>>();
    test_void_t<AbstractTemplate<Class>>();
    test_void_t<AbstractTemplate<incomplete_type>>();
    test_void_t<Final>();
    test_void_t<Enum>();
    test_void_t<EnumSigned>();
    test_void_t<EnumUnsigned>();
    test_void_t<EnumClass>();
    test_void_t<Function>();
    test_void_t<FunctionPtr>();
    test_void_t<MemberObjectPtr>();
    test_void_t<MemberFunctionPtr>();
    test_void_t<incomplete_type>();
    test_void_t<int Class::*>();
    test_void_t<float Class::*>();
    test_void_t<void * Class::*>();
    test_void_t<int * Class::*>();

    test_void_t<void()>();
    test_void_t<void() noexcept>();
    test_void_t<void(int)>();
    test_void_t<void(int) noexcept>();

    test_void_t<void(...)>();
    test_void_t<void(...) noexcept>();
    test_void_t<void(int, ...)>();
    test_void_t<void(int, ...) noexcept>();

    test_void_t<void (*)()>();
    test_void_t<void (*)() noexcept>();
    test_void_t<void (*)(int)>();
    test_void_t<void (*)(int) noexcept>();

    test_void_t<void (*)(...)>();
    test_void_t<void (*)(...) noexcept>();
    test_void_t<void (*)(int, ...)>();
    test_void_t<void (*)(int, ...) noexcept>();

    test_void_t<void (Class::*)()>();
    test_void_t<void (Class::*)()&>();
    test_void_t<void (Class::*)() &&>();
    test_void_t<void (Class::*)() const>();
    test_void_t<void (Class::*)() const&>();
    test_void_t<void (Class::*)() const&&>();

    test_void_t<void (Class::*)() noexcept>();
    test_void_t<void (Class::*)()& noexcept>();
    test_void_t<void (Class::*)()&& noexcept>();
    test_void_t<void (Class::*)() const noexcept>();
    test_void_t<void (Class::*)() const& noexcept>();
    test_void_t<void (Class::*)() const&& noexcept>();

    test_void_t<void (Class::*)(int)>();
    test_void_t<void (Class::*)(int)&>();
    test_void_t<void (Class::*)(int) &&>();
    test_void_t<void (Class::*)(int) const>();
    test_void_t<void (Class::*)(int) const&>();
    test_void_t<void (Class::*)(int) const&&>();

    test_void_t<void (Class::*)(int) noexcept>();
    test_void_t<void (Class::*)(int)& noexcept>();
    test_void_t<void (Class::*)(int)&& noexcept>();
    test_void_t<void (Class::*)(int) const noexcept>();
    test_void_t<void (Class::*)(int) const& noexcept>();
    test_void_t<void (Class::*)(int) const&& noexcept>();

    test_void_t<void (Class::*)(...)>();
    test_void_t<void (Class::*)(...)&>();
    test_void_t<void (Class::*)(...) &&>();
    test_void_t<void (Class::*)(...) const>();
    test_void_t<void (Class::*)(...) const&>();
    test_void_t<void (Class::*)(...) const&&>();

    test_void_t<void (Class::*)(...) noexcept>();
    test_void_t<void (Class::*)(...)& noexcept>();
    test_void_t<void (Class::*)(...)&& noexcept>();
    test_void_t<void (Class::*)(...) const noexcept>();
    test_void_t<void (Class::*)(...) const& noexcept>();
    test_void_t<void (Class::*)(...) const&& noexcept>();

    test_void_t<void (Class::*)(int, ...)>();
    test_void_t<void (Class::*)(int, ...)&>();
    test_void_t<void (Class::*)(int, ...) &&>();
    test_void_t<void (Class::*)(int, ...) const>();
    test_void_t<void (Class::*)(int, ...) const&>();
    test_void_t<void (Class::*)(int, ...) const&&>();

    test_void_t<void (Class::*)(int, ...) noexcept>();
    test_void_t<void (Class::*)(int, ...)& noexcept>();
    test_void_t<void (Class::*)(int, ...)&& noexcept>();
    test_void_t<void (Class::*)(int, ...) const noexcept>();
    test_void_t<void (Class::*)(int, ...) const& noexcept>();
    test_void_t<void (Class::*)(int, ...) const&& noexcept>();
}
