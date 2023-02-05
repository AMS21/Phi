#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABSL_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABSL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_FABSL) && !defined(PHI_SUPPORTS_FABSL)
#    if PHI_HAS_INTRINSIC_BUILTIN_FABSL()
#        define PHI_FABSL(value)     __builtin_fabsl(value)
#        define PHI_SUPPORTS_FABSL() 1
#    else
#        define PHI_SUPPORTS_FABSL() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABSL_HPP
