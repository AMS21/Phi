#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_CONVERTIBLE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_CONVERTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_IS_CONVERTIBLE) && !defined(PHI_SUPPORTS_IS_CONVERTIBLE)
#    if PHI_HAS_INTRINSIC_IS_CONVERTIBLE()
#        define PHI_IS_CONVERTIBLE(from, to)  __is_convertible(from, to)
#        define PHI_SUPPORTS_IS_CONVERTIBLE() 1
#    elif PHI_HAS_INTRINSIC_IS_CONVERTIBLE_TO()
#        define PHI_IS_CONVERTIBLE(from, to)  __is_convertible_to(from, to)
#        define PHI_SUPPORTS_IS_CONVERTIBLE() 1
#    else
#        define PHI_IS_CONVERTIBLE(from, to)  false
#        define PHI_SUPPORTS_IS_CONVERTIBLE() 0
#    endif

#    if defined(PHI_CONFIG_NO_INTRINSICS)
#        undef PHI_SUPPORTS_IS_CONVERTIBLE
#        define PHI_SUPPORTS_IS_CONVERTIBLE() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_CONVERTIBLE_HPP
