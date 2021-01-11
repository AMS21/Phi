/*!
 * \file Inline.hpp
 * \brief Exports macros to force or forbid inlining of a function.
**/
#ifndef INCG_PHI_CONFIG_INLINE_HPP
#define INCG_PHI_CONFIG_INLINE_HPP

#include "Phi/Config/Compiler.hpp"

/*!
 * \def PHI_ALWAYS_INLINE
 * \brief Declares a function as always to be inlined (if possible).
 * \warning Overrides the compiler's cost-benefit-analysis in regards to
 *          inlining. Only use when certain. May not work if compiler is
 *          unknown.
**/

/*!
 * \def PHI_NEVER_INLINE
 * \brief Declares a function as never to be inlined.
 * \warning May not work if compiler is unknown.
**/

#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(CLANG) || PHI_COMPILER_IS(ICC)
#    define PHI_ALWAYS_INLINE __attribute__((always_inline)) inline
#    define PHI_NEVER_INLINE  __attribute__((noinline))
#elif PHI_COMPILER_IS(MSVC)
#    define PHI_ALWAYS_INLINE __forceinline
#    define PHI_NEVER_INLINE  __declspec(noinline)
#else
#    define PHI_ALWAYS_INLINE inline
#    define PHI_NEVER_INLINE  /* nothing */
#endif

#ifdef PHI_CONFIG_ALWAYS_INLINE_OVERWRITE
#    undef PHI_ALWAYS_INLINE
#    define PHI_ALWAYS_INLINE PHI_CONFIG_ALWAYS_INLINE_OVERWRITE
#endif

#ifdef PHI_CONFIG_NEVER_INLINE_OVERWRITE
#    undef PHI_NEVER_INLINE
#    define PHI_NEVER_INLINE PHI_CONFIG_NEVER_INLINE_OVERWRITE
#endif

#endif // INCG_PHI_CONFIG_INLINE_HPP
