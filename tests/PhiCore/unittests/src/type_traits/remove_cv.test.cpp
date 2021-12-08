#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/remove_cv.hpp>
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

    test_remove_cv<phi::boolean, phi::boolean>();
    test_remove_cv<phi::integer<signed char>, phi::integer<signed char>>();
    test_remove_cv<phi::integer<unsigned char>, phi::integer<unsigned char>>();
    test_remove_cv<phi::integer<short>, phi::integer<short>>();
    test_remove_cv<phi::integer<unsigned short>, phi::integer<unsigned short>>();
    test_remove_cv<phi::integer<int>, phi::integer<int>>();
    test_remove_cv<phi::integer<unsigned int>, phi::integer<unsigned int>>();
    test_remove_cv<phi::integer<long>, phi::integer<long>>();
    test_remove_cv<phi::integer<unsigned long>, phi::integer<unsigned long>>();
    test_remove_cv<phi::integer<long long>, phi::integer<long long>>();
    test_remove_cv<phi::integer<unsigned long long>, phi::integer<unsigned long long>>();
    test_remove_cv<phi::floating_point<float>, phi::floating_point<float>>();
    test_remove_cv<phi::floating_point<double>, phi::floating_point<double>>();
    test_remove_cv<phi::floating_point<long double>, phi::floating_point<long double>>();

    test_remove_cv<std::vector<int>, std::vector<int>>();
    test_remove_cv<phi::scope_ptr<int>, phi::scope_ptr<int>>();

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
