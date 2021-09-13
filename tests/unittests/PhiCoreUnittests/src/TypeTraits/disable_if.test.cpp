#include <catch2/catch_test_macros.hpp>

#include <Phi/TypeTraits/disable_if.hpp>
#include <Phi/TypeTraits/is_same.hpp>

TEST_CASE("disable_if")
{
    STATIC_REQUIRE(phi::is_same_v<void, phi::disable_if<false>::type>);
    STATIC_REQUIRE(phi::is_same_v<int, phi::disable_if<false, int>::type>);

    STATIC_REQUIRE(phi::is_same_v<void, phi::disable_if_t<false>>);
    STATIC_REQUIRE(phi::is_same_v<int, phi::disable_if_t<false, int>>);

    using t1 = phi::disable_if<true, void>;
    STATIC_REQUIRE(phi::is_same_v<t1, phi::disable_if<true>>);
}
