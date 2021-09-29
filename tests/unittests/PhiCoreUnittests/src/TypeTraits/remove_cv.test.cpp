#include <catch2/catch.hpp>

#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/remove_cv.hpp>
#include <vector>

template <typename T, typename U>
void test_remove_cv()
{
    CHECK_SAME_TYPE(typename phi::remove_cv<T>::type, U);
    CHECK_SAME_TYPE(typename phi::remove_cv<const T>::type, U);
    CHECK_SAME_TYPE(typename phi::remove_cv<volatile T>::type, U);
    CHECK_SAME_TYPE(typename phi::remove_cv<const volatile T>::type, U);

    CHECK_SAME_TYPE(phi::remove_cv_t<T>, U);
    CHECK_SAME_TYPE(phi::remove_cv_t<const T>, U);
    CHECK_SAME_TYPE(phi::remove_cv_t<volatile T>, U);
    CHECK_SAME_TYPE(phi::remove_cv_t<const volatile T>, U);
}

TEST_CASE("remove_cv")
{
    test_remove_cv<void, void>();
    test_remove_cv<phi::nullptr_t, phi::nullptr_t>();
    test_remove_cv<bool, bool>();
    test_remove_cv<char, char>();
    test_remove_cv<signed char, signed char>();
    test_remove_cv<unsigned char, unsigned char>();
    test_remove_cv<short, short>();
    test_remove_cv<unsigned short, unsigned short>();
    test_remove_cv<int, int>();
    test_remove_cv<unsigned int, unsigned int>();
    test_remove_cv<long, long>();
    test_remove_cv<unsigned long, unsigned long>();
    test_remove_cv<long long, long long>();
    test_remove_cv<unsigned long long, unsigned long long>();
    test_remove_cv<float, float>();
    test_remove_cv<double, double>();
    test_remove_cv<long double, long double>();
    test_remove_cv<char8_t, char8_t>();
    test_remove_cv<char16_t, char16_t>();
    test_remove_cv<char32_t, char32_t>();
    test_remove_cv<wchar_t, wchar_t>();

    test_remove_cv<phi::Boolean, phi::Boolean>();
    test_remove_cv<phi::Integer<signed char>, phi::Integer<signed char>>();
    test_remove_cv<phi::Integer<unsigned char>, phi::Integer<unsigned char>>();
    test_remove_cv<phi::Integer<short>, phi::Integer<short>>();
    test_remove_cv<phi::Integer<unsigned short>, phi::Integer<unsigned short>>();
    test_remove_cv<phi::Integer<int>, phi::Integer<int>>();
    test_remove_cv<phi::Integer<unsigned int>, phi::Integer<unsigned int>>();
    test_remove_cv<phi::Integer<long>, phi::Integer<long>>();
    test_remove_cv<phi::Integer<unsigned long>, phi::Integer<unsigned long>>();
    test_remove_cv<phi::Integer<long long>, phi::Integer<long long>>();
    test_remove_cv<phi::Integer<unsigned long long>, phi::Integer<unsigned long long>>();
    test_remove_cv<phi::FloatingPoint<float>, phi::FloatingPoint<float>>();
    test_remove_cv<phi::FloatingPoint<double>, phi::FloatingPoint<double>>();
    test_remove_cv<phi::FloatingPoint<long double>, phi::FloatingPoint<long double>>();

    test_remove_cv<std::vector<int>, std::vector<int>>();
    test_remove_cv<phi::ScopePtr<int>, phi::ScopePtr<int>>();

    test_remove_cv<int&, int&>();
    test_remove_cv<const int&, const int&>();
    test_remove_cv<volatile int&, volatile int&>();
    test_remove_cv<const volatile int&, const volatile int&>();
    test_remove_cv<int&&, int&&>();
    test_remove_cv<const int&&, const int&&>();
    test_remove_cv<volatile int&&, volatile int&&>();
    test_remove_cv<const volatile int&&, const volatile int&&>();
    test_remove_cv<int*, int*>();
    test_remove_cv<const int*, const int*>();
    test_remove_cv<volatile int*, volatile int*>();
    test_remove_cv<const volatile int*, const volatile int*>();
    test_remove_cv<int**, int**>();
    test_remove_cv<const int**, const int**>();
    test_remove_cv<volatile int**, volatile int**>();
    test_remove_cv<const volatile int**, const volatile int**>();
    test_remove_cv<void*, void*>();
    test_remove_cv<char[3], char[3]>();
    test_remove_cv<char[], char[]>();
    test_remove_cv<char* [3], char* [3]>();
    test_remove_cv<char*[], char*[]>();
    test_remove_cv<Class, Class>();
    test_remove_cv<Struct, Struct>();
    test_remove_cv<Union, Union>();
    test_remove_cv<NonEmptyUnion, NonEmptyUnion>();
    test_remove_cv<Empty, Empty>();
    test_remove_cv<NotEmpty, NotEmpty>();
    test_remove_cv<bit_zero, bit_zero>();
    test_remove_cv<bit_one, bit_one>();
    test_remove_cv<Abstract, Abstract>();
    test_remove_cv<AbstractTemplate<int>, AbstractTemplate<int>>();
    test_remove_cv<AbstractTemplate<double>, AbstractTemplate<double>>();
    test_remove_cv<AbstractTemplate<Class>, AbstractTemplate<Class>>();
    test_remove_cv<AbstractTemplate<incomplete_type>, AbstractTemplate<incomplete_type>>();
    test_remove_cv<Final, Final>();
    test_remove_cv<Enum, Enum>();
    test_remove_cv<EnumSigned, EnumSigned>();
    test_remove_cv<EnumUnsigned, EnumUnsigned>();
    test_remove_cv<EnumClass, EnumClass>();
    test_remove_cv<Function, Function>();
    test_remove_cv<FunctionPtr, FunctionPtr>();
    test_remove_cv<MemberObjectPtr, MemberObjectPtr>();
    test_remove_cv<MemberFunctionPtr, MemberFunctionPtr>();
    test_remove_cv<incomplete_type, incomplete_type>();
    test_remove_cv<int Class::*, int Class::*>();
    test_remove_cv<float Class::*, float Class::*>();

    test_remove_cv<void(), void()>();
    test_remove_cv<void() noexcept, void() noexcept>();
    test_remove_cv<void(int), void(int)>();
    test_remove_cv<void(int) noexcept, void(int) noexcept>();

    test_remove_cv<void(...), void(...)>();
    test_remove_cv<void(...) noexcept, void(...) noexcept>();
    test_remove_cv<void(int, ...), void(int, ...)>();
    test_remove_cv<void(int, ...) noexcept, void(int, ...) noexcept>();

    test_remove_cv<void (*)(), void (*)()>();
    test_remove_cv<void (*)() noexcept, void (*)() noexcept>();
    test_remove_cv<void (*)(int), void (*)(int)>();
    test_remove_cv<void (*)(int) noexcept, void (*)(int) noexcept>();

    test_remove_cv<void (*)(...), void (*)(...)>();
    test_remove_cv<void (*)(...) noexcept, void (*)(...) noexcept>();
    test_remove_cv<void (*)(int, ...), void (*)(int, ...)>();
    test_remove_cv<void (*)(int, ...) noexcept, void (*)(int, ...) noexcept>();

    test_remove_cv<void (Class::*)(), void (Class::*)()>();
    test_remove_cv<void (Class::*)()&, void (Class::*)()&>();
    test_remove_cv<void (Class::*)()&&, void (Class::*)() &&>();
    test_remove_cv<void (Class::*)() const, void (Class::*)() const>();
    test_remove_cv<void (Class::*)() const&, void (Class::*)() const&>();
    test_remove_cv<void (Class::*)() const&&, void (Class::*)() const&&>();

    test_remove_cv<void (Class::*)() noexcept, void (Class::*)() noexcept>();
    test_remove_cv<void (Class::*)()& noexcept, void (Class::*)()& noexcept>();
    test_remove_cv<void (Class::*)()&& noexcept, void (Class::*)()&& noexcept>();
    test_remove_cv<void (Class::*)() const noexcept, void (Class::*)() const noexcept>();
    test_remove_cv<void (Class::*)() const& noexcept, void (Class::*)() const& noexcept>();
    test_remove_cv<void (Class::*)() const&& noexcept, void (Class::*)() const&& noexcept>();

    test_remove_cv<void (Class::*)(int), void (Class::*)(int)>();
    test_remove_cv<void (Class::*)(int)&, void (Class::*)(int)&>();
    test_remove_cv<void (Class::*)(int)&&, void (Class::*)(int) &&>();
    test_remove_cv<void (Class::*)(int) const, void (Class::*)(int) const>();
    test_remove_cv<void (Class::*)(int) const&, void (Class::*)(int) const&>();
    test_remove_cv<void (Class::*)(int) const&&, void (Class::*)(int) const&&>();

    test_remove_cv<void (Class::*)(int) noexcept, void (Class::*)(int) noexcept>();
    test_remove_cv<void (Class::*)(int)& noexcept, void (Class::*)(int)& noexcept>();
    test_remove_cv<void (Class::*)(int)&& noexcept, void (Class::*)(int)&& noexcept>();
    test_remove_cv<void (Class::*)(int) const noexcept, void (Class::*)(int) const noexcept>();
    test_remove_cv<void (Class::*)(int) const& noexcept, void (Class::*)(int) const& noexcept>();
    test_remove_cv<void (Class::*)(int) const&& noexcept, void (Class::*)(int) const&& noexcept>();

    test_remove_cv<void (Class::*)(...), void (Class::*)(...)>();
    test_remove_cv<void (Class::*)(...)&, void (Class::*)(...)&>();
    test_remove_cv<void (Class::*)(...)&&, void (Class::*)(...) &&>();
    test_remove_cv<void (Class::*)(...) const, void (Class::*)(...) const>();
    test_remove_cv<void (Class::*)(...) const&, void (Class::*)(...) const&>();
    test_remove_cv<void (Class::*)(...) const&&, void (Class::*)(...) const&&>();

    test_remove_cv<void (Class::*)(...) noexcept, void (Class::*)(...) noexcept>();
    test_remove_cv<void (Class::*)(...)& noexcept, void (Class::*)(...)& noexcept>();
    test_remove_cv<void (Class::*)(...)&& noexcept, void (Class::*)(...)&& noexcept>();
    test_remove_cv<void (Class::*)(...) const noexcept, void (Class::*)(...) const noexcept>();
    test_remove_cv<void (Class::*)(...) const& noexcept, void (Class::*)(...) const& noexcept>();
    test_remove_cv<void (Class::*)(...) const&& noexcept, void (Class::*)(...) const&& noexcept>();
}
