#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/type_traits/is_none_of_rv.hpp>

template <typename TypeT, typename... ArgsT>
void test_is_none_of_rv()
{
    STATIC_REQUIRE(phi::is_none_of_rv<TypeT, ArgsT...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_none_of_rv_v<TypeT, ArgsT...>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_none_of_rv<TypeT, ArgsT...>);
}

template <typename TypeT, typename... ArgsT>
void test_is_not_none_of_rv()
{
    STATIC_REQUIRE_FALSE(phi::is_none_of_rv<TypeT, ArgsT...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_none_of_rv_v<TypeT, ArgsT...>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_none_of_rv<TypeT, ArgsT...>);
}

struct A
{};

TEST_CASE("is_none_of_rv")
{
    test_is_none_of_rv<int, void>();
    test_is_none_of_rv<int, unsigned, void>();
    test_is_none_of_rv<int, float, unsigned, void>();
    test_is_none_of_rv<int, A, float, unsigned, void>();

    test_is_not_none_of_rv<int, int, void>();
    test_is_not_none_of_rv<int, void, int>();
    test_is_not_none_of_rv<int, int, void, void>();
    test_is_not_none_of_rv<int, void, int, void>();
    test_is_not_none_of_rv<int, void, void, int>();
    test_is_not_none_of_rv<int, int, void, void, void>();
    test_is_not_none_of_rv<int, void, int, void, void>();
    test_is_not_none_of_rv<int, void, void, int, void>();
    test_is_not_none_of_rv<int, void, void, void, int>();

    test_is_none_of_rv<int, void>();
    test_is_none_of_rv<int, void, void>();
    test_is_none_of_rv<int, void, void, void>();

    // volatile
    test_is_not_none_of_rv<int, volatile int>();
    test_is_not_none_of_rv<volatile int, int>();

    // const, ref
    test_is_none_of_rv<int, const int, const volatile int, int&, int&&, const int&, const int&&,
                       volatile int&, volatile int&&, const volatile int&, const volatile int&&>();
}
