#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_REFERENCE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_REFERENCE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_IS_REFERENCE) && !defined(PHI_SUPPORTS_IS_REFERENCE)
#    if PHI_HAS_INTRINSIC_IS_REFERENCE()
#        define PHI_IS_REFERENCE(type)      __is_reference(type)
#        define PHI_SUPPORTS_IS_REFERENCE() 1
#    else
#        define PHI_SUPPORTS_IS_REFERENCE() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_REFERENCE_HPP
