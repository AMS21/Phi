#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_LVALUE_REFERENCE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_LVALUE_REFERENCE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"

#if PHI_HAS_INTRINSIC_IS_LVALUE_REFERENCE()
#    define PHI_IS_LVALUE_REFERENCE(type)      __is_lvalue_reference(type)
#    define PHI_SUPPORTS_IS_LVALUE_REFERENCE() 1
#else
#    define PHI_IS_LVALUE_REFERENCE(type)      false
#    define PHI_SUPPORTS_IS_LVALUE_REFERENCE() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_LVALUE_REFERENCE
#    define PHI_SUPPORTS_IS_LVALUE_REFERENCE() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_LVALUE_REFERENCE_HPP
