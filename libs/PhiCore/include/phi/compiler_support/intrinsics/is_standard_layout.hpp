#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_STANDARD_LAYOUT_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_STANDARD_LAYOUT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if PHI_HAS_INTRINSIC_IS_STANDARD_LAYOUT()
#    define PHI_IS_STANDARD_LAYOUT(type)      __is_standard_layout(type)
#    define PHI_SUPPORTS_IS_STANDARD_LAYOUT() 1
#else
#    define PHI_IS_STANDARD_LAYOUT(type)      false
#    define PHI_SUPPORTS_IS_STANDARD_LAYOUT() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_STANDARD_LAYOUT
#    define PHI_SUPPORTS_IS_STANDARD_LAYOUT() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_STANDARD_LAYOUT_HPP
