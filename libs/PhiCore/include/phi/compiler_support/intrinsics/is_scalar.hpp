#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_SCALAR_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_SCALAR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if PHI_HAS_INTRINSIC_IS_SCALAR()
#    define PHI_IS_SCALAR(type)      __is_scalar(type)
#    define PHI_SUPPORTS_IS_SCALAR() 1
#else
#    define PHI_IS_SCALAR(type)      false
#    define PHI_SUPPORTS_IS_SCALAR() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_SCALAR
#    define PHI_SUPPORTS_IS_SCALAR() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_SCALAR_HPP
