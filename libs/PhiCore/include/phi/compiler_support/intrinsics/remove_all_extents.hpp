#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_REMOVE_ALL_EXTENTS_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_REMOVE_ALL_EXTENTS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_REMOVE_ALL_EXTENTS) && !defined(PHI_SUPPORTS_REMOVE_ALL_EXTENTS)

#    if PHI_COMPILER_IS_ATLEAST(CLANG, 16, 0, 0)
#        define PHI_REMOVE_ALL_EXTENTS(type)      __remove_all_extents(type)
#        define PHI_SUPPORTS_REMOVE_ALL_EXTENTS() 1
#    else
#        define PHI_SUPPORTS_REMOVE_ALL_EXTENTS() 0
#    endif

#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_REMOVE_ALL_EXTENTS_HPP
