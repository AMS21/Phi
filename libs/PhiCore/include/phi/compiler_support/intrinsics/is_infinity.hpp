#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_INFINITY_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_INFINITY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_IS_INFINITY) && !defined(PHI_SUPPORTS_IS_INFINITY)

#    if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(CLANG_COMPAT)
#        define PHI_IS_INFINITY(value)     __builtin_isinf(value)
#        define PHI_SUPPORTS_IS_INFINITY() 1
#    else
#        define PHI_SUPPORTS_IS_INFINITY() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_INFINITY_HPP
