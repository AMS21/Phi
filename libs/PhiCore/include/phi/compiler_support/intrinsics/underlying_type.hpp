#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_UNDERLYING_TYPE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_UNDERLYING_TYPE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_UNDERLYING_TYPE) && !defined(PHI_SUPPORTS_UNDERLYING_TYPE)
#    if PHI_HAS_INTRINSIC_UNDERLYING_TYPE()
#        define PHI_UNDERLYING_TYPE(type)      __underlying_type(type)
#        define PHI_SUPPORTS_UNDERLYING_TYPE() 1
#    else
#        define PHI_UNDERLYING_TYPE(type)      false
#        define PHI_SUPPORTS_UNDERLYING_TYPE() 0
#    endif

#    if defined(PHI_CONFIG_NO_INTRINSICS)
#        undef PHI_SUPPORTS_UNDERLYING_TYPE
#        define PHI_SUPPORTS_UNDERLYING_TYPE() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_UNDERLYING_TYPE_HPP
