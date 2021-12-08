#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/type_identity.hpp>
#include <vector>

template <typename T>
void test_type_identity()
{
    CHECK_SAME_TYPE(T, typename phi::type_identity<T>::type);
    CHECK_SAME_TYPE(const T, const typename phi::type_identity<T>::type);
    CHECK_SAME_TYPE(volatile T, volatile typename phi::type_identity<T>::type);
    CHECK_SAME_TYPE(const volatile T, const volatile typename phi::type_identity<T>::type);

    CHECK_SAME_TYPE(const T, typename phi::type_identity<const T>::type);
    CHECK_SAME_TYPE(volatile T, typename phi::type_identity<volatile T>::type);
    CHECK_SAME_TYPE(const volatile T, volatile typename phi::type_identity<const volatile T>::type);

    CHECK_SAME_TYPE(T, phi::type_identity_t<T>);
    CHECK_SAME_TYPE(const T, const phi::type_identity_t<T>);
    CHECK_SAME_TYPE(volatile T, volatile phi::type_identity_t<T>);
    CHECK_SAME_TYPE(const volatile T, const volatile phi::type_identity_t<T>);

    CHECK_SAME_TYPE(const T, phi::type_identity_t<const T>);
    CHECK_SAME_TYPE(volatile T, phi::type_identity_t<volatile T>);
    CHECK_SAME_TYPE(const volatile T, phi::type_identity_t<const volatile T>);
}

TEST_CASE("type_identity")
{
    test_type_identity<void>();
    test_type_identity<phi::nullptr_t>();
    test_type_identity<bool>();
    test_type_identity<char>();
    test_type_identity<signed char>();
    test_type_identity<unsigned char>();
    test_type_identity<short>();
    test_type_identity<unsigned short>();
    test_type_identity<int>();
    test_type_identity<unsigned int>();
    test_type_identity<long>();
    test_type_identity<unsigned long>();
    test_type_identity<long long>();
    test_type_identity<unsigned long long>();
    test_type_identity<float>();
    test_type_identity<double>();
    test_type_identity<long double>();
    test_type_identity<char8_t>();
    test_type_identity<char16_t>();
    test_type_identity<char32_t>();
    test_type_identity<wchar_t>();

    test_type_identity<phi::boolean>();
    test_type_identity<phi::integer<signed char>>();
    test_type_identity<phi::integer<unsigned char>>();
    test_type_identity<phi::integer<short>>();
    test_type_identity<phi::integer<unsigned short>>();
    test_type_identity<phi::integer<int>>();
    test_type_identity<phi::integer<unsigned int>>();
    test_type_identity<phi::integer<long>>();
    test_type_identity<phi::integer<unsigned long>>();
    test_type_identity<phi::integer<long long>>();
    test_type_identity<phi::integer<unsigned long long>>();
    test_type_identity<phi::floating_point<float>>();
    test_type_identity<phi::floating_point<double>>();
    test_type_identity<phi::floating_point<long double>>();

    test_type_identity<std::vector<int>>();
    test_type_identity<phi::scope_ptr<int>>();

    test_type_identity<int&>();
    test_type_identity<const int&>();
    test_type_identity<volatile int&>();
    test_type_identity<const volatile int&>();
    test_type_identity<int&&>();
    test_type_identity<const int&&>();
    test_type_identity<volatile int&&>();
    test_type_identity<const volatile int&&>();
    test_type_identity<int*>();
    test_type_identity<const int*>();
    test_type_identity<volatile int*>();
    test_type_identity<const volatile int*>();
    test_type_identity<int**>();
    test_type_identity<const int**>();
    test_type_identity<volatile int**>();
    test_type_identity<const volatile int**>();
    test_type_identity<int*&>();
    test_type_identity<const int*&>();
    test_type_identity<volatile int*&>();
    test_type_identity<const volatile int*&>();
    test_type_identity<void*>();
    test_type_identity<char[3]>();
    test_type_identity<char[]>();
    test_type_identity<char* [3]>();
    test_type_identity<char*[]>();
    test_type_identity<int(*)[3]>();
    test_type_identity<int(*)[]>();
    test_type_identity<int(&)[3]>();
    test_type_identity<int(&)[]>();
    test_type_identity<Class>();
    test_type_identity<Union>();
    test_type_identity<NonEmptyUnion>();
    test_type_identity<Empty>();
    test_type_identity<NotEmpty>();
    test_type_identity<bit_zero>();
    test_type_identity<bit_one>();
    test_type_identity<Abstract>();
    test_type_identity<AbstractTemplate<int>>();
    test_type_identity<AbstractTemplate<double>>();
    test_type_identity<AbstractTemplate<Class>>();
    test_type_identity<AbstractTemplate<incomplete_type>>();
    test_type_identity<Final>();
    test_type_identity<Enum>();
    test_type_identity<EnumSigned>();
    test_type_identity<EnumUnsigned>();
    test_type_identity<EnumClass>();
    test_type_identity<Function>();
    test_type_identity<FunctionPtr>();
    test_type_identity<MemberObjectPtr>();
    test_type_identity<MemberFunctionPtr>();
    test_type_identity<incomplete_type>();
    test_type_identity<int Class::*>();
    test_type_identity<float Class::*>();
    test_type_identity<void * Class::*>();
    test_type_identity<int * Class::*>();

    test_type_identity<void()>();
    test_type_identity<void() noexcept>();
    test_type_identity<void(int)>();
    test_type_identity<void(int) noexcept>();

    test_type_identity<void(...)>();
    test_type_identity<void(...) noexcept>();
    test_type_identity<void(int, ...)>();
    test_type_identity<void(int, ...) noexcept>();

    test_type_identity<void (*)()>();
    test_type_identity<void (*)() noexcept>();
    test_type_identity<void (*)(int)>();
    test_type_identity<void (*)(int) noexcept>();

    test_type_identity<void (*)(...)>();
    test_type_identity<void (*)(...) noexcept>();
    test_type_identity<void (*)(int, ...)>();
    test_type_identity<void (*)(int, ...) noexcept>();

    test_type_identity<void (Class::*)()>();
    test_type_identity<void (Class::*)()&>();
    test_type_identity<void (Class::*)() &&>();
    test_type_identity<void (Class::*)() const>();
    test_type_identity<void (Class::*)() const&>();
    test_type_identity<void (Class::*)() const&&>();

    test_type_identity<void (Class::*)() noexcept>();
    test_type_identity<void (Class::*)()& noexcept>();
    test_type_identity<void (Class::*)()&& noexcept>();
    test_type_identity<void (Class::*)() const noexcept>();
    test_type_identity<void (Class::*)() const& noexcept>();
    test_type_identity<void (Class::*)() const&& noexcept>();

    test_type_identity<void (Class::*)(int)>();
    test_type_identity<void (Class::*)(int)&>();
    test_type_identity<void (Class::*)(int) &&>();
    test_type_identity<void (Class::*)(int) const>();
    test_type_identity<void (Class::*)(int) const&>();
    test_type_identity<void (Class::*)(int) const&&>();

    test_type_identity<void (Class::*)(int) noexcept>();
    test_type_identity<void (Class::*)(int)& noexcept>();
    test_type_identity<void (Class::*)(int)&& noexcept>();
    test_type_identity<void (Class::*)(int) const noexcept>();
    test_type_identity<void (Class::*)(int) const& noexcept>();
    test_type_identity<void (Class::*)(int) const&& noexcept>();

    test_type_identity<void (Class::*)(...)>();
    test_type_identity<void (Class::*)(...)&>();
    test_type_identity<void (Class::*)(...) &&>();
    test_type_identity<void (Class::*)(...) const>();
    test_type_identity<void (Class::*)(...) const&>();
    test_type_identity<void (Class::*)(...) const&&>();

    test_type_identity<void (Class::*)(...) noexcept>();
    test_type_identity<void (Class::*)(...)& noexcept>();
    test_type_identity<void (Class::*)(...)&& noexcept>();
    test_type_identity<void (Class::*)(...) const noexcept>();
    test_type_identity<void (Class::*)(...) const& noexcept>();
    test_type_identity<void (Class::*)(...) const&& noexcept>();

    test_type_identity<void (Class::*)(int, ...)>();
    test_type_identity<void (Class::*)(int, ...)&>();
    test_type_identity<void (Class::*)(int, ...) &&>();
    test_type_identity<void (Class::*)(int, ...) const>();
    test_type_identity<void (Class::*)(int, ...) const&>();
    test_type_identity<void (Class::*)(int, ...) const&&>();

    test_type_identity<void (Class::*)(int, ...) noexcept>();
    test_type_identity<void (Class::*)(int, ...)& noexcept>();
    test_type_identity<void (Class::*)(int, ...)&& noexcept>();
    test_type_identity<void (Class::*)(int, ...) const noexcept>();
    test_type_identity<void (Class::*)(int, ...) const& noexcept>();
    test_type_identity<void (Class::*)(int, ...) const&& noexcept>();
}
