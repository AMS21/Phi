#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_IS_NAN_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_IS_NAN_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_NAN) && !defined(PHI_SUPPORTS_IS_NAN)

#    if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(CLANG_COMPAT)
#        define PHI_IS_NAN(value)     __builtin_isnan(value)
#        define PHI_SUPPORTS_IS_NAN() 1
#    else
#        define PHI_SUPPORTS_IS_NAN() 0
#    endif

#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_IS_NAN_HPP
