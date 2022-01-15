#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_trivially_copy_constructible.hpp>
#include <vector>

template <typename T>
void test_is_trivially_copy_constructible()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_COPY_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_trivially_copy_constructible<T>::value);
    STATIC_REQUIRE(phi::is_trivially_copy_constructible<const T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_copy_constructible_v<T>);
    STATIC_REQUIRE(phi::is_trivially_copy_constructible_v<const T>);
#    endif
#endif
}

template <typename T>
void test_is_not_trivially_copy_constructible()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_COPY_CONSTRUCTIBLE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_copy_constructible<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_trivially_copy_constructible<const T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_copy_constructible_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_trivially_copy_constructible_v<const T>);
#    endif
#endif
}

struct A
{
    A(const A&);
};

struct B
{
    B(const B&)
    {}
};

struct C
{
    C& operator=(const C&) = default;
};

struct D
{
    D(const D&) = delete;
};

TEST_CASE("is_trivially_copy_constructible")
{
    test_is_not_trivially_copy_constructible<A>();
    test_is_not_trivially_copy_constructible<B>();
    test_is_trivially_copy_constructible<C>();
    test_is_not_trivially_copy_constructible<D>();

    test_is_not_trivially_copy_constructible<void>();
    test_is_not_trivially_copy_constructible<volatile void>();
    test_is_trivially_copy_constructible<phi::nullptr_t>();
    test_is_trivially_copy_constructible<bool>();
    test_is_trivially_copy_constructible<char>();
    test_is_trivially_copy_constructible<signed char>();
    test_is_trivially_copy_constructible<unsigned char>();
    test_is_trivially_copy_constructible<short>();
    test_is_trivially_copy_constructible<unsigned short>();
    test_is_trivially_copy_constructible<int>();
    test_is_trivially_copy_constructible<unsigned int>();
    test_is_trivially_copy_constructible<long>();
    test_is_trivially_copy_constructible<unsigned long>();
    test_is_trivially_copy_constructible<long long>();
    test_is_trivially_copy_constructible<unsigned long long>();
    test_is_trivially_copy_constructible<float>();
    test_is_trivially_copy_constructible<double>();
    test_is_trivially_copy_constructible<long double>();
    test_is_trivially_copy_constructible<char8_t>();
    test_is_trivially_copy_constructible<char16_t>();
    test_is_trivially_copy_constructible<char32_t>();
    test_is_trivially_copy_constructible<wchar_t>();

    test_is_trivially_copy_constructible<phi::boolean>();
    test_is_trivially_copy_constructible<phi::integer<signed char>>();
    test_is_trivially_copy_constructible<phi::integer<unsigned char>>();
    test_is_trivially_copy_constructible<phi::integer<short>>();
    test_is_trivially_copy_constructible<phi::integer<unsigned short>>();
    test_is_trivially_copy_constructible<phi::integer<int>>();
    test_is_trivially_copy_constructible<phi::integer<unsigned int>>();
    test_is_trivially_copy_constructible<phi::integer<long>>();
    test_is_trivially_copy_constructible<phi::integer<unsigned long>>();
    test_is_trivially_copy_constructible<phi::integer<long long>>();
    test_is_trivially_copy_constructible<phi::integer<unsigned long long>>();
    test_is_trivially_copy_constructible<phi::floating_point<float>>();
    test_is_trivially_copy_constructible<phi::floating_point<double>>();
    test_is_trivially_copy_constructible<phi::floating_point<long double>>();

    test_is_not_trivially_copy_constructible<std::vector<int>>();
    test_is_not_trivially_copy_constructible<phi::scope_ptr<int>>();

    test_is_trivially_copy_constructible<int&>();
    test_is_trivially_copy_constructible<const int&>();
    test_is_trivially_copy_constructible<volatile int&>();
    test_is_trivially_copy_constructible<const volatile int&>();
    test_is_not_trivially_copy_constructible<int&&>();
    test_is_not_trivially_copy_constructible<const int&&>();
    test_is_not_trivially_copy_constructible<volatile int&&>();
    test_is_not_trivially_copy_constructible<const volatile int&&>();
    test_is_trivially_copy_constructible<int*>();
    test_is_trivially_copy_constructible<const int*>();
    test_is_trivially_copy_constructible<volatile int*>();
    test_is_trivially_copy_constructible<const volatile int*>();
    test_is_trivially_copy_constructible<int**>();
    test_is_trivially_copy_constructible<const int**>();
    test_is_trivially_copy_constructible<volatile int**>();
    test_is_trivially_copy_constructible<const volatile int**>();
    test_is_trivially_copy_constructible<void*>();
    test_is_not_trivially_copy_constructible<char[3]>();
    test_is_not_trivially_copy_constructible<char[]>();
    test_is_not_trivially_copy_constructible<char* [3]>();
    test_is_not_trivially_copy_constructible<char*[]>();
    test_is_not_trivially_copy_constructible<Class>();
    test_is_trivially_copy_constructible<Union>();
    test_is_trivially_copy_constructible<NonEmptyUnion>();
    test_is_trivially_copy_constructible<Empty>();
    test_is_not_trivially_copy_constructible<NotEmpty>();
    test_is_trivially_copy_constructible<bit_zero>();
    test_is_trivially_copy_constructible<bit_one>();
    test_is_not_trivially_copy_constructible<Abstract>();
    test_is_not_trivially_copy_constructible<AbstractTemplate<int>>();
    test_is_trivially_copy_constructible<AbstractTemplate<double>>();
    test_is_not_trivially_copy_constructible<AbstractTemplate<Class>>();
    test_is_trivially_copy_constructible<Final>();
    test_is_trivially_copy_constructible<Enum>();
    test_is_trivially_copy_constructible<EnumSigned>();
    test_is_trivially_copy_constructible<EnumUnsigned>();
    test_is_trivially_copy_constructible<EnumClass>();
    test_is_not_trivially_copy_constructible<Function>();
    test_is_trivially_copy_constructible<FunctionPtr>();
    test_is_trivially_copy_constructible<MemberObjectPtr>();
    test_is_trivially_copy_constructible<MemberFunctionPtr>();
    test_is_trivially_copy_constructible<int Class::*>();
    test_is_trivially_copy_constructible<float Class::*>();

    test_is_not_trivially_copy_constructible<void()>();
    test_is_not_trivially_copy_constructible<void() noexcept>();
    test_is_not_trivially_copy_constructible<void(int)>();
    test_is_not_trivially_copy_constructible<void(int) noexcept>();

    test_is_not_trivially_copy_constructible<void(...)>();
    test_is_not_trivially_copy_constructible<void(...) noexcept>();
    test_is_not_trivially_copy_constructible<void(int, ...)>();
    test_is_not_trivially_copy_constructible<void(int, ...) noexcept>();

    test_is_trivially_copy_constructible<void (*)()>();
    test_is_trivially_copy_constructible<void (*)() noexcept>();
    test_is_trivially_copy_constructible<void (*)(int)>();
    test_is_trivially_copy_constructible<void (*)(int) noexcept>();

    test_is_trivially_copy_constructible<void (*)(...)>();
    test_is_trivially_copy_constructible<void (*)(...) noexcept>();
    test_is_trivially_copy_constructible<void (*)(int, ...)>();
    test_is_trivially_copy_constructible<void (*)(int, ...) noexcept>();

    test_is_trivially_copy_constructible<void (Class::*)()>();
    test_is_trivially_copy_constructible<void (Class::*)()&>();
    test_is_trivially_copy_constructible<void (Class::*)() &&>();
    test_is_trivially_copy_constructible<void (Class::*)() const>();
    test_is_trivially_copy_constructible<void (Class::*)() const&>();
    test_is_trivially_copy_constructible<void (Class::*)() const&&>();

    test_is_trivially_copy_constructible<void (Class::*)() noexcept>();
    test_is_trivially_copy_constructible<void (Class::*)()& noexcept>();
    test_is_trivially_copy_constructible<void (Class::*)()&& noexcept>();
    test_is_trivially_copy_constructible<void (Class::*)() const noexcept>();
    test_is_trivially_copy_constructible<void (Class::*)() const& noexcept>();
    test_is_trivially_copy_constructible<void (Class::*)() const&& noexcept>();

    test_is_trivially_copy_constructible<void (Class::*)(int)>();
    test_is_trivially_copy_constructible<void (Class::*)(int)&>();
    test_is_trivially_copy_constructible<void (Class::*)(int) &&>();
    test_is_trivially_copy_constructible<void (Class::*)(int) const>();
    test_is_trivially_copy_constructible<void (Class::*)(int) const&>();
    test_is_trivially_copy_constructible<void (Class::*)(int) const&&>();

    test_is_trivially_copy_constructible<void (Class::*)(int) noexcept>();
    test_is_trivially_copy_constructible<void (Class::*)(int)& noexcept>();
    test_is_trivially_copy_constructible<void (Class::*)(int)&& noexcept>();
    test_is_trivially_copy_constructible<void (Class::*)(int) const noexcept>();
    test_is_trivially_copy_constructible<void (Class::*)(int) const& noexcept>();
    test_is_trivially_copy_constructible<void (Class::*)(int) const&& noexcept>();

    test_is_trivially_copy_constructible<void (Class::*)(...)>();
    test_is_trivially_copy_constructible<void (Class::*)(...)&>();
    test_is_trivially_copy_constructible<void (Class::*)(...) &&>();
    test_is_trivially_copy_constructible<void (Class::*)(...) const>();
    test_is_trivially_copy_constructible<void (Class::*)(...) const&>();
    test_is_trivially_copy_constructible<void (Class::*)(...) const&&>();

    test_is_trivially_copy_constructible<void (Class::*)(...) noexcept>();
    test_is_trivially_copy_constructible<void (Class::*)(...)& noexcept>();
    test_is_trivially_copy_constructible<void (Class::*)(...)&& noexcept>();
    test_is_trivially_copy_constructible<void (Class::*)(...) const noexcept>();
    test_is_trivially_copy_constructible<void (Class::*)(...) const& noexcept>();
    test_is_trivially_copy_constructible<void (Class::*)(...) const&& noexcept>();
}
