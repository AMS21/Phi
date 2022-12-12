#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/warning.hpp>
#include <iostream>

TEST_CASE("CHECK")
{
    std::cout << "Hello from CHECK\n";

    CHECK(false);
}
