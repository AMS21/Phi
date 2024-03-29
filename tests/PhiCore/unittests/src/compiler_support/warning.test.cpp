#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/warning.hpp>

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4800)
PHI_MSVC_SUPPRESS_WARNING_POP()

PHI_MSVC_SUPPRESS_WARNING_WITH_PUSH(4800)
PHI_MSVC_SUPPRESS_WARNING_POP()

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wextra")
PHI_CLANG_SUPPRESS_WARNING_POP()

PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wextra")
PHI_CLANG_SUPPRESS_WARNING_POP()

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wextra")
PHI_GCC_SUPPRESS_WARNING_POP()

PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wextra")
PHI_GCC_SUPPRESS_WARNING_POP()

PHI_CLANG_AND_GCC_SUPPRESS_WARNING_PUSH()
PHI_CLANG_AND_GCC_SUPPRESS_WARNING("-Wextra")
PHI_CLANG_AND_GCC_SUPPRESS_WARNING_POP()

PHI_CLANG_AND_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wextra")
PHI_CLANG_AND_GCC_SUPPRESS_WARNING_POP()

PHI_EMCC_SUPPRESS_WARNING_PUSH()
PHI_EMCC_SUPPRESS_WARNING("-Wextra")
PHI_EMCC_SUPPRESS_WARNING_POP()

PHI_EMCC_SUPPRESS_WARNING_WITH_PUSH("-Wextra")
PHI_EMCC_SUPPRESS_WARNING_POP()

PHI_EXTERNAL_HEADERS_BEGIN()
PHI_EXTERNAL_HEADERS_END()

TEST_CASE("Warning.CompilerWarning")
{
#if !defined(PHI_CONFIG_WARNINGS_AS_ERRORS) || PHI_COMPILER_IS(CLANG)
    PHI_COMPILER_WARNING("Test warning")
#endif
}
