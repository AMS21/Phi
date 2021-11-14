#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_SIGNED_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_SIGNED_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"

#if PHI_HAS_INTRINSIC_IS_SIGNED()
#    define PHI_IS_SIGNED(type)      __is_signed(type)
#    define PHI_SUPPORTS_IS_SIGNED() 1
#else
#    define PHI_IS_SIGNED(type)      false
#    define PHI_SUPPORTS_IS_SIGNED() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_SIGNED
#    define PHI_SUPPORTS_IS_SIGNED() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_SIGNED_HPP
