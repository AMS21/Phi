#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_INTEGRAL_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_INTEGRAL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/features.hpp"

#if PHI_HAS_INTRINSIC_IS_INTEGRAL()
#    define PHI_IS_INTEGRAL(type)      __is_integral(type)
#    define PHI_SUPPORTS_IS_INTEGRAL() 1
#else
#    define PHI_IS_INTEGRAL(type)      false
#    define PHI_SUPPORTS_IS_INTEGRAL() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_INTEGRAL
#    define PHI_SUPPORTS_IS_INTEGRAL() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_INTEGRAL_HPP
