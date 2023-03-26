#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABS_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_FABS) && !defined(PHI_FABSF) && !defined(PHI_FABSL) && !defined(PHI_SUPPORTS_FABS)

#    if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(CLANG_COMPAT)
#        define PHI_FABS(value)  __builtin_fabs(value)
#        define PHI_FABSF(value) __builtin_fabsf(value)
#        define PHI_FABSL(value) __builtin_fabsl(value)

#        define PHI_SUPPORTS_FABS() 1
#    else
#        define PHI_SUPPORTS_FABS() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABS_HPP
