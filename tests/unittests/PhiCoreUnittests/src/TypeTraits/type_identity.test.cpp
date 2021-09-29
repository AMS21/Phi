#include <catch2/catch.hpp>

#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/type_identity.hpp>
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

    test_type_identity<phi::Boolean>();
    test_type_identity<phi::Integer<signed char>>();
    test_type_identity<phi::Integer<unsigned char>>();
    test_type_identity<phi::Integer<short>>();
    test_type_identity<phi::Integer<unsigned short>>();
    test_type_identity<phi::Integer<int>>();
    test_type_identity<phi::Integer<unsigned int>>();
    test_type_identity<phi::Integer<long>>();
    test_type_identity<phi::Integer<unsigned long>>();
    test_type_identity<phi::Integer<long long>>();
    test_type_identity<phi::Integer<unsigned long long>>();
    test_type_identity<phi::FloatingPoint<float>>();
    test_type_identity<phi::FloatingPoint<double>>();
    test_type_identity<phi::FloatingPoint<long double>>();

    test_type_identity<std::vector<int>>();
    test_type_identity<phi::ScopePtr<int>>();

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
    test_type_identity<Struct>();
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
