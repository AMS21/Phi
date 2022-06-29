#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/counter.hpp>

TEST_CASE("counter")
{
    int first  = PHI_COUNTER();
    int second = PHI_COUNTER();

    CHECK(first != second);
}
