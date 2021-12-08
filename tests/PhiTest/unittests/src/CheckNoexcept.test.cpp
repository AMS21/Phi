#include <phi/test/test_macros.hpp>

void f() noexcept;

TEST_CASE("CHECK_NOEXCEPT")
{
    CHECK_NOEXCEPT(f());
}
