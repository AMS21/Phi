#include <phi/test/test_macros.hpp>

#include <phi/core/size_t.hpp>
#include <phi/type_traits/static_min.hpp>

template <phi::size_t Expected, phi::size_t... Values>
void test_static_min()
{
    STATIC_REQUIRE(phi::static_min<Values...>::value == Expected);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::static_min_v<Values...> == Expected);
#endif
}

TEST_CASE("type_traits.static_min")
{
    // 1 Argument
    test_static_min<0, 0>();
    test_static_min<1, 1>();
    test_static_min<2, 2>();
    test_static_min<3, 3>();

    // 2 Arguments
    test_static_min<0, 0, 0>();
    test_static_min<0, 1, 0>();
    test_static_min<0, 0, 1>();
    test_static_min<1, 1, 1>();
    test_static_min<1, 2, 1>();
    test_static_min<1, 1, 2>();
    test_static_min<0, 0, 2>();
    test_static_min<0, 2, 0>();
    test_static_min<2, 2, 2>();
    test_static_min<1, 2, 1>();
    test_static_min<1, 1, 3>();
    test_static_min<0, 0, 3>();
    test_static_min<0, 3, 0>();
    test_static_min<2, 2, 3>();
    test_static_min<2, 3, 2>();
    test_static_min<3, 3, 3>();

    // 3 Arguments
    test_static_min<0, 0, 0, 0>();
    test_static_min<0, 1, 0, 0>();
    test_static_min<0, 0, 1, 0>();
    test_static_min<0, 0, 0, 1>();
    test_static_min<0, 1, 1, 0>();
    test_static_min<0, 1, 0, 1>();
    test_static_min<1, 1, 1, 1>();
    test_static_min<0, 2, 0, 0>();
    test_static_min<0, 0, 2, 0>();
    test_static_min<0, 0, 0, 2>();
    test_static_min<0, 2, 1, 0>();
    test_static_min<0, 2, 0, 1>();
    test_static_min<0, 1, 2, 0>();
    test_static_min<0, 0, 2, 1>();
    test_static_min<0, 1, 0, 2>();
    test_static_min<0, 0, 1, 2>();

    // 10 Arguments
    test_static_min<0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9>();
}
