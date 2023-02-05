#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ARRAY_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ARRAY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_IS_ARRAY) && !defined(PHI_SUPPORTS_IS_ARRAY)
#    if PHI_HAS_INTRINSIC_IS_ARRAY()
#        define PHI_IS_ARRAY(type)      __is_array(type)
#        define PHI_SUPPORTS_IS_ARRAY() 1
#    else
#        define PHI_SUPPORTS_IS_ARRAY() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ARRAY_HPP
