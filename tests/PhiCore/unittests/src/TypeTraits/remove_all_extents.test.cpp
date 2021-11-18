#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/remove_all_extents.hpp>
#include <vector>

template <typename T, typename U>
void test_remove_all_extents()
{
    CHECK_SAME_TYPE(typename phi::remove_all_extents<T>::type, U);
    CHECK_SAME_TYPE(typename phi::remove_all_extents<const T>::type, const U);
    CHECK_SAME_TYPE(typename phi::remove_all_extents<volatile T>::type, volatile U);
    CHECK_SAME_TYPE(typename phi::remove_all_extents<const volatile T>::type, const volatile U);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    CHECK_SAME_TYPE(phi::remove_all_extents_t<T>, U);
    CHECK_SAME_TYPE(phi::remove_all_extents_t<const T>, const U);
    CHECK_SAME_TYPE(phi::remove_all_extents_t<volatile T>, volatile U);
    CHECK_SAME_TYPE(phi::remove_all_extents_t<const volatile T>, const volatile U);
#endif
}

TEST_CASE("remove_all_extents")
{
    test_remove_all_extents<int[], int>();
    test_remove_all_extents<int[2], int>();
    test_remove_all_extents<int[][3], int>();
    test_remove_all_extents<int[2][3], int>();
    test_remove_all_extents<int[][3][4], int>();
    test_remove_all_extents<int[2][3][4], int>();
    test_remove_all_extents<float[], float>();
    test_remove_all_extents<float[2], float>();
    test_remove_all_extents<float[][3], float>();
    test_remove_all_extents<float[2][3], float>();
    test_remove_all_extents<float[][3][4], float>();
    test_remove_all_extents<float[2][3][4], float>();
    test_remove_all_extents<Class[], Class>();
    test_remove_all_extents<Class[2], Class>();
    test_remove_all_extents<Class[][3], Class>();
    test_remove_all_extents<Class[2][3], Class>();
    test_remove_all_extents<Class[][3][4], Class>();
    test_remove_all_extents<Class[2][3][4], Class>();

    test_remove_all_extents<void, void>();
    test_remove_all_extents<phi::nullptr_t, phi::nullptr_t>();
    test_remove_all_extents<bool, bool>();
    test_remove_all_extents<char, char>();
    test_remove_all_extents<signed char, signed char>();
    test_remove_all_extents<unsigned char, unsigned char>();
    test_remove_all_extents<short, short>();
    test_remove_all_extents<unsigned short, unsigned short>();
    test_remove_all_extents<int, int>();
    test_remove_all_extents<unsigned int, unsigned int>();
    test_remove_all_extents<long, long>();
    test_remove_all_extents<unsigned long, unsigned long>();
    test_remove_all_extents<long long, long long>();
    test_remove_all_extents<unsigned long long, unsigned long long>();
    test_remove_all_extents<float, float>();
    test_remove_all_extents<double, double>();
    test_remove_all_extents<long double, long double>();
    test_remove_all_extents<char8_t, char8_t>();
    test_remove_all_extents<char16_t, char16_t>();
    test_remove_all_extents<char32_t, char32_t>();
    test_remove_all_extents<wchar_t, wchar_t>();

    test_remove_all_extents<phi::Boolean, phi::Boolean>();
    test_remove_all_extents<phi::Integer<signed char>, phi::Integer<signed char>>();
    test_remove_all_extents<phi::Integer<unsigned char>, phi::Integer<unsigned char>>();
    test_remove_all_extents<phi::Integer<short>, phi::Integer<short>>();
    test_remove_all_extents<phi::Integer<unsigned short>, phi::Integer<unsigned short>>();
    test_remove_all_extents<phi::Integer<int>, phi::Integer<int>>();
    test_remove_all_extents<phi::Integer<unsigned int>, phi::Integer<unsigned int>>();
    test_remove_all_extents<phi::Integer<long>, phi::Integer<long>>();
    test_remove_all_extents<phi::Integer<unsigned long>, phi::Integer<unsigned long>>();
    test_remove_all_extents<phi::Integer<long long>, phi::Integer<long long>>();
    test_remove_all_extents<phi::Integer<unsigned long long>, phi::Integer<unsigned long long>>();
    test_remove_all_extents<phi::FloatingPoint<float>, phi::FloatingPoint<float>>();
    test_remove_all_extents<phi::FloatingPoint<double>, phi::FloatingPoint<double>>();
    test_remove_all_extents<phi::FloatingPoint<long double>, phi::FloatingPoint<long double>>();

    test_remove_all_extents<std::vector<int>, std::vector<int>>();
    test_remove_all_extents<phi::ScopePtr<int>, phi::ScopePtr<int>>();

    test_remove_all_extents<int&, int&>();
    test_remove_all_extents<const int&, const int&>();
    test_remove_all_extents<volatile int&, volatile int&>();
    test_remove_all_extents<const volatile int&, const volatile int&>();
    test_remove_all_extents<int&&, int&&>();
    test_remove_all_extents<const int&&, const int&&>();
    test_remove_all_extents<volatile int&&, volatile int&&>();
    test_remove_all_extents<const volatile int&&, const volatile int&&>();
    test_remove_all_extents<int*, int*>();
    test_remove_all_extents<const int*, const int*>();
    test_remove_all_extents<volatile int*, volatile int*>();
    test_remove_all_extents<const volatile int*, const volatile int*>();
    test_remove_all_extents<int**, int**>();
    test_remove_all_extents<const int**, const int**>();
    test_remove_all_extents<volatile int**, volatile int**>();
    test_remove_all_extents<const volatile int**, const volatile int**>();
    test_remove_all_extents<void*, void*>();
    test_remove_all_extents<char[3], char>();
    test_remove_all_extents<char[], char>();
    test_remove_all_extents<char* [3], char*>();
    test_remove_all_extents<char*[], char*>();
    test_remove_all_extents<Class, Class>();
    test_remove_all_extents<Union, Union>();
    test_remove_all_extents<NonEmptyUnion, NonEmptyUnion>();
    test_remove_all_extents<Empty, Empty>();
    test_remove_all_extents<NotEmpty, NotEmpty>();
    test_remove_all_extents<bit_zero, bit_zero>();
    test_remove_all_extents<bit_one, bit_one>();
    test_remove_all_extents<Abstract, Abstract>();
    test_remove_all_extents<AbstractTemplate<int>, AbstractTemplate<int>>();
    test_remove_all_extents<AbstractTemplate<double>, AbstractTemplate<double>>();
    test_remove_all_extents<AbstractTemplate<Class>, AbstractTemplate<Class>>();
    test_remove_all_extents<AbstractTemplate<incomplete_type>, AbstractTemplate<incomplete_type>>();
    test_remove_all_extents<Final, Final>();
    test_remove_all_extents<Enum, Enum>();
    test_remove_all_extents<EnumSigned, EnumSigned>();
    test_remove_all_extents<EnumUnsigned, EnumUnsigned>();
    test_remove_all_extents<EnumClass, EnumClass>();
    test_remove_all_extents<Function, Function>();
    test_remove_all_extents<FunctionPtr, FunctionPtr>();
    test_remove_all_extents<MemberObjectPtr, MemberObjectPtr>();
    test_remove_all_extents<MemberFunctionPtr, MemberFunctionPtr>();
    test_remove_all_extents<incomplete_type, incomplete_type>();
    test_remove_all_extents<int Class::*, int Class::*>();
    test_remove_all_extents<float Class::*, float Class::*>();

    test_remove_all_extents<void(), void()>();
    test_remove_all_extents<void() noexcept, void() noexcept>();
    test_remove_all_extents<void(int), void(int)>();
    test_remove_all_extents<void(int) noexcept, void(int) noexcept>();

    test_remove_all_extents<void(...), void(...)>();
    test_remove_all_extents<void(...) noexcept, void(...) noexcept>();
    test_remove_all_extents<void(int, ...), void(int, ...)>();
    test_remove_all_extents<void(int, ...) noexcept, void(int, ...) noexcept>();

    test_remove_all_extents<void (*)(), void (*)()>();
    test_remove_all_extents<void (*)() noexcept, void (*)() noexcept>();
    test_remove_all_extents<void (*)(int), void (*)(int)>();
    test_remove_all_extents<void (*)(int) noexcept, void (*)(int) noexcept>();

    test_remove_all_extents<void (*)(...), void (*)(...)>();
    test_remove_all_extents<void (*)(...) noexcept, void (*)(...) noexcept>();
    test_remove_all_extents<void (*)(int, ...), void (*)(int, ...)>();
    test_remove_all_extents<void (*)(int, ...) noexcept, void (*)(int, ...) noexcept>();

    test_remove_all_extents<void (Class::*)(), void (Class::*)()>();
    test_remove_all_extents<void (Class::*)()&, void (Class::*)()&>();
    test_remove_all_extents<void (Class::*)()&&, void (Class::*)() &&>();
    test_remove_all_extents<void (Class::*)() const, void (Class::*)() const>();
    test_remove_all_extents<void (Class::*)() const&, void (Class::*)() const&>();
    test_remove_all_extents<void (Class::*)() const&&, void (Class::*)() const&&>();

    test_remove_all_extents<void (Class::*)() noexcept, void (Class::*)() noexcept>();
    test_remove_all_extents<void (Class::*)()& noexcept, void (Class::*)()& noexcept>();
    test_remove_all_extents<void (Class::*)()&& noexcept, void (Class::*)()&& noexcept>();
    test_remove_all_extents<void (Class::*)() const noexcept, void (Class::*)() const noexcept>();
    test_remove_all_extents<void (Class::*)() const& noexcept, void (Class::*)() const& noexcept>();
    test_remove_all_extents<void (Class::*)() const&& noexcept,
                            void (Class::*)() const&& noexcept>();

    test_remove_all_extents<void (Class::*)(int), void (Class::*)(int)>();
    test_remove_all_extents<void (Class::*)(int)&, void (Class::*)(int)&>();
    test_remove_all_extents<void (Class::*)(int)&&, void (Class::*)(int) &&>();
    test_remove_all_extents<void (Class::*)(int) const, void (Class::*)(int) const>();
    test_remove_all_extents<void (Class::*)(int) const&, void (Class::*)(int) const&>();
    test_remove_all_extents<void (Class::*)(int) const&&, void (Class::*)(int) const&&>();

    test_remove_all_extents<void (Class::*)(int) noexcept, void (Class::*)(int) noexcept>();
    test_remove_all_extents<void (Class::*)(int)& noexcept, void (Class::*)(int)& noexcept>();
    test_remove_all_extents<void (Class::*)(int)&& noexcept, void (Class::*)(int)&& noexcept>();
    test_remove_all_extents<void (Class::*)(int) const noexcept,
                            void (Class::*)(int) const noexcept>();
    test_remove_all_extents<void (Class::*)(int) const& noexcept,
                            void (Class::*)(int) const& noexcept>();
    test_remove_all_extents<void (Class::*)(int) const&& noexcept,
                            void (Class::*)(int) const&& noexcept>();

    test_remove_all_extents<void (Class::*)(...), void (Class::*)(...)>();
    test_remove_all_extents<void (Class::*)(...)&, void (Class::*)(...)&>();
    test_remove_all_extents<void (Class::*)(...)&&, void (Class::*)(...) &&>();
    test_remove_all_extents<void (Class::*)(...) const, void (Class::*)(...) const>();
    test_remove_all_extents<void (Class::*)(...) const&, void (Class::*)(...) const&>();
    test_remove_all_extents<void (Class::*)(...) const&&, void (Class::*)(...) const&&>();

    test_remove_all_extents<void (Class::*)(...) noexcept, void (Class::*)(...) noexcept>();
    test_remove_all_extents<void (Class::*)(...)& noexcept, void (Class::*)(...)& noexcept>();
    test_remove_all_extents<void (Class::*)(...)&& noexcept, void (Class::*)(...)&& noexcept>();
    test_remove_all_extents<void (Class::*)(...) const noexcept,
                            void (Class::*)(...) const noexcept>();
    test_remove_all_extents<void (Class::*)(...) const& noexcept,
                            void (Class::*)(...) const& noexcept>();
    test_remove_all_extents<void (Class::*)(...) const&& noexcept,
                            void (Class::*)(...) const&& noexcept>();
}
