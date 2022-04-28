#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/type_traits/is_any_of_rcvref.hpp>

template <typename T, typename... Args>
void test_is_any_of_rcvref()
{
    STATIC_REQUIRE(phi::is_any_of_rcvref<T, Args...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_any_of_rcvref_v<T, Args...>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_any_of_rcvref<T, Args...>);
}

template <typename T, typename... Args>
void test_is_not_any_of_rcvref()
{
    STATIC_REQUIRE_FALSE(phi::is_any_of_rcvref<T, Args...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_any_of_rcvref_v<T, Args...>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_any_of_rcvref<T, Args...>);
}

struct A
{};

TEST_CASE("is_any_of_rcvref")
{
    test_is_any_of_rcvref<int, int>();
    test_is_any_of_rcvref<int, unsigned, int>();
    test_is_any_of_rcvref<int, float, unsigned, int>();
    test_is_any_of_rcvref<int, A, float, unsigned, int>();

    test_is_any_of_rcvref<int, int, void>();
    test_is_any_of_rcvref<int, void, int>();
    test_is_any_of_rcvref<int, int, void, void>();
    test_is_any_of_rcvref<int, void, int, void>();
    test_is_any_of_rcvref<int, void, void, int>();
    test_is_any_of_rcvref<int, int, void, void, void>();
    test_is_any_of_rcvref<int, void, int, void, void>();
    test_is_any_of_rcvref<int, void, void, int, void>();
    test_is_any_of_rcvref<int, void, void, void, int>();

    test_is_not_any_of_rcvref<int, void>();
    test_is_not_any_of_rcvref<int, void, void>();
    test_is_not_any_of_rcvref<int, void, void, void>();

    // const, volatile, ref
    test_is_any_of_rcvref<int, const int>();
    test_is_any_of_rcvref<int, volatile int>();
    test_is_any_of_rcvref<int, const volatile int>();
    test_is_any_of_rcvref<int, const int&>();
    test_is_any_of_rcvref<int, volatile int&>();
    test_is_any_of_rcvref<int, const volatile int&>();
    test_is_any_of_rcvref<int, const int&&>();
    test_is_any_of_rcvref<int, volatile int&&>();
    test_is_any_of_rcvref<int, const volatile int&&>();

    test_is_any_of_rcvref<const int, const int>();
    test_is_any_of_rcvref<const int, volatile int>();
    test_is_any_of_rcvref<const int, const volatile int>();
    test_is_any_of_rcvref<const int, const int&>();
    test_is_any_of_rcvref<const int, volatile int&>();
    test_is_any_of_rcvref<const int, const volatile int&>();
    test_is_any_of_rcvref<const int, const int&&>();
    test_is_any_of_rcvref<const int, volatile int&&>();
    test_is_any_of_rcvref<const int, const volatile int&&>();

    test_is_any_of_rcvref<volatile int, const int>();
    test_is_any_of_rcvref<volatile int, volatile int>();
    test_is_any_of_rcvref<volatile int, const volatile int>();
    test_is_any_of_rcvref<volatile int, const int&>();
    test_is_any_of_rcvref<volatile int, volatile int&>();
    test_is_any_of_rcvref<volatile int, const volatile int&>();
    test_is_any_of_rcvref<volatile int, const int&&>();
    test_is_any_of_rcvref<volatile int, volatile int&&>();
    test_is_any_of_rcvref<volatile int, const volatile int&&>();

    test_is_any_of_rcvref<const volatile int, const int>();
    test_is_any_of_rcvref<const volatile int, volatile int>();
    test_is_any_of_rcvref<const volatile int, const volatile int>();
    test_is_any_of_rcvref<const volatile int, const int&>();
    test_is_any_of_rcvref<const volatile int, volatile int&>();
    test_is_any_of_rcvref<const volatile int, const volatile int&>();
    test_is_any_of_rcvref<const volatile int, const int&&>();
    test_is_any_of_rcvref<const volatile int, volatile int&&>();
    test_is_any_of_rcvref<const volatile int, const volatile int&&>();
}
