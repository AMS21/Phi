#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABS_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_FABS) && !defined(PHI_SUPPORTS_FABS)
#    if PHI_HAS_INTRINSIC_BUILTIN_FABS()
#        define PHI_FABS(value)     __builtin_fabs(value)
#        define PHI_SUPPORTS_FABS() 1
#    else
#        define PHI_SUPPORTS_FABS() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABS_HPP
