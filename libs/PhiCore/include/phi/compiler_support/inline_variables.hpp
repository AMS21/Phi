#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_INLINE_VARIABLES_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_INLINE_VARIABLES_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/features.hpp"

#if PHI_HAS_FEATURE_INLINE_VARIABLES()
#    define PHI_INLINE_VARIABLE                 inline
#    define PHI_INLINE_VARIABLE_OR(alternative) inline
#else
#    define PHI_INLINE_VARIABLE                 /* Nothing */
#    define PHI_INLINE_VARIABLE_OR(alternative) alternative
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_INLINE_VARIABLES_HPP
