#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_NORETURN_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_NORETURN_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/features.hpp"

#if PHI_HAS_FEATURE_NORETURN()
#    define PHI_NORETURN [[noreturn]]
#elif PHI_HAS_EXTENSION_NORETURN()
#    define PHI_NORETURN _Noreturn
#elif PHI_HAS_EXTENSION_ATTRIBUTE_NORETURN()
#    define PHI_NORETURN __attribute__((noreturn))
#elif PHI_HAS_EXTENSION_DECLSPEC_NORETURN()
#    define PHI_NORETURN __declspec(noreturn)
#else
#    define PHI_NORETURN /* Nothing */
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_NORETURN_HPP
