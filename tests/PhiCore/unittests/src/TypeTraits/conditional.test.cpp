#include <Phi/Test/TestMacros.hpp>

#include <Phi/TypeTraits/conditional.hpp>

TEST_CASE("type_traits.conditional")
{
    CHECK_SAME_TYPE(phi::conditional<true, int, double>::type, int);
    CHECK_SAME_TYPE(phi::conditional<false, int, double>::type, double);
    CHECK_SAME_TYPE(phi::conditional<sizeof(int) >= sizeof(double), int, double>::type, double);

    CHECK_SAME_TYPE(phi::conditional_t<true, int, double>, int);
    CHECK_SAME_TYPE(phi::conditional_t<false, int, double>, double);
    CHECK_SAME_TYPE(phi::conditional_t<sizeof(int) >= sizeof(double), int, double>, double);
}
