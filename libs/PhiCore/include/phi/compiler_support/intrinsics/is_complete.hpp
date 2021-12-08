#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_COMPLETE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_COMPLETE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/features.hpp"

#if PHI_HAS_INTRINSIC_IS_COMPLETE_TYPE()
#    define PHI_IS_COMPLETE(type)      __is_complete_type(type)
#    define PHI_SUPPORTS_IS_COMPLETE() 1
#else
#    define PHI_IS_COMPLETE(type)      false
#    define PHI_SUPPORTS_IS_COMPLETE() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_COMPLETE
#    define PHI_SUPPORTS_IS_COMPLETE() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_COMPLETE_HPP
