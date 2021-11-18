#include <Phi/Test/TestMacros.hpp>

#include <Phi/TypeTraits/disable_if.hpp>

TEST_CASE("disable_if")
{
    CHECK_SAME_TYPE(void, phi::disable_if<false>::type);
    CHECK_SAME_TYPE(int, phi::disable_if<false, int>::type);

    CHECK_SAME_TYPE(void, phi::disable_if_t<false>);
    CHECK_SAME_TYPE(int, phi::disable_if_t<false, int>);

    using t1 = phi::disable_if<true, void>;
    CHECK_SAME_TYPE(t1, phi::disable_if<true>);
}
