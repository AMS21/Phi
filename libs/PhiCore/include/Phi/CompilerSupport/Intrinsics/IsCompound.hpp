#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_COMPOUND_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_COMPOUND_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"

#if PHI_HAS_INTRINSIC_IS_COMPOUND()
#    define PHI_IS_COMPOUND(type)      __is_compound(type)
#    define PHI_SUPPORTS_IS_COMPOUND() 1
#else
#    define PHI_IS_COMPOUND(type)      false
#    define PHI_SUPPORTS_IS_COMPOUND() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_COMPOUND
#    define PHI_SUPPORTS_IS_COMPOUND() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_COMPOUND_HPP
