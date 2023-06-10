#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/cpp_standard.hpp>
#include <phi/compiler_support/platform.hpp>
#include <phi/compiler_support/standard_library.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/container/string_view.hpp>
#include <phi/preprocessor/function_like_macro.hpp>
#include <phi/preprocessor/stringify.hpp>
#include <cstdio>

PHI_MSVC_SUPPRESS_WARNING(4127) // conditional expression is constant
PHI_MSVC_SUPPRESS_WARNING(
        4476) // 'function' : unknown type field character 'character' in format specifier

void print_cond(phi::string_view data, bool cond)
{
    (void)std::printf("%s: %s\n", data.data(), cond ? "true" : "false");
}

void print_val(phi::string_view text, int val)
{
    (void)std::printf("%s: %d\n", text.data(), val);
}

void print_val(phi::string_view text, long val)
{
    (void)std::printf("%s: %ld\n", text.data(), val);
}

void print_val(phi::string_view text, phi::string_view val)
{
    (void)std::printf("%s: %s\n", text.data(), val.data());
}

int main()
{
    // Compiler
    (void)std::printf("Compiler info\n");

    print_val("Compiler name", PHI_COMPILER_NAME());
    print_val("Compiler version", PHI_CURRENT_COMPILER_VERSION_STR());

    print_cond("Compiler is gcc", PHI_COMPILER_IS(GCC));
    print_cond("Compiler is clang", PHI_COMPILER_IS(CLANG));
    print_cond("Compiler is AppleClang", PHI_COMPILER_IS(APPLECLANG));
    print_cond("Compiler is WinClang", PHI_COMPILER_IS(WINCLANG));
    print_cond("Compiler is MSVC", PHI_COMPILER_IS(MSVC));
    print_cond("Compiler is ICC", PHI_COMPILER_IS(ICC));
    print_cond("Compiler is emcc", PHI_COMPILER_IS(EMCC));
    print_cond("Compiler is mingw", PHI_COMPILER_IS(MINGW));
    print_cond("Compiler is Cheerp", PHI_COMPILER_IS(CHEERP));

    print_cond("Compiler is gcc compat", PHI_COMPILER_IS(GCC_COMPAT));
    print_cond("Compiler is clang compat", PHI_COMPILER_IS(CLANG_COMPAT));

    // CPlusPlus
    (void)std::printf("\nEnabled C++ standards\n");

    print_val("PHI_CPP_STANDARD", PHI_CPP_STANDARD());
    print_val("PHI_CPLUSPLUS_LATEST", PHI_CPLUSPLUS_LATEST());

    print_cond("C++-98 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(98));
    print_cond("C++-11 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(11));
    print_cond("C++-14 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(14));
    print_cond("C++-17 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(17));
    print_cond("C++-20 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(20));
    print_cond("C++-23 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(23));
    print_cond("C++-26 Standard enabled", PHI_CPP_STANDARD_IS_ATLEAST(26));

    // Platform
    (void)std::printf("\nPlatform info\n");

    print_cond("Platform is Windows", PHI_PLATFORM_IS(WINDOWS));
    print_cond("Platform is Apple", PHI_PLATFORM_IS(APPLE));
    print_cond("Platform is MacOS", PHI_PLATFORM_IS(MACOS));
    print_cond("Platform is Linux", PHI_PLATFORM_IS(LINUX));
    print_cond("Platform is Android", PHI_PLATFORM_IS(ANDROID));
    print_cond("Platform is BSD", PHI_PLATFORM_IS(BSD));
    print_cond("Platform is FreeBSD", PHI_PLATFORM_IS(FREEBSD));
    print_cond("Platform is OpenBSD", PHI_PLATFORM_IS(OPENBSD));
    print_cond("Platform is Solaris", PHI_PLATFORM_IS(SOLARIS));
    print_cond("Platform is iOS", PHI_PLATFORM_IS(IOS));
    print_cond("Platform is iOS simulator", PHI_PLATFORM_IS(IOS_SIMULATOR));
    print_cond("Platform is Unix", PHI_PLATFORM_IS(UNIX));
    print_cond("Platform is DOS", PHI_PLATFORM_IS(DOS));
    print_cond("Platform is Web", PHI_PLATFORM_IS(WEB));

    // Standard library
    (void)std::printf("\nStandard library info\n");

    print_cond("Standard library libc++ ", PHI_STANDARD_LIBRARY_LIBCXX());
    print_cond("Standard library libstdc++", PHI_STANDARD_LIBRARY_LIBSTDCXX());
    print_cond("Standard library msvc-stl", PHI_STANDARD_LIBRARY_MSVC());
    print_val("PHI_STANDARD_LIBRARY_NAME", PHI_STANDARD_LIBRARY_NAME());
    print_val("PHI_STANDARD_LIBRARY_DATE", PHI_STANDARD_LIBRARY_DATE());
    print_val("PHI_STANDARD_LIBRARY_VERSION_MAJOR", PHI_STANDARD_LIBRARY_VERSION_MAJOR());
    print_val("PHI_STANDARD_LIBRARY_VERSION_MINOR", PHI_STANDARD_LIBRARY_VERSION_MINOR());
    print_val("PHI_STANDARD_LIBRARY_VERSION_PATCH", PHI_STANDARD_LIBRARY_VERSION_PATCH());

    return 0;
}
