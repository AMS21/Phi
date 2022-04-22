#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/type_traits/is_constructible.hpp>
#include <phi/type_traits/is_trivially_constructible.hpp>
#include <type_traits>

template <typename T, typename... ArgsT>
void test_is_trivially_constructible()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_trivially_constructible<T, ArgsT...>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_constructible<T, ArgsT...>::value);
    STATIC_REQUIRE(phi::is_constructible<T, ArgsT...>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_constructible_v<T, ArgsT...>);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_constructible_v<T, ArgsT...>);
    STATIC_REQUIRE(phi::is_constructible_v<T, ArgsT...>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_trivially_constructible<T, ArgsT...>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_trivially_constructible<T, ArgsT...>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_trivially_constructible<T, ArgsT...>::value);
#endif
}

template <typename T, typename... ArgsT>
void test_is_not_trivially_constructible()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_CONSTRUCTIBLE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_constructible<T, ArgsT...>::value);
    STATIC_REQUIRE(phi::is_not_trivially_constructible<T, ArgsT...>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_constructible_v<T, ArgsT...>);
    STATIC_REQUIRE(phi::is_not_trivially_constructible_v<T, ArgsT...>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_trivially_constructible<T, ArgsT...>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_trivially_constructible<T, ArgsT...>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_trivially_constructible<T, ArgsT...>::value);
#endif
}

struct A
{
    explicit A(int);
    A(int, double);
};

struct B
{
    B() = default;

    B(int)
    {}
};

TEST_CASE("is_trivially_constructible")
{
    test_is_trivially_constructible<int>();
    test_is_trivially_constructible<int, int>();
    test_is_trivially_constructible<int, int&>();
    test_is_trivially_constructible<int, const int&>();

    test_is_not_trivially_constructible<A>();
    test_is_not_trivially_constructible<A, int>();
    test_is_not_trivially_constructible<A, int, double>();

    test_is_trivially_constructible<B>();
    test_is_not_trivially_constructible<B, int>();
}
