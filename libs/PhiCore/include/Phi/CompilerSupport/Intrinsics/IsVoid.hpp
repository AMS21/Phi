#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_VOID_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_VOID_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/Config/Compiler.hpp"

#if PHI_HAS_INTRINSIC_IS_VOID() && PHI_HAS_KEYWORD(__is_void)
#    define PHI_IS_VOID(type)      __is_void(type)
#    define PHI_SUPPORTS_IS_VOID() 1
#else
#    define PHI_IS_VOID(type)      false
#    define PHI_SUPPORTS_IS_VOID() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_VOID
#    define PHI_SUPPORTS_IS_VOID() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_VOID_HPP