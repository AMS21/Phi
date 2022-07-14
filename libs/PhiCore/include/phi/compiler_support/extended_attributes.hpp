#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_EXTENDED_ATTRIBUTES_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_EXTENDED_ATTRIBUTES_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if PHI_HAS_EXTENSION_ATTRIBUTE_CONST()
#    define PHI_ATTRIBUTE_CONST __attribute__((const))
#else
#    define PHI_ATTRIBUTE_CONST /* Nothing */
#endif

#if PHI_HAS_EXTENSION_ATTRIBUTE_PURE()
#    define PHI_ATTRIBUTE_PURE __attribute__((pure))
#else
#    define PHI_ATTRIBUTE_PURE /* Nothing */
#endif

#if PHI_HAS_EXTENSION_ATTRIBUTE_COLD()
#    define PHI_ATTRIBUTE_COLD __attribute__((cold))
#else
#    define PHI_ATTRIBUTE_COLD /* Nothing */
#endif

#if PHI_HAS_EXTENSION_GSL_OWNER()
#    define PHI_ATTRIBUTE_OWNER [[gsl::Owner]]
#else
#    define PHI_ATTRIBUTE_OWNER /* Nothing */
#endif

#if PHI_HAS_EXTENSION_GSL_POINTER()
#    define PHI_ATTRIBUTE_POINTER [[gsl::Pointer]]
#else
#    define PHI_ATTRIBUTE_POINTER /* Nothing */
#endif

#if PHI_HAS_EXTENSION_ATTRIBUTE_RETURNS_NONNULL()
#    define PHI_ATTRIBUTE_RETURNS_NONNULL __attribute__((returns_nonnull))
#elif PHI_HAS_EXTENSION_RET_NONNULL()
#    define PHI_ATTRIBUTE_RETURNS_NONNULL _Ret_notnull_
#else
#    define PHI_ATTRIBUTE_RETURNS_NONNULL /* Nothing */
#endif

#if PHI_HAS_EXTENSION_ATTRIBUTE_NONNULL()
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
