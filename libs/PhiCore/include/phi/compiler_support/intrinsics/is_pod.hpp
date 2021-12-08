#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_POD_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_POD_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/features.hpp"

#if PHI_HAS_INTRINSIC_IS_POD()
#    define PHI_IS_POD(type)      __is_pod(type)
#    define PHI_SUPPORTS_IS_POD() 1
#else
#    define PHI_IS_POD(type)      false
#    define PHI_SUPPORTS_IS_POD() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_POD
#    define PHI_SUPPORTS_IS_POD() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_POD_HPP
