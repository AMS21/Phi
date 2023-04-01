#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_EXTENDED_ATTRIBUTES_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_EXTENDED_ATTRIBUTES_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(CLANG_COMPAT)
#    define PHI_ATTRIBUTE_CONST __attribute__((const))
#else
#    define PHI_ATTRIBUTE_CONST /* Nothing */
#endif

#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(CLANG_COMPAT)
#    define PHI_ATTRIBUTE_PURE __attribute__((pure))
#else
#    define PHI_ATTRIBUTE_PURE /* Nothing */
#endif

#if PHI_COMPILER_IS_ATLEAST(GCC, 4, 4, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 2, 0) ||            \
        PHI_COMPILER_IS(APPLECLANG) || PHI_COMPILER_IS(EMCC)
#    define PHI_ATTRIBUTE_COLD __attribute__((cold))
#else
#    define PHI_ATTRIBUTE_COLD /* Nothing */
#endif

#if PHI_COMPILER_IS_ATLEAST(CLANG, 10, 0, 0) || PHI_COMPILER_IS_ATLEAST(APPLECLANG, 12, 4, 0) ||   \
        PHI_COMPILER_IS(EMCC)
#    define PHI_ATTRIBUTE_OWNER [[gsl::Owner]]
#else
#    define PHI_ATTRIBUTE_OWNER /* Nothing */
#endif

#if PHI_COMPILER_IS_ATLEAST(CLANG, 10, 0, 0) || PHI_COMPILER_IS_ATLEAST(APPLECLANG, 12, 4, 0) ||   \
        PHI_COMPILER_IS(EMCC)
#    define PHI_ATTRIBUTE_POINTER [[gsl::Pointer]]
#else
#    define PHI_ATTRIBUTE_POINTER /* Nothing */
#endif

// https://clang.llvm.org/docs/AttributeReference.html#lifetimebound
#if PHI_COMPILER_IS_ATLEAST(CLANG, 7, 0, 0) || PHI_COMPILER_IS(APPLECLANG) || PHI_COMPILER_IS(EMCC)
#    define PHI_ATTRIBUTE_LIFETIMEBOUND [[clang::lifetimebound]]
#else
#    define PHI_ATTRIBUTE_LIFETIMEBOUND /* Nothing */
#endif

#if PHI_COMPILER_IS_ATLEAST(GCC, 4, 9, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 5, 0) ||            \
        PHI_COMPILER_IS(APPLECLANG) || PHI_COMPILER_IS(EMCC)
#    define PHI_ATTRIBUTE_RETURNS_NONNULL __attribute__((returns_nonnull))
#else
#    define PHI_ATTRIBUTE_RETURNS_NONNULL /* Nothing */
#endif

#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(CLANG_COMPAT)
#    define PHI_ATTRIBUTE_NONNULL                 __attribute__((nonnull))
#    define PHI_ATTRIBUTE_NONNULL_PARAMETERS(...) __attribute__((nonnull(__VA_ARGS__)))
#else
#    define PHI_ATTRIBUTE_NONNULL                 /* Nothing */
#    define PHI_ATTRIBUTE_NONNULL_PARAMETERS(...) /* Nothing */
#endif

#if defined(PHI_CONFIG_DISABLE_NULLABILITY)
#    undef PHI_ATTRIBUTE_RETURNS_NONNULL
#    undef PHI_ATTRIBUTE_NONNULL
#    undef PHI_ATTRIBUTE_NONNULL_PARAMETERS

#    define PHI_ATTRIBUTE_RETURNS_NONNULL         /* Nothing */
#    define PHI_ATTRIBUTE_NONNULL                 /* Nothing */
#    define PHI_ATTRIBUTE_NONNULL_PARAMETERS(...) /* Nothing */
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_EXTENDED_ATTRIBUTES_HPP
