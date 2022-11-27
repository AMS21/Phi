#include <phi/compiler_support/warning.hpp>

PHI_EXTERNAL_HEADERS_BEGIN()
#include <iostream>
PHI_EXTERNAL_HEADERS_END()

int main()
{
    std::cerr << "[TEST_STRING_WHICH_INDICATES_TEST_FAILURE]\n";
}
