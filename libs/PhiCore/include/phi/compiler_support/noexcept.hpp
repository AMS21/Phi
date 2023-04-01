#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_NOEXCEPT_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_NOEXCEPT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/features.hpp"

#if PHI_HAS_FEATURE_NOEXCEPT()
#    define PHI_NOEXCEPT() noexcept
#else
#    define PHI_NOEXCEPT() /* Nothing */
#endif

#if PHI_HAS_FEATURE_NOEXCEPT_EXPR()
#    define PHI_NOEXCEPT_EXPR(...) noexcept(__VA_ARGS__)
#else
#    define PHI_NOEXCEPT_EXPR(...) /* Nothing */
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_NOEXCEPT_HPP
