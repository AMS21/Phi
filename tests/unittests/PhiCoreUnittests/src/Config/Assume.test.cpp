#include <catch2/catch_test_macros.hpp>

#include <Phi/Config/Assume.hpp>

TEST_CASE("assume", "[Config][Assume]")
{
    PHI_ASSUME(42 % 2 == 0);
    PHI_ASSUME(31 % 2 == 1);
}
