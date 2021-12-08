#include <phi/test/test_macros.hpp>

#include <phi/core/types.hpp>
#include <phi/type_traits/true_t.hpp>

class CustomClass
{};

template <typename... T>
void test_true_t()
{
    STATIC_REQUIRE(phi::true_t<T...>::value);
    STATIC_REQUIRE_FALSE(!phi::true_t<T...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::true_v<T...>);
    STATIC_REQUIRE_FALSE(!phi::true_v<T...>);
#endif
}

template <typename TypeT>
void func()
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
    test_true_t<CustomClass>();

    STATIC_REQUIRE(phi::true_t<>::value);
    STATIC_REQUIRE(phi::true_t<int>::value);
    STATIC_REQUIRE(phi::true_t<int, int>::value);
    STATIC_REQUIRE(phi::true_t<int, int, int>::value);
    STATIC_REQUIRE(phi::true_t<int, int, int, int>::value);
    STATIC_REQUIRE(phi::true_t<int, int, int, int, int>::value);

    func<int>();
}
