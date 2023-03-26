#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ARRAY_EXTENT_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ARRAY_EXTENT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_ARRAY_EXTENT) && !defined(PHI_SUPPORTS_ARRAY_EXTENT)

#    if PHI_COMPILER_IS(CLANG_COMPAT)
#        define PHI_ARRAY_EXTENT(type, dimension) __array_extent(type, dimension)
#        define PHI_SUPPORTS_ARRAY_EXTENT()       1
#    else
#        define PHI_SUPPORTS_ARRAY_EXTENT() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ARRAY_EXTENT_HPP
