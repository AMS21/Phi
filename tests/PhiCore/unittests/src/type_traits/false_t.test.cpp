#include <phi/test/test_macros.hpp>

#include <phi/core/types.hpp>
#include <phi/type_traits/false_t.hpp>

class CustomClass
{};

template <typename... T>
void test_false_t()
{
    STATIC_REQUIRE_FALSE(phi::false_t<T...>::value);
    STATIC_REQUIRE(!phi::false_t<T...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::false_v<T...>);
    STATIC_REQUIRE(!phi::false_v<T...>);
#endif
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
    test_false_t<CustomClass>();

    STATIC_REQUIRE_FALSE(phi::false_t<>::value);
    STATIC_REQUIRE_FALSE(phi::false_t<int>::value);
    STATIC_REQUIRE_FALSE(phi::false_t<int, int>::value);
    STATIC_REQUIRE_FALSE(phi::false_t<int, int, int>::value);
    STATIC_REQUIRE_FALSE(phi::false_t<int, int, int, int>::value);
    STATIC_REQUIRE_FALSE(phi::false_t<int, int, int, int, int>::value);

    func<int>();
}
