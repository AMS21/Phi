#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_EMPTY_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_EMPTY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_IS_EMPTY) && !defined(PHI_SUPPORTS_IS_EMPTY)
#    if PHI_HAS_INTRINSIC_IS_EMPTY()
#        define PHI_IS_EMPTY(type)      __is_empty(type)
#        define PHI_SUPPORTS_IS_EMPTY() 1
#    else
#        define PHI_SUPPORTS_IS_EMPTY() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_EMPTY_HPP
