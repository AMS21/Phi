#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_NOEXCEPT_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_NOEXCEPT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/features.hpp"

#if PHI_HAS_FEATURE_NOEXCEPT()

#    define PHI_NOEXCEPT           noexcept
#    define PHI_NOEXCEPT_EXPR(...) noexcept(__VA_ARGS__)

#    if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
#        define PHI_NOEXCEPT_CLASS_EXPR(...) noexcept(__VA_ARGS__)
#    else
#        define PHI_NOEXCEPT_CLASS_EXPR(...) /* Nothing */
#    endif

#else

#    define PHI_NOEXCEPT                 /* Nothing */
#    define PHI_NOEXCEPT_EXPR(...)       /* Nothing */
#    define PHI_NOEXCEPT_CLASS_EXPR(...) /* Nothing */

#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_NOEXCEPT_HPP
