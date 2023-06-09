#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/cpp_standard.hpp>
#include <phi/compiler_support/platform.hpp>
#include <phi/compiler_support/standard_library.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/preprocessor/function_like_macro.hpp>
#include <phi/preprocessor/stringify.hpp>
#include <cstdio>

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4127) // conditional expression is constant

#define PRINT_COND(text, cond)                                                                     \
    PHI_BEGIN_MACRO()                                                                              \
    if (cond)                                                                                      \
    {                                                                                              \
        std::printf(text ": true\n");                                                              \
    }                                                                                              \
    else                                                                                           \
    {                                                                                              \
        std::printf(text ": false\n");                                                             \
    }                                                                                              \
    PHI_END_MACRO()

#define PRINT_VAL(text, val)                                                                       \
    PHI_BEGIN_MACRO()                                                                              \
    std::printf(text ": " PHI_STRINGIFY(val) "\n");                                                \
    PHI_END_MACRO()

#define PRINT_STR(text, str)                                                                       \
    PHI_BEGIN_MACRO()                                                                              \
    std::printf(text ": " str "\n");                                                               \
    PHI_END_MACRO()

int main()
{
    // Compiler
    std::printf("Compiler info\n");

    PRINT_STR("Compiler name", PHI_COMPILER_NAME());
    PRINT_STR("Compiler version", PHI_CURRENT_COMPILER_VERSION_STR());

    PRINT_COND("Compiler is gcc", PHI_COMPILER_IS(GCC));
    PRINT_COND("Compiler is clang", PHI_COMPILER_IS(CLANG));
    PRINT_COND("Compiler is AppleClang", PHI_COMPILER_IS(APPLECLANG));
    PRINT_COND("Compiler is WinClang", PHI_COMPILER_IS(WINCLANG));
    PRINT_COND("Compiler is MSVC", PHI_COMPILER_IS(MSVC));
    PRINT_COND("Compiler is ICC", PHI_COMPILER_IS(ICC));
    PRINT_COND("Compiler is emcc", PHI_COMPILER_IS(EMCC));
    PRINT_COND("Compiler is mingw", PHI_COMPILER_IS(MINGW));
    PRINT_COND("Compiler is Cheerp", PHI_COMPILER_IS(CHEERP));

    PRINT_COND("Compiler is gcc compat", PHI_COMPILER_IS(GCC_COMPAT));
    PRINT_COND("Compiler is clang compat", PHI_COMPILER_IS(CLANG_COMPAT));

    // CPlusPlus
    std::printf("\nEnabled C++ standards\n");
    PRINT_VAL("PHI_CPP_STANDARD", PHI_CPP_STANDARD());
    PRINT_VAL("PHI_CPLUSPLUS_LATEST", PHI_CPLUSPLUS_LATEST());

    PRINT_COND("C++-98 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(98));
    PRINT_COND("C++-11 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(11));
    PRINT_COND("C++-14 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(14));
    PRINT_COND("C++-17 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(17));
    PRINT_COND("C++-20 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(20));
    PRINT_COND("C++-23 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(23));
    PRINT_COND("C++-26 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(26));

    // Platform
    std::printf("\nPlatform info\n");

    PRINT_COND("Platform is Windows", PHI_PLATFORM_IS(WINDOWS));
    PRINT_COND("Platform is Apple", PHI_PLATFORM_IS(APPLE));
    PRINT_COND("Platform is MacOS", PHI_PLATFORM_IS(MACOS));
    PRINT_COND("Platform is Linux", PHI_PLATFORM_IS(LINUX));
    PRINT_COND("Platform is Android", PHI_PLATFORM_IS(ANDROID));
    PRINT_COND("Platform is BSD", PHI_PLATFORM_IS(BSD));
    PRINT_COND("Platform is FreeBSD", PHI_PLATFORM_IS(FREEBSD));
    PRINT_COND("Platform is OpenBSD", PHI_PLATFORM_IS(OPENBSD));
    PRINT_COND("Platform is Solaris", PHI_PLATFORM_IS(SOLARIS));
    PRINT_COND("Platform is iOS", PHI_PLATFORM_IS(IOS));
    PRINT_COND("Platform is iOS simulator", PHI_PLATFORM_IS(IOS_SIMULATOR));
    PRINT_COND("Platform is Unix", PHI_PLATFORM_IS(UNIX));
    PRINT_COND("Platform is DOS", PHI_PLATFORM_IS(DOS));
    PRINT_COND("Platform is Web", PHI_PLATFORM_IS(WEB));

    // Standard library
    std::printf("\nStandard library info\n");

    PRINT_COND("Standard library libc++ ", PHI_STANDARD_LIBRARY_LIBCXX());
    PRINT_COND("Standard library libstdc++", PHI_STANDARD_LIBRARY_LIBSTDCXX());
    PRINT_COND("Standard library msvc-stl", PHI_STANDARD_LIBRARY_MSVC());
    PRINT_STR("PHI_STANDARD_LIBRARY_NAME", PHI_STANDARD_LIBRARY_NAME());
    PRINT_VAL("PHI_STANDARD_LIBRARY_DATE", PHI_STANDARD_LIBRARY_DATE());
    PRINT_VAL("PHI_STANDARD_LIBRARY_VERSION_MAJOR", PHI_STANDARD_LIBRARY_VERSION_MAJOR());
    PRINT_VAL("PHI_STANDARD_LIBRARY_VERSION_MINOR", PHI_STANDARD_LIBRARY_VERSION_MINOR());
    PRINT_VAL("PHI_STANDARD_LIBRARY_VERSION_PATCH", PHI_STANDARD_LIBRARY_VERSION_PATCH());

    return 0;
}

PHI_MSVC_SUPPRESS_WARNING_POP()
