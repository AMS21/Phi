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

#define PHI_COMPILER_APPLECLANG() 0
#define PHI_COMPILER_CLANG()      0
#define PHI_COMPILER_ICC()        0
#define PHI_COMPILER_MSVC()       0
#define PHI_COMPILER_GCC()        0
#define PHI_COMPILER_GCC_COMPAT() 0
#define PHI_COMPILER_MINGW()      0
#define PHI_COMPILER_EMSCRIPTEN() 0

#if defined(__clang__)
#    undef PHI_COMPILER_CLANG
#    define PHI_COMPILER_CLANG() 1
#    define PHI_COMPILER_MAJOR() __clang_major__
#    define PHI_COMPILER_MINOR() __clang_minor__
#    define PHI_COMPILER_PATCH() __clang_patchlevel__
#    define PHI_COMPILER_NAME()  "Clang"
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
#    undef PHI_COMPILER_ICC
#    define PHI_COMPILER_ICC()   1
#    define PHI_COMPILER_MAJOR() (__INTEL_COMPILER / 100)
#    define PHI_COMPILER_MINOR() (__INTEL_COMPILER % 100 / 10)
#    define PHI_COMPILER_PATCH() (__INTEL_COMPILER % 10)
#    define PHI_COMPILER_NAME()  "Intel ICC"
#elif defined(_MSC_VER)
#    undef PHI_COMPILER_MSVC
#    define PHI_COMPILER_MSVC()  1
#    define PHI_COMPILER_MAJOR() (_MSC_FULL_VER / 10000000)
#    define PHI_COMPILER_MINOR() (_MSC_FULL_VER % 10000000 / 100000)
#    define PHI_COMPILER_PATCH() (_MSC_FULL_VER % 100000)
#    define PHI_COMPILER_NAME()  "Microsoft Visual C++ Compiler"
#elif defined(__MINGW32__) || defined(__MINGW64__)
#    include "stdlib.h" // Needed for version information
#    undef PHI_COMPILER_MINGW
#    define PHI_COMPILER_MINGW() 1
#    define PHI_COMPILER_MAJOR() __MINGW32_MAJOR_VERSION
#    define PHI_COMPILER_MINOR() __MINGW32_MINOR_VERSION
#    define PHI_COMPILER_PATCH() 0 // no patch version defined for MingW
#    if defined(__MINGW64__) || defined(__MINGW64_VERSION_MAJOR) || defined(__MINGW64_VERSION_MINOR)
#        define PHI_COMPILER_NAME() "MinGW64"
#    else
#        define PHI_COMPILER_NAME() "MinGW32"
#    endif
#elif defined(__EMSCRIPTEN__)
#    undef PHI_COMPILER_EMSCRIPTEN
#    define PHI_COMPILER_EMSCRIPTEN() 1
#    define PHI_COMPILER_MAJOR()      __EMSCRIPTEN_major__
#    define PHI_COMPILER_MINOR()      __EMSCRIPTEN_minor__
#    define PHI_COMPILER_PATCH()      __EMSCRIPTEN_tiny__
#    define PHI_COMPILER_NAME()       "Emscripten"
#elif defined(__GNUC__) || defined(__GNUG__)
#    undef PHI_COMPILER_GCC
#    define PHI_COMPILER_GCC()   1
#    define PHI_COMPILER_MAJOR() __GNUC__
#    define PHI_COMPILER_MINOR() __GNUC_MINOR__
#    define PHI_COMPILER_PATCH() __GNUC_PATCHLEVEL__
#    define PHI_COMPILER_NAME()  "GCC"
#endif

// Check for gcc compatibility
#if defined(__GNUC__) || defined(__GNUG__)
#    undef PHI_COMPILER_GCC_COMPAT
#    define PHI_COMPILER_GCC_COMPAT() 1
#endif

#define PHI_COMPILER_VERSION()                                                                     \
    (PHI_VERSION_CREATE(PHI_COMPILER_MAJOR(), PHI_COMPILER_MINOR(), PHI_COMPILER_PATCH()))

#define PHI_COMPILER_VERSION_IS_ATLEAST(major, minor, patch)                                       \
    (PHI_VERSION_CREATE(major, minor, patch) <= PHI_COMPILER_VERSION())

#define PHI_COMPILER_VERSION_IS_BELOW(major, minor, patch)                                         \
    (PHI_VERSION_CREATE(major, minor, patch) > PHI_COMPILER_VERSION())

#define PHI_COMPILER_IS(compiler) (PHI_COMPILER_##compiler())

#define PHI_COMPILER_IS_NOT(compiler) (!PHI_COMPILER_IS(compiler))

#define PHI_COMPILER_IS_ATLEAST(compiler, major, minor, patch)                                     \
    (PHI_COMPILER_IS(compiler) && PHI_COMPILER_VERSION_IS_ATLEAST(major, minor, patch))

#define PHI_COMPILER_IS_BELOW(compiler, major, minor, patch)                                       \
    (PHI_COMPILER_IS(compiler) && PHI_COMPILER_VERSION_IS_BELOW(major, minor, patch))

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
