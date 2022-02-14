#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ADDRESS_OF_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ADDRESS_OF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_ADDRESS_OF) && !defined(PHI_SUPPORTS_ADDRESS_OF)
#    if PHI_HAS_INTRINSIC_BUILTIN_ADDRESS_OF()
#        define PHI_ADDRESS_OF(obj)       __builtin_addressof(obj)
#        define PHI_SUPPORTS_ADDRESS_OF() 1
#    else
#        define PHI_ADDRESS_OF(obj)       0
#        define PHI_SUPPORTS_ADDRESS_OF() 0
#    endif

#    if defined(PHI_CONFIG_NO_INTRINSICS)
#        undef PHI_SUPPORTS_ADDRESS_OF
#        define PHI_SUPPORTS_ADDRESS_OF() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ADDRESS_OF_HPP
