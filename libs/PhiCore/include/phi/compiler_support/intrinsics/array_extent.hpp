#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ARRAY_EXTENT_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ARRAY_EXTENT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_ARRAY_EXTENT) && !defined(PHI_SUPPORTS_ARRAY_EXTENT)
#    if PHI_HAS_INTRINSIC_ARRAY_EXTENT()
#        define PHI_ARRAY_EXTENT(type, dimension) __array_extent(type, dimension)
#        define PHI_SUPPORTS_ARRAY_EXTENT()       1
#    else
#        define PHI_ARRAY_EXTENT(type, dimension) 0
#        define PHI_SUPPORTS_ARRAY_EXTENT()       0
#    endif

#    if defined(PHI_CONFIG_NO_INTRINSICS)
#        undef PHI_SUPPORTS_ARRAY_EXTENT
#        define PHI_SUPPORTS_ARRAY_EXTENT() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ARRAY_EXTENT_HPP
