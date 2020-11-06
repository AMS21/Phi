#include <catch2/catch_test_macros.hpp>

#include <Phi/Config/Glue.hpp>

TEST_CASE("Glue")
{
    int PHI_GLUE(int_, var) = 3;

    int_var = 5;
    CHECK(int_var == 5);
}
