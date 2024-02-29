#ifndef INCG_PHI_COMPILER_SUPPORT_CONSTEVAL_HPP
#define INCG_PHI_COMPILER_SUPPORT_CONSTEVAL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/features.hpp"
#include "phi/preprocessor/if.hpp"

#if PHI_HAS_FEATURE_CONSTEVAL()

#    define PHI_CONSTEVAL                       consteval
#    define PHI_CONSTEVAL_OR_CONSTEXPR          consteval
#    define PHI_CONSTEVAL_OR_EXTENDED_CONSTEXPR consteval
#    define PHI_CONSTEVAL_OR(alternative)       consteval
#    define PHI_CONSTEVAL_IF(condition)         PHI_IF(condition, consteval)

#else

#    define PHI_CONSTEVAL /* Nothing */

// PHI_CONSTEVAL_OR_CONSTEXPR
#    if PHI_HAS_FEATURE_CONSTEXPR()
#        define PHI_CONSTEVAL_OR_CONSTEXPR constexpr
#    else
#        define PHI_CONSTEVAL_OR_CONSTEXPR /* Nothing */
#    endif

// PHI_CONSTEVAL_OR_EXTENDED_CONSTEXPR
#    if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
#        define PHI_CONSTEVAL_OR_EXTENDED_CONSTEXPR constexpr
#    else
#        define PHI_CONSTEVAL_OR_EXTENDED_CONSTEXPR /* Nothing */
#    endif

#    define PHI_CONSTEVAL_OR(alternative) alternative

#    define PHI_CONSTEVAL_IF(condition) /* Nothing */

#endif

#endif // INCG_PHI_COMPILER_SUPPORT_CONSTEVAL_HPP
