#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_REMOVE_CONST_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_REMOVE_CONST_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/features.hpp"

#if PHI_HAS_INTRINSIC_REMOVE_CONST()
#    define PHI_REMOVE_CONST(type)      __remove_const(type)
#    define PHI_SUPPORTS_REMOVE_CONST() 1
#else
#    define PHI_REMOVE_CONST(type)      false
#    define PHI_SUPPORTS_REMOVE_CONST() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_REMOVE_CONST
#    define PHI_SUPPORTS_REMOVE_CONST() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_REMOVE_CONST_HPP
