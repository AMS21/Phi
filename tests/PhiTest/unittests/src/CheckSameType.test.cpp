#include <Phi/Test/TestMacros.hpp>

struct A
{};

TEST_CASE("CHECK_SAME_TYPE")
{
    CHECK_SAME_TYPE(A, A);
    CHECK_SAME_TYPE(const A, const A);
    CHECK_SAME_TYPE(int, int);
}
