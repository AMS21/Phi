#include <catch2/catch.hpp>

#include "SameType.hpp"
#include <Phi/TypeTraits/enable_if.hpp>

TEST_CASE("enable_if")
{
    CHECK_SAME_TYPE(void, phi::enable_if<true>::type);
    CHECK_SAME_TYPE(int, phi::enable_if<true, int>::type);

    CHECK_SAME_TYPE(void, phi::enable_if_t<true>);
    CHECK_SAME_TYPE(int, phi::enable_if_t<true, int>);

    using t1 = phi::enable_if<false, void>;
    CHECK_SAME_TYPE(t1, phi::enable_if<false>);
}
