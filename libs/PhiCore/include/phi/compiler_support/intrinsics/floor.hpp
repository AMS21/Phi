#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FLOOR_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FLOOR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_ADDRESS_FLOOR) && !defined(PHI_SUPPORTS_FLOOR)
#    if PHI_HAS_INTRINSIC_BUILTIN_FLOOR()
#        define PHI_FLOOR(value)     __builtin_floor(value)
#        define PHI_SUPPORTS_FLOOR() 1
#    else
#        define PHI_FLOOR(value)     0.0
#        define PHI_SUPPORTS_FLOOR() 0
#    endif

#    if defined(PHI_CONFIG_NO_INTRINSICS)
#        undef PHI_SUPPORTS_FLOOR
#        define PHI_SUPPORTS_FLOOR() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FLOOR_HPP
