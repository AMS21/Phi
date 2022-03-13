#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/warning.hpp>

PHI_MSVC_SUPPRESS_WARNING_WITH_PUSH(
        4668) // '__STDC_WANT_SECURE_LIB__' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
#include <iostream>
PHI_MSVC_SUPPRESS_WARNING_POP()

TEST_CASE("CHECK")
{
    std::cout << "Hello from CHECK\n";

    CHECK(false);
}
