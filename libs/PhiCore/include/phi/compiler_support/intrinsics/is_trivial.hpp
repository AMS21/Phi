#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_TRIVIAL_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_TRIVIAL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/features.hpp"

#if PHI_HAS_INTRINSIC_IS_TRIVIAL()
#    define PHI_IS_TRIVIAL(type)      __is_trivial(type)
#    define PHI_SUPPORTS_IS_TRIVIAL() 1
#else
#    define PHI_IS_TRIVIAL(type)      false
#    define PHI_SUPPORTS_IS_TRIVIAL() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_TRIVIAL
#    define PHI_SUPPORTS_IS_TRIVIAL() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_TRIVIAL_HPP
