#include <phi/compiler_support/warning.hpp>

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnoexcept")

#include <phi/test/test_macros.hpp>

void f() noexcept(false)
{}

TEST_CASE("CHECK_NOT_NOEXCEPT")
{
    CHECK_NOT_NOEXCEPT(f());
}

PHI_GCC_SUPPRESS_WARNING_POP()