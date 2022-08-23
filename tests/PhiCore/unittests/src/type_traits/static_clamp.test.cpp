#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/core/size_t.hpp>
#include <phi/type_traits/static_clamp.hpp>

template <phi::size_t Value, phi::size_t Min, phi::size_t Max, phi::size_t Expected>
void test_static_clamp()
{
    STATIC_REQUIRE(phi::static_clamp<Value, Min, Max>::value == Expected);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::static_clamp_v<Value, Min, Max> == Expected);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::static_clamp<Value, Min, Max>);
}

TEST_CASE("type_traits.static_clamp")
{
    test_static_clamp<0, 0, 0, 0>();
    test_static_clamp<1, 0, 0, 0>();
    test_static_clamp<2, 0, 0, 0>();

    test_static_clamp<0, 0, 1, 0>();
    test_static_clamp<1, 0, 1, 1>();
    test_static_clamp<2, 0, 1, 1>();

    test_static_clamp<0, 1, 1, 1>();
    test_static_clamp<1, 1, 1, 1>();
    test_static_clamp<2, 1, 1, 1>();

    test_static_clamp<0, 0, 2, 0>();
    test_static_clamp<1, 0, 2, 1>();
    test_static_clamp<2, 0, 2, 2>();

    test_static_clamp<0, 1, 2, 1>();
    test_static_clamp<1, 1, 2, 1>();
    test_static_clamp<2, 1, 2, 2>();

    test_static_clamp<0, 2, 2, 2>();
    test_static_clamp<1, 2, 2, 2>();
    test_static_clamp<2, 2, 2, 2>();
}
