#include <phi/test/test_macros.hpp>

#include <phi/preprocessor/function_like_macro.hpp>

#define FN_TEST()                                                                                  \
    PHI_BEGIN_MACRO()                                                                              \
    int integer2 = 3;                                                                              \
    integer      = integer2;                                                                       \
    PHI_END_MACRO()

#define FN_TEST_2() PHI_EMPTY_MACRO()

TEST_CASE("FunctionLikeMacro", "[Config][FunctionLikeMacro]")
{
    int integer = 0;

    REQUIRE(integer == 0);

    FN_TEST();

    CHECK(integer == 3);

    FN_TEST_2();

    int integer2 = 42;
    CHECK(integer2 == 42);
}
