#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FLOORL_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FLOORL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_FLOORL) && !defined(PHI_SUPPORTS_FLOORL)
#    if PHI_HAS_INTRINSIC_BUILTIN_FLOORL()
#        define PHI_FLOORL(value)     __builtin_floorl(value)
#        define PHI_SUPPORTS_FLOORL() 1
#    else
#        define PHI_FLOORL(value)     (value > 0.0 ? value : -value)
#        define PHI_SUPPORTS_FLOORL() 0
#    endif

#    if defined(PHI_CONFIG_NO_INTRINSICS)
#        undef PHI_SUPPORTS_FLOORL
#        define PHI_SUPPORTS_FLOORL() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FLOORL_HPP
