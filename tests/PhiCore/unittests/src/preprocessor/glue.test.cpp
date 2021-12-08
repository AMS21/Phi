#include <phi/test/test_macros.hpp>

#include <phi/preprocessor/glue.hpp>

TEST_CASE("Glue")
{
    int PHI_GLUE(int_, var) = 3;

    int_var = 5;
    CHECK(int_var == 5);
}
