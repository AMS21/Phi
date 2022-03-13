#include <phi/compiler_support/warning.hpp>

PHI_MSVC_SUPPRESS_WARNING_WITH_PUSH(
        4668) // '__STDC_WANT_SECURE_LIB__' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
#include <iostream>
PHI_MSVC_SUPPRESS_WARNING_POP()

int main()
{
    std::cerr << "[TEST_STRING_WHICH_INDICATES_TEST_FAILURE]\n";
}
