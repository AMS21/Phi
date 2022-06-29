#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/core/types.hpp>
#include <phi/type_traits/false_t.hpp>

struct Custom
{};

template <typename... ArgsT>
void test_false_t()
{
    STATIC_REQUIRE_FALSE(phi::false_t<ArgsT...>::value);
    STATIC_REQUIRE(!phi::false_t<ArgsT...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::false_v<ArgsT...>);
    STATIC_REQUIRE(!phi::false_v<ArgsT...>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::false_t<ArgsT...>);
}

template <typename TypeT>
void func()
{
    static_assert(phi::false_t<TypeT>::value, "Failure");
}

template <>
void func<int>()
{}

TEST_CASE("false_t")
{
    test_false_t<void>();
    test_false_t<int>();
    test_false_t<float>();
    test_false_t<phi::i32>();
    test_false_t<phi::f64>();
    test_false_t<Custom>();

    test_false_t<>();
    test_false_t<int>();
    test_false_t<int, int>();
    test_false_t<int, int, int>();
    test_false_t<int, int, int, int>();
    test_false_t<int, int, int, int, int>();

    func<int>();
}
