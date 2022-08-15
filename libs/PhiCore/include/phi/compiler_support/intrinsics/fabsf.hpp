#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABSF_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABSF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_FABSF) && !defined(PHI_SUPPORTS_FABSF)
#    if PHI_HAS_INTRINSIC_BUILTIN_FABSF()
#        define PHI_FABSF(value)     __builtin_fabsf(value)
#        define PHI_SUPPORTS_FABSF() 1
#    else
#        define PHI_SUPPORTS_FABSF() 0
#    endif

#    if defined(PHI_CONFIG_NO_INTRINSICS)
#        undef PHI_SUPPORTS_FABSF
#        define PHI_SUPPORTS_FABSF() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABSF_HPP
