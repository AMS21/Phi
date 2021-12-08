#include <phi/test/test_macros.hpp>

#include <iostream>

TEST_CASE("CHECK")
{
    std::cout << "Hello from CHECK\n";

    CHECK(false);
}
