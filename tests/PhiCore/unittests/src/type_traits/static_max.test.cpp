#include <phi/test/test_macros.hpp>

#include <phi/core/size_t.hpp>
#include <phi/type_traits/static_max.hpp>

template <phi::size_t Expected, phi::size_t... Values>
void test_static_max()
{
    STATIC_REQUIRE(phi::static_max<Values...>::value == Expected);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::static_max_v<Values...> == Expected);
#endif
}

TEST_CASE("type_traits.static_max")
{
    // 1 Argument
    test_static_max<0, 0>();
    test_static_max<1, 1>();
    test_static_max<2, 2>();
    test_static_max<3, 3>();

    // 2 Arguments
    test_static_max<0, 0, 0>();
    test_static_max<1, 1, 0>();
    test_static_max<1, 0, 1>();
    test_static_max<1, 1, 1>();
    test_static_max<2, 2, 1>();
    test_static_max<2, 1, 2>();
    test_static_max<2, 0, 2>();
    test_static_max<2, 2, 0>();
    test_static_max<2, 2, 2>();
    test_static_max<2, 2, 1>();
    test_static_max<3, 1, 3>();
    test_static_max<3, 0, 3>();
    test_static_max<3, 3, 0>();
    test_static_max<3, 2, 3>();
    test_static_max<3, 3, 2>();
    test_static_max<3, 3, 3>();

    // 3 Arguments
    test_static_max<0, 0, 0, 0>();
    test_static_max<1, 1, 0, 0>();
    test_static_max<1, 0, 1, 0>();
    test_static_max<1, 0, 0, 1>();
    test_static_max<1, 1, 1, 0>();
    test_static_max<1, 1, 0, 1>();
    test_static_max<1, 1, 1, 1>();
    test_static_max<2, 2, 0, 0>();
    test_static_max<2, 0, 2, 0>();
    test_static_max<2, 0, 0, 2>();
    test_static_max<2, 2, 1, 0>();
    test_static_max<2, 2, 0, 1>();
    test_static_max<2, 1, 2, 0>();
    test_static_max<2, 0, 2, 1>();
    test_static_max<2, 1, 0, 2>();
    test_static_max<2, 0, 1, 2>();

    // 10 Arguments
    test_static_max<9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9>();
}
