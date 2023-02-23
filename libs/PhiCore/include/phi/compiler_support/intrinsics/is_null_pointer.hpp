#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_NULLPTR_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_NULLPTR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_IS_NULL_POINTER) && !defined(PHI_SUPPORTS_IS_NULL_POINTER)
#    if PHI_HAS_INTRINSIC_IS_NULLPTR()
#        define PHI_IS_NULL_POINTER(type)      __is_nullptr(type)
#        define PHI_SUPPORTS_IS_NULL_POINTER() 1
#    else
#        define PHI_SUPPORTS_IS_NULL_POINTER() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_NULLPTR_HPP
