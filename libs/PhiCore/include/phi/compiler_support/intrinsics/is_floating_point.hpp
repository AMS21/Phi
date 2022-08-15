#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_FLOATING_POINT_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_FLOATING_POINT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_IS_FLOATING_POINT) && !defined(PHI_SUPPORTS_IS_FLOATING_POINT)
#    if PHI_HAS_INTRINSIC_IS_FLOATING_POINT()
#        define PHI_IS_FLOATING_POINT(type)      __is_floating_point(type)
#        define PHI_SUPPORTS_IS_FLOATING_POINT() 1
#    else
#        define PHI_SUPPORTS_IS_FLOATING_POINT() 0
#    endif

#    if defined(PHI_CONFIG_NO_INTRINSICS)
#        undef PHI_SUPPORTS_IS_FLOATING_POINT
#        define PHI_SUPPORTS_IS_FLOATING_POINT() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_FLOATING_POINT_HPP
