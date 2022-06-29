#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/core/types.hpp>
#include <phi/type_traits/true_t.hpp>

struct Custom
{};

template <typename... ArgsT>
void test_true_t()
{
    STATIC_REQUIRE(phi::true_t<ArgsT...>::value);
    STATIC_REQUIRE_FALSE(!phi::true_t<ArgsT...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::true_v<ArgsT...>);
    STATIC_REQUIRE_FALSE(!phi::true_v<ArgsT...>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::true_t<ArgsT...>);
}

template <typename TypeT>
static void func()
{
    static_assert(!phi::true_t<TypeT>::value, "Failure");
}

template <>
void func<int>()
{}

TEST_CASE("true_t")
{
    test_true_t<void>();
    test_true_t<int>();
    test_true_t<float>();
    test_true_t<phi::i32>();
    test_true_t<phi::f64>();
    test_true_t<Custom>();

    test_true_t<>();
    test_true_t<int>();
    test_true_t<int, int>();
    test_true_t<int, int, int>();
    test_true_t<int, int, int, int>();
    test_true_t<int, int, int, int, int>();

    func<int>();
}
