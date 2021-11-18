#include <Phi/Test/TestMacros.hpp>

struct A
{};

struct B
{};

TEST_CASE("CHECK_NOT_SAME_TYPE")
{
    CHECK_NOT_SAME_TYPE(A, B);
    CHECK_NOT_SAME_TYPE(B, A);

    CHECK_NOT_SAME_TYPE(A, int);
    CHECK_NOT_SAME_TYPE(int, A);

    CHECK_NOT_SAME_TYPE(A, const A);
    CHECK_NOT_SAME_TYPE(const A, A);
}
