/*!
 * \file Compiler.hpp
 * \brief Defines macros to determine the compiler
 *        and the version of the compiler being used.
 *
**/
#ifndef INCG_PHI_CONFIG_COMPILER_HPP
#define INCG_PHI_CONFIG_COMPILER_HPP

#include "Phi/Config/Glue.hpp"
#include "Phi/Config/Versioning.hpp" // PHI_VERSION_CREATE

#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
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

#if defined(_MSC_VER)
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

#if defined(__clang__) && !PHI_COMPILER_EMCC()
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

#if (defined(__GNUC__) || defined(__GNUG__)) && (!PHI_COMPILER_CLANG() && !PHI_COMPILER_MINGW())
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

#define PHI_COMPILER_IS(compiler) (PHI_COMPILER_##compiler())

#define PHI_COMPILER_IS_NOT(compiler) (!PHI_COMPILER_IS(compiler))

#define PHI_COMPILER_IS_ATLEAST(compiler, major, minor, patch)                                     \
    (PHI_COMPILER_IS(compiler) &&                                                                  \
     (PHI_VERSION_CREATE(major, minor, patch) <= PHI_COMPILER_VERSION(compiler)))

#define PHI_COMPILER_IS_BELOW(compiler, major, minor, patch)                                       \
    (PHI_COMPILER_IS(compiler) &&                                                                  \
     (PHI_VERSION_CREATE(major, minor, patch) > PHI_COMPILER_VERSION(compiler)))

// Compiler name
#if PHI_COMPILER_IS(EMCC)
#    define PHI_COMPILER_NAME() "Emscripten"
#elif PHI_COMPILER_IS(ICC)
#    define PHI_COMPILER_NAME() "Intel ICC"
#elif PHI_COMPILER_IS(MSVC)
#    define PHI_COMPILER_NAME() "Microsoft Visual C++ Compiler"
#elif PHI_COMPILER_IS(MINGW)
#    if defined(__MINGW64__) || defined(__MINGW64_VERSION_MAJOR) || defined(__MINGW64_VERSION_MINOR)
#        define PHI_COMPILER_NAME() "MinGW64"
#    else
#        define PHI_COMPILER_NAME() "MinGW32"
#    endif
#elif PHI_COMPILER_IS(CLANG)
#    define PHI_COMPILER_NAME() "Clang"
#elif PHI_COMPILER_IS(GCC)
#    define PHI_COMPILER_NAME() "GCC"
#else
#    define PHI_COMPILER_NAME() "Unknown"
#endif

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

// pragma
#if PHI_COMPILER_IS(CLANG) || PHI_COMPILER_IS_ATLEAST(GCC, 3, 0, 0) ||                             \
        PHI_COMPILER_IS_ATLEAST(ICC, 13, 0, 0)
#    define PHI_PRAGMA(value) _Pragma(#    value)
#elif PHI_COMPILER_IS_ATLEAST(MSVC, 15, 0, 0)
#    define PHI_PRAGMA(value) __pragma(value)
#else
#    define PHI_PRAGMA(value) /* Nothing */
#endif

#endif // INCG_PHI_CONFIG_COMPILER_HPP
