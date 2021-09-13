#include <catch2/catch_test_macros.hpp>

#include <Phi/TypeTraits/enable_if.hpp>
#include <Phi/TypeTraits/is_same.hpp>

TEST_CASE("enable_if")
{
    STATIC_REQUIRE(phi::is_same_v<void, phi::enable_if<true>::type>);
    STATIC_REQUIRE(phi::is_same_v<int, phi::enable_if<true, int>::type>);

    STATIC_REQUIRE(phi::is_same_v<void, phi::enable_if_t<true>>);
    STATIC_REQUIRE(phi::is_same_v<int, phi::enable_if_t<true, int>>);

    using t1 = phi::enable_if<false, void>;
    STATIC_REQUIRE(phi::is_same_v<t1, phi::enable_if<false>>);
}
