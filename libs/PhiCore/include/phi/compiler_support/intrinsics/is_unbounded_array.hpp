#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_UNBOUNDED_ARRAY_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_UNBOUNDED_ARRAY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_IS_UNBOUNDED_ARRAY) && !defined(PHI_SUPPORTS_IS_UNBOUNDED_ARRAY)
#    if PHI_HAS_INTRINSIC_IS_UNBOUNDED_ARRAY()
#        define PHI_IS_UNBOUNDED_ARRAY(type)      __is_unbounded_array(type)
#        define PHI_SUPPORTS_IS_UNBOUNDED_ARRAY() 1
#    else
#        define PHI_SUPPORTS_IS_UNBOUNDED_ARRAY() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_UNBOUNDED_ARRAY_HPP
