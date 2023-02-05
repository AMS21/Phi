#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_BASE_OF_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_BASE_OF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_IS_BASE_OF) && !defined(PHI_SUPPORTS_IS_BASE_OF)
#    if PHI_HAS_INTRINSIC_IS_BASE_OF()
#        define PHI_IS_BASE_OF(base, derived) __is_base_of(base, derived)
#        define PHI_SUPPORTS_IS_BASE_OF()     1
#    else
#        define PHI_SUPPORTS_IS_BASE_OF() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_BASE_OF_HPP
