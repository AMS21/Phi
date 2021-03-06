#include <catch2/catch_test_macros.hpp>

#include <Phi/Config/Warning.hpp>

TEST_CASE("Warning.Clang", "[Config][Warning]")
{
    PHI_CLANG_SUPPRESS_WARNING_PUSH();
    PHI_CLANG_SUPPRESS_WARNING("-Wextra");
    PHI_CLANG_SUPPRESS_WARNING_POP();

    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wextra");
    PHI_CLANG_SUPPRESS_WARNING_POP();
}

TEST_CASE("Warning.GCC", "[Config][Warning]")
{
    PHI_GCC_SUPPRESS_WARNING_PUSH();
    PHI_GCC_SUPPRESS_WARNING("-Wextra");
    PHI_GCC_SUPPRESS_WARNING_POP();

    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wextra");
    PHI_GCC_SUPPRESS_WARNING_POP();
}

TEST_CASE("Warning.MSVC", "[Config][Warning]")
{
    PHI_MSVC_SUPPRESS_WARNING_PUSH();
    PHI_MSVC_SUPPRESS_WARNING(4800);
    PHI_MSVC_SUPPRESS_WARNING_POP();

    PHI_MSVC_SUPPRESS_WARNING_WITH_PUSH(4800);
    PHI_MSVC_SUPPRESS_WARNING_POP();
}

TEST_CASE("Warning.CompilerWarning", "[Config][Warning]")
{
    PHI_COMPILER_WARNING("Test warning");
}
