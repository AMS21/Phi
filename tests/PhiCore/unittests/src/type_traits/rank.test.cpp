#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/rank.hpp>
#include <vector>

template <typename T, unsigned A>
void test_rank()
{
    STATIC_REQUIRE(phi::rank<T>::value == A);
    STATIC_REQUIRE(phi::rank<const T>::value == A);
    STATIC_REQUIRE(phi::rank<volatile T>::value == A);
    STATIC_REQUIRE(phi::rank<const volatile T>::value == A);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::rank_v<T> == A);
    STATIC_REQUIRE(phi::rank_v<const T> == A);
    STATIC_REQUIRE(phi::rank_v<volatile T> == A);
    STATIC_REQUIRE(phi::rank_v<const volatile T> == A);
#endif
}

TEST_CASE("rank")
{
    test_rank<char[], 1>();
    test_rank<char[3], 1>();
    test_rank<char[1], 1>();
    test_rank<char[][3], 2>();
    test_rank<char[2][3], 2>();
    test_rank<char[][4][3], 3>();
    test_rank<char[2][4][3], 3>();
    test_rank<Class[], 1>();
    test_rank<Class[1], 1>();
    test_rank<Class[][1], 2>();
    test_rank<Class[2][1], 2>();
    test_rank<Class[][2][1], 3>();
    test_rank<Class[3][2][1], 3>();

    test_rank<void, 0>();
    test_rank<phi::nullptr_t, 0>();
    test_rank<bool, 0>();
    test_rank<char, 0>();
    test_rank<signed char, 0>();
    test_rank<unsigned char, 0>();
    test_rank<short, 0>();
    test_rank<unsigned short, 0>();
    test_rank<int, 0>();
    test_rank<unsigned int, 0>();
    test_rank<long, 0>();
    test_rank<unsigned long, 0>();
    test_rank<long long, 0>();
    test_rank<unsigned long long, 0>();
    test_rank<float, 0>();
    test_rank<double, 0>();
    test_rank<long double, 0>();
    test_rank<char8_t, 0>();
    test_rank<char16_t, 0>();
    test_rank<char32_t, 0>();
    test_rank<wchar_t, 0>();

    test_rank<phi::boolean, 0>();
    test_rank<phi::integer<signed char>, 0>();
    test_rank<phi::integer<unsigned char>, 0>();
    test_rank<phi::integer<short>, 0>();
    test_rank<phi::integer<unsigned short>, 0>();
    test_rank<phi::integer<int>, 0>();
    test_rank<phi::integer<unsigned int>, 0>();
    test_rank<phi::integer<long>, 0>();
    test_rank<phi::integer<unsigned long>, 0>();
    test_rank<phi::integer<long long>, 0>();
    test_rank<phi::integer<unsigned long long>, 0>();
    test_rank<phi::floating_point<float>, 0>();
    test_rank<phi::floating_point<double>, 0>();
    test_rank<phi::floating_point<long double>, 0>();

    test_rank<std::vector<int>, 0>();
    test_rank<phi::scope_ptr<int>, 0>();

    test_rank<int&, 0>();
    test_rank<const int&, 0>();
    test_rank<volatile int&, 0>();
    test_rank<const volatile int&, 0>();
    test_rank<int&&, 0>();
    test_rank<const int&&, 0>();
    test_rank<volatile int&&, 0>();
    test_rank<const volatile int&&, 0>();
    test_rank<int*, 0>();
    test_rank<const int*, 0>();
    test_rank<volatile int*, 0>();
    test_rank<const volatile int*, 0>();
    test_rank<int**, 0>();
    test_rank<const int**, 0>();
    test_rank<volatile int**, 0>();
    test_rank<const volatile int**, 0>();
    test_rank<void*, 0>();
    test_rank<char[3], 1>();
    test_rank<char[], 1>();
    test_rank<char* [3], 1>();
    test_rank<char*[], 1>();
    test_rank<Class, 0>();
    test_rank<Union, 0>();
    test_rank<NonEmptyUnion, 0>();
    test_rank<Empty, 0>();
    test_rank<NotEmpty, 0>();
    test_rank<bit_zero, 0>();
    test_rank<bit_one, 0>();
    test_rank<Abstract, 0>();
    test_rank<AbstractTemplate<int>, 0>();
    test_rank<AbstractTemplate<double>, 0>();
    test_rank<AbstractTemplate<Class>, 0>();
    test_rank<AbstractTemplate<incomplete_type>, 0>();
    test_rank<Final, 0>();
    test_rank<Enum, 0>();
    test_rank<EnumSigned, 0>();
    test_rank<EnumUnsigned, 0>();
    test_rank<EnumClass, 0>();
    test_rank<Function, 0>();
    test_rank<FunctionPtr, 0>();
    test_rank<MemberObjectPtr, 0>();
    test_rank<MemberFunctionPtr, 0>();
    test_rank<incomplete_type, 0>();
    test_rank<int Class::*, 0>();
    test_rank<float Class::*, 0>();

    test_rank<void(), 0>();
    test_rank<void() noexcept, 0>();
    test_rank<void(int), 0>();
    test_rank<void(int) noexcept, 0>();

    test_rank<void(...), 0>();
    test_rank<void(...) noexcept, 0>();
    test_rank<void(int, ...), 0>();
    test_rank<void(int, ...) noexcept, 0>();

    test_rank<void (*)(), 0>();
    test_rank<void (*)() noexcept, 0>();
    test_rank<void (*)(int), 0>();
    test_rank<void (*)(int) noexcept, 0>();

    test_rank<void (*)(...), 0>();
    test_rank<void (*)(...) noexcept, 0>();
    test_rank<void (*)(int, ...), 0>();
    test_rank<void (*)(int, ...) noexcept, 0>();

    test_rank<void (Class::*)(), 0>();
    test_rank<void (Class::*)()&, 0>();
    test_rank<void (Class::*)()&&, 0>();
    test_rank<void (Class::*)() const, 0>();
    test_rank<void (Class::*)() const&, 0>();
    test_rank<void (Class::*)() const&&, 0>();

    test_rank<void (Class::*)() noexcept, 0>();
    test_rank<void (Class::*)()& noexcept, 0>();
    test_rank<void (Class::*)()&& noexcept, 0>();
    test_rank<void (Class::*)() const noexcept, 0>();
    test_rank<void (Class::*)() const& noexcept, 0>();
    test_rank<void (Class::*)() const&& noexcept, 0>();

    test_rank<void (Class::*)(int), 0>();
    test_rank<void (Class::*)(int)&, 0>();
    test_rank<void (Class::*)(int)&&, 0>();
    test_rank<void (Class::*)(int) const, 0>();
    test_rank<void (Class::*)(int) const&, 0>();
    test_rank<void (Class::*)(int) const&&, 0>();

    test_rank<void (Class::*)(int) noexcept, 0>();
    test_rank<void (Class::*)(int)& noexcept, 0>();
    test_rank<void (Class::*)(int)&& noexcept, 0>();
    test_rank<void (Class::*)(int) const noexcept, 0>();
    test_rank<void (Class::*)(int) const& noexcept, 0>();
    test_rank<void (Class::*)(int) const&& noexcept, 0>();

    test_rank<void (Class::*)(...), 0>();
    test_rank<void (Class::*)(...)&, 0>();
    test_rank<void (Class::*)(...)&&, 0>();
    test_rank<void (Class::*)(...) const, 0>();
    test_rank<void (Class::*)(...) const&, 0>();
    test_rank<void (Class::*)(...) const&&, 0>();

    test_rank<void (Class::*)(...) noexcept, 0>();
    test_rank<void (Class::*)(...)& noexcept, 0>();
    test_rank<void (Class::*)(...)&& noexcept, 0>();
    test_rank<void (Class::*)(...) const noexcept, 0>();
    test_rank<void (Class::*)(...) const& noexcept, 0>();
    test_rank<void (Class::*)(...) const&& noexcept, 0>();
}
