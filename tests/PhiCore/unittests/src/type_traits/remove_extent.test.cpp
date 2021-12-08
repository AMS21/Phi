#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/remove_extent.hpp>
#include <vector>

template <typename T, typename U>
void test_remove_extent()
{
    CHECK_SAME_TYPE(typename phi::remove_extent<T>::type, U);
    CHECK_SAME_TYPE(typename phi::remove_extent<const T>::type, const U);
    CHECK_SAME_TYPE(typename phi::remove_extent<volatile T>::type, volatile U);
    CHECK_SAME_TYPE(typename phi::remove_extent<const volatile T>::type, const volatile U);

    CHECK_SAME_TYPE(phi::remove_extent_t<T>, U);
    CHECK_SAME_TYPE(phi::remove_extent_t<const T>, const U);
    CHECK_SAME_TYPE(phi::remove_extent_t<volatile T>, volatile U);
    CHECK_SAME_TYPE(phi::remove_extent_t<const volatile T>, const volatile U);
}

TEST_CASE("remove_extent")
{
    test_remove_extent<int[], int>();
    test_remove_extent<int[2], int>();
    test_remove_extent<int[][3], int[3]>();
    test_remove_extent<int[2][3], int[3]>();
    test_remove_extent<int[][3][4], int[3][4]>();
    test_remove_extent<int[2][3][4], int[3][4]>();
    test_remove_extent<float[], float>();
    test_remove_extent<float[2], float>();
    test_remove_extent<float[][3], float[3]>();
    test_remove_extent<float[2][3], float[3]>();
    test_remove_extent<float[][3][4], float[3][4]>();
    test_remove_extent<float[2][3][4], float[3][4]>();
    test_remove_extent<Class[], Class>();
    test_remove_extent<Class[2], Class>();
    test_remove_extent<Class[][3], Class[3]>();
    test_remove_extent<Class[2][3], Class[3]>();
    test_remove_extent<Class[][3][4], Class[3][4]>();
    test_remove_extent<Class[2][3][4], Class[3][4]>();

    test_remove_extent<void, void>();
    test_remove_extent<phi::nullptr_t, phi::nullptr_t>();
    test_remove_extent<bool, bool>();
    test_remove_extent<char, char>();
    test_remove_extent<signed char, signed char>();
    test_remove_extent<unsigned char, unsigned char>();
    test_remove_extent<short, short>();
    test_remove_extent<unsigned short, unsigned short>();
    test_remove_extent<int, int>();
    test_remove_extent<unsigned int, unsigned int>();
    test_remove_extent<long, long>();
    test_remove_extent<unsigned long, unsigned long>();
    test_remove_extent<long long, long long>();
    test_remove_extent<unsigned long long, unsigned long long>();
    test_remove_extent<float, float>();
    test_remove_extent<double, double>();
    test_remove_extent<long double, long double>();
    test_remove_extent<char8_t, char8_t>();
    test_remove_extent<char16_t, char16_t>();
    test_remove_extent<char32_t, char32_t>();
    test_remove_extent<wchar_t, wchar_t>();

    test_remove_extent<phi::boolean, phi::boolean>();
    test_remove_extent<phi::integer<signed char>, phi::integer<signed char>>();
    test_remove_extent<phi::integer<unsigned char>, phi::integer<unsigned char>>();
    test_remove_extent<phi::integer<short>, phi::integer<short>>();
    test_remove_extent<phi::integer<unsigned short>, phi::integer<unsigned short>>();
    test_remove_extent<phi::integer<int>, phi::integer<int>>();
    test_remove_extent<phi::integer<unsigned int>, phi::integer<unsigned int>>();
    test_remove_extent<phi::integer<long>, phi::integer<long>>();
    test_remove_extent<phi::integer<unsigned long>, phi::integer<unsigned long>>();
    test_remove_extent<phi::integer<long long>, phi::integer<long long>>();
    test_remove_extent<phi::integer<unsigned long long>, phi::integer<unsigned long long>>();
    test_remove_extent<phi::floating_point<float>, phi::floating_point<float>>();
    test_remove_extent<phi::floating_point<double>, phi::floating_point<double>>();
    test_remove_extent<phi::floating_point<long double>, phi::floating_point<long double>>();

    test_remove_extent<std::vector<int>, std::vector<int>>();
    test_remove_extent<phi::scope_ptr<int>, phi::scope_ptr<int>>();

    test_remove_extent<int&, int&>();
    test_remove_extent<const int&, const int&>();
    test_remove_extent<volatile int&, volatile int&>();
    test_remove_extent<const volatile int&, const volatile int&>();
    test_remove_extent<int&&, int&&>();
    test_remove_extent<const int&&, const int&&>();
    test_remove_extent<volatile int&&, volatile int&&>();
    test_remove_extent<const volatile int&&, const volatile int&&>();
    test_remove_extent<int*, int*>();
    test_remove_extent<const int*, const int*>();
    test_remove_extent<volatile int*, volatile int*>();
    test_remove_extent<const volatile int*, const volatile int*>();
    test_remove_extent<int**, int**>();
    test_remove_extent<const int**, const int**>();
    test_remove_extent<volatile int**, volatile int**>();
    test_remove_extent<const volatile int**, const volatile int**>();
    test_remove_extent<void*, void*>();
    test_remove_extent<char[3], char>();
    test_remove_extent<char[], char>();
    test_remove_extent<char* [3], char*>();
    test_remove_extent<char*[], char*>();
    test_remove_extent<Class, Class>();
    test_remove_extent<Union, Union>();
    test_remove_extent<NonEmptyUnion, NonEmptyUnion>();
    test_remove_extent<Empty, Empty>();
    test_remove_extent<NotEmpty, NotEmpty>();
    test_remove_extent<bit_zero, bit_zero>();
    test_remove_extent<bit_one, bit_one>();
    test_remove_extent<Abstract, Abstract>();
    test_remove_extent<AbstractTemplate<int>, AbstractTemplate<int>>();
    test_remove_extent<AbstractTemplate<double>, AbstractTemplate<double>>();
    test_remove_extent<AbstractTemplate<Class>, AbstractTemplate<Class>>();
    test_remove_extent<AbstractTemplate<incomplete_type>, AbstractTemplate<incomplete_type>>();
    test_remove_extent<Final, Final>();
    test_remove_extent<Enum, Enum>();
    test_remove_extent<EnumSigned, EnumSigned>();
    test_remove_extent<EnumUnsigned, EnumUnsigned>();
    test_remove_extent<EnumClass, EnumClass>();
    test_remove_extent<Function, Function>();
    test_remove_extent<FunctionPtr, FunctionPtr>();
    test_remove_extent<MemberObjectPtr, MemberObjectPtr>();
    test_remove_extent<MemberFunctionPtr, MemberFunctionPtr>();
    test_remove_extent<incomplete_type, incomplete_type>();
    test_remove_extent<int Class::*, int Class::*>();
    test_remove_extent<float Class::*, float Class::*>();

    test_remove_extent<void(), void()>();
    test_remove_extent<void() noexcept, void() noexcept>();
    test_remove_extent<void(int), void(int)>();
    test_remove_extent<void(int) noexcept, void(int) noexcept>();

    test_remove_extent<void(...), void(...)>();
    test_remove_extent<void(...) noexcept, void(...) noexcept>();
    test_remove_extent<void(int, ...), void(int, ...)>();
    test_remove_extent<void(int, ...) noexcept, void(int, ...) noexcept>();

    test_remove_extent<void (*)(), void (*)()>();
    test_remove_extent<void (*)() noexcept, void (*)() noexcept>();
    test_remove_extent<void (*)(int), void (*)(int)>();
    test_remove_extent<void (*)(int) noexcept, void (*)(int) noexcept>();

    test_remove_extent<void (*)(...), void (*)(...)>();
    test_remove_extent<void (*)(...) noexcept, void (*)(...) noexcept>();
    test_remove_extent<void (*)(int, ...), void (*)(int, ...)>();
    test_remove_extent<void (*)(int, ...) noexcept, void (*)(int, ...) noexcept>();

    test_remove_extent<void (Class::*)(), void (Class::*)()>();
    test_remove_extent<void (Class::*)()&, void (Class::*)()&>();
    test_remove_extent<void (Class::*)()&&, void (Class::*)() &&>();
    test_remove_extent<void (Class::*)() const, void (Class::*)() const>();
    test_remove_extent<void (Class::*)() const&, void (Class::*)() const&>();
    test_remove_extent<void (Class::*)() const&&, void (Class::*)() const&&>();

    test_remove_extent<void (Class::*)() noexcept, void (Class::*)() noexcept>();
    test_remove_extent<void (Class::*)()& noexcept, void (Class::*)()& noexcept>();
    test_remove_extent<void (Class::*)()&& noexcept, void (Class::*)()&& noexcept>();
    test_remove_extent<void (Class::*)() const noexcept, void (Class::*)() const noexcept>();
    test_remove_extent<void (Class::*)() const& noexcept, void (Class::*)() const& noexcept>();
    test_remove_extent<void (Class::*)() const&& noexcept, void (Class::*)() const&& noexcept>();

    test_remove_extent<void (Class::*)(int), void (Class::*)(int)>();
    test_remove_extent<void (Class::*)(int)&, void (Class::*)(int)&>();
    test_remove_extent<void (Class::*)(int)&&, void (Class::*)(int) &&>();
    test_remove_extent<void (Class::*)(int) const, void (Class::*)(int) const>();
    test_remove_extent<void (Class::*)(int) const&, void (Class::*)(int) const&>();
    test_remove_extent<void (Class::*)(int) const&&, void (Class::*)(int) const&&>();

    test_remove_extent<void (Class::*)(int) noexcept, void (Class::*)(int) noexcept>();
    test_remove_extent<void (Class::*)(int)& noexcept, void (Class::*)(int)& noexcept>();
    test_remove_extent<void (Class::*)(int)&& noexcept, void (Class::*)(int)&& noexcept>();
    test_remove_extent<void (Class::*)(int) const noexcept, void (Class::*)(int) const noexcept>();
    test_remove_extent<void (Class::*)(int) const& noexcept,
                       void (Class::*)(int) const& noexcept>();
    test_remove_extent<void (Class::*)(int) const&& noexcept,
                       void (Class::*)(int) const&& noexcept>();

    test_remove_extent<void (Class::*)(...), void (Class::*)(...)>();
    test_remove_extent<void (Class::*)(...)&, void (Class::*)(...)&>();
    test_remove_extent<void (Class::*)(...)&&, void (Class::*)(...) &&>();
    test_remove_extent<void (Class::*)(...) const, void (Class::*)(...) const>();
    test_remove_extent<void (Class::*)(...) const&, void (Class::*)(...) const&>();
    test_remove_extent<void (Class::*)(...) const&&, void (Class::*)(...) const&&>();

    test_remove_extent<void (Class::*)(...) noexcept, void (Class::*)(...) noexcept>();
    test_remove_extent<void (Class::*)(...)& noexcept, void (Class::*)(...)& noexcept>();
    test_remove_extent<void (Class::*)(...)&& noexcept, void (Class::*)(...)&& noexcept>();
    test_remove_extent<void (Class::*)(...) const noexcept, void (Class::*)(...) const noexcept>();
    test_remove_extent<void (Class::*)(...) const& noexcept,
                       void (Class::*)(...) const& noexcept>();
    test_remove_extent<void (Class::*)(...) const&& noexcept,
                       void (Class::*)(...) const&& noexcept>();
}
