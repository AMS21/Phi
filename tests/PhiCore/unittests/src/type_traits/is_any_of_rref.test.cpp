#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/type_traits/is_any_of_rref.hpp>

template <typename TypeT, typename... ArgsT>
void test_is_any_of_rref()
{
    STATIC_REQUIRE(phi::is_any_of_rref<TypeT, ArgsT...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_any_of_rref_v<TypeT, ArgsT...>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_any_of_rref<TypeT, ArgsT...>);
}

template <typename TypeT, typename... ArgsT>
void test_is_not_any_of_rref()
{
    STATIC_REQUIRE_FALSE(phi::is_any_of_rref<TypeT, ArgsT...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_any_of_rref_v<TypeT, ArgsT...>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_any_of_rref<TypeT, ArgsT...>);
}

struct A
{};

TEST_CASE("is_any_of_rref")
{
    test_is_any_of_rref<int, int>();
    test_is_any_of_rref<int, unsigned, int>();
    test_is_any_of_rref<int, float, unsigned, int>();
    test_is_any_of_rref<int, A, float, unsigned, int>();

    test_is_any_of_rref<int, int, void>();
    test_is_any_of_rref<int, void, int>();
    test_is_any_of_rref<int, int, void, void>();
    test_is_any_of_rref<int, void, int, void>();
    test_is_any_of_rref<int, void, void, int>();
    test_is_any_of_rref<int, int, void, void, void>();
    test_is_any_of_rref<int, void, int, void, void>();
    test_is_any_of_rref<int, void, void, int, void>();
    test_is_any_of_rref<int, void, void, void, int>();

    test_is_not_any_of_rref<int, void>();
    test_is_not_any_of_rref<int, void, void>();
    test_is_not_any_of_rref<int, void, void, void>();

    // const, volatile
    test_is_not_any_of_rref<int, const int, volatile int, const volatile int, const int&,
                            volatile int&, const volatile int&, const int&&, volatile int&&,
                            const volatile int&&>();

    // ref
    test_is_any_of_rref<int, int&>();
    test_is_any_of_rref<int, int&&>();
}
