#include <catch2/catch.hpp>

#include <Phi/Config/FunctionLikeMacro.hpp>

#define FN_TEST()                                                                                  \
    PHI_BEGIN_MACRO()                                                                              \
    int i = 3;                                                                                     \
    PHI_END_MACRO()

#define FN_TEST_2() PHI_EMPTY_MACRO()

TEST_CASE("FunctionLikeMacro", "[Config][FunctionLikeMacro]")
{
    FN_TEST();

    FN_TEST_2();

    int i = 42;
    CHECK(i == 42);
}
