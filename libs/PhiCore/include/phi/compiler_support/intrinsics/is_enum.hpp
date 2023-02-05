#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ENUM_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ENUM_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_IS_ENUM) && !defined(PHI_SUPPORTS_IS_ENUM)
#    if PHI_HAS_INTRINSIC_IS_ENUM()
#        define PHI_IS_ENUM(type)      __is_enum(type)
#        define PHI_SUPPORTS_IS_ENUM() 1
#    else
#        define PHI_SUPPORTS_IS_ENUM() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ENUM_HPP
