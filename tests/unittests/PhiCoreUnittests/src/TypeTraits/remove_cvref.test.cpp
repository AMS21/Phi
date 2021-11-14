#include <catch2/catch.hpp>

#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/remove_cvref.hpp>
#include <vector>

template <typename T, typename U>
void test_remove_cvref()
{
    CHECK_SAME_TYPE(typename phi::remove_cvref<T>::type, U);
    CHECK_SAME_TYPE(typename phi::remove_cvref<const T>::type, U);
    CHECK_SAME_TYPE(typename phi::remove_cvref<volatile T>::type, U);
    CHECK_SAME_TYPE(typename phi::remove_cvref<const volatile T>::type, U);

    CHECK_SAME_TYPE(phi::remove_cvref_t<T>, U);
    CHECK_SAME_TYPE(phi::remove_cvref_t<const T>, U);
    CHECK_SAME_TYPE(phi::remove_cvref_t<volatile T>, U);
    CHECK_SAME_TYPE(phi::remove_cvref_t<const volatile T>, U);
}

TEST_CASE("remove_cvref")
{
    test_remove_cvref<void, void>();
    test_remove_cvref<phi::nullptr_t, phi::nullptr_t>();
    test_remove_cvref<bool, bool>();
    test_remove_cvref<char, char>();
    test_remove_cvref<signed char, signed char>();
    test_remove_cvref<unsigned char, unsigned char>();
    test_remove_cvref<short, short>();
    test_remove_cvref<unsigned short, unsigned short>();
    test_remove_cvref<int, int>();
    test_remove_cvref<unsigned int, unsigned int>();
    test_remove_cvref<long, long>();
    test_remove_cvref<unsigned long, unsigned long>();
    test_remove_cvref<long long, long long>();
    test_remove_cvref<unsigned long long, unsigned long long>();
    test_remove_cvref<float, float>();
    test_remove_cvref<double, double>();
    test_remove_cvref<long double, long double>();
    test_remove_cvref<char8_t, char8_t>();
    test_remove_cvref<char16_t, char16_t>();
    test_remove_cvref<char32_t, char32_t>();
    test_remove_cvref<wchar_t, wchar_t>();

    test_remove_cvref<phi::Boolean, phi::Boolean>();
    test_remove_cvref<phi::Integer<signed char>, phi::Integer<signed char>>();
    test_remove_cvref<phi::Integer<unsigned char>, phi::Integer<unsigned char>>();
    test_remove_cvref<phi::Integer<short>, phi::Integer<short>>();
    test_remove_cvref<phi::Integer<unsigned short>, phi::Integer<unsigned short>>();
    test_remove_cvref<phi::Integer<int>, phi::Integer<int>>();
    test_remove_cvref<phi::Integer<unsigned int>, phi::Integer<unsigned int>>();
    test_remove_cvref<phi::Integer<long>, phi::Integer<long>>();
    test_remove_cvref<phi::Integer<unsigned long>, phi::Integer<unsigned long>>();
    test_remove_cvref<phi::Integer<long long>, phi::Integer<long long>>();
    test_remove_cvref<phi::Integer<unsigned long long>, phi::Integer<unsigned long long>>();
    test_remove_cvref<phi::FloatingPoint<float>, phi::FloatingPoint<float>>();
    test_remove_cvref<phi::FloatingPoint<double>, phi::FloatingPoint<double>>();
    test_remove_cvref<phi::FloatingPoint<long double>, phi::FloatingPoint<long double>>();

    test_remove_cvref<std::vector<int>, std::vector<int>>();
    test_remove_cvref<phi::ScopePtr<int>, phi::ScopePtr<int>>();

    test_remove_cvref<int&, int>();
    test_remove_cvref<const int&, int>();
    test_remove_cvref<volatile int&, int>();
    test_remove_cvref<const volatile int&, int>();
    test_remove_cvref<int&&, int>();
    test_remove_cvref<const int&&, int>();
    test_remove_cvref<volatile int&&, int>();
    test_remove_cvref<const volatile int&&, int>();
    test_remove_cvref<int*, int*>();
    test_remove_cvref<const int*, const int*>();
    test_remove_cvref<volatile int*, volatile int*>();
    test_remove_cvref<const volatile int*, const volatile int*>();
    test_remove_cvref<int**, int**>();
    test_remove_cvref<const int**, const int**>();
    test_remove_cvref<volatile int**, volatile int**>();
    test_remove_cvref<const volatile int**, const volatile int**>();
    test_remove_cvref<void*, void*>();
    test_remove_cvref<char[3], char[3]>();
    test_remove_cvref<char[], char[]>();
    test_remove_cvref<char* [3], char* [3]>();
    test_remove_cvref<char*[], char*[]>();
    test_remove_cvref<Class, Class>();
    test_remove_cvref<Union, Union>();
    test_remove_cvref<NonEmptyUnion, NonEmptyUnion>();
    test_remove_cvref<Empty, Empty>();
    test_remove_cvref<NotEmpty, NotEmpty>();
    test_remove_cvref<bit_zero, bit_zero>();
    test_remove_cvref<bit_one, bit_one>();
    test_remove_cvref<Abstract, Abstract>();
    test_remove_cvref<AbstractTemplate<int>, AbstractTemplate<int>>();
    test_remove_cvref<AbstractTemplate<double>, AbstractTemplate<double>>();
    test_remove_cvref<AbstractTemplate<Class>, AbstractTemplate<Class>>();
    test_remove_cvref<AbstractTemplate<incomplete_type>, AbstractTemplate<incomplete_type>>();
    test_remove_cvref<Final, Final>();
    test_remove_cvref<Enum, Enum>();
    test_remove_cvref<EnumSigned, EnumSigned>();
    test_remove_cvref<EnumUnsigned, EnumUnsigned>();
    test_remove_cvref<EnumClass, EnumClass>();
    test_remove_cvref<Function, Function>();
    test_remove_cvref<FunctionPtr, FunctionPtr>();
    test_remove_cvref<MemberObjectPtr, MemberObjectPtr>();
    test_remove_cvref<MemberFunctionPtr, MemberFunctionPtr>();
    test_remove_cvref<incomplete_type, incomplete_type>();
    test_remove_cvref<int Class::*, int Class::*>();
    test_remove_cvref<float Class::*, float Class::*>();

    test_remove_cvref<void(), void()>();
    test_remove_cvref<void() noexcept, void() noexcept>();
    test_remove_cvref<void(int), void(int)>();
    test_remove_cvref<void(int) noexcept, void(int) noexcept>();

    test_remove_cvref<void(...), void(...)>();
    test_remove_cvref<void(...) noexcept, void(...) noexcept>();
    test_remove_cvref<void(int, ...), void(int, ...)>();
    test_remove_cvref<void(int, ...) noexcept, void(int, ...) noexcept>();

    test_remove_cvref<void (*)(), void (*)()>();
    test_remove_cvref<void (*)() noexcept, void (*)() noexcept>();
    test_remove_cvref<void (*)(int), void (*)(int)>();
    test_remove_cvref<void (*)(int) noexcept, void (*)(int) noexcept>();

    test_remove_cvref<void (*)(...), void (*)(...)>();
    test_remove_cvref<void (*)(...) noexcept, void (*)(...) noexcept>();
    test_remove_cvref<void (*)(int, ...), void (*)(int, ...)>();
    test_remove_cvref<void (*)(int, ...) noexcept, void (*)(int, ...) noexcept>();

    test_remove_cvref<void (Class::*)(), void (Class::*)()>();
    test_remove_cvref<void (Class::*)()&, void (Class::*)()&>();
    test_remove_cvref<void (Class::*)()&&, void (Class::*)() &&>();
    test_remove_cvref<void (Class::*)() const, void (Class::*)() const>();
    test_remove_cvref<void (Class::*)() const&, void (Class::*)() const&>();
    test_remove_cvref<void (Class::*)() const&&, void (Class::*)() const&&>();

    test_remove_cvref<void (Class::*)() noexcept, void (Class::*)() noexcept>();
    test_remove_cvref<void (Class::*)()& noexcept, void (Class::*)()& noexcept>();
    test_remove_cvref<void (Class::*)()&& noexcept, void (Class::*)()&& noexcept>();
    test_remove_cvref<void (Class::*)() const noexcept, void (Class::*)() const noexcept>();
    test_remove_cvref<void (Class::*)() const& noexcept, void (Class::*)() const& noexcept>();
    test_remove_cvref<void (Class::*)() const&& noexcept, void (Class::*)() const&& noexcept>();

    test_remove_cvref<void (Class::*)(int), void (Class::*)(int)>();
    test_remove_cvref<void (Class::*)(int)&, void (Class::*)(int)&>();
    test_remove_cvref<void (Class::*)(int)&&, void (Class::*)(int) &&>();
    test_remove_cvref<void (Class::*)(int) const, void (Class::*)(int) const>();
    test_remove_cvref<void (Class::*)(int) const&, void (Class::*)(int) const&>();
    test_remove_cvref<void (Class::*)(int) const&&, void (Class::*)(int) const&&>();

    test_remove_cvref<void (Class::*)(int) noexcept, void (Class::*)(int) noexcept>();
    test_remove_cvref<void (Class::*)(int)& noexcept, void (Class::*)(int)& noexcept>();
    test_remove_cvref<void (Class::*)(int)&& noexcept, void (Class::*)(int)&& noexcept>();
    test_remove_cvref<void (Class::*)(int) const noexcept, void (Class::*)(int) const noexcept>();
    test_remove_cvref<void (Class::*)(int) const& noexcept, void (Class::*)(int) const& noexcept>();
    test_remove_cvref<void (Class::*)(int) const&& noexcept,
                      void (Class::*)(int) const&& noexcept>();

    test_remove_cvref<void (Class::*)(...), void (Class::*)(...)>();
    test_remove_cvref<void (Class::*)(...)&, void (Class::*)(...)&>();
    test_remove_cvref<void (Class::*)(...)&&, void (Class::*)(...) &&>();
    test_remove_cvref<void (Class::*)(...) const, void (Class::*)(...) const>();
    test_remove_cvref<void (Class::*)(...) const&, void (Class::*)(...) const&>();
    test_remove_cvref<void (Class::*)(...) const&&, void (Class::*)(...) const&&>();

    test_remove_cvref<void (Class::*)(...) noexcept, void (Class::*)(...) noexcept>();
    test_remove_cvref<void (Class::*)(...)& noexcept, void (Class::*)(...)& noexcept>();
    test_remove_cvref<void (Class::*)(...)&& noexcept, void (Class::*)(...)&& noexcept>();
    test_remove_cvref<void (Class::*)(...) const noexcept, void (Class::*)(...) const noexcept>();
    test_remove_cvref<void (Class::*)(...) const& noexcept, void (Class::*)(...) const& noexcept>();
    test_remove_cvref<void (Class::*)(...) const&& noexcept,
                      void (Class::*)(...) const&& noexcept>();
}
