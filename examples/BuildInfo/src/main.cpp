#include <Phi/Config/CPlusPlus.hpp>
#include <Phi/Config/Compiler.hpp>
#include <Phi/Config/FunctionLikeMacro.hpp>
#include <Phi/Config/Platform.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#define PRINT_COND(text, cond)                                                                     \
    PHI_BEGIN_MACRO()                                                                              \
    if (cond)                                                                                      \
    {                                                                                              \
        logger->info(text ": true");                                                               \
    }                                                                                              \
    else                                                                                           \
    {                                                                                              \
        logger->error(text ": false");                                                             \
    }                                                                                              \
    PHI_END_MACRO()

int main()
{
    // Setup
    auto logger = spdlog::stdout_color_st("out");

    logger->set_pattern("%^%v%$");

    // Compiler
    logger->trace("Compiler info");

    PRINT_COND("Compiler is gcc", PHI_COMPILER_IS(GCC));
    PRINT_COND("Compiler is clang", PHI_COMPILER_IS(CLANG));
    PRINT_COND("Compiler is MSVC", PHI_COMPILER_IS(MSVC));
    PRINT_COND("Compiler is ICC", PHI_COMPILER_IS(ICC));
    PRINT_COND("Compiler is emcc", PHI_COMPILER_IS(EMCC));
    PRINT_COND("Compiler is mingw", PHI_COMPILER_IS(MINGW));

    PRINT_COND("Compiler is gcc compat", PHI_COMPILER_IS(GCC_COMPAT));
    PRINT_COND("Compiler is clang compat", PHI_COMPILER_IS(CLANG_COMPAT));

    // CPlusPlus
    logger->trace("Enabled C++ standards");

    PRINT_COND("C++-98 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(98));
    PRINT_COND("C++-11 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(11));
    PRINT_COND("C++-14 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(14));
    PRINT_COND("C++-17 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(17));
    PRINT_COND("C++-20 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(20));

    // Platform
    logger->trace("Platform info");

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
