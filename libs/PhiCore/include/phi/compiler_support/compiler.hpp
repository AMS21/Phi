/*!
 * \file Compiler.hpp
 * \brief Defines macros to determine the compiler
 *        and the version of the compiler being used.
 *
**/
#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_COMPILER_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_COMPILER_HPP

#include "phi/compiler_support/platform.hpp"
#include "phi/preprocessor/glue.hpp"
#include "phi/preprocessor/stringify.hpp"
#include "phi/preprocessor/versioning.hpp" // PHI_VERSION_CREATE

#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) ||                               \
        defined(__INTEL_COMPILER_UPDATE) || defined(__INTEL_CLANG_COMPILER) ||                     \
        defined(__INTEL_LLVM_COMPILER)
#    define PHI_COMPILER_ICC()      1
#    define PHI_ICC_VERSION_MAJOR() (__INTEL_COMPILER / 100)
#    define PHI_ICC_VERSION_MINOR() (__INTEL_COMPILER % 100 / 10)
#    define PHI_ICC_VERSION_PATCH() (__INTEL_COMPILER % 10)
#else
#    define PHI_COMPILER_ICC()      0
#    define PHI_ICC_VERSION_MAJOR() 0
#    define PHI_ICC_VERSION_MINOR() 0
#    define PHI_ICC_VERSION_PATCH() 0
#endif

#if defined(__EMSCRIPTEN__)
// NOTE: Since emscripten 3.1.23 the '__EMSCRIPTEN_major/minor/tiny__' macros are only available from the <emscripten/version.h> header file
// https://github.com/emscripten-core/emscripten/commit/f99af02045357d3d8b12e63793cef36dfde4530a
// https://github.com/emscripten-core/emscripten/commit/f76ddc702e4956aeedb658c49790cc352f892e4c

// Only include the header if it's actually needed
#    if !defined(__EMSCRIPTEN_major__)
#        include <emscripten/version.h>
#    endif

#    define PHI_COMPILER_EMCC()      1
#    define PHI_EMCC_VERSION_MAJOR() __EMSCRIPTEN_major__
#    define PHI_EMCC_VERSION_MINOR() __EMSCRIPTEN_minor__
#    define PHI_EMCC_VERSION_PATCH() __EMSCRIPTEN_tiny__
#else
#    define PHI_COMPILER_EMCC()      0
#    define PHI_EMCC_VERSION_MAJOR() 0
#    define PHI_EMCC_VERSION_MINOR() 0
#    define PHI_EMCC_VERSION_PATCH() 0
#endif

// Clang on windows also defines the _MSC_VER macro
#if defined(_MSC_VER) && !defined(__clang__)
#    define PHI_COMPILER_MSVC()      1
#    define PHI_MSVC_VERSION_MAJOR() (_MSC_FULL_VER / 10000000)
#    define PHI_MSVC_VERSION_MINOR() (_MSC_FULL_VER % 10000000 / 100000)
#    define PHI_MSVC_VERSION_PATCH() (_MSC_FULL_VER % 100000)
#else
#    define PHI_COMPILER_MSVC()      0
#    define PHI_MSVC_VERSION_MAJOR() 0
#    define PHI_MSVC_VERSION_MINOR() 0
#    define PHI_MSVC_VERSION_PATCH() 0
#endif

#if defined(__MINGW32__) || defined(__MINGW64__)
#    include "stdlib.h" // Needed for version information
#    define PHI_COMPILER_MINGW()      1
#    define PHI_MINGW_VERSION_MAJOR() __MINGW32_MAJOR_VERSION
#    define PHI_MINGW_VERSION_MINOR() __MINGW32_MINOR_VERSION
#    define PHI_MINGW_VERSION_PATCH() 0 // no patch version defined for MingW
#else
#    define PHI_COMPILER_MINGW()      0
#    define PHI_MINGW_VERSION_MAJOR() 0
#    define PHI_MINGW_VERSION_MINOR() 0
#    define PHI_MINGW_VERSION_PATCH() 0
#endif

#if defined(__clang__) && defined(__apple_build_version__) && !PHI_COMPILER_EMCC()
#    define PHI_COMPILER_APPLECLANG()      1
#    define PHI_APPLECLANG_VERSION_MAJOR() __clang_major__
#    define PHI_APPLECLANG_VERSION_MINOR() __clang_minor__
#    define PHI_APPLECLANG_VERSION_PATCH() __clang_patchlevel__
#else
#    define PHI_COMPILER_APPLECLANG()      0
#    define PHI_APPLECLANG_VERSION_MAJOR() 0
#    define PHI_APPLECLANG_VERSION_MINOR() 0
#    define PHI_APPLECLANG_VERSION_PATCH() 0
#endif

#if defined(__clang__) && !PHI_COMPILER_EMCC() && !PHI_COMPILER_APPLECLANG()
#    define PHI_COMPILER_CLANG()      1
#    define PHI_CLANG_VERSION_MAJOR() __clang_major__
#    define PHI_CLANG_VERSION_MINOR() __clang_minor__
#    define PHI_CLANG_VERSION_PATCH() __clang_patchlevel__
#else
#    define PHI_COMPILER_CLANG()      0
#    define PHI_CLANG_VERSION_MAJOR() 0
#    define PHI_CLANG_VERSION_MINOR() 0
#    define PHI_CLANG_VERSION_PATCH() 0
#endif

#if PHI_COMPILER_CLANG() && PHI_PLATFORM_IS(WINDOWS)
#    define PHI_COMPILER_WINCLANG()      1
#    define PHI_WINCLANG_VERSION_MAJOR() __clang_major__
#    define PHI_WINCLANG_VERSION_MINOR() __clang_minor__
#    define PHI_WINCLANG_VERSION_PATCH() __clang_patchlevel__
#else
#    define PHI_COMPILER_WINCLANG()      0
#    define PHI_WINCLANG_VERSION_MAJOR() 0
#    define PHI_WINCLANG_VERSION_MINOR() 0
#    define PHI_WINCLANG_VERSION_PATCH() 0
#endif

#if (defined(__GNUC__) || defined(__GNUG__)) &&                                                    \
        (!PHI_COMPILER_CLANG() && !PHI_COMPILER_EMCC() && !PHI_COMPILER_APPLECLANG())
#    define PHI_COMPILER_GCC()      1
#    define PHI_GCC_VERSION_MAJOR() __GNUC__
#    define PHI_GCC_VERSION_MINOR() __GNUC_MINOR__
#    define PHI_GCC_VERSION_PATCH() __GNUC_PATCHLEVEL__
#else
#    define PHI_COMPILER_GCC()      0
#    define PHI_GCC_VERSION_MAJOR() 0
#    define PHI_GCC_VERSION_MINOR() 0
#    define PHI_GCC_VERSION_PATCH() 0
#endif

// Compiler compatibility

#if (defined(__GNUC__) || defined(__GNUG__))
#    define PHI_COMPILER_GCC_COMPAT()      1
#    define PHI_GCC_COMPAT_VERSION_MAJOR() __GNUC__
#    define PHI_GCC_COMPAT_VERSION_MINOR() __GNUC_MINOR__
#    define PHI_GCC_COMPAT_VERSION_PATCH() __GNUC_PATCHLEVEL__
#else
#    define PHI_COMPILER_GCC_COMPAT()      0
#    define PHI_GCC_COMPAT_VERSION_MAJOR() 0
#    define PHI_GCC_COMPAT_VERSION_MINOR() 0
#    define PHI_GCC_COMPAT_VERSION_PATCH() 0
#endif

#if defined(__clang__)
#    define PHI_COMPILER_CLANG_COMPAT()      1
#    define PHI_CLANG_COMPAT_VERSION_MAJOR() __clang_major__
#    define PHI_CLANG_COMPAT_VERSION_MINOR() __clang_minor__
#    define PHI_CLANG_COMPAT_VERSION_PATCH() __clang_patchlevel__
#else
#    define PHI_COMPILER_CLANG_COMPAT()      0
#    define PHI_CLANG_COMPAT_VERSION_MAJOR() 0
#    define PHI_CLANG_COMPAT_VERSION_MINOR() 0
#    define PHI_CLANG_COMPAT_VERSION_PATCH() 0
#endif

#define PHI_COMPILER_VERSION(compiler)                                                             \
    (PHI_VERSION_CREATE(PHI_##compiler##_VERSION_MAJOR(), PHI_##compiler##_VERSION_MINOR(),        \
                        PHI_##compiler##_VERSION_PATCH()))

#define PHI_COMPILER_VERSION_MAJOR(compiler) PHI_##compiler##_VERSION_MAJOR()

#define PHI_COMPILER_VERSION_MINOR(compiler) PHI_##compiler##_VERSION_MINOR()

#define PHI_COMPILER_VERSION_PATCH(compiler) PHI_##compiler##_VERSION_PATCH()

#define PHI_COMPILER_IS(compiler) (PHI_COMPILER_##compiler())

#define PHI_COMPILER_IS_NOT(compiler) (!PHI_COMPILER_IS(compiler))

#define PHI_COMPILER_IS_ATLEAST(compiler, major, minor, patch)                                     \
    (PHI_COMPILER_IS(compiler) &&                                                                  \
     (PHI_VERSION_CREATE(major, minor, patch) <= PHI_COMPILER_VERSION(compiler)))

#define PHI_COMPILER_IS_BELOW(compiler, major, minor, patch)                                       \
    (PHI_COMPILER_IS(compiler) &&                                                                  \
     (PHI_VERSION_CREATE(major, minor, patch) > PHI_COMPILER_VERSION(compiler)))

#define PHI_COMPILER_WORKAROUND(compiler, major, minor, patch)                                     \
    (PHI_COMPILER_IS_NOT(compiler) ||                                                              \
     (PHI_VERSION_CREATE(major, minor, patch) <= PHI_COMPILER_VERSION(compiler)))

// Compiler name and version
#if PHI_COMPILER_IS(EMCC)
#    define PHI_COMPILER_NAME()                  "Emscripten"
#    define PHI_CURRENT_COMPILER_VERSION()       PHI_COMPILER_VERSION(EMCC)
#    define PHI_CURRENT_COMPILER_VERSION_MAJOR() PHI_COMPILER_VERSION_MAJOR(EMCC)
#    define PHI_CURRENT_COMPILER_VERSION_MINOR() PHI_COMPILER_VERSION_MINOR(EMCC)
#    define PHI_CURRENT_COMPILER_VERSION_PATCH() PHI_COMPILER_VERSION_PATCH(EMCC)
#elif PHI_COMPILER_IS(ICC)
#    define PHI_COMPILER_NAME()                  "Intel ICC"
#    define PHI_CURRENT_COMPILER_VERSION()       PHI_COMPILER_VERSION(ICC)
#    define PHI_CURRENT_COMPILER_VERSION_MAJOR() PHI_COMPILER_VERSION_MAJOR(ICC)
#    define PHI_CURRENT_COMPILER_VERSION_MINOR() PHI_COMPILER_VERSION_MINOR(ICC)
#    define PHI_CURRENT_COMPILER_VERSION_PATCH() PHI_COMPILER_VERSION_PATCH(ICC)
#elif PHI_COMPILER_IS(MSVC)
#    define PHI_COMPILER_NAME()                  "MSVC"
#    define PHI_CURRENT_COMPILER_VERSION()       PHI_COMPILER_VERSION(MSVC)
#    define PHI_CURRENT_COMPILER_VERSION_MAJOR() PHI_COMPILER_VERSION_MAJOR(MSVC)
#    define PHI_CURRENT_COMPILER_VERSION_MINOR() PHI_COMPILER_VERSION_MINOR(MSVC)
#    define PHI_CURRENT_COMPILER_VERSION_PATCH() PHI_COMPILER_VERSION_PATCH(MSVC)
#elif PHI_COMPILER_IS(MINGW)
#    if defined(__MINGW64__) || defined(__MINGW64_VERSION_MAJOR) || defined(__MINGW64_VERSION_MINOR)
#        define PHI_COMPILER_NAME() "MinGW64"
#    else
#        define PHI_COMPILER_NAME() "MinGW32"
#    endif
#    define PHI_CURRENT_COMPILER_VERSION()       PHI_COMPILER_VERSION(MINGW)
#    define PHI_CURRENT_COMPILER_VERSION_MAJOR() PHI_COMPILER_VERSION_MAJOR(MINGW)
#    define PHI_CURRENT_COMPILER_VERSION_MINOR() PHI_COMPILER_VERSION_MINOR(MINGW)
#    define PHI_CURRENT_COMPILER_VERSION_PATCH() PHI_COMPILER_VERSION_PATCH(MINGW)
#elif PHI_COMPILER_APPLECLANG()
#    define PHI_COMPILER_NAME()                  "AppleClang"
#    define PHI_CURRENT_COMPILER_VERSION()       PHI_COMPILER_VERSION(APPLECLANG)
#    define PHI_CURRENT_COMPILER_VERSION_MAJOR() PHI_COMPILER_VERSION_MAJOR(APPLECLANG)
#    define PHI_CURRENT_COMPILER_VERSION_MINOR() PHI_COMPILER_VERSION_MINOR(APPLECLANG)
#    define PHI_CURRENT_COMPILER_VERSION_PATCH() PHI_COMPILER_VERSION_PATCH(APPLECLANG)
#elif PHI_COMPILER_WINCLANG()
#    define PHI_COMPILER_NAME()                  "WinClang"
#    define PHI_CURRENT_COMPILER_VERSION()       PHI_COMPILER_VERSION(WINCLANG)
#    define PHI_CURRENT_COMPILER_VERSION_MAJOR() PHI_COMPILER_VERSION_MAJOR(WINCLANG)
#    define PHI_CURRENT_COMPILER_VERSION_MINOR() PHI_COMPILER_VERSION_MINOR(WINCLANG)
#    define PHI_CURRENT_COMPILER_VERSION_PATCH() PHI_COMPILER_VERSION_PATCH(WINCLANG)
#elif PHI_COMPILER_IS(CLANG)
#    define PHI_COMPILER_NAME()                  "Clang"
#    define PHI_CURRENT_COMPILER_VERSION()       PHI_COMPILER_VERSION(CLANG)
#    define PHI_CURRENT_COMPILER_VERSION_MAJOR() PHI_COMPILER_VERSION_MAJOR(CLANG)
#    define PHI_CURRENT_COMPILER_VERSION_MINOR() PHI_COMPILER_VERSION_MINOR(CLANG)
#    define PHI_CURRENT_COMPILER_VERSION_PATCH() PHI_COMPILER_VERSION_PATCH(CLANG)
#elif PHI_COMPILER_IS(GCC)
#    define PHI_COMPILER_NAME()                  "GCC"
#    define PHI_CURRENT_COMPILER_VERSION()       PHI_COMPILER_VERSION(GCC)
#    define PHI_CURRENT_COMPILER_VERSION_MAJOR() PHI_COMPILER_VERSION_MAJOR(GCC)
#    define PHI_CURRENT_COMPILER_VERSION_MINOR() PHI_COMPILER_VERSION_MINOR(GCC)
#    define PHI_CURRENT_COMPILER_VERSION_PATCH() PHI_COMPILER_VERSION_PATCH(GCC)
#else
#    define PHI_COMPILER_NAME()                  "Unknown"
#    define PHI_CURRENT_COMPILER_VERSION()       PHI_VERSION_CREATE(0, 0, 0)
#    define PHI_CURRENT_COMPILER_VERSION_MAJOR() PHI_COMPILER_VERSION_MAJOR(0)
#    define PHI_CURRENT_COMPILER_VERSION_MINOR() PHI_COMPILER_VERSION_MINOR(0)
#    define PHI_CURRENT_COMPILER_VERSION_PATCH() PHI_COMPILER_VERSION_PATCH(0)
#endif

#define PHI_CURRENT_COMPILER_VERSION_STR()                                                         \
    PHI_STRINGIFY(PHI_CURRENT_COMPILER_VERSION_MAJOR())                                            \
    "." PHI_STRINGIFY(PHI_CURRENT_COMPILER_VERSION_MINOR()) "." PHI_STRINGIFY(                     \
            PHI_CURRENT_COMPILER_VERSION_MINOR())

// has attribute
#if defined(__has_attribute)
#    define PHI_HAS_ATTRIBUTE(attribute) __has_attribute(attribute)
#else
#    define PHI_HAS_ATTRIBUTE(attribute) (0)
#endif

// has builtin
#if defined(__has_builtin)
#    define PHI_HAS_BUILTIN(builtin) __has_builtin(builtin)
#else
#    define PHI_HAS_BUILTIN(builtin) (0)
#endif

// has declspec attribute
#if defined(__has_declspec_attribute)
#    define PHI_HAS_DECLSPEC_ATTRIBUTE(attribute) __has_declspec_attribute(attribute)
#else
#    define PHI_HAS_DECLSPEC_ATTRIBUTE(attribute) (0)
#endif

// has feature
#if defined(__has_feature)
#    define PHI_HAS_FEATURE(feature) __has_feature(feature)
#else
#    define PHI_HAS_FEATURE(feature) (0)
#endif

// has extension
#if defined(__has_extension)
#    define PHI_HAS_EXTENSION(extension) __has_extension(extension)
#else
#    define PHI_HAS_EXTENSION(extension) (0)
#endif

// has warning
#if defined(__has_warning)
#    define PHI_HAS_WARNING(warning) __has_warning(warning)
#else
#    define PHI_HAS_WARNING(warning) (0)
#endif

// is identifier / has keyword
#if defined(__is_identifier)
#    define PHI_IS_IDENTIFIER(identifier) __is_identifier(identifier)
#    define PHI_HAS_KEYWORD(keyword)      !(__is_identifier(keyword))
#else
#    define PHI_IS_IDENTIFIER(keyword) (0)
#    define PHI_HAS_KEYWORD(keyword)   (0)
#endif

// has include
#if defined(__has_include)
#    define PHI_HAS_INCLUDE(...) __has_include(__VA_ARGS__)
#else
#    define PHI_HAS_INCLUDE(...) (0)
#endif

// pragma
#if PHI_COMPILER_IS(CLANG_COMPAT) || PHI_COMPILER_IS_ATLEAST(GCC, 3, 0, 0) ||                      \
        PHI_COMPILER_IS_ATLEAST(ICC, 13, 0, 0)
// clang-format off
#    define PHI_PRAGMA(value) _Pragma(#value)
// clang-format on
#elif PHI_COMPILER_IS_ATLEAST(MSVC, 15, 0, 0)
#    define PHI_PRAGMA(value) __pragma(value)
#else
#    define PHI_PRAGMA(value) /* Nothing */
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_COMPILER_HPP
