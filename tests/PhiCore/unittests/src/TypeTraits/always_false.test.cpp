#include <Phi/Test/TestMacros.hpp>

#include <Phi/Core/Types.hpp>
#include <Phi/TypeTraits/always_false.hpp>

class CustomClass
{};

template <typename... T>
void test_always_false()
{
    STATIC_REQUIRE_FALSE(phi::always_false<T...>::value);
    STATIC_REQUIRE(!phi::always_false<T...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::always_false_v<T...>);
    STATIC_REQUIRE(!phi::always_false_v<T...>);
#endif
}

template <typename TypeT>
void func()
{
    static_assert(phi::always_false<TypeT>::value, "Failure");
}

template <>
void func<int>()
{}

TEST_CASE("always_false")
{
    test_always_false<void>();
    test_always_false<int>();
    test_always_false<float>();
    test_always_false<phi::i32>();
    test_always_false<phi::f64>();
    test_always_false<CustomClass>();

    STATIC_REQUIRE_FALSE(phi::always_false<>::value);
    STATIC_REQUIRE_FALSE(phi::always_false<int>::value);
    STATIC_REQUIRE_FALSE(phi::always_false<int, int>::value);
    STATIC_REQUIRE_FALSE(phi::always_false<int, int, int>::value);
    STATIC_REQUIRE_FALSE(phi::always_false<int, int, int, int>::value);
    STATIC_REQUIRE_FALSE(phi::always_false<int, int, int, int, int>::value);

    func<int>();
}
