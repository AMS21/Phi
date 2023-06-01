#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_REMOVE_CVREF_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_REMOVE_CVREF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_REMOVE_CVREF) && !defined(PHI_SUPPORTS_REMOVE_CVREF)

// NOTE: While gcc-13 supports this type trait, it gives an compile time error when using it.
#    if PHI_COMPILER_IS_ATLEAST(CLANG, 16, 0, 0)
#        define PHI_REMOVE_CVREF(type)      __remove_cvref(type)
#        define PHI_SUPPORTS_REMOVE_CVREF() 1
#    else
#        define PHI_SUPPORTS_REMOVE_CVREF() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_REMOVE_CVREF_HPP
