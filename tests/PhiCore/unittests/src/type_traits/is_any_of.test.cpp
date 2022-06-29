#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/type_traits/is_any_of.hpp>

template <typename TypeT, typename... ArgsT>
void test_is_any_of()
{
    STATIC_REQUIRE(phi::is_any_of<TypeT, ArgsT...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_any_of_v<TypeT, ArgsT...>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_any_of<TypeT, ArgsT...>);
}

template <typename TypeT, typename... ArgsT>
void test_is_not_any_of()
{
    STATIC_REQUIRE_FALSE(phi::is_any_of<TypeT, ArgsT...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_any_of_v<TypeT, ArgsT...>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_any_of<TypeT, ArgsT...>);
}

struct A
{};

TEST_CASE("is_any_of")
{
    test_is_any_of<int, int>();
    test_is_any_of<int, unsigned, int>();
    test_is_any_of<int, float, unsigned, int>();
    test_is_any_of<int, A, float, unsigned, int>();

    test_is_any_of<int, int, void>();
    test_is_any_of<int, void, int>();
    test_is_any_of<int, int, void, void>();
    test_is_any_of<int, void, int, void>();
    test_is_any_of<int, void, void, int>();
    test_is_any_of<int, int, void, void, void>();
    test_is_any_of<int, void, int, void, void>();
    test_is_any_of<int, void, void, int, void>();
    test_is_any_of<int, void, void, void, int>();

    test_is_not_any_of<int, void>();
    test_is_not_any_of<int, void, void>();
    test_is_not_any_of<int, void, void, void>();

    // const, volatile, ref
    test_is_not_any_of<int, const int, volatile int, const volatile int, int&, int&&, const int&,
                       const int&&, volatile int&, volatile int&&, const volatile int&,
                       const volatile int&&>();
}
