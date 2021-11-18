#include <Phi/Test/TestMacros.hpp>

void f() noexcept(false)
{}

TEST_CASE("CHECK_NOT_NOEXCEPT")
{
    CHECK_NOT_NOEXCEPT(f());
}
