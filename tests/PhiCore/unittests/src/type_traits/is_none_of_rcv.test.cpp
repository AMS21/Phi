#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/type_traits/is_none_of_rcv.hpp>

template <typename TypeT, typename... ArgsT>
void test_is_none_of_rcv()
{
    STATIC_REQUIRE(phi::is_none_of_rcv<TypeT, ArgsT...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_none_of_rcv_v<TypeT, ArgsT...>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_none_of_rcv<TypeT, ArgsT...>);
}

template <typename TypeT, typename... ArgsT>
void test_is_not_none_of_rcv()
{
    STATIC_REQUIRE_FALSE(phi::is_none_of_rcv<TypeT, ArgsT...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_none_of_rcv_v<TypeT, ArgsT...>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_none_of_rcv<TypeT, ArgsT...>);
}

struct A
{};

TEST_CASE("is_none_of_rcv")
{
    test_is_none_of_rcv<int, void>();
    test_is_none_of_rcv<int, unsigned, void>();
    test_is_none_of_rcv<int, float, unsigned, void>();
    test_is_none_of_rcv<int, A, float, unsigned, void>();

    test_is_not_none_of_rcv<int, int, void>();
    test_is_not_none_of_rcv<int, void, int>();
    test_is_not_none_of_rcv<int, int, void, void>();
    test_is_not_none_of_rcv<int, void, int, void>();
    test_is_not_none_of_rcv<int, void, void, int>();
    test_is_not_none_of_rcv<int, int, void, void, void>();
    test_is_not_none_of_rcv<int, void, int, void, void>();
    test_is_not_none_of_rcv<int, void, void, int, void>();
    test_is_not_none_of_rcv<int, void, void, void, int>();

    test_is_none_of_rcv<int, void>();
    test_is_none_of_rcv<int, void, void>();
    test_is_none_of_rcv<int, void, void, void>();

    // const, volatile
    test_is_not_none_of_rcv<int, const int>();
    test_is_not_none_of_rcv<int, volatile int>();
    test_is_not_none_of_rcv<int, const volatile int>();
    test_is_not_none_of_rcv<const int, const int>();
    test_is_not_none_of_rcv<const int, volatile int>();
    test_is_not_none_of_rcv<const int, const volatile int>();
    test_is_not_none_of_rcv<volatile int, const int>();
    test_is_not_none_of_rcv<volatile int, volatile int>();
    test_is_not_none_of_rcv<volatile int, const volatile int>();
    test_is_not_none_of_rcv<const volatile int, const int>();
    test_is_not_none_of_rcv<const volatile int, volatile int>();
    test_is_not_none_of_rcv<const volatile int, const volatile int>();
    test_is_not_none_of_rcv<float, const float>();
    test_is_not_none_of_rcv<const int, int>();
    test_is_not_none_of_rcv<volatile int, const volatile int>();

    // ref
    test_is_none_of_rcv<int, int&, int&&, const int&, const int&&, volatile int&, volatile int&&,
                        const volatile int&, const volatile int&&>();
}
