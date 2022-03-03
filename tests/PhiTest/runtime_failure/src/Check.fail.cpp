#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/warning.hpp>

PHI_EXTERNAL_HEADERS_BEGIN()
#include <iostream>
PHI_EXTERNAL_HEADERS_END()

TEST_CASE("CHECK")
{
    std::cout << "Hello from CHECK\n";

    CHECK(false);
}
