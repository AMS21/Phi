#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABSL_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABSL_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"

#if PHI_HAS_INTRINSIC_BUILTIN_FABSL()
#    define PHI_FABSL(value)     __builtin_fabsl(value)
#    define PHI_SUPPORTS_FABSL() 1
#else
#    define PHI_FABSL(value)     (value > 0.0L ? value : -value)
#    define PHI_SUPPORTS_FABSL() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_FABSL
#    define PHI_SUPPORTS_FABSL() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABSL_HPP
