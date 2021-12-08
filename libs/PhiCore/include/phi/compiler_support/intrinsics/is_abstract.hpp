#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ABSTRACT_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ABSTRACT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/features.hpp"

#if PHI_HAS_INTRINSIC_IS_ABSTRACT()
#    define PHI_IS_ABSTRACT(type)      __is_abstract(type)
#    define PHI_SUPPORTS_IS_ABSTRACT() 1
#else
#    define PHI_IS_ABSTRACT(type)      false
#    define PHI_SUPPORTS_IS_ABSTRACT() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_ABSTRACT
#    define PHI_SUPPORTS_IS_ABSTRACT() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ABSTRACT_HPP
