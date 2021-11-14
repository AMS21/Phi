#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ENUM_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ENUM_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"

#if PHI_HAS_INTRINSIC_IS_ENUM()
#    define PHI_IS_ENUM(type)      __is_enum(type)
#    define PHI_SUPPORTS_IS_ENUM() 1
#else
#    define PHI_IS_ENUM(type)      false
#    define PHI_SUPPORTS_IS_ENUM() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_ENUM
#    define PHI_SUPPORTS_IS_ENUM() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ENUM_HPP
