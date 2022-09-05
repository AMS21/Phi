#include <phi/test/test_macros.hpp>

void f() noexcept(false);

void g();

TEST_CASE("CHECK_NOT_NOEXCEPT")
{
    CHECK_NOT_NOEXCEPT(f());
    CHECK_NOT_NOEXCEPT(g());
}
