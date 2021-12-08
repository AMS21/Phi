#include <phi/test/test_macros.hpp>

#include <phi/preprocessor/function_like_macro.hpp>

#define FN_TEST()                                                                                  \
    PHI_BEGIN_MACRO()                                                                              \
    int i = 3;                                                                                     \
    j     = i;                                                                                     \
    PHI_END_MACRO()

#define FN_TEST_2() PHI_EMPTY_MACRO()

TEST_CASE("FunctionLikeMacro", "[Config][FunctionLikeMacro]")
{
    int j = 0;

    REQUIRE(j == 0);

    FN_TEST();

    CHECK(j == 3);

    FN_TEST_2();

    int i = 42;
    CHECK(i == 42);
}
