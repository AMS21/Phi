#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/remove_pointer.hpp>
#include <vector>

template <typename T, typename U>
void test_remove_pointer()
{
    CHECK_SAME_TYPE(typename phi::remove_pointer<T>::type, U);
    CHECK_SAME_TYPE(typename phi::remove_pointer<const T>::type, const U);
    CHECK_SAME_TYPE(typename phi::remove_pointer<volatile T>::type, volatile U);
    CHECK_SAME_TYPE(typename phi::remove_pointer<const volatile T>::type, const volatile U);

    CHECK_SAME_TYPE(phi::remove_pointer_t<T>, U);
    CHECK_SAME_TYPE(phi::remove_pointer_t<const T>, const U);
    CHECK_SAME_TYPE(phi::remove_pointer_t<volatile T>, volatile U);
    CHECK_SAME_TYPE(phi::remove_pointer_t<const volatile T>, const volatile U);
}

template <typename T, typename U>
void test_remove_pointer_ptr()
{
    CHECK_SAME_TYPE(typename phi::remove_pointer<T>::type, U);
    CHECK_SAME_TYPE(phi::remove_pointer_t<T>, U);
}

TEST_CASE("remove_pointer")
{
    test_remove_pointer_ptr<int* const, int>();
    test_remove_pointer_ptr<int* volatile, int>();
    test_remove_pointer_ptr<int* const volatile, int>();
    test_remove_pointer_ptr<int** const, int*>();
    test_remove_pointer_ptr<int** volatile, int*>();
    test_remove_pointer_ptr<int** const volatile, int*>();
    test_remove_pointer_ptr<int* const*, int* const>();
    test_remove_pointer_ptr<int* volatile*, int* volatile>();
    test_remove_pointer_ptr<int* const volatile*, int* const volatile>();

    test_remove_pointer<void, void>();
    test_remove_pointer<phi::nullptr_t, phi::nullptr_t>();
    test_remove_pointer<bool, bool>();
    test_remove_pointer<char, char>();
    test_remove_pointer<signed char, signed char>();
    test_remove_pointer<unsigned char, unsigned char>();
    test_remove_pointer<short, short>();
    test_remove_pointer<unsigned short, unsigned short>();
    test_remove_pointer<int, int>();
    test_remove_pointer<unsigned int, unsigned int>();
    test_remove_pointer<long, long>();
    test_remove_pointer<unsigned long, unsigned long>();
    test_remove_pointer<long long, long long>();
    test_remove_pointer<unsigned long long, unsigned long long>();
    test_remove_pointer<float, float>();
    test_remove_pointer<double, double>();
    test_remove_pointer<long double, long double>();
    test_remove_pointer<char8_t, char8_t>();
    test_remove_pointer<char16_t, char16_t>();
    test_remove_pointer<char32_t, char32_t>();
    test_remove_pointer<wchar_t, wchar_t>();

    test_remove_pointer<phi::Boolean, phi::Boolean>();
    test_remove_pointer<phi::Integer<signed char>, phi::Integer<signed char>>();
    test_remove_pointer<phi::Integer<unsigned char>, phi::Integer<unsigned char>>();
    test_remove_pointer<phi::Integer<short>, phi::Integer<short>>();
    test_remove_pointer<phi::Integer<unsigned short>, phi::Integer<unsigned short>>();
    test_remove_pointer<phi::Integer<int>, phi::Integer<int>>();
    test_remove_pointer<phi::Integer<unsigned int>, phi::Integer<unsigned int>>();
    test_remove_pointer<phi::Integer<long>, phi::Integer<long>>();
    test_remove_pointer<phi::Integer<unsigned long>, phi::Integer<unsigned long>>();
    test_remove_pointer<phi::Integer<long long>, phi::Integer<long long>>();
    test_remove_pointer<phi::Integer<unsigned long long>, phi::Integer<unsigned long long>>();
    test_remove_pointer<phi::FloatingPoint<float>, phi::FloatingPoint<float>>();
    test_remove_pointer<phi::FloatingPoint<double>, phi::FloatingPoint<double>>();
    test_remove_pointer<phi::FloatingPoint<long double>, phi::FloatingPoint<long double>>();

    test_remove_pointer<std::vector<int>, std::vector<int>>();
    test_remove_pointer<phi::ScopePtr<int>, phi::ScopePtr<int>>();

    test_remove_pointer<int&, int&>();
    test_remove_pointer<const int&, const int&>();
    test_remove_pointer<volatile int&, volatile int&>();
    test_remove_pointer<const volatile int&, const volatile int&>();
    test_remove_pointer<int&&, int&&>();
    test_remove_pointer<const int&&, const int&&>();
    test_remove_pointer<volatile int&&, volatile int&&>();
    test_remove_pointer<const volatile int&&, const volatile int&&>();
    test_remove_pointer_ptr<int*, int>();
    test_remove_pointer_ptr<const int*, const int>();
    test_remove_pointer_ptr<volatile int*, volatile int>();
    test_remove_pointer_ptr<const volatile int*, const volatile int>();
    test_remove_pointer_ptr<int**, int*>();
    test_remove_pointer_ptr<const int**, const int*>();
    test_remove_pointer_ptr<volatile int**, volatile int*>();
    test_remove_pointer_ptr<const volatile int**, const volatile int*>();
    test_remove_pointer<int*&, int*&>();
    test_remove_pointer<const int*&, const int*&>();
    test_remove_pointer<volatile int*&, volatile int*&>();
    test_remove_pointer<const volatile int*&, const volatile int*&>();
    test_remove_pointer_ptr<void*, void>();
    test_remove_pointer<char[3], char[3]>();
    test_remove_pointer<char[], char[]>();
    test_remove_pointer<char* [3], char* [3]>();
    test_remove_pointer<char*[], char*[]>();
    test_remove_pointer_ptr<int(*)[3], int[3]>();
    test_remove_pointer_ptr<int(*)[], int[]>();
    test_remove_pointer<int(&)[3], int(&)[3]>();
    test_remove_pointer<int(&)[], int(&)[]>();
    test_remove_pointer<Class, Class>();
    test_remove_pointer<Union, Union>();
    test_remove_pointer<NonEmptyUnion, NonEmptyUnion>();
    test_remove_pointer<Empty, Empty>();
    test_remove_pointer<NotEmpty, NotEmpty>();
    test_remove_pointer<bit_zero, bit_zero>();
    test_remove_pointer<bit_one, bit_one>();
    test_remove_pointer<Abstract, Abstract>();
    test_remove_pointer<AbstractTemplate<int>, AbstractTemplate<int>>();
    test_remove_pointer<AbstractTemplate<double>, AbstractTemplate<double>>();
    test_remove_pointer<AbstractTemplate<Class>, AbstractTemplate<Class>>();
    test_remove_pointer<AbstractTemplate<incomplete_type>, AbstractTemplate<incomplete_type>>();
    test_remove_pointer<Final, Final>();
    test_remove_pointer<Enum, Enum>();
    test_remove_pointer<EnumSigned, EnumSigned>();
    test_remove_pointer<EnumUnsigned, EnumUnsigned>();
    test_remove_pointer<EnumClass, EnumClass>();
    test_remove_pointer<Function, Function>();
    test_remove_pointer_ptr<FunctionPtr, Function>();
    test_remove_pointer<MemberObjectPtr, MemberObjectPtr>();
    test_remove_pointer<MemberFunctionPtr, MemberFunctionPtr>();
    test_remove_pointer<incomplete_type, incomplete_type>();
    test_remove_pointer<int Class::*, int Class::*>();
    test_remove_pointer<float Class::*, float Class::*>();
    test_remove_pointer<int * Class::*, int * Class::*>();
    test_remove_pointer<float * Class::*, float * Class::*>();

    test_remove_pointer<void(), void()>();
    test_remove_pointer<void() noexcept, void() noexcept>();
    test_remove_pointer<void(int), void(int)>();
    test_remove_pointer<void(int) noexcept, void(int) noexcept>();

    test_remove_pointer<void(...), void(...)>();
    test_remove_pointer<void(...) noexcept, void(...) noexcept>();
    test_remove_pointer<void(int, ...), void(int, ...)>();
    test_remove_pointer<void(int, ...) noexcept, void(int, ...) noexcept>();

    test_remove_pointer<void (*)(), void()>();
    test_remove_pointer<void (*)() noexcept, void() noexcept>();
    test_remove_pointer<void (*)(int), void(int)>();
    test_remove_pointer<void (*)(int) noexcept, void(int) noexcept>();

    test_remove_pointer<void (*)(...), void(...)>();
    test_remove_pointer<void (*)(...) noexcept, void(...) noexcept>();
    test_remove_pointer<void (*)(int, ...), void(int, ...)>();
    test_remove_pointer<void (*)(int, ...) noexcept, void(int, ...) noexcept>();

    test_remove_pointer<void (Class::*)(), void (Class::*)()>();
    test_remove_pointer<void (Class::*)()&, void (Class::*)()&>();
    test_remove_pointer<void (Class::*)()&&, void (Class::*)() &&>();
    test_remove_pointer<void (Class::*)() const, void (Class::*)() const>();
    test_remove_pointer<void (Class::*)() const&, void (Class::*)() const&>();
    test_remove_pointer<void (Class::*)() const&&, void (Class::*)() const&&>();

    test_remove_pointer<void (Class::*)() noexcept, void (Class::*)() noexcept>();
    test_remove_pointer<void (Class::*)()& noexcept, void (Class::*)()& noexcept>();
    test_remove_pointer<void (Class::*)()&& noexcept, void (Class::*)()&& noexcept>();
    test_remove_pointer<void (Class::*)() const noexcept, void (Class::*)() const noexcept>();
    test_remove_pointer<void (Class::*)() const& noexcept, void (Class::*)() const& noexcept>();
    test_remove_pointer<void (Class::*)() const&& noexcept, void (Class::*)() const&& noexcept>();

    test_remove_pointer<void (Class::*)(int), void (Class::*)(int)>();
    test_remove_pointer<void (Class::*)(int)&, void (Class::*)(int)&>();
    test_remove_pointer<void (Class::*)(int)&&, void (Class::*)(int) &&>();
    test_remove_pointer<void (Class::*)(int) const, void (Class::*)(int) const>();
    test_remove_pointer<void (Class::*)(int) const&, void (Class::*)(int) const&>();
    test_remove_pointer<void (Class::*)(int) const&&, void (Class::*)(int) const&&>();

    test_remove_pointer<void (Class::*)(int) noexcept, void (Class::*)(int) noexcept>();
    test_remove_pointer<void (Class::*)(int)& noexcept, void (Class::*)(int)& noexcept>();
    test_remove_pointer<void (Class::*)(int)&& noexcept, void (Class::*)(int)&& noexcept>();
    test_remove_pointer<void (Class::*)(int) const noexcept, void (Class::*)(int) const noexcept>();
    test_remove_pointer<void (Class::*)(int) const& noexcept,
                        void (Class::*)(int) const& noexcept>();
    test_remove_pointer<void (Class::*)(int) const&& noexcept,
                        void (Class::*)(int) const&& noexcept>();

    test_remove_pointer<void (Class::*)(...), void (Class::*)(...)>();
    test_remove_pointer<void (Class::*)(...)&, void (Class::*)(...)&>();
    test_remove_pointer<void (Class::*)(...)&&, void (Class::*)(...) &&>();
    test_remove_pointer<void (Class::*)(...) const, void (Class::*)(...) const>();
    test_remove_pointer<void (Class::*)(...) const&, void (Class::*)(...) const&>();
    test_remove_pointer<void (Class::*)(...) const&&, void (Class::*)(...) const&&>();

    test_remove_pointer<void (Class::*)(...) noexcept, void (Class::*)(...) noexcept>();
    test_remove_pointer<void (Class::*)(...)& noexcept, void (Class::*)(...)& noexcept>();
    test_remove_pointer<void (Class::*)(...)&& noexcept, void (Class::*)(...)&& noexcept>();
    test_remove_pointer<void (Class::*)(...) const noexcept, void (Class::*)(...) const noexcept>();
    test_remove_pointer<void (Class::*)(...) const& noexcept,
                        void (Class::*)(...) const& noexcept>();
    test_remove_pointer<void (Class::*)(...) const&& noexcept,
                        void (Class::*)(...) const&& noexcept>();

    test_remove_pointer<void (Class::*)(int, ...), void (Class::*)(int, ...)>();
    test_remove_pointer<void (Class::*)(int, ...)&, void (Class::*)(int, ...)&>();
    test_remove_pointer<void (Class::*)(int, ...)&&, void (Class::*)(int, ...) &&>();
    test_remove_pointer<void (Class::*)(int, ...) const, void (Class::*)(int, ...) const>();
    test_remove_pointer<void (Class::*)(int, ...) const&, void (Class::*)(int, ...) const&>();
    test_remove_pointer<void (Class::*)(int, ...) const&&, void (Class::*)(int, ...) const&&>();

    test_remove_pointer<void (Class::*)(int, ...) noexcept, void (Class::*)(int, ...) noexcept>();
    test_remove_pointer<void (Class::*)(int, ...)& noexcept, void (Class::*)(int, ...)& noexcept>();
    test_remove_pointer<void (Class::*)(int, ...)&& noexcept,
                        void (Class::*)(int, ...)&& noexcept>();
    test_remove_pointer<void (Class::*)(int, ...) const noexcept,
                        void (Class::*)(int, ...) const noexcept>();
    test_remove_pointer<void (Class::*)(int, ...) const& noexcept,
                        void (Class::*)(int, ...) const& noexcept>();
    test_remove_pointer<void (Class::*)(int, ...) const&& noexcept,
                        void (Class::*)(int, ...) const&& noexcept>();
}
