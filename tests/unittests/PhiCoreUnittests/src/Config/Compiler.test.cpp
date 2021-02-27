#include <catch2/catch_test_macros.hpp>

#include <Phi/Config/Compiler.hpp>

TEST_CASE("Config Compiler", "[Config][Compiler]")
{
#if PHI_COMPILER_IS(CLANG)
    STATIC_REQUIRE(PHI_COMPILER_CLANG());
#endif
#if PHI_COMPILER_IS(GCC)
    STATIC_REQUIRE(PHI_COMPILER_GCC());
#endif
#if PHI_COMPILER_IS(MSVC)
    STATIC_REQUIRE(PHI_COMPILER_MSVC());
#endif
#if PHI_COMPILER_IS(MINGW)
    STATIC_REQUIRE(PHI_COMPILER_MINGW());
#endif
#if PHI_COMPILER_IS(EMCC)
    STATIC_REQUIRE(PHI_COMPILER_EMCC());
#endif
}
