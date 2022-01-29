#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_UNSIGNED_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_UNSIGNED_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if PHI_HAS_INTRINSIC_IS_UNSIGNED()
#    define PHI_IS_UNSIGNED(type)      __is_unsigned(type)
#    define PHI_SUPPORTS_IS_UNSIGNED() 1
#else
#    define PHI_IS_UNSIGNED(type)      false
#    define PHI_SUPPORTS_IS_UNSIGNED() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_UNSIGNED
#    define PHI_SUPPORTS_IS_UNSIGNED() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_UNSIGNED_HPP
