#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_RESTRICT_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_RESTRICT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(CLANG_COMPAT) || PHI_COMPILER_IS(MSVC)

#    define PHI_SUPPORTS_RESTRICT() 1
#    define PHI_RESTRICT            __restrict

#else

#    define PHI_SUPPORTS_RESTRICT() 0
#    define PHI_RESTRICT            /* Nothing */

#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_RESTRICT_HPP
