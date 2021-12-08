#include <phi/test/test_macros.hpp>

struct A
{};

TEST_CASE("CHECK_NOT_SAME_TYPE")
{
    CHECK_NOT_SAME_TYPE(A, A);
}
