#include <Phi/Test/TestMacros.hpp>

#include <iostream>

TEST_CASE("CHECK")
{
    std::cout << "Hello from CHECK\n";

    CHECK(false);
}
