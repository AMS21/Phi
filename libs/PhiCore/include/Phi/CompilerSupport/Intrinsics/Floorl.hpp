#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FLOORL_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FLOORL_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"

#if PHI_HAS_INTRINSIC_BUILTIN_FLOORL()
#    define PHI_FLOORL(value)     __builtin_floorl(value)
#    define PHI_SUPPORTS_FLOORL() 1
#else
#    define PHI_FLOORL(value)     (value > 0.0 ? value : -value)
#    define PHI_SUPPORTS_FLOORL() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_FLOORL
#    define PHI_SUPPORTS_FLOORL() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FLOORL_HPP
