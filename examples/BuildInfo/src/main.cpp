#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/cpp_standard.hpp>
#include <phi/compiler_support/platform.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/preprocessor/function_like_macro.hpp>

PHI_CLANG_SUPPRESS_WARNING_PUSH()
#if PHI_COMPILER_IS_ATLEAST(CLANG, 13, 0, 0)
PHI_CLANG_SUPPRESS_WARNING("-Wreserved-macro-identifier")
#else
PHI_CLANG_SUPPRESS_WARNING("-Wreserved-id-macro")
#endif

#ifndef __STDC_WANT_SECURE_LIB__
#    define __STDC_WANT_SECURE_LIB__ 1
#endif
#include <iostream>

PHI_CLANG_SUPPRESS_WARNING_POP()

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4127) // conditional expression is constant

#define PRINT_COND(text, cond)                                                                     \
    PHI_BEGIN_MACRO()                                                                              \
    if (cond)                                                                                      \
    {                                                                                              \
        std::cout << text << ": true\n";                                                           \
    }                                                                                              \
    else                                                                                           \
    {                                                                                              \
        std::cout << text << ": false\n";                                                          \
    }                                                                                              \
    PHI_END_MACRO()

#define PRINT_VAL(text, val)                                                                       \
    PHI_BEGIN_MACRO()                                                                              \
    std::cout << text << ": " << val << '\n';                                                      \
    PHI_END_MACRO()

int main()
{
    // Compiler
    std::cout << "Compiler info\n";

    PRINT_VAL("Compiler name", PHI_COMPILER_NAME());
    PRINT_VAL("Compiler version", PHI_CURRENT_COMPILER_VERSION_STR());

    PRINT_COND("Compiler is gcc", PHI_COMPILER_IS(GCC));
    PRINT_COND("Compiler is clang", PHI_COMPILER_IS(CLANG));
    PRINT_COND("Compiler is appleclang", PHI_COMPILER_IS(APPLECLANG));
    PRINT_COND("Compiler is winclang", PHI_COMPILER_IS(WINCLANG));
    PRINT_COND("Compiler is MSVC", PHI_COMPILER_IS(MSVC));
    PRINT_COND("Compiler is ICC", PHI_COMPILER_IS(ICC));
    PRINT_COND("Compiler is emcc", PHI_COMPILER_IS(EMCC));
    PRINT_COND("Compiler is mingw", PHI_COMPILER_IS(MINGW));

    PRINT_COND("Compiler is gcc compat", PHI_COMPILER_IS(GCC_COMPAT));
    PRINT_COND("Compiler is clang compat", PHI_COMPILER_IS(CLANG_COMPAT));

    // CPlusPlus
    std::cout << "Enabled C++ standards\n";
    PRINT_VAL("PHI_CPP_STANDARD", PHI_CPP_STANDARD());
    PRINT_VAL("PHI_CPLUSPLUS_LATEST", PHI_CPLUSPLUS_LATEST());

    PRINT_COND("C++-98 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(98));
    PRINT_COND("C++-11 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(11));
    PRINT_COND("C++-14 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(14));
    PRINT_COND("C++-17 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(17));
    PRINT_COND("C++-20 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(20));
    PRINT_COND("C++-23 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(23));

    // Platform
    std::cout << "Platform info\n";

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

    return 0;
}

PHI_MSVC_SUPPRESS_WARNING_POP()
