#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABS_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABS_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"

#if PHI_HAS_INTRINSIC_BUILTIN_FABS()
#    define PHI_FABS(value)     __builtin_fabs(value)
#    define PHI_SUPPORTS_FABS() 1
#else
#    define PHI_FABS(value)     (value > 0.0 ? value : -value)
#    define PHI_SUPPORTS_FABS() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_FABS
#    define PHI_SUPPORTS_FABS() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABS_HPP
