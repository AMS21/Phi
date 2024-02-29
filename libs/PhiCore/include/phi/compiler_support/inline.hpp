/*!
 * \file Inline.hpp
 * \brief Exports macros to force or forbid inlining of a function.
**/
#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_INLINE_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_INLINE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

/*!
 * \def PHI_ALWAYS_INLINE
 * \brief Declares a function as always to be inlined (if possible).
 * \warning Overrides the compiler's cost-benefit-analysis in regards to
 *          inlining. Only use when certain. May not work if compiler is
 *          unknown.
**/

#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(CLANG_COMPAT)

#    define PHI_ALWAYS_INLINE __attribute__((always_inline)) inline

#elif PHI_COMPILER_IS(MSVC)

#    define PHI_ALWAYS_INLINE __forceinline

#else

#    define PHI_ALWAYS_INLINE inline

#endif

/*!
 * \def PHI_NEVER_INLINE
 * \brief Declares a function as never to be inlined.
 * \warning May not work if compiler is unknown.
**/

#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(CLANG_COMPAT)

#    define PHI_NEVER_INLINE __attribute__((noinline))

#elif PHI_COMPILER_IS(MSVC)

#    define PHI_NEVER_INLINE __declspec(noinline)

#else

#    define PHI_NEVER_INLINE /* nothing */

#endif

#ifdef PHI_CONFIG_ALWAYS_INLINE_OVERWRITE
#    undef PHI_ALWAYS_INLINE
#    define PHI_ALWAYS_INLINE PHI_CONFIG_ALWAYS_INLINE_OVERWRITE
#endif

#ifdef PHI_CONFIG_NEVER_INLINE_OVERWRITE
#    undef PHI_NEVER_INLINE
#    define PHI_NEVER_INLINE PHI_CONFIG_NEVER_INLINE_OVERWRITE
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_INLINE_HPP
