#include <phi/test/test_macros.hpp>

#include "phi/compiler_support/char8_t.hpp"
#include "phi/core/nullptr_t.hpp"
#include "test_types.hpp"
#include <phi/type_traits/is_nothrow_move_constructible.hpp>

template <typename T>
void test_is_nothrow_move_constructible()
{
    STATIC_REQUIRE(phi::is_nothrow_move_constructible<T>::value);
    STATIC_REQUIRE(phi::is_nothrow_move_constructible<const T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_move_constructible_v<T>);
    STATIC_REQUIRE(phi::is_nothrow_move_constructible_v<const T>);
#endif
}

template <typename T>
void test_is_not_nothrow_move_constructible()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_move_constructible<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_move_constructible<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_move_constructible<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_move_constructible<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_move_constructible_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_move_constructible_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_move_constructible_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_move_constructible_v<const volatile T>);
#endif
}

struct A
{
    A(const A&);
};

struct B
{
    B(const B&) noexcept;
};

struct C
{
    C(C&&);
};

struct D
{
    D(const D&) noexcept;
    D(D&&) noexcept;
};

TEST_CASE("is_nothrow_move_constructible")
{
    test_is_nothrow_move_constructible<phi::nullptr_t>();
    test_is_not_nothrow_move_constructible<void>();
    test_is_not_nothrow_move_constructible<volatile void>();
    test_is_nothrow_move_constructible<bool>();
    test_is_nothrow_move_constructible<char>();
    test_is_nothrow_move_constructible<signed char>();
    test_is_nothrow_move_constructible<unsigned char>();
    test_is_nothrow_move_constructible<short>();
    test_is_nothrow_move_constructible<unsigned short>();
    test_is_nothrow_move_constructible<int>();
    test_is_nothrow_move_constructible<unsigned int>();
    test_is_nothrow_move_constructible<long>();
    test_is_nothrow_move_constructible<unsigned long>();
    test_is_nothrow_move_constructible<long long>();
    test_is_nothrow_move_constructible<unsigned long long>();
    test_is_nothrow_move_constructible<float>();
    test_is_nothrow_move_constructible<double>();
    test_is_nothrow_move_constructible<long double>();
    test_is_nothrow_move_constructible<char8_t>();
    test_is_nothrow_move_constructible<char16_t>();
    test_is_nothrow_move_constructible<char32_t>();
    test_is_nothrow_move_constructible<wchar_t>();

    test_is_nothrow_move_constructible<int&>();
    test_is_nothrow_move_constructible<int&&>();
    test_is_nothrow_move_constructible<int*>();
    test_is_nothrow_move_constructible<const int*>();
    test_is_nothrow_move_constructible<volatile int*>();
    test_is_nothrow_move_constructible<const volatile int*>();
    test_is_nothrow_move_constructible<int**>();
    test_is_nothrow_move_constructible<Class>();
    test_is_nothrow_move_constructible<Union>();
    test_is_nothrow_move_constructible<NonEmptyUnion>();
    test_is_nothrow_move_constructible<Empty>();
    test_is_nothrow_move_constructible<NotEmpty>();
    test_is_nothrow_move_constructible<bit_zero>();
    test_is_nothrow_move_constructible<bit_one>();
    test_is_not_nothrow_move_constructible<Abstract>();
    test_is_not_nothrow_move_constructible<AbstractTemplate<int>>();
    test_is_nothrow_move_constructible<AbstractTemplate<double>>();
    test_is_not_nothrow_move_constructible<AbstractTemplate<Class>>();
    test_is_nothrow_move_constructible<Enum>();
    test_is_nothrow_move_constructible<EnumSigned>();
    test_is_nothrow_move_constructible<EnumUnsigned>();
    test_is_nothrow_move_constructible<EnumClass>();
    test_is_not_nothrow_move_constructible<Function>();
    test_is_nothrow_move_constructible<FunctionPtr>();
    test_is_nothrow_move_constructible<MemberObjectPtr>();
    test_is_nothrow_move_constructible<MemberFunctionPtr>();

    test_is_not_nothrow_move_constructible<A>();
    test_is_nothrow_move_constructible<B>();
    test_is_not_nothrow_move_constructible<C>();
    test_is_nothrow_move_constructible<D>();
}
