#include <Phi/Test/TestMacros.hpp>

void f();

TEST_CASE("CHECK_NOEXCEPT")
{
    CHECK_NOEXCEPT(f());
}
