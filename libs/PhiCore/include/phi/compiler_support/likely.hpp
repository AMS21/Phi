#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_LIKELY_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_LIKELY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"
#include "phi/compiler_support/features.hpp"

#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(CLANG_COMPAT)

#    define PHI_LIKELY(condition)   __builtin_expect(!!(condition), 1)
#    define PHI_UNLIKELY(condition) __builtin_expect(!!(condition), 0)

#else

#    define PHI_LIKELY(condition)   condition
#    define PHI_UNLIKELY(condition) condition

#endif

#if PHI_HAS_FEATURE_ATTRIBUTE_LIKELY()

#    define PHI_LIKELY_CASE   [[likely]]
#    define PHI_UNLIKELY_CASE [[unlikely]]

#else

#    define PHI_LIKELY_CASE   /* Nothing */
#    define PHI_UNLIKELY_CASE /* Nothing */

#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_LIKELY_HPP
