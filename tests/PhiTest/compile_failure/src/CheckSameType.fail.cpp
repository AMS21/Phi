#include <Phi/Test/TestMacros.hpp>

struct A
{};

struct B
{};

TEST_CASE("CHECK_SAME_TYPE")
{
    CHECK_SAME_TYPE(A, B);
}
