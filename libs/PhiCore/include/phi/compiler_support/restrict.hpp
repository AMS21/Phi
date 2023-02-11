#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_RESTRICT_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_RESTRICT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if PHI_HAS_EXTENSION_RESTRICT()

#    define PHI_SUPPORTS_RESTRICT() 1
#    define PHI_RESTRICT            __restrict

#elif PHI_HAS_EXTENSION_RESTRICT_UNDERSCORE()

#    define PHI_SUPPORTS_RESTRICT() 1
#    define PHI_RESTRICT            __restrict__

#else

#    define PHI_SUPPORTS_RESTRICT() 0
#    define PHI_RESTRICT            /* Nothing */

#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_RESTRICT_HPP
