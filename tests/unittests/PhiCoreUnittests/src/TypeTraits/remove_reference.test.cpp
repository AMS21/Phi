#include <catch2/catch.hpp>

#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/remove_reference.hpp>
#include <vector>

template <typename T, typename U>
void test_remove_reference()
{
    CHECK_SAME_TYPE(typename phi::remove_reference<T>::type, U);
    CHECK_SAME_TYPE(typename phi::remove_reference<const T>::type, const U);
    CHECK_SAME_TYPE(typename phi::remove_reference<volatile T>::type, volatile U);
    CHECK_SAME_TYPE(typename phi::remove_reference<const volatile T>::type, const volatile U);

    CHECK_SAME_TYPE(phi::remove_reference_t<T>, U);
    CHECK_SAME_TYPE(phi::remove_reference_t<const T>, const U);
    CHECK_SAME_TYPE(phi::remove_reference_t<volatile T>, volatile U);
    CHECK_SAME_TYPE(phi::remove_reference_t<const volatile T>, const volatile U);
}

template <typename T, typename U>
void test_remove_reference_ref()
{
    CHECK_SAME_TYPE(typename phi::remove_reference<T>::type, U);
    CHECK_SAME_TYPE(phi::remove_reference_t<T>, U);
}

TEST_CASE("remove_reference")
{
    test_remove_reference<void, void>();
    test_remove_reference<phi::nullptr_t, phi::nullptr_t>();
    test_remove_reference<bool, bool>();
    test_remove_reference<char, char>();
    test_remove_reference<signed char, signed char>();
    test_remove_reference<unsigned char, unsigned char>();
    test_remove_reference<short, short>();
    test_remove_reference<unsigned short, unsigned short>();
    test_remove_reference<int, int>();
    test_remove_reference<unsigned int, unsigned int>();
    test_remove_reference<long, long>();
    test_remove_reference<unsigned long, unsigned long>();
    test_remove_reference<long long, long long>();
    test_remove_reference<unsigned long long, unsigned long long>();
    test_remove_reference<float, float>();
    test_remove_reference<double, double>();
    test_remove_reference<long double, long double>();
    test_remove_reference<char8_t, char8_t>();
    test_remove_reference<char16_t, char16_t>();
    test_remove_reference<char32_t, char32_t>();
    test_remove_reference<wchar_t, wchar_t>();

    test_remove_reference<phi::Boolean, phi::Boolean>();
    test_remove_reference<phi::Integer<signed char>, phi::Integer<signed char>>();
    test_remove_reference<phi::Integer<unsigned char>, phi::Integer<unsigned char>>();
    test_remove_reference<phi::Integer<short>, phi::Integer<short>>();
    test_remove_reference<phi::Integer<unsigned short>, phi::Integer<unsigned short>>();
    test_remove_reference<phi::Integer<int>, phi::Integer<int>>();
    test_remove_reference<phi::Integer<unsigned int>, phi::Integer<unsigned int>>();
    test_remove_reference<phi::Integer<long>, phi::Integer<long>>();
    test_remove_reference<phi::Integer<unsigned long>, phi::Integer<unsigned long>>();
    test_remove_reference<phi::Integer<long long>, phi::Integer<long long>>();
    test_remove_reference<phi::Integer<unsigned long long>, phi::Integer<unsigned long long>>();
    test_remove_reference<phi::FloatingPoint<float>, phi::FloatingPoint<float>>();
    test_remove_reference<phi::FloatingPoint<double>, phi::FloatingPoint<double>>();
    test_remove_reference<phi::FloatingPoint<long double>, phi::FloatingPoint<long double>>();

    test_remove_reference<std::vector<int>, std::vector<int>>();
    test_remove_reference<phi::ScopePtr<int>, phi::ScopePtr<int>>();

    test_remove_reference_ref<int&, int>();
    test_remove_reference_ref<const int&, const int>();
    test_remove_reference_ref<volatile int&, volatile int>();
    test_remove_reference_ref<const volatile int&, const volatile int>();
    test_remove_reference_ref<int&&, int>();
    test_remove_reference_ref<const int&&, const int>();
    test_remove_reference_ref<volatile int&&, volatile int>();
    test_remove_reference_ref<const volatile int&&, const volatile int>();
    test_remove_reference<int*, int*>();
    test_remove_reference<const int*, const int*>();
    test_remove_reference<volatile int*, volatile int*>();
    test_remove_reference<const volatile int*, const volatile int*>();
    test_remove_reference<int**, int**>();
    test_remove_reference<const int**, const int**>();
    test_remove_reference<volatile int**, volatile int**>();
    test_remove_reference<const volatile int**, const volatile int**>();
    test_remove_reference_ref<int*&, int*>();
    test_remove_reference_ref<const int*&, const int*>();
    test_remove_reference_ref<volatile int*&, volatile int*>();
    test_remove_reference_ref<const volatile int*&, const volatile int*>();
    test_remove_reference<void*, void*>();
    test_remove_reference<char[3], char[3]>();
    test_remove_reference<char[], char[]>();
    test_remove_reference<char* [3], char* [3]>();
    test_remove_reference<char*[], char*[]>();
    test_remove_reference<int(*)[3], int(*)[3]>();
    test_remove_reference<int(*)[], int(*)[]>();
    test_remove_reference_ref<int(&)[3], int[3]>();
    test_remove_reference_ref<int(&)[], int[]>();
    test_remove_reference<Class, Class>();
    test_remove_reference<Struct, Struct>();
    test_remove_reference<Union, Union>();
    test_remove_reference<NonEmptyUnion, NonEmptyUnion>();
    test_remove_reference<Empty, Empty>();
    test_remove_reference<NotEmpty, NotEmpty>();
    test_remove_reference<bit_zero, bit_zero>();
    test_remove_reference<bit_one, bit_one>();
    test_remove_reference<Abstract, Abstract>();
    test_remove_reference<AbstractTemplate<int>, AbstractTemplate<int>>();
    test_remove_reference<AbstractTemplate<double>, AbstractTemplate<double>>();
    test_remove_reference<AbstractTemplate<Class>, AbstractTemplate<Class>>();
    test_remove_reference<AbstractTemplate<incomplete_type>, AbstractTemplate<incomplete_type>>();
    test_remove_reference<Final, Final>();
    test_remove_reference<Enum, Enum>();
    test_remove_reference<EnumSigned, EnumSigned>();
    test_remove_reference<EnumUnsigned, EnumUnsigned>();
    test_remove_reference<EnumClass, EnumClass>();
    test_remove_reference<Function, Function>();
    test_remove_reference<FunctionPtr, FunctionPtr>();
    test_remove_reference<MemberObjectPtr, MemberObjectPtr>();
    test_remove_reference<MemberFunctionPtr, MemberFunctionPtr>();
    test_remove_reference<incomplete_type, incomplete_type>();
    test_remove_reference<int Class::*, int Class::*>();
    test_remove_reference<float Class::*, float Class::*>();
    test_remove_reference<int * Class::*, int * Class::*>();
    test_remove_reference<float * Class::*, float * Class::*>();

    test_remove_reference<void(), void()>();
    test_remove_reference<void() noexcept, void() noexcept>();
    test_remove_reference<void(int), void(int)>();
    test_remove_reference<void(int) noexcept, void(int) noexcept>();

    test_remove_reference<void(...), void(...)>();
    test_remove_reference<void(...) noexcept, void(...) noexcept>();
    test_remove_reference<void(int, ...), void(int, ...)>();
    test_remove_reference<void(int, ...) noexcept, void(int, ...) noexcept>();

    test_remove_reference<void (*)(), void (*)()>();
    test_remove_reference<void (*)() noexcept, void (*)() noexcept>();
    test_remove_reference<void (*)(int), void (*)(int)>();
    test_remove_reference<void (*)(int) noexcept, void (*)(int) noexcept>();

    test_remove_reference<void (*)(...), void (*)(...)>();
    test_remove_reference<void (*)(...) noexcept, void (*)(...) noexcept>();
    test_remove_reference<void (*)(int, ...), void (*)(int, ...)>();
    test_remove_reference<void (*)(int, ...) noexcept, void (*)(int, ...) noexcept>();

    test_remove_reference<void (Class::*)(), void (Class::*)()>();
    test_remove_reference<void (Class::*)()&, void (Class::*)()&>();
    test_remove_reference<void (Class::*)()&&, void (Class::*)() &&>();
    test_remove_reference<void (Class::*)() const, void (Class::*)() const>();
    test_remove_reference<void (Class::*)() const&, void (Class::*)() const&>();
    test_remove_reference<void (Class::*)() const&&, void (Class::*)() const&&>();

    test_remove_reference<void (Class::*)() noexcept, void (Class::*)() noexcept>();
    test_remove_reference<void (Class::*)()& noexcept, void (Class::*)()& noexcept>();
    test_remove_reference<void (Class::*)()&& noexcept, void (Class::*)()&& noexcept>();
    test_remove_reference<void (Class::*)() const noexcept, void (Class::*)() const noexcept>();
    test_remove_reference<void (Class::*)() const& noexcept, void (Class::*)() const& noexcept>();
    test_remove_reference<void (Class::*)() const&& noexcept, void (Class::*)() const&& noexcept>();

    test_remove_reference<void (Class::*)(int), void (Class::*)(int)>();
    test_remove_reference<void (Class::*)(int)&, void (Class::*)(int)&>();
    test_remove_reference<void (Class::*)(int)&&, void (Class::*)(int) &&>();
    test_remove_reference<void (Class::*)(int) const, void (Class::*)(int) const>();
    test_remove_reference<void (Class::*)(int) const&, void (Class::*)(int) const&>();
    test_remove_reference<void (Class::*)(int) const&&, void (Class::*)(int) const&&>();

    test_remove_reference<void (Class::*)(int) noexcept, void (Class::*)(int) noexcept>();
    test_remove_reference<void (Class::*)(int)& noexcept, void (Class::*)(int)& noexcept>();
    test_remove_reference<void (Class::*)(int)&& noexcept, void (Class::*)(int)&& noexcept>();
    test_remove_reference<void (Class::*)(int) const noexcept,
                          void (Class::*)(int) const noexcept>();
    test_remove_reference<void (Class::*)(int) const& noexcept,
                          void (Class::*)(int) const& noexcept>();
    test_remove_reference<void (Class::*)(int) const&& noexcept,
                          void (Class::*)(int) const&& noexcept>();

    test_remove_reference<void (Class::*)(...), void (Class::*)(...)>();
    test_remove_reference<void (Class::*)(...)&, void (Class::*)(...)&>();
    test_remove_reference<void (Class::*)(...)&&, void (Class::*)(...) &&>();
    test_remove_reference<void (Class::*)(...) const, void (Class::*)(...) const>();
    test_remove_reference<void (Class::*)(...) const&, void (Class::*)(...) const&>();
    test_remove_reference<void (Class::*)(...) const&&, void (Class::*)(...) const&&>();

    test_remove_reference<void (Class::*)(...) noexcept, void (Class::*)(...) noexcept>();
    test_remove_reference<void (Class::*)(...)& noexcept, void (Class::*)(...)& noexcept>();
    test_remove_reference<void (Class::*)(...)&& noexcept, void (Class::*)(...)&& noexcept>();
    test_remove_reference<void (Class::*)(...) const noexcept,
                          void (Class::*)(...) const noexcept>();
    test_remove_reference<void (Class::*)(...) const& noexcept,
                          void (Class::*)(...) const& noexcept>();
    test_remove_reference<void (Class::*)(...) const&& noexcept,
                          void (Class::*)(...) const&& noexcept>();

    test_remove_reference<void (Class::*)(int, ...), void (Class::*)(int, ...)>();
    test_remove_reference<void (Class::*)(int, ...)&, void (Class::*)(int, ...)&>();
    test_remove_reference<void (Class::*)(int, ...)&&, void (Class::*)(int, ...) &&>();
    test_remove_reference<void (Class::*)(int, ...) const, void (Class::*)(int, ...) const>();
    test_remove_reference<void (Class::*)(int, ...) const&, void (Class::*)(int, ...) const&>();
    test_remove_reference<void (Class::*)(int, ...) const&&, void (Class::*)(int, ...) const&&>();

    test_remove_reference<void (Class::*)(int, ...) noexcept, void (Class::*)(int, ...) noexcept>();
    test_remove_reference<void (Class::*)(int, ...)& noexcept,
                          void (Class::*)(int, ...)& noexcept>();
    test_remove_reference<void (Class::*)(int, ...)&& noexcept,
                          void (Class::*)(int, ...)&& noexcept>();
    test_remove_reference<void (Class::*)(int, ...) const noexcept,
                          void (Class::*)(int, ...) const noexcept>();
    test_remove_reference<void (Class::*)(int, ...) const& noexcept,
                          void (Class::*)(int, ...) const& noexcept>();
    test_remove_reference<void (Class::*)(int, ...) const&& noexcept,
                          void (Class::*)(int, ...) const&& noexcept>();
}
