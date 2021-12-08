#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/counter.hpp>

TEST_CASE("counter")
{
    int i = PHI_COUNTER();
    int j = PHI_COUNTER();

    CHECK(i != j);
}
