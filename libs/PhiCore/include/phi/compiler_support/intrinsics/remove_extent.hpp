#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_REMOVE_EXTENT_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_REMOVE_EXTENT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_REMOVE_EXTENT) && !defined(PHI_SUPPORTS_REMOVE_EXTENT)

#    if PHI_COMPILER_IS_ATLEAST(CLANG, 16, 0, 0)
#        define PHI_REMOVE_EXTENT(type)      __remove_extent(type)
#        define PHI_SUPPORTS_REMOVE_EXTENT() 1
#    else
#        define PHI_SUPPORTS_REMOVE_EXTENT() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_REMOVE_EXTENT_HPP
