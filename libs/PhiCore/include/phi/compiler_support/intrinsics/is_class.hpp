#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_CLASS_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_CLASS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/features.hpp"

#if PHI_HAS_INTRINSIC_IS_CLASS()
#    define PHI_IS_CLASS(type)      __is_class(type)
#    define PHI_SUPPORTS_IS_CLASS() 1
#else
#    define PHI_IS_CLASS(type)      false
#    define PHI_SUPPORTS_IS_CLASS() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_CLASS
#    define PHI_SUPPORTS_IS_CLASS() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_CLASS_HPP
