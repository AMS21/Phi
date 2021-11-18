#include <Phi/Test/TestMacros.hpp>

void f() noexcept;

TEST_CASE("CHECK_NOT_NOEXCEPT")
{
    CHECK_NOT_NOEXCEPT(f());
}
