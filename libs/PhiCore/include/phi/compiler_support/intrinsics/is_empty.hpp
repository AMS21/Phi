#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_EMPTY_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_EMPTY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/features.hpp"

#if PHI_HAS_INTRINSIC_IS_EMPTY()
#    define PHI_IS_EMPTY(type)      __is_empty(type)
#    define PHI_SUPPORTS_IS_EMPTY() 1
#else
#    define PHI_IS_EMPTY(type)      false
#    define PHI_SUPPORTS_IS_EMPTY() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_EMPTY
#    define PHI_SUPPORTS_IS_EMPTY() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_EMPTY_HPP
