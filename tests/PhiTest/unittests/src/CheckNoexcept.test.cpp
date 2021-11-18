#include <Phi/Test/TestMacros.hpp>

void f() noexcept;

TEST_CASE("CHECK_NOEXCEPT")
{
    CHECK_NOEXCEPT(f());
}
