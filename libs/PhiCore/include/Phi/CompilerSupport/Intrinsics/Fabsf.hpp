#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABSF_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABSF_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"

#if PHI_HAS_INTRINSIC_BUILTIN_FABSF()
#    define PHI_FABSF(value)     __builtin_fabsf(value)
#    define PHI_SUPPORTS_FABSF() 1
#else
#    define PHI_FABSF(value)     (value > 0.0f ? value : -value)
#    define PHI_SUPPORTS_FABSF() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_FABSF
#    define PHI_SUPPORTS_FABSF() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FABSF_HPP
