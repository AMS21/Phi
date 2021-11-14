#include <catch2/catch.hpp>

#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/remove_const.hpp>
#include <vector>

template <typename T, typename U>
void test_remove_const()
{
    CHECK_SAME_TYPE(typename phi::remove_const<T>::type, U);
    CHECK_SAME_TYPE(typename phi::remove_const<const T>::type, U);
    CHECK_SAME_TYPE(typename phi::remove_const<volatile T>::type, volatile U);
    CHECK_SAME_TYPE(typename phi::remove_const<const volatile T>::type, volatile U);

    CHECK_SAME_TYPE(phi::remove_const_t<T>, U);
    CHECK_SAME_TYPE(phi::remove_const_t<const T>, U);
    CHECK_SAME_TYPE(phi::remove_const_t<volatile T>, volatile U);
    CHECK_SAME_TYPE(phi::remove_const_t<const volatile T>, volatile U);
}

TEST_CASE("remove_const")
{
    test_remove_const<void, void>();
    test_remove_const<phi::nullptr_t, phi::nullptr_t>();
    test_remove_const<bool, bool>();
    test_remove_const<char, char>();
    test_remove_const<signed char, signed char>();
    test_remove_const<unsigned char, unsigned char>();
    test_remove_const<short, short>();
    test_remove_const<unsigned short, unsigned short>();
    test_remove_const<int, int>();
    test_remove_const<unsigned int, unsigned int>();
    test_remove_const<long, long>();
    test_remove_const<unsigned long, unsigned long>();
    test_remove_const<long long, long long>();
    test_remove_const<unsigned long long, unsigned long long>();
    test_remove_const<float, float>();
    test_remove_const<double, double>();
    test_remove_const<long double, long double>();
    test_remove_const<char8_t, char8_t>();
    test_remove_const<char16_t, char16_t>();
    test_remove_const<char32_t, char32_t>();
    test_remove_const<wchar_t, wchar_t>();

    test_remove_const<phi::Boolean, phi::Boolean>();
    test_remove_const<phi::Integer<signed char>, phi::Integer<signed char>>();
    test_remove_const<phi::Integer<unsigned char>, phi::Integer<unsigned char>>();
    test_remove_const<phi::Integer<short>, phi::Integer<short>>();
    test_remove_const<phi::Integer<unsigned short>, phi::Integer<unsigned short>>();
    test_remove_const<phi::Integer<int>, phi::Integer<int>>();
    test_remove_const<phi::Integer<unsigned int>, phi::Integer<unsigned int>>();
    test_remove_const<phi::Integer<long>, phi::Integer<long>>();
    test_remove_const<phi::Integer<unsigned long>, phi::Integer<unsigned long>>();
    test_remove_const<phi::Integer<long long>, phi::Integer<long long>>();
    test_remove_const<phi::Integer<unsigned long long>, phi::Integer<unsigned long long>>();
    test_remove_const<phi::FloatingPoint<float>, phi::FloatingPoint<float>>();
    test_remove_const<phi::FloatingPoint<double>, phi::FloatingPoint<double>>();
    test_remove_const<phi::FloatingPoint<long double>, phi::FloatingPoint<long double>>();

    test_remove_const<std::vector<int>, std::vector<int>>();
    test_remove_const<phi::ScopePtr<int>, phi::ScopePtr<int>>();

    test_remove_const<int&, int&>();
    test_remove_const<const int&, const int&>();
    test_remove_const<volatile int&, volatile int&>();
    test_remove_const<const volatile int&, const volatile int&>();
    test_remove_const<int&&, int&&>();
    test_remove_const<const int&&, const int&&>();
    test_remove_const<volatile int&&, volatile int&&>();
    test_remove_const<const volatile int&&, const volatile int&&>();
    test_remove_const<int*, int*>();
    test_remove_const<const int*, const int*>();
    test_remove_const<volatile int*, volatile int*>();
    test_remove_const<const volatile int*, const volatile int*>();
    test_remove_const<int**, int**>();
    test_remove_const<const int**, const int**>();
    test_remove_const<volatile int**, volatile int**>();
    test_remove_const<const volatile int**, const volatile int**>();
    test_remove_const<void*, void*>();
    test_remove_const<char[3], char[3]>();
    test_remove_const<char[], char[]>();
    test_remove_const<char* [3], char* [3]>();
    test_remove_const<char*[], char*[]>();
    test_remove_const<Class, Class>();
    test_remove_const<Union, Union>();
    test_remove_const<NonEmptyUnion, NonEmptyUnion>();
    test_remove_const<Empty, Empty>();
    test_remove_const<NotEmpty, NotEmpty>();
    test_remove_const<bit_zero, bit_zero>();
    test_remove_const<bit_one, bit_one>();
    test_remove_const<Abstract, Abstract>();
    test_remove_const<AbstractTemplate<int>, AbstractTemplate<int>>();
    test_remove_const<AbstractTemplate<double>, AbstractTemplate<double>>();
    test_remove_const<AbstractTemplate<Class>, AbstractTemplate<Class>>();
    test_remove_const<AbstractTemplate<incomplete_type>, AbstractTemplate<incomplete_type>>();
    test_remove_const<Final, Final>();
    test_remove_const<Enum, Enum>();
    test_remove_const<EnumSigned, EnumSigned>();
    test_remove_const<EnumUnsigned, EnumUnsigned>();
    test_remove_const<EnumClass, EnumClass>();
    test_remove_const<Function, Function>();
    test_remove_const<FunctionPtr, FunctionPtr>();
    test_remove_const<MemberObjectPtr, MemberObjectPtr>();
    test_remove_const<MemberFunctionPtr, MemberFunctionPtr>();
    test_remove_const<incomplete_type, incomplete_type>();
    test_remove_const<int Class::*, int Class::*>();
    test_remove_const<float Class::*, float Class::*>();

    test_remove_const<void(), void()>();
    test_remove_const<void() noexcept, void() noexcept>();
    test_remove_const<void(int), void(int)>();
    test_remove_const<void(int) noexcept, void(int) noexcept>();

    test_remove_const<void(...), void(...)>();
    test_remove_const<void(...) noexcept, void(...) noexcept>();
    test_remove_const<void(int, ...), void(int, ...)>();
    test_remove_const<void(int, ...) noexcept, void(int, ...) noexcept>();

    test_remove_const<void (*)(), void (*)()>();
    test_remove_const<void (*)() noexcept, void (*)() noexcept>();
    test_remove_const<void (*)(int), void (*)(int)>();
    test_remove_const<void (*)(int) noexcept, void (*)(int) noexcept>();

    test_remove_const<void (*)(...), void (*)(...)>();
    test_remove_const<void (*)(...) noexcept, void (*)(...) noexcept>();
    test_remove_const<void (*)(int, ...), void (*)(int, ...)>();
    test_remove_const<void (*)(int, ...) noexcept, void (*)(int, ...) noexcept>();

    test_remove_const<void (Class::*)(), void (Class::*)()>();
    test_remove_const<void (Class::*)()&, void (Class::*)()&>();
    test_remove_const<void (Class::*)()&&, void (Class::*)() &&>();
    test_remove_const<void (Class::*)() const, void (Class::*)() const>();
    test_remove_const<void (Class::*)() const&, void (Class::*)() const&>();
    test_remove_const<void (Class::*)() const&&, void (Class::*)() const&&>();

    test_remove_const<void (Class::*)() noexcept, void (Class::*)() noexcept>();
    test_remove_const<void (Class::*)()& noexcept, void (Class::*)()& noexcept>();
    test_remove_const<void (Class::*)()&& noexcept, void (Class::*)()&& noexcept>();
    test_remove_const<void (Class::*)() const noexcept, void (Class::*)() const noexcept>();
    test_remove_const<void (Class::*)() const& noexcept, void (Class::*)() const& noexcept>();
    test_remove_const<void (Class::*)() const&& noexcept, void (Class::*)() const&& noexcept>();

    test_remove_const<void (Class::*)(int), void (Class::*)(int)>();
    test_remove_const<void (Class::*)(int)&, void (Class::*)(int)&>();
    test_remove_const<void (Class::*)(int)&&, void (Class::*)(int) &&>();
    test_remove_const<void (Class::*)(int) const, void (Class::*)(int) const>();
    test_remove_const<void (Class::*)(int) const&, void (Class::*)(int) const&>();
    test_remove_const<void (Class::*)(int) const&&, void (Class::*)(int) const&&>();

    test_remove_const<void (Class::*)(int) noexcept, void (Class::*)(int) noexcept>();
    test_remove_const<void (Class::*)(int)& noexcept, void (Class::*)(int)& noexcept>();
    test_remove_const<void (Class::*)(int)&& noexcept, void (Class::*)(int)&& noexcept>();
    test_remove_const<void (Class::*)(int) const noexcept, void (Class::*)(int) const noexcept>();
    test_remove_const<void (Class::*)(int) const& noexcept, void (Class::*)(int) const& noexcept>();
    test_remove_const<void (Class::*)(int) const&& noexcept,
                      void (Class::*)(int) const&& noexcept>();

    test_remove_const<void (Class::*)(...), void (Class::*)(...)>();
    test_remove_const<void (Class::*)(...)&, void (Class::*)(...)&>();
    test_remove_const<void (Class::*)(...)&&, void (Class::*)(...) &&>();
    test_remove_const<void (Class::*)(...) const, void (Class::*)(...) const>();
    test_remove_const<void (Class::*)(...) const&, void (Class::*)(...) const&>();
    test_remove_const<void (Class::*)(...) const&&, void (Class::*)(...) const&&>();

    test_remove_const<void (Class::*)(...) noexcept, void (Class::*)(...) noexcept>();
    test_remove_const<void (Class::*)(...)& noexcept, void (Class::*)(...)& noexcept>();
    test_remove_const<void (Class::*)(...)&& noexcept, void (Class::*)(...)&& noexcept>();
    test_remove_const<void (Class::*)(...) const noexcept, void (Class::*)(...) const noexcept>();
    test_remove_const<void (Class::*)(...) const& noexcept, void (Class::*)(...) const& noexcept>();
    test_remove_const<void (Class::*)(...) const&& noexcept,
                      void (Class::*)(...) const&& noexcept>();
}
