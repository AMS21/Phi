#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/assume.hpp>

TEST_CASE("assume", "[Config][Assume]")
{
    PHI_ASSUME(42 % 2 == 0);
    PHI_ASSUME(31 % 2 == 1);
}
