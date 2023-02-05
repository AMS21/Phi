#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_IS_NAN_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_IS_NAN_HPP

#include "phi/generated/compiler_support/features.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#if !defined(PHI_IS_NAN) && !defined(PHI_SUPPORTS_IS_NAN)
#    if PHI_HAS_INTRINSIC_BUILTIN_ISNAN()
#        define PHI_IS_NAN(value)     __builtin_isnan(value)
#        define PHI_SUPPORTS_IS_NAN() 1
#    else
#        define PHI_SUPPORTS_IS_NAN() 0
#    endif
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_IS_NAN_HPP
