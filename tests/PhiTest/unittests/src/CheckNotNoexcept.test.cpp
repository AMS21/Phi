#include <phi/test/test_macros.hpp>

void f() noexcept(false)
{}

TEST_CASE("CHECK_NOT_NOEXCEPT")
{
    CHECK_NOT_NOEXCEPT(f());
}
